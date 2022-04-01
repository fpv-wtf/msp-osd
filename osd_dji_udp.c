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
#include <sys/poll.h>

#include "dji_display.h"
#include "network.h"
#include "msp.h"
#include "msp_displayport.h"

#define OSD_WIDTH 31
#define OSD_HEIGHT 16

#define X_OFFSET 180
#define Y_OFFSET 0

#define PORT 7654

#define WIDTH 1440
#define HEIGHT 810
#define BYTES_PER_PIXEL 4
#define PLANE_ID 6

#define FONT_WIDTH 36
#define FONT_HEIGHT 54

#ifdef DEBUG
#define DEBUG_PRINT(fmt, args...)    fprintf(stderr, fmt, ## args)
#else
#define DEBUG_PRINT(fmt, args...)
#endif

#define SWAP32(data)   \
( (((data) >> 24) & 0x000000FF) | (((data) >>  8) & 0x0000FF00) | \
  (((data) <<  8) & 0x00FF0000) | (((data) << 24) & 0xFF000000) ) 

static volatile sig_atomic_t quit = 0;
dji_display_state_t *dji_display;
uint8_t character_map[OSD_WIDTH][OSD_HEIGHT];
displayport_vtable_t *display_driver;
void *font;
uint8_t which_fb = 0;

static void sig_handler(int _)
{
    quit = 1;
}

static void draw_character(uint32_t x, uint32_t y, uint8_t c)
{
    if (x > OSD_WIDTH - 1 || y > OSD_HEIGHT - 1) {
        return;
    }
    character_map[x][y] = c;
}

static void draw_screen() {
    void *fb_addr = dji_display_get_fb_address(dji_display, which_fb);
    // DJI has a backwards alpha channel - FF is transparent, 00 is opaque.
    memset(fb_addr, 0x000000FF, WIDTH * HEIGHT * BYTES_PER_PIXEL);
    for(int y = 0; y < OSD_HEIGHT; y++) {
        for(int x = 0; x < OSD_WIDTH; x++) {
            uint8_t c = character_map[x][y];
            if (c != 0) {
                uint32_t pixel_x = (x * FONT_WIDTH) + X_OFFSET;
                uint32_t pixel_y = (y * FONT_HEIGHT) + Y_OFFSET;
                uint32_t character_offset = (((FONT_HEIGHT * FONT_WIDTH) * BYTES_PER_PIXEL) * c);
                for(uint8_t gx = 0; gx < FONT_WIDTH; gx++) {
                    for(uint8_t gy = 0; gy < FONT_HEIGHT; gy++) {
                        uint32_t font_offset = character_offset + (gy * FONT_WIDTH * BYTES_PER_PIXEL) + (gx * BYTES_PER_PIXEL);
                        uint32_t target_offset = ((((pixel_x + gx) * BYTES_PER_PIXEL) + ((pixel_y + gy) * WIDTH * BYTES_PER_PIXEL)));
                        *((uint8_t *)fb_addr + target_offset) = *(uint8_t *)((uint8_t *)font + font_offset + 2);        
                        *((uint8_t *)fb_addr + target_offset + 1) = *(uint8_t *)((uint8_t *)font + font_offset + 1);    
                        *((uint8_t *)fb_addr + target_offset + 2) = *(uint8_t *)((uint8_t *)font + font_offset);   
                        *((uint8_t *)fb_addr + target_offset + 3) = ~*(uint8_t *)((uint8_t *)font + font_offset + 3);  
                    }
                }
                DEBUG_PRINT("%c", c > 31 ? c : 20);
            }
            DEBUG_PRINT(" ");
        }
        DEBUG_PRINT("\n");
    }   
}

static void clear_screen()
{
    memset(character_map, 0, sizeof(character_map));
}

static void draw_complete() {
    draw_screen();
    dji_display_push_frame(dji_display, which_fb);
    which_fb = !which_fb;
    DEBUG_PRINT("drew a frame\n"); 
}

static void msp_callback(msp_msg_t *msp_message)
{
    displayport_process_message(display_driver, msp_message);
}

static void *open_font(const char *filename) {
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
    struct pollfd poll_fds[1];

    signal(SIGINT, sig_handler);
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
    
    int socket_fd = bind_socket(PORT);
    printf("started up, listening on port %d\n", PORT);

    // Draw an empty screen to get transparency back
    draw_screen();

    int recv_len = 0;
    uint8_t byte = 0;
    uint8_t buffer[4096];
    struct sockaddr_storage src_addr;
    socklen_t src_addr_len=sizeof(src_addr);

    while (!quit)
    {
        poll_fds[0].fd = socket_fd;
        poll_fds[0].events = POLLIN;
        poll(poll_fds, 1, -1);    
        if (0 < (recv_len = recvfrom(socket_fd,&buffer,sizeof(buffer),0,(struct sockaddr*)&src_addr,&src_addr_len)))
        {
            DEBUG_PRINT("got packet len %d\n", recv_len);
            for (int i=0; i<recv_len; i++)
                msp_process_data(msp_state, buffer[i]);
        }
    }
    dji_display_close_framebuffer(dji_display);
    dji_display_state_free(dji_display);
    free(display_driver);
    free(msp_state);
    return 0;
}