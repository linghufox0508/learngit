/* Copyright (c) 2009-2016, The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include <linux/module.h>
#include <linux/of_gpio.h>
#include <linux/platform_device.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/fs.h>
#include<linux/cdev.h>


static struct cdev chr_dev;
static dev_t ndev;

//#include <debug.h>
static const struct of_device_id helloworld_dt_match[] = {
	{.compatible = "hq,hello world", .data = NULL},
	{}
};

static int32_t helloworld_platform_probe(struct platform_device *pdev)
{
    pr_err("[hq]pdev->name = %s\n",pdev->name);
    pr_err("[hq]pdev.dev->of_node->name = %s\n",pdev->dev.of_node->name);
    printk("[hq]hello world,probe succeed \n");
    return 0;
}

static  int chr_open(struct inode *nd,struct file *flip)
{
	int major = MAJOR(nd->i_rdev);
	int minor = MINOR(nd->i_rdev);
	printk("chr_open,major = %d,minor = %d\n",major,minor);
	return 0;
}


static ssize_t chr_read(struct file *f,char __user *u,size_t sz,loff_t *off)
{
	printk("In the chr_read()function\n");
	printk("hello world\n");
	return 0;
}

struct file_operations chr_ops = 
{
	.owner = THIS_MODULE,
	.open = chr_open,
	.read = chr_read,
	//.ioctl = NULL,
	.write = NULL,
	.unlocked_ioctl = NULL,
};


static int demo_init(void)
{
	int ret;
	cdev_init(&chr_dev,&chr_ops);
	ret = alloc_chrdev_region(&ndev,0,1,"chr_dev");//分配设备号
	if (ret < 0)
		return ret;
	
	printk("demo_init:major = %d,minor = %d\n",MAJOR(ndev),MINOR(ndev));
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
static struct platform_driver helloworld_platform_driver = {
	.probe = helloworld_platform_probe,
	.driver = {
		.name = "HQ,hello world",
		.owner = THIS_MODULE,
		.of_match_table = helloworld_dt_match,
	},
};

static int __init helloworld_init(void)
{
	int32_t rc = 0;
	printk("Enter\n");
	rc = platform_driver_register(&helloworld_platform_driver);
	if (rc)
		pr_err("platform probe for hello world failed");
     
     
    rc = demo_init();
    if (rc)
		pr_err("demo_init failed");
		
	return rc;
}

static void __exit helloworld_exit(void)
{
    demo_exit();
	platform_driver_unregister(&helloworld_platform_driver);
	return;
}



module_init(helloworld_init);
module_exit(helloworld_exit);
MODULE_DESCRIPTION("HELLO WORLD");
MODULE_LICENSE("GPL v2");

