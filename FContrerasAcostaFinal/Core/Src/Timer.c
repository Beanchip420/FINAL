/*
 * Timer.c
 *
 *  Created on: Dec 3, 2024
 *      Author: root
 */

#include "Timer.h"

static uint8_t timHALStatus;
static TIM_HandleTypeDef htim2;
static TIM_HandleTypeDef htim5;


void TIMER_Init(void)
{
	__HAL_RCC_TIM5_CLK_ENABLE();
	htim5.Instance = TIM5;
	htim5.Init.Prescaler = PRESCALER;
	htim5.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim5.Init.Period = ARR_MAX;
	htim5.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim5.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	timHALStatus = HAL_TIM_Base_Init(&htim5);


	__HAL_RCC_TIM2_CLK_ENABLE();

	// TIM 2 Config

	htim2.Instance = TIM2;
	htim2.Init.Prescaler = PRESCALER;
	htim2.Init.CounterMode = TIM_COUNTERMODE_UP;

	// TODO: CHANGE ME TO ARR_3 for the blocks to fall every 3 Seconds

	htim2.Init.Period = ARR_1;
	htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	timHALStatus = HAL_TIM_Base_Init(&htim2);
	if(timHALStatus != HAL_OK)
		{
			for(;;);
		}



}

//void TIMER_Start(void);
//
//void TIMER_Stop(void);
//
void TIMER_Reset()
{
	TIM2->CNT = RESET;
}

//void TIMER_Reset(GPTIMR_RegDef_t *specific_clock)
//{
//	specific_clock->CNT = RESET;
//}


uint32_t TIMER_ReturnVal() // Return Timer Value
{
	return __HAL_TIM_GET_COUNTER(&htim5);
}

void TIMER_Int_Start(void)
{

	timHALStatus = HAL_TIM_Base_Start_IT(&htim2);
	if(timHALStatus != HAL_OK)
		{
			for(;;);
		}
}

void TIMER_Int_Stop(void)
{
	timHALStatus = HAL_TIM_Base_Stop_IT(&htim2);
	if(timHALStatus != HAL_OK)
		{
			for(;;);
		}
}

uint32_t Timer_ReturnAuthoRel(void)
{
	return __HAL_TIM_GET_AUTORELOAD(&htim2);
}

void TIMER5_Start(void)
{
	HAL_TIM_Base_Start(&htim5);
}

void TIMER_Stop(void)
{
	HAL_TIM_Base_Stop(&htim5);
}





