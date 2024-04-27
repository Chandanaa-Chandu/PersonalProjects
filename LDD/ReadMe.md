# Linux Device Driver

Here you can find all the examples for simple Linux Kernel Modules and Linux Drivers.

## Preperation 

I have used a Raspberry Pi 2 Model B to develop and test the kernel modules and drivers. To compile these modules, we need to install the kernel headers on our Raspberry Pi OS. We can you do this with the following commands:

```bash
sudo apt update
sudo apt install raspberrypi-kernel-headers
```

Raspberry Pi OS is only installs the latest kernel headers. So, make sure, we are running the latest kernel. We can do this by running the below commands:

```bash
sudo apt upgrade
```

We also need the build utils (make, gcc, ...)

To Run the kernel module, follow the below steps:
- Step1: Create a device file in .c and write the kernel module code
- Step2: Create a Makefile
- Step3: Open Makefile and specify the object file that should be built
- Step4: Specify the directory where the kernel source code resides (/lib/modules/$(shell uname -r)/build)
- Step5: Specify the directory containing the module source code resides (M=$(PWD))

## Contents

In this directory we can find the examples for:
1. Simple Kernel Module
