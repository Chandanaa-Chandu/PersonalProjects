#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/cdev.h>

/* Meta Information */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Chandana R");
MODULE_DESCRIPTION("Register a character device and device file dynamically, implemented read and write funcions");

/* Variables regarding the buffers */
static char buffer[255];
static int buffer_pointer = 0;

/* Variables for device and device class */
static dev_t device_num;
static struct class *device_class;
static struct cdev chr_device;

#define DRIVER_NAME	"devfile_rw_chrdriver"
#define DRIVER_CLASS	"ModuleClass"

/**
 * @brief This function is called, to read the data buffer to user
 */
static ssize_t driver_read(struct file *file, char *user_buffer, size_t length, loff_t *offset) {
	int to_copy, not_copied, delta;

	/* Calculate the amount of data to be read out */
	to_copy = min(length, buffer_pointer);

	/* Copy data to User */
	not_copied = copy_to_user(user_buffer, buffer, to_copy);

	delta = to_copy - not_copied;

	return delta;
}

/**
 * @brief This function is called, to write the data from user
 */
static ssize_t driver_write(struct file *file, const char *user_buffer, size_t length, loff_t *offset) {
	int to_copy, not_copied, delta;

	/* Calculate the amount of data to copy */
	to_copy = min(length, sizeof(buffer));

	/* Copy data from user */
	not_copied = copy_from_user(buffer, user_buffer, to_copy);
	buffer_pointer = to_copy;

	delta = to_copy - not_copied;

	return delta;
}

/**
 * @brief This function is called, when the device file is opened
 */
static int driver_open(struct inode *device_file, struct file *instance) {
	printk("devfile_rw - Device file is Opened\n");
	return 0;
}

/**
 * @brief This function is called, when the device file is closed
 */
static int driver_close(struct inode *device_file, struct file *instance) {
	printk("devfile_rw - Device file is closed\n");
	return 0;
}

/* Specify the file operations */
static struct file_operations fops = {
	.owner = THIS_MODULE,
	.open = driver_open,
	.release = driver_close,
	.read = driver_read,
	.write = driver_write
};

static int __init ModuleInit(void) {
	printk("devfile_rw - Module is Entering into kernel\n");

	/* Allocate a device number dynamically */
	if(alloc_chrdev_region(&device_num, 0, 1, DRIVER_NAME) < 0) {
		printk("devfile_rw - Could not allocate a device number!\n");
		return -1;
	}

	printk("devfile_rw - Device registered with major:%d and minor:%d numbers successfully\n", device_num >> 20, device_num & 0xfffff);

	/* Create a device class */
	if((device_class = class_create(DRIVER_CLASS)) == NULL) {
		printk("devfile_rw - Could not create a device class\n");
		goto ClassError;
	}

	/* Create a device file */
	if(device_create(device_class, NULL, device_num, NULL, DRIVER_NAME) == NULL) {
		printk("devfile_rw - Could not create a device file\n");
		goto FileError;
	}

	/* Initialize a device file */
	cdev_init(&chr_device, &fops);

	/* Register a device with kernel */
	if(cdev_add(&chr_device, device_num, 1) == -1) {
		printk("devfile_rw - device registration failed with kernel\n");
		goto AddError;
	}

	return 0;

AddError:
	device_destroy(device_class, device_num);
FileError:
	class_destroy(device_class);
ClassError:
	unregister_chrdev_region(device_num,1);
	return -1;

}


/**
 * @brief This function is called, when the module is unloaded from the kernel
 */
static void __exit ModuleExit(void) {
	cdev_del(&chr_device);
	device_destroy(device_class, device_num);
	class_destroy(device_class);
	unregister_chrdev_region(device_num,1);
	printk("devfil_rw - Module is Unloading from the kernel\n");
}

module_init(ModuleInit);
module_exit(ModuleExit);
