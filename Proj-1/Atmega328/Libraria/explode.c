/********************************************************************
	EXPLODE
Author: Sergio Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: all
Date: 30112022
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
	explode.XI = 0;
	explode.XF = 0;
	// function pointers
	explode.update = EXPLODEupdate;
	return explode; // return copy
}
// boot (preamble in while loop)
void EXPLODEupdate(EXPLODE *self, uint8_t x)
{
	self->XI = self->XF;
	self->XF = x;
	self->HL = EXPLODEhl(self);
	self->LH = EXPLODElh(self);
	self->HH = EXPLODEhh(self);
	self->LL = EXPLODEll(self);
}
// hh
uint8_t EXPLODEhh(EXPLODE *self)
{
	return (self->XI & self->XF);
}
// ll
uint8_t EXPLODEll(EXPLODE *self)
{
	return ~(self->XI | self->XF);
}
// lh
uint8_t EXPLODElh(EXPLODE *self)
{
	uint8_t i;
	i = self->XI ^ self->XF;
	i &= self->XF;
	return i;
}
// hl
uint8_t EXPLODEhl(EXPLODE *self)
{
	uint8_t i;
	i = self->XF ^ self->XI;
	i &= self->XI;
	return i;
}

/*** File Interrupt ***/

/***EOF***/

