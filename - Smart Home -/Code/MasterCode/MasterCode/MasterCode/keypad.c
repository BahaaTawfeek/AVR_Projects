/*
 * keypad.c
 *
 * Created: 26/04/2022 01:24:43 am
 *  Author: Bahaa Tawfik
 */
#include "keypad.h"
#define  F_CPU 8000000UL 
#include <util/delay.h>


/*
 *Function Description : Initialize the Keypad
 */

void keypad_vInit()
{
	DIO_vsetPinDir('D',0,1); // make first 4 pins as output
	DIO_vsetPinDir('D',1,1); 
	DIO_vsetPinDir('D',2,1); 
	DIO_vsetPinDir('D',3,1); 
	DIO_vsetPinDir('D',4,0); // make first 4 pins as input
	DIO_vsetPinDir('D',5,0); 
	DIO_vsetPinDir('D',6,0); 
	DIO_vsetPinDir('D',7,0); 
	DIO_vconnectPullup('D',4,1);     //  make all input pin as a pullup as microcontroller has internal pullup   
	DIO_vconnectPullup('D',5,1);       
	DIO_vconnectPullup('D',6,1);
	DIO_vconnectPullup('D',7,1);
	
}


char keypad_u8check_press()
{
	char arr[4][4]={{'7','8','9','/'},
					{'4','5','6','*'},
					{'1','2','3','-'},
					{'C','0','=','+'}
		       	   };					 // Array represent buttons of Keypad
	
	char row,column,x ,returnval= NOTPRESSED;
	
	for(row=0;row<4;row++)
	{
		DIO_vwritePin('D',0,1);
		DIO_vwritePin('D',1,1);
		DIO_vwritePin('D',2,1);
		DIO_vwritePin('D',3,1);
		DIO_vwritePin('D',row,0);    // to make only one row=0 and the rest rows one to determine in which rows button is pressed
		
		for(column=0;column<4;column++)
		{
			x=DIO_u8readPin('D',(column+4));   // to determine in which columns button is pressed
			if (x==0)					 // check switch is pressed . Zero due to pull-up
			{
				_delay_ms(20);      // for bouncing  
				while(DIO_u8readPin('D',(column+4)) == 0);  //for scan press only one time .....the delay of pressing
				
				returnval=arr[row][column];
				break;             // to break (stop) 2nd loop and return 1st for
			}
		}
		if (x==0)
		{
			break;
		}						
	}
	return returnval ; 		
}