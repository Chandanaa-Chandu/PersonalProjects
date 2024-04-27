# Simple Linux Kernel Module

Steps to run:
1. Create a simple_lkm.c file add the code
2. Create a Makefile and add the code
3. Run below command:

```bash
make
```

4. Insert the module into kernel by following command:

```bash
sudo insmod simple_lkm.ko
```

5. Display the log:

```bash
sudo dmesg | tail -n 10
```

6. Remove the module from the kernel by following command:

```bash
sudo rmmod simple_lkm
```

7. Display the log:

```bash
sudo dmesg | tail -n 10
```
