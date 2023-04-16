/************************************************************************
	ATCOMMANDS
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: ALL
Date: 01122022
Comment:
	Stable
************************************************************************/
#ifndef _ATCOMMANDS_H_
	#define _ATCOMMANDS_H_

/*** Compiler ***/

/*** Working Frequency ***/

/*** Global Library ***/
#include <inttypes.h>

/*** Global Constant & Macro ***/

/*** Global Variable ***/

/*** Global Header ***/
char* BT05ATcmd(uint16_t num);
char* HC42ATcmd(uint16_t num);
char* HC05ATcmd(uint16_t num);

#endif
/***EOF***/

