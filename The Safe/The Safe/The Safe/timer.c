/*
 * timer.c
 *
 * Created: 26/04/2022 01:28:52 am
 *  Author: Bahaa Tawfik
 */
 
#include "std_macros.h"
#include <avr/io.h>
#include <avr/interrupt.h>
void timer_CTC_init_interrupt(void)
{
	/* select CTC mode*/
	SetBit(TCCR0,WGM01);
	/* load a value in OCR0 */
	OCR0=80;
	/* select timer clock */	
	SetBit(TCCR0,CS00);
	SetBit(TCCR0,CS02);
	/* enable interrupt*/
	sei();
	SetBit(TIMSK,OCIE0);
}


void timer_wave_nonPWM(void)
{
	/* set OC0 as output pin */
	SetBit(DDRB,3);
	/* select CTC mode*/
	SetBit(TCCR0,WGM01);
	/* load a value in OCR0 */
	OCR0=64;
	/* select timer clock */
	SetBit(TCCR0,CS00);
	SetBit(TCCR0,CS02);
	/* toggle OC0 on compare match*/
	SetBit(TCCR0,COM00);
}

void timer1_wave_fastPWM(double value)
{
	/* set OC1A as output pin */
	SetBit(DDRD,5);
	/* select fast PWM mode*/
	SetBit(TCCR1A,WGM11);
	SetBit(TCCR1B,WGM12);
	SetBit(TCCR1B,WGM13);
	/* load a value in OCR1A,ICR1 */
	OCR1A=value*1000;
	ICR1=19999;
	/* select timer clock, no prescaling */
	SetBit(TCCR1B,CS10);
	/* clear OC1A on compare match, set OC1A at BOTTOM,(non inverting mode)*/
	SetBit(TCCR1A,COM1A1);
}


void timer_wave_phasecorrectPWM(void)
{
	/* set OC0 as output pin */
	SetBit(DDRB,3);
	/* select phase correct PWM mode*/
	SetBit(TCCR0,WGM00);
	/* load a value in OCR0 */
	OCR0=64;
	/* select timer clock */
	SetBit(TCCR0,CS00);
	SetBit(TCCR0,CS02);
	/* Set OC0 on compare match when up-counting. Clear OC0 on compare match when down counting.*/
	SetBit(TCCR0,COM00);
	SetBit(TCCR0,COM01);
}
