/*
 * ApplicationCode.h
 *
 *  Created on: Dec 30, 2023
 *      Author: Xavion
 */

#include "InterruptControl.h"
#include "Tetris.h"

#include <stdio.h>

#ifndef INC_APPLICATIONCODE_H_
#define INC_APPLICATIONCODE_H_

void ApplicationInit(void);
//void LCD_Visual_Demo(void);

// ************** Write your functions here **************

void ApplicationGame(void);
void First_Screen();
//void Game();
void LCD_Touch_Polling(void);

void Tim_Init(void);
void BUTT_Init_IT(void);
void Random_Init(void);

void TIM2_IRQHandler (void);
void EXTI0_IRQHandler(void);



// ************** Write your functions here **************

#if (COMPILE_TOUCH_FUNCTIONS == 1) && (COMPILE_TOUCH_INTERRUPT_SUPPORT == 0)
void LCD_Touch_Polling_Demo(void);
#endif // (COMPILE_TOUCH_FUNCTIONS == 1) && (COMPILE_TOUCH_INTERRUPT_SUPPORT == 0)

#endif /* INC_APPLICATIONCODE_H_ */
