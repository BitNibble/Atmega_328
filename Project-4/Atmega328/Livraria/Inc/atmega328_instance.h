/************************************************************************
	ATMEGA 328 INSTANCE
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: Atmega328 by ETT ET-BASE
Update:   23092025
************************************************************************/
#ifndef _ATMEGA328_INSTANCE_H_
	#define _ATMEGA328_INSTANCE_H_

/*** Library ***/
#include "atmega328_register.h"

/*****************************/
/**** MAIN HARDWARE LAYER ****/
/*****************************/
// GPWR
typedef volatile struct {
	uint8_t r0; // 0x00
	uint8_t r1; // 0x01
	uint8_t r2; // 0x02
	uint8_t r3; // 0x03
	uint8_t r4; // 0x04
	uint8_t r5; // 0x05
	uint8_t r6; // 0x06
	uint8_t r7; // 0x07
	uint8_t r8; // 0x08
	uint8_t r9; // 0x09
	uint8_t r10; // 0x0A
	uint8_t r11; // 0x0B
	uint8_t r12; // 0x0C
	uint8_t r13; // 0x0D
	uint8_t r14; // 0x0E
	uint8_t r15; // 0x0F
	uint8_t r16; // 0x10
	uint8_t r17; // 0x11
	uint8_t r18; // 0x12
	uint8_t r19; // 0x13
	uint8_t r20; // 0x14
	uint8_t r21; // 0x15
	uint8_t r22; // 0x16
	uint8_t r23; // 0x17
	uint8_t r24; // 0x18
	uint8_t r25; // 0x19
	uint16_t X; // 0x1A 0x1B
	uint16_t Y; // 0x1C 0x1D
	uint16_t Z; // 0x1E 0x1F
} Atmega328GPWR_TypeDef;

// I/O Port (PORTB)
typedef volatile struct {
	PIN_b pin; // 0x23
	DD_rb ddr; // 0x24
	PORT_b port; //0x25
} Atmega328PORTB_TypeDef;

// I/O Port (PORTC)
typedef volatile struct {
	PIN_c pin; // 0x26
	DD_rc ddr; // 0x27
	PORT_c port; // 0x28
} Atmega328PORTC_TypeDef;

// I/O Port (PORTD)
typedef volatile struct {
	PIN_d pin; // 0x29
	DD_rd ddr; // 0x2A
	PORT_d port; // 0x2B
} Atmega328PORTD_TypeDef;

// Timer/Counter 0, 1 and 2 Interrupt Flag
typedef volatile struct {
	TC0_ifr tifr0; // 0x35
	TC1_ifr tifr1; // 0x36
	TC2_ifr tifr2; // 0x37
} Atmega328TimerInterruptFlag_TypeDef;

// External Interrupts Flag (EXINT)
typedef volatile struct {
	EXINT_pcifr pcifr; // 0x3B
	EXINT_ifr eifr; // 0x3C
} Atmega328ExternalInterruptFlag_TypeDef;

// External Interrupts Mask (EXINT)
typedef volatile struct {
	EXINT_imsk eimsk; // 0x3D [eimsk]
} Atmega328ExternalInterruptMask_TypeDef;

// CPU Register Gpio0 (CPU)
typedef volatile struct {
	MCU_gpior0 r0; // 0x3E [gpior0]
} Atmega328CpuGeneralPurposeIoRegister0_TypeDef;

// EEPROM (EEPROM)
typedef volatile struct {
	EEPROM_cr eecr; // 0x3F
	EEPROM_dr eedr; // 0x40
	EEPROM_ar eear; // 0x41
} Atmega328Eeprom_TypeDef;

// TIMER General Control
typedef volatile struct {
	GTC_cr gtccr; // 0x43 [gtccr]
} Atmega328TimerGeneralControlRegister_TypeDef;

// Timer/Counter, 8-bit A sync (TC0)
typedef volatile struct {
	TC0_ifr tifr0; // 0x35
	uint8_t fill1[13]; // (43 - 35) - 1
	GTC_cr gtccr; // 0x43
	TC0_cra tccr0a; // 0x44
	TC0_crb tccr0b; // 0x45
	TC0_nt tcnt0; // 0x46
	TC0_ocra ocr0a; // 0x47
	TC0_ocrb ocr0b; // 0x48
	uint8_t fill2[37]; // (6E - 48) - 1
	TC1_imsk timsk0; // 0x6E
} Atmega328TimerCounter0_TypeDef;

