/*
 * ADC_driver.c
 *
 * Created: 29/04/2022 
 *  Author: Bahaa Tawfik
 */

#include <avr/io.h>
#include "std_macros.h"

/*	Function Description : Initialize ADC          */
void ADC_vinit(void)
{
	/* to increase the accurse of ADC 
	 *configure VREF to the internal voltage(2.56 V)*/
	SetBit(ADMUX,REFS0);
	SetBit(ADMUX,REFS1);
	
	SetBit(ADCSRA,ADEN); // enable ADC
   /* adjust ADC clock =ps=64  */
	SetBit(ADCSRA,ADPS2);
	SetBit(ADCSRA,ADPS1);
}



/*	Function Description : read ADC value after conversion         */
 unsigned short ADC_u16Read( unsigned char pinnumber )
{
	 unsigned short read_val;

	ADMUX |=pinnumber;    // Select the input to the ADC (channel)
	
	SetBit(ADCSRA,ADSC); // Start conversion 
	while(Is_Bit_Clear(ADCSRA,ADIF));//stay in your position till ADIF become 1
// Stay here till the H.W raise the ADC Flag after end of conversion 
// while((ADCSRA&(1<<ADIF))==0);     or     while (!(ADCSRA & (1<<ADIF)));

	SetBit(ADCSRA,ADIF); // clear ADIF
	read_val=(ADCL);
	read_val|=(ADCH<<8);
	return read_val ;    // return the value that been read after conversion
}