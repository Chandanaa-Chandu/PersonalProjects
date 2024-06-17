/*
 * exti.c
 *
 *  Created on: 11-Jun-2024
 *      Author: chandanar
 */
#include "exti.h"
#include "main.h"
#include "stm32f4xx.h"
#include "my_tasks.h"

/**
 * @brief This function will initiate a External Interrupt for PA0
 */
void EXTI0Init(void) {
	/* Disable global interrupts (optional) */
	__disable_irq();

	/* Enable clock access to SYSCFG */
	RCC_APB2ENR |= SYSCFGEN;

	/* Select PORT A for EXTI0 */
	SYSCFG_EXTICR1 &= ~(1U<<0);
	SYSCFG_EXTICR1 &= ~(1U<<1);
	SYSCFG_EXTICR1 &= ~(1U<<2);
	SYSCFG_EXTICR1 &= ~(1U<<3);

	/* Unmask EXTI0 */
	EXTI_IMR |= (1U<<0);

	/* Select falling edge trigger */
	EXTI_FTSR |= (1U<<0);

	/* Set EXTI0 priority */
	NVIC_SetPriority(EXTI0_IRQn, 15); // Lowest priority

	/* Enable EXTI0 line in NVIC */
	NVIC_EnableIRQ(EXTI0_IRQn);

	/* Enable global interrupts */
	__enable_irq();
}

