#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <dlfcn.h>
#include <string.h>

#include "osd.h"
#include "hw/dji_display.h"
#include "hw/dji_services.h"

// Which window in the creation order is the overlay / top menu. Usually 1.
#define MENU_WINDOW_ORDER 1

static duss_disp_instance_handle_t *disp_instance = NULL;
static duss_hal_obj_handle_t ion_handle = NULL;
static int started = 0;
static int are_v2 = 0;
static int window_count = 0;
static void *menu_window = NULL;

// Patch a seemingly unused window management thread in libtp1801_gui.so to inject our code into the dji_glasses process.
void _ZN24MMSFBWindowManagerThread10threadMainEv(void *this) {
    printf("ENTERING MAIN \n");
    are_v2 = dji_goggles_are_v2();
    while(1) {
        if(started == 0 && disp_instance != NULL && ion_handle != NULL) {
            printf("ENTERING OSD! fbdev disp %x ion %x\n", disp_instance, ion_handle);
            started = 1;
            osd_directfb(disp_instance, ion_handle);
        }
        usleep(50000);
    }
}

static void (*_ZN23GlassVideoChnlUIManager19setNextVideoChannelE19GlassVideoChannelId2)(void *this, uint32_t channel_id) = NULL;
static void *tp1801_gui_lib = NULL;

void _ZN23GlassVideoChnlUIManager19setNextVideoChannelE19GlassVideoChannelId(void *this, uint32_t channel_id) {
    if (_ZN23GlassVideoChnlUIManager19setNextVideoChannelE19GlassVideoChannelId2 == NULL) {
        _ZN23GlassVideoChnlUIManager19setNextVideoChannelE19GlassVideoChannelId2 = dlsym(RTLD_NEXT, "_ZN23GlassVideoChnlUIManager19setNextVideoChannelE19GlassVideoChannelId");
        if (_ZN23GlassVideoChnlUIManager19setNextVideoChannelE19GlassVideoChannelId2 == NULL) {
            tp1801_gui_lib = dlopen("/system/lib/libtp1801_gui.so", 1);
            _ZN23GlassVideoChnlUIManager19setNextVideoChannelE19GlassVideoChannelId2 = dlsym(tp1801_gui_lib, "_ZN23GlassVideoChnlUIManager19setNextVideoChannelE19GlassVideoChannelId");
            if (_ZN23GlassVideoChnlUIManager19setNextVideoChannelE19GlassVideoChannelId2 == NULL) {
                printf("dlsym: %s\n", dlerror());
            }
        }
    }
    // RTOS video channels:
    // 1 = Playback
    // 2 = Unknown
    // 3 = Live Video
    // 4 = AV-IN
    if(channel_id == 3) {
        osd_enable();
    } else {
        osd_disable();
    }
    _ZN23GlassVideoChnlUIManager19setNextVideoChannelE19GlassVideoChannelId2(this, channel_id);
}

static void *hal_lib = NULL;

static duss_result_t (*duss_hal_mem_alloc2)(duss_hal_obj_handle_t handle, duss_hal_mem_handle_t *mem_handle, uint32_t size, uint32_t param1, uint32_t param2, uint32_t param3) = 0;
// Patch libduml_hal's duss_hal_mem_alloc.
// Use the first invocation of this to steal the duss_hal_obj_handle_t pointing to the ion shared memory service.
duss_result_t duss_hal_mem_alloc(duss_hal_obj_handle_t handle, duss_hal_mem_handle_t *mem_handle, uint32_t size, uint32_t param1, uint32_t param2, uint32_t param3) {
    if (duss_hal_mem_alloc2 == NULL) {
	    duss_hal_mem_alloc2 = dlsym(RTLD_NEXT, "duss_hal_mem_alloc");
		if (duss_hal_mem_alloc2 == 0){
			if (hal_lib == NULL){
				hal_lib = dlopen("/system/lib/libduml_hal.so", 1);
			}
			duss_hal_mem_alloc2 = dlsym(hal_lib, "duss_hal_mem_alloc");
			if (duss_hal_mem_alloc2 == 0) {
				printf("dlsym: %s\n", dlerror());
				return -1;
			}
		}
    }
    if (ion_handle == NULL) {
        ion_handle = handle;
    }
	return duss_hal_mem_alloc2(handle, mem_handle, size, param1, param2, param3);
}

static duss_result_t (*duss_hal_display_aquire_plane2)(duss_disp_instance_handle_t * , duss_disp_plane_type_t , duss_disp_plane_id_t * ) = 0;

// Patch libduml_hal's duss_hal_display_aquire_plane.
// Use the first invocation of this with plane == 5 to steal the duss_hal_instance_handle_t pointing to the display driver.
duss_result_t duss_hal_display_aquire_plane(duss_disp_instance_handle_t *disp, duss_disp_plane_type_t plane_type, duss_disp_plane_id_t *plane_id) {
	if (duss_hal_display_aquire_plane2 == NULL) {
	    duss_hal_display_aquire_plane2 = dlsym(RTLD_NEXT, "duss_hal_display_aquire_plane");
		if (duss_hal_display_aquire_plane2 == 0){
			if(hal_lib == NULL) {
				hal_lib = dlopen("/system/lib/libduml_hal.so", 1);
			}
			duss_hal_display_aquire_plane2 = dlsym(hal_lib, "duss_hal_display_aquire_plane");
			if (duss_hal_display_aquire_plane2 == 0) {
				printf("dlsym: %s\n", dlerror());
				return -1;
			}
		}
    }
	if(disp_instance == NULL && *plane_id == 5) {
		disp_instance = disp;
	}
	return duss_hal_display_aquire_plane2(disp, plane_type, plane_id);
}

duss_result_t (*duss_hal_display_plane_blending_set2)(duss_disp_instance_handle_t *disp, duss_disp_plane_id_t plane_id, duss_disp_plane_blending_t *blending) = NULL;
duss_result_t duss_hal_display_plane_blending_set(duss_disp_instance_handle_t *disp, duss_disp_plane_id_t plane_id, duss_disp_plane_blending_t *blending) {
    if (duss_hal_display_plane_blending_set2 == NULL) {
	   duss_hal_display_plane_blending_set2 = dlsym(RTLD_NEXT, "duss_hal_display_plane_blending_set");
		if (duss_hal_display_plane_blending_set2 == NULL) {
			if (hal_lib == NULL) {
				hal_lib = dlopen("/system/lib/libduml_hal.so", 1);
			}
			duss_hal_display_plane_blending_set2 = dlsym(hal_lib, "duss_hal_display_plane_blending_set");
			if (duss_hal_display_plane_blending_set2 == NULL) {
				printf("dlsym: %s\n", dlerror());
				return -1;
			}
		}
    }
    // Patch blending order for DJI UI on V1 Goggles to match V2, so we can draw under them.
    if (blending->order == 1) {
        blending->order = 4;
    }
    return duss_hal_display_plane_blending_set2(disp, plane_id, blending);
}