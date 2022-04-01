#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/poll.h>

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
    if(argc < 3) {
        printf("usage: msp_displayport_mux ipaddr serial_port [pty_target]");
        return 0;
    }
    char *ip_address = argv[1];
    char *serial_port = argv[2];
    signal(SIGINT, sig_handler);
    struct pollfd poll_fds[2];
    const char *pty_name_ptr;
    msp_state_t *msp_state = calloc(1, sizeof(msp_state_t));
    msp_state->cb = &msp_callback;
    serial_fd = open_serial_port(serial_port);
    if (serial_fd <= 0) {
        printf("Failed to open serial port!\n");
        return 1;
    }
    pty_fd = open_pty(&pty_name_ptr);
    printf("Allocated PTY %s\n", pty_name_ptr);
    if (argc > 3) {
        unlink(argv[1]);
        symlink(pty_name_ptr, argv[1]);   
        printf("Relinked %s to %s\n", argv[1], pty_name_ptr); 
    }
    socket_fd = connect_to_server(ip_address, PORT);
    uint8_t serial_data[256];
    ssize_t serial_data_size;
    while (!quit) {
        poll_fds[0].fd = serial_fd;
        poll_fds[1].fd = pty_fd;
        poll_fds[0].events = POLLIN;
        poll_fds[1].events = POLLIN;
        poll(poll_fds, 2, -1); 
        if (0 < (serial_data_size = read(serial_fd, serial_data, sizeof(serial_data)))) {
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
        if(0 < (serial_data_size = read(pty_fd, serial_data, sizeof(serial_data)))) {
           write(serial_fd, &serial_data, serial_data_size);
        }

    }
    close(serial_fd);
    close(pty_fd);
    close(socket_fd);
    free(msp_state);
}
