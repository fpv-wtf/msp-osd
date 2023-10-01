#include <time.h>


typedef struct GlassRacingChnlUI GlassRacingChnlUI, *PGlassRacingChnlUI;
typedef struct GlassRacingChnlUI GlassRacingChnlUI_t;

struct GlassRacingChnlUI {
	char dummy[0x4a0];
	float gs_voltage;
	char dummy2[0xa];
	uint16_t gs_bitrate;
	char dummy3[0x200]; //ends at 0x6b0

}__attribute__((packed, aligned(1)));

static GlassRacingChnlUI *chnl_ui;

typedef enum gs_link_stat_t {
    GS_LINK_STAT_NORMAL=0,
    GS_LINK_STAT_WEAK=1,
    GS_LINK_STAT_LOST=2,
    GS_LINK_STAT_UKNOWN=3
} gs_link_stat_t;

typedef enum Record_sender {
    RECORD_BUTTON=0,
    RECORD_DISARM=1
} Record_sender;

typedef enum record_state {
    RECORD_STATE_IDLE=0,
    RECORD_STATE_RECORDING=1,
    RECORD_STATE_STOP_ERROR=2,
    RECORD_STATE_STOP_FULL=3,
    RECORD_STATE_STOP_WRITE_SLOW=4,
    RECORD_STATE_STARTING=5,
    RECORD_STATE_STOPPING=6
} record_state;

typedef enum record_state record_state_t;

typedef struct __gs_queue __gs_queue, *P__gs_queue;
typedef struct __gs_queue gs_queue_t;

struct __gs_queue {
    uint32_t * addr;
    uint32_t size;
    uint32_t num;
    uint32_t writer;
    uint32_t reader;
};

typedef struct __gs_gui_config __gs_gui_config, *P__gs_gui_config;
typedef struct __gs_gui_config gs_gui_config_t;

