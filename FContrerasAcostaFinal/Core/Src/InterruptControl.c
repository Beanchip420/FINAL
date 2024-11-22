/*
 * InterruptControl.c
 *
 *  Created on: Sep 30, 2024
 *      Author: beanchip42
 */



#include "InterruptControl.h"

#define check 32
static uint8_t reg_select;
static uint32_t bit_select;

void IRQ_ENABLE(uint8_t number)
{
	reg_select = number / check;
	bit_select = number % check;
	*(NVIC_ISER0+reg_select) |= (0x1 << bit_select);

}

void IRQ_DISABLE(uint8_t number)
{
	reg_select = number / check;
	bit_select = number % check;
	*(NVIC_ICER0+reg_select) |= (0x1 << bit_select);
}

void IRQ_CLEAR(uint8_t number) // N ee
{
	reg_select = number / check;
	bit_select = number % check;
	*(NVIC_ICPR0+reg_select) |= (0x1 << bit_select);
}

void IRQ_SET(uint8_t number){
	reg_select = number / check;
	bit_select = number % check;
	*(NVIC_ISPR0+reg_select) |= (0x1 << bit_select);
}

void CLEAR_EXTI(uint8_t number) // EXTI is for external hardware don't apply to clocks since internal hardware
{
	EXTI->PR |= (0x1 << number);
}


