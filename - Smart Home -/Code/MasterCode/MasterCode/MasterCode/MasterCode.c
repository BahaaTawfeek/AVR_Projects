/*
 * MasterCode.c
 *
 * Created: 16/07/2022 12:31:32 
 *  Author: Bahaa Tawfik
 */ 


#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include "EEPROM.h"
#include "LCD.h"
#include "keypad.h"
#include "SPI_driver.h"
#include "STD_MESSAGES.h"

#define  EEPROM_ADMIN_STATUS_LOCATION 0x20			//status location indicate that the first time enter SmartHome System app to appear msg"set Admin pass:" or not
#define  EEPROM_ADMIN_PASSWORD_LOCATION1 0x21			 // represent to 1st Digit of Admin pass
#define  EEPROM_ADMIN_PASSWORD_LOCATION2 0x22			 // represent to 2nd Digit of Admin pass
#define  EEPROM_ADMIN_PASSWORD_LOCATION3 0x23			// represent to 3rd Digit of Admin pass
#define  EEPROM_ADMIN_PASSWORD_LOCATION4 0x24			// represent to 4th Digit of Admin  pass

#define  EEPROM_GUEST_STATUS_LOCATION 0x25			//status location indicate that the first time enter SmartHome System app to appear msg"set GUEST pass:" or not
#define  EEPROM_GUEST_PASSWORD_LOCATION1 0x26			 // represent to 1st Digit of GUEST pass
#define  EEPROM_GUEST_PASSWORD_LOCATION2 0x27			 // represent to 2nd Digit of GUEST pass
#define  EEPROM_GUEST_PASSWORD_LOCATION3 0x28			// represent to 3rd Digit of GUEST pass
#define  EEPROM_GUEST_PASSWORD_LOCATION4 0x29			// represent to 4th Digit of GUEST  pass

#define EEPROM_LOGIN_BLOCKED_LOCATION    0X30		// location indicate that login Block


#define BLOCK_MODE_TIME		   (unsigned long)20000
#define MAX_TRIES 3				// no of max tries to reenter pass if entered in a wrong form

char arr[4]={NOTPRESSED};





