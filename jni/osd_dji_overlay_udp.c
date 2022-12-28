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
#include <sys/eventfd.h>

#include "hw/dji_display.h"
#include "hw/dji_radio_shm.h"
#include "hw/dji_services.h"
#include "json/osd_config.h"
#include "fakehd/fakehd.h"
#include "font/font.h"
#include "lz4/lz4.h"
#include "toast/toast.h"
#include "net/network.h"
#include "net/data_protocol.h"
#include "msp/msp.h"
#include "msp/msp_displayport.h"
#include "rec/rec.h"
#include "util/display_info.h"
#include "util/fs_util.h"
#include "util/time_util.h"

#define MSP_PORT 7654
#define DATA_PORT 7655
#define COMPRESSED_DATA_PORT 7656
#define DICTIONARY_VERSION 1

#define WIDTH 1440
#define HEIGHT 810
#define BYTES_PER_PIXEL 4
#define PLANE_ID 6

#define GOGGLES_V1_VOFFSET 575
#define GOGGLES_V2_VOFFSET 215

#define INPUT_FILENAME "/dev/input/event0"
#define SPLASH_STRING "OSD WAITING..."
#define SHUTDOWN_STRING "SHUTTING DOWN..."
#define SPLASH_KEY "show_waiting"

#define FORCE_RENDER_HZ 2
#define TOAST_HZ 2

#define GOGGLES_VOLTAGE_PATH "/sys/devices/platform/soc/f0a00000.apb/f0a71000.omc/voltage5"

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

#define MAX_DISPLAY_X 60
#define MAX_DISPLAY_Y 22

static void rec_msp_draw_complete_hook();

static volatile sig_atomic_t quit = 0;
static dji_display_state_t *dji_display;
static uint16_t msp_character_map[MAX_DISPLAY_X][MAX_DISPLAY_Y];
static uint16_t msp_render_character_map[MAX_DISPLAY_X][MAX_DISPLAY_Y];
static uint16_t overlay_character_map[MAX_DISPLAY_X][MAX_DISPLAY_Y];
static displayport_vtable_t *display_driver;
static uint8_t which_fb = 0;
struct timespec last_render;

static char current_fc_variant[5];

static display_info_t sd_display_info = {
    .char_width = 30,
    .char_height = 15,
    .font_width = 36,
    .font_height = 54,
    .x_offset = 180,
    .y_offset = 0,
    .fonts = {NULL, NULL, NULL, NULL},
};

static display_info_t full_display_info = {
    .char_width = 60,
    .char_height = 22,
    .font_width = 24,
    .font_height = 36,
    .x_offset = 0,
    .y_offset = 0,
    .fonts = {NULL, NULL, NULL, NULL},
};

static display_info_t hd_display_info = {
    .char_width = 50,
    .char_height = 18,
    .font_width = 24,
    .font_height = 36,
    .x_offset = 120,
    .y_offset = 80,
    .fonts = {NULL, NULL, NULL, NULL},
};

static display_info_t overlay_display_info = {
    .char_width = 20,
    .char_height = 10,
    .font_width = 24,
    .font_height = 36,
    .x_offset = 960,
    .y_offset = 450,
    .fonts = {NULL, NULL, NULL, NULL},
};

static enum display_mode_s {
        DISPLAY_DISABLED = 0,
        DISPLAY_RUNNING = 1,
        DISPLAY_WAITING = 2
} display_mode = DISPLAY_RUNNING;

static display_info_t *current_display_info;

int event_fd;

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

/* Main rendering function: take a character_map and a display_info and draw it into a framebuffer */

