#ifndef MYUART_H
#define MYUART_H

#include "stm32f10x.h"

void MyUART_init(void);
int ProcessCommand(char command);

#endif