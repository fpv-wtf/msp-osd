#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>

#include "rec.h"
#include "rec_shim.h"
#include "rec_util.h"

#include "rec_pb.h"

#define MAX_X 60
#define MAX_Y 22
#define MAX_T (MAX_X * MAX_Y)

#ifdef DEBUG
#define DEBUG_PRINT(fmt, args...) fprintf(stderr, "msp_osd.rec_pb: " fmt "\n", ##args)
#else
#define DEBUG_PRINT(fmt, args...)
#endif

cp_vdec_t *rec_pb_cp_vdec = NULL;
vdec_local_player_t *rec_pb_vdec_local_player = NULL;
uint8_t rec_pb_start_attempted = false;

static FILE *osd_fd = NULL;
static rec_config_t osd_config = {0};

static int64_t frame_counter = 0;
static int64_t last_frame_counter = 0;

static rec_frame_header_t current_frame_header = {0};
static uint16_t current_frame_map[MAX_T] = {0};

static rec_frame_header_t next_frame_header = {0};
static uint16_t next_frame_map[MAX_T] = {0};

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

    if (file_header.version != REC_VERSION)
    {
        DEBUG_PRINT("invalid osd file version! expected: %d, got: %d", REC_VERSION, file_header.version);
        fclose(osd_fd);
        osd_fd = NULL;
        return 1;
    }

    DEBUG_PRINT("header ok!");
    memcpy(&osd_config, &file_header.config, sizeof(rec_config_t));

    fread(&current_frame_header, sizeof(rec_frame_header_t), 1, osd_fd);
    fread(&current_frame_map, sizeof(uint16_t), MAX_T, osd_fd);

    fread(&next_frame_header, sizeof(rec_frame_header_t), 1, osd_fd);
    fread(&next_frame_map, sizeof(uint16_t), MAX_T, osd_fd);

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

int rec_pb_get_next_frame(int64_t frame_delta, uint16_t *map_out) {
    // frame_counter += frame_delta / 1000 / 1000 / 1000;

    // //DEBUG_PRINT("%lld", rec_pb_cp_vdec->play_tm_ms);

    // frame_counter = rec_pb_cp_vdec->play_tm_ms / (1000 / 60);

    last_frame_counter = frame_counter;
    frame_counter = ((rec_pb_cp_vdec->play_tm_ms) * 60 / 1000) - 45;

    if (frame_counter == last_frame_counter)
    {
        frame_counter += 2;
    }

    // if (llabs((int64_t)frame_counter - rec_pb_cp_vdec->frames_sent) >= 90)
    // {
    //     DEBUG_PRINT("sync: frame_counter: %f, frames_sent: %d", frame_counter, rec_pb_cp_vdec->frames_sent);
    //     frame_counter = rec_pb_cp_vdec->frames_sent;
    // }

    if (frame_counter >= next_frame_header.frame_idx) {
        current_frame_header = next_frame_header;
        memcpy(current_frame_map, next_frame_map, sizeof(uint16_t) * MAX_T);
        memcpy(map_out, &current_frame_map, sizeof(uint16_t) * MAX_T);

        while (true) {
            // DEBUG_PRINT("searching for next frame");

            if (fread(&next_frame_header, sizeof(rec_frame_header_t), 1, osd_fd) != 1) {
                return 1;
            }

            if (next_frame_header.frame_idx >= current_frame_header.frame_idx + 2) {
                // DEBUG_PRINT("found frame");
                break;
            }

            if (fseek(osd_fd, sizeof(uint16_t) * MAX_T, SEEK_CUR) != 0) {
                return 1;
            }
        }

        if (fread(&next_frame_map, sizeof(uint16_t), MAX_T, osd_fd) != MAX_T) {
            return 1;
        }
    }

    return 0;
}

bool rec_pb_gls_is_playing()
{
    if (rec_pb_is_ready() == false)
    {
        return false;
    }

    return rec_pb_vdec_local_player->b_running && !rec_pb_vdec_local_player->b_v_eos;
}

bool rec_pb_is_ready()
{
    return rec_pb_cp_vdec != NULL && rec_pb_vdec_local_player != NULL;
}
