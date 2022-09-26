#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/poll.h>
#include <time.h>

#include "hw/dji_radio_shm.h"
#include "json/osd_config.h"
#include "net/data_protocol.h"
#include "net/network.h"
#include "net/serial.h"
#include "msp/msp.h"
#include "util/time_util.h"
#include "util/fs_util.h"

#define CPU_TEMP_PATH "/sys/devices/platform/soc/f0a00000.apb/f0a71000.omc/temp1"
#define AU_VOLTAGE_PATH "/sys/devices/platform/soc/f0a00000.apb/f0a71000.omc/voltage4"

#define FAST_SERIAL_KEY "fast_serial"
#define CACHE_SERIAL_KEY "cache_serial"

// The MSP_PORT is used to send MSP passthrough messages.
// The DATA_PORT is used to send arbitrary data - for example, bitrate and temperature data.

#define MSP_PORT 7654
#define DATA_PORT 7655

#ifdef DEBUG
#define DEBUG_PRINT(fmt, args...)    fprintf(stderr, fmt, ## args)
#else
#define DEBUG_PRINT(fmt, args...)
#endif

typedef struct msp_cache_entry_s {
    struct timespec time;
    msp_msg_t message;
} msp_cache_entry_t;

static msp_cache_entry_t *msp_message_cache[256]; // make a slot for all possible messages

static uint8_t frame_buffer[8192]; // buffer a whole frame of MSP commands until we get a draw command
static uint32_t fb_cursor = 0;

static uint8_t message_buffer[256]; // only needs to be the maximum size of an MSP packet, we only care to fwd MSP

static char current_fc_identifier[4];

int pty_fd;
int serial_fd;
int socket_fd;

static volatile sig_atomic_t quit = 0;
static uint8_t serial_passthrough = 1;

static void sig_handler(int _)
{
    quit = 1;
}

static uint8_t cache_msp_message(msp_msg_t *msp_message) {
    // 0 -> cache overwritten
    // 1 -> freshly cached
    uint8_t retval = 0;
    msp_cache_entry_t *cache_message = msp_message_cache[msp_message->cmd];
    if (cache_message == NULL) {
        DEBUG_PRINT("FC -> AU CACHE: no entry for msg %d, allocating\n", msp_message->cmd);
        cache_message = calloc(1, sizeof(msp_cache_entry_t));
        msp_message_cache[msp_message->cmd] = cache_message;
        retval = 1;
    }
    DEBUG_PRINT ("FC -> AU CACHE: refreshing %d\n", msp_message->cmd);
    memcpy(&cache_message->message, msp_message, sizeof(msp_msg_t));
    clock_gettime(CLOCK_MONOTONIC, &cache_message->time);
    return retval;
}

static int16_t msp_msg_from_cache(uint8_t msg_buffer[], uint8_t cmd_id) {
    // returns size of message or -1
    msp_cache_entry_t *cache_message = msp_message_cache[cmd_id];
    if (cache_message == NULL) {
        // cache missed, return -1 to trigger a serial send
        return -1;
    } else {
        // cache hit, let's see if it's too old
        // messages we care to expire after second boundary
        if(cmd_id == MSP_CMD_ANALOG
        || cmd_id == MSP_CMD_STATUS
        || cmd_id == MSP_CMD_BATTERY_STATE) {
            struct timespec now;
            clock_gettime(CLOCK_MONOTONIC, &now);
            if(now.tv_sec > cache_message->time.tv_sec) {
                // message is too old, invalidate cache and force a resend
                DEBUG_PRINT("MSP cache EXPIRED %d\n", cmd_id);
                free(cache_message);
                msp_message_cache[cmd_id] = 0;
                return -1;
            }
        }
        // message existed and was not stale, send it back
        return msp_data_from_msg(msg_buffer, &cache_message->message);
    }
}

