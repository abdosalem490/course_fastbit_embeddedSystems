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

void SVC_Handler_c(uint32_t *pBaseOfStackFrame);

int main(void)
{
	__asm volatile("SVC #8");

	// 5. get the value of SVC number after modifying
	//register uint32_t data __asm("r0");
	uint32_t data;
	__asm("MOV %0,R0": "=r"(data) );
	printf("data = %d\n",data);

	for(;;);
}

__attribute__((naked)) void SVC_Handler(void)
{
	// 1. get the value of the MSB
	__asm ("MRS R0,MSP");
	__asm ("B SVC_Handler_c");	// according to ARM architecture , R) will be the first attribute of the function
}

void SVC_Handler_c(uint32_t *pBaseOfStackFrame)
{
	printf("in SVC handler\n");


	uint8_t *pReturn_addr = (uint8_t*)pBaseOfStackFrame[6];

	// 2.decrement the return address by 2 to point to opcode of the SVC instruction in the program memory
	pReturn_addr -= 2;

	// 3. extract the SVC number (LSByte of the opcode)
	uint8_t svc_number = *pReturn_addr;
	printf("SVC number is : %d\n",svc_number);

	// 4. increment the SVC number by 4 to pass it back to thread mode using Register R0
	svc_number += 4;
	pBaseOfStackFrame[0] = svc_number;

}
