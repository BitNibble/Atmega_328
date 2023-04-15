/************************************************************************
	EXPLODE
Author: Sergio Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: all
Date: 30112022
Comment:
	Pin Analysis
************************************************************************/
#ifndef _EXPLODE_H_
	#define _EXPLODE_H_

/*** Compiler ***/

/*** Working Frequency ***/

/*** Global Library ***/
#include <inttypes.h>

/*** Global Variable ***/
struct expld{
	// Variable
	unsigned int XI;
	unsigned int XF;
	unsigned int HL;
	unsigned int LH;
	unsigned int HH;
	unsigned int LL;
	// PROTOTYPES VTABLE
	void (*update)(struct expld *self, uint8_t x); // preamble (while loop)
};
typedef struct expld EXPLODE;

/*** Global Header ***/
EXPLODE EXPLODEenable(void);

#endif
/***EOF***/

