/*********************************************************
	ATMEGA 328 MAPPING
Author: Sergio Manuel Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: Atmega328 by ETT ET-BASE
Date: 07122022
Comment:
	Virtual Image Atmega 328 mapping.
**********************************************************/
/*** File Library ***/
#include "atmega328mapping.h"

/*** File Define & Macro ***/
#define GPWRaddr 0x0000
#define AnalogComparator 0x0050
#define AnalogToDigitalConverter 0x0078
#define CPURegister 0x003E
#define Eeprom 0x003F
#define ExternalInterrupts 0x003B
#define PORTBaddr 0x0023
#define PORTCaddr 0x0026
#define PORTDaddr 0x0029
#define SerialPeripherialInterface 0x004C
#define TimerCounter1 0x0036
#define TimerCounter0 0X0035
#define TimerCounter2 0x0037
#define TwoWireSerialInterface 0x00B8
#define Usart 0x00C0
#define WatchdogTimer 0x0060
// FLASH
#define InterruptVectors 0x0000

/***File Header***/
uint16_t ReadHLByte(HighLowByte reg);
uint16_t ReadLHByte(HighLowByte reg);
HighLowByte WriteHLByte(uint16_t val);
HighLowByte WriteLHByte(uint16_t val);
uint16_t SwapByte(uint16_t num);

/*** File Procedure & Function ***/
ATMEGA328 ATMEGA328enable(void){ 
	ATMEGA328 ret;
	// Assign
	ret.gpwr.reg = (Atmega328GPWR_TypeDef*) GPWRaddr;
	// AC
	ret.ac.reg = (Atmega328AnalogComparator_TypeDef*) AnalogComparator;
	// ADC
	ret.adc.reg = (Atmega328AnalogToDigitalConverter_TypeDef*) AnalogToDigitalConverter;
	#if defined(_ATMEGA328ANALOG_H_)
		ret.adc.enable = ANALOGenable;
	#endif
	ret.cpu.reg = (Atmega328CPURegister_TypeDef*) CPURegister;
	// EEPROM
	ret.eeprom.reg = (Atmega328Eeprom_TypeDef*) Eeprom;
	#if defined(_EEPROM_H_)
		ret.eeprom.enable = EEPROMenable;
	#endif
	// EXINT
	ret.exint.reg = (Atmega328ExternalInterrupts_TypeDef*) ExternalInterrupts;
	#if defined(_ATMEGA328INTERRUPT_H_)
		ret.exint.enable = INTERRUPTenable;
	#endif
	ret.portb.reg = (Atmega328PORTB_TypeDef*) PORTBaddr;
	ret.portc.reg = (Atmega328PORTC_TypeDef*) PORTCaddr;
	ret.portd.reg = (Atmega328PORTD_TypeDef*) PORTDaddr;
	// SPI
	ret.spi.reg = (Atmega328SerialPeripherialInterface_TypeDef*) SerialPeripherialInterface;
	#if defined(_ATMEGA328SPI_H_)
		ret.spi.enable = SPIenable;
	#endif
	// TC1
	ret.tc1.reg = (Atmega328TimerCounter1_TypeDef*) TimerCounter1;
	#if defined(_ATMEGA328TIMER_H_)
		ret.tc1.enable = TIMER_COUNTER1enable;
	#endif
	// TC0
	ret.tc0.reg = (Atmega328TimerCounter0_TypeDef*) TimerCounter0;
	#if defined(_ATMEGA328TIMER_H_)
		ret.tc0.enable = TIMER_COUNTER0enable;
	#endif
	// TC2
	ret.tc2.reg = (Atmega328TimerCounter2_TypeDef*) TimerCounter2;
	#if defined(_ATMEGA328TIMER_H_)
		ret.tc2.enable = TIMER_COUNTER2enable;
	#endif
	// TWI
	ret.twi.reg = (Atmega328TwoWireSerialInterface_TypeDef*) TwoWireSerialInterface;
	#if defined(_ATMEGA328TWI_H_)
		ret.twi.enable = TWIenable;
	#endif
	// USART
	ret.usart.reg = (Atmega328Usart_TypeDef*) Usart;
	#if defined(_ATMEGA328UART_H_)
		ret.usart.enable = UARTenable;
	#endif
	ret.wdt.reg = (Atmega328WatchdogTimer_TypeDef*) WatchdogTimer;
	// FLASH
	// ret.intvect.isr = (Atmega328InterruptVectors_TypeDef*) InterruptVectors;
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

HighLowByte WriteHLByte(uint16_t val)
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
// ISR(ANALOG_COMP_vect){}
// ISR(TWI_vect){}
// ISR(SPM_READY_vect){}

/***EOF***/

/******
1º Sequence
2º Scope
3º Pointer and Variable
******/

