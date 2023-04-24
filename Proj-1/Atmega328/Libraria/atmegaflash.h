/*************************************************************************
	flash wrapper
Author: Sergio Manuel Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: ATmega
Date: 09122022
Comment:
	Start 09122022
*************************************************************************/
#ifndef _ATMEGAEEPROM_H_
#define _ATMEGAEEPROM_H_

/*** Compiler ***/
#if (__GNUC__ * 100 + __GNUC_MINOR__) < 304
#error "This library requires AVR-GCC 3.4 or later, update to newer AVR-GCC compiler !"
#endif

/*** Working Frequency ***/

/*** Global Library ***/
#include <avr/io.h>
#include <avr/pgmspace.h>
//#include <self_programming.h>
#include <inttypes.h>

/*** Global Constant & Macro ***/
//#define PAGESIZE xxxxx

/*** Global Variable ***/
struct flsh{
	// vtable
	unsigned char (*readbyte)( MyAddressType flashAdr );
	unsigned char (*readpage)( MyAddressType flashStartAdr, unsigned char *dataPage );
	unsigned char (*writebyte)( MyAddressType flashAddr, unsigned char data );
	unsigned char (*writepage)( MyAddressType flashStartAdr, unsigned char *dataPage );
	unsigned char (*recover)( void );
};
typedef struct flsh FLASH;

/*** Global Header ***/
FLASH FLASHenable(void);

#endif
/***EOF***/

