#ifndef MYTIMER_H
#define MYTIMER_H

#include "stm32f10x.h"

typedef struct {
	TIM_TypeDef * Timer;
	unsigned short ARR;
	unsigned short PSC;
} MyTimer_Struct_TypeDef;


void MyTimer_Base_Init(MyTimer_Struct_TypeDef * Timer);
void MyTimer_ActiveIT(TIM_TypeDef * Timer, char Prio, void (*IT_function) (void));
void MyTimer_PMW(TIM_TypeDef * Timer, char Channel);
void MyTimerSetPWMCycle(TIM_TypeDef * Timer, char Channel, int cycle);

#define MyTimer_Base_Start(Temp) (Temp.Timer -> CR1 |= 0x01)
#define MyTimer_Base_Stop(Timer) (Timer.Timer -> CR1 |= 0x00)

#endif
