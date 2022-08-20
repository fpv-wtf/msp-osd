#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <dlfcn.h>
#include <string.h>

#include "osd.h"
#include "hw/dji_display.h"

typedef struct dfb_fbdev_s {
    void *hal_device;
    duss_disp_instance_handle_t *disp_instance;
} dfb_fbdev_t;

static dfb_fbdev_t *dfb_fbdev = 0;
static duss_hal_obj_handle_t ion_handle = 0;
static int started = 0;

// Patch a seemingly unused window management thread in libtp2801.so to inject our code into the dji_glasses process.

void _ZN24MMSFBWindowManagerThread10threadMainEv(void *this) {
    printf("ENTERING MAIN \n");
    while(1) {
        if(started == 0 && dfb_fbdev != NULL && ion_handle != NULL) {
            printf("ENTERING OSD! fbdev ptr %x -> disp %x ion %x\n", dfb_fbdev, dfb_fbdev->disp_instance, ion_handle);
            started = 1;
            osd_directfb(dfb_fbdev->disp_instance, ion_handle);
        }
        usleep(50000);
    }
}

duss_result_t (*duss_hal_mem_alloc2)(duss_hal_obj_handle_t handle, duss_hal_mem_handle_t *mem_handle, uint32_t size, uint32_t param1, uint32_t param2, uint32_t param3) = 0;
static void *hal_lib = 0;

// Patch libduml_hal's duss_hal_mem_alloc.
// Use the first invocation of this to steal the duss_hal_obj_handle_t pointing to the ion shared memory service.
duss_result_t duss_hal_mem_alloc(duss_hal_obj_handle_t handle, duss_hal_mem_handle_t *mem_handle, uint32_t size, uint32_t param1, uint32_t param2, uint32_t param3) {
    if (duss_hal_mem_alloc2 == NULL) {
	    duss_hal_mem_alloc2 = dlsym (RTLD_NEXT, "duss_hal_mem_alloc");
		if (duss_hal_mem_alloc2 == 0){
			hal_lib = dlopen("/system/lib/libduml_hal.so", 1);
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


static void *(*calloc2) ( size_t count, size_t bytes) = 0;
static void *direct_lib = 0;

// Patch libdirect.so's calloc. Detect the allocation of a dfb_fbdev object (first allocated struct with size 0x4C).
// Use this struct to steal the pointer to the duss_disp_instance_handle_t.
void *direct_calloc ( size_t count, size_t bytes) {
    if(calloc2 == NULL) {
	    calloc2 = dlsym (RTLD_NEXT, "direct_calloc");
		if (calloc2 == 0){
			direct_lib = dlopen("/system/lib/libdirect.so", 1);
			calloc2 = dlsym (direct_lib, "direct_calloc");
			if (calloc2 == 0)
			{
				printf("dlsym: %s\n", dlerror());
				return -1;
			}
		}
    }
	void *cal = calloc2(count, bytes);
	
	if(bytes == 0x4c && dfb_fbdev == NULL) {  // dfb_fbdev
		dfb_fbdev = cal;
	}
	
	return cal;
}
