#include "stm32f10x.h"
#include "MyTimer.h"
#include "MyGPIO.h"
#include "MyADC.h"
#include "stdbool.h"

//configure GPIO output pin PA5
//output mode : Out_Ppull
MyGPIO_Struct_typedef out;
MyTimer_Struct_TypeDef TimerStep;
MyTimer_Struct_TypeDef TimerPWM;


int cnt = 0;
bool monter = true;
//50maj de pwm par pente
void MajPWM() {
	if (monter) {
			cnt++;
	}
	else
	{
		cnt--;
	}

	MyTimerSetPWMCycle(TimerPWM.Timer, 1, cnt * 2);
	//clear interrupt flag
	TIM2->SR &= ~TIM_SR_UIF;
	
		if(cnt == 50){
		monter = false;
	}
	if (cnt == 0){
		monter = true;
	}
}

void IEM(void) {




	//---------PWM maj -----------------
		//timer step maj PWM = TIM2. period = 2 sec / 50 = 0.04 sec
		TimerStep.Timer = TIM2;
		TimerStep.PSC = 1694;
		TimerStep.ARR = 1700;		
		MyTimer_Base_Init(&TimerStep);
		MyTimer_Base_Start(TimerStep);
		MyTimer_ActiveIT(TimerStep.Timer, 3, &MajPWM);
	//---------------------------------
		
	
	//-------PWM----------------
	//pin config : TIM3 CH1 output. connected to PWM
out.GPIO = GPIOA;
out.GPIO_Pin = 6;
out.GPIO_Conf = AltOut_Ppull;
MyGPIO_Init(&out);
	
	//timer PWM = TIM3 CH 1. frequence 1kHz
		TimerPWM.Timer = TIM3;
		TimerPWM.PSC = 143;
		TimerPWM.ARR = 500;	
	MyTimer_Base_Init(&TimerPWM);
		MyTimer_Base_Start(TimerPWM);
		MyTimerSetPWMCycle(TimerPWM.Timer, 1, 70);
		MyTimer_PMW(TimerPWM.Timer, 1);

	//----------------------------

		
	}



	//A FAIRE	
//init pwm
//sortie PWM connecte a la led
//faire varier la PWM en fonction du temps 