static void draw_character_map(display_info_t *display_info, void* restrict fb_addr, uint16_t character_map[MAX_DISPLAY_X][MAX_DISPLAY_Y]) {
    if (display_info->fonts[0] == NULL) {
        DEBUG_PRINT("No font available, failed to draw.\n");
        return;
    }
    void* restrict font;
    for(int y = 0; y < display_info->char_height; y++) {
        for(int x = 0; x < display_info->char_width; x++) {
            uint16_t c = character_map[x][y];
            if (c != 0) {
                int page = (c & 0x300) >> 8;
                c = c & 0xFF;
                font = display_info->fonts[page];
                if(font == NULL) {
                    font = display_info->fonts[0];
                }
                uint32_t pixel_x = (x * display_info->font_width) + display_info->x_offset;
                uint32_t pixel_y = (y * display_info->font_height) + display_info->y_offset;
                uint32_t font_offset = (((display_info->font_height * display_info->font_width) * BYTES_PER_PIXEL) * c);
                uint32_t target_offset = ((pixel_x * BYTES_PER_PIXEL) + (pixel_y * WIDTH * BYTES_PER_PIXEL));
                for(uint8_t gy = 0; gy < display_info->font_height; gy++) {
                    for(uint8_t gx = 0; gx < display_info->font_width; gx++) {
                        *((uint8_t *)fb_addr + target_offset) = *(uint8_t *)((uint8_t *)font + font_offset + 2);
                        *((uint8_t *)fb_addr + target_offset + 1) = *(uint8_t *)((uint8_t *)font + font_offset + 1);
                        *((uint8_t *)fb_addr + target_offset + 2) = *(uint8_t *)((uint8_t *)font + font_offset);
                        *((uint8_t *)fb_addr + target_offset + 3) = ~*(uint8_t *)((uint8_t *)font + font_offset + 3);
                        font_offset += BYTES_PER_PIXEL;
                        target_offset += BYTES_PER_PIXEL;
                    }
                    target_offset += WIDTH * BYTES_PER_PIXEL - (display_info->font_width * BYTES_PER_PIXEL);
                }
                DEBUG_PRINT("%c", c > 31 ? c : 20);
            }
            DEBUG_PRINT(" ");
        }
        DEBUG_PRINT("\n");
    }
}

static void clear_framebuffer() {
    void *fb_addr = dji_display_get_fb_address(dji_display, which_fb);
    // DJI has a backwards alpha channel - FF is transparent, 00 is opaque.
    memset(fb_addr, 0x000000FF, WIDTH * HEIGHT * BYTES_PER_PIXEL);
}

static void draw_screen() {
    clear_framebuffer();

    void *fb_addr = dji_display_get_fb_address(dji_display, which_fb);

    if (fakehd_is_enabled()) {
        fakehd_map_sd_character_map_to_hd(msp_character_map, msp_render_character_map);
        draw_character_map(current_display_info, fb_addr, msp_render_character_map);
    } else {
        draw_character_map(current_display_info, fb_addr, msp_character_map);
    }
    draw_character_map(&overlay_display_info, fb_addr, overlay_character_map);
}

static void clear_overlay() {
    memset(overlay_character_map, 0, sizeof(overlay_character_map));
}

static void msp_clear_screen() {
    memset(msp_character_map, 0, sizeof(msp_character_map));
    memset(msp_render_character_map, 0, sizeof(msp_render_character_map));
}

static void render_screen() {
    draw_screen();
    if (display_mode == DISPLAY_DISABLED) {
        clear_framebuffer();
    }
    dji_display_push_frame(dji_display, which_fb);
    which_fb = !which_fb;
    DEBUG_PRINT("drew a frame\n");
    clock_gettime(CLOCK_MONOTONIC, &last_render);
}

static void msp_draw_complete() {
    render_screen();

    if (rec_is_enabled()) {
        rec_msp_draw_complete_hook();
        if (rec_is_osd_recording() == true)
        {
            rec_write_frame(
                fakehd_is_enabled() ? msp_render_character_map : msp_character_map,
                MAX_DISPLAY_X * MAX_DISPLAY_Y);
        }
    }
}

static void msp_callback(msp_msg_t *msp_message)
{
    displayport_process_message(display_driver, msp_message);
}

static void load_fonts(font_variant_e font_variant) {
    char file_path[255];
    get_font_path_with_extension(file_path, "FONT font", ".png", 255, 0, font_variant);
    toast(file_path);
    load_font(&sd_display_info, font_variant);
    load_font(&hd_display_info, font_variant);
    load_font(&full_display_info, font_variant);
    load_font(&overlay_display_info, font_variant);
}

