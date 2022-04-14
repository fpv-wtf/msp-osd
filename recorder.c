#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <fcntl.h>

#include "dji_media.h"

static volatile uint8_t quit = 0;

static void sig_handler(int _)
{
    quit = 1;
}

int main(int argc, char *argv[]) {
    signal(SIGINT, sig_handler);

    duss_media_apcp_cmd_t apcp_cmd;
    bridge_io_pkt_t pkt;

    int media_channel = dji_open_media_control_channel();
    int transfer_channel = dji_open_video_transfer_channel();
    FILE *out_file = fopen(argv[1], "wb");

    dji_send_media_command(media_channel, DUSS_MEDIA_CMD_GND_STO_START);

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
                void *frame_data = (void *)(frame_base_addr + *(int *)(frame_base_addr + 0xc));
                uint32_t frame_len = *(uint32_t *)(frame_base_addr + 0x10);
                printf("got %p data len %d\n", frame_data, frame_len);
                fwrite(frame_data, frame_len, 1, out_file);
                break;
            }
            }
            munmap(frame, size);
            ioctl(transfer_channel, DUSS_RELEASE_BRIDGE_IO_PKT, &pkt);
        }
        usleep(5000);
    }
    dji_send_media_command(media_channel, DUSS_MEDIA_CMD_GND_STO_STOP);
    close(transfer_channel);
    close(media_channel);
    fclose(out_file);
}