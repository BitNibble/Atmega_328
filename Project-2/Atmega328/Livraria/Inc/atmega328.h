/************************************************************************
	ATMEGA 328
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: Atmega328 by ETT ET-BASE
Update:   23092025
************************************************************************/
#ifndef _ATMEGA328_H_
	#define _ATMEGA328_H_

/*** Working Frequency ***/
#ifndef F_CPU
	#define F_CPU 8000000UL
#endif

/*** Library ***/
#include <avr/io.h>
#include <avr/boot.h>
#include <avr/fuse.h>
#include <avr/eeprom.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <util/atomic.h>
#include <util/delay.h>

#include "atmega328_instance.h"

/*** Constant & Macro ***/
#define ZERO 0
#define ONE 1
#define TWO 2
#define NIBBLE_BITS 4
#define BYTE_BITS 8
#define WORD_BITS 16
#define DWORD_BITS 32
#define QWORD_BITS 64
#define SRAMSTART 0x0100
#define SRAMEND 0x08FF
// Macros for common operations
#define SET_REG(REG, HBITS)		(REG |= HBITS)
#define CLEAR_REG(REG, HBITS)	(REG &= ~HBITS)
#define READ_BIT(REG, BIT)		((REG >> BIT) & 1)
#define TOGGLE_REG(REG, HBITS)	(REG ^= HBITS)

/*******************************************************************/
/********************** ATMEGA 328 IMAGE **************************/
/*******************************************************************/
typedef struct {
	//		Second Layer
	Atmega328GPWR_TypeDef* const gpwr;
	Atmega328AnalogComparator_TypeDef* const ac;
	Atmega328AnalogToDigitalConverter_TypeDef* const adc;
	Atmega328CPURegister_TypeDef* const cpu;
	Atmega328Eeprom_TypeDef* const eeprom;
	Atmega328ExternalInterrupt_TypeDef* const exint;
	Atmega328PORTB_TypeDef* const portb;
	Atmega328PORTC_TypeDef* const portc;
	Atmega328PORTD_TypeDef* const portd;
	Atmega328SerialPeripherialInterface_TypeDef* const spi;
	Atmega328TimerCounter1_TypeDef* const tc1;
	Atmega328TimerCounter0_TypeDef* const tc0;
	Atmega328TimerCounter2_TypeDef* const tc2;
	Atmega328TwoWireSerialInterface_TypeDef* const twi;
	Atmega328Usart0_TypeDef* const usart0;
	Atmega328WatchdogTimer_TypeDef* const wdt;
} dev_atmega328;

/*** Global Header ***/
dev_atmega328* dev(void);

/*****************************/
/**** MAIN HARDWARE LAYER ****/
/*****************************/
// GPWR
Atmega328GPWR_TypeDef* gpwr_reg(void);

// I/O Port (PORTB)
Atmega328PORTB_TypeDef* gpiob_reg(void);

// I/O Port (PORTC)
Atmega328PORTC_TypeDef* gpioc_reg(void);

// I/O Port (PORTD)
Atmega328PORTD_TypeDef* gpiod_reg(void);

// Timer/Counter 0, 1 and 2 Interrupt Flag
Atmega328TimerInterruptFlag_TypeDef* tc_iflag_reg(void);

// External Interrupts Flag (EXINT)
Atmega328ExternalInterruptFlag_TypeDef* exint_iflag_reg(void);

// External Interrupts Mask (EXINT)
Atmega328ExternalInterruptMask_TypeDef* exint_imask_reg(void);

// CPU Register Gpio0 (CPU)
Atmega328CpuGeneralPurposeIoRegister0_TypeDef* cpu_gpio0_reg(void);

// EEPROM (EEPROM)
Atmega328Eeprom_TypeDef* eeprom_reg(void);

// TIMER General Control
Atmega328TimerGeneralControlRegister_TypeDef* tc_gcontrol_reg(void);

// Timer/Counter, 8-bit A sync (TC0)
Atmega328TimerCounter0_TypeDef* tc0_reg(void);

// Timer/Counter, 8-bit A sync Compare (TC0)
Atmega328TimerCompareRegister0_TypeDef* tc0_compare_reg(void);

// CPU Register Gpio1 (CPU)
Atmega328CpuGeneralPurposeIoRegister1_TypeDef* cpu_gpio1_reg(void);

