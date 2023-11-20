#include "stm32f10x.h"
#include "MyTimer.h"
#include "MyGPIO.h"
#include "MyADC.h"

//configure GPIO output pin PA5
//output mode : Out_Ppull
MyGPIO_Struct_typedef out;
MyTimer_Struct_TypeDef Temp;

void IEM(void) {
out.GPIO = GPIOA;
out.GPIO_Pin = 0;
out.GPIO_Conf = Out_Ppull;
MyGPIO_Init(&out);



//init timer
//periode 2sec

	
		
		Temp.Timer = TIM2;
		Temp.PSC = 2200;
		Temp.ARR = 0xffff;
		
		MyTimer_Base_Init(&Temp);
		
		MyTimer_Base_Start(Temp);

	//MyTimer_ActiveIT(Temp.Timer, 0, &ToggleLed);
	
	MyTimerSetPWMCycle(Temp.Timer, 1, 30);
	MyTimer_PMW(Temp.Timer, 1);



//init pwm


//sortie PWM connecte a la led

//faire varier la PWM en fonction du temps 

}