static void close_all_fonts() {
    close_font(&sd_display_info);
    close_font(&hd_display_info);
    close_font(&overlay_display_info);
    close_font(&full_display_info);
}

static void msp_set_options(uint8_t font_num, msp_hd_options_e is_hd) {
    msp_clear_screen();

    switch (is_hd) {
        case MSP_HD_OPTION_60_22:
            fakehd_disable();
            current_display_info = &full_display_info;
            break;
        case MSP_HD_OPTION_50_18:
        case MSP_HD_OPTION_30_16:
            fakehd_disable();
            current_display_info = &hd_display_info;
            break;
        default:
            current_display_info = &sd_display_info;
            break;
    }
}

static void display_print_string(uint8_t init_x, uint8_t y, const char *string, uint8_t len) {
    for(uint8_t x = 0; x < len; x++) {
        draw_character(&overlay_display_info, overlay_character_map, x + init_x, y, string[x]);
    }
}

/* DJI framebuffer configuration */

static duss_result_t pop_func(duss_disp_instance_handle_t *disp_handle,duss_disp_plane_id_t plane_id, duss_frame_buffer_t *frame_buffer,void *user_ctx) {
    return 0;
}

void dji_display_open_framebuffer_injected(dji_display_state_t *display_state, duss_disp_instance_handle_t *disp, duss_hal_obj_handle_t ion_handle, duss_disp_plane_id_t plane_id) {
    uint32_t hal_device_open_unk = 0;
    duss_result_t res = 0;
    display_state->disp_instance_handle = disp;
    display_state->ion_handle = ion_handle;
    display_state->plane_id = plane_id;

    // PLANE BLENDING

    display_state->pb_0->is_enable = 1;

    // TODO just check hwid to figure this out. Not actually V1/V2 related but an HW version ID.

    display_state->pb_0->voffset = GOGGLES_V1_VOFFSET;
    display_state->pb_0->hoffset = 0;

    // On Goggles V1, the UI and video are in Z-Order 1.
    // On Goggles V2, they're in Z-Order 4, but we inline patch them to Z-Order 1 (see displayport_osd_shim.c)

    display_state->pb_0->order = 2;

    // Global alpha - disable as we want per pixel alpha.

    display_state->pb_0->glb_alpha_en = 0;
    display_state->pb_0->glb_alpha_val = 0;

    // These aren't documented. Blending algorithm 0 is employed for menus and 1 for screensaver.

    display_state->pb_0->blending_alg = 1;

    // No idea what this "plane mode" actually does but it's different on V2
    uint8_t acquire_plane_mode = display_state->is_v2_goggles ? 6 : 0;

    DEBUG_PRINT("acquire plane\n");
    res = duss_hal_display_aquire_plane(display_state->disp_instance_handle,acquire_plane_mode,&plane_id);
    if (res != 0) {
        DEBUG_PRINT("failed to acquire plane");
        exit(0);
    }
    res = duss_hal_display_register_frame_cycle_callback(display_state->disp_instance_handle, plane_id, &pop_func, 0);
    if (res != 0) {
        DEBUG_PRINT("failed to register callback");
        exit(0);
    }

    res = duss_hal_display_plane_blending_set(display_state->disp_instance_handle, plane_id, display_state->pb_0);

    if (res != 0) {
        DEBUG_PRINT("failed to set blending");
        exit(0);
    }
    DEBUG_PRINT("alloc ion buf\n");
    res = duss_hal_mem_alloc(display_state->ion_handle,&display_state->ion_buf_0,0x473100,0x400,0,0x17);
    if (res != 0) {
        DEBUG_PRINT("failed to allocate VRAM");
        exit(0);
    }
    res = duss_hal_mem_map(display_state->ion_buf_0, &display_state->fb0_virtual_addr);
    if (res != 0) {
        DEBUG_PRINT("failed to map VRAM");
        exit(0);
    }
    res = duss_hal_mem_get_phys_addr(display_state->ion_buf_0, &display_state->fb0_physical_addr);
    if (res != 0) {
        DEBUG_PRINT("failed to get FB0 phys addr");
        exit(0);
    }
    DEBUG_PRINT("first buffer VRAM mapped virtual memory is at %p : %p\n", display_state->fb0_virtual_addr, display_state->fb0_physical_addr);

    res = duss_hal_mem_alloc(display_state->ion_handle,&display_state->ion_buf_1,0x473100,0x400,0,0x17);
    if (res != 0) {
        DEBUG_PRINT("failed to allocate FB1 VRAM");
        exit(0);
    }
    res = duss_hal_mem_map(display_state->ion_buf_1,&display_state->fb1_virtual_addr);
    if (res != 0) {
        DEBUG_PRINT("failed to map FB1 VRAM");
        exit(0);
    }
    res = duss_hal_mem_get_phys_addr(display_state->ion_buf_1, &display_state->fb1_physical_addr);
    if (res != 0) {
        DEBUG_PRINT("failed to get FB1 phys addr");
        exit(0);
    }
    DEBUG_PRINT("second buffer VRAM mapped virtual memory is at %p : %p\n", display_state->fb1_virtual_addr, display_state->fb1_physical_addr);

    for(int i = 0; i < 2; i++) {
        duss_frame_buffer_t *fb = i ? display_state->fb_1 : display_state->fb_0;
        fb->buffer = i ? display_state->ion_buf_1 : display_state->ion_buf_0;
        fb->pixel_format = display_state->is_v2_goggles ? DUSS_PIXFMT_RGBA8888_GOGGLES_V2 : DUSS_PIXFMT_RGBA8888; // 20012 instead on V2
        fb->frame_id = i;
        fb->planes[0].bytes_per_line = 0x1680;
        fb->planes[0].offset = 0;
        fb->planes[0].plane_height = 810;
        fb->planes[0].bytes_written = 0x473100;
        fb->width = 1440;
        fb->height = 810;
        fb->plane_count = 1;
    }
}

