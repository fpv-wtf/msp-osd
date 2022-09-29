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
LOCAL_MODULE    := displayport_osd_shim
LOCAL_SRC_FILES := displayport_osd_shim.c osd_dji_overlay_udp.c msp/msp_displayport.c msp/msp.c net/network.c util/fs_util.c hw/dji_radio_shm.c hw/dji_display.c hw/dji_services.c json/osd_config.c json/parson.c fakehd/fakehd.c
LOCAL_SHARED_LIBRARIES := duml_hal

include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)

LOCAL_SRC_FILES:= msp_displayport_mux.c net/serial.c net/network.c msp/msp.c util/fs_util.c hw/dji_radio_shm.c json/osd_config.c json/parson.c
LOCAL_MODULE := msp_displayport_mux

include $(BUILD_EXECUTABLE)