static void rx_msp_callback(msp_msg_t *msp_message)
{
    // Process a received MSP message from FC and decide whether to send it to the PTY (DJI) or UDP port (MSP-OSD on Goggles)
    DEBUG_PRINT("FC->AU MSP msg %d with data len %d \n", msp_message->cmd, msp_message->size);
    if(msp_message->cmd == MSP_CMD_DISPLAYPORT) {
        // This was an MSP DisplayPort message, so buffer it until we get a whole frame.
        if(fb_cursor > sizeof(frame_buffer)) {
            printf("Exhausted frame buffer! Resetting...\n");
            fb_cursor = 0;
            return;
        }
        uint16_t size = msp_data_from_msg(message_buffer, msp_message);
        memcpy(&frame_buffer[fb_cursor], message_buffer, size);
        fb_cursor += size;
        if(msp_message->payload[0] == 4) {
            // Once we have a whole frame of data, send it to the goggles.
            write(socket_fd, frame_buffer, fb_cursor);
            DEBUG_PRINT("DRAW! wrote %d bytes\n", fb_cursor);
            fb_cursor = 0;
        }
    } else {
        uint16_t size = msp_data_from_msg(message_buffer, msp_message);
        // This is an FC Variant response, so we want to use it to set our FC variant.
        if(msp_message->cmd == MSP_CMD_FC_VARIANT) {
            DEBUG_PRINT("Got FC Variant response!\n");
            memcpy(current_fc_identifier, msp_message->payload, 4);
        }
        // This isn't an MSP DisplayPort message, so send it to either DJI directly or to the cache.
        if(serial_passthrough) {
            write(pty_fd, message_buffer, size);
        } else {
            // Serial passthrough is off, so cache the response we got.
            if(cache_msp_message(msp_message)) {
                // 1 -> cache miss, so this message expired or hasn't been seen.
                // this means DJI is waiting for it, so send it over
                DEBUG_PRINT("DJI was waiting, got msg %d\n", msp_message->cmd);
                for (int i = 0; i < size; i++) {
                    DEBUG_PRINT("%02X ", message_buffer[i]);
                }
                DEBUG_PRINT("\n");
                write(pty_fd, message_buffer, size);
            }
        }
    }
}

static void tx_msp_callback(msp_msg_t *msp_message)
{
    // We got a valid message from DJI asking for something. See if there's a response in the cache or not.
    // We can only get here if serial passthrough is off and caching is on, so no need to check again.
    DEBUG_PRINT("DJI->FC MSP msg %d with request len %d \n", msp_message->cmd, msp_message->size);
    uint8_t send_buffer[256];
    int16_t size;
    if(0 < (size = msp_msg_from_cache(send_buffer, msp_message->cmd))) {
        // cache hit, so write the cached message straight back to DJI
        DEBUG_PRINT("DJI->FC MSP CACHE HIT msg %d with response len %d \n", msp_message->cmd, size);
        for(int i = 0; i < size; i++) {
            DEBUG_PRINT("%02X ", send_buffer[i]);
        }
        DEBUG_PRINT("\n");
        write(pty_fd, send_buffer, size);
    } else {
        // cache miss, so write the DJI request to serial and wait for the FC to come back.
        DEBUG_PRINT("DJI->FC MSP CACHE MISS msg %d\n",msp_message->cmd);
        uint16_t size = msp_data_from_msg(message_buffer, msp_message);
        write(serial_fd, message_buffer, size);
    }
}

static void send_variant_request(int serial_fd) {
    uint8_t buffer[255];
    construct_msp_command(buffer, MSP_CMD_FC_VARIANT, NULL, 0, MSP_OUTBOUND);
    write(serial_fd, &buffer, 6);
}

static void send_data_packet(int data_socket_fd, dji_shm_state_t *dji_shm) {
    packet_data_t data;
    memset(&data, 0, sizeof(data));
    data.version_specifier = 0xFFFF;
    data.tx_temperature = get_int_from_fs(CPU_TEMP_PATH);
    data.tx_voltage = get_int_from_fs(AU_VOLTAGE_PATH);
    memcpy(data.fc_variant, current_fc_identifier, sizeof(current_fc_identifier));
    DEBUG_PRINT("got voltage %f V temp %d C variant %.4s\n", (float)(data.tx_voltage / 64.0f), data.tx_temperature, data.fc_variant);
    write(data_socket_fd, &data, sizeof(data));
}

int main(int argc, char *argv[]) {
    memset(current_fc_identifier, 0, sizeof(current_fc_identifier));

    int opt;
    uint8_t fast_serial = 0;
    uint8_t msp_command_number = 0;
    while((opt = getopt(argc, argv, "fsp")) != -1){
        switch(opt){
        case 'f':
            fast_serial = 1;
            break;
        case 's':
            serial_passthrough = 0;
            break;
        case '?':
            printf("unknown option: %c\n", optopt);
            break;
        }
    }

    if((argc - optind) < 2) {
        printf("usage: msp_displayport_mux [-f] [-s] ipaddr serial_port [pty_target]\n-s : enable serial caching\n-f : 230400 baud serial\n");
        return 0;
    }

    if(get_boolean_config_value(FAST_SERIAL_KEY)) {
        fast_serial = 1;
    }

    if(get_boolean_config_value(CACHE_SERIAL_KEY)) {
        serial_passthrough = 0;
    }

    if(fast_serial == 1) {
        printf("Configured to use 230400 baud rate. \n");
    }

    if(serial_passthrough == 0) {
        printf("Configured to use serial caching. \n");
    }

    dji_shm_state_t dji_radio;
    memset(&dji_radio, 0, sizeof(dji_radio));
    open_dji_radio_shm(&dji_radio);

    char *ip_address = argv[optind];
    char *serial_port = argv[optind + 1];
    signal(SIGINT, sig_handler);
    struct pollfd poll_fds[2];
    const char *pty_name_ptr;
    msp_state_t *rx_msp_state = calloc(1, sizeof(msp_state_t));
    msp_state_t *tx_msp_state = calloc(1, sizeof(msp_state_t));
    rx_msp_state->cb = &rx_msp_callback;
    tx_msp_state->cb = &tx_msp_callback;
    serial_fd = open_serial_port(serial_port, fast_serial ? B230400 : B115200);
    if (serial_fd <= 0) {
        printf("Failed to open serial port!\n");
        return 1;
    }
    pty_fd = open_pty(&pty_name_ptr);
    printf("Allocated PTY %s\n", pty_name_ptr);
    if ((argc - optind) > 2) {
        unlink(argv[optind + 2]);
        symlink(pty_name_ptr, argv[optind + 2]);   
        printf("Relinked %s to %s\n", argv[optind + 2], pty_name_ptr); 
    }
    socket_fd = connect_to_server(ip_address, MSP_PORT);
    int data_fd = connect_to_server(ip_address, DATA_PORT);
    uint8_t serial_data[256];
    ssize_t serial_data_size;
    struct timespec now, last;
    clock_gettime(CLOCK_MONOTONIC, &now);
    clock_gettime(CLOCK_MONOTONIC, &last);
    while (!quit) {
        poll_fds[0].fd = serial_fd;
        poll_fds[1].fd = pty_fd;
        poll_fds[0].events = POLLIN;
        poll_fds[1].events = POLLIN;

        poll(poll_fds, 2, 250);
        
        // We got inbound serial data, process it as MSP data.
        if (0 < (serial_data_size = read(serial_fd, serial_data, sizeof(serial_data)))) {
            DEBUG_PRINT("RECEIVED data! length %d\n", serial_data_size);
            for (ssize_t i = 0; i < serial_data_size; i++) {
                msp_process_data(rx_msp_state, serial_data[i]);
            }
        }
        // We got data from DJI (the pty), so see what to do next:
        if(0 < (serial_data_size = read(pty_fd, serial_data, sizeof(serial_data)))) {
            if (serial_passthrough) {
                // If serial passthrough is enabled, send the message through verbatim.
                DEBUG_PRINT("SEND data! length %d\n", serial_data_size);
                for (ssize_t i= 0; i < serial_data_size; i++) {
                    DEBUG_PRINT("%02X ", serial_data[i]);
                }
                DEBUG_PRINT("\n");
                write(serial_fd, &serial_data, serial_data_size);
            } else {
                // Otherwise, queue it up for processing by the MSP layer.
                DEBUG_PRINT("SEND data to MSP buffer! length %d\n", serial_data_size);
                for (ssize_t i = 0; i < serial_data_size; i++) {
                    msp_process_data(tx_msp_state, serial_data[i]);
                }
            }
        }
        clock_gettime(CLOCK_MONOTONIC, &now);
        if(timespec_subtract_ns(&now, &last) > (NSEC_PER_SEC / 2)) {
            // More than 500ms have elapsed, let's go ahead and send a data frame
            clock_gettime(CLOCK_MONOTONIC, &last);
            send_data_packet(data_fd, &dji_radio);
            if(current_fc_identifier[0] == 0) {
                send_variant_request(serial_fd);
            }
        }
    }
    close_dji_radio_shm(&dji_radio);
    close(serial_fd);
    close(pty_fd);
    close(socket_fd);
    close(data_fd);
    free(rx_msp_state);
    free(tx_msp_state);
}