// CPU Register Gpio012 (CPU)
Atmega328CpuGeneralPurposeIoRegister_TypeDef* cpu_gpio012_reg(void);

// CPU Register Gpio2 (CPU)
Atmega328CpuGeneralPurposeIoRegister2_TypeDef* cpu_gpio2_reg(void);

// Serial Peripheral Interface (SPI)
Atmega328SerialPeripherialInterface_TypeDef* spi_reg(void);

// Analog Comparator (AC)
Atmega328AnalogComparator_TypeDef* ac_reg(void);

// Watchdog Timer (WDT)
Atmega328WatchdogTimer_TypeDef* wdt_reg(void);

// CPU Register (CPU)
Atmega328CPURegister_TypeDef* cpu_reg(void);

// External Interrupt (EXINT)
Atmega328ExternalInterrupt_TypeDef* exint_reg(void);

// External Interrupt Pin Change Mask (EXINT)
Atmega328ExternalInterruptPinChangeMask_TypeDef* exint_pcmask_reg(void);

// Timer/Counter 0, 1 and 2 Interrupt Mask
Atmega328TimerInterruptMask_TypeDef* tc_imask_reg(void);

// Analog to Digital Converter (ADC)
Atmega328AnalogToDigitalConverter_TypeDef* adc_reg(void);

// Analog Comparator Did (AC)
Atmega328AnalogComparatorDid_TypeDef* ac_did_reg(void);

// Timer/Counter, 16-bit (TC1)
Atmega328TimerCounter1_TypeDef* tc1_reg(void);

// Timer/Counter, 16-bit Compare (TC1)
Atmega328TimerCompareRegister1_TypeDef* tc1_compare_reg(void);

// Timer/Counter, 8-bit (TC2)
Atmega328TimerCounter2_TypeDef* tc2_reg(void);

// Timer/Counter, 8-bit Compare (TC2)
Atmega328TimerCompareRegister2_TypeDef* tc2_compare_reg(void);

// Two Wire Serial Interface (TWI)
Atmega328TwoWireSerialInterface_TypeDef* twi_reg(void);

// USART (USART0)
Atmega328Usart0_TypeDef* usart0_reg(void);

/*********************************************************************/
/*************** Procedure and Function declaration ******************/
/*********************************************************************/
uint16_t readhlbyte(U_word reg);
uint16_t readlhbyte(U_word reg);
U_word writehlbyte(uint16_t val);
U_word writelhbyte(uint16_t val);
uint16_t swapbyte(uint16_t num);
uint16_t BAUDRATEnormal(uint32_t BAUD);
uint16_t BAUDRATEdouble(uint32_t BAUD);
uint16_t BAUDRATEsynchronous(uint32_t BAUD);
void Atmega328ClockPrescalerSelect(volatile uint8_t prescaler);
void Atmega328MoveInterruptsToBoot(void);

/*********************************************************************/
/*************** Procedure and Function declaration ******************/
/*********************************************************************/
void set_reg(volatile uint8_t* reg, uint8_t hbits);
void clear_reg(volatile uint8_t* reg, uint8_t hbits);
uint8_t get_reg_block(uint8_t reg, uint8_t size_block, uint8_t bit_n);
uint8_t get_reg_Msk(uint8_t reg, uint8_t Msk);
void write_reg_block(volatile uint8_t* reg, uint8_t size_block, uint8_t bit_n, uint8_t data);
void write_reg_Msk(volatile uint8_t* reg, uint8_t Msk, uint8_t data);
void set_reg_block(volatile uint8_t* reg, uint8_t size_block, uint8_t bit_n, uint8_t data);
void set_reg_Msk(volatile uint8_t* reg, uint8_t Msk, uint8_t data);
uint8_t get_bit_block(volatile uint8_t* reg, uint8_t size_block, uint8_t bit_n);
void set_bit_block(volatile uint8_t* reg, uint8_t size_block, uint8_t bit_n, uint8_t data);
/*** NULL Check ***/
int isPtrNull(void* ptr);
int isCharPtrFlush(void* ptr);
/*** Fall Threw Delay ***/
int ftdelayCycles(uint8_t lock_ID, unsigned int n_cycle);
void ftdelayReset(uint8_t ID);

#endif
/*** EOF ***/



