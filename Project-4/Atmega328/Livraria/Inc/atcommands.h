/************************************************************************
	ATCOMMANDS
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: ALL
Date:     24042023
Comment:
	Stable
************************************************************************/
#ifndef _ATCOMMANDS_H_
	#define _ATCOMMANDS_H_

/*** Global Library ***/
#include <inttypes.h>

/*** Global Header ***/
char* bt05at_cmd(uint16_t num);
char* hc42at_cmd(uint16_t num);
char* hc05at_cmd(uint16_t num);
char* esp8266_cmd(uint16_t num);

#endif

/*** EOF ***/

