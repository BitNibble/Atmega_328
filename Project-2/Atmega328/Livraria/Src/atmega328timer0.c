/*************************************************************************
	TIMER0
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: Atmega328 by ETT ET-BASE
Update:   01/01/2024
*************************************************************************/
/*** Library ***/
#include "atmega328timer0.h"

/*** Variable ***/
static TC0 setup_tc0;
static unsigned char timer0_state;

/*** Procedure and Function declaration ***/
void TIMER_COUNTER0_compoutmodeA(unsigned char compoutmode);
void TIMER_COUNTER0_compoutmodeB(unsigned char compoutmode);
void TIMER_COUNTER0_compareA(unsigned char compare);
void TIMER_COUNTER0_compareB(unsigned char compare);
void TIMER_COUNTER0_start(unsigned int prescaler);
void TIMER_COUNTER0_stop(void);

/*** Handler ***/
TC0 tc0_enable(unsigned char wavegenmode, unsigned char interrupt)
//	PARAMETER SETTING
//	wavegen mode: Normal; PWM phase correct; Fast PWM; default-Normasl;
//	interrupt: off; overflow; output compare; both; default - non.
{
	timer0_state = 0;
	tc0_reg()->tccr0a.var &= ~((1 << WGM01) | (1 << WGM00));
	tc0_reg()->tccr0b.var &= ~(1 << WGM02);
	switch(wavegenmode){
		case 0: // Normal
		break;
		case 1: // PWM, Phase Correct, 8-bit
			tc0_reg()->tccr0a.var |= (1 << WGM00);
		break;
		case 2: // PWM, Phase Correct, 9-bit
			tc0_reg()->tccr0a.var |= (1 << WGM01);
		break;
		case 3: // Fast PWM
			tc0_reg()->tccr0a.var |= (1 << WGM00) | (1 << WGM01);
		break;
		case 5: // PWM, Phase Correct
			tc0_reg()->tccr0a.var |= (1 << WGM00);
			tc0_reg()->tccr0b.var |= (1 << WGM02);
		break;
		case 7: // Fast PWM
			tc0_reg()->tccr0a.var |= (1 << WGM00) | (1 << WGM01);
			tc0_reg()->tccr0b.var |= (1 << WGM02);
		break;
		default: // Normal
		break;
	}
	tc_imask_reg()->timsk0.var &= ~((1 << OCIE0B) | (1 << OCIE0A) | (1 << TOIE0));
	switch(interrupt){
		case 0: 
		break;
		case 1:
			tc_imask_reg()->timsk0.var |= (1 << TOIE0);
			cpu_reg()->sreg.var |= (1 << GLOBAL_INTERRUPT_ENABLE);
		break;
		case 2:
			tc_imask_reg()->timsk0.var |= (1 << OCIE0A);
			cpu_reg()->sreg.var |= (1 << GLOBAL_INTERRUPT_ENABLE);
		break;
		case 3:
			tc_imask_reg()->timsk0.var |= (1 << OCIE0B);
			cpu_reg()->sreg.var |= (1 << GLOBAL_INTERRUPT_ENABLE);
		break;
		case 4:
			tc_imask_reg()->timsk0.var |= (1 << TOIE0) | (1 << OCIE0A);
			cpu_reg()->sreg.var |= (1 << GLOBAL_INTERRUPT_ENABLE);
		break;
		case 5:
			tc_imask_reg()->timsk0.var |= (1 << TOIE0) | (1 << OCIE0B);
			cpu_reg()->sreg.var |= (1 << GLOBAL_INTERRUPT_ENABLE);
		break;
		case 6:
			tc_imask_reg()->timsk0.var |= (1 << TOIE0) | (1 << OCIE0A) | (1 << OCIE0B);
			cpu_reg()->sreg.var |= (1 << GLOBAL_INTERRUPT_ENABLE);
		break;
		case 7:
			tc_imask_reg()->timsk0.var |= (1 << OCIE0A) | (1 << OCIE0B);
			cpu_reg()->sreg.var |= (1 << GLOBAL_INTERRUPT_ENABLE);
		break;
		default:
		break;
	}
	// V-table
	setup_tc0.compoutmodeA = TIMER_COUNTER0_compoutmodeA;
	setup_tc0.compoutmodeB = TIMER_COUNTER0_compoutmodeB;
	setup_tc0.compareA = TIMER_COUNTER0_compareA;
	setup_tc0.compareB = TIMER_COUNTER0_compareB;
	setup_tc0.start = TIMER_COUNTER0_start;
	setup_tc0.stop = TIMER_COUNTER0_stop;

	return setup_tc0;
}

TC0* tc0(void){ return &setup_tc0; };

