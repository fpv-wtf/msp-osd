#pragma once

#include <unistd.h>

struct shram_handle {
    int fd;
    void *page_addr;
};
typedef struct shram_handle shram_handle_t;

uint8_t shram_open();

void shram_set_u64(shram_handle_t *shram, uint32_t offset, uint64_t value);
void shram_set_u32(shram_handle_t *shram, uint32_t offset, uint32_t value);
void shram_set_u8(shram_handle_t *shram, uint32_t offset, uint8_t value);

enum shram_offset {
    SHRAM_OFFSET_PAUSE = 0x39,
    SHRAM_OFFSET_RATE_NUM = 0x20,
    SHRAM_OFFSET_RATE_DEN = 0x24
};
