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

#include "hw/dji_display.h"
#include "hw/dji_radio_shm.h"
#include "hw/dji_services.h"
#include "net/network.h"
#include "net/data_protocol.h"
#include "msp/msp.h"
#include "msp/msp_displayport.h"
#include "util/fs_util.h"

#define MSP_PORT 7654
#define DATA_PORT 7655

#define WIDTH 1440
#define HEIGHT 810
#define BYTES_PER_PIXEL 4
#define PLANE_ID 6

#define NUM_CHARS 256

#define INPUT_FILENAME "/dev/input/event0"
#define SPLASH_STRING "OSD WAITING..."
#define SHUTDOWN_STRING "SHUTTING DOWN..."

#define FALLBACK_FONT_PATH "/blackbox/font"
#define ENTWARE_FONT_PATH "/opt/fonts/font"
#define SDCARD_FONT_PATH "/storage/sdcard0/font"

#define GOGGLES_VOLTAGE_PATH "/sys/devices/platform/soc/f0a00000.apb/f0a71000.omc/voltage5"

#define EV_CODE_BACK 0xc9

#define BACK_BUTTON_DELAY 4
#define BACK_BUTTON_DOUBLETAP_TIME 2
#define CYCLE_SLEEP_TIME 9

#ifdef DEBUG
#define DEBUG_PRINT(fmt, args...)    fprintf(stderr, fmt, ## args)
#else
#define DEBUG_PRINT(fmt, args...)
#endif

#define SWAP32(data)   \
( (((data) >> 24) & 0x000000FF) | (((data) >>  8) & 0x0000FF00) | \
  (((data) <<  8) & 0x00FF0000) | (((data) << 24) & 0xFF000000) )

#define MAX_DISPLAY_X 50
#define MAX_DISPLAY_Y 18

typedef struct display_info_s {
    uint8_t char_width;
    uint8_t char_height;
    uint8_t font_width;
    uint8_t font_height;
    uint16_t x_offset;
    uint16_t y_offset;
    void *font_page_1;
    void *font_page_2;
} display_info_t;

static volatile sig_atomic_t quit = 0;
static dji_display_state_t *dji_display;
static uint16_t msp_character_map[MAX_DISPLAY_X][MAX_DISPLAY_Y];
static uint16_t overlay_character_map[MAX_DISPLAY_X][MAX_DISPLAY_Y];
static displayport_vtable_t *display_driver;
static uint8_t which_fb = 0;

static display_info_t sd_display_info = {
    .char_width = 31,
    .char_height = 15,
    .font_width = 36,
    .font_height = 54,
    .x_offset = 180,
    .y_offset = 0,
    .font_page_1 = NULL,
    .font_page_2 = NULL,
};

static display_info_t hd_display_info = {
    .char_width = 50,
    .char_height = 18,
    .font_width = 24,
    .font_height = 36,
    .x_offset = 120,
    .y_offset = 80,
    .font_page_1 = NULL,
    .font_page_2 = NULL,
};

static display_info_t overlay_display_info = {
    .char_width = 20,
    .char_height = 10,
    .font_width = 24,
    .font_height = 36,
    .x_offset = 960,
    .y_offset = 450,
    .font_page_1 = NULL,
    .font_page_2 = NULL,
};

static display_info_t *current_display_info;

static void sig_handler(int _)
{
    quit = 1;
}

static void draw_character(display_info_t *display_info, uint16_t character_map[MAX_DISPLAY_X][MAX_DISPLAY_Y], uint32_t x, uint32_t y, uint16_t c)
{
    if ((x > (display_info->char_width - 1)) || (y > (display_info->char_height - 1))) {
        return;
    }
    character_map[x][y] = c;
}

static void msp_draw_character(uint32_t x, uint32_t y, uint16_t c) {
    draw_character(current_display_info, msp_character_map, x, y, c);
}