/* Display initialization and deinitialization */

static void start_display(uint8_t is_v2_goggles,duss_disp_instance_handle_t *disp, duss_hal_obj_handle_t ion_handle) {
    memset(msp_character_map, 0, sizeof(msp_character_map));
    memset(msp_render_character_map, 0, sizeof(msp_render_character_map));
    memset(overlay_character_map, 0, sizeof(overlay_character_map));

    dji_display = dji_display_state_alloc(is_v2_goggles);
    dji_display_open_framebuffer_injected(dji_display, disp, ion_handle, PLANE_ID);
    if(get_boolean_config_value(SPLASH_KEY)) {
        display_print_string(0, overlay_display_info.char_height -1, SPLASH_STRING, sizeof(SPLASH_STRING));
    }
    msp_draw_complete();
}

static void stop_display() {
    display_print_string(0, overlay_display_info.char_height -1, SHUTDOWN_STRING, sizeof(SHUTDOWN_STRING));
    dji_display_close_framebuffer(dji_display);
    dji_display_state_free(dji_display);
}

/* AU Voltage and Temp overlay */

#define SHOW_AU_DATA_KEY "show_au_data"
static int au_overlay_enabled = 0;

static void check_is_au_overlay_enabled()
{
    DEBUG_PRINT("Checking for AU overlay enabled: ");
    if (get_boolean_config_value(SHOW_AU_DATA_KEY))
    {
        DEBUG_PRINT("Enabled\n");
        au_overlay_enabled = 1;
    } else {
        DEBUG_PRINT("Disabled\n");
    }
}

