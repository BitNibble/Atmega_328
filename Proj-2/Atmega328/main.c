/***********************************************************
Hardware: Atmega328.c
Author : Sergio Santos
	<sergio.salazar.santos@gmail.com>
Date: 15/04/2023 14:00:00
Comment:
	
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
	m328.gpwr.reg->X.L=m328.HLByte.L=0xFF;
	m328.tc1.reg->timsk1=0XFF;
	//m328.gpwr.reg->X=0xFFFF;
	m328.ac.reg->acsr=0xFF;
	
    /* Replace with your application code */
    while (TRUE)
    {
		m328.cpu.reg->gpior0=0xFF;
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

