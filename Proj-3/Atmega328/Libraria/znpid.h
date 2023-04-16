/************************************************************************
	ZNPID
Author: Sergio Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: Atmega 128
Date: 17022021_start
Comment:

************************************************************************/
#ifndef _ZNPID_H_
	#define _ZNPID_H_

/*** Compiler ***/

/*** Working Frequency ***/
#ifndef F_CPU
	#define F_CPU 16000000UL
#endif

/*** Global Library ***/
#include <inttypes.h>

/*** Global Constant & Macro ***/

/*** Global Variable ***/
struct znpid{
	float kc; // constant p
	float ki; // constant i
	float kd; // constant d
	float Err_past; // Last Error reading
	float dy; // difference error y axis points.
	float dx; // difference time x axis points.
	float integral; // progression
	float derivative; // rate of growth (tangent), or derivative
	float SetPoint; // desired output
	float PV; // output feedback
	float OP; // output signal
	/******/
	void (*set_kc)(struct znpid* self, float kc);
	void (*set_ki)(struct znpid* self, float ki);
	void (*set_kd)(struct znpid* self, float kd);
	void (*set_SP)(struct znpid* self, float setpoint);
	float (*output)(struct znpid* self, float PV, float timelapse);
};
typedef struct znpid ZNPID;

/*** Global Header ***/
ZNPID ZNPIDenable(void);

#endif
/***EOF***/

