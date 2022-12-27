#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../json/osd_config.h"

#include "rec.h"
#include "rec_shim.h"
#include "rec_util.h"

#define REC_CONFIG_ENABLED_KEY "rec_enabled"

#ifdef DEBUG
#define DEBUG_PRINT(fmt, args...) fprintf(stderr, "msp_osd.rec: " fmt "\n", ##args)
#else
#define DEBUG_PRINT(fmt, args...)
#endif

static bool rec_is_ready();
static uint32_t rec_get_frame_idx();

static bool rec_enabled = false;
gs_lv_transcode_t *rec_lv_transcode = NULL;
static FILE *rec_fd = NULL;
static bool rec_recording = false;

void rec_start(rec_config_t *config)
{
    if (!rec_is_ready())
        return;

    if (rec_fd != NULL)
    {
        fflush(rec_fd);
        fclose(rec_fd);
    }

    char rec_file_name[256];
    rec_util_osd_path_from_video_path(
        rec_lv_transcode->file_name,
        rec_file_name,
        sizeof(rec_file_name));
    DEBUG_PRINT("rec_file_name: %s", rec_file_name);

    rec_fd = fopen(rec_file_name, "wb");
    if (rec_fd == NULL)
    {
        DEBUG_PRINT("Failed to open file: %s", rec_file_name);
        return;
    }

    rec_file_header_t file_header = {
        .magic = REC_MAGIC,
        .version = REC_VERSION,
    };
    memcpy(&file_header.config, config, sizeof(rec_config_t));
    fwrite(&file_header, sizeof(rec_file_header_t), 1, rec_fd);

    rec_recording = true;
}

void rec_stop()
{
    if (rec_fd != NULL)
    {
        fflush(rec_fd);
        fclose(rec_fd);
        rec_fd = NULL;
    }

    rec_recording = false;
}

void rec_write_frame(uint16_t *frame_data, size_t frame_size)
{
    if (rec_fd == NULL)
        return;

    rec_frame_header_t frame_header = {
        .frame_idx = rec_get_frame_idx(),
        .size = frame_size,
    };

    fwrite(&frame_header, sizeof(frame_header), 1, rec_fd);
    fwrite(frame_data, sizeof(uint16_t), frame_size, rec_fd);
}

void rec_load_config()
{
    rec_enabled = get_boolean_config_value(REC_CONFIG_ENABLED_KEY);

    DEBUG_PRINT("rec_enabled: %d", rec_enabled);
}

bool rec_is_enabled()
{
    return rec_enabled;
}

bool rec_is_osd_recording()
{
    return rec_recording;
}

bool rec_is_gls_recording()
{
    if (rec_is_ready() == false)
        return false;

    return rec_lv_transcode->cur_state == RECORD_STATE_RECORDING;
}

static bool rec_is_ready()
{
    return rec_lv_transcode != NULL;
}

static uint32_t rec_get_frame_idx()
{

    return rec_lv_transcode->last_frame_idx;
}
