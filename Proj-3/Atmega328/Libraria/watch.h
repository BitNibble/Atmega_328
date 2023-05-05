/************************************************************************
Title:    watch.h
Author:   Sergio Manuel Santos <sergio.salazar.santos@gmail.com>
File:     $Id: watch.h,v 0.2 2017/07/01 17:00:00 Sergio Exp $
Software: AVR-GCC 4.1, AVR Libc 1.4
Hardware:
License:  GNU General Public License
Comment:
	
************************************************************************/
#ifndef _WATCH_H_
	#define _WATCH_H_

/*** Global library ***/
#include <inttypes.h>

/*** Global Constant & Macro ***/

/*** Global Variable ***/
struct WATCHTIME{
	uint8_t hour;
	uint8_t minute;
	uint8_t second;
	uint16_t seconds;
};
struct WATCH{
	struct WATCHTIME* time;
	uint8_t (*start_delay)(uint8_t n_delay, uint16_t seconds);
	void (*increment)(void);
	void (*decrement)(void);
	char* (*show)(void);
};
typedef struct WATCH WATCH;

/*** Global Header ***/
WATCH WATCHenable(void);

#endif

/***EOF***/

