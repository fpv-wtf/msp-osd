#include <stdio.h>

#include <libavcodec/avcodec.h>
#include <libavcodec/bsf.h>
#include <libavformat/avformat.h>
#include <libavfilter/avfilter.h>
#include <libavutil/avutil.h>


int main(int argc, char *argv[])
{
    int ret;
    av_log_set_level(AV_LOG_DEBUG);

    AVFormatContext *format_ctx = avformat_alloc_context();
    if (format_ctx == NULL) {
        printf("Could not allocate format context\n");
        return 1;
    }

    if ((ret = avformat_open_input(&format_ctx, "./bunny.mp4", NULL, NULL)) != 0) {
        printf("Couldn't open file: %s\n", av_err2str(ret));
        return 1;
    }

    avformat_find_stream_info(format_ctx, NULL);

    AVCodec *codec = avcodec_find_decoder(format_ctx->streams[0]->codecpar->codec_id);
    if (codec == NULL) {
        printf("Could not find codec\n");
        return 1;
    }

    AVCodecContext *codec_ctx = avcodec_alloc_context3(codec);
    if (codec_ctx == NULL) {
        printf("Could not allocate codec context\n");
        return 1;
    }

    if ((ret = avcodec_parameters_to_context(codec_ctx, format_ctx->streams[0]->codecpar)) < 0) {
        printf("Could not copy codec parameters to codec context\n");
        return 1;
    }

    if ((ret = avcodec_open2(codec_ctx, codec, NULL)) < 0) {
        printf("Could not open codec\n");
        return 1;
    }

    AVBitStreamFilter *bsf = av_bsf_get_by_name("h264_mp4toannexb");
    if (bsf == NULL) {
        printf("Could not find bitstream filter\n");
        return 1;
    }

    AVBSFContext *bsf_ctx = NULL;
    if ((ret = av_bsf_alloc(bsf, &bsf_ctx)) < 0) {
        printf("Could not allocate bitstream filter context\n");
        return 1;
    }

    AVPacket packet;
    av_init_packet(&packet);

    while (av_read_frame(format_ctx, &packet) >= 0) {
        printf("packet size: %d\n", packet.size);

        if (packet.stream_index == 0) {
            if ((ret = av_bsf_send_packet(bsf_ctx, &packet)) < 0) {
                printf("Could not send packet to bitstream filter\n");
                return 1;
            }

            while (ret >= 0) {
                ret = av_bsf_receive_packet(bsf_ctx, &packet);
                if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF) {
                    break;
                } else if (ret < 0) {
                    printf("Could not receive packet from bitstream filter\n");
                    return 1;
                }
            }
        }

        av_packet_unref(&packet);
    }

    printf("done\n");

    avformat_close_input(&format_ctx);

    return 0;
}
