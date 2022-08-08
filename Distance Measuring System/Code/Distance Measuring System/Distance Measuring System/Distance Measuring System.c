/*
 * Distance_Measuring_System.c
 
 
 
 *
 * Created: 27/05/2022 02:51:21 
 *  Author: Bahaa Tawfik    / / 
 */ 

#include <avr/io.h>
#include "LCD.h"
#define  F_CPU 1000000UL
#include <util/delay.h>
int main(void)
{
	
	LCD_vInit();
	unsigned short a,b,high,distance;
	
	DIO_vsetPinDir('D',7,1);			// make a direction of trigger pin of Ultrasonic Sensor is output pin
	DIO_vsetPinDir('D',6,0);			// make a direction of echo pin of Ultrasonic Sensor is output pin
	

	while(1)
	{
		TCCR1A=0;		/* Set all bit to zero Normal operation */
		TIFR = 1<<ICF1;				/* Clear ICP flag (Input Capture flag) */
        /* Give  more than 10us trigger pulse on trig. pin to US */
        DIO_vwritePin('D',7,1);
        _delay_us(50);
        DIO_vwritePin('D',7,0);
        _delay_us(50);			// not need 
		
		TCCR1B = 0xc1;				/* Capture on rising edge, No prescaler, noise cancel*/ 
		while ((TIFR&(1<<ICF1)) == 0);		//mentor ICF falg until set ===== note () is important for periorty 
		a=ICR1;					  // Take value of capute register
		TIFR=(1<<ICF1);			 // clear ICF1 flag
		
		TCCR1B= 0x81;		/* Capture on failing edge, No prescaler, noise cancel*/
		while ((TIFR&(1<<ICF1)) == 0);		//mentor ICF falg until set ===== note () is important for periorty 
		b=ICR1;					  // Take value of capute register
		TIFR=(1<<ICF1);			 // clear ICF1 flag
		TCNT1=0;		// Clear Timer counter 
		TCCR1B=0;		// stop timer

/*Calculation (distance in cm) 
 *Sound velocity =   343.00 m/s = 34300 cm/s
 */	
		high=b-a;
		distance = ((high*34600)/(F_CPU*2)) ;     
		
		if (distance<=80)
		{
			LCD_vclearscreen();
			LCD_vsend_string("distance=");
			LCD_vsend_char((distance/10)+48);
			LCD_vsend_char((distance%10)+48);
			LCD_vsend_string("cm");
			_delay_ms(500);	
		}
		else
		{
			LCD_vclearscreen();
			LCD_vsend_string("No Object Found,");
			LCD_vmovecursor(2,0);
			LCD_vsend_string("MaxDetect.. 80cm"); 
			_delay_ms(500);		
		}
	}//end of while
}//end of main function


