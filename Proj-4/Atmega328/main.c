/*********************************************************************
Hardware: Atmega328.c
Author: Sergio Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Created: 20/04/2023 14:00:00
Comment:
		74HC595
			Shift Register Connected to relay board
	-PD4 pin 6 - Serial Data
	-PD5 pin 11 - Shift Bit
	-PD7 pin 12 - Output
		LCD
	-PB0 pin 14 cmd
	-PB1 pin 15 cmd
	-PB2 pin 16 cmd
	-PB3 pin 17 cmd
	-PC0 pin 23 data
	-PC1 pin 24 data
	-PC2 pin 25 data
	-PC3 pin 26 data
		Bluetooth HC-05 
			(MAX 232 bypassed with jumpers) 
			12 para 38400 at 8Mhz, AT+BAUD6\r\n, AT+TYPE1\r\n,
			AT+ROLE0\r\n, AT+PIN916919\r\n.
	-PD0 pin 2 Tx
	-PD1 pin 3 Rx
		Buttons
	-PB4 pin 18
	-PB5 pin 19
	-PC4 pin 27
	-PC5 pin 28
	
	Stable
 ********************************************************************/
/*** Frequency ***/
#define F_CPU 8000000UL

/*** Compiler ***/
#if (__GNUC__ * 100 + __GNUC_MINOR__) < 304
#error "This library requires AVR-GCC 3.4 or later, update to newer AVR-GCC compiler !"
#endif

/*** File library ***/
#include "atmega328mapping.h"
#include "function.h"
#include "lcd2p.h"
//#include "keypad.h"
#include "74hc595.h"
#include "explode.h"
//#include "atcommands.h"
#include <util/delay.h>
//#include <stdio.h>
#include <stdlib.h>
//#include <inttypes.h>
#include <string.h>
//#include <stdarg.h>
#include <math.h>

/*** File Constant and Macros ***/
#define TRUE 1
#define ZERO 0

/*** File Variable ***/
ATMEGA328 m;
TIMER_COUNTER1 tc1;
HC595 sh;
UART uart;
FUNC func;
LCD0 lcd;
EXPLODE button;

uint8_t input;
char* uartreceive = NULL; // pointing to Rx Buffer raw
char uartrcv[UART_RX_BUFFER_SIZE];
char uartmsg[UART_RX_BUFFER_SIZE];

/*** File Header ***/
void PORTINIT(void);

/*** File Procedure & Function ***/
int main(void)
{	
PORTINIT();
	
m = ATMEGA328enable();
func = FUNCenable();
lcd = LCD0enable(&DDRB, &PINB, &PORTB, &DDRC, &PINC, &PORTC);
sh = HC595enable(&DDRD,&PORTD,4,5,7);
// UART 103 para 9600, 68 para 14400, 25 para 38400, 8 para 115200 at 16Mhz
// UART 51 para 9600, 12 para 38400 at 8Mhz
uart = m.usart.enable(12,8,1,NONE);
tc1 = m.tc1.enable(4, 2);
button = EXPLODEenable();
	
tc1.start(1024);
tc1.compareA(0x1AFF);
	
// Replace with your application code
uint8_t window;
for (window = 0; TRUE; ) // Looping
{
	if(!window){ // preamble
		lcd.reboot();
		input = ( m.portc.reg->pin & 0xF0 ) | ( m.portb.reg->pin >> 4 );
		button.update(&button.par, input);
		uartreceive = uart.gets();
		strcpy(uartrcv, uartreceive);
		if(uart.getch() == '.'){ uart.rxflush(); }
		else{strcpy( uartmsg, uartreceive ); }
		window = 1; continue;
	}		
/********************************************************************/
	if(window == 1){ // application code
		
		
		
		
		
		window = 0; continue;
	}
}}

void PORTINIT(void)
{
	m.portb.reg->ddr = 0x00;
	m.portb.reg->port = 0xF0;
	m.portc.reg->ddr = 0x00;
	m.portc.reg->port = 0xF0;
}

//double product (double u, double v){return (u * v);}
/*** File Interrupt ***/
ISR(TIMER1_COMPA_vect)
{
}

/***EOF***/

/******
1º Sequence
2º Scope
3º Pointer and Variable
4º Casting
******/

