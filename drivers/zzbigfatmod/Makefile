#
# Makefile for the bigfatwifi module
# This is where all the magic happens

obj-m		+= bigfatwifi.o


bigfatwifi-y	+= init/load.o

#---------------------------------------------------------------------------------
#misc.

bigfatwifi-$(CONFIG_EEPROM_93) 			+= misc/eeprom_93cx6.o
bigfatwifi-$(CONFIG_CRC_ITU_ST) 		+= misc/crc-itu-t.o

ccflags-y 					+= -D__CHECK_ENDIAN__
#---------------------------------------------------------------------------------
#cfg80211

bigfatwifi-$(CONFIG_LIB80211)			+= wireless/lib80211.o
bigfatwifi-$(CONFIG_LIB80211_CRYPT_WEP) 	+= wireless/lib80211_crypt_wep.o
bigfatwifi-$(CONFIG_LIB80211_CRYPT_CCMP)	+= wireless/lib80211_crypt_ccmp.o
bigfatwifi-$(CONFIG_LIB80211_CRYPT_TKIP)	+= wireless/lib80211_crypt_tkip.o

bigfatwifi-$(CONFIG_WEXT_CORE)			+= wireless/wext-core.o
bigfatwifi-$(CONFIG_WEXT_PROC) 			+= wireless/wext-proc.o
bigfatwifi-$(CONFIG_WEXT_SPY)			+= wireless/wext-spy.o
bigfatwifi-$(CONFIG_WEXT_PRIV)			+= wireless/wext-priv.o


bigfatwifi-$(CONFIG_CFG80211) 		+= wireless/sysfs.o   wireless/radiotap.o \
			  		   wireless/util.o    wireless/reg.o \
			  		   wireless/scan.o    wireless/nl80211.o \
					   wireless/core.o

bigfatwifi-$(CONFIG_CFG80211)		+= wireless/mlme.o    wireless/ibss.o \
					   wireless/sme.o     wireless/chan.o \
					   wireless/ethtool.o wireless/mesh.o 

bigfatwifi-$(CONFIG_CFG80211_DEBUGFS) 		+= wireless/debugfs.o
bigfatwifi-$(CONFIG_CFG80211_WEXT) 		+= wireless/wext-compat.o \
						   wireless/wext-sme.o
bigfatwifi-$(CONFIG_CFG80211_INTERNAL_REGDB) 	+= wireless/regdb.o


#----------------------------------------------------------------------------------------
#mac80211

bigfatwifi-$(CONFIG_MAC80211)		+= mac80211/main.o \
					   mac80211/status.o \
 				 	   mac80211/sta_info.o \
 					   mac80211/wep.o \
 					   mac80211/wpa.o \
 					   mac80211/scan.o \
 					   mac80211/offchannel.o \
 					   mac80211/ht.o \
 					   mac80211/agg-tx.o \
 					   mac80211/agg-rx.o \
 					   mac80211/ibss.o \
 					   mac80211/mlme.o \
 					   mac80211/work.o \
 					   mac80211/iface.o \
 					   mac80211/rate.o \
 					   mac80211/michael.o \
 					   mac80211/tkip.o \
 					   mac80211/aes_ccm.o \
 					   mac80211/aes_cmac.o \
 					   mac80211/cfg.o \
 					   mac80211/rx.o \
 					   mac80211/spectmgmt.o \
 					   mac80211/tx.o \
 					   mac80211/key.o \
 					   mac80211/util.o \
 					   mac80211/wme.o \
 					   mac80211/event.o \
 					   mac80211/chan.o

bigfatwifi-$(CONFIG_MAC80211_LEDS) 		+= mac80211/led.o

bigfatwifi-$(CONFIG_MAC80211_DEBUGFS) 		+= mac80211/debugfs.o \
 						   mac80211/debugfs_sta.o \
 						   mac80211/debugfs_netdev.o \
 					       	   mac80211/debugfs_key.o
 
bigfatwifi-$(CONFIG_MAC80211_MESH) 		+= mac80211/mesh.o \
 						   mac80211/mesh_pathtbl.o \
 					   	   mac80211/mesh_plink.o \
 						   mac80211/mesh_hwmp.o

bigfatwifi-$(CONFIG_PM) 			+= mac80211/pm.o

bigfatwifi-$(CONFIG_MAC80211_DRIVER_API_TRACER) += mac80211/driver-trace.o
CFLAGS_driver-trace.o := -I$(src)


rc80211_pid-y 					:= mac80211/rc80211_pid_algo.o
rc80211_pid-$(CONFIG_MAC80211_DEBUGFS) 		+= mac80211/rc80211_pid_debugfs.o

rc80211_minstrel-y 				:= mac80211/rc80211_minstrel.o
rc80211_minstrel-$(CONFIG_MAC80211_DEBUGFS) 	+= mac80211/rc80211_minstrel_debugfs.o

rc80211_minstrel_ht-y 				:= mac80211/rc80211_minstrel_ht.o
rc80211_minstrel_ht-$(CONFIG_MAC80211_DEBUGFS) 	+= mac80211/rc80211_minstrel_ht_debugfs.o

bigfatwifi-$(CONFIG_MAC80211_RC_PID) 		+= $(rc80211_pid-y)
bigfatwifi-$(CONFIG_MAC80211_RC_MINSTREL) 	+= $(rc80211_minstrel-y)
bigfatwifi-$(CONFIG_MAC80211_RC_MINSTREL_HT)    += $(rc80211_minstrel_ht-y)

#----------------------------------------------------------------------------------------
#ralink

