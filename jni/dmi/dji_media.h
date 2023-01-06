#pragma once

#include "duss_media.h"

int dji_open_media_control_channel();
int dji_open_media_playback_channel();

void dji_init_media_message(duss_media_apcp_cmd_t *apcp_cmd, uint32_t command, uint32_t param);
void dji_send_media_command(int media_control_channel, uint32_t command, uint32_t param);

typedef struct io_pkt_handle {
    bridge_io_pkt_t pkt;

    void *page;
    size_t page_size;
    uint32_t page_offset;

    void *data;
} io_pkt_handle_t;

void dji_claim_io_pkt(int fd, io_pkt_handle_t *pkt);
void dji_release_io_pkt(int fd, io_pkt_handle_t *pkt, size_t pkt_size);
