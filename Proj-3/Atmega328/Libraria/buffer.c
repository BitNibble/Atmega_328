/******************************************************************************
	BUFFER
Author: Sergio Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: all
Date: 17112022
Comment:
	Buffer
******************************************************************************/
/*** File Library ***/
#include "buffer.h"
#include <stdio.h>
#include <string.h>

/*** File Constant & Macro ***/

/*** File Variable ***/

/*** File Header ***/
void BUFF_push(bufferposition* pos, BUFFvar data);
BUFFvar* BUFF_raw(bufferposition* pos);
void BUFF_flush(bufferposition* pos);

/*** Procedure & Function ***/
BUFF BUFFenable( uint8_t size_buff, BUFFvar* buff )
{
	// OBJECT STRUCT
	BUFF ret;
	// inic VAR
	ret.pos.orig = buff;
	ret.pos.head = buff;
	ret.pos.end = buff + ( size_buff ); // generic
	// function pointers
	ret.push = BUFF_push;
	ret.raw = BUFF_raw;
	ret.flush = BUFF_flush;
	return ret; // return copy
}

void BUFF_push( bufferposition* pos, BUFFvar data ){
	BUFFvar* head; BUFFvar* next;
	head = pos->head;
	if(data){
		if( head == pos->end ){
			head = pos->orig;
			next = head + 1;
		}else{
			next = head + 1;
		}
			*head = data;
			*next = 0;
			pos->head = next;
	}
}

BUFFvar* BUFF_raw( bufferposition* pos ){
		return pos->orig;
}

void BUFF_flush( bufferposition* pos ){
	BUFFvar* head;
	head = pos->orig;
	pos->head = head;
	*head = 0;
}

/*** File Interrupt ***/

/***EOF***/

