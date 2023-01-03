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
#include "shram.h"

int main(int argc, char *argv[])
{
    int ret = 0;

    shram_handle_t shram;
    if (shram_open(&shram) != 0) {
        return 1;
    }

    av_log_set_level(AV_LOG_DEBUG);

    int mcc = dji_open_media_control_channel();
    int mpc = dji_open_media_playback_channel();

    // dji_send_media_command(mcc, DUSS_MEDIA_CMD_PB_STOP, 0);
    // dji_send_media_command(mcc, DUSS_MEDIA_CMD_GND_LV_STOP, 0);
    dji_send_media_command(mcc, DUSS_MEDIA_CMD_PB_START, 1280 | 720 << 0x10);

    AVFormatContext *format_ctx = avformat_alloc_context();
    avformat_open_input(&format_ctx, "./bunny.mp4", NULL, NULL);
    avformat_find_stream_info(format_ctx, NULL);

    AVCodec *codec = avcodec_find_decoder(format_ctx->streams[0]->codecpar->codec_id);
    AVCodecContext *codec_ctx = avcodec_alloc_context3(codec);

    shram_set_u32(&shram, SHRAM_OFFSET_RATE_NUM, format_ctx->streams[0]->time_base.num);
    shram_set_u32(&shram, SHRAM_OFFSET_RATE_DEN, format_ctx->streams[0]->time_base.den);
    shram_set_u64(&shram, 0x18, 0); // ???

    io_pkt_handle_t pkt_handle;
    dji_claim_io_pkt(mpc, &pkt_handle);

    stream_in_header_t header;
    memset(&header, 0, sizeof(header));

    size_t extradata_size = format_ctx->streams[0]->codecpar->extradata_size;
    printf("extradata size: %d\n", extradata_size);
    printf("extradata first byte: %x\n", *(uint8_t *)format_ctx->streams[0]->codecpar->extradata);

    header.eof = 0;
    header.eos = 0;
    header.is_first_frm = 1;
    header.is_parted = 0;
    header.payload_lenth = extradata_size;
    header.payload_offset = 0x20;
    header.pts = 0;

    memcpy(pkt_handle.data, &header, 0x20);
    memcpy(pkt_handle.data + 0x20, format_ctx->streams[0]->codecpar->extradata, extradata_size);

    pkt_handle.pkt.size = 0x20 + extradata_size;
    pkt_handle.pkt.notify = 1;

    dji_release_io_pkt(mpc, &pkt_handle);

    AVBitStreamFilter *bsf = av_bsf_get_by_name("h264_mp4toannexb");
    AVBSFContext *bsf_ctx = NULL;
    av_bsf_alloc(bsf, &bsf_ctx);
    bsf_ctx->par_in = format_ctx->streams[0]->codecpar;
    bsf_ctx->time_base_in = format_ctx->streams[0]->time_base;
    av_bsf_init(bsf_ctx);

    AVPacket av_pkt;
    AVPacket av_pkt_annexb;
    av_init_packet(&av_pkt);
    av_init_packet(&av_pkt_annexb);

    shram_set_u8(&shram, SHRAM_OFFSET_PAUSE, 0);

    while (av_read_frame(format_ctx, &av_pkt) >= 0) {
        printf("frame size: %d\n", av_pkt.size);

        av_bsf_send_packet(bsf_ctx, &av_pkt);
        while (true) {
            ret = av_bsf_receive_packet(bsf_ctx, &av_pkt_annexb);
            if (ret == AVERROR(EAGAIN)) {
                break;
            } else if (ret == AVERROR_EOF || ret < 0) {
                printf("av_bsf_receive_packet failed: %s\n", av_err2str(ret));
                return 1;
            }
        }

        dji_claim_io_pkt(mpc, &pkt_handle);

        header.eof = 0;
        header.eos = 0;
        header.is_first_frm = 0;
        header.is_parted = 0;
        header.payload_lenth = av_pkt_annexb.size;
        header.payload_offset = 0x20;
        header.pts = av_pkt_annexb.pts;
        printf("pts: %lld\n", av_pkt_annexb.pts);

        memcpy(pkt_handle.data, &header, 0x20);
        memcpy(pkt_handle.data + 0x20, av_pkt_annexb.data, av_pkt_annexb.size);

        printf("copied frame!\n");

        pkt_handle.pkt.size = 0x20 + av_pkt_annexb.size;
        pkt_handle.pkt.notify = 1;

        dji_release_io_pkt(mpc, &pkt_handle);
        av_packet_unref(&av_pkt_annexb);

        usleep(100000);
    }

    dji_send_media_command(mcc, DUSS_MEDIA_CMD_PB_STOP, 0);

    return 0;
}
