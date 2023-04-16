/*************************************************************************
	Atmega 328 Interrupt
Author: Sergio Manuel Santos <sergio.salazar.santos@gmail.com>
Hardware: ATmega128 at 16 Mhz
License: GNU General Public License        
Date: 04122022
Comment:

*************************************************************************/
/*** File Library ***/
#include "atmega328mapping.h"
#include <stdarg.h>

/*** File Constant & Macro ***/
#if defined(__AVR_ATmega48__) ||defined(__AVR_ATmega88__) || defined(__AVR_ATmega168__) || \
      defined(__AVR_ATmega48P__) ||defined(__AVR_ATmega88P__) || defined(__AVR_ATmega168P__) || \
      defined(__AVR_ATmega328__) || defined(__AVR_ATmega328P__) 
	#define MEGA_INTERRUPT
	#define External_Interrupt_Control_Register_A EICRA
	#define External_Interrupt_Mask_Register EIMSK
	#define External_Interrupt_Flag_Register EIFR
	#define Pin_Change_Interrrupt_Control_Register PCICR
	#define Pin_Change_Interrupt_Flag_Register PCIFR
	#define Pin_Change_Mask_Register_2 PCMSK2
	#define Pin_Change_Mask_Register_1 PCMSK1
	#define Pin_Change_Mask_Register_0 PCMSK0
	#define MCU_Control_Status_Register MCUSR
	#define MCU_Control_Status_Register_Mask 0X0F
#else
 	#error "Not Atmega 328"
#endif

/*** File Variable ***/

/*** File Header ***/
void INTERRUPT_set(uint8_t channel, uint8_t sense);
void INTERRUPT_off(uint8_t channel);
uint8_t INTERRUPT_reset_status(void);

/*** Procedure and Function ***/
INTERRUPT INTERRUPTenable(void)
// setup blank
{
	struct intrpt interrupt;
	// Pre-Processor Case 1
	External_Interrupt_Mask_Register = 0X00;
	
	interrupt.set = INTERRUPT_set;
	interrupt.off = INTERRUPT_off;
	interrupt.reset_status = INTERRUPT_reset_status;
	
	return interrupt;
}
uint8_t INTERRUPT_reset_status(void)
{
	uint8_t reset, ret = 0;
	reset = (MCU_Control_Status_Register & MCU_Control_Status_Register_Mask);
	switch(reset){
		case 1: // Power-On Reset Flag
			ret = 0;
			MCU_Control_Status_Register &= ~(1 << PORF);
			break;
		case 2: // External Reset Flag
			MCU_Control_Status_Register &= ~(1 << EXTRF);
			ret = 1;
			break;
		case 4: // Brown-out Reset Flag
			MCU_Control_Status_Register &= ~(1 << BORF);
			ret = 2;
			break;
		case 8: // Watchdog Reset Flag
			MCU_Control_Status_Register &= ~(1 << WDRF);
			ret = 3;
			break;
		default: // clear all status
			MCU_Control_Status_Register &= ~(MCU_Control_Status_Register_Mask);
			break;
	}
	return ret;
}
void INTERRUPT_set(uint8_t channel, uint8_t sense)
{
	switch( channel ){
		case 0: 
			External_Interrupt_Mask_Register &= ~(1 << INT0);
			External_Interrupt_Control_Register_A &= ~((1 << ISC01) | (1 << ISC00));
			switch(sense){
				case 0: // The low level of INT0 generates an interrupt request.
				case 1: // Any logical change on INT0 generates an interrupt request.
					break;
				case 2: // The falling edge of INT0 generates an interrupt request.
					External_Interrupt_Control_Register_A |= (1 << ISC01);
					break;
				case 3: // The rising edge of INT0 generates an interrupt request.
					External_Interrupt_Control_Register_A |= ((1 << ISC01) | (1 << ISC00));
					break;
				default: // The low level of INT0 generates an interrupt request.
					break;
			}
			External_Interrupt_Mask_Register |= (1 << INT0);
			break;
		case 1:
			External_Interrupt_Mask_Register &= ~(1 << INT1);
			External_Interrupt_Control_Register_A &= ~((1 << ISC11) | (1 << ISC10));
			switch(sense){
				case 0: // The low level of INT1 generates an interrupt request.
				case 1: // Any logical change on INT1 generates an interrupt request.
					break;
				case 2: // The falling edge of INT1 generates an interrupt request.
					External_Interrupt_Control_Register_A |= (1 << ISC11);
					break;
				case 3: // The rising edge of INT1 generates an interrupt request.
					External_Interrupt_Control_Register_A |= ((1 << ISC11) | (1 << ISC10));
					break;
				default: // The low level of INT1 generates an interrupt request.
					break;
			}
			External_Interrupt_Mask_Register |= (1 << INT1);
			break;
		default:
			External_Interrupt_Mask_Register = 0X00;
			break;
	}
}
void INTERRUPT_off(uint8_t channel)
{
	switch( channel ){
		case 0: // desable
			External_Interrupt_Mask_Register &= ~(1 << INT0);
			break;
		case 1: // desable
			External_Interrupt_Mask_Register &= ~(1 << INT1);
			break;
		default: // all disable
			External_Interrupt_Mask_Register = 0X00;
			break;
	}
}

/*** File Interrupt ***/
// ISR(INT0_vect){}
// ISR(INT1_vect){}

/***EOF***/

