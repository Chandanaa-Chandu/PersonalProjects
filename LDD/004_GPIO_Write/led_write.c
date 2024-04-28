#include <linux/module>
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

/**
 * @brief This function is called, to write the data buffer from user
 */
 static ssize_t driver_write(struct file *file, const char *user_buffer, size_t length, loff_t *offset) {
 	int to_copy, not_copied, delta;
 	int command;
 	
 	/* Calculate the amount of data to copy from the user buffer */
 	to_copy = min(length, sizeof(command));
 	
 	/* Copy the data from user */
 	not_copied = copy_from_user(&command, user_buffer, to_copy);
 	
 	switch(command) {
 		
 	
