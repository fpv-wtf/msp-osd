#include "../duml_hal.h"

duss_result_t duss_hal_initialize(duss_hal_device_desc_t *)
{
    duss_result_t dummy;

    return dummy;
}


duss_result_t duss_hal_deinitialize()
{
    duss_result_t dummy;

    return dummy;
}


duss_result_t duss_hal_device_open(char *device_name, void *unknown, duss_hal_obj_handle_t *)
{
    duss_result_t dummy;

    return dummy;
}


duss_result_t duss_hal_device_start(duss_hal_obj_handle_t, void *)
{
    duss_result_t dummy;

    return dummy;
}


duss_result_t duss_hal_device_close(duss_hal_obj_handle_t)
{
    duss_result_t dummy;

    return dummy;
}


duss_result_t duss_hal_device_stop(duss_hal_obj_handle_t)
{
    duss_result_t dummy;

    return dummy;
}


duss_result_t duss_hal_mem_alloc(duss_hal_obj_handle_t, duss_hal_mem_handle_t *, uint32_t size, uint32_t, uint32_t, uint32_t)
{
    duss_result_t dummy;

    return dummy;
}


duss_result_t duss_hal_mem_get_phys_addr(duss_hal_mem_handle_t, void **)
{
    duss_result_t dummy;

    return dummy;
}


duss_result_t duss_hal_mem_map(duss_hal_mem_handle_t, void **)
{
    duss_result_t dummy;

    return dummy;
}


duss_result_t duss_hal_mem_free(duss_hal_mem_handle_t)
{
    duss_result_t dummy;

    return dummy;
}


duss_result_t duss_hal_mem_sync(duss_hal_mem_handle_t, uint32_t)
{
    duss_result_t dummy;

    return dummy;
}


duss_result_t duss_hal_display_open(duss_hal_obj_handle_t, duss_disp_instance_handle_t **, duss_disp_vop_id_t)
{
    duss_result_t dummy;

    return dummy;
}


duss_result_t duss_hal_display_close(duss_hal_obj_handle_t, duss_disp_instance_handle_t **)
{
    duss_result_t dummy;

    return dummy;
}


duss_result_t duss_hal_display_aquire_plane(duss_disp_instance_handle_t *, duss_disp_plane_type_t, duss_disp_plane_id_t *)
{
    duss_result_t dummy;

    return dummy;
}


duss_result_t duss_hal_display_reset(duss_disp_instance_handle_t *)
{
    duss_result_t dummy;

    return dummy;
}


duss_result_t duss_hal_display_register_frame_cycle_callback(duss_disp_instance_handle_t *, duss_disp_plane_id_t, frame_pop_handler *, void *)
{
    duss_result_t dummy;

    return dummy;
}


duss_result_t duss_hal_display_timing_detail_get(duss_disp_instance_handle_t *, duss_disp_timing_detail_t *)
{
    duss_result_t dummy;

    return dummy;
}


duss_result_t duss_hal_display_port_enable(duss_disp_instance_handle_t *, duss_disp_port_id_t, uint8_t)
{
    duss_result_t dummy;

    return dummy;
}


duss_result_t duss_hal_display_plane_blending_set(duss_disp_instance_handle_t *, duss_disp_plane_id_t, duss_disp_plane_blending_t *)
{
    duss_result_t dummy;

    return dummy;
}


duss_result_t duss_hal_display_release_plane(duss_disp_instance_handle_t *, duss_disp_plane_id_t)
{
    duss_result_t dummy;

    return dummy;
}


duss_result_t duss_hal_display_push_frame(duss_disp_instance_handle_t *, duss_disp_plane_id_t, duss_frame_buffer_t *)
{
    duss_result_t dummy;

    return dummy;
}


duss_result_t duss_hal_attach_disp(char *param_1, duss_hal_obj **param_2)
{
    duss_result_t dummy;

    return dummy;
}


duss_result_t duss_hal_attach_ion_mem(char *param_1, duss_hal_obj **param_2)
{
    duss_result_t dummy;

    return dummy;
}


duss_result_t duss_hal_detach_ion_mem()
{
    duss_result_t dummy;

    return dummy;
}


duss_result_t duss_hal_detach_disp()
{
    duss_result_t dummy;

    return dummy;
}


