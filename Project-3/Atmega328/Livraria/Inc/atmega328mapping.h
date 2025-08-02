/********************************************************************
	ATMEGA 328 MAPPING
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: Atmega328 by ETT ET-BASE
Update:   01/01/2024
*********************************************************************/
/****** Comment: 
	Virtual Image Atmega 328 mapping.
	NB:
	- This Header file should be the first to be placed
*********************************************************************/
#ifndef _ATMEGA328MAPPING_H_
	#define _ATMEGA328MAPPING_H_

/*** Global Library ***/
#include "atmega328.h"

/*********************************************************/
/****************** Include Switches  ********************/
/*********************************************************/
// User may Comment out if not in use
// MODULES
#define _ANALOG_MODULE_
#define _EEPROM_MODULE_
#define _INTERRUPT_MODULE_
#define _TIMER0_MODULE_
#define _TIMER1_MODULE_
#define _TIMER2_MODULE_
#define _TWI_MODULE_
//#define _SPI_MODULE_
#define _USART0_MODULE_
/*********************************************************/
/******************* Hardware Includes *******************/
/*********************************************************/
// MODULES
#ifdef _ANALOG_MODULE_
	#include "atmega328analog.h"
//#else
//	#warning "NO ANALOG MODULE"
#endif
#ifdef _EEPROM_MODULE_
	#include "atmegaeeprom.h"
//#else
//	#warning "NO EEPROM MODULE"
#endif
#ifdef _INTERRUPT_MODULE_
	#include "atmega328interrupt.h"
//#else
//	#warning "NO INTERRUPT MODULE"
#endif
#ifdef _TIMER0_MODULE_
	#include "atmega328timer0.h"
//#else
//	#warning "NO TIMER MODULE"
#endif
#ifdef _TIMER1_MODULE_
	#include "atmega328timer1.h"
//#else
//	#warning "NO TIMER MODULE"
#endif
#ifdef _TIMER2_MODULE_
	#include "atmega328timer2.h"
//#else
//	#warning "NO TIMER MODULE"
#endif
#ifdef _TWI_MODULE_
	#include "atmega328twi.h"
//#else
//	#warning "NO TWI MODULE"
#endif
#ifdef _SPI_MODULE_
	#include "atmega328spi.h"
//#else
//	#warning "NO SPI MODULE"
#endif
#ifdef _USART0_MODULE_
	#include "atmega328_usart0.h"
//#else
//	#warning "NO UART MODULE"
#endif
/*******************************************************************/
/************************* ATMEGA 328 IMAGE ************************/
/*************************** Third Layer ***************************/
/*******************************************************************/
typedef struct {
	/***GPWR***/
	Atmega328GPWR_TypeDef* gpwr_reg;
	/***AC***/
	Atmega328AnalogComparator_TypeDef* ac_reg;
	Atmega328AnalogComparatorDid_TypeDef* ac_did_reg;
	/***ADC***/
	Atmega328AnalogToDigitalConverter_TypeDef* adc_reg;
	#ifdef _ANALOG_MODULE_
		ADC0 (*adc_enable)( uint8_t Vreff, uint8_t Divfactor, int n_channel, ... );
		ADC0* adc;
	#endif
	/***CPU***/
	Atmega328CPURegister_TypeDef* cpu_reg;
	Atmega328CpuGeneralPurposeIoRegister_TypeDef* cpu_gpio012_reg;
	/***EEPROM***/
	Atmega328Eeprom_TypeDef* eeprom_reg;
	#ifdef _EEPROM_MODULE_
		EEPROM0 (*eeprom_enable)(void);
		EEPROM0* eeprom;
	#endif
	/***EXINT***/
	Atmega328ExternalInterrupt_TypeDef* exint_reg;
	Atmega328ExternalInterruptFlag_TypeDef* exint_iflag_reg;
	Atmega328ExternalInterruptMask_TypeDef* exint_imask_reg;
	Atmega328ExternalInterruptPinChangeMask_TypeDef* exint_pcmask_reg;
	#ifdef _INTERRUPT_MODULE_
		EXINT0 (*exint_enable)(void);
		EXINT0* exint;
	#endif
	/***PORTB***/
	Atmega328PORTB_TypeDef* gpiob_reg;
	/***PORTC***/
	Atmega328PORTC_TypeDef* gpioc_reg;
	/***PORTD***/
	Atmega328PORTD_TypeDef* gpiod_reg;
	/***SPI***/
	Atmega328SerialPeripherialInterface_TypeDef* spi_reg;
	#ifdef _SPI_MODULE_
		SPI0 (*spi_enable)(uint8_t master_slave_select, uint8_t data_order,  uint8_t data_modes, uint8_t prescaler);
		SPI0* spi;
	#endif
	/***TC1***/
	Atmega328TimerCounter1_TypeDef* tc1_reg;
	Atmega328TimerGeneralControlRegister_TypeDef* tc1_gcontrol_reg;
	Atmega328TimerInterruptFlag_TypeDef* tc1_iflag_reg;
	Atmega328TimerInterruptMask_TypeDef* tc1_imask_reg;
	Atmega328TimerCompareRegister1_TypeDef* tc1_compare_reg;
	#ifdef _TIMER1_MODULE_
		TC1 (*tc1_enable)(unsigned char wavegenmode, unsigned char interrupt);
		TC1* tc1;
	#endif
	/***TC0***/
	Atmega328TimerCounter0_TypeDef* tc0_reg;
	Atmega328TimerGeneralControlRegister_TypeDef* tc0_gcontrol_reg;
	Atmega328TimerInterruptFlag_TypeDef* tc0_iflag_reg;
	Atmega328TimerInterruptMask_TypeDef* tc0_imask_reg;
	Atmega328TimerCompareRegister0_TypeDef* tc0_compare_reg;
	#ifdef _TIMER0_MODULE_
		TC0 (*tc0_enable)( unsigned char wavegenmode, unsigned char interrupt );
		TC0* tc0;
	#endif
	/***TC2***/
	Atmega328TimerCounter2_TypeDef* tc2_reg;
	Atmega328TimerGeneralControlRegister_TypeDef* tc2_gcontrol_reg;
	Atmega328TimerInterruptFlag_TypeDef* tc2_iflag_reg;
	Atmega328TimerInterruptMask_TypeDef* tc2_imask_reg;
	Atmega328TimerCompareRegister2_TypeDef* tc2_compare_reg;
	#ifdef _TIMER2_MODULE_
		TC2 (*tc2_enable)(unsigned char wavegenmode, unsigned char interrupt);
		TC2* tc2;
	#endif
	/***TWI***/
	Atmega328TwoWireSerialInterface_TypeDef* twi_reg;
	#ifdef _TWI_MODULE_
		TWI0 (*twi_enable)(uint8_t atmega_ID, uint8_t prescaler);
		TWI0* twi;
	#endif
	/***USART0***/
	Atmega328Usart0_TypeDef* usart0_reg;
	#ifdef _USART0_MODULE_
		USART0 (*usart0_enable)(uint32_t baudrate, unsigned int FDbits, unsigned int Stopbits, unsigned int Parity );
		USART0* usart0;
	#endif
	/***WDT***/
	Atmega328WatchdogTimer_TypeDef* wdt_reg;
	/***Pointer Function***/
	void (*Clock_Prescaler_Select)(volatile uint8_t prescaler);
	void (*Move_Interrupts_To_Boot)(void);
}ATMEGA328;

ATMEGA328 atmega328_enable(void);
ATMEGA328* atmega328(void);

#endif

/******
1º Sequence
2º Scope
3º Pointer and Variable
4º Casting
******/

/*** EOF ***/

