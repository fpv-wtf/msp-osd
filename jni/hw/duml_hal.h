#ifndef DUML_HAL_H
#define DUML_HAL_H
#include <stdint.h>

typedef int32_t duss_result_t;

typedef uint8_t duss_hal_state_t;
typedef uint8_t duss_hal_class_t;

struct sem_t {
    uint32_t count;
};

struct duss_osal_mutex_attrib_t {
    char * name;
};

struct duss_osal_mutex_handle_t {
    struct duss_osal_mutex_attrib_t attrib;
    struct sem_t sema;
};

typedef struct duss_osal_mutex_handle_t duss_osal_mutex_handle_t, *Pduss_osal_mutex_handle_t;


typedef struct duss_hal_obj_dev_t duss_hal_obj_dev_t, *Pduss_hal_obj_dev_t;

typedef struct duss_hal_obj * duss_hal_obj_handle_t;

struct duss_hal_obj_dev_t {
    char * name;
    duss_hal_state_t obj_state;
    duss_hal_class_t obj_class;
    uint16_t obj_index;
    int32_t obj_refcnt;
    struct duss_osal_mutex_handle_t * obj_lock;
    struct duss_osal_mutex_handle_t * app_lock;
    duss_result_t (* open)(duss_hal_obj_handle_t, void *);
    duss_result_t (* close)(duss_hal_obj_handle_t);
    duss_result_t (* set_cfg)(duss_hal_obj_handle_t, void *);
    duss_result_t (* get_cfg)(duss_hal_obj_handle_t, void *);
    duss_result_t (* start)(duss_hal_obj_handle_t, void *);
    duss_result_t (* stop)(duss_hal_obj_handle_t, void *);
};

struct duss_hal_obj {
    struct duss_hal_obj_dev_t dev;
    void * dev_class;
    void * dev_priv;
};

struct duss_hal_device_desc_t {
    char * name;
    duss_result_t (* attach)(char *, duss_hal_obj_handle_t *);
    duss_result_t (* detach)(duss_hal_obj_handle_t);
    duss_hal_obj_handle_t obj;
};

typedef enum duss_pixel_format {
    DUSS_PIXFMT_COMPRESSED_END=30002,
    DUSS_PIXFMT_DRAW_V1=30000,
    DUSS_PIXFMT_DUAL_PLANE_16BIT=40003,
    DUSS_PIXFMT_DUAL_PLANE_8BIT=40002,
    DUSS_PIXFMT_GENERAL_END=40004,
    DUSS_PIXFMT_JPEG_LS=30001,
    DUSS_PIXFMT_OPAQUE=0,
    DUSS_PIXFMT_RAW10_PACKED=10004,
    DUSS_PIXFMT_RAW12_PACKED=10005,
    DUSS_PIXFMT_RAW12_UNPACKED=10008,
    DUSS_PIXFMT_RAW14_PACKED=10006,
    DUSS_PIXFMT_RAW14_UNPACKED=10009,
    DUSS_PIXFMT_RAW16_OPAQUE=10001,
    DUSS_PIXFMT_RAW16_UNPACKED=10010,
    DUSS_PIXFMT_RAW18_PACKED=10007,
    DUSS_PIXFMT_RAW18_UNPACKED=10011,
    DUSS_PIXFMT_RAW24_OPAQUE=10002,
    DUSS_PIXFMT_RAW24_UNPACKED=10012,
    DUSS_PIXFMT_RAW32_OPAQUE=10003,
    DUSS_PIXFMT_RAW32_UNPACKED=10013,
    DUSS_PIXFMT_RAW8_OPAQUE=10000,
    DUSS_PIXFMT_RAW_END=10014,
    DUSS_PIXFMT_RGB101010=20003,
    DUSS_PIXFMT_RGB565=20001,
    DUSS_PIXFMT_RGB888=20000,
    DUSS_PIXFMT_RGBA8888=20002,
    DUSS_PIXFMT_RGBA8888_GOGGLES_V2=20012,
    DUSS_PIXFMT_RGB_END=20004,
    DUSS_PIXFMT_SINGLE_PLANE_16BIT=40001,
    DUSS_PIXFMT_SINGLE_PLANE_8BIT=40000,
    DUSS_PIXFMT_YUV10_420_END=1005,
    DUSS_PIXFMT_YUV10_422_END=1105,
    DUSS_PIXFMT_YUV10_444_END=1203,
    DUSS_PIXFMT_YUV10_P444_YUV=1202,
    DUSS_PIXFMT_YUV10_SP420_YUV=1003,
    DUSS_PIXFMT_YUV10_SP420_YUV16=1001,
    DUSS_PIXFMT_YUV10_SP420_YVU=1004,
    DUSS_PIXFMT_YUV10_SP420_YVU16=1002,
    DUSS_PIXFMT_YUV10_SP422_YUV=1103,
    DUSS_PIXFMT_YUV10_SP422_YUV16=1101,
    DUSS_PIXFMT_YUV10_SP422_YVU=1104,
    DUSS_PIXFMT_YUV10_Y422_YUYV16=1102,
    DUSS_PIXFMT_YUV10_Y444_UYVA=1201,
    DUSS_PIXFMT_YUV8_420_END=4,
    DUSS_PIXFMT_YUV8_422_END=106,
    DUSS_PIXFMT_YUV8_444_END=203,
    DUSS_PIXFMT_YUV8_P420_YUV=1,
    DUSS_PIXFMT_YUV8_P422_YUV=105,
    DUSS_PIXFMT_YUV8_P444_YUV=202,
    DUSS_PIXFMT_YUV8_SP420_YUV=2,
    DUSS_PIXFMT_YUV8_SP420_YVU=3,
    DUSS_PIXFMT_YUV8_SP422_YUV=103,
    DUSS_PIXFMT_YUV8_SP422_YVU=104,
    DUSS_PIXFMT_YUV8_Y422_UYVY=101,
    DUSS_PIXFMT_YUV8_Y422_YUYV=102,
    DUSS_PIXFMT_YUV8_Y444_UYV=201,
    DUSS_PIXFMT_YUV_END=1204
} duss_pixel_format;

