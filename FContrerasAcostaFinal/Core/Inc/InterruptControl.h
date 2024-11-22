/*
 * InterruptControl.h
 *
 *  Created on: Sep 30, 2024
 *      Author: beanchip42
 */

#ifndef INTERRUPTCONTROL_H_
#define INTERRUPTCONTROL_H_
#include "stm32f4xx_hal.h"
#include <stdbool.h>
//#include <stdint.h>


#define NVIC_ISER0 ((volatile uint32_t*) 0xE000E100) // Set-Enable
#define NVIC_ICER0 ((volatile uint32_t*) 0XE000E180) // Clear Enable
#define NVIC_ISPR0 ((volatile uint32_t*) 0XE000E200) // Set-Pending
#define NVIC_ICPR0 ((volatile uint32_t*) 0XE000E280) // Clear-Pending

#define APB2_BASE_ADDR 0x40013800 // Is this correct?
#define SYSCFG_BASE_ADDR (APB2_BASE_ADDR)
#define EXTI_BASE_ADDR (APB2_BASE_ADDR + 0x400)

typedef struct //4 Members in Structrue, Third memeber is Array [4]
{
	volatile uint32_t MEMRMP;
	volatile uint32_t PMC;
	volatile uint32_t EXTICR[4]; //0th index:EXTICR1 1st index:EXTICR2 2nd index:EXTICR3 4th index:EXTICR4
	volatile uint32_t CMPCR;

}SYSCFG_RegDef_t; // To enable external interups

typedef struct //6 Members in Structrue
{
	volatile uint32_t IMR;
	volatile uint32_t EMR;
	volatile uint32_t RTSR;
	volatile uint32_t FTSR;
	volatile uint32_t SWIER;
	volatile uint32_t PR;

}EXTI_RegDef_t; // Configure exti interups

//#define SYSCFG ((SYSCFG_RegDef_t*) SYSCFG_BASE_ADDR)
//#define EXTI ((EXTI_RegDef_t*) EXTI_BASE_ADDR)

#define SYSCFG_CLK_OFFSET 14
#define SYSCFG_CLK_ENABLE (RCC->APB2ENR |= (0x1 << SYSCFG_CLK_OFFSET))
#define SYSCFG_CLK_DISABLE (RCC->APB2ENR &= (0x1 << SYSCFG_CLK_OFFSET))

#define EXTI0_IRQ_NUMBER 6 // EXTI0 is interrupt for pin 0 but it's IRQ position/number is 6

void IRQ_ENABLE(uint8_t number);
void IRQ_DISABLE(uint8_t number);
void IRQ_CLEAR(uint8_t number);
void IRQ_SET(uint8_t number);

void CLEAR_EXTI(uint8_t number); // Difference between this and the IRQ clear?

#endif /* INTERRUPTCONTROL_H_ */
