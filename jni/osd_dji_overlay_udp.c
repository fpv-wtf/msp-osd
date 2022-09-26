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

#define FONT_VARIANT_GENERIC 0
#define FONT_VARIANT_BETAFLIGHT 1
#define FONT_VARIANT_INAV 2
#define FONT_VARIANT_ARDUPILOT 3

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
static uint16_t msp_render_character_map[MAX_DISPLAY_X][MAX_DISPLAY_Y];
static uint16_t overlay_character_map[MAX_DISPLAY_X][MAX_DISPLAY_Y];
static displayport_vtable_t *display_driver;
static uint8_t which_fb = 0;

static char current_fc_variant[5];

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

static display_info_t fakehd_display_info = {
    .char_width = 59,
    .char_height = 22,
    .font_width = 24,
    .font_height = 36,
    .x_offset = 24,
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

/* FakeHD: spread characters for a small OSD across the whole screen */

#define FAKEHD_ENABLE_KEY "fakehd_enable"
#define FAKEHD_LOCK_CENTER_KEY "fakehd_lock_center"
#define FAKEHD_HIDE_THROTTLE_KEY "fakehd_hide_throttle_element"
static int fakehd_enabled = 0;
static int fakehd_hide_throttle_element = 0;
static int fakehd_lock_center = 0;
static int fakehd_trigger_x = 99;
static int fakehd_trigger_y = 99;

static void load_fake_hd_config()
{
    DEBUG_PRINT("checking for fakehd enabled\n");
    if (get_boolean_config_value(FAKEHD_ENABLE_KEY))
    {
        DEBUG_PRINT("fakehd enabled\n");
        fakehd_enabled = 1;
    } else {
        DEBUG_PRINT("fakehd disabled\n");
    }

    DEBUG_PRINT("checking for fakehd hide throttle \n");
    if (get_boolean_config_value(FAKEHD_HIDE_THROTTLE_KEY))
    {
        DEBUG_PRINT("fakehd hide throttle\n");
        fakehd_hide_throttle_element = 1;
    }
    else
    {
        DEBUG_PRINT("fakehd no hide throttle\n");
    }
    DEBUG_PRINT("checking for fakehd lock center \n");
    if (get_boolean_config_value(FAKEHD_LOCK_CENTER_KEY))
    {
        DEBUG_PRINT("fakehd lock center\n");
        fakehd_lock_center = 1;
    }
    else
    {
        DEBUG_PRINT("fakehd no lock center\n");
    }
}

static void fakehd_map_sd_character_map_to_hd()
{
    int render_x = 0;
    int render_y = 0;
    for (int y = 15; y >= 0; y--)
    {
        for (int x = 29; x >= 0; x--)
        {
            // skip if it's not a character
            if (msp_character_map[x][y] != 0)
            {
                // if current element is fly min or throttle icon
                // record the current position as the 'trigger' position
                if (fakehd_trigger_x == 99 &&
                        (
                            msp_character_map[x][y] == 0x9c // fly minutes icon (armed time)
                            ||
                            msp_character_map[x][y] == 0x04 // throttle icon
                        )
                    )
                {
                    DEBUG_PRINT("found fakehd triggger \n");
                    fakehd_trigger_x = x;
                    fakehd_trigger_y = y;
                }

                // if we have seen a trigger (see above) - and it's now gone, switch to centering
                // this is intented to center the menu + postflight stats, which don't contain
                // timer/battery symbols
                if (
                    fakehd_lock_center ||
                    (fakehd_trigger_x != 99 &&
                    msp_character_map[fakehd_trigger_x][fakehd_trigger_y] != 0x9c &&
                    msp_character_map[fakehd_trigger_x][fakehd_trigger_y] != 0x04)
                )
                {
                    render_x = x + 15;
                    render_y = y + 3;
                } else {
                    render_y = y;
                    if (y >= 10)
                    {
                        render_y += 6;
                    }
                    else if (y >= 5)
                    {
                        render_y += 3;
                    }

                    render_x = x;
                    // a full/unspaced couple of rows for warnings...
                    // and the bottom row may as well be as the edges just overlap the DJI built in bits
                    if (y == 6 || y == 7) {
                        render_x += 15;
                    }
                    else if (y == 15)
                    {
                        render_x += 11;
                    }
                    else if (x >= 20)
                    {
                        render_x += 29;
                    }
                    else if (x >= 10)
                    {
                        render_x += 15;
                    }
                }

                // 0 out the throttle element if configured to do so
                // and also the three adjacent positions where the thottle percent will be
                if (fakehd_trigger_x != 99 &&
                    fakehd_hide_throttle_element &&
                    msp_character_map[x][y] == 0x04)
                {
                    msp_render_character_map[render_x][render_y] = 0;
                    (render_x <= 57) && (msp_render_character_map[render_x+1][render_y] = 0);
                    (render_x <= 56) && (msp_render_character_map[render_x+2][render_y] = 0);
                    (render_x <= 55) && (msp_render_character_map[render_x+3][render_y] = 0);
                } else {
                    // otherwise, the normal path
                    msp_render_character_map[render_x][render_y] = msp_character_map[x][y];
                }
            }
        }
    }
}

/* Character map helpers */

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
        // give up if we don't have a font loaded
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
    void *fb_addr = dji_display_get_fb_address(dji_display, which_fb);
    // DJI has a backwards alpha channel - FF is transparent, 00 is opaque.
    memset(fb_addr, 0x000000FF, WIDTH * HEIGHT * BYTES_PER_PIXEL);

    if (fakehd_enabled) {
        fakehd_map_sd_character_map_to_hd();
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
}

static void msp_draw_complete() {
    render_screen();
}

static void msp_callback(msp_msg_t *msp_message)
{
    displayport_process_message(display_driver, msp_message);
}

/* Font helper methods */
static uint8_t font_variant_from_string(char *variant_string) {
    uint8_t font_variant = FONT_VARIANT_GENERIC;
    if(strncmp(current_fc_variant, "ARDU", 4) == 0) {
        font_variant = FONT_VARIANT_ARDUPILOT;
    } else if (strncmp(current_fc_variant, "BTFL", 4) == 0) {
        font_variant = FONT_VARIANT_BETAFLIGHT;
    } else if (strncmp(current_fc_variant, "INAV", 4) == 0) {
        font_variant = FONT_VARIANT_INAV;
    }
    return font_variant;
}

static void get_font_path_with_prefix(char *font_path_dest, const char *font_path, uint8_t len, uint8_t is_hd, uint8_t font_variant, uint8_t page)
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

static int open_font(const char *filename, void **font, uint8_t page, uint8_t is_hd, uint8_t font_variant)
{
    char file_path[255];
    get_font_path_with_prefix(file_path, filename, 255, is_hd, font_variant, page);
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
    void* font_data = malloc(desired_filesize);
    void* mmappedData = mmap(NULL, filesize, PROT_READ, MAP_PRIVATE, fd, 0);
    if (mmappedData != MAP_FAILED) {
        memcpy(font_data, mmappedData, desired_filesize);
        *font = font_data;
    } else {
        printf("Could not map font %s\n", file_path);
        free(font_data);
        *font = 0;
    }
    close(fd);
    munmap(mmappedData, desired_filesize);
    return 0;
}

static void load_font(void *font_buffer, uint8_t page, uint8_t is_hd, uint8_t font_variant) {
    // Note: load_font will not replace an existing font.
    if(font_buffer == NULL) {
        if (open_font(SDCARD_FONT_PATH, &font_buffer, page, is_hd, font_variant) < 0) {
            if (open_font(ENTWARE_FONT_PATH, &font_buffer, page, is_hd, font_variant) < 0) {
                open_font(FALLBACK_FONT_PATH, &font_buffer, page, is_hd, font_variant);
            }
        }
    }
}

static void load_fonts(uint8_t font_variant) {
    load_font(sd_display_info.font_page_1, 0, 0, font_variant);
    load_font(sd_display_info.font_page_2, 1, 0, font_variant);
    load_font(hd_display_info.font_page_1, 0, 1, font_variant);
    load_font(hd_display_info.font_page_2, 1, 1, font_variant);
    load_font(fakehd_display_info.font_page_1, 0, 1, font_variant);
    load_font(fakehd_display_info.font_page_2, 1, 1, font_variant);
    load_font(overlay_display_info.font_page_1, 0, 1, font_variant);
    load_font(overlay_display_info.font_page_2, 1, 1, font_variant);
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
    close_fonts(&fakehd_display_info);
}

static void msp_set_options(uint8_t font_num, uint8_t is_hd) {
    msp_clear_screen();
    if(is_hd) {
        fakehd_enabled = 0;
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

    // On Goggles V1, the UI and video are in Z-Order 1. On Goggles V2, they're in Z-Order 4.
    // Unfortunately, this means we cannot draw below the DJI UI on Goggles V1. But, on Goggles V2 we get what we want.

    display_state->pb_0->order = 2;

    // Global alpha - disable as we want per pixel alpha.

    display_state->pb_0->glb_alpha_en = 0;
    display_state->pb_0->glb_alpha_val = 0;

    // These aren't documented. Blending algorithm 0 is employed for menus and 1 for screensaver.

    display_state->pb_0->blending_alg = 1;

    // No idea what this "plane mode" actually does but it's different on V2
    uint8_t acquire_plane_mode = display_state->is_v2_goggles ? 6 : 0;

    printf("acquire plane\n");
    res = duss_hal_display_aquire_plane(display_state->disp_instance_handle,acquire_plane_mode,&plane_id);
    if (res != 0) {
        printf("failed to acquire plane");
        exit(0);
    }
    res = duss_hal_display_register_frame_cycle_callback(display_state->disp_instance_handle, plane_id, &pop_func, 0);
    if (res != 0) {
        printf("failed to register callback");
        exit(0);
    }

    res = duss_hal_display_plane_blending_set(display_state->disp_instance_handle, plane_id, display_state->pb_0);

    if (res != 0) {
        printf("failed to set blending");
        exit(0);
    }
    printf("alloc ion buf\n");
    res = duss_hal_mem_alloc(display_state->ion_handle,&display_state->ion_buf_0,0x473100,0x400,0,0x17);
    if (res != 0) {
        printf("failed to allocate VRAM");
        exit(0);
    }
    res = duss_hal_mem_map(display_state->ion_buf_0, &display_state->fb0_virtual_addr);
    if (res != 0) {
        printf("failed to map VRAM");
        exit(0);
    }
    res = duss_hal_mem_get_phys_addr(display_state->ion_buf_0, &display_state->fb0_physical_addr);
    if (res != 0) {
        printf("failed to get FB0 phys addr");
        exit(0);
    }
    printf("first buffer VRAM mapped virtual memory is at %p : %p\n", display_state->fb0_virtual_addr, display_state->fb0_physical_addr);

    res = duss_hal_mem_alloc(display_state->ion_handle,&display_state->ion_buf_1,0x473100,0x400,0,0x17);
    if (res != 0) {
        printf("failed to allocate FB1 VRAM");
        exit(0);
    }
    res = duss_hal_mem_map(display_state->ion_buf_1,&display_state->fb1_virtual_addr);
    if (res != 0) {
        printf("failed to map FB1 VRAM");
        exit(0);
    }
    res = duss_hal_mem_get_phys_addr(display_state->ion_buf_1, &display_state->fb1_physical_addr);
    if (res != 0) {
        printf("failed to get FB1 phys addr");
        exit(0);
    }
    printf("second buffer VRAM mapped virtual memory is at %p : %p\n", display_state->fb1_virtual_addr, display_state->fb1_physical_addr);

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
    DEBUG_PRINT("got data %f version spec %d C %f V\n", packet->version_specifier, packet->tx_temperature, packet->tx_voltage / 64.0f);
    char str[8];
    clear_overlay();
    if(au_overlay_enabled) {
        snprintf(str, 8, "%d C", packet->tx_temperature);
        display_print_string(overlay_display_info.char_width - 5, overlay_display_info.char_height - 8, str, 5);
        snprintf(str, 8, "A %2.1fV", packet->tx_voltage / 64.0f);
        display_print_string(overlay_display_info.char_width - 7, overlay_display_info.char_height - 7, str, 7);
    }
    if(packet->version_specifier == 0xFFFF) {
        // should have FC type
        if(strncmp(current_fc_variant, packet->fc_variant, 4) != 0) {
            memcpy(current_fc_variant, packet->fc_variant, 4);
            close_all_fonts();
            load_fonts(font_variant_from_string(current_fc_variant));
            load_fonts(FONT_VARIANT_GENERIC);
        }
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

    load_fake_hd_config();
    check_is_au_overlay_enabled();

    uint8_t is_v2_goggles = dji_goggles_are_v2();
    printf("Detected DJI goggles %s\n", is_v2_goggles ? "V2" : "V1");

    if (fakehd_enabled) {
        current_display_info = &fakehd_display_info;
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

    event_fd = eventfd(0, NULL);
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
    struct timespec button_start, display_start, now;
    memset(&display_start, 0, sizeof(display_start));
    memset(&button_start, 0, sizeof(button_start));

    load_fonts(FONT_VARIANT_GENERIC);
    open_dji_radio_shm(&radio_shm);
    start_display(is_v2_goggles, disp, ion_handle);

    uint64_t event_number;

    while (!quit)
    {
        poll_fds[0].fd = msp_socket_fd;
        poll_fds[0].events = POLLIN;
        poll_fds[1].fd = event_fd;
        poll_fds[1].events = POLLIN;
        poll_fds[2].fd = data_socket_fd;
        poll_fds[2].events = POLLIN;
        poll(poll_fds, 3, -1);

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
                    display_mode = DISPLAY_RUNNING;
                } else {
                    display_mode = DISPLAY_DISABLED;
                }
                render_screen();
            }
        }
    }

    free(display_driver);
    free(msp_state);
    close(msp_socket_fd);
    close(data_socket_fd);
    close(event_fd);
    return;
}