typedef enum duss_pixel_format duss_pixel_format_t;

struct duss_object {
    int ref_count;
    struct duss_osal_mutex_handle_t * lock;
    void (* on_released)(struct duss_object *);
};

typedef struct duss_object duss_object_t;

typedef struct duss_hal_mem_buf * duss_hal_mem_handle_t;

typedef struct duss_frame_plane duss_frame_plane, *Pduss_frame_plane;

typedef struct duss_frame_plane duss_frame_plane_t;

struct duss_frame_plane {
    int32_t bytes_per_line;
    int32_t offset;
    int32_t plane_height;
    int32_t bytes_written;
};

struct __attribute__((__packed__)) duss_frame_buffer {
    duss_object_t obj;
    duss_hal_mem_handle_t buffer;
    duss_pixel_format_t pixel_format;
    uint32_t unknown;
    int64_t time_stamp;
    int32_t width;
    int32_t height;
    duss_frame_plane_t planes[4];
    int32_t plane_count;
    uint32_t frame_id;
};

typedef struct duss_frame_buffer duss_frame_buffer_t;

typedef struct duss_hal_device_desc_t duss_hal_device_desc_t, *Pduss_hal_device_desc_t;

typedef struct duss_hal_obj duss_hal_obj, *Pduss_hal_obj;

typedef struct duss_disp_instance_handle_t duss_disp_instance_handle_t, *Pduss_disp_instance_handle_t;

struct __attribute__((__packed__)) duss_disp_instance_handle_t {
    uint8_t is_init;
    uint8_t field_0x1;
    uint8_t field_0x2;
    uint8_t field_0x3;
    uint32_t current_vop_index;
    uint32_t ref_cnt;
    duss_hal_obj_handle_t obj;
    void * instance_private_data;
    void * global_disp_info;
};

typedef uint8_t duss_disp_vop_id_t;

typedef uint8_t duss_disp_plane_type_t;

typedef uint8_t duss_disp_port_id_t;

typedef struct duss_disp_timing_detail_t duss_disp_timing_detail_t, *Pduss_disp_timing_detail_t;

typedef enum duss_disp_timing_bitdepth_t {
    DUSS_DISP_BITDEPTH_10BIT=1,
    DUSS_DISP_BITDEPTH_12BIT=2,
    DUSS_DISP_BITDEPTH_8BIT=0
} duss_disp_timing_bitdepth_t;

