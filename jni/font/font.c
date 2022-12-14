#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>

#include "../libspng/spng.h"
#include "font.h"

#define BYTES_PER_PIXEL 4
#define FALLBACK_FONT_PATH "/blackbox/font"
#define ENTWARE_FONT_PATH "/opt/fonts/font"
#define SDCARD_FONT_PATH "/storage/sdcard0/font"

#define HD_FONT_WIDTH 24

#ifdef DEBUG
#define DEBUG_PRINT(fmt, args...)    fprintf(stderr, fmt, ## args)
#else
#define DEBUG_PRINT(fmt, args...)
#endif

/* Font helper methods */

font_variant_e font_variant_from_string(char *variant_string) {
    font_variant_e font_variant = FONT_VARIANT_GENERIC;
    if(strncmp(variant_string, "ARDU", 4) == 0) {
        font_variant = FONT_VARIANT_ARDUPILOT;
    } else if (strncmp(variant_string, "BTFL", 4) == 0) {
        font_variant = FONT_VARIANT_BETAFLIGHT;
    } else if (strncmp(variant_string, "INAV", 4) == 0) {
        font_variant = FONT_VARIANT_INAV;
    } else if (strncmp(variant_string, "ULTR", 4) == 0) {
        font_variant = FONT_VARIANT_KISS_ULTRA;
    }
    return font_variant;
}

void get_font_path_with_prefix(char *font_path_dest, const char *font_path, uint8_t len, uint8_t is_hd, font_variant_e font_variant)
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

    snprintf(font_path_dest, len, "%s%s.png", name_buf, res_buf);
}

static int open_font(const char *filename, display_info_t *display_info, font_variant_e font_variant)
{
    char file_path[255];
    int is_hd = (display_info->char_width == HD_FONT_WIDTH) ? 1 : 0;
    get_font_path_with_prefix(file_path, filename, 255, is_hd, font_variant);
    DEBUG_PRINT("Opening font: %s\n", file_path);
    struct stat st;
    memset(&st, 0, sizeof(st));
    stat(file_path, &st);
    size_t filesize = st.st_size;
    if(!(filesize > 0)) {
        DEBUG_PRINT("Font file did not exist: %s\n", file_path);
        return -1;
    }

    FILE *fd = fopen(file_path, "rb");
    if (!fd) {
        DEBUG_PRINT("Could not open file %s\n", file_path);
        return -1;
    }
    
    spng_ctx *ctx = spng_ctx_new(0);
    DEBUG_PRINT("Allocated PNG context\n");
    // Set some kind of reasonable PNG limit so we don't get blown up
    size_t limit = 1024 * 1024 * 64;
    spng_set_chunk_limits(ctx, limit, limit);
    DEBUG_PRINT("Set PNG chunk limits\n");
    spng_set_png_file(ctx, fd);
    DEBUG_PRINT("Set PNG file\n");

    struct spng_ihdr ihdr;
    int ret = spng_get_ihdr(ctx, &ihdr);
    DEBUG_PRINT("Got PNG header\n");

    if(ret)
    {
        printf("spng_get_ihdr() error: %s\n", spng_strerror(ret));
        goto err;
    }

    if(ihdr.height != display_info->font_height * NUM_CHARS) {
        printf("font invalid height, got %d wanted %d\n", ihdr.height, display_info->font_height * NUM_CHARS);
        goto err;
    }

    if(ihdr.width % display_info->font_width != 0) {
        printf("font invalid width, not a multiple of %d\n", display_info->font_width);
        goto err;
    }

    DEBUG_PRINT("Image pixel size %d x %d\n", ihdr.width, ihdr.height);

    int num_pages = ihdr.width / display_info->font_width;

    DEBUG_PRINT("Font has %d pages\n", num_pages);

    size_t image_size = 0;
    int fmt = SPNG_FMT_RGBA8;
    ret = spng_decoded_image_size(ctx, fmt, &image_size);
    if(ret) {
        goto err;
    }

    DEBUG_PRINT("Allocating image size %d\n", image_size);

    void* font_data = malloc(image_size);
    ret = spng_decode_image(ctx, font_data, image_size, SPNG_FMT_RGBA8, 0);
    if(ret) {
        printf("Failed to decode PNG!\n");
        free(font_data);
        goto err;
    }

    for(int page = 0; page < num_pages; page++) {
        DEBUG_PRINT("Loading font page %d of %d, placing %x\n", page, num_pages, display_info->fonts);
        display_info->fonts[page] = malloc(display_info->font_width * display_info->font_height * NUM_CHARS * BYTES_PER_PIXEL);
        DEBUG_PRINT("Allocated %d bytes for font page buf at%x\n", display_info->font_width * display_info->font_height * NUM_CHARS * BYTES_PER_PIXEL, display_info->fonts[page]);
        for(int char_num = 0; char_num < NUM_CHARS; char_num++) {
            for(int y = 0; y < display_info->font_height; y++) {
                // Copy each character line at a time into the correct font buffer
                int char_width_bytes = display_info->font_width * BYTES_PER_PIXEL;
                int char_size_bytes_dest = (display_info->font_width * display_info->font_height * BYTES_PER_PIXEL);
                int char_size_bytes_src =  (ihdr.width * display_info->font_height * BYTES_PER_PIXEL);
                memcpy((uint8_t *)display_info->fonts[page] + (char_num * char_size_bytes_dest) + (y * char_width_bytes), (uint8_t *)font_data + (char_num * char_size_bytes_src) + (ihdr.width * y * BYTES_PER_PIXEL) + (page * char_width_bytes), char_width_bytes);
            }
        }
    }

    free(font_data);
    spng_ctx_free(ctx);
    fclose(fd);
    return 0;
    err:
        spng_ctx_free(ctx);
        fclose(fd);
        return -1;
}

void load_font(display_info_t *display_info, font_variant_e font_variant) {
    // Note: load_font will not replace an existing font.
    if(display_info->fonts[0] == NULL) {
        if (open_font(SDCARD_FONT_PATH, display_info, font_variant) < 0) {
            if (open_font(ENTWARE_FONT_PATH, display_info, font_variant) < 0) {
                open_font(FALLBACK_FONT_PATH, display_info, font_variant);
            }
        }
    }
}

void close_font(display_info_t *display_info) {
    for(int i = 0; i < NUM_FONT_PAGES; i++) {
        if(display_info->fonts[i] != NULL) {
            free(display_info->fonts[i]);
            display_info->fonts[i] = NULL;
        }
    }
}