/*
 * Timer.h
 *
 *  Created on: Dec 3, 2024
 *      Author: root
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_tim.h"
#include "stm32f4xx_hal_tim_ex.h"

#define PRESCALER	4999
#define PCLK	84000000
// To keep track of the time
#define ARR_MAX 0xFFFFFFFF
#define ARR_1	16799
#define ARR_3	50399

void TIMER_Init(void);
void TIMER5_Start(void);
void TIMER_Stop(void);
void TIMER_Reset(void);

void TIMER_Int_Start(void);

void TIMER_Int_Stop(void);

uint32_t TIMER_ReturnVal(); // Return Timer Value
void TIMER_IntEnable(void);
uint32_t Timer_ReturnAuthoRel(void);

#endif /* INC_TIMER_H_ */
