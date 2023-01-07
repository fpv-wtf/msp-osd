#pragma once

#include <libavcodec/avcodec.h>
#include "shram.h"

typedef struct dmi_pb_handle {
    int media_playback_channel;
    int media_control_channel;
    shram_handle_t shram_handle;
} dmi_pb_handle_t;

void dmi_pb_init(dmi_pb_handle_t* handle, AVRational *time_base, uint32_t width, uint32_t height);
void dmi_pb_close(dmi_pb_handle_t* handle);

void dmi_pb_send_extradata(dmi_pb_handle_t* handle, uint8_t *extradata, size_t extradata_size);
void dmi_pb_send_packet(dmi_pb_handle_t* handle, AVPacket *pkt);
void dmi_pb_send(dmi_pb_handle_t* handle, stream_in_header_t *header, uint8_t *data, size_t size);
