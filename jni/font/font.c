#include <sys/fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "../libspng/spng.h"
#include "font.h"
#include "../util/debug.h"

#define BYTES_PER_PIXEL 4
#define HD_FONT_WIDTH 24

/* Font helper methods */

void get_font_path_with_extension(char *font_path_dest, const char *font_path, const char *extension, uint8_t len, uint8_t is_hd, char *font_variant)
{
    char name_buf[len];
    char res_buf[len];

    if (font_variant != NULL && strlen(font_variant) > 0)
    {
        snprintf(name_buf, len, "%s_%s", font_path, font_variant);
    } else {
        snprintf(name_buf, len, "%s", font_path);
    }

    if (is_hd)
    {
        // surely there's a better way...
        snprintf(res_buf, len, "%s", "_hd");
    } else {
        snprintf(res_buf, len, "%s", "");
    }
    snprintf(font_path_dest, len, "%s%s%s", name_buf, res_buf, extension);
    DEBUG_PRINT("Font path: %s\n", font_path_dest);
}

static int open_font(const char *filename, display_info_t *display_info, char *font_variant)
{
    char file_path[255];
    int is_hd = (display_info->font_width == HD_FONT_WIDTH) ? 1 : 0;
    get_font_path_with_extension(file_path, filename, ".png", 255, is_hd, font_variant);
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

void load_font(display_info_t *display_info, char *font_variant) {

    // Note: load_font will not replace an existing font.
    if(display_info->fonts[0] == NULL) {
        int loaded_font = 0;
        DEBUG_PRINT("IN LOAD_FONT\n");
        // create a copy of font_variant
        char font_variant_lower[5] = "";
        if (font_variant  != NULL)
        {
            DEBUG_PRINT("Lowercasing variant\n");
            int length = sizeof(font_variant) / sizeof(char);
            for (int i = 0; i < length; i++)
            {
                font_variant_lower[i] = tolower(font_variant[i]);
            }
        }
        else
        {
            DEBUG_PRINT("Font variant is NULL\n");
        }

        DEBUG_PRINT("Loading font %s\n", font_variant_lower);

        char *fallback_font_variant = "";
        if (font_variant_lower!=NULL && strcmp(font_variant_lower, "btfl") == 0)
        {
            DEBUG_PRINT("Setting fallback font variant to bf\n");
            fallback_font_variant = "bf";
        }
        else if (font_variant_lower != NULL && strcmp(font_variant_lower, "ultr") == 0)
        {
            DEBUG_PRINT("Setting fallback font variant to ultra\n");
            fallback_font_variant = "ultra";
        }

        // try the three paths for the current font
        DEBUG_PRINT("Loading from: %s %s\n", SDCARD_FONT_PATH, font_variant_lower);
        loaded_font = open_font(SDCARD_FONT_PATH, display_info, font_variant_lower);
        if (loaded_font < 0 && strcmp(fallback_font_variant, "") != 0)
        {
            DEBUG_PRINT("Loading fallback variant from: %s %s\n", SDCARD_FONT_PATH, fallback_font_variant);
            loaded_font = open_font(SDCARD_FONT_PATH, display_info, fallback_font_variant);
        }
        if (loaded_font < 0)
        {
            DEBUG_PRINT("Loading from: %s %s\n", FALLBACK_FONT_PATH, font_variant_lower);
            loaded_font = open_font(FALLBACK_FONT_PATH, display_info, font_variant_lower);
        }
        if (loaded_font < 0 && strcmp(fallback_font_variant, "") != 0)
        {
            DEBUG_PRINT("Loading fallback variant from: %s %s\n", FALLBACK_FONT_PATH, fallback_font_variant);
            loaded_font = open_font(FALLBACK_FONT_PATH, display_info, fallback_font_variant);
        }
        if (loaded_font < 0)
        {
            DEBUG_PRINT("Loading from: %s %s\n", ENTWARE_FONT_PATH, font_variant_lower);
            loaded_font = open_font(ENTWARE_FONT_PATH, display_info, font_variant_lower);
        }


        // finally, if we have no fonts for this FC, fallback to the default font
        if (loaded_font)
        {
            DEBUG_PRINT("Loading generic from: %s\n", SDCARD_FONT_PATH);
            loaded_font = open_font(SDCARD_FONT_PATH, display_info, "");
            if (loaded_font < 0)
            {
                DEBUG_PRINT("Loading generic from: %s\n", FALLBACK_FONT_PATH);
                loaded_font = open_font(FALLBACK_FONT_PATH, display_info, "");
            }
            if (loaded_font < 0)
            {
                DEBUG_PRINT("Loading generic from: %s\n", ENTWARE_FONT_PATH);
                loaded_font = open_font(ENTWARE_FONT_PATH, display_info, "");
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

