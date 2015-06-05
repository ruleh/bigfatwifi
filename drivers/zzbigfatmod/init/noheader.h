/* This is the header file for load.c
** Here you can declare all the functions/structures/etc
** This can also be used to include other header files needed by load.c
*/
#include <linux/usb.h>

/*rt2x00*/
extern struct usb_driver rt73usb_driver ;
extern struct usb_driver rt2500usb_driver ;
extern struct usb_driver rt2800usb_driver ;

/*rtl8187*/
extern struct usb_driver rtl8187_driver ;

/*ath9k*/
extern struct usb_driver ath9k_hif_usb_driver;
extern struct rate_control_ops ath_rate_ops;