/*************************************************************************
	TIMER1
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: Atmega328 by ETT ET-BASE
Update:   01/01/2024
*************************************************************************/
/*** Library ***/
#include "atmega328timer1.h"

/*** Variable ***/
static TC1 setup_tc1;
static unsigned char timer1_state;

/*** Procedure and Function declaration ***/
void TIMER_COUNTER1_compoutmodeA(unsigned char compoutmode);
void TIMER_COUNTER1_compoutmodeB(unsigned char compoutmode);
void TIMER_COUNTER1_compareA(uint16_t compare);
void TIMER_COUNTER1_compareB(uint16_t compare);
void TIMER_COUNTER1_start(unsigned int prescaler);
void TIMER_COUNTER1_stop(void);

/*** Handler ***/
TC1 tc1_enable(unsigned char wavegenmode, unsigned char interrupt)
//	PARAMETER SETTING
//	wavegen mode: Normal; PWM, Phase Correct, 8-bit; PWM, Phase Correct, 9-bit; PWM, Phase Correct, 10-bit;
//	CTC; Fast PWM, 8-bit; Fast PWM, 9-bit; Fast PWM, 10-bit; PWM, Phase and Frequency Correct; PWM, Phase and Frequency Correct;
//	PWM, Phase Correct; PWM, Phase Correct; CTC; (Reserved); Fast PWM; Fast PWM.
//	interrupt: off; overflow; output compare; both; default - non.
//	for more information read data sheet.
{
	timer1_state = 0;
	tc1_reg()->tccr1a.var &= ~((1 << WGM11) | (1 << WGM10));
	tc1_reg()->tccr1b.var &= ~((1 << WGM13) | (1 << WGM12));
	switch(wavegenmode){
		case 0: // Normal
		break;
		case 1: // PWM, Phase Correct, 8-bit
			tc1_reg()->tccr1a.var |= (1 << WGM10);
		break;
		case 2:	// PWM, Phase Correct, 9-bit
			tc1_reg()->tccr1a.var |= (1 << WGM11);
		break;
		case 3:	// PWM, Phase Correct, 10-bit
			tc1_reg()->tccr1a.var |= (1 << WGM11) | (1 << WGM10);
		break;
		case 4:	// CTC
			tc1_reg()->tccr1b.var |= (1 << WGM12);
		break;
		case 5:	// Fast PWM, 8-bit
			tc1_reg()->tccr1a.var |= (1 << WGM10);
			tc1_reg()->tccr1b.var |= (1 << WGM12);
		break;
		case 6:	// Fast PWM, 9-bit
			tc1_reg()->tccr1a.var |= (1 << WGM11);
			tc1_reg()->tccr1b.var |= (1 << WGM12);
		break;
		case 7:	// Fast PWM, 10-bit
			tc1_reg()->tccr1a.var |= (1 << WGM11) | (1 << WGM10);
			tc1_reg()->tccr1b.var |= (1 << WGM12);
		break;
		case 8:	// PWM, Phase and Frequency Correct
			tc1_reg()->tccr1b.var |= (1 << WGM13);
		break;
		case 9:	// PWM, Phase and Frequency Correct
			tc1_reg()->tccr1a.var |= (1 << WGM10);
			tc1_reg()->tccr1b.var |= (1 << WGM13);
		break;
		case 10: // PWM, Phase Correct
			tc1_reg()->tccr1a.var |= (1 << WGM11);
			tc1_reg()->tccr1b.var |= (1 << WGM13);
		break;
		case 11: // PWM, Phase Correct
			tc1_reg()->tccr1a.var |= (1 << WGM11) | (1 << WGM10);
			tc1_reg()->tccr1b.var |= (1 << WGM13);
		break;
		case 12: // CTC
			tc1_reg()->tccr1b.var |= (1 << WGM13) | (1 << WGM12);
		break;
		case 13: // (Reserved)
			tc1_reg()->tccr1a.var |= (1 << WGM10);
			tc1_reg()->tccr1b.var |= (1 << WGM13) | (1 << WGM12);
		break;
		case 14: // Fast PWM
			tc1_reg()->tccr1a.var |= (1 << WGM11);
			tc1_reg()->tccr1b.var |= (1 << WGM13) | (1 << WGM12);
		break;
		case 15: // Fast PWM
			tc1_reg()->tccr1a.var |= (1 << WGM11) | (1 << WGM10);
			tc1_reg()->tccr1b.var |= (1 << WGM13) | (1 << WGM12);
		break;
		default: // Normal
		break;
	}
	tc1_reg()->tccr1a.var &= ~((3 << COM1A0) | (3 << COM1B0));
	tc_imask_reg()->timsk1.var &= ~((1 << ICIE1)  | (1 << OCIE1B) | (1 << OCIE1A) | (1 << TOIE1));
	switch(interrupt){
		case 0:
		break;
		case 1:
			tc_imask_reg()->timsk1.var |= (1 << TOIE1);
			cpu_reg()->sreg.var |= (1 << GLOBAL_INTERRUPT_ENABLE);
		break;
		case 2:
			tc_imask_reg()->timsk1.var |= (1 << OCIE1A);
			cpu_reg()->sreg.var |= (1 << GLOBAL_INTERRUPT_ENABLE);
		break;
		case 3:
			tc_imask_reg()->timsk1.var |= (1 << OCIE1B);
			cpu_reg()->sreg.var |= (1 << GLOBAL_INTERRUPT_ENABLE);
		break;
		case 4:
			tc_imask_reg()->timsk1.var |= (1 << ICIE1);
			cpu_reg()->sreg.var |= (1 << GLOBAL_INTERRUPT_ENABLE);
		break;
		case 5:
			tc_imask_reg()->timsk1.var |= (1 << OCIE1A) | (1 << OCIE1B);
			cpu_reg()->sreg.var |= (1 << GLOBAL_INTERRUPT_ENABLE);
		break;
		case 6:
			tc_imask_reg()->timsk1.var |= (1 << OCIE1A) | (1 << TOIE1);
			cpu_reg()->sreg.var |= (1 << GLOBAL_INTERRUPT_ENABLE);
		break;
		case 7:
			tc_imask_reg()->timsk1.var |= (1 << OCIE1B) | (1 << TOIE1);
			cpu_reg()->sreg.var |= (1 << GLOBAL_INTERRUPT_ENABLE);
		break;
		case 8:
			tc_imask_reg()->timsk1.var |= (1 << ICIE1) | (1 << TOIE1);
			cpu_reg()->sreg.var |= (1 << GLOBAL_INTERRUPT_ENABLE);
		break;
		case 9:
			tc_imask_reg()->timsk1.var |= (1 << OCIE1A) | (1 << OCIE1B) | (1 << TOIE1);
			cpu_reg()->sreg.var |= (1 << GLOBAL_INTERRUPT_ENABLE);
		break;
		case 10:
			tc_imask_reg()->timsk1.var |= (1 << ICIE1) | (1 << OCIE1A) | (1 << OCIE1B) | (1 << TOIE1);
			cpu_reg()->sreg.var |= (1 << GLOBAL_INTERRUPT_ENABLE);
		break;
		case 11:
			tc_imask_reg()->timsk1.var |= (1 << OCIE1A) | (1 << OCIE1B);
			cpu_reg()->sreg.var |= (1 << GLOBAL_INTERRUPT_ENABLE);
		break;
		default:
		break;
	}
	// V-table
	setup_tc1.compoutmodeA = TIMER_COUNTER1_compoutmodeA;
	setup_tc1.compoutmodeB = TIMER_COUNTER1_compoutmodeB;
	setup_tc1.compareA = TIMER_COUNTER1_compareA;
	setup_tc1.compareB = TIMER_COUNTER1_compareB;
	setup_tc1.start = TIMER_COUNTER1_start;
	setup_tc1.stop = TIMER_COUNTER1_stop;

	return setup_tc1;
}

TC1* tc1(void){ return &setup_tc1; }

/*** Procedure and Function definition ***/
void TIMER_COUNTER1_start(unsigned int prescaler)
//	PARAMETER SETTING
//	Frequency oscillator devision factor or prescaler.
//	prescaler: clk T0S /(No prescaling); clk T0S /8 (From prescaler); clk T0S /64 (From prescaler);
//	clk T0S /256 (From prescaler); clk T0S /1024 (From prescaler); External clock source on Tn pin. Clock on falling edge;
//	External clock source on Tn pin. Clock on rising edge; default - clk T 0 S /1024 (From prescaler).
{
	if(timer1_state == 0){ // one shot
		TIMER_COUNTER1_compareA(0xFFFF); // preset as max
		TIMER_COUNTER1_compareB(0xFFFF); // preset as max
		tc1_reg()->tccr1b.var &= ~(7 << CS10); // No clock source. (Timer/Counter stopped)
		switch(prescaler){
			case 1: // clkI/O/1 (No prescaler)
				tc1_reg()->tccr1b.var |= (1 << CS10);
			break;
			case 8: // clkI/O/8 (From prescaler)
				tc1_reg()->tccr1b.var |= (1 << CS11);
			break;
			case 64: // clkI/O/64 (From prescaler)
				tc1_reg()->tccr1b.var |= (3 << CS10);
			break;
			case 256: // clkI/O/256 (From prescaler)
				tc1_reg()->tccr1b.var |= (1 << CS12);
			break;
			case 1024: // clkI/O/1024 (From prescaler)
				tc1_reg()->tccr1b.var |= (5 << CS10);
			break;
			case 3: // External clock source on Tn pin. Clock on falling edge
				tc1_reg()->tccr1b.var |= (6 << CS10);
			break;
			case 5: // External clock source on Tn pin. Clock on rising edge
				tc1_reg()->tccr1b.var |= (7 << CS10);
			break;
			default: // clkI/O/1024 (From prescaler)
				tc1_reg()->tccr1b.var |= (5 << CS10);
			break;
		}
		timer1_state = 1;
	}	
}
void TIMER_COUNTER1_compoutmodeA(unsigned char compoutmode)
{
	tc1_reg()->tccr1a.var &= ~(3 << COM1A0);
	switch(compoutmode){ // see table 53, 54, 55 in data sheet for more information
		case 0: // Normal gpio operation, OC1 disconnected.
		break;
		case 1: // Reserved
				// Toggle OC1 on compare match
			gpiob_reg()->ddr.var |= (1 << 1);
			tc1_reg()->tccr1a.var |= (1 << COM1A0);
		break;
		case 2: // Clear OC1 on compare match when up-counting.
				// Set OC1 on compare
				// match when down counting.
				// Clear OC1 on compare match
			gpiob_reg()->ddr.var |= (1 << 1);
			tc1_reg()->tccr1a.var |= (1 << COM1A1);
		break;
		case 3: // Set OC1 on compare match when up-counting.
				// Clear OC1 on compare
				// match when down counting.
				// Set OC1 on compare match
			gpiob_reg()->ddr.var |= (1 << 1);
			tc1_reg()->tccr1a.var |= (1 << COM1A0) | (1 << COM1A1);
		break;
		default: // Normal gpio operation, OC1 disconnected.
		break;
	}
}
void TIMER_COUNTER1_compoutmodeB(unsigned char compoutmode)
{
	tc1_reg()->tccr1a.var &= ~(3 << COM1B0);
	switch(compoutmode){ // see table 53, 54, 55 in data sheet for more information
		case 0: // Normal gpio operation, OC1 disconnected.
		break;
		case 1: // Reserved
				// Toggle OC1 on compare match
			gpiob_reg()->ddr.var |= (1 << 2);
			tc1_reg()->tccr1a.var |= (1 << COM1B0);
		break;
		case 2: // Clear OC1 on compare match when up-counting.
				// Set OC1 on compare
				// match when down counting.
				// Clear OC1 on compare match
			gpiob_reg()->ddr.var |= (1 << 2);
			tc1_reg()->tccr1a.var |= (1 << COM1B1);
		break;
		case 3: // Set OC1 on compare match when up-counting.
				// Clear OC1 on compare
				// match when down counting.
				// Set OC1 on compare match
			gpiob_reg()->ddr.var |= (1 << 2);
			tc1_reg()->tccr1a.var |= (1 << COM1B0) | (1 << COM1B1);
		break;
		default: // Normal port operation, OC1 disconnected.
		break;
	}
}
void TIMER_COUNTER1_compareA(uint16_t compare)
{
	tc1_compare_reg()->ocr1a.var = writehlbyte(compare).var;
}
void TIMER_COUNTER1_compareB(uint16_t compare)
{
	tc1_compare_reg()->ocr1b.var = writehlbyte(compare).var;
}
void TIMER_COUNTER1_stop(void)
// stops timer by setting prescaler to zero
{
	tc1_reg()->tccr1b.var &= ~(7 << CS10); // No clock source. (Timer/Counter stopped)
	tc1_reg()->tcnt1.var = writehlbyte(0X0000).var;
	timer1_state = 0;
}

/*** EOF ***/

