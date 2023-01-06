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
#include "dmi_pb.h"
#include "duss_media.h"
#include "shram.h"

int main(int argc, char *argv[])
{
    AVFormatContext *format_ctx = avformat_alloc_context();
    avformat_open_input(
        &format_ctx,
        "/storage/sdcard0/DCIM/100MEDIA/DJIG0167.mp4",
        NULL,
        NULL
    );
    avformat_find_stream_info(format_ctx, NULL);

    dmi_pb_handle_t pb_handle;
    dmi_pb_init(
        &pb_handle,
        &format_ctx->streams[0]->time_base,
        format_ctx->streams[0]->codecpar->width,
        format_ctx->streams[0]->codecpar->height
    );

    dmi_pb_send_extradata(
        &pb_handle,
        format_ctx->streams[0]->codecpar->extradata,
        format_ctx->streams[0]->codecpar->extradata_size
    );

    AVPacket av_pkt;
    av_init_packet(&av_pkt);
    while (av_read_frame(format_ctx, &av_pkt) >= 0)
    {
        dmi_pb_send_packet(&pb_handle, &av_pkt);
        av_packet_unref(&av_pkt);
    }

    dmi_pb_close(&pb_handle);

    return 0;
}
