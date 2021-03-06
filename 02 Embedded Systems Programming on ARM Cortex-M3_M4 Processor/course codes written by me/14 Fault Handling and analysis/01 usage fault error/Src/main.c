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

#define SHCRS 0xE000ED24

#define UFSR 0xE000ED2A

int main(void)
{
	// 1. enable all configurable exceptions like usage fault, mem manage fault and bus fault
	uint32_t *pSHCRS = (uint32_t*) SHCRS;
	*pSHCRS |= (1 << 18); // usage fault
	*pSHCRS |= (1 << 16); // mem manage fault
	*pSHCRS |= (1 << 17); // bus fault


	// 3. lets force the processor to execute some undefined instruction

	// 3.1 executing invalid instruction
	uint32_t *pSRAM = (uint32_t*) 0x20010000;
	*pSRAM = 0xFFFFFFFF;
	void (*some_address) (void);
	//some_address = (void*)(((uint32_t)pSRAM) + 1); // to make T bit = 1
	some_address = (void*)pSRAM; // will give an error as T bit = 0
	some_address();



	// 4. analyze the fault


	for(;;);
}

// 2. implement the fault handlers
void BusFault_Handler(void)
{
	printf("Exception : BusFault\n");
	while(1);
}

void MemManage_Handler(void)
{
	printf("Exception : MemManage\n");
	while(1);
}

__attribute__((naked)) void UsageFault_Handler(void)
{
	// here we extracted the value of MSP which happens to be the base address of
	// the stack frame which got saved during the exception entry from thread mode to handler mode
	__asm ("MRS r0,MSP"); // according to ARM architecture , r0 will be used to be passed as the 1st param to the calee function
	__asm ("B UsageFault_Handler_c");
}

void UsageFault_Handler_c(uint32_t* pBaseStackFrame)
{
	// analyze contents of stack frame
	printf("MSP = %p\n",pBaseStackFrame);

	// print status register of error
	uint32_t *pUFSR = (uint32_t*) UFSR;
	printf("Exception : UsageFault\n");
	printf("UFSR = %lx\n",(*pUFSR) & 0xFFFF);

	// print the values of stack frame
	printf("Value of R0 	= %lx\n",pBaseStackFrame[0]);
	printf("Value of R1 	= %lx\n",pBaseStackFrame[1]);
	printf("Value of R2 	= %lx\n",pBaseStackFrame[2]);
	printf("Value of R3 	= %lx\n",pBaseStackFrame[3]);
	printf("Value of R12	= %lx\n",pBaseStackFrame[4]);
	printf("Value of LR 	= %lx\n",pBaseStackFrame[5]);
	printf("Value of PC 	= %lx\n",pBaseStackFrame[6]);
	printf("Value of XPSR 	= %lx\n",pBaseStackFrame[7]);
	while(1);
}

void HardFault_Handler(void)
{
	printf("Exception : HardFault\n");
	while(1);
}
