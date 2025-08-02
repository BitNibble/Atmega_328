/*********************************************************************
Hardware: Atmega328.c
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Created:  27/01/2024 14:00:00
 ********************************************************************/
/****** Comment:
	LCD
-PB0 pin 14 cmd RS
-PB1 pin 15 cmd RW
-PB2 pin 16 cmd E
-PB3 pin 17 cmd Reboot
-PC0 pin 23 data D4
-PC1 pin 24 data D5
-PC2 pin 25 data D6
-PC3 pin 26 data D7
	USART0
-PD0 RXD pin 2
-PD1 TXD pin 3
********************************************************************/
/*** File library ***/
#include "atmega328_usart0.h"
#include "function.h"
#include "lcd2p.h"
//#include<util/delay.h>

#define TRUE 1
#define FALSE 0

char* uart_receive = NULL; // pointing to Rx Buffer raw
char uart_oneshot[UART0_RX_BUFFER_SIZE];
char uart_msg[UART0_RX_BUFFER_SIZE];

uint16_t count;

int main(void)
{
func_enable();
lcd02p_enable(&DDRB, &PINB, &PORTB, &DDRC, &PINC, &PORTC);
usart0_enable(38400,8,1,0);

uint8_t menu;
for (menu = 1; TRUE; ) // Looping
{
	lcd02p()->reboot();
	uart_receive = usart0_messageprint( usart0(), uart_oneshot, uart_msg, ".");
	
	switch(menu){ // MENU
		case 1: // Main Program Menu 1
			lcd02p()->gotoxy(0,0);
			lcd02p()->putch(':'); lcd02p()->string_size(uart_msg,19);
			lcd02p()->gotoxy(1,15);
			lcd02p()->string_size(func()->ui16toa(count), 5);
		break;
		case 2: // Main Program Menu 2
				
		break;
		default:
		break;
	}
	
}}

/***EOF***/

