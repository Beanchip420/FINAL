/*
 * Tetris.c
 *
 *  Created on: Dec 3, 2024
 *      Author: root
 */

#include "Tetris.h"


// IF THIS LOWEST ROW FLAG is one that means that the lowest row has not been found
volatile uint8_t ENDGAME_FLAG = 0;
volatile uint8_t ELAPSE_FLAG = 0;
volatile uint64_t count_value = 0;
volatile uint64_t time_elapsed = 0;

static uint8_t LOWRFLAG = 1;
static uint8_t HIGHRFLAG = 1;

static uint8_t highest_row = 0;
static uint8_t lowest_row = 0;

static uint8_t far_overal_l_col = 0;
static uint8_t far_overal_r_col = 0;
static uint8_t Ran_Numb;


static block_t block_struct;
// Case 0:
static uint8_t O [4] [4] =
{
		{0, 1, 1, 0},

		{0, 1, 1, 0},

		{0,	0, 0, 0},

		{0,	0, 0, 0}
};


// Case 1:
static uint8_t I [4] [4] =
{
		{0,	0,	1,	0},

		{0,	0,	1,	0},

		{0,	0,	1,	0},

		{0,	0,	1,	0}
};

// Case 2:
static uint8_t S [4] [4] =
{
		{0,	0,	1,	1},

		{0,	1,	1,	0},

		{0,	0,	0,	0},

		{0,	0,	0,	0}
};

// Case 3:
static uint8_t Z [4] [4] =
{
		{0,	1,	1,	0},

		{0,	0,	1,	1},

		{0,	0,	0,	0},

		{0,	0,	0,	0}
};

// Case 4:
static uint8_t L [4] [4] =
{
		{0,	1,	0,	0},

		{0,	1,	0,	0},

		{0,	1,	1,	0},

		{0,	0,	0,	0}
};

// Case 5:
static uint8_t J [4] [4] =
{
		{0,	0,	1,	0},

		{0,	0,	1,	0},

		{0,	1,	1 ,	0},

		{0,	0,	0,	0}
};

// Case 6:

static uint8_t T [4] [4] =
{
		{0,	0,	0,	0},

		{1,	1,	1,	0},

		{0,	1,	0,	0},

		{0,	0,	0,	0}

};

static uint8_t Board [16][12] =
{
	{1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1},

	{1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1},

	{1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1},

	{1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1},

	{1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1},

	{1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1},

	{1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1},

	{1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1},

	{1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1},

	{1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1},

	{1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1},

	{1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1},

	{1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1},

	{1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1},

	{1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1},

	{1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1}

};


void Start_Tetris(void)
{

	Ran_Numb = Random_Shape();

	block_struct.x_pos = 4;
	block_struct.y_pos=0;


             	switch(Ran_Numb)
	{
	case 0:
		memcpy(block_struct.Current_Shape, O, sizeof(block_struct.Current_Shape));
		block_struct.Current_Color = LCD_COLOR_YELLOW;
		break;

	case 1:
		memcpy(block_struct.Current_Shape, I, sizeof(block_struct.Current_Shape));
		block_struct.Current_Color = LCD_COLOR_CYAN;
		break;

	case 2:
		memcpy(block_struct.Current_Shape, S, sizeof(block_struct.Current_Shape));
		block_struct.Current_Color = LCD_COLOR_RED;
		break;

	case 3:
		memcpy(block_struct.Current_Shape, Z, sizeof(block_struct.Current_Shape));
		block_struct.Current_Color = LCD_COLOR_GREEN;
		break;

	case 4:
		memcpy(block_struct.Current_Shape, L, sizeof(block_struct.Current_Shape));
		block_struct.Current_Color = LCD_COLOR_BLUE;
		break;

	case 5:
		memcpy(block_struct.Current_Shape, J, sizeof(block_struct.Current_Shape));
		block_struct.Current_Color = LCD_COLOR_MAGENTA;
		break;

	case 6:
		memcpy(block_struct.Current_Shape, T, sizeof(block_struct.Current_Shape));
		block_struct.Current_Color = LCD_COLOR_BLUE2;
		break;
	}

	Draw_Shape(&block_struct);
	TIMER_Int_Start();

}

void Draw_Shape(block_t* block)
{
	// Iterate thru the Shape array to find where the ones are
	// If element is 1 then draw block @ x_start and y_start

	// If any element in the row is 1 then draw block @ x_start+i and y_start

	// If any element in the next colm then draw block @ x_start+i and y_start+j // i may very well be 0 cause far left

	for (uint16_t j = 0; j < 4; j++)
	{
		for (uint16_t i = 0; i < 4; i++)
		{
			if((block->Current_Shape)[j][i] == 1)
			{
				Draw_Block((block->x_pos+i)*20, (block->y_pos+j)*20, block->Current_Color);

			}
		}
	}
}
// Got an Error when I did block_t* block then did switch(block->Current_Shape) so decided to do
// Void for input then did an instance!
void Update_Board(void)
{
	uint8_t i;
	uint8_t j;


	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (block_struct.Current_Shape[i][j] == 1)
			{
				Board[(block_struct.y_pos) + i-1][block_struct.x_pos + j] = 1;
			}
		}
	}
}

uint8_t Random_Shape(void)
{
	uint32_t random = Gen_Number();
	random = random % SEVEN;
	return random;
}

void Rotate_CC(void)
{
	if( Check_Down() == true )
	{
		uint16_t temp_color;
		temp_color = block_struct.Current_Color;
		block_struct.Current_Color = LCD_COLOR_BLACK;
		Draw_Shape(&block_struct);
		block_struct.Current_Color = temp_color;

		uint8_t temp[4][4] = {0};
		// Flip the matrix clockwise using nested loops
		for (uint8_t i = 0; i < 4; i++)
		{
			for (uint8_t j = 0; j < 4; j++)
			{
				temp[j][4 - i - 1] = (block_struct.Current_Shape)[i][j];
			}
		}

		// Copy result back to mat
		for (uint8_t i = 0; i < 4; i++)
		{
			for (uint8_t j = 0; j < 4; j++)
			{
				(block_struct.Current_Shape)[i][j] = temp[i][j];
			}
		}

		Draw_Shape(&block_struct);
	}
	else
	{

	}


}
bool Check_Down(void)
{
	far_overal_l_col = 0;
	far_overal_r_col = 0;

	lowest_row = 0;
	int8_t i = 0;
	int8_t j = 0;

	for ( i = 3; i > -1; i--)
		{
			for ( j = 0; j < 4; j++)
			{
				// Find the lowest row that has element equal to 1 because then when checking
				// the board I can just check Board[(block_struct.y_pos)-lowest_row]
				if( (block_struct.Current_Shape)[i][j] && LOWRFLAG == 1)
				{
					LOWRFLAG = 0;
					lowest_row = i;
					break;
				}
			}
		}

		LOWRFLAG = 1;

		for ( j=0; j<4; j++)
		{
			for ( i=0; i<=lowest_row; i++)
			{
				if ( ( block_struct.Current_Shape)[i][j] && LOWRFLAG == 1)
				{
					LOWRFLAG = 0;
					far_overal_l_col = j;
					break;
				}
			}
			if (LOWRFLAG == 0)
			{
				break;
			}
		}

		LOWRFLAG = 1;

		for ( j=3; j>-1; j--)
		{
			for ( i=0; i<=lowest_row; i++)
			{
				if ( ( block_struct.Current_Shape)[i][j] && LOWRFLAG == 1)
				{
					LOWRFLAG = 0;
					far_overal_r_col = j;
					break;
				}

			}
			if (LOWRFLAG == 0)
			{
				break;
			}
		}

//	if ( LOWRFLAG == 0)
//	{
//		for (i = lowest_row; i> -1; i--  )
//		{
//			for ( j = far_overal_l_col; j <= far_overal_r_col; j++)
//			{
//				if(Board[(block_struct.y_pos)+i][(block_struct.x_pos)+j] && block_struct.Current_Shape[i][j] == 1)
//				{
//					return false;
//				}
//			}
//		}
//	}
//		LOWRFLAG = 1;
//		return true;

	if (LOWRFLAG == 0)
	{
		for (int i = lowest_row; i > -1; i--)
		{
			for (int j = far_overal_l_col; j <= far_overal_r_col; j++)
			{
				int8_t board_x = block_struct.x_pos + j;
				int8_t board_y = block_struct.y_pos + i;

				if (board_x == 0 || board_x == 11)
				{
					continue;
				}

				if (board_x < 0 || board_x >= 12 || board_y >= 16)
				{
					continue;
				}

				if (Board[board_y][board_x] && block_struct.Current_Shape[i][j] == 1)
				{
					return false;
				}
			}
		}

		LOWRFLAG = 1;
		return true; // No collisions

	}
	return false;
}

void Move_Down(void)
{
	if( Check_Down() == true )
	{
		uint16_t temp_color;
		temp_color = block_struct.Current_Color;
		block_struct.Current_Color = LCD_COLOR_BLACK;
		Draw_Shape(&block_struct);


		block_struct.Current_Color = temp_color;
		block_struct.y_pos +=1;
		Draw_Shape(&block_struct);
	}
	else
	{
		TIMER_Int_Stop();
		TIMER_Reset();
		Update_Board();
		Check_Endgame();
		Start_Tetris();

	}
}

void Check_Endgame(void)
{

	for (uint8_t j = 2; j <= 9; j++)
	{
		if ( Board[0][j] == 1)
		{

			EndGame();
			ENDGAME_FLAG = 1;
			break;
		}
	}

}

void EndGame(void)
{
	count_value = 0;
	time_elapsed = 0;

	char Time[5] = {'P', 'P', 'P', 'P', 'P'};

	LCD_Clear(0,LCD_COLOR_BLACK);
	LCD_SetTextColor(LCD_COLOR_WHITE);
	LCD_SetFont(&Font12x12);

	LCD_DisplayChar(20, 100, 'E');
	LCD_DisplayChar(30, 100, 'L');
	LCD_DisplayChar(40, 100, 'A');
	LCD_DisplayChar(50, 100, 'P');
	LCD_DisplayChar(60, 100, 'S');
	LCD_DisplayChar(70, 100, 'E');
	LCD_DisplayChar(80, 100, 'D');

	LCD_DisplayChar(100, 100, 'T');
	LCD_DisplayChar(110, 100, 'I');
	LCD_DisplayChar(120, 100, 'M');
	LCD_DisplayChar(130, 100, 'E');

	LCD_DisplayChar(15, 250, 'R');
	LCD_DisplayChar(25, 250, 'E');
	LCD_DisplayChar(35, 250, 'S');
	LCD_DisplayChar(45, 250, 'E');
	LCD_DisplayChar(55, 250, 'T');

	LCD_DisplayChar(75, 250, 'T');
	LCD_DisplayChar(85, 250, 'O');

	LCD_DisplayChar(105, 250, 'P');
	LCD_DisplayChar(115, 250, 'L');
	LCD_DisplayChar(125, 250, 'A');
	LCD_DisplayChar(135, 250, 'Y');

	LCD_DisplayChar(155, 250, 'A');
	LCD_DisplayChar(165, 250, 'G');
	LCD_DisplayChar(175, 250, 'A');
	LCD_DisplayChar(185, 250, 'I');
	LCD_DisplayChar(195, 250, 'N');

	TIMER_Stop();
	count_value = TIMER_ReturnVal();
	// In seconds
	time_elapsed = ((count_value + 1)*(PRESCALER + 1))/PCLK;
	itoa(time_elapsed, Time, 10);
	uint8_t Temp = 0;

	for (int8_t i = 4; i>=0; i--)
	{
		if ( Time[i] != 'P' && ELAPSE_FLAG == 0)
		{
			Temp = i;
			ELAPSE_FLAG = 1;
			break;
		}
	}

	uint8_t space = 0;
	for (uint8_t i = 0; i < Temp; i++)
	{

		LCD_DisplayChar(150+space, 100 ,Time[i]);
		space += 10;
	}
	HAL_Delay(15000);
}

bool Check_Right(void)
{
	//far_overal_l_col = 0;
//	static uint8_t LOWRFLAG = 1;
//	static uint8_t RIGHTCFLAG = 1;
//	static uint8_t LEFTFLAG = 1;
//	static uint8_t highest_row = 0;
//	static uint8_t lowest_row = 0;
//
//	static uint8_t far_overal_l_col = 0;
//	static uint8_t far_overal_r_col = 0;
	far_overal_r_col = 0;
	far_overal_l_col = 0;

	highest_row = 0;
	lowest_row = 0;
	int8_t i = 0;
	int8_t j = 0;

	for ( i = 3; i > -1; i--)
		{
			for ( j = 0; j < 4; j++)
			{
				// Find the lowest row that has element equal to 1 because then when checking
				// the board I can just check Board[(block_struct.y_pos)-lowest_row]
				if( (block_struct.Current_Shape)[i][j] && LOWRFLAG == 1)
				{
					LOWRFLAG = 0;
					lowest_row = i;
					break;
				}
			}
		}

		LOWRFLAG = 1;

		for ( i = 0; i < 4 ; i++)
		{
			for ( j = 0; j < 4; j++)
			{
				// Find the highest row that has element equal to 1 because then when checking
				// the board I can just check Board[(block_struct.y_pos)-lowest_row]
				if( (block_struct.Current_Shape)[i][j] && HIGHRFLAG == 1)
				{
					HIGHRFLAG = 0;
					highest_row = i;
					break;
				}
			}
		}

		HIGHRFLAG = 1;


		for ( j=0; j<4; j++)
		{
			for ( i=0; i<=lowest_row; i++)
			{
				if ( ( block_struct.Current_Shape)[i][j] && LOWRFLAG == 1)
				{
					LOWRFLAG = 0;
					far_overal_l_col = j;
					break;
				}
			}
			if (LOWRFLAG == 0)
			{
				break;
			}
		}

		LOWRFLAG = 1;

		for ( j = 3; j > -1; j--)
		{
			for ( i = 0; i <= lowest_row; i++)
			{
				if ( ( block_struct.Current_Shape)[i][j] && LOWRFLAG == 1)
				{
					LOWRFLAG = 0;
					far_overal_r_col = j;
					break;
				}

			}
			if (LOWRFLAG == 0)
			{
				break;
			}
		}

	if ( LOWRFLAG == 0)
	{
		for (j = far_overal_r_col; j >= far_overal_l_col; j--  )
		{
			for ( i = highest_row; i <= lowest_row; i++)
			{
				if(Board[(block_struct.y_pos)+i][(block_struct.x_pos)+j] && block_struct.Current_Shape[i][j] == 1)
				{
					return false;
				}
			}
		}

		LOWRFLAG = 1;
		return true;

	}
	return false;
}

bool Check_Left(void)
{
	//far_overal_l_col = 0;
	//	static uint8_t LOWRFLAG = 1;
	//	static uint8_t RIGHTCFLAG = 1;
	//	static uint8_t LEFTFLAG = 1;
	//	static uint8_t highest_row = 0;
	//	static uint8_t lowest_row = 0;
	//
	//	static uint8_t far_overal_l_col = 0;
	//	static uint8_t far_overal_r_col = 0;
	far_overal_r_col = 0;
	far_overal_l_col = 0;

	highest_row = 0;
	lowest_row = 0;
	int8_t i = 0;
	int8_t j = 0;

	for ( i = 3; i > -1; i--)
		{
			for ( j = 0; j < 4; j++)
			{
				// Find the lowest row that has element equal to 1 because then when checking
				// the board I can just check Board[(block_struct.y_pos)-lowest_row]
				if( (block_struct.Current_Shape)[i][j] && LOWRFLAG == 1)
				{
					LOWRFLAG = 0;
					lowest_row = i;
					break;
				}
			}
		}

		LOWRFLAG = 1;

		for ( i = 0; i < 4 ; i++)
		{
			for ( j = 0; j < 4; j++)
			{
				// Find the highest row that has element equal to 1 because then when checking
				// the board I can just check Board[(block_struct.y_pos)-lowest_row]
				if( (block_struct.Current_Shape)[i][j] && HIGHRFLAG == 1)
				{
					HIGHRFLAG = 0;
					highest_row = i;
					break;
				}
			}
		}

		HIGHRFLAG = 1;


		for ( j = 0; j < 4; j++)
		{
			for ( i = 0; i<= lowest_row; i++)
			{
				if ( ( block_struct.Current_Shape)[i][j] && LOWRFLAG == 1)
				{
					LOWRFLAG = 0;
					far_overal_l_col = j;
					break;
				}
			}
			if (LOWRFLAG == 0)
			{
				break;
			}
		}

		LOWRFLAG = 1;

		for ( j = 3; j > -1; j--)
		{
			for ( i = 0; i <= lowest_row; i++)
			{
				if ( ( block_struct.Current_Shape)[i][j] && LOWRFLAG == 1)
				{
					LOWRFLAG = 0;
					far_overal_r_col = j;
					break;
				}

			}
			if (LOWRFLAG == 0)
			{
				break;
			}
		}

	if ( LOWRFLAG == 0)
	{
		for (j = far_overal_l_col; j <= far_overal_r_col; j++  )
		{
			for ( i = highest_row; i <= lowest_row; i++)
			{
				if(Board[(block_struct.y_pos)+i][(block_struct.x_pos)+j] && block_struct.Current_Shape[i][j] == 1)
				{
					return false;
				}
			}
		}

		LOWRFLAG = 1;
		return true;

	}
	return false;
}

void Move_Right(void)
{
	if( Check_Right() == true )
	{
		uint16_t temp_color;
		temp_color = block_struct.Current_Color;
		block_struct.Current_Color = LCD_COLOR_BLACK;
		Draw_Shape(&block_struct);


		block_struct.Current_Color = temp_color;
		block_struct.x_pos +=1;
		Draw_Shape(&block_struct);
	}
	else
	{

	}
}

void Move_Left(void)
{
	if( Check_Left() == true )
	{
		uint16_t temp_color;
		temp_color = block_struct.Current_Color;
		block_struct.Current_Color = LCD_COLOR_BLACK;
		Draw_Shape(&block_struct);


		block_struct.Current_Color = temp_color;
		block_struct.x_pos -=1;
		Draw_Shape(&block_struct);
	}
	else
	{

	}
}






