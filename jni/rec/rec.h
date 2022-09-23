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

typedef struct rec_file_header_t
{
    char magic[7];
    uint16_t version;
    uint8_t frame_width;
    uint8_t frame_height;
    uint8_t font_variant;
} __attribute__((packed)) rec_file_header_t;

typedef struct rec_frame_header_t
{
    uint32_t frame_idx;
    uint32_t size;
} __attribute__((packed)) rec_frame_header_t;

void rec_start();
void rec_stop();

bool rec_is_ready();
bool rec_is_osd_recording();
bool rec_is_gls_recording();
uint32_t rec_get_frame_idx();
int64_t rec_get_last_frame_ts();

