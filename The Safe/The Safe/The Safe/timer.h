/*
 * timer.h
 *
 * Created: 26/04/2022 01:12:12 am
 *  Author: Bahaa Tawfik
 */


#ifndef TIMER_H_
#define TIMER_H_
/*
	Function Name        : timer_CTC_init_interrupt
	Function Returns     : void
	Function Arguments   : void
	Function Description : initialize the interrupt of the CTC mode of timer0.
*/
void timer_CTC_init_interrupt(void);

/*
	Function Name        : timer_wave_nonPWM
	Function Returns     : void
	Function Arguments   : void
	Function Description : initialize the generation of a wave on OC0 pin in non PWM mode.
*/
void timer_wave_nonPWM(void);


/*
	Function Name        : timer_wave_PWM
	Function Returns     : void
	Function Arguments   : void
	Function Description : initialize the generation of a wave on OC0 pin in fast PWM mode.
*/
void timer1_wave_fastPWM(double value);

/*
	Function Name        : timer_wave_phasecorrectPWM
	Function Returns     : void
	Function Arguments   : void
	Function Description : initialize the generation of a wave on OC0 pin in phase correct PWM mode.
*/

void timer_wave_phasecorrectPWM(void);
#endif /* TIMER_H_ */