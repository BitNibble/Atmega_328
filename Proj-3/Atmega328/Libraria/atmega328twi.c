/***************************************************************************************************
	TWI API
Author: Sergio Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: Atmega328 by ETT ET-BASE
Date: 30112022
Comment:
	Stable
***************************************************************************************************/
/*** File Library ***/
#include "atmega328mapping.h"
#include <util/delay.h>

/*** File Define and Macro ***/
#define TWI_T_START 0X08
#define TWI_T_REPEATSTART 0X10

// Status Codes for MASTER Transmitter Mode
#define TWI_M_SLAW_R_ACK 0X18
#define TWI_M_SLAW_R_NACK 0X20
#define TWI_M_DATABYTE_R_ACK 0X28
#define TWI_M_DATABYTE_R_NACK 0X30
#define TWI_ARBLSLAWDATABYTE 0X38
// Status Codes for Master Receiver Mode
#define TWI_ARBLSLARNACK 0X38
#define TWI_M_SLAR_R_ACK 0X40
#define TWI_M_SLAR_R_NACK 0X48
#define TWI_M_DATABYTE_T_ACK 0X50
#define TWI_M_DATABYTE_T_NACK 0X58
// Status Codes for SLAVE Receiver Mode
#define TWI_SR_OSLAW_T_ACK 0X60
#define TWI_MARBLSLARW_SR_OSLAW_T_ACK 0X68
#define TWI_SR_GCALL_T_ACK 0X70
#define TWI_MARBLSLARW_SR_GCALL_T_ACK 0X78
#define TWI_POSLAW_SR_DATABYTE_T_ACK 0X80
#define TWI_POSLAW_SR_DATABYTE_T_NACK 0X88
#define TWI_PGCALL_SR_DATABYTE_T_ACK 0X90
#define TWI_PGCALL_SR_DATABYTE_T_NACK 0X98
#define TWI_SR_STOPREPEATSTART 0XA0
// Status Codes for Slave Transmitter Mode
#define TWI_ST_OSLAR_T_ACK 0XA8
#define TWI_MARBLSLARW_ST_OSLAR_T_ACK 0XB0
#define TWI_ST_DATABYTE_R_ACK 0XB8
#define TWI_ST_DATABYTE_R_NACK 0XC0
#define TWI_ST_LASTDATABYTE_R_ACK 0XC8
// Miscellaneous States
#define TWI_TWINT_AT_ZERO 0XF8
#define TWI_BUS_ERROR 0X00
// Masks
#if defined(__AVR_ATmega328__)
	#define TWI_MEGA_328
	#define TWI_IO_MASK 0x30
	#define TWI_STATUS_MASK 0xF8
	#define TWI_PRESCALER_MASK 0x03
	#define TWI_ADDRESS_REGISTER_MASK 0xFE
#else
	#error "Not Atmega 328"
#endif
#define Nticks 1023 //anti polling freeze.

/*** File Variable ***/
ATMEGA328 m;

/*** File Header ***/
void TWI_init(uint8_t device_id, uint8_t prescaler);
void TWI_start(void);
void TWI_connect(uint8_t address, uint8_t rw);
void TWI_master_write(uint8_t var_twiData_u8);
uint8_t TWI_master_read(uint8_t ack_nack);
void TWI_stop(void);
// auxiliary
uint8_t TWI_status(void);
void TWI_wait_twint( uint16_t nticks );

