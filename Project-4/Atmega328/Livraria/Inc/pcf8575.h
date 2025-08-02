/***************************************************************************************************
	PCF8575
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: PCF8575
Date:     24012024
***************************************************************************************************/
/****** Comment:
	
 **************************************************************************************************/
#ifndef _PCF8575_H_
	#define _PCF8575_H_

/*** Global Library ***/
#include <inttypes.h>

#if defined(__AVR_ATmega64__) || defined(__AVR_Atmega328__)
	#include "atmega328twi.h"
#elif defined(__AVR_ATmega328__) || defined(__AVR_ATmega328P__)
	#include "atmega328twi.h"
#else
	#error "MCU Lib not available"
#endif

/*** Global Constant & Macro ***/
#ifndef HIGH
	#define HIGH 0xFF
#endif
#ifndef LOW
	#define LOW 0x00
#endif
#define N_Instance_PCF8575 4
#define PCF8575_BASE_ADDRESS 32

typedef struct{
	TWI0 twi;
	uint8_t pcf8575_id;
	uint16_t state;
}pcf8575_parameter;

typedef struct{
	pcf8575_parameter par;
	void (*writehbits)( pcf8575_parameter *par, uint16_t hbits, uint8_t state );
	uint16_t (*readhbits)( pcf8575_parameter *par, uint16_t hbits );
}PCF8575;

/*** Global Header ***/
PCF8575 pcf8575_enable( uint8_t pcf8575_id, uint8_t twi_prescaler );

#endif

/*** EOF ***/

