#include <stdint.h>

#include "../util/display_info.h"

typedef enum {
    FONT_VARIANT_GENERIC,
    FONT_VARIANT_BETAFLIGHT,
    FONT_VARIANT_INAV,
    FONT_VARIANT_ARDUPILOT,
    FONT_VARIANT_KISS_ULTRA
} font_variant_e;

void load_font(display_info_t *display_info, font_variant_e font_variant);
void close_font(display_info_t *display_info);
void get_font_path_with_prefix(char *font_path_dest, const char *font_path, uint8_t len, uint8_t is_hd, font_variant_e font_variant);
font_variant_e font_variant_from_string(char *variant_string);