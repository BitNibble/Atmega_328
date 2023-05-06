/************************************************************************
	74HC595
Author: Sergio Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: 74HC595
Date: 07052023
Comment:
	tested Atemga128 16Mhz and Atmega328 8Mhz
************************************************************************/
#ifndef _74HC595_H_
	#define _74HC595_H_

/*** Global Library ***/
#include <inttypes.h>

/*** Global Constant & Macro ***/

/*** Global Variable ***/
typedef struct {
	uint8_t HC595_datapin;
	uint8_t HC595_clkpin;
	uint8_t HC595_outpin;
}hc595parameter;

typedef struct {
	volatile uint8_t *hc595_DDR;
	volatile uint8_t *hc595_PORT;
}hc595signal;

struct hc595{
	hc595parameter par;
	hc595signal sig;
	void (*bit)(struct hc595* self, uint8_t bool);
	void (*ibyte)(struct hc595* self, uint8_t byte);
	void (*byte)(struct hc595* self, uint8_t byte);
	void (*out)(struct hc595* self);
};
typedef struct hc595 HC595;

/*** Global Header ***/
HC595 HC595enable(volatile uint8_t *ddr, volatile uint8_t *port, uint8_t datapin, uint8_t clkpin, uint8_t outpin);

#endif

/***EOF***/

