/*************************************************************************
	ANALOG
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: Atmega328
Update:   01/01/2024
*************************************************************************/
/*** Library ***/
#include "atmega328analog.h"
#include <stdarg.h>

/*** Variable ***/
static ADC0 setup_analog;

static volatile int ADC_VALUE[ADC_MAX_CHANNEL];
static volatile int ADC_CHANNEL_GAIN[ADC_MAX_CHANNEL];
static volatile int ADC_N_CHANNEL;
static volatile int ADC_SELECTOR;
static volatile int adc_sample;
static volatile int adc_tmp;
static volatile unsigned char adc_n_sample;

/*** Procedure and Function declaration ***/
int ANALOG_read(int selection);

/*** Handler ***/
ADC0 adc_enable( uint8_t Vreff, uint8_t Divfactor, int n_channel, ... )
// Interrupt running mode setup
// setup, and list of channels to be probed
{
	uint8_t tSREG;
	va_list list;
	int i;

	tSREG = cpu_reg()->sreg.var;
	cpu_reg()->sreg.par.i= 0;
	
	ADC_N_CHANNEL = n_channel;
	ADC_SELECTOR = 0;
	adc_n_sample = 0;

	adc_reg()->admux.var &= ~(3 << REFS0);
	switch( Vreff ){
		case 0:
			setup_analog.par.VREFF = 0;
		break;
		case 1:
			adc_reg()->admux.var |=	(1 << REFS0);
			setup_analog.par.VREFF = 1;
		break;
		case 3:
			adc_reg()->admux.var |=	(3 << REFS0);
			setup_analog.par.VREFF = 3;
		break;
		default:
			setup_analog.par.VREFF = 0;
		break;
	}
	
	adc_reg()->admux.var &= ~(1 << ADLAR);
	
	va_start(list, n_channel);
	for( i = 0; i < n_channel; i++ ){
		ADC_CHANNEL_GAIN[i] = va_arg(list, int);
		switch(ADC_CHANNEL_GAIN[i]){
			case 0:
				gpioc_reg()->ddr.par.c0 = 0;
			break;
			case 1:
				gpioc_reg()->ddr.par.c1 = 0;
			break;
			case 2:
				gpioc_reg()->ddr.par.c2 = 0;
			break;
			case 3:
				gpioc_reg()->ddr.par.c3 = 0;
			break;
			case 4:
				gpioc_reg()->ddr.par.c4 = 0;
			break;
			case 5:
				gpioc_reg()->ddr.par.c5 = 0;
			break;
			default:
			break;
		}
	}
	va_end(list);
	
	adc_reg()->admux.var &= ~ADC_MUX_MASK;
	adc_reg()->admux.var |= (ADC_MUX_MASK & ADC_CHANNEL_GAIN[ADC_SELECTOR]);
	
	adc_reg()->adcsra.var |= (1 << ADEN);
	adc_reg()->adcsra.var |= (1 << ADSC);
	adc_reg()->adcsra.var &= ~(1 << ADATE);
	adc_reg()->adcsrb.var &= ~(7 << ADTS0);
	adc_reg()->adcsra.var |= (1 << ADIE);
	
	adc_reg()->adcsra.var &= ~(7 << ADPS0);
	switch( Divfactor ){
		case 2: // 1
			setup_analog.par.DIVISION_FACTOR = 2;
		break;
		case 4: // 2
			adc_reg()->adcsra.var |= (1 << ADPS1);
			setup_analog.par.DIVISION_FACTOR = 4;
		break;
		case 8: // 3
			adc_reg()->adcsra.var |= (3 << ADPS0);
			setup_analog.par.DIVISION_FACTOR = 8;
		break;
		case 16: // 4
			adc_reg()->adcsra.var |= (1 << ADPS2);
			setup_analog.par.DIVISION_FACTOR	=	16;
		break;
		case 32: // 5
			adc_reg()->adcsra.var |= (5 << ADPS0);
			setup_analog.par.DIVISION_FACTOR = 32;
		break;
		case 64: // 6
			adc_reg()->adcsra.var |= (6 << ADPS0);
			setup_analog.par.DIVISION_FACTOR = 64;
		break;
		case 128: // 7
			adc_reg()->adcsra.var |= (7 << ADPS0);
			setup_analog.par.DIVISION_FACTOR = 128;
		break;
		default: // 7
			adc_reg()->adcsra.var |= (7 << ADPS0);
			setup_analog.par.DIVISION_FACTOR = 128;
		break;
	}
	//V-table
	setup_analog.read = ANALOG_read;
	
	cpu_reg()->sreg.var = tSREG;
	cpu_reg()->sreg.par.i = 1;

	return setup_analog;
}

ADC0* adc(void){ return &setup_analog; }

/*** Procedure and Function definition ***/
int ANALOG_read(int selection)
// Returns selected Channel ADC_VALUE
{
	uint8_t ADSC_FLAG;
	ADSC_FLAG = (1 << ADSC);
	if( !(adc_reg()->adcsra.var & ADSC_FLAG) ){
		//ADC_SELECT
		adc_reg()->adcsra.var |= (1 << ADSC);
	}	
	return ADC_VALUE[selection];
}

/*** File Interrupt ***/
ISR(ANALOG_INTERRUPT)
// Function: ANALOG interrupt
// Purpose:  Read Analog Input
{
	adc_tmp = ADCL;
	adc_tmp |= (ADCH << 8);
	if(adc_n_sample < (1 << ADC_NUMBER_SAMPLE)){
		adc_n_sample++;
		adc_sample += adc_tmp;
	}else{
		ADC_VALUE[ADC_SELECTOR] = adc_sample >> ADC_NUMBER_SAMPLE;
		adc_n_sample=adc_sample = 0;
		/******/
		if(ADC_SELECTOR < ADC_N_CHANNEL)
			ADC_SELECTOR++;
		else
			ADC_SELECTOR = 0;
		adc_reg()->admux.var &= ~ADC_MUX_MASK;
		adc_reg()->admux.var |= (ADC_CHANNEL_GAIN[ADC_SELECTOR] & ADC_MUX_MASK);
	}		
}

/*** EOF ***/

