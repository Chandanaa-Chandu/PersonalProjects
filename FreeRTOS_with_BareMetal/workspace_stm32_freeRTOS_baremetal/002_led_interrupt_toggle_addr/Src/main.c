/**
 * @brief This is the Bare-Metal Project using FreeRTOS
 *	Using the STM32F407G-DISC1 board with STM32F407VGT6 MCU
 *	This project will toggle the User LED upon the Interrupt generated
 *	using task notification for every 1 second
 *	The interrupt will generate whenever the user push button is pressed.
 *
 *	User LD3: Orange LED is a user LED connected to the I/O PD13 of the STM32F407VGT6
 *	Pin:  13
 *	Port: D
 *
 *	B1 USER: User Push Button connected to the I/O PA0 of the STM32F407VG
 *	Pin:  0
 *	Port: A
 */

#include "my_tasks.h"
#include "main.h"
#include "exti.h"

/* Declaration of Task handles */
TaskHandle_t xISRTaskHandle = NULL;

int main()
{
	/* Enable a clock access for GPIOD */
	RCC_AHB1ENR |= GPIODEN;
	/* Enable a clock access for GPIOA */
	RCC_AHB1ENR |= GPIOAEN;

	/* Set the mode of the GPIO Pin13 of PortD to Output */
	GPIOD_MODER |= (1U<<26);
	GPIOD_MODER &= ~(1U<<27);

	/* Set the mode of GPIO Pin0 of PortA to Input */
	GPIOA_MODER &= ~(1U<<0);
	GPIOA_MODER &= ~(1U<<1);

	EXTI0Init();
	taskSetup();
	initTasks();
}

void toggleLED(void) {
	/* Toggle a LED for every 1 Second */
	GPIOD_ODR ^= LED_PIN;
}

/**
 * @brief This function will create a new task which will handle ISR
 */
void isrHandleTaskCreate(void) {
	xTaskCreate(
			isrHandleTask,				// Function of a task
			"ISR Handle Task",			// Name of a task
			configMINIMAL_STACK_SIZE,	// Stack size for a task
			NULL,						// Task parameter
			tskIDLE_PRIORITY + 1,		// Priority of a task
			&xISRTaskHandle);
}

void isrHandleTask(void *pvParameter) {
	for (;;) {
		uint32_t ulNotificationValue;

		for (;;) {
			// Wait for the notification
			ulNotificationValue = ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

			if (ulNotificationValue != 0) {
				// Notification received, handle it
				toggleLED();
			}
		}
	}
}

void EXTI0_IRQHandler(void){
	if(EXTI_PR & (1U<<0)) {
		BaseType_t xHigherPriorityTaskWoken = pdFALSE;

		/* Clear the PR Flag */
		EXTI_PR |= (1U<<0);

		// Notify the button task about button press
		vTaskNotifyGiveFromISR(xISRTaskHandle, &xHigherPriorityTaskWoken);

		// If giving the notification unblocks a higher priority task, request a context switch
		portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
	}
}
