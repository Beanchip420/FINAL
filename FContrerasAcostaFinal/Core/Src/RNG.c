/*
 * RNG.c
 *
 *  Created on: Dec 3, 2024
 *      Author: root
 */


#include "RNG.h"

static uint8_t rngHALStatus;
static RNG_HandleTypeDef hrng;

// HAL_StatusTypeDef HAL_RNG_Init(RNG_HandleTypeDef *hrng);

void RNG_Init(void)
{
	__HAL_RCC_RNG_CLK_ENABLE();

	 hrng.Instance = RNG;
	 rngHALStatus = HAL_RNG_Init(&hrng);
		if(rngHALStatus != HAL_OK)
			{
				for(;;);
			}

}

uint32_t Gen_Number(void)
{
	uint32_t randomNumber;

	 rngHALStatus = HAL_RNG_GenerateRandomNumber(&hrng, &randomNumber);
		if(rngHALStatus != HAL_OK)
			{
				for(;;);
			}
	return randomNumber;

}
