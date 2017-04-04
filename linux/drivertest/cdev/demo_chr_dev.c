#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include <linux/seq_file.h>
#include <linux/proc_fs.h>

static struct cdev chr_dev;
static dev_t ndev;

static int chr_open(struct inode *nd, struct file *filp)
{
  int major = MAJOR(nd->i_rdev);
  int minor = MINOR(nd->i_rdev);

  printk("chr_open,major=%d, minor=%d\n",major,minor);
  return 0;
}


static ssize_t chr_read(struct file *f, char __user *u, size_t sz,loff_t *off)
{                                                                                                                                                               
    printk("In the chr_read() function!\n"); 
   return 0;
}

struct file_operations chr_ops= 
{
   .owner = THIS_MODULE,
   .open = chr_open,
   .read = chr_read,
};

static ssize_t proc_ausu_flash_brightness_read(struct file *file, const char *buffer, size_t count, loff_t *ppos)
{
   printk("[ausu test] read\n");
   unsigned long p = *ppos;
   int ret = 0;
   
   char val[20];  
   printk(KERN_ERR "###### global_read \n");  
      
   sprintf(val, "%s\n", g_val);  
   //ssize_t simple_read_from_buffer(void __user *to, size_t count,loff_t *ppos, const void *from, size_t available);  
   ret = simple_read_from_buffer(buf, len, off, val, strlen(val));  
   return ret; 
    
}

static ssize_t proc_ausu_flash_brightness_write(struct file *file, char *buffer, size_t count, loff_t *ppos)
{

  printk("[ausu test]count = %ld\n",count);
  return 0;
}

static const struct file_operations ausu_flash_brightness_fops = 
{

  .owner   = THIS_MODULE,
  .read = proc_ausu_flash_brightness_read,
  .write = proc_ausu_flash_brightness_write,

};

static int demo_init(void)
{
  int ret;
  cdev_init(&chr_dev,&chr_ops);
  ret = alloc_chrdev_region(&ndev,0,0,"chr_dev");
  if(ret < 0) 
      return ret;

  
  printk("demo_init():major = %d,minor = %d\n",MAJOR(ndev),MINOR(ndev));

  ret = cdev_add(&chr_dev,ndev,1);

  if(ret < 0)
       return ret;

  proc_create("driver/ausu_flash_brightness",0666, NULL, &ausu_flash_brightness_fops);
  return 0;

}


static void demo_exit(void)
{
  
   printk("Removing chr_dev module..\n");

   cdev_del(&chr_dev);
   unregister_chrdev_region(ndev,1);

}


module_init(demo_init);
module_exit(demo_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Dennis @AMD Linux FGL");
MODULE_DESCRIPTION("A char device driver as an example");



