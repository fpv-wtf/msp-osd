#pragma once

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

int rec_pb_start();
void rec_pb_stop();

int rec_pb_get_next_frame(int64_t frame_delta, uint16_t *map_out);

rec_config_t *rec_pb_get_config();

bool rec_pb_is_ready();
bool rec_pb_gls_is_playing();
