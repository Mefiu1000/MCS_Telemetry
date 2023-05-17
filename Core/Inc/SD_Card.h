/*
 * my_functions.h
 *
 *  Created on: Apr 27, 2023
 *      Author: sebastian.sosnowski
 */

#ifndef INC_MY_FUNCTIONS_H_
#define INC_MY_FUNCTIONS_H_



#endif /* INC_MY_FUNCTIONS_H_ */

#include "main.h"
#include "fatfs.h"
#include "usart.h"
#include <stdio.h>


uint8_t sd_write2(uint8_t num_msg, char* file_name);
uint8_t sd_read2(uint8_t num_msg, char* file_name);
