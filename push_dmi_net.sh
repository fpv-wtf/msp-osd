#!/bin/bash
set -xe

ndk-build

adb shell "setprop dji.glasses_wm150_service 0"

adb push ./jni/ffmpeg/lib/libav*so* /tmp
adb push ./libs/armeabi-v7a/dmi-net /tmp
adb shell "export LD_LIBRARY_PATH=/tmp; cd /tmp; /tmp/dmi-net"
