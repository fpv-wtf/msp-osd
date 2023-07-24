#pragma once

#include "hw/dji_display.h"

void osd_directfb(duss_disp_instance_handle_t *disp, duss_hal_obj_handle_t ion_handle);
void osd_disable();
void osd_enable();