bigfatwifi-$(CONFIG_RT2X00)			+= drivers/wireless/rt2x00/rt2x00dev.o
bigfatwifi-$(CONFIG_RT2X00)			+= drivers/wireless/rt2x00/rt2x00mac.o
bigfatwifi-$(CONFIG_RT2X00)			+= drivers/wireless/rt2x00/rt2x00config.o
bigfatwifi-$(CONFIG_RT2X00)			+= drivers/wireless/rt2x00/rt2x00queue.o
bigfatwifi-$(CONFIG_RT2X00)			+= drivers/wireless/rt2x00/rt2x00link.o
bigfatwifi-$(CONFIG_RT2X00_LIB_DEBUGFS)		+= drivers/wireless/rt2x00/rt2x00debug.o
bigfatwifi-$(CONFIG_RT2X00_LIB_CRYPTO)		+= drivers/wireless/rt2x00/rt2x00crypto.o
bigfatwifi-$(CONFIG_RT2X00_LIB_FIRMWARE)	+= drivers/wireless/rt2x00/rt2x00firmware.o
bigfatwifi-$(CONFIG_RT2X00_LIB_LEDS)		+= drivers/wireless/rt2x00/rt2x00leds.o

bigfatwifi-$(CONFIG_RT2X00_LIB_USB)		+= drivers/wireless/rt2x00/rt2x00usb.o
bigfatwifi-$(CONFIG_RT2800_LIB)			+= drivers/wireless/rt2x00/rt2800lib.o
bigfatwifi-$(CONFIG_RT2500USB)			+= drivers/wireless/rt2x00/rt2500usb.o
bigfatwifi-$(CONFIG_RT73USB)			+= drivers/wireless/rt2x00/rt73usb.o
bigfatwifi-$(CONFIG_RT2800USB)			+= drivers/wireless/rt2x00/rt2800usb.o

#----------------------------------------------------------------------------------------
#realtek

bigfatwifi-$(CONFIG_RTL8187)		+= drivers/wireless/rtl818x/rtl8187/dev.o \
					   drivers/wireless/rtl818x/rtl8187/rtl8225.o \
					   drivers/wireless/rtl818x/rtl8187/leds.o \
					   drivers/wireless/rtl818x/rtl8187/rfkill.o
#----------------------------------------------------------------------------------------
#atheros
bigfatwifi-$(CONFIG_ATH_COMMON)		+= drivers/wireless/ath/main.o \
					   drivers/wireless/ath/regd.o \
					   drivers/wireless/ath/hw.o \
					   drivers/wireless/ath/key.o

bigfatwifi-$(CONFIG_ATH_DEBUG)		+= drivers/wireless/ath/debug.o


#bigfatwifi-$(CONFIG_ATH9K_PCI)		+= drivers/wireless/ath/ath9k/pci.o
#bigfatwifi-$(CONFIG_ATH9K_AHB) 	+= drivers/wireless/ath/ath9k/ahb.o

bigfatwifi-$(CONFIG_ATH9K_DEBUGFS) 	+= drivers/wireless/ath/ath9k/debug.o


bigfatwifi-$(CONFIG_ATH9K_HW)		+= drivers/wireless/ath/ath9k/ar9002_hw.o \
					   drivers/wireless/ath/ath9k/ar9003_hw.o \
					   drivers/wireless/ath/ath9k/hw.o \
					   drivers/wireless/ath/ath9k/ar9003_phy.o \
					   drivers/wireless/ath/ath9k/ar9002_phy.o \
					   drivers/wireless/ath/ath9k/ar5008_phy.o \
					   drivers/wireless/ath/ath9k/ar9002_calib.o \
					   drivers/wireless/ath/ath9k/ar9003_calib.o \
					   drivers/wireless/ath/ath9k/calib.o \
					   drivers/wireless/ath/ath9k/eeprom.o \
					   drivers/wireless/ath/ath9k/eeprom_def.o \
					   drivers/wireless/ath/ath9k/eeprom_4k.o \
					   drivers/wireless/ath/ath9k/eeprom_9287.o \
					   drivers/wireless/ath/ath9k/ani.o \
					   drivers/wireless/ath/ath9k/btcoex.o \
					   drivers/wireless/ath/ath9k/mac.o \
					   drivers/wireless/ath/ath9k/ar9002_mac.o \
					   drivers/wireless/ath/ath9k/ar9003_mac.o \
					   drivers/wireless/ath/ath9k/ar9003_eeprom.o \
					   drivers/wireless/ath/ath9k/ar9003_paprd.o



bigfatwifi-$(CONFIG_ATH9K_COMMON)	+= drivers/wireless/ath/ath9k/common.o
bigfatwifi-$(CONFIG_ATH9K_RATE_CONTROL) += drivers/wireless/ath/ath9k/rc.o


bigfatwifi-$(CONFIG_ATH9K_HTC) 		+= drivers/wireless/ath/ath9k/htc_hst.o \
					   drivers/wireless/ath/ath9k/hif_usb.o \
					   drivers/wireless/ath/ath9k/wmi.o \
					   drivers/wireless/ath/ath9k/htc_drv_txrx.o \
					   drivers/wireless/ath/ath9k/htc_drv_main.o \
					   drivers/wireless/ath/ath9k/htc_drv_beacon.o \
					   drivers/wireless/ath/ath9k/htc_drv_init.o \
				 	   drivers/wireless/ath/ath9k/htc_drv_gpio.o

bigfatwifi-$(CONFIG_ATH9K_HTC_DEBUGFS) 	+= drivers/wireless/ath/ath9k/htc_drv_debug.o
#----------------------------------------------------------------------------------------
#----------------------------------------------------------------------------------------
#add more drivers above			||<---try to keep things between these lines--->||
#
#also add the driver's init/exit functions to the init/exit file (load.c).
#----------------------------------------------------------------------------------------
#----------------------------------------------------------------------------------------