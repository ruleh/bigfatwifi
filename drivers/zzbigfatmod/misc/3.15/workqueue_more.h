extern struct workqueue_struct *system_wq __read_mostly;
extern struct workqueue_struct *system_long_wq __read_mostly;
extern struct workqueue_struct *system_nrt_wq __read_mostly;
extern struct workqueue_struct *system_unbound_wq __read_mostly;
extern struct workqueue_struct *system_freezable_wq __read_mostly;
extern struct workqueue_struct *system_nrt_freezable_wq __read_mostly;




extern int execute_in_process_context(work_func_t fn, struct execute_work *ew);


extern struct workqueue_struct *__alloc_workqueue_key(const char *name,
					       unsigned int flags,
					       int max_active,
					       struct lock_class_key *key,
					       const char *lock_name);

extern void workqueue_set_max_active(struct workqueue_struct *wq, int max_active);

extern long work_on_cpu(unsigned int cpu, long (*fn)(void *), void *arg);

