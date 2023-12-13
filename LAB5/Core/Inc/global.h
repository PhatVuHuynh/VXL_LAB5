/*
 * global.h
 *
 *  Created on: Dec 12, 2023
 *      Author: ADMIN
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_
#include "main.h"
#include <stdlib.h>
#include <stdio.h>
#include "string.h"

# define MAX_BUFFER_SIZE 30

#define TICK 10 //call back
#define SEC_TO_MILISEC 1000

extern ADC_HandleTypeDef hadc1;

extern UART_HandleTypeDef huart2;

extern uint8_t temp;

void addBuffer();
uint8_t checkCmd();
void resetBuffer();
uint8_t isFull();
void printVal();
uint8_t isFlag();
void resetFlag();
uint8_t* getCmd();

#endif /* INC_GLOBAL_H_ */
