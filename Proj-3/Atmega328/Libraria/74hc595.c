/*************************************************************************
	74HC595
Author: Sergio Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License     
Hardware: 74HC595
Date: 07052023
Comment:
	Tested Atemga88 8Mhz and Atmega328 8Mhz
************************************************************************/
/*** File Library ***/
#include "74hc595.h"

/*** File Constant & Macro ***/

/*** File Variable ***/

/*** File Header ***/
void HC595_shift_bit(struct hc595* self, uint8_t bool);
void HC595_shift_ibyte(struct hc595* self, uint8_t byte);
void HC595_shift_byte(struct hc595* self, uint8_t byte);
void HC595_shift_out(struct hc595* self);

/*** Procedure & Function ***/
HC595 HC595enable(volatile uint8_t *ddr, volatile uint8_t *port, uint8_t datapin, uint8_t clkpin, uint8_t outpin)
{
	// LOCAL VARIABLES
	// ALLOCAÇÂO MEMORIA PARA Estrutura
	HC595 hc595;
	// import parametros
	hc595.sig.hc595_DDR = ddr;
	hc595.sig.hc595_PORT = port;
	hc595.par.HC595_datapin = datapin;
	hc595.par.HC595_clkpin = clkpin;
	hc595.par.HC595_outpin = outpin;
	// inic variables
	*hc595.sig.hc595_DDR |= (1 << datapin) | (1 << clkpin) | (1 << outpin);
	*hc595.sig.hc595_PORT &= ~((1<<datapin) | (1<<clkpin) | (1 << outpin));
	// Direccionar apontadores para PROTOTIPOS
	hc595.bit = HC595_shift_bit;
	hc595.ibyte = HC595_shift_ibyte;
	hc595.byte = HC595_shift_byte;
	hc595.out = HC595_shift_out;
	
	return hc595;
}
void HC595_shift_bit(struct hc595* self, uint8_t bool)
{
	if (bool)
		*self->sig.hc595_PORT |= (1 << self->par.HC595_datapin); // Data bit HIGH
	else
		*self->sig.hc595_PORT &= ~(1 << self->par.HC595_datapin); // Data bit LOW
	*self->sig.hc595_PORT |= (1 << self->par.HC595_clkpin); // Shift bit
	*self->sig.hc595_PORT &= ~(1 << self->par.HC595_clkpin); // Shift disable
}
void HC595_shift_ibyte(struct hc595* self, uint8_t byte)
{
	uint8_t i;
	for(i = 0; i < 8; i++)
		HC595_shift_bit(self, byte & (1 << i));
	HC595_shift_out(self);
}
void HC595_shift_byte(struct hc595* self, uint8_t byte)
{
	uint8_t i;
	for(i = 0; i < 8; i++)
		HC595_shift_bit(self, byte & (1 << (7 - i)));
	HC595_shift_out(self);
}
void HC595_shift_out(struct hc595* self)
{
	*self->sig.hc595_PORT |= (1 << self->par.HC595_outpin); // Output enable
	*self->sig.hc595_PORT &= ~(1 << self->par.HC595_outpin); // Output disable
}

/***File Interrupt***/

/***EOF***/

