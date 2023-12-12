/*
 * scheduler.c
 *
 *  Created on: Nov 15, 2023
 *      Author: ADMIN
 */

#include "scheduler.h"
#include "main.h"

struct sTask{
	void(*pTask)();

	uint32_t Delay;
	uint32_t Period;
	uint32_t Run;
	uint32_t taskId;

	struct sTask* next;
};


struct sTask* head = 0;

void SCH_Update(){
	if(!head) return;

	if(head->Delay == 0){
		++head->Run;
	}
	else --head->Delay;
}

void SCH_Dispatch_Tasks(){
	if(!head) return;

	if(head->Run > 0){
		(*(head->pTask))();
		--head->Run;

		if(head->Run == 0){

//			struct sTask* temp = head;//, *nextHead = head->next;
//
////			if(head->Period > 0) head->Delay = head->Period;
//
//			if(temp->Period > 0) SCH_Add_Task(temp->pTask, temp->Period, temp->Period);
//
//			SCH_Delete_Task(temp->taskId);
			if(head->Period > 0) SCH_Add_Task(head->pTask, head->Period, head->Period);

			SCH_Delete_Task(head->taskId);
//			if(head->Period == 100) HAL_GPIO_TogglePin(GPIOB, normal_Pin);
//			else HAL_GPIO_TogglePin(GPIOB, head_Pin);

			//		head = nextHead;
		}
	}
}

uint8_t SCH_Delete_Task(uint32_t taskId){
	if(!head) return 16;

	struct sTask* cur = head, *pre = head;
	while(cur && cur->taskId != taskId){
		pre = cur;
		cur = cur->next;
	}

	if(!cur) return 16;

	pre->next = cur->next;

	if(taskId == 0) head = pre->next;

	if(!cur->next) {
		free(cur);
		return taskId;
	}

	pre->next->Delay += cur->Delay;

	pre = pre->next;

	while(pre){
		--pre->taskId;
		pre = pre->next;
	}

	free(cur);

	return taskId;
}

uint32_t SCH_Add_Task(void (*pFunc)(), uint32_t Delay, uint32_t Period){
	struct sTask* temp = (struct sTask*)malloc(sizeof(struct sTask));
	temp->pTask = pFunc;
	temp->Delay = Delay;
	temp->Period = Period;
	temp->Run = 0;
	temp->taskId = 0;
	temp->next = 0;

	if(!head){
		head = temp;
		return 1;
	}
	else{
		struct sTask* cur = head, *pre = head;
		while(cur && temp->Delay >= cur->Delay){
			temp->Delay -= cur->Delay;
			pre = cur;
			cur = cur->next;
		}

		if(pre != cur){
			pre->next = temp;
			temp->next = cur;

			temp->taskId = pre->taskId + 1;
//			if(cur) cur->taskId = temp->taskId + 1;
		}
		else{
			temp->next = cur;
//			temp->taskId = 0;
//			HAL_GPIO_TogglePin(GPIOB, head_Pin);
			head = temp;
		}

		if(cur) cur->Delay -= temp->Delay;

		pre = temp;
		temp = temp->next;

		while(temp){
			temp->taskId = pre->taskId + 1;
			pre = temp;
			temp = temp->next;
		}


	}

	return 1;
}
