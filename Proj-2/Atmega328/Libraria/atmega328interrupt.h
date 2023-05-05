/************************************************************************
	Atmega 328 Interrupt
Author: Sergio Manuel Santos
		<sergio.salazar.santos@gmail.com>
Hardware: ATmega328
License: GNU General Public License 
Date: 25042023
Comment:

************************************************************************/
#ifndef _ATMEGA328INTERRUPT_H_
	#define _ATMEGA328INTERRUPT_H_

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

