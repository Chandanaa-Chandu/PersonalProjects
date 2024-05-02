#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/cdev.h>
#include <linux/gpio.h>

/* Meta Information */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Chandana R");
MODULE_DESCRIPTION("Writing into GPIO Pin - turning ON/OFF the LED");

/* Variables for device and device class */
static dev_t device_num;
static struct class *device_class;
static struct cdev gpio_w_chrdev;

#define DRIVER_NAME	"gpio_w_driver"
#define DRIVER_CLASS	"ModuleClass"

/* Variables for LED */
#define GPIO_PIN	2
#define LED_PIN		GPIO_PIN

/**
 * @brief This function is called, to write the data buffer from user
 */
 static ssize_t driver_write(struct file *file, const char *user_buffer, size_t length, loff_t *offset) {
 	int to_copy, not_copied, delta;
 	char command;
 	
 	/* Calculate the amount of data to copy from the user buffer */
 	to_copy = min(length, sizeof(command));
 	
 	/* Copy the data from user */
 	not_copied = copy_from_user(&command, user_buffer, to_copy);
 	
 	switch(command) {
		case '0':
			gpio_set_value(LED_PIN, 0);	// Setting GPIO PIN to Low, turning LED OFF
			break;
		case '1':
			gpio_set_value(LED_PIN, 1);	// Setting GPIO PIN to High, turning LED ON
			break;
		default:
			printk("Invalind GPIO command from user\n");
			break;
	}
	
	/* Calculate delta */	
	delta = to_copy - not_copied;
	
	return delta;
 }

/**
 * @brief This function is called, when the device file is opened
 */
static int driver_open(struct inode *device_file, struct file *instance) {
	printk("004_GPIO_Write - Device file opened\n");
	return 0;
}

/**
 * @brief This function is called, when the device file is closed
 */
static int driver_close(struct inode *device_file, struct file *instance) {
	printk("004_GPIO_Write - Device file is closed\n");
	return 0;
}

/* Specify the required file operations */
static struct file_operations fops = {
	.owner = THIS_MODULE,
	.open = driver_open,
	.release = driver_close,
	.write = driver_write
};

/**
 * @brief This function is called, when the module is loaded into kernel
 */
static int __init ModuleInit(void) {
	printk("004_GPIO_Write - Module is loading into kernel\n");

	/* Allocate a device number */
	if((alloc_chrdev_region(&device_num, 0, 1, DRIVER_NAME)) < 0) {
		printk("004_GPIO_Write - Unable to allocate the device number\n");
	return -1;
	}
	
	printk("004_GPIO_Write - Device allocated with device Major: %d and Minor: %d numbers\n", device_num >> 20, device_num & 0xfffff);
	
	/* Create a device class */
	if((device_class = class_create(THIS_MODULE, DRIVER_CLASS)) == NULL) {
		printk("004_GPIO_Write - Could not create a class\n");
		goto ClassError;
	}

	/* Create a device file */
	if(device_create(device_class, NULL, device_num, NULL, DRIVER_NAME) == NULL) {
		printk("004_GPIO_Write - Unable to create a device file\n");
		goto FileError;
	}

	/* Initiate the character device */
	cdev_init(&gpio_w_chrdev, &fops);

	/* Register a device with kernel */
	if((cdev_add(&gpio_w_chrdev, device_num, 1)) == -1) {
		printk("004_GPIO_Write - Unable to register a device with kernel\n");
		goto AddError;
	}

	/* Initiate a GPIO PIN */
	if(gpio_request(GPIO_PIN, "rpi-gpio-2")) {
		printk("004_GPIO_Write - Could not initiate a GPIO Pin\n");
		goto AddError;
	}

	/* Set a GPIO pin as OUTPUT mode */
	if(gpio_direction_output(GPIO_PIN, 0)) {
		printk("004_GPIO_Write - Could not set the GPIO Pin to Output mode\n");
		goto GPIO4Error;
	}

	return 0;

GPIO4Error:
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
 * @brief This function is called, when the module is unloading from the kernel
 */
static void __exit ModuleExit(void) {
	gpio_set_value(GPIO_PIN, 0);	// Setting the GPIO Pin to Low
	gpio_free(GPIO_PIN);		// Free the GPIO Pin
	cdev_del(&gpio_w_chrdev);
	device_destroy(device_class, device_num);
	class_destroy(device_class);
	unregister_chrdev_region(device_num, 1);
	printk("004_GPIO_Write - Module is Unloading from the kernel\n");
}

module_init(ModuleInit);
module_exit(ModuleExit);
