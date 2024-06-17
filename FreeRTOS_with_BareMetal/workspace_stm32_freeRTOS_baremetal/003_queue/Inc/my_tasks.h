/*
 * my_tasks.h
 *
 *  Created on: May 8, 2024
 *      Author: chandanar
 */

#ifndef MY_TASKS_H_
#define MY_TASKS_H_

/* Includes necessary freeRTOS header files */
#include "freeRTOS.h"
#include "task.h"

/* Declaration of Queue related variables */
#define QUEUE_LENGTH		5
#define QUEUE_ITEM_SIZE     sizeof(int)

/* Function prototypes */
void initTasks(void);

void taskSetup(void);

void senderTaskCreate(void);
void senderTask(void *pvParameter);
void receiverTaskCreate(void);
void receiverTask(void *pvParameter);

#endif /* MY_TASKS_H_ */
