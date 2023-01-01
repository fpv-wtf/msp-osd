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

void shram_set_u8(void *mmap_addr, int mmap_offset, int offset, uint8_t value) {
    uint8_t *addr = mmap_addr + mmap_offset + offset;
    *addr = value;
}

int main(int argc, char *argv[])
{
    av_log_set_level(AV_LOG_DEBUG);

    int shram_fd = open("/dev/mem", O_RDWR);
    if (shram_fd < 0) {
        printf("open shram failed: %s\n", strerror(errno));
        return 1;
    }

    uint64_t shram_base = PDT_SHRAM_BASE & 0xfffff000;
    uint64_t shram_offset = PDT_SHRAM_BASE & 0xfff;
    uint64_t shram_len = PDT_SHRAM_LEN + 0xfff & 0xfffff000;
    printf("shram base: 0x%x\n", shram_base);
    printf("shram offset: 0x%x\n", shram_offset);
    printf("shram len: 0x%x\n", shram_len);

    void *shram_addr = mmap64(NULL, shram_len, PROT_READ | PROT_WRITE, MAP_SHARED, shram_fd, shram_base);
    if (shram_addr == MAP_FAILED) {
        printf("shram mmap failed: %s\n", strerror(errno));
        return 1;
    }
    printf("shram map: %p\n", shram_addr);

    // ????
    shram_set_u64(shram_addr, shram_offset, 0x16, 0);

    // Unpause?
    shram_set_u8(shram_addr, shram_offset, 0x39, 0);

    int mcc = dji_open_media_control_channel();
    int mpc = dji_open_media_playback_channel();

    // dji_send_media_command(mcc, DUSS_MEDIA_CMD_PB_STOP, 0);
    // dji_send_media_command(mcc, DUSS_MEDIA_CMD_GND_LV_STOP, 0);
    dji_send_media_command(mcc, DUSS_MEDIA_CMD_PB_START, 1280 | 720 << 0x10);

    printf("ok!\n");

    AVFormatContext *format_ctx = avformat_alloc_context();
    avformat_open_input(&format_ctx, "/storage/sdcard0/DCIM/100MEDIA/DJIG0020.mp4", NULL, NULL);
    avformat_find_stream_info(format_ctx, NULL);

    AVCodec *codec = avcodec_find_decoder(format_ctx->streams[0]->codecpar->codec_id);
    AVCodecContext *codec_ctx = avcodec_alloc_context3(codec);

    // shram_set_u32(shram_addr, shram_offset, 0x20, format_ctx->streams[0]->time_base.den);
    // shram_set_u32(shram_addr, shram_offset, 0x24, format_ctx->streams[0]->time_base.num);
    shram_set_u32(shram_addr, shram_offset, 0x20, 100);
    shram_set_u32(shram_addr, shram_offset, 0x24, 10000);

    AVBitStreamFilter *bsf = av_bsf_get_by_name("h264_mp4toannexb");
    AVBSFContext *bsf_ctx = NULL;
    av_bsf_alloc(bsf, &bsf_ctx);

    AVPacket av_pkt;
    av_init_packet(&av_pkt);

    bridge_io_pkt_t io_pkt;
    memset(&io_pkt, 0, sizeof(io_pkt));

    int ret = 0;
    stream_in_header_t header;

    int first_frame = 1;
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

        void *frame_page = mmap(NULL, size, 3, 1, mpc, io_pkt.paddr & 0xfffff000);
        void *frame = frame_page + addr_remainder;
        printf("mmap returned %p\n", frame_page);

        header.eof = 0;
        header.is_first_frm = first_frame;
        header.is_parted = 0;
        header.payload_lenth = av_pkt.size;
        header.payload_offset = 0x20;
        header.pts = av_pkt.pts;
        header.eos = 1;
        first_frame = 0;

        printf("pts: %lld\n", av_pkt.pts);

        memcpy(frame, &header, 0x20);
        memcpy(frame + 0x20, av_pkt.data, av_pkt.size);

        printf("copied frame!\n");

        io_pkt.size = av_pkt.size + 0x20;
        io_pkt.notify = 1;

        munmap(frame_page, size);
        ioctl(mpc, DUSS_RELEASE_BRIDGE_IO_PKT, &io_pkt);
        av_packet_unref(&av_pkt);
        usleep(1000000 / 5);
    }

    dji_send_media_command(mcc, DUSS_MEDIA_CMD_PB_STOP, 0);

    return 0;
}
