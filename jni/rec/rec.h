#pragma once

#include <stdbool.h>
#include <stdint.h>

#define REC_MAGIC "MSPOSD"
#define REC_VERSION 1

typedef struct rec_start_config_t
{
    uint8_t frame_width;
    uint8_t frame_height;
    uint8_t font_variant;
} rec_start_config_t;

void rec_start();
void rec_stop();
bool rec_is_osd_recording();
bool rec_is_gls_recording();

