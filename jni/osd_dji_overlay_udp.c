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
#include "lz4/lz4.h"
#include "toast/toast.h"
#include "net/network.h"
#include "net/data_protocol.h"
#include "msp/msp.h"
#include "msp/msp_displayport.h"

#include "util/debug.h"
#include "util/fs_util.h"
#include "util/time_util.h"
#include "rec/rec.h"
#include "rec/rec_pb.h"

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

#define NUM_CHARS 256

#define INPUT_FILENAME "/dev/input/event0"
#define SPLASH_STRING "OSD WAITING..."
#define SHUTDOWN_STRING "SHUTTING DOWN..."
#define SPLASH_KEY "show_waiting"

#define FALLBACK_FONT_PATH "/blackbox/font"
#define ENTWARE_FONT_PATH "/opt/fonts/font"
#define SDCARD_FONT_PATH "/storage/sdcard0/font"

typedef enum
{
    FONT_VARIANT_GENERIC,
    FONT_VARIANT_BETAFLIGHT,
    FONT_VARIANT_INAV,
    FONT_VARIANT_ARDUPILOT,
    FONT_VARIANT_KISS_ULTRA,
    FONT_VARIANT_QUICKSILVER
} font_variant_e;

#define FORCE_RENDER_HZ 2
#define TOAST_HZ 2

#define GOGGLES_VOLTAGE_PATH "/sys/devices/platform/soc/f0a00000.apb/f0a71000.omc/voltage5"

#define EV_CODE_BACK 0xc9

#define BACK_BUTTON_DELAY 4

#define SWAP32(data)   \
( (((data) >> 24) & 0x000000FF) | (((data) >>  8) & 0x0000FF00) | \
  (((data) <<  8) & 0x00FF0000) | (((data) << 24) & 0xFF000000) )

#define MAX_DISPLAY_X 60
#define MAX_DISPLAY_Y 22

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

static void rec_msp_draw_complete_hook();
static font_variant_e font_variant_from_string(char *variant_string);

static volatile sig_atomic_t quit = 0;
static dji_display_state_t *dji_display;
static uint16_t msp_character_map[MAX_DISPLAY_X][MAX_DISPLAY_Y];
static uint16_t msp_render_character_map[MAX_DISPLAY_X][MAX_DISPLAY_Y];
static uint16_t overlay_character_map[MAX_DISPLAY_X][MAX_DISPLAY_Y];
static displayport_vtable_t *display_driver;
static uint8_t which_fb = 0;
struct timespec last_render;

static char current_fc_variant[5];

static uint8_t frame_waiting = 0;

static display_info_t sd_display_info = {
    .char_width = 30,
    .char_height = 15,
    .font_width = 36,
    .font_height = 54,
    .x_offset = 180,
    .y_offset = 0,
    .font_page_1 = NULL,
    .font_page_2 = NULL,
};

