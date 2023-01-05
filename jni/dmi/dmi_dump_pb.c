#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>

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

    io_pkt_handle_t pkt_handle;

    int mcc = dji_open_media_control_channel();
    int mpc = dji_open_media_playback_channel();

    dji_send_media_command(mcc, DUSS_MEDIA_CMD_GND_LV_STOP, 0);
    dji_send_media_command(mcc, DUSS_MEDIA_CMD_PB_STOP, 0);
    dji_send_media_command(mcc, DUSS_MEDIA_CMD_PB_START, 1280 | 720 << 0x10);

    shram_set_u32(&shram, SHRAM_OFFSET_RATE_NUM, 60);
    shram_set_u32(&shram, SHRAM_OFFSET_RATE_DEN, 1);
    shram_set_u32(&shram, 0x18, 0);
    shram_set_u32(&shram, SHRAM_OFFSET_PAUSE, 0);

    int dump_fd = open("/storage/sdcard0/dmi_dump_20230105_144836", O_RDONLY);

    stream_in_header_t header;

    while (ret = read(dump_fd, &header, sizeof(header)) > 0) {
        printf("header.hdr_type: %x\n", header.hdr_type);
        printf("header.is_parted: %x\n", header.is_parted);
        printf("header.eof: %x\n", header.eof);
        printf("header.eos: %x\n", header.eos);
        printf("header.pts: %llx\n", header.pts);
        printf("header.payload_offset: %x\n", header.payload_offset);
        printf("header.payload_lenth: %x\n", header.payload_lenth);
        printf("header.is_first_frm: %x\n", header.is_first_frm);

        dji_claim_io_pkt(mpc, &pkt_handle);
        pkt_handle.pkt.notify = 0;

        memcpy(pkt_handle.data, &header, sizeof(header));
        read(dump_fd, pkt_handle.data + sizeof(header), header.payload_lenth);

        pkt_handle.pkt.size = sizeof(header) + header.payload_lenth;
        pkt_handle.pkt.notify = 1;

        dji_release_io_pkt(mpc, &pkt_handle);

        // usleep(100000);
    }

    dji_send_media_command(mcc, DUSS_MEDIA_CMD_PB_STOP, 0);
    close(dump_fd);

    return 0;
}

