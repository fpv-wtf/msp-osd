#pragma once

#include <stdbool.h>

typedef unsigned char undefined;

typedef unsigned char byte;
typedef unsigned int dword;
typedef long long longlong;
typedef unsigned long long qword;
typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned long long ulonglong;
typedef unsigned char undefined1;
typedef unsigned short undefined2;
typedef unsigned int undefined4;
typedef unsigned long long undefined8;
typedef unsigned short ushort;
typedef unsigned short word;
typedef struct __gs_info __gs_info;

typedef struct __gs_info gs_info_t;

typedef struct duss_event_client duss_event_client;

typedef struct duss_event_client *duss_event_client_handle_t;

typedef struct duss_hal_obj duss_hal_obj;

typedef struct duss_hal_obj *duss_hal_obj_handle_t;

typedef int __int32_t;

typedef __int32_t int32_t;

typedef struct gs_debug_ctrl gs_debug_ctrl;

typedef struct gs_debug_ctrl gs_debug_ctrl_t;

typedef struct duss_osal_task_handle_t duss_osal_task_handle_t;

typedef struct __gs_local_sd_info __gs_local_sd_info;

typedef struct __gs_local_sd_info gs_local_sd_info_t;

typedef struct duss_osal_timer_handle_t duss_osal_timer_handle_t;

typedef struct _DUSS_MSG_RC_BAT_INFO_t _DUSS_MSG_RC_BAT_INFO_t;

typedef struct _DUSS_MSG_RC_BAT_INFO_t DUSS_MSG_RC_BAT_INFO_t;

typedef struct gs_battery_info gs_battery_info;

typedef struct gs_battery_info gs_battery_info_t;

typedef uchar __uint8_t;

typedef __uint8_t uint8_t;

typedef struct gs_modem_ctrl gs_modem_ctrl;

typedef struct gs_modem_ctrl gs_modem_ctrl_t;

typedef struct _DUSS_MSG_RC_MS_LINK_STATUS _DUSS_MSG_RC_MS_LINK_STATUS;

typedef struct _DUSS_MSG_RC_MS_LINK_STATUS DUSS_MSG_RC_MS_LINK_STATUS_t;

typedef struct __gs_use_times_info __gs_use_times_info;

typedef struct __gs_use_times_info gs_use_times_info_t;

typedef struct gs_rc_ctrl gs_rc_ctrl;

typedef struct gs_rc_ctrl gs_rc_ctrl_t;

typedef struct keys_pack_to_racing_glass_t keys_pack_to_racing_glass_t;

typedef struct duss_osal_timer_attrib_t duss_osal_timer_attrib_t;

typedef struct pack_for_factory_test_t pack_for_factory_test_t;

typedef struct gs_buzzer_info gs_buzzer_info;

typedef struct gs_buzzer_info gs_buzzer_info_t;

typedef struct gs_fan_info gs_fan_info;

typedef struct gs_fan_info gs_fan_info_t;

typedef struct __gs_common_cmd_ctrl __gs_common_cmd_ctrl;

typedef struct __gs_common_cmd_ctrl gs_common_cmd_ctrl_t;

typedef struct gs_camera_cmd_ctrl_t gs_camera_cmd_ctrl_t;

typedef struct _DUSS_MSG_CAMERA_STATUS_PUSH_t _DUSS_MSG_CAMERA_STATUS_PUSH_t;

typedef struct _DUSS_MSG_CAMERA_STATUS_PUSH_t DUSS_MSG_CAMERA_STATUS_PUSH_t;

typedef struct gs_video_channel_manager gs_video_channel_manager;

typedef struct gs_video_channel_manager gs_video_channel_manager_t;

typedef struct gs_wl_ctrl gs_wl_ctrl;

typedef struct gs_wl_ctrl gs_wl_ctrl_t;

typedef struct gs_av_in_ctrl gs_av_in_ctrl;

typedef struct gs_av_in_ctrl gs_av_in_ctrl_t;

typedef struct vdec_local_player vdec_local_player;

typedef struct vdec_local_player vdec_local_player_t;

typedef struct metadata_retriever metadata_retriever;

typedef struct metadata_retriever metadata_retriever_t;

typedef struct gs_lv_src gs_lv_src;

typedef struct gs_lv_src gs_lv_src_t;

typedef struct gs_lv_rec_ctrl gs_lv_rec_ctrl;

typedef struct gs_lv_rec_ctrl gs_lv_rec_ctrl_t;

typedef struct gs_usb_gadget_vt gs_usb_gadget_vt;

typedef struct gs_usb_gadget_vt gs_usb_gadget_vt_t;

typedef struct gs_lv_transcode gs_lv_transcode;

typedef struct gs_lv_transcode gs_lv_transcode_t;

typedef struct gs_aout gs_aout;

typedef struct gs_aout gs_aout_t;

typedef struct gs_audio_wl gs_audio_wl;

typedef struct gs_audio_wl gs_audio_wl_t;

typedef struct gs_media_cmd_chnl gs_media_cmd_chnl;

typedef struct gs_media_cmd_chnl gs_media_cmd_chnl_t;

typedef struct gs_bl gs_bl;

typedef struct gs_bl gs_bl_t;

typedef struct timeval timeval;

typedef uint __uint32_t;

typedef __uint32_t uint32_t;

typedef struct __gs_gui __gs_gui;

typedef struct __gs_gui_config __gs_gui_config;

typedef struct debug_osd_info debug_osd_info;

typedef struct debug_osd_info debug_codec_osd_info_t;

typedef struct debug_cam_osd_info debug_cam_osd_info;

typedef struct debug_cam_osd_info debug_cam_osd_info_t;

typedef struct debug_temp_osd_info debug_temp_osd_info;

typedef struct debug_temp_osd_info debug_temp_osd_info_t;

typedef struct debug_cp_osd_info debug_cp_osd_info;

typedef struct debug_cp_osd_info debug_cp_osd_info_t;

typedef ulonglong __uint64_t;

typedef __uint64_t uint64_t;

typedef enum record_mode
{
    RECORD_MODE_MANNUAL = 0,
    RECORD_MODE_LOOPING = 1
} record_mode;

typedef enum record_mode record_mode_t;

typedef enum Record_sender
{
    RECORD_BUTTON = 0,
    RECORD_DISARM = 1
} Record_sender;

typedef ushort __uint16_t;

typedef __uint16_t uint16_t;

typedef struct gs_battery_voltage gs_battery_voltage;

typedef struct gs_battery_voltage gs_battery_voltage_t;

typedef struct __gs_gui_config gs_gui_config_t;

typedef struct gs_gui_event_t gs_gui_event_t;

typedef struct __gs_gui gs_gui_t;

typedef struct gs_ext_fc gs_ext_fc;

typedef struct gs_ext_fc gs_ext_fc_t;

typedef struct gs_shram gs_shram;

typedef struct gs_shram gs_shram_t;

typedef struct __gs_queue __gs_queue;

typedef struct __gs_queue gs_queue_t;

typedef struct gs_user_json_root gs_user_json_root;

typedef struct gs_user_json_root gs_user_json_root_t;

typedef struct duss_osal_mutex_handle_t duss_osal_mutex_handle_t;

typedef struct __gs_avin_test_ctrl __gs_avin_test_ctrl;

typedef struct __gs_avin_test_ctrl gs_avin_test_ctrl_t;

typedef struct gs_watermarker_ctrl gs_watermarker_ctrl;

typedef struct gs_watermarker_ctrl gs_watermarker_ctrl_t;

typedef struct duss_mb_client duss_mb_client;

typedef int32_t duss_result_t;

typedef uint16_t duss_msg_attrib_t;

typedef uint32_t duss_msg_id_t;

typedef struct duss_mb_route_item_t duss_mb_route_item_t;

typedef struct duss_mb_client *duss_mb_client_handle_t;

typedef struct duss_osal_msgq_handle_t duss_osal_msgq_handle_t;

typedef struct duss_osal_event_handle_t duss_osal_event_handle_t;

typedef struct duss_event_ack_identify duss_event_ack_identify;

typedef struct duss_event_ack_identify duss_event_ack_identify_t;

typedef struct duss_event_cmd_desc duss_event_cmd_desc;

typedef struct duss_event duss_event;

typedef struct duss_event duss_event_t;

typedef struct duss_event_cmd_desc duss_event_cmd_desc_t;

typedef struct duss_hal_obj_dev_t duss_hal_obj_dev_t;

typedef struct product_shm_info product_shm_info;

typedef struct product_shm_info product_shm_info_t;

typedef uint size_t;

typedef struct modem_shmem_info_t modem_shmem_info_t;

typedef struct racing_debug_info_t racing_debug_info_t;

typedef struct duss_osal_task_attrib_t duss_osal_task_attrib_t;

typedef long pthread_t;

typedef struct duss_storage_client duss_storage_client;

typedef struct duss_storage_client duss_storage_client_t;

typedef enum sd_file_type
{
    SD_FILE_TYPE_UNKNOWN = 0,
    SD_FILE_TYPE_FAT32 = 1,
    SD_FILE_TYPE_EXFAT = 2,
    SD_FILE_TYPE_MAX = 3
} sd_file_type;

typedef enum sd_file_type sd_file_type_t;

typedef struct gs_storage_listener gs_storage_listener;

typedef enum storage_event
{
    STORAGE_EVENT_NONE = 0,
    STORAGE_EVENT_SPACE_LOW = 1
} storage_event;

typedef enum storage_event storage_event_t;

typedef struct gs_storage_listener gs_storage_listener_t;

typedef struct gs_sd_listener gs_sd_listener;

typedef enum sd_event
{
    SD_EVENT_NONE = 0,
    SD_EVENT_SPACE_LOW = 1,
    SD_EVENT_SD_INSERT = 2,
    SD_EVENT_SD_REMOVE = 3
} sd_event;

typedef enum sd_event sd_event_t;

typedef struct gs_sd_listener gs_sd_listener_t;

typedef struct gs_meta_listener gs_meta_listener;

typedef enum meta_event
{
    META_EVENT_NONE = 0,
    META_EVENT_SD_INSERT = 1,
    META_EVENT_SD_REMOVE = 2,
    META_EVENT_SD_FORMAT = 3
} meta_event;

typedef enum meta_event meta_event_t;

typedef struct gs_meta_listener gs_meta_listener_t;

typedef struct gs_playback_listener gs_playback_listener;

typedef enum playback_event
{
    PB_EVENT_NONE = 0,
    PB_EVENT_SD_INSERT = 1,
    PB_EVENT_SD_REMOVE = 2,
    PB_EVENT_SD_FORMAT = 3
} playback_event;

typedef enum playback_event playback_event_t;

typedef struct gs_playback_listener gs_playback_listener_t;

typedef struct sem_t sem_t;

typedef struct timespec timespec;

typedef struct gs_modem_link_listener gs_modem_link_listener;

typedef struct gs_modem_link_listener gs_modem_link_listener_t;

typedef struct glass_signal_quality_t glass_signal_quality_t;

typedef struct _DUSS_MSG_RACING_CHANNEL_SCAN_REQ_t _DUSS_MSG_RACING_CHANNEL_SCAN_REQ_t;

typedef struct _DUSS_MSG_RACING_CHANNEL_SCAN_REQ_t DUSS_MSG_RACING_CHANNEL_SCAN_REQ_t;

typedef struct _DUSS_MSG_RACING_CHANNEL_SCAN_INFO_t _DUSS_MSG_RACING_CHANNEL_SCAN_INFO_t;

typedef struct _DUSS_MSG_RACING_CHANNEL_SCAN_INFO_t DUSS_MSG_RACING_CHANNEL_SCAN_INFO_t;

typedef struct _DUSS_MSG_RACING_CHANNEL_ROB_INFO_t _DUSS_MSG_RACING_CHANNEL_ROB_INFO_t;

typedef struct _DUSS_MSG_RACING_CHANNEL_ROB_INFO_t DUSS_MSG_RACING_CHANNEL_ROB_INFO_t;

typedef struct _DUSS_MSG_RACING_PHY_CHECK_REQ_t _DUSS_MSG_RACING_PHY_CHECK_REQ_t;

typedef struct _DUSS_MSG_RACING_PHY_CHECK_REQ_t DUSS_MSG_RACING_PHY_CHECK_REQ_t;

typedef struct _DUSS_MSG_RACING_PHY_CHECK_INFO_t _DUSS_MSG_RACING_PHY_CHECK_INFO_t;

typedef struct _DUSS_MSG_RACING_PHY_CHECK_INFO_t DUSS_MSG_RACING_PHY_CHECK_INFO_t;

typedef enum gs_modem_scan_type_t
{
    GS_MODEM_SCAN_ISM = 0,
    GS_MODEM_SCAN_HAM = 1,
    GS_MODEM_SCAN_JAPAN_HAM_5G = 2,
    GS_MODEM_SCAN_HAM_MATCH = 3,
    GS_MODEM_SCAN_HAM_40MHz = 4,
    GS_MODEM_SCAN_HAM_40MHz_EXTRA = 5,
    GS_MODEM_SCAN_UKNOWN = 6
} gs_modem_scan_type_t;

typedef union rc_set_reverse_t rc_set_reverse_t;

typedef struct rc_set_all_st_t rc_set_all_st_t;

typedef struct rc_set_all_ep_t rc_set_all_ep_t;

typedef struct rc_set_all_st_and_rev_t rc_set_all_st_and_rev_t;

typedef struct dummy_ui_ctx_t dummy_ui_ctx_t;

typedef void (*duss_osal_timer_entry_t)(void *);

typedef enum duss_osal_priority_t
{
    DUSS_OSAL_PRI_NORMAL = 0,
    DUSS_OSAL_PRI_LOWEST = 1,
    DUSS_OSAL_PRI_LOW1 = 3,
    DUSS_OSAL_PRI_LOW2 = 6,
    DUSS_OSAL_PRI_LOW3 = 9,
    DUSS_OSAL_PRI_MID1 = 13,
    DUSS_OSAL_PRI_MID2 = 16,
    DUSS_OSAL_PRI_MID3 = 19,
    DUSS_OSAL_PRI_HIGH1 = 23,
    DUSS_OSAL_PRI_HIGH2 = 26,
    DUSS_OSAL_PRI_HIGH3 = 29,
    DUSS_OSAL_PRI_TIM1 = 33,
    DUSS_OSAL_PRI_TIM2 = 36,
    DUSS_OSAL_PRI_TIM3 = 39,
    DUSS_OSAL_PRI_INT = 50,
    DUSS_OSAL_PRI_HIGHEST = 99
} duss_osal_priority_t;

typedef struct factory_check factory_check;

typedef struct anon_struct_conflictc3fb_for_sw anon_struct_conflictc3fb_for_sw;

typedef struct anon_struct_conflictc431_for_key anon_struct_conflictc431_for_key;

typedef struct duss_osal_mutex_attrib_t duss_osal_mutex_attrib_t;

typedef enum gs_fan_level_t
{
    GS_FAN_LEVEL_0 = 0,
    GS_FAN_LEVEL_1 = 1,
    GS_FAN_LEVEL_2 = 2,
    GS_FAN_LEVEL_3 = 3,
    GS_FAN_LEVEL_4 = 4,
    GS_FAN_LEVEL_5 = 5,
    GS_FAN_LEVEL_MAX = 6
} gs_fan_level_t;

typedef struct _DUSS_MSG_SYSTEM_STATE_t _DUSS_MSG_SYSTEM_STATE_t;

typedef struct _DUSS_MSG_SYSTEM_STATE_t DUSS_MSG_SYSTEM_STATE_t;

typedef struct _DUSS_MSG_F_INDEX_MODE_t _DUSS_MSG_F_INDEX_MODE_t;

typedef struct _DUSS_MSG_F_INDEX_MODE_t DUSS_MSG_F_INDEX_MODE_t;

typedef struct _DUSS_MSG_QUICKVIEW_t _DUSS_MSG_QUICKVIEW_t;

typedef struct _DUSS_MSG_QUICKVIEW_t DUSS_MSG_QUICKVIEW_t;

typedef struct _DUSS_MSG_PHOTO_OSD_PARA_ _DUSS_MSG_PHOTO_OSD_PARA_;

typedef struct _DUSS_MSG_PHOTO_OSD_PARA_ DUSS_MSG_PHOTO_OSD_PARA_t;

typedef struct _DUSS_MSG_PREVIEW_OSD_PARA_t _DUSS_MSG_PREVIEW_OSD_PARA_t;

typedef struct _DUSS_MSG_PREVIEW_OSD_PARA_t DUSS_MSG_PREVIEW_OSD_PARA_t;

typedef struct _DUSS_MSG_HISTOGRAM_t _DUSS_MSG_HISTOGRAM_t;

typedef struct _DUSS_MSG_HISTOGRAM_t DUSS_MSG_HISTOGRAM_t;

typedef struct _DUSS_MSG_CAMERA_AUDIO_STATUS_t _DUSS_MSG_CAMERA_AUDIO_STATUS_t;

typedef struct _DUSS_MSG_CAMERA_AUDIO_STATUS_t DUSS_MSG_CAMERA_AUDIO_STATUS_t;

typedef struct _DUSS_MSG_HYPERLAPSE_LIVEVIEW_MARGIN_t _DUSS_MSG_HYPERLAPSE_LIVEVIEW_MARGIN_t;

typedef struct _DUSS_MSG_HYPERLAPSE_LIVEVIEW_MARGIN_t DUSS_MSG_HYPERLAPSE_LIVEVIEW_MARGIN_t;

typedef struct gs_wl_channel gs_wl_channel;

typedef struct gs_wl_channel gs_wl_channel_t;

typedef struct gs_local_playback_channel gs_local_playback_channel;

typedef struct gs_local_playback_channel gs_local_playback_channel_t;

typedef struct gs_av_in_channel gs_av_in_channel;

typedef struct gs_av_in_channel gs_av_in_channel_t;

typedef struct gs_rc_setting_channel gs_rc_setting_channel;

typedef struct gs_rc_setting_channel gs_rc_setting_channel_t;

typedef struct gs_csi_channel gs_csi_channel;

typedef struct gs_csi_channel gs_csi_channel_t;

typedef struct gs_non_video_channel gs_non_video_channel;

typedef struct gs_non_video_channel gs_non_video_channel_t;

typedef struct gs_video_channel gs_video_channel;

typedef struct gs_video_channel_message gs_video_channel_message;

typedef struct gs_video_channel_message gs_video_channel_message_t;

typedef struct gs_video_channel gs_video_channel_t;

typedef struct gs_video_channel_id gs_video_channel_id;

typedef struct gs_video_channel_id gs_video_channel_id_t;

typedef void (*gs_video_channel_switch_callback_t)(void *, gs_video_channel_id_t *);

typedef void (*gs_video_channel_push_callback_t)(void *, gs_video_channel_id_t *);

typedef struct gs_avin_us gs_avin_us;

typedef struct gs_avin_us gs_avin_us_t;

typedef struct AVFormatContext AVFormatContext;

typedef struct audio_dec audio_dec;

typedef enum decoder_event
{
    DEC_EVENT_INVALID = 0,
    DEC_EVENT_A_EOS = 1,
    DEC_EVENT_V_EOS = 2
} decoder_event;

typedef enum decoder_event dec_event_t;

typedef struct audio_dec audio_dec_t;

typedef struct cp_vdec cp_vdec;

typedef struct cp_vdec cp_vdec_t;

typedef struct vdec_video_file_info vdec_video_file_info;

typedef struct vdec_video_file_info vdec_video_file_info_t;

typedef longlong __int64_t;

typedef __int64_t int64_t;

typedef struct sqlite3 sqlite3;

typedef struct gs_lv_csm gs_lv_csm;

typedef struct gs_lv_pkt gs_lv_pkt;

typedef struct gs_lv_pkt gs_lv_pkt_t;

typedef struct gs_lv_csm gs_lv_csm_t;

typedef struct duss_list_head duss_list_head;

typedef struct gs_usb_listener gs_usb_listener;

typedef enum usb_event
{
    USB_EVENT_NONE = 0,
    USB_EVENT_GADGET_CONNECTED = 1
} usb_event;

typedef enum usb_event usb_event_t;

typedef struct gs_usb_listener gs_usb_listener_t;

typedef struct ion_info ion_info;

typedef struct ion_info ion_info_t;

typedef enum record_state
{
    RECORD_STATE_IDLE = 0,
    RECORD_STATE_RECORDING = 1,
    RECORD_STATE_STOP_ERROR = 2,
    RECORD_STATE_STOP_FULL = 3,
    RECORD_STATE_STOP_WRITE_SLOW = 4,
    RECORD_STATE_STARTING = 5,
    RECORD_STATE_STOPPING = 6
} record_state;

typedef enum record_state record_state_t;

typedef struct AVCodecContext AVCodecContext;

typedef struct AVFrame AVFrame;

typedef enum AVPixelFormat
{
    AV_PIX_FMT_NONE = -1,
    PIX_FMT_NONE = -1,
    AV_PIX_FMT_YUV420P = 0,
    PIX_FMT_YUV420P = 0,
    AV_PIX_FMT_YUYV422 = 1,
    PIX_FMT_YUYV422 = 1,
    AV_PIX_FMT_RGB24 = 2,
    PIX_FMT_RGB24 = 2,
    AV_PIX_FMT_BGR24 = 3,
    PIX_FMT_BGR24 = 3,
    AV_PIX_FMT_YUV422P = 4,
    PIX_FMT_YUV422P = 4,
    AV_PIX_FMT_YUV444P = 5,
    PIX_FMT_YUV444P = 5,
    AV_PIX_FMT_YUV410P = 6,
    PIX_FMT_YUV410P = 6,
    AV_PIX_FMT_YUV411P = 7,
    PIX_FMT_YUV411P = 7,
    AV_PIX_FMT_GRAY8 = 8,
    PIX_FMT_GRAY8 = 8,
    AV_PIX_FMT_MONOWHITE = 9,
    PIX_FMT_MONOWHITE = 9,
    AV_PIX_FMT_MONOBLACK = 10,
    PIX_FMT_MONOBLACK = 10,
    AV_PIX_FMT_PAL8 = 11,
    PIX_FMT_PAL8 = 11,
    AV_PIX_FMT_YUVJ420P = 12,
    PIX_FMT_YUVJ420P = 12,
    AV_PIX_FMT_YUVJ422P = 13,
    PIX_FMT_YUVJ422P = 13,
    AV_PIX_FMT_YUVJ444P = 14,
    PIX_FMT_YUVJ444P = 14,
    AV_PIX_FMT_XVMC_MPEG2_MC = 15,
    PIX_FMT_XVMC_MPEG2_MC = 15,
    AV_PIX_FMT_XVMC_MPEG2_IDCT = 16,
    PIX_FMT_XVMC_MPEG2_IDCT = 16,
    AV_PIX_FMT_UYVY422 = 17,
    PIX_FMT_UYVY422 = 17,
    AV_PIX_FMT_UYYVYY411 = 18,
    PIX_FMT_UYYVYY411 = 18,
    AV_PIX_FMT_BGR8 = 19,
    PIX_FMT_BGR8 = 19,
    AV_PIX_FMT_BGR4 = 20,
    PIX_FMT_BGR4 = 20,
    AV_PIX_FMT_BGR4_BYTE = 21,
    PIX_FMT_BGR4_BYTE = 21,
    AV_PIX_FMT_RGB8 = 22,
    PIX_FMT_RGB8 = 22,
    AV_PIX_FMT_RGB4 = 23,
    PIX_FMT_RGB4 = 23,
    AV_PIX_FMT_RGB4_BYTE = 24,
    PIX_FMT_RGB4_BYTE = 24,
    AV_PIX_FMT_NV12 = 25,
    PIX_FMT_NV12 = 25,
    AV_PIX_FMT_NV21 = 26,
    PIX_FMT_NV21 = 26,
    AV_PIX_FMT_ARGB = 27,
    PIX_FMT_ARGB = 27,
    AV_PIX_FMT_RGBA = 28,
    PIX_FMT_RGBA = 28,
    AV_PIX_FMT_ABGR = 29,
    PIX_FMT_ABGR = 29,
    AV_PIX_FMT_BGRA = 30,
    PIX_FMT_BGRA = 30,
    AV_PIX_FMT_GRAY16BE = 31,
    PIX_FMT_GRAY16BE = 31,
    AV_PIX_FMT_GRAY16LE = 32,
    PIX_FMT_GRAY16LE = 32,
    AV_PIX_FMT_YUV440P = 33,
    PIX_FMT_YUV440P = 33,
    AV_PIX_FMT_YUVJ440P = 34,
    PIX_FMT_YUVJ440P = 34,
    AV_PIX_FMT_YUVA420P = 35,
    PIX_FMT_YUVA420P = 35,
    AV_PIX_FMT_VDPAU_H264 = 36,
    PIX_FMT_VDPAU_H264 = 36,
    AV_PIX_FMT_VDPAU_MPEG1 = 37,
    PIX_FMT_VDPAU_MPEG1 = 37,
    AV_PIX_FMT_VDPAU_MPEG2 = 38,
    PIX_FMT_VDPAU_MPEG2 = 38,
    AV_PIX_FMT_VDPAU_WMV3 = 39,
    PIX_FMT_VDPAU_WMV3 = 39,
    AV_PIX_FMT_VDPAU_VC1 = 40,
    PIX_FMT_VDPAU_VC1 = 40,
    AV_PIX_FMT_RGB48BE = 41,
    PIX_FMT_RGB48BE = 41,
    AV_PIX_FMT_RGB48LE = 42,
    PIX_FMT_RGB48LE = 42,
    AV_PIX_FMT_RGB565BE = 43,
    PIX_FMT_RGB565BE = 43,
    AV_PIX_FMT_RGB565LE = 44,
    PIX_FMT_RGB565LE = 44,
    AV_PIX_FMT_RGB555BE = 45,
    PIX_FMT_RGB555BE = 45,
    AV_PIX_FMT_RGB555LE = 46,
    PIX_FMT_RGB555LE = 46,
    AV_PIX_FMT_BGR565BE = 47,
    PIX_FMT_BGR565BE = 47,
    AV_PIX_FMT_BGR565LE = 48,
    PIX_FMT_BGR565LE = 48,
    AV_PIX_FMT_BGR555BE = 49,
    PIX_FMT_BGR555BE = 49,
    AV_PIX_FMT_BGR555LE = 50,
    PIX_FMT_BGR555LE = 50,
    AV_PIX_FMT_VAAPI_MOCO = 51,
    PIX_FMT_VAAPI_MOCO = 51,
    AV_PIX_FMT_VAAPI_IDCT = 52,
    PIX_FMT_VAAPI_IDCT = 52,
    AV_PIX_FMT_VAAPI_VLD = 53,
    PIX_FMT_VAAPI_VLD = 53,
    AV_PIX_FMT_YUV420P16LE = 54,
    PIX_FMT_YUV420P16LE = 54,
    AV_PIX_FMT_YUV420P16BE = 55,
    PIX_FMT_YUV420P16BE = 55,
    AV_PIX_FMT_YUV422P16LE = 56,
    PIX_FMT_YUV422P16LE = 56,
    AV_PIX_FMT_YUV422P16BE = 57,
    PIX_FMT_YUV422P16BE = 57,
    AV_PIX_FMT_YUV444P16LE = 58,
    PIX_FMT_YUV444P16LE = 58,
    AV_PIX_FMT_YUV444P16BE = 59,
    PIX_FMT_YUV444P16BE = 59,
    AV_PIX_FMT_VDPAU_MPEG4 = 60,
    PIX_FMT_VDPAU_MPEG4 = 60,
    AV_PIX_FMT_DXVA2_VLD = 61,
    PIX_FMT_DXVA2_VLD = 61,
    AV_PIX_FMT_RGB444LE = 62,
    PIX_FMT_RGB444LE = 62,
    AV_PIX_FMT_RGB444BE = 63,
    PIX_FMT_RGB444BE = 63,
    AV_PIX_FMT_BGR444LE = 64,
    PIX_FMT_BGR444LE = 64,
    AV_PIX_FMT_BGR444BE = 65,
    PIX_FMT_BGR444BE = 65,
    AV_PIX_FMT_GRAY8A = 66,
    AV_PIX_FMT_Y400A = 66,
    AV_PIX_FMT_YA8 = 66,
    PIX_FMT_GRAY8A = 66,
    AV_PIX_FMT_BGR48BE = 67,
    PIX_FMT_BGR48BE = 67,
    AV_PIX_FMT_BGR48LE = 68,
    PIX_FMT_BGR48LE = 68,
    AV_PIX_FMT_YUV420P9BE = 69,
    PIX_FMT_YUV420P9BE = 69,
    AV_PIX_FMT_YUV420P9LE = 70,
    PIX_FMT_YUV420P9LE = 70,
    AV_PIX_FMT_YUV420P10BE = 71,
    PIX_FMT_YUV420P10BE = 71,
    AV_PIX_FMT_YUV420P10LE = 72,
    PIX_FMT_YUV420P10LE = 72,
    AV_PIX_FMT_YUV422P10BE = 73,
    PIX_FMT_YUV422P10BE = 73,
    AV_PIX_FMT_YUV422P10LE = 74,
    PIX_FMT_YUV422P10LE = 74,
    AV_PIX_FMT_YUV444P9BE = 75,
    PIX_FMT_YUV444P9BE = 75,
    AV_PIX_FMT_YUV444P9LE = 76,
    PIX_FMT_YUV444P9LE = 76,
    AV_PIX_FMT_YUV444P10BE = 77,
    PIX_FMT_YUV444P10BE = 77,
    AV_PIX_FMT_YUV444P10LE = 78,
    PIX_FMT_YUV444P10LE = 78,
    AV_PIX_FMT_YUV422P9BE = 79,
    PIX_FMT_YUV422P9BE = 79,
    AV_PIX_FMT_YUV422P9LE = 80,
    PIX_FMT_YUV422P9LE = 80,
    AV_PIX_FMT_VDA_VLD = 81,
    PIX_FMT_VDA_VLD = 81,
    AV_PIX_FMT_GBRP = 82,
    PIX_FMT_GBRP = 82,
    AV_PIX_FMT_GBRP9BE = 83,
    PIX_FMT_GBRP9BE = 83,
    AV_PIX_FMT_GBRP9LE = 84,
    PIX_FMT_GBRP9LE = 84,
    AV_PIX_FMT_GBRP10BE = 85,
    PIX_FMT_GBRP10BE = 85,
    AV_PIX_FMT_GBRP10LE = 86,
    PIX_FMT_GBRP10LE = 86,
    AV_PIX_FMT_GBRP16BE = 87,
    PIX_FMT_GBRP16BE = 87,
    AV_PIX_FMT_GBRP16LE = 88,
    PIX_FMT_GBRP16LE = 88,
    AV_PIX_FMT_YUVA422P_LIBAV = 89,
    AV_PIX_FMT_YUVA444P_LIBAV = 90,
    AV_PIX_FMT_YUVA420P9BE = 91,
    AV_PIX_FMT_YUVA420P9LE = 92,
    AV_PIX_FMT_YUVA422P9BE = 93,
    AV_PIX_FMT_YUVA422P9LE = 94,
    AV_PIX_FMT_YUVA444P9BE = 95,
    AV_PIX_FMT_YUVA444P9LE = 96,
    AV_PIX_FMT_YUVA420P10BE = 97,
    AV_PIX_FMT_YUVA420P10LE = 98,
    AV_PIX_FMT_YUVA422P10BE = 99,
    AV_PIX_FMT_YUVA422P10LE = 100,
    AV_PIX_FMT_YUVA444P10BE = 101,
    AV_PIX_FMT_YUVA444P10LE = 102,
    AV_PIX_FMT_YUVA420P16BE = 103,
    AV_PIX_FMT_YUVA420P16LE = 104,
    AV_PIX_FMT_YUVA422P16BE = 105,
    AV_PIX_FMT_YUVA422P16LE = 106,
    AV_PIX_FMT_YUVA444P16BE = 107,
    AV_PIX_FMT_YUVA444P16LE = 108,
    AV_PIX_FMT_VDPAU = 109,
    AV_PIX_FMT_XYZ12LE = 110,
    AV_PIX_FMT_XYZ12BE = 111,
    AV_PIX_FMT_NV16 = 112,
    AV_PIX_FMT_NV20LE = 113,
    AV_PIX_FMT_NV20BE = 114,
    AV_PIX_FMT_RGBA64BE_LIBAV = 115,
    AV_PIX_FMT_RGBA64LE_LIBAV = 116,
    AV_PIX_FMT_BGRA64BE_LIBAV = 117,
    AV_PIX_FMT_BGRA64LE_LIBAV = 118,
    AV_PIX_FMT_YVYU422 = 119,
    AV_PIX_FMT_VDA = 120,
    AV_PIX_FMT_YA16BE = 121,
    AV_PIX_FMT_YA16LE = 122,
    AV_PIX_FMT_RGBA64BE = 291,
    PIX_FMT_RGBA64BE = 291,
    AV_PIX_FMT_RGBA64LE = 292,
    PIX_FMT_RGBA64LE = 292,
    AV_PIX_FMT_BGRA64BE = 293,
    PIX_FMT_BGRA64BE = 293,
    AV_PIX_FMT_BGRA64LE = 294,
    PIX_FMT_BGRA64LE = 294,
    AV_PIX_FMT_0RGB = 295,
    PIX_FMT_0RGB = 295,
    AV_PIX_FMT_RGB0 = 296,
    PIX_FMT_RGB0 = 296,
    AV_PIX_FMT_0BGR = 297,
    PIX_FMT_0BGR = 297,
    AV_PIX_FMT_BGR0 = 298,
    PIX_FMT_BGR0 = 298,
    AV_PIX_FMT_YUVA444P = 299,
    PIX_FMT_YUVA444P = 299,
    AV_PIX_FMT_YUVA422P = 300,
    PIX_FMT_YUVA422P = 300,
    AV_PIX_FMT_YUV420P12BE = 301,
    PIX_FMT_YUV420P12BE = 301,
    AV_PIX_FMT_YUV420P12LE = 302,
    PIX_FMT_YUV420P12LE = 302,
    AV_PIX_FMT_YUV420P14BE = 303,
    PIX_FMT_YUV420P14BE = 303,
    AV_PIX_FMT_YUV420P14LE = 304,
    PIX_FMT_YUV420P14LE = 304,
    AV_PIX_FMT_YUV422P12BE = 305,
    PIX_FMT_YUV422P12BE = 305,
    AV_PIX_FMT_YUV422P12LE = 306,
    PIX_FMT_YUV422P12LE = 306,
    AV_PIX_FMT_YUV422P14BE = 307,
    PIX_FMT_YUV422P14BE = 307,
    AV_PIX_FMT_YUV422P14LE = 308,
    PIX_FMT_YUV422P14LE = 308,
    AV_PIX_FMT_YUV444P12BE = 309,
    PIX_FMT_YUV444P12BE = 309,
    AV_PIX_FMT_YUV444P12LE = 310,
    PIX_FMT_YUV444P12LE = 310,
    AV_PIX_FMT_YUV444P14BE = 311,
    PIX_FMT_YUV444P14BE = 311,
    AV_PIX_FMT_YUV444P14LE = 312,
    PIX_FMT_YUV444P14LE = 312,
    AV_PIX_FMT_GBRP12BE = 313,
    PIX_FMT_GBRP12BE = 313,
    AV_PIX_FMT_GBRP12LE = 314,
    PIX_FMT_GBRP12LE = 314,
    AV_PIX_FMT_GBRP14BE = 315,
    PIX_FMT_GBRP14BE = 315,
    AV_PIX_FMT_GBRP14LE = 316,
    PIX_FMT_GBRP14LE = 316,
    AV_PIX_FMT_GBRAP = 317,
    PIX_FMT_NB = 317,
    AV_PIX_FMT_GBRAP16BE = 318,
    AV_PIX_FMT_GBRAP16LE = 319,
    AV_PIX_FMT_YUVJ411P = 320,
    AV_PIX_FMT_BAYER_BGGR8 = 321,
    AV_PIX_FMT_BAYER_RGGB8 = 322,
    AV_PIX_FMT_BAYER_GBRG8 = 323,
    AV_PIX_FMT_BAYER_GRBG8 = 324,
    AV_PIX_FMT_BAYER_BGGR16LE = 325,
    AV_PIX_FMT_BAYER_BGGR16BE = 326,
    AV_PIX_FMT_BAYER_RGGB16LE = 327,
    AV_PIX_FMT_BAYER_RGGB16BE = 328,
    AV_PIX_FMT_BAYER_GBRG16LE = 329,
    AV_PIX_FMT_BAYER_GBRG16BE = 330,
    AV_PIX_FMT_BAYER_GRBG16LE = 331,
    AV_PIX_FMT_BAYER_GRBG16BE = 332,
    AV_PIX_FMT_NB = 333
} AVPixelFormat;

