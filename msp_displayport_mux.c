#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "network.h"
#include "serial.h"
#include "msp.h"

#define SERIAL_PORT "/dev/ttyS1"
#define IP_ADDRESS "192.168.41.2"
#define PORT 7654

uint8_t message_buffer[256]; // only needs to be the maximum size of an MSP packet, we only care to fwd MSP
uint8_t cursor = 0;
int pty_fd;
int serial_fd;
int socket_fd;

void msp_callback(msp_msg_t *msp_message)
{
    if(msp_message->cmd == MSP_CMD_DISPLAYPORT) {
        write(socket_fd, &message_buffer, cursor);
        cursor = 0;
    } else {
        write(pty_fd, &message_buffer, cursor);
        cursor = 0;
    }
}

int main() {
    const char *pty_name_ptr;
    msp_state_t *msp_state = calloc(1, sizeof(msp_state_t));
    msp_state->cb = &msp_callback;
    serial_fd = open_serial_port(SERIAL_PORT);
    pty_fd = open_pty(&pty_name_ptr);
    printf("%s", pty_name_ptr);
    socket_fd = connect_to_server(IP_ADDRESS, PORT);
    uint8_t serial_byte = 0;
    uint8_t pty_byte = 0;
    uint8_t exit = 0;
    while (!exit) {
        if (read(serial_fd, &serial_byte, 1) > 0) {
            if(msp_process_data(msp_state, serial_byte) == 0) {
                // 0 -> MSP data was valid, so buffer it to forward on later
                message_buffer[cursor] = serial_byte;
                cursor++;
            }
        }
        if(read(pty_fd, &pty_byte, 1) > 0) {
           write(serial_fd, &pty_byte, 1);
        }
    }
    close(serial_fd);
    close(pty_fd);
    close(socket_fd);
    free(msp_state);
}
