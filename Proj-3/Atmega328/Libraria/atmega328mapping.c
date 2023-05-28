/********************************************************************
	ATMEGA 328 MAPPING
Author: Sergio Manuel Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: Atmega328 by ETT ET-BASE
Date: 13052023
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
uint16_t Atmega328_ReadHLByte(HighLowByte reg);
uint16_t Atmega328_ReadLHByte(HighLowByte reg);
HighLowByte Atmega328_WriteHLByte(uint16_t val);
HighLowByte Atmega328_WriteLHByte(uint16_t val);
uint16_t Atmega328_SwapByte(uint16_t num);
uint8_t Atmega328_ByteMask(uint8_t target, uint8_t mask);
void Atmega328_ByteSet(uint8_t* target, uint8_t set);
void Atmega328_ByteClear(uint8_t* target, uint8_t clear);
uint8_t Atmega328_ByteShiftright(uint8_t target, uint8_t shift);
uint8_t Atmega328_ByteShiftleft(uint8_t target, uint8_t shift);

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
	// CPU
	ret.cpu.reg = (Atmega328CPURegister_TypeDef*) Atmega328CPURegister_Address;
	ret.cpu.gpio = (Atmega328CpuGeneralPurposeIoRegister_TypeDef*) Atmega328CpuGeneralPurposeIoRegister_Address;
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
	ret.tc1.gcr = (Atmega328TimerGeneralControlRegister_TypeDef*) Atmega328TimerGeneralControlRegister_Address;
	ret.tc1.iflag = (Atmega328TimerInterruptFlag_TypeDef*) Atmega328TimerInterruptFlag_Address;
	ret.tc1.imask = (Atmega328TimerMask_TypeDef*) Atmega328TimerMask_Address;
	ret.tc1.comp = (Atmega328TimerCompareRegister1_TypeDef*) Atmega328TimerCompareRegister1_Address;
	#if defined(_ATMEGA328TIMER_H_)
		ret.tc1.enable = TIMER_COUNTER1enable;
		ret.tc1.compoutmodeA = TIMER_COUNTER1_compoutmodeA;
		ret.tc1.compoutmodeB = TIMER_COUNTER1_compoutmodeB;
		ret.tc1.compareA = TIMER_COUNTER1_compareA;
		ret.tc1.compareB = TIMER_COUNTER1_compareB;
		ret.tc1.start = TIMER_COUNTER1_start;
		ret.tc1.stop = TIMER_COUNTER1_stop;
	#endif
	// TC0
	ret.tc0.reg = (Atmega328TimerCounter0_TypeDef*) Atmega328TimerCounter0_Address;
	ret.tc0.gcr = (Atmega328TimerGeneralControlRegister_TypeDef*) Atmega328TimerGeneralControlRegister_Address;
	ret.tc0.iflag = (Atmega328TimerInterruptFlag_TypeDef*) Atmega328TimerInterruptFlag_Address;
	ret.tc0.imask = (Atmega328TimerMask_TypeDef*) Atmega328TimerMask_Address;
	ret.tc0.comp = (Atmega328TimerCompareRegister0_TypeDef*) Atmega328TimerCompareRegister0_Address;
	#if defined(_ATMEGA328TIMER_H_)
		ret.tc0.enable = TIMER_COUNTER0enable;
		ret.tc0.compoutmodeA = TIMER_COUNTER0_compoutmodeA;
		ret.tc0.compoutmodeB = TIMER_COUNTER0_compoutmodeB;
		ret.tc0.compareA = TIMER_COUNTER0_compareA;
		ret.tc0.compareB = TIMER_COUNTER0_compareB;
		ret.tc0.start = TIMER_COUNTER0_start;
		ret.tc0.stop = TIMER_COUNTER0_stop;
	#endif
	// TC2
	ret.tc2.reg = (Atmega328TimerCounter2_TypeDef*) Atmega328TimerCounter2_Address;
	ret.tc2.gcr = (Atmega328TimerGeneralControlRegister_TypeDef*) Atmega328TimerGeneralControlRegister_Address;
	ret.tc2.iflag = (Atmega328TimerInterruptFlag_TypeDef*) Atmega328TimerInterruptFlag_Address;
	ret.tc2.imask = (Atmega328TimerMask_TypeDef*) Atmega328TimerMask_Address;
	ret.tc2.comp = (Atmega328TimerCompareRegister2_TypeDef*) Atmega328TimerCompareRegister2_Address;
	#if defined(_ATMEGA328TIMER_H_)
		ret.tc2.enable = TIMER_COUNTER2enable;
		ret.tc2.compoutmodeA = TIMER_COUNTER2_compoutmodeA;
		ret.tc2.compoutmodeB = TIMER_COUNTER2_compoutmodeB;
		ret.tc2.compareA = TIMER_COUNTER2_compareA;
		ret.tc2.compareB = TIMER_COUNTER2_compareB;
		ret.tc2.start = TIMER_COUNTER2_start;
		ret.tc2.stop = TIMER_COUNTER2_stop;
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
	// func
	ret.readhlbyte = Atmega328_ReadHLByte;
	ret.readlhbyte = Atmega328_ReadLHByte;
	ret.writehlbyte = Atmega328_WriteHLByte;
	ret.writelhbyte = Atmega328_WriteLHByte;
	ret.swapbyte = Atmega328_SwapByte;
	ret.byte_mask = Atmega328_ByteMask;
	ret.byte_set = Atmega328_ByteSet;
	ret.byte_clear = Atmega328_ByteClear;
	ret.byte_shiftright = Atmega328_ByteShiftright;
	ret.byte_shiftleft = Atmega328_ByteShiftleft;
	return ret;
}

// COMMON
uint16_t Atmega328_ReadHLByte(HighLowByte reg)
{
	return (reg.H << 8) | reg.L;
}

uint16_t Atmega328_ReadLHByte(HighLowByte reg)
{
	return (reg.L << 8) | reg.H;
}

HighLowByte Atmega328_WriteHLByte(uint16_t val) // AVR normal little endian
{
	HighLowByte reg; reg.H = (val >> 8); reg.L = val;
	return reg;
}

HighLowByte Atmega328_WriteLHByte(uint16_t val)
{
	HighLowByte reg; reg.L = (val >> 8); reg.H = val;
	return reg;
}

uint16_t Atmega328_SwapByte(uint16_t num)
{
	uint16_t tp;
	tp = (num << 8);
	return (num >> 8) | tp;
}

uint8_t Atmega328_ByteMask(uint8_t target, uint8_t mask)
{
	return target & mask;
}

void Atmega328_ByteSet(uint8_t* target, uint8_t set)
{
	*target |= set;
}

void Atmega328_ByteClear(uint8_t* target, uint8_t clear)
{
	*target &= ~clear;
}

uint8_t Atmega328_ByteShiftright(uint8_t target, uint8_t shift)
{
	return target >> shift;
}

uint8_t Atmega328_ByteShiftleft(uint8_t target, uint8_t shift)
{
	return target << shift;
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