typedef struct pl_muxer_t pl_muxer_t;

typedef struct pl_muxer_t *p1_muxer_handle_t;

typedef struct __sFILE __sFILE;

typedef long __kernel_long_t;

typedef __kernel_long_t __kernel_off_t;

typedef __kernel_off_t off_t;

typedef off_t fpos_t;

typedef struct __sFILE FILE;

typedef struct pcm_config pcm_config;

typedef struct pcm pcm;

typedef __kernel_long_t __kernel_time_t;

typedef __kernel_long_t __kernel_suseconds_t;

typedef struct ext_fc_ops ext_fc_ops;

typedef enum batteryState_e
{
    BATTERY_OK = 0,
    BATTERY_WARNING = 1,
    BATTERY_CRITICAL = 2,
    BATTERY_NOT_PRESENT = 3,
    BATTERY_INIT = 4
} batteryState_e;

typedef struct DUSS_MSG_FC_RACING_DRONE_OSD_PUSH DUSS_MSG_FC_RACING_DRONE_OSD_PUSH;

typedef struct DUSS_MSG_FC_RACING_DRONE_OSD_PUSH DUSS_MSG_FC_RACING_DRONE_OSD_PUSH_t;

typedef struct DUSS_MSG_EXT_FC_RTC DUSS_MSG_EXT_FC_RTC;

typedef struct DUSS_MSG_EXT_FC_RTC DUSS_MSG_EXT_FC_RTC_t;

typedef struct ext_fc_ops ext_fc_ops_t;

typedef struct vr_device_ops vr_device_ops;

typedef short __int16_t;

typedef __int16_t int16_t;

typedef struct vr_device_ops vr_device_ops_t;

typedef struct local_playback_ops local_playback_ops;

typedef struct local_playback_ops local_playback_ops_t;

typedef struct uav_camera_ops uav_camera_ops;

typedef struct __gs_camera_cmd __gs_camera_cmd;

typedef struct __gs_camera_cmd gs_camera_cmd_t;

typedef struct uav_camera_ops uav_camera_ops_t;

typedef struct uav_gimbal_ops uav_gimbal_ops;

typedef struct uav_gimbal_ops uav_gimbal_ops_t;

typedef struct modem_ops modem_ops;

typedef enum gs_link_stat_t
{
    GS_LINK_STAT_NORMAL = 0,
    GS_LINK_STAT_WEAK = 1,
    GS_LINK_STAT_LOST = 2,
    GS_LINK_STAT_UKNOWN = 3
} gs_link_stat_t;

typedef struct modem_ops modem_ops_t;

typedef struct rc_ops rc_ops;

typedef struct rc_set_function_pack_t rc_set_function_pack_t;

typedef struct rc_set_stick_mode_pack_t rc_set_stick_mode_pack_t;

typedef struct rc_set_warning_mode_pack_t rc_set_warning_mode_pack_t;

typedef struct rc_monitor_pack_t rc_monitor_pack_t;

typedef struct rc_ops rc_ops_t;

typedef struct vcm_ops vcm_ops;

typedef enum gs_main_channel_id
{
    GS_FIRST_VIDEO_CHANNEL = 0,
    GS_WL_CHANNEL = 0,
    GS_LOCAL_PLAYBACK_CHANNEL = 1,
    GS_AV_IN_CHANNEL = 2,
    GS_RC_SETTING_CHANNEL = 3,
    GS_CSI_CHANNEL = 4,
    GS_NONE_VIDEO_CHANNEL = 5,
    GS_VIDEO_CHANNEL_COUNT = 6,
    GS_UNKNOWN_VIDEO_CHANNEL = 7
} gs_main_channel_id;

typedef enum gs_main_channel_id gs_main_channel_id_t;

typedef struct vcm_ops vcm_ops_t;

typedef struct common_cmd_ops common_cmd_ops;

typedef struct __gs_common_cmd __gs_common_cmd;

typedef struct __gs_common_cmd gs_common_cmd_t;

typedef struct common_cmd_ops common_cmd_ops_t;

typedef struct debug_osd_item debug_osd_item;

typedef struct debug_osd_item debug_osd_item_t;

typedef uint gs_gui_event_type_t;

typedef uint gs_gui_event_symbol_t;

typedef struct DUSS_MSG_EXT_FC_PID DUSS_MSG_EXT_FC_PID;

typedef struct DUSS_MSG_EXT_FC_PID DUSS_MSG_EXT_FC_PID_t;

typedef struct DUSS_MSG_EXT_FC_AUX DUSS_MSG_EXT_FC_AUX;

typedef struct DUSS_MSG_EXT_FC_AUX DUSS_MSG_EXT_FC_AUX_t;

typedef struct DUSS_MSG_EXT_FC_RATE DUSS_MSG_EXT_FC_RATE;

typedef struct DUSS_MSG_EXT_FC_RATE DUSS_MSG_EXT_FC_RATE_t;

typedef struct DUSS_MSG_EXT_FC_SERVO DUSS_MSG_EXT_FC_SERVO;

typedef struct DUSS_MSG_EXT_FC_SERVO DUSS_MSG_EXT_FC_SERVO_t;

typedef struct DUSS_MSG_EXT_FC_FILTER DUSS_MSG_EXT_FC_FILTER;

typedef struct DUSS_MSG_EXT_FC_FILTER DUSS_MSG_EXT_FC_FILTER_t;

typedef struct DUSS_MSG_EXT_FC_ADVANCED_PID DUSS_MSG_EXT_FC_ADVANCED_PID;

typedef struct DUSS_MSG_EXT_FC_ADVANCED_PID DUSS_MSG_EXT_FC_ADVANCED_PID_t;

typedef struct DUSS_MSG_EXT_FC_MSP_STATUS DUSS_MSG_EXT_FC_MSP_STATUS;

typedef struct DUSS_MSG_EXT_FC_MSP_STATUS DUSS_MSG_EXT_FC_MSP_STATUS_t;

typedef struct DUSS_MSG_EXT_FC_RC DUSS_MSG_EXT_FC_RC;

typedef struct DUSS_MSG_EXT_FC_RC DUSS_MSG_EXT_FC_RC_t;

typedef struct DUSS_MSG_EXT_FC_BATTERY_STATE DUSS_MSG_EXT_FC_BATTERY_STATE;

typedef struct DUSS_MSG_EXT_FC_BATTERY_STATE DUSS_MSG_EXT_FC_BATTERY_STATE_t;

typedef struct DUSS_MSG_EXT_FC_OSD_CONFIG DUSS_MSG_EXT_FC_OSD_CONFIG;

typedef struct DUSS_MSG_EXT_FC_OSD_CONFIG DUSS_MSG_EXT_FC_OSD_CONFIG_t;

typedef struct DUSS_MSG_EXT_FC_ESC_DATA DUSS_MSG_EXT_FC_ESC_DATA;

typedef struct DUSS_MSG_EXT_FC_ESC_DATA DUSS_MSG_EXT_FC_ESC_DATA_t;

typedef struct DUSS_MSG_EXT_FC_VERSION DUSS_MSG_EXT_FC_VERSION;

typedef struct DUSS_MSG_EXT_FC_VERSION DUSS_MSG_EXT_FC_VERSION_t;

typedef enum GS_EXT_FC_OSD_STATUS
{
    OSD_CONFIG_REQUEST_UPDATE = 0,
    OSD_CONFIG_UPDATE_COMPLETE = 1
} GS_EXT_FC_OSD_STATUS;

typedef struct cJSON cJSON;

typedef struct gs_watermarker_us gs_watermarker_us;

typedef struct gs_watermarker_us gs_watermarker_us_t;

typedef uint8_t duss_mb_channel_t;

typedef uint8_t duss_mb_pack_ver_t;

typedef union anon_union_conflict1232_for_channel anon_union_conflict1232_for_channel;

typedef struct duss_mb_filter_t duss_mb_filter_t;

typedef struct duss_mb_route_table_t duss_mb_route_table_t;

typedef struct fd_set fd_set;

typedef struct duss_osal_msgq_attrib_t duss_osal_msgq_attrib_t;

typedef struct duss_osal_event_attrib_t duss_osal_event_attrib_t;

typedef uint8_t duss_hal_state_t;

typedef uint8_t duss_hal_class_t;

typedef void (*duss_osal_task_entry_t)(void *);

typedef struct duss_hal_storage_params duss_hal_storage_params;

typedef struct duss_hal_storage_info duss_hal_storage_info;

typedef struct _DUSS_MSG_RACING_CHANNEL_OCCUPIED_IPSD_t _DUSS_MSG_RACING_CHANNEL_OCCUPIED_IPSD_t;

typedef struct _DUSS_MSG_RACING_CHANNEL_OCCUPIED_IPSD_t DUSS_MSG_RACING_CHANNEL_OCCUPIED_IPSD_t;

typedef struct anon_struct_conflict47e0 anon_struct_conflict47e0;

typedef struct rc_set_subtrim_t rc_set_subtrim_t;

typedef struct rc_set_endpoint_t rc_set_endpoint_t;

typedef struct rc_set_subtrim_reverse_t rc_set_subtrim_reverse_t;

typedef struct _DUSS_MSG_CAM_STATE_t _DUSS_MSG_CAM_STATE_t;

typedef struct _DUSS_MSG_CAM_STATE_t DUSS_MSG_CAM_STATE_t;

typedef union anon_union_conflict23e3_for_u anon_union_conflict23e3_for_u;

typedef union anon_union_conflict2544_for_u anon_union_conflict2544_for_u;

typedef enum gs_video_channel_message_id_t
{
    GS_CHANNEL_MSG_HDMI_PLUG = 0,
    GS_CHANNEL_MSG_CAMERA_WORKMODE = 1,
    GS_CHANNEL_MSG_CAMERA_PBMODE = 2,
    GS_CHANNEL_MSG_CAMERA_MODEL = 3,
    GS_CHANNEL_MSG_WIRELESS_LINK_STATUS = 4,
    GS_CHANNEL_MSG_LOCAL_PLAYBACK_ON = 5,
    GS_CHANNEL_MSG_LOCAL_PLAYBACK_OFF = 6,
    GS_CHANNEL_MSG_CHANNEL_ENABLE = 7,
    GS_CHANNEL_MSG_CHANNEL_DISABLE = 8,
    GS_CHANNEL_MSG_SUB_CHANNEL_ENABLE = 9,
    GS_CHANNEL_MSG_SUB_CHANNEL_DISABLE = 10,
    GS_CHANNEL_MSG_ANALOG_VIDEO_ON = 11,
    GS_CHANNEL_MSG_ANALOG_VIDEO_OFF = 12,
    GS_CHANNEL_MSG_RC_SETTING_ON = 13,
    GS_CHANNEL_MSG_RC_SETTING_OFF = 14,
    GS_CHANNEL_MSG_ID_COUNT = 15
} gs_video_channel_message_id_t;

typedef union anon_union_conflict3b31_for_field_1 anon_union_conflict3b31_for_field_1;

typedef enum gs_sub_channel_id
{
    GS_FIRST_SUB_CHANNEL = 0,
    GS_LIVEVIEW_SUB_CHANNEL = 0,
    GS_PLAYBACK_SUB_CHANNEL = 1,
    GS_RACING_SUB_CHANNEL = 2,
    GS_HDMI_SUB_CHANNEL = 3,
    GS_ANALOG_VIDEO_SUB_CHANNEL = 4,
    GS_RC_SETTING_SUB_CHANNEL = 5,
    GS_SUB_CHANNEL_COUNT = 6,
    GS_NO_SUB_CHANNEL = 7
} gs_sub_channel_id;

typedef enum gs_sub_channel_id gs_sub_channel_id_t;

typedef struct AVClass AVClass;

typedef enum AVClassCategory
{
    AV_CLASS_CATEGORY_NA = 0,
    AV_CLASS_CATEGORY_INPUT = 1,
    AV_CLASS_CATEGORY_OUTPUT = 2,
    AV_CLASS_CATEGORY_MUXER = 3,
    AV_CLASS_CATEGORY_DEMUXER = 4,
    AV_CLASS_CATEGORY_ENCODER = 5,
    AV_CLASS_CATEGORY_DECODER = 6,
    AV_CLASS_CATEGORY_FILTER = 7,
    AV_CLASS_CATEGORY_BITSTREAM_FILTER = 8,
    AV_CLASS_CATEGORY_SWSCALER = 9,
    AV_CLASS_CATEGORY_SWRESAMPLER = 10,
    AV_CLASS_CATEGORY_DEVICE_VIDEO_OUTPUT = 40,
    AV_CLASS_CATEGORY_DEVICE_VIDEO_INPUT = 41,
    AV_CLASS_CATEGORY_DEVICE_AUDIO_OUTPUT = 42,
    AV_CLASS_CATEGORY_DEVICE_AUDIO_INPUT = 43,
    AV_CLASS_CATEGORY_DEVICE_OUTPUT = 44,
    AV_CLASS_CATEGORY_DEVICE_INPUT = 45,
    AV_CLASS_CATEGORY_NB = 46
} AVClassCategory;

typedef struct AVOptionRanges AVOptionRanges;

typedef struct AVInputFormat AVInputFormat;

typedef struct AVProbeData AVProbeData;

typedef struct AVPacket AVPacket;

typedef struct AVDeviceInfoList AVDeviceInfoList;

typedef struct AVDeviceCapabilitiesQuery AVDeviceCapabilitiesQuery;

typedef struct AVOutputFormat AVOutputFormat;

