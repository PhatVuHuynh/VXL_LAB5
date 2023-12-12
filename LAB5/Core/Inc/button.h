/*
 * button.h
 *
 *  Created on: Nov 3, 2023
 *      Author: ADMIN
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "main.h"

#define NORMAL_STATE GPIO_PIN_SET
#define PRESS_STATE GPIO_PIN_RESET

extern int key_flag;

void subKeyProcess();

int is_Pressed();

void getKeyInput();

//extern int key_flag[3];
//
//void subKeyProcess(int id);
//
//int is_Pressed(int id);
//
//void getKeyInput(int id, uint16_t BUTTON);

#endif /* INC_BUTTON_H_ */