// Timer/Counter, 8-bit A sync Compare (TC0)
typedef volatile struct {
	TC0_ocra ocr0a; // 0x47
	TC0_ocrb ocr0b; // 0x48
} Atmega328TimerCompareRegister0_TypeDef;

// CPU Register Gpio1 (CPU)
typedef volatile struct {
	MCU_gpior1 r1; // 0x4A [gpior1]
} Atmega328CpuGeneralPurposeIoRegister1_TypeDef;

// CPU Register Gpio012 (CPU)
typedef volatile struct {
	MCU_gpior0 r0; // 0x3E
	uint8_t fill[11]; // (0x4A - 0x3E) - 1
	MCU_gpior1 r1; // 0x4A
	MCU_gpior2 r2; // 0x4B
} Atmega328CpuGeneralPurposeIoRegister_TypeDef;

// CPU Register Gpio2 (CPU)
typedef volatile struct {
	MCU_gpior2 r2; // 0x4B [gpior2]
} Atmega328CpuGeneralPurposeIoRegister2_TypeDef;

// Serial Peripheral Interface (SPI)
typedef volatile struct {
	SPI_cr spcr; // 0x4C
	SPI_sr spsr; // 0x4D
	SPI_dr spdr; // 0x4E
} Atmega328SerialPeripherialInterface_TypeDef;

// Analog Comparator (AC)
typedef volatile struct {
	AC_sr acsr; // 0x50 [acsr]
	uint8_t fill[46]; // (0x7F - 0x50) - 1
	AC_didr1 didr1; // 0x7F
} Atmega328AnalogComparator_TypeDef;

// Watchdog Timer (WDT)
typedef volatile struct {
	WDT_csr wdtcsr; // 0x60 [wdtcsr]
} Atmega328WatchdogTimer_TypeDef;

// CPU Register (CPU)
typedef volatile struct {
	MCU_gpior0 gpior0; // 0x3E
	uint8_t fill1[11]; // (0x4A - 0x3E) - 1
	MCU_gpior1 gpior1; // 0x4A
	MCU_gpior2 gpior2; // 0x4B
	uint8_t fill2[7]; // (0x53 - 0x4B) - 1
	MCU_smcr smcr; // 0x53
	MCU_sr mcusr; // 0x54
	MCU_cr mcucr; // 0x55
	uint8_t fill3; // (0x57 - 0x55) - 1
	MCU_spmcsr spmcsr; // 0x57
	uint8_t fill4[5]; // (0x5D - 0x57) - 1
	MCU_sp sp; // 0x5D 0x5E
	MCU_sreg sreg; // 0x5F
	uint8_t fill5; // (0x61 - 0x5F) - 1
	MCU_clkpr clkpr; // 0x61
	uint8_t fill6[2]; // (0x64 - 0x61) - 1
	MCU_prr prr; // 0x64
	uint8_t fill7; // (0x66 - 0x64) - 1
	MCU_osccal osccal; // 0x66
} Atmega328CPURegister_TypeDef;

// External Interrupt (EXINT)
typedef volatile struct {
	EXINT_pcifr pcifr; // 0x3B
	EXINT_ifr eifr; // 0x3C
	EXINT_imsk eimsk; // 0x3D
	uint8_t fill1[42]; // (0x68 - 0x3D) - 1
	EXINT_pcicr pcicr; // 0x68
	EXINT_icra eicra; // 0x69
	uint8_t fill2; // (0x6B - 0x69) - 1
	EXINT_pcmsk0 pcmsk0; // 0x6B
	EXINT_pcmsk1 pcmsk1; // 0x6C
	EXINT_pcmsk2 pcmsk2; // 0x6D
} Atmega328ExternalInterrupt_TypeDef;

// External Interrupt Pin Change Mask (EXINT)
typedef volatile struct {
	EXINT_pcmsk0 pcmsk0; // 0x6B
	EXINT_pcmsk1 pcmsk1; // 0x6C
	EXINT_pcmsk2 pcmsk2; // 0x6D
} Atmega328ExternalInterruptPinChangeMask_TypeDef;

