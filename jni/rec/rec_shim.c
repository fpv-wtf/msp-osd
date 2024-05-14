#include <dlfcn.h>
#include <stdio.h>
#include <string.h>

#include "../hw/dji_services.h"
#include "rec_shim.h"

#ifdef DEBUG
#define DEBUG_PRINT(fmt, args...) fprintf(stderr, "msp_osd.rec_shim: " fmt "\n", ##args)
#else
#define DEBUG_PRINT(fmt, args...)
#endif

duss_osal_priority_t (*duss_osal_task_create_orig)(
    duss_osal_task_attrib_t *task_attrib,
    duss_osal_task_handle_t **task_handle) = NULL;

extern cp_vdec_t *rec_pb_cp_vdec;
extern vdec_local_player_t *rec_pb_vdec_local_player;

extern gs_lv_transcode_t *rec_lv_transcode;

duss_osal_priority_t duss_osal_task_create(
    duss_osal_task_attrib_t *task_attrib,
    duss_osal_task_handle_t **task_handle)
{
    if (duss_osal_task_create_orig == NULL)
    {
        duss_osal_task_create_orig = dlsym(RTLD_NEXT, "duss_osal_task_create");
    }

    if (strcmp(task_attrib->name, "record_thread") == 0)
    {
        rec_lv_transcode = task_attrib->param;
        DEBUG_PRINT("got lv_transcode_t from record_thread: %p", rec_lv_transcode);
    }
    else if (strcmp(task_attrib->name, "player_thread") == 0)
    {
        gs_info_t *ctx = task_attrib->param;

        if (dji_goggles_are_v2())
        {
            rec_pb_vdec_local_player = *(vdec_local_player_t **)((void *)ctx + 0x8b8);
        }
        else
        {
            rec_pb_vdec_local_player = *(vdec_local_player_t **)((void *)ctx + 0x8b4);
        }

        DEBUG_PRINT("got vdec_local_player_t from player_thread: %p", rec_pb_vdec_local_player);
    }
    else if (strcmp(task_attrib->name, "vdec_thread") == 0)
    {
        rec_pb_cp_vdec = task_attrib->param;
        DEBUG_PRINT("got cp_vdec_t from vdec_thread: %p", rec_pb_cp_vdec);
    }

    return duss_osal_task_create_orig(task_attrib, task_handle);
}
