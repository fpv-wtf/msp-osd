#include <string.h>
#ifdef __ANDROID_API__
#include <sys/system_properties.h>
#endif

void dji_stop_goggles(int is_v2) {
#ifdef __ANDROID_API__
    if(is_v2) {
        __system_property_set("dji.dji.glasses_wm150_service", "0");
    } else {
        __system_property_set("dji.glasses_service", "0");
    }
#endif
}

void dji_start_goggles(int is_v2) {
#ifdef __ANDROID_API__
    if(is_v2) {
        __system_property_set("dji.dji.glasses_wm150_service", "1");
    } else {
        __system_property_set("dji.glasses_service", "1");
    }
#endif
}

int dji_goggles_are_v2() {
#ifdef __ANDROID_API__
    char goggles_version_response[255];
    int len = __system_property_get("ro.product.device", &goggles_version_response);
    return(strcmp(goggles_version_response, "pigeon_wm170_gls") == 0);
#else
    return 0;
#endif
}