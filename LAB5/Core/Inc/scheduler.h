/*
 * scheduler.h
 *
 *  Created on: Nov 15, 2023
 *      Author: ADMIN
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include <stdint.h>
#include <stdlib.h>

void SCH_Update();

void SCH_Dispatch_Tasks();

uint8_t SCH_Delete_Task(uint32_t taskId);

uint32_t SCH_Add_Task(void(*pFunc)(), uint32_t Delay, uint32_t Period);


#endif /* INC_SCHEDULER_H_ */
