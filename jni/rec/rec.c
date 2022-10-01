#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rec.h"
#include "rec_shim.h"

#ifdef DEBUG
#define DEBUG_PRINT(fmt, args...) fprintf(stderr, "msp_osd.rec_shim: " fmt "\n", ##args)
#else
#define DEBUG_PRINT(fmt, args...)
#endif

typedef struct rec_file_header_t
{
    char magic[7];
    uint16_t version;
    rec_config_t config;
} __attribute__((packed)) rec_file_header_t;

typedef struct rec_frame_header_t
{
    uint32_t frame_idx;
    uint32_t size;
} __attribute__((packed)) rec_frame_header_t;

static bool rec_is_ready();
static uint32_t rec_get_frame_idx();

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

    char *file_basename = strrchr(rec_lv_transcode->file_name, '/') + 1;
    char *file_ext = strrchr(file_basename, '.');
    uint8_t file_dir_len = file_basename - rec_lv_transcode->file_name - 1;
    uint8_t file_stem_len = file_ext - file_basename;

    char rec_file_name[256];
    snprintf(
        rec_file_name,
        sizeof(rec_file_name),
        "%.*s/%.*s.osd",
        file_dir_len,
        rec_lv_transcode->file_name,
        file_stem_len,
        file_basename);

    DEBUG_PRINT("rec_file_name: %s", rec_file_name);

    rec_fd = fopen(rec_file_name, "wb");

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

    // DEBUG_PRINT("wrote frame %u", frame_header.frame_idx, frame_header.size);
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
    if (rec_is_ready() == false)
        return 0;

    return rec_lv_transcode->last_frame_idx;
}
