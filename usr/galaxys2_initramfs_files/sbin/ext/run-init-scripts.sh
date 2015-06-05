#!/system/bin/sh
mount -o remount,rw /system
mount -o remount,rw /data
if [ -d /system/etc/init.d ]; then
  /system/bin/sh run-parts /system/etc/init.d
fi;

if [ -f /system/bin/customboot.sh ]; then
  /system/bin/sh /system/bin/customboot.sh;
fi;

if [ -f /system/xbin/customboot.sh ]; then
  /system/bin/sh /system/xbin/customboot.sh
fi;

if [ -f /data/local/customboot.sh ]; then
  /system/bin/sh /data/local/customboot.sh
fi;
