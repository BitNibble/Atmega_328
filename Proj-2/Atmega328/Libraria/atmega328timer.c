/*************************************************************************
	TIMER
Author: Sergio Manuel Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: Atmega328 by ETT ET-BASE
Date: 26112022
Comment:
	Very Stable
*************************************************************************/
/*** File library ***/
#include "atmega328mapping.h"

/*** File Constant & Macro ***/
#if defined(__AVR_ATmega328__) || defined(__AVR_ATmega328P__)
#else
	#error "Not Atmega 328"
#endif

/*** File Variable ***/
ATMEGA328 mega328;

static unsigned char timer0_state;
static unsigned char timer1_state;
static unsigned char timer2_state;

/*** File Header ***/
void TIMER_COUNTER0_compoutmodeA(unsigned char compoutmode);
void TIMER_COUNTER0_compoutmodeB(unsigned char compoutmode);
void TIMER_COUNTER0_compareA(unsigned char compare);
void TIMER_COUNTER0_compareB(unsigned char compare);
void TIMER_COUNTER0_start(unsigned int prescaler);
void TIMER_COUNTER0_stop(void);

void TIMER_COUNTER1_compoutmodeA(unsigned char compoutmode);
void TIMER_COUNTER1_compoutmodeB(unsigned char compoutmode);
void TIMER_COUNTER1_compareA(uint16_t compare);
void TIMER_COUNTER1_compareB(uint16_t compare);
void TIMER_COUNTER1_start(unsigned int prescaler);
void TIMER_COUNTER1_stop(void);

void TIMER_COUNTER2_compoutmodeA(unsigned char compoutmode);
void TIMER_COUNTER2_compoutmodeB(unsigned char compoutmode);
void TIMER_COUNTER2_compareA(unsigned char compare);
void TIMER_COUNTER2_compareB(unsigned char compare);
void TIMER_COUNTER2_start(unsigned int prescaler);
void TIMER_COUNTER2_stop(void);

/*** Procedure & Function ***/
TIMER_COUNTER0 TIMER_COUNTER0enable(unsigned char wavegenmode, unsigned char interrupt)
//	PARAMETER SETTING
//	wavegen mode: Normal; PWM phase correct; Fast PWM; default-Normasl;
//	interrupt: off; overflow; output compare; both; default - non.
{
	TIMER_COUNTER0 timer0;
	mega328 = ATMEGA328enable();
	
	timer0_state = 0;
	mega328.tc0.reg->tccr0a &= ~((1 << WGM01) | (1 << WGM00));
	mega328.tc0.reg->tccr0b &= ~(1 << WGM02);
	switch(wavegenmode){
		case 0: // Normal
		break;
		case 1: // PWM, Phase Correct, 8-bit
			mega328.tc0.reg->tccr0a |= (1 << WGM00);
		break;
		case 2: // PWM, Phase Correct, 9-bit
			mega328.tc0.reg->tccr0a |= (1 << WGM01);
		break;
		case 3: // Fast PWM
			mega328.tc0.reg->tccr0a |= (1 << WGM00) | (1 << WGM01);
		break;
		case 5: // PWM, Phase Correct
			mega328.tc0.reg->tccr0a |= (1 << WGM00);
			mega328.tc0.reg->tccr0b |= (1 << WGM02);
		break;
		case 7: // Fast PWM
			mega328.tc0.reg->tccr0a |= (1 << WGM00) | (1 << WGM01);
			mega328.tc0.reg->tccr0b |= (1 << WGM02);
		break;
		default:
		break;
	}
	mega328.tc0.reg->timsk0 &= ~((1 << OCIE0B) | (1 << OCIE0A) | (1 << TOIE0));
	switch(interrupt){
		case 0: 
		break;
		case 1:
			mega328.tc0.reg->timsk0 |= (1 << TOIE0);
		break;
		case 2:
			mega328.tc0.reg->timsk0 |= (1 << OCIE0A);
		break;
		case 3:
			mega328.tc0.reg->timsk0 |= (1 << OCIE0B);
		break;
		case 4:
			mega328.tc0.reg->timsk0 |= (1 << TOIE0) | (1 << OCIE0A);
		break;
		case 5:
			mega328.tc0.reg->timsk0 |= (1 << TOIE0) | (1 << OCIE0B);
		break;
		case 6:
			mega328.tc0.reg->timsk0 |= (1 << TOIE0) | (1 << OCIE0A) | (1 << OCIE0B);
		break;
		case 7:
			mega328.tc0.reg->timsk0 |= (1 << OCIE0A) | (1 << OCIE0B);
		break;
		default:
		break;
	}
	timer0.compoutmodeA = TIMER_COUNTER0_compoutmodeA;
	timer0.compoutmodeB = TIMER_COUNTER0_compoutmodeB;
	timer0.compareA = TIMER_COUNTER0_compareA;
	timer0.compareB = TIMER_COUNTER0_compareB;
	timer0.start = TIMER_COUNTER0_start;
	timer0.stop = TIMER_COUNTER0_stop;
	return timer0;
}
void TIMER_COUNTER0_start(unsigned int prescaler)
//	PARAMETER SETTING
//	Frequency oscillator devision factor or prescaler.
//	prescaler: clk T0S /(No prescaling); clk T0S /8 (From prescaler); clk T0S /32 (From prescaler);
//	clk T0S /64 (From prescaler); clk T0S /128 (From prescaler); clk T 0 S /256 (From prescaler);
//	clk T 0 S /1024 (From prescaler); default - clk T 0 S /1024 (From prescaler).
{
	if(timer0_state == 0){ // one shot
		mega328.tc0.reg->ocr0a = 0XFF;
		mega328.tc0.reg->tccr0b &= ~(7 << CS00); // No clock source. (Timer/Counter stopped)
		switch(prescaler){
			case 1: // clk T0S /(No prescaler)
				mega328.tc0.reg->tccr0b |= (1 << CS00);
			break;
			case 8: // clk T0S /8 (From prescaler)
				mega328.tc0.reg->tccr0b |= (1 << CS01);
			break;
			case 64: // clk T0S /64 (From prescaler)
				mega328.tc0.reg->tccr0b |= (3 << CS00);
			break;
			case 256: // clk T 0 S /256 (From prescaler)
				mega328.tc0.reg->tccr0b |= (4 << CS00);
			break;
			case 1024: // clk T 0 S /1024 (From prescaler)
				mega328.tc0.reg->tccr0b |= (5 << CS00);
			break;
			case 3: // External clock source on T0 pin. Clock on falling edge.
				mega328.tc0.reg->tccr0b |= (6 << CS00);
			break;
			case 5: // External clock source on T0 pin. Clock on rising edge.
				mega328.tc0.reg->tccr0b |= (7 << CS00);
			break;
			default:
				mega328.tc0.reg->tccr0b |= (5 << CS00);
			break;
		}
		mega328.cpu.reg->sreg |= (1 << GLOBAL_INTERRUPT_ENABLE);
		timer0_state = 1;
	}	
}
void TIMER_COUNTER0_compoutmodeA(unsigned char compoutmode)
//	compoutmode: Normal port operation, OC0 disconnected; Toggle OC0 on compare match; 
//	Clear OC0 on compare match when up-counting. Set OC0 on compare match when downcounting. Clear OC0 on compare match;
//	Set OC0 on compare match when up-counting. Clear OC0 on compare match when downcounting. Set OC0 on compare match ;
//	default-Normal port operation, OC0 disconnected.
{
	mega328.tc0.reg->tccr0a &= ~((1 << COM0A0) | (1 << COM0A1));
	switch(compoutmode){
		case 0: // Normal port operation, OC0 disconnected.
		break;
		case 1: // Reserved
				// Toggle OC0 on compare match
			mega328.tc0.reg->tccr0a |= (1 << COM0A0);
		break;
		case 2: // Clear OC0 on compare match when up-counting. Set OC0 on compare
				// match when down counting.
				// Clear OC0 on compare match
			mega328.tc0.reg->tccr0a |= (1 << COM0A1);
		break;
		case 3: // Set OC0 on compare match when up-counting. Clear OC0 on compare
				// match when down counting.
				// Set OC0 on compare match
			mega328.tc0.reg->tccr0a |= (1 << COM0A0) | (1 << COM0A1);
		break;
		default:
		break;
	}
}
void TIMER_COUNTER0_compoutmodeB(unsigned char compoutmode)
//	compoutmode: Normal port operation, OC0 disconnected; Toggle OC0 on compare match; 
//	Clear OC0 on compare match when up-counting. Set OC0 on compare match when downcounting. Clear OC0 on compare match;
//	Set OC0 on compare match when up-counting. Clear OC0 on compare match when downcounting. Set OC0 on compare match ;
//	default-Normal port operation, OC0 disconnected.
{
	mega328.tc0.reg->tccr0a &= ~((1 << COM0B0) | (1 << COM0B1));
	switch(compoutmode){ // see table 53, 54, 55 in data sheet for more information
		case 0: // Normal port operation, OC0 disconnected.
		break;
		case 1: // Reserved
				// Toggle OC0 on compare match
			mega328.tc0.reg->tccr0a |= (1 << COM0B0);
		break;
		case 2: // Clear OC0 on compare match when up-counting. Set OC0 on compare
				// match when down counting.
				// Clear OC0 on compare match
			mega328.tc0.reg->tccr0a |= (1 << COM0B1);
		break;
		case 3: // Set OC0 on compare match when up-counting. Clear OC0 on compare
				// match when down counting.
				// Set OC0 on compare match
			mega328.tc0.reg->tccr0a |= (1 << COM0B0) | (1 << COM0B1);
		break;
		default:
		break;
	}
}
void TIMER_COUNTER0_compareA(unsigned char compare)
{
	mega328.tc0.reg->ocr0a = compare;
}
void TIMER_COUNTER0_compareB(unsigned char compare)
{
	mega328.tc0.reg->ocr0b = compare;
}
void TIMER_COUNTER0_stop(void)
// stops timer by setting prescaler to zero
{
	mega328.tc0.reg->tccr0b &= ~(7 << CS00); // No clock source. (Timer/Counter stopped)
	mega328.tc0.reg->tcnt0 = 0X00;
	timer0_state = 0;
}

TIMER_COUNTER1 TIMER_COUNTER1enable(unsigned char wavegenmode, unsigned char interrupt)
//	PARAMETER SETTING
//	wavegen mode: Normal; PWM, Phase Correct, 8-bit; PWM, Phase Correct, 9-bit; PWM, Phase Correct, 10-bit;
//	CTC; Fast PWM, 8-bit; Fast PWM, 9-bit; Fast PWM, 10-bit; PWM, Phase and Frequency Correct; PWM, Phase and Frequency Correct;
//	PWM, Phase Correct; PWM, Phase Correct; CTC; (Reserved); Fast PWM; Fast PWM.
//	interrupt: off; overflow; output compare; both; default - non.
//	for more information read data sheet.
{
	TIMER_COUNTER1 timer1;
	mega328 = ATMEGA328enable();
	
	timer1_state = 0;
	mega328.tc1.reg->tccr1a &= ~((1 << WGM11) | (1 << WGM10));
	mega328.tc1.reg->tccr1b &= ~((1 << WGM13) | (1 << WGM12));
	switch(wavegenmode){
		case 0: // Normal
		break;
		case 1: // PWM, Phase Correct, 8-bit
			mega328.tc1.reg->tccr1a |= (1 << WGM10);
		break;
		case 2:	// PWM, Phase Correct, 9-bit
			mega328.tc1.reg->tccr1a |= (1 << WGM11);
		break;
		case 3:	// PWM, Phase Correct, 10-bit
			mega328.tc1.reg->tccr1a |= (1 << WGM11) | (1 << WGM10);
		break;
		case 4:	// CTC
			mega328.tc1.reg->tccr1b |= (1 << WGM12);
		break;
		case 5:	// Fast PWM, 8-bit
			mega328.tc1.reg->tccr1a |= (1 << WGM10);
			mega328.tc1.reg->tccr1b |= (1 << WGM12);
		break;
		case 6:	// Fast PWM, 9-bit
			mega328.tc1.reg->tccr1a |= (1 << WGM11);
			mega328.tc1.reg->tccr1b |= (1 << WGM12);
		break;
		case 7:	// Fast PWM, 10-bit
			mega328.tc1.reg->tccr1a |= (1 << WGM11) | (1 << WGM10);
			mega328.tc1.reg->tccr1b |= (1 << WGM12);
		break;
		case 8:	// PWM, Phase and Frequency Correct
			mega328.tc1.reg->tccr1b |= (1 << WGM13);
		break;
		case 9:	// PWM, Phase and Frequency Correct
			mega328.tc1.reg->tccr1a |= (1 << WGM10);
			mega328.tc1.reg->tccr1b |= (1 << WGM13);
		break;
		case 10: // PWM, Phase Correct
			mega328.tc1.reg->tccr1a |= (1 << WGM11);
			mega328.tc1.reg->tccr1b |= (1 << WGM13);
		break;
		case 11: // PWM, Phase Correct
			mega328.tc1.reg->tccr1a |= (1 << WGM11) | (1 << WGM10);
			mega328.tc1.reg->tccr1b |= (1 << WGM13);
		break;
		case 12: // CTC
			mega328.tc1.reg->tccr1b |= (1 << WGM13) | (1 << WGM12);
		break;
		case 13: // (Reserved)
			mega328.tc1.reg->tccr1a |= (1 << WGM10);
			mega328.tc1.reg->tccr1b |= (1 << WGM13) | (1 << WGM12);
		break;
		case 14: // Fast PWM
			mega328.tc1.reg->tccr1a |= (1 << WGM11);
			mega328.tc1.reg->tccr1b |= (1 << WGM13) | (1 << WGM12);
		break;
		case 15: // Fast PWM
			mega328.tc1.reg->tccr1a |= (1 << WGM11) | (1 << WGM10);
			mega328.tc1.reg->tccr1b |= (1 << WGM13) | (1 << WGM12);
		break;
		default:
		break;
	}
	mega328.tc1.reg->tccr1a &= ~((3 << COM1A0) | (3 << COM1B0));
	mega328.tc1.reg->timsk1 &= ~((1 << ICIE1)  | (1 << OCIE1B) | (1 << OCIE1A) | (1 << TOIE1));
	switch(interrupt){
		case 0:
		break;
		case 1:
			mega328.tc1.reg->timsk1 |= (1 << TOIE1);
		break;
		case 2:
			mega328.tc1.reg->timsk1 |= (1 << OCIE1A);
		break;
		case 3:
			mega328.tc1.reg->timsk1 |= (1 << OCIE1B);
		break;
		case 4:
			mega328.tc1.reg->timsk1 |= (1 << ICIE1);
		break;
		case 5:
			mega328.tc1.reg->timsk1 |= (1 << OCIE1A) | (1 << OCIE1B);
		break;
		case 6:
			mega328.tc1.reg->timsk1 |= (1 << OCIE1A) | (1 << TOIE1);
		break;
		case 7:
			mega328.tc1.reg->timsk1 |= (1 << OCIE1B) | (1 << TOIE1);
		break;
		case 8:
			mega328.tc1.reg->timsk1 |= (1 << ICIE1) | (1 << TOIE1);
		break;
		case 9:
			mega328.tc1.reg->timsk1 |= (1 << OCIE1A) | (1 << OCIE1B) | (1 << TOIE1);
		break;
		case 10:
			mega328.tc1.reg->timsk1 |= (1 << ICIE1) | (1 << OCIE1A) | (1 << OCIE1B) | (1 << TOIE1);
		break;
		case 11:
			mega328.tc1.reg->timsk1 |= (1 << OCIE1A) | (1 << OCIE1B);
		break;
		default:
		break;
	}
	//
	timer1.compoutmodeA = TIMER_COUNTER1_compoutmodeA;
	timer1.compoutmodeB = TIMER_COUNTER1_compoutmodeB;
	timer1.compareA = TIMER_COUNTER1_compareA;
	timer1.compareB = TIMER_COUNTER1_compareB;
	timer1.start = TIMER_COUNTER1_start;
	timer1.stop = TIMER_COUNTER1_stop;
	return timer1;
}
void TIMER_COUNTER1_start(unsigned int prescaler)
//	PARAMETER SETTING
//	Frequency oscillator devision factor or prescaler.
//	prescaler: clk T0S /(No prescaling); clk T0S /8 (From prescaler); clk T0S /64 (From prescaler);
//	clk T0S /256 (From prescaler); clk T0S /1024 (From prescaler); External clock source on Tn pin. Clock on falling edge;
//	External clock source on Tn pin. Clock on rising edge; default - clk T 0 S /1024 (From prescaler).
{
	if(timer1_state == 0){ // one shot
		mega328.tc1.reg->ocr1a = mega328.writelhbyte(0xFFFF);
		mega328.tc1.reg->tccr1b &= ~(7 << CS10); // No clock source. (Timer/Counter stopped)
		switch(prescaler){
			case 1: // clkI/O/1 (No prescaler)
				mega328.tc1.reg->tccr1b |= (1 << CS10);
			break;
			case 8: // clkI/O/8 (From prescaler)
				mega328.tc1.reg->tccr1b |= (1 << CS11);
			break;
			case 64: // clkI/O/64 (From prescaler)
				mega328.tc1.reg->tccr1b |= (3 << CS10);
			break;
			case 256: // clkI/O/256 (From prescaler)
				mega328.tc1.reg->tccr1b |= (1 << CS12);
			break;
			case 1024: // clkI/O/1024 (From prescaler)
				mega328.tc1.reg->tccr1b |= (5 << CS10);
			break;
			case 3: // External clock source on Tn pin. Clock on falling edge
				mega328.tc1.reg->tccr1b |= (6 << CS10);
			break;
			case 5: // External clock source on Tn pin. Clock on rising edge
				mega328.tc1.reg->tccr1b |= (7 << CS10);
			break;
			default:
				mega328.tc1.reg->tccr1b |= (5 << CS10);
			break;
		}
		mega328.cpu.reg->sreg |= (1 << GLOBAL_INTERRUPT_ENABLE);
		timer1_state = 1;
	}	
}
void TIMER_COUNTER1_compoutmodeA(unsigned char compoutmode)
{
	mega328.tc1.reg->tccr1a &= ~(3 << COM1A0);
	switch(compoutmode){ // see table 53, 54, 55 in data sheet for more information
		case 0: // Normal port operation, OC0 disconnected.
		break;
		case 1: // Reserved
				// Toggle OC0 on compare match
			mega328.tc1.reg->tccr1a |= (1 << COM1A0);
		break;
		case 2: // Clear OC0 on compare match when up-counting. Set OC0 on compare
				// match when down counting.
				// Clear OC0 on compare match
			mega328.tc1.reg->tccr1a |= (1 << COM1A1);
		break;
		case 3: // Set OC0 on compare match when up-counting. Clear OC0 on compare
				// match when down counting.
				// Set OC0 on compare match
			mega328.tc1.reg->tccr1a |= (1 << COM1A0) | (1 << COM1A1);
		break;
		default:
		break;
	}
}
void TIMER_COUNTER1_compoutmodeB(unsigned char compoutmode)
{
	mega328.tc1.reg->tccr1a &= ~(3 << COM1B0);
	switch(compoutmode){ // see table 53, 54, 55 in data sheet for more information
		case 0: // Normal port operation, OC0 disconnected.
		break;
		case 1: // Reserved
				// Toggle OC0 on compare match
			mega328.tc1.reg->tccr1a |= (1 << COM1B0);
		break;
		case 2: // Clear OC0 on compare match when up-counting. Set OC0 on compare
				// match when down counting.
				// Clear OC0 on compare match
			mega328.tc1.reg->tccr1a |= (1 << COM1B1);
		break;
		case 3: // Set OC0 on compare match when up-counting. Clear OC0 on compare
				// match when down counting.
				// Set OC0 on compare match
			mega328.tc1.reg->tccr1a |= (1 << COM1B0) | (1 << COM1B1);
		break;
		default:
		break;
	}
}
void TIMER_COUNTER1_compareA(uint16_t compare)
{
	mega328.tc1.reg->ocr1a = mega328.writelhbyte(compare);
}
void TIMER_COUNTER1_compareB(uint16_t compare)
{
	mega328.tc1.reg->ocr1b = mega328.writelhbyte(compare);
}
void TIMER_COUNTER1_stop(void)
// stops timer by setting prescaler to zero
{
	mega328.tc1.reg->tccr1b &= ~(7 << CS10); // No clock source. (Timer/Counter stopped)
	mega328.tc1.reg->tcnt1 = mega328.writelhbyte(0X0000);
	timer1_state = 0;
}
/*****************************************************************************************/
TIMER_COUNTER2 TIMER_COUNTER2enable(unsigned char wavegenmode, unsigned char interrupt)
//	PARAMETER SETTING
//	wavegen mode: Normal; PWM phase correct; Fast PWM; default-Normasl;
//	interrupt: off; overflow; output compare; both; default - non.
{
	TIMER_COUNTER2 timer2;
	mega328 = ATMEGA328enable();
	
	timer2_state = 0;
	mega328.tc2.reg->tccr2a &= ~((1 << WGM21) | (1 << WGM20));
	mega328.tc2.reg->tccr2b &= ~(1<<WGM22);
	switch(wavegenmode){
		case 0: // Normal
		break;
		case 1: // PWM, Phase Correct
			mega328.tc2.reg->tccr2a |=(1 << WGM20);
		break;
		case 2: // CTC
			mega328.tc2.reg->tccr2a |= (1 << WGM21);
		break;
		case 3: // Fast PWM
			mega328.tc2.reg->tccr2a |= (1 << WGM20) | (1 << WGM21);
		break;
		case 5: // PWM, Phase Correct
			mega328.tc2.reg->tccr2a |= (1 << WGM20);
			mega328.tc2.reg->tccr2b |= (1 << WGM22);
		break;
		case 7: // Fast PWM
			mega328.tc2.reg->tccr2a |= (1 << WGM20) | (1 << WGM21);
			mega328.tc2.reg->tccr2b |= (1 << WGM22);
		break;
		default:
		break;
	}
	mega328.tc2.reg->timsk2 &= ~((1 << OCIE2B) | (1 << OCIE2A) | (1 << TOIE2));
	switch(interrupt){
		case 0: 
		break;
		case 1:
			mega328.tc2.reg->timsk2 |= (1 << TOIE2);
		break;
		case 2:
			mega328.tc2.reg->timsk2 |= (1 << OCIE2A);
		break;
		case 3:
			mega328.tc2.reg->timsk2 |= (1 << TOIE2) | (1 << OCIE2A);
		break;
		case 4:
			mega328.tc2.reg->timsk2 |= (1 << TOIE2) | (1 << OCIE2B);
		break;
		case 5:
			mega328.tc2.reg->timsk2 |= (1 << OCIE2B) | (1 << OCIE2A);
		break;
		case 6:
			mega328.tc2.reg->timsk2 |= (1 << OCIE2B) | (1 << OCIE2A) | (1 << TOIE2);
		break;
		default:
		break;
	}
	timer2.compoutmodeA = TIMER_COUNTER2_compoutmodeA;
	timer2.compoutmodeB = TIMER_COUNTER2_compoutmodeB;
	timer2.compareA = TIMER_COUNTER2_compareA;
	timer2.compareB = TIMER_COUNTER2_compareB;
	timer2.start = TIMER_COUNTER2_start;
	timer2.stop = TIMER_COUNTER2_stop;
	return timer2;
}
void TIMER_COUNTER2_start(unsigned int prescaler)
//	PARAMETER SETTING
//	Frequency oscillator devision factor or prescaler.
//	prescaler: clk T0S /(No prescaling); clk T0S /8 (From prescaler); clk T0S /64 (From prescaler);
//	clk T0S /256 (From prescaler); clk T0S /1024 (From prescaler); External clock source on Tn pin. Clock on falling edge;
//	External clock source on Tn pin. Clock on rising edge; default - clk T 0 S /1024 (From prescaler).
{
	if(timer2_state == 0){ // one shot
		mega328.tc2.reg->ocr2a = 0XFF;
		mega328.tc2.reg->tccr2b &= ~(7 << CS20); // No clock source. (Timer/Counter stopped)
		switch(prescaler){
			case 1: // clkI/O/(No prescaler)
				mega328.tc2.reg->tccr2b |= (1 << CS20);
			break;
			case 8: // clkI/O/8 (From prescaler)
				mega328.tc2.reg->tccr2b |= (1 << CS21);
			break;
			case 32: // clkI/O/32 (From prescaler)
				mega328.tc2.reg->tccr2b |= (1 << CS21) | (1 << CS20);
			break;
			case 64: // clkI/O/64 (From prescaler)
				mega328.tc2.reg->tccr2b |= (1 << CS22);
			break;
			case 128: // clkI/O/128 (From prescaler)
				mega328.tc2.reg->tccr2b |= (1 << CS22) | (1 << CS20);
			break;
			case 256: // clkI/O/256 (From prescaler)
				mega328.tc2.reg->tccr2b |= (1 << CS22) | (1 << CS21);
			break;
			case 1024: // clkI/O/1024 (From prescaler)
				mega328.tc2.reg->tccr2b |= (7 << CS20);
			break;
			default:
				mega328.tc2.reg->tccr2b |= (7 << CS20);
			break;
		}
		mega328.cpu.reg->sreg |= (1 << GLOBAL_INTERRUPT_ENABLE);
		timer2_state = 1;
	}	
}
void TIMER_COUNTER2_compoutmodeA(unsigned char compoutmode)
//	compoutmode: Normal port operation, OC0 disconnected; Toggle OC0 on compare match; 
//	Clear OC0 on compare match when up-counting. Set OC0 on compare match when downcounting. Clear OC0 on compare match;
//	Set OC0 on compare match when up-counting. Clear OC0 on compare match when downcounting. Set OC0 on compare match ;
//	default-Normal port operation, OC0 disconnected.
{
	mega328.tc2.reg->tccr2a &= ~((1 << COM2A0) | (1 << COM2A1));
	switch(compoutmode){ // see table 53, 54, 55 in data sheet for more information
		case 0: // Normal port operation, OC0 disconnected.
		break;
		case 1: // Reserved
				// Toggle OC0 on compare match
			mega328.tc2.reg->tccr2a |= (1 << COM2A0);
		break;
		case 2: // Clear OC0 on compare match when up-counting. Set OC0 on compare
				// match when down counting.
				// Clear OC0 on compare match
			mega328.tc2.reg->tccr2a |= (1 << COM2A1);
		break;
		case 3: // Set OC0 on compare match when up-counting. Clear OC0 on compare
				// match when down counting.
				// Set OC0 on compare match
			mega328.tc2.reg->tccr2a |= (1 << COM2A0) | (1 << COM2A1);
		break;
		default:
		break;
	}
}
void TIMER_COUNTER2_compoutmodeB(unsigned char compoutmode)
//	compoutmode: Normal port operation, OC0 disconnected; Toggle OC0 on compare match; 
//	Clear OC0 on compare match when up-counting. Set OC0 on compare match when downcounting. Clear OC0 on compare match;
//	Set OC0 on compare match when up-counting. Clear OC0 on compare match when downcounting. Set OC0 on compare match ;
//	default-Normal port operation, OC0 disconnected.
{
	mega328.tc2.reg->tccr2a &= ~((1 << COM2B0) | (1 << COM2B1));
	switch(compoutmode){ // see table 53, 54, 55 in data sheet for more information
		case 0: // Normal port operation, OC0 disconnected.
		break;
		case 1: // Reserved
				// Toggle OC0 on compare match
			mega328.tc2.reg->tccr2a |= (1 << COM2B0);
		break;
		case 2: // Clear OC0 on compare match when up-counting. Set OC0 on compare
				// match when down counting.
				// Clear OC0 on compare match
			mega328.tc2.reg->tccr2a |= (1 << COM2B1);
		break;
		case 3: // Set OC0 on compare match when up-counting. Clear OC0 on compare
				// match when down counting.
				// Set OC0 on compare match
			mega328.tc2.reg->tccr2a |= (1 << COM2B0) | (1 << COM2B1);
		break;
		default:
		break;
	}
}
void TIMER_COUNTER2_compareA(unsigned char compare)
{
	mega328.tc2.reg->ocr2a = compare;
}
	void TIMER_COUNTER2_compareB(unsigned char compare)
{
	mega328.tc2.reg->ocr2b = compare;
}
void TIMER_COUNTER2_stop(void)
// stops timer by setting prescaler to zero
{
	mega328.tc2.reg->tccr2b &= ~(7 << CS20); // No clock source. (Timer/Counter stopped)
	mega328.tc2.reg->tcnt2 = 0X00;
	timer2_state = 0;
}

/*** File Interrupt ***/
// ISR(TIMER2_COMPA_vect){}
// ISR(TIMER2_COMPB_vect){}
// ISR(TIMER2_OVF_vect){}
// ISR(TIMER1_CAPT_vect){}
// ISR(TIMER1_COMPA_vect){}
// ISR(TIMER1_COMPB_vect){}
// ISR(TIMER1_OVF_vect){}
// ISR(TIMER0_COMPA_vect){}
// ISR(TIMER0_COMPB_vect){}
// ISR(TIMER0_OVF_vect){}

/***EOF***/

