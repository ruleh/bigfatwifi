/*This file contains the symbols that are no longer present
 *as external functions inside the module itself
 *I should have done this earlier
 */

#include <linux/workqueue.h>
#include <linux/platform_device.h>
#include <linux/bottom_half.h>
#include <linux/skbuff.h>
#include <linux/hardirq.h>


/*workqueue*/
extern int queue_delayed_work(struct workqueue_struct *wq,
			struct delayed_work *dwork, unsigned long delay)
{
	if (delay == 0)
		return queue_work(wq, &dwork->work);

	return queue_delayed_work_on(-1, wq, dwork, delay);
}

extern int queue_work(struct workqueue_struct *wq, struct work_struct *work)
{
	int ret;

	ret = queue_work_on(get_cpu(), wq, work);
	put_cpu();

	return ret;
}


extern int schedule_work(struct work_struct *work)
{
	return queue_work(system_wq, work);
}


extern int schedule_work_on(int cpu, struct work_struct *work)
{
	return queue_work_on(cpu, system_wq, work);
}

extern int schedule_delayed_work(struct delayed_work *dwork,
					unsigned long delay)
{
	return queue_delayed_work(system_wq, dwork, delay);
}

/*platform*/
extern struct platform_device *platform_device_register_resndata(
		struct device *parent,
		const char *name, int id,
		const struct resource *res, unsigned int num,
		const void *data, size_t size)
{
	int ret = -ENOMEM;
	struct platform_device *pdev;

	pdev = platform_device_alloc(name, id);
	if (!pdev)
		goto err;

	pdev->dev.parent = parent;

	ret = platform_device_add_resources(pdev, res, num);
	if (ret)
		goto err;

	ret = platform_device_add_data(pdev, data, size);
	if (ret)
		goto err;

	ret = platform_device_add(pdev);
	if (ret) {
err:
		platform_device_put(pdev);
		return ERR_PTR(ret);
	}

	return pdev;
}

/*bottom_half*/
static inline void __local_bh_disable(unsigned long ip, unsigned int cnt)
{
	add_preempt_count(cnt);
	barrier();
}

extern void local_bh_disable(void)
{
	__local_bh_disable((unsigned long)__builtin_return_address(0),
				SOFTIRQ_DISABLE_OFFSET);
}

/*skbuff*/
extern struct sk_buff *dev_alloc_skb(unsigned int length)
{
	return __dev_alloc_skb(length, GFP_ATOMIC);
}