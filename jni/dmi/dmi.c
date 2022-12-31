#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>

#include <libavcodec/avcodec.h>
#include <libavcodec/bsf.h>
#include <libavformat/avformat.h>

#include "dji_media.h"
#include "duss_media.h"

#define PDT_SHRAM_BASE 0xfffc10c0
#define PDT_SHRAM_LEN 0x200

void shram_set_u64(void *mmap_addr, int mmap_offset, int offset, uint64_t value) {
    uint64_t *addr = mmap_addr + mmap_offset + offset;
    *addr = value;
}

void shram_set_u32(void *mmap_addr, int mmap_offset, int offset, uint32_t value) {
    uint32_t *addr = mmap_addr + mmap_offset + offset;
    *addr = value;
}

int main(int argc, char *argv[])
{
    int shram_fd = open("/dev/mem", O_RDWR);
    if (shram_fd < 0) {
        printf("open shram failed: %s\n", strerror(errno));
        return 1;
    }

    int shram_base = PDT_SHRAM_BASE & 0xfffff000;
    int shram_offset = PDT_SHRAM_BASE & 0xfff;
    int shram_len = PDT_SHRAM_LEN + 0xfff & 0xfffff000;
    printf("shram base: 0x%x\n", shram_base);
    printf("shram offset: 0x%x\n", shram_offset);
    printf("shram len: 0x%x\n", shram_len);

    void *shram_addr = mmap(NULL, shram_len, PROT_READ | PROT_WRITE, MAP_SHARED, shram_fd, shram_base);
    if (shram_addr == MAP_FAILED) {
        printf("shram mmap failed: %s\n", strerror(errno));
        return 1;
    }

    // ????
    shram_set_u64(shram_addr, shram_offset, 0x16, 0);

    // Framerate
    shram_set_u32(shram_addr, shram_offset, 0x20, 1);
    shram_set_u32(shram_addr, shram_offset, 0x24, 60);

    AVFormatContext *format_ctx = avformat_alloc_context();
    avformat_open_input(&format_ctx, "./bunny.mp4", NULL, NULL);
    avformat_find_stream_info(format_ctx, NULL);

    AVCodec *codec = avcodec_find_decoder(format_ctx->streams[0]->codecpar->codec_id);
    AVCodecContext *codec_ctx = avcodec_alloc_context3(codec);

    AVBitStreamFilter *bsf = av_bsf_get_by_name("h264_mp4toannexb");
    AVBSFContext *bsf_ctx = NULL;
    av_bsf_alloc(bsf, &bsf_ctx);

    int mcc = dji_open_media_control_channel();
    int mpc = dji_open_media_playback_channel();

    // dji_send_media_command(mcc, DUSS_MEDIA_CMD_GND_LV_STOP, 0);
    dji_send_media_command(mcc, DUSS_MEDIA_CMD_PB_START, 1280 | 720 << 0x10);

    bridge_io_pkt_t io_pkt;
    memset(&io_pkt, 0, sizeof(io_pkt));

    AVPacket av_pkt;
    av_init_packet(&av_pkt);

    int ret = 0;
    while (av_read_frame(format_ctx, &av_pkt) >= 0) {
        av_bsf_send_packet(bsf_ctx, &av_pkt);
        av_bsf_receive_packet(bsf_ctx, &av_pkt);
        printf("frame size: %d\n", av_pkt.size);

        while (ioctl(mpc, DUSS_CLAIM_BRIDGE_IO_PKT, &io_pkt) != 0) {
            printf("ioctl failed: %s\n", strerror(errno));
            usleep(100000);
        }

        size_t size = io_pkt.size + 0xfff & 0xfffff000;
        int addr_remainder = io_pkt.paddr & 0xfff;
        printf("ioctl got packet with size %x at addr %p calc page base %p offset %d\n", io_pkt.size, io_pkt.paddr, io_pkt.paddr & 0xfffff000, addr_remainder);
        if(0x1000 < addr_remainder + size) {
            size += 0x1000;
        }

        void *frame = mmap(NULL, size, 3, 1, mpc, io_pkt.paddr & 0xfffff000);
        printf("mmap returned %p\n", frame);

        // memcpy(frame + addr_remainder, av_pkt.data, 1);

        munmap(frame, size);
        ioctl(mpc, DUSS_RELEASE_BRIDGE_IO_PKT, &io_pkt);
        av_packet_unref(&av_pkt);
        // sleep(1);
    }

    dji_send_media_command(mcc, DUSS_MEDIA_CMD_PB_STOP, 0);

    return 0;
}
