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

#define SRAM_START 0x20000000U
#define SRAM_SIZE (128*1024)
#define SRAM_END ((SRAM_START) + (SRAM_SIZE))
#define STACK_START SRAM_END

// not used
#define STACK_MSP_START STACK_START
#define STACK_MSP_END (STACK_MSP_START + 512)
#define STACK_PSP_START STACK_MSP_END

int fun_add(int a, int b, int c, int d)
{
	return a+b+c+d;
}

// this is how to make inline assembly function
__attribute__((naked)) void change_sp_to_psp(void)
{
	__asm volatile(".equ SRAM_END,(0x20000000 + (128 * 1024))");
	__asm volatile(".equ PSP_START,(SRAM_END - 512)");
	__asm volatile("LDR R0,=PSP_START");
	__asm volatile("MSR PSP,R0");
	__asm volatile("MOV R0,#0x02");
	__asm volatile("MSR CONTROL,R0");
	// this is like the return instruction but in assembly function
	__asm volatile("BX LR");
}

// this code generates exception and service number of excpetion is 2
void generate_exception(void)
{
	__asm volatile("SVC #0x2");
}

int main(void)
{
	change_sp_to_psp();

	int ret;
	ret = fun_add(1, 2, 3, 4);
	printf("result = %d\n",ret);

	generate_exception();

	for(;;);
}

// name of function is got from the vector table written in startup code
void SVC_Handler(void)
{
	printf(" in SVC_Handler\n");
}
