#include "rec_util.h"
#include <string.h>

void rec_util_osd_path_from_video_path(const char *video_path, char *osd_path, size_t osd_path_size)
{
    char *file_basename = strrchr(video_path, '/') + 1;
    char *file_ext = strrchr(file_basename, '.');
    uint8_t file_dir_len = file_basename - video_path - 1;
    uint8_t file_stem_len = file_ext - file_basename;

    snprintf(
        osd_path,
        osd_path_size,
        "%.*s/%.*s.osd",
        file_dir_len,
        video_path,
        file_stem_len,
        file_basename);
}
