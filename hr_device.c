#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/random.h>
#include <linux/uaccess.h>

#include "hr_device.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("KernelTLV");
MODULE_DESCRIPTION("An imaginary heart rate monitor");
MODULE_VERSION("0.1");

static int major = 0;
static unsigned char heart_rate = 127;
static struct class *hr_class = NULL;
static struct device *hr_device = NULL;

static int hr_open(struct inode *inode, struct file *filp)
{
    return 0;
}

static unsigned char new_hr_value(unsigned char hr_value)
{
    char random = 0;
    get_random_bytes(&random, sizeof(random));

    if (random < 0)
    {
        return clamp(heart_rate - HEART_RATE_DELTA, 0, 255);
    }
    else
    {
        return clamp(heart_rate + HEART_RATE_DELTA, 0, 255);
    }
}

static ssize_t hr_read(struct file *file, char __user *buf,
			 size_t count, loff_t *ppos)
{
    ssize_t pos = 0;

    while (count > 0)
    {
        heart_rate = new_hr_value(heart_rate);
        printk(KERN_DEBUG "%s: new heart rate value: %d\n", __func__, heart_rate);
        if (copy_to_user(buf, &heart_rate, 1))
        {
            return -EFAULT;
        }
        ++buf;
        ++pos;
        --count;
    }

    return pos;
}

static const struct file_operations hr_fops = {
	.open = hr_open,
	.read = hr_read,
	.llseek = noop_llseek,
};

static int __init hr_device_init(void)
{
    printk(KERN_INFO "Heart rate monitor driver loaded!\n");

    major = register_chrdev(0, DEVICE_NAME, &hr_fops);
    if (major < 0)
    {
		printk(KERN_INFO "Unable to register hr device\n");
		return major;
	}

	printk(KERN_INFO "Registered heart rate monitor device: %d\n", major);

	hr_class = class_create(THIS_MODULE, DEVICE_NAME);
	if (IS_ERR(hr_class))
	{
	    unregister_chrdev(major, DEVICE_NAME);
		return PTR_ERR(hr_class);
    }

    hr_device = device_create(hr_class, NULL, MKDEV(major, 0), NULL, DEVICE_NAME);
    if (IS_ERR(hr_device))
    {
        class_destroy(hr_class);
        unregister_chrdev(major, DEVICE_NAME);
        return PTR_ERR(hr_device);
    }
    return 0;
}

static void __exit hr_device_exit(void)
{
    device_destroy(hr_class, MKDEV(major, 0));
    class_destroy(hr_class);
    unregister_chrdev(major, DEVICE_NAME);

    printk(KERN_INFO "Heart rate monitor driver unloaded!\n");
}

module_init(hr_device_init);
module_exit(hr_device_exit);