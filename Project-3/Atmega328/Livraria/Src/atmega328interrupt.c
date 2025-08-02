/*************************************************************************
	Atmega 328 Interrupt
Author:   <sergio.salazar.santos@gmail.com>
Hardware: ATmega328
License:  GNU General Public License        
Update:   01/01/2024
*************************************************************************/
/*** Library ***/
#include "atmega328interrupt.h"

/*** File Variable ***/
static EXINT0 setup_interrupt;

/*** Header ***/
void INTERRUPT_set(uint8_t channel, uint8_t sense);
void INTERRUPT_off(uint8_t channel);
uint8_t INTERRUPT_reset_status(void);

/*** Handler ***/
EXINT0 exint_enable(void)
// setup blank
{
	exint_imask_reg()->eimsk.var = 0X00;
	// V-table
	setup_interrupt.set = INTERRUPT_set;
	setup_interrupt.off = INTERRUPT_off;
	setup_interrupt.reset_status = INTERRUPT_reset_status;

	return setup_interrupt;
}

EXINT0* exint(void){ return &setup_interrupt; };

/*** Procedure and Function definition ***/
uint8_t INTERRUPT_reset_status(void)
{
	uint8_t reset, ret = 0;
	reset = (cpu_reg()->mcusr.var & MCU_Control_Status_register_Mask);
	switch(reset){
		case 1: // Power-On Reset Flag
			ret = 0;
			cpu_reg()->mcusr.var &= ~(1 << PORF);
			break;
		case 2: // External Reset Flag
			cpu_reg()->mcusr.var &= ~(1 << EXTRF);
			ret = 1;
			break;
		case 4: // Brown-out Reset Flag
			cpu_reg()->mcusr.var &= ~(1 << BORF);
			ret = 2;
			break;
		case 8: // Watchdog Reset Flag
			cpu_reg()->mcusr.var &= ~(1 << WDRF);
			ret = 3;
			break;
		default: // clear all status
			cpu_reg()->mcusr.var &= ~(MCU_Control_Status_register_Mask);
			break;
	}
	
	return ret;
}
void INTERRUPT_set(uint8_t channel, uint8_t sense)
{
	switch( channel ){
		case 0: 
			exint_imask_reg()->eimsk.var &= ~(1 << INT0);
			exint_reg()->eicra.var &= ~((1 << ISC01) | (1 << ISC00));
			switch(sense){
				case 0: // The low level of INT0 generates an interrupt request.
				case 1: // Any logical change on INT0 generates an interrupt request.
					break;
				case 2: // The falling edge of INT0 generates an interrupt request.
					exint_reg()->eicra.var |= (1 << ISC01);
					break;
				case 3: // The rising edge of INT0 generates an interrupt request.
					exint_reg()->eicra.var |= ((1 << ISC01) | (1 << ISC00));
					break;
				default: // The low level of INT0 generates an interrupt request.
					break;
			}
			exint_imask_reg()->eimsk.var |= (1 << INT0);
			break;
		case 1:
			exint_imask_reg()->eimsk.var &= ~(1 << INT1);
			exint_reg()->eicra.var &= ~((1 << ISC11) | (1 << ISC10));
			switch(sense){
				case 0: // The low level of INT1 generates an interrupt request.
				case 1: // Any logical change on INT1 generates an interrupt request.
					break;
				case 2: // The falling edge of INT1 generates an interrupt request.
					exint_reg()->eicra.var |= (1 << ISC11);
					break;
				case 3: // The rising edge of INT1 generates an interrupt request.
					exint_reg()->eicra.var |= ((1 << ISC11) | (1 << ISC10));
					break;
				default: // The low level of INT1 generates an interrupt request.
					break;
			}
			exint_imask_reg()->eimsk.var |= (1 << INT1);
			break;
		default:
			exint_imask_reg()->eimsk.var = 0X00;
			break;
	}
}
void INTERRUPT_off(uint8_t channel)
{
	switch( channel ){
		case 0: // disable
			exint_imask_reg()->eimsk.var &= ~(1 << INT0);
			break;
		case 1: // disable
			exint_imask_reg()->eimsk.var &= ~(1 << INT1);
			break;
		default: // all disable
			exint_imask_reg()->eimsk.var = 0X00;
			break;
	}
}

/*** EOF ***/