static void process_data_packet(uint8_t *buf, int len, dji_shm_state_t *radio_shm) {
    packet_data_t *packet = (packet_data_t *)buf;
    DEBUG_PRINT("got data %04X version spec %d C %f V variant %.4s\n", packet->version_specifier, packet->tx_temperature, packet->tx_voltage / 64.0f, packet->fc_variant);
    char str[8];
    clear_overlay();
    if(au_overlay_enabled) {
        snprintf(str, 8, "%d C", packet->tx_temperature);
        display_print_string(overlay_display_info.char_width - 5, overlay_display_info.char_height - 8, str, 5);
        snprintf(str, 8, "A %2.1fV", packet->tx_voltage / 64.0f);
        display_print_string(overlay_display_info.char_width - 7, overlay_display_info.char_height - 7, str, 7);
    }
    if(len > 6) {
        DEBUG_PRINT("Got new packet with variant %.4s\n", packet->fc_variant);
        // should have FC type
        if(strncmp(current_fc_variant, packet->fc_variant, 4) != 0) {
            memcpy(current_fc_variant, &packet->fc_variant, 4);
            DEBUG_PRINT("Changed current FC variant to %.4s\n", current_fc_variant);
            toast("FC %.4s", current_fc_variant);
            close_all_fonts();
            load_fonts(font_variant_from_string(current_fc_variant));
            // This is not a typo - fill in any missing fonts for the current variant with the generic one.
            load_fonts(FONT_VARIANT_GENERIC);
        }
    }
}

static void process_compressed_data(void *buf, int len, void *dict, int dict_size) {
    compressed_data_header_t *header = (compressed_data_header_t*)buf;
    if (header->version != DICTIONARY_VERSION) {
        return;
    }
    switch ((msp_hd_options_e)header->hd_options) {
        case MSP_HD_OPTION_60_22:
            fakehd_disable();
            current_display_info = &full_display_info;
            break;
        case MSP_HD_OPTION_30_16:
        case MSP_HD_OPTION_50_18:
            fakehd_disable();
            current_display_info = &hd_display_info;
            break;
        default:
            if (fakehd_is_enabled()) {
                memset(msp_render_character_map, 0, sizeof(msp_render_character_map));
                current_display_info = &full_display_info;
            } else {
                current_display_info = &sd_display_info;
            }
            break;
    }
    int decompressed_size = LZ4_decompress_safe_usingDict((buf + sizeof(compressed_data_header_t)), msp_character_map, len - sizeof(compressed_data_header_t), sizeof(msp_character_map), dict, dict_size);
    DEBUG_PRINT("Decompressed %d bytes!\n", decompressed_size);
    msp_draw_complete();
}

/* Recording hooks */

static void rec_msp_draw_complete_hook()
{
    if (rec_is_osd_recording() == false && rec_is_gls_recording() == true)
    {
        if (current_fc_variant[0] == '\0')
        {
            DEBUG_PRINT("msp_osd: gls started recording, but no fc variant yet!?\n");
            return;
        }

        DEBUG_PRINT("msp_osd: gls started recording, start osd rec\n");

        rec_config_t config = {
            .char_width = current_display_info->char_width,
            .char_height = current_display_info->char_height,
            .font_width = current_display_info->font_width,
            .font_height = current_display_info->font_height,
            .x_offset = current_display_info->x_offset,
            .y_offset = current_display_info->y_offset,
            .font_variant = font_variant_from_string(current_fc_variant),
        };

        rec_start(&config);
    }
    else if (rec_is_osd_recording() == true && rec_is_gls_recording() == false)
    {
        DEBUG_PRINT("msp_osd: gls stopped recording, stop osd rec\n");
        rec_stop();
    }
}

/* Public OSD enable/disable methods */

void osd_disable() {
    uint64_t disable = 1;
    write(event_fd, &disable, sizeof(uint64_t));
}

void osd_enable() {
    uint64_t enable = 2;
    write(event_fd, &enable, sizeof(uint64_t));
}

/* Entry point and main loop */

