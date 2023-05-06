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
/*** File Library ***/
#include "atmegaflash.h"

/*** File Constant & Macro ***/

/*** File Variable ***/

/*** File Header ***/

/*** Procedure & Function ***/
FLASH FLASHenable(void){
	FLASH flash;
	flash.readbyte =  ReadFlashByte;
	flash.readpage = ReadFlashPage;
	flash.writebyte =  WriteFlashByte;
	flash.writepage = WriteFlashPage;
	flash.recover = RecoverFlash;
	return flash;
}

/*** File Interrupt ***/

/***EOF***/

