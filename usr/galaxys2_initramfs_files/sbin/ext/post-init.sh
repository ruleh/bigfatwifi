#!/system/bin/sh
# Logging
#/sbin/busybox cp /data/user.log /data/user.log.bak
#/sbin/busybox rm /data/user.log
#exec >>/data/user.log
#exec 2>&1

#!/sbin/busybox sh

SYNPASE=0
STWEAKS=0

# check if synapse is installed
if [ -f "/data/app/com.af.synapse-2.apk" ]; then
SYNAPSE=1
fi
if [ -f "/data/app/com.af.synapse-1.apk" ]; then
SYNAPSE=1
fi

if [ "$SYNAPSE" = "1" ]; then
# set up Synapse support
/sbin/uci;

# apply some of synapse defaults at boot
echo "0" > /sys/devices/virtual/sec/sec_touchscreen/tsp_slide2wake
echo "1200000" > /sys/devices/system/cpu/cpu0/cpufreq/scaling_max_freq
chmod 0664 /system/etc/gps.conf
if [ -f /data/gps.conf ]
then
mount -o remount,rw /system
mount -o remount,rw /data
chown system system /system/etc/gps.conf
chmod 0660 /system/etc/gps.conf
cp /data/gps.conf /system/etc/gps.conf
chown system system /system/etc/gps.conf
chmod 0660 /system/etc/gps.conf
mount -o remount,ro /system	    
fi
fi
# if synapse is not installed check if stweaks is
if [ -f "/data/app/com.gokhanmoral.stweaks.app-1.apk" ]; then
STWEAKS=1
fi

if [ "$STWEAKS" = "1" ]; then
# set up stweaks support
mkdir /data/.siyah
chmod 0777 /data/.siyah

. /res/customconfig/customconfig-helper

ccxmlsum=`md5sum /res/customconfig/customconfig.xml | awk '{print $1}'`
if [ "a${ccxmlsum}" != "a`cat /data/.siyah/.ccxmlsum`" ];
then
  rm -f /data/.siyah/*.profile
  echo ${ccxmlsum} > /data/.siyah/.ccxmlsum
fi
[ ! -f /data/.siyah/default.profile ] && cp /res/customconfig/default.profile /data/.siyah

read_defaults
read_config

#apply last soundgasm level on boot
/res/uci.sh soundgasm_hp $soundgasm_hp

# apply STweaks defaults
/res/uci.sh apply

#usb mode
/res/customconfig/actions/usb-mode ${usb_mode}

fi

# system status script
cp /res/systemstatus /system/bin/systemstatus
chown root.system /system/bin/systemstatus
chmod 0755 /system/bin/systemstatus

cp /res/systemcat /system/bin/systemcat
chown root.system /system/bin/systemcat
chmod 0755 /system/bin/systemcat

mount -o remount,ro /system

# google dns
setprop net.dns1 8.8.8.8
setprop net.dns2 8.8.4.4

# set recommended KSM settings by google
echo "100" > /sys/kernel/mm/ksm/pages_to_scan
echo "500" > /sys/kernel/mm/ksm/sleep_millisecs

cp /res/msaa /data/msaa

sysctl -w vm.dirty_background_ratio=5;
sysctl -w vm.dirty_ratio=10;
# low swapiness to use swap only when the system 
# is under extreme memory pressure
sysctl -w vm.swappiness=25;
