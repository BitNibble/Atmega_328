/***********************************************************
Hardware: Atmega328.c
Author: Sergio Santos
	<sergio.salazar.santos@gmail.com>
Created: 04/10/2020 16:37:53
Comment:
	74HC595
	-PD4 pin 6 - Serial Data
	-PD5 pin 11 - Shift Bit
	-PD7 pin 12 - Output
	Shift Register Connected to relay board
	LCD
	-PB0 pin 14 cmd
	-PB1 pin 15 cmd
	-PB2 pin 16 cmd
	-PB3 pin 17 cmd
	-PC0 pin 23 data
	-PC1 pin 24 data
	-PC2 pin 25 data
	-PC3 pin 26 data
	Bluetooth HC-05 (MAX 232 bypassed with jumpers)
	-PD0 pin 2 Tx
	-PD1 pin 3 Rx
	
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
//uint8_t i,j;
char* uartreceive = NULL; // pointing to Rx Buffer raw
char uartrcv[UART_RX_BUFFER_SIZE];
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
	sh = HC595enable(&DDRD,&PORTD,4,5,7); //4,5,7 using board from ETT with altered pin.
	// UART 103 para 9600, 68 para 14400, 25 para 38400, 8 para 115200 at 16Mhz
	// UART 51 para 9600, 12 para 38400 at 8Mhz
	uart = m.usart.enable(12,8,1,NONE);
	tc0 = m.tc0.enable(1, 1);
	tc0.start(~0);
	
	uint8_t output = 0xFF;
	d = 0;
	
	// uart detect '\n'
	uint8_t uartoneshot = 0;
	sh.byte(output);
	
	// Replace with your application code
    while (TRUE)
    {
		// preamble
		// lcd reboot
		lcd.reboot();
		// uart capture
		if(uartoneshot){ uartoneshot = 0; uart.rxflush(); strcpy(uartrcv, " "); }
		uartreceive = uart.gets(); // UART1
		if(uart.getch() == '\n'){ uartoneshot = 1; strcpy(uartrcv, uartreceive); }
		// procedures
		
		lcd.gotoxy(0,0);
		lcd.string_size("Welcome",7);
		
		lcd.gotoxy(1,0);
		
		if(!strcmp(uartrcv, "led 1 on\r\n")){
			if(output & 1){
				output&=~1;
				strcpy(uartmsg, "led 1 on");
				uart.puts("led 1 on\n");
			}else{
				output|=1;
				strcpy(uartmsg, "led 1 off");
				uart.puts("led 1 off\n");
			}
		}
		if(!strcmp(uartrcv, "led 1 off\r\n")){
				output|=1;
				strcpy(uartmsg, "led 1 off");
				uart.puts("led 1 off\n");
		}
		
		if(!strcmp(uartrcv, "led 2 on\r\n")){
			if(output & 2){
				output&=~2;
				strcpy(uartmsg, "led 2 on");
				uart.puts("led 2 on\n");
			}else{
				output|=2;
				strcpy(uartmsg, "led 2 off");
				uart.puts("led 2 off\n");
			}
		}
		if(!strcmp(uartrcv, "led 2 off\r\n")){
			output|=2;
			strcpy(uartmsg, "led 2 off");
			uart.puts("led 2 off\n");
		}
		
		if(!strcmp(uartrcv, "led 3 on\r\n")){
			if(output & 4){
				output&=~4;
				strcpy(uartmsg, "led 3 on");
				uart.puts("led 3 on\n");
			}else{
				output|=4;
				strcpy(uartmsg, "led 3 off");
				uart.puts("led 3 off\n");
			}
		}
		if(!strcmp(uartrcv, "led 3 off\r\n")){
			output|=4;
			strcpy(uartmsg, "led 3 off");
			uart.puts("led 3 off\n");
		}
		
		if(!strcmp(uartmsg, "led 4 on\r\n")){
			if(output & 8){
				output&=~8;
				strcpy(uartmsg, "led 4 on");
				uart.puts("led 4 on\n");
			}else{
				output|=8;
				strcpy(uartmsg, "led 4 off");
				uart.puts("led 4 off\n");
			}
		}
		if(!strcmp(uartrcv, "led 4 off\r\n")){
			output|=8;
			strcpy(uartmsg, "led 4 off");
			uart.puts("led 4 off\n");
		}
			
		if(!strcmp(uartrcv, "all off\r\n")){
			output = 0xFF;
			strcpy(uartmsg, "all off");
			uart.puts("all off\n");
			_delay_ms(100);
		}
		
		lcd.string_size("HC:",3);
		lcd.string_size(uartmsg,13);
		
		sh.byte(output);
		
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
	/**
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
	**/
}

/***EOF***/


/******
1º Sequence
2º Scope
3º Pointer and Variable
******/

