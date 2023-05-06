/************************************************************************
	ATMEGA 328 REGISTERS
Author: Sergio Manuel Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: Atmega328 by ETT ET-BASE
Date: 03122022
Comment: 
	Virtual Image Atmega 328.
************************************************************************/
#ifndef _ATMEGA328_H_
	#define _ATMEGA328_H_

/*** Global Library ***/
#include <inttypes.h>

/*** Global Constant & Macro ***/
#define Atmega328GPWR_Address 0x0000
#define Atmega328AnalogComparator_Address 0x0050
#define Atmega328AnalogToDigitalConverter_Address 0x0078
#define Atmega328CPURegister_Address 0x003E
#define Atmega328Eeprom_Address 0x003F
#define Atmega328ExternalInterrupts_Address 0x003B
#define Atmega328PORTB_Address 0x0023
#define Atmega328PORTC_Address 0x0026
#define Atmega328PORTD_Address 0x0029
#define Atmega328SerialPeripherialInterface_Address 0x004C
#define Atmega328TimerCounter1_Address 0x0036
#define Atmega328TimerCounter0_Address 0x0035
#define Atmega328TimerCounter2_Address 0x0037
#define Atmega328TwoWireSerialInterface_Address 0x00B8
#define Atmega328Usart_Address 0x00C0
#define Atmega328WatchdogTimer_Address 0x0060

/*** Global Variable ***/
// Low Byte High Byte
typedef struct { // little endian
	uint8_t L; // Lower address
	uint8_t H; // Higher address
} HighLowByte;

/*** MAIN HARDWARE LAYER ***/
// GPWR
typedef struct {
	uint8_t r0;
	uint8_t r1;
	uint8_t r2;
	uint8_t r3;
	uint8_t r4;
	uint8_t r5;
	uint8_t r6;
	uint8_t r7;
	uint8_t r8;
	uint8_t r9;
	uint8_t r10;
	uint8_t r11;
	uint8_t r12;
	uint8_t r13;
	uint8_t r14;
	uint8_t r15;
	uint8_t r16;
	uint8_t r17;
	uint8_t r18;
	uint8_t r19;
	uint8_t r20;
	uint8_t r21;
	uint8_t r22;
	uint8_t r23;
	uint8_t r24;
	uint8_t r25;
	HighLowByte X;
	HighLowByte Y;
	HighLowByte Z;
} Atmega328GPWR_TypeDef;

// Analog Comparator (AC)
typedef struct {
	uint8_t acsr; // 0x50
	uint8_t fill[46]; // (0x7F - 0x50) - 1
	uint8_t didr1; // 0x7F
} Atmega328AnalogComparator_TypeDef;

// Analog to Digital Converter (ADC)
typedef struct {
	HighLowByte adc; // 0x78 0x79
	uint8_t adcsra; // 0x7A
	uint8_t adscrb; // 0x7B
	uint8_t admux; // 0x7C
	uint8_t fill; // (0x7E - 0x7C) - 1
	uint8_t didr0; // 0x7E
} Atmega328AnalogToDigitalConverter_TypeDef;

// CPU Register (CPU)
typedef struct {
	uint8_t gpior0; // 0x3E
	uint8_t fill1[11]; // (0x4A - 0x3E) - 1
	uint8_t gpior1; // 0x4A
	uint8_t gpior2; // 0x4B
	uint8_t fill2[7]; // (0x53 - 0x4B) - 1
	uint8_t smcr; // 0x53
	uint8_t mcusr; // 0x54
	uint8_t mcucr; // 0x55
	uint8_t fill3; // (0x57 - 0x55) - 1
	uint8_t spmcsr; // 0x57
	uint8_t fill4[5]; // (0x5D - 0x57) - 1
	HighLowByte sp; // 0x5D 0x5E
	uint8_t sreg; // 0x5F
	uint8_t fill5; // (0x61 - 0x5F) - 1
	uint8_t clkpr; // 0x61
	uint8_t fill6[2]; // (0x64 - 0x61) - 1
	uint8_t prr; // 0x64
	uint8_t fill7; // (0x66 - 0x64) - 1
	uint8_t osccal; // 0x66
} Atmega328CPURegister_TypeDef;

// EEPROM (EEPROM)
typedef struct {
	uint8_t eecr; // 0x3F
	uint8_t eedr; // 0x40
	uint16_t eear; // 0x41
} Atmega328Eeprom_TypeDef;

// External Interrupts (EXINT)
typedef struct {
	uint8_t pcifr; // 0x3B
	uint8_t eifr; // 0x3C
	uint8_t eimsk; // 0x3D
	uint8_t fill1[42]; // (0x68 - 0x3D) - 1
	uint8_t pcicr; // 0x68
	uint8_t eicra; // 0x69
	uint8_t fill2; // (0x6B - 0x69) - 1
	uint8_t pcmsk0; // 0x6B
	uint8_t pcmsk1; // 0x6C
	uint8_t pcmsk2; // 0x6D
} Atmega328ExternalInterrupts_TypeDef;

// I/O Port (PORTB)
typedef struct {
	uint8_t pin; // 0x23
	uint8_t ddr; // 0x24
	uint8_t port; //0x25
} Atmega328PORTB_TypeDef;

// I/O Port (PORTC)
typedef struct {
	uint8_t pin; // 0x26
	uint8_t ddr; // 0x27
	uint8_t port; // 0x28
} Atmega328PORTC_TypeDef;

// I/O Port (PORTD)
typedef struct {
	uint8_t pin; // 0x29
	uint8_t ddr; // 0x2A
	uint8_t port; // 0x2B
} Atmega328PORTD_TypeDef;

// Serial Peripheral Interface (SPI)
typedef struct {
	uint8_t spcr; // 0x4C
	uint8_t spsr; // 0x4D
	uint8_t spdr; // 0x4E
} Atmega328SerialPeripherialInterface_TypeDef;

// Timer/Counter, 16-bit (TC1)
typedef struct {
	uint8_t tifr1; // 0x36
	uint8_t fill1[12]; // (0x43 - 0x36) - 1
	uint8_t gtccr; // 0x43
	uint8_t fill2[43]; // (0x6F - 0x43) - 1
	uint8_t timsk1; // 0x6F
	uint8_t fill3[16]; // (0x80 - 0x6F) - 1
	uint8_t tccr1a; // 0x80
	uint8_t tccr1b; // 0x81
	uint8_t tccr1c; // 0x82
	uint8_t fill4; // (0x84 - 0x82) - 1
	HighLowByte tcnt1; // 0x84 0x85
	HighLowByte icr1; // 0x86 0x87
	HighLowByte ocr1a; // 0x88 0x89
	HighLowByte ocr1b; // 0x8A 0x8B
} Atmega328TimerCounter1_TypeDef;

// Timer/Counter, 8-bit A sync (TC0)
typedef struct {
	uint8_t tifr0; // 0x35
	uint8_t fill1[13]; // (0x43 - 0x35) - 1
	uint8_t gtccr; // 0x43
	uint8_t tccr0a; // 0x44
	uint8_t tccr0b; // 0x45
	uint8_t tcnt0; // 0x46
	uint8_t ocr0a; // 0x47
	uint8_t ocr0b; // 0x48
	uint8_t fill2[37]; // (0x6E - 0x48) - 1
	uint8_t timsk0; // 0x6E
} Atmega328TimerCounter0_TypeDef;

// Timer/Counter, 8-bit (TC2)
typedef struct {
	uint8_t tifr2; // 0x37
	uint8_t fill1[11]; // (0x43 - 0x37) - 1
	uint8_t gtccr; // 0x43
	uint8_t fill2[44]; // (0x70 - 0x43) - 1
	uint8_t timsk2; // 0x70
	uint8_t fill3[63]; // (0xB0 - 0x70) - 1
	uint8_t tccr2a; // 0xB0
	uint8_t tccr2b; // 0xB1
	uint8_t tcnt2; // 0xB2
	uint8_t ocr2a; // 0xB3
	uint8_t ocr2b; // 0xB4
	uint8_t fill4; // (0xB6 - 0xB4) - 1
	uint8_t assr; // 0xB6
} Atmega328TimerCounter2_TypeDef;

// Two Wire Serial Interface (TWI)
typedef struct {
	uint8_t twbr; // 0xB8
	uint8_t twsr; // 0xB9
	uint8_t twar; // 0xBA
	uint8_t twdr; // 0xBB
	uint8_t twcr; // 0xBC
	uint8_t twamr; // 0xBD
} Atmega328TwoWireSerialInterface_TypeDef;

// USART (USART0)
typedef struct {
	uint8_t ucsr0a; // 0xC0
	uint8_t ucsr0b; // 0xC1
	uint8_t ucsr0c; // 0xC2
	uint8_t fill; // (0xC4 - 0xC2) - 1
	HighLowByte ubrr0; // 0xC4 0xC5
	uint8_t udr0; // 0xC6
} Atmega328Usart_TypeDef;

// Watchdog Timer (WDT)
typedef struct {
	uint8_t wdtcsr; // 0x60
} Atmega328WatchdogTimer_TypeDef;

/*** STATIC RAM ***/
// Interrupt Vectors (ISR)
typedef struct { // SRAM START = 0x0100 END = 0x0877 atmega328
	HighLowByte RESET_vect; // 0x0000
	HighLowByte INT0_vect; // 0x0002
	HighLowByte INT1_vect; // 0x0004
	HighLowByte PCINT0_vect; // 0x0006
	HighLowByte PCINT1_vect; // 0x0008
	HighLowByte PCINT2_vect; // 0x000A
	HighLowByte WDT_vect; // 0x000C
	HighLowByte TIMER2_COMPA_vect; // 0x000E
	HighLowByte TIMER2_COMPB_vect; // 0x0010
	HighLowByte TIMER2_OVF_vect; // 0x0012
	HighLowByte TIMER1_CAPT_vect; // 0x0014
	HighLowByte TIMER1_COMPA_vect; // 0x0016
	HighLowByte TIMER1_COMPB_vect; // 0x0018
	HighLowByte TIMER1_OVF_vect; // 0x0001A
	HighLowByte TIMER0_COMPA_vect; // 0x001C
	HighLowByte TIMER0_COMPB_vect; // 0x001E
	HighLowByte TIMER0_OVF_vect; // 0x0020
	HighLowByte SPI_STC_vect; // 0x0022
	HighLowByte USART_RX_vect; // 0x0024
	HighLowByte USART_UDRE_vect; // 0x0026
	HighLowByte USART_TX_vect; // 0x0028
	HighLowByte ADC_vect; // 0x002A
	HighLowByte EE_READY_vect; // 0x002C
	HighLowByte ANALOG_COMP_vect; // 0x002E
	HighLowByte TWI_vect; // 0x0030
	HighLowByte SPM_READY_vect; // 0x0032
} Atmega328InterruptVectors_TypeDef;

#endif

/***EOF***/
/***
Notes:
The Reset button is an interrupt [address 0 rjump] that jumps to the main() location.


***/