static void draw_character_map(display_info_t *display_info, void *fb_addr, uint16_t character_map[MAX_DISPLAY_X][MAX_DISPLAY_Y]) {
    if (display_info->font_page_1 == NULL) {
        // give up if we don't have a font loaded
        return;
    }
    void *font;
    for(int y = 0; y < display_info->char_height; y++) {
        for(int x = 0; x < display_info->char_width; x++) {
            uint16_t c = character_map[x][y];
            if (c != 0) {
                font = display_info->font_page_1;
                if (c > 255) {
                    c = c & 0xFF;
                    if (display_info->font_page_2 != NULL) {
                        // fall back to writing page 1 chars if we don't have a page 2 font
                        font = display_info->font_page_2;
                    }
                }
                uint32_t pixel_x = (x * display_info->font_width) + display_info->x_offset;
                uint32_t pixel_y = (y * display_info->font_height) + display_info->y_offset;
                uint32_t character_offset = (((display_info->font_height * display_info->font_width) * BYTES_PER_PIXEL) * c);
                for(uint8_t gx = 0; gx < display_info->font_width; gx++) {
                    for(uint8_t gy = 0; gy < display_info->font_height; gy++) {
                        uint32_t font_offset = character_offset + (gy * display_info->font_width * BYTES_PER_PIXEL) + (gx * BYTES_PER_PIXEL);
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

static void draw_screen() {
    void *fb_addr = dji_display_get_fb_address(dji_display, which_fb);
    // DJI has a backwards alpha channel - FF is transparent, 00 is opaque.
    memset(fb_addr, 0x000000FF, WIDTH * HEIGHT * BYTES_PER_PIXEL);

    draw_character_map(current_display_info, fb_addr, msp_character_map);
    draw_character_map(&overlay_display_info, fb_addr, overlay_character_map);
}

static void msp_clear_screen()
{
    memset(msp_character_map, 0, sizeof(msp_character_map));
}

static void msp_draw_complete() {
    draw_screen();
    dji_display_push_frame(dji_display, which_fb);
    which_fb = !which_fb;
    DEBUG_PRINT("drew a frame\n");
}

static void msp_callback(msp_msg_t *msp_message)
{
    displayport_process_message(display_driver, msp_message);
}

static void get_font_path_with_prefix(char *font_path_dest, const char *font_path, uint8_t len, uint8_t is_hd, uint8_t page) {
    char name_buf[len];
    if (is_hd) {
        snprintf(name_buf, len, "%s_hd", font_path);
    } else {
        snprintf(name_buf, len, "%s", font_path);
    }
    if (page > 0) {
        snprintf(font_path_dest, len, "%s_%d.bin", name_buf, page + 1);
    } else {
        snprintf(font_path_dest, len, "%s.bin", name_buf);
    }
}

static int open_font(const char *filename, void** font, uint8_t page, uint8_t is_hd) {
    char file_path[255];
    get_font_path_with_prefix(file_path, filename, 255, is_hd, page);
    printf("Opening font: %s\n", file_path);
    struct stat st;
    memset(&st, 0, sizeof(st));
    stat(file_path, &st);
    size_t filesize = st.st_size;
    display_info_t display_info = is_hd ? hd_display_info : sd_display_info;
    size_t desired_filesize = display_info.font_height *  display_info.font_width * NUM_CHARS * BYTES_PER_PIXEL;
    if(filesize != desired_filesize) {
        if (filesize != 0) {
            printf("Font was wrong size: %s %d != %d\n", file_path, filesize, desired_filesize);
        }
        return -1;
    }
    int fd = open(file_path, O_RDONLY, 0);
    if (!fd) {
        printf("Could not open file %s\n", file_path);
        return -1;
    }
    void* mmappedData = mmap(NULL, filesize, PROT_READ, MAP_PRIVATE, fd, 0);
    // there is no need to keep an FD open after mmap
    close(fd);
    if (mmappedData != MAP_FAILED) {
        *font = mmappedData;
    } else {
        printf("Could not map font %s\n", file_path);
        *font = 0;
    }
    return 0;
}

static void load_font() {
    if (open_font(SDCARD_FONT_PATH, &sd_display_info.font_page_1, 0, 0) < 0) {
        if (open_font(ENTWARE_FONT_PATH, &sd_display_info.font_page_1, 0, 0) < 0) {
          open_font(FALLBACK_FONT_PATH, &sd_display_info.font_page_1, 0, 0);
        }
    }
    if (open_font(SDCARD_FONT_PATH, &sd_display_info.font_page_2, 1, 0) < 0) {
        if (open_font(ENTWARE_FONT_PATH, &sd_display_info.font_page_2, 1, 0) < 0) {
          open_font(FALLBACK_FONT_PATH, &sd_display_info.font_page_2, 1, 0);
        }
    }
    if (open_font(SDCARD_FONT_PATH, &hd_display_info.font_page_1, 0, 1) < 0) {
        if (open_font(ENTWARE_FONT_PATH, &hd_display_info.font_page_1, 0, 1) < 0) {
          open_font(FALLBACK_FONT_PATH, &hd_display_info.font_page_1, 0, 1);
        }
    }
    if (open_font(SDCARD_FONT_PATH, &hd_display_info.font_page_2, 1, 1) < 0) {
        if (open_font(ENTWARE_FONT_PATH, &hd_display_info.font_page_2, 1, 1) < 0) {
          open_font(FALLBACK_FONT_PATH, &hd_display_info.font_page_2, 1, 1);
        }
    }
    if (open_font(SDCARD_FONT_PATH, &overlay_display_info.font_page_1, 0, 1) < 0) {
        if (open_font(ENTWARE_FONT_PATH, &overlay_display_info.font_page_1, 0, 1) < 0) {
          open_font(FALLBACK_FONT_PATH, &overlay_display_info.font_page_1, 0, 1);
        }
    }
    if (open_font(SDCARD_FONT_PATH, &overlay_display_info.font_page_2, 1, 1) < 0) {
        if (open_font(ENTWARE_FONT_PATH, &overlay_display_info.font_page_2, 1, 1) < 0) {
          open_font(FALLBACK_FONT_PATH, &overlay_display_info.font_page_2, 1, 1);
        }
    }
}

static void close_fonts(display_info_t *display_info) {
    if (display_info->font_page_1 != NULL)
    {
        munmap(display_info->font_page_1, display_info->font_height * display_info->font_width * NUM_CHARS * 4);
    }
    if (display_info->font_page_2 != NULL)
    {
        munmap(display_info->font_page_2, display_info->font_height * display_info->font_width * NUM_CHARS * 4);
    }
}

static void msp_set_options(uint8_t font_num, uint8_t is_hd) {
    msp_clear_screen();
    if(is_hd) {
        current_display_info = &hd_display_info;
    } else {
        current_display_info = &sd_display_info;
    }
}

static void display_print_string(uint8_t init_x, uint8_t y, const char *string, uint8_t len) {
    for(uint8_t x = 0; x < len; x++) {
        draw_character(&overlay_display_info, overlay_character_map, x + init_x, y, string[x]);
    }
}

static void start_display(uint8_t is_v2_goggles) {
    memset(msp_character_map, 0, sizeof(msp_character_map));
    memset(overlay_character_map, 0, sizeof(overlay_character_map));

    dji_display = dji_display_state_alloc(is_v2_goggles);
    dji_display_open_framebuffer(dji_display, PLANE_ID);
    display_print_string(0, overlay_display_info.char_height -1, SPLASH_STRING, sizeof(SPLASH_STRING));
    msp_draw_complete();
}

static void stop_display() {
    display_print_string(0, overlay_display_info.char_height -1, SHUTDOWN_STRING, sizeof(SHUTDOWN_STRING));
    dji_display_close_framebuffer(dji_display);
    dji_display_state_free(dji_display);
}

static void process_data_packet(uint8_t *buf, int len, dji_shm_state_t *radio_shm) {
    packet_data_t *packet = (packet_data_t *)buf;
    DEBUG_PRINT("got data %f mbit %d C %f V\n", packet->tx_bitrate / 1000.0f, packet->tx_temperature, packet->tx_voltage / 64.0f);
    memset(overlay_character_map, 0, sizeof(overlay_character_map));
    char str[8];
    snprintf(str, 8, "%2.1fMB ", packet->tx_bitrate / 1000.0f);
    display_print_string(overlay_display_info.char_width - 6, overlay_display_info.char_height - 5, str, 6);
    uint16_t latency = dji_radio_latency_ms(radio_shm);
    snprintf(str, 8, "%d MS", latency);
    display_print_string(overlay_display_info.char_width - 6, overlay_display_info.char_height - 4, str, 6);
    snprintf(str, 8, "%d C", packet->tx_temperature);
    display_print_string(overlay_display_info.char_width - 5, overlay_display_info.char_height - 3, str, 5);
    snprintf(str, 8, "A %2.1fV", packet->tx_voltage / 64.0f);
    display_print_string(overlay_display_info.char_width - 7, overlay_display_info.char_height - 2, str, 7);
    uint16_t goggle_voltage = get_int_from_fs(GOGGLES_VOLTAGE_PATH);
    snprintf(str, 8, "G %2.1fV", (goggle_voltage / 45.0f) - 0.65f);
    display_print_string(overlay_display_info.char_width - 7, overlay_display_info.char_height - 1, str, 7);
}


int main(int argc, char *argv[])
{
    signal(SIGINT, sig_handler);

    current_display_info = &sd_display_info;

    uint8_t is_v2_goggles = dji_goggles_are_v2();
    printf("Detected DJI goggles %s\n", is_v2_goggles ? "V2" : "V1");

    display_driver = calloc(1, sizeof(displayport_vtable_t));
    display_driver->draw_character = &msp_draw_character;
    display_driver->clear_screen = &msp_clear_screen;
    display_driver->draw_complete = &msp_draw_complete;
    display_driver->set_options = &msp_set_options;

    msp_state_t *msp_state = calloc(1, sizeof(msp_state_t));
    msp_state->cb = &msp_callback;

    int event_fd = open(INPUT_FILENAME, O_RDONLY);
    assert(event_fd > 0);

    dji_shm_state_t radio_shm;
    memset(&radio_shm, 0, sizeof(radio_shm));

    int msp_socket_fd = bind_socket(MSP_PORT);
    int data_socket_fd = bind_socket(DATA_PORT);
    printf("started up, listening on port %d\n", MSP_PORT);


    struct pollfd poll_fds[3];
    int recv_len = 0;
    uint8_t byte = 0;
    uint8_t buffer[4096];
    struct sockaddr_storage src_addr;
    socklen_t src_addr_len=sizeof(src_addr);
    struct input_event ev;
    struct timespec button_start, display_start, now, last_back, doubletap_sleep_start;
    memset(&display_start, 0, sizeof(display_start));
    memset(&button_start, 0, sizeof(button_start));
    memset(&last_back, 0, sizeof(last_back));
    memset(&doubletap_sleep_start, 0, sizeof(doubletap_sleep_start));

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
            open_dji_radio_shm(&radio_shm);
            start_display(is_v2_goggles);
            display_mode = DISPLAY_RUNNING;
        }
        if ((display_mode == DISPLAY_RUNNING) && (button_start.tv_sec > 0) && ((now.tv_sec - last_back.tv_sec) < BACK_BUTTON_DOUBLETAP_TIME))
        {
            printf("Cycling Enabled -> Disabled -> Enabled\n");
            printf("Disabling\n");
            stop_display();
            close_dji_radio_shm(&radio_shm);
            close_fonts(&sd_display_info);
            close_fonts(&hd_display_info);
            close_fonts(&overlay_display_info);
            display_mode = DISPLAY_DISABLED;
            dji_start_goggles(is_v2_goggles);
            printf("Waiting\n");
            clock_gettime(CLOCK_MONOTONIC, &doubletap_sleep_start);
        }
        else if (doubletap_sleep_start.tv_sec > 0 && ((now.tv_sec - doubletap_sleep_start.tv_sec) > CYCLE_SLEEP_TIME))
        {
            printf("Enabling\n");
            dji_stop_goggles(is_v2_goggles);
            clock_gettime(CLOCK_MONOTONIC, &display_start);
            display_mode = DISPLAY_WAITING;

            memset(&last_back, 0, sizeof(last_back));
            memset(&doubletap_sleep_start, 0, sizeof(doubletap_sleep_start));
        }
        else if(button_start.tv_sec > 0 && ((now.tv_sec - button_start.tv_sec) > BACK_BUTTON_DELAY)) {
            // We held the back button down for 5 seconds.
            memset(&button_start, 0, sizeof(button_start));
            if (display_mode == DISPLAY_DISABLED) {
                printf("Switching Disabled -> Enabled!\n");
                dji_stop_goggles(is_v2_goggles);
                clock_gettime(CLOCK_MONOTONIC, &display_start);
                display_mode = DISPLAY_WAITING;
            } else {
                printf("Switching Enabled/Waiting -> Disabled!\n");
                if(display_mode == DISPLAY_RUNNING) {
                    stop_display();
                    close_dji_radio_shm(&radio_shm);
                }
                close_fonts(&sd_display_info);
                close_fonts(&hd_display_info);
                close_fonts(&overlay_display_info);
                display_mode = DISPLAY_DISABLED;
                dji_start_goggles(is_v2_goggles);
            }
        }

        poll_fds[0].fd = msp_socket_fd;
        poll_fds[0].events = POLLIN;
        poll_fds[1].fd = event_fd;
        poll_fds[1].events = POLLIN;
        poll_fds[2].fd = data_socket_fd;
        poll_fds[2].events = POLLIN;
        poll(poll_fds, 3, 100);

        if(poll_fds[1].revents) {
            read(event_fd, &ev, sizeof(struct input_event));
            if(ev.code == EV_CODE_BACK) {
                if(ev.value == 1) {
                    clock_gettime(CLOCK_MONOTONIC, &button_start);
                } else {
                    clock_gettime(CLOCK_MONOTONIC, &last_back);
                    memset(&button_start, 0, sizeof(button_start));
                }
            }
            DEBUG_PRINT("input type: %i, code: %i, value: %i\n", ev.type, ev.code, ev.value);
        }
        if(poll_fds[0].revents) {
            // Got MSP UDP packet
            if (0 < (recv_len = recvfrom(msp_socket_fd,&buffer,sizeof(buffer),0,(struct sockaddr*)&src_addr,&src_addr_len)))
            {
                DEBUG_PRINT("got MSP packet len %d\n", recv_len);
                if(display_mode == DISPLAY_RUNNING) {
                    for (int i=0; i<recv_len; i++)
                        msp_process_data(msp_state, buffer[i]);
                }
            }
        }
         if(poll_fds[2].revents) {
            // Got data UDP packet
            if (0 < (recv_len = recvfrom(data_socket_fd,&buffer,sizeof(buffer),0,(struct sockaddr*)&src_addr,&src_addr_len)))
            {
                DEBUG_PRINT("got DATA packet len %d\n", recv_len);
                if(display_mode == DISPLAY_RUNNING) {
                    process_data_packet(buffer, recv_len, &radio_shm);
                }
            }
        }
    }
    if(display_mode == DISPLAY_RUNNING) {
        stop_display();
    }

    free(display_driver);
    free(msp_state);
    close(msp_socket_fd);
    close(data_socket_fd);
    close(event_fd);
    return 0;
}
