#include <stdlib.h>
#include <dlfcn.h>
#include "json/osd_config.h"
#include "util/debug.h"

#define VTX_MPS_CONFIG_KEY "vtx_msp"

static void *tp1801_gui_lib = NULL;
static uint32_t (* setChannelPilotOriginal)(void *this,unsigned short param_1, bool param_2) = 0;
static uint32_t (* userSettingsGetInstanceOriginal)() = 0;
static uint32_t userSettingsInstance = 0;
static int8_t currentChannel = -1;

void changeChannel(int8_t channel) {
    if(!get_boolean_config_value(VTX_MPS_CONFIG_KEY)) {
        return;
    }

    //Load SetPilotChannel original
    setChannelPilotOriginal = dlsym (RTLD_NEXT, "_ZN17GlassUserSettings15setPilotChannelEtb");
    if (setChannelPilotOriginal == NULL) {
        if(!tp1801_gui_lib){
            tp1801_gui_lib = dlopen("/system/lib/libtp1801_gui.so", 1);
        }
        setChannelPilotOriginal = dlsym (tp1801_gui_lib, "_ZN17GlassUserSettings15setPilotChannelEtb");
        if (setChannelPilotOriginal == NULL)
        {
            printf("dlsym: %s\n", dlerror());
            return;
        }
    }

    //Load UserSettingGetInstance original
    userSettingsGetInstanceOriginal = dlsym (tp1801_gui_lib, "_ZN17GlassUserSettings11getInstanceEv");
    if (userSettingsGetInstanceOriginal == NULL)
    {
        printf("dlsym: %s\n", dlerror());
        return;
    }

    if (channel <= 0 || channel > 8) {
        printf("VTX_MANAGER Error:, invalid channel index: %d\n", channel);
        return;
    }

    if(currentChannel == channel) {
        return;
    }
    currentChannel = channel;

    // if 8, need to set to public
    DEBUG_PRINT("VTX_MANAGER: requesting to the goggles to set channel %d\n", channel);
    
    int8_t channelIdx = channel - 1;
    setChannelPilotOriginal(userSettingsGetInstanceOriginal(), channelIdx, true);
}