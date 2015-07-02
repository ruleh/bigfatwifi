/*This file contains the symbols that are no longer present
 *as external functions inside the module itself
 *I should have done this earlier
 */

#include <linux/workqueue.h>
#include <linux/platform_device.h>
#include <linux/bottom_half.h>
#include <linux/skbuff.h>
#include <linux/interrupt.h>
#include <linux/random.h>
#include <linux/kernel_stat.h>
#include <mach/sec_debug.h>
#include <linux/sched.h>

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

DEFINE_PER_CPU(struct task_struct *, ksoftirqd);


static void wakeup_softirqd(void)
{
        /* Interrupts are disabled: no need to stop preemption */
        struct task_struct *tsk = __this_cpu_read(ksoftirqd);

        if (tsk && tsk->state != TASK_RUNNING)
                wake_up_process(tsk);
}


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



static void __local_bh_enable(unsigned int cnt)
{
	WARN_ON_ONCE(in_irq());
	WARN_ON_ONCE(!irqs_disabled());

	if (softirq_count() == cnt)
		trace_softirqs_on((unsigned long)__builtin_return_address(0));
	sub_preempt_count(cnt);
}



static inline void _local_bh_enable_ip(unsigned long ip)
{
	WARN_ON_ONCE(in_irq() || irqs_disabled());
#ifdef CONFIG_TRACE_IRQFLAGS
	local_irq_disable();
#endif

	if (softirq_count() == SOFTIRQ_DISABLE_OFFSET)
		trace_softirqs_on(ip);

	sub_preempt_count(SOFTIRQ_DISABLE_OFFSET - 1);

	if (unlikely(!in_interrupt() && local_softirq_pending()))
		do_softirq();

	dec_preempt_count();
#ifdef CONFIG_TRACE_IRQFLAGS
	local_irq_enable();
#endif
	preempt_check_resched();
}


extern void local_bh_enable(void)
{
	_local_bh_enable_ip((unsigned long)__builtin_return_address(0));
}


/*skbuff*/
extern struct sk_buff *dev_alloc_skb(unsigned int length)
{
	return __dev_alloc_skb(length, GFP_ATOMIC);
}

/*random32*/
static DEFINE_PER_CPU(struct rnd_state, net_rand_state);

extern u32 prandom32(struct rnd_state *state)
{
#define TAUSWORTHE(s,a,b,c,d) ((s&c)<<d) ^ (((s <<a) ^ s)>>b)

        state->s1 = TAUSWORTHE(state->s1, 13, 19, 4294967294UL, 12);
        state->s2 = TAUSWORTHE(state->s2, 2, 25, 4294967288UL, 4);
        state->s3 = TAUSWORTHE(state->s3, 3, 11, 4294967280UL, 17);

        return (state->s1 ^ state->s2 ^ state->s3);
}

extern u32 random32(void)
{
        unsigned long r;
        struct rnd_state *state = &get_cpu_var(net_rand_state);
        r = prandom32(state);
        put_cpu_var(state);
        return r;
}
/*bug  <--cause what is a module without one*/
extern void __attribute__((noreturn)) __bug(const char *file, int line)
{
        printk(KERN_CRIT"kernel BUG at %s:%d!\n", file, line);
        *(int *)0 = 0;

        /* Avoid "noreturn function does return" */
        for (;;);
}
