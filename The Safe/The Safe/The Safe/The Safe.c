/*
 * The_Safe.c
 *
 * Created: 08/05/2022 09:44:03 م
 *  Author: Bahaa
 */

#include <avr/io.h>
#define  F_CPU 1000000UL
#include <util/delay.h>
#include "EEPROM.h"
#include "LCD.h"
#include "keypad.h"
#include "servo motor.h"


#define  EEPROM_STATUS_LOCATION 0x20			//status location indicate that the first time enter safa app to appear msg"set pass:" or not
#define  EEPROM_PASSWORD_LOCATION1 0x21			 // represent to 1st Digit of pass
#define  EEPROM_PASSWORD_LOCATION2 0x22			 // represent to 2nd Digit of pass
#define  EEPROM_PASSWORD_LOCATION3 0x23			// represent to 3rd Digit of pass
#define  EEPROM_PASSWORD_LOCATION4 0x24			// represent to 4th Digit pf pass
#define MAX_TRIES 3				// no of max tries to reenter pass if entered in a wrong form

char arr[4]={NOTPRESSED};

int main(void)
{
	LCD_vInit();
	keypad_vInit();
	char value=NOTPRESSED;  	 //  default value 0xff = 0b1111,1111 of all locations in EEPROM
	char flag=0,i;
	char tries=MAX_TRIES;
	
	if (EEPROM_u8read(EEPROM_STATUS_LOCATION)==NOTPRESSED)	  // if read a EEPROM_STATUS_LOCATION as a default 0xff = 0b1111,1111  that mean no thing is writen HERE
	{
		LCD_vsend_string("Set Pass:");			// set pass:- consist of 4 Digit that enter via for loop 
		for (i=0;i<=3;i++)
		{
			do
			{
				value=keypad_u8check_press();
			} while (value==NOTPRESSED);						
			LCD_vsend_char(value);	
			_delay_ms(500);		
			LCD_vmovecursor(1,9+i);			// column10 as start count from zero 9+i as "set pass:" string 9 character and no.10 is the 1st digit of it's pass
			LCD_vsend_char('*');				// put "*" in the 1st digit of it's pass
			_delay_ms(500);	
			EEPROM_vwrite(EEPROM_PASSWORD_LOCATION1+i,value);		// put the value of the 1st digit of it's pass in location of EEPROM to keep it after power off					
	  }//end for
	  EEPROM_vwrite(EEPROM_STATUS_LOCATION,0x00);		//  to indicate that EEPROM_STATUS_LOCATION is writen     not as a default 0xff = 0b1111,1111  that mean no thing is writen HERE		
	}//end if
	
	
	while(flag==0)		//if (EEPROM_u8read(EEPROM_STATUS_LOCATION)==0x00) if read a EEPROM_STATUS_LOCATION as NOT AS a default 0xff = 0b1111,1111  that mean thing is writen HERE
	{	//arr[0]=arr[1]=arr[2]=arr[3]=NOTPRESSED;	
		LCD_vclearscreen();
		LCD_vsend_string("check pass:");
		for (i=0;i<=3;i++)
		{
			do
			{
				arr[i]=keypad_u8check_press();		// check pass:- enter your pass that consist of 4 Digit that enterd when "set pass" in the first time open the Safe app 
			} while (arr[i]==NOTPRESSED);			
			LCD_vsend_char(arr[i]);
			_delay_ms(500);
			LCD_vmovecursor(1,11+i);		// column11 as start count from zero  12+i as "check pass:" string 11 character and no.12 is the 1st digit of it's pass
			LCD_vsend_char('*');
			_delay_ms(500);
		}//end for				
	
	/*********************************************  match pass that saved in EEPROM via "set pass" with pass that enterd via "check pass"  ******************************************************/
		if(EEPROM_u8read(EEPROM_PASSWORD_LOCATION1)==arr[0] &&  EEPROM_u8read(EEPROM_PASSWORD_LOCATION2)==arr[1] && EEPROM_u8read(EEPROM_PASSWORD_LOCATION3)==arr[2] && EEPROM_u8read(EEPROM_PASSWORD_LOCATION4)==arr[3])
		{
			LCD_vclearscreen();
			LCD_vsend_string("true password");
			LCD_vmovecursor(2,1);
			LCD_vsend_string("safe opened^-^");
			
			vservo_Motor();		// move the direction of servo motor to angle 90 clockwise			
			
			flag=1;
		}
		else
		{
			tries=tries-1;
			if (tries>0)
			{
				LCD_vclearscreen();
				LCD_vsend_string("wrong password");
				_delay_ms(1000);
				LCD_vclearscreen();
				LCD_vsend_string("tries left:");
				LCD_vsend_char(tries+48);
				_delay_ms(1000);				
			}
			else
			{
				LCD_vclearscreen();
				LCD_vsend_string("wrong password");
				LCD_vmovecursor(2,1);
				LCD_vsend_string("safe closed");
				flag=1;
			}//end of else
		}//end of else
   }//end of while
	      
} //end main Func.