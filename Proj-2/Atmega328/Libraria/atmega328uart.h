/************************************************************************
	Atmega328Uart
Author: Sergio Manuel Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: Atmega328 ETT ET-BASE
Date: 02122022
Comment:
	stable
************************************************************************/
#ifndef _ATMEGA328UART_H_
	#define _ATMEGA328UART_H_

/*** Compiler ***/
#if (__GNUC__ * 100 + __GNUC_MINOR__) < 304
	#error "This library requires AVR-GCC 3.4 or later, update to newer AVR-GCC compiler !"
#endif

/*** Working Frequency ***/
#ifndef F_CPU
	#define F_CPU 8000000UL
#endif
#ifndef TWI_SCL_CLOCK
	#define TWI_SCL_CLOCK 100000UL
#endif

/*** Global Library ***/
#include <inttypes.h>

/*** Global Constant & Macro ***/
#ifndef GLOBAL_INTERRUPT_ENABLE
	#define GLOBAL_INTERRUPT_ENABLE 7
#endif
#ifndef UART_RX_BUFFER_SIZE
	#define UART_RX_BUFFER_SIZE 32
#endif
#define UARTvar char
// Parity choices
#define NONE 0
#define EVEN 2
#define ODD 3

/*** Global Variable ***/
struct uart {
	// Parameters
	unsigned int ubrr;
	unsigned int FDbits;
	unsigned int Stopbits;
	unsigned int Parity;
	// prototype pointers
	UARTvar (*read)(void);
	UARTvar (*getch)(void);
	UARTvar* (*gets)(void);
	void (*rxflush)(void);
	void (*write)(UARTvar data);
	void (*putch)(UARTvar c);
	void (*puts)(UARTvar* s);
};
typedef struct uart UART;

/*** Global Header ****/
UART UARTenable( unsigned int baudrate, unsigned int FDbits, unsigned int Stopbits, unsigned int Parity );

#endif
/***EOF***/

