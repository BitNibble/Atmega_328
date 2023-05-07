/********************************************************************
	EXPLODE
Author: Sergio Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: all
Date: 07052023
Comment:
	Pin Analysis
********************************************************************/
/*** File Library ***/
#include "explode.h"

/*** File Constant & Macro ***/

/*** File Variable ***/

/*** File Header ***/
void EXPLODEupdate(explodesignal* sig, uint8_t x);
uint8_t EXPLODEhh(explodesignal* sig);
uint8_t EXPLODEll(explodesignal* sig);
uint8_t EXPLODElh(explodesignal* sig);
uint8_t EXPLODEhl(explodesignal* sig);

/*** Procedure & Function ***/
EXPLODE EXPLODEenable( void )
{
	// struct object
	struct expld explode;
	// initialize VAR
	explode.sig.XI = 0;
	explode.sig.XF = 0;
	// function pointers
	explode.update = EXPLODEupdate;
	return explode; // return copy
}
// boot (preamble in while loop)
void EXPLODEupdate(explodesignal* sig, uint8_t x)
{
	sig->XI = sig->XF;
	sig->XF = x;
	sig->HL = EXPLODEhl(sig);
	sig->LH = EXPLODElh(sig);
	sig->HH = EXPLODEhh(sig);
	sig->LL = EXPLODEll(sig);
}
// hh
uint8_t EXPLODEhh(explodesignal* sig)
{
	return (sig->XI & sig->XF);
}
// ll
uint8_t EXPLODEll(explodesignal* sig)
{
	return ~(sig->XI | sig->XF);
}
// lh
uint8_t EXPLODElh(explodesignal* sig)
{
	uint8_t i;
	i = sig->XI ^ sig->XF;
	i &= sig->XF;
	return i;
}
// hl
uint8_t EXPLODEhl(explodesignal* sig)
{
	uint8_t i;
	i = sig->XF ^ sig->XI;
	i &= sig->XI;
	return i;
}

/*** File Interrupt ***/

/***EOF***/

