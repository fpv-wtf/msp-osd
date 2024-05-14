#pragma once

#include <stdbool.h>
#include <stdint.h>

#define REC_MAGIC "MSPOSD"
#define REC_VERSION 2

typedef struct rec_config_t
{
    uint8_t char_width;
    uint8_t char_height;
    uint8_t font_width;
    uint8_t font_height;
    uint16_t x_offset;
    uint16_t y_offset;
    char font_variant[5];
} __attribute__((packed)) rec_config_t;

typedef struct rec_file_header_t
{
    char magic[7];
    uint16_t version;
    rec_config_t config;
} __attribute__((packed)) rec_file_header_t;

typedef struct rec_config_v1_t
{
    uint8_t char_width;
    uint8_t char_height;
    uint8_t font_width;
    uint8_t font_height;
    uint16_t x_offset;
    uint16_t y_offset;
    uint8_t font_variant;
} __attribute__((packed)) rec_config_v1_t;

typedef struct rec_file_header_v1_t
{
    char magic[7];
    uint16_t version;
    rec_config_v1_t config;
} __attribute__((packed)) rec_file_header_v1_t;

typedef struct rec_frame_header_t
{
    uint32_t frame_idx;
    uint32_t size;
} __attribute__((packed)) rec_frame_header_t;

void rec_start();
void rec_stop();
void rec_load_config();
void rec_write_frame(uint16_t *frame_data, size_t frame_size);
bool rec_is_enabled();
bool rec_is_osd_recording();
bool rec_is_gls_recording();

