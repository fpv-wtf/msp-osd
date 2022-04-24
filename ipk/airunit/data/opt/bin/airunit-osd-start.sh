#!/system/bin/sh
setprop dji.hdvt_uav_service 0

if [ ! -e "/dev/ttyS1_moved" ]
then
  mv /dev/ttyS1 /dev/ttyS1_moved
fi

/opt/bin/msp_displayport_mux 192.168.41.2 /dev/ttyS1_moved /dev/ttyS1 &
echo $! > /opt/var/run/airunit-osd-dji.pid
setprop dji.hdvt_uav_service 1
