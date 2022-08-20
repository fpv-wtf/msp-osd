#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <dlfcn.h>
#include <string.h>

#include "osd.h"
#include "hw/dji_display.h"

static duss_disp_instance_handle_t *disp_instance = NULL;
static duss_hal_obj_handle_t ion_handle = NULL;
static int started = 0;

// Patch a seemingly unused window management thread in libtp2801.so to inject our code into the dji_glasses process.

void _ZN24MMSFBWindowManagerThread10threadMainEv(void *this) {
    printf("ENTERING MAIN \n");
    while(1) {
        if(started == 0 && disp_instance != NULL && ion_handle != NULL) {
            printf("ENTERING OSD! fbdev disp %x ion %x\n", disp_instance, ion_handle);
            started = 1;
            osd_directfb(disp_instance, ion_handle);
        }
        usleep(50000);
    }
}

static void *hal_lib = NULL;

static duss_result_t (*duss_hal_mem_alloc2)(duss_hal_obj_handle_t handle, duss_hal_mem_handle_t *mem_handle, uint32_t size, uint32_t param1, uint32_t param2, uint32_t param3) = 0;
// Patch libduml_hal's duss_hal_mem_alloc.
// Use the first invocation of this to steal the duss_hal_obj_handle_t pointing to the ion shared memory service.
duss_result_t duss_hal_mem_alloc(duss_hal_obj_handle_t handle, duss_hal_mem_handle_t *mem_handle, uint32_t size, uint32_t param1, uint32_t param2, uint32_t param3) {
    if (duss_hal_mem_alloc2 == NULL) {
	    duss_hal_mem_alloc2 = dlsym (RTLD_NEXT, "duss_hal_mem_alloc");
		if (duss_hal_mem_alloc2 == 0){
			if(hal_lib == NULL)
			{
				hal_lib = dlopen("/system/lib/libduml_hal.so", 1);
			}
			duss_hal_mem_alloc2 = dlsym (hal_lib, "duss_hal_mem_alloc");
			if (duss_hal_mem_alloc2 == 0)
			{
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
	    duss_hal_display_aquire_plane2 = dlsym (RTLD_NEXT, "duss_hal_display_aquire_plane");
		if (duss_hal_display_aquire_plane2 == 0){
			if(hal_lib == NULL)
			{
				hal_lib = dlopen("/system/lib/libduml_hal.so", 1);
			}
			duss_hal_display_aquire_plane2 = dlsym (hal_lib, "duss_hal_display_aquire_plane");
			if (duss_hal_display_aquire_plane2 == 0)
			{
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
