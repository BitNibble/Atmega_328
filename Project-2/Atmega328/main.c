/*********************************************************************
Hardware: Atmega328.c
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Created:  20/04/2023 14:00:00
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
		RTC PCF8563 (twi)
-PC4 SDA pin 27
-PC5 SCL pin 28
********************************************************************/
/*** File library ***/
#include "atmega328.h"
#include "function.h"
#include "lcd2p.h"
#include "pcf8563rtc.h"

#define TRUE 1
#define ZERO 0

PCF8563RTC rtc;
struct time tm; // time struct RTC
struct date dt; // date struct RTC

uint16_t count;

int main(void)
{
func_enable();
lcd02p_enable(&DDRB, &PINB, &PORTB, &DDRC, &PINC, &PORTC);
rtc = pcf8563rtc_enable(16); // RTC with I2C

for ( ; TRUE; ) // Looping
{
	lcd02p()->reboot();
	
	tm=rtc.GetTime();
	dt=rtc.GetDate();
	lcd02p()->gotoxy(0,0);
	lcd02p()->string_size("S:",3);
	lcd02p()->gotoxy(0,8);
	lcd02p()->string_size(func()->ui16toa(rtc.bcd2dec(dt.days)),2);
	lcd02p()->putch(':');
	lcd02p()->string_size(func()->ui16toa(rtc.bcd2dec(dt.century_months)),2);
	lcd02p()->putch(':');
	lcd02p()->string_size(func()->ui16toa(rtc.bcd2dec(dt.years)),2);
	lcd02p()->gotoxy(1,8);
	lcd02p()->string_size(func()->ui16toa(rtc.bcd2dec(tm.hours)),2);
	lcd02p()->putch(':');
	lcd02p()->string_size(func()->ui16toa(rtc.bcd2dec(tm.minutes)),2);
	lcd02p()->putch(':');
	lcd02p()->string_size(func()->ui16toa(rtc.bcd2dec(tm.VL_seconds)),2);
	
	
	//lcd02p()->gotoxy(0,0);
	//lcd02p()->string_size("Welcome", 15);
	//lcd02p()->gotoxy(1,0);
	//lcd02p()->string_size( func()->ui16toa(count), 6 );
	
	
}}

/*** EOF ***/

/******
1º Sequence
2º Scope
3º Pointer and Variable
4º Casting
******/

