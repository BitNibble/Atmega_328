/*********************************************************************
Hardware: Atmega328.c
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Created:  20/04/2023 14:00:00
*********************************************************************/
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
		PCF8575 (twi) IO Expander
-PC4 SDA pin 27
-PC5 SCL pin 28
		HC05 Bluetooth module (usart0)
-PD0 RXD pin 2
-PD1 TXD pin 3
detail:
(38400,8,1,NONE)
-AT+ROLE0\r\n
-AT+TYPE1\r\n
-AT+BAUD6\r\n
-AT+ADVI3\r\n
-AT+PIN916919\r\n
********************************************************************/
#define F_CPU 16000000UL
/*** File library ***/
#include "atmega328_usart0.h"
#include "function.h"
#include "lcd2p.h"
#include "pcf8575.h"
#include <string.h>

#define TRUE 1
#define ZERO 0

PCF8575 pcf8575;

char* uart_receive = NULL; // pointing to Rx Buffer raw
char uart_oneshot[UART0_RX_BUFFER_SIZE];
char uart_msg[UART0_RX_BUFFER_SIZE];
const char* term = ".";

uint16_t count;

int main(void)
{
func_enable();
lcd02p_enable(&DDRB, &PINB, &PORTB, &DDRC, &PINC, &PORTC);
usart0_enable(38400,8,1,NONE);
pcf8575 = pcf8575_enable(32, 16); // A0 to A3 connected to ground
pcf8575.writehbits( &pcf8575.par, 65535, 1 );
uint8_t menu;
for (menu = 1; TRUE; ) // Looping
{
	lcd02p()->reboot();
	uart_receive = usart0_messageprint( usart0(), uart_oneshot, uart_msg, term);

	switch(menu){ // MENU
		case 1: // Main Program Menu 1
			lcd02p()->gotoxy(0,0);
			lcd02p()->putch(':'); lcd02p()->string_size(uart_msg,19);
			//lcd02p()->putch(':'); lcd02p()->string_size(uart_receive,19);
			lcd02p()->gotoxy(1,15);
			lcd02p()->string_size(func()->ui16toa(count), 5);
			if( !strcmp( uart_receive, "Connected\r\n" ) ){usart0()->rxflush();}
		break;
		case 2: // Main Program Menu 2
		break;
		default:
		break;
	}

	//OUT 1
	if( !strcmp( uart_oneshot, "s00." ) ){
		if( pcf8575.readhbits( &pcf8575.par, (1 << 0) ) ){
			pcf8575.writehbits( &pcf8575.par, (1 << 0), LOW );
			count++;
		}else{
			pcf8575.writehbits( &pcf8575.par, (1 << 0), HIGH);
		}
	}
	//OUT 2
	if(!strcmp( uart_oneshot, "s01." )){
		if( pcf8575.readhbits( &pcf8575.par, (1 << 1) ) ){
			pcf8575.writehbits( &pcf8575.par, (1 << 1), LOW );
		}else{
			pcf8575.writehbits( &pcf8575.par, (1 << 1), HIGH );
		}
	}
	//OUT 3
	if(!strcmp( uart_oneshot, "s02." )){
		if( pcf8575.readhbits( &pcf8575.par, (1 << 2) ) ){
			pcf8575.writehbits( &pcf8575.par, (1 << 2), LOW );
		}else{
			pcf8575.writehbits( &pcf8575.par, (1 << 2), HIGH );
		}
	}
	//OUT 4
	if(!strcmp( uart_oneshot, "s03." )){
		if( pcf8575.readhbits( &pcf8575.par, (1 << 3) ) ){
			pcf8575.writehbits( &pcf8575.par, (1 << 3), LOW );
		}else{
			pcf8575.writehbits( &pcf8575.par, (1 << 3), HIGH );
		}
	}
	//OUT 5
	if(!strcmp( uart_oneshot, "s04." )){
		if( pcf8575.readhbits( &pcf8575.par, (1 << 4) ) ){
			pcf8575.writehbits( &pcf8575.par, (1 << 4), LOW );
		}else{
			pcf8575.writehbits( &pcf8575.par, (1 << 4), HIGH );
		}
	}
	//OUT 6
	if(!strcmp( uart_oneshot, "s05." )){
		if( pcf8575.readhbits( &pcf8575.par, (1 << 5) ) ){
			pcf8575.writehbits( &pcf8575.par, (1 << 5), LOW );
		}else{
			pcf8575.writehbits( &pcf8575.par, (1 << 5), HIGH );
		}
	}
	//OUT 7
	if(!strcmp( uart_oneshot, "s06." )){
		if( pcf8575.readhbits( &pcf8575.par, (1 << 6) ) ){
			pcf8575.writehbits( &pcf8575.par, (1 << 6), LOW );
		}else{
			pcf8575.writehbits( &pcf8575.par, (1 << 6), HIGH );
		}
	}
	//OUT 8
	if(!strcmp( uart_oneshot, "s07." )){
		if( pcf8575.readhbits( &pcf8575.par, (1 << 7) ) ){
			pcf8575.writehbits( &pcf8575.par, (1 << 7), LOW );
		}else{
			pcf8575.writehbits( &pcf8575.par, (1 << 7), HIGH );
		}
	}
	//OUT 9
	if(!strcmp( uart_oneshot, "s08." )){
		if( pcf8575.readhbits( &pcf8575.par, (1 << 8) ) ){
			pcf8575.writehbits( &pcf8575.par, (1 << 8), LOW );
		}else{
			pcf8575.writehbits( &pcf8575.par, (1 << 8), HIGH );
		}
	}
	//OUT 10
	if(!strcmp( uart_oneshot, "s09." )){
		if( pcf8575.readhbits( &pcf8575.par, (1 << 9) ) ){
			pcf8575.writehbits( &pcf8575.par, (1 << 9), LOW );
		}else{
			pcf8575.writehbits( &pcf8575.par, (1 << 9), HIGH );
		}
	}
	//OUT 11
	if(!strcmp( uart_oneshot, "s10." )){
		if( pcf8575.readhbits( &pcf8575.par, (1 << 10) ) ){
			pcf8575.writehbits( &pcf8575.par, (1 << 10), LOW );
		}else{
			pcf8575.writehbits( &pcf8575.par, (1 << 10), HIGH );
		}
	}
	//OUT 12
	if(!strcmp( uart_oneshot, "s11." )){
		if( pcf8575.readhbits( &pcf8575.par, (1 << 11) ) ){
			pcf8575.writehbits( &pcf8575.par, (1 << 11), LOW );
		}else{
			pcf8575.writehbits( &pcf8575.par, (1 << 11), HIGH );
		}
	}
	//OUT 13
	if(!strcmp( uart_oneshot, "s12." )){
		if( pcf8575.readhbits( &pcf8575.par, (1 << 12) ) ){
			pcf8575.writehbits( &pcf8575.par, (1 << 12), LOW );
		}else{
			pcf8575.writehbits( &pcf8575.par, (1 << 12), HIGH );
		}
	}
	//OUT 14
	if(!strcmp( uart_oneshot, "s13." )){
		if( pcf8575.readhbits( &pcf8575.par, (1 << 13) ) ){
			pcf8575.writehbits( &pcf8575.par, (1 << 13), LOW );
		}else{
			pcf8575.writehbits( &pcf8575.par, (1 << 13), HIGH );
		}
	}
	//OUT 15
	if(!strcmp( uart_oneshot, "s14." )){
		if( pcf8575.readhbits( &pcf8575.par, (1 << 14) ) ){
			pcf8575.writehbits( &pcf8575.par, (1 << 14), LOW );
		}else{
			pcf8575.writehbits( &pcf8575.par, (1 << 14), HIGH );
		}
	}
	//OUT 16
	if(!strcmp( uart_oneshot, "s15." )){
		if( pcf8575.readhbits( &pcf8575.par, (1 << 15) ) ){
			pcf8575.writehbits( &pcf8575.par, (1 << 15), LOW );
		}else{
			pcf8575.writehbits( &pcf8575.par, (1 << 15), HIGH );
		}
	}
	//
	if(!strcmp( uart_oneshot, "all off." )){
		pcf8575.writehbits( &pcf8575.par, 65535, HIGH );
	}
	//
	if(!strcmp( uart_oneshot, "all on." )){
		pcf8575.writehbits( &pcf8575.par, 65535, LOW );
	}

	//STATUS FEEDBACK
	if(!strcmp(uart_oneshot, "status.")){
		usart0()->puts( func()->print_binary( 16, ~pcf8575.readhbits( &pcf8575.par, 0xFFFF ) ) );
		usart0()->putch('\n');
	}

	lcd02p()->gotoxy(3,0);
	lcd02p()->string_size( "->", 3);
	lcd02p()->gotoxy(3,3);
	lcd02p()->string_size(func()->print_binary( 16, ~pcf8575.readhbits( &pcf8575.par, 0xFFFF ) ), 16);

	//_delay_ms(500);
}
} /*** MAIN ***/

/*** File Interrupt ***/

/******
1º Sequence
2º Scope
3º Pointer and Variable
4º Casting
******/

/*** EOF ***/

