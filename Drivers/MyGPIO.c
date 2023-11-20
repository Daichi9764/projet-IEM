 

#include "stm32f10x.h"
#include "MyGPIO.h"


void MyGPIO_Init(MyGPIO_Struct_typedef * GPIOStructPtr){
	if(GPIOStructPtr->GPIO == GPIOA){
		RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	}
	else if(GPIOStructPtr->GPIO == GPIOB){
		RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	}
	else if(GPIOStructPtr->GPIO == GPIOC){
		RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	}
	
	if(GPIOStructPtr->GPIO_Pin < 8){
		GPIOStructPtr->GPIO->CRL &= ~(0xF << GPIOStructPtr->GPIO_Pin*4);
		
		if (GPIOStructPtr->GPIO_Conf == In_PullDown){
			GPIOStructPtr->GPIO->CRL |= (In_PullDown << GPIOStructPtr->GPIO_Pin * 4);
			MyGPIO_Reset(GPIOStructPtr->GPIO,GPIOStructPtr->GPIO_Pin);
		}
		else if (GPIOStructPtr->GPIO_Conf == In_PullUp){
			GPIOStructPtr->GPIO->CRL |= (In_PullDown << GPIOStructPtr->GPIO_Pin * 4);
			MyGPIO_Set(GPIOStructPtr->GPIO,GPIOStructPtr->GPIO_Pin);
		}
		else{
			GPIOStructPtr->GPIO->CRL |= (GPIOStructPtr->GPIO_Conf << GPIOStructPtr->GPIO_Pin * 4);
		}
	}
	else{
		GPIOStructPtr->GPIO->CRH &= ~(0xF << (GPIOStructPtr->GPIO_Pin - 8)*4);
		
		if (GPIOStructPtr->GPIO_Conf == In_PullDown){
			GPIOStructPtr->GPIO->CRH |= (In_PullDown << (GPIOStructPtr->GPIO_Pin - 8) * 4);
			MyGPIO_Reset(GPIOStructPtr->GPIO,GPIOStructPtr->GPIO_Pin);
		}
		else if (GPIOStructPtr->GPIO_Conf == In_PullUp){
			GPIOStructPtr->GPIO->CRH |= (In_PullDown << (GPIOStructPtr->GPIO_Pin - 8) * 4);
			MyGPIO_Set(GPIOStructPtr->GPIO,GPIOStructPtr->GPIO_Pin);
		}
		else{
			GPIOStructPtr->GPIO->CRH |= (GPIOStructPtr->GPIO_Conf << (GPIOStructPtr->GPIO_Pin - 8) * 4);
		}
	}
}


int MyGPIO_Read(GPIO_TypeDef * GPIO,char GPIO_Pin){
	return ((GPIO->IDR)>>GPIO_Pin) & 1;
}

void MyGPIO_Set(GPIO_TypeDef * GPIO,char GPIO_Pin){
	GPIO->ODR |= (0x1 << GPIO_Pin);
}

void MyGPIO_Reset(GPIO_TypeDef * GPIO,char GPIO_Pin){
	GPIO->ODR = ~(0x1 << GPIO_Pin);
}

void MyGPIO_Toggle(GPIO_TypeDef * GPIO,char GPIO_Pin){
	GPIO->ODR ^= (0x1 << GPIO_Pin);
}


