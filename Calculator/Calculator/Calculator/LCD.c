/*
 * LCD.c
 *
 * Created: 26/04/2022 01:23:46am
 *  Author: Bahaa Tawfik
 */
#include "LCD.h"
#define  F_CPU 8000000UL 
#include <util/delay.h>



/*
 *Function Description : Initialize the LCD
 */

void LCD_vInit(void)
{
	_delay_ms(200);										  // delay more than 30 ms after power ON  AS  data sheet
	/****************************************** for  8_bits Mode   *********************************************************/
	#if defined eight_bits_mode							 
	
	DIO_vsetPortDir('C',1);							   // make the direction of whole port C as output port  
	DIO_vsetPinDir('A',EN,1);					      // make the direction of pin0 (EN)  as output port
	DIO_vsetPinDir('A',RW,1);						  // make the direction of pin1 (RW)  as output port
	DIO_vsetPinDir('A',RS,1);						 // make the direction of pin2 (RS)  as output port
	
	
	DIO_vwritePin('A',RW,0);					     //always we select  write mode 

	LCD_vsend_cmd(EIGHT_BITS);						 //predefined  0x38=0b0011,1000  from function set mode
	_delay_ms(1);									 // delay more than 39 us after function set mode AS data sheet
	LCD_vsend_cmd(CURSOR_ON_DISPLAY_ON);			//predefined 0b0000,1110 from Display on-off control mode
	_delay_ms(1);									// delay more than 39 us after Display on-off control mode AS data sheet
	LCD_vsend_cmd(CLR_SCREEN);						//predefined  0b0000,0010 from Display clear mode  AS data sheet
	_delay_ms(10);									// delay more than 1.52 ms after Display clear mode AS data sheet
	LCD_vsend_cmd(ENTRY_MODE);						//predefined 0b0000,0110 from Entry mode as data sheet
	
	/****************************************** for  4_bits Mode   *********************************************************/
	#elif defined four_bits_mode
	
	DIO_vsetPinDir('C',4,1);						  // make the direction of pin4 as output port
	DIO_vsetPinDir('C',5,1);						  // make the direction of pin5 as output port	
	DIO_vsetPinDir('C',6,1);						  // make the direction of pin6 as output port	
	DIO_vsetPinDir('C',7,1);						  // make the direction of pin7 as output port		
	
	DIO_vsetPinDir('A',EN,1);					      // make the direction of pin0 (EN)  as output port
	DIO_vsetPinDir('A',RW,1);						  // make the direction of pin1 (RW)  as output port
	DIO_vsetPinDir('A',RS,1);						 // make the direction of pin2 (RS)  as output port
	
	DIO_vwritePin('A',RW,0);					     //write mode select
	
	LCD_vsend_cmd(RETURN_HOME);				//return home
	_delay_ms(10);

	LCD_vsend_cmd(FOUR_BITS);						//predefined  0x28=0b0010,1000  from function set mode
	_delay_ms(1);									 // delay more than 39 us after function set mode AS data sheet
	LCD_vsend_cmd(CURSOR_ON_DISPLAY_ON);			//predefined 0b0000,1110 from Display on-off control mode
	_delay_ms(1);									// delay more than 39 us after Display on-off control mode AS data sheet
	LCD_vsend_cmd(CLR_SCREEN);						//predefined  0b0000,0010 from Display clear mode  AS data sheet
	_delay_ms(5);									// delay more than 1.52 ms after Display clear mode AS data sheet
	LCD_vsend_cmd(ENTRY_MODE);						//predefined 0b0000,0110 from Entry mode as data sheet
	
	#endif
	
}


/*
 *Function Description :  create falling edge to active Enable pin of LCD
 *use a static function as not need to make a call outside the file
 *function to enable LCD display
 */

static  void vsend_falling_edge(void)
{
	DIO_vwritePin('A',EN,1);        // create high edge
	_delay_ms(2);
	DIO_vwritePin('A',EN,0);      // create high edge
	_delay_ms(2);
}


/*
 *Function Description :  Send Command to  LCD
 */

void LCD_vsend_cmd(char cmd)
{
	/****************************************** for  8_bits Mode   *********************************************************/
	#if defined eight_bits_mode
	
	DIO_vwritePort('C',cmd);			//  Send the command value to the LCD data port .
	DIO_vwritePin('A',RS,0);			// Make RS pin low, RS = 0 (command reg.)
	vsend_falling_edge();				// enable LCD display
	
	/****************************************** for  4_bits Mode   *********************************************************/
	#elif defined four_bits_mode
	
	DIO_vwrite_high_nibble('C',cmd>>4);			//  shifted right to write high nibble of cmd  
	DIO_vwritePin('A',RS,0);			//  Make RS pin low, RS = 0 (command reg.)
	vsend_falling_edge();				// enable LCD display
	DIO_vwrite_high_nibble('C',cmd);			//   write high nibble of cmd (low nibble )
	DIO_vwritePin('A',RS,0);			//  Make RS pin low, RS = 0 (command reg.)
	vsend_falling_edge();				// enable LCD display
	
	// _delay_ms(1);
	#endif	  	
}



/*
 *Function Description :  Send Character to  LCD
 */
void LCD_vsend_char(char data)
{
	/****************************************** for  8_bits Mode   *********************************************************/
	#if defined eight_bits_mode
	
	DIO_vwritePort('C',data);				 //  Send the command value to the LCD data port 
	DIO_vwritePin('A',RS,1);			//  Make RS pin high, RS = 1 (data reg.)
	vsend_falling_edge();					// enable LCD display
	
	
	/****************************************** for  4_bits Mode   *********************************************************/
	#elif defined four_bits_mode
	
	DIO_vwrite_high_nibble('C',data>>4);			//  shifted right to write high nibble of data
	DIO_vwritePin('A',RS,1);			//  Make RS pin high, RS = 1 (Data reg.)
	vsend_falling_edge();				// enable LCD display
	DIO_vwrite_high_nibble('C',data);			//   write high nibble of cmd (low nibble )
	DIO_vwritePin('A',RS,1);			//  Make RS pin high, RS = 1 (data reg.)
	vsend_falling_edge();				// enable LCD display
		
	// _delay_ms(1);
	#endif
}




/*
 *Function Description :  Send String to  LCD
 */

void LCD_vsend_string(char *data)
{
	while( (*data) != '\0')							// Null=='\0'
	{
		LCD_vsend_char(*data);
		data++;
		
	}	
}


/*
 *Function Description :   clear screen of  LCD
 */

void LCD_vclearscreen()
{
	LCD_vsend_cmd(CLR_SCREEN);	
	_delay_ms(10);
}



/*
 *Function Description :  move the cursor of  LCD
 */

void LCD_vmovecursor(char row,char coloumn)
{
	if( coloumn>=0 && coloumn<=39 )
	{
		switch(row)
		{
			case 1:
			LCD_vsend_cmd(0x80 + coloumn);			// To put cursor of LCD on: Address of first row column 1 : 0x80 + 0  .......

			break;
			
			case 2:
			LCD_vsend_cmd(0xC0 + coloumn);			// To put cursor of LCD on: Address of second row column 1 : 0xC0 + 0  .......
			break;
			default:  /*   print  Error  */ break;
		}	
	}
	else
	{/*  print Error  */}
}



