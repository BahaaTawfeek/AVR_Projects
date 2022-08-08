/*
 * SlaveCode.c
 *
 * Created: 16/07/2022 12:31
 *  Author: Bahaa Tawfik
 */



#include <avr/io.h>
#include "std_macros.h"
#include "STD_MESSAGES.h"
#include "DIO.h"
#include "LED.h"
#include "timer_driver.h"
#include "ADC_driver.h"
#include "SPI_driver.h"

#define DUMMY_DATA    0xFF




volatile unsigned short required_temperature = 24; // the required temperature which sent from Master with initial value 24
volatile unsigned short  temp_sensor_reading= 0; // the temperature of the room
volatile unsigned char counter = 0; // the counter which determine the periodic time of implementing ISR
volatile unsigned char last_air_conditioning_value = 0; // 0->AIR_CONDTIONING_OFF and 1->ON last air conditioning value which will help in hysteresis


int main(void)
{
	
	/*****************  INITIALIZE  ***********************/
	SPI_SlaveInit();//initialize the SPI as a slave
	ADC_vinit();//initialize the ADC of the micro controller
	LED_vInit('D',2);//initialize Led of  AIR_COND_PIN 7
	LED_vInit('D',3);//initialize Led of  TV_PIN 7
	LED_vInit('D',4);//initialize Led of  ROOM1_PIN 4
	LED_vInit('D',5);//initialize Led of  ROOM1_PIN 5
	LED_vInit('D',6);//initialize Led of  ROOM1_PIN 6
	LED_vInit('D',7);//initialize Led of  ROOM1_PIN 7
	timer0_initializeCTC();//Initialize the timer zero of the micro controller
	
	/******************************************************/
	
	unsigned char request = 1;//the value that is received from the master
	unsigned char response = 1;//the values that is sent back to the master
	unsigned char Status = 0; // it's default value 0 as off and 1 as ON
	unsigned char TurnOn= 1;  //1 as ON
	unsigned char TurnOff = 0; // 0 as off
	
	
    while(1)
    {
		request = SPI_Receivechar(Slave_ACK);//wait for the master to start the transmitting
		switch(request)
		{
			/************************************************************************/
			/*								ROOM1                                        */
			/************************************************************************/
			case ROOM1_STATUS:  //to send the current status of room 1 back to the master
			
			if (LED_u8ReadStatus('D',4)==1)//if the led of ROOM1 is turned on
			{
				response = 1;//set the response as on status
			}
			else if (LED_u8ReadStatus('D',4)==0)//if the led of ROOM1 is turned off
			{
				response = 0 ;//set the response as off status
			}
			SPI_Transmitchar(response);//response to the transmitter with the status
			
			break;//break the switch case
			
			case ROOM1_TURN_ON:
			LED_vTurnOn('D',4);//turn on the led of room 1
			break;
			case ROOM1_TURN_OFF:
			LED_vTurnOff('D',4);//turn off the led of room 1
			break;
			
			/************************************************************************/
			/*								ROOM2                                        */
			/************************************************************************/
			case ROOM2_STATUS:  //to send the current status of room 2 back to the master
			
			if (LED_u8ReadStatus('D',5)==1)//if the led of ROOM2 is turned on
			{
				response = 1;//set the response as on status
			}
			else if (LED_u8ReadStatus('D',5)==0)//if the led of ROOM2 is turned off
			{
				response = 0 ;//set the response as off status
			}
			SPI_Transmitchar(response);//response to the transmitter with the status
			
			break;//break the switch case
			
			case ROOM2_TURN_ON:
			LED_vTurnOn('D',5);//turn on the led of room 2
			break;
			case ROOM2_TURN_OFF:
			LED_vTurnOff('D',5);//turn off the led of room 2
			break;
			/************************************************************************/
			/*								ROOM3                                       */
			/************************************************************************/
			case ROOM3_STATUS:  //to send the current status of room 3 back to the master
			
			if (LED_u8ReadStatus('D',6)==1)//if the led of ROOM3 is turned on
			{
				response = 1;//set the response as on status
			}
			else if (LED_u8ReadStatus('D',6)==0)//if the led of ROOM3 is turned off
			{
				response = 0 ;//set the response as off status
			}
			SPI_Transmitchar(response);//response to the transmitter with the status
			
			break;//break the switch case
			
			case ROOM3_TURN_ON:
			LED_vTurnOn('D',6);//turn on the led of room 3
			break;
			case ROOM3_TURN_OFF:
			LED_vTurnOff('D',6);//turn off the led of room 3
			break;
			/************************************************************************/
			/*								ROOM4                                        */
			/************************************************************************/
			case ROOM4_STATUS:  //to send the current status of room4 back to the master
			
			if (LED_u8ReadStatus('D',7)==1)//if the led of ROOM4 is turned on
			{
				response = 1;//set the response as on status
			}
			else if (LED_u8ReadStatus('D',7)==0)//if the led of ROOM4 is turned off
			{
				response = 0 ;//set the response as off status
			}
			SPI_Transmitchar(response);//response to the transmitter with the status
			
			break;//break the switch case
			
			case ROOM4_TURN_ON:
			LED_vTurnOn('D',7);//turn on the led of room 4
			break;
			case ROOM4_TURN_OFF:
			LED_vTurnOff('D',7);//turn off the led of room 4
			break;
			/************************************************************************/
			/*								TV                                        */
			/************************************************************************/
			case TV_STATUS:  //to send the current status of TV  back to the master
			
			if (LED_u8ReadStatus('D',3)==1)//if the led of TV  is turned on
			{
				response = 1;//set the response as on status
			}
			else if (LED_u8ReadStatus('D',3)==0)//if the led of TV  is turned off
			{
				response = 0 ;//set the response as off status
			}
			SPI_Transmitchar(response);//response to the transmitter with the status
			
			break;//break the switch case
			
			case TV_TURN_ON:
			LED_vTurnOn('D',3);//turn on the led of TV 
			break;
			case TV_TURN_OFF:
			LED_vTurnOff('D',3);//turn off the led of TV 
			break;
			/************************************************************************/
			/*								AIR CONDITON                                        */
			/************************************************************************/
			case AIR_COND_STATUS:  //to send the current status of AIR CONDITON   back to the master
			
			if (LED_u8ReadStatus('D',2)==1)//if the led of AIR CONDITON   is turned on
			{
				response = 1;//set the response as on status
			}
			else if (LED_u8ReadStatus('D',2)==0)//if the led of AIR CONDITON   is turned off
			{
				response = 0 ;//set the response as off status
			}
			SPI_Transmitchar(response);//response to the transmitter with the status
			
			break;//break the switch case
			
			case AIR_COND_TURN_ON:
			timer0_initializeCTC();
			LED_vTurnOn('D',2);//turn on the led of  AIR CONDITON  
			break;
			case AIR_COND_TURN_OFF:
			timer0_stop();
			LED_vTurnOff('D',2);//turn off the led of AIR CONDITON  
			break;
			
			/*********************************   Set temperature   ********************************/
			case SET_TEMPERATURE://case of receive--> the Sending  code of set temperature from master
			required_temperature = SPI_Receivechar(Slave_ACK);//get the temperature from the master and store the temperature in required temperature
			break;//break the switch case
			
			
			
			
			
			
			
			
			
		}// end of switch
		
      
    }// end of while (1)
				
} // end of main function



