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

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#define MySolution	1
#define ALIAS_BASE 0x22000000U
#define BITBAND_BASE 0x20000000U

int main(void)
{

#if MySolution
	// put value 0xFF at address 0x2000_0200
	__asm volatile ("MOV R0,#0xFF");
	__asm volatile ("LDR R1,=0x20000200");
	__asm volatile ("STR R0,[R1]");

	#if 0
		// normal method
		__asm volatile ("LDR R0,=0x20000200");
		__asm volatile ("LDR R1,[R0]");
		__asm volatile ("AND R1,R1,#0x7F");
		__asm volatile ("STR R1,[R0]");

	#else
		// bit banding method
		__asm volatile ("LDR R1,=0x2200401C");
		__asm volatile ("MOV R0,#0X00");
		__asm volatile ("STR R0,[R1]");
	#endif

#else

	// normal method
	uint8_t *ptr = (uint8_t*)0x20000200;
	*ptr = 0xFF;
	*ptr &= ~(1 << 7);

	// bit band method
	*ptr = 0xFF;
	uint8_t* alias_addr = (uint8_t*)(ALIAS_BASE + 32 * (0x20000200 - BITBAND_BASE) + 7 * 4);
	*alias_addr = 0;

#endif

	for(;;);
}
