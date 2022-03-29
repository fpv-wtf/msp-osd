#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <assert.h>

#include "dji_display.h"

#include "msp.h"
#include "msp_displayport.h"

#define OSD_WIDTH 30
#define OSD_HEIGHT 16

#define SERVER "10.211.55.4"
#define PORT 5762

#define WIDTH 1440
#define HEIGHT 810
#define BYTES_PER_PIXEL 4
#define PLANE_ID 6

#define FONT_WIDTH 36
#define FONT_HEIGHT 54


dji_display_state_t *dji_display;
uint8_t character_map[OSD_WIDTH][OSD_HEIGHT];
displayport_vtable_t *display_driver;
uint8_t *font;

void draw_character(uint32_t x, uint32_t y, uint8_t c)
{
    if (x > OSD_WIDTH || y > OSD_HEIGHT) {
        return;
    }
    character_map[x][y] = c;
}

void draw_screen() {
    memset(dji_display->fb0_virtual_addr, 0, WIDTH * HEIGHT * BYTES_PER_PIXEL);
    for(int y = 0; y < OSD_HEIGHT; y++) {
        for(int x = 0; x < OSD_WIDTH; x++) {
            uint8_t c = character_map[x][y];
            if (c != 0) {
                printf("%c", c > 31 ? c : 20);
                memcpy(((uint8_t *)dji_display->fb0_virtual_addr + ((x * FONT_WIDTH) + (y * FONT_HEIGHT * WIDTH) * BYTES_PER_PIXEL)), (font + (y * FONT_HEIGHT * FONT_WIDTH * c)), FONT_WIDTH * FONT_HEIGHT * BYTES_PER_PIXEL);
            }
            printf(" ");
        }
        printf("\n");
    }
    dji_display_push_frame(dji_display, dji_display->fb_0);
}

void clear_screen()
{
    printf("clear\n");
    memset(character_map, 0, sizeof(character_map));
}

void draw_complete() {
    printf("draw complete!\n");
}

void msp_callback(msp_msg_t *msp_message)
{
    displayport_process_message(display_driver, msp_message);
    draw_screen();
}

int connect_to_server(char *address)
{
    int sockfd, connfd;
    struct sockaddr_in servaddr;

    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        printf("socket failed!\n");
        exit(0);
    }
    else
        printf("socket created!\n");

    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(address);
    servaddr.sin_port = htons(PORT);

    if (connect(sockfd, &servaddr, sizeof(servaddr)) != 0)
    {
        printf("connection failed!\n");
        exit(0);
    }
    else
        printf("connected!\n");
    fcntl(sockfd, F_SETFL, O_NONBLOCK);
    return sockfd;
}

uint8_t *open_font(const char *filename) {
    struct stat st;
    stat(filename, &st);
    size_t filesize = st.st_size;
    int fd = open(filename, O_RDONLY, 0);
    assert(fd != -1);
    void* mmappedData = mmap(NULL, filesize, PROT_READ, MAP_PRIVATE, fd, 0);
    assert(mmappedData != MAP_FAILED);
    return mmappedData;
}

int main(int argc, char *args[])
{
    memset(character_map, 0, sizeof(character_map));
    dji_display = dji_display_state_alloc();
    dji_display_open_framebuffer(dji_display, PLANE_ID);

    font = open_font("font.bin");
    
    display_driver = calloc(1, sizeof(displayport_vtable_t));
    display_driver->draw_character = &draw_character;
    display_driver->clear_screen = &clear_screen;
    display_driver->draw_complete = &draw_complete;

    msp_state_t *msp_state = calloc(1, sizeof(msp_state_t));
    msp_state->cb = &msp_callback;
    
    int socket_fd = connect_to_server(SERVER);

    uint8_t quit = 0;
    while (!quit)
    {   
        uint8_t byte = 0;
        if (read(socket_fd, &byte, 1) > 0)
            msp_process_data(msp_state, byte);
    }
    dji_display_close_framebuffer(dji_display);
    dji_display_state_free(dji_display);
    free(display_driver);
    return 0;
}