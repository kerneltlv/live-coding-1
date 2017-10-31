# KernelTLV Live Coding Session #1 Demo
Code for Live Coding Session 1.

To use, clone this repository using git, then:

1. Install Vagrant.
1. Install VirtualBox (or your favorite VM provider that's supported by Vagrant)
1. If using VirtualBox, install the vagrant-vbguest plugin.
1. Run `vagrant up` to create a shiny new VM.
1. To build the kernel module, run `make -C /lib/modules/`uname -r`/build M=$PWD` in the `/project` directory.
1. Experiment!

Have fun,

KernelTLV Team