/***********************************************************
	Testing Hardware Mapping
Author : Sergio Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: Atmega 328
Software: Microchip Studio (Version: 7.0.2542)
Date: 15/04/2023 14:00:00
Comment:
	Testing Atmega 328 Hardware layer
	
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
ATMEGA328 m328;

/***File Header***/
void PORTINIT(void);

/***Procedure & Function****/
int main(void)
{
	/***Preamble***/
	m328 = ATMEGA328enable();
	/***Local Variable***/
	
	/***Local Variable***/
	m328.gpwr.reg->r0=0xFF;
	m328.gpwr.reg->r1=0xFF;
	m328.gpwr.reg->X.L=m328.par.HLbyte.L=0xFF;
	m328.tc1.imask->timsk1=0XFF;
	//m328.gpwr.reg->X=0xFFFF;
	m328.ac.reg->acsr=0xFF;
	
    /* Replace with your application code */
    while (TRUE)
    {
		m328.cpu.gpio->gpior0=0xFF;
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
1� Sequence
2� Scope
3� Pointer and Variable
4� Casting
******/

