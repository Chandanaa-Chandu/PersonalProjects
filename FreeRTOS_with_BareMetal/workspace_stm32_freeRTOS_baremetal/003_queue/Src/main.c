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

int main()
{
	taskSetup();
	initTasks();
}
