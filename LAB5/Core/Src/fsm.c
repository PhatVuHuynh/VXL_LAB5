/*
 * fsm.c
 *
 *  Created on: Dec 12, 2023
 *      Author: ADMIN
 */
#include "fsm.h"
#include "global.h"
#include "scheduler.h"

uint8_t cmd_flag = 0;
uint8_t adc_val = 0;

static char cmd[10];

extern ADC_HandleTypeDef hadc1;

extern UART_HandleTypeDef huart2;

static enum{
	read, handle
} command_status = read;

static enum{
	wait, send
} uart_status = wait;

void command_parsel_fsm(){
	switch(command_status){
		case read:
			if(isFlag()){
				HAL_GPIO_TogglePin(GPIOA, LED_Pin);
				if(isFull()) resetBuffer();
				if(checkCmd()){
					command_status = handle;
				}

				resetFlag();
			}
			break;
		case handle:
			command_status = read;
			strcpy(cmd, (char*)getCmd());
			cmd_flag = 1;
			break;
	}
}

void uart_communiation_fsm(){
	switch(uart_status){
		case wait:
			adc_val = HAL_ADC_GetValue(&hadc1) % 4096;
			if (cmd_flag) {
				if (strcmp((const char*)cmd, RST) == 0) {
					SCH_Add_Task(printVal, 0, 3 * SEC_TO_MILISEC / TICK);
					uart_status = send;
				}
				cmd_flag = 0;
			}
			break;
		case send:
			if (cmd_flag) {
				if (!strcmp((const char*)cmd, OK)){
					SCH_Delete_Task(printVal);
					uart_status = wait;
				}
				cmd_flag = 0;
			}
			break;
	}
}

void printVal(void) {
	char str[20];
	uint8_t len = sprintf(str, "!ADC=%u#\n", (unsigned int) adc_val);
	HAL_UART_Transmit(&huart2, (void*) str, len, 100);
}
