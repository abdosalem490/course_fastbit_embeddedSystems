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
#include "main.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

void softwareDelay(uint32_t timeInMillis);

/**** Address of the Clock control register (AHB1ENR) ****/
#define	AHB1ENR 0x40023830 // base address of RCC (register control clock) register (0x40023800) + offset of AHB1ENR reg (0x30) Address of the clock control register in which GIOD D enable bit is in it

/**** Address of the GPID mode register (used to control mode) ****/
#define GPIOD_MODE 0x40020C00 // base address of GPIO D registers (0x40020C00) + offset of mode register (0x00) -> make the mode of pin 12 (bit 24 to 1 & 25 to 0) so that we can use them as general purpose output

/**** Address of the GPIOD output data register (used to write) ****/
#define GPIOD_OUTPUT 0x40020C14 // base address of GPIO D registers (0x40020C00) + offset of output register (0x14) -> make the mode of pin 12 (bit 24 to 1 & 25 to 0) so that we can use them as general purpose output

int main(void)
{

	RCC_AHB1ENR_t volatile *const pClkCtrlReg = (RCC_AHB1ENR_t*)AHB1ENR;
	GPIOx_MODE_t volatile *const pPortDModeReg = (GPIOx_MODE_t*)GPIOD_MODE;
	GPIOx_ODR_t volatile *const pPortDOutputReg = (GPIOx_ODR_t*)GPIOD_OUTPUT;

	// 1.enable the clock for GPIOD peripheral in the AHB1ENR (Set the 3rd bit position)
	pClkCtrlReg->gpiod_en = 1;

	// 	a.clear the 24th and 25th bit positions (CLEAR)
	pPortDModeReg->pin_12 = 1;
	pPortDModeReg->pin_13 = 1;
	pPortDModeReg->pin_14 = 1;
	pPortDModeReg->pin_15 = 1;

	// 3.for loop which toggles the led and then wait
	while(1){
		pPortDOutputReg->pin_12 ^= 1;
		pPortDOutputReg->pin_13 ^= 1;
		pPortDOutputReg->pin_14 ^= 1;
		pPortDOutputReg->pin_15 ^= 1;
		softwareDelay(1000);
	}

	/* Loop forever */
	for(;;);
}

void softwareDelay(uint32_t timeInMillis)
{
	for(uint32_t i = 0;  i < timeInMillis * 1600 ; i++);
}