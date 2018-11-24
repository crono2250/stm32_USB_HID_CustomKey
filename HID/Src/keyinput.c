/*
 * keyinput.c
 *
 *  Created on: 2018/11/24
 *      Author: cronos
 */
#include "stm32f1xx_hal.h"
#include "xprintf.h"

static uint8_t keydata[16] = {0};
uint8_t buf = 0;


/*
[ROW,COL]

[3,0] [3,1] [3,2] [3,3]
[2,0] [2,1] [2,2] [2,3]
[1,0] [1,1] [1,2] [1,3]
[0,0] [0,1] [0,2] [0,3]

KP_ROW0 = 0x0001;
KP_ROW1 = 0x0002;
KP_ROW2 = 0x0004;
KP_ROW3 = 0x0008;
*/

uint8_t KeyMatrix_Input(void)
{
//HAL_GPIO_WritePin(GPIOA, KP_ROW0_Pin|KP_ROW1_Pin|KP_ROW2_Pin|KP_ROW3_Pin, GPIO_PIN_RESET);
//HAL_GPIO_ReadPin(GPIOA, KP_COL0_Pin);
;

uint8_t i;
uint8_t	ROW_COUNT;
uint8_t	COL_COUNT;
uint16_t	KeyData_Raw = 0;

	for(ROW_COUNT = 0; ROW_COUNT <= 3; ROW_COUNT++)
	{
		HAL_GPIO_WritePin(GPIOA, KP_ROW0_Pin|KP_ROW1_Pin|KP_ROW2_Pin|KP_ROW3_Pin, GPIO_PIN_SET);
//		GPIOA->ODR = (1 << ROW_COUNT) & 0x000F;
		HAL_GPIO_WritePin(GPIOA, (KP_ROW0_Pin << ROW_COUNT) & 0x000F, GPIO_PIN_RESET);

		HAL_Delay(1);
//		KeyData_Raw = (GPIO_ReadInputData(GPIOA) & 0x000F);
		KeyData_Raw = GPIOA->IDR;
		KeyData_Raw = (KeyData_Raw >> 4) & 0x000F;

		xprintf("data = %04X\n",KeyData_Raw);

		for(COL_COUNT = 0; COL_COUNT <= 3; COL_COUNT++)
		{
			if(KeyData_Raw & 0x0001)
			{
				keydata[(COL_COUNT + ROW_COUNT*4)] = 1;
			}
			else
			{
				keydata[(COL_COUNT + ROW_COUNT*4)] = 0;
			}
			KeyData_Raw = KeyData_Raw >> 1;

		}

	}

	xputs("key : ");
	for(i = 0; i <= 15; i++)
	{
		xprintf(" %1d",keydata[i]);
	}
	xputs("\n");
	return buf;
}