/*** Procedure and Function ***/
// TWI TWIenable(uint8_t atmega_ID,  uint8_t prescaler)
TWI TWIenable(uint8_t atmega_ID,  uint8_t prescaler)
{
	//local var
	uint8_t tSREG;
	TWI ic;
	//inic file var
	m = ATMEGA328enable();
	//inic local var
	tSREG = m.cpu.reg->sreg;
	m.cpu.reg->sreg &= ~(1<<GLOBAL_INTERRUPT_ENABLE);
	// Vtable
	ic.start = TWI_start;
	ic.connect = TWI_connect;
	ic.stop = TWI_stop;
	ic.master_write = TWI_master_write;
	ic.master_read = TWI_master_read;
	ic.status = TWI_status;
	
	TWI_init(atmega_ID, prescaler);
	m.cpu.reg->sreg = tSREG;
	
	return ic;
}
// void TWI_Init(uint8_t device_id, uint8_t prescaler)
void TWI_init(uint8_t device_id, uint8_t prescaler)
{
	uint8_t cmd = 0x00;
	if(device_id > 0 && device_id < 128)
		cmd = (device_id << 1) | (1 << TWGCE);
	else
		cmd = (1 << TWGCE); // no address, but accept general call
	m.twi.reg->twar = cmd;
	m.portd.reg->ddr |= TWI_IO_MASK;
	m.portd.reg->port |= TWI_IO_MASK;
	switch(prescaler){
		case 1:
			m.twi.reg->twsr &= ~TWI_PRESCALER_MASK;
		break;
		case 4:
			m.twi.reg->twsr |= (1 << TWPS0);
		break;
		case 16:
			m.twi.reg->twsr |= (2 << TWPS0);
		break;
		case 64:
			m.twi.reg->twsr |= (3 << TWPS0);
		break;
		default:
			prescaler = 1;
			m.twi.reg->twsr &= ~TWI_PRESCALER_MASK;
		break;
	}
	m.twi.reg->twbr = ((F_CPU / TWI_SCL_CLOCK) - 16) / (2 * prescaler);
	// Standard Config begin
	//m.twi->twsr = 0x00; //set presca1er bits to zero
	//m.twi->twbr = 0x46; //SCL frequency is 50K for 16Mhz
	//m.twi->twcr = 0x04; //enab1e TWI module
	// Standard Config end
}
// void TWI_Start(void)
void TWI_start(void) // $08
{
	uint8_t cmd = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
	m.twi.reg->twcr = cmd;
	
	TWI_wait_twint( Nticks );
	
	switch( TWI_status( ) ){
		case TWI_T_START:
			// Do nothing
		break;
		default:
			TWI_stop( ); // error
		break;
	}
}
// void TWI_Connect(uint8_t address, uint8_t rw)
void TWI_connect( uint8_t address, uint8_t rw )
{
	uint8_t cmd = 0;
	if( rw )
		cmd = (address << 1) | (1 << 0);
	else
		cmd = (address << 1) | (0 << 0);
	m.twi.reg->twdr = cmd;
	
	cmd = (1 << TWINT) | (1 << TWEN);
	m.twi.reg->twcr = cmd;
	
	TWI_wait_twint( Nticks );
	
	switch( TWI_status( ) ){
		case TWI_M_SLAW_R_ACK:
			// Do nothing
		break;
		case TWI_M_SLAR_R_ACK:
			// Do nothing
		break;
		default:
			TWI_stop( ); // error
		break;
	}
}
// void TWI_Write(uint8_t var_twiData_u8)
void TWI_master_write( uint8_t var_twiData_u8 )
{
	uint8_t cmd = var_twiData_u8;
	m.twi.reg->twdr = cmd;
	
	cmd = (1 << TWINT) | (1 << TWEN);
	m.twi.reg->twcr = cmd;
	
	TWI_wait_twint( Nticks );
	
	switch( TWI_status( ) ){
		case TWI_M_DATABYTE_R_ACK:
			// Do nothing
		break;
		default:
			TWI_stop( ); // error
		break;
	}
}
// uint8_t TWI_Read(uint8_t ack_nack)
uint8_t TWI_master_read( uint8_t ack_nack )
{
	uint8_t cmd = 0x00;
	if( ack_nack )
		cmd |= ( 1 << TWEA );
	cmd |= ( 1 << TWINT ) | ( 1 << TWEN );
	m.twi.reg->twcr = cmd;
	
	TWI_wait_twint( Nticks );
	
	switch( TWI_status( ) ){
		case TWI_ARBLSLARNACK:
			TWI_stop( );
		break;
		default:
		break;
	}
	
	cmd = m.twi.reg->twdr;
	return cmd;
}
// void TWI_stop(void)
void TWI_stop(void)
{
	uint8_t cmd = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
	m.twi.reg->twcr = cmd;
	
	_delay_us(100); //wait for a short time
}
// auxiliary
uint8_t TWI_status( void )
{
	uint8_t cmd = m.twi.reg->twsr & TWI_STATUS_MASK;
	return cmd;
}

void TWI_wait_twint( uint16_t nticks ) // hardware triggered
{
	unsigned int i;
	for(i = 0; !( m.twi.reg->twcr & (1 << TWINT)); i++ ){ // wait for acknowledgment confirmation bit.
		if( i > nticks ) // timeout
			break;
	}
}

/*** File Interrupt ***/
// ISR(TWI_vect){}
	
/***EOF***/

