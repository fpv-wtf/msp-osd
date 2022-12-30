LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := duml_hal
LOCAL_SRC_FILES := libduml_hal.so
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/include
include $(PREBUILT_SHARED_LIBRARY)
include $(CLEAR_VARS)

LOCAL_CFLAGS += -fPIC -std=c99 -O3
LOCAL_LDFLAGS += -fPIC
LOCAL_LDLIBS := -llog
LOCAL_ARM_NEON := true
LOCAL_MODULE := displayport_osd_shim
LOCAL_SHARED_LIBRARIES := duml_hal
LOCAL_SRC_FILES := \
	displayport_osd_shim.c \
	fakehd/fakehd.c \
	hw/dji_display.c \
	hw/dji_radio_shm.c \
	hw/dji_services.c \
	json/osd_config.c \
	json/parson.c \
	lz4/lz4.c \
	msp/msp_displayport.c \
	msp/msp.c \
	net/network.c \
	osd_dji_overlay_udp.c \
	rec/rec_pb.c \
	rec/rec_shim.c \
	rec/rec_util.c \
	rec/rec.c \
	toast/toast.c \
	util/fs_util.c
include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
	hw/dji_radio_shm.c \
	json/osd_config.c \
	json/parson.c \
	msp_displayport_mux.c \
	msp/msp.c \
	msp/msp_displayport.c \
	net/network.c \
	net/serial.c \
	util/fs_util.c \
	lz4/lz4.c
LOCAL_MODULE := msp_displayport_mux
include $(BUILD_EXECUTABLE)
include $(CLEAR_VARS)

LOCAL_MODULE := libavcodec
LOCAL_SRC_FILES := ffmpeg/lib/libavcodec.so
include $(PREBUILT_SHARED_LIBRARY)
include $(CLEAR_VARS)

LOCAL_MODULE := libavformat
LOCAL_SRC_FILES := ffmpeg/lib/libavformat.so
include $(PREBUILT_SHARED_LIBRARY)
include $(CLEAR_VARS)

LOCAL_MODULE := libavutil
LOCAL_SRC_FILES := ffmpeg/lib/libavutil.so
include $(PREBUILT_SHARED_LIBRARY)
include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
	dmi/dmi.c \
	dmi/dji_media.c
LOCAL_MODULE := dmi-playback
LOCAL_SHARED_LIBRARIES := libavcodec libavformat libavutil
LOCAL_CFLAGS += -I$(LOCAL_PATH)/ffmpeg/include
LOCAL_CFLAGS += -fPIC -std=c99 -O3
LOCAL_LDFLAGS += -fPIC
include $(BUILD_EXECUTABLE)
include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
	dmi/ffmpeg_test.c
LOCAL_MODULE := ffmpeg_test
LOCAL_SHARED_LIBRARIES := libavcodec libavformat libavutil
LOCAL_CFLAGS += -I$(LOCAL_PATH)/ffmpeg/include
LOCAL_CFLAGS += -fPIC -std=c99 -O3
LOCAL_LDFLAGS += -fPIC
include $(BUILD_EXECUTABLE)
include $(CLEAR_VARS)