struct __gs_gui_config {
	gs_queue_t * osd_gen_data_queue;
	gs_queue_t * osd_home_data_queue;
	gs_queue_t * file_del_queue;
	gs_queue_t * camera_stat_queue;
	gs_queue_t * camera_cap_param_queue;
	gs_queue_t * camera_pb_param_queue;
	gs_queue_t * camera_file_info_queue;
	gs_queue_t * camera_dcf_abstract_queue;
	gs_queue_t * camera_fov_param_queue;
	gs_queue_t * rc_bat_stat_queue;
	gs_queue_t * signal_quality_queue;
	gs_queue_t * uav_bat_common_info_queue;
	gs_queue_t * sdr_wl_env_queue;
	gs_queue_t * sdr_uav_data_queue;
	gs_queue_t * sdr_gnd_data_queue;
	gs_queue_t * rc_param_queue;
	gs_queue_t * rc_pushed_gps_queue;
	gs_queue_t * racing_drone_fc_osd_queue;
	bool * touchpadLockState;
	void * gs_info;
	int (* gs_ext_fc_get_craft_name)(void *ctx,char *craft_name);
	int (* gs_ext_fc_get_pid)(void *ctx,uint8_t type,uint8_t *value);
	int (* gs_ext_fc_get_rate)(void *ctx,uint8_t type,uint8_t *value);
	int (* gs_ext_fc_get_osd_profile_index)(void *ctx,uint8_t *osd_index);
	int (* gs_ext_fc_select_file)(void *ctx,uint8_t type,uint8_t index);
	int (* gs_ext_fc_copy_file)(void *ctx,uint8_t type,uint8_t src_index,uint8_t dst_index);
	int (* gs_ext_fc_write_eeprom)(void *ctx);
	int (* gs_ext_fc_get_rc_channel)(void *ctx,uint8_t chnl_index,uint16_t *value);
	int (* gs_ext_fc_get_aux_mode_id_by_index)(void *ctx,uint8_t *aux_id,uint8_t aux_index,uint8_t *start_step,uint8_t *end_step);
	int (* gs_ext_fc_get_aux_mode)(void *ctx,uint8_t aux_id,uint8_t *aux_index,uint8_t *start_step,uint8_t *end_step);
	int (* gs_ext_fc_set_aux_mode)(void *ctx,uint8_t aux_id,uint8_t aux_index,uint8_t start_step,uint8_t end_step);
	int (* gs_ext_fc_set_request_type)(void *ctx,uint8_t type);
	int (* gs_ext_fc_get_request_type)(void *ctx,uint8_t *type);
	int (* gs_ext_fc_get_ag_gain)(void *ctx,uint16_t *ag_gain);
	int (* gs_ext_fc_set_ag_gain)(void *ctx,uint16_t ag_gain);
	int (* gs_ext_fc_get_ag_thr)(void *ctx,uint16_t *thr);
	int (* gs_ext_fc_set_ag_thr)(void *ctx,uint16_t thr);
	int (* gs_ext_fc_get_thr_boost)(void *ctx,uint8_t *boost);
	int (* gs_ext_fc_set_thr_boost)(void *ctx,uint8_t boost);
	int (* gs_ext_fc_get_ff_trans)(void *ctx,uint8_t *ff_trans);
	int (* gs_ext_fc_set_ff_trans)(void *ctx,uint8_t ff_trans);
	int (* gs_ext_fc_get_filter)(void *ctx,uint8_t filter_type,uint16_t *value);
	int (* gs_ext_fc_set_filter)(void *ctx,uint8_t filter_type,uint16_t value);
	int (* gs_ext_fc_get_rate_profile_index)(void *ctx,uint8_t *rate_index);
	int (* gs_ext_fc_set_rate)(void *ctx,uint8_t type,uint8_t value);
	int (* gs_ext_fc_get_super_rate)(void *ctx,uint8_t type,uint8_t *value);
	int (* gs_ext_fc_set_super_rate)(void *ctx,uint8_t type,uint8_t value);
	int (* gs_ext_fc_get_expo)(void *ctx,uint8_t type,uint8_t *value);
	int (* gs_ext_fc_set_expo)(void *ctx,uint8_t type,uint8_t value);
	int (* gs_ext_fc_get_dyn_thr)(void *ctx,uint8_t *value);
	int (* gs_ext_fc_set_dyn_thr)(void *ctx,uint8_t value);
	int (* gs_ext_fc_get_thr_mid)(void *ctx,uint8_t *value);
	int (* gs_ext_fc_set_thr_mid)(void *ctx,uint8_t value);
	int (* gs_ext_fc_get_thr_expo)(void *ctx,uint8_t *value);
	int (* gs_ext_fc_set_thr_expo)(void *ctx,uint8_t value);
	int (* gs_ext_fc_get_tpa)(void *ctx,uint16_t *value);
	int (* gs_ext_fc_set_tpa)(void *ctx,uint16_t value);
	int (* gs_ext_fc_get_pid_f)(void *ctx,uint8_t type,uint16_t *ff);
	int (* gs_ext_fc_set_pid_f)(void *ctx,uint8_t type,uint16_t ff);
	int (* gs_ext_fc_get_pid_profile_index)(void *ctx,uint8_t *pid_index);
	int (* gs_ext_fc_set_pid)(void *ctx,uint8_t type,uint8_t value);
	int (* gs_ext_fc_get_battery_state)(void *ctx,void *state);//(void *ctx,batteryState_e *state);
	int (* gs_ext_fc_get_battery_voltage)(void *ctx,uint16_t *batt_voltage);
	int (* gs_ext_fc_get_battery_avg_voltage)(void *ctx,uint16_t *avg_batt_voltage);
	int (* gs_ext_fc_get_battery_amperage)(void *ctx,uint16_t *batt_amperage);
	int (* gs_ext_fc_get_battery_mah)(void *ctx,uint16_t *mah);
	int (* gs_ext_fc_get_battery_usage)(void *ctx,uint16_t *percent);
	int (* gs_ext_fc_get_battery_power)(void *ctx,uint16_t *power);
	int (* gs_ext_fc_set_arming_disabled)(void *ctx,uint8_t arming_disabled);
	int (* gs_ext_fc_get_arming_disabled)(void *ctx,uint32_t *arming_disabled);
	int (* gs_ext_fc_get_version)(void *ctx,uint8_t *major,uint8_t *minor,uint8_t *patch_level);
	int (* gs_ext_fc_set_sbus_mode)(void *ctx,uint8_t sbus_mode);
	int (* gs_ext_fc_get_racing_osd_info)(void *ctx,void *osdInfo);//(void *ctx,DUSS_MSG_FC_RACING_DRONE_OSD_PUSH_t *osdInfo);
	int (* gs_ext_fc_get_osd_position)(void *ctx,int num,bool *activated,int *x,int *y);
	int (* gs_ext_fc_get_units)(void *ctx,uint8_t *units);
	int (* gs_ext_fc_get_fly_mode)(void *ctx,uint16_t *fly_mode);
	int (* gs_ext_fc_get_rtc_date)(void *ctx,void *rtc);//(void *ctx,DUSS_MSG_EXT_FC_RTC_t *rtc);
	int (* gs_ext_fc_get_esc_temperature)(void *ctx,uint8_t *temp);
	void (* dummy_1)(void);
	void (* dummy_2)(void);
	int (* gs_media_adjust_fov)(void *ctx,uint32_t scaling,int16_t x,int16_t y);
	int (* gs_bl_set_brightness_value)(void *ctx,uint8_t value);
	int (* gs_bl_get_brightness_value)(void *ctx,uint8_t *value);
	void (* get_device_volume)(void);
	void (* set_device_volume)(void);
	void (* gs_imu_acc_gyro_calibrate)(char *configfile);
	void (* gs_imu_initialize)(void);
	void (* gs_imu_destroy)(void);
	void (* gs_imu_start)(void);
	void (* gs_imu_stop)(void);
	void (* gs_imu_get_init_status)(void);
	void (* gs_imu_get_attitude)(void);
	int (* gs_sd_format_wrap)(void *ctx);
	int (* gs_sd_get_info_wrap)(void *ctx,void *sd_info);//(void *ctx,gs_local_sd_info_t *sd_info)
	int (* gs_get_battery_info)(void *ctx,void *bat_info);//(void *ctx,DUSS_MSG_RC_BAT_INFO_t *bat_info);
	int (* gs_get_device_active_state)(void *ctx,int device_type);
	int (* gs_av_in_us_get_brightness)(void *ctx,uint8_t *value);
	int (* gs_av_in_us_set_brightness)(void *ctx,uint8_t value);
	void (* dummy_3)(void);
	int (* gs_av_in_us_get_satutation)(void *ctx,uint8_t *value);
	int (* gs_av_in_us_set_saturaton)(void *ctx,uint8_t value);
	int (* gs_reset_user_settings)(void *ctx);
	int (* gs_ui_event_tracking)(void *ctx,int32_t value,uint8_t event_type,uint8_t event_sub_id);
	void (* gs_get_real_flight_stat)(uint8_t *stat);
	void (* gs_set_flight_stat)(uint8_t stat);
	int (* gs_watermarker_us_get_flag)(void *ctx,uint8_t *value);
	int (* gs_watermarker_us_set_flag)(void *ctx,uint8_t value);
	int (* gs_watermarker_us_reset)(void *ctx);
	int (* gs_player_open)(void *ctx,char *filename);
	int (* gs_player_close)(void *ctx);
	int (* gs_player_stop)(void *ctx);
	int (* gs_player_pause)(void *ctx);
	int (* gs_player_resume)(void *ctx);
	int (* gs_player_seek_time)(void *ctx,uint32_t time);
	int (* gs_player_seek)(void *ctx,uint32_t pos);
	int (* gs_player_get_duration)(char *filename,uint32_t *duration);
	int (* gs_player_get_cur_time)(void *ctx,uint32_t *cur_time,uint32_t *duration);
	int (* gs_player_get_state)(void *ctx,uint32_t *state);
	int (* gs_player_get_fileinfo)(char *filename,void *file_info);//(char *filename,vdec_video_file_info_t *file_info);
	int (* gs_player_is_playing)(void *ctx,bool *is_playing);
	int (* gs_player_delete_file)(char *filename);
	int (* gs_send_camera_cmd_async)(void *event_obj,int cam_cmd,void *msg,uint32_t msg_len,uint16_t seq_id);//(duss_event_client *event_obj,int cam_cmd,void *msg,uint32_t msg_len,uint16_t seq_ id)
	int (* gs_set_camera_param)(void *ctx,uint8_t param_type,uint8_t param);
	int (* gs_uav_camera_get_rec_time)(void *ctx,int *mode,int *rec_time);
	int (* gs_modem_pairing_control_wrap)(void *ctx,uint32_t ctrl);
	void (* dummy_4)(void);
	void (* dummy_5)(void);
	void (* dummy_6)(void);
	void (* dummy_7)(void);
	void (* dummy_8)(void);
	void (* dummy_9)(void);
	void (* dummy_10)(void);
	void (* dummy_11)(void);
	void (* dummy_12)(void);
	void (* dummy_13)(void);
	void (* dummy_14)(void);
	void (* dummy_15)(void);
	void (* dummy_16)(void);
	int (* gs_modem_get_link_state_wrap)(void *ctx,gs_link_stat_t *link_stat);
	int (* gs_modem_get_bandwidth)(void *ctx,uint16_t *bandwidth);
	int (* gs_modem_set_bandwidth)(void *ctx,uint16_t bandwidth);
	int (* gs_modem_get_chnl)(void *ctx,uint16_t *chnl_id);
	int (* gs_modem_set_chnl_scan_info)(void *ctx,uint8_t chnl_num,uint8_t bandwidth);
	int (* gs_modem_rob_chnl_cancel)(void *ctx);
	int (* gs_modem_rob_chnl)(void *ctx,uint16_t chnl_id);
	int (* gs_modem_get_rob_left_time)(void *ctx,uint8_t *left_time);
	int (* gs_modem_get_rob_flag)(void *ctx,uint8_t *flag);
	int (* gs_modem_clear_rob_flag)(void *ctx);
	int (* gs_modem_set_public_chnl)(void *ctx);
	int (* gs_modem_is_drone_broadcast)(void *ctx,uint16_t *is_brdcst);
	int (* gs_modem_enable_drone_broadcast)(void *ctx,uint16_t enable);
	int (* gs_modem_listen_broadcast)(void *ctx,uint16_t chnl_id);
	int (* gs_modem_is_silent)(void *ctx,uint16_t *is_silent);
	int (* gs_modem_set_chnl)(void *ctx,uint16_t chnl_id);
	int (* gs_modem_scan_chnl_x)(void *ctx,uint8_t chnl_id,uint8_t bandwidth);
	int (* gs_modem_check_ant_status)(void *ctx);
	int (* gs_modem_if_new_chnl_scan_info)(void *ctx,uint8_t *flag);
	int (* gs_modem_if_new_phy_check_info)(void *ctx,uint8_t *flag);
	int (* gs_modem_if_update_bandwidth_pending)(void *ctx,uint8_t *pending);
	int (* gs_modem_clear_scan_flag)(void *ctx);
	int (* gs_modem_clear_check_flag)(void *ctx);
	int (* gs_modem_get_chnl_scan_info)(void *ctx,uint8_t chnl_id,uint8_t *occupied,uint8_t *work_ind,uint32_t *ipsd );
	int (* gs_modem_get_ant_status)(void *ctx,uint8_t *tx_ant,uint8_t *rx_ant);
	int (* gs_modem_get_dbg_mcs)(void *ctx,uint16_t *mcs);
	int (* gs_modem_set_dbg_mcs)(void *ctx,uint16_t mcs);
	int (* gs_modem_get_dbg_harq)(void *ctx,uint16_t *harq);
	int (* gs_modem_set_dbg_harq)(void *ctx,uint16_t harq);
	int (* gs_modem_get_dbg_codec_rate)(void *ctx,uint16_t *codec_rate);
	int (* gs_modem_set_dbg_codec_rate)(void *ctx,uint16_t codec_rate);
	int (* gs_modem_get_signal_quality)(void *ctx,void *signal_quality);//(void *ctx,glass_signal_quality_t *signal_quality);
	int (* gs_modem_get_rc_signal_quality)(void *ctx,void *rc_signal_quality);//(void *ctx,glass_signal_quality_t *rc_signal_quality)
	int (* gs_modem_set_bandwidth_mode)(void *ctx,uint16_t bandwidth_id);
	int (* gs_modem_change_silent_mode)(void *ctx,uint8_t mode);
	int (* gs_modem_get_chnl_cnt_wrap)(void *ctx,uint16_t *chnl_cnt);
	int (* gs_modem_get_freq_by_index_wrap)(void *ctx,uint16_t *freqByIndex,uint16_t chnlId);
	int (* gs_modem_get_scan_type_wrap)(void *ctx,uint8_t *scanType);
	int (* gs_modem_get_wireless_area_id)(void *ctx,uint8_t *area_id);
	int (* gs_modem_get_pairing_finish_flag)(void *ctx,uint8_t *pairing_finish);
	int (* gs_modem_check_conf_items)(void *ctx);
	int (* gs_rc_get_version)(void *ctx,char *ap_ver,char *board_sn,int8_t *valid);
	int (* gs_rc_get_version_async)(void *ctx);
	int (* gs_rc_set_subtrim)(void *ctx,uint8_t stick,int16_t st);
	int (* gs_rc_set_subtrim_async)(void *ctx,uint8_t stick,int16_t st);
	int (* gs_rc_get_subtrim_sync)(void *ctx,void *subtrim);//(void *ctx,rc_set_all_st_t *subtrim)
	int (* gs_rc_get_subtrim_async)(void *ctx);
	int (* gs_rc_set_reverse)(void *ctx,uint8_t stick,uint8_t rev);
	int (* gs_rc_get_reverse_sync)(void *ctx,void *reverse);//(void *ctx,rc_set_reverse_t *reverse)
	int (* gs_rc_get_reverse_async)(void *ctx);
	int (* gs_rc_set_endpoint)(void *ctx,uint8_t stick_ch,uint8_t ep_min,uint8_t ep_max);
	int (* gs_rc_set_endpoint_async)(void *ctx,uint8_t stick_ch,uint8_t ep_min,uint8_t ep_max);
	int (* gs_rc_get_endpoint_sync)(void *ctx,void *ep);//(void *ctx,rc_set_all_ep_t *ep)
	int (* gs_rc_get_endpoint_async)(void *ctx);
	int (* gs_rc_set_function_mode)(void *ctx,uint8_t func,uint8_t stick,uint8_t set_val);
	int (* gs_rc_get_function_mode)(void *ctx,void *func_mode);//(void *ctx,rc_set_function_pack_t *func_mode)
	int (* gs_rc_set_stick_mode)(void *ctx,uint8_t stick_mode);
	int (* gs_rc_get_stick_mode_async)(void *ctx);
	int (* gs_rc_get_stick_mode_ext)(void *ctx,uint8_t *mode);
	int (* gs_rc_get_stick_mode_sync)(void *ctx,uint8_t *mode);
	int (* gs_rc_set_stick_cali_stage)(void *ctx,uint8_t tid,uint8_t stage,uint8_t *rc_stage);
	int (* gs_rc_get_stick_cali_value)(void *ctx,uint8_t tid,int8_t *x1_pct,int8_t *y1_pct,int8_t *x2_pct,int8_t *y2_pct);
	int (* gs_rc_set_warning_mode)(void *ctx,int warn);//(void *ctx,rc_set_warning_mode_pack_t warn)
	int (* gs_rc_get_warning_mode)(void *ctx,void *warn);//(void *ctx,rc_set_warning_mode_pack_t *warn)
	int (* gs_rc_monitor_setup)(void *ctx,void *monitor);//(void *ctx,rc_monitor_pack_t *monitor)
	int (* gs_rc_reset_all_get_status)(void *ctx);
	int (* gs_rc_reset_default_async)(void *ctx,uint8_t resetType);
	uint8_t (* gs_rc_get_lock_state)(void *ctx);
	uint8_t (* gs_rc_get_link_state)(void *ctx);
	int (* gs_vcm_register_channel_switch_callback_wrap)(void *ctx,int callback,void *data);//(void *ctx,gs_video_channel_switch_callback_t callback,void *data)
	int (* gs_vcm_register_channel_push_callback_wrap)(void *ctx,int callback,void *data);//(void *ctx,gs_video_channel_push_callback_t callback,void *data)
	int (* gs_vcm_query_current_channel_wrap)(void *ctx,void *chnl_id);//(void *ctx,gs_video_channel_id_t *chnl_id)
	int (* gs_vcm_enable_channel_wrap)(void *ctx,int chnl_id);//(void *ctx,gs_main_channel_id_t chnl_id)
	int (* gs_vcm_disable_channel_wrap)(void *ctx,int chnl_id);//(void *ctx,gs_main_channel_id_t chnl_id)
	int (* gs_vcm_enable_sub_channel_wrap)(void *ctx,void *sub_chnl_id);//(void *ctx,gs_video_channel_id_t *sub_chnl_id)
	int (* gs_vcm_disable_sub_channel_wrap)(void *ctx,void *sub_chnl_id);//(void *ctx,gs_video_channel_id_t *sub_chnl_id)
	int (* gs_vcm_local_playback_on_wrap)(void *ctx,char *video_path);
	int (* gs_vcm_local_playback_off_wrap)(void *ctx);
	int (* gs_vcm_rc_setting_on_wrap)(void *ctx);
	int (* gs_vcm_rc_setting_off_wrap)(void *ctx);
	int (* gs_common_send_cmd)(void *ctx,void *cmd,bool sync);//(void *ctx,gs_common_cmd_t *cmd,bool sync)
	int (* gs_get_codec_debug_osd_info)(void *ctx,void *info);//(void *ctx,debug_codec_osd_info_t *info)
	int (* gs_get_cam_debug_osd_info)(void *ctx,void *info);//(void *ctx,debug_cam_osd_info_t *info)
	int (* gs_get_temp_debug_osd_info)(void *ctx,void *info);//(void *ctx,debug_temp_osd_info_t *info)
	int (* gs_get_uav_max_temp)(void *ctx,int32_t *uav_temp);
	int (* gs_get_cp_debug_osd_info)(void *ctx,void *info);//(void *ctx,debug_cp_osd_info_t *info)
	int (* gs_set_racing_enc_strategy)(void *ctx,uint8_t strategy);
	int (* gs_debug_is_camera_in_record)(void *ctx,int *record_state);
	int (* gs_get_cparm_version)(void *ctx,char *arm_ver);
	int (* gs_get_dsp_version)(void *ctx,char *dsp_ver);
	int (* gs_get_flight_time)(void *ctx,uint64_t *flight_time);
	int (* gs_get_arm_status)(void *ctx,uint8_t *flag);
	int (* gs_clear_adb_log_info)(void *ctx);
	int (* gs_reset_camera_param)(void *ctx);
	int (* gs_set_low_power_mode)(void *ctx,bool mode);
	int (* gs_get_uav_version)(void *ctx,char *ap_ver,char *board_sn);
	int (* gs_get_uav_hardware_version)(void *ctx,char *hw_ver);
	int (* gs_get_uav_power_status)(void *ctx,uint8_t *power_status,uint8_t *arm_flag);
	int (* gs_get_uav_camera_type)(void *ctx,uint8_t *cam_type);
	int (* gs_get_liveview_fps)(void *ctx,uint8_t *lv_fps);
	int (* gs_fbdev_open)(void);
	int (* gs_fbdev_disp_frame)(int *frm_id);
	int (* gs_fbdev_close)(void);
	int (* gs_record_liveview)(void *ctx,bool b_record);
	int (* gs_liveview_get_state)(void *ctx,int *lv_rec_state);
	int (* gs_lv_transcode_get_looping_mode)(void *ctx);
	int (* gs_lv_transcode_set_looping_mode)(void *ctx,int rec_mode);//(void *ctx,record_mode_t rec_mode)
	int (* gs_lv_transcode_get_state)(void *ctx);
	int (* gs_lv_transcode_record)(void *ctx,bool b_record,Record_sender sender);
	int (* gs_lv_transcode_get_rec_time)(void *ctx,int *rec_time);
	int (* gs_enable_audio_liveview)(void *ctx,bool b_enable);
	int (* gs_get_frame_delay_e2e)(void *ctx,uint16_t *delay);
	int (* gs_get_chnl_status)(void *ctx,uint16_t *chnl_status);
	int (* gs_get_pigeon_battery_info)(void *ctx,void *vol);//(void *ctx,gs_battery_voltage_t *vol)
	int (* gs_get_sd_status)(void *ctx,int type,uint8_t *sd_status,uint32_t *total_kbytes,uint32_t *free_kbytes);
	int (* gs_pwm_buzzer_playback)(void *ctx,int freq,int duty,int delay_ms);
	int (* gs_pwm_buzzer_enable_bat)(void *ctx,bool enable);
};
