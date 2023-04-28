/************************************************************************
	EXPLODE
Author: Sergio Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: all
Date: 20042023
Comment:
	Pin Analysis
************************************************************************/
#ifndef _EXPLODE_H_
	#define _EXPLODE_H_

/*** Global Library ***/
#include <inttypes.h>

/*** Global Constant & Macro ***/

/*** Global Variable ***/
struct expldparam{
	unsigned int XI;
	unsigned int XF;
};

struct expld{
	// Variable
	struct expldparam par;
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

