#!/system/bin/sh
setprop dji.hdvt_uav_service 0
setprop dji.shuttle_service 0

if [ ! -e "/dev/ttyS1_moved" ]
then
  mv /dev/ttyS1 /dev/ttyS1_moved
fi

/opt/bin/msp_displayport_mux 192.168.41.2 /dev/ttyS1_moved /dev/ttyS1 &
echo $! > /opt/var/run/airunit-osd-dji.pid
setprop dji.hdvt_uav_service 1
setprop dji.shuttle_service 1



BBSTORE="/blackbox/dump_tty_`date '+%Y%m%d-%H%M%S'`.log"

stdbuf -o0 cat /dev/ttyS1_moved >$BBSTORE &
echo $! > /opt/var/run/dump-tty.pid

###wait 10sec and if file >0kb then kill process (msp data, not bb log)
sleep 10
if [ -s $BBSTORE ]; then
	kill `cat /opt/var/run/dump-tty.pid`
	rm $BBSTORE
else
	#file is empty = no msp data
fi