typedef enum duss_disp_timing_fmt_t {
    DUSS_DISP_FMT_RGB=0,
    DUSS_DISP_FMT_YUV420=3,
    DUSS_DISP_FMT_YUV422=2,
    DUSS_DISP_FMT_YUV444=1
} duss_disp_timing_fmt_t;

struct duss_disp_timing_detail_t {
    int32_t clock;
    int32_t hdisplay;
    int32_t hsync_start;
    int32_t hsync_end;
    int32_t htotal;
    int32_t hskew;
    int32_t vdisplay;
    int32_t vsync_start;
    int32_t vsync_end;
    int32_t vtotal;
    int32_t vscan;
    enum duss_disp_timing_fmt_t disp_fmt;
    enum duss_disp_timing_bitdepth_t disp_bitdepth;
};

typedef struct duss_disp_plane_blending_t duss_disp_plane_blending_t, *Pduss_disp_plane_blending_t;

typedef uint8_t duss_disp_plane_alpha_alg_t;
typedef int8_t duss_disp_plane_id_t;

struct __attribute__((__packed__)) duss_disp_plane_blending_t {
    uint8_t is_enable;
    uint8_t glb_alpha_en;
    uint8_t field_0x2;
    uint8_t field_0x3;
    int32_t glb_alpha_val;
    duss_disp_plane_alpha_alg_t blending_alg;
    duss_disp_plane_id_t order;
    uint8_t field_0xa;
    uint8_t field_0xb;
    int32_t hoffset;
    int32_t voffset;
};

typedef duss_result_t (frame_pop_handler)(duss_disp_instance_handle_t * , duss_disp_plane_id_t , duss_frame_buffer_t * , void * );

duss_result_t duss_hal_initialize(duss_hal_device_desc_t * );
duss_result_t duss_hal_deinitialize();
duss_result_t duss_hal_device_open(char *device_name, void *unknown, duss_hal_obj_handle_t * );
duss_result_t duss_hal_device_start(duss_hal_obj_handle_t , void * );
duss_result_t duss_hal_device_close(duss_hal_obj_handle_t );
duss_result_t duss_hal_device_stop(duss_hal_obj_handle_t );

duss_result_t duss_hal_mem_alloc(duss_hal_obj_handle_t , duss_hal_mem_handle_t * , uint32_t size, uint32_t , uint32_t , uint32_t );
duss_result_t duss_hal_mem_get_phys_addr(duss_hal_mem_handle_t , void * * );
duss_result_t duss_hal_mem_map(duss_hal_mem_handle_t , void * * );
duss_result_t duss_hal_mem_free(duss_hal_mem_handle_t );
duss_result_t duss_hal_mem_sync(duss_hal_mem_handle_t , uint32_t );

duss_result_t duss_hal_display_open(duss_hal_obj_handle_t , duss_disp_instance_handle_t * * , duss_disp_vop_id_t );
duss_result_t duss_hal_display_close(duss_hal_obj_handle_t , duss_disp_instance_handle_t * *);
// sic
duss_result_t duss_hal_display_aquire_plane(duss_disp_instance_handle_t * , duss_disp_plane_type_t , duss_disp_plane_id_t * );
duss_result_t duss_hal_display_reset(duss_disp_instance_handle_t *);
duss_result_t duss_hal_display_register_frame_cycle_callback(duss_disp_instance_handle_t * , duss_disp_plane_id_t , frame_pop_handler * , void * );
duss_result_t duss_hal_display_timing_detail_get(duss_disp_instance_handle_t * , duss_disp_timing_detail_t * );
duss_result_t duss_hal_display_port_enable(duss_disp_instance_handle_t * , duss_disp_port_id_t , uint8_t );
duss_result_t duss_hal_display_plane_blending_set(duss_disp_instance_handle_t * , duss_disp_plane_id_t , duss_disp_plane_blending_t * );
duss_result_t duss_hal_display_release_plane(duss_disp_instance_handle_t * , duss_disp_plane_id_t );
duss_result_t duss_hal_display_push_frame(duss_disp_instance_handle_t * , duss_disp_plane_id_t , duss_frame_buffer_t * );

duss_result_t duss_hal_attach_disp(char *param_1,duss_hal_obj **param_2);
duss_result_t duss_hal_attach_ion_mem(char *param_1,duss_hal_obj **param_2);
duss_result_t duss_hal_detach_ion_mem();
duss_result_t duss_hal_detach_disp();
#endif