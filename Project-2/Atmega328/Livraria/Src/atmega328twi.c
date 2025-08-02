/***************************************************************************************************
	TWI API
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: Atmega328 by ETT ET-BASE
Update:   01/01/2024
***************************************************************************************************/
/*** Library ***/
#include "atmega328twi.h"
#include <util/delay.h>

/*** Variable ***/
static TWI0 setup_i2c;

/*** Procedure and Function declaration ***/
void TWI_init(uint8_t device_id, uint8_t prescaler);
void TWI_start(void);
void TWI_connect(uint8_t address, uint8_t rw);
void TWI_master_write(uint8_t var_twiData_u8);
uint8_t TWI_master_read(uint8_t ack_nack);
void TWI_stop(void);
// auxiliary
uint8_t TWI_status(void);
void TWI_wait_twint( uint16_t nticks );

/*** Handler ***/
TWI0 twi_enable(uint8_t atmega_ID,  uint8_t prescaler)
{
	//local var
	uint8_t tSREG;
	
	// Init local var
	tSREG = cpu_reg()->sreg.var;
	cpu_reg()->sreg.par.i = 0;
	// V-table
	setup_i2c.start = TWI_start;
	setup_i2c.connect = TWI_connect;
	setup_i2c.stop = TWI_stop;
	setup_i2c.master_write = TWI_master_write;
	setup_i2c.master_read = TWI_master_read;
	setup_i2c.status = TWI_status;
	
	TWI_init(atmega_ID, prescaler);
	cpu_reg()->sreg.var = tSREG;

	return setup_i2c;
}

TWI0* twi(void){ return &setup_i2c; };

/*** Procedure and Function definition ***/
// void TWI_Init(uint8_t device_id, uint8_t prescaler)
void TWI_init(uint8_t device_id, uint8_t prescaler)
{
	uint8_t cmd = 0x00;
	if(device_id > 0 && device_id < 128)
		cmd = (device_id << 1) | (1 << TWGCE);
	else
		cmd = (1 << TWGCE); // no address, but accept general call
	twi_reg()->twar.var = cmd;
	gpioc_reg()->ddr.var |= TWI_IO_MASK;
	gpioc_reg()->port.var |= TWI_IO_MASK;
	switch(prescaler){
		case 1:
			twi_reg()->twsr.par.twps = 0;
		break;
		case 4:
			twi_reg()->twsr.par.twps = 1;
		break;
		case 16:
			twi_reg()->twsr.par.twps= 2;
		break;
		case 64:
			twi_reg()->twsr.par.twps = 3;
		break;
		default:
			prescaler = 1;
			twi_reg()->twsr.par.twps = 0;
		break;
	}
	twi_reg()->twbr.var = ((F_CPU / TWI_SCL_CLOCK) - 16) / (2 * prescaler);
	// Standard Config begin
	//twi_reg()->twsr.var = 0x00; //set presca1er bits to zero
	//twi_reg()->twbr.var = 0x46; //SCL frequency is 50K for 16Mhz
	//twi_reg()->twcr.var = 0x04; //enab1e TWI module
	// Standard Config end
}
// void TWI_Start(void)
void TWI_start(void) // $08
{
	uint8_t cmd = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
	twi_reg()->twcr.var = cmd;
	
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
	twi_reg()->twdr.var = cmd;
	
	cmd = (1 << TWINT) | (1 << TWEN);
	twi_reg()->twcr.var = cmd;
	
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
	twi_reg()->twdr.var = cmd;
	
	cmd = (1 << TWINT) | (1 << TWEN);
	twi_reg()->twcr.var = cmd;
	
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
	twi_reg()->twcr.var = cmd;
	
	TWI_wait_twint( Nticks );
	
	switch( TWI_status( ) ){
		case TWI_ARBLSLARNACK:
			TWI_stop( );
		break;
		default:
		break;
	}
	
	cmd = twi_reg()->twdr.var;
	return cmd;
}
// void TWI_stop(void)
void TWI_stop(void)
{
	uint8_t cmd = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
	twi_reg()->twcr.var = cmd;
	
	_delay_us(100); //wait for a short time
}
// auxiliary
uint8_t TWI_status( void )
{
	uint8_t cmd = twi_reg()->twsr.par.tws;
	return cmd;
}

void TWI_wait_twint( uint16_t nticks ) // hardware triggered
{
	unsigned int i;
	for(i = 0; !( twi_reg()->twcr.par.twint ); i++ ){ // wait for acknowledgment confirmation bit.
		if( i > nticks ) // timeout
			break;
	}
}
	
/*** EOF ***/