typedef enum AVCodecID
{
    AV_CODEC_ID_NONE = 0,
    CODEC_ID_NONE = 0,
    AV_CODEC_ID_MPEG1VIDEO = 1,
    CODEC_ID_MPEG1VIDEO = 1,
    AV_CODEC_ID_MPEG2VIDEO = 2,
    CODEC_ID_MPEG2VIDEO = 2,
    AV_CODEC_ID_MPEG2VIDEO_XVMC = 3,
    CODEC_ID_MPEG2VIDEO_XVMC = 3,
    AV_CODEC_ID_H261 = 4,
    CODEC_ID_H261 = 4,
    AV_CODEC_ID_H263 = 5,
    CODEC_ID_H263 = 5,
    AV_CODEC_ID_RV10 = 6,
    CODEC_ID_RV10 = 6,
    AV_CODEC_ID_RV20 = 7,
    CODEC_ID_RV20 = 7,
    AV_CODEC_ID_MJPEG = 8,
    CODEC_ID_MJPEG = 8,
    AV_CODEC_ID_MJPEGB = 9,
    CODEC_ID_MJPEGB = 9,
    AV_CODEC_ID_LJPEG = 10,
    CODEC_ID_LJPEG = 10,
    AV_CODEC_ID_SP5X = 11,
    CODEC_ID_SP5X = 11,
    AV_CODEC_ID_JPEGLS = 12,
    CODEC_ID_JPEGLS = 12,
    AV_CODEC_ID_MPEG4 = 13,
    CODEC_ID_MPEG4 = 13,
    AV_CODEC_ID_RAWVIDEO = 14,
    CODEC_ID_RAWVIDEO = 14,
    AV_CODEC_ID_MSMPEG4V1 = 15,
    CODEC_ID_MSMPEG4V1 = 15,
    AV_CODEC_ID_MSMPEG4V2 = 16,
    CODEC_ID_MSMPEG4V2 = 16,
    AV_CODEC_ID_MSMPEG4V3 = 17,
    CODEC_ID_MSMPEG4V3 = 17,
    AV_CODEC_ID_WMV1 = 18,
    CODEC_ID_WMV1 = 18,
    AV_CODEC_ID_WMV2 = 19,
    CODEC_ID_WMV2 = 19,
    AV_CODEC_ID_H263P = 20,
    CODEC_ID_H263P = 20,
    AV_CODEC_ID_H263I = 21,
    CODEC_ID_H263I = 21,
    AV_CODEC_ID_FLV1 = 22,
    CODEC_ID_FLV1 = 22,
    AV_CODEC_ID_SVQ1 = 23,
    CODEC_ID_SVQ1 = 23,
    AV_CODEC_ID_SVQ3 = 24,
    CODEC_ID_SVQ3 = 24,
    AV_CODEC_ID_DVVIDEO = 25,
    CODEC_ID_DVVIDEO = 25,
    AV_CODEC_ID_HUFFYUV = 26,
    CODEC_ID_HUFFYUV = 26,
    AV_CODEC_ID_CYUV = 27,
    CODEC_ID_CYUV = 27,
    AV_CODEC_ID_H264 = 28,
    CODEC_ID_H264 = 28,
    AV_CODEC_ID_INDEO3 = 29,
    CODEC_ID_INDEO3 = 29,
    AV_CODEC_ID_VP3 = 30,
    CODEC_ID_VP3 = 30,
    AV_CODEC_ID_THEORA = 31,
    CODEC_ID_THEORA = 31,
    AV_CODEC_ID_ASV1 = 32,
    CODEC_ID_ASV1 = 32,
    AV_CODEC_ID_ASV2 = 33,
    CODEC_ID_ASV2 = 33,
    AV_CODEC_ID_FFV1 = 34,
    CODEC_ID_FFV1 = 34,
    AV_CODEC_ID_4XM = 35,
    CODEC_ID_4XM = 35,
    AV_CODEC_ID_VCR1 = 36,
    CODEC_ID_VCR1 = 36,
    AV_CODEC_ID_CLJR = 37,
    CODEC_ID_CLJR = 37,
    AV_CODEC_ID_MDEC = 38,
    CODEC_ID_MDEC = 38,
    AV_CODEC_ID_ROQ = 39,
    CODEC_ID_ROQ = 39,
    AV_CODEC_ID_INTERPLAY_VIDEO = 40,
    CODEC_ID_INTERPLAY_VIDEO = 40,
    AV_CODEC_ID_XAN_WC3 = 41,
    CODEC_ID_XAN_WC3 = 41,
    AV_CODEC_ID_XAN_WC4 = 42,
    CODEC_ID_XAN_WC4 = 42,
    AV_CODEC_ID_RPZA = 43,
    CODEC_ID_RPZA = 43,
    AV_CODEC_ID_CINEPAK = 44,
    CODEC_ID_CINEPAK = 44,
    AV_CODEC_ID_WS_VQA = 45,
    CODEC_ID_WS_VQA = 45,
    AV_CODEC_ID_MSRLE = 46,
    CODEC_ID_MSRLE = 46,
    AV_CODEC_ID_MSVIDEO1 = 47,
    CODEC_ID_MSVIDEO1 = 47,
    AV_CODEC_ID_IDCIN = 48,
    CODEC_ID_IDCIN = 48,
    AV_CODEC_ID_8BPS = 49,
    CODEC_ID_8BPS = 49,
    AV_CODEC_ID_SMC = 50,
    CODEC_ID_SMC = 50,
    AV_CODEC_ID_FLIC = 51,
    CODEC_ID_FLIC = 51,
    AV_CODEC_ID_TRUEMOTION1 = 52,
    CODEC_ID_TRUEMOTION1 = 52,
    AV_CODEC_ID_VMDVIDEO = 53,
    CODEC_ID_VMDVIDEO = 53,
    AV_CODEC_ID_MSZH = 54,
    CODEC_ID_MSZH = 54,
    AV_CODEC_ID_ZLIB = 55,
    CODEC_ID_ZLIB = 55,
    AV_CODEC_ID_QTRLE = 56,
    CODEC_ID_QTRLE = 56,
    AV_CODEC_ID_TSCC = 57,
    CODEC_ID_TSCC = 57,
    AV_CODEC_ID_ULTI = 58,
    CODEC_ID_ULTI = 58,
    AV_CODEC_ID_QDRAW = 59,
    CODEC_ID_QDRAW = 59,
    AV_CODEC_ID_VIXL = 60,
    CODEC_ID_VIXL = 60,
    AV_CODEC_ID_QPEG = 61,
    CODEC_ID_QPEG = 61,
    AV_CODEC_ID_PNG = 62,
    CODEC_ID_PNG = 62,
    AV_CODEC_ID_PPM = 63,
    CODEC_ID_PPM = 63,
    AV_CODEC_ID_PBM = 64,
    CODEC_ID_PBM = 64,
    AV_CODEC_ID_PGM = 65,
    CODEC_ID_PGM = 65,
    AV_CODEC_ID_PGMYUV = 66,
    CODEC_ID_PGMYUV = 66,
    AV_CODEC_ID_PAM = 67,
    CODEC_ID_PAM = 67,
    AV_CODEC_ID_FFVHUFF = 68,
    CODEC_ID_FFVHUFF = 68,
    AV_CODEC_ID_RV30 = 69,
    CODEC_ID_RV30 = 69,
    AV_CODEC_ID_RV40 = 70,
    CODEC_ID_RV40 = 70,
    AV_CODEC_ID_VC1 = 71,
    CODEC_ID_VC1 = 71,
    AV_CODEC_ID_WMV3 = 72,
    CODEC_ID_WMV3 = 72,
    AV_CODEC_ID_LOCO = 73,
    CODEC_ID_LOCO = 73,
    AV_CODEC_ID_WNV1 = 74,
    CODEC_ID_WNV1 = 74,
    AV_CODEC_ID_AASC = 75,
    CODEC_ID_AASC = 75,
    AV_CODEC_ID_INDEO2 = 76,
    CODEC_ID_INDEO2 = 76,
    AV_CODEC_ID_FRAPS = 77,
    CODEC_ID_FRAPS = 77,
    AV_CODEC_ID_TRUEMOTION2 = 78,
    CODEC_ID_TRUEMOTION2 = 78,
    AV_CODEC_ID_BMP = 79,
    CODEC_ID_BMP = 79,
    AV_CODEC_ID_CSCD = 80,
    CODEC_ID_CSCD = 80,
    AV_CODEC_ID_MMVIDEO = 81,
    CODEC_ID_MMVIDEO = 81,
    AV_CODEC_ID_ZMBV = 82,
    CODEC_ID_ZMBV = 82,
    AV_CODEC_ID_AVS = 83,
    CODEC_ID_AVS = 83,
    AV_CODEC_ID_SMACKVIDEO = 84,
    CODEC_ID_SMACKVIDEO = 84,
    AV_CODEC_ID_NUV = 85,
    CODEC_ID_NUV = 85,
    AV_CODEC_ID_KMVC = 86,
    CODEC_ID_KMVC = 86,
    AV_CODEC_ID_FLASHSV = 87,
    CODEC_ID_FLASHSV = 87,
    AV_CODEC_ID_CAVS = 88,
    CODEC_ID_CAVS = 88,
    AV_CODEC_ID_JPEG2000 = 89,
    CODEC_ID_JPEG2000 = 89,
    AV_CODEC_ID_VMNC = 90,
    CODEC_ID_VMNC = 90,
    AV_CODEC_ID_VP5 = 91,
    CODEC_ID_VP5 = 91,
    AV_CODEC_ID_VP6 = 92,
    CODEC_ID_VP6 = 92,
    AV_CODEC_ID_VP6F = 93,
    CODEC_ID_VP6F = 93,
    AV_CODEC_ID_TARGA = 94,
    CODEC_ID_TARGA = 94,
    AV_CODEC_ID_DSICINVIDEO = 95,
    CODEC_ID_DSICINVIDEO = 95,
    AV_CODEC_ID_TIERTEXSEQVIDEO = 96,
    CODEC_ID_TIERTEXSEQVIDEO = 96,
    AV_CODEC_ID_TIFF = 97,
    CODEC_ID_TIFF = 97,
    AV_CODEC_ID_GIF = 98,
    CODEC_ID_GIF = 98,
    AV_CODEC_ID_DXA = 99,
    CODEC_ID_DXA = 99,
    AV_CODEC_ID_DNXHD = 100,
    CODEC_ID_DNXHD = 100,
    AV_CODEC_ID_THP = 101,
    CODEC_ID_THP = 101,
    AV_CODEC_ID_SGI = 102,
    CODEC_ID_SGI = 102,
    AV_CODEC_ID_C93 = 103,
    CODEC_ID_C93 = 103,
    AV_CODEC_ID_BETHSOFTVID = 104,
    CODEC_ID_BETHSOFTVID = 104,
    AV_CODEC_ID_PTX = 105,
    CODEC_ID_PTX = 105,
    AV_CODEC_ID_TXD = 106,
    CODEC_ID_TXD = 106,
    AV_CODEC_ID_VP6A = 107,
    CODEC_ID_VP6A = 107,
    AV_CODEC_ID_AMV = 108,
    CODEC_ID_AMV = 108,
    AV_CODEC_ID_VB = 109,
    CODEC_ID_VB = 109,
    AV_CODEC_ID_PCX = 110,
    CODEC_ID_PCX = 110,
    AV_CODEC_ID_SUNRAST = 111,
    CODEC_ID_SUNRAST = 111,
    AV_CODEC_ID_INDEO4 = 112,
    CODEC_ID_INDEO4 = 112,
    AV_CODEC_ID_INDEO5 = 113,
    CODEC_ID_INDEO5 = 113,
    AV_CODEC_ID_MIMIC = 114,
    CODEC_ID_MIMIC = 114,
    AV_CODEC_ID_RL2 = 115,
    CODEC_ID_RL2 = 115,
    AV_CODEC_ID_ESCAPE124 = 116,
    CODEC_ID_ESCAPE124 = 116,
    AV_CODEC_ID_DIRAC = 117,
    CODEC_ID_DIRAC = 117,
    AV_CODEC_ID_BFI = 118,
    CODEC_ID_BFI = 118,
    AV_CODEC_ID_CMV = 119,
    CODEC_ID_CMV = 119,
    AV_CODEC_ID_MOTIONPIXELS = 120,
    CODEC_ID_MOTIONPIXELS = 120,
    AV_CODEC_ID_TGV = 121,
    CODEC_ID_TGV = 121,
    AV_CODEC_ID_TGQ = 122,
    CODEC_ID_TGQ = 122,
    AV_CODEC_ID_TQI = 123,
    CODEC_ID_TQI = 123,
    AV_CODEC_ID_AURA = 124,
    CODEC_ID_AURA = 124,
    AV_CODEC_ID_AURA2 = 125,
    CODEC_ID_AURA2 = 125,
    AV_CODEC_ID_V210X = 126,
    CODEC_ID_V210X = 126,
    AV_CODEC_ID_TMV = 127,
    CODEC_ID_TMV = 127,
    AV_CODEC_ID_V210 = 128,
    CODEC_ID_V210 = 128,
    AV_CODEC_ID_DPX = 129,
    CODEC_ID_DPX = 129,
    AV_CODEC_ID_MAD = 130,
    CODEC_ID_MAD = 130,
    AV_CODEC_ID_FRWU = 131,
    CODEC_ID_FRWU = 131,
    AV_CODEC_ID_FLASHSV2 = 132,
    CODEC_ID_FLASHSV2 = 132,
    AV_CODEC_ID_CDGRAPHICS = 133,
    CODEC_ID_CDGRAPHICS = 133,
    AV_CODEC_ID_R210 = 134,
    CODEC_ID_R210 = 134,
    AV_CODEC_ID_ANM = 135,
    CODEC_ID_ANM = 135,
    AV_CODEC_ID_BINKVIDEO = 136,
    CODEC_ID_BINKVIDEO = 136,
    AV_CODEC_ID_IFF_ILBM = 137,
    CODEC_ID_IFF_ILBM = 137,
    AV_CODEC_ID_IFF_BYTERUN1 = 138,
    CODEC_ID_IFF_BYTERUN1 = 138,
    AV_CODEC_ID_KGV1 = 139,
    CODEC_ID_KGV1 = 139,
    AV_CODEC_ID_YOP = 140,
    CODEC_ID_YOP = 140,
    AV_CODEC_ID_VP8 = 141,
    CODEC_ID_VP8 = 141,
    AV_CODEC_ID_PICTOR = 142,
    CODEC_ID_PICTOR = 142,
    AV_CODEC_ID_ANSI = 143,
    CODEC_ID_ANSI = 143,
    AV_CODEC_ID_A64_MULTI = 144,
    CODEC_ID_A64_MULTI = 144,
    AV_CODEC_ID_A64_MULTI5 = 145,
    CODEC_ID_A64_MULTI5 = 145,
    AV_CODEC_ID_R10K = 146,
    CODEC_ID_R10K = 146,
    AV_CODEC_ID_MXPEG = 147,
    CODEC_ID_MXPEG = 147,
    AV_CODEC_ID_LAGARITH = 148,
    CODEC_ID_LAGARITH = 148,
    AV_CODEC_ID_PRORES = 149,
    CODEC_ID_PRORES = 149,
    AV_CODEC_ID_JV = 150,
    CODEC_ID_JV = 150,
    AV_CODEC_ID_DFA = 151,
    CODEC_ID_DFA = 151,
    AV_CODEC_ID_WMV3IMAGE = 152,
    CODEC_ID_WMV3IMAGE = 152,
    AV_CODEC_ID_VC1IMAGE = 153,
    CODEC_ID_VC1IMAGE = 153,
    AV_CODEC_ID_UTVIDEO = 154,
    CODEC_ID_UTVIDEO = 154,
    AV_CODEC_ID_BMV_VIDEO = 155,
    CODEC_ID_BMV_VIDEO = 155,
    AV_CODEC_ID_VBLE = 156,
    CODEC_ID_VBLE = 156,
    AV_CODEC_ID_DXTORY = 157,
    CODEC_ID_DXTORY = 157,
    AV_CODEC_ID_V410 = 158,
    CODEC_ID_V410 = 158,
    AV_CODEC_ID_XWD = 159,
    CODEC_ID_XWD = 159,
    AV_CODEC_ID_CDXL = 160,
    CODEC_ID_CDXL = 160,
    AV_CODEC_ID_XBM = 161,
    CODEC_ID_XBM = 161,
    AV_CODEC_ID_ZEROCODEC = 162,
    CODEC_ID_ZEROCODEC = 162,
    AV_CODEC_ID_MSS1 = 163,
    CODEC_ID_MSS1 = 163,
    AV_CODEC_ID_MSA1 = 164,
    CODEC_ID_MSA1 = 164,
    AV_CODEC_ID_TSCC2 = 165,
    CODEC_ID_TSCC2 = 165,
    AV_CODEC_ID_MTS2 = 166,
    CODEC_ID_MTS2 = 166,
    AV_CODEC_ID_CLLC = 167,
    CODEC_ID_CLLC = 167,
    AV_CODEC_ID_MSS2 = 168,
    AV_CODEC_ID_VP9 = 169,
    AV_CODEC_ID_AIC = 170,
    AV_CODEC_ID_ESCAPE130_DEPRECATED = 171,
    AV_CODEC_ID_G2M_DEPRECATED = 172,
    AV_CODEC_ID_WEBP_DEPRECATED = 173,
    AV_CODEC_ID_HNM4_VIDEO = 174,
    AV_CODEC_ID_HEVC_DEPRECATED = 175,
    AV_CODEC_ID_FIC = 176,
    AV_CODEC_ID_ALIAS_PIX = 177,
    AV_CODEC_ID_BRENDER_PIX_DEPRECATED = 178,
    AV_CODEC_ID_PAF_VIDEO_DEPRECATED = 179,
    AV_CODEC_ID_EXR_DEPRECATED = 180,
    AV_CODEC_ID_VP7_DEPRECATED = 181,
    AV_CODEC_ID_SANM_DEPRECATED = 182,
    AV_CODEC_ID_SGIRLE_DEPRECATED = 183,
    AV_CODEC_ID_MVC1_DEPRECATED = 184,
    AV_CODEC_ID_MVC2_DEPRECATED = 185,
    AV_CODEC_ID_FIRST_AUDIO = 65536,
    AV_CODEC_ID_PCM_S16LE = 65536,
    CODEC_ID_FIRST_AUDIO = 65536,
    CODEC_ID_PCM_S16LE = 65536,
    AV_CODEC_ID_PCM_S16BE = 65537,
    CODEC_ID_PCM_S16BE = 65537,
    AV_CODEC_ID_PCM_U16LE = 65538,
    CODEC_ID_PCM_U16LE = 65538,
    AV_CODEC_ID_PCM_U16BE = 65539,
    CODEC_ID_PCM_U16BE = 65539,
    AV_CODEC_ID_PCM_S8 = 65540,
    CODEC_ID_PCM_S8 = 65540,
    AV_CODEC_ID_PCM_U8 = 65541,
    CODEC_ID_PCM_U8 = 65541,
    AV_CODEC_ID_PCM_MULAW = 65542,
    CODEC_ID_PCM_MULAW = 65542,
    AV_CODEC_ID_PCM_ALAW = 65543,
    CODEC_ID_PCM_ALAW = 65543,
    AV_CODEC_ID_PCM_S32LE = 65544,
    CODEC_ID_PCM_S32LE = 65544,
    AV_CODEC_ID_PCM_S32BE = 65545,
    CODEC_ID_PCM_S32BE = 65545,
    AV_CODEC_ID_PCM_U32LE = 65546,
    CODEC_ID_PCM_U32LE = 65546,
    AV_CODEC_ID_PCM_U32BE = 65547,
    CODEC_ID_PCM_U32BE = 65547,
    AV_CODEC_ID_PCM_S24LE = 65548,
    CODEC_ID_PCM_S24LE = 65548,
    AV_CODEC_ID_PCM_S24BE = 65549,
    CODEC_ID_PCM_S24BE = 65549,
    AV_CODEC_ID_PCM_U24LE = 65550,
    CODEC_ID_PCM_U24LE = 65550,
    AV_CODEC_ID_PCM_U24BE = 65551,
    CODEC_ID_PCM_U24BE = 65551,
    AV_CODEC_ID_PCM_S24DAUD = 65552,
    CODEC_ID_PCM_S24DAUD = 65552,
    AV_CODEC_ID_PCM_ZORK = 65553,
    CODEC_ID_PCM_ZORK = 65553,
    AV_CODEC_ID_PCM_S16LE_PLANAR = 65554,
    CODEC_ID_PCM_S16LE_PLANAR = 65554,
    AV_CODEC_ID_PCM_DVD = 65555,
    CODEC_ID_PCM_DVD = 65555,
    AV_CODEC_ID_PCM_F32BE = 65556,
    CODEC_ID_PCM_F32BE = 65556,
    AV_CODEC_ID_PCM_F32LE = 65557,
    CODEC_ID_PCM_F32LE = 65557,
    AV_CODEC_ID_PCM_F64BE = 65558,
    CODEC_ID_PCM_F64BE = 65558,
    AV_CODEC_ID_PCM_F64LE = 65559,
    CODEC_ID_PCM_F64LE = 65559,
    AV_CODEC_ID_PCM_BLURAY = 65560,
    CODEC_ID_PCM_BLURAY = 65560,
    AV_CODEC_ID_PCM_LXF = 65561,
    CODEC_ID_PCM_LXF = 65561,
    AV_CODEC_ID_S302M = 65562,
    CODEC_ID_S302M = 65562,
    AV_CODEC_ID_PCM_S8_PLANAR = 65563,
    CODEC_ID_PCM_S8_PLANAR = 65563,
    AV_CODEC_ID_PCM_S24LE_PLANAR_DEPRECATED = 65564,
    AV_CODEC_ID_PCM_S32LE_PLANAR_DEPRECATED = 65565,
    AV_CODEC_ID_ADPCM_IMA_QT = 69632,
    CODEC_ID_ADPCM_IMA_QT = 69632,
    AV_CODEC_ID_ADPCM_IMA_WAV = 69633,
    CODEC_ID_ADPCM_IMA_WAV = 69633,
    AV_CODEC_ID_ADPCM_IMA_DK3 = 69634,
    CODEC_ID_ADPCM_IMA_DK3 = 69634,
    AV_CODEC_ID_ADPCM_IMA_DK4 = 69635,
    CODEC_ID_ADPCM_IMA_DK4 = 69635,
    AV_CODEC_ID_ADPCM_IMA_WS = 69636,
    CODEC_ID_ADPCM_IMA_WS = 69636,
    AV_CODEC_ID_ADPCM_IMA_SMJPEG = 69637,
    CODEC_ID_ADPCM_IMA_SMJPEG = 69637,
    AV_CODEC_ID_ADPCM_MS = 69638,
    CODEC_ID_ADPCM_MS = 69638,
    AV_CODEC_ID_ADPCM_4XM = 69639,
    CODEC_ID_ADPCM_4XM = 69639,
    AV_CODEC_ID_ADPCM_XA = 69640,
    CODEC_ID_ADPCM_XA = 69640,
    AV_CODEC_ID_ADPCM_ADX = 69641,
    CODEC_ID_ADPCM_ADX = 69641,
    AV_CODEC_ID_ADPCM_EA = 69642,
    CODEC_ID_ADPCM_EA = 69642,
    AV_CODEC_ID_ADPCM_G726 = 69643,
    CODEC_ID_ADPCM_G726 = 69643,
    AV_CODEC_ID_ADPCM_CT = 69644,
    CODEC_ID_ADPCM_CT = 69644,
    AV_CODEC_ID_ADPCM_SWF = 69645,
    CODEC_ID_ADPCM_SWF = 69645,
    AV_CODEC_ID_ADPCM_YAMAHA = 69646,
    CODEC_ID_ADPCM_YAMAHA = 69646,
    AV_CODEC_ID_ADPCM_SBPRO_4 = 69647,
    CODEC_ID_ADPCM_SBPRO_4 = 69647,
    AV_CODEC_ID_ADPCM_SBPRO_3 = 69648,
    CODEC_ID_ADPCM_SBPRO_3 = 69648,
    AV_CODEC_ID_ADPCM_SBPRO_2 = 69649,
    CODEC_ID_ADPCM_SBPRO_2 = 69649,
    AV_CODEC_ID_ADPCM_THP = 69650,
    CODEC_ID_ADPCM_THP = 69650,
    AV_CODEC_ID_ADPCM_IMA_AMV = 69651,
    CODEC_ID_ADPCM_IMA_AMV = 69651,
    AV_CODEC_ID_ADPCM_EA_R1 = 69652,
    CODEC_ID_ADPCM_EA_R1 = 69652,
    AV_CODEC_ID_ADPCM_EA_R3 = 69653,
    CODEC_ID_ADPCM_EA_R3 = 69653,
    AV_CODEC_ID_ADPCM_EA_R2 = 69654,
    CODEC_ID_ADPCM_EA_R2 = 69654,
    AV_CODEC_ID_ADPCM_IMA_EA_SEAD = 69655,
    CODEC_ID_ADPCM_IMA_EA_SEAD = 69655,
    AV_CODEC_ID_ADPCM_IMA_EA_EACS = 69656,
    CODEC_ID_ADPCM_IMA_EA_EACS = 69656,
    AV_CODEC_ID_ADPCM_EA_XAS = 69657,
    CODEC_ID_ADPCM_EA_XAS = 69657,
    AV_CODEC_ID_ADPCM_EA_MAXIS_XA = 69658,
    CODEC_ID_ADPCM_EA_MAXIS_XA = 69658,
    AV_CODEC_ID_ADPCM_IMA_ISS = 69659,
    CODEC_ID_ADPCM_IMA_ISS = 69659,
    AV_CODEC_ID_ADPCM_G722 = 69660,
    CODEC_ID_ADPCM_G722 = 69660,
    AV_CODEC_ID_ADPCM_IMA_APC = 69661,
    CODEC_ID_ADPCM_IMA_APC = 69661,
    AV_CODEC_ID_ADPCM_VIMA_DEPRECATED = 69662,
    AV_CODEC_ID_AMR_NB = 73728,
    CODEC_ID_AMR_NB = 73728,
    AV_CODEC_ID_AMR_WB = 73729,
    CODEC_ID_AMR_WB = 73729,
    AV_CODEC_ID_RA_144 = 77824,
    CODEC_ID_RA_144 = 77824,
    AV_CODEC_ID_RA_288 = 77825,
    CODEC_ID_RA_288 = 77825,
    AV_CODEC_ID_ROQ_DPCM = 81920,
    CODEC_ID_ROQ_DPCM = 81920,
    AV_CODEC_ID_INTERPLAY_DPCM = 81921,
    CODEC_ID_INTERPLAY_DPCM = 81921,
    AV_CODEC_ID_XAN_DPCM = 81922,
    CODEC_ID_XAN_DPCM = 81922,
    AV_CODEC_ID_SOL_DPCM = 81923,
    CODEC_ID_SOL_DPCM = 81923,
    AV_CODEC_ID_MP2 = 86016,
    CODEC_ID_MP2 = 86016,
    AV_CODEC_ID_MP3 = 86017,
    CODEC_ID_MP3 = 86017,
    AV_CODEC_ID_AAC = 86018,
    CODEC_ID_AAC = 86018,
    AV_CODEC_ID_AC3 = 86019,
    CODEC_ID_AC3 = 86019,
    AV_CODEC_ID_DTS = 86020,
    CODEC_ID_DTS = 86020,
    AV_CODEC_ID_VORBIS = 86021,
    CODEC_ID_VORBIS = 86021,
    AV_CODEC_ID_DVAUDIO = 86022,
    CODEC_ID_DVAUDIO = 86022,
    AV_CODEC_ID_WMAV1 = 86023,
    CODEC_ID_WMAV1 = 86023,
    AV_CODEC_ID_WMAV2 = 86024,
    CODEC_ID_WMAV2 = 86024,
    AV_CODEC_ID_MACE3 = 86025,
    CODEC_ID_MACE3 = 86025,
    AV_CODEC_ID_MACE6 = 86026,
    CODEC_ID_MACE6 = 86026,
    AV_CODEC_ID_VMDAUDIO = 86027,
    CODEC_ID_VMDAUDIO = 86027,
    AV_CODEC_ID_FLAC = 86028,
    CODEC_ID_FLAC = 86028,
    AV_CODEC_ID_MP3ADU = 86029,
    CODEC_ID_MP3ADU = 86029,
    AV_CODEC_ID_MP3ON4 = 86030,
    CODEC_ID_MP3ON4 = 86030,
    AV_CODEC_ID_SHORTEN = 86031,
    CODEC_ID_SHORTEN = 86031,
    AV_CODEC_ID_ALAC = 86032,
    CODEC_ID_ALAC = 86032,
    AV_CODEC_ID_WESTWOOD_SND1 = 86033,
    CODEC_ID_WESTWOOD_SND1 = 86033,
    AV_CODEC_ID_GSM = 86034,
    CODEC_ID_GSM = 86034,
    AV_CODEC_ID_QDM2 = 86035,
    CODEC_ID_QDM2 = 86035,
    AV_CODEC_ID_COOK = 86036,
    CODEC_ID_COOK = 86036,
    AV_CODEC_ID_TRUESPEECH = 86037,
    CODEC_ID_TRUESPEECH = 86037,
    AV_CODEC_ID_TTA = 86038,
    CODEC_ID_TTA = 86038,
    AV_CODEC_ID_SMACKAUDIO = 86039,
    CODEC_ID_SMACKAUDIO = 86039,
    AV_CODEC_ID_QCELP = 86040,
    CODEC_ID_QCELP = 86040,
    AV_CODEC_ID_WAVPACK = 86041,
    CODEC_ID_WAVPACK = 86041,
    AV_CODEC_ID_DSICINAUDIO = 86042,
    CODEC_ID_DSICINAUDIO = 86042,
    AV_CODEC_ID_IMC = 86043,
    CODEC_ID_IMC = 86043,
    AV_CODEC_ID_MUSEPACK7 = 86044,
    CODEC_ID_MUSEPACK7 = 86044,
    AV_CODEC_ID_MLP = 86045,
    CODEC_ID_MLP = 86045,
    AV_CODEC_ID_GSM_MS = 86046,
    CODEC_ID_GSM_MS = 86046,
    AV_CODEC_ID_ATRAC3 = 86047,
    CODEC_ID_ATRAC3 = 86047,
    AV_CODEC_ID_VOXWARE = 86048,
    CODEC_ID_VOXWARE = 86048,
    AV_CODEC_ID_APE = 86049,
    CODEC_ID_APE = 86049,
    AV_CODEC_ID_NELLYMOSER = 86050,
    CODEC_ID_NELLYMOSER = 86050,
    AV_CODEC_ID_MUSEPACK8 = 86051,
    CODEC_ID_MUSEPACK8 = 86051,
    AV_CODEC_ID_SPEEX = 86052,
    CODEC_ID_SPEEX = 86052,
    AV_CODEC_ID_WMAVOICE = 86053,
    CODEC_ID_WMAVOICE = 86053,
    AV_CODEC_ID_WMAPRO = 86054,
    CODEC_ID_WMAPRO = 86054,
    AV_CODEC_ID_WMALOSSLESS = 86055,
    CODEC_ID_WMALOSSLESS = 86055,
    AV_CODEC_ID_ATRAC3P = 86056,
    CODEC_ID_ATRAC3P = 86056,
    AV_CODEC_ID_EAC3 = 86057,
    CODEC_ID_EAC3 = 86057,
    AV_CODEC_ID_SIPR = 86058,
    CODEC_ID_SIPR = 86058,
    AV_CODEC_ID_MP1 = 86059,
    CODEC_ID_MP1 = 86059,
    AV_CODEC_ID_TWINVQ = 86060,
    CODEC_ID_TWINVQ = 86060,
    AV_CODEC_ID_TRUEHD = 86061,
    CODEC_ID_TRUEHD = 86061,
    AV_CODEC_ID_MP4ALS = 86062,
    CODEC_ID_MP4ALS = 86062,
    AV_CODEC_ID_ATRAC1 = 86063,
    CODEC_ID_ATRAC1 = 86063,
    AV_CODEC_ID_BINKAUDIO_RDFT = 86064,
    CODEC_ID_BINKAUDIO_RDFT = 86064,
    AV_CODEC_ID_BINKAUDIO_DCT = 86065,
    CODEC_ID_BINKAUDIO_DCT = 86065,
    AV_CODEC_ID_AAC_LATM = 86066,
    CODEC_ID_AAC_LATM = 86066,
    AV_CODEC_ID_QDMC = 86067,
    CODEC_ID_QDMC = 86067,
    AV_CODEC_ID_CELT = 86068,
    CODEC_ID_CELT = 86068,
    AV_CODEC_ID_G723_1 = 86069,
    CODEC_ID_G723_1 = 86069,
    AV_CODEC_ID_G729 = 86070,
    CODEC_ID_G729 = 86070,
    AV_CODEC_ID_8SVX_EXP = 86071,
    CODEC_ID_8SVX_EXP = 86071,
    AV_CODEC_ID_8SVX_FIB = 86072,
    CODEC_ID_8SVX_FIB = 86072,
    AV_CODEC_ID_BMV_AUDIO = 86073,
    CODEC_ID_BMV_AUDIO = 86073,
    AV_CODEC_ID_RALF = 86074,
    CODEC_ID_RALF = 86074,
    AV_CODEC_ID_IAC = 86075,
    CODEC_ID_IAC = 86075,
    AV_CODEC_ID_ILBC = 86076,
    CODEC_ID_ILBC = 86076,
    AV_CODEC_ID_OPUS_DEPRECATED = 86077,
    AV_CODEC_ID_COMFORT_NOISE = 86078,
    AV_CODEC_ID_TAK_DEPRECATED = 86079,
    AV_CODEC_ID_METASOUND = 86080,
    AV_CODEC_ID_PAF_AUDIO_DEPRECATED = 86081,
    AV_CODEC_ID_ON2AVC = 86082,
    AV_CODEC_ID_DVD_SUBTITLE = 94208,
    AV_CODEC_ID_FIRST_SUBTITLE = 94208,
    CODEC_ID_DVD_SUBTITLE = 94208,
    CODEC_ID_FIRST_SUBTITLE = 94208,
    AV_CODEC_ID_DVB_SUBTITLE = 94209,
    CODEC_ID_DVB_SUBTITLE = 94209,
    AV_CODEC_ID_TEXT = 94210,
    CODEC_ID_TEXT = 94210,
    AV_CODEC_ID_XSUB = 94211,
    CODEC_ID_XSUB = 94211,
    AV_CODEC_ID_SSA = 94212,
    CODEC_ID_SSA = 94212,
    AV_CODEC_ID_MOV_TEXT = 94213,
    CODEC_ID_MOV_TEXT = 94213,
    AV_CODEC_ID_HDMV_PGS_SUBTITLE = 94214,
    CODEC_ID_HDMV_PGS_SUBTITLE = 94214,
    AV_CODEC_ID_DVB_TELETEXT = 94215,
    CODEC_ID_DVB_TELETEXT = 94215,
    AV_CODEC_ID_SRT = 94216,
    CODEC_ID_SRT = 94216,
    AV_CODEC_ID_FIRST_UNKNOWN = 98304,
    AV_CODEC_ID_TTF = 98304,
    CODEC_ID_FIRST_UNKNOWN = 98304,
    CODEC_ID_TTF = 98304,
    AV_CODEC_ID_PROBE = 102400,
    CODEC_ID_PROBE = 102400,
    AV_CODEC_ID_MPEG2TS = 131072,
    CODEC_ID_MPEG2TS = 131072,
    AV_CODEC_ID_MPEG4SYSTEMS = 131073,
    CODEC_ID_MPEG4SYSTEMS = 131073,
    AV_CODEC_ID_FFMETADATA = 135168,
    CODEC_ID_FFMETADATA = 135168,
    AV_CODEC_ID_G2M = 4665933,
    CODEC_ID_G2M = 4665933,
    AV_CODEC_ID_IDF = 4801606,
    CODEC_ID_IDF = 4801606,
    AV_CODEC_ID_OTF = 5198918,
    CODEC_ID_OTF = 5198918,
    AV_CODEC_ID_PCM_S24LE_PLANAR = 407917392,
    AV_CODEC_ID_PCM_S32LE_PLANAR = 542135120,
    AV_CODEC_ID_012V = 808530518,
    AV_CODEC_ID_EXR = 809850962,
    CODEC_ID_EXR = 809850962,
    AV_CODEC_ID_ADPCM_G726LE = 909260615,
    AV_CODEC_ID_ADPCM_AFC = 1095123744,
    AV_CODEC_ID_APNG = 1095781959,
    AV_CODEC_ID_ASS = 1095979808,
    AV_CODEC_ID_AVRP = 1096176208,
    CODEC_ID_AVRP = 1096176208,
    AV_CODEC_ID_AVRN = 1096176238,
    AV_CODEC_ID_AVUI = 1096176969,
    CODEC_ID_AVUI = 1096176969,
    AV_CODEC_ID_AYUV = 1096373590,
    CODEC_ID_AYUV = 1096373590,
    AV_CODEC_ID_BRENDER_PIX = 1112557912,
    AV_CODEC_ID_BINTEXT = 1112823892,
    CODEC_ID_BINTEXT = 1112823892,
    AV_CODEC_ID_CPIA = 1129335105,
    AV_CODEC_ID_BIN_DATA = 1145132097,
    AV_CODEC_ID_DVD_NAV = 1145979222,
    AV_CODEC_ID_DSD_LSBF_PLANAR = 1146307633,
    AV_CODEC_ID_DSD_MSBF_PLANAR = 1146307640,
    AV_CODEC_ID_DSD_LSBF = 1146307660,
    AV_CODEC_ID_DSD_MSBF = 1146307661,
    AV_CODEC_ID_ADPCM_DTK = 1146374944,
    AV_CODEC_ID_ESCAPE130 = 1160852272,
    CODEC_ID_ESCAPE130 = 1160852272,
    AV_CODEC_ID_FFWAVESYNTH = 1179014995,
    CODEC_ID_FFWAVESYNTH = 1179014995,
    AV_CODEC_ID_HEVC = 1211250229,
    AV_CODEC_ID_JACOSUB = 1246975298,
    CODEC_ID_JACOSUB = 1246975298,
    AV_CODEC_ID_SMPTE_KLV = 1263294017,
    AV_CODEC_ID_MPL2 = 1297108018,
    AV_CODEC_ID_MVC1 = 1297498929,
    AV_CODEC_ID_MVC2 = 1297498930,
    AV_CODEC_ID_ADPCM_IMA_OKI = 1330333984,
    AV_CODEC_ID_OPUS = 1330664787,
    CODEC_ID_OPUS = 1330664787,
    AV_CODEC_ID_PAF_AUDIO = 1346455105,
    CODEC_ID_PAF_AUDIO = 1346455105,
    AV_CODEC_ID_PAF_VIDEO = 1346455126,
    CODEC_ID_PAF_VIDEO = 1346455126,
    AV_CODEC_ID_PCM_S16BE_PLANAR = 1347637264,
    AV_CODEC_ID_PJS = 1349012051,
    AV_CODEC_ID_ADPCM_IMA_RAD = 1380008992,
    AV_CODEC_ID_REALTEXT = 1381259348,
    CODEC_ID_REALTEXT = 1381259348,
    AV_CODEC_ID_SAMI = 1396788553,
    CODEC_ID_SAMI = 1396788553,
    AV_CODEC_ID_SANM = 1396788813,
    CODEC_ID_SANM = 1396788813,
    AV_CODEC_ID_SGIRLE = 1397180754,
    AV_CODEC_ID_SMVJPEG = 1397577290,
    AV_CODEC_ID_SNOW = 1397641047,
    CODEC_ID_SNOW = 1397641047,
    AV_CODEC_ID_SONIC = 1397706307,
    CODEC_ID_SONIC = 1397706307,
    AV_CODEC_ID_SONIC_LS = 1397706316,
    CODEC_ID_SONIC_LS = 1397706316,
    AV_CODEC_ID_SUBRIP = 1397909872,
    AV_CODEC_ID_SUBVIEWER1 = 1398953521,
    AV_CODEC_ID_STL = 1399870540,
    AV_CODEC_ID_SUBVIEWER = 1400201814,
    CODEC_ID_SUBVIEWER = 1400201814,
    AV_CODEC_ID_TARGA_Y216 = 1412575542,
    AV_CODEC_ID_TIMED_ID3 = 1414087731,
    AV_CODEC_ID_V308 = 1446195256,
    CODEC_ID_V308 = 1446195256,
    AV_CODEC_ID_V408 = 1446260792,
    CODEC_ID_V408 = 1446260792,
    AV_CODEC_ID_ADPCM_VIMA = 1447644481,
    AV_CODEC_ID_VIMA = 1447644481,
    CODEC_ID_VIMA = 1447644481,
    AV_CODEC_ID_VP7 = 1448097584,
    AV_CODEC_ID_VPLAYER = 1448111218,
    AV_CODEC_ID_WEBP = 1464156752,
    AV_CODEC_ID_WEBVTT = 1465275476,
    AV_CODEC_ID_XBIN = 1480739150,
    CODEC_ID_XBIN = 1480739150,
    AV_CODEC_ID_XFACE = 1480999235,
    AV_CODEC_ID_Y41P = 1496592720,
    CODEC_ID_Y41P = 1496592720,
    AV_CODEC_ID_YUV4 = 1498764852,
    CODEC_ID_YUV4 = 1498764852,
    AV_CODEC_ID_EIA_608 = 1664495672,
    CODEC_ID_EIA_608 = 1664495672,
    AV_CODEC_ID_MICRODVD = 1833195076,
    CODEC_ID_MICRODVD = 1833195076,
    AV_CODEC_ID_EVRC = 1936029283,
    AV_CODEC_ID_SMV = 1936944502,
    AV_CODEC_ID_TAK = 1950507339
} AVCodecID;

typedef struct AVIOContext AVIOContext;

typedef struct AVStream AVStream;

typedef struct AVProgram AVProgram;

typedef struct AVChapter AVChapter;

typedef struct AVDictionary AVDictionary;

typedef struct AVIOInterruptCB AVIOInterruptCB;

typedef enum AVDurationEstimationMethod
{
    AVFMT_DURATION_FROM_PTS = 0,
    AVFMT_DURATION_FROM_STREAM = 1,
    AVFMT_DURATION_FROM_BITRATE = 2
} AVDurationEstimationMethod;

typedef struct AVPacketList AVPacketList;

typedef struct AVRational AVRational;

typedef struct AVFormatInternal AVFormatInternal;

typedef struct AVCodec AVCodec;

typedef struct AVSubtitle AVSubtitle;

typedef enum AUDIO_PB_STATE
{
    AUDIO_PB_IDLE = 0,
    AUDIO_PB_PREPARING = 1,
    AUDIO_PB_PLAYING = 2,
    AUDIO_PB_PAUSED = 3,
    AUDIO_PB_EOF = 4,
    AUDIO_PB_ERROR = 5,
    AUDIO_PB_CLOSED = 6
} AUDIO_PB_STATE;

typedef enum AUDIO_PB_STATE audio_pb_state_t;

typedef struct pl_decoder_t pl_decoder_t;

typedef struct pl_decoder_t *pl_decoder_handle_t;

typedef struct pl_decoder_itf_t pl_decoder_itf_t;

typedef int (*input_data_cb)(void *, void *, int, int);

typedef int (*output_data_cb)(void *, void *, int, int);

typedef struct audio_resampler_t audio_resampler_t;

typedef struct audio_resampler_t *audio_resampler_ptr;

typedef enum VDEC_STATE
{
    VDEC_IDLE = 0,
    VDEC_PREPARING = 1,
    VDEC_PLAYING = 2,
    VDEC_PAUSED = 3,
    VDEC_EOF = 4,
    VDEC_ERROR = 5,
    VDEC_CLOSED = 6
} VDEC_STATE;

typedef enum VDEC_STATE vdec_state_t;

typedef enum DUSS_FILE_FORMAT
{
    DUSS_FILE_FORMAT_NULL = 0,
    DUSS_FILE_FORMAT_H264RAW = 1,
    DUSS_FILE_FORMAT_H265RAW = 2,
    DUSS_FILE_FORMAT_AACRAW = 3,
    DUSS_FILE_FORMAT_AACADTSRAW = 4,
    DUSS_FILE_FORMAT_MJPGRAW = 5,
    DUSS_FILE_FORMAT_PRORESRAW = 6,
    DUSS_FILE_FORMAT_PRORESRAWRAW = 7,
    DUSS_FILE_FORMAT_USERDATARAW = 8,
    DUSS_FILE_FORMAT_MPEG4RAW = 9,
    DUSS_FILE_FORMAT_RAWMAX = 10,
    DUSS_FILE_FORMAT_MP4 = 11,
    DUSS_FILE_FORMAT_MOV = 12,
    DUSS_FILE_FORMAT_MP2TS = 13,
    DUSS_FILE_FORMAT_MAX = 14,
    DUSS_FILE_FORMAT_NOT_SUPPORTED_YET = 14
} DUSS_FILE_FORMAT;

typedef int (*gs_consumer_prepare_t)(void *);

typedef struct bridge_io_pkt bridge_io_pkt;

typedef struct bridge_io_pkt bridge_io_pkt_t;

typedef int (*gs_consumer_finish_t)(void *);

typedef struct duss_hal_mem_config_t duss_hal_mem_config_t;

typedef struct duss_hal_mem_param_t duss_hal_mem_param_t;

typedef struct duss_hal_mem_buf duss_hal_mem_buf;

typedef struct duss_hal_mem_buf *duss_hal_mem_handle_t;

typedef enum AVMediaType
{
    AVMEDIA_TYPE_UNKNOWN = -1,
    AVMEDIA_TYPE_VIDEO = 0,
    AVMEDIA_TYPE_AUDIO = 1,
    AVMEDIA_TYPE_DATA = 2,
    AVMEDIA_TYPE_SUBTITLE = 3,
    AVMEDIA_TYPE_ATTACHMENT = 4,
    AVMEDIA_TYPE_NB = 5
} AVMediaType;

typedef struct AVCodecInternal AVCodecInternal;

typedef enum AVPictureType
{
    AV_PICTURE_TYPE_NONE = 0,
    AV_PICTURE_TYPE_I = 1,
    AV_PICTURE_TYPE_P = 2,
    AV_PICTURE_TYPE_B = 3,
    AV_PICTURE_TYPE_S = 4,
    AV_PICTURE_TYPE_SI = 5,
    AV_PICTURE_TYPE_SP = 6,
    AV_PICTURE_TYPE_BI = 7
} AVPictureType;

typedef struct AVPanScan AVPanScan;

typedef struct AVBufferRef AVBufferRef;

typedef struct AVFrameSideData AVFrameSideData;

typedef enum AVColorRange
{
    AVCOL_RANGE_UNSPECIFIED = 0,
    AVCOL_RANGE_MPEG = 1,
    AVCOL_RANGE_JPEG = 2,
    AVCOL_RANGE_NB = 3
} AVColorRange;

typedef enum AVColorPrimaries
{
    AVCOL_PRI_RESERVED0 = 0,
    AVCOL_PRI_BT709 = 1,
    AVCOL_PRI_UNSPECIFIED = 2,
    AVCOL_PRI_RESERVED = 3,
    AVCOL_PRI_BT470M = 4,
    AVCOL_PRI_BT470BG = 5,
    AVCOL_PRI_SMPTE170M = 6,
    AVCOL_PRI_SMPTE240M = 7,
    AVCOL_PRI_FILM = 8,
    AVCOL_PRI_BT2020 = 9,
    AVCOL_PRI_NB = 10
} AVColorPrimaries;

typedef enum AVColorTransferCharacteristic
{
    AVCOL_TRC_RESERVED0 = 0,
    AVCOL_TRC_BT709 = 1,
    AVCOL_TRC_UNSPECIFIED = 2,
    AVCOL_TRC_RESERVED = 3,
    AVCOL_TRC_GAMMA22 = 4,
    AVCOL_TRC_GAMMA28 = 5,
    AVCOL_TRC_SMPTE170M = 6,
    AVCOL_TRC_SMPTE240M = 7,
    AVCOL_TRC_LINEAR = 8,
    AVCOL_TRC_LOG = 9,
    AVCOL_TRC_LOG_SQRT = 10,
    AVCOL_TRC_IEC61966_2_4 = 11,
    AVCOL_TRC_BT1361_ECG = 12,
    AVCOL_TRC_IEC61966_2_1 = 13,
    AVCOL_TRC_BT2020_10 = 14,
    AVCOL_TRC_BT2020_12 = 15,
    AVCOL_TRC_NB = 16
} AVColorTransferCharacteristic;

typedef enum AVColorSpace
{
    AVCOL_SPC_RGB = 0,
    AVCOL_SPC_BT709 = 1,
    AVCOL_SPC_UNSPECIFIED = 2,
    AVCOL_SPC_RESERVED = 3,
    AVCOL_SPC_FCC = 4,
    AVCOL_SPC_BT470BG = 5,
    AVCOL_SPC_SMPTE170M = 6,
    AVCOL_SPC_SMPTE240M = 7,
    AVCOL_SPC_YCOCG = 8,
    AVCOL_SPC_BT2020_NCL = 9,
    AVCOL_SPC_BT2020_CL = 10,
    AVCOL_SPC_NB = 11
} AVColorSpace;

typedef enum AVChromaLocation
{
    AVCHROMA_LOC_UNSPECIFIED = 0,
    AVCHROMA_LOC_LEFT = 1,
    AVCHROMA_LOC_CENTER = 2,
    AVCHROMA_LOC_TOPLEFT = 3,
    AVCHROMA_LOC_TOP = 4,
    AVCHROMA_LOC_BOTTOMLEFT = 5,
    AVCHROMA_LOC_BOTTOM = 6,
    AVCHROMA_LOC_NB = 7
} AVChromaLocation;

typedef enum AVFieldOrder
{
    AV_FIELD_UNKNOWN = 0,
    AV_FIELD_PROGRESSIVE = 1,
    AV_FIELD_TT = 2,
    AV_FIELD_BB = 3,
    AV_FIELD_TB = 4,
    AV_FIELD_BT = 5
} AVFieldOrder;

typedef enum AVSampleFormat
{
    AV_SAMPLE_FMT_NONE = -1,
    AV_SAMPLE_FMT_U8 = 0,
    AV_SAMPLE_FMT_S16 = 1,
    AV_SAMPLE_FMT_S32 = 2,
    AV_SAMPLE_FMT_FLT = 3,
    AV_SAMPLE_FMT_DBL = 4,
    AV_SAMPLE_FMT_U8P = 5,
    AV_SAMPLE_FMT_S16P = 6,
    AV_SAMPLE_FMT_S32P = 7,
    AV_SAMPLE_FMT_FLTP = 8,
    AV_SAMPLE_FMT_DBLP = 9,
    AV_SAMPLE_FMT_NB = 10
} AVSampleFormat;

typedef enum AVAudioServiceType
{
    AV_AUDIO_SERVICE_TYPE_MAIN = 0,
    AV_AUDIO_SERVICE_TYPE_EFFECTS = 1,
    AV_AUDIO_SERVICE_TYPE_VISUALLY_IMPAIRED = 2,
    AV_AUDIO_SERVICE_TYPE_HEARING_IMPAIRED = 3,
    AV_AUDIO_SERVICE_TYPE_DIALOGUE = 4,
    AV_AUDIO_SERVICE_TYPE_COMMENTARY = 5,
    AV_AUDIO_SERVICE_TYPE_EMERGENCY = 6,
    AV_AUDIO_SERVICE_TYPE_VOICE_OVER = 7,
    AV_AUDIO_SERVICE_TYPE_KARAOKE = 8,
    AV_AUDIO_SERVICE_TYPE_NB = 9
} AVAudioServiceType;

typedef struct RcOverride RcOverride;

typedef struct AVHWAccel AVHWAccel;

typedef struct MpegEncContext MpegEncContext;

typedef enum AVDiscard
{
    AVDISCARD_NONE = -16,
    AVDISCARD_DEFAULT = 0,
    AVDISCARD_NONREF = 8,
    AVDISCARD_BIDIR = 16,
    AVDISCARD_NONINTRA = 24,
    AVDISCARD_NONKEY = 32,
    AVDISCARD_ALL = 48
} AVDiscard;

typedef struct AVCodecDescriptor AVCodecDescriptor;

typedef struct pl_muxer_itf_t pl_muxer_itf_t;

typedef enum pl_muxer_config_index_t
{
    PL_MUXER_CONFIG_INDEX_NONE = 0,
    PL_MUXER_CONFIG_INDEX_EXTRADATA = 1,
    PL_MUXER_CONFIG_INDEX_FRAGMENTED_MP4 = 2
} pl_muxer_config_index_t;

typedef struct __sbuf __sbuf;

typedef enum pcm_format
{
    PCM_FORMAT_INVALID = -1,
    PCM_FORMAT_S16_LE = 0,
    PCM_FORMAT_S32_LE = 1,
    PCM_FORMAT_S8 = 2,
    PCM_FORMAT_S24_LE = 3,
    PCM_FORMAT_S24_3LE = 4,
    PCM_FORMAT_MAX = 5
} pcm_format;

typedef enum pcm_tstamp
{
    NONE_TSTAMP = 0,
    ALSA_TSTAMP = 1,
    ALSA_TSTAMP_SYNC = 2,
    TSTAMP_TYPE_MAX = 3
} pcm_tstamp;

typedef struct snd_pcm_mmap_status snd_pcm_mmap_status;

typedef struct snd_pcm_mmap_control snd_pcm_mmap_control;

typedef struct snd_pcm_sync_ptr snd_pcm_sync_ptr;

typedef union anon_union_conflict2c9b_for_field_3 anon_union_conflict2c9b_for_field_3;

typedef struct stick_mode_self_define_t stick_mode_self_define_t;

typedef struct loc_channel_addr loc_channel_addr;

typedef struct ip_channel_addr ip_channel_addr;

typedef struct wl_channel_addr wl_channel_addr;

typedef struct uart_channel_addr uart_channel_addr;

typedef struct can_channel_addr can_channel_addr;

typedef struct i2c_channel_addr i2c_channel_addr;

typedef struct spi_channel_addr spi_channel_addr;

typedef struct hpi_channel_addr hpi_channel_addr;

typedef struct usb_channel_addr usb_channel_addr;

typedef struct usbacc_channel_addr usbacc_channel_addr;

typedef struct icc_channel_addr icc_channel_addr;

typedef struct netlink_channel_addr netlink_channel_addr;

typedef struct bulk_channel_addr bulk_channel_addr;

typedef enum duss_storage_client_type_t
{
    DUSS_STORAGE_EMMC0 = 0,
    DUSS_STORAGE_SDCARD0 = 1,
    DUSS_STORAGE_SDCARD1 = 2,
    DUSS_STORAGE_UDISK = 3
} duss_storage_client_type_t;

typedef struct anon_struct_conflict2349 anon_struct_conflict2349;

typedef struct anon_struct_conflict242a anon_struct_conflict242a;

typedef struct gs_local_video_info gs_local_video_info;

typedef struct gs_local_video_info gs_local_video_info_t;

typedef struct gs_local_panorama_info gs_local_panorama_info;

typedef struct gs_local_panorama_info gs_local_panorama_info_t;

typedef struct AVOption AVOption;

typedef struct AVOptionRange AVOptionRange;

typedef struct AVCodecTag AVCodecTag;

typedef struct AVPacketSideData AVPacketSideData;

typedef struct AVFrac AVFrac;

typedef struct anon_struct_conflict69b3c_for_info anon_struct_conflict69b3c_for_info;

typedef enum AVStreamParseType
{
    AVSTREAM_PARSE_NONE = 0,
    AVSTREAM_PARSE_FULL = 1,
    AVSTREAM_PARSE_HEADERS = 2,
    AVSTREAM_PARSE_TIMESTAMPS = 3,
    AVSTREAM_PARSE_FULL_ONCE = 4,
    AVSTREAM_PARSE_FULL_RAW = 1463898624
} AVStreamParseType;

typedef struct AVCodecParserContext AVCodecParserContext;

typedef struct AVIndexEntry AVIndexEntry;

typedef struct AVProfile AVProfile;

typedef struct AVCodecDefault AVCodecDefault;

typedef struct AVSubtitleRect AVSubtitleRect;

typedef struct SwrContext SwrContext;

typedef struct AVBuffer AVBuffer;

typedef enum AVFrameSideDataType
{
    AV_FRAME_DATA_PANSCAN = 0,
    AV_FRAME_DATA_A53_CC = 1,
    AV_FRAME_DATA_STEREO3D = 2,
    AV_FRAME_DATA_MATRIXENCODING = 3,
    AV_FRAME_DATA_DOWNMIX_INFO = 4,
    AV_FRAME_DATA_REPLAYGAIN = 5,
    AV_FRAME_DATA_DISPLAYMATRIX = 6,
    AV_FRAME_DATA_AFD = 7,
    AV_FRAME_DATA_MOTION_VECTORS = 8,
    AV_FRAME_DATA_SKIP_SAMPLES = 9
} AVFrameSideDataType;

typedef struct _DUSS_MSG_APERTURE_t _DUSS_MSG_APERTURE_t;

typedef struct _DUSS_MSG_APERTURE_t DUSS_MSG_APERTURE_t;

typedef struct _DUSS_MSG_SHUTTER_SPEED_t _DUSS_MSG_SHUTTER_SPEED_t;

typedef struct _DUSS_MSG_SHUTTER_SPEED_t DUSS_MSG_SHUTTER_SPEED_t;

typedef struct _DUSS_MSG_ISO_t _DUSS_MSG_ISO_t;

typedef struct _DUSS_MSG_ISO_t DUSS_MSG_ISO_t;

typedef struct _DUSS_MSG_EXPO_MODE_t _DUSS_MSG_EXPO_MODE_t;

typedef struct _DUSS_MSG_EXPO_MODE_t DUSS_MSG_EXPO_MODE_t;

typedef struct _DUSS_MSG_EV_BIAS_t _DUSS_MSG_EV_BIAS_t;

typedef struct _DUSS_MSG_EV_BIAS_t DUSS_MSG_EV_BIAS_t;

typedef struct _DUSS_MSG_P_STORAGE_FMT_t _DUSS_MSG_P_STORAGE_FMT_t;

typedef struct _DUSS_MSG_P_STORAGE_FMT_t DUSS_MSG_P_STORAGE_FMT_t;

typedef struct _DUSS_MSG_WB_t _DUSS_MSG_WB_t;

typedef struct _DUSS_MSG_WB_t DUSS_MSG_WB_t;

typedef struct _DUSS_MSG_SCENE_MODE_t _DUSS_MSG_SCENE_MODE_t;

typedef struct _DUSS_MSG_SCENE_MODE_t DUSS_MSG_SCENE_MODE_t;

typedef struct _DUSS_MSG_DIGITAL_EFFECT_t _DUSS_MSG_DIGITAL_EFFECT_t;

typedef struct _DUSS_MSG_DIGITAL_EFFECT_t DUSS_MSG_DIGITAL_EFFECT_t;

typedef struct _DUSS_MSG_P_SIZE_t _DUSS_MSG_P_SIZE_t;

typedef struct _DUSS_MSG_P_SIZE_t DUSS_MSG_P_SIZE_t;

typedef struct _DUSS_MSG_SET_FOCUS_REGION_t _DUSS_MSG_SET_FOCUS_REGION_t;

typedef struct _DUSS_MSG_SET_FOCUS_REGION_t DUSS_MSG_SET_FOCUS_REGION_t;

typedef struct _DUSS_MSG_CAPTURE_MODE_t _DUSS_MSG_CAPTURE_MODE_t;

typedef struct _DUSS_MSG_CAPTURE_MODE_t DUSS_MSG_CAPTURE_MODE_t;

typedef struct _DUSS_MSG_CONTICAP_PARAM_t _DUSS_MSG_CONTICAP_PARAM_t;

typedef struct _DUSS_MSG_CONTICAP_PARAM_t DUSS_MSG_CONTICAP_PARAM_t;

typedef struct _DUSS_MSG_V_STORAGE_FMT_t _DUSS_MSG_V_STORAGE_FMT_t;

typedef struct _DUSS_MSG_V_STORAGE_FMT_t DUSS_MSG_V_STORAGE_FMT_t;

typedef struct _DUSS_MSG_V_FORMAT_t _DUSS_MSG_V_FORMAT_t;

typedef struct _DUSS_MSG_V_FORMAT_t DUSS_MSG_V_FORMAT_t;

typedef struct _DUSS_MSG_VIDEO_STANDARD_t _DUSS_MSG_VIDEO_STANDARD_t;

typedef struct _DUSS_MSG_VIDEO_STANDARD_t DUSS_MSG_VIDEO_STANDARD_t;

typedef struct _DUSS_MSG_WORKMODE_t _DUSS_MSG_WORKMODE_t;

typedef struct _DUSS_MSG_WORKMODE_t DUSS_MSG_WORKMODE_t;

typedef struct _DUSS_MSG_SINGLE_PLAY_CRTL_t _DUSS_MSG_SINGLE_PLAY_CRTL_t;

typedef struct _DUSS_MSG_SINGLE_PLAY_CRTL_t DUSS_MSG_SINGLE_PLAY_CRTL_t;

typedef struct _DUSS_MSG_V_CRTL_t _DUSS_MSG_V_CRTL_t;

typedef struct _DUSS_MSG_V_CRTL_t DUSS_MSG_V_CRTL_t;

typedef struct _DUSS_MSG_SD_INFO_t _DUSS_MSG_SD_INFO_t;

typedef struct _DUSS_MSG_SD_INFO_t DUSS_MSG_SD_INFO_t;

typedef struct _DUSS_MSG_ZOOM_PARAM_t _DUSS_MSG_ZOOM_PARAM_t;

typedef struct _DUSS_MSG_ZOOM_PARAM_t DUSS_MSG_ZOOM_PARAM_t;

typedef struct _DUSS_MSG_FLIP _DUSS_MSG_FLIP;

typedef struct _DUSS_MSG_FLIP DUSS_MSG_FLIP_t;

typedef struct _DUSS_MSG_SHARPNESS_t _DUSS_MSG_SHARPNESS_t;

typedef struct _DUSS_MSG_SHARPNESS_t DUSS_MSG_SHARPNESS_t;

typedef struct _DUSS_MSG_CONTRAST_t _DUSS_MSG_CONTRAST_t;

typedef struct _DUSS_MSG_CONTRAST_t DUSS_MSG_CONTRAST_t;

typedef struct _DUSS_MSG_SATURATION_t _DUSS_MSG_SATURATION_t;

typedef struct _DUSS_MSG_SATURATION_t DUSS_MSG_SATURATION_t;

typedef struct _DUSS_MSG_CAPTURE_t _DUSS_MSG_CAPTURE_t;

typedef struct _DUSS_MSG_CAPTURE_t DUSS_MSG_CAPTURE_t;

typedef struct _DUSS_MSG_RECORD_t _DUSS_MSG_RECORD_t;

typedef struct _DUSS_MSG_RECORD_t DUSS_MSG_RECORD_t;

typedef struct _UAV_RECORD_MODE_t _UAV_RECORD_MODE_t;

typedef struct _UAV_RECORD_MODE_t UAV_RECORD_MODE_t;

typedef uint8_t duss_wl_prot_type_t;

typedef uint8_t duss_wl_prio_t;

typedef struct duss_hal_uart_config_t duss_hal_uart_config_t;

typedef struct duss_hal_can_config_t duss_hal_can_config_t;

typedef struct duss_hal_i2c_config_t duss_hal_i2c_config_t;

typedef struct duss_hal_spi_config_t duss_hal_spi_config_t;

typedef struct hpi_channel hpi_channel;

typedef struct hpi_channel duss_hal_hpi_config_t;

typedef struct duss_hal_usbacc_config_t duss_hal_usbacc_config_t;

typedef struct duss_hal_icc_config_t duss_hal_icc_config_t;

typedef struct duss_hal_bulk_config_t duss_hal_bulk_config_t;

typedef enum AVOptionType
{
    AV_OPT_TYPE_FLAGS = 0,
    FF_OPT_TYPE_FLAGS = 0,
    AV_OPT_TYPE_INT = 1,
    FF_OPT_TYPE_INT = 1,
    AV_OPT_TYPE_INT64 = 2,
    FF_OPT_TYPE_INT64 = 2,
    AV_OPT_TYPE_DOUBLE = 3,
    FF_OPT_TYPE_DOUBLE = 3,
    AV_OPT_TYPE_FLOAT = 4,
    FF_OPT_TYPE_FLOAT = 4,
    AV_OPT_TYPE_STRING = 5,
    FF_OPT_TYPE_STRING = 5,
    AV_OPT_TYPE_RATIONAL = 6,
    FF_OPT_TYPE_RATIONAL = 6,
    AV_OPT_TYPE_BINARY = 7,
    FF_OPT_TYPE_BINARY = 7,
    AV_OPT_TYPE_DICT = 8,
    AV_OPT_TYPE_CONST = 128,
    FF_OPT_TYPE_CONST = 128,
    AV_OPT_TYPE_CHANNEL_LAYOUT = 1128811585,
    AV_OPT_TYPE_COLOR = 1129270354,
    AV_OPT_TYPE_DURATION = 1146442272,
    AV_OPT_TYPE_PIXEL_FMT = 1346784596,
    AV_OPT_TYPE_SAMPLE_FMT = 1397116244,
    AV_OPT_TYPE_IMAGE_SIZE = 1397316165,
    AV_OPT_TYPE_VIDEO_RATE = 1448231252
} AVOptionType;

typedef union anon_union_conflictac8f4_for_default_val anon_union_conflictac8f4_for_default_val;

typedef enum AVPacketSideDataType
{
    AV_PKT_DATA_PALETTE = 0,
    AV_PKT_DATA_NEW_EXTRADATA = 1,
    AV_PKT_DATA_PARAM_CHANGE = 2,
    AV_PKT_DATA_H263_MB_INFO = 3,
    AV_PKT_DATA_REPLAYGAIN = 4,
    AV_PKT_DATA_DISPLAYMATRIX = 5,
    AV_PKT_DATA_STEREO3D = 6,
    AV_PKT_DATA_SKIP_SAMPLES = 70,
    AV_PKT_DATA_JP_DUALMONO = 71,
    AV_PKT_DATA_STRINGS_METADATA = 72,
    AV_PKT_DATA_SUBTITLE_POSITION = 73,
    AV_PKT_DATA_MATROSKA_BLOCKADDITIONAL = 74,
    AV_PKT_DATA_WEBVTT_IDENTIFIER = 75,
    AV_PKT_DATA_WEBVTT_SETTINGS = 76,
    AV_PKT_DATA_METADATA_UPDATE = 77
} AVPacketSideDataType;

typedef struct AVCodecParser AVCodecParser;

typedef enum AVPictureStructure
{
    AV_PICTURE_STRUCTURE_UNKNOWN = 0,
    AV_PICTURE_STRUCTURE_TOP_FIELD = 1,
    AV_PICTURE_STRUCTURE_BOTTOM_FIELD = 2,
    AV_PICTURE_STRUCTURE_FRAME = 3
} AVPictureStructure;

typedef struct AVPicture AVPicture;

typedef enum AVSubtitleType
{
    SUBTITLE_NONE = 0,
    SUBTITLE_BITMAP = 1,
    SUBTITLE_TEXT = 2,
    SUBTITLE_ASS = 3
} AVSubtitleType;

typedef struct _DUSS_MSG_SHUTTER_A_t _DUSS_MSG_SHUTTER_A_t;

typedef struct _DUSS_MSG_SHUTTER_A_t DUSS_MSG_SHUTTER_A_t;

typedef struct _DUSS_MSG_V_SS_CONFIG_t _DUSS_MSG_V_SS_CONFIG_t;

typedef struct _DUSS_MSG_V_SS_CONFIG_t DUSS_MSG_V_SS_CONFIG_t;

typedef struct _DUSS_MSG_SD_STATUS_t _DUSS_MSG_SD_STATUS_t;

typedef struct _DUSS_MSG_SD_STATUS_t DUSS_MSG_SD_STATUS_t;

typedef struct _DUSS_MSG_ZOOM_CTRL_MODE_t_ _DUSS_MSG_ZOOM_CTRL_MODE_t_;

typedef struct _DUSS_MSG_ZOOM_CTRL_MODE_t_ DUSS_MSG_ZOOM_CTRL_MODE_t;

typedef union anon_union_conflict21a2_for_OZoomRaUnion anon_union_conflict21a2_for_OZoomRaUnion;

typedef uint8_t duss_uart_parity_t;

typedef uint8_t duss_uart_stopbit_t;

typedef uint8_t duss_uart_wordlen_t;

typedef uint8_t duss_mb_can_chip_t;

typedef uint16_t duss_mb_host_id_t;

typedef uint8_t duss_i2c_addr_len_t;

typedef uint __u32;

typedef uchar __u8;

typedef ushort __u16;

typedef uint16_t duss_usbacc_port_t;

typedef enum duss_hal_icc_role_t
{
    DUSS_HAL_ICC_ROLE_SOURCE = 0,
    DUSS_HAL_ICC_ROLE_TARGET = 1,
    DUSS_HAL_ICC_ROLE_MAX = 2
} duss_hal_icc_role_t;

typedef enum duss_hal_icc_shm_type_t
{
    DUSS_HAL_ICC_SHM_SRAM = 0,
    DUSS_HAL_ICC_SHM_DDR = 1,
    DUSS_HAL_ICC_SHM_MAX = 2
} duss_hal_icc_shm_type_t;

typedef struct _DUSS_MSG_ZOOM_S_t _DUSS_MSG_ZOOM_S_t;

typedef struct _DUSS_MSG_ZOOM_S_t DUSS_MSG_ZOOM_S_t;

typedef struct _DUSS_MSG_ZOOM_P_t _DUSS_MSG_ZOOM_P_t;

typedef struct _DUSS_MSG_ZOOM_P_t DUSS_MSG_ZOOM_P_t;

typedef struct _DUSS_MSG_ZOOM_C_t _DUSS_MSG_ZOOM_C_t;

typedef struct _DUSS_MSG_ZOOM_C_t DUSS_MSG_ZOOM_C_t;

struct _DUSS_MSG_RACING_CHANNEL_OCCUPIED_IPSD_t
{
    uint16_t freq_idx;
    uint8_t occupied_ind;
    uint8_t work_ind;
    uint32_t chn_ipsd;
};

struct __gs_avin_test_ctrl
{
    struct duss_osal_task_handle_t *avin_test_task;
    _Bool avin_test_task_quit;
    _Bool avin_test_flag;
    _Bool init;
    undefined field4_0x7;
};

struct gs_lv_csm
{
    char *name;
    _Bool high_prior;
    undefined field2_0x5;
    undefined field3_0x6;
    undefined field4_0x7;
    void *ctx;
    gs_consumer_prepare_t prepare;
    int (*consume)(void *, gs_lv_pkt_t *);
    gs_consumer_finish_t finish;
};

struct gs_usb_gadget_vt
{
    int fdin;
    int fdout;
    gs_usb_listener_t *usb_listener;
    struct duss_osal_task_handle_t *usb_out_task;
    _Bool usb_task_quit;
    _Bool is_wl_chnl_orig;
    _Bool is_wl_chnl_cur;
    undefined field7_0x13;
    gs_lv_src_t *lv_src;
    gs_lv_csm_t lv_csm;
    gs_media_cmd_chnl_t *mcc;
    gs_modem_ctrl_t *modem_ctrl;
    int lv_igr_cnt;
    uint32_t listener_id;
};

struct gs_battery_voltage
{
    int32_t voltage;
    float batt;
    uint8_t series;
    undefined field3_0x9;
    undefined field4_0xa;
    undefined field5_0xb;
    enum batteryState_e state;
};

struct gs_battery_info
{
    uint32_t interval;
    char *addr;
    gs_battery_voltage_t vol;
};

