/************************************************************************
	Atmega 328 Interrupt
Author: Sergio Manuel Santos <sergio.salazar.santos@gmail.com>
Hardware: ATmega128 at 16 Mhz
License: GNU General Public License 
Date: 04122022
Comment:

************************************************************************/
#ifndef _ATMEGA328INTERRUPT_H_
	#define _ATMEGA328INTERRUPT_H_

/*** Compiler ***/
#if (__GNUC__ * 100 + __GNUC_MINOR__) < 304
	#error "This library requires AVR-GCC 3.4 or later, update to newer AVR-GCC compiler !"
#endif

/*** Working Frequency ***/
#ifndef F_CPU
	#define F_CPU 8000000UL
#endif

/*** Global Library ***/
#include <inttypes.h>

/*** Global Constant & Macros ***/

/*** Global Variable ***/
struct intrpt{
	void (*set)(uint8_t channel, uint8_t sense);
	void (*off)(uint8_t channel);
	uint8_t (*reset_status)(void);
};
typedef struct intrpt INTERRUPT;

/*** Global Header ***/
INTERRUPT INTERRUPTenable(void);

#endif
/***EOF***/

