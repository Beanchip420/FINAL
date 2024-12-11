/*
 * RNG.h
 *
 *  Created on: Dec 3, 2024
 *      Author: root
 */

#ifndef INC_RNG_H_
#define INC_RNG_H_

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_rng.h"

void RNG_Init(void);

uint32_t Gen_Number(void);

#endif /* INC_RNG_H_ */
