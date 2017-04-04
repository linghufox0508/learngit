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

	return rc;
}

static void __exit helloworld_exit(void)
{
	platform_driver_unregister(&helloworld_platform_driver);
	return;
}



module_init(helloworld_init);
module_exit(helloworld_exit);
MODULE_DESCRIPTION("HELLO WORLD");
MODULE_LICENSE("GPL v2");

