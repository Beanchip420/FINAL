/*
 * Tetris.h
 *
 *  Created on: Dec 3, 2024
 *      Author: root
 */

#ifndef INC_TETRIS_H_
#define INC_TETRIS_H_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include <string.h>

#include "Scheduler.h"
#include "LCD_Driver.h"
#include "Timer.h"
#include "Button_Driver.h"
#include "RNG.h"

#include "stm32f4xx_hal.h"

#define DROP	3
#define ONE 	1
#define HALF_BOARD	120
#define SEVEN	7

typedef struct block_t
{
	uint8_t Current_Shape[4][4];
	uint16_t x_pos;
	uint16_t y_pos;
	uint16_t Current_Color;
}block_t;

//void Game_Screen(void);
void Start_Tetris(void);

void Draw_Shape(block_t* block);

void Update_Board(void);

void Rotate_CC(void);

bool Check_Down(void);

bool Check_Right(void);

bool Check_Left(void);

void Move_Down(void);

void Move_Right(void);

void Move_Left(void);

uint8_t Random_Shape(void);

void Check_Endgame(void);

void EndGame(void);




#endif /* INC_TETRIS_H_ */
