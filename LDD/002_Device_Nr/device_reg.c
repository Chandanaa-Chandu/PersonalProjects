#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>

/* Meta Information */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Chandana R");
MODULE_DESCRIPTION("Register a character device with device number");

/* variabled used in this devie file */
#define MAJOR_NUM	2
#define DEVICE_NAME	"device_reg_chrdev"

/**
 * @brief This function is called, when the device file is opened
 */
static int driver_open(struct inode *device_file, struct file *instance) {
	printk("device_reg - Device file Open was called\n");
	return 0;
}

/**
 * @brief This function is called, when the device file is closed
 */
static int driver_close(struct inode *device_file, struct file *instance) {
	printk("device_reg - Device file close was called\n");
	return 0;
}

/* Define the file operations */
static struct file_operations fops = {
	.owner = THIS_MODULE,
	.open = driver_open,
	.release = driver_close
};

/**
 * @brief This function is called, when the module loaded into kernel
 */
static int __init ModuleInit(void) {
	int retval;

	printk("device_reg - module is loading into kernel\n");

	/* Register a character device with the kernel */
	retval = register_chrdev(MAJOR_NUM, DEVICE_NAME, &fops);
	if(retval == 0) {
		printk("device_reg - Device regsitered with Major:%d and Minor:%d numbers\n",MAJOR_NUM,0);
	} else if(retval > 0) {
		printk("device_reg - Device registered with major:%d and Minor:%d number\n", retval>>20, retval&0xfffff);
	} else {
		printk("device_reg - Device could not register\n");
		return -1;
	}
	return 0;
}

/**
 * @brief This function is called, when the module is unloaded from the kernel
 */
static void __exit ModuleExit(void) {
	unregister_chrdev(MAJOR_NUM, DEVICE_NAME);
	printk("device_reg - module is Unloading from the kernel\n");
}

module_init(ModuleInit);
module_exit(ModuleExit);
