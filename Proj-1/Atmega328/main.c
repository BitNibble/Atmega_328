/***********************************************************
	Testing Uart Threw FTDI
Author : Sergio Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: Atmega 328
Software: Microchip Studio (Version: 7.0.2542)
Date: 15/04/2023 14:00:00
Comment:
		LCD
	-PB0 pin 14 cmd
	-PB1 pin 15 cmd
	-PB2 pin 16 cmd
	-PB3 pin 17 cmd
	-PC0 pin 23 data
	-PC1 pin 24 data
	-PC2 pin 25 data
	-PC3 pin 26 data
		FTDI (MAX 232 bypassed with jumpers)
	-PD0 pin 2 Tx
	-PD1 pin 3 Rx
	
 **********************************************************/
#define F_CPU 16000000UL

/***File Library***/
#include <stdlib.h>
#include <string.h>
#include <util/delay.h>
#include <inttypes.h>
#include <math.h>
#include "atmega328mapping.h"
#include "function.h"
#include "lcd2p.h"

/***File Constant and Macros***/
#define TRUE 1
#define ZERO 0

/***File Variables***/

/***File Header***/
void PORTINIT(void);

/***Procedure & Function****/
int main(void)
{
	/***Preamble***/
	/***Local Variable***/
	//FUNC func = FUNCenable();
	LCD0 lcd = LCD0enable(&DDRB,&PINB,&PORTB, &DDRC,&PINC,&PORTC);
	//HC595 shift = HC595enable(&DDRB,&PORTB,3,1,0); //REMEMBER!!!
	UART uart = UARTenable(103,8,1,NONE);
	/***Local Variable***/
	//char* uartreceive;
    /* Replace with your application code */
    while (TRUE)
    {
		lcd.gotoxy(0,0);
		lcd.string_size("Welcome",7);
		if(!(PIND & 0x04))
		{
			uart.putch('>');
			uart.puts("Welcome to uart com threw ftdi ! \r \n");
			uart.puts("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAA ! \r \n");
		}
    }
}
void PORTINIT(void)
{
	DDRD&=~(0x04);
	PORTD|=0x04;
	DDRB|=0x02;
	PORTB=0X02;
}

/***File Interrupt***/

/***EOF***/


/******
1º Sequence
2º Scope
3º Pointer and Variable
******/



