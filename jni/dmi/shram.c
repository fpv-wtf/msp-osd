#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <errno.h>

#include "shram.h"

#define PDT_SHRAM_BASE 0xfffc10c0
#define PDT_SHRAM_LEN 0x200

#define PDT_SHRAM_PAGE (PDT_SHRAM_BASE & 0xfffff000)
#define PDT_SHRAM_PAGE_LEN (PDT_SHRAM_LEN + 0xfff & 0xfffff000)
#define PDT_SHRAM_PAGE_OFFSET (PDT_SHRAM_BASE & 0xfff)

uint8_t shram_open(shram_handle_t *shram) {
    shram->fd = open("/dev/mem", O_RDWR);
    if (shram->fd < 0) {
        printf("open shram failed: %s\n", strerror(errno));
        return 1;
    }

    shram->page_addr = mmap64(NULL, PDT_SHRAM_LEN, PROT_READ | PROT_WRITE, MAP_SHARED, shram->fd, PDT_SHRAM_PAGE);
    if (shram->page_addr == MAP_FAILED) {
        printf("shram mmap failed: %s\n", strerror(errno));
        return 1;
    }

    printf("shram map: %p\n", shram->page_addr);
    return 0;
}

void shram_set_u64(shram_handle_t *shram, uint32_t offset, uint64_t value) {
    uint64_t *addr = shram->page_addr + PDT_SHRAM_PAGE_OFFSET + offset;
    *addr = value;
}

void shram_set_u32(shram_handle_t *shram, uint32_t offset, uint32_t value) {
    uint32_t *addr = shram->page_addr + PDT_SHRAM_PAGE_OFFSET + offset;
    *addr = value;
}

void shram_set_u8(shram_handle_t *shram, uint32_t offset, uint8_t value) {
    uint8_t *addr = shram->page_addr + PDT_SHRAM_PAGE_OFFSET + offset;
    *addr = value;
}
