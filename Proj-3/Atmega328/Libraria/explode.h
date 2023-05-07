/************************************************************************
	EXPLODE
Author: Sergio Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: all
Date: 07052023
Comment:
	Pin Analysis
************************************************************************/
#ifndef _EXPLODE_H_
	#define _EXPLODE_H_

/*** Global Library ***/
#include <inttypes.h>

/*** Global Constant & Macro ***/

/*** Global Variable ***/
typedef struct {
	unsigned int XI;
	unsigned int XF;
	unsigned int HL;
	unsigned int LH;
	unsigned int HH;
	unsigned int LL;
}explodesignal;

struct expld{
	// Variable
	explodesignal sig;
	// PROTOTYPES VTABLE
	void (*update)(explodesignal* sig, uint8_t x); // preamble in (while loop)
};

typedef struct expld EXPLODE;

/*** Global Header ***/
EXPLODE EXPLODEenable(void);

#endif

/***EOF***/

