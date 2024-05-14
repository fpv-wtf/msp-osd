#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>

#include "../json/osd_config.h"

#include "rec.h"
#include "rec_shim.h"
#include "rec_util.h"

#include "rec_pb.h"

#include "../font/font.h"

#define REC_PB_CONFIG_ENABLED_KEY "rec_pb_enabled"

#define MAX_X 60
#define MAX_Y 22
#define MAX_T (MAX_X * MAX_Y)

#define FRAME_SIZE (sizeof(rec_frame_header_t) + (sizeof(uint16_t) * MAX_T))

// #ifdef DEBUG
#define DEBUG_PRINT(fmt, args...) fprintf(stderr, "msp_osd.rec_pb: " fmt "\n", ##args)
// #else
// #define DEBUG_PRINT(fmt, args...)
// #endif

cp_vdec_t *rec_pb_cp_vdec = NULL;
vdec_local_player_t *rec_pb_vdec_local_player = NULL;
uint8_t rec_pb_start_attempted = false;

static bool rec_pb_enabled = false;

static FILE *osd_fd = NULL;
static rec_config_t osd_config = {0};

static uint32_t header_size = 0;
static int64_t frame_counter = 0;

static uint32_t *frame_idxs;
static uint32_t frame_idx_len = 0;
static uint32_t current_frame_idx = 0;

void rec_pb_load_config()
{
    rec_pb_enabled = get_boolean_config_value(REC_PB_CONFIG_ENABLED_KEY);

    DEBUG_PRINT("rec_pb_enabled: %d", rec_pb_enabled);
}

bool rec_pb_is_enabled()
{
    return rec_pb_enabled;
}

int rec_pb_start()
{
    if (rec_pb_is_ready() == false)
    {
        return 1;
    }

    if (osd_fd != NULL)
    {
        return 1;
    }

    // TODO: Mutex needed here? Can cause a crash if placback stops as we're trying to read info.
    DEBUG_PRINT("playback on: %s", rec_pb_vdec_local_player->fmt_ctx->filename);

    char osd_path[256];
    rec_util_osd_path_from_video_path(rec_pb_vdec_local_player->fmt_ctx->filename, osd_path, sizeof(osd_path));

    DEBUG_PRINT("osd path: %s", osd_path);
    osd_fd = fopen(osd_path, "rb");
    if (osd_fd == NULL)
    {
        DEBUG_PRINT("osd file not found");
        return 1;
    }

    DEBUG_PRINT("osd file found");
    rec_file_header_t file_header;
    fread(&file_header, sizeof(rec_file_header_t), 1, osd_fd);

    if (strncmp(file_header.magic, REC_MAGIC, sizeof(REC_MAGIC)) != 0)
    {
        DEBUG_PRINT("invalid osd file");
        fclose(osd_fd);
        osd_fd = NULL;
        return 1;
    }

    if (file_header.version == REC_VERSION)
    {
        DEBUG_PRINT("header ok!");
        memcpy(&osd_config, &file_header.config, sizeof(rec_config_t));
        header_size = sizeof(rec_file_header_t);
    }
    else if (file_header.version == 1)
    {
        DEBUG_PRINT("header is v1");
        rec_file_header_v1_t file_header_v1;
        fseek(osd_fd, 0, SEEK_SET);

        fread(&file_header_v1, sizeof(rec_file_header_v1_t), 1, osd_fd);
        if (strncmp(file_header_v1.magic, REC_MAGIC, sizeof(REC_MAGIC)) != 0)
        {
            DEBUG_PRINT("invalid osd file");
            fclose(osd_fd);
            osd_fd = NULL;
            return 1;
        }

        switch (file_header_v1.config.font_variant)
        {
        case FONT_VARIANT_BETAFLIGHT:
            strcpy(file_header.config.font_variant, "BTFL");
            break;
        case FONT_VARIANT_INAV:
            strcpy(file_header.config.font_variant, "INAV");
            break;
        case FONT_VARIANT_ARDUPILOT:
            strcpy(file_header.config.font_variant, "ARDU");
            break;
        case FONT_VARIANT_KISS_ULTRA:
            strcpy(file_header.config.font_variant, "ULTR");
            break;
        case FONT_VARIANT_QUICKSILVER:
            strcpy(file_header.config.font_variant, "QUIC");
            break;
        default:
            file_header.config.font_variant[0] = '\0'; // Empty string
        }

        memcpy(&osd_config, &file_header.config, sizeof(rec_config_t));
        header_size = sizeof(rec_file_header_v1_t);
    }
    else
    {
        DEBUG_PRINT("invalid osd file version! expected: %d, got: %d", REC_VERSION, file_header.version);
        fclose(osd_fd);
        osd_fd = NULL;
        return 1;
    }

    DEBUG_PRINT("loading frame indexes");

    fseek(osd_fd, 0, SEEK_END);
    uint32_t file_size = ftell(osd_fd);
    fseek(osd_fd, header_size, SEEK_SET);
    DEBUG_PRINT("file size: %d", file_size);

    frame_idx_len = file_size / FRAME_SIZE;
    DEBUG_PRINT("frame_idx_len: %d", frame_idx_len);
    frame_idxs = malloc(sizeof(uint32_t) * frame_idx_len);

    for (uint32_t i = 0; i < frame_idx_len; i++)
    {
        rec_frame_header_t frame_header;
        fread(&frame_header, sizeof(rec_frame_header_t), 1, osd_fd);
        frame_idxs[i] = frame_header.frame_idx;
        DEBUG_PRINT("frame_idx: %d = %d", i, frame_idxs[i]);
        fseek(osd_fd, sizeof(uint16_t) * MAX_T, SEEK_CUR);
    }

    fseek(osd_fd, header_size, SEEK_SET);

    current_frame_idx = 0;
    frame_counter = rec_pb_cp_vdec->frames_sent;

    return 0;
}

