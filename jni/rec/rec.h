#pragma once

#include <stdbool.h>
#include <stdint.h>

#define REC_MAGIC "MSPOSD"
#define REC_VERSION 1

typedef struct rec_config_t
{
    uint8_t char_width;
    uint8_t char_height;
    uint8_t font_width;
    uint8_t font_height;
    uint16_t x_offset;
    uint16_t y_offset;
    uint8_t font_variant;
} __attribute__((packed)) rec_config_t;

void rec_start();
void rec_stop();
bool rec_is_osd_recording();
bool rec_is_gls_recording();

