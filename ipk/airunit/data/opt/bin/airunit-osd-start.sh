#!/system/bin/sh
if [ ! -e "/dev/ttyS1_moved" ]
then
  setprop dji.hdvt_uav_service 0
  mv /dev/ttyS1 /dev/ttyS1_moved
  /opt/bin/msp_displayport_mux 192.168.41.2 /dev/ttyS1_moved /dev/ttyS1 &
  setprop dji.hdvt_uav_service 1
fi
