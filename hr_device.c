#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/fs.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("KernelTLV");
MODULE_DESCRIPTION("An imaginary heart rate monitor");
MODULE_VERSION("0.1");

static int __init hr_device_init(void)
{
    printk(KERN_INFO "Heart rate monitor driver loaded!\n");
    return 0;
}

static void __exit hr_device_exit(void)
{
    printk(KERN_INFO "Heart rate monitor driver unloaded!\n");
}

module_init(hr_device_init);
module_exit(hr_device_exit);
