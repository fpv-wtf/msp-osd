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

        // try the three paths for the current font
        loaded_font = open_font(SDCARD_FONT_PATH, display_info, font_variant);
        if (loaded_font < 0)
        {
            loaded_font = open_font(FALLBACK_FONT_PATH, display_info, font_variant);
        }
        if (loaded_font < 0)
        {
            loaded_font = open_font(ENTWARE_FONT_PATH, display_info, font_variant);
        }

        // we used to map BTFL to BF in the font filename, so support BF still for B/C
        if (loaded_font < 0 && strcmp(font_variant, "BTFL") == 0)
        {
            loaded_font = open_font(SDCARD_FONT_PATH, display_info, "BF");
            if (loaded_font < 0)
            {
                loaded_font = open_font(FALLBACK_FONT_PATH, display_info, "BF");
            }
            if (loaded_font < 0)
            {
                loaded_font = open_font(ENTWARE_FONT_PATH, display_info, "BF");
            }
        }
        // we used to map ULTR to ULTRA in the font filename, so support ULTRA still for B/C
        if (loaded_font < 0 && strcmp(font_variant, "ULTR") == 0)
        {
            loaded_font = open_font(SDCARD_FONT_PATH, display_info, "ULTRA");
            if (loaded_font < 0)
            {
                loaded_font = open_font(FALLBACK_FONT_PATH, display_info, "ULTRA");
            }
            if (loaded_font < 0)
            {
                loaded_font = open_font(ENTWARE_FONT_PATH, display_info, "ULTRA");
            }
        }

        // finally, if we have no fonts for this FC, fallback to the default font
        if (loaded_font)
        {
            loaded_font = open_font(SDCARD_FONT_PATH, display_info, "");
            if (loaded_font < 0)
            {
                loaded_font = open_font(FALLBACK_FONT_PATH, display_info, "");
            }
            if (loaded_font < 0)
            {
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

void convert_bin_fonts(const char *file_location)
{
    display_info_t sd_display_info = {
        .char_width = 30,
        .char_height = 15,
        .font_width = 36,
        .font_height = 54,
        .x_offset = 180,
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

    char *legacy_fcs[6] = {"", "bf", "inav", "ardu", "ultra", "quic"};

    for (int is_hd = 0; is_hd < 2; is_hd++)
    {
        for (int i = 0; i < 6; i++)
        {
            int page_count = 1;
            char file_path[255];
            get_font_path_with_extension(file_path, file_location, ".bin", 255, is_hd, legacy_fcs[i]);
            char page_2_file_path[255];
            get_font_path_with_extension(page_2_file_path, file_location, "_2.bin", 255, is_hd, legacy_fcs[i]);
            char *file_paths[2] = {file_path, page_2_file_path};
            struct stat st;
            memset(&st, 0, sizeof(st));
            stat(file_path, &st);
            size_t page_1_filesize = st.st_size;
            stat(page_2_file_path, &st);
            size_t page_2_filesize = st.st_size;
            display_info_t display_info = is_hd ? hd_display_info : sd_display_info;
            size_t desired_filesize = display_info.font_height *  display_info.font_width * NUM_CHARS * BYTES_PER_PIXEL;
            DEBUG_PRINT("Found a font candidate to convert: %s %d\n", file_path, page_1_filesize);
            if(page_1_filesize == desired_filesize) {
                DEBUG_PRINT("Found a font to convert: %s %d\n", file_path, desired_filesize);
            } else {
                continue;
            }
            if(page_2_filesize == desired_filesize) {
                page_count = 2;
            }
            void *image_buf = malloc(desired_filesize * page_count);
            for(int page = 0; page < page_count; page++) {
                int fd = open(file_paths[page], O_RDONLY, 0);
                if (!fd) {
                    DEBUG_PRINT("Could not open file %s\n", file_path);
                    continue;
                }
                void* mmappedData = mmap(NULL, desired_filesize, PROT_READ, MAP_PRIVATE, fd, 0);
                if (mmappedData != MAP_FAILED) {
                    for(int char_num = 0; char_num < NUM_CHARS; char_num++) {
                        for(int y = 0; y < display_info.font_height; y++) {
                            // Copy each character line at a time into the correct font buffer
                            int char_width_bytes = display_info.font_width * BYTES_PER_PIXEL;
                            int char_size_bytes_src = (display_info.font_width * display_info.font_height * BYTES_PER_PIXEL);
                            int char_size_bytes_dest =  (display_info.font_width * page_count * display_info.font_height * BYTES_PER_PIXEL);
                            memcpy((uint8_t *)image_buf + (char_num * char_size_bytes_dest) + (display_info.font_width * page_count * y * BYTES_PER_PIXEL) + (page * char_width_bytes), (uint8_t *)mmappedData + (char_num * char_size_bytes_src) + (y * char_width_bytes), char_width_bytes);
                        }
                    }
                } else {
                    DEBUG_PRINT("Could not map font %s\n", file_path);
                    free(image_buf);
                    continue;
                }
                close(fd);
                munmap(mmappedData, desired_filesize);
            }
            char out_file_path[255];
            get_font_path_with_extension(out_file_path, file_location, ".png", 255, is_hd, legacy_fcs[i]);
            FILE* out_fd = fopen(out_file_path, "wb");
            if(out_fd == NULL) {
                DEBUG_PRINT("Could not open output %s\n", out_file_path);
                continue;
            }
            spng_ctx *enc = spng_ctx_new(SPNG_CTX_ENCODER);
            struct spng_ihdr ihdr =
            {
                .width = display_info.font_width * page_count,
                .height = display_info.font_height * NUM_CHARS,
                .bit_depth = 8,
                .color_type = SPNG_COLOR_TYPE_TRUECOLOR_ALPHA
            };
            spng_set_ihdr(enc, &ihdr);
            spng_set_png_file(enc, out_fd);
            spng_encode_image(enc, image_buf, desired_filesize * page_count, SPNG_FMT_PNG, SPNG_ENCODE_FINALIZE);
            spng_ctx_free(enc);
            free(image_buf);
            fclose(out_fd);
        }
    }
}

