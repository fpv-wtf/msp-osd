#include <errno.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>

#include "dji_media.h"
#include "duss_media.h"

int dji_open_media_control_channel() {
    return open(DUSS_MEDIA_CONTROL_PATH, O_RDWR);
}

int dji_open_media_playback_channel() {
    return open(DUSS_MEDIA_DMI_PLAYBACK_PATH, O_RDWR);
}

void dji_init_media_message(duss_media_apcp_cmd_t *apcp_cmd, uint32_t command, uint32_t param) {
    memset(apcp_cmd, 0, sizeof(*apcp_cmd));
    apcp_cmd->magic[0] = 'm';
    apcp_cmd->magic[1] = 'd';
    apcp_cmd->magic[2] = 'i';
    apcp_cmd->magic[3] = 'a';
    apcp_cmd->cmd_id = command;
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    apcp_cmd->param1 = now.tv_sec;
    apcp_cmd->param2 = param;
}

void dji_send_media_command(int media_control_channel, uint32_t command, uint32_t param) {
    duss_media_apcp_cmd_t apcp_cmd;
    dji_init_media_message(&apcp_cmd, command, param);
    write(media_control_channel, &apcp_cmd, sizeof(apcp_cmd));
}


void dji_claim_io_pkt(int fd, io_pkt_handle_t *handle) {
    while (ioctl(fd, DUSS_CLAIM_BRIDGE_IO_PKT, &handle->pkt) != 0) {
        printf("Packet claim failed: %s\n", strerror(errno));
        usleep(100000);
    }

    handle->page_size = handle->pkt.size + 0xfff & 0xfffff000;
    handle->page_offset = handle->pkt.paddr & 0xfff;

    if (0x1000 < handle->page_size + handle->page_offset) {
        handle->page_size += 0x1000;
    }

    handle->page = mmap(NULL, handle->page_size, 3, 1, fd, handle->pkt.paddr & 0xfffff000);
    handle->data = handle->page + handle->page_offset;
}

void dji_release_io_pkt(int fd, io_pkt_handle_t *handle) {
    munmap(handle->page, handle->page_size);

    while (ioctl(fd, DUSS_RELEASE_BRIDGE_IO_PKT, &handle->pkt) != 0) {
        printf("Packet release failed: %s\n", strerror(errno));
        usleep(100000);
    }
}
