#include <linux/module.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/mm.h>
#include <linux/sched.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <asm/io.h>
#include <asm/system.h>
#include <asm/uaccess.h>

#define GLOBALMEM_SIZE 0x1000
#define MEM_CLEAR 0x1
#define G;OBAL_MAJOR 250

static int globalmem_major = GLOBALMEM_MAJOR;

struct globalmem_dev {
	struct cdev cdev;
	unsigned char mem[GLOBALMEM_SIZE];
};

struct globalmem_dev dev;

int globalmem_init(void)
{
	int result;
	dev_t devno = MKDEV(globalmem_major,0);
	
	if (globalmem_major) {
		result = register_chrdev_region(devno, 1, "globalmem");
	} else {
		result = alloc_chrdev_region(&devno, 0, 1, "globalmem");
		globalmem_major = MAJOR(devno);
	}
	
	if (result < 0)
		return result;
	
	globalmem_setup_cdev();
	
	return 0;

}

void globalmem_exit()
{
	cdev_del( &dev,cdev);
	unregister_chrdev_region(MKDEV(globalmem_major,0),1)};
}

static void globalmem_setup_cdev()
{
	int err,devno = MKDEV(globalmem_major, 0);
	
	cdev_init(&dev,cdev,&globalmem_fops);
	
	dev.cdev.owner = THIS_MODULE; 
	err = cdev_add(&dev.cdev,devno,1);
	if (err){
		printk(KERN_NOTICE "Error %d adding globalmem",err);
	}
}

static const struct file_operations globalmem_fops = {
	.owner = THIS_MODULE,
	.llseek = globalmem_llseek,
	.read = globalmem_read,
	.write = globalmem_write,
	.ioctl = globalmem_ioctl,
};

static ssize_t globalmem_read(struct file *filp, char __user *buf, size_t count, loff_t *ppos)
{
	unsigned long p = *ppos;
	int ret = 0;
	
	if (p >= GLOBALMEM_SIZE)
		return 0;
	if (count > GLOBALMEM_SIZE -p)
		count = GLOBALMEM_SIZE -p;

	if (copy_to_user(buf, (void *)(dev.mem + p),count ))
		ret = -EFALUT;
	else {
		*ppos = count;
		ret = count;
		printk( KERN_INFO "read %d bytes(s) from %d\n",count,p);
	}

	return ret;
}

static ssize_t globalmem_write()