struct gs_meta_listener
{
    void *ctx;
    int (*event_cb)(void *, meta_event_t);
};

struct metadata_retriever
{
    gs_meta_listener_t meta_listener;
    struct duss_osal_mutex_handle_t *db_mutex;
    struct sqlite3 *p_db;
    _Bool b_parse_pending;
    _Bool b_running;
    undefined field5_0x12;
    undefined field6_0x13;
    struct duss_osal_task_handle_t *task_retriever;
};

struct __gs_common_cmd_ctrl
{
    struct duss_osal_task_handle_t *cmn_cmd_task;
    struct duss_osal_msgq_handle_t *cmn_cmd_queue;
    _Bool cmn_cmd_task_quit;
    undefined field3_0x9;
    undefined field4_0xa;
    undefined field5_0xb;
    duss_event_client_handle_t event_client;
    _Bool init;
    undefined field8_0x11;
    undefined field9_0x12;
    undefined field10_0x13;
    void *ctx;
};

struct gs_media_cmd_chnl
{
    int chnl_fd;
    _Bool init;
    undefined field2_0x5;
    undefined field3_0x6;
    undefined field4_0x7;
};

struct keys_pack_to_racing_glass_t
{
    uint8_t right_wheel_press : 2;
    uint8_t right_wheel_scroll : 2;
    uint8_t f1_press : 2;
    uint8_t home : 2;
    uint8_t left_wheel_scroll : 2;
    uint8_t record_press : 2;
    uint8_t reverved_2 : 2;
    uint8_t reverved_3 : 2;
};

struct gs_audio_wl
{
    void *private_data;
};

struct anon_struct_conflictc3fb_for_sw
{
    uint8_t fun_key1 : 1;
    uint8_t fun_key2 : 1;
    uint8_t others : 6;
};

struct anon_struct_conflictc431_for_key
{
    uint8_t up_5d : 1;
    uint8_t down_5d : 1;
    uint8_t left_5d : 1;
    uint8_t right_5d : 1;
    uint8_t ensure_5d : 1;
    uint8_t cancel : 1;
    uint8_t record : 1;
    uint8_t pair : 1;
};

struct factory_check
{
    uint32_t reserved : 31;
    uint32_t result : 1;
};

struct pack_for_factory_test_t
{
    struct factory_check check;
    uint16_t not_use1[6];
    struct anon_struct_conflictc3fb_for_sw sw;
    struct anon_struct_conflictc431_for_key key;
    uint8_t not_use2[26];
};

struct gs_shram
{
    int fd;
    uint8_t *addr;
    int phy_size;
    int map_offset;
    int size;
};

struct gs_watermarker_us
{
    uint8_t watermarker_flag;
    undefined field1_0x1;
    undefined field2_0x2;
    undefined field3_0x3;
    int dev_mem;
    void *uncal_nvram_va;
    void *uncal_nvram_align_va;
    size_t uncal_nvram_map_sz;
};

struct gs_watermarker_ctrl
{
    gs_media_cmd_chnl_t *mcc;
    gs_watermarker_us_t watermarker_us;
};

struct __gs_queue
{
    uchar *addr;
    uint size;
    uint num;
    uint writer;
    uint reader;
};

struct __gs_gui
{
    _Bool gui_en;
    undefined field1_0x1;
    undefined field2_0x2;
    undefined field3_0x3;
    void *context;
    void *dl_hdl;
    gs_queue_t racing_drone_fc_osd_queue;
    int (*initialize)(void **, gs_gui_config_t *);
    void (*destroy)(void *);
    int (*run)(void *);
    int (*send_event)(void *, struct gs_gui_event_t *);
};

struct __gs_local_sd_info
{
    duss_storage_client_t *sdcard_cli;
    _Bool sd_insert;
    undefined field2_0x5;
    undefined field3_0x6;
    undefined field4_0x7;
    sd_file_type_t sd_type;
    uint32_t sd_total_kbytes;
    uint32_t sd_free_kbytes;
    uint32_t sd_minfree_kbytes;
    uint8_t sd_status;
    uint8_t sd_formatting;
    _Bool sd_init;
    undefined field12_0x1b;
    struct duss_osal_mutex_handle_t *sd_status_mutex;
    gs_storage_listener_t *storage_listener;
    gs_sd_listener_t *sd_listener;
    gs_meta_listener_t *meta_listener;
    gs_playback_listener_t *pb_listener;
};

struct rc_set_endpoint_t
{
    uint8_t ep_min;
    uint8_t ep_max;
};

struct rc_set_all_ep_t
{
    struct rc_set_endpoint_t a_ch;
    struct rc_set_endpoint_t e_ch;
    struct rc_set_endpoint_t t_ch;
    struct rc_set_endpoint_t r_ch;
};

struct dummy_ui_ctx_t
{
    _Bool client;
    undefined field1_0x1;
    undefined field2_0x2;
    undefined field3_0x3;
    int sock_fd;
    _Bool quit;
    undefined field6_0x9;
    undefined field7_0xa;
    undefined field8_0xb;
    struct duss_osal_task_handle_t *console_task;
    struct duss_osal_timer_handle_t *console_timer;
    struct duss_osal_event_handle_t *event;
    struct duss_osal_task_handle_t *reader_task;
    int (*msg_cb)(void *, void *);
};

struct rc_set_subtrim_reverse_t
{
    uint16_t reserved : 6;
    uint16_t reverse : 1;
    uint16_t subtrim : 9;
};

struct rc_set_all_st_and_rev_t
{
    struct rc_set_subtrim_reverse_t a_ch;
    struct rc_set_subtrim_reverse_t e_ch;
    struct rc_set_subtrim_reverse_t t_ch;
    struct rc_set_subtrim_reverse_t r_ch;
};

struct rc_set_subtrim_t
{
    int16_t st_value;
};

struct rc_set_all_st_t
{
    struct rc_set_subtrim_t a_ch;
    struct rc_set_subtrim_t e_ch;
    struct rc_set_subtrim_t t_ch;
    struct rc_set_subtrim_t r_ch;
};

struct anon_struct_conflict47e0
{
    uint8_t reserved : 4;
    uint8_t is_reverse_r : 1;
    uint8_t is_reverse_t : 1;
    uint8_t is_reverse_e : 1;
    uint8_t is_reverse_a : 1;
};

union rc_set_reverse_t
{
    struct anon_struct_conflict47e0 rev_bit;
    uint8_t rev_byte;
};

struct gs_rc_ctrl
{
    struct duss_osal_msgq_handle_t *rc_cmd_queue;
    struct duss_osal_task_handle_t *rc_cmd_task;
    _Bool rc_cmd_task_quit;
    _Bool init;
    union rc_set_reverse_t reverse_setting;
    int8_t reverse_valid;
    struct rc_set_all_st_t subtrim_setting;
    int8_t subtrim_valid;
    struct rc_set_all_ep_t endpoint_setting;
    int8_t endpoint_valid;
    uint8_t stick_mode;
    int8_t stick_valid;
    char rc_firm_ver[128];
    char rc_sn[20];
    int rc_mp_state;
    int rc_active_state;
    int8_t version_valid;
    struct rc_set_all_st_and_rev_t subtrim_endpiont_setting;
    uint8_t rc_lock_stat;
    _Bool rc_monitor_quit;
    undefined field20_0xc7;
    struct duss_osal_task_handle_t *rc_monitor;
    duss_event_client_handle_t event_client;
    struct dummy_ui_ctx_t dummy_ui_ctx;
    void *ctx;
};

struct gs_wl_ctrl
{
    gs_media_cmd_chnl_t *mcc;
    _Bool wl_start;
    undefined field2_0x5;
    undefined field3_0x6;
    undefined field4_0x7;
};

struct racing_debug_info_t
{
    uint8_t sdr_log_dump;
    uint8_t vstream_dump;
    uint8_t record;
    uint32_t enc_sto_frm_drop_cnt;
    uint32_t enc_lv_frm_drop_cnt;
    uint32_t csi_frm_drop_cnt;
    uint16_t channel_status;
    uint16_t cam_frame_interval;
    uint16_t outlier_frame_interval;
    uint16_t outlier_frame_interval_cnt;
    uint16_t cam_error;
    uint16_t cam_ae_bv;
    uint16_t cam_ae_dv;
    uint32_t cam_ae_exp_time;
    uint16_t cam_ae_iso;
    uint16_t cam_awb_temp;
    uint16_t cam_atm_value;
    uint16_t cam_scene_mode;
    uint16_t cam_snr;
    uint16_t cam_ae_speed;
    uint16_t cam_ltm_str;
    uint16_t cam_saturation;
    uint16_t cam_saturation_bias;
    uint16_t cam_gamma;
    uint16_t cam_snr_temp;
    uint8_t cam_resolution;
    uint8_t cam_angle;
    uint8_t cam_mode;
    uint8_t cam_ev;
    uint8_t cam_satur;
    uint8_t cam_white_balance;
    int32_t shtl_ddr_temp;
    int32_t shtl_acpu_temp;
    int32_t shtl_modem_temp;
    int32_t shtl_media_temp;
    int32_t shtl_omc_temp;
    uint8_t shtl_cp_report;
    uint8_t shtl_cp_seq;
    char shtl_ap_ver[128];
    char shtl_board_sn[16];
    uint8_t uav_rec_mode;
    uint8_t uav_low_power_mode;
    uint8_t uav_power_policy;
    uint8_t HDVT_pref;
    uint8_t enc_roi;
    uint8_t sbus_mode;
    char shtl_hardware_version[16];
    uint8_t camera_type;
};

struct gs_debug_ctrl
{
    struct __gs_info *gs_info;
    product_shm_info_t *pdt_shm_va;
    void *pdt_shm_align_va;
    size_t pdt_shm_map_sz;
    struct modem_shmem_info_t *plf_shm_va;
    void *plf_shm_align_va;
    size_t plf_shm_map_sz;
    struct racing_debug_info_t rac_dbg_info;
    undefined field8_0x116;
    undefined field9_0x117;
};

struct timeval
{
    __kernel_time_t tv_sec;
    __kernel_suseconds_t tv_usec;
};

struct pcm_config
{
    uint channels;
    uint rate;
    uint period_size;
    uint period_count;
    enum pcm_format format;
    enum pcm_tstamp tstamp_type;
    uint start_threshold;
    uint stop_threshold;
    uint silence_threshold;
    uint silence_size;
    int avail_min;
};

struct gs_aout
{
    struct pcm_config config;
    struct pcm *pcm_device;
    uint32_t buffer_size;
};

struct gs_lv_src
{
    int lv_dmi_fd;
    _Bool force_stop;
    undefined field2_0x5;
    undefined field3_0x6;
    undefined field4_0x7;
    gs_media_cmd_chnl_t *mcc;
    struct duss_osal_task_handle_t *lpc_ctrl_task;
    _Bool lpc_ctrl_task_quit;
    undefined field8_0x11;
    undefined field9_0x12;
    undefined field10_0x13;
    struct duss_osal_msgq_handle_t *lpc_ctrl_queue;
    struct duss_osal_task_handle_t *lpc_data_task;
    _Bool lpc_data_task_quit;
    _Bool lpc_data_eos;
    undefined field15_0x1e;
    undefined field16_0x1f;
    gs_lv_csm_t *csm;
};

struct gs_user_json_root
{
    struct cJSON *user_file_json_root;
    struct cJSON *device_sn_json_root;
};

struct gs_video_channel
{
    int (*start)(struct gs_video_channel *);
    int (*stop)(struct gs_video_channel *);
    _Bool (*handle_message)(struct gs_video_channel *, gs_video_channel_message_t *);
    _Bool (*update_channel)(struct gs_video_channel *);
    struct gs_video_channel_manager *chnl_mgr;
    _Bool ready;
    _Bool enable;
    _Bool lazy_stop;
    _Bool force_switch;
    gs_main_channel_id_t id;
    gs_sub_channel_id_t sub_id;
    char *name;
    _Bool sub_chnl_enable[6];
    undefined field13_0x2a;
    undefined field14_0x2b;
};

struct gs_wl_channel
{
    gs_video_channel_t base;
    _Bool wl_link;
    uint8_t cam_workmode;
    uint8_t cam_pbmode;
    uint8_t cam_model;
};

struct gs_local_playback_channel
{
    gs_video_channel_t base;
    char video_path[256];
    char audio_path[256];
};

struct gs_csi_channel
{
    gs_video_channel_t base;
    _Bool hdmi_plugin;
    undefined field2_0x2d;
    undefined field3_0x2e;
    undefined field4_0x2f;
};

struct gs_rc_setting_channel
{
    gs_video_channel_t base;
};

struct gs_non_video_channel
{
    gs_video_channel_t base;
};

struct gs_video_channel_id
{
    gs_main_channel_id_t main_chnl_id;
    gs_sub_channel_id_t sub_chnl_id;
};

struct gs_av_in_channel
{
    gs_video_channel_t base;
    _Bool av_plugin;
    undefined field2_0x2d;
    undefined field3_0x2e;
    undefined field4_0x2f;
};

struct gs_video_channel_manager
{
    gs_wl_channel_t wl_chnl;
    gs_local_playback_channel_t local_pb_chnl;
    gs_av_in_channel_t av_in_chnl;
    gs_rc_setting_channel_t rc_setting_chnl;
    gs_csi_channel_t csi_chnl;
    gs_non_video_channel_t non_video_chnl;
    gs_video_channel_t *cur_chnl;
    gs_video_channel_t *indexed_chnls[6];
    gs_video_channel_t *prior_ordered_chnls[6];
    gs_video_channel_t *pend_release_chnl;
    gs_video_channel_id_t last_chnl_id;
    struct __gs_info *gs_info;
    gs_video_channel_switch_callback_t chnl_switch_cb;
    void *chnl_switch_data;
    gs_video_channel_push_callback_t chnl_push_cb;
    void *chnl_push_data;
    int8_t ignore_cam_push_cnt;
    uint8_t cam_model;
    uint8_t cam_workmode;
    uint8_t cam_pbmode;
    uint8_t racing_mode;
    undefined field21_0x36d;
    undefined field22_0x36e;
    undefined field23_0x36f;
    uint32_t listener_id;
    struct duss_osal_task_handle_t *chnl_ctrl_task;
    _Bool chnl_ctrl_task_quit;
    undefined field27_0x379;
    undefined field28_0x37a;
    undefined field29_0x37b;
    struct duss_osal_msgq_handle_t *chnl_ctrl_queue;
    struct duss_osal_mutex_handle_t *chnl_ctrl_lock;
};

struct duss_osal_mutex_attrib_t
{
    char *name;
};

struct gs_buzzer_info
{
    struct duss_osal_mutex_handle_t *buzzer_mutex;
    struct duss_osal_mutex_attrib_t buzzer_mutex_attr;
    struct duss_osal_task_handle_t *buzzer_play_sound;
    _Bool buzzer_play_sound_quit;
    undefined field4_0xd;
    undefined field5_0xe;
    undefined field6_0xf;
    int buzzer_enable_fd;
    int buzzer_period_fd;
    int buzzer_duty_fd;
    _Bool buzzer_bat_enable;
    undefined field11_0x1d;
    undefined field12_0x1e;
    undefined field13_0x1f;
};

struct _DUSS_MSG_RC_BAT_INFO_t
{
    uint32_t bat_remain_value;
    uint8_t bat_remain_ratio;
    uint8_t bat_is_charging;
};

struct glass_signal_quality_t
{
    uint8_t direction;
    uint8_t signal_percent;
    uint8_t energy1_uav_or_gnd;
    uint8_t energy2_uav_or_gnd;
};

struct _DUSS_MSG_RACING_PHY_CHECK_REQ_t
{
    uint8_t ant_check;
    uint8_t reserved[2];
};

struct _DUSS_MSG_RACING_PHY_CHECK_INFO_t
{
    uint8_t tx_ant_status;
    uint8_t rx_ant_status;
    uint8_t tx_ant_numbers;
    uint8_t rx_ant_numbers;
    uint8_t reserved;
};

struct _DUSS_MSG_RACING_CHANNEL_SCAN_INFO_t
{
    uint8_t chnl_num;
    uint8_t bw;
    DUSS_MSG_RACING_CHANNEL_OCCUPIED_IPSD_t chn_info[16];
    uint8_t flag;
};

struct _DUSS_MSG_RACING_CHANNEL_SCAN_REQ_t
{
    uint8_t chnl_num;
    uint8_t bw;
    uint16_t freq_idx[16];
};

struct gs_modem_link_listener
{
    void (*link_chg_cb)(void *, _Bool);
    void *cb_ctx;
};

struct _DUSS_MSG_RACING_CHANNEL_ROB_INFO_t
{
    uint8_t left_time;
    uint8_t robber_name[7];
};

struct gs_modem_ctrl
{
    int8_t gls_role;
    uint8_t gls_count;
    uint16_t conf_items[17];
    struct duss_osal_mutex_handle_t *status_mutex_handle;
    _Bool modem_monitor_quit;
    undefined field5_0x29;
    undefined field6_0x2a;
    undefined field7_0x2b;
    struct duss_osal_task_handle_t *modem_monitor;
    uint8_t modem_state;
    uint8_t sdr_role;
    _Bool in_factory_mode;
    _Bool in_aging_test;
    _Bool flag_pairing_finished;
    uint8_t last_modem_state;
    uint8_t rob_flag;
    undefined field16_0x37;
    duss_event_client_handle_t event_client;
    uint32_t seq_id;
    gs_modem_link_listener_t listeners[8];
    struct glass_signal_quality_t signal_quality;
    DUSS_MSG_RACING_CHANNEL_SCAN_REQ_t scan_req;
    DUSS_MSG_RACING_CHANNEL_SCAN_INFO_t scan_info;
    DUSS_MSG_RACING_CHANNEL_ROB_INFO_t rob_info;
    DUSS_MSG_RACING_PHY_CHECK_REQ_t check_req;
    DUSS_MSG_RACING_PHY_CHECK_INFO_t check_info;
    undefined field26_0x139;
    undefined field27_0x13a;
    undefined field28_0x13b;
    enum gs_modem_scan_type_t modem_scan_type;
    uint8_t area_id;
    uint8_t nation_code[2];
    uint8_t area_active_flag;
    int dev_mem;
    void *uncal_nvram_va;
    void *uncal_nvram_align_va;
    size_t uncal_nvram_map_sz;
    struct glass_signal_quality_t rc_signal_quality;
    uint16_t update_bandwidth;
    _Bool power_level_expanded;
    _Bool bw_pending;
};

struct DUSS_MSG_EXT_FC_RTC
{
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;
    uint16_t millis;
};

struct DUSS_MSG_EXT_FC_RATE
{
    uint8_t roll_rates;
    uint8_t roll_expos;
    uint8_t roll_s_rates;
    uint8_t pitch_s_rates;
    uint8_t yaw_s_rates;
    uint8_t dyn_thr;
    uint8_t thr_mid;
    uint8_t thr_expos;
    uint16_t tpa_bp;
    uint8_t yaw_expos;
    uint8_t yaw_rates;
    uint8_t pitch_rates;
    uint8_t pitch_expos;
    uint8_t throttle_limit_type;
    uint8_t throttle_limit_percent;
    uint16_t rate_limit_roll;
    uint16_t rate_limit_pitch;
    uint16_t rate_limit_yaw;
};

struct DUSS_MSG_EXT_FC_FILTER
{
    uint8_t gyro_lpf1;
    uint16_t dterm_lpf1;
    uint16_t yaw_lpf;
    uint16_t gyro_no1;
    uint16_t gyro_no1_cut;
    uint16_t dterm_no1;
    uint16_t dterm_no1_cut;
    uint16_t gyro_no2;
    uint16_t gyro_no2_cut;
    uint8_t dterm_lpf1_type;
    uint8_t gyro_hw_cut;
    uint8_t gyro_hw32_cut;
    uint16_t gyro_lpf1_alt;
    uint16_t gyro_lpf2;
    uint8_t gyro_lpf1_type;
    uint8_t gyro_lpf2_type;
    uint16_t dterm_lpf2;
    uint8_t dterm_ft2_type;
    uint16_t dyn_lpf_gyro_min_hz;
    uint16_t dyn_lpf_gyro_max_hz;
    uint16_t dyn_lpf_dterm_min_hz;
    uint16_t dyn_lpf_dterm_max_hz;
    uint8_t dyn_notch_range;
    uint8_t dyn_notch_width_percent;
    uint16_t dyn_notch_q;
    uint16_t dyn_notch_min_hz;
    uint8_t gyro_rpm_notch_harmonics;
    uint8_t gyro_rpm_notch_min;
};

struct DUSS_MSG_EXT_FC_AUX
{
    uint8_t aux_id;
    uint8_t aux_index;
    uint8_t start_step;
    uint8_t end_step;
};

struct DUSS_MSG_EXT_FC_BATTERY_STATE
{
    uint8_t cell;
    uint16_t capacity;
    uint8_t voltage;
    uint16_t MAhDrawn;
    uint16_t amperage;
    uint8_t state;
    uint16_t battVoltage;
};

struct DUSS_MSG_EXT_FC_RC
{
    uint16_t chnl_1_v;
    uint16_t chnl_2_v;
    uint16_t chnl_3_v;
    uint16_t chnl_4_v;
    uint16_t chnl_5_v;
    uint16_t chnl_6_v;
    uint16_t chnl_7_v;
    uint16_t chnl_8_v;
    uint16_t chnl_9_v;
    uint16_t chnl_10_v;
    uint16_t chnl_11_v;
    uint16_t chnl_12_v;
    uint16_t chnl_13_v;
    uint16_t chnl_14_v;
    uint16_t chnl_15_v;
    uint16_t chnl_16_v;
    uint16_t chnl_17_v;
    uint16_t chnl_18_v;
};

struct DUSS_MSG_EXT_FC_MSP_STATUS
{
    uint16_t task_delta_time;
    uint16_t i2c_error_counter;
    uint16_t sensor_status;
    uint32_t flight_flags_lsb;
    uint8_t pid_index;
    uint16_t sysAvgLoad;
    uint8_t pid_count;
    uint8_t rate_index;
    uint8_t flight_count;
    uint8_t arming_count;
    uint32_t arming_flags;
    uint8_t flight_flags_msb;
};

struct DUSS_MSG_EXT_FC_ESC_DATA
{
    uint8_t temperature;
    uint16_t rpm;
};

struct DUSS_MSG_EXT_FC_OSD_CONFIG
{
    uint8_t osdFlags;
    uint8_t videoSystems;
    uint8_t units;
    uint8_t rssi_alarm;
    uint16_t cap_alarm;
    uint8_t reserved;
    uint8_t item_count;
    uint16_t alt_alarm;
    uint16_t item_position[100];
    uint8_t stat_count;
    uint8_t stat_state[100];
    uint8_t timer_count;
    uint16_t timer[10];
    uint16_t enablewarnings;
    uint8_t warning_count;
    uint32_t warnings;
    uint8_t profile_count;
    uint8_t profile_index;
    uint8_t stick_overlay;
};

struct DUSS_MSG_EXT_FC_SERVO
{
    uint16_t min;
    uint16_t max;
    uint16_t middle;
    uint8_t rate;
    uint8_t ffchnl;
    uint32_t reverse;
};

struct DUSS_MSG_EXT_FC_VERSION
{
    uint8_t major;
    uint8_t minor;
    uint8_t patch_level;
};

struct DUSS_MSG_EXT_FC_ADVANCED_PID
{
    uint16_t reserved1;
    uint16_t reserved2;
    uint16_t reserved3;
    uint8_t reserved4;
    uint8_t vbat_comp;
    uint8_t feedForwardTrans;
    uint8_t reserved5;
    uint8_t reserved6;
    uint8_t reserved7;
    uint8_t reserved8;
    uint16_t rateAcelLimit;
    uint16_t yawrateAcelLimit;
    uint8_t levelAngleLimit;
    uint8_t reserved9;
    uint16_t ThrottleThreshold;
    uint16_t AcceleratorGain;
    uint16_t reserved10;
    uint8_t rotation;
    uint8_t smartFF;
    uint8_t relax;
    uint8_t relax_type;
    uint8_t abs_control_gain;
    uint8_t throttle_boost;
    uint8_t acro_trainer_angle_limit;
    uint16_t RollFF;
    uint16_t PitchFF;
    uint16_t YawFF;
    uint8_t ag_mode;
    uint8_t d_min_roll;
    uint8_t d_min_pitch;
    uint8_t d_min_yaw;
    uint8_t d_min_gain;
    uint8_t d_min_advance;
    uint8_t use_integrated_yaw;
    uint8_t integrated_yaw_relax;
    uint8_t iterm_relax_cutoff;
};

struct DUSS_MSG_FC_RACING_DRONE_OSD_PUSH
{
    uint8_t GPS_3D_fix;
    uint8_t GPS_numSat;
    int32_t Lattitude;
    int32_t Longtitude;
    uint16_t GPS_altitude;
    uint16_t GPS_speed;
    uint16_t GPS_distance_home;
    int16_t GPS_direction_home;
    int16_t angx;
    int16_t angy;
    int16_t heading;
    int32_t estAlt;
    int16_t vario;
    uint8_t vbat;
    uint16_t intPowerMeterSum;
    uint16_t rssi;
    uint16_t amperage;
};

struct DUSS_MSG_EXT_FC_PID
{
    uint8_t roll_p;
    uint8_t roll_i;
    uint8_t roll_d;
    uint8_t pitch_p;
    uint8_t pitch_i;
    uint8_t pitch_d;
    uint8_t yaw_p;
    uint8_t yaw_i;
    uint8_t yaw_d;
    uint8_t angle_str;
    uint8_t horizon_str;
    uint8_t horizon_trans;
    uint8_t mag_p;
    uint8_t mag_i;
    uint8_t mag_d;
};

struct gs_ext_fc
{
    uint8_t requestType;
    DUSS_MSG_EXT_FC_PID_t pid;
    DUSS_MSG_EXT_FC_AUX_t aux[20];
    DUSS_MSG_EXT_FC_RATE_t rate;
    DUSS_MSG_EXT_FC_SERVO_t servo[8];
    DUSS_MSG_EXT_FC_FILTER_t filter;
    DUSS_MSG_EXT_FC_ADVANCED_PID_t pid_adv;
    DUSS_MSG_EXT_FC_MSP_STATUS_t msp_status;
    DUSS_MSG_EXT_FC_RC_t rc;
    DUSS_MSG_EXT_FC_BATTERY_STATE_t batt;
    DUSS_MSG_EXT_FC_OSD_CONFIG_t osd_config;
    DUSS_MSG_EXT_FC_ESC_DATA_t esc_data[4];
    DUSS_MSG_EXT_FC_RTC_t fc_rtc;
    char name[17];
    DUSS_MSG_EXT_FC_VERSION_t fc_version;
    DUSS_MSG_FC_RACING_DRONE_OSD_PUSH_t osd_info;
    undefined field16_0x31b;
    enum GS_EXT_FC_OSD_STATUS osd_status;
    struct duss_osal_task_handle_t *get_osd_config;
    _Bool get_osd_quit;
    undefined field20_0x325;
    undefined field21_0x326;
    undefined field22_0x327;
};

struct _DUSS_MSG_HISTOGRAM_t
{
    uint8_t Op : 1;
    uint8_t Reserved : 7;
};

struct anon_struct_conflict2349
{
    uint16_t DataDisp : 1;
    uint16_t PertureDisp : 1;
    uint16_t ShutterSpeedDisp : 1;
    uint16_t ISODisp : 1;
    uint16_t EvBiasDisp : 1;
    uint16_t SharpnessDisp : 1;
    uint16_t ContrastDisp : 1;
    uint16_t SaturationDisp : 1;
    uint16_t Res : 8;
};

union anon_union_conflict23e3_for_u
{
    struct anon_struct_conflict2349 bits;
    uint16_t Value;
};

struct _DUSS_MSG_PHOTO_OSD_PARA_
{
    union anon_union_conflict23e3_for_u u;
};

struct anon_struct_conflict242a
{
    uint32_t DataDisp : 1;
    uint32_t PertureDisp : 1;
    uint32_t ShutterSpeedDisp : 1;
    uint32_t ISODisp : 1;
    uint32_t AeModeDisp : 1;
    uint32_t FlashLightDisp : 1;
    uint32_t WbDisp : 1;
    uint32_t EvBiasDisp : 1;
    uint32_t SharpnessDisp : 1;
    uint32_t ContrastDisp : 1;
    uint32_t SaturationDisp : 1;
    uint32_t CapModeDisp : 1;
    uint32_t PhoSizeDisp : 1;
    uint32_t PhoVideoQualityDisp : 1;
    uint32_t HistogramsDisp : 1;
    uint32_t BatteryPowerDisp : 1;
    uint32_t Res : 16;
};

union anon_union_conflict2544_for_u
{
    struct anon_struct_conflict242a bits;
    uint16_t Value;
};

struct _DUSS_MSG_PREVIEW_OSD_PARA_t
{
    union anon_union_conflict2544_for_u u;
};

struct _DUSS_MSG_QUICKVIEW_t
{
    uint8_t Time : 7;
    uint8_t Op : 1;
};

struct _DUSS_MSG_CAMERA_AUDIO_STATUS_t
{
    uint8_t reversed : 6;
    uint8_t mic_opened : 1;
    uint8_t speaker_opened : 1;
    uint8_t speaker_audio_volumn;
};

struct _DUSS_MSG_F_INDEX_MODE_t
{
    uint8_t Mode;
};

struct _DUSS_MSG_CAM_STATE_t
{
    uint32_t WifiCon : 1;
    uint32_t UsbCon : 1;
    uint32_t TimeSync : 1;
    uint32_t Capture : 3;
    uint32_t Record : 2;
    uint32_t SensorErr : 1;
    uint32_t SdInserted : 1;
    uint32_t SdStatus : 4;
    uint32_t FwUpgrading : 1;
    uint32_t FwUpgradErr : 2;
    uint32_t OverHeat : 1;
    uint32_t CapForbit : 1;
    uint32_t Storage : 1;
    uint32_t ContiCap : 1;
    uint32_t Hdmi : 1;
    uint32_t Encrypt : 2;
    uint32_t FileSync : 1;
    uint32_t RCBtmForbid : 1;
    uint32_t InFocus : 1;
    uint32_t gimbal_state : 1;
    uint32_t is_tracking : 1;
    uint32_t is_hyperlapse : 1;
    uint32_t Reserved : 2;
};

struct _DUSS_MSG_SYSTEM_STATE_t
{
    DUSS_MSG_CAM_STATE_t CamState;
    uint8_t WorkMode;
};

