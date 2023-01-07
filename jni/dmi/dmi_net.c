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

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

int listen_sockfd = -1;
int client_sockfd = -1;
struct sockaddr_in listen_addr;

int main(int argc, char *argv[])
{
    AVRational timebase = { 1, 60 };

    dmi_pb_handle_t pb_handle;
    dmi_pb_init(
        &pb_handle,
        &timebase,
        1280,
        720
    );

    listen_sockfd = socket(AF_INET, SOCK_STREAM, 0);

    listen_addr.sin_family = AF_INET;
    listen_addr.sin_addr.s_addr = INADDR_ANY;
    listen_addr.sin_port = htons(5123);
    memset(listen_addr.sin_zero, 0, sizeof(listen_addr.sin_zero));

    bind(listen_sockfd, &listen_addr, sizeof(listen_addr));
    listen(listen_sockfd, 1);
    client_sockfd = accept(listen_sockfd, NULL, NULL);

    printf("client_sockfd: %d\n", client_sockfd);

    uint8_t first_frame = 1;
    stream_in_header_t header;
    memset(&header, 0, sizeof(stream_in_header_t));
    header.eof = 1;
    header.payload_offset = sizeof(stream_in_header_t);
    header.pts = 0;

    uint8_t *frame = NULL;
    uint32_t frame_size = 0;
    uint32_t frame_offset = 0;
    while (true) {
        uint32_t want_len = frame == NULL ? 4 : frame_size - frame_offset;
        uint8_t buf[want_len];

        uint32_t recv_len = recv(client_sockfd, buf, want_len, 0);
        printf("recv_len: %d\n", recv_len);

        if (recv_len <= 0) {
            continue;
        }

        if (frame == NULL) {
            frame_size = *(uint32_t *)buf;
            printf("frame_size: %u\n", frame_size);

            frame = malloc(frame_size);
        } else {
            memcpy(frame + frame_offset, &buf, recv_len);
            frame_offset += recv_len;

            if (frame_offset == frame_size) {
                printf("frame complete\n");

                header.is_first_frm = first_frame;
                header.payload_lenth = frame_size;

                dmi_pb_send(&pb_handle, &header, frame, frame_size);

                first_frame = 0;
                frame_offset = 0;
                frame_size = 0;
                free(frame);
                frame = NULL;
            }
        }
    }

    // av_log_set_level(AV_LOG_DEBUG);

    // AVFormatContext *format_ctx = NULL;
    // avformat_open_input(
    //     &format_ctx,
    //     "rtmp://192.168.42.100/mystream",
    //     NULL,
    //     NULL
    // );
    // avformat_find_stream_info(format_ctx, NULL);

    dmi_pb_close(&pb_handle);

    return 0;
}
