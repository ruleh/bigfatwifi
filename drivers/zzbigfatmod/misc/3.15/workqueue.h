extern struct workqueue_struct *system_wq __read_mostly;
extern struct workqueue_struct *system_long_wq __read_mostly;
extern struct workqueue_struct *system_nrt_wq __read_mostly;
extern struct workqueue_struct *system_unbound_wq __read_mostly;
extern struct workqueue_struct *system_freezable_wq __read_mostly;
extern struct workqueue_struct *system_nrt_freezable_wq __read_mostly;

extern void __init_work(struct work_struct *work, int onstack);

extern void destroy_work_on_stack(struct work_struct *work);

extern int queue_work(struct workqueue_struct *wq, struct work_struct *work);

extern int queue_work_front(struct workqueue_struct *wq, struct work_struct *work);

extern int queue_work_on(int cpu, struct workqueue_struct *wq, struct work_struct *work);

extern int queue_delayed_work(struct workqueue_struct *wq,
			struct delayed_work *dwork, unsigned long delay);

extern int queue_delayed_work_on(int cpu, struct workqueue_struct *wq,
			struct delayed_work *dwork, unsigned long delay);

extern void flush_workqueue(struct workqueue_struct *wq);

extern bool flush_work(struct work_struct *work);

extern bool flush_work_sync(struct work_struct *work);

extern bool cancel_work_sync(struct work_struct *work);

extern bool flush_delayed_work(struct delayed_work *dwork);

extern bool flush_delayed_work_sync(struct delayed_work *dwork);

extern bool cancel_delayed_work_sync(struct delayed_work *dwork);

extern int schedule_work(struct work_struct *work);

extern int schedule_work_on(int cpu, struct work_struct *work);

extern int schedule_delayed_work(struct delayed_work *dwork,
					unsigned long delay);

extern int schedule_delayed_work_on(int cpu,
			struct delayed_work *dwork, unsigned long delay);

extern int execute_in_process_context(work_func_t fn, struct execute_work *ew);

extern void flush_scheduled_work(void);

extern struct workqueue_struct *__alloc_workqueue_key(const char *name,
					       unsigned int flags,
					       int max_active,
					       struct lock_class_key *key,
					       const char *lock_name);

extern void destroy_workqueue(struct workqueue_struct *wq);

extern void workqueue_set_max_active(struct workqueue_struct *wq, int max_active);

extern bool workqueue_congested(unsigned int cpu, struct workqueue_struct *wq);

extern unsigned int work_cpu(struct work_struct *work);

extern unsigned int work_busy(struct work_struct *work);

extern long work_on_cpu(unsigned int cpu, long (*fn)(void *), void *arg);

