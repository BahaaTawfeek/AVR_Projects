/*
 * LCD.h
 *
 * Created: 26/04/2022 01:22:52 am
 *  Author: Bahaa Tawfik
 */

#ifndef LCD_H_
#define LCD_H_
#include "LCD_configure.h"
#include "DIO.h"

#define CLR_SCREEN 0x01                  //0b0000,0001
#define CURSOR_ON_DISPLAY_ON 0x0e		 //0b0000,1110
#define RETURN_HOME 0x02				 //0b0000,0010
#define ENTRY_MODE 0x06					 //0b0000,0110


#if defined four_bits_mode        // for  4_bits Mode 
#define EN 0				     //pin0
#define RW 1			        //pin1
#define RS 2					//pin2
#define FOUR_BITS 0x28		   //ob0010,1000  from function set mode(0b001 DL,NF XX) select 4 bit mode and 1== 2Num of line and 0==font 5X7 dots

#elif defined eight_bits_mode    // for  8_bits Mode 
#define EN 0					 //pin0
#define RW 1					 //pin1
#define RS 2	  				//pin2
#define EIGHT_BITS 0x38			//ob0011,1000  from function set mode

#endif

void LCD_vInit(void);
static  void vsend_falling_edge(void);   //use a static function as not need to make a call outside the file
void LCD_vsend_cmd(char cmd);
void LCD_vsend_char(char data);
void LCD_vsend_string(char *data);
void LCD_vclearscreen();
void LCD_vmovecursor(char row,char coloumn);






#endif /* LCD_H_ */