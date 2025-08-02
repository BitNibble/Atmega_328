/***************************************************************************************************
	TWI API
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: Atmega 328 by ETT ET-BASE
Update:   01/01/2024
**************************************************************************************************/
#ifndef _ATMEGA328TWI_H_
	#define _ATMEGA328TWI_H_

/*** Library ***/
#include "atmega328.h"

/*** Constant & Macro ***/
#ifndef _TWI_MODULE_
	#define _TWI_MODULE_
#endif
#ifndef F_CPU
	#define F_CPU 16000000UL
#endif
#ifndef TWI_SCL_CLOCK
	#define TWI_SCL_CLOCK 100000UL
#endif
#define TWI_NACK 0
#define TWI_ACK 1
#define TWI_WRITE 0
#define TWI_READ 1
/************/
#define TWI_T_START 0x01
#define TWI_T_REPEATSTART 0X02
// Status Codes for MASTER Transmitter Mode
#define TWI_M_SLAW_R_ACK 0X03
#define TWI_M_SLAW_R_NACK 0X04
#define TWI_M_DATABYTE_R_ACK 0X05
#define TWI_M_DATABYTE_R_NACK 0X06
#define TWI_ARBLSLAWDATABYTE 0X07
// Status Codes for Master Receiver Mode
#define TWI_ARBLSLARNACK 0X07
#define TWI_M_SLAR_R_ACK 0X08
#define TWI_M_SLAR_R_NACK 0X09
#define TWI_M_DATABYTE_T_ACK 0X0A
#define TWI_M_DATABYTE_T_NACK 0X0B
// Status Codes for SLAVE Receiver Mode
#define TWI_SR_OSLAW_T_ACK 0X0C
#define TWI_MARBLSLARW_SR_OSLAW_T_ACK 0X0D
#define TWI_SR_GCALL_T_ACK 0X0E
#define TWI_MARBLSLARW_SR_GCALL_T_ACK 0X0F
#define TWI_POSLAW_SR_DATABYTE_T_ACK 0X10
#define TWI_POSLAW_SR_DATABYTE_T_NACK 0X11
#define TWI_PGCALL_SR_DATABYTE_T_ACK 0X12
#define TWI_PGCALL_SR_DATABYTE_T_NACK 0X13
#define TWI_SR_STOPREPEATSTART 0X14
// Status Codes for Slave Transmitter Mode
#define TWI_ST_OSLAR_T_ACK 0X15
#define TWI_MARBLSLARW_ST_OSLAR_T_ACK 0X16
#define TWI_ST_DATABYTE_R_ACK 0X17
#define TWI_ST_DATABYTE_R_NACK 0X18
#define TWI_ST_LASTDATABYTE_R_ACK 0X19
// Miscellaneous States
#define TWI_TWINT_AT_ZERO 0X1F
#define TWI_BUS_ERROR 0X00
// Masks
#define TWI_IO_MASK 0x30
#define TWI_STATUS_MASK 0xF8
#define TWI_PRESCALER_MASK 0x03
#define TWI_ADDRESS_instanceISTER_MASK 0xFE
#define Nticks 1023 //anti polling freeze.

// devices
//#define PCF8563 0x51			// RTC
//#define DS1307_ID 0xD0		// I2C DS1307 Device Identifier
//#define TC74_ID 0x9A			// device address of TC74
//#define Dev24C02_ID 0xA2		// device address 24C02
//#define LM73_ID 0x90			// LM73 address temperature sensor

/*** Handler ***/
typedef struct{
	// V-table
	void (*start)(void);
	void (*connect)(uint8_t address, uint8_t rw);
	void (*master_write)(uint8_t var_twiData_u8);
	uint8_t (*master_read)(uint8_t ack_nack);
	void (*stop)(void);
	uint8_t (*status)(void);
}TWI0;

TWI0 twi_enable(uint8_t atmega_ID, uint8_t prescaler);
TWI0* twi(void);

#endif
/*** EOF ***/

