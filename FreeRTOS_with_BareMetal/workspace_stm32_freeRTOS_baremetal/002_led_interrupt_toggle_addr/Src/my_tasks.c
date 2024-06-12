/*
 * my_tasks.c
 *
 *  Created on: May 8, 2024
 *      Author: chandanar
 */

/* Include necessary header files */
#include "my_tasks.h"
#include "main.h"

/**
 * @brief This function is called, to setup/create required tasks
 */
void taskSetup(void) {
	isrHandleTaskCreate();
}





/**
 * @brief This function is called, to start the task scheduler
 */
void initTasks(void) {
	vTaskStartScheduler();
}