static display_info_t full_display_info = {
    .char_width = 60,
    .char_height = 22,
    .font_width = 24,
    .font_height = 36,
    .x_offset = 0,
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
    if (display_info->font_page_1 == NULL) {
        DEBUG_PRINT("No font available, failed to draw.\n");
        return;
    }
    void *font_page_2 = display_info->font_page_2 == NULL ? display_info->font_page_1 : display_info->font_page_2;
    void* restrict font;
    for(int y = 0; y < display_info->char_height; y++) {
        for(int x = 0; x < display_info->char_width; x++) {
            uint16_t c = character_map[x][y];
            if (c != 0) {
                font = display_info->font_page_1;
                if (c > 255) {
                    c = c & 0xFF;
                    font = font_page_2;
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
                // DEBUG_PRINT("%c", c > 31 ? c : 20);
            }
            // DEBUG_PRINT(" ");
        }
        // DEBUG_PRINT("\n");
    }
}

static void clear_framebuffer() {
    void *fb_addr = dji_display_get_fb_address(dji_display, which_fb);
    // DJI has a backwards alpha channel - FF is transparent, 00 is opaque.
    memset(fb_addr, 0x000000FF, WIDTH * HEIGHT * BYTES_PER_PIXEL);
}

static void draw_screen() {
    void *fb_addr = dji_display_get_fb_address(dji_display, which_fb);
    // DJI has a backwards alpha channel - FF is transparent, 00 is opaque.
    memset(fb_addr, 0x000000FF, WIDTH * HEIGHT * BYTES_PER_PIXEL);

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
    which_fb = dji_display_push_frame(dji_display, which_fb);
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

/* Font helper methods */

static font_variant_e font_variant_from_string(char *variant_string) {
    font_variant_e font_variant = FONT_VARIANT_GENERIC;
    if(strncmp(current_fc_variant, "ARDU", 4) == 0) {
        font_variant = FONT_VARIANT_ARDUPILOT;
    } else if (strncmp(current_fc_variant, "BTFL", 4) == 0) {
        font_variant = FONT_VARIANT_BETAFLIGHT;
    } else if (strncmp(current_fc_variant, "INAV", 4) == 0) {
        font_variant = FONT_VARIANT_INAV;
    } else if (strncmp(current_fc_variant, "ULTR", 4) == 0) {
        font_variant = FONT_VARIANT_KISS_ULTRA;
    } else if (strncmp(current_fc_variant, "QUIC", 4) == 0) {
        font_variant = FONT_VARIANT_QUICKSILVER;
    }
    return font_variant;
}

static void get_font_path_with_prefix(char *font_path_dest, const char *font_path, uint8_t len, uint8_t is_hd, font_variant_e font_variant, uint8_t page)
{
    char name_buf[len];
    char res_buf[len];

    switch (font_variant)
    {
        case FONT_VARIANT_BETAFLIGHT:
            snprintf(name_buf, len, "%s_bf", font_path);
            break;
        case FONT_VARIANT_INAV:
            snprintf(name_buf, len, "%s_inav", font_path);
            break;
        case FONT_VARIANT_ARDUPILOT:
            snprintf(name_buf, len, "%s_ardu", font_path);
            break;
        case FONT_VARIANT_KISS_ULTRA:
            snprintf(name_buf, len, "%s_ultra", font_path);
            break;
        case FONT_VARIANT_QUICKSILVER:
            snprintf(name_buf, len, "%s_quic", font_path);
            break;
        default:
            snprintf(name_buf, len, "%s", font_path);
    }

    if (is_hd)
    {
        // surely there's a better way...
        snprintf(res_buf, len, "%s", "_hd");
    } else {
        snprintf(res_buf, len, "%s", "");
    }

    if (page > 0)
    {
        snprintf(font_path_dest, len, "%s%s_%d.bin", name_buf, res_buf, page + 1);
    }
    else
    {
        snprintf(font_path_dest, len, "%s%s.bin", name_buf, res_buf);
    }
}

static int open_font(const char *filename, void **font, uint8_t page, uint8_t is_hd, font_variant_e font_variant)
{
    char file_path[255];
    get_font_path_with_prefix(file_path, filename, 255, is_hd, font_variant, page);
    DEBUG_PRINT("Opening font: %s\n", file_path);
    struct stat st;
    memset(&st, 0, sizeof(st));
    stat(file_path, &st);
    size_t filesize = st.st_size;
    display_info_t display_info = is_hd ? hd_display_info : sd_display_info;
    size_t desired_filesize = display_info.font_height *  display_info.font_width * NUM_CHARS * BYTES_PER_PIXEL;
    if(filesize != desired_filesize) {
        if (filesize != 0) {
            DEBUG_PRINT("Font was wrong size: %s %d != %d\n", file_path, filesize, desired_filesize);
        }
        return -1;
    }
    int fd = open(file_path, O_RDONLY, 0);
    if (!fd) {
        DEBUG_PRINT("Could not open file %s\n", file_path);
        return -1;
    }
    void* font_data = malloc(desired_filesize);
    void* mmappedData = mmap(NULL, filesize, PROT_READ, MAP_PRIVATE, fd, 0);
    if (mmappedData != MAP_FAILED) {
        memcpy(font_data, mmappedData, desired_filesize);
        *font = font_data;
    } else {
        DEBUG_PRINT("Could not map font %s\n", file_path);
        free(font_data);
        *font = 0;
    }
    close(fd);
    munmap(mmappedData, desired_filesize);
    return 0;
}

static void load_font(void **font_buffer, uint8_t page, uint8_t is_hd, font_variant_e font_variant) {
    // Note: load_font will not replace an existing font.
    if(*font_buffer == NULL) {
        if (open_font(SDCARD_FONT_PATH, font_buffer, page, is_hd, font_variant) < 0) {
            if (open_font(ENTWARE_FONT_PATH, font_buffer, page, is_hd, font_variant) < 0) {
                open_font(FALLBACK_FONT_PATH, font_buffer, page, is_hd, font_variant);
            }
        }
    }
}

static void load_fonts(font_variant_e font_variant) {
    char file_path[255];
    get_font_path_with_prefix(file_path, "FONT font", 255, 0, font_variant, 0);
    toast(file_path);
    load_font(&sd_display_info.font_page_1, 0, 0, font_variant);
    load_font(&sd_display_info.font_page_2, 1, 0, font_variant);
    load_font(&hd_display_info.font_page_1, 0, 1, font_variant);
    load_font(&hd_display_info.font_page_2, 1, 1, font_variant);
    load_font(&full_display_info.font_page_1, 0, 1, font_variant);
    load_font(&full_display_info.font_page_2, 1, 1, font_variant);
    load_font(&overlay_display_info.font_page_1, 0, 1, font_variant);
    load_font(&overlay_display_info.font_page_2, 1, 1, font_variant);
}


static void close_fonts(display_info_t *display_info) {
    if (display_info->font_page_1 != NULL)
    {
        free(display_info->font_page_1);
        display_info->font_page_1 = NULL;
    }
    if (display_info->font_page_2 != NULL)
    {
        free(display_info->font_page_2);
        display_info->font_page_2 = NULL;
    }
}

static void close_all_fonts() {
    close_fonts(&sd_display_info);
    close_fonts(&hd_display_info);
    close_fonts(&overlay_display_info);
    close_fonts(&full_display_info);
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

static void rec_pb_play_loop()
{
    struct timespec last;
    clock_gettime(CLOCK_MONOTONIC, &last);

    int64_t target_diff = NSEC_PER_SEC / 15; // 15 fps
    int64_t next_diff = target_diff;

    while (rec_pb_gls_is_playing())
    {
        struct timespec now;
        clock_gettime(CLOCK_MONOTONIC, &now);
        int64_t diff_ns = timespec_subtract_ns(&now, &last);

        if (diff_ns >= next_diff)
        {
            rec_pb_do_next_frame((uint16_t *) msp_character_map);
            render_screen();

            next_diff = target_diff + (target_diff - diff_ns);
            last = now;
        }
    }

    rec_pb_stop();
}

static void rec_pb_timeout_hook()
{
    uint8_t is_playing = rec_pb_gls_is_playing();

    // Only try start once per playback.
    if (is_playing == true && rec_pb_start_attempted == true) {
        return;
    } else if (is_playing == true) {
        rec_pb_start_attempted = true;
    } else {
        rec_pb_start_attempted = false;
    }

    if (is_playing == true) {
        DEBUG_PRINT("msp_osd: gls playing dvr, let's try too!\n");

        if (rec_pb_start() != 0)
        {
            DEBUG_PRINT("msp_osd: failed to start playback!\n");
            return;
        }

        rec_config_t *rec_config = rec_pb_get_config();
        display_info_t *osd_display_info = malloc(sizeof(display_info_t));
        memset(osd_display_info, 0, sizeof(display_info_t));

        osd_display_info->char_width = rec_config->char_width;
        osd_display_info->char_height = rec_config->char_height;
        osd_display_info->font_width = rec_config->font_width;
        osd_display_info->font_height = rec_config->font_height;
        osd_display_info->x_offset = rec_config->x_offset;
        osd_display_info->y_offset = rec_config->y_offset;

        DEBUG_PRINT("msp_osd: playback config, char_width: %d\n", osd_display_info->char_width);
        DEBUG_PRINT("msp_osd: playback config, char_height: %d\n", osd_display_info->char_height);
        DEBUG_PRINT("msp_osd: playback config, font_width: %d\n", osd_display_info->font_width);
        DEBUG_PRINT("msp_osd: playback config, font_height: %d\n", osd_display_info->font_height);
        DEBUG_PRINT("msp_osd: playback config, x_offset: %d\n", osd_display_info->x_offset);
        DEBUG_PRINT("msp_osd: playback config, y_offset: %d\n", osd_display_info->y_offset);

        DEBUG_PRINT("msp_osd: gls playing dvr, loading font variant %d\n", rec_config->font_variant);
        uint8_t is_hd = osd_display_info->font_width != sd_display_info.font_width;
        load_font(
            &osd_display_info->font_page_1,
            0,
            is_hd,
            rec_config->font_variant);
        load_font(
            &osd_display_info->font_page_2,
            1,
            is_hd,
            rec_config->font_variant);

        // TODO: Sketchy swap here?
        // Might end playback after swapping channel, maybe? So back on live channel but with
        // DISPLAY_DISABLED which would be bad. :(
        current_display_info = osd_display_info;
        clear_overlay();
        display_mode = DISPLAY_RUNNING;

        uint8_t fakehd_was_enabled = fakehd_is_enabled();
        if (fakehd_was_enabled == true) {
            fakehd_disable();
        }

        rec_pb_play_loop();

        current_display_info = &sd_display_info;
        memset(msp_character_map, 0, sizeof(msp_character_map));
        display_mode = DISPLAY_DISABLED;

        if (fakehd_was_enabled == true) {
            fakehd_enable();
        }

        free(osd_display_info->font_page_1);
        free(osd_display_info->font_page_2);
        free(osd_display_info);
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
    rec_pb_load_config();
    check_is_au_overlay_enabled();

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

        if (rec_pb_is_enabled()) {
            rec_pb_timeout_hook();
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
