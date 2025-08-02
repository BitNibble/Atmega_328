/*************************************************************************
	TIMER2
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: Atmega 328 by ETT ET-BASE
Update:   01/01/2024
*************************************************************************/
#ifndef _ATMEGA328TIMER2_H_
	#define _ATMEGA328TIMER2_H_

/*** Library ***/
#include "atmega328.h"

/*** Constant & Macro ***/
#if defined(__AVR_ATmega328__) || defined(__AVR_ATmega328P__)
	#ifndef GLOBAL_INTERRUPT_ENABLE
		#define GLOBAL_INTERRUPT_ENABLE 7
	#endif
#else
	#error "Not Atmega 328"
#endif

/*** Handler ***/
typedef struct{
	// V-table
	void (*compoutmodeA)(unsigned char compoutmode);
	void (*compoutmodeB)(unsigned char compoutmode);
	void (*compareA)(unsigned char compare);
	void (*compareB)(unsigned char compare);
	void (*start)(unsigned int prescaler);
	void (*stop)(void);
}TC2;

TC2 tc2_enable(unsigned char wavegenmode, unsigned char interrupt);
TC2* tc2(void);

#endif
/*** EOF ***/

