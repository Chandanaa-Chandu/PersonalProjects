/*
 * my_tasks.c
 *
 *  Created on: May 8, 2024
 *      Author: chandanar
 */

/* Include necessary header files */
#include "my_tasks.h"
#include "main.h"
#include "queue.h"
#include "stdio.h"

/* Declaration of a required task handles */
TaskHandle_t xsenderTaskHandle = NULL;
TaskHandle_t xreceiverTaskHandle = NULL;

/* Declare Queue Handles */
QueueHandle_t xQueueTaskHandle;
int sendValue = 0;
int receivedValue;
/**
 * @brief This function is called, to setup/create required tasks
 */
void taskSetup(void) {
	senderTaskCreate();
	receiverTaskCreate();
}

/**
 * @brief This function will create a sender queue task
 */
void senderTaskCreate(void) {
	xTaskCreate(
			senderTask,					// Function of a task
			"Sender Queue Task",		// Name for a task
			configMINIMAL_STACK_SIZE,	// Stack size for a task
			NULL,						// Parameter of a task
			tskIDLE_PRIORITY + 1,		// Priority of a task
			&xsenderTaskHandle);		// Task handle
}

/**
 * @brief This is a function of senderTask
 */
void senderTask(void *pvParameter) {

	BaseType_t xStatus;

	while (1) {
		/* Send data to a Queue */
		xStatus = xQueueSend(xQueueTaskHandle, &sendValue, 0);

		/* Check whether the data sent successfully or not to Queue */
		if(xStatus == pdPASS) {
			printf("Data sent: %d\n", sendValue);
			sendValue++;
		} else {
			printf("Failed to send\n");
		}

		/* Delay for 1Second */
		vTaskDelay(pdMS_TO_TICKS(1000));
	}
}

/**
 * @brief This function will create a Queue Reciever Task
 */
void receiverTaskCreate(void) {
	xTaskCreate(
			receiverTask,				// Function of a task
			"Receiver Queue Task",		// Name of a task
			configMINIMAL_STACK_SIZE,	// Stack size for a task
			NULL,						// Task parameters
			tskIDLE_PRIORITY + 1,		// Priority of a task
			&xreceiverTaskHandle);		// Task handle
}

/**
 * @brief This is a function of receiverTask
 */
void receiverTask(void *pvParameter) {


	while (1) {
		// Receive a value from the Queue
		if(xQueueReceive(xQueueTaskHandle, &receivedValue, portMAX_DELAY)) {
			printf("Received Value: %d\n", receivedValue);
		} else {
			printf("Failed to Received\n");
		}
	}
}

/**
 * @brief This function is called, to start the task scheduler
 */
void initTasks(void) {
	vTaskStartScheduler();
}