int main(void)
{
	
	char value=NOTPRESSED;  	 //  default value 0xff = 0b1111,1111 of all locations in EEPROM
	char mode = NOTPRESSED;
	char flag=0,i;
	char block_mode_flag = 0; //is 1 if the login is blocked or 0 if not blocked
	char tries=MAX_TRIES;
	
	/*****************  INITIALIZE  ***********************/
	LED_vInit('C',0);	//initializes the led of admin
	LED_vInit('C',1);	//initializes the led of guest
	LED_vInit('C',2);	//initializes the led of block
	LCD_vInit();	//initializes the LCD screen
	keypad_vInit();	//initializes the keypad
	SPI_MasterInit();	//initializes the communication protocol of SPI
	/******************************************************/
	
	/* Printing Welcome screen */	
	LCD_vsend_string("Welcome To Home");
	LCD_vmovecursor(2,1);
	LCD_vsend_string("Home System");
	_delay_ms(1000);	// delay the system for time in (ms)   
	LCD_vclearscreen();
/***************************/
/*Setting Admin and Guest passwords if not set */
//read the state of the the passwords of the admin and guest if both are set or not set
// if read a EEPROM_STATUS_LOCATION as a default 0xff = 0b1111,1111  that mean no thing is written HERE
	if ( (EEPROM_u8read(EEPROM_ADMIN_STATUS_LOCATION)== NOTPRESSED) || (EEPROM_u8read(EEPROM_GUEST_STATUS_LOCATION)== NOTPRESSED) )
	{
		LCD_vsend_string("Login for");	//printing login menu
		LCD_vmovecursor(2,1);	//move the cursor to the second line
		LCD_vsend_string("first time");
		_delay_ms(1000);	//delay the system for time in (ms)
		LCD_vclearscreen();		//remove all previously printed characters on the LCD and move the cursor to the first column of the first row
		LCD_vsend_string("Set Admin Pass");  //printing the set admin password menu
		LCD_vmovecursor(2,1);
		LCD_vsend_string("Admin Pass:");  // set pass:- consist of 4 Digit that enter via for loop
	
		/********************************* setting Admin password **********************************************/
		for (i=0;i<=3;i++)
		{
			do
			{
				value=keypad_u8check_press();
			} while (value==NOTPRESSED);
			LCD_vsend_char(value);
			_delay_ms(300);
			LCD_vmovecursor(2,12+i);			// column12 as start count from zero 12+i as "Admin Pass:" string 11 character and no.12 is the 1st digit of it's pass
			LCD_vsend_char('*');				// put "*" in the 1st digit of it's pass
			_delay_ms(100);
			EEPROM_vwrite(EEPROM_ADMIN_PASSWORD_LOCATION1+i,value);		// put the value of the 1st digit of it's pass in location of EEPROM to keep it after power off
		}//end for
		EEPROM_vwrite(EEPROM_ADMIN_STATUS_LOCATION,0x00);		//  to indicate that EEPROM_ADMIN_STATUS_LOCATION is written   not as a default 0xff = 0b1111,1111  that mean no thing is writen HERE
		LCD_vclearscreen();
		LCD_vsend_string("Pass Saved");// show pass saved message
		_delay_ms(500);//delay the system for time in (ms)
		LCD_vclearscreen();



		/********************************* setting guest password **********************************************/

		LCD_vsend_string("Set Guest Pass");//printing the set GUEST password menu
		LCD_vmovecursor(2,1);
		LCD_vsend_string("Guest Pass:");

		for (i=0;i<=3;i++)
		{
			do
			{
				value=keypad_u8check_press();
			} while (value==NOTPRESSED);
			LCD_vsend_char(value);
			_delay_ms(300);
			LCD_vmovecursor(2,12+i);			// column12 as start count from zero 12+i as "Guest Pass:" string 11 character and no.12 is the 1st digit of it's pass
			LCD_vsend_char('*');				// put "*" in the 1st digit of it's pass
			_delay_ms(100);
			EEPROM_vwrite(EEPROM_GUEST_PASSWORD_LOCATION1+i,value);		// put the value of the 1st digit of it's pass in location of EEPROM to keep it after power off
		}//end for
		EEPROM_vwrite(EEPROM_GUEST_STATUS_LOCATION,0x00);		//  to indicate that EEPROM_GUEST_STATUS_LOCATION is writen     not as a default 0xff = 0b1111,1111  that mean no thing is writen HERE
		LCD_vclearscreen();
		LCD_vsend_string("Pass Saved");// show pass saved message
		_delay_ms(500);//delay the system for time in (ms)
		LCD_vclearscreen();
	

	}//end if admin and guest password is set

/* this code of else run only if the system is not running for the first time (ADMIN and GUEST passwords are set )*/
	else
	{
		block_mode_flag = EEPROM_u8read(EEPROM_LOGIN_BLOCKED_LOCATION); //read the blocked location from EEPROM
	}

/* ============================================================================================================================== */
/* ============================================================================================================================== */


	while(flag==0)		//if (EEPROM_u8read(EEPROM_ADMIN_STATUS_LOCATION)==0x00) if read a EEPROM_ADMIN_STATUS_LOCATION as NOT AS a default 0xff = 0b1111,1111  that mean thing is writen HERE
	{	//arr[0]=arr[1]=arr[2]=arr[3]=NOTPRESSED;
	
	/* ===================  Code active in case block mode flag Active =1  and off = 0   =========================== */
		if(block_mode_flag==1)//if the login process was blocked wait till the end of the block period
		{
			LCD_vclearscreen();
			LCD_vsend_string("Login blocked");
			LCD_vmovecursor(2,1);
			LED_vTurnOn('C',2);  //Turn on the led of Block Mode		
			LCD_vsend_string("wait ");
			// count 20 seconds Descending  i.e 20,19,18,... and so on till 1
			for (int i=20;i>=1;i--)
			{
				LCD_vmovecursor(2,6);
				LCD_vsend_char( (i/10) +48);
				LCD_vsend_char( (i%10) +48);
				LCD_vsend_string(" seconds");
				_delay_ms(1000);//delay  the system for 1 Second time in (ms)
			}
	        // _delay_ms(BLOCK_MODE_TIME);//delay  the system for the time in (ms)
			tries = 0;    //Clear the count on number of wrong tries
			block_mode_flag = 0;//Disable block of runtime
			LED_vTurnOff('C',2);//Turn off the led of Blocked
			EEPROM_vwrite(EEPROM_LOGIN_BLOCKED_LOCATION,0x00);//write "0x00" at blocked location in EEPROM .. so make it as NOT AS a default 0xff = 0b1111,1111  that mean thing is writen HERE
		}	//end if 
	
		LCD_vclearscreen();
		LCD_vsend_string("Select Mode:");
		LCD_vmovecursor(2,1);
		LCD_vsend_string("0:Admin 1:Guest");
	
	
		while(value == NOTPRESSED )//wait for select which mode?
		{
			value = keypad_u8check_press();//if the user pressed any button in keypad save it's value in Value Variable
		}
	
		if ( value!= '0' && value!= '1' )  // if value!= "0:Admin 1:Guest" -->handle wrong input from user
		{
			LCD_vclearscreen();
			LCD_vsend_string("Wrong input.");	//Prints error message on the LCD
			value = NOTPRESSED;	//return the variable"value" that holds the pressed key from keypad to its initial value
			_delay_ms(1000);	//delay  the system for the time in (ms)
			continue;	//return to the loop of login #while (login_mode==NO_MODE)# line 128
		}
		
		
		
		switch(value)
			{   /********************************* User Select Admin login Mode **********************************************/
				case '0' :  // indicate to user select '0' Admin Mode
				LCD_vclearscreen();
				LCD_vsend_string("Admin mode");
				LCD_vmovecursor(2,1);
				LCD_vsend_string("Check Pass:");
				_delay_ms(200);   
				
				for (i=0;i<=3;i++)
				{
					do
					{
						arr[i]=keypad_u8check_press();		// check pass:- enter your admin pass that consist of 4 Digit that entered when "Admin Pass:" in the first time open the smart home system
					} while (arr[i]==NOTPRESSED);
					LCD_vsend_char(arr[i]);
					_delay_ms(300);
					LCD_vmovecursor(2,12+i);		// column11 as start count from zero  12+i as "Enter Pass:" string 11 character and no.12 is the 1st digit of it's pass
					LCD_vsend_char('*');
					_delay_ms(100);
				}//end for
				
				/*********************************************  match pass that saved in EEPROM via "Admin pass" with pass that entered via "Enter pass"  ******************************************************/
				if(EEPROM_u8read(EEPROM_ADMIN_PASSWORD_LOCATION1)==arr[0] &&  EEPROM_u8read(EEPROM_ADMIN_PASSWORD_LOCATION2)==arr[1] && EEPROM_u8read(EEPROM_ADMIN_PASSWORD_LOCATION3)==arr[2] && EEPROM_u8read(EEPROM_ADMIN_PASSWORD_LOCATION4)==arr[3] )
				{
					LCD_vclearscreen();
					LCD_vsend_string("true password");
					LCD_vmovecursor(2,1);
					LCD_vsend_string("Admin Mode");
					_delay_ms(500);
					LED_vTurnOn('C', 0 );//turn on the led of admin
					mode=0;// indicate to user in '0' Admin Mode
					flag=1;			
				}
				else//in case of wrong password
				{
					tries=tries-1;    // decrease no of tries by 1 and then check 
					if (tries>0)
					{
						LCD_vclearscreen();
						LCD_vsend_string("wrong password");
						LCD_vmovecursor(2,1);
						LCD_vsend_string("tries left:");
						LCD_vsend_char(tries+48);
						_delay_ms(1000);
						LCD_vclearscreen();
					}
					else
					{
						
						EEPROM_vwrite(EEPROM_LOGIN_BLOCKED_LOCATION,0x00); //Need To active Block Mode for 20 Sec
						block_mode_flag=1;
						break;//break the loop of admin login # while(flag==0) @ line 138
					}//end of else
				}
				break;   // break switch case of admin mode
					
				/********************************* User Select Guest login Mode **********************************************/
				case '1' :
				LCD_vclearscreen();
				LCD_vsend_string("Guest mode");
				LCD_vmovecursor(2,1);
				LCD_vsend_string("Check Pass:");
				_delay_ms(200);
					 
				for (i=0;i<=3;i++)
				{
					do
					{
						arr[i]=keypad_u8check_press();		// check pass:- enter your guest pass that consist of 4 Digit that entered when "Guest Pass:" in the first time open the smart home system
					} while (arr[i]==NOTPRESSED);
					LCD_vsend_char(arr[i]);
					_delay_ms(300);
					LCD_vmovecursor(2,12+i);		// column11 as start count from zero  12+i as "Check Pass:" string 11 character and no.12 is the 1st digit of it's pass
					LCD_vsend_char('*');
					_delay_ms(100);
				}//end for
					 
				/*********************************************  match pass that saved in EEPROM via "Guest pass" with pass that entered via "Check pass"  ******************************************************/
				if(EEPROM_u8read(EEPROM_GUEST_PASSWORD_LOCATION1)==arr[0] &&  EEPROM_u8read(EEPROM_GUEST_PASSWORD_LOCATION2)==arr[1] && EEPROM_u8read(EEPROM_GUEST_PASSWORD_LOCATION3)==arr[2] && EEPROM_u8read(EEPROM_GUEST_PASSWORD_LOCATION4)==arr[3] )
				{
					LCD_vclearscreen();
					LCD_vsend_string("true password");
					LCD_vmovecursor(2,1);
					LCD_vsend_string("Guest Mode");
					_delay_ms(500);
					LED_vTurnOn('C', 1 );//turn on the led of Guest
					mode=1;// indicate to user in '0' Admin Mode
					flag=1;
				}
				else//in case of wrong password
				{
					tries=tries-1;    // decrease no of tries by 1 and then check
					if (tries>0)
					{
						LCD_vclearscreen();
						LCD_vsend_string("wrong password");
						LCD_vmovecursor(2,1);
						LCD_vsend_string("tries left:");
						LCD_vsend_char(tries+48);
						_delay_ms(1000);
						LCD_vclearscreen();
					}
					else
					{
						LCD_vclearscreen();
						EEPROM_vwrite(EEPROM_LOGIN_BLOCKED_LOCATION,0x00); //Need To active Block Mode for 20 Sec
						block_mode_flag=1;
						break;//break the loop of admin login # while(flag==0) @ line 138
						
					}//end of else
						
				}// end else of in case of wrong password
				break;   // break switch case of Guest mode
														
			}// end of switch
				
	} // end of while 
	
	/*==============================================  Menu Iteams  ==================================================*/
	unsigned short show_menu = 0 ;
	unsigned char Status = 0; // it's default value 0 as off and 1 as ON
	unsigned char TurnOn= 1;  //1 as ON
	unsigned char TurnOff = 0; // 0 as off
	unsigned char receive ;
	unsigned char temperature = 0; ////The average temperature of the room  related  for Air Condition 
	unsigned char second_digit_temp = 0xff;//The entered right number of the temperature --'0xff' means not choosed yet
	unsigned char first_digit_temp = 0xff;//The entered left number of the temperature
	
	
while(1)
{	
	
    value = NOTPRESSED;   //Set the key pressed by the user to its default value
	switch (show_menu)
	{
		case 0:
		do
		{
			/******************** print main Menu ******************/
			LCD_vclearscreen();
			LCD_vsend_string("1:Room1 2:Room2");
			LCD_vmovecursor(2,1);
			if(mode==0)  //check login mode
			{
				LCD_vsend_string("3:Room3 4:More");//this menu options only printed if the logged in user as admin
			}
			else if(mode==1)//check login mode
			{
				LCD_vsend_string("3:Room3 4:Room4");//this menu options only printed if the logged in user as guest
			}
			/*******************************************************/
			value=NOTPRESSED;
			while( value == NOTPRESSED )    //repeat till the user press any key
			{ //wait for the user till key is pressed select from menu 
		    value=keypad_u8check_press();
			}			
			_delay_ms(100);//to avoid the duplication of the pressed key
			
	/*		if ( value> '4' || value< '1' )  // if value!= "0:Admin 1:Guest" -->handle wrong input from user
			{
				LCD_vclearscreen();
				LCD_vsend_string("Wrong input.");	//Prints error message on the LCD
				value = NOTPRESSED;	//return the variable"value" that holds the pressed key from keypad to its initial value
				_delay_ms(1000);	//delay  the system for the time in (ms)
				continue;	//return to the loop of login #	do  line 326
			}
	*/	
			
			
			if (value == '1')//If key pressed is 1 i.e. select room1
			{
				show_menu = 1;//Set the next menu to be shown to room1 menu

			}
			else if (value == '2')//If key pressed is 2
			{
				show_menu = 2;//Set the next menu to be shown to room2 menu
			}
			else if (value == '3')//If key pressed is 3
			{
				show_menu = 3;//Set the next menu to be shown to room3 menu
			}
			else if (value == '4' && mode == 1)//If key pressed is 4 and the logged in user is guest
			{
				show_menu = 41;//Set the next menu to be shown to [[[[ room4 menu]]]
			}
			else if (value == '4' && mode == 0)//If key pressed is 4 and the logged in user is admin
			{
				show_menu = 40;//Set the next menu to be shown to [[[more menu]]]
			}
			else if(value != NOTPRESSED)//show wrong input message if the user pressed wrong key
			{
				LCD_vclearscreen();
				LCD_vsend_string("Wrong input");//print error message
				_delay_ms(500);//Halt the system for the given time in (ms)
			}
			
		} while ( (value < '1') || (value > '4')   );//break the loop in case of valid key or time is out
		continue;
		break;//End of main menu case
		
		/************************************************************************/
		/*						Romm1 Menu                                                                     */
		/************************************************************************/
		
		case 1:// pressed 1 to select room1 menu
		do{
				Status = ROOM1_STATUS;
				TurnOn = ROOM1_TURN_ON;
				TurnOff = ROOM1_TURN_OFF;
		
				LCD_vclearscreen();
				LCD_vsend_string("Room1 S:");
				SPI_Transmitchar(Status);//demand the status from the slave
				_delay_ms(100);//Halt the system for the given time in (ms)
				receive = SPI_Receivechar(Master_ACK);//the master micro controller asks for the status
				
				
				if (receive== 1)//if the response from the slave was on status
				{
					LCD_vsend_string("ON");//print the status on
				}
				else//if the response from the slave was off status
				{
					LCD_vsend_string("OFF");//print the status off
				}
				LCD_vmovecursor(2,1);//move the cursor to the start of the second line
				LCD_vsend_string("1-On 2-Off 0-RET");//print the sub menu
				
								
				value=NOTPRESSED;
				while( value == NOTPRESSED )    //repeat till the user press any key
				{ //wait for the user till key is pressed select from menu
					value=keypad_u8check_press();
				}
				_delay_ms(100);//to avoid the duplication of the pressed key
				
				
				/*there is no need to take any action in case of the user pressed 0(RET) key
				breaking the loop will be enough since it will be handled in the main*/
					
				if (value == '1')
				{
					SPI_Transmitchar(TurnOn);//Send turn on signal from master to slave
				}
				else if (value == '2')
				{
					SPI_Transmitchar(TurnOff);//Send turn off signal from master to slave
				}
		    	else if( (value != NOTPRESSED) && (value != '0') )//show wrong input message if the user entered non numeric value
				{
					LCD_vclearscreen();
					LCD_vsend_string("Wrong input");//print error message
					_delay_ms(500);//Halt the system for the given time in (ms)
				}
			//show_menu=0;	
		}while( (value < '0') || (value > '2')  );//break the loop in case of valid key or time is out	
		show_menu=0;
		continue;
		break;
		
		/************************************************************************/
		/*						Romm2 Menu                                                                     */
		/************************************************************************/
		
		case 2:// pressed 2 to select room2 menu
		do{
				Status = ROOM2_STATUS;
				TurnOn = ROOM2_TURN_ON;
				TurnOff = ROOM2_TURN_OFF;
		
				LCD_vclearscreen();
				LCD_vsend_string("Room2 S:");
				SPI_Transmitchar(Status);//demand the status from the slave
				_delay_ms(100);//Halt the system for the given time in (ms)
				receive = SPI_Receivechar(Master_ACK);//the master micro controller asks for the status
				
				
				if (receive== 1)//if the response from the slave was on status
				{
					LCD_vsend_string("ON");//print the current status on
				}
				else//if the response from the slave was off status
				{
					LCD_vsend_string("OFF");//print the current status off
				}
				LCD_vmovecursor(2,1);//move the cursor to the start of the second line
				LCD_vsend_string("1-On 2-Off 0-RET");//print the sub menu
				
								
				value=NOTPRESSED;
				while( value == NOTPRESSED )    //repeat till the user press any key
				{ //wait for the user till key is pressed select from menu
					value=keypad_u8check_press();
				}
				_delay_ms(100);//to avoid the duplication of the pressed key
				
				
				/*there is no need to take any action in case of the user pressed 0(RET) key
				breaking the loop will be enough since it will be handled in the main*/
					
				if (value == '1')
				{
					SPI_Transmitchar(TurnOn);//Send turn on signal from master to slave
				}
				else if (value == '2')
				{
					SPI_Transmitchar(TurnOff);//Send turn off signal from master to slave
				}
		    	else if( (value != NOTPRESSED) && (value != '0') )//show wrong input message if the user entered non numeric value
				{
					LCD_vclearscreen();
					LCD_vsend_string("Wrong input");//print error message
					_delay_ms(500);//Halt the system for the given time in (ms)
				}
			//show_menu=0;	
		}while( (value < '0') || (value > '2')  );//break the loop in case of valid key or time is out	
		show_menu=0;
		continue;
		break;
		/************************************************************************/
		/*						Romm3 Menu                                                                     */
		/************************************************************************/
		
		case 3:// pressed 3 to select room3 menu
		do{
				Status = ROOM3_STATUS;
				TurnOn = ROOM3_TURN_ON;
				TurnOff = ROOM3_TURN_OFF;
		
				LCD_vclearscreen();
				LCD_vsend_string("Room3 S:");
				SPI_Transmitchar(Status);//demand the status from the slave
				_delay_ms(100);//Halt the system for the given time in (ms)
				receive = SPI_Receivechar(Master_ACK);//the master micro controller asks for the status
				
				
				if (receive== 1)//if the response from the slave was on status
				{
					LCD_vsend_string("ON");//print the status on
				}
				else//if the response from the slave was off status
				{
					LCD_vsend_string("OFF");//print the status off
				}
				LCD_vmovecursor(2,1);//move the cursor to the start of the second line
				LCD_vsend_string("1-On 2-Off 0-RET");//print the sub menu
				
								
				value=NOTPRESSED;
				while( value == NOTPRESSED )    //repeat till the user press any key
				{ //wait for the user till key is pressed select from menu
					value=keypad_u8check_press();
				}
				_delay_ms(100);//to avoid the duplication of the pressed key
				
				
				/*there is no need to take any action in case of the user pressed 0(RET) key
				breaking the loop will be enough since it will be handled in the main*/
					
				if (value == '1')
				{
					SPI_Transmitchar(TurnOn);//Send turn on signal from master to slave
				}
				else if (value == '2')
				{
					SPI_Transmitchar(TurnOff);//Send turn off signal from master to slave
				}
		    	else if( (value != NOTPRESSED) && (value != '0') )//show wrong input message if the user entered non numeric value
				{
					LCD_vclearscreen();
					LCD_vsend_string("Wrong input");//print error message
					_delay_ms(500);//Halt the system for the given time in (ms)
				}
			//show_menu=0;	
		}while( (value < '0') || (value > '2')  );//break the loop in case of valid key or time is out	
		show_menu=0;
		continue;
		break;
		/************************************************************************/
		/*						[[[4-more Menu ]]] in admin mode only
		             If key pressed is 4 and the logged in user is admin
		                                                                   */
		/************************************************************************/
		
		case 40:// pressed 4 to select 4-more menu
		do{
				/******************** print more Menu ******************/
				LCD_vclearscreen();
				LCD_vsend_string("1:Room4    2:TV   ");
				LCD_vmovecursor(2,1);
				LCD_vsend_string("3:AirCond .4:RET");
				/*******************************************************/
		
				value=NOTPRESSED;
				while( value == NOTPRESSED )    //repeat till the user press any key
				{ //wait for the user till key is pressed select from menu
					value=keypad_u8check_press();
				}
				_delay_ms(100);//to avoid the duplication of the pressed key
				
				if (value == '1')//If key pressed is 1 - Set the next menu to be shown to room4 menu
				{
					show_menu = 41;//Set the next menu to be shown to [[[room4 menu]]]
				}
				else if (value == '2')//If key pressed is 2- Set the next menu to be shown to TV menu
				{
					show_menu = 42;//Set the next menu to be shown to [[[TV menu]]]
				}
				else if (value == '3')//If key pressed is 3
				{
					show_menu = 43;//Set the next menu to be shown to [[[Air conditioning menu]]]
				}
				else if (value == '4')//If key pressed is 4 (RET)
				{
					show_menu = 0;//Set the next menu to be shown to [[[main menu]]]
				}
				else if(value != NOTPRESSED)//show wrong input message if the user pressed wrong key
				{
					LCD_vclearscreen();
					LCD_vsend_string("Wrong input");//print error message
					_delay_ms(500);//Halt the system for the given time in (ms)
				}
			} while ( (value < '1') || (value > '4') );//break the loop in case of valid key or time is out
			
			continue;
			break;//End of more menu case
			/************************************************************************/
		/*						4-more Menu  in admin mode only
											Romm4 Menu  
						check in room4 menu in admin mode or guest mode                                                                   */
		/************************************************************************/
		
		case 41://If key pressed is 1  in more menu appear room4 menu
		do{
				Status = ROOM4_STATUS;
				TurnOn = ROOM4_TURN_ON;
				TurnOff = ROOM4_TURN_OFF;
		
				LCD_vclearscreen();
				LCD_vsend_string("Room4 S:");
				SPI_Transmitchar(Status);//demand the status from the slave
				_delay_ms(100);//Halt the system for the given time in (ms)
				receive = SPI_Receivechar(Master_ACK);//the master micro controller asks for the status
				
				
				if (receive== 1)//if the response from the slave was on status
				{
					LCD_vsend_string("ON");//print the status on
				}
				else//if the response from the slave was off status
				{
					LCD_vsend_string("OFF");//print the status off
				}
				LCD_vmovecursor(2,1);//move the cursor to the start of the second line
				LCD_vsend_string("1-On 2-Off 0-RET");//print the sub menu
				
								
				value=NOTPRESSED;
				while( value == NOTPRESSED )    //repeat till the user press any key
				{ //wait for the user till key is pressed select from menu
					value=keypad_u8check_press();
				}
				_delay_ms(100);//to avoid the duplication of the pressed key
				
				
				/*there is no need to take any action in case of the user pressed 0(RET) key
				breaking the loop will be enough since it will be handled in the main*/
					
				if (value == '1')
				{
					SPI_Transmitchar(TurnOn);//Send turn on signal from master to slave
				}
				else if (value == '2')
				{
					SPI_Transmitchar(TurnOff);//Send turn off signal from master to slave
				}
		    	else if( (value != NOTPRESSED) && (value != '0') )//show wrong input message if the user entered non numeric value
				{
					LCD_vclearscreen(); 
					LCD_vsend_string("Wrong input");//print error message
					_delay_ms(500);//Halt the system for the given time in (ms)
				}
		}while( (value < '0') || (value > '2')  );//break the loop in case of valid key or time is out	
		
		/***************************** select ROOM4 in witch mode  *******************************************/
		if (mode == 1)//in case of guest is logged in
		{
			show_menu = 0;//Set the next menu to be shown to [[[main menu]]]
		}
		else//in case of admin is logged in
		{
			show_menu = 40;//Set the next menu to be shown to [[[more menu]]]
		}
		continue;   
		break;
		/************************************************************************/
		/*						4-more Menu  in admin mode only
											TV Menu                                                                     */
		/************************************************************************/
		
		case 42://If key pressed is 1  in more menu  appear TV menu
		do{
				Status = TV_STATUS;
				TurnOn = TV_TURN_ON;
				TurnOff = TV_TURN_OFF;
		
				LCD_vclearscreen();
				LCD_vsend_string("TV S:");
				SPI_Transmitchar(Status);//demand the status from the slave
				_delay_ms(100);//Halt the system for the given time in (ms)
				receive = SPI_Receivechar(Master_ACK);//the master micro controller asks for the status
				
				
				if (receive== 1)//if the response from the slave was on status
				{
					LCD_vsend_string("ON");//print the status on
				}
				else//if the response from the slave was off status
				{
					LCD_vsend_string("OFF");//print the status off
				}
				LCD_vmovecursor(2,1);//move the cursor to the start of the second line
				LCD_vsend_string("1-On 2-Off 0-RET");//print the sub menu
				
								
				value=NOTPRESSED;
				while( value == NOTPRESSED )    //repeat till the user press any key
				{ //wait for the user till key is pressed select from menu
					value=keypad_u8check_press();
				}
				_delay_ms(100);//to avoid the duplication of the pressed key
				
				
				/*there is no need to take any action in case of the user pressed 0(RET) key
				breaking the loop will be enough since it will be handled in the main*/
					
				if (value == '1')
				{
					SPI_Transmitchar(TurnOn);//Send turn on signal from master to slave
				}
				else if (value == '2')
				{
					SPI_Transmitchar(TurnOff);//Send turn off signal from master to slave
				}
		    	else if( (value != NOTPRESSED) && (value != '0') )//show wrong input message if the user entered non numeric value
				{
					LCD_vclearscreen();
					LCD_vsend_string("Wrong input");//print error message
					_delay_ms(500);//Halt the system for the given time in (ms)
				}
			//show_menu=0;	
		}while( (value < '0') || (value > '2')  );//break the loop in case of valid key or time is out	
		show_menu=40;// show 4-more menu  in admin mode only
		continue;
		break;
		/************************************************************************/
		/*						4-more Menu  in admin mode only
									AIRCONDITIONING_MENU Menu                                                                     */
		/************************************************************************/
		
		case 43:
		do
		{
			/******************** print more Menu ******************/
			LCD_vclearscreen();//remove all previously printed characters on the LCD and move the cursor to the first column of the first row
			LCD_vsend_string("1:Set temperature ");
			LCD_vmovecursor(2,1);
			LCD_vsend_string("2:Control  0:RET");
			/*******************************************************/
			value=NOTPRESSED;
			while( value == NOTPRESSED )    //repeat till the user press any key
			{ //wait for the user till key is pressed select from menu
				value=keypad_u8check_press();
			}
			_delay_ms(100);//to avoid the duplication of the pressed key
			
			if (value == '1')//If key pressed is 1 SELECT_SET_TEMPERATURE
			{
				show_menu = 431;//Set the next menu to be shown to set temperature menu
			}
			else if (value == '2')//If key pressed is 2 --Set the next menu to be shown to air conditioning control menu
			{
				show_menu = 432;//Set the next menu to be shown to air conditioning control menu
			}
			else if (value == '0')//If key pressed is 0 -- SELECT_AIR_COND_RET
			{
				show_menu = 0;//Set the next menu to be shown to more menu
			}
			else if(value != NOTPRESSED)//show wrong input message if the user pressed wrong key
			{
				LCD_vclearscreen();//remove all previously printed characters on the LCD and move the cursor to the first column of the first row
				LCD_vsend_string("Wrong input");//print error message
				_delay_ms(500);
			}
		}while( (value < '0') || (value > '2')  );//break the loop in case of valid key or time is out	
		continue;
		break;
		
		/************************************************************************/
		/*						4-more Menu  in admin mode only
									AIRCONDITIONING_MENU Menu  
								[[[	1-set temperature menu ]]]                                                                  */
		/************************************************************************/
		case 431:
		temperature = 0;//clear the value of temperature
		while (temperature==0 )//start the loop that asks for the temperature from the user 
		{
			value = NOTPRESSED;//set the key pressed to the default value
			LCD_vclearscreen(); 
			LCD_vsend_string("Set temp.:__ ");//print the format of inserting temperature
			LCD_vsend_char(0xDF); // print the symbol of degree
			LCD_vsend_char('C'); // print the C character
			LCD_vmovecursor(1,11);//move the cursor to the place to write the entered temperature
			_delay_ms(200);//Halt the system for time in (ms)
			/*******************************enter the first_digit_temp ************************************************/
			value=NOTPRESSED;
			while( value == NOTPRESSED )    //repeat till the user press any key
			{ //wait for the user till key is pressed select from menu
				value=keypad_u8check_press();
			}
			_delay_ms(250);//to avoid the duplication of the pressed key

			if (value <'0' || value >'9')//show wrong input message if the user entered non numeric value
			{
				LCD_vclearscreen();//remove all previously printed characters on the LCD and move the cursor to the first column of the first row
				LCD_vsend_string("Wrong input");//print error message
				_delay_ms(500);//Halt the system for the given time in (ms)
				continue;//return to #while (temperature==0)# line 797
			}
			else//if the value is valid
			{
				LCD_vsend_char(value);//print the value on the lcd
				first_digit_temp = value-'0';//save the entered value of first_digit_temp by subtract from ASCii of zero
				value=NOTPRESSED;				
			}
			/*********************************enter the second_digit_temp**********************************************/
			value=NOTPRESSED;
			while( value == NOTPRESSED )    //repeat till the user press any key
			{ //wait for the user till key is pressed select from menu
				value=keypad_u8check_press();
			}
			_delay_ms(250);//to avoid the duplication of the pressed key

			if (value <'0' || value >'9')//show wrong input message if the user entered non numeric value
			{
				LCD_vclearscreen();//remove all previously printed characters on the LCD and move the cursor to the first column of the first row
				LCD_vsend_string("Wrong input");//print error message
				_delay_ms(500);//Halt the system for the given time in (ms)
				continue;//return to #while (temperature==0)# line 797
			}
			else//if the value is valid
			{
				LCD_vsend_char(value);//print the value on the lcd
				second_digit_temp = value-'0';//save the entered value of second_digit_temp by subtract from ASCii of zero
				value = NOTPRESSED;//set the key pressed to the default value
			}
			temperature = first_digit_temp*10 + second_digit_temp;//set the value of the temperature from the given separated values
			SPI_Transmitchar(SET_TEMPERATURE);//Send the code of set temperature
			_delay_ms(200);
			SPI_Transmitchar(temperature);//send the entered temperature
			LCD_vclearscreen();//remove all previously printed characters on the LCD and move the cursor to the first column of the first row
			LCD_vsend_string("Temperature Sent");//show the message
			_delay_ms(500);//Halt the system for the given time in (ms)
		}
		show_menu = 43;//Set the next menu to be shown to air conditioning menu
		continue;
		break;//break from switch
		
		/************************************************************************/
		/*						4-more Menu  in admin mode only
									AIRCONDITIONING_MENU Menu  
								[[[	2-Control ]]]                                                                  */
		/************************************************************************/
		case 432:	
		do{
				Status = AIR_COND_STATUS;
				TurnOn = AIR_COND_TURN_ON;
				TurnOff = AIR_COND_TURN_OFF;
		
				LCD_vclearscreen();
				LCD_vsend_string("Air Cond. S:");
				SPI_Transmitchar(Status);//demand the status from the slave
				_delay_ms(100);//Halt the system for the given time in (ms)
				receive = SPI_Receivechar(Master_ACK);//the master micro controller asks for the status
				
				
				if (receive== 1)//if the response from the slave was on status
				{
					LCD_vsend_string("ON");//print the status on
				}
				else//if the response from the slave was off status
				{
					LCD_vsend_string("OFF");//print the status off
				}
				LCD_vmovecursor(2,1);//move the cursor to the start of the second line
				LCD_vsend_string("1-On 2-Off 0-RET");//print the sub menu
				
								
				value=NOTPRESSED;
				while( value == NOTPRESSED )    //repeat till the user press any key
				{ //wait for the user till key is pressed select from menu
					value=keypad_u8check_press();
				}
				_delay_ms(100);//to avoid the duplication of the pressed key
				
				
				/*there is no need to take any action in case of the user pressed 0(RET) key
				breaking the loop will be enough since it will be handled in the main*/
					
				if (value == '1')
				{
					SPI_Transmitchar(TurnOn);//Send turn on signal from master to slave
				}
				else if (value == '2')
				{
					SPI_Transmitchar(TurnOff);//Send turn off signal from master to slave
				}
		    	else if( (value != NOTPRESSED) && (value != '0') )//show wrong input message if the user entered non numeric value
				{
					LCD_vclearscreen();
					LCD_vsend_string("Wrong input");//print error message
					_delay_ms(500);//Halt the system for the given time in (ms)
				}
			//show_menu=0;	
		}while( (value < '0') || (value > '2')  );//break the loop in case of valid key or time is out	
		show_menu = 43;//Set the next menu to be shown to air conditioning menu
		continue;
		break;
		
			
			}//end of switch line#325
			
		}	// end of while line#321		
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			/*************************Set the commands to be sent to the slave based on  the sent room or device *************************/
	/*	do{
			
			switch(value)
			{
				case '1' :// select to Room 1 menu
				
				
				 Status = ROOM1_STATUS;
				 TurnOn = ROOM1_TURN_ON;
				 TurnOff = ROOM1_TURN_OFF;
				
				LCD_vclearscreen();
				LCD_vsend_string("Room1 S:");
			//	show_menu=1;
			
				break;
					
			}
			
				SPI_send_char(Status);//demand the status from the slave
				_delay_ms(100);//Halt the system for the given time in (ms)
				receive = SPI_receive_char();//the master micro controller asks for the status
				
				
				if (receive== 1)//if the response from the slave was on status
				{
					LCD_vsend_string("ON");//print the status on
				}
				else//if the response from the slave was off status
				{
					LCD_vsend_string("OFF");//print the status off
				}

				LCD_vmovecursor(2,1);//move the cursor to the start of the second line
				LCD_vsend_string("1-On 2-Off 0-RET");//print the sub menu
				
				
					
				value=NOTPRESSED;
				while( value == NOTPRESSED )    //repeat till the user press any key
				{ //wait for the user till key is pressed select from menu
					value=keypad_u8check_press();
				}
				_delay_ms(100);//to avoid the duplication of the pressed key
				
				
				/*there is no need to take any action in case of the user pressed 0(RET) key
				breaking the loop will be enough since it will be handled in the main*/
					
/*				if (value == '1')
				{
					SPI_send_char(TurnOn);//Send turn on signal from master to slave
					
				}
				else if (value == '2')
				{
					SPI_send_char(TurnOff);//Send turn off signal from master to slave
				}
		    	else if( (value != NOTPRESSED) && (value != '0') )//show wrong input message if the user entered non numeric value
				{
					LCD_vclearscreen();//remove all previously printed characters on the LCD and move the cursor to the first column of the first row
					LCD_vsend_string("Wrong input");//print error message
					_delay_ms(500);//Halt the system for the given time in (ms)
		
				}
				
		}while( (value < '0') || (value > '2')  );//break the loop in case of valid key or time is out	
		
		value=NOTPRESSED;	 // return to the main menu
	//	show_menu=0;
		continue;  // return to the main menu switch (show_menu) line 317
	
				
				
				
			
				case '2':
				show_menu=2;
				break;
			
						
				
		}while( (value < '1') || (value > '4')  );//break the loop in case of valid key or time is out
		
		break;
			
	}// end of switch					
			

	*/

	
	
	
}//end main Function


