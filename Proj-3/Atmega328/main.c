/***********************************************************
Hardware: Atmega328.c
Author: Sergio Santos
	<sergio.salazar.santos@gmail.com>
Created: 04/10/2020 16:37:53
Comment:
	Stable
 **********************************************************/
#define F_CPU 8000000UL

/*** File library ***/
#include "atmega328mapping.h"
#include "function.h"
#include "lcd2p.h"
#include "keypad.h"
#include "74hc595.h"
#include "atcommands.h"
#include <util/delay.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <inttypes.h>
#include <string.h>
//#include <stdarg.h>
//#include <math.h>

/*** File Constant and Macros ***/
#define TRUE 1
#define ZERO 0

/*** File Variable ***/
ATMEGA328 m;
TIMER_COUNTER0 tc0;
HC595 sh;
UART uart;
FUNC func;
LCD0 lcd;
uint16_t d;
uint8_t i,j;
char* uartreceive = NULL; // pointing to Rx Buffer
char uartmsg[UART_RX_BUFFER_SIZE];

/*** File Header ***/
void PORTINIT(void);

/*** File Procedure & Function ***/
int main(void)
{
	m = ATMEGA328enable();
	func = FUNCenable();
	lcd = LCD0enable(&DDRB, &PINB, &PORTB, &DDRC, &PINC, &PORTC); //using arduino
	// HC595 sh = HC595enable(&DDRB,&PORTB,3,1,0); //using arduino
	sh = HC595enable(&DDRD,&PORTD,4,5,7); //4,7,5 using board from ETT with altered pin.
	// UART 103 para 9600, 68 para 14400, 25 para 38400, 8 para 115200 at 16Mhz
	// UART 51 para 9600, 12 para 38400 at 8Mhz
	uart = m.usart.enable(12,8,1,NONE);
	tc0 = m.tc0.enable(1, 1);
	tc0.start(~0);
	
	uint8_t i = 0;
	uint8_t output = 255;
	d = 0;
	
	// uart detect '\n'
	//uint8_t uartoneshot = 0;
	sh.byte(output);
	
	// Replace with your application code
    while (TRUE)
    {
		// preamble
		// lcd reboot
		lcd.reboot();
		// uart capture
		//if(uartoneshot){ uartoneshot = 0; uart.rxflush();} // the matrix
		strcpy(uartmsg, " ");
		uartreceive = uart.gets(); // UART1
		if(uart.getch() == '\n'){ strcpy(uartmsg, uartreceive); uart.rxflush();}
		// procedures
		
		lcd.gotoxy(0,0);
		lcd.string_size("Welcome",7);
		
		
		
		lcd.gotoxy(1,0);
		lcd.string_size("HC:",3);
		lcd.string_size(uartmsg,13);
		
		if(!strcmp(uartmsg, "led 1 on\r\n")){
			output = 5;
			
			for(i = 0; i < 8; i++){
				_delay_ms(100);
				sh.bit(output & (1 << i));
				
				
				lcd.gotoxy(0,8);
				lcd.string(func.ui16toa(output));
				lcd.hspace(2);
				lcd.string(func.ui16toa((1 << i)));
				
			}
			sh.out();
			
			
			
			//shift.byte(output);
		}
			
		if(!strcmp(uartmsg, "led 1 off\r\n")){
			output = 0;
			sh.byte(255);
		}
			
			
		//sh.byte(output);
		
    }
}

void PORTINIT(void)
{
	DDRB=0x0B;
	PORTB=0x0B;
}

/*** File Interrupt ***/
ISR(TIMER0_OVF_vect)
{
	d++;
	/*
	// Play around
	if(i < 8){
		if(j){
			sh.bit(1);
			sh.out();
			i++;
		}else{
			sh.bit(0);
			sh.out();
			i++;
		}
	}else{
		i = 0; 
		if(j) j = 0;
		else j =1;
	}
	*/
}

/***EOF***/


/******
1º Sequence
2º Scope
3º Pointer and Variable
******/

