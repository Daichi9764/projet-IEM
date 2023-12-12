#include "stm32f10x.h"
#include "MyUART.h"

#define TIMER_CLOCK_FREQ 1000000 // 1 MHz

void MyUART_init(void) {
	// Clock configuration register for GPIOA and USART1
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN | RCC_APB2ENR_IOPAEN;
	
	// UART configuration
	USART1->BRR = 7500; // Set the serial communication speed (baud rate of 9600 when clock is running at 72MHz)
	USART1->CR1 |= USART_CR1_UE; // Enable USART
	USART1->CR1 |= USART_CR1_TE | USART_CR1_UE; // Enable transmitter and receiver
	
	// Enable reception interrupt at USART level
	USART1->CR1 |= USART_CR1_RXNEIE;
	
	// Enable interrupt at NVIC level
	NVIC->ISER[1] |= (0x1<<5);
	// Level of prority set to 3 as default
	NVIC->IP[37] = 0x3;
}

void USART1_IRQHandler(void) {
	if(USART1->SR & USART_SR_RXNE) { // Verify that the data is ready to be read
		char received_char = USART1->DR; // Read data that was received
		ProcessCommand(received_char);
	}
}
	
int ProcessCommand(char command) {
    static float period = 2.0; // Initialize with a 2s period

    if (command == '+') {
        period = (period < 4.0) ? period + 0.1 : 4.0; // Not go more than 4 seconds
    } else if (command == '-') {
        period = (period > 0.4) ? period - 0.1 : 0.4; // No go lower than 4s
    }

    return period * TIMER_CLOCK_FREQ;
}