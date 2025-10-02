/*********************************************************************
Hardware: Atmega328.c
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Created:  20/04/2023 14:00:00
Update:   22/01/2024
*********************************************************************/
/****** Comment:
		74HC595
	-PD4 pin 6 - Serial Data
	-PD5 pin 11 - Shift Bit
	-PD7 pin 12 - Output
	Shift Register Connected to relay board
		LCD
	-PB0 pin 14 cmd RS
	-PB1 pin 15 cmd RW
	-PB2 pin 16 cmd E
	-PB3 pin 17 cmd Reboot
	-PC0 pin 23 data D4
	-PC1 pin 24 data D5
	-PC2 pin 25 data D6
	-PC3 pin 26 data D7
		Bluetooth HC-05 (MAX 232 bypassed with jumpers) 
		12 para 38400 at 8Mhz, AT+BAUD6\r\n, AT+TYPE1\r\n,
		AT+ROLE0\r\n, AT+PIN916919\r\n. (38400,8,1,NONE).
	-PD0 pin 2 Rx
	-PD1 pin 3 Tx
		Buttons
	-PB4 pin 18
	-PB5 pin 19
	-PC4 pin 27
	-PC5 pin 28
	-PD2 pin 4 -> used to toggle between menus
	-PD3 pin 5 -> used to send command to HC05
	
 ********************************************************************/
#define F_CPU 8000000UL
/******/
#include "atmega328timer1.h"
#include "atmega328_usart0.h"
#include "function.h"
#include "lcd2p.h"
#include "74hc595.h"
#include "explode.h"
#include "bt05atcommands.h"
#include <stdlib.h>
#include <string.h>
//#include <stdarg.h>

/*** File Constant and Macros ***/
#define TRUE 1
#define ZERO 0

/*** File Variable ***/
HC595 sh;
EXPLODE button;
EXPLODE disp;

double d;
double e;
uint8_t i;
uint8_t j;
uint8_t tmp;

char* uartreceive = NULL; // pointing to Rx Buffer raw
char uartrcv[UART0_RX_BUFFER_SIZE] = {0};
char uartmsg[UART0_RX_BUFFER_SIZE] = {0};

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
char test[18];
/*** File Header ***/
void PORTINIT(void);
void exponencial(double* target, double rate);

/*** File Procedure & Function ***/
int main(void)
{	
//		main preamble
PORTINIT();

//		Inic Vars
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
d = 0; j=1; e=0;

func_enable();
lcd02p_enable(&DDRB, &PINB, &PORTB, &DDRC, &PINC, &PORTC);

// HC595 sh = HC595enable(&DDRB,&PORTB,3,1,0); //using arduino
sh = hc595_enable(&DDRD,&PORTD,4,5,7); //4,5,7 using board from ETT with altered pin.

// UART 103 para 9600, 68 para 14400, 25 para 38400, 8 para 115200 at 16Mhz
// UART 51 para 9600, 12 para 38400 at 8Mhz
usart0_enable(38400,8,1,NONE);

button = explode_enable();
disp = explode_enable();

tc1_enable(4, 2);
tc1()->start(1024);
tc1()->compareA(0x1AFF);

// Local Vars
uint8_t input;	
uint8_t output = 0xFF;

sh.byte(&sh.par,output);
func()->strtovec(LCD.pos.l10, "off");
func()->strtovec(LCD.pos.l11, "off");
func()->strtovec(LCD.pos.l12, "off");
func()->strtovec(LCD.pos.l13, "off");

// Replace with your application code
uint8_t window, menu;
for (window = 0, menu = 1; TRUE; )
{
	// 0
	if(!window){ // Loop preamble
		lcd02p()->reboot();
		
		input = ( gpioc_reg()->pin.var & 0xF0 ) | get_reg_block( gpiob_reg()->pin.var, 4, 4 );
		button.update(&button.par, input);
		disp.update(&disp.par, gpiod_reg()->pin.var);
		
		// uart capture
		uartreceive = usart0_messageprint( usart0(), uartrcv, uartmsg, "\r\n");
		
		func()->rmcrnl(uartmsg);
		
		window = 1; continue;
	}
	// 1
	if(window == 1){ // procedures
		switch(menu){ // MENU
			case 1: // Main Program Menu 1
				if((disp.par.HL & (1 << 2))){lcd02p()->clear();menu = 2;}
				else{
					lcd02p()->gotoxy(0,0);
					lcd02p()->putch(':'); 
					lcd02p()->string_size(uartmsg,15);
					lcd02p()->gotoxy(1,0);
					lcd02p()->string_size(LCDline1, 16);
				}
				break;
			case 2: // Main Program Menu 2
				if((disp.par.HL & (1 << 2))){lcd02p()->clear();menu = 3;}
				else{
					lcd02p()->gotoxy(0,0);
					lcd02p()->hspace(4); lcd02p()->string_size("Welcome",7);
					lcd02p()->gotoxy(1,0);
					lcd02p()->string_size(LCDline1, 16);
				}
			break;
			case 3: // Main Program Menu 3
				if((disp.par.HL & (1 << 2))){lcd02p()->clear();menu = 4;}
				else{
					lcd02p()->gotoxy(0,0);
					lcd02p()->hspace(4); lcd02p()->string_size("bt05 ->",7);
					if((disp.par.HL & (1 << 3)))
					{
						usart0()->puts(bt05at_cmd(2));
						//usart0()->puts(bt05at_cmd(27));
						//usart0()->puts(bt05at_cmd(29));
						//usart0()->puts(bt05at_cmd(20));
						usart0()->rxflush();
					}
				}
			break;
			case 4: // Main Program Menu 4
				if((disp.par.HL & (1 << 2))){menu = 1;}
				else{
					lcd02p()->gotoxy(0,0);
					lcd02p()->string_size("Testing, 1 2 3",16);
					lcd02p()->gotoxy(1,0);
					lcd02p()->string_size(func()->ftoa(e, 2), 16);
				}
			break;
			default:
				break;
		}
		sh.byte(&sh.par,output);	
		//LED 1
		if(!strcmp(uartrcv, "s00\r\n") || (button.par.HL & 1)){
			if(output & 1){
				output&=~1;
				func()->strtovec(LCD.pos.l10, "on ");
			}else{
				output|=1;
				func()->strtovec(LCD.pos.l10, "off");
			}
		}
		if(!strcmp(uartrcv, "s00 off\r\n")){
				output|=1;
				func()->strtovec(LCD.pos.l10, "off");
		}
		//LED 2
		if(!strcmp(uartrcv, "s01\r\n") || (button.par.HL & 2)){
			if(output & 2){
				output&=~2;
				func()->strtovec(LCD.pos.l11, "on ");
			}else{
				output|=2;
				func()->strtovec(LCD.pos.l11, "off");
			}
		}
		if(!strcmp(uartrcv, "s01 off\r\n")){
			output|=2;
			func()->strtovec(LCD.pos.l11, "off");
		}		
		//LED 3
		if(!strcmp(uartrcv, "s02\r\n") || (button.par.HL & 16)){
			if(output & 4){
				output&=~4;
				func()->strtovec(LCD.pos.l12, "on ");
			}else{
				output|=4;
				func()->strtovec(LCD.pos.l12, "off");
			}
		}
		if(!strcmp(uartrcv, "s02 off\r\n")){
			output|=4;
			func()->strtovec(LCD.pos.l12, "off");
		}
		//LED 4
		if(!strcmp(uartrcv, "s03\r\n") || (button.par.HL & 32)){
			if(output & 8){
				output&=~8;
				func()->strtovec(LCD.pos.l13, "on ");
			}else{
				output|=8;
				func()->strtovec(LCD.pos.l13, "off");
			}
		}
		if(!strcmp(uartrcv, "s03 off\r\n")){
			output|=8;
			func()->strtovec(LCD.pos.l13, "off");
		}
		//ALL OFF
		if(!strcmp(uartrcv, "all off\r\n")){
			output = 0xFF;
			func()->strtovec(LCD.pos.l10, "off");
			func()->strtovec(LCD.pos.l11, "off");
			func()->strtovec(LCD.pos.l12, "off");
			func()->strtovec(LCD.pos.l13, "off");
		}
		//STATUS FEEDBACK
		if(!strcmp(uartrcv, "status\r\n")){
			usart0()->puts(LCDline1);
		}
		window = 0; continue;
	}
}}

/*** Procedure and Function Definitions ***/
void PORTINIT(void)
{
	write_reg_block(&gpiob_reg()->ddr.var,2,4,0);
	write_reg_block(&gpiob_reg()->port.var,2,4,3);
	write_reg_block(&gpioc_reg()->ddr.var,2,4,0);
	write_reg_block(&gpioc_reg()->port.var,2,4,3);
	write_reg_block(&gpiod_reg()->ddr.var,2,2,0);
	write_reg_block(&gpiod_reg()->port.var,2,2,3);
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

/*** File Interrupt ***/
// ISR(TIMER1_OVF_vect)
ISR(TIMER1_COMPA_vect)
{
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
}

/***EOF***/

/******
1º Sequence
2º Scope
3º Pointer and Variable
4º Casting
******/

