#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <time.h>
#include <unistd.h>

#include "dji_media.h"
#include "duss_media.h"
#include "shram.h"

FILE *dump_f = NULL;

void yoink_close();

void yoink_open() {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char buf[256];
    strftime(buf, sizeof(buf), "/storage/sdcard0/dmi_dump_%Y%m%d_%H%M%S", tm);

    if (dump_f != NULL) {
        yoink_close();
    }

    dump_f = fopen(buf, "w");
}

void yoink_close() {
    if (dump_f == NULL) {
        return;
    }

    fflush(dump_f);
    fflush(dump_f);
    dump_f = NULL;
}

void yoink_do(int fd, bridge_io_pkt_t *pkt) {
    printf("yoinking frame... (fd: %d, pkt: %p)\n", fd, pkt);
    printf("paddr: %x, size: %x, notify: %x\n", pkt->paddr, pkt->size, pkt->notify);

    uint32_t page_size = (pkt->size + 0xfff) & 0xfffff000;
    uint32_t page_offset = pkt->paddr & 0xfff;

    void *page = mmap(NULL, page_size, 3, 1, fd, pkt->paddr & 0xfffff000);
    if (page == MAP_FAILED) {
        printf("mmap failed: %s\n", strerror(errno));
        return;
    }

    void *data = page + page_offset;

    stream_in_header_t *header = data;
    uint8_t *payload = data + sizeof(stream_in_header_t);

    printf("header->hdr_type: %x\n", header->hdr_type);
    printf("header->is_parted: %x\n", header->is_parted);
    printf("header->eof: %x\n", header->eof);
    printf("header->eos: %x\n", header->eos);
    printf("header->pts: %llx\n", header->pts);
    printf("header->payload_offset: %x\n", header->payload_offset);
    printf("header->payload_lenth: %x\n", header->payload_lenth);
    printf("header->is_first_frm: %x\n", header->is_first_frm);

    fwrite(header, sizeof(stream_in_header_t), 1, dump_f);
    fwrite(payload, header->payload_lenth, 1, dump_f);
    fflush(dump_f);

    munmap(page, page_size);
}

void yoink_frame(uint8_t *buf, size_t len, uint8_t key, uint8_t eos, uint32_t pts) {
    stream_in_header_t header;
    memset(&header, 0, sizeof(header));

    header.hdr_type = 0;
    header.is_parted = 0;
    header.is_first_frm = 0;
    header.eof = 1;
    header.eos = eos;
    header.pts = pts;
    header.payload_offset = sizeof(stream_in_header_t);
    header.payload_lenth = len;

    fwrite(&header, sizeof(stream_in_header_t), 1, dump_f);
    fwrite(buf, len, 1, dump_f);
    fflush(dump_f);
}