ISR(TIMER0_COMP_vect)
{
	counter++;//count the ticks of the timer zero
	if(counter>=10)//do that code every 10 ticks
	{
		counter=0;//clear the counter of ticks
		temp_sensor_reading=(0.25*ADC_u16Read(0));//read the temperature from the temperature sensor connected to the ADC of the micro controller
		if (temp_sensor_reading>=(required_temperature+1))//do that code if the read temperature if greater than required temperature by one or more
		{
			LED_vTurnOn('D',2);//turn on the led of the air conditioning
			last_air_conditioning_value=1;//save the value of the state of the air conditioning"AIR_CONDTIONING_ON"
		}
		else if (temp_sensor_reading<=(required_temperature-1))//do that code if the read temperature if lesser than required temperature by one or more
		{
			LED_vTurnOff('D',2);//turn off the led of the air conditioning
			last_air_conditioning_value=0;//save the value of the state of the air conditioning"AIR_CONDTIONING_OFF"
		}
		
		else if (required_temperature==temp_sensor_reading)//do that code if the read temperature is equal to the required temperature
		{
			if (last_air_conditioning_value==1)//in the case of the last saved status of the air conditioning was on
			{
				LED_vTurnOn('D',2);//turn on the led of the air conditioning
			}
			else if (last_air_conditioning_value==0)//in the case of the last saved status of the air conditioning was off
			{
				LED_vTurnOff('D',2);//turn off the led of the air conditioning
			}
		}//end of else
	}//end of if
} // end of ISR

				