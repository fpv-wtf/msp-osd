#pragma once

#include <stdint.h>

#define NUM_CHARS 256
#define NUM_FONT_PAGES 4

typedef struct display_info_s {
    uint8_t char_width;
    uint8_t char_height;
    uint8_t font_width;
    uint8_t font_height;
    uint16_t x_offset;
    uint16_t y_offset;
    void *fonts[NUM_FONT_PAGES];
} display_info_t;