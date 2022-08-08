/*
 * servo_motor.c
 *
 * Created: 26/04/2022 01:21:42 am
 *  Author: Bahaa Tawfik
 */


#include <avr/io.h>
#define F_CPU 1000000UL
#include <util/delay.h>
#include "servo motor.h"



void vservo_Motor(void)
{
		timer1_wave_fastPWM(2);  //  a pulse of >= 2ms will move the shaft clockwise at+90
		_delay_ms(1000);
}



