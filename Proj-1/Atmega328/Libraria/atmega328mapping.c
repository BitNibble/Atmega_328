/********************************************************************
	ATMEGA 328 MAPPING
Author: Sergio Manuel Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: Atmega328 by ETT ET-BASE
Date: 07122022
Comment:
	Virtual Image Atmega 328 mapping and linking.
*********************************************************************/
/*** File Library ***/
#include "atmega328mapping.h"

/*** File Define & Macro ***/
// STATIC RAM
#define Atmega328InterruptVectors_Address 0x0100

/***File Variable***/
ATMEGA328 ret;

/***File Header***/
uint16_t ReadHLByte(HighLowByte reg);
uint16_t ReadLHByte(HighLowByte reg);
HighLowByte WriteHLByte(uint16_t val);
HighLowByte WriteLHByte(uint16_t val);
uint16_t SwapByte(uint16_t num);

/*** File Procedure & Function ***/
ATMEGA328 ATMEGA328enable(void){
	// Assign
	// GPWR
	ret.gpwr.reg = (Atmega328GPWR_TypeDef*) Atmega328GPWR_Address;
	// AC
	ret.ac.reg = (Atmega328AnalogComparator_TypeDef*) Atmega328AnalogComparator_Address;
	// ADC
	ret.adc.reg = (Atmega328AnalogToDigitalConverter_TypeDef*) Atmega328AnalogToDigitalConverter_Address;
	#if defined(_ATMEGA328ANALOG_H_)
		ret.adc.enable = ANALOGenable;
	#endif
	ret.cpu.reg = (Atmega328CPURegister_TypeDef*) Atmega328CPURegister_Address;
	// EEPROM
	ret.eeprom.reg = (Atmega328Eeprom_TypeDef*) Atmega328Eeprom_Address;
	#if defined(_ATMEGAEEPROM_H_)
		ret.eeprom.enable = EEPROMenable;
	#endif
	// EXINT
	ret.exint.reg = (Atmega328ExternalInterrupts_TypeDef*) Atmega328ExternalInterrupts_Address;
	#if defined(_ATMEGA328INTERRUPT_H_)
		ret.exint.enable = INTERRUPTenable;
	#endif
	// PORTB
	ret.portb.reg = (Atmega328PORTB_TypeDef*) Atmega328PORTB_Address;
	// PORTC
	ret.portc.reg = (Atmega328PORTC_TypeDef*) Atmega328PORTC_Address;
	// PORTD
	ret.portd.reg = (Atmega328PORTD_TypeDef*) Atmega328PORTD_Address;
	// SPI
	ret.spi.reg = (Atmega328SerialPeripherialInterface_TypeDef*) Atmega328SerialPeripherialInterface_Address;
	#if defined(_ATMEGA328SPI_H_)
		ret.spi.enable = SPIenable;
	#endif
	// TC1
	ret.tc1.reg = (Atmega328TimerCounter1_TypeDef*) Atmega328TimerCounter1_Address;
	#if defined(_ATMEGA328TIMER_H_)
		ret.tc1.enable = TIMER_COUNTER1enable;
	#endif
	// TC0
	ret.tc0.reg = (Atmega328TimerCounter0_TypeDef*) Atmega328TimerCounter0_Address;
	#if defined(_ATMEGA328TIMER_H_)
		ret.tc0.enable = TIMER_COUNTER0enable;
	#endif
	// TC2
	ret.tc2.reg = (Atmega328TimerCounter2_TypeDef*) Atmega328TimerCounter2_Address;
	#if defined(_ATMEGA328TIMER_H_)
		ret.tc2.enable = TIMER_COUNTER2enable;
	#endif
	// TWI
	ret.twi.reg = (Atmega328TwoWireSerialInterface_TypeDef*) Atmega328TwoWireSerialInterface_Address;
	#if defined(_ATMEGA328TWI_H_)
		ret.twi.enable = TWIenable;
	#endif
	// USART
	ret.usart.reg = (Atmega328Usart_TypeDef*) Atmega328Usart_Address;
	#if defined(_ATMEGA328UART_H_)
		ret.usart.enable = UARTenable;
	#endif
	// WDT
	ret.wdt.reg = (Atmega328WatchdogTimer_TypeDef*) Atmega328WatchdogTimer_Address;
	// Static RAM
	// ISR
	ret.isr.reg = (Atmega328InterruptVectors_TypeDef*) Atmega328InterruptVectors_Address;
	// func
	ret.readhlbyte = ReadHLByte;
	ret.readlhbyte = ReadLHByte;
	ret.writehlbyte = WriteHLByte;
	ret.writelhbyte = WriteLHByte;
	ret.swapbyte = SwapByte;
	return ret;
}

