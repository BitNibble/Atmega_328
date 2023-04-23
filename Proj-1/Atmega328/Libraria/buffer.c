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
void BUFF_push(BUFF* self, BUFFvar data);
BUFFvar* BUFF_raw(BUFF* self);
void BUFF_flush(BUFF* self);

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

void BUFF_push( BUFF* self, BUFFvar data ){
	BUFFvar* head; BUFFvar* next;
	head = self->pos.head;
	if(data){
		if( head == self->pos.end ){
			head = self->pos.orig;
			next = head + 1;
		}else{
			next = head + 1;
		}
			*head = data;
			*next = 0;
			self->pos.head = next;
	}
}

BUFFvar* BUFF_raw( BUFF* self ){
		return self->pos.orig;
}

void BUFF_flush( BUFF* self ){
	BUFFvar* head;
	head = self->pos.orig;
	self->pos.head = head;
	*head = 0;
}

/*** File Interrupt ***/

/***EOF***/

