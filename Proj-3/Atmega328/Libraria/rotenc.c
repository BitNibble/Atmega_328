/************************************************************************
	ROTENC
Author: Sergio Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: Rotary encoder Potentiometer
Date: 25102020
Comment:
	Stable
************************************************************************/
/*** File Library ***/
#include "rotenc.h"

/*** File Constant & Macro ***/

/*** File Variable ***/

/*** File Header ***/
ROTENC RotEnc_rte(ROTENC *self, uint8_t data);

/*** Procedure & Function ***/
ROTENC ROTENCenable( uint8_t ChnApin, uint8_t ChnBpin )
{
	// struct object
	ROTENC rtnc;
	// Initialize variables
	rtnc.PinChnA = ChnApin;
	rtnc.PinChnB = ChnBpin;
	rtnc.pchn=rtnc.chn = (1 << ChnBpin) | (1 << ChnApin);
	rtnc.num = 0;
	// function pointers
	rtnc.rte = RotEnc_rte;
	
	return rtnc;
}

ROTENC RotEnc_rte(ROTENC *self, uint8_t data)
{
	uint8_t hl;
	self->chn = data & ((1 << self->PinChnB) | (1 << self->PinChnA));
	hl = self->chn ^ self->pchn;
	hl &= self->pchn;
	if(self->pchn != self->chn){
		if((self->pchn == ((1 << self->PinChnB) | (1 << self->PinChnA))) && (hl & (1 << self->PinChnA)))
		self->num++;
		if((self->pchn == ((1 << self->PinChnB) | (1 << self->PinChnA))) && (hl & (1 << self->PinChnB)))
		self->num--;
	}
	self->pchn = self->chn;
	return *self;
}

/*** File Interrupt ***/

/***EOF***/

