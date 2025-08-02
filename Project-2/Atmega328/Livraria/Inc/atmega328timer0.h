/*************************************************************************
	TIMER0
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: Atmega 328 by ETT ET-BASE
Update:   01/01/2024
*************************************************************************/
#ifndef _ATMEGA328TIMER0_H_
	#define _ATMEGA328TIMER0_H_

/*** Library ***/
#include "atmega328.h"

#ifndef GLOBAL_INTERRUPT_ENABLE
	#define GLOBAL_INTERRUPT_ENABLE 7
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
}TC0;

TC0 tc0_enable(unsigned char wavegenmode, unsigned char interrupt);
TC0* tc0(void);

#endif
/*** EOF ***/

