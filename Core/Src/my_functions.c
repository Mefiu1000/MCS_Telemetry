/*
 * my_functions.c
 *
 *  Created on: Apr 27, 2023
 *      Author: sebastian.sosnowski
 */

#include "my_functions.h"


#define f_unmount(path) f_mount(&SD_FATFS, path, 0);

uint8_t sd_write(uint8_t num_msg)
{
	uint8_t Size;
	char data[60]; //buffor UART

	if(HAL_GPIO_ReadPin(SD_A_SIGNAL_GPIO_Port, SD_A_SIGNAL_Pin) != GPIO_PIN_SET)
	{
		Size = sprintf(data, "No card detected \n\r");
		HAL_UART_Transmit(&huart1, (uint8_t*) data, Size, 1000);
		return 1; //ERROR
	}

	FRESULT Result;
	FATFS SD_FATFS;
	FIL SD_Card_File;

	Result = f_mount(&SD_FATFS, "", 1);

	if(Result != FR_OK)
	{
		Size = sprintf(data, "Mount error \n\r");
		HAL_UART_Transmit(&huart1, (uint8_t*) data, Size, 1000);
	}
	else
	{
		Size = sprintf(data, "Mount correct  \n\r");
		HAL_UART_Transmit(&huart1, (uint8_t*) data, Size, 1000);

		Result = f_open(&SD_Card_File, "pomiar_T.txt", FA_WRITE | FA_CREATE_ALWAYS);\

		if(Result != FR_OK)
		{
			Size = sprintf(data, "File open error \n\r");
			HAL_UART_Transmit(&huart1, (uint8_t*) data, Size, 1000);
		}
		else
		{
			Size = sprintf(data, "File opened \n\r");
			HAL_UART_Transmit(&huart1, (uint8_t*) data, Size, 1000);

			for(uint8_t i = 0; i < 10; i++)
			{
				f_printf(&SD_Card_File, " TEST %d\n", i);
			}

			Result = f_close(&SD_Card_File);

			if(Result != FR_OK)
			{
				Size = sprintf(data, "File close error \n\r");
				HAL_UART_Transmit(&huart1, (uint8_t*) data, Size, 1000);
				f_unmount("") //not sure if its needed
			}
			else
			{
				Size = sprintf(data, "File closed \n\r");
				HAL_UART_Transmit(&huart1, (uint8_t*) data, Size, 1000);
			}
		}
	}

	return 0; //OK
}