/*** Procedure and Function definition ***/
void TIMER_COUNTER0_start(unsigned int prescaler)
//	PARAMETER SETTING
//	Frequency oscillator devision factor or prescaler.
//	prescaler: clk T0S /(No prescaling); clk T0S /8 (From prescaler); clk T0S /32 (From prescaler);
//	clk T0S /64 (From prescaler); clk T0S /128 (From prescaler); clk T 0 S /256 (From prescaler);
//	clk T 0 S /1024 (From prescaler); default - clk T 0 S /1024 (From prescaler).
{
	if(timer0_state == 0){ // one shot
		tc0_compare_reg()->ocr0a.var = 0XFF;
		tc0_reg()->tccr0b.var &= ~(7 << CS00); // No clock source. (Timer/Counter stopped)
		switch(prescaler){
			case 1: // clk T0S /(No prescaler)
				tc0_reg()->tccr0b.var |= (1 << CS00);
			break;
			case 8: // clk T0S /8 (From prescaler)
				tc0_reg()->tccr0b.var |= (1 << CS01);
			break;
			case 64: // clk T0S /64 (From prescaler)
				tc0_reg()->tccr0b.var |= (3 << CS00);
			break;
			case 256: // clk T 0 S /256 (From prescaler)
				tc0_reg()->tccr0b.var |= (4 << CS00);
			break;
			case 1024: // clk T 0 S /1024 (From prescaler)
				tc0_reg()->tccr0b.var |= (5 << CS00);
			break;
			case 3: // External clock source on T0 pin. Clock on falling edge.
				tc0_reg()->tccr0b.var |= (6 << CS00);
			break;
			case 5: // External clock source on T0 pin. Clock on rising edge.
				tc0_reg()->tccr0b.var |= (7 << CS00);
			break;
			default: // clk T 0 S /1024 (From prescaler)
				tc0_reg()->tccr0b.var |= (5 << CS00);
			break;
		}
		timer0_state = 1;
	}	
}
void TIMER_COUNTER0_compoutmodeA(unsigned char compoutmode)
//	compoutmode: Normal gpio operation, OC0 disconnected; Toggle OC0 on compare match; 
//	Clear OC0 on compare match when up-counting. Set OC0 on compare match when downcounting. Clear OC0 on compare match;
//	Set OC0 on compare match when up-counting. Clear OC0 on compare match when downcounting. Set OC0 on compare match ;
//	default-Normal gpio operation, OC0 disconnected.
{
	tc0_reg()->tccr0a.var &= ~((1 << COM0A0) | (1 << COM0A1));
	switch(compoutmode){
		case 0: // Normal gpio operation, OC0 disconnected.
		break;
		case 1: // Reserved
				// Toggle OC0 on compare match
			gpiod_reg()->ddr.var |= (1 << 6);
			tc0_reg()->tccr0a.var |= (1 << COM0A0);
			
		break;
		case 2: // Clear OC0 on compare match when up-counting.
				// Set OC0 on compare
				// match when down counting.
				// Clear OC0 on compare match
			gpiod_reg()->ddr.var |= (1 << 6);
			tc0_reg()->tccr0a.var |= (1 << COM0A1);
		break;
		case 3: // Set OC0 on compare match when up-counting.
				// Clear OC0 on compare
				// match when down counting.
				// Set OC0 on compare match
			gpiod_reg()->ddr.var |= (1 << 6);
			tc0_reg()->tccr0a.var |= (1 << COM0A0) | (1 << COM0A1);
		break;
		default: // Normal gpio operation, OC0 disconnected.
		break;
	}
}
void TIMER_COUNTER0_compoutmodeB(unsigned char compoutmode)
//	compoutmode: Normal gpio operation, OC0 disconnected; Toggle OC0 on compare match; 
//	Clear OC0 on compare match when up-counting. Set OC0 on compare match when downcounting. Clear OC0 on compare match;
//	Set OC0 on compare match when up-counting. Clear OC0 on compare match when downcounting. Set OC0 on compare match ;
//	default-Normal gpio operation, OC0 disconnected.
{
	tc0_reg()->tccr0a.var &= ~((1 << COM0B0) | (1 << COM0B1));
	switch(compoutmode){ // see table 53, 54, 55 in data sheet for more information
		case 0: // Normal gpio operation, OC0 disconnected.
		break;
		case 1: // Reserved
				// Toggle OC0 on compare match
			gpiod_reg()->ddr.var |= (1 << 5);
			tc0_reg()->tccr0a.var |= (1 << COM0B0);
		break;
		case 2: // Clear OC0 on compare match when up-counting.
				// Set OC0 on compare
				// match when down counting.
				// Clear OC0 on compare match
			gpiod_reg()->ddr.var |= (1 << 5);
			tc0_reg()->tccr0a.var |= (1 << COM0B1);
		break;
		case 3: // Set OC0 on compare match when up-counting.
				// Clear OC0 on compare
				// match when down counting.
				// Set OC0 on compare match
			gpiod_reg()->ddr.var |= (1 << 5);
			tc0_reg()->tccr0a.var |= (1 << COM0B0) | (1 << COM0B1);
		break;
		default: // Normal port operation, OC0 disconnected.
		break;
	}
}
void TIMER_COUNTER0_compareA(unsigned char compare)
{
	tc0_compare_reg()->ocr0a.var = compare;
}
void TIMER_COUNTER0_compareB(unsigned char compare)
{
	tc0_compare_reg()->ocr0b.var = compare;
}
void TIMER_COUNTER0_stop(void)
// stops timer by setting prescaler to zero
{
	tc0_reg()->tccr0b.var &= ~(7 << CS00); // No clock source. (Timer/Counter stopped)
	tc0_reg()->tcnt0.var = 0X00;
	timer0_state = 0;
}

/*** EOF ***/

