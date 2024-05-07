#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/cdev.h>
#include <linux/gpio.h>

/* Meta Information */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Chandana R");
MODULE_DESCRIPTION("Register device number dynamically and read a push button state and write the LED");

/* Variables for device and device class */
static dev_t device_num;
static struct class *device_class;
static struct cdev chrdev_gpio_rw;

#define DRIVER_CLASS	"ModuleClass"
#define DRIVER_NAME	"gpio_rw_driver"

/* Variables for GPIOs */
#define PUSH_BUTTON	3
#define LED		2

/**
 * @brief This function is called, when the user read the buffer
 */
static ssize_t driver_read(struct file *file, char *user_buffer, size_t length, loff_t *offset) {
	int to_copy, not_copied, delta;
	char tmp[3] = " \n";

	/* Calculate the amount of data to copy */
	to_copy = min(length, sizeof(tmp));

	/* Get the push button status */
	printk("gpio_rw - status of the push button is: %d\n", gpio_get_value(PUSH_BUTTON));
	tmp[0] = gpio_get_value(PUSH_BUTTON) + '0';

	/* Copy the data into user */
	not_copied = copy_to_user(user_buffer, &tmp, to_copy);

	delta = to_copy - not_copied;

	return delta;
}

/**
 * @brief This function is called, when the user write into buffer
 */
static ssize_t driver_write(struct file *file, const char *user_buffer, size_t length, loff_t *offset) {
	int to_copy, not_copied, delta;
	char command;

	/* Calculate the amount of data to copy */
	to_copy = min(length, sizeof(command));

	/* Copy the data from user */
	not_copied = copy_from_user(&command, user_buffer, to_copy);

	/* Write the LED based on the command */
	switch(command) {
		case '0':
			gpio_set_value(LED, 0);	// Turning OFF LED
			break;
		case '1':
			gpio_set_value(LED, 1);	// Turning ON LED
			break;
		default:
			printk("gpio_rw - Invalid command from user\n");
			break;
	}

	/* calculate delta */
	delta = to_copy - not_copied;

	return delta;
}

/**
 * @brief This function is called, when the device file is opened
 */
static int driver_open(struct inode *device_file, struct file *instance) {
	printk("gpio_rw - Device file is Opened\n");
	return 0;
}

/**
 * @brief This function is called, when the device file is closed 
 */
static int driver_close(struct inode *device_file, struct file *instance) {
	printk("gpio_rw - Device file is Closed\n");
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

/**
 * @brief This function is called, when the module is loading into kernel
 */
static int __init ModuleInit(void) {
	printk("gpio_rw - Module is Entering into Kernel\n");

	/* Allocate a device number */
	if((alloc_chrdev_region(&device_num, 0, 1, DRIVER_NAME)) < 0) {
		printk("gpio_rw - Unable to allocate a device number\n");
		return -1;
	}

	printk("gpio_rw - Device registered with Major: %d and Minor: %d\n", device_num>>20, device_num& 0xfffff);

	/* Create a device class */
	if((device_class = class_create(THIS_MODULE, DRIVER_CLASS)) == NULL) {
		printk("gpio_rw - Unable to create a device class\n");
		goto ClassError;
	}

	/* Create a device file */
	if(device_create(device_class, NULL, device_num, NULL, DRIVER_NAME) == NULL) {
		printk("gpio_rw - Unable to create a device file\n");
		goto FileError;
	}

	/* Initiate a character device */
	cdev_init(&chrdev_gpio_rw, &fops);

	/* Register a device with kernel */
	if((cdev_add(&chrdev_gpio_rw, device_num, 1)) < -1) {
		printk("gpio_rw - Unable to register a device with kernel\n");
		goto AddError;
	}

	/* Initiate a LED GPIO Pin*/
	if(gpio_request(LED, "rpi-gpio-2")) {
		printk("gpio_rw - Unable to allocate a LED GPIO Pin\n");
		goto AddError;
	}

	/* Set the direction of LED Pin to Output */
	if(gpio_direction_output(LED, 0)) {
		printk("gpio_rw - Unable to set the LED direction to Output\n");
		goto GPIOLedError;
	}
	
	/* Initiate a Push button GPIO Pin */
	if(gpio_request(PUSH_BUTTON, "rpi-gpio-3")) {
		printk("gpio_rw - Unable to allocate a Push Button GPIO Pin\n");
		goto GPIOLedError;
	}

	/* Set a direction of Push Button to Input */
	if(gpio_direction_input(PUSH_BUTTON)) {
		printk("gpio_rw - Unable to set the direction of Push Button Pin\n");
		goto GPIOButnError;
	}

	return 0;

GPIOButnError:
	gpio_free(PUSH_BUTTON);
	
GPIOLedError:
	gpio_free(LED);

AddError:
	device_destroy(device_class, device_num);

FileError:
	class_destroy(device_class);

ClassError:
	unregister_chrdev_region(device_num, 1);
	return -1;
}

/**
 * @brief This function is called, when the module is unloading from kernel
 */
static void __exit ModuleExit(void) {
	gpio_set_value(LED, 0);
	gpio_free(LED);
	gpio_free(PUSH_BUTTON);
	cdev_del(&chrdev_gpio_rw);
	device_destroy(device_class, device_num);
	class_destroy(device_class);
	unregister_chrdev_region(device_num, 1);
	printk("gpio_rw - Module is Exiting from the kernel\n");
}

module_init(ModuleInit);
module_exit(ModuleExit);

