#include<linux/init.h>
#include <linux/module.h>
#include <linux/kthread.h>
#include <linux/timer.h>


MODULE_LICENSE("Dual BSD/GPL");
extern void msleep(int );
static struct task_struct *tsk;

static  int thread_function(void *data)
{

	int time_count = 0;

	do {
		printk(KERN_INFO "thread_function:%d times",++time_count);
		msleep(1000);
	}while (!kthread_should_stop()&& time_count <= 30);
	return time_count;
}
static int hello_init(void)
{
	printk(KERN_INFO "HELLO,world/h");

	tsk = kthread_run(thread_function,NULL,"fox_thread%d",1);

	if(!IS_ERR(tsk)){
		printk(KERN_INFO "create kthread fail\n");
	} else {
		printk(KERN_INFO "create kthread ok!\n");
	}
	return 0;

}

static void hello_exit(void)
{
	printk(KERN_INFO "hello exit\n");

	if(!IS_ERR(tsk)) {
		int ret = kthread_stop(tsk);
		printk(KERN_INFO "thread function has run %d\n",ret);
	}
}

module_init(hello_init);
module_exit(hello_exit);



