/***************************************************************************************************
	PCF8575
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: PCF8575
Date:     24012024
Comment:
	
***************************************************************************************************/
/*** File Library ***/
#include "pcf8575.h"

/*** File Header ***/
void PCF8575_writehbits( pcf8575_parameter *par, uint16_t hbits, uint8_t state );
uint16_t PCF8575_readhbits( pcf8575_parameter *par, uint16_t hbits );

/*** Procedure & Function ***/
PCF8575 pcf8575_enable(uint8_t pcf8575_id, uint8_t twi_prescaler)
{
	PCF8575 setup_pcf8575;
	
	setup_pcf8575.par.twi = twi_enable(pcf8575_id, twi_prescaler); // Initialize the I2c module.
	setup_pcf8575.par.pcf8575_id = pcf8575_id;
	setup_pcf8575.par.state = 0xFFFF;
	
	// Vtable
	setup_pcf8575.writehbits = PCF8575_writehbits;
	setup_pcf8575.readhbits = PCF8575_readhbits;
	
	return setup_pcf8575;
}

void PCF8575_writehbits(pcf8575_parameter *par, uint16_t hbits, uint8_t state)
{
	if(state) par->state |= hbits; else par->state &= ~hbits;
	par->twi.start();
	par->twi.connect(par->pcf8575_id,TWI_WRITE);
	par->twi.master_write(writehlbyte(par->state).par.l);
	par->twi.master_write(writehlbyte(par->state).par.h);
	par->twi.stop();
}

uint16_t PCF8575_readhbits(pcf8575_parameter *par, uint16_t hbits)
{
	U_word data;
	par->twi.start();
	par->twi.connect(par->pcf8575_id, TWI_READ);
	data.par.l = par->twi.master_read(TWI_ACK);
	data.par.h = par->twi.master_read(TWI_NACK);
	par->twi.stop();
	return (readhlbyte(data) & hbits);
}

/***File Interrupt***/

/*** EOF ***/

