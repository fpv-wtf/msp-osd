#include <dlfcn.h>
#include <stdio.h>
#include <string.h>

#include "rec_shim.h"

#ifdef DEBUG
#define DEBUG_PRINT(fmt, args...) fprintf(stderr, "msp_osd.rec_shim: " fmt "\n", ##args)
#else
#define DEBUG_PRINT(fmt, args...)
#endif

duss_osal_priority_t (*duss_osal_task_create_orig)(
    duss_osal_task_attrib_t *task_attrib,
    duss_osal_task_handle_t **task_handle) = NULL;

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
    DEBUG_PRINT("got lv_transcode from record_thread: %p", rec_lv_transcode);
  }

  return duss_osal_task_create_orig(task_attrib, task_handle);
}
