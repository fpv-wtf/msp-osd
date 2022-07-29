#include <string.h>
#ifdef __ANDROID_API__
#include <sys/system_properties.h>
#endif

#define V2_SERVICE_NAME "dji.glasses_wm150_service"
#define V1_SERVICE_NAME "dji.glasses_service"
#define DEVICE_PROPERTY_NAME "ro.product.device"
#define V2_GOGGLES_DEVICE "pigeon_wm170_gls"

void dji_stop_goggles(int is_v2) {
#ifdef __ANDROID_API__
    __system_property_set(is_v2 ? V2_SERVICE_NAME : V1_SERVICE_NAME, "0");
#endif
}

void dji_start_goggles(int is_v2) {
#ifdef __ANDROID_API__
    __system_property_set(is_v2 ? V2_SERVICE_NAME : V1_SERVICE_NAME, "1");
#endif
}

int dji_goggles_are_v2() {
#ifdef __ANDROID_API__
    char goggles_version_response[255];
    int len = __system_property_get(DEVICE_PROPERTY_NAME, &goggles_version_response);
    return(strcmp(goggles_version_response, V2_GOGGLES_DEVICE) == 0);
#else
    return 0;
#endif
}