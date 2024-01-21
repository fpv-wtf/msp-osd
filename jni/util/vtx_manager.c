#include <stdlib.h>
#include <dlfcn.h>
#include "util/debug.h"
#include "vtx_manager.h"
#include "../rec/rec_shim.h"


#define CHANNEL_PUBLIC 8

static void *tp1801_gui_lib = NULL;
// static uint32_t (* setChannelPilotOriginal)(void *this,unsigned short param_1, bool param_2) = 0;
// or
static uint32_t (* setChannelPilotOriginal)(uint32_t this, unsigned short param_1, bool param_2) = 0;
static uint32_t (* userSettingsGetInstanceOriginal)() = 0;
static uint32_t userSettingsInstance = 0;
static __gs_gui_config *gs_gui_config = 0;
static int8_t currentChannel = -1;

void setupVTXManager() {
    if(setChannelPilotOriginal != NULL)  {
        //Already setup
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

    userSettingsInstance = userSettingsGetInstanceOriginal();
    if(userSettingsInstance == NULL) {
        printf("dlsym: error loading user setting instance");
        return;
    }
    gs_gui_config = (__gs_gui_config *)*(uint32_t *)((int)userSettingsInstance + 0xe4);
}

void changeChannel(int8_t channel) {
    if (channel <= 0 || channel > 8) {
        printf("VTX_MANAGER Error:, invalid channel index: %d\n", channel);
        return;
    }

    if(currentChannel == channel) {
        return;
    }
    currentChannel = channel;

    DEBUG_PRINT("VTX_MANAGER: requesting to the goggles to set channel %d\n", channel);

    if(channel == CHANNEL_PUBLIC){
        gs_gui_config->gs_modem_set_public_chnl(gs_gui_config->ctx);
    } else {
        int8_t channelIdx = channel - 1;
        setChannelPilotOriginal(userSettingsGetInstanceOriginal(), channelIdx, true);
    }
}
