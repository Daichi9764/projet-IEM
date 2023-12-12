#include "stm32f10x.h"
#include "MyADC.h"
#include "MyGPIO.h"

void MyADC_init(void) {	
	// Set prescaler to div6
	// Clock configuration register (RCC_CFGR), field ADC PRE[1:0] set to 10 for div6
	RCC->CFGR &= ~(0x3<<14);
	RCC->CFGR |= (0x2<<14);
	
	//no need to set caliber
	//register:
	//ADC status register ADC_SR
	//ADC Control Register ADC_CR
	//ADC Sequence Register ADC_SQR
	//EOC: End of conversion. cleared by software or by reading the ADC_DR.

	//enable adc 
	// Enable clock for adc
	RCC -> APB2ENR |= RCC_APB2ENR_ADC1EN;
	
	// Set ADON bit in ADC_CR2 register
	ADC1 -> CR2 |= ADC_CR2_ADON;

	//If the EXTTRIG control bit is set then external events are able to trigger a conversion
	//config with EXTTRIG (ADC1 -> CR2)
	//EXTSEL set to SW Start (EXTSEL[2:0] set to 111)
	ADC1 -> CR2 |= ADC_CR2_EXTTRIG;
	ADC1 -> CR2 |= ADC_CR2_EXTSEL&0;
	
	// Set conversion sequence so it uses channel 8
	ADC1->SQR3 = 8;
	
	//If a regular channel was converted:
	//The converted data is stored in the 16-bit ADC_DR register
	//The EOC (End Of Conversion) flag is set
	//and an interrupt is generated if the EOCIE is set.
	//result of conversion stored in ADC1 -> DR
	
	// Set sampling time for channel 8
	ADC1->SMPR2 |= ADC_SMPR2_SMP8; // Sampling time for channel 8

//interruption when end of conversion 
	//when flag EOC is set, send IT to NVIC to read data.
	//enable interrupt at ADC level : EOCIE set to 1	
		ADC1->CR1 |= ADC_CR1_EOCIE;
	// Enable interrupt at NVIC level
	NVIC->ISER[0] |= (0x1<<18);
	//NVIC_EnableIRQ(ADC1_2_IRQn);
	//level of prority set to 3 as default
	NVIC->IP[18] = 0x3;
 //NVIC_SetPriority(ADC1_2_IRQn, 3);
	
}



//EOC Handler
	void ADC1_IRQHandler() {
		//Clear EOC flag, may not be necessary because cleared when reading th DR register
		ADC1->SR &= ~ADC_SR_EOC;
	}
	
	int MyADC_ReadADC(){
	// Start ADC conversion
	ADC1->CR2 |= ADC_CR2_SWSTART;
		
	// Wait until conversion is completed
	while (!(ADC1->SR & ADC_SR_EOC));
		
	// read and return ADC value
	return ADC1->DR;
}
	

	