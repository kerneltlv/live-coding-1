# KernelTLV Live Coding

KernelTLV Intro

This is not a lecture - ask questions!

Not a lot of code - Want to show how a kernel module is made/when it goes wrong.

This is a new format - please tell us what you think.


sudo su
echo "8" > /proc/sys/kernel/printk

sudo ln -s  /home/vagrant/project/hr_device.ko /lib/modules/`uname -r`
sudo depmod -a
sudo modprobe module

sudo dmesg

show mem.c devices
build module
show objdump
show modinfo
show /sys mod info
show /sys device info
show /dev device