#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

#include <libavcodec/avcodec.h>
#include <libavcodec/bsf.h>
#include <libavformat/avformat.h>

#include "dji_media.h"
#include "duss_media.h"
#include "shram.h"

uint8_t *mangle_extradata(uint8_t *extradata, size_t extradata_size,
                          size_t *new_extradata_size)
{
    *new_extradata_size = 0;

    uint8_t *new_extradata = malloc(extradata_size);
    memset(new_extradata, 0, extradata_size);

    uint8_t nalu_len = extradata[4] & 0x03 + 1;
    uint8_t sps_num = extradata[5] & 0x1f;
    uint16_t sps_size = extradata[6] << 8 | extradata[7];
    uint8_t pps_num = extradata[8 + sps_size];
    uint16_t pps_size = extradata[9 + sps_size] << 8 | extradata[10 + sps_size];

    new_extradata[0] = 0x00;
    new_extradata[1] = 0x00;
    new_extradata[2] = 0x00;
    new_extradata[3] = 0x01;
    *new_extradata_size += 4;

    memcpy(new_extradata + 4, extradata + 8, sps_size);
    *new_extradata_size += sps_size;

    (new_extradata + *new_extradata_size)[0] = 0x00;
    (new_extradata + *new_extradata_size)[1] = 0x00;
    (new_extradata + *new_extradata_size)[2] = 0x00;
    (new_extradata + *new_extradata_size)[3] = 0x01;
    *new_extradata_size += 4;

    memcpy(new_extradata + *new_extradata_size, extradata + 11 + sps_size, pps_size);
    *new_extradata_size += pps_size;

    printf("mangle extradata\n");
    printf("nalu_len: %d\n", nalu_len);
    printf("sps_num: %d\n", sps_num);
    printf("sps_size: %d\n", sps_size);
    printf("pps_num: %d\n", pps_num);
    printf("pps_size: %d\n", pps_size);
    printf("new extradata size: %d vs %d\n", *new_extradata_size, extradata_size);

    return new_extradata;
}

uint32_t get_nalu_size(uint8_t nalu_len, uint8_t *frame)
{
    uint32_t nalu_size = 0;

    for (int i = 0; i < nalu_len; i++)
    {
        nalu_size = nalu_size << 8;
        nalu_size |= frame[i];
    }

    return nalu_size;
}

void *mangle_frame(uint8_t *frame, size_t frame_size, size_t *new_frame_size)
{
    uint8_t nalu_len = 4; // TODO: get from extradata

    // Initial check for NALU size here, but seems to throw it away after?
    uint32_t nalu_size = get_nalu_size(nalu_len, frame);
    if (nalu_size == 0)
    {
        printf("nalu size is 0\n");
        return NULL;
    }

    *new_frame_size = 0;
    uint32_t frame_index = 0;

    while (frame_index < frame_size)
    {
        printf("frame index: %u\n", frame_index);
        printf("new frame size: %u\n", *new_frame_size);

        if (nalu_len + frame_index > frame_size)
        {
            printf("frame index + nalu len > frame size\n");
            return NULL;
        }

        nalu_size = get_nalu_size(nalu_len, frame + frame_index);
        frame_index += nalu_len;

        if (frame_size - frame_index < nalu_size)
        {
            printf("frame size - frame index < nalu size\n");
            return NULL;
        }
        else if (nalu_size == 0)
        {
            printf("nalu size is 0\n");
            return NULL;
        }

        frame_index += nalu_size;
        *new_frame_size += nalu_size + 4;
    }

    printf("new frame size: %u\n", *new_frame_size);

    if (*new_frame_size == 0)
    {
        printf("new frame size is 0\n");
        return NULL;
    }

    uint8_t *new_frame = malloc(*new_frame_size);
    memset(new_frame, 0, *new_frame_size);

    frame_index = 0;
    uint32_t new_frame_index = 0;
    while (frame_index < frame_size)
    {
        if (frame_size < frame_index + nalu_len)
        {
            printf("frame size < frame index + nalu len\n");
            return NULL;
        }

        nalu_size = get_nalu_size(nalu_len, frame + frame_index);
        frame_index += nalu_len;

        if (frame_size - frame_index < nalu_size)
        {
            printf("frame size - frame index < nalu size\n");
            return NULL;
        }
        else if (nalu_size == 0)
        {
            printf("nalu size is 0\n");
            return NULL;
        }

        if (*new_frame_size < nalu_size + new_frame_index + 4)
        {
            printf("new frame size < nalu size + frame index 2 + 4\n");
            return NULL;
        }

        (new_frame + new_frame_index)[0] = 0x00;
        (new_frame + new_frame_index)[1] = 0x00;
        (new_frame + new_frame_index)[2] = 0x00;
        (new_frame + new_frame_index)[3] = 0x01;

        memcpy(new_frame + new_frame_index + 4, frame + frame_index, nalu_size);

        frame_index += nalu_size;
        new_frame_index += nalu_size + 4;
    }

    return new_frame;
}

FILE *dump_f = NULL;

int main(int argc, char *argv[])
{
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char buf[256];
    strftime(buf, sizeof(buf), "/storage/sdcard0/pb_dump_%Y%m%d_%H%M%S", tm);
    dump_f = fopen(buf, "w");

    shram_handle_t shram;
    if (shram_open(&shram) != 0)
    {
        return 1;
    }

    av_log_set_level(AV_LOG_DEBUG);
    AVFormatContext *format_ctx = avformat_alloc_context();
    avformat_open_input(
        &format_ctx,
        "/storage/sdcard0/DCIM/100MEDIA/DJIG0167.mp4",
        NULL,
        NULL
    );
    avformat_find_stream_info(format_ctx, NULL);

    AVCodec *codec =
        avcodec_find_decoder(format_ctx->streams[0]->codecpar->codec_id);
    AVCodecContext *codec_ctx = avcodec_alloc_context3(codec);

    int mcc = dji_open_media_control_channel();
    int mpc = dji_open_media_playback_channel();

    // These seem to want flipped around, for some reason? Doesn't match how the glasses do it.
    shram_set_u32(&shram, SHRAM_OFFSET_RATE_NUM, format_ctx->streams[0]->time_base.den);
    shram_set_u32(&shram, SHRAM_OFFSET_RATE_DEN, format_ctx->streams[0]->time_base.num);

    shram_set_u64(&shram, SHRAM_OFFSET_AUDIO_PTS_MAYBE, 0); // Set to 0 in my goggles.
    shram_set_u8(&shram, SHRAM_OFFSET_PAUSE, 0);

    dji_send_media_command(
        mcc,
        DUSS_MEDIA_CMD_PB_START,
        format_ctx->streams[0]->codecpar->width | format_ctx->streams[0]->codecpar->height << 0x10
    );

    stream_in_header_t header;
    io_pkt_handle_t pkt_handle;
    memset(&header, 0, sizeof(header));

    dji_claim_io_pkt(mpc, &pkt_handle);

    size_t new_extradata_size = 0;
    uint8_t *new_extradata = mangle_extradata(
        format_ctx->streams[0]->codecpar->extradata,
        format_ctx->streams[0]->codecpar->extradata_size,
        &new_extradata_size
    );

    header.eof = 1;
    header.eos = 0;
    header.is_first_frm = 1;
    header.is_parted = 0;
    header.payload_lenth = new_extradata_size;
    header.payload_offset = sizeof(header);
    header.pts = 0;
    header.hdr_type = 0;

    memcpy(pkt_handle.data, &header, sizeof(header));
    memcpy(pkt_handle.data + sizeof(header), new_extradata, new_extradata_size);

    fwrite(&header, sizeof(header), 1, dump_f);
    fwrite(new_extradata, new_extradata_size, 1, dump_f);

    free(new_extradata);
    dji_release_io_pkt(mpc, &pkt_handle, sizeof(header) + new_extradata_size);

    AVPacket av_pkt;
    av_init_packet(&av_pkt);
    while (av_read_frame(format_ctx, &av_pkt) >= 0)
    {
        size_t mangled_frame_size = 0;
        void *mangled_frame = mangle_frame(av_pkt.data, av_pkt.size, &mangled_frame_size);

        dji_claim_io_pkt(mpc, &pkt_handle);

        header.eof = 1;
        header.eos = 0;
        header.is_first_frm = 0;
        header.is_parted = 0;
        header.payload_lenth = mangled_frame_size;
        header.payload_offset = sizeof(header);
        header.pts = av_rescale_q(av_pkt.pts, format_ctx->streams[0]->time_base, AV_TIME_BASE_Q);
        header.hdr_type = 0;

        memcpy(pkt_handle.data, &header, sizeof(header));
        memcpy(pkt_handle.data + sizeof(header), mangled_frame, mangled_frame_size);

        fwrite(&header, sizeof(header), 1, dump_f);
        fwrite(mangled_frame, mangled_frame_size, 1, dump_f);
        fflush(dump_f);

        dji_release_io_pkt(mpc, &pkt_handle, sizeof(header) + mangled_frame_size);
        av_packet_unref(&av_pkt);
        free(mangled_frame);
    }

    // Send EOS.
    dji_claim_io_pkt(mpc, &pkt_handle);
    header.eof = 1;
    header.eos = 1;
    header.is_first_frm = 0;
    header.is_parted = 0;
    header.payload_lenth = 0;
    header.payload_offset = sizeof(header);
    header.pts = 0;
    header.hdr_type = 0;
    memcpy(pkt_handle.data, &header, sizeof(header));
    dji_release_io_pkt(mpc, &pkt_handle, sizeof(header));

    dji_send_media_command(mcc, DUSS_MEDIA_CMD_PB_STOP, 0);

    return 0;
}
