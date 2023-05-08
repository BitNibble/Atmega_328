/*************************************************************************
	ANALOG
Author: Sergio Manuel Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: Atmega328
Date: 24042023
Comment:
	Very Stable
*************************************************************************/
/*** File Library ***/
#include "atmega328mapping.h"
#include <stdarg.h>

/*** File Constant & Macro ***/
#ifndef GLOBAL_INTERRUPT_ENABLE
	#define GLOBAL_INTERRUPT_ENABLE 7
#endif
// if using differential channels this value has to be greater than one
#define MAX_CHANNEL 8
#if defined(__AVR_ATmega48__) ||defined(__AVR_ATmega88__) || defined(__AVR_ATmega168__) || \
      defined(__AVR_ATmega48P__) ||defined(__AVR_ATmega88P__) || defined(__AVR_ATmega168P__) || \
      defined(__AVR_ATmega328P__) ||defined(__AVR_ATmega328__)
	#define MUX_MASK 15
	#define ANALOG_INTERRUPT ADC_vect
#else
 	#error "Not Atmega328"
#endif

/*** File Variable ***/
ATMEGA328 analogmega328;
static volatile int ADC_VALUE[MAX_CHANNEL];
static volatile int ADC_CHANNEL_GAIN[MAX_CHANNEL];
static volatile int ADC_N_CHANNEL;
static volatile int ADC_SELECTOR;
static volatile int adc_sample;
static volatile int adc_tmp;
static volatile unsigned char adc_n_sample;

/*** File Header ***/
int ANALOG_read(int selection);

/*** Procedure & Function ***/
ANALOG ANALOGenable( uint8_t Vreff, uint8_t Divfactor, int n_channel, ... )
// Interrupt running mode setup
// setup, and list of channels to be probed
{
	uint8_t tSREG;
	analogmega328 = ATMEGA328enable();
	va_list list;
	int i;

	tSREG = analogmega328.cpu.reg->sreg;
	analogmega328.cpu.reg->sreg &= ~ (1 << GLOBAL_INTERRUPT_ENABLE);
	
	ADC_N_CHANNEL = n_channel;
	ADC_SELECTOR = 0;
	adc_n_sample = 0;

	ANALOG analog;
	//Vtable
	analog.read = ANALOG_read;
	
	analogmega328.adc.reg->admux &= ~(3 << REFS0);
	switch( Vreff ){
		case 0:
			analog.par.VREFF = 0;
		break;
		case 1:
			analogmega328.adc.reg->admux |=	(1 << REFS0);
			analog.par.VREFF = 1;
		break;
		case 3:
			analogmega328.adc.reg->admux |=	(3 << REFS0);
			analog.par.VREFF = 3;
		break;
		default:
			analog.par.VREFF = 0;
		break;
	}
	
	analogmega328.adc.reg->admux &= ~(1 << ADLAR);
	
	va_start(list, n_channel);
	for( i = 0; i < n_channel; i++ ){
		ADC_CHANNEL_GAIN[i] = va_arg(list, int);
	}
	va_end(list);
	analogmega328.adc.reg->admux &= ~MUX_MASK;
	analogmega328.adc.reg->admux |= (MUX_MASK & ADC_CHANNEL_GAIN[ADC_SELECTOR]);
	
	analogmega328.adc.reg->adcsra |= (1 << ADEN);
	analogmega328.adc.reg->adcsra |= (1 << ADSC);
	analogmega328.adc.reg->adcsra &= ~(1 << ADATE);
	analogmega328.adc.reg->adscrb &= ~(7 << ADTS0);
	analogmega328.adc.reg->adcsra |= (1 << ADIE);
	
	analogmega328.adc.reg->adcsra &= ~(7 << ADPS0);
	switch( Divfactor ){
		case 2: // 1
			analog.par.DIVISION_FACTOR = 2;
		break;
		case 4: // 2
			analogmega328.adc.reg->adcsra |= (1 << ADPS1);
			analog.par.DIVISION_FACTOR = 4;
		break;
		case 8: // 3
			analogmega328.adc.reg->adcsra |= (3 << ADPS0);
			analog.par.DIVISION_FACTOR = 8;
		break;
		case 16: // 4
			analogmega328.adc.reg->adcsra |= (1 << ADPS2);
			analog.par.DIVISION_FACTOR	=	16;
		break;
		case 32: // 5
			analogmega328.adc.reg->adcsra |= (5 << ADPS0);
			analog.par.DIVISION_FACTOR = 32;
		break;
		case 64: // 6
			analogmega328.adc.reg->adcsra |= (6 << ADPS0);
			analog.par.DIVISION_FACTOR = 64;
		break;
		case 128: // 7
			analogmega328.adc.reg->adcsra |= (7 << ADPS0);
			analog.par.DIVISION_FACTOR = 128;
		break;
		default: // 7
			analogmega328.adc.reg->adcsra |= (7 << ADPS0);
			analog.par.DIVISION_FACTOR = 128;
		break;
	}
	analogmega328.cpu.reg->sreg = tSREG;
	analogmega328.cpu.reg->sreg |= (1 << GLOBAL_INTERRUPT_ENABLE);
	
	return analog;
}

int ANALOG_read(int selection)
// Returns selected Channel ADC_VALUE
{
	uint8_t ADSC_FLAG;
	ADSC_FLAG = (1 << ADSC);
	if( !(analogmega328.adc.reg->adcsra & ADSC_FLAG) ){
		//ADC_SELECT
		analogmega328.adc.reg->adcsra |= (1 << ADSC);
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
		analogmega328.adc.reg->admux &= ~MUX_MASK;
		analogmega328.adc.reg->admux |= (ADC_CHANNEL_GAIN[ADC_SELECTOR] & MUX_MASK);
	}		
}

/***EOF***/