struct _DUSS_MSG_HYPERLAPSE_LIVEVIEW_MARGIN_t
{
    float x;
    float y;
};

struct _DUSS_MSG_CAMERA_STATUS_PUSH_t
{
    DUSS_MSG_SYSTEM_STATE_t CameraStatus;
    uint32_t Capacity;
    uint32_t SpareCap;
    uint32_t RemainShots;
    uint32_t RemainTime;
    DUSS_MSG_F_INDEX_MODE_t FileIndexMode;
    DUSS_MSG_QUICKVIEW_t PhotoQuickViewPara;
    DUSS_MSG_PHOTO_OSD_PARA_t PhotoOSDPara;
    DUSS_MSG_PREVIEW_OSD_PARA_t PreviewOSDPara;
    uint16_t RecordTime;
    uint8_t CapCapacityNum;
    DUSS_MSG_HISTOGRAM_t Histogram;
    uint8_t CameraModel;
    uint16_t CurrentRecordingTime;
    uint8_t ProtocolType;
    uint8_t RawSupport;
    uint8_t LcdFormat;
    uint8_t Reserved;
    uint8_t CropMode;
    uint8_t NdFilter;
    uint32_t ErrCode;
    uint8_t mic_audio_volumn;
    uint8_t camera_advance_mode;
    uint8_t StreamQuality;
    DUSS_MSG_CAMERA_AUDIO_STATUS_t audio_status;
    DUSS_MSG_HYPERLAPSE_LIVEVIEW_MARGIN_t HyperlapseMargin;
};

struct duss_list_head
{
    struct duss_list_head *next;
    struct duss_list_head *prev;
};

struct gs_storage_listener
{
    void *ctx;
    int (*event_cb)(void *, storage_event_t);
};

struct gs_lv_rec_ctrl
{
    uint8_t *lv_rec_state;
    gs_lv_src_t *lv_src;
    gs_lv_csm_t lv_csm;
    gs_storage_listener_t storage_listener;
    struct duss_osal_mutex_handle_t *list_mutex;
    struct duss_list_head frame_list;
    int num_in_list;
    int frames_received;
    _Bool b_wrf_running;
    undefined field9_0x3d;
    undefined field10_0x3e;
    undefined field11_0x3f;
    int frames_write;
    struct duss_osal_task_handle_t *task_wrf;
};

struct gs_avin_us
{
    uint8_t brightness;
    uint8_t saturation;
    undefined field2_0x2;
    undefined field3_0x3;
    int dev_mem;
    void *uncal_nvram_va;
    void *uncal_nvram_align_va;
    size_t uncal_nvram_map_sz;
};

struct gs_av_in_ctrl
{
    gs_media_cmd_chnl_t *mcc;
    _Bool avin_start;
    undefined field2_0x5;
    undefined field3_0x6;
    undefined field4_0x7;
    gs_avin_us_t avin_us;
};

struct gs_camera_cmd_ctrl_t
{
    struct duss_osal_task_handle_t *cam_cmd_task;
    struct duss_osal_msgq_handle_t *cam_cmd_queue;
    _Bool cam_cmd_task_quit;
    undefined field3_0x9;
    undefined field4_0xa;
    undefined field5_0xb;
    duss_event_client_handle_t event_client;
    _Bool init;
    _Bool set_best_liveview;
    uint8_t lv_format;
    undefined field10_0x13;
    struct duss_osal_task_handle_t *cam_monitor_task;
    _Bool cam_monitor_task_quit;
    undefined field13_0x19;
    undefined field14_0x1a;
    undefined field15_0x1b;
    void *ctx;
};

struct gs_bl
{
    duss_hal_obj_handle_t i2c_obj[2];
    uint8_t brightness_value;
    undefined field2_0x9;
    undefined field3_0xa;
    undefined field4_0xb;
    float lr_ratio;
    uint8_t mode;
    _Bool b_quit_monitor;
    undefined field8_0x12;
    undefined field9_0x13;
    struct duss_osal_task_handle_t *lcd_monitor_task;
};

struct _DUSS_MSG_RC_MS_LINK_STATUS
{
    uint8_t pair_role;
    uint8_t master_link_stat : 4;
    uint8_t master_device_type : 4;
    uint8_t slave_link_stat : 4;
    uint8_t slave_device_type : 4;
    uint8_t coach_role;
    uint8_t double_rc_stat;
};

struct duss_osal_timer_attrib_t
{
    char *name;
    duss_osal_timer_entry_t entry;
    void *param;
    uint32_t timeout_us;
    int32_t repeat_times;
    enum duss_osal_priority_t priority;
};

struct gs_fan_info
{
    struct duss_osal_task_handle_t *fan_adjust_task;
    _Bool fan_adjust_task_quit;
    undefined field2_0x5;
    undefined field3_0x6;
    undefined field4_0x7;
    int fan_pwm_period;
    int fan_pwm_duty;
    enum gs_fan_level_t fan_pwm_level;
    _Bool fan_enable;
    undefined field9_0x15;
    undefined field10_0x16;
    undefined field11_0x17;
};

struct __gs_use_times_info
{
    uint8_t magic[2];
    _Bool flag;
    uint32_t times;
};

struct gs_usb_listener
{
    void *ctx;
    int (*event_cb)(void *, usb_event_t);
};

struct gs_sd_listener
{
    void *ctx;
    int (*event_cb)(void *, sd_event_t);
};

struct gs_lv_transcode
{
    ion_info_t *ion_info;
    struct duss_osal_mutex_handle_t *rec_mutex;
    record_state_t cur_state;
    record_state_t tgt_state;
    _Bool b_rec_running;
    undefined field5_0x11;
    undefined field6_0x12;
    undefined field7_0x13;
    struct duss_osal_task_handle_t *rec_thread;
    uint8_t *lv_rec_state;
    gs_local_sd_info_t *sd_info;
    gs_sd_listener_t sd_listener;
    gs_usb_listener_t usb_listener;
    gs_media_cmd_chnl_t *mcc;
    int dmi_data_fd;
    int file_idx;
    char file_name[128];
    struct AVCodecContext *avcodec_ctx;
    p1_muxer_handle_t muxer;
    record_mode_t rec_mode;
    int video_stream_index;
    undefined field21_0xcc;
    undefined field22_0xcd;
    undefined field23_0xce;
    undefined field24_0xcf;
    int64_t cur_rec_time;
    char *sps_buf;
    uint32_t sps_len;
    struct duss_osal_mutex_handle_t *video_list_mutex;
    struct duss_list_head video_list;
    int num_frames;
    _Bool b_running;
    _Bool b_eos;
    undefined field33_0xf2;
    undefined field34_0xf3;
    struct duss_osal_task_handle_t *task_rx;
    uint32_t frames_received;
    uint32_t frames_write;
    uint32_t last_key_frm_idx;
    uint32_t last_frame_idx;
    _Bool b_wrf_running;
    undefined field41_0x109;
    undefined field42_0x10a;
    undefined field43_0x10b;
    FILE *p_file;
    struct duss_osal_task_handle_t *task_wrf;
    int first_idx_in_file;
    _Bool b_pending_new_file;
    _Bool b_avin_recording;
    undefined field49_0x11a;
    undefined field50_0x11b;
    undefined field51_0x11c;
    undefined field52_0x11d;
    undefined field53_0x11e;
    undefined field54_0x11f;
    int64_t cur_rec_time_ms;
    char srt_file_name[128];
    _Bool b_srt_record_running;
    _Bool b_srt_switch_new_file;
    undefined field59_0x1aa;
    undefined field60_0x1ab;
    FILE *p_srt_file;
    struct duss_osal_task_handle_t *task_srt_record;
    undefined field63_0x1b4;
    undefined field64_0x1b5;
    undefined field65_0x1b6;
    undefined field66_0x1b7;
};

struct __gs_info
{
    duss_event_client_handle_t event_client;
    duss_hal_obj_handle_t vmem_obj;
    duss_hal_obj_handle_t gpio_obj;
    int32_t dev_mem;
    gs_debug_ctrl_t dbg_ctrl;
    struct duss_osal_task_handle_t *sdr_status_listen_task;
    _Bool b_sdr_status_quit;
    undefined field7_0x12d;
    undefined field8_0x12e;
    undefined field9_0x12f;
    gs_local_sd_info_t sd_info;
    struct duss_osal_timer_handle_t *sd_monitor_timer;
    DUSS_MSG_RC_BAT_INFO_t bat_info;
    undefined field13_0x16a;
    undefined field14_0x16b;
    gs_battery_info_t batt_info;
    uint8_t current_uav_rc_sdr_mode;
    undefined field17_0x185;
    undefined field18_0x186;
    undefined field19_0x187;
    gs_modem_ctrl_t modem_ctrl;
    DUSS_MSG_RC_MS_LINK_STATUS_t ms_link_stat;
    _Bool b_active_quit;
    _Bool b_rc_mp_state_got;
    _Bool b_rc_active_get_pending;
    _Bool b_uav_mp_state_got;
    _Bool b_uav_active_get_pending;
    uint8_t uav_mp_state;
    uint8_t uav_active_state;
    uint8_t gls_active_state;
    undefined field30_0x2f1;
    undefined field31_0x2f2;
    undefined field32_0x2f3;
    struct duss_osal_task_handle_t *get_activate_task;
    gs_use_times_info_t use_times_before_active;
    undefined field35_0x2ff;
    gs_rc_ctrl_t rc_ctrl;
    struct keys_pack_to_racing_glass_t key_state;
    _Bool key_flag;
    undefined field39_0x3f7;
    struct duss_osal_timer_handle_t *keyscan_task_handle;
    struct duss_osal_timer_attrib_t keyscan_task_attrib;
    struct duss_osal_timer_handle_t *detect_taking_off_task_handle;
    struct duss_osal_timer_attrib_t detect_taking_off_task_attrib;
    struct pack_for_factory_test_t factory_test_key_info;
    gs_buzzer_info_t buzzer_info;
    gs_fan_info_t fan_info;
    uint8_t cam_model;
    uint8_t cam_work_mode;
    _Bool check_cam_work_mode;
    _Bool cam_is_pb;
    gs_common_cmd_ctrl_t cmn_cmd_ctrl;
    struct gs_camera_cmd_ctrl_t cam_cmd_ctrl;
    DUSS_MSG_CAMERA_STATUS_PUSH_t uav_cam_stat;
    undefined field54_0x50b;
    gs_video_channel_manager_t chnl_mgr;
    gs_wl_ctrl_t wl_ctrl;
    gs_av_in_ctrl_t avin_ctrl;
    vdec_local_player_t *player;
    metadata_retriever_t metad_rt;
    uint8_t lv_rec_state;
    undefined field61_0x8d1;
    undefined field62_0x8d2;
    undefined field63_0x8d3;
    gs_lv_src_t lv_src;
    gs_lv_rec_ctrl_t lv_rec_ctrl;
    gs_usb_gadget_vt_t usb_vt;
    gs_lv_transcode_t lv_transcode;
    gs_aout_t gs_aout;
    gs_audio_wl_t audio_wl;
    gs_media_cmd_chnl_t media_cmd_chnl;
    gs_bl_t gs_bl;
    struct timeval disarm_start;
    uint8_t disarm_flag;
    uint8_t low_power_mode;
    undefined field75_0xb9a;
    undefined field76_0xb9b;
    uint32_t rtc_listener_id;
    struct duss_osal_timer_handle_t *rtc_brdcst_timer;
    struct duss_osal_timer_handle_t *lcdc_blending_check_timer;
    gs_gui_t gui;
    gs_ext_fc_t ext_fc;
    gs_shram_t pdt_shram;
    gs_shram_t plf_shram;
    char user_data_file_name[64];
    gs_queue_t user_data_queue;
    struct duss_osal_timer_handle_t *user_data_update_timer;
    struct duss_osal_task_handle_t *user_data_sender_task;
    struct duss_osal_task_handle_t *device_sn_check_task;
    _Bool is_pc_connect;
    uint8_t user_privacy_setting;
    uint16_t user_vt_sn_id;
    uint16_t user_rc_sn_id;
    uint8_t user_country_code[2];
    _Bool b_sender_task_quit;
    _Bool b_sn_check_task_quit;
    gs_user_json_root_t json_root_info;
    undefined field97_0xf9a;
    undefined field98_0xf9b;
    struct duss_osal_mutex_handle_t *user_queue_mutex;
    gs_avin_test_ctrl_t avin_test_ctrl;
    _Bool is_speaker_test_start;
    undefined field102_0xfa9;
    undefined field103_0xfaa;
    undefined field104_0xfab;
    struct duss_osal_mutex_handle_t *test_status_mutex;
    uint8_t uav_power_status;
    uint8_t arm_flag_from_uav;
    uint8_t exit_flag;
    undefined field109_0xfb3;
    gs_watermarker_ctrl_t watermarker_ctrl;
    undefined field111_0xfcc;
    undefined field112_0xfcd;
    undefined field113_0xfce;
    undefined field114_0xfcf;
};

struct ip_channel_addr
{
    char *ifx;
    uint16_t loc_port;
    undefined field2_0x6;
    undefined field3_0x7;
    char *address;
    uint16_t rmt_port;
    undefined field6_0xe;
    undefined field7_0xf;
};

struct pthread_cond_t
{
    int32_t __private[1];
};

struct AVFrac
{
    int64_t val;
    int64_t num;
    int64_t den;
};

struct duss_hal_storage_info
{
    char id[64];
    char fs[8];
    char path[256];
    char state;
    undefined field4_0x149;
    undefined field5_0x14a;
    undefined field6_0x14b;
    int speed;
    int uhs_grade;
    int capacity;
    int readonly;
    int block_size;
};

struct AVIndexEntry
{
    int64_t pos;
    int64_t timestamp;
    int flags : 2;
    int size : 30;
    int min_distance;
};

struct AVBuffer
{
};

struct AVRational
{
    int num;
    int den;
};

struct AVChapter
{
    int id;
    struct AVRational time_base;
    undefined field2_0xc;
    undefined field3_0xd;
    undefined field4_0xe;
    undefined field5_0xf;
    int64_t start;
    int64_t end;
    struct AVDictionary *metadata;
    undefined field9_0x24;
    undefined field10_0x25;
    undefined field11_0x26;
    undefined field12_0x27;
};

struct gs_gui_event_t
{
    gs_gui_event_type_t type;
    gs_gui_event_symbol_t symbol;
    float posx;
    float posy;
    float dx;
    float dy;
    float yaw;
    float pitch;
    float roll;
};

struct _DUSS_MSG_V_CRTL_t
{
    uint8_t Op;
    uint32_t time_offset;
};

struct pthread_mutex_t
{
    int32_t __private[1];
};

struct duss_osal_event_attrib_t
{
    char *name;
};

struct duss_osal_event_handle_t
{
    struct duss_osal_event_attrib_t attrib;
    struct pthread_mutex_t mutex;
    struct pthread_cond_t cond;
    uint32_t data;
    int32_t flag;
};

struct modem_ops
{
    int (*pairing_control)(void *, uint32_t);
    int (*set_pairing_role)(void *, uint32_t);
    int (*get_link_stat)(void *, enum gs_link_stat_t *);
    int (*get_bandwidth)(void *, uint16_t *);
    int (*set_bandwidth)(void *, uint16_t);
    int (*get_chnl)(void *, uint16_t *);
    int (*set_chnl)(void *, uint16_t);
    int (*rob_chnl)(void *, uint16_t);
    int (*rob_chnl_cancel)(void *);
    int (*get_rob_left_time)(void *, uint8_t *);
    int (*get_rob_flag)(void *, uint8_t *);
    int (*clear_rob_flag)(void *);
    int (*set_public_chnl)(void *);
    int (*is_drone_broadcast)(void *, uint16_t *);
    int (*enable_drone_broadcast)(void *, uint16_t);
    int (*listen_broadcast)(void *, uint16_t);
    int (*is_silent)(void *, uint16_t *);
    int (*set_chnl_scan_info)(void *, uint8_t, uint8_t);
    int (*scan_chnl_x)(void *, uint8_t, uint8_t);
    int (*check_ant_status)(void *);
    int (*if_new_chnl_scan_info)(void *, uint8_t *);
    int (*if_new_phy_check_info)(void *, uint8_t *);
    int (*if_update_bandwidth_pending)(void *, uint8_t *);
    int (*clear_scan_flag)(void *);
    int (*clear_check_flag)(void *);
    int (*get_chnl_scan_info)(void *, uint8_t, uint8_t *, uint8_t *, uint32_t *);
    int (*get_ant_status)(void *, uint8_t *, uint8_t *);
    int (*get_dbg_mcs)(void *, uint16_t *);
    int (*set_dbg_mcs)(void *, uint16_t);
    int (*get_dbg_harq)(void *, uint16_t *);
    int (*set_dbg_harq)(void *, uint16_t);
    int (*get_dbg_codec_rate)(void *, uint16_t *);
    int (*set_dbg_codec_rate)(void *, uint16_t);
    int (*get_signal_quality)(void *, struct glass_signal_quality_t *);
    int (*get_rc_signal_quality)(void *, struct glass_signal_quality_t *);
    int (*set_bandwidth_mode)(void *, uint16_t);
    int (*change_silent_mode)(void *, uint8_t);
    int (*get_chnl_cnt)(void *, uint16_t *);
    int (*get_freq_by_index)(void *, uint16_t *, uint16_t);
    int (*get_scan_type)(void *, uint8_t *);
    int (*get_wl_area_id)(void *, uint8_t *);
    int (*get_pairing_finish_flag)(void *, uint8_t *);
    int (*check_conf_items)(void *);
};

struct _UAV_RECORD_MODE_t
{
    uint8_t type;
    uint8_t value;
};

struct AVFrameSideData
{
    enum AVFrameSideDataType type;
    uint8_t *data;
    int size;
    struct AVDictionary *metadata;
};

struct _DUSS_MSG_APERTURE_t
{
    uint16_t Value;
};

struct _DUSS_MSG_VIDEO_STANDARD_t
{
    uint8_t Value;
};

struct AVCodecParser
{
    int codec_ids[5];
    int priv_data_size;
    int (*parser_init)(struct AVCodecParserContext *);
    int (*parser_parse)(struct AVCodecParserContext *, struct AVCodecContext *, uint8_t **, int *, uint8_t *, int);
    void (*parser_close)(struct AVCodecParserContext *);
    int (*split)(struct AVCodecContext *, uint8_t *, int);
    struct AVCodecParser *next;
};

struct hpi_channel
{
    __u32 priority;
    __u8 major_id : 4;
    __u8 minor_id : 4;
    undefined field3_0x5;
    __u16 order;
};

struct hpi_channel_addr
{
    char *obj_name;
    duss_hal_hpi_config_t cfg;
};

struct _DUSS_MSG_WORKMODE_t
{
    uint8_t WorkMode;
};

struct timespec
{
    __kernel_time_t tv_sec;
    long tv_nsec;
};

struct ext_fc_ops
{
    int (*get_craft_name)(void *, char *);
    int (*get_pid_profile_index)(void *, uint8_t *);
    int (*get_rate_profile_index)(void *, uint8_t *);
    int (*get_osd_profile_index)(void *, uint8_t *);
    int (*select_file)(void *, uint8_t, uint8_t);
    int (*copy_file)(void *, uint8_t, uint8_t, uint8_t);
    int (*write_eeprom)(void *);
    int (*get_rc_channel)(void *, uint8_t, uint16_t *);
    int (*get_aux_id)(void *, uint8_t *, uint8_t, uint8_t *, uint8_t *);
    int (*get_aux_mode)(void *, uint8_t, uint8_t *, uint8_t *, uint8_t *);
    int (*set_aux_mode)(void *, uint8_t, uint8_t, uint8_t, uint8_t);
    int (*set_request_type)(void *, uint8_t);
    int (*get_request_type)(void *, uint8_t *);
    int (*get_ag_gain)(void *, uint16_t *);
    int (*set_ag_gain)(void *, uint16_t);
    int (*get_ag_thr)(void *, uint16_t *);
    int (*set_ag_thr)(void *, uint16_t);
    int (*get_thr_boost)(void *, uint8_t *);
    int (*set_thr_boost)(void *, uint8_t);
    int (*get_ff_trans)(void *, uint8_t *);
    int (*set_ff_trans)(void *, uint8_t);
    int (*get_filter)(void *, uint8_t, uint16_t *);
    int (*set_filter)(void *, uint8_t, uint16_t);
    int (*get_rate)(void *, uint8_t, uint8_t *);
    int (*set_rate)(void *, uint8_t, uint8_t);
    int (*get_super_rate)(void *, uint8_t, uint8_t *);
    int (*set_super_rate)(void *, uint8_t, uint8_t);
    int (*get_expo)(void *, uint8_t, uint8_t *);
    int (*set_expo)(void *, uint8_t, uint8_t);
    int (*get_dyn_thr)(void *, uint8_t *);
    int (*set_dyn_thr)(void *, uint8_t);
    int (*get_thr_mid)(void *, uint8_t *);
    int (*set_thr_mid)(void *, uint8_t);
    int (*get_thr_expo)(void *, uint8_t *);
    int (*set_thr_expo)(void *, uint8_t);
    int (*get_tpa)(void *, uint16_t *);
    int (*set_tpa)(void *, uint16_t);
    int (*get_pid)(void *, uint8_t, uint8_t *);
    int (*set_pid)(void *, uint8_t, uint8_t);
    int (*get_pid_f)(void *, uint8_t, uint16_t *);
    int (*set_pid_f)(void *, uint8_t, uint16_t);
    int (*get_battery_state)(void *, enum batteryState_e *);
    int (*get_battery_voltage)(void *, uint16_t *);
    int (*get_battery_avg_voltage)(void *, uint16_t *);
    int (*get_battery_amperage)(void *, uint16_t *);
    int (*get_battery_mah)(void *, uint16_t *);
    int (*get_battery_usage)(void *, uint16_t *);
    int (*get_battery_power)(void *, uint16_t *);
    int (*set_arming_disabled)(void *, uint8_t);
    int (*get_arming_disabled)(void *, uint32_t *);
    int (*get_fc_version)(void *, uint8_t *, uint8_t *, uint8_t *);
    int (*set_sbus_mode)(void *, uint8_t);
    int (*get_racing_osd_info)(void *, DUSS_MSG_FC_RACING_DRONE_OSD_PUSH_t *);
    int (*get_osd_position)(void *, int, _Bool *, int *, int *);
    int (*get_units)(void *, uint8_t *);
    int (*get_fly_mode)(void *, uint16_t *);
    int (*get_rtc_date)(void *, DUSS_MSG_EXT_FC_RTC_t *);
    int (*get_esc_temperature)(void *, uint8_t *);
};

struct duss_hal_usbacc_config_t
{
    duss_usbacc_port_t port;
};

struct usbacc_channel_addr
{
    char *obj_name;
    struct duss_hal_usbacc_config_t cfg;
    undefined field2_0x6;
    undefined field3_0x7;
};

struct AVCodecContext
{
    struct AVClass *av_class;
    int log_level_offset;
    enum AVMediaType codec_type;
    struct AVCodec *codec;
    char codec_name[32];
    enum AVCodecID codec_id;
    uint codec_tag;
    uint stream_codec_tag;
    void *priv_data;
    struct AVCodecInternal *internal;
    void *opaque;
    int bit_rate;
    int bit_rate_tolerance;
    int global_quality;
    int compression_level;
    int flags;
    int flags2;
    uint8_t *extradata;
    int extradata_size;
    struct AVRational time_base;
    int ticks_per_frame;
    int delay;
    int width;
    int height;
    int coded_width;
    int coded_height;
    int gop_size;
    enum AVPixelFormat pix_fmt;
    int me_method;
    void (*draw_horiz_band)(struct AVCodecContext *, struct AVFrame *, int *, int, int, int);
    AVPixelFormat (*get_format)(struct AVCodecContext *, enum AVPixelFormat *);
    int max_b_frames;
    float b_quant_factor;
    int rc_strategy;
    int b_frame_strategy;
    float b_quant_offset;
    int has_b_frames;
    int mpeg_quant;
    float i_quant_factor;
    float i_quant_offset;
    float lumi_masking;
    float temporal_cplx_masking;
    float spatial_cplx_masking;
    float p_masking;
    float dark_masking;
    int slice_count;
    int prediction_method;
    int *slice_offset;
    struct AVRational sample_aspect_ratio;
    int me_cmp;
    int me_sub_cmp;
    int mb_cmp;
    int ildct_cmp;
    int dia_size;
    int last_predictor_count;
    int pre_me;
    int me_pre_cmp;
    int pre_dia_size;
    int me_subpel_quality;
    int dtg_active_format;
    int me_range;
    int intra_quant_bias;
    int inter_quant_bias;
    int slice_flags;
    int xvmc_acceleration;
    int mb_decision;
    uint16_t *intra_matrix;
    uint16_t *inter_matrix;
    int scenechange_threshold;
    int noise_reduction;
    int me_threshold;
    int mb_threshold;
    int intra_dc_precision;
    int skip_top;
    int skip_bottom;
    float border_masking;
    int mb_lmin;
    int mb_lmax;
    int me_penalty_compensation;
    int bidir_refine;
    int brd_scale;
    int keyint_min;
    int refs;
    int chromaoffset;
    int scenechange_factor;
    int mv0_threshold;
    int b_sensitivity;
    enum AVColorPrimaries color_primaries;
    enum AVColorTransferCharacteristic color_trc;
    enum AVColorSpace colorspace;
    enum AVColorRange color_range;
    enum AVChromaLocation chroma_sample_location;
    int slices;
    enum AVFieldOrder field_order;
    int sample_rate;
    int channels;
    enum AVSampleFormat sample_fmt;
    int frame_size;
    int frame_number;
    int block_align;
    int cutoff;
    int request_channels;
    undefined field102_0x1bc;
    undefined field103_0x1bd;
    undefined field104_0x1be;
    undefined field105_0x1bf;
    uint64_t channel_layout;
    uint64_t request_channel_layout;
    enum AVAudioServiceType audio_service_type;
    enum AVSampleFormat request_sample_fmt;
    int (*get_buffer)(struct AVCodecContext *, struct AVFrame *);
    void (*release_buffer)(struct AVCodecContext *, struct AVFrame *);
    int (*reget_buffer)(struct AVCodecContext *, struct AVFrame *);
    int (*get_buffer2)(struct AVCodecContext *, struct AVFrame *, int);
    int refcounted_frames;
    float qcompress;
    float qblur;
    int qmin;
    int qmax;
    int max_qdiff;
    float rc_qsquish;
    float rc_qmod_amp;
    int rc_qmod_freq;
    int rc_buffer_size;
    int rc_override_count;
    struct RcOverride *rc_override;
    char *rc_eq;
    int rc_max_rate;
    int rc_min_rate;
    float rc_buffer_aggressivity;
    float rc_initial_cplx;
    float rc_max_available_vbv_use;
    float rc_min_vbv_overflow_use;
    int rc_initial_buffer_occupancy;
    int coder_type;
    int context_model;
    int lmin;
    int lmax;
    int frame_skip_threshold;
    int frame_skip_factor;
    int frame_skip_exp;
    int frame_skip_cmp;
    int trellis;
    int min_prediction_order;
    int max_prediction_order;
    undefined field145_0x264;
    undefined field146_0x265;
    undefined field147_0x266;
    undefined field148_0x267;
    int64_t timecode_frame_start;
    void (*rtp_callback)(struct AVCodecContext *, void *, int, int);
    int rtp_payload_size;
    int mv_bits;
    int header_bits;
    int i_tex_bits;
    int p_tex_bits;
    int i_count;
    int p_count;
    int skip_count;
    int misc_bits;
    int frame_bits;
    char *stats_out;
    char *stats_in;
    int workaround_bugs;
    int strict_std_compliance;
    int error_concealment;
    int debug;
    int debug_mv;
    int err_recognition;
    undefined field169_0x2bc;
    undefined field170_0x2bd;
    undefined field171_0x2be;
    undefined field172_0x2bf;
    int64_t reordered_opaque;
    struct AVHWAccel *hwaccel;
    void *hwaccel_context;
    uint64_t error[8];
    int dct_algo;
    int idct_algo;
    int bits_per_coded_sample;
    int bits_per_raw_sample;
    int lowres;
    struct AVFrame *coded_frame;
    int thread_count;
    int thread_type;
    int active_thread_type;
    int thread_safe_callbacks;
    int (*execute)(struct AVCodecContext *, int (*)(struct AVCodecContext *, void *), void *, int *, int, int);
    int (*execute2)(struct AVCodecContext *, int (*)(struct AVCodecContext *, void *, int, int), void *, int *, int);
    void *thread_opaque;
    int nsse_weight;
    int profile;
    int level;
    enum AVDiscard skip_loop_filter;
    enum AVDiscard skip_idct;
    enum AVDiscard skip_frame;
    uint8_t *subtitle_header;
    int subtitle_header_size;
    int error_rate;
    struct AVPacket *pkt;
    undefined field200_0x36c;
    undefined field201_0x36d;
    undefined field202_0x36e;
    undefined field203_0x36f;
    uint64_t vbv_delay;
    int side_data_only_packets;
    int initial_padding;
    struct AVRational framerate;
    struct AVRational pkt_timebase;
    struct AVCodecDescriptor *codec_descriptor;
    undefined field210_0x394;
    undefined field211_0x395;
    undefined field212_0x396;
    undefined field213_0x397;
    int64_t pts_correction_num_faulty_pts;
    int64_t pts_correction_num_faulty_dts;
    int64_t pts_correction_last_pts;
    int64_t pts_correction_last_dts;
    char *sub_charenc;
    int sub_charenc_mode;
    int skip_alpha;
    int seek_preroll;
    uint16_t *chroma_intra_matrix;
    uint8_t *dump_separator;
    char *codec_whitelist;
    int bit_depth_luma;
    int chroma_format_idc;
    undefined field227_0x3dc;
    undefined field228_0x3dd;
    undefined field229_0x3de;
    undefined field230_0x3df;
};

struct _DUSS_MSG_SATURATION_t
{
    int8_t Value;
};

struct _DUSS_MSG_ZOOM_P_t
{
    uint16_t Ratio;
};

struct _DUSS_MSG_ZOOM_S_t
{
    uint16_t Step : 8;
    uint16_t Direction : 1;
    uint16_t Reserved : 7;
};

struct _DUSS_MSG_ZOOM_C_t
{
    uint16_t Speed : 8;
    uint16_t Direction : 1;
    uint16_t Reserved : 7;
};

union anon_union_conflict21a2_for_OZoomRaUnion
{
    DUSS_MSG_ZOOM_S_t ZoomS;
    DUSS_MSG_ZOOM_P_t ZoomP;
    DUSS_MSG_ZOOM_C_t ZoomC;
};

struct _DUSS_MSG_ZOOM_CTRL_MODE_t_
{
    uint8_t DZoomMode : 2;
    uint8_t Reserved1 : 1;
    uint8_t DZoomCtrl : 1;
    uint8_t OZoomMode : 2;
    uint8_t Reserved2 : 1;
    uint8_t OZoomCtrl : 1;
};

struct _DUSS_MSG_ZOOM_PARAM_t
{
    DUSS_MSG_ZOOM_CTRL_MODE_t Mode;
    union anon_union_conflict21a2_for_OZoomRaUnion OZoomRaUnion;
    union anon_union_conflict21a2_for_OZoomRaUnion DZoomRaUnion;
};

struct _DUSS_MSG_CAPTURE_MODE_t
{
    uint8_t Op;
    uint8_t Mcap_Cnt;
    uint8_t Ccap_Type;
    uint8_t Ccap_Cnt;
    uint16_t Ccap_Interval;
};

struct _DUSS_MSG_ISO_t
{
    uint8_t Value;
};

struct _DUSS_MSG_SD_STATUS_t
{
    uint8_t Inserted : 1;
    uint8_t Status : 4;
    uint8_t Reserved : 3;
};

struct _DUSS_MSG_SD_INFO_t
{
    DUSS_MSG_SD_STATUS_t SdStatus;
    uint32_t Capacity;
    uint32_t SpareCap;
    uint32_t RemainShots;
    uint32_t RemainTime;
};

struct _DUSS_MSG_EXPO_MODE_t
{
    uint8_t Mode;
    uint8_t ScnMode;
};

struct _DUSS_MSG_FLIP
{
    uint8_t type;
    uint8_t angle;
};

struct _DUSS_MSG_SHARPNESS_t
{
    int8_t Value;
};

struct _DUSS_MSG_CONTICAP_PARAM_t
{
    uint8_t Type;
    uint8_t Cnt;
    uint16_t Interval;
};

struct _DUSS_MSG_P_STORAGE_FMT_t
{
    uint8_t Fmt;
};

struct _DUSS_MSG_RECORD_t
{
    uint8_t Op : 2;
    uint8_t type : 4;
    uint8_t Reserved : 2;
};

struct _DUSS_MSG_WB_t
{
    uint8_t Mode;
    uint8_t WbCt;
};

struct _DUSS_MSG_CONTRAST_t
{
    int8_t Value;
};

struct _DUSS_MSG_SHUTTER_A_t
{
    uint16_t Value : 15;
    uint16_t Flag : 1;
    uint8_t Decimal;
};

struct _DUSS_MSG_SHUTTER_SPEED_t
{
    uint8_t Mode;
    DUSS_MSG_SHUTTER_A_t ShutterA;
};

struct _DUSS_MSG_DIGITAL_EFFECT_t
{
    uint8_t Effect;
};

struct _DUSS_MSG_EV_BIAS_t
{
    uint8_t Bias;
};

struct _DUSS_MSG_V_STORAGE_FMT_t
{
    uint8_t Fmt;
};

struct _DUSS_MSG_SINGLE_PLAY_CRTL_t
{
    uint32_t FileIndex;
};

struct _DUSS_MSG_SCENE_MODE_t
{
    uint8_t Mode;
};

struct _DUSS_MSG_SET_FOCUS_REGION_t
{
    float x;
    float y;
};

struct _DUSS_MSG_V_SS_CONFIG_t
{
    uint8_t Op : 1;
    uint8_t Reserved : 7;
};

struct _DUSS_MSG_V_FORMAT_t
{
    uint8_t FSResolution;
    uint8_t FrameRate;
    uint8_t Fov;
    DUSS_MSG_V_SS_CONFIG_t SSConfig;
    uint8_t SSResolution;
};

struct _DUSS_MSG_P_SIZE_t
{
    uint8_t Size;
    uint8_t AspectRatio;
};

struct _DUSS_MSG_CAPTURE_t
{
    uint8_t Op;
};

union anon_union_conflict2c9b_for_field_3
{
    DUSS_MSG_APERTURE_t aperture;
    DUSS_MSG_SHUTTER_SPEED_t shut_spd;
    DUSS_MSG_ISO_t iso;
    DUSS_MSG_EXPO_MODE_t expo_mode;
    DUSS_MSG_EV_BIAS_t ev_bias;
    DUSS_MSG_P_STORAGE_FMT_t p_storage;
    DUSS_MSG_WB_t wb;
    DUSS_MSG_SCENE_MODE_t scene_mode;
    DUSS_MSG_DIGITAL_EFFECT_t digit_effect;
    DUSS_MSG_P_SIZE_t p_size;
    DUSS_MSG_SET_FOCUS_REGION_t focus;
    DUSS_MSG_CAPTURE_MODE_t cap_mode;
    DUSS_MSG_CONTICAP_PARAM_t conticap;
    DUSS_MSG_V_STORAGE_FMT_t v_storage;
    DUSS_MSG_V_FORMAT_t v_fmt;
    DUSS_MSG_VIDEO_STANDARD_t v_std;
    DUSS_MSG_WORKMODE_t work_mode;
    DUSS_MSG_SINGLE_PLAY_CRTL_t play_ctrl_data;
    DUSS_MSG_V_CRTL_t video_ctrl_data;
    DUSS_MSG_SD_INFO_t sd_info;
    DUSS_MSG_ZOOM_PARAM_t zoom_param;
    DUSS_MSG_FLIP_t flip_mode;
    DUSS_MSG_SHARPNESS_t sharpness;
    DUSS_MSG_CONTRAST_t contrast;
    DUSS_MSG_SATURATION_t saturation;
    uint8_t lv_format;
    DUSS_MSG_CAPTURE_t cap_photo;
    DUSS_MSG_RECORD_t cap_video;
    UAV_RECORD_MODE_t rec_mode;
    uint8_t uav_low_power_mode;
    uint8_t uav_power_policy;
    uint8_t HDVT_pref;
    uint8_t enc_roi;
    uint8_t white_balance;
};

struct __gs_camera_cmd
{
    uint16_t cmd_id;
    uint16_t session_id;
    uint8_t ack_result;
    union anon_union_conflict2c9b_for_field_3 field_3;
    undefined field4_0x16;
    undefined field5_0x17;
    void (*call_back_handler)(struct __gs_camera_cmd *);
};

struct bridge_io_pkt
{
    uint32_t paddr;
    uint32_t size;
    uint8_t notify;
    undefined field3_0x9;
    undefined field4_0xa;
    undefined field5_0xb;
};

struct gs_lv_pkt
{
    void *align_vaddr;
    int align_size;
    void *vaddr;
    void *payload_vaddr;
    uint32_t payload_size;
    bridge_io_pkt_t pkt;
};

struct uav_gimbal_ops
{
    int (*ctrl_start)(void *);
    int (*ctrl_racing_start)(void *);
    int (*ctrl_stop)(void *);
    int (*reset_init_value)(void *);
    int (*turndown_start)(void *);
    int (*turndown_stop)(void *);
    int (*set_workmode)(void *, uint8_t);
    int (*ctrl_set_racing_pitch_offset)(void *, int16_t);
    int (*ctrl_set_racing_yaw_offset)(void *, int16_t);
    int (*ctrl_set_racing_pitch_sense)(void *, float);
    int (*ctrl_set_racing_yaw_sense)(void *, float);
    int (*ctrl_get_state)(void *, uint8_t *);
};

struct duss_hal_icc_config_t
{
    enum duss_hal_icc_role_t role;
    enum duss_hal_icc_shm_type_t shm_type;
    uint32_t shm_size;
};

struct RcOverride
{
    int start_frame;
    int end_frame;
    int qscale;
    float quality_factor;
};

struct uav_camera_ops
{
    int (*send_camera_cmd)(void *, gs_camera_cmd_t *, _Bool);
    int (*set_camera_param)(void *, uint8_t, uint8_t);
    int (*get_rec_time)(void *, int *, int *);
};

struct duss_event_cmd_desc
{
    duss_result_t (*req_cb)(struct duss_event_client *, duss_event_t *, void *);
    duss_result_t (*ack_cb)(struct duss_event_client *, duss_event_t *, void *);
    uint32_t flags;
};

struct cJSON
{
    struct cJSON *next;
    struct cJSON *prev;
    struct cJSON *child;
    int type;
    char *valuestring;
    int valueint;
    double valuedouble;
    char *string;
    undefined field8_0x24;
    undefined field9_0x25;
    undefined field10_0x26;
    undefined field11_0x27;
};

struct vr_device_ops
{
    int (*get_video_scale)(void *, float *);
    int (*set_video_scale)(void *, float);
    int (*adjust_fov)(void *, uint32_t, int16_t, int16_t);
    int (*set_brightness_value)(void *, uint8_t);
    int (*get_brightness_value)(void *, uint8_t *);
    int (*get_device_volume)(void *, uint8_t, uint32_t *);
    int (*set_device_volume)(void *, uint8_t, uint32_t);
    int (*calibrate_imu)(char *);
    int (*initialize_imu)(void *, ...);
    int (*destroy_imu)(void *, ...);
    int (*start_imu)(void *, ...);
    int (*stop_imu)(void *, ...);
    int (*get_imu_init_status)(void *, ...);
    int (*get_imu_attitude)(float *);
    int (*format_sd)(void *);
    int (*get_sd_info)(void *, gs_local_sd_info_t *);
    int (*get_battery_info)(void *, DUSS_MSG_RC_BAT_INFO_t *);
    int (*get_device_active_state)(void *, int);
    int (*get_upgrade_info)(void *, _Bool *, uint8_t *, uint8_t *);
    int (*av_in_us_get_brightness)(void *, uint8_t *);
    int (*av_in_us_set_brightness)(void *, uint8_t);
    int (*av_in_us_get_saturation)(void *, uint8_t *);
    int (*av_in_us_set_saturation)(void *, uint8_t);
    int (*reset_user_settings)(void *);
    int (*event_tracking)(void *, int32_t, uint8_t, uint8_t);
    void (*get_flight_stat)(uint8_t *);
    void (*set_flight_stat)(uint8_t);
    int (*watermarker_us_get_flag)(void *, uint8_t *);
    int (*watermarker_us_set_flag)(void *, uint8_t);
    int (*watermarker_us_reset)(void *);
};

struct pl_decoder_itf_t
{
    int (*create)(pl_decoder_handle_t *, void *, void *);
    int (*destroy)(pl_decoder_handle_t);
    int (*init)(pl_decoder_handle_t);
    int (*config)(pl_decoder_handle_t, void *);
    int (*prepare)(pl_decoder_handle_t);
    int (*release)(pl_decoder_handle_t);
    int (*decode)(pl_decoder_handle_t, void *, uint32_t, void *, uint32_t *);
    int (*push_frame)(pl_decoder_handle_t, void *, uint32_t);
    int (*set_input_datacb)(pl_decoder_handle_t, void *, input_data_cb);
    int (*set_output_datacb)(pl_decoder_handle_t, void *, output_data_cb);
};

struct duss_event_ack_identify
{
    duss_msg_id_t msg_id;
    uint16_t peer_host;
    uint16_t seq_id;
    uint16_t valid;
    undefined field4_0xa;
    undefined field5_0xb;
    void *buffer_ptr;
    uint32_t buffer_size;
};

struct vcm_ops
{
    int (*register_channel_switch_callback)(void *, gs_video_channel_switch_callback_t, void *);
    int (*register_channel_push_callback)(void *, gs_video_channel_push_callback_t, void *);
    int (*query_current_channel)(void *, gs_video_channel_id_t *);
    int (*enable_channel)(void *, gs_main_channel_id_t);
    int (*disable_channel)(void *, gs_main_channel_id_t);
    int (*enable_sub_channel)(void *, gs_video_channel_id_t *);
    int (*disable_sub_channel)(void *, gs_video_channel_id_t *);
    int (*local_playback_on)(void *, char *);
    int (*local_playback_off)(void *);
    int (*rc_setting_on)(void *);
    int (*rc_setting_off)(void *);
};

struct AVOptionRange
{
    char *str;
    undefined field1_0x4;
    undefined field2_0x5;
    undefined field3_0x6;
    undefined field4_0x7;
    double value_min;
    double value_max;
    double component_min;
    double component_max;
    int is_range;
    undefined field10_0x2c;
    undefined field11_0x2d;
    undefined field12_0x2e;
    undefined field13_0x2f;
};

struct debug_osd_item
{
    char *name;
    int value;
};

struct debug_cam_osd_info
{
    debug_osd_item_t items[26];
    int n_items;
};

struct AVPanScan
{
    int id;
    int width;
    int height;
    int16_t position[3][2];
};

struct AVProfile
{
    int profile;
    char *name;
};

struct loc_channel_addr
{
    uint16_t direct_host;
};

struct __gs_common_cmd
{
    duss_msg_id_t msg_id;
    uint16_t receiver_id;
    uint16_t session_id;
    uint8_t ack_result;
    undefined field4_0x9;
    undefined field5_0xa;
    undefined field6_0xb;
    uint8_t *msg_buf;
    uint32_t msg_len;
    uint8_t *resp_msg_buf;
    uint32_t resp_msg_len;
    void (*call_back_handler)(struct __gs_common_cmd *);
};

struct duss_hal_mem_config_t
{
    uint32_t reserved;
};

struct wl_channel_addr
{
    char *ifx;
    uint16_t loc_port;
    undefined field2_0x6;
    undefined field3_0x7;
    char *address;
    uint16_t rmt_port;
    uint16_t mtu;
    _Bool is_server;
    duss_wl_prot_type_t protocol;
    duss_wl_prio_t priority;
    undefined field10_0x13;
    int flags;
};

struct AVDeviceCapabilitiesQuery
{
};

struct __sbuf
{
    uchar *_base;
    int _size;
};

struct vdec_video_file_info
{
    uint32_t strm_type;
    uint32_t total_time;
    uint32_t frame_interval;
    uint32_t fps_numerator;
    uint32_t fps_denorm;
    uint32_t width;
    uint32_t height;
    int32_t rotation;
    enum DUSS_FILE_FORMAT video_format;
};

struct fd_set
{
    ulong fds_bits[32];
};

struct duss_mb_client
{
    uint16_t this_host;
    undefined field1_0x2;
    undefined field2_0x3;
    duss_result_t (*msg_cb)(struct duss_mb_client *, uint16_t, uint16_t, duss_msg_attrib_t, duss_msg_id_t, uint8_t *, int32_t, void *);
    void *msg_cb_userdata;
    duss_result_t (*filter_cb)(struct duss_mb_client *, struct duss_mb_route_item_t *, uint16_t, uint16_t, uint16_t, duss_msg_attrib_t, duss_msg_id_t, uint8_t *, int32_t, void *);
    void *filter_cb_userdata;
    struct duss_mb_route_table_t *route_table;
    struct duss_osal_mutex_handle_t *lock;
    struct duss_osal_task_handle_t *task;
    int fd_max;
    struct fd_set fds;
    _Bool finish;
    undefined field13_0xa5;
    undefined field14_0xa6;
    undefined field15_0xa7;
    int channel_num;
    void *channel[32];
    int target_num;
    void *target[64];
};

struct AVPacket
{
    struct AVBufferRef *buf;
    undefined field1_0x4;
    undefined field2_0x5;
    undefined field3_0x6;
    undefined field4_0x7;
    int64_t pts;
    int64_t dts;
    uint8_t *data;
    int size;
    int stream_index;
    int flags;
    struct AVPacketSideData *side_data;
    int side_data_elems;
    int duration;
    void (*destruct)(struct AVPacket *);
    void *priv;
    undefined field16_0x3c;
    undefined field17_0x3d;
    undefined field18_0x3e;
    undefined field19_0x3f;
    int64_t pos;
    int64_t convergence_duration;
    _Bool is_last_section;
    undefined field23_0x51;
    undefined field24_0x52;
    undefined field25_0x53;
    int32_t nal_total_size;
};

struct icc_channel_addr
{
    char *obj_name;
    char *snd_chn;
    char *rcv_chn;
    struct duss_hal_icc_config_t cfg;
};

struct duss_mb_route_table_t
{
    void *priv_data;
    int target_size;
    struct duss_mb_route_item_t *targets[128];
};

struct AVCodecInternal
{
};

struct pl_decoder_t
{
    struct pl_decoder_itf_t *itf;
    void *context;
    struct AVRational time_base;
    void *me;
    _Bool running;
    undefined field5_0x15;
    undefined field6_0x16;
    undefined field7_0x17;
    struct duss_osal_msgq_handle_t *packet_queue;
    struct duss_osal_msgq_handle_t *frame_queue;
    struct duss_osal_task_handle_t *decode_task;
};

struct gs_local_panorama_info
{
    char file_path[256];
    uint8_t file_type;
    undefined field2_0x101;
    undefined field3_0x102;
    undefined field4_0x103;
    int gfxLayerFd;
};

struct duss_hal_i2c_config_t
{
    int baudrate;
    duss_i2c_addr_len_t addr_len;
    undefined field2_0x5;
    undefined field3_0x6;
    undefined field4_0x7;
};

struct duss_hal_storage_params
{
    enum duss_storage_client_type_t client_id;
    void *user_data;
    void (*callback)(struct duss_hal_storage_info *, void *);
};

struct AVBufferRef
{
    struct AVBuffer *buffer;
    uint8_t *data;
    int size;
};

struct sem_t
{
    uint count;
};

struct duss_osal_mutex_handle_t
{
    struct duss_osal_mutex_attrib_t attrib;
    struct sem_t sema;
};

struct stick_mode_self_define_t
{
    uint8_t ch_reverse : 1;
    uint8_t stick_channel : 7;
};

struct rc_set_stick_mode_pack_t
{
    uint8_t stick_mode;
    struct stick_mode_self_define_t ch_setup[0];
};

struct duss_osal_task_attrib_t
{
    char *name;
    duss_osal_task_entry_t entry;
    void *param;
    enum duss_osal_priority_t priority;
    uint32_t stack_size;
    uint32_t time_slice;
    _Bool detached;
    undefined field7_0x19;
    undefined field8_0x1a;
    undefined field9_0x1b;
    uint32_t affinity_mask;
};

struct SwrContext
{
};

struct AVHWAccel
{
    char *name;
    enum AVMediaType type;
    enum AVCodecID id;
    enum AVPixelFormat pix_fmt;
    int capabilities;
    struct AVHWAccel *next;
    int (*alloc_frame)(struct AVCodecContext *, struct AVFrame *);
    int (*start_frame)(struct AVCodecContext *, uint8_t *, uint32_t);
    int (*decode_slice)(struct AVCodecContext *, uint8_t *, uint32_t);
    int (*end_frame)(struct AVCodecContext *);
    int frame_priv_data_size;
    void (*decode_mb)(struct MpegEncContext *);
    int (*init)(struct AVCodecContext *);
    int (*uninit)(struct AVCodecContext *);
    int priv_data_size;
};

struct netlink_channel_addr
{
    uint16_t host_pid;
    uint16_t group;
    uint16_t target_pid;
};

struct duss_hal_uart_config_t
{
    int baudrate;
    duss_uart_parity_t parity;
    duss_uart_stopbit_t stopbit;
    duss_uart_wordlen_t wordlen;
    undefined field4_0x7;
};

struct uart_channel_addr
{
    char *obj_name;
    struct duss_hal_uart_config_t cfg;
};

struct usb_channel_addr
{
    char *device;
    uint32_t vid;
    uint32_t pid;
    uint16_t interface;
    uint16_t altsetting;
    uint8_t in_ep;
    uint8_t out_ep;
    undefined field7_0x12;
    undefined field8_0x13;
};

struct duss_hal_spi_config_t
{
    int mode;
    int baudrate;
    int lsb_first;
    int bits_per_word;
};

struct spi_channel_addr
{
    char *obj_name;
    struct duss_hal_spi_config_t cfg;
};

struct duss_hal_can_config_t
{
    duss_mb_can_chip_t chip;
    undefined field1_0x1;
    undefined field2_0x2;
    undefined field3_0x3;
    uint32_t baudrate;
    duss_mb_host_id_t target;
    undefined field6_0xa;
    undefined field7_0xb;
    uint32_t rx;
    uint32_t tx;
};

struct can_channel_addr
{
    char *obj_name;
    struct duss_hal_can_config_t cfg;
};

struct duss_hal_bulk_config_t
{
};

struct bulk_channel_addr
{
    char *obj_name;
    struct duss_hal_bulk_config_t cfg;
};

struct i2c_channel_addr
{
    char *obj_name;
    struct duss_hal_i2c_config_t cfg;
};

union anon_union_conflict1232_for_channel
{
    struct loc_channel_addr local;
    struct ip_channel_addr ip;
    struct wl_channel_addr wl;
    struct uart_channel_addr uart;
    struct can_channel_addr can;
    struct i2c_channel_addr i2c;
    struct spi_channel_addr spi;
    struct hpi_channel_addr hpi;
    struct usb_channel_addr usb;
    struct usbacc_channel_addr usbacc;
    struct icc_channel_addr icc;
    struct netlink_channel_addr netlink;
    struct bulk_channel_addr bulk;
};

struct AVPicture
{
    uint8_t *data[8];
    int linesize[8];
};

struct debug_cp_osd_info
{
    debug_osd_item_t items[4];
    int n_items;
};

struct AVDictionary
{
};

struct duss_hal_mem_param_t
{
    uint32_t reserved;
};

struct ion_info
{
    duss_hal_obj_handle_t mem_obj;
    struct duss_hal_mem_config_t mem_cfg;
    struct duss_hal_mem_param_t mem_param;
    duss_hal_mem_handle_t ion_buf;
    void *ion_virt_addr;
    uint32_t ion_len;
    struct duss_osal_mutex_handle_t *ion_mutex;
    uint32_t start_addr;
    uint32_t stop_addr;
    uint32_t size_waste;
};

struct audio_resampler_t
{
    struct SwrContext *swr_ctx;
    int src_rate;
    int dst_rate;
    int src_nb_channels;
    int dst_nb_channels;
    enum AVSampleFormat src_sample_fmt;
    enum AVSampleFormat dst_sample_fmt;
};

struct pcm
{
    int fd;
    uint flags;
    uint running : 1;
    uint prepared : 1;
    undefined field4_0x9;
    undefined field5_0xa;
    undefined field6_0xb;
    int underruns;
    uint buffer_size;
    uint boundary;
    char error[128];
    struct pcm_config config;
    struct snd_pcm_mmap_status *mmap_status;
    struct snd_pcm_mmap_control *mmap_control;
    struct snd_pcm_sync_ptr *sync_ptr;
    void *mmap_buffer;
    uint noirq_frames_per_msec;
    int wait_for_avail_min;
    struct timespec tstamp;
    int (*ev_callback)(int, void *);
    void *ev_params;
    char ev_running;
    undefined field22_0xed;
    undefined field23_0xee;
    undefined field24_0xef;
    pthread_t ev_thread;
    char chg_3le_to_le;
    undefined field27_0xf5;
    undefined field28_0xf6;
    undefined field29_0xf7;
    char *buffer_4le;
    uint size_4le;
};

struct duss_mb_filter_t
{
    uint16_t source;
    uint16_t target;
    duss_msg_id_t msg_id;
    duss_msg_attrib_t attrib;
    undefined field4_0xa;
    undefined field5_0xb;
};

struct duss_hal_obj_dev_t
{
    char *name;
    duss_hal_state_t obj_state;
    duss_hal_class_t obj_class;
    uint16_t obj_index;
    int32_t obj_refcnt;
    struct duss_osal_mutex_handle_t *obj_lock;
    struct duss_osal_mutex_handle_t *app_lock;
    duss_result_t (*open)(duss_hal_obj_handle_t, void *);
    duss_result_t (*close)(duss_hal_obj_handle_t);
    duss_result_t (*set_cfg)(duss_hal_obj_handle_t, void *);
    duss_result_t (*get_cfg)(duss_hal_obj_handle_t, void *);
    duss_result_t (*start)(duss_hal_obj_handle_t, void *);
    duss_result_t (*stop)(duss_hal_obj_handle_t, void *);
};

struct duss_hal_obj
{
    struct duss_hal_obj_dev_t dev;
    void *dev_class;
    void *dev_priv;
};

struct duss_event
{
    duss_msg_id_t msg_id;
    uint16_t peer_host;
    duss_msg_attrib_t attrib;
    uint16_t seq_id;
    undefined field4_0xa;
    undefined field5_0xb;
    uint32_t msg_len;
    uint8_t msg_buf[0];
};

struct common_cmd_ops
{
    int (*send_common_cmd)(void *, gs_common_cmd_t *, _Bool);
};

struct local_playback_ops
{
    int (*open)(void *, char *);
    int (*close)(void *);
    int (*stop)(void *);
    int (*pause)(void *);
    int (*resume)(void *);
    int (*seek)(void *, uint32_t);
    int (*seek_time)(void *, uint32_t);
    int (*get_duration)(char *, uint32_t *);
    int (*get_cur_time)(void *, uint32_t *, uint32_t *);
    int (*get_state)(void *, uint32_t *);
    int (*get_file_info)(char *, vdec_video_file_info_t *);
    int (*is_playing)(void *, _Bool *);
    int (*delete_file)(char *);
};

struct rc_ops
{
    int (*get_version)(void *, char *, char *, int8_t *);
    int (*get_version_async)(void *);
    int (*set_subtrim)(void *, uint8_t, int16_t);
    int (*set_subtrim_async)(void *, uint8_t, int16_t);
    int (*get_subtrim)(void *, struct rc_set_all_st_t *, int8_t *);
    int (*get_subtrim_async)(void *);
    int (*set_reverse)(void *, uint8_t, uint8_t);
    int (*get_reverse)(void *, union rc_set_reverse_t *, int8_t *);
    int (*get_reverse_async)(void *);
    int (*set_endpoint)(void *, uint8_t, uint8_t, uint8_t);
    int (*set_endpoint_async)(void *, uint8_t, uint8_t, uint8_t);
    int (*get_endpoint)(void *, struct rc_set_all_ep_t *, int8_t *);
    int (*get_endpoint_async)(void *);
    int (*set_func_mode)(void *, uint8_t, uint8_t, uint8_t);
    int (*get_func_mode)(void *, struct rc_set_function_pack_t *);
    int (*set_stick_mode)(void *, uint8_t);
    int (*get_stick_mode)(void *, struct rc_set_stick_mode_pack_t *, int8_t *);
    int (*get_stick_mode_ext)(void *, uint8_t *);
    int (*get_stick_mode_async)(void *);
    int (*set_stick_cali)(void *, uint8_t, uint8_t, uint8_t *);
    int (*get_stick_cali)(void *, uint8_t, int8_t *, int8_t *, int8_t *, int8_t *);
    int (*set_warning)(void *, struct rc_set_warning_mode_pack_t);
    int (*get_warning)(void *, struct rc_set_warning_mode_pack_t *);
    int (*monitor)(void *, struct rc_monitor_pack_t *);
    int (*reset_all_get_status)(void *);
    int (*reset_default_async)(void *, uint8_t);
    uint8_t (*get_lock_state)(void *);
    uint8_t (*get_link_state)(void *);
};

struct __gs_gui_config
{
    gs_queue_t *osd_gen_data_queue;
    gs_queue_t *osd_home_data_queue;
    gs_queue_t *file_del_queue;
    gs_queue_t *camera_stat_queue;
    gs_queue_t *camera_cap_param_queue;
    gs_queue_t *camera_pb_param_queue;
    gs_queue_t *camera_file_info_queue;
    gs_queue_t *camera_dcf_abstract_queue;
    gs_queue_t *camera_fov_param_queue;
    gs_queue_t *rc_bat_stat_queue;
    gs_queue_t *signal_quality_queue;
    gs_queue_t *uav_bat_common_info_queue;
    gs_queue_t *sdr_wl_env_queue;
    gs_queue_t *sdr_uav_data_queue;
    gs_queue_t *sdr_gnd_data_queue;
    gs_queue_t *rc_param_queue;
    gs_queue_t *rc_pushed_gps_queue;
    gs_queue_t *racing_drone_fc_osd_queue;
    _Bool *touchpadLockState;
    void *ctx;
    ext_fc_ops_t ext_fc_ops;
    vr_device_ops_t vdev_ops;
    local_playback_ops_t local_pb_ops;
    uav_camera_ops_t uav_cam_ops;
    uav_gimbal_ops_t gimbal_ops;
    modem_ops_t modem_ops;
    rc_ops_t rc_ops;
    vcm_ops_t vcm_ops;
    common_cmd_ops_t cmn_cmd_ops;
    int (*get_codec_debug_osd_info)(void *, debug_codec_osd_info_t *);
    int (*get_cam_debug_osd_info)(void *, debug_cam_osd_info_t *);
    int (*get_temp_debug_osd_info)(void *, debug_temp_osd_info_t *);
    int (*get_uav_max_temp)(void *, int32_t *);
    int (*get_cp_debug_osd_info)(void *, debug_cp_osd_info_t *);
    int (*set_racing_enc_strategy)(void *, uint8_t);
    int (*is_camera_in_record)(void *, int *);
    int (*get_cparm_version)(void *, char *);
    int (*get_dsp_version)(void *, char *);
    int (*get_flight_time)(void *, uint64_t *);
    int (*get_arm_status)(void *, uint8_t *);
    int (*clear_adb_log_info)(void *);
    int (*reset_camera_param)(void *);
    int (*set_low_power_mode)(void *, _Bool);
    int (*get_uav_version)(void *, char *, char *);
    int (*get_uav_hardware_version)(void *, char *);
    int (*get_uav_power_status)(void *, uint8_t *, uint8_t *);
    int (*get_uav_camera_type)(void *, uint8_t *);
    int (*get_liveview_fps)(void *, uint8_t *);
    int (*fbdev_open)(void);
    int (*fbdev_disp_frame)(int);
    int (*fbdev_close)(void);
    int (*record_liveview)(void *, _Bool);
    int (*get_liveview_state)(void *, int *);
    record_mode_t (*get_liveview_record_mode)(void *);
    int (*set_liveview_record_mode)(void *, record_mode_t);
    int (*get_liveview_record_enable)(void *);
    int (*set_liveview_record_enable)(void *, _Bool, enum Record_sender);
    int (*get_liveview_record_time)(void *, int *);
    int (*enable_audio_liveview)(void *, _Bool);
    int (*get_frame_delay_e2e)(void *, uint16_t *);
    int (*get_chnl_status)(void *, uint16_t *);
    int (*get_pigeon_battery_info)(void *, gs_battery_voltage_t *);
    int (*get_sd_status)(void *, int, uint8_t *, uint32_t *, uint32_t *);
    int (*play_pwm_buzzer)(void *, int, int, int);
    int (*buzzer_enable_bat)(void *, _Bool);
};

