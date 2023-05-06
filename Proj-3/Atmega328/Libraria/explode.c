/********************************************************************
	EXPLODE
Author: Sergio Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: all
Date: 06052023
Comment:
	Pin Analysis
********************************************************************/
/*** File Library ***/
#include "explode.h"

/*** File Constant & Macro ***/

/*** File Variable ***/

/*** File Header ***/
void EXPLODEupdate(EXPLODE *self, uint8_t x);
uint8_t EXPLODEhh(EXPLODE *self);
uint8_t EXPLODEll(EXPLODE *self);
uint8_t EXPLODElh(EXPLODE *self);
uint8_t EXPLODEhl(EXPLODE *self);

/*** Procedure & Function ***/
EXPLODE EXPLODEenable( void )
{
	// struct object
	struct expld explode;
	// initialize VAR
	explode.par.XI = 0;
	explode.par.XF = 0;
	// function pointers
	explode.update = EXPLODEupdate;
	return explode; // return copy
}
// boot (preamble in while loop)
void EXPLODEupdate(EXPLODE *self, uint8_t x)
{
	self->par.XI = self->par.XF;
	self->par.XF = x;
	self->sig.HL = EXPLODEhl(self);
	self->sig.LH = EXPLODElh(self);
	self->sig.HH = EXPLODEhh(self);
	self->sig.LL = EXPLODEll(self);
}
// hh
uint8_t EXPLODEhh(EXPLODE *self)
{
	return (self->par.XI & self->par.XF);
}
// ll
uint8_t EXPLODEll(EXPLODE *self)
{
	return ~(self->par.XI | self->par.XF);
}
// lh
uint8_t EXPLODElh(EXPLODE *self)
{
	uint8_t i;
	i = self->par.XI ^ self->par.XF;
	i &= self->par.XF;
	return i;
}
// hl
uint8_t EXPLODEhl(EXPLODE *self)
{
	uint8_t i;
	i = self->par.XF ^ self->par.XI;
	i &= self->par.XI;
	return i;
}

/*** File Interrupt ***/

/***EOF***/

