#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/cdev.h>
#include <linux/gpio.h>

/* Meta Information */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Chandana R");
MODULE_DESCRIPTION("Register the Device number dynamically and read the status of push button");

/* Variables for Device and Device Class */
static dev_t device_num;
static struct class *device_class;
static struct cdev chrdev_gpio_rd;

#define DRIVER_CLASS	"ModuleClass"
#define DRIVER_NAME 	"gpio_rd_driver"

/* Variables for GPIO */
#define GPIO_PIN	2
#define PUSH_BUTTON	GPIO_PIN

/**
 * @brief This function is called, when the user wants to read the buffer
 */
static ssize_t driver_read(struct file *file, char *user_buffer, size_t length, loff_t *offset) {
	int to_copy, not_copied, delta;
	char tmp[3] = " \n";

	/* Calculate the amount of data to be write into User */
	to_copy = min(length, sizeof(tmp));

	/* Read the status of the push button */
	printk("005_GPIO_Read - The Status of button: %d\n", gpio_get_value(PUSH_BUTTON));
	tmp[0] = gpio_get_value(PUSH_BUTTON) + '0';

	/* Copy the date into User */
	not_copied = copy_to_user(user_buffer,&tmp,to_copy);

	/* Calculate the delta */
	delta = to_copy - not_copied;

	return delta;
}

/**
 * @brief This function is called, when the device file is opened
 */
static int driver_open(struct inode *device_file, struct file *instance) {
	printk("005_GPIO_Read - Device file is Opened\n");
	return 0;
}

/**
 * @brief This function is called, when the device file is closed
 */
static int driver_close(struct inode *device_file, struct file *instance) {
	printk("005_GPIO_Read - Device file is Closed\n");
	return 0;
}

/* Specify the file operations */
static struct file_operations fops = {
	.owner = THIS_MODULE,
	.open = driver_open,
	.release = driver_close,
	.read = driver_read
};

/**
 * @brief This function is called, when the Module is Loaded into Kernel
 */
static int __init ModuleInit(void) {
	printk("005_GPIO_Read - Module is Entering into Kernel\n");

	/* Allocate the device number */
	if((alloc_chrdev_region(&device_num, 0, 1, DRIVER_NAME)) < 0) {
		printk("005_GPIO_Read - Unable to register device number\n");
		return -1;
	}

	printk("005_GPIO_Read - Registered device numbers Major: %d and Minor: %d\n", device_num >> 20, device_num & 0xfffff);

	/* Create a Device Class */
	if((device_class = class_create(THIS_MODULE, DRIVER_CLASS)) == NULL) {
		printk("005_GPIO_Read - Unable to create a device class\n");
		goto ClassError;
	}

	/* Create a Device File */
	if(device_create(device_class, NULL, device_num, NULL, DRIVER_NAME) == NULL) {
		printk("005_GPIO_Read - Unable to create a device file\n");
		goto FileError;
	}

	/* Initialize the character device */
	cdev_init(&chrdev_gpio_rd, &fops);
	
	/* Register a device with kernel */
	if(cdev_add(&chrdev_gpio_rd, device_num, 1) == -1) {
		printk("005_GPIO_Read - Unable to register a device with kernel\n");
		goto AddError;
	}

	/* Initiate a GPIO Pin */
	if(gpio_request(GPIO_PIN, "rpi-gpio-2")) {
		printk("005_GPIO_Read - Unable to allocate the GPIO Pin\n");
	}

	/* Set the direction of the GPIO Pin */
	if(gpio_direction_input(GPIO_PIN)) {
		printk("005_GPIO_PIN - Unable to set the direction of the GPIO Pin\n");
		goto GPIO2Error;
	}

	return 0;
	
GPIO2Error:
	gpio_free(GPIO_PIN);

AddError:
	device_destroy(device_class, device_num);

FileError:
	class_destroy(device_class);

ClassError:
	unregister_chrdev_region(device_num, 1);
	return -1;
}

/**
 * @brief This function is called, when the module is Unloading from the kernel
 */
static void __exit ModuleExit(void) {
	gpio_free(GPIO_PIN);
	cdev_del(&chrdev_gpio_rd);
	device_destroy(device_class, device_num);
	class_destroy(device_class);
	unregister_chrdev_region(device_num, 1);
	printk("005_GPIO_Read - Module is Unloading from the Kernel");
}

module_init(ModuleInit);
module_exit(ModuleExit);


