/*
 * my_tasks.c
 *
 *  Created on: May 8, 2024
 *      Author: chandanar
 */

/* Include necessary header files */
#include "my_tasks.h"
#include "main.h"

/* Declare the task handles */
TaskHandle_t xTimerTaskHandle = NULL;

/**
 * @brief This function is called, to setup/create required tasks
 */
void taskSetup(void) {
	timerTaskStart();	// Create a task
}

/**
 * @brief This function is called, to create a timer task
 */
void timerTaskStart(void) {
	/* Create a new Timer Task */
	xTaskCreate(
			timerTask,					// Function of a task
			"Timer Task",				// Name for a task
			configMINIMAL_STACK_SIZE,	// Stack size
			NULL,						// Task parameters
			tskIDLE_PRIORITY + 1,			// Priority of task
			&xTimerTaskHandle);			// Task handle
}

/**
 * brief This will define task function
 */
void timerTask(void* pvParameters) {
	TickType_t xLastWakeTime;

	const TickType_t xTimerPeriod = pdMS_TO_TICKS(1000); // 1000ms = 1 second

	/* Initialize the last wake time */
	xLastWakeTime = xTaskGetTickCount();

	while (1)
	{
		/* Task function */
		toggleLED();

		/* Delay until the next timer period */
		vTaskDelayUntil(&xLastWakeTime, xTimerPeriod);
	}
}

/**
 * @brief This function is called, to start the task scheduler
 */
void initTasks(void) {
	vTaskStartScheduler();
}