struct AVCodecParserContext
{
    void *priv_data;
    struct AVCodecParser *parser;
    int64_t frame_offset;
    int64_t cur_offset;
    int64_t next_frame_offset;
    int pict_type;
    int repeat_pict;
    int64_t pts;
    int64_t dts;
    int64_t last_pts;
    int64_t last_dts;
    int fetch_timestamp;
    int cur_frame_start_index;
    int64_t cur_frame_offset[4];
    int64_t cur_frame_pts[4];
    int64_t cur_frame_dts[4];
    int flags;
    undefined field17_0xb4;
    undefined field18_0xb5;
    undefined field19_0xb6;
    undefined field20_0xb7;
    int64_t offset;
    int64_t cur_frame_end[4];
    int key_frame;
    undefined field24_0xe4;
    undefined field25_0xe5;
    undefined field26_0xe6;
    undefined field27_0xe7;
    int64_t convergence_duration;
    int dts_sync_point;
    int dts_ref_dts_delta;
    int pts_dts_delta;
    undefined field32_0xfc;
    undefined field33_0xfd;
    undefined field34_0xfe;
    undefined field35_0xff;
    int64_t cur_frame_pos[4];
    int64_t pos;
    int64_t last_pos;
    int duration;
    enum AVFieldOrder field_order;
    enum AVPictureStructure picture_structure;
    int output_picture_number;
};

struct duss_osal_msgq_attrib_t
{
    char *name;
    uint32_t buf_size;
};

struct duss_osal_msgq_handle_t
{
    struct duss_osal_msgq_attrib_t attrib;
    struct pthread_mutex_t r_mutex;
    struct pthread_mutex_t s_mutex;
    struct pthread_cond_t r_cond;
    struct pthread_cond_t s_cond;
    uint32_t buf_size;
    uint32_t head;
    uint32_t tail;
    uint8_t *buffer;
};

struct duss_mb_route_item_t
{
    uint8_t status;
    char name[16];
    undefined field2_0x11;
    uint16_t target;
    duss_mb_channel_t access_channel;
    uint8_t distance;
    duss_mb_pack_ver_t pack_ver;
    undefined field7_0x17;
    union anon_union_conflict1232_for_channel channel;
    int filter_size;
    struct duss_mb_filter_t *filters;
};

struct rc_monitor_pack_t
{
    uint8_t channel_num;
    uint16_t channel_val[0];
};

struct AVFormatInternal
{
};

struct debug_osd_info
{
    debug_osd_item_t items[15];
    int n_items;
};

struct AVOptionRanges
{
    struct AVOptionRange **range;
    int nb_ranges;
    int nb_components;
};

struct snd_pcm_sync_ptr
{
};

union anon_union_conflictac8f4_for_default_val
{
    int64_t i64;
    double dbl;
    char *str;
    struct AVRational q;
};

struct gs_playback_listener
{
    void *ctx;
    int (*event_cb)(void *, playback_event_t);
};

struct gs_local_video_info
{
    char video_path[256];
    char audio_path[256];
};

union anon_union_conflict3b31_for_field_1
{
    _Bool plugin;
    uint8_t cam_workmode;
    uint8_t cam_pbmode;
    uint8_t cam_model;
    _Bool wl_link;
    gs_main_channel_id_t chnl_id;
    gs_video_channel_id_t sub_chnl_id;
    gs_local_video_info_t video_info;
    uint32_t video_index;
    _Bool is_pal;
    gs_local_panorama_info_t pano_info;
};

struct gs_video_channel_message
{
    enum gs_video_channel_message_id_t msg_id;
    union anon_union_conflict3b31_for_field_1 field_1;
};

struct snd_pcm_mmap_status
{
};

struct audio_dec
{
    void *gs_info;
    void *cb_ctx;
    int (*cb_func)(void *, dec_event_t);
    audio_pb_state_t audio_pb_state;
    int codec_id;
    int sample_rate;
    int channels;
    int sample_fmt;
    pl_decoder_handle_t hnd;
    struct pl_decoder_itf_t *itf;
    _Bool b_running;
    _Bool b_eos;
    undefined field12_0x2a;
    undefined field13_0x2b;
    struct duss_osal_task_handle_t *thread_dec;
    _Bool b_aout_running;
    undefined field16_0x31;
    undefined field17_0x32;
    undefined field18_0x33;
    struct duss_osal_task_handle_t *thread_aout;
    audio_resampler_ptr resampler;
    uint8_t *resample_buffer;
    int resample_buf_size;
    int frames_received;
    int frames_decoded;
    FILE *f_a_out;
    struct duss_osal_mutex_handle_t *list_mutex;
    struct duss_list_head frame_list;
    int num_in_list;
    struct duss_osal_mutex_handle_t *pcm_mutex;
    struct duss_list_head pcm_list;
    int num_pcm;
    _Bool b_started;
    undefined field33_0x71;
    undefined field34_0x72;
    undefined field35_0x73;
    struct timespec tstamp;
    int samples_played;
    _Bool b_first_frm_sent;
    undefined field39_0x81;
    undefined field40_0x82;
    undefined field41_0x83;
    undefined field42_0x84;
    undefined field43_0x85;
    undefined field44_0x86;
    undefined field45_0x87;
    int64_t play_tm_offset_ms;
    int64_t play_tm_ms;
};

struct AVCodecDefault
{
};

struct AVCodecTag
{
};

struct AVProgram
{
    int id;
    int flags;
    enum AVDiscard discard;
    uint *stream_index;
    uint nb_stream_indexes;
    struct AVDictionary *metadata;
    int program_num;
    int pmt_pid;
    int pcr_pid;
    undefined field9_0x24;
    undefined field10_0x25;
    undefined field11_0x26;
    undefined field12_0x27;
    int64_t start_time;
    int64_t end_time;
    int64_t pts_wrap_reference;
    int pts_wrap_behavior;
    undefined field17_0x44;
    undefined field18_0x45;
    undefined field19_0x46;
    undefined field20_0x47;
};

struct AVInputFormat
{
    char *name;
    char *long_name;
    int flags;
    char *extensions;
    struct AVCodecTag **codec_tag;
    struct AVClass *priv_class;
    char *mime_type;
    struct AVInputFormat *next;
    int raw_codec_id;
    int priv_data_size;
    int (*read_probe)(struct AVProbeData *);
    int (*read_header)(struct AVFormatContext *);
    int (*read_packet)(struct AVFormatContext *, struct AVPacket *);
    int (*read_close)(struct AVFormatContext *);
    int (*read_seek)(struct AVFormatContext *, int, int64_t, int);
    int64_t (*read_timestamp)(struct AVFormatContext *, int, int64_t *, int64_t);
    int (*read_play)(struct AVFormatContext *);
    int (*read_pause)(struct AVFormatContext *);
    int (*read_seek2)(struct AVFormatContext *, int, int64_t, int64_t, int64_t, int);
    int (*get_device_list)(struct AVFormatContext *, struct AVDeviceInfoList *);
    int (*create_device_capabilities)(struct AVFormatContext *, struct AVDeviceCapabilitiesQuery *);
    int (*free_device_capabilities)(struct AVFormatContext *, struct AVDeviceCapabilitiesQuery *);
};

struct anon_struct_conflict69b3c_for_info
{
    int64_t last_dts;
    int64_t duration_gcd;
    int duration_count;
    undefined field3_0x14;
    undefined field4_0x15;
    undefined field5_0x16;
    undefined field6_0x17;
    int64_t rfps_duration_sum;
    double *duration_error[2][373];
    undefined field9_0x24;
    undefined field10_0x25;
    undefined field11_0x26;
    undefined field12_0x27;
    int64_t codec_info_duration;
    int64_t codec_info_duration_fields;
    int found_decoder;
    undefined field16_0x3c;
    undefined field17_0x3d;
    undefined field18_0x3e;
    undefined field19_0x3f;
    int64_t last_duration;
    int64_t fps_first_dts;
    int fps_first_dts_idx;
    undefined field23_0x54;
    undefined field24_0x55;
    undefined field25_0x56;
    undefined field26_0x57;
    int64_t fps_last_dts;
    int fps_last_dts_idx;
    undefined field29_0x64;
    undefined field30_0x65;
    undefined field31_0x66;
    undefined field32_0x67;
};

struct duss_storage_client
{
    _Bool start_flag;
    undefined field1_0x1;
    undefined field2_0x2;
    undefined field3_0x3;
    struct duss_hal_storage_params param;
    struct duss_hal_storage_info info;
};

struct duss_osal_timer_handle_t
{
    struct duss_osal_timer_attrib_t attrib;
    pthread_t thread;
    int32_t repeat_cnt;
    _Bool suspend;
    _Bool restart;
    undefined field5_0x22;
    undefined field6_0x23;
    struct sem_t sema;
    struct sem_t lock;
    struct timespec saved_time;
};

struct rc_set_warning_mode_pack_t
{
    uint8_t ext_flag : 1;
    uint8_t warning_tid : 4;
    uint8_t warning_mode : 3;
    uint16_t ext_val;
};

struct AVClass
{
    char *class_name;
    char *(*item_name)(void *);
    struct AVOption *option;
    int version;
    int log_level_offset_offset;
    int parent_log_context_offset;
    void *(*child_next)(void *, void *);
    AVClass *(*child_class_next)(struct AVClass *);
    enum AVClassCategory category;
    AVClassCategory (*get_category)(void *);
    int (*query_ranges)(struct AVOptionRanges **, void *, char *, int);
};

struct AVIOInterruptCB
{
    int (*callback)(void *);
    void *opaque;
};

struct AVPacketSideData
{
    uint8_t *data;
    int size;
    enum AVPacketSideDataType type;
};

struct product_shm_info
{
    uint16_t frm_width;
    uint16_t frm_height;
    uint8_t fps;
    uint8_t enc_strategy;
    uint16_t lcdc_underflow_cnt;
    uint32_t enc_sto_frm_dropped;
    uint32_t enc_lv_frm_dropped;
    uint32_t mipi_csi_frm_dropped;
    uint32_t display_frm_dropped;
    uint64_t audio_pts;
    uint32_t local_fps_num;
    uint32_t local_fps_den;
    uint16_t frame_delay_e2e;
    uint16_t cam_frame_interval;
    uint16_t outliner_frame_interval;
    uint16_t outliner_frame_interval_cnt;
    uint16_t max_frame_delay_e2e;
    uint16_t min_frame_delay_e2e;
    uint16_t avg_frame_delay_e2e;
    uint16_t if_switch;
    uint8_t if_change_pipe;
    uint8_t if_pb_pause;
    uint8_t liveview_pipeline_running;
    uint8_t avIn_pipeline_running;
    uint8_t avIn_stream_type;
    uint8_t pb_flush;
    uint8_t disp_pannel_need_reset;
    undefined field27_0x3f;
};

struct debug_temp_osd_info
{
    debug_osd_item_t items[11];
    int n_items;
};

struct pl_muxer_itf_t
{
    int (*create)(p1_muxer_handle_t *, void *, void *);
    int (*destroy)(p1_muxer_handle_t);
    int (*prepare)(p1_muxer_handle_t);
    int (*release)(p1_muxer_handle_t);
    int (*add_stream)(p1_muxer_handle_t, enum AVCodecID, void *);
    int (*write)(p1_muxer_handle_t, void *, uint32_t, int);
    void *(*get_stream)(p1_muxer_handle_t, uint);
    int (*config_stream)(p1_muxer_handle_t, enum pl_muxer_config_index_t, void *);
};

struct AVFrame
{
    uint8_t *data[8];
    int linesize[8];
    uint8_t **extended_data;
    int width;
    int height;
    int nb_samples;
    int format;
    int key_frame;
    enum AVPictureType pict_type;
    uint8_t *base[8];
    struct AVRational sample_aspect_ratio;
    undefined field11_0x84;
    undefined field12_0x85;
    undefined field13_0x86;
    undefined field14_0x87;
    int64_t pts;
    int64_t pkt_pts;
    int64_t pkt_dts;
    int coded_picture_number;
    int display_picture_number;
    int quality;
    int reference;
    int8_t *qscale_table;
    int qstride;
    int qscale_type;
    uint8_t *mbskip_table;
    int16_t *motion_val[2];
    uint32_t *mb_type;
    short *dct_coeff;
    int8_t *ref_index[2];
    void *opaque;
    undefined field31_0xdc;
    undefined field32_0xdd;
    undefined field33_0xde;
    undefined field34_0xdf;
    uint64_t error[8];
    int type;
    int repeat_pict;
    int interlaced_frame;
    int top_field_first;
    int palette_has_changed;
    int buffer_hints;
    struct AVPanScan *pan_scan;
    undefined field43_0x13c;
    undefined field44_0x13d;
    undefined field45_0x13e;
    undefined field46_0x13f;
    int64_t reordered_opaque;
    void *hwaccel_picture_private;
    struct AVCodecContext *owner;
    void *thread_opaque;
    uint8_t motion_subsample_log2;
    undefined field52_0x155;
    undefined field53_0x156;
    undefined field54_0x157;
    int sample_rate;
    undefined field56_0x15c;
    undefined field57_0x15d;
    undefined field58_0x15e;
    undefined field59_0x15f;
    uint64_t channel_layout;
    struct AVBufferRef *buf[8];
    struct AVBufferRef **extended_buf;
    int nb_extended_buf;
    struct AVFrameSideData **side_data;
    int nb_side_data;
    int flags;
    enum AVColorRange color_range;
    enum AVColorPrimaries color_primaries;
    enum AVColorTransferCharacteristic color_trc;
    enum AVColorSpace colorspace;
    enum AVChromaLocation chroma_location;
    int64_t best_effort_timestamp;
    int64_t pkt_pos;
    int64_t pkt_duration;
    struct AVDictionary *metadata;
    int decode_error_flags;
    int channels;
    int pkt_size;
    struct AVBufferRef *qp_table_buf;
    undefined field80_0x1dc;
    undefined field81_0x1dd;
    undefined field82_0x1de;
    undefined field83_0x1df;
};

struct vdec_local_player
{
    gs_playback_listener_t pb_listener;
    void *gs_info;
    uint32_t state;
    uint32_t cur_time;
    _Bool b_pending_seek;
    undefined field5_0x15;
    undefined field6_0x16;
    undefined field7_0x17;
    uint32_t seek_pos;
    struct AVFormatContext *fmt_ctx;
    _Bool b_f_eof;
    undefined field11_0x21;
    undefined field12_0x22;
    undefined field13_0x23;
    int audio_stream_index;
    audio_dec_t *adec;
    _Bool b_a_eos;
    undefined field17_0x2d;
    undefined field18_0x2e;
    undefined field19_0x2f;
    int video_stream_index;
    cp_vdec_t *vdec;
    _Bool b_v_eos;
    _Bool b_running;
    undefined field24_0x3a;
    undefined field25_0x3b;
    struct duss_osal_task_handle_t *task_player;
    struct duss_osal_mutex_handle_t *vmutex;
    vdec_video_file_info_t file_info;
    int64_t first_pts;
};

struct AVDeviceInfoList
{
};

struct AVCodecDescriptor
{
    enum AVCodecID id;
    enum AVMediaType type;
    char *name;
    char *long_name;
    int props;
    char **mime_types;
};

struct AVFormatContext
{
    struct AVClass *av_class;
    struct AVInputFormat *iformat;
    struct AVOutputFormat *oformat;
    void *priv_data;
    struct AVIOContext *pb;
    int ctx_flags;
    uint nb_streams;
    struct AVStream **streams;
    char filename[1024];
    int64_t start_time;
    int64_t duration;
    int bit_rate;
    uint packet_size;
    int max_delay;
    int flags;
    uint probesize;
    int max_analyze_duration;
    uint8_t *key;
    int keylen;
    uint nb_programs;
    struct AVProgram **programs;
    enum AVCodecID video_codec_id;
    enum AVCodecID audio_codec_id;
    enum AVCodecID subtitle_codec_id;
    uint max_index_size;
    uint max_picture_buffer;
    uint nb_chapters;
    struct AVChapter **chapters;
    struct AVDictionary *metadata;
    int64_t start_time_realtime;
    int fps_probe_size;
    int error_recognition;
    struct AVIOInterruptCB interrupt_callback;
    int debug;
    undefined field34_0x494;
    undefined field35_0x495;
    undefined field36_0x496;
    undefined field37_0x497;
    int64_t max_interleave_delta;
    int strict_std_compliance;
    int event_flags;
    int max_ts_probe;
    int avoid_negative_ts;
    int ts_id;
    int audio_preload;
    int max_chunk_duration;
    int max_chunk_size;
    int use_wallclock_as_timestamps;
    int avio_flags;
    enum AVDurationEstimationMethod duration_estimation_method;
    undefined field50_0x4cc;
    undefined field51_0x4cd;
    undefined field52_0x4ce;
    undefined field53_0x4cf;
    int64_t skip_initial_bytes;
    uint correct_ts_overflow;
    int seek2any;
    int flush_packets;
    int probe_score;
    int format_probesize;
    char *codec_whitelist;
    char *format_whitelist;
    struct AVPacketList *packet_buffer;
    struct AVPacketList *packet_buffer_end;
    undefined field64_0x4fc;
    undefined field65_0x4fd;
    undefined field66_0x4fe;
    undefined field67_0x4ff;
    int64_t data_offset;
    struct AVPacketList *raw_packet_buffer;
    struct AVPacketList *raw_packet_buffer_end;
    struct AVPacketList *parse_queue;
    struct AVPacketList *parse_queue_end;
    int raw_packet_buffer_remaining_size;
    undefined field74_0x51c;
    undefined field75_0x51d;
    undefined field76_0x51e;
    undefined field77_0x51f;
    int64_t offset;
    struct AVRational offset_timebase;
    struct AVFormatInternal *internal;
    int io_repositioned;
    struct AVCodec *video_codec;
    struct AVCodec *audio_codec;
    struct AVCodec *subtitle_codec;
    int metadata_header_padding;
    void *opaque;
    int (*control_message_cb)(struct AVFormatContext *, int, void *, size_t);
    int64_t output_ts_offset;
    int64_t max_analyze_duration2;
    int64_t probesize2;
    uint8_t *dump_separator;
    undefined field92_0x56c;
    undefined field93_0x56d;
    undefined field94_0x56e;
    undefined field95_0x56f;
};

struct duss_event_client
{
    uint16_t this_host;
    undefined field1_0x2;
    undefined field2_0x3;
    duss_mb_client_handle_t mb_client_obj;
    struct duss_osal_msgq_handle_t *msgq;
    struct duss_osal_task_handle_t *task;
    struct duss_osal_mutex_handle_t *wait_ack_mutex;
    struct duss_osal_event_handle_t *wait_ack_event;
    duss_event_ack_identify_t wait_ack_list[32];
    uint32_t wait_ack_cnt;
    _Bool finish;
    undefined field11_0x29d;
    undefined field12_0x29e;
    undefined field13_0x29f;
    duss_event_cmd_desc_t *cmd_desc_tbl[79];
    uint32_t cmd_desc_num[79];
    void *userdata;
};

struct MpegEncContext
{
};

struct AVPacketList
{
    struct AVPacket pkt;
    struct AVPacketList *next;
    undefined field2_0x5c;
    undefined field3_0x5d;
    undefined field4_0x5e;
    undefined field5_0x5f;
};

struct AVProbeData
{
    char *filename;
    uchar *buf;
    int buf_size;
    char *mime_type;
};

struct AVStream
{
    int index;
    int id;
    struct AVCodecContext *codec;
    void *priv_data;
    struct AVFrac pts;
    struct AVRational time_base;
    int64_t start_time;
    int64_t duration;
    int64_t nb_frames;
    int disposition;
    enum AVDiscard discard;
    struct AVRational sample_aspect_ratio;
    struct AVDictionary *metadata;
    struct AVRational avg_frame_rate;
    undefined field14_0x64;
    undefined field15_0x65;
    undefined field16_0x66;
    undefined field17_0x67;
    struct AVPacket attached_pic;
    struct AVPacketSideData *side_data;
    int nb_side_data;
    int event_flags;
    struct anon_struct_conflict69b3c_for_info *info;
    int pts_wrap_bits;
    undefined field24_0xd4;
    undefined field25_0xd5;
    undefined field26_0xd6;
    undefined field27_0xd7;
    int64_t first_dts;
    int64_t cur_dts;
    int64_t last_IP_pts;
    int last_IP_duration;
    int probe_packets;
    int codec_info_nb_frames;
    enum AVStreamParseType need_parsing;
    struct AVCodecParserContext *parser;
    struct AVPacketList *last_in_packet_buffer;
    struct AVProbeData probe_data;
    int64_t pts_buffer[17];
    struct AVIndexEntry *index_entries;
    int nb_index_entries;
    uint index_entries_allocated_size;
    struct AVRational r_frame_rate;
    int stream_identifier;
    int64_t interleaver_chunk_size;
    int64_t interleaver_chunk_duration;
    int request_probe;
    int skip_to_keyframe;
    int skip_samples;
    undefined field49_0x1d4;
    undefined field50_0x1d5;
    undefined field51_0x1d6;
    undefined field52_0x1d7;
    int64_t first_discard_sample;
    int64_t last_discard_sample;
    int nb_decoded_frames;
    undefined field56_0x1ec;
    undefined field57_0x1ed;
    undefined field58_0x1ee;
    undefined field59_0x1ef;
    int64_t mux_ts_offset;
    int64_t pts_wrap_reference;
    int pts_wrap_behavior;
    int update_initial_durations_done;
    int64_t pts_reorder_error[17];
    uint8_t pts_reorder_error_count[17];
    undefined field66_0x2a1;
    undefined field67_0x2a2;
    undefined field68_0x2a3;
    undefined field69_0x2a4;
    undefined field70_0x2a5;
    undefined field71_0x2a6;
    undefined field72_0x2a7;
    int64_t last_dts_for_order_check;
    uint8_t dts_ordered;
    uint8_t dts_misordered;
    undefined field76_0x2b2;
    undefined field77_0x2b3;
    int inject_global_side_data;
    char *recommended_encoder_configuration;
    struct AVRational display_aspect_ratio;
    undefined field81_0x2c4;
    undefined field82_0x2c5;
    undefined field83_0x2c6;
    undefined field84_0x2c7;
};

struct duss_hal_mem_buf
{
};

struct AVSubtitleRect
{
    int x;
    int y;
    int w;
    int h;
    int nb_colors;
    struct AVPicture pict;
    enum AVSubtitleType type;
    char *text;
    char *ass;
    int flags;
};

struct AVIOContext
{
    struct AVClass *av_class;
    uchar *buffer;
    int buffer_size;
    uchar *buf_ptr;
    uchar *buf_end;
    void *opaque;
    int (*read_packet)(void *, uint8_t *, int);
    int (*write_packet)(void *, uint8_t *, int);
    int64_t (*seek)(void *, int64_t, int);
    undefined field9_0x24;
    undefined field10_0x25;
    undefined field11_0x26;
    undefined field12_0x27;
    int64_t pos;
    int must_flush;
    int eof_reached;
    int write_flag;
    int max_packet_size;
    ulong checksum;
    uchar *checksum_ptr;
    ulong (*update_checksum)(ulong, uint8_t *, uint);
    int error;
    int (*read_pause)(void *, int);
    int64_t (*read_seek)(void *, int, int64_t, int);
    int seekable;
    undefined field25_0x5c;
    undefined field26_0x5d;
    undefined field27_0x5e;
    undefined field28_0x5f;
    int64_t maxsize;
    int direct;
    undefined field31_0x6c;
    undefined field32_0x6d;
    undefined field33_0x6e;
    undefined field34_0x6f;
    int64_t bytes_read;
    int seek_count;
    int writeout_count;
    int orig_buffer_size;
    undefined field39_0x84;
    undefined field40_0x85;
    undefined field41_0x86;
    undefined field42_0x87;
};

struct AVOption
{
    char *name;
    char *help;
    int offset;
    enum AVOptionType type;
    union anon_union_conflictac8f4_for_default_val default_val;
    double min;
    double max;
    int flags;
    char *unit;
};

struct AVSubtitle
{
    uint16_t format;
    undefined field1_0x2;
    undefined field2_0x3;
    uint32_t start_display_time;
    uint32_t end_display_time;
    uint num_rects;
    struct AVSubtitleRect **rects;
    undefined field7_0x14;
    undefined field8_0x15;
    undefined field9_0x16;
    undefined field10_0x17;
    int64_t pts;
};

struct duss_osal_task_handle_t
{
    struct duss_osal_task_attrib_t attrib;
    pthread_t thread;
};

struct modem_shmem_info_t
{
    uint32_t frm_idx;
    uint16_t frm_isI;
    uint16_t frm_len;
    uint16_t frm_dsti;
    uint16_t frm_dstf;
    uint16_t channel_status;
    uint16_t dec_err_status;
    uint16_t cur_time;
    uint16_t delta_time;
    uint16_t dbg_msc;
    uint8_t dbg_ap_ready;
    uint8_t dbg_cp_ready;
    uint32_t local_id;
    uint8_t cp_state;
    uint8_t cp_report;
    uint8_t cp_report_seq;
    uint8_t client_type;
    uint32_t cp_boot_status0;
    uint32_t cp_boot_status1;
    uint32_t board_version;
    uint32_t board_sub_version;
    uint8_t machine_role;
    uint8_t is_reverse;
    int8_t cp_tx_power;
    uint8_t gnd_type;
    uint32_t cp_sssfn;
    uint32_t ulow_en;
    uint8_t mipi_rx_response;
    uint8_t liveview_broken_status;
    uint8_t reserved01;
    uint8_t reserved02;
    uint8_t ap_reboot_flag;
    uint8_t ap_reboot_ack_flag;
    uint8_t secure_sync_flag;
    uint8_t reserve00;
    uint8_t area_state;
    uint8_t area_substate;
    uint8_t GsCtrl;
    uint8_t GsSubState;
    uint8_t WaterLevel[4];
    uint16_t RxCntStastic[4];
    uint16_t TxCntStastic[4];
    uint8_t Reserved[8];
    uint32_t com_uart_status;
    uint32_t fcr_rx_status;
    uint32_t fcr_tx_status;
    uint32_t frm_idx_for_display;
    uint32_t frm_delay_for_display;
    uint16_t wifi_sdr_mode;
    uint16_t frm_isI_for_display;
    uint32_t country_code;
    uint16_t frm_len_for_display;
    uint16_t delta_time_for_display;
    uint8_t uint8_t_reboot_reason;
    undefined field54_0x85;
    undefined field55_0x86;
    undefined field56_0x87;
    uint64_t cpa7_version;
    uint64_t dsp_version;
    uint8_t u8_dual_band_capability;
    undefined field60_0x99;
    undefined field61_0x9a;
    undefined field62_0x9b;
    undefined field63_0x9c;
    undefined field64_0x9d;
    undefined field65_0x9e;
    undefined field66_0x9f;
};

struct sqlite3
{
};

struct cp_vdec
{
    void *gs_info;
    uint32_t width;
    uint32_t height;
    void *cb_ctx;
    int (*cb_func)(void *, dec_event_t);
    vdec_state_t vdec_state;
    _Bool b_running;
    _Bool b_eos;
    _Bool b_first_frm_sent;
    undefined field9_0x1b;
    gs_media_cmd_chnl_t *mcc;
    int dmi_data_fd;
    struct duss_osal_task_handle_t *thread_tx;
    int frames_received;
    int frames_sent;
    struct duss_osal_mutex_handle_t *list_mutex;
    struct duss_list_head frame_list;
    int num_in_list;
    int64_t play_tm_ms;
};

struct AVOutputFormat
{
    char *name;
    char *long_name;
    char *mime_type;
    char *extensions;
    enum AVCodecID audio_codec;
    enum AVCodecID video_codec;
    enum AVCodecID subtitle_codec;
    int flags;
    struct AVCodecTag **codec_tag;
    struct AVClass *priv_class;
    struct AVOutputFormat *next;
    int priv_data_size;
    int (*write_header)(struct AVFormatContext *);
    int (*write_packet)(struct AVFormatContext *, struct AVPacket *);
    int (*write_trailer)(struct AVFormatContext *);
    int (*interleave_packet)(struct AVFormatContext *, struct AVPacket *, struct AVPacket *, int);
    int (*query_codec)(enum AVCodecID, int);
    void (*get_output_timestamp)(struct AVFormatContext *, int, int64_t *, int64_t *);
    int (*control_message)(struct AVFormatContext *, int, void *, size_t);
    int (*write_uncoded_frame)(struct AVFormatContext *, int, struct AVFrame **, uint);
    int (*get_device_list)(struct AVFormatContext *, struct AVDeviceInfoList *);
    int (*create_device_capabilities)(struct AVFormatContext *, struct AVDeviceCapabilitiesQuery *);
    int (*free_device_capabilities)(struct AVFormatContext *, struct AVDeviceCapabilitiesQuery *);
};

struct rc_set_function_pack_t
{
    uint8_t arm_channel : 2;
    uint8_t arm_setval : 2;
    uint8_t flip_channel : 2;
    uint8_t flip_setval : 2;
};

struct pl_muxer_t
{
    struct pl_muxer_itf_t *itf;
    void *context;
    void *me;
};

struct AVCodec
{
    char *name;
    char *long_name;
    enum AVMediaType type;
    enum AVCodecID id;
    int capabilities;
    struct AVRational *supported_framerates;
    enum AVPixelFormat *pix_fmts;
    int *supported_samplerates;
    enum AVSampleFormat *sample_fmts;
    uint64_t *channel_layouts;
    uint8_t max_lowres;
    undefined field11_0x29;
    undefined field12_0x2a;
    undefined field13_0x2b;
    struct AVClass *priv_class;
    struct AVProfile *profiles;
    int priv_data_size;
    struct AVCodec *next;
    int (*init_thread_copy)(struct AVCodecContext *);
    int (*update_thread_context)(struct AVCodecContext *, struct AVCodecContext *);
    struct AVCodecDefault *defaults;
    void (*init_static_data)(struct AVCodec *);
    int (*init)(struct AVCodecContext *);
    int (*encode_sub)(struct AVCodecContext *, uint8_t *, int, struct AVSubtitle *);
    int (*encode2)(struct AVCodecContext *, struct AVPacket *, struct AVFrame *, int *);
    int (*decode)(struct AVCodecContext *, void *, int *, struct AVPacket *);
    int (*close)(struct AVCodecContext *);
    void (*flush)(struct AVCodecContext *);
};

struct snd_pcm_mmap_control
{
};
