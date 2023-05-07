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

/*** Global Library ***/
#include <inttypes.h>

/*** Global Constant & Macro ***/

/*** Global Variable ***/
typedef struct {
	double kc; // constant p
	double ki; // constant i
	double kd; // constant d
	double SetPoint; // desired output
	double Err_past; // Last Error reading
	double dy; // difference error y axis points.
	double dx; // difference time x axis points.
	double integral; // progression
	double derivative; // rate of growth (tangent), or derivative
	double PV; // output feedback
	double OP; // output signal
}znpidparameter;

struct znpid{
	znpidparameter par;
	/******/
	void (*set_kc)(znpidparameter* par, double kc);
	void (*set_ki)(znpidparameter* par, double ki);
	void (*set_kd)(znpidparameter* par, double kd);
	void (*set_SP)(znpidparameter* par, double setpoint);
	double (*output)(znpidparameter* par, double PV, double timelapse);
};
typedef struct znpid ZNPID;

/*** Global Header ***/
ZNPID ZNPIDenable(void);

#endif

/***EOF***/

