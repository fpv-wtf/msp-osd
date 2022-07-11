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
#include <time.h>
#include <linux/input.h>

#include "dji_display.h"
#include "dji_services.h"
#include "network.h"
#include "msp.h"
#include "msp_displayport.h"

#define OSD_WIDTH 31
#define OSD_HEIGHT 15

#define X_OFFSET 180
#define Y_OFFSET 0

#define PORT 7654

#define WIDTH 1440
#define HEIGHT 810
#define BYTES_PER_PIXEL 4
#define PLANE_ID 6

#define FONT_WIDTH 36
#define FONT_HEIGHT 54

#define INPUT_FILENAME "/dev/input/event0"
#define SPLASH_STRING "MSP OSD WAITING FOR DATA..."
#define SHUTDOWN_STRING "MSP OSD SHUTTING DOWN..."

#define FALLBACK_FONT_PATH "/blackbox/font.bin"
#define ENTWARE_FONT_PATH "/opt/fonts/font.bin"
#define SDCARD_FONT_PATH "/storage/sdcard0/font.bin"
#define FONT_FILE_SIZE 1990656

#define EV_CODE_BACK 0xc9

#define BACK_BUTTON_DELAY 4

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
    if ((x > (OSD_WIDTH - 1)) || (y > (OSD_HEIGHT - 1))) {
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

static int open_font(const char *filename, void** font) {
    printf("Opening font: %s\n", filename);
    struct stat st;
    stat(filename, &st);
    size_t filesize = st.st_size;
    if(filesize != FONT_FILE_SIZE) {
        return -1;
    }
    int fd = open(filename, O_RDONLY, 0);
    if (!fd) {
        return -1;
    }
    void* mmappedData = mmap(NULL, filesize, PROT_READ, MAP_PRIVATE, fd, 0);
    assert(mmappedData != MAP_FAILED);
    // there is no need to keep an FD open after mmap
    close(fd);
    *font = mmappedData;
    return 0;
}

static void close_font(void *font) {
    munmap(font, FONT_FILE_SIZE);
}

static void display_print_string(const char *string, uint8_t len) {
    for(int x = 0; x < len; x++) {
        character_map[x][OSD_HEIGHT - 2] = string[x];
    }
    draw_complete();
}

static void start_display(uint8_t is_v2_goggles) {
    memset(character_map, 0, sizeof(character_map));
    dji_display = dji_display_state_alloc(is_v2_goggles);
    dji_display_open_framebuffer(dji_display, PLANE_ID);
    display_print_string(SPLASH_STRING, sizeof(SPLASH_STRING));
}

static void stop_display() {
    display_print_string(SHUTDOWN_STRING, sizeof(SHUTDOWN_STRING));
    dji_display_close_framebuffer(dji_display);
    dji_display_state_free(dji_display);
}

static void load_font() {
    if (open_font(SDCARD_FONT_PATH, &font) < 0) {
        if (open_font(ENTWARE_FONT_PATH, &font) < 0) {
          open_font(FALLBACK_FONT_PATH, &font);
        }
    }
}

int main(int argc, char *argv[])
{
    signal(SIGINT, sig_handler);

    uint8_t is_v2_goggles = dji_goggles_are_v2();
    printf("Detected DJI goggles %s\n", is_v2_goggles ? "V2" : "V1");

    display_driver = calloc(1, sizeof(displayport_vtable_t));
    display_driver->draw_character = &draw_character;
    display_driver->clear_screen = &clear_screen;
    display_driver->draw_complete = &draw_complete;

    msp_state_t *msp_state = calloc(1, sizeof(msp_state_t));
    msp_state->cb = &msp_callback;

    int event_fd = open(INPUT_FILENAME, O_RDONLY);
    assert(event_fd > 0);

    int socket_fd = bind_socket(PORT);
    printf("started up, listening on port %d\n", PORT);

    struct pollfd poll_fds[2];
    int recv_len = 0;
    uint8_t byte = 0;
    uint8_t buffer[4096];
    struct sockaddr_storage src_addr;
    socklen_t src_addr_len=sizeof(src_addr);
    struct input_event ev;
    struct timespec button_start, display_start, now;
    memset(&display_start, 0, sizeof(display_start));
    memset(&button_start, 0, sizeof(button_start));

    enum display_mode_s {
        DISPLAY_DISABLED = 0,
        DISPLAY_RUNNING = 1,
        DISPLAY_WAITING = 2
    } display_mode = DISPLAY_DISABLED;

    while (!quit)
    {
        clock_gettime(CLOCK_MONOTONIC, &now);
        if(display_mode == DISPLAY_WAITING && display_start.tv_sec > 0 && ((now.tv_sec - display_start.tv_sec) > 1)) {
            // Wait 1 second between stopping Glasses service and trying to start OSD.
            memset(&display_start, 0, sizeof(display_start));
            load_font();
            start_display(is_v2_goggles);
            display_mode = DISPLAY_RUNNING;
        }
        if(button_start.tv_sec > 0 && ((now.tv_sec - button_start.tv_sec) > BACK_BUTTON_DELAY)) {
            // We held the back button down for 5 seconds.
            memset(&button_start, 0, sizeof(button_start));
            if (display_mode == DISPLAY_DISABLED) {
                printf("Switching Disabled -> Enabled!\n");
                dji_stop_goggles(is_v2_goggles);
                clock_gettime(CLOCK_MONOTONIC, &display_start);
                display_mode = DISPLAY_WAITING;
            } else {
                printf("Switching Enabled/Waiting -> Disabled!\n");
                if(display_mode == DISPLAY_RUNNING)
                    stop_display();
                close_font(font);
                display_mode = DISPLAY_DISABLED;
                dji_start_goggles(is_v2_goggles);
            }
        }

        poll_fds[0].fd = socket_fd;
        poll_fds[0].events = POLLIN;
        poll_fds[1].fd = event_fd;
        poll_fds[1].events = POLLIN;
        poll(poll_fds, 2, 100);

        if(poll_fds[1].revents) {
            read(event_fd, &ev, sizeof(struct input_event));
            if(ev.code == EV_CODE_BACK) {
                if(ev.value == 1) {
                    clock_gettime(CLOCK_MONOTONIC, &button_start);
                } else {
                    memset(&button_start, 0, sizeof(button_start));
                }
            }
            DEBUG_PRINT("input type: %i, code: %i, value: %i\n", ev.type, ev.code, ev.value);
        }
        if(poll_fds[0].revents) {
            // Got UDP packet
            if (0 < (recv_len = recvfrom(socket_fd,&buffer,sizeof(buffer),0,(struct sockaddr*)&src_addr,&src_addr_len)))
            {
                DEBUG_PRINT("got packet len %d\n", recv_len);
                if(display_mode == DISPLAY_RUNNING) {
                    for (int i=0; i<recv_len; i++)
                        msp_process_data(msp_state, buffer[i]);
                }
            }
        }
    }
    if(display_mode == DISPLAY_RUNNING) {
        stop_display();
    }
    free(display_driver);
    free(msp_state);
    close(socket_fd);
    close(event_fd);

    return 0;
}
