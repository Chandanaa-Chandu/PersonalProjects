# Register a Character device using device number

## Description

Open/Close a device file through user space application using device file path

To create a device file,

```bash
sudo mknod /dev/<file_name> c <major_nr> <minor_nr>
```

Steps to run:
1. Create module in .c 
2. Create Makefile and build
3. Insert module into kernel
4. Display the log to know registered major and minor numbers
4. Create a device file
5. Run a user space application
