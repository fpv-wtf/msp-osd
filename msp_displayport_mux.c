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

uint8_t frame_buffer[4196]; // buffer a whole frame of MSP commands until we get a draw command
uint8_t message_buffer[256]; // only needs to be the maximum size of an MSP packet, we only care to fwd MSP
uint8_t cursor = 0;
uint32_t fb_cursor = 0;

int pty_fd;
int serial_fd;
int socket_fd;

static volatile sig_atomic_t quit = 0;

static void sig_handler(int _)
{
    quit = 1;
}

static void msp_callback(msp_msg_t *msp_message)
{
    DEBUG_PRINT("MSP cmd %d with data len %d \n", msp_message->cmd, msp_message->size);

    // Process a received MSP message and decide whether to send it to the PTY (DJI) or UDP port (MSP-OSD on Goggles)
    if(msp_message->cmd == MSP_CMD_DISPLAYPORT) {
        if(fb_cursor > sizeof(frame_buffer)) {
            printf("Exhausted frame buffer!\n");
        }
        memcpy(&frame_buffer[fb_cursor], message_buffer, cursor);
        fb_cursor += cursor;
        cursor = 0;
        if(msp_message->payload[0] == 4) { // Draw command
            write(socket_fd, frame_buffer, fb_cursor);
            DEBUG_PRINT("DRAW! wrote %d bytes\n", fb_cursor);
            fb_cursor = 0;
        }
    } else {
        write(pty_fd, message_buffer, cursor);
        cursor = 0;
    }
}

int main(int argc, char *argv[]) {
    int opt;
    uint8_t fast_serial = 0;
    uint8_t serial_passthrough = 1;
    uint8_t poll_manually = 0;
    uint8_t msg_flip = 0;
    while((opt = getopt(argc, argv, "fsp")) != -1){
        switch(opt){
        case 'f':
            fast_serial = 1;
            printf("Configuring serial to 230400 baud\n");
            break;  
        case 's':
            serial_passthrough = 0;
            printf("Disabling serial passthrough, enabling filtering\n");
            break;
        case 'p':
            poll_manually = 1;
            printf("Enabling manual MSP polling every 500ms\n");
            break;
        case '?':
            printf("unknown option: %c\n", optopt);
            break;
        }
    }
  
    if((argc - optind) < 2) {
        printf("usage: msp_displayport_mux [-f] [-s] [-p] ipaddr serial_port [pty_target]\n-s : enable serial filtering\n-f : 230400 baud serial\n-p: enable manual polling\n");
        return 0;
    }

    char *ip_address = argv[optind];
    char *serial_port = argv[optind + 1];
    signal(SIGINT, sig_handler);
    struct pollfd poll_fds[2];
    const char *pty_name_ptr;
    msp_state_t *msp_state = calloc(1, sizeof(msp_state_t));
    msp_state->cb = &msp_callback;
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
        // We got serial data, process it as MSP data.
        if (0 < (serial_data_size = read(serial_fd, serial_data, sizeof(serial_data)))) {
            DEBUG_PRINT("RECEIVED data! length %d\n", serial_data_size);
            for (ssize_t i = 0; i < serial_data_size; i++) {
                if(msp_process_data(msp_state, serial_data[i]) == 0) {
                    // 0 -> MSP data was valid, so buffer it to forward on later
                    message_buffer[cursor] = serial_data[i];
                    cursor++;
                } else {
                    cursor = 0;
                }
            }
        }

        // If serial passthrough is enabled, send the message through verbatim.
        if(0 < (serial_data_size = read(pty_fd, serial_data, sizeof(serial_data))) && serial_passthrough) {
           DEBUG_PRINT("SEND data! length %d\n", serial_data_size);
           for (ssize_t i= 0; i < serial_data_size; i++) {
            DEBUG_PRINT("%02X ", serial_data[i]);
           }
           DEBUG_PRINT("\n");
           write(serial_fd, &serial_data, serial_data_size);
        }

        // If manual MSP polling is enabled, poll only for a few messages: arming status and battery voltage
        clock_gettime(CLOCK_MONOTONIC, &now);
        if(poll_manually && (now.tv_sec > last.tv_sec || now.tv_nsec > (last.tv_nsec + 50000000000))) {
            construct_msp_command(&serial_data, msg_flip ? MSP_CMD_STATUS : MSP_CMD_BATTERY_STATE, 0, 0);
            msg_flip = !msg_flip;
            DEBUG_PRINT("Polling: ");
            for(ssize_t i = 0; i < 6; i++) {
                DEBUG_PRINT("%02X ", serial_data[i]);
            }
            DEBUG_PRINT("\n");
            write(serial_fd, &serial_data, 6);
        }
        last = now;
    }
    close(serial_fd);
    close(pty_fd);
    close(socket_fd);
    free(msp_state);
}
