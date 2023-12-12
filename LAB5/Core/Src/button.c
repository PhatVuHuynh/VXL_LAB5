/*
 * button.c
 *
 *  Created on: Nov 3, 2023
 *      Author: ADMIN
 */
#include "button.h"

int key_flag;//[3] = {0, 0, 0};

int keyReg0 = NORMAL_STATE;//[3] = {NORMAL_STATE, NORMAL_STATE, NORMAL_STATE};
int keyReg1 = NORMAL_STATE;//[3] = {NORMAL_STATE, NORMAL_STATE, NORMAL_STATE};
int keyReg2 = NORMAL_STATE;//[3] = {NORMAL_STATE, NORMAL_STATE, NORMAL_STATE};

int preState = NORMAL_STATE;//[3] = {NORMAL_STATE, NORMAL_STATE, NORMAL_STATE};
int TimerForKeyPress = 50;

void subKeyProcess(){
	//HAL_GPIO_TogglePin(GPIOA, A5_Pin);
	key_flag = 1;
}

int is_Pressed(){
	if(key_flag){
		key_flag = 0;
		return 1;
	}
	return 0;
}

void getKeyInput(){
	keyReg0 = keyReg1;
	keyReg1 = keyReg2;
//	keyReg2 = HAL_GPIO_ReadPin(GPIOB, BUTTON1_Pin);

	if(keyReg0 == keyReg1 && keyReg1 == keyReg2){
		if(keyReg2 != preState){
			preState = keyReg2;

			if(keyReg2 == PRESS_STATE){
//				subKeyProcess();
				key_flag = 1;
				//TimerForKeyPress = 200;
				TimerForKeyPress = 50;
			}
		}
		else{
			--TimerForKeyPress;
			if(TimerForKeyPress <= 0){
				if(keyReg2 == PRESS_STATE){
					subKeyProcess();
				}
				//TimerForKeyPress = 200;
				TimerForKeyPress = 50;
			}
		}
	}
};

//void subKeyProcess(int id){
//	//HAL_GPIO_TogglePin(GPIOA, A5_Pin);
//	key_flag[id] = 1;
//}

//int is_Pressed(int id){
//	if(key_flag[id]){
//		key_flag[id] = 0;
//		return 1;
//	}
//	return 0;
//}
//
//void getKeyInput(int id, uint16_t BUTTON){
//	keyReg0[id] = keyReg1[id];
//	keyReg1[id] = keyReg2[id];
//	keyReg2[id] = HAL_GPIO_ReadPin(GPIOB, BUTTON);
//
//	if(keyReg0[id] == keyReg1[id] && keyReg1[id] == keyReg2[id]){
//		if(keyReg2[id] != preState[id]){
//			preState[id] = keyReg2[id];
//
//			if(keyReg2[id] == PRESS_STATE){
//				subKeyProcess(id);
//				//TimerForKeyPress = 200;
//				TimerForKeyPress = 50;
//			}
//		}
//		else{
//			--TimerForKeyPress;
//			if(TimerForKeyPress <= 0){
//				if(keyReg2[id] == PRESS_STATE){
//					subKeyProcess(id);
//				}
//				//TimerForKeyPress = 200;
//				TimerForKeyPress = 50;
//			}
//		}
//	}
//};
