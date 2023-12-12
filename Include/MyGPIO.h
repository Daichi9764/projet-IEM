#ifndef MYGPIO_H
#define MYGPIO_H


#include "stm32f10x.h"

typedef struct{
	GPIO_TypeDef * GPIO;
	char GPIO_Pin;
	char GPIO_Conf;
} MyGPIO_Struct_typedef;


#define In_Floating 0x04
#define In_PullDown 0x08
#define In_PullUp 0x18
#define In_Analog 0x00

#define Out_Ppull 0x02
#define Out_OD 0x06
#define AltOut_Ppull 0x0A
#define AltOut_OD 0x0E


void MyGPIO_Init(MyGPIO_Struct_typedef * GPIOStructPtr);
int MyGPIO_Read(GPIO_TypeDef * GPIO,char GPIO_Pin);
void MyGPIO_Set(GPIO_TypeDef * GPIO,char GPIO_Pin);
void MyGPIO_Reset(GPIO_TypeDef * GPIO,char GPIO_Pin);
void MyGPIO_Toggle(GPIO_TypeDef * GPIO,char GPIO_Pin);



#endif
