/*************************************************************************
	ZNPID
Author: Sergio Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License     
Hardware: Atmega 128
Date: 17022021_start
Comment:

************************************************************************/
/***File Library***/
#include "znpid.h"

/***File Constant & Macro***/
#define ZNPID_outMAX 1023
#define ZNPID_outMIN -1023

/***File Variable***/
/***************************
struct ZNPID_DATA{
	float proportional;
	float integral;
	float derivative;
}reading;
***************************/
float ZNPID_tmp;

/***File Header***/
void ZNPID_set_kc(ZNPID* self, float kc);
void ZNPID_set_ki(ZNPID* self, float ki);
void ZNPID_set_kd(ZNPID* self, float kp);
void ZNPID_set_SP(ZNPID* self, float setpoint);
float ZNPID_delta(float present_value, float past_value);
float ZNPID_sum(float value_1, float value_2);
float ZNPID_product(float value_1, float value_2);
float ZNPID_integral(ZNPID* self, float PV, float timelapse);
float ZNPID_derivative(ZNPID* self, float PV, float timelapse);
float ZNPID_output(ZNPID* self, float PV, float timelapse);

/***Procedure & Function***/
ZNPID ZNPIDenable(void)
{
	// LOCAL VARIABLES
	// ALLOCAÇÂO MEMORIA PARA Estrutura
	ZNPID znpid;
	// import parameters
	// initialize variables
	znpid.par.kc = 1;
	znpid.par.ki = 0;
	znpid.par.kd = 0;
	znpid.par.SetPoint = 0;
	znpid.Err_past = 0;
	znpid.dy = 0;
	znpid.dx = 0;
	znpid.integral = 0;
	znpid.derivative = 0;
	znpid.PV = 0;
	znpid.OP = 0;
	// Direccionar apontadores para PROTOTIPOS
	znpid.set_kc = ZNPID_set_kc;
	znpid.set_ki = ZNPID_set_ki;
	znpid.set_kd = ZNPID_set_kd;
	znpid.set_SP = ZNPID_set_SP;
	znpid.output = ZNPID_output;
	
	return znpid;
}
void ZNPID_set_kc(ZNPID* self, float kc)
{
	self->par.kc = kc;
}
void ZNPID_set_ki(ZNPID* self, float ki)
{
	self->par.ki = ki;
}
void ZNPID_set_kd(ZNPID* self, float kd)
{	
	self->par.kd = kd;
}
void ZNPID_set_SP(ZNPID* self, float setpoint)
{
	self->par.SetPoint = setpoint;
}
float ZNPID_delta(float present_value, float past_value)
{
	return (present_value - past_value);
}
float ZNPID_sum(float value_1, float value_2)
{
	return (value_1 + value_2);
}
float ZNPID_product(float value_1, float value_2)
{
	return (value_1 * value_2);
}
float ZNPID_integral(ZNPID* self, float PV, float timelapse)
{
	ZNPID_tmp = ZNPID_product(ZNPID_sum(ZNPID_delta(self->par.SetPoint, PV), self->Err_past), timelapse);
	ZNPID_tmp /= 2;
	return (self->integral += ZNPID_tmp);
}
float ZNPID_derivative(ZNPID* self, float PV, float timelapse)
{
	ZNPID_tmp = ZNPID_delta(ZNPID_delta(self->par.SetPoint, PV), self->Err_past);
	return (self->derivative = (ZNPID_tmp / timelapse));
}
float ZNPID_output(ZNPID* self, float PV, float timelapse)
{
	float result;
	self->PV = PV;
	self->dy = ZNPID_delta(self->par.SetPoint, PV);
	self->dx = timelapse;
	result = ZNPID_product(self->par.kc, self->dy);
	ZNPID_tmp = ZNPID_product(self->par.ki, ZNPID_integral(self, PV, timelapse));
	result = ZNPID_sum(result, ZNPID_tmp);
	ZNPID_tmp = ZNPID_product(self->par.kd, ZNPID_derivative(self, PV, timelapse));
	result = ZNPID_sum(result, ZNPID_tmp);
	self->Err_past = self->dy;
	self->OP = result;
	if(result > ZNPID_outMAX)
		self->integral = ZNPID_outMAX - (self->dy * self->dx) - (self->derivative * self->dx * self->dx);
	else if(result < ZNPID_outMIN)
		self->integral = ZNPID_outMIN + (self->dy * self->dx) + (self->derivative * self->dx * self->dx);
	return result;
}

/***File Interrupt***/

/***EOF***/

