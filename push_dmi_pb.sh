#!/bin/bash
set -xe

ndk-build

# adb push dmi_dump_dvr2 /tmp/

adb shell "setprop dji.glasses_wm150_service 0"

adb push ./libs/armeabi-v7a/dmi-dump-pb /tmp
adb shell "export LD_LIBRARY_PATH=/tmp; cd /tmp; /tmp/dmi-dump-pb"
