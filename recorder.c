#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <errno.h>

#include "aio.h"
#include "dji_media.h"

typedef struct frame_io_cb_s {
    struct iocb *cb;
    void *data;
    int len;
} frame_io_cb_t;

static volatile uint8_t quit = 0;

int transfer_channel = 0;

static void sig_handler(int _)
{
    quit = 1;
}

void release_frame(frame_io_cb_t *frame_info) {
    free(frame_info->cb);
    free(frame_info->data);
    free(frame_info);
}

int main(int argc, char *argv[]) {
    signal(SIGINT, sig_handler);

    struct io_event events[1];

    duss_media_apcp_cmd_t apcp_cmd;
    bridge_io_pkt_t pkt;

    int media_channel = dji_open_media_control_channel();
    transfer_channel = dji_open_video_transfer_channel();
    FILE *out_file = fopen(argv[1], "wb");
    static uint64_t file_offset = 0;

    aio_context_t ctx;
    memset(&ctx, 0, sizeof(ctx));
    io_setup(64, &ctx);

    dji_send_media_command(media_channel, DUSS_MEDIA_CMD_GND_STO_START);

    uint32_t last_frame_counter = 0;
    uint32_t frame_counter = 0;

    while(!quit) {
        if(ioctl(transfer_channel, DUSS_CLAIM_BRIDGE_IO_PKT, &pkt) == 0) {
            // some hacky way to bind size to a 4k page boundary, and preserve the offset to use later
            size_t size = pkt.size + 0xfff & 0xfffff000;
            int addr_remainder = pkt.paddr & 0xfff;
            printf("ioctl got packet with size %d at addr %p calc page base %p offset %d\n", pkt.size, pkt.paddr, pkt.paddr & 0xfffff000, addr_remainder);
            if(0x1000 < addr_remainder + size) {
                size += 0x1000;
            }
            void* frame = mmap(0x0, size, 3, 1, transfer_channel, pkt.paddr & 0xfffff000);
            void* frame_base_addr = frame + addr_remainder;
            int msg_type = *(int *)(frame_base_addr + 8);
            switch (msg_type)
            {
            case 3:
            {
                printf("got stream end to change %d %d %d %d\n", *(int *)(frame_base_addr + 0x14), *(int *)(frame_base_addr + 0x18), *(int *)(frame_base_addr + 0x1c), *(int *)(frame_base_addr + 0x20));
                break;
            }
            case 1:
            {
                printf("got stream begin x %d y %d fps %d %d\n", *(int *)(frame_base_addr + 0x14), *(int *)(frame_base_addr + 0x18), *(int *)(frame_base_addr + 0x1c), *(int *)(frame_base_addr + 0x20));
                // yes, we want to fall through, need to write stream header
            }
            default:
            {
                struct iocb *cb = calloc(1, sizeof(struct iocb));
                struct iocb *list_of_iocb[1] = {cb};

                frame_io_cb_t *frame_io = calloc(1, sizeof(frame_io_cb_t));
                
                void *frame_data = (void *)(frame_base_addr + *(int *)(frame_base_addr + 0xc));
                last_frame_counter = frame_counter;
                frame_counter = *(uint32_t *)(frame_base_addr + 0x18);
                if(last_frame_counter + 1 != frame_counter) {
                    printf("!!! Frame counter mismatch, wanted %d got %d\n", last_frame_counter + 1, frame_counter);
                }

                uint32_t frame_len = *(uint32_t *)(frame_base_addr + 0x10);
                
                printf("got %p data len %d frame counter %d\n", frame_data, frame_len, frame_counter);
                
                void *frame_data_copy = malloc(frame_len);
                memcpy(frame_data_copy, frame_data, frame_len);
                
                munmap(frame, size);
                ioctl(transfer_channel, DUSS_RELEASE_BRIDGE_IO_PKT, &pkt);
               
                frame_io->cb = cb;
                frame_io->data = frame_data_copy;
                frame_io->len = frame_len;
                cb->aio_buf = (uintptr_t)frame_data_copy;
                cb->aio_fildes = fileno(out_file);
                cb->aio_nbytes = frame_len;
                cb->aio_offset = file_offset;
                cb->aio_lio_opcode = IOCB_CMD_PWRITE;
                cb->aio_data = (uintptr_t)frame_io;
                int ret = io_submit(ctx, 1, list_of_iocb);  
                file_offset += frame_len; 
                break;
            }
            }
        }
        if(io_getevents(ctx, 0, 1, events, 0) > 0) {
            struct io_event *ev = &events[0];
            frame_io_cb_t *frame_io = (frame_io_cb_t *)ev->data;
            printf("Frame IO cb wrote data, releasing buffers: %p : %d\n", frame_io->data, frame_io->len);
            release_frame(frame_io);
        }
        usleep(1500);
    }
    dji_send_media_command(media_channel, DUSS_MEDIA_CMD_GND_STO_STOP);
    close(transfer_channel);
    close(media_channel);
    fclose(out_file);
}