#include <linux/module.h>
#include <linux/init.h>

/* Meta Information */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Chandana R");
MODULE_DESCRIPTION("Simple Linux Kernel Module to load and unload");

/**
 * @brief This function is called, when the module is loaded into the kernel
 */
static int __init ModuleInit(void) {
	printk("The module is loading into the kernel\n");
	return 0;
}

/**
 * @brief This function is called, when the module is unloaded from the kernel
 */
static void __exit ModuleExit(void) {
	printk("The module is Unloading from the kernel\n");
}

module_init(ModuleInit);
module_exit(ModuleExit);
