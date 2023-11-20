#include "stm32f10x.h"
#include "MyTimer.h"

// create pointer for tim2 handler function
void (*TIM2Handler_Fct_Ptr) (void);

void MyTimer_Base_Init(MyTimer_Struct_TypeDef * Timer) {
	
	/* Initialize timers */
		if (Timer -> Timer == TIM2){
		RCC -> APB1ENR |= RCC_APB1ENR_TIM2EN;
	}
	else if (Timer -> Timer == TIM3) {
		RCC -> APB1ENR |= RCC_APB1ENR_TIM3EN;
	}
	
	/* Initialize PCS and ARR */
	Timer -> Timer -> PSC = Timer -> PSC;
	Timer -> Timer -> ARR = Timer -> ARR;
}

void MyTimer_ActiveIT(TIM_TypeDef * Timer, char Prio, void (*IT_function) (void)) {
	Timer -> DIER |= TIM_DIER_UIE;
	TIM2Handler_Fct_Ptr = IT_function;
	NVIC_EnableIRQ(TIM2_IRQn);
	NVIC_SetPriority(TIM2_IRQn, Prio);
}

void TIM2_IRQHandler(void) {
	TIM2 -> SR &= -(TIM_SR_UIF);
	(*TIM2Handler_Fct_Ptr)();
}

void MyTimer_PMW(TIM_TypeDef * Timer, char Channel) {
	switch(Channel){
		case 1:
			Timer -> CCMR1 &= ~(TIM_CCMR1_OC1M);
			Timer -> CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1;
			Timer-> CCER |= TIM_CCER_CC1E;
			break;
		case 2:
			Timer->CCMR1 &= ~(TIM_CCMR1_OC2M);
			Timer->CCMR1 |= TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_2;
			Timer->CCER |= TIM_CCER_CC2E;
			break;
		case 3:
			Timer->CCMR2 &= ~(TIM_CCMR2_OC3M);
			Timer->CCMR2 |= TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3M_1;
			Timer->CCER |= TIM_CCER_CC3E;
			break;
		case 4:
			Timer->CCMR2 &= ~(TIM_CCMR2_OC4M);
			Timer->CCMR2 |= TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1;
			Timer->CCER |= TIM_CCER_CC4E;
			break;
	}
	Timer->CR1 |= TIM_CR1_ARPE;
	Timer->CR1 &= ~(TIM_CR1_DIR);
	Timer->EGR |= TIM_EGR_UG;
}

void MyTimerSetPWMCycle(TIM_TypeDef * Timer, char Channel, int cycle) {
	Timer->CCR1 = 0x0300;
	switch(Channel) {
		case 1:
			Timer->CCR1 = (Timer->ARR * cycle) / 100;
			break;

	}
}
