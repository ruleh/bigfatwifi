/* This is the init/exit file for the bigfat module
** All init and exit functions are defined here in one place
** Note that no init function should return 0.
** Only use return for errors. 
**
**the included .c files need to be removed in the near future
**and be replaced by .h files included in noheader.h
*/
#include "../wireless/lib80211.c"
#include "../wireless/core.c"
#include "../wireless/wext-core.c"
#include "../mac80211/main.c"
#include "noheader.h"


MODULE_AUTHOR("ruleh");
MODULE_DESCRIPTION("Bigfatwifi--a collection of your favourite wifi drivers");
MODULE_DESCRIPTION("All credit goes to the people responsible for each component");
MODULE_LICENSE("GPL");

static int __init bigfat_init(void)
{

/*cfg80211 init*/
	pr_info(DRV_DESCRIPTION "\n");



	int err;

	err = register_pernet_device(&cfg80211_pernet_ops);
	if (err)
		goto out_fail_pernet;

	err = wiphy_sysfs_init();
	if (err)
		goto out_fail_sysfs;

	err = register_netdevice_notifier(&cfg80211_netdev_notifier);
	if (err)
		goto out_fail_notifier;

	err = nl80211_init();
	if (err)
		goto out_fail_nl80211;

	ieee80211_debugfs_dir = debugfs_create_dir("ieee80211", NULL);

	err = regulatory_init();
	if (err)
		goto out_fail_reg;

	cfg80211_wq = create_singlethread_workqueue("cfg80211");
	if (!cfg80211_wq)
		goto out_fail_wq;



/*mac80211 init*/
	struct sk_buff *skb;
	int ret;

	BUILD_BUG_ON(sizeof(struct ieee80211_tx_info) > sizeof(skb->cb));
	BUILD_BUG_ON(offsetof(struct ieee80211_tx_info, driver_data) +
		     IEEE80211_TX_INFO_DRIVER_DATA_SIZE > sizeof(skb->cb));

	ret = rc80211_minstrel_init();
	if (ret)
		return ret;

	ret = rc80211_minstrel_ht_init();
	if (ret)
		goto err_minstrel;

	ret = rc80211_pid_init();
	if (ret)
		goto err_pid;

	ret = ieee80211_iface_init();
	if (ret)
		goto err_netdev;


/*cfg wext*/
	register_pernet_subsys(&wext_pernet_ops);

	
/*rt2x00*/
	usb_register(&rt73usb_driver);
	usb_register(&rt2500usb_driver);
	usb_register(&rt2800usb_driver);

/*rtl8187*/
	usb_register(&rtl8187_driver);

/*ath9k*/
	usb_register(&ath9k_hif_usb_driver);
	ieee80211_rate_control_register(&ath_rate_ops);


	return 0;


/*errors*/

/*cfg e*/
out_fail_wq:
	regulatory_exit();
out_fail_reg:
	debugfs_remove(ieee80211_debugfs_dir);
out_fail_nl80211:
	unregister_netdevice_notifier(&cfg80211_netdev_notifier);
out_fail_notifier:
	wiphy_sysfs_exit();
out_fail_sysfs:
	unregister_pernet_device(&cfg80211_pernet_ops);
out_fail_pernet:
	return err;


/*mac e*/	
 err_netdev:
	rc80211_pid_exit();
 err_pid:
	rc80211_minstrel_ht_exit();
 err_minstrel:
	rc80211_minstrel_exit();

	return ret;
}

static void __exit bigfat_exit(void)
{
/*ath9k*/
	usb_deregister(&ath9k_hif_usb_driver);
	ieee80211_rate_control_unregister(&ath_rate_ops);

/*rt2x00*/
	usb_deregister(&rt73usb_driver);
	usb_deregister(&rt2500usb_driver);
	usb_deregister(&rt2800usb_driver);

/*rtl8187*/
	usb_deregister(&rtl8187_driver);


/*mac80211 exit*/
	rc80211_pid_exit();
	rc80211_minstrel_ht_exit();
	rc80211_minstrel_exit();

	if (mesh_allocated)
		ieee80211s_stop();

	ieee80211_iface_exit();

	rcu_barrier();



/*cfg80211 exit*/
	debugfs_remove(ieee80211_debugfs_dir);
	nl80211_exit();
	unregister_netdevice_notifier(&cfg80211_netdev_notifier);
	wiphy_sysfs_exit();
	regulatory_exit();
	unregister_pernet_device(&cfg80211_pernet_ops);
	destroy_workqueue(cfg80211_wq);
	lib80211_unregister_crypto_ops(&lib80211_crypt_null);
	BUG_ON(!list_empty(&lib80211_crypto_algs));
}


subsys_initcall(bigfat_init);
module_exit(bigfat_exit);