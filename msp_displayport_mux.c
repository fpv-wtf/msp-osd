#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/poll.h>
#include <time.h>

#include "network.h"
#include "serial.h"
#include "msp.h"

#define PORT 7654

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

static uint8_t frame_buffer[4196]; // buffer a whole frame of MSP commands until we get a draw command
static uint32_t fb_cursor = 0;

static uint8_t rx_message_buffer[256]; // only needs to be the maximum size of an MSP packet, we only care to fwd MSP
static uint8_t rx_cursor = 0;

static uint8_t tx_message_buffer[256];
static uint8_t tx_cursor = 0;

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
        DEBUG_PRINT("no entry for msg %d, allocating\n", msp_message->cmd);
        cache_message = calloc(1, sizeof(msp_cache_entry_t));
        msp_message_cache[msp_message->cmd] = cache_message;
        retval = 1;
    }
    memcpy(&cache_message->message, msp_message, sizeof(msp_message));
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
                free(cache_message);
                msp_message_cache[cmd_id] = 0;
                return -1;
            }
        }
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
            printf("Exhausted frame buffer!\n");
        }
        memcpy(&frame_buffer[fb_cursor], rx_message_buffer, rx_cursor);
        fb_cursor += rx_cursor;
        rx_cursor = 0;
        if(msp_message->payload[0] == 4) {
            // Once we have a whole frame of data, send it to the goggles.
            write(socket_fd, frame_buffer, fb_cursor);
            DEBUG_PRINT("DRAW! wrote %d bytes\n", fb_cursor);
            fb_cursor = 0;
        }
    } else {
        // This isn't an MSP DisplayPort message, so send it to either DJI directly or to the cache.
        if(serial_passthrough) {
            // Serial passthrough is on, so send it straight to DJI.
            write(pty_fd, rx_message_buffer, rx_cursor);
        } else {
            // Serial passthrough is off, so cache the response we got.
            if(cache_msp_message(msp_message)) {
                // 1 -> cache miss, so this message expired or hasn't been seen. this means DJI is waiting for it, so send it over
                write(pty_fd, rx_message_buffer, rx_cursor);
            }
        }
        rx_cursor = 0;
    }
}

static void tx_msp_callback(msp_msg_t *msp_message)
{
    // We got a valid message from DJI asking for something. See if there's a response in the cache or not.
    // We can only get here if serial passthrough is off and caching is on, so no need to check again.
    DEBUG_PRINT("DJI->FC MSP msg %d with data len %d \n", msp_message->cmd, msp_message->size);
    uint8_t send_buffer[256];
    uint16_t size;
    if(0 < (size = msp_msg_from_cache(send_buffer, msp_message->cmd))) {
        // cache hit, so write the cached message straight back to DJI
        DEBUG_PRINT("DJI->FC MSP CACHE HIT %d with data len %d \n", msp_message->cmd, size);
        write(pty_fd, send_buffer, size);
    } else {
        // cache miss, so write the DJI request to serial and wait for the FC to come back.
        DEBUG_PRINT("DJI->FC MSP CACHE MISS %d\n",msp_message->cmd);
        write(serial_fd, tx_message_buffer, tx_cursor);
    }
    tx_cursor = 0;
}

int main(int argc, char *argv[]) {
    int opt;
    uint8_t fast_serial = 0;
    uint8_t msp_command_number = 0;
    while((opt = getopt(argc, argv, "fsp")) != -1){
        switch(opt){
        case 'f':
            fast_serial = 1;
            printf("Configuring serial to 230400 baud\n");
            break;  
        case 's':
            serial_passthrough = 0;
            printf("Disabling serial passthrough, enabling caching\n");
            break;
        case '?':
            printf("unknown option: %c\n", optopt);
            break;
        }
    }
  
    if((argc - optind) < 2) {
        printf("usage: msp_displayport_mux [-f] [-s] [-p] ipaddr serial_port [pty_target]\n-s : enable serial caching\n-f : 230400 baud serial\n");
        return 0;
    }

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
    socket_fd = connect_to_server(ip_address, PORT);
    uint8_t serial_data[256];
    ssize_t serial_data_size;
    struct timespec now, last;
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
                if(msp_process_data(rx_msp_state, serial_data[i]) == 0) {
                    // 0 -> MSP data was valid, so buffer it to forward on to either goggles or DJI later
                    rx_message_buffer[rx_cursor] = serial_data[i];
                    rx_cursor++;
                } else {
                    rx_cursor = 0;
                }
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
                    if(msp_process_data(tx_msp_state, serial_data[i]) == 0) {
                        // 0 -> MSP data was valid, so buffer it to forward on later
                        tx_message_buffer[tx_cursor] = serial_data[i];
                        tx_cursor++;
                    } else {
                        tx_cursor = 0;
                    }
                }
            }
        }
    }
    close(serial_fd);
    close(pty_fd);
    close(socket_fd);
    free(rx_msp_state);
    free(tx_msp_state);
}
