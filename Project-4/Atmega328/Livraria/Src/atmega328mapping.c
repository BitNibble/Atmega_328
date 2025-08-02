/********************************************************************
	ATMEGA 328 MAPPING
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: Atmega328 by ETT ET-BASE
Update:   01/01/2024
*********************************************************************/
/****** Comment:
	Virtual Image Atmega 328 mapping and linking.
*********************************************************************/
/*** File Library ***/
#include "atmega328mapping.h"

static ATMEGA328 setup_atmega328;

/*** File Procedure & Function ***/
ATMEGA328 atmega328_enable(void){
	/***GPWR***/
	setup_atmega328.gpwr_reg = gpwr_reg();
	/***AC***/
	setup_atmega328.ac_reg = ac_reg();
	setup_atmega328.ac_did_reg = ac_did_reg();
	/***ADC***/
	setup_atmega328.adc_reg = adc_reg();
	#if defined(_ANALOG_MODULE_)
		setup_atmega328.adc_enable = adc_enable;
		setup_atmega328.adc = adc();
	#endif
	/***CPU***/
	setup_atmega328.cpu_reg = cpu_reg();
	setup_atmega328.cpu_gpio012_reg = cpu_gpio012_reg();
	/***EEPROM***/
	setup_atmega328.eeprom_reg = eeprom_reg();
	#if defined(_EEPROM_MODULE_)
		setup_atmega328.eeprom_enable = eeprom_enable;
		setup_atmega328.eeprom = eeprom();
	#endif
	/***EXINT***/
	setup_atmega328.exint_reg = exint_reg();
	setup_atmega328.exint_iflag_reg = exint_iflag_reg();
	setup_atmega328.exint_imask_reg = exint_imask_reg();
	setup_atmega328.exint_pcmask_reg = exint_pcmask_reg();
	#if defined(_INTERRUPT_MODULE_)
		setup_atmega328.exint_enable = exint_enable;
		setup_atmega328.exint = exint();
	#endif
	/***PORTB***/
	setup_atmega328.gpiob_reg = gpiob_reg();
	/***PORTC***/
	setup_atmega328.gpioc_reg = gpioc_reg();
	/***PORTD***/
	setup_atmega328.gpiod_reg = gpiod_reg();
	/***SPI***/
	setup_atmega328.spi_reg = spi_reg();
	#if defined(_SPI_MODULE_)
		setup_atmega328.spi_enable = spi_enable;
		setup_atmega328.spi = spi();
	#endif
	/***TC1***/
	setup_atmega328.tc1_reg = tc1_reg();
	setup_atmega328.tc1_gcontrol_reg = tc_gcontrol_reg();
	setup_atmega328.tc1_iflag_reg = tc_iflag_reg();
	setup_atmega328.tc1_imask_reg = tc_imask_reg();
	setup_atmega328.tc1_compare_reg = tc1_compare_reg();
	#if defined(_TIMER1_MODULE_)
		setup_atmega328.tc1_enable = tc1_enable;
		setup_atmega328.tc1 = tc1();
	#endif
	/***TC0***/
	setup_atmega328.tc0_reg = tc0_reg();
	setup_atmega328.tc0_gcontrol_reg = tc_gcontrol_reg();
	setup_atmega328.tc0_iflag_reg = tc_iflag_reg();
	setup_atmega328.tc0_imask_reg = tc_imask_reg();
	setup_atmega328.tc0_compare_reg = tc0_compare_reg();
	#if defined(_TIMER0_MODULE_)
		setup_atmega328.tc0_enable = tc0_enable;
		setup_atmega328.tc0 = tc0();
	#endif
	/***TC2***/
	setup_atmega328.tc2_reg = tc2_reg();
	setup_atmega328.tc2_gcontrol_reg = tc_gcontrol_reg();
	setup_atmega328.tc2_iflag_reg = tc_iflag_reg();
	setup_atmega328.tc2_imask_reg = tc_imask_reg();
	setup_atmega328.tc2_compare_reg = tc2_compare_reg();
	#if defined(_TIMER2_MODULE_)
		setup_atmega328.tc2_enable = tc2_enable;
		setup_atmega328.tc2 = tc2();
	#endif
	/***TWI***/
	setup_atmega328.twi_reg = twi_reg();
	#if defined(_TWI_MODULE_)
		setup_atmega328.twi_enable = twi_enable;
		setup_atmega328.twi = twi();
	#endif
	/***USART***/
	setup_atmega328.usart0_reg = usart0_reg();
	#if defined(_USART0_MODULE_)
		setup_atmega328.usart0_enable = usart0_enable;
	#endif
	/***WDT***/
	setup_atmega328.wdt_reg = wdt_reg();
	/*** Pointer Function***/
	setup_atmega328.Clock_Prescaler_Select = Atmega328ClockPrescalerSelect;
	setup_atmega328.Move_Interrupts_To_Boot = Atmega328MoveInterruptsToBoot;
	
	return setup_atmega328;
}

ATMEGA328* atmega328(void){ return &setup_atmega328; }

/******
1º Sequence
2º Scope
3º Pointer and Variable
4º Casting
******/

/*** EOF ***/

