/*********************************************************************
Hardware: Atmega328.c
Author: Sergio Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Created: 20/04/2023 14:00:00
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
#define F_CPU 8000000UL

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
EXPLODE button;

uint16_t d;
uint8_t i;
// uint8_t j;

char* uartreceive = NULL; // pointing to Rx Buffer raw
char uartrcv[UART_RX_BUFFER_SIZE];
char uartmsg[UART_RX_BUFFER_SIZE];

// Virtual LCD
struct LCDposition {
	char* l00;
	char* l01;
	char* l02;
	char* l03;
	char* l10;
	char* l11;
	char* l12;
	char* l13;
};
struct LCDvirtual {
	struct LCDposition pos;
}LCD;
char LCDline0[18];
char LCDline1[18];

/*** File Header ***/
void PORTINIT(void);
void interrupt1(void){d++;}

/*** File Procedure & Function ***/
int main(void)
{	
	PORTINIT();
	
	//timer0_ovf = interrupt1;
	
	LCD.pos.l00 = LCDline0;
	LCD.pos.l10 = LCDline1;	
	LCD.pos.l01 = LCDline0 + 4;
	LCD.pos.l11 = LCDline1 + 4;
	LCD.pos.l02 = LCDline0 + 8;
	LCD.pos.l12 = LCDline1 + 8;
	LCD.pos.l03 = LCDline0 + 12;
	LCD.pos.l13 = LCDline1 + 12;
	for(i=0; i<18; LCDline0[i]=' ', i++);
	for(i=0; i<18; LCDline1[i]=' ', i++);
	LCDline0[16] = '\n';
	LCDline1[16] = '\n';
	LCDline0[17] = '\0';
	LCDline1[17] = '\0';
	
	m = ATMEGA328enable();
	func = FUNCenable();
	lcd = LCD0enable(&DDRB, &PINB, &PORTB, &DDRC, &PINC, &PORTC);
	// HC595 sh = HC595enable(&DDRB,&PORTB,3,1,0); //using arduino
	sh = HC595enable(&DDRD,&PORTD,4,5,7); //4,5,7 using board from ETT with altered pin.
	// UART 103 para 9600, 68 para 14400, 25 para 38400, 8 para 115200 at 16Mhz
	// UART 51 para 9600, 12 para 38400 at 8Mhz
	uart = m.usart.enable(12,8,1,NONE);
	tc0 = m.tc0.enable(1, 1);
	button = EXPLODEenable();
	
	tc0.start(~0);
	
	uint8_t input;	
	uint8_t output = 0xFF;
	d = 0;
	
	sh.byte(output);
	func.strtovec(LCD.pos.l10, "off");
	func.strtovec(LCD.pos.l11, "off");
	func.strtovec(LCD.pos.l12, "off");
	func.strtovec(LCD.pos.l13, "off");
	
	// Replace with your application code
    while (TRUE)
    {
		// preamble
		// lcd reboot
		lcd.reboot();
		
		input = ( PINC & 0xF0 ) | ( PINB >> 4 );
		button.update(&button, input);
		
		// uart capture
		uartreceive = uart.gets(); // UART1
		strcpy(uartrcv, uartreceive);
		
		if(uart.getch() == '.'){ uart.rxflush(); }
		else{strcpy( uartmsg, uartreceive ); }
		
		// procedures
		sh.byte(output);
		
		lcd.gotoxy(0,0);
		lcd.putch(':'); lcd.string_size(uartmsg,16); //lcd.hspace(2); lcd.string_size(func.ui16toa(d), 6);
		
		// check character table of LCD 
		//for(i=0;i<16;lcd.putch(i),i++);
		//for(i=16;i<32;lcd.putch(i),i++);
		//for(i=32;i<64;lcd.putch(i),i++);
		//for(i=64;i<80;lcd.putch(i),i++);
		//for(i=80;i<96;lcd.putch(i),i++);
		//for(i=96;i<112;lcd.putch(i),i++);
		//for(i=112;i<128;lcd.putch(i),i++);
		//for(i=128;i<144;lcd.putch(i),i++);
		//for(i=144;i<160;lcd.putch(i),i++);
		//for(i=160;i<176;lcd.putch(i),i++);
		//for(i=176;i<192;lcd.putch(i),i++);
		//for(i=192;i<208;lcd.putch(i),i++);
		//for(i=208;i<224;lcd.putch(i),i++);
		//for(i=224;i<240;lcd.putch(i),i++);
		//for(i=240;i<255;lcd.putch(i),i++); // 255 is a BLACK P.
		
		lcd.gotoxy(1,0);
		lcd.string_size(LCDline1, 16);
		
		
		//LED 1
		if(!strcmp(uartrcv, "led 1.") || (button.HL & 1)){
			if(output & 1){
				output&=~1;
				func.strtovec(LCD.pos.l10, "on ");
			}else{
				output|=1;
				func.strtovec(LCD.pos.l10, "off");
			}
		}
		if(!strcmp(uartrcv, "led 1 off.")){
				output|=1;
				func.strtovec(LCD.pos.l10, "off");
		}
		
		//LED 2
		if(!strcmp(uartrcv, "led 2.") || (button.HL & 2)){
			if(output & 2){
				output&=~2;
				func.strtovec(LCD.pos.l11, "on ");
			}else{
				output|=2;
				func.strtovec(LCD.pos.l11, "off");
			}
		}
		if(!strcmp(uartrcv, "led 2 off.")){
			output|=2;
			func.strtovec(LCD.pos.l11, "off");
		}
		
		//LED 3
		if(!strcmp(uartrcv, "led 3.") || (button.HL & 16)){
			if(output & 4){
				output&=~4;
				func.strtovec(LCD.pos.l12, "on ");
			}else{
				output|=4;
				func.strtovec(LCD.pos.l12, "off");
			}
		}
		if(!strcmp(uartrcv, "led 3 off.")){
			output|=4;
			func.strtovec(LCD.pos.l12, "off");
		}
		
		//LED 4
		if(!strcmp(uartrcv, "led 4.") || (button.HL & 32)){
			if(output & 8){
				output&=~8;
				func.strtovec(LCD.pos.l13, "on ");
			}else{
				output|=8;
				func.strtovec(LCD.pos.l13, "off");
			}
		}
		if(!strcmp(uartrcv, "led 4 off.")){
			output|=8;
			func.strtovec(LCD.pos.l13, "off");
		}
		
		//ALL OFF
		if(!strcmp(uartrcv, "all off.")){
			output = 0xFF;
			func.strtovec(LCD.pos.l10, "off");
			func.strtovec(LCD.pos.l11, "off");
			func.strtovec(LCD.pos.l12, "off");
			func.strtovec(LCD.pos.l13, "off");
		}
		
		//STATUS FEEDBACK
		if(!strcmp(uartrcv, "status.")){
			uart.puts(LCDline1);
		}
		
		
    }
}

void PORTINIT(void)
{
	m.portb.reg->ddr = 0x00;
	m.portb.reg->port = 0xF0;
	m.portc.reg->ddr = 0x00;
	m.portc.reg->port = 0xF0;
}

/*** File Interrupt ***/
ISR(TIMER0_OVF_vect)
{
	interrupt1();
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

