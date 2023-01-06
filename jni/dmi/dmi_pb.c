#include "dji_media.h"
#include "dmi_pb.h"
#include "duss_media.h"
#include "shram.h"

static void dmi_pb_send(dmi_pb_handle_t* handle, stream_in_header_t *header, uint8_t *data, size_t size);

static uint8_t *mangle_extradata(uint8_t *extradata, size_t extradata_size, size_t *new_extradata_size);
static uint32_t get_nalu_size(uint8_t nalu_len, uint8_t *frame);
static void *mangle_frame(uint8_t *frame, size_t frame_size, size_t *new_frame_size);

void dmi_pb_init(dmi_pb_handle_t* handle, AVRational *time_base, uint32_t width, uint32_t height) {
    shram_open(&handle->shram_handle);
    shram_set_u32(&handle->shram_handle, SHRAM_OFFSET_RATE_NUM, time_base->den);
    shram_set_u32(&handle->shram_handle, SHRAM_OFFSET_RATE_DEN, time_base->num);
    shram_set_u64(&handle->shram_handle, SHRAM_OFFSET_AUDIO_PTS_MAYBE, 0);
    shram_set_u8(&handle->shram_handle, SHRAM_OFFSET_PAUSE, 0);

    handle->media_control_channel = dji_open_media_control_channel();
    handle->media_playback_channel = dji_open_media_playback_channel();

    printf("media_control_channel: %d\n", handle->media_control_channel);
    printf("media_playback_channel: %d\n", handle->media_playback_channel);

    dji_send_media_command(
        handle->media_control_channel,
        DUSS_MEDIA_CMD_PB_START,
        width | height << 0x10
    );
}

void dmi_pb_close(dmi_pb_handle_t* handle) {
    stream_in_header_t header;
    memset(&header, 0, sizeof(header));
    header.eof = 1;
    header.eos = 1;
    dmi_pb_send(handle, &header, NULL, 0);

    dji_send_media_command(handle->media_control_channel, DUSS_MEDIA_CMD_PB_STOP, 0);
}

void dmi_pb_send_extradata(dmi_pb_handle_t* handle, uint8_t *extradata, size_t extradata_size) {
    size_t new_extradata_size;
    uint8_t *new_extradata = mangle_extradata(extradata, extradata_size, &new_extradata_size);

    stream_in_header_t header;
    memset(&header, 0, sizeof(header));
    header.eof = 1;
    header.is_first_frm = 1;
    header.payload_lenth = new_extradata_size;
    header.payload_offset = sizeof(stream_in_header_t);
    header.pts = 0;

    dmi_pb_send(handle, &header, new_extradata, new_extradata_size);
    free(new_extradata);
}

void dmi_pb_send_packet(dmi_pb_handle_t* handle, AVPacket *pkt) {
    size_t new_frame_size;
    uint8_t *new_frame = mangle_frame(pkt->data, pkt->size, &new_frame_size);

    stream_in_header_t header;
    memset(&header, 0, sizeof(header));
    header.eof = 1;
    header.is_first_frm = 0;
    header.payload_lenth = new_frame_size;
    header.payload_offset = sizeof(stream_in_header_t);
    header.pts = 0;

    dmi_pb_send(handle, &header, new_frame, new_frame_size);
    free(new_frame);
}

static void dmi_pb_send(dmi_pb_handle_t* handle, stream_in_header_t *header, uint8_t *data, size_t size) {
    io_pkt_handle_t pkt_handle;

    dji_claim_io_pkt(handle->media_playback_channel, &pkt_handle);

    memcpy(pkt_handle.data, header, sizeof(stream_in_header_t));
    memcpy(pkt_handle.data + sizeof(stream_in_header_t), data, size);

    dji_release_io_pkt(handle->media_playback_channel, &pkt_handle, sizeof(stream_in_header_t) + size);
}


static uint8_t *mangle_extradata(uint8_t *extradata, size_t extradata_size,
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

static uint32_t get_nalu_size(uint8_t nalu_len, uint8_t *frame)
{
    uint32_t nalu_size = 0;

    for (int i = 0; i < nalu_len; i++)
    {
        nalu_size = nalu_size << 8;
        nalu_size |= frame[i];
    }

    return nalu_size;
}

static void *mangle_frame(uint8_t *frame, size_t frame_size, size_t *new_frame_size)
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
