ndk-build
adb push libs/armeabi-v7a/msp_displayport_mux /blackbox
adb shell setprop dji.hdvt_uav_service 0
adb shell mv /dev/ttyS1 /dev/ttyS1_moved
adb shell nohup /blackbox/msp_displayport_mux 192.168.41.2 /dev/ttyS1_moved /dev/ttyS1 &
adb shell setprop dji.hdvt_uav_service 1