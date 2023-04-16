/***************************************************************************************************
	TWI API
Author: Sergio Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: Atmega328 by ETT ET-BASE
Date: 30112022
Comment:
	Stable
 **************************************************************************************************/
#ifndef _ATMEGA328TWI_H_
	#define _ATMEGA328TWI_H_

/*** Working Frequency ***/
#ifndef F_CPU
	#define F_CPU 8000000UL
#endif
#ifndef TWI_SCL_CLOCK
	#define TWI_SCL_CLOCK 100000UL
#endif

/*** Global Library ***/
#include <inttypes.h>

/*** Global Constant & Macro ***/
#ifndef GLOBAL_INTERRUPT_ENABLE
	#define GLOBAL_INTERRUPT_ENABLE 7
#endif
#define TWI_NACK 0
#define TWI_ACK 1
#define TWI_WRITE 0
#define TWI_READ 1
// devices
//#define PCF8563 0x51			// RTC
//#define DS1307_ID 0xD0		// I2C DS1307 Device Identifier
//#define TC74_ID 0x9A			// device address of TC74
//#define Dev24C02_ID 0xA2		// device address 24C02
//#define LM73_ID 0x90			// LM73 address temperature sensor

/*** Global Variable ***/
struct twowire{
	void (*start)(void);
	void (*connect)(uint8_t address, uint8_t rw);
	void (*master_write)(uint8_t var_twiData_u8);
	uint8_t (*master_read)(uint8_t ack_nack);
	void (*stop)(void);
	uint8_t (*status)(void);
};
typedef struct twowire TWI;
/*** Global Header ***/
TWI TWIenable(uint8_t atmega_ID, uint8_t prescaler);

#endif
/***EOF***/

