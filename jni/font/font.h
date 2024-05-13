#pragma once

#include <stdint.h>

#include "../util/display_info.h"

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
    FONT_VARIANT_QUICKSILVER,
    FONT_VARIANT_COUNT
} font_variant_e;

void load_font(display_info_t *display_info, char *font_variant);
void close_font(display_info_t *display_info);
void get_font_path_with_extension(char *font_path_dest, const char *font_path, const char *extension, uint8_t len, uint8_t is_hd, char *font_variant);
