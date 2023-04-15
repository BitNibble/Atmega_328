/************************************************************************
	FUNCTION
Author: Sergio Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: all
Date: 06082022
Comment:
	Very Stable
	Tested Atemga128 16Mhz and Atmega328 8Mhz and STM32F446RE
************************************************************************/
#ifndef _FUNCTION_H_
	#define _FUNCTION_H_

/*** Global Library ***/
/*******pc use*******
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
********************/
#include <inttypes.h>

/*** Global Constant & Macro ***/

/*** Global Variable ***/
// Low Byte High Byte
typedef struct
{
	uint8_t H;
	uint8_t L;
} FUNCHighLowByte;

typedef struct
{
	// PROTOTYPES VTABLE
	int (*stringlength)(const char string[]);
	void (*reverse)(char s[]);
	unsigned int (*mayia)(unsigned int xi, unsigned int xf, uint8_t nbits);
	void (*swap)(long *px, long *py);
	void (*copy)(char to[], char from[]);
	void (*squeeze)(char s[], int c);
	void (*shellsort)(int v[], int n);
	char* (*i16toa)(int16_t n);
	char* (*ui16toa)(uint16_t n);
	char* (*i32toa)(int32_t n);
	int (*trim)(char s[]);
	int (*pmax)(int a1, int a2);
	int (*gcd)(int u, int v);
	int (*strToInt)(const char string[]);
	uint8_t (*filter)(uint8_t mask, uint8_t data);
	unsigned int (*ticks)(unsigned int num);
	int (*twocomptoint8bit)(int twoscomp);
	int (*twocomptoint10bit)(int twoscomp);
	int (*twocomptointnbit)(int twoscomp, uint8_t nbits);
	char (*dec2bcd)(char num);
	char (*bcd2dec)(char num);
	char* (*resizestr)(char *string, int size);
	long (*trimmer)(long x, long in_min, long in_max, long out_min, long out_max);
	unsigned char (*bcd2bin)(unsigned char val);
	unsigned char (*bin2bcd)(unsigned val);
	long (*gcd1)(long a, long b);
	uint8_t (*pincheck)(uint8_t port, uint8_t pin);
	char* (*print_binary)(unsigned int n_bits, unsigned int number);
	char* (*ftoa)(double num, char* res, uint8_t afterpoint);
	char* (*dectohex)(int32_t num);
	uint16_t (*ReadHLByte)(FUNCHighLowByte reg);
	uint16_t (*ReadLHByte)(FUNCHighLowByte reg);
	FUNCHighLowByte (*WriteHLByte)(uint16_t val);
	FUNCHighLowByte (*WriteLHByte)(uint16_t val);
	uint16_t (*SwapByte)(uint16_t num);
	char* (*print)( const char *format, ... );
	/**********************pc use**********************
	char* (*fltos)(FILE* stream);
	char* (*ftos)(FILE* stream);
	int (*strtotok)(char* line,char* token[], const char* parser);
	char* (*putstr)(char* str);
	int (*getnum)(char* x);
	unsigned int (*getnumv2)(char* x);
	int (*readint)(int nmin, int nmax);
	**************************************************/
}FUNC;

/*** Global Header ***/
FUNC FUNCenable(void);

#endif
/***EOF***/

