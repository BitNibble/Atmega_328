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
	-PD2 pin 4 -> used to toggle between menus
	
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
EXPLODE disp;

double d;
double e;
uint8_t i;
uint8_t j;

char* uartreceive = NULL; // pointing to Rx Buffer raw
char uartrcv[UART_RX_BUFFER_SIZE];
char uartmsg[UART_RX_BUFFER_SIZE];
char result[UART_RX_BUFFER_SIZE];

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
void linear(double* target, double rate);
void exponencial(double* target, double rate);

/*** File Procedure & Function ***/
int main(void)
{	
	//		main preamble
	m = ATMEGA328enable();
	PORTINIT();
	
	//		Inic Global Vars
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
	
	func = FUNCenable();
	lcd = LCD0enable(&DDRB, &PINB, &PORTB, &DDRC, &PINC, &PORTC);
	// HC595 sh = HC595enable(&DDRB,&PORTB,3,1,0); //using arduino
	sh = HC595enable(&DDRD,&PORTD,4,5,7); //4,5,7 using board from ETT with altered pin.
	// UART 103 para 9600, 68 para 14400, 25 para 38400, 8 para 115200 at 16Mhz
	// UART 51 para 9600, 12 para 38400 at 8Mhz
	uart = m.usart.enable(12,8,1,NONE);
	m.tc1.enable(4, 2);
	button = EXPLODEenable();
	disp = EXPLODEenable();
	
	m.tc1.start(1024);
	m.tc1.compareA(0x1AFF);
	
	// Local Vars
	uint8_t input;	
	uint8_t output = 0xFF;
	d = 0; j=1; e=0;
	
	sh.byte(&sh.par,output);
	func.strtovec(LCD.pos.l10, "off");
	func.strtovec(LCD.pos.l11, "off");
	func.strtovec(LCD.pos.l12, "off");
	func.strtovec(LCD.pos.l13, "off");
	
	// Replace with your application code
	uint8_t window, menu;
    for (window = 0, menu = 1; TRUE; ) // Looping
    {
		// 0
		if(!window){ // Loop preamble
			lcd.reboot();
			input = m.byte_mask( m.portc.reg->pin, 0xF0 ) | m.byte_shiftright( m.portb.reg->pin, 4 );
			button.update(&button.par, input);
			disp.update(&disp.par, m.portd.reg->pin);
			// uart capture
			uartreceive = uart.gets(); // UART1
			strcpy(uartrcv, uartreceive);
			if(uart.getch() == '.'){ uart.rxflush(); }
			else{strcpy( uartmsg, uartreceive ); }
			window = 1; continue;
		}
		// 1
		if(window == 1){ // procedures
			switch(menu){ // MENU
				case 1: // Main Program Menu
					if(m.byte_mask(disp.par.HL, m.byte_shiftleft(1, 2))){menu = 2;}
					lcd.gotoxy(0,0);
					lcd.putch(':'); lcd.string_size(uartmsg,16);
					lcd.gotoxy(1,0);
					lcd.string_size(LCDline1, 16);		
					break;
				case 2: // Main Program Menu
					if(m.byte_mask(disp.par.HL, m.byte_shiftleft(1, 2))){menu = 3;}
					lcd.gotoxy(0,0);
					lcd.hspace(4); lcd.string_size("Welcome",7);
					lcd.gotoxy(1,0);
					lcd.string_size(LCDline1, 16);
				break;
				case 3: // Main Program Menu
					if(m.byte_mask(disp.par.HL, m.byte_shiftleft(1, 2))){menu = 4;}
					lcd.gotoxy(0,0);
					lcd.string_size("Testing, 1 2 3",16);
					lcd.gotoxy(1,0);
					lcd.string_size("Testing, 1 2 3",16);
				break;
				case 4: // Main Program Menu
					if(m.byte_mask(disp.par.HL, m.byte_shiftleft(1, 2))){menu = 1;}
					lcd.gotoxy(0,0);
					lcd.string_size("Testing, 1 2 3",16);
					lcd.gotoxy(1,0);
					lcd.string_size(func.ftoa(e,result,2), 16);
				break;
				default:
					break;
			}		
			sh.byte(&sh.par,output);	
			//LED 1
			if(!strcmp(uartrcv, "led 1.") || m.byte_mask(button.par.HL, 1)){
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
			if(!strcmp(uartrcv, "led 2.") || m.byte_mask(button.par.HL, 2)){
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
			if(!strcmp(uartrcv, "led 3.") || m.byte_mask(button.par.HL, 16)){
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
			if(!strcmp(uartrcv, "led 4.") || m.byte_mask(button.par.HL, 32)){
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
			window = 0; continue;
		}
		// 2
		if(window == 2){ // testing	
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
			window = 0; continue;
		}
    }
}

/*** Procedure and Function Definitions ***/
void PORTINIT(void)
{
	m.byte_clear(&m.portb.reg->ddr, 0xFF);
	m.byte_set(&m.portb.reg->port, 0xF0);
	m.byte_clear(&m.portc.reg->ddr, 0xFF);
	m.byte_set(&m.portc.reg->port, 0xF0);
	m.byte_clear(&m.portd.reg->ddr, m.byte_shiftleft(1, 2));
	m.byte_set(&m.portd.reg->port, m.byte_shiftleft(1, 2));	
	//		OLD WAY
	//m.portb.reg->ddr = 0x00;
	//m.portb.reg->port |= 0xF0;
	//m.portc.reg->ddr = 0x00;
	//m.portc.reg->port |= 0xF0;
	//m.portd.reg->ddr &= ~m.byte_shiftleft(1, 2);
	//m.portd.reg->port |= m.byte_shiftleft(1, 2);
}
// make a library for these functions with extra functionalities (these are incomplete)
void linear(double* target, double rate) // *target = rate * t -> t is interrupt timer
{
	double cpy = *target;
	double next;
	next = rate + cpy;
	*target = next;
}
void exponencial(double* target, double rate) // *target = rate ^ t -> t is interrupt timer therefore rate > 0
{
	double cpy = *target;
	double next;
	double diff;
	// filter inputs
	if( rate ){ if(rate < 0) rate = - rate; }else rate = 1;
	if( cpy ) ; else cpy = 1;
	
	next = rate * cpy;
	diff = next - cpy; // to have growth rate (could be bypassed)
	*target = cpy + diff;
}
//double product (double u, double v){return (u * v);}

/*** File Interrupt ***/
// ISR(TIMER1_OVF_vect)
ISR(TIMER1_COMPA_vect)
{
	//interrupt1();
	//linear(&d,-0.2);
	exponencial(&d,-1.2718);
	switch(j){
		case 1:
			if(e > 1065){
				d = 0; j = 2;
			}else
				e = 1066.95 - (1066.95 - d); // d = x ^ t
			break;
		case 2:
			if(e < 1.2720){
				d = 0; j = 1;
			}else
				e = 1066.95 - d;
			break;
		default:
			break;
	}	
	//d=2.0 * 2;
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
4º Casting
******/

