/*
 * Button_Driver.c
 *
 *  Created on: Sep 24, 2024
 *      Author: beanchip42
 */

#include "Button_Driver.h"

void BUTTON_Init (void)
{

	BUTTON_ClockControl();
	GPIO_InitTypeDef BUTTONPinConfig = {RESET};
	BUTTONPinConfig.Pin = GPIO_PIN_0;
	BUTTONPinConfig.Mode = GPIO_MODE_INPUT; // Configure as Input
	BUTTONPinConfig.Speed = GPIO_SPEED_FREQ_HIGH;
	BUTTONPinConfig.Pull = GPIO_NOPULL;
	//BUTTONPinConfig.Alternate = GPIO_PUPDR_NONE;

	// Static structure but by using "&" I pass the address to Hal_gpio_init
	// Which requires a pointer to GPIO_INITTYPEDEF structure.
	HAL_GPIO_Init(GPIOA, &BUTTONPinConfig);

}

void BUTTON_ClockControl(void)
{

	__HAL_RCC_GPIOA_CLK_ENABLE();

}

bool BUTTON_CHECK(void)
{

	uint8_t state = HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0);
	if (state == PRESSED)
	{
		return true;
	}

	else
	{
		return false;
	}
}

void BUTTON_Init_Interupt(void)
{

	BUTTON_ClockControl();
	GPIO_InitTypeDef BUTTONPinConfig= {RESET};
	BUTTONPinConfig.Pin = GPIO_PIN_0;
	BUTTONPinConfig.Mode = GPIO_MODE_IT_RISING; // Configure as Rising Edge Int
	BUTTONPinConfig.Speed = GPIO_SPEED_FREQ_HIGH;
	BUTTONPinConfig.Pull = GPIO_NOPULL;
	//BUTTONPinConfig.Alternate = GPIO_PUPDR_NONE;

	HAL_GPIO_Init(GPIOA, &BUTTONPinConfig);
	//HAL_NVIC_EnableIRQ(EXTI0_IRQ_NUMBER);

	IRQ_ENABLE(EXTI0_IRQ_NUMBER);

}
