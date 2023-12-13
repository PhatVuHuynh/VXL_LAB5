/*
 * global.c
 *
 *  Created on: Dec 12, 2023
 *      Author: ADMIN
 */
#include "global.h"

uint8_t temp = 0;

static uint8_t cmd[10];

static struct{
	uint8_t buffer [ MAX_BUFFER_SIZE ];
	uint8_t index_buffer;
	uint8_t buffer_flag;
	uint8_t head;
	uint8_t tail;
} ringBuff = {.head = 0, .tail = 0, .index_buffer= 0, .buffer_flag = 0};

uint8_t checkCmd(){
	if(temp != '#') return 0;

	uint8_t end = ringBuff.head;
	while(ringBuff.buffer[end] != '#') {
		++end;
		end %= MAX_BUFFER_SIZE;
		if(end == ringBuff.head) return 0;
	}

	uint8_t start = end;

	while(ringBuff.buffer[start] != '!') {
		--start;
		if(start < 0) start = MAX_BUFFER_SIZE - 1;
		if(start == end) return 0;
	}

	uint8_t size = 0;
	if(start <= end){
		size = end - start + 1;
		memcpy(cmd, ringBuff.buffer + start, size);
	}
	else{
		size = MAX_BUFFER_SIZE - start;
		memcpy(cmd, ringBuff.buffer+ start, size);
		memcpy(cmd, ringBuff.buffer, end + 1);
		size += end;
	}
	cmd[size] = '\0';

	ringBuff.head = (ringBuff.tail + 1) % MAX_BUFFER_SIZE;
	ringBuff.tail = ringBuff.head;

	return 1;
}

void addBuffer(){
	ringBuff.buffer[ringBuff.tail++] = temp;
	ringBuff.tail %= MAX_BUFFER_SIZE;
}

void resetBuffer(){
	ringBuff.head = 0;
	ringBuff.tail = 0;
}

uint8_t isFull(){
	if(ringBuff.head + ringBuff.tail + 1 == MAX_BUFFER_SIZE) return 1;

	return 0;
}

void HAL_UART_RxCpltCallback ( UART_HandleTypeDef * huart ) {
	if(huart->Instance == USART2){
		HAL_UART_Transmit(&huart2, &temp, 1, 50);
		if(!isFull()){
			addBuffer();
		}
		ringBuff.buffer_flag = 1;
		HAL_UART_Receive_IT(&huart2, &temp, 1);
	}
}

uint8_t isFlag(){
	return ringBuff.buffer_flag;
}

void resetFlag(){
	ringBuff.buffer_flag = 0;
}

uint8_t* getCmd(){
	return cmd;
}