void osd_directfb(duss_disp_instance_handle_t *disp, duss_hal_obj_handle_t ion_handle)
{
    memset(current_fc_variant, 0, sizeof(current_fc_variant));

    toast_load_config();
    load_fakehd_config();
    rec_load_config();
    check_is_au_overlay_enabled();
    convert_bin_fonts(SDCARD_FONT_PATH);

    uint8_t is_v2_goggles = dji_goggles_are_v2();
    DEBUG_PRINT("Detected DJI goggles %s\n", is_v2_goggles ? "V2" : "V1");

    if (fakehd_is_enabled())
    {
        current_display_info = &full_display_info;
    } else {
        current_display_info = &sd_display_info;
    }

    display_driver = calloc(1, sizeof(displayport_vtable_t));
    display_driver->draw_character = &msp_draw_character;
    display_driver->clear_screen = &msp_clear_screen;
    display_driver->draw_complete = &msp_draw_complete;
    display_driver->set_options = &msp_set_options;

    msp_state_t *msp_state = calloc(1, sizeof(msp_state_t));
    msp_state->cb = &msp_callback;

    event_fd = eventfd(0, 0);
    assert(event_fd > 0);

    dji_shm_state_t radio_shm;
    memset(&radio_shm, 0, sizeof(radio_shm));

    int msp_socket_fd = bind_socket(MSP_PORT);
    int data_socket_fd = bind_socket(DATA_PORT);
    int compressed_socket_fd = bind_socket(COMPRESSED_DATA_PORT);
    printf("*** MSP-OSD: MSP-OSD started up, listening on port %d\n", MSP_PORT);

    struct pollfd poll_fds[4];
    int recv_len = 0;
    uint8_t byte = 0;
    uint8_t buffer[8192];
    struct sockaddr_storage src_addr;
    socklen_t src_addr_len=sizeof(src_addr);
    struct input_event ev;
    struct timespec now, last_toast;
    memset(&last_toast, 0, sizeof(last_toast));
    memset(&last_render, 0, sizeof(last_render));
    memset(&now, 0, sizeof(now));

    load_fonts(FONT_VARIANT_GENERIC);
    open_dji_radio_shm(&radio_shm);
    start_display(is_v2_goggles, disp, ion_handle);

    int compression_dict_size = 0;
    void *compression_dict = open_dict(DICTIONARY_VERSION, &compression_dict_size);

    uint64_t event_number;
    while (!quit)
    {
        poll_fds[0].fd = msp_socket_fd;
        poll_fds[0].events = POLLIN;
        poll_fds[1].fd = event_fd;
        poll_fds[1].events = POLLIN;
        poll_fds[2].fd = data_socket_fd;
        poll_fds[2].events = POLLIN;
        poll_fds[3].fd = compressed_socket_fd;
        poll_fds[3].events = POLLIN;

        // spin every 250ms if we didn't get a packet, then check and see if we need to do the toast/overlay logic
        poll(poll_fds, 4, 250);

        clock_gettime(CLOCK_MONOTONIC, &now);

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
        if(poll_fds[1].revents) {
            // Got eventfd message from another thread to enable/disable OSD
            if (0 < (recv_len = read(event_fd, &event_number, sizeof(uint64_t)))) {
                if(event_number > 1) {
                    DEBUG_PRINT("Display running transition\n");
                    display_mode = DISPLAY_RUNNING;
                } else {
                    DEBUG_PRINT("Display disabled transition\n");
                    display_mode = DISPLAY_DISABLED;
                }
            }
        }

        if(poll_fds[3].revents) {
            // Got compressed data
            if (0 < (recv_len = recvfrom(compressed_socket_fd,&buffer,sizeof(buffer),0,(struct sockaddr*)&src_addr,&src_addr_len)))
            {
                DEBUG_PRINT("got COMPRESSED data packet len %d\n", recv_len);
                if(display_mode == DISPLAY_RUNNING) {
                    process_compressed_data(buffer, recv_len, compression_dict, compression_dict_size);
                }
            }
        }

        if(timespec_subtract_ns(&now, &last_toast) > (NSEC_PER_SEC / TOAST_HZ)) {
            // lets toast run + update any notices
            do_toast(display_print_string);
            clock_gettime(CLOCK_MONOTONIC, &last_toast);
        }

        if(timespec_subtract_ns(&now, &last_render) > (NSEC_PER_SEC / FORCE_RENDER_HZ)) {
            // More than 500ms have elapsed without a render, let's go ahead and manually render
            render_screen();
        }
    }

    free(display_driver);
    free(msp_state);
    free(compression_dict);
    close(msp_socket_fd);
    close(data_socket_fd);
    close(compressed_socket_fd);
    close(event_fd);
    return;
}
