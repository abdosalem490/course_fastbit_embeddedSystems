/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

#include <stdint.h>
#include <stdio.h>

#define TIM2_IRQNO	28
#define I2C1_EV_IRQNO	31

#define NVIC_ISER0	0xE000E100
#define NVIC_ISPR0	0XE000E200
#define NVIC_IPR0	0xE000E400;

void configure_priority_for_irqs(uint8_t irq_no, uint8_t priority_value);

uint32_t *pNVIC_IPRBase = (uint32_t*)NVIC_IPR0 ;
uint32_t *pNVIC_ISERBase = (uint32_t*)NVIC_ISER0 ;
uint32_t *pNVIC_ISPRBase = (uint32_t*)NVIC_ISPR0 ;


int main(void)
{
	// 1. lets configure the priority for the peripherals
	configure_priority_for_irqs(TIM2_IRQNO, 0x80);
	//configure_priority_for_irqs(I2C1_EV_IRQNO, 0x80);
	configure_priority_for_irqs(I2C1_EV_IRQNO, 0x70);

	// 2. Manually pend the pending bit for the TIM2,I2C1_EV IRQ number in NVIC
	*pNVIC_ISPRBase |= (1 << (TIM2_IRQNO % 32));
	//*pNVIC_ISPRBase |= (1 << (I2C1_EV_IRQNO % 32));

	// 3. Enable the USART3 IRQ number in NVIC
	*pNVIC_ISERBase |= (1 << (I2C1_EV_IRQNO % 32));
	*pNVIC_ISERBase |= (1 << (TIM2_IRQNO % 32));


	for(;;);
}
void configure_priority_for_irqs(uint8_t irq_no, uint8_t priority_value)
{
	// 1. find out iprx
	uint8_t iprx = irq_no / 4;
	uint32_t *ipr = pNVIC_IPRBase + iprx;

	// 2. position in iprx
	uint8_t pos = (irq_no % 4) * 8;

	// 3.configure the priority
	*ipr &= ~(0xFF << pos);
	*ipr |= (priority_value << pos);
}

// TIM2 ISR
void TIM2_IRQHandler(void)
{
	printf("[TIM2_IRQHandler]\n");
	*pNVIC_ISPRBase |= (1 << (I2C1_EV_IRQNO % 32));
	while(1);
}

// I2C1_EV ISR
void I2C1_EV_IRQHandler(void)
{
	printf("[I2C1_EV_IRQHandler]\n");
}
