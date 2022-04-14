#include "duss_media.h"

void dji_init_media_message(duss_media_apcp_cmd_t *apcp_cmd, uint32_t command);
int dji_open_media_control_channel();
int dji_open_video_transfer_channel();
void dji_send_media_command(int media_control_channel, uint32_t command);