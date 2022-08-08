/*
 * Calculator.c
 * Project Description : Simple Calculator make all basic calculation like (+,-,*,/) on two numbers which consist of 2 digits as maximum
 * Used Drivers : DIO - Keypad - LCD
 *Created: 26/04/2022 01:17:29 am
 *  Author: Bahaa Tawfik
 */ 


#include <avr/io.h>
#define  F_CPU 8000000UL
#include <util/delay.h>
#include "keypad.h"
#include "LCD.h"

int main(void)
{
	label: LCD_vInit() ;
	keypad_vInit();
	unsigned char counter=0;
	unsigned short res=0;
	unsigned  char arr[6]={NOTPRESSED,NOTPRESSED,NOTPRESSED,NOTPRESSED,NOTPRESSED,NOTPRESSED};
	
	
    while(1)
    {
		/*************************** check first digit of first Number *********************************************/ 
		do 
		{ 
			arr[counter]=keypad_u8check_press();
			
		} while (arr[counter]==NOTPRESSED);   // loop until fail the condition (as soon as button pressed i.e condition fail so out of the loop)
		
		// check to ensure that ==only== digit buttons is pressed i.e 0...9   
		if (arr[counter]=='/' ||arr[counter]=='*' ||arr[counter]=='-' ||arr[counter]=='+'||arr[counter]=='='||arr[counter]=='C')
		{
			LCD_vclearscreen();
			goto label;
		} 
		else
		{
			LCD_vsend_char(arr[counter]);	 	 //  send digit to lcd
		}
		counter++;
        _delay_ms(200); 
		
		/*************************** check 2nd digit of first Number *********************************************/ 		
		do
		{
			arr[counter]=keypad_u8check_press();
			
		} while (arr[counter]==NOTPRESSED);   // loop until fail the condition (as soon as button pressed i.e condition fail so out of the loop)
		
		// check to ensure that ==only== digit buttons is pressed i.e 0...9 
		if (arr[counter]=='/' ||arr[counter]=='*' ||arr[counter]=='-' ||arr[counter]=='+'||arr[counter]=='='||arr[counter]=='C')
		{
			LCD_vclearscreen();
			goto label;
		}
		else
		{
			LCD_vsend_char(arr[counter]);
		}
		counter++;
		_delay_ms(200);
		
		/*************************** check 3rd digit  i.e operation sign (+,-,*,/) *********************************************/ 	
		do
		{
			arr[counter]=keypad_u8check_press();
			
		} while (arr[counter]==NOTPRESSED);   // loop until fail the condition (as soon as button pressed i.e condition fail so out of the loop)
		
		//check to ensure that ==only== operation buttons is pressed i.e (+,-,*,/)
		if (arr[counter]=='=' ||arr[counter]=='C' ||arr[counter]=='0' ||arr[counter]=='1' ||arr[counter]=='2' ||arr[counter]=='3' ||
		    arr[counter]=='4' ||arr[counter]=='5' ||arr[counter]=='6' ||arr[counter]=='7' ||arr[counter]=='8' ||arr[counter]=='9')
		{
			LCD_vclearscreen();
			goto label;
		}
		else
		{
			LCD_vsend_char(arr[counter]);		//  send operation sign (+,-,*,/)  to lcd
		}
		counter++;
		_delay_ms(200);
		
		/***************************  check 1st digit of second Number *********************************************/ 		
		do
		{
			arr[counter]=keypad_u8check_press();
			
		} while (arr[counter]==NOTPRESSED);   // loop until fail the condition (as soon as button pressed i.e condition fail so out of the loop)
	
		//check to ensure that ==only== digit buttons is pressed i.e 0...9  
		if (arr[counter]=='/' ||arr[counter]=='*' ||arr[counter]=='-' ||arr[counter]=='+'||arr[counter]=='='||arr[counter]=='C')
		{
			LCD_vclearscreen();
			goto label;
		}
		else
		{
			LCD_vsend_char(arr[counter]);	 	 //  send digit to lcd
		}
		counter++;
		_delay_ms(200);
		
		/***************************  check 2nd digit of second Number *********************************************/
		do
		{
			arr[counter]=keypad_u8check_press();
			
		} while (arr[counter]==NOTPRESSED);   // loop until fail the condition (as soon as button pressed i.e condition fail so out of the loop)
		
		//check to ensure that only digit buttons is pressed i.e 0...9
		if (arr[counter]=='/' ||arr[counter]=='*' ||arr[counter]=='-' ||arr[counter]=='+'||arr[counter]=='='||arr[counter]=='C')
		{
			LCD_vclearscreen();
			goto label;
		}
		else
		{
			LCD_vsend_char(arr[counter]);	 	 //  send digit to lcd
		}
		counter++;
		_delay_ms(200);
		
		/***************************  check 5th digit i.e equal sign(=)  *********************************************/
		do
		{
			arr[counter]=keypad_u8check_press();
			
		} while (arr[counter]==NOTPRESSED);   // loop until fail the condition (as soon as button pressed i.e condition fail so out of the loop)
		
		//check to ensure that ==only== digit button equal sign(=)   is pressed 
		if (arr[counter]=='=')
		{
			LCD_vsend_char(arr[counter]);
			switch(arr[counter - 3]) //check which operation is pressed
			{
				
				
				/***************************  check 5th digit i.e equal sign(=)  *********************************************
				* Ex 73 + 85 = 158 .... so 1st digit=7 when counter=0   and 2nd digit=2 when counter=1 and 3rd digit=op+ when counter=2
				*						   1st digit of 2nd number=8 when counter=4     and  2nd digit of 2nd number=5 when counter=5 
				*					 ******************** ***************************************************
				*  send res=158 to LCD  ....  
				*
				*************************** (+) Operation ******************** *********************************************/
				
				case '+':
				res= ((arr[counter-5]-48)*10)+(arr[counter-4]-48) + ((arr[counter-2]-48)*10)+(arr[counter -1]-48) ;
				if (res>=100 && res<1000)
				{
					LCD_vsend_char((res/100) +48); 
					LCD_vsend_char( ((res/10)%10) +48);
					LCD_vsend_char( (res%10) +48);
				}
				else if(res>=10 && res<100)
				{
					LCD_vsend_char( (res/10) +48);
					LCD_vsend_char( (res%10) +48);				
				}
				else if (res<10)
				{
					LCD_vsend_char(res+48);
				}
				break;
				/************************** (-) Operation ******************** *********************************************/
				case '-':
				res= ( ((arr[counter-5]-48)*10)+(arr[counter-4]-48) ) - ( ((arr[counter-2]-48)*10)+(arr[counter -1]-48) ) ;
				if (res>=100 && res<1000)
				{
					LCD_vsend_char((res/100) +48);
					LCD_vsend_char( ((res/10)%10) +48);
					LCD_vsend_char( (res%10) +48);
				}
				else if(res>=10 && res<100)
				{
					LCD_vsend_char( (res/10) +48);
					LCD_vsend_char( (res%10) +48);
				}
				else if (res<10)
				{
					LCD_vsend_char(res+48);
				}
				break;
				/************************** (*) Operation ******************** *********************************************/
				case '*':
				res= ( ((arr[counter-5]-48)*10)+(arr[counter-4]-48) ) * ( ((arr[counter-2]-48)*10)+(arr[counter -1]-48) ) ;
				if (res>=100 && res<1000)
				{
					LCD_vsend_char((res/100) +48);
					LCD_vsend_char( ((res/10)%10) +48);
					LCD_vsend_char( (res%10) +48);
				}
				else if(res>=10 && res<100)
				{
					LCD_vsend_char( (res/10) +48);
					LCD_vsend_char( (res%10) +48);
				}
				else if (res<10)
				{
					LCD_vsend_char(res+48);
				}
				break;
				/************************** (/) Operation ******************** *********************************************/
				case '/':
				res= ( ((arr[counter-5]-48)*10)+(arr[counter-4]-48) ) / ( ((arr[counter-2]-48)*10)+(arr[counter -1]-48) ) ;
				if (res>=100 && res<1000)
				{
					LCD_vsend_char((res/100) +48);
					LCD_vsend_char( ((res/10)%10) +48);
					LCD_vsend_char( (res%10) +48);
				}
				else if(res>=10 && res<100)
				{
					LCD_vsend_char( (res/10) +48);
					LCD_vsend_char( (res%10) +48);
				}
				else if (res<10)
				{
					LCD_vsend_char(res+48);
				}
				break;
				default: break;								
			}	 //  end of switch
		} //  end of IF
		else
		{
			LCD_vclearscreen();
			goto label;	
		}
		_delay_ms(200);		
		
    }		//end of while loop
}			//end of main function 