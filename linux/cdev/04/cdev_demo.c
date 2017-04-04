#include <linux/module.h>
#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>


#define GLOBALMEM_SIZE 0x1000
#define GLOBALMEM_MAJOR 250

static int globalmem_major = GLOBALMEM_MAJOR

struct globalmem_dev {
     struct cdev cdev;
     unsigned char mem[GLOBALMEM_SIZE];
};

struct globalmem_dev dev;

static  int chr_open(struct inode *nd,struct file *flip)
{
	int major = MAJOR(nd->i_rdev);
	int minor = MINOR(nd->i_rdev);
	printk("chr_open... \n");
	//printk("chr_open,major = %d,minor = %d\n",major,minor);

	return 0;
}

static ssize_t chr_read(struct file *f,char __user *u,size_t sz,loff_t *off)
{
	printk("In the chr_read... \n");
	return 0;
}

static ssize_t chr_write(struct file *f,const char __user *u,size_t sz,loff_t *off)
{
	printk("In the chr_write... \n");
	return 0;
}

struct file_operations chr_ops = 
{
	.owner = THIS_MODULE,
	.open = chr_open,
	.read = chr_read,
	//.ioctl = NULL,
	.write = chr_write,
	.unlocked_ioctl = NULL,
};

static int demo_init(void)
{
	int ret;
	cdev_init(&chr_dev,&chr_ops);
	ret = alloc_chrdev_region(&ndev,0,1,"chr_dev");//分配设备号
	if (ret < 0)
		return ret;
	
	printk("demo_init... \n");
	printk("major = %d,minor = %d\n",MAJOR(ndev),MINOR(ndev));
	ret = cdev_add(&chr_dev,ndev,1);
	if(ret < 0)
		 return ret;
	return 0;
}

static void demo_exit(void)
{
	printk("Removing chr_dev module ..\n");
	cdev_del(&chr_dev);
	unregister_chrdev_region(ndev,1);
}

module_init(demo_init)
module_exit(demo_exit)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("xxxx");
MODULE_DESCRIPTION("a char device driver example");