void rec_pb_stop()
{
    if (osd_fd != NULL)
    {
        fclose(osd_fd);
        osd_fd = NULL;
    }

    rec_pb_cp_vdec = NULL;
    rec_pb_vdec_local_player = NULL;

    free(frame_idxs);
    frame_idxs = NULL;

    DEBUG_PRINT("playback stopped");
}

rec_config_t *rec_pb_get_config()
{
    if (rec_pb_is_ready() == false)
    {
        return NULL;
    }

    return &osd_config;
}

int rec_pb_do_next_frame(uint16_t *map_out)
{
    // -45 is absolutely a magic number based on testing, seems play_tm_ms lags by about that much.
    uint64_t frame_counter = ((rec_pb_cp_vdec->play_tm_ms) * 60 / 1000) - 45;

    uint32_t closest_frame_idx = 0;
    for (uint32_t i = 0; i < frame_idx_len; i++)
    {
        if (frame_idxs[i] > frame_counter)
        {
            break;
        }

        closest_frame_idx = i;
    }

    if (closest_frame_idx == current_frame_idx && current_frame_idx != 0)
    {
        return 0;
    }

    fseek(
        osd_fd,
        header_size + (closest_frame_idx * FRAME_SIZE) + sizeof(rec_frame_header_t),
        SEEK_SET);
    fread(map_out, sizeof(uint16_t), MAX_T, osd_fd);

    current_frame_idx = closest_frame_idx;

    return 0;
}

bool rec_pb_gls_is_playing()
{
    if (rec_pb_is_ready() == false)
    {
        return false;
    }

    // state == 5 is stopped (i.e., when gs_player_stop is called)
    return rec_pb_vdec_local_player->b_running && !rec_pb_vdec_local_player->b_v_eos && rec_pb_vdec_local_player->state != 5;
}

bool rec_pb_is_ready()
{
    return rec_pb_cp_vdec != NULL && rec_pb_vdec_local_player != NULL;
}

