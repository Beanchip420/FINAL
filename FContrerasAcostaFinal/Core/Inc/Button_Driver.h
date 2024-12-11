/*
 * Button_Driver.h
 *
 *  Created on: Sep 24, 2024
 *      Author: beanchip42
 */

#ifndef BUTTON_DRIVER_H_
#define BUTTON_DRIVER_H_
#include "InterruptControl.h"


//USER & WAKE-UP Button PA0

#define B_port GPIOA // DO I NEED TO DO THIS?
//#define B_PIN 0
#define PRESSED 1 // PRESSED IS 1
#define UNPRESSED 0 // NOT PRESSED IS 0



void BUTTON_Init (void);
void BUTTON_ClockControl(void);
bool BUTTON_CHECK(void);

void BUTTON_Init_Interupt(void);

#endif /* BUTTON_DRIVER_H_ */