// COMMON
uint16_t ReadHLByte(HighLowByte reg)
{
	return (reg.H << 8) | reg.L;
}

uint16_t ReadLHByte(HighLowByte reg)
{
	return (reg.L << 8) | reg.H;
}

HighLowByte WriteHLByte(uint16_t val) // AVR normal little endian
{
	HighLowByte reg; reg.H = (val >> 8); reg.L = val;
	return reg;
}

HighLowByte WriteLHByte(uint16_t val)
{
	HighLowByte reg; reg.L = (val >> 8); reg.H = val;
	return reg;
}

uint16_t SwapByte(uint16_t num)
{
	uint16_t tp;
	tp = (num << 8);
	return (num >> 8) | tp;
}

/*** File Interrupt ***/
// ISR(RESET_vect){}
// ISR(INT0_vect){}
// ISR(INT1_vect){}
// ISR(PCINT0_vect){}
// ISR(PCINT1_vect){}
// ISR(PCINT2_vect){}
// ISR(WDT_vect){}
// ISR(TIMER2_COMPA_vect){}
// ISR(TIMER2_COMPB_vect){}
// ISR(TIMER2_OVF_vect){}
// ISR(TIMER1_CAPT_vect){}
// ISR(TIMER1_COMPA_vect){}
// ISR(TIMER1_COMPB_vect){}
// ISR(TIMER1_OVF_vect){}
// ISR(TIMER0_COMPA_vect){}
// ISR(TIMER0_COMPB_vect){}
// ISR(TIMER0_OVF_vect){}
// ISR(SPI_STC_vect){}
// ISR(USART_RX_vect){}
// ISR(USART_UDRE_vect){}
// ISR(USART_TX_vect){}
// ISR(ADC_vect){}
// ISR(EE_READY_vect){}
// ISR(ANALOG_INTERRUPT)
// ISR(ANALOG_COMP_vect){}
// ISR(TWI_vect){}
// ISR(SPM_READY_vect){}

// Experiment A
//ISR(TIMER2_COMPA_vect){if(timer2_compa)timer2_compa();}
//ISR(TIMER2_COMPB_vect){if(timer2_compb)timer2_compb();}
//ISR(TIMER2_OVF_vect){if(timer2_ovf)timer2_ovf();}
//ISR(TIMER1_CAPT_vect){if(timer1_capt)timer1_capt();}
//ISR(TIMER1_COMPA_vect){if(timer1_compa)timer1_compa();}
//ISR(TIMER1_COMPB_vect){if(timer1_compb)timer1_compb();}
//ISR(TIMER1_OVF_vect){if(timer1_ovf)timer1_ovf();}
//ISR(TIMER0_COMPA_vect){if(timer0_compa)timer0_compa();}
//ISR(TIMER0_COMPB_vect){if(timer0_compb)timer0_compb();}
//ISR(TIMER0_OVF_vect){if(timer0_ovf)timer0_ovf();}

/***EOF***/

/******
1º Sequence
2º Scope
3º Pointer and Variable
4º Casting
******/

