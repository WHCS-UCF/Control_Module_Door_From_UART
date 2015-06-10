/*
 * Control_Module_Door_From_UART.cpp
 *
 * Created: 6/10/2015 1:11:03 PM
 *  Author: Jimmy
 */ 

#define F_CPU 16000000L
#include <avr/io.h>
#include "MEGA88A_UART_LIBRARY.h"
#include <util/delay.h>

//Initializes an LED attached to Port B pin 0.
void LED_Init() {
	DDRB |= (1<<DDB0);
	PORTB |= (1<<DDB0);
}

void LED_blink() {
	PORTB ^= (1<<DDB0);
	_delay_ms(1000);
	PORTB ^= (1<<DDB0);
	_delay_ms(1000);
}

void initStrikePin() {
	DDRC |= (1<<DDC1);
}

void strikeOn() {
	PORTC |= (1<<DDC1);
}

void strikeOff() {
	PORTC &= ~(1<<DDC1);	
}

int main(void)
{
	int i;
	
	LED_Init();
	for(i=0;i<3;i++){
		LED_blink();
	}
	
	initUart();
	initStrikePin();
	
	while(1)
	{
		uint8_t letter;
		letter = USART_ReceiveByte();
		USART_SendByte(letter);
		if(letter == 'O') {
			strikeOn();
		}
		else {
			strikeOff();
		}
	}
}