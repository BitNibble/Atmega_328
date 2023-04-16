/*************************************************************************
	LCD
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: all
Date: 12112022
Comment:
	Tested Atemga128 16Mhz and Atmega328 8Mhz                    
************************************************************************/
/***File Library***/
#include "lcd.h"
#include <util/delay.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <stdarg.h>
//#include <math.h>

/***File Constant & Macro***/
// CMD RS
#define INST 0
#define DATA 1
// ticks depends on CPU frequency this case 16Mhz
#define LCD_N_TICKS 0
#define BIT_N_TICKS 0

/***File Variable***/
volatile uint8_t *lcd0_DDR;
volatile uint8_t *lcd0_PIN;
volatile uint8_t *lcd0_PORT;
uint8_t lcd0_detect;
volatile uint8_t *lcd1_DDR;
volatile uint8_t *lcd1_PIN;
volatile uint8_t *lcd1_PORT;
uint8_t lcd1_detect;

/***File Header***/
void LCD0_inic(void);
void LCD0_write(char c, unsigned short D_I);
char LCD0_read(unsigned short D_I);
void LCD0_BF(void);
void LCD0_putch(char c);
char LCD0_getch(void);
void LCD0_string(const char* s); // RAW
void LCD0_string_size(const char* s, uint8_t size); // RAW
void LCD0_hspace(uint8_t n);
void LCD0_clear(void);
void LCD0_gotoxy(unsigned int y, unsigned int x);
void LCD0_strobe(uint16_t num);
void LCD0_reboot(void);
void LCD1_inic(void);
void LCD1_write(char c, unsigned short D_I);
char LCD1_read(unsigned short D_I);
void LCD1_BF(void);
void LCD1_putch(char c);
char LCD1_getch(void);
void LCD1_string(const char* s); // RAW
void LCD1_string_size(const char* s, uint8_t size); // RAW
void LCD1_hspace(uint8_t n);
void LCD1_clear(void);
void LCD1_gotoxy(unsigned int y, unsigned int x);
void LCD1_strobe(uint16_t num);
void LCD1_reboot(void);
void LCD_ticks(uint16_t num);

/***Procedure & Function***/
LCD0 LCD0enable(volatile uint8_t *ddr, volatile uint8_t *pin, volatile uint8_t *port)
{
	// LOCAL VARIABLES
	// ALLOCAÇÂO MEMORIA PARA Estrutura
	LCD0 lcd0;
	// import parameters
	lcd0_DDR = ddr;
	lcd0_PIN = pin;
	lcd0_PORT = port;
	// initialize variables
	*lcd0_DDR = 0x00;
	*lcd0_PORT = 0xFF;
	lcd0_detect = *lcd0_PIN & (1 << NC);
	// Direccionar apontadores para PROTOTIPOS
	lcd0.write = LCD0_write;
	lcd0.read = LCD0_read;
	lcd0.BF = LCD0_BF;
	lcd0.putch = LCD0_putch;
	lcd0.getch = LCD0_getch;
	lcd0.string = LCD0_string; // RAW
	lcd0.string_size = LCD0_string_size; // RAW
	lcd0.hspace = LCD0_hspace;
	lcd0.clear = LCD0_clear;
	lcd0.gotoxy = LCD0_gotoxy;
	lcd0.reboot = LCD0_reboot;
	// LCD INIC
	LCD0_inic();
	//
	return lcd0;
}
void LCD0_inic(void)
{
	// LCD INIC
	*lcd0_DDR = (1 << RS) | (1 << RW) | (1 << EN) | (0 << NC);
	*lcd0_PORT = (1 << NC);
	// INICIALIZACAO LCD datasheet/
	_delay_ms(40); // using clock at 16Mhz
	LCD0_write(0x38, INST); // function set
	_delay_us(39);
	LCD0_write(0x38, INST); // function set
	_delay_us(39);
	LCD0_write(0x38, INST); // function set
	_delay_us(39);
	LCD0_write(0x28, INST); // function set 2B
	_delay_us(37);
	LCD0_write(0x28, INST); // function set 2B
	_delay_us(37);
	/**************************************/
	// for(repeat = 2 ; repeat ; repeat--){
	// repeat twice in 4 bit length
	LCD0_write(0x28, INST); // function set 2B
	LCD0_BF();
	LCD0_write(0x28, INST); // function set 2B
	LCD0_BF();

	LCD0_write(0x0C, INST);// display on/off control
	LCD0_BF();
	LCD0_write(0x0C, INST);// display on/off control
	LCD0_BF();

	LCD0_write(0x01, INST);// clear display
	LCD0_BF();
	LCD0_write(0x01, INST);// clear display
	LCD0_BF();

	LCD0_write(0x06, INST);// entry mode set (crazy settings)
	LCD0_BF();
	LCD0_write(0x06, INST);// entry mode set (crazy settings)
	LCD0_BF();
	//}
	// INICIALIZATION END
	// LCD0_write(0x1F, INST);// cursor or display shift
	// _delay_us(39);
	// LCD0_write(0x03, INST);// return home
	// _delay_ms(1.53);
	LCD0_gotoxy(0,0);
}
void LCD0_write(char c, unsigned short D_I)
{
	*lcd0_PORT &= ~(1 << RW); // lcd as input
	*lcd0_DDR |= (1 << DB4) | (1 << DB5) | (1 << DB6) | (1 << DB7); // mcu as output
	
	if(D_I) *lcd0_PORT |= (1 << RS); else *lcd0_PORT &= ~(1 << RS);
	LCD0_strobe(LCD_N_TICKS); LCD_ticks(BIT_N_TICKS);
	
	if(c & 0x80) *lcd0_PORT |= 1 << DB7; else *lcd0_PORT &= ~(1 << DB7); LCD_ticks(BIT_N_TICKS);
	if(c & 0x40) *lcd0_PORT |= 1 << DB6; else *lcd0_PORT &= ~(1 << DB6); LCD_ticks(BIT_N_TICKS);
	if(c & 0x20) *lcd0_PORT |= 1 << DB5; else *lcd0_PORT &= ~(1 << DB5); LCD_ticks(BIT_N_TICKS);
	if(c & 0x10) *lcd0_PORT |= 1 << DB4; else *lcd0_PORT &= ~(1 << DB4); LCD_ticks(BIT_N_TICKS);
	
	if(D_I) *lcd0_PORT |= (1 << RS); else *lcd0_PORT &= ~(1 << RS);
	LCD0_strobe(LCD_N_TICKS); LCD_ticks(BIT_N_TICKS);
	
	if(c & 0x08) *lcd0_PORT |= 1 << DB7; else *lcd0_PORT &= ~(1 << DB7); LCD_ticks(BIT_N_TICKS);
	if(c & 0x04) *lcd0_PORT |= 1 << DB6; else *lcd0_PORT &= ~(1 << DB6); LCD_ticks(BIT_N_TICKS);
	if(c & 0x02) *lcd0_PORT |= 1 << DB5; else *lcd0_PORT &= ~(1 << DB5); LCD_ticks(BIT_N_TICKS);
	if(c & 0x01) *lcd0_PORT |= 1 << DB4; else *lcd0_PORT &= ~(1 << DB4); LCD_ticks(BIT_N_TICKS);
	
	*lcd0_PORT &= ~(1 << EN); LCD_ticks(LCD_N_TICKS);
}
char LCD0_read(unsigned short D_I)
{
	char c = 0x00;
	*lcd0_DDR &= ~((1 << DB4) | (1 << DB5) | (1 << DB6) | (1 << DB7)); // mcu as input
	*lcd0_PORT |= (1 << DB4) | (1 << DB5) | (1 << DB6) | (1 << DB7); // pull up resistors
	*lcd0_PORT |= (1 << RW); // lcd as output
	
	if(D_I) *lcd0_PORT |= (1 << RS); else *lcd0_PORT &= ~(1 << RS);
	LCD0_strobe(LCD_N_TICKS); LCD_ticks(BIT_N_TICKS);
	
	if(*lcd0_PIN & (1 << DB7)) c |= 1 << 7; else c &= ~(1 << 7); LCD_ticks(BIT_N_TICKS);
	if(*lcd0_PIN & (1 << DB6)) c |= 1 << 6; else c &= ~(1 << 6); LCD_ticks(BIT_N_TICKS);
	if(*lcd0_PIN & (1 << DB5)) c |= 1 << 5; else c &= ~(1 << 5); LCD_ticks(BIT_N_TICKS);
	if(*lcd0_PIN & (1 << DB4)) c |= 1 << 4; else c &= ~(1 << 4); LCD_ticks(BIT_N_TICKS);
	
	if(D_I) *lcd0_PORT |= (1 << RS); else *lcd0_PORT &= ~(1 << RS);
	LCD0_strobe(LCD_N_TICKS); LCD_ticks(BIT_N_TICKS);
	
	if(*lcd0_PIN & (1 << DB7)) c |= 1 << 3; else c &= ~(1 << 3); LCD_ticks(BIT_N_TICKS);
	if(*lcd0_PIN & (1 << DB6)) c |= 1 << 2; else c &= ~(1 << 2); LCD_ticks(BIT_N_TICKS);
	if(*lcd0_PIN & (1 << DB5)) c |= 1 << 1; else c &= ~(1 << 1); LCD_ticks(BIT_N_TICKS);
	if(*lcd0_PIN & (1 << DB4)) c |= 1 << 0; else c &= ~(1 << 0); LCD_ticks(BIT_N_TICKS);
	
	*lcd0_PORT &= ~(1 << EN); LCD_ticks(LCD_N_TICKS);
	
	return c;
}
void LCD0_BF(void)
// it has to read at minimum one equal and exit immediately if not equal, weird property.
{
	uint8_t i;
	char inst = 0x80;
	for(i=0; 0x80 & inst; i++){
		inst = LCD0_read(INST);
		if(i > 1)
			break;
	}
}
char LCD0_getch(void)
{
	char c;
	c = LCD0_read(DATA);
	LCD0_BF();
	return c;
}
void LCD0_putch(char c)
{
	LCD0_write(c, DATA);
	LCD0_BF();
}
void LCD0_string(const char* s)
{
	char tmp;
	while(*s){
		tmp = *(s++);
		LCD0_putch(tmp);
	}
}
void LCD0_string_size(const char* s, uint8_t size)
{
	char tmp;
	uint8_t pos = 0;
	while(*s){
		tmp=*(s++);
		pos++;
		if(pos > size) // 1 TO SIZE+1
			break;
		LCD0_putch(tmp);
	}
	while(pos<size){ // TO SIZE
		LCD0_putch(' ');
		pos++;
	}
}
void LCD0_hspace(uint8_t n)
{
	for(; n; n--){
		LCD0_putch(' ');
	}
}
void LCD0_clear(void)
{
	LCD0_write(0x01, INST);
    _delay_ms(1.53);
}
void LCD0_gotoxy(unsigned int y, unsigned int x)
{
	switch(y){
		case 0:
			LCD0_write((0x80 + x), INST);
			LCD0_BF();
		break;
		case 1:
			LCD0_write((0xC0 + x), INST);
			LCD0_BF();
		break;
		case 2:
			LCD0_write((0x94 + x), INST); // 0x94
			LCD0_BF();
		break;
		case 3:
			LCD0_write((0xD4 + x), INST); // 0xD4
			LCD0_BF();
		break;
		default:
		break;
	}
}
void LCD0_strobe(uint16_t num)
{
	*lcd0_PORT &= ~(1 << EN);
	LCD_ticks(num);
	*lcd0_PORT |= (1 << EN);
}
void LCD0_reboot(void)
{
	// low high detect pin NC
	uint8_t i;
	uint8_t tmp;
	tmp = *lcd0_PIN & (1 << NC);
	i = tmp ^ lcd0_detect;
	i &= tmp;
	if(i)
		LCD0_inic();
	lcd0_detect = tmp;
}
// LCD 1
LCD1 LCD1enable(volatile uint8_t *ddr, volatile uint8_t *pin, volatile uint8_t *port)
{
	// LOCAL VARIABLES
	// ALLOCAÇÂO MEMORIA PARA Estrutura
	LCD1 lcd1;
	// import parameters
	lcd1_DDR = ddr;
	lcd1_PIN = pin;
	lcd1_PORT = port;
	// initialize variables
	*lcd1_DDR = 0x00;
	*lcd1_PORT = 0xFF;
	lcd1_detect = *lcd1_PIN & (1 << NC);
	// Direccionar apontadores para PROTOTIPOS
	lcd1.write = LCD1_write;
	lcd1.read = LCD1_read;
	lcd1.BF = LCD1_BF;
	lcd1.putch = LCD1_putch;
	lcd1.getch = LCD1_getch;
	lcd1.string = LCD1_string; // RAW
	lcd1.string_size = LCD1_string_size; // RAW
	lcd1.hspace = LCD1_hspace;
	lcd1.clear = LCD1_clear;
	lcd1.gotoxy = LCD1_gotoxy;
	lcd1.reboot = LCD1_reboot;
	// LCD INIC
	LCD1_inic();
	//
	return lcd1;
}
void LCD1_inic(void)
{
	// LCD INIC
	*lcd1_DDR = (1 << RS) | (1 << RW) | (1 << EN) | (0 << NC);
	*lcd1_PORT = (1 << NC);
	// INICIALIZACAO LCD datasheet
	_delay_ms(40); // using clock at 16Mhz
	LCD1_write(0x38, INST); // function set
	_delay_us(39);
	LCD1_write(0x38, INST); // function set
	_delay_us(39);
	LCD1_write(0x38, INST); // function set
	_delay_us(39);
	LCD1_write(0x28, INST); // function set 2B
	_delay_us(37);
	LCD1_write(0x28, INST); // function set 2B
	_delay_us(37);
	// for(repeat = 2 ; repeat ; repeat--){
	// repeat twice in 4 bit length
	LCD1_write(0x28, INST); // function set 2B
	LCD1_BF();
	LCD1_write(0x28, INST); // function set 2B
	LCD1_BF();

	LCD1_write(0x0C, INST); // display on/off control
	LCD1_BF();
	LCD1_write(0x0C, INST); // display on/off control
	LCD1_BF();

	LCD1_write(0x01, INST); // clear display
	LCD1_BF();
	LCD1_write(0x01, INST); // clear display
	LCD1_BF();

	LCD1_write(0x06, INST); // entry mode set (crazy settings)
	LCD1_BF();
	LCD1_write(0x06, INST); // entry mode set (crazy settings)
	LCD1_BF();
	//}
	// INICIALIZATION END
	// LCD1_write(0x1F, INST); // cursor or display shift
	// _delay_us(39);
	// LCD1_write(0x03, INST); // return home
	// _delay_ms(1.53);
	LCD1_gotoxy(0,0);
}
void LCD1_write(char c, unsigned short D_I)
{
	*lcd1_PORT &= ~(1 << RW); // lcd as input
	*lcd1_DDR |= (1 << DB4) | (1 << DB5) | (1 << DB6) | (1 << DB7); // mcu as output
	
	if(D_I) *lcd1_PORT |= (1 << RS); else *lcd1_PORT &= ~(1 << D_I);
	LCD1_strobe(LCD_N_TICKS); LCD_ticks(BIT_N_TICKS);
	
	if(c & 0x80) *lcd1_PORT |= 1 << DB7; else *lcd1_PORT &= ~(1 << DB7); LCD_ticks(BIT_N_TICKS);
	if(c & 0x40) *lcd1_PORT |= 1 << DB6; else *lcd1_PORT &= ~(1 << DB6); LCD_ticks(BIT_N_TICKS);
	if(c & 0x20) *lcd1_PORT |= 1 << DB5; else *lcd1_PORT &= ~(1 << DB5); LCD_ticks(BIT_N_TICKS);
	if(c & 0x10) *lcd1_PORT |= 1 << DB4; else *lcd1_PORT &= ~(1 << DB4); LCD_ticks(BIT_N_TICKS);
	
	if(D_I) *lcd1_PORT |= (1 << RS); else *lcd1_PORT &= ~(1 << D_I);
	LCD1_strobe(LCD_N_TICKS); LCD_ticks(BIT_N_TICKS);
	
	if(c & 0x08) *lcd1_PORT |= 1 << DB7; else *lcd1_PORT &= ~(1 << DB7); LCD_ticks(BIT_N_TICKS);
	if(c & 0x04) *lcd1_PORT |= 1 << DB6; else *lcd1_PORT &= ~(1 << DB6); LCD_ticks(BIT_N_TICKS);
	if(c & 0x02) *lcd1_PORT |= 1 << DB5; else *lcd1_PORT &= ~(1 << DB5); LCD_ticks(BIT_N_TICKS);
	if(c & 0x01) *lcd1_PORT |= 1 << DB4; else *lcd1_PORT &= ~(1 << DB4); LCD_ticks(BIT_N_TICKS);
	
	*lcd1_PORT &= ~(1<<EN); LCD_ticks(LCD_N_TICKS);
}
char LCD1_read(unsigned short D_I)
{
	char c = 0x00;
	*lcd1_DDR &= ~((1 << DB4) | (1 << DB5) | (1 << DB6) | (1 << DB7)); // mcu as input
	*lcd1_PORT |= (1 << DB4) | (1 << DB5) | (1 << DB6) | (1 << DB7); // pull up resistors
	*lcd1_PORT |= (1 << RW); // lcd as output
	
	if(D_I) *lcd1_PORT |= (1 << RS); else *lcd1_PORT &= ~(1 << D_I);
	LCD1_strobe(LCD_N_TICKS); LCD_ticks(BIT_N_TICKS);
	
	if(*lcd1_PIN & (1 << DB7)) c |= 1 << 7; else c &= ~(1 << 7); LCD_ticks(BIT_N_TICKS);
	if(*lcd1_PIN & (1 << DB6)) c |= 1 << 6; else c &= ~(1 << 6); LCD_ticks(BIT_N_TICKS);
	if(*lcd1_PIN & (1 << DB5)) c |= 1 << 5; else c &= ~(1 << 5); LCD_ticks(BIT_N_TICKS);
	if(*lcd1_PIN & (1 << DB4)) c |= 1 << 4; else c &= ~(1 << 4); LCD_ticks(BIT_N_TICKS);
	
	if(D_I) *lcd1_PORT |= (1 << RS); else *lcd1_PORT &= ~(1 << D_I);
	LCD1_strobe(LCD_N_TICKS); LCD_ticks(BIT_N_TICKS);
	
	if(*lcd1_PIN & (1 << DB7)) c |= 1 << 3; else c &= ~(1 << 3); LCD_ticks(BIT_N_TICKS);
	if(*lcd1_PIN & (1 << DB6)) c |= 1 << 2; else c &= ~(1 << 2); LCD_ticks(BIT_N_TICKS);
	if(*lcd1_PIN & (1 << DB5)) c |= 1 << 1; else c &= ~(1 << 1); LCD_ticks(BIT_N_TICKS);
	if(*lcd1_PIN & (1 << DB4)) c |= 1 << 0; else c &= ~(1 << 0); LCD_ticks(BIT_N_TICKS);
	
	*lcd1_PORT &= ~(1<<EN); LCD_ticks(LCD_N_TICKS);
	
	return c;
}
void LCD1_BF(void)
{
	uint8_t i;
	char inst = 0x80;
	for(i=0; (0x80 & inst); i++){ // it has to read at minimum one equal and exit immediately if not equal, weird property.
		inst = LCD0_read(INST);
		if(i > 1)
			break;
	}
}
char LCD1_getch(void)
{
	char c;
	c = LCD1_read(DATA);
	LCD1_BF();
	return c;
}
void LCD1_putch(char c)
{
	LCD1_write(c, DATA);
	LCD1_BF();
}
void LCD1_string(const char* s)
{
	char tmp;
	while(*s){
		tmp = *(s++);
		LCD1_putch(tmp);
	}
}
void LCD1_string_size(const char* s, uint8_t size)
{
	char tmp;
	uint8_t pos = 0;
	while(*s){
		tmp = *(s++);
		pos++;
		if(pos > size)
			break;
		LCD1_putch(tmp);
	}
	while(pos < size){
		LCD1_putch(' ');
		pos++;
	}
}
void LCD1_hspace(uint8_t n)
{
	for(; n; n--){
		LCD1_putch(' ');
	}
}
void LCD1_clear(void)
{
	LCD1_write(0x01, INST);
	_delay_ms(1.53);
}
void LCD1_gotoxy(unsigned int y, unsigned int x)
{
	switch(y){
		case 0:
			LCD1_write((0x80 + x), INST);
			LCD1_BF();
		break;
		case 1:
			LCD1_write((0xC0 + x), INST);
			LCD1_BF();
		break;
		case 2:
			LCD1_write((0x94 + x), INST); // 0x94
			LCD1_BF();
		break;
		case 3:
			LCD1_write((0xD4 + x), INST); // 0xD4
			LCD1_BF();
		break;
		default:
		break;
	}
}
void LCD1_strobe(uint16_t num)
{
	*lcd1_PORT &= ~(1<<EN);
	LCD_ticks(num);
	*lcd1_PORT |= (1<<EN);
}
void LCD1_reboot(void)
{
	// low high detect pin NC
	uint8_t i;
	uint8_t tmp;
	tmp = *lcd1_PIN & (1 << NC);
	i = tmp ^ lcd1_detect;
	i &= tmp;
	if(i)
		LCD1_inic();
	lcd1_detect = tmp;
}
void LCD_ticks(uint16_t num)
{
	uint16_t count;
	for(count = 0; count < num; count++) ;
}

/***File Interrupt***/

/***EOF***/