// Timer/Counter 0, 1 and 2 Interrupt Mask
typedef volatile struct {
	TC0_imsk timsk0; // 0x6E
	TC1_imsk timsk1; // 0x6F
	TC2_imsk timsk2; // 0x70
} Atmega328TimerInterruptMask_TypeDef;

// Analog to Digital Converter (ADC)
typedef volatile struct {
	ADC_dr adc; // 0x78 0x79
	ADC_sra adcsra; // 0x7A
	ADC_srb adcsrb; // 0x7B
	ADC_admux admux; // 0x7C
	uint8_t fill; // (0x7E - 0x7C) - 1
	ADC_didr0 didr0; // 0x7E
} Atmega328AnalogToDigitalConverter_TypeDef;

// Analog Comparator Did (AC)
typedef volatile struct {
	ADC_didr0 r0; // 0x7E [didr0]
	AC_didr1 r1; // 0x7F [didr1]
} Atmega328AnalogComparatorDid_TypeDef;

// Timer/Counter, 16-bit (TC1)
typedef volatile struct {
	TC1_ifr tifr1; // 0x36
	uint8_t fill1[12]; // (0x43 - 0x36) - 1
	GTC_cr gtccr; // 0x43
	uint8_t fill2[43]; // (0x6F - 0x43) - 1
	TC1_imsk timsk1; // 0x6F
	uint8_t fill3[16]; // (0x80 - 0x6F) - 1
	TC1_cra tccr1a; // 0x80
	TC1_crb tccr1b; // 0x81
	TC1_crc tccr1c; // 0x82
	uint8_t fill4; // (0x84 - 0x82) - 1
	TC1_nt tcnt1; // 0x84 0x85
	TC1_icr icr1; // 0x86 0x87
	TC1_ocra ocr1a; // 0x88 0x89
	TC1_ocrb ocr1b; // 0x8A 0x8B
} Atmega328TimerCounter1_TypeDef;

// Timer/Counter, 16-bit Compare (TC1)
typedef volatile struct {
	TC1_icr icr1; // 0x86 0x87
	TC1_ocra ocr1a; // 0x88 0x89
	TC1_ocrb ocr1b; // 0x8A 0x8B
} Atmega328TimerCompareRegister1_TypeDef;

// Timer/Counter, 8-bit (TC2)
typedef volatile struct {
	TC2_ifr tifr2; // 0x37
	uint8_t fill1[11]; // (0x43 - 0x37) - 1
	GTC_cr gtccr; // 0x43
	uint8_t fill2[44]; // (0x70 - 0x43) - 1
	TC2_imsk timsk2; // 0x70
	uint8_t fill3[63]; // (0xB0 - 0x70) - 1
	TC2_cra tccr2a; // 0xB0
	TC2_crb tccr2b; // 0xB1
	TC2_nt tcnt2; // 0xB2
	TC2_ocra ocr2a; // 0xB3
	TC2_ocrb ocr2b; // 0xB4
	uint8_t fill4; // (0xB6 - 0xB4) - 1
	TC2_assr assr; // 0xB6
} Atmega328TimerCounter2_TypeDef;

// Timer/Counter, 8-bit Compare (TC2)
typedef volatile struct {
	TC2_ocra ocr2a; // 0xB3
	TC2_ocrb ocr2b; // 0xB4
	uint8_t fill; // (0xB6 - 0xB4) - 1
	TC2_assr assr; // 0xB6
} Atmega328TimerCompareRegister2_TypeDef;

// Two Wire Serial Interface (TWI)
typedef volatile struct {
	TWI_br twbr; // 0xB8
	TWI_sr twsr; // 0xB9
	TWI_ar twar; // 0xBA
	TWI_dr twdr; // 0xBB
	TWI_cr twcr; // 0xBC
	TWI_amr twamr; // 0xBD
} Atmega328TwoWireSerialInterface_TypeDef;

// USART (USART0)
typedef volatile struct {
	USART0_csra ucsr0a; // 0xC0
	USART0_csrb ucsr0b; // 0xC1
	USART0_csrc ucsr0c; // 0xC2
	uint8_t fill; // (0xC4 - 0xC2) - 1
	USART0_brr ubrr0; // 0xC4 0xC5
	USART0_dr udr0; // 0xC6
} Atmega328Usart0_TypeDef;

#endif
/*** EOF ***/



