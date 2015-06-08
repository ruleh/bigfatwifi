/* This is the header file for load.c
** Here you can declare all the functions/structures/etc that are used by load.c
** This can also be used to include other header files needed by load.c
*/
#include "../wireless/sysfs.h"
#include "../wireless/nl80211.h"
#include "../wireless/reg.h"
#include "../wireless/core.h"

/*cfg80211*/
extern struct pernet_operations cfg80211_pernet_ops;
extern struct notifier_block cfg80211_netdev_notifier;
extern struct dentry *ieee80211_debugfs_dir;

/*lib80211*/
extern struct lib80211_crypto_ops lib80211_crypt_null;

/*cfg wext*/
extern struct pernet_operations wext_pernet_ops;

/*rt2x00*/
extern struct usb_driver rt73usb_driver;
extern struct usb_driver rt2500usb_driver;
extern struct usb_driver rt2800usb_driver;

/*rtl8187*/
extern struct usb_driver rtl8187_driver;

/*ath9k*/
extern struct usb_driver ath9k_hif_usb_driver;
extern struct rate_control_ops ath_rate_ops;