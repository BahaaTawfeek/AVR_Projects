 /*
 * DIO.c
 *
 * Created: 26/04/2022 01:22:27 am
 *  Author: Bahaa Tawfik
 */
#include <avr/io.h>
#include "DIO.h"
#include "std_macros.h"

/*
 *Function Description : Set the direction of the given pin in the given port (direction 0 = input : 1 = output)
 */

void DIO_vsetPinDir(unsigned char portname,unsigned char pinnumber,unsigned char direction)
{
	switch(portname)
	{
		case 'A':
		if (direction == 1)
			{
				SetBit(DDRA,pinnumber);     //Set the direction 1 = output of the given pin in port A as output
			}
		else
			{
				ClearBit(DDRA,pinnumber);    //Set the direction 0 = input of the given pin in port A as input
			}
		break;	
				  	
				  
		case 'B':
		if (direction == 1)
			{
				SetBit(DDRB,pinnumber);     //Set the direction 1 = output of the given pin in port B as output
			}
		else
			{
				ClearBit(DDRB,pinnumber);    //Set the direction 0 = input of the given pin in port B as input
			}
		break;
				
		case 'C':
		if (direction == 1)
			{
				SetBit(DDRC,pinnumber);     //Set the direction 1 = output of the given pin in port C as output
			}
		else
			{
				ClearBit(DDRC,pinnumber);    //Set the direction 0 = input of the given pin in port C as input
			}
		break;
				
		case 'D':
		if (direction == 1)
			{
				SetBit(DDRD,pinnumber);     //Set the direction 1 = output of the given pin in port D as output
			}
		else
			{
				ClearBit(DDRD,pinnumber);    //Set the direction  0 = input of the given pin in port D as input
			}
		break;
		
		default:
		break ;
				
	}  // end of switch 
	
} // end of Function




/*
 *Function Description : set the direction of whole port . (port direction 0 = input port : 1 = output port)
 */

void DIO_vsetPortDir(unsigned char portname,unsigned char direction)
{
	switch(portname)
	{
		case 'A':
		DDRA=direction;    //set the direction of port A		
		break;
		
		case 'B':
		DDRB=direction;    //set the direction of port B
		break;
		
		case 'C':
		DDRC=direction;    //set the direction of port C
		break;
		
		case 'D':
		DDRD=direction;    //set the direction of port D	
		break;
		
		default:
		break ;
			
	}// end of switch 
	

} // end of Function




/*
 *Function Description : Set the value of the given pin in the given port (outputvalue 0 = low : 1 = high)
 */

void DIO_vwritePin(unsigned char portname,unsigned char pinnumber,unsigned char value)
{
	switch(portname)
	{
		case 'A':
		if (value==1)
		{
			SetBit(PORTA,pinnumber);  //Set the value of the given pin in port A as High
		}
		else
		{
			ClearBit(PORTA,pinnumber);  //Set the value of the given pin in port A as Low
		}
		break;
		
		case 'B':
		if (value==1)
		{
			SetBit(PORTB,pinnumber);  //Set the value of the given pin in port B as High
		}
		else
		{
			ClearBit(PORTB,pinnumber);  //Set the value of the given pin in port B as Low
		}
		break;
		
		case 'C':
		if (value==1)
		{
			SetBit(PORTC,pinnumber);  //Set the value of the given pin in port C as High
		}
		else
		{
			ClearBit(PORTC,pinnumber);  //Set the value of the given pin in port C as Low
		}
		break;
		
		case 'D':
		if (value==1)
		{
			SetBit(PORTD,pinnumber);  //Set the value of the given pin in port D as High
		}
		else
		{
			ClearBit(PORTD,pinnumber);  //Set the value of the given pin in port D as Low
		}
		break;
		
		default:
		break ;		
					
	}// end of switch 
	
}// end of Function



/*
 *Function Description : Write the value to all port pins (outputvalue 0 = low : 1 = high)
 */

void DIO_vwritePort(unsigned char portname,unsigned char value)
{
	switch(portname)
	{
		case 'A':
		PORTA=value;   //Write the given value to the port A
		break;
		
		case 'B':
		PORTB=value;   //Write the given value to the port B
		break;
		
		case 'C':
		PORTC=value;   //Write the given value to the port C
		break;
		
		case 'D':
		PORTD=value;   //Write the given value to the port D
		break;
		
		default:
		break ;
		
	}// end of switch 
	
}// end of Function



/*
 *Function Description : Returns 1 if the value of the given pin is high and zero if the value is low
 */

unsigned char DIO_u8readPin(unsigned char portname,unsigned char pinnumber)
{
	unsigned char return_value=0;
	switch(portname)
	{
		case 'A':
		return_value = ReadBit(PINA,pinnumber);   //Read the value from the given pin in port A
		break;
		
		case 'B':
		return_value = ReadBit(PINB,pinnumber);   //Read the value from the given pin in port B
		break;
		
		case 'C':
		return_value = ReadBit(PINC,pinnumber);   //Read the value from the given pin in port C
		break;
		
		case 'D':
		return_value = ReadBit(PIND,pinnumber);   //Read the value from the given pin in port D
		break;
		
		default:
		break ;
								
	}	// end of switch 
		
	return return_value;
	
}// end of Function	



/*
 *Function Description : Read the value of the given  port
 */

unsigned char DIO_u8readPort(unsigned char portname)
{
	unsigned char return_val=0;
	switch(portname)
	{
		case 'A':
		return_val = PINA; // read the value of port A
		break;
		
		case 'B':
		return_val = PINB; // read the value of port B
		break;
		
		case 'C':
		return_val = PINC; // read the value of port C
		break;
		
		case 'D':
		return_val = PIND; // read the value of port D
		break;
		
		default:
		break ;			
		
	}// end of switch 
		
	return return_val;
	
}// end of Function	



/*
 *Function Description : Reverse the value of the given pin in the given port.
 */

void DIO_vtogglePin(unsigned char portname,unsigned char pinnumber)
{
	switch(portname)
	{
		case 'A':
		ToggleBit(PORTA,pinnumber);   //Toggle the value of the given pin in port A
		break;
		
		case 'B':
		ToggleBit(PORTB,pinnumber);   //Toggle the value of the given pin in port B
		break;
		
		case 'C':
		ToggleBit(PORTC,pinnumber);   //Toggle the value of the given pin in port C
		break;
		
		case 'D':
		ToggleBit(PORTD,pinnumber);   //Toggle the value of the given pin in port D
		break;
		
		default:
		break;	
		
	}// end of switch 
	
}// end of Function	



/*
 *Function Description : Reverse the value of the given port.
 */

void DIO_vtogglePort(unsigned char portname)
{
	switch(portname)
	{
		case 'A':
		PORTA=~PORTA;
		break;
		
		case 'B':
		PORTB=~PORTB;
		break;
		
		case 'C':
		PORTC=~PORTC;
		break;
		
		case 'D':
		PORTD=~PORTD;
		break;
		
		default:
		break;
	
	}// end of switch

}// end of Function	



/*
 *Function Description  : Connect and disconnect pull up resistor to the given pin at the given port 
 */

void DIO_vconnectPullup(char portname ,char pinnumber, char connect_pullup)
{
	switch(portname)
	{
		case 'A':
		if(connect_pullup==1)
		{
			SetBit(PORTA,pinnumber);
		}
		else
		{
			ClearBit(PORTA,pinnumber);
		}
		break;
		
		case 'B':
		if(connect_pullup==1)
		{
			SetBit(PORTB,pinnumber);
		}
		else
		{
			ClearBit(PORTB,pinnumber);
		}
		break;
		
		case 'C':
		if(connect_pullup==1)
		{
			SetBit(PORTC,pinnumber);
			
		}
		else
		{
			ClearBit(PORTC,pinnumber);
		}
		break;
		
		case 'D':
		if(connect_pullup==1)
		{
			SetBit(PORTD,pinnumber);
			
		}
		else
		{
			ClearBit(PORTD,pinnumber);
		}
		break;
		
		default:
		break;

	}// end of switch
	
}// end of Function	                                                                                                                                        

                                                                                                                                                                                                                                                                

                                             
/*                                                          
 *Function Description : write the first 4-bit of a value to the low nibble of the port  
 */

void DIO_vwrite_low_nibble(unsigned char portname,unsigned char value)
{
	value&=0x0f;      //  mask low nibble of value nnnn,nnnn and 0000,1111 =0000,nnnn
	switch(portname)
	{
		case 'A':
		PORTA&=0xf0;   //  aaaa,aaaa and 1111,0000 = aaaa,0000                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          
		PORTA|=value;  // aaaa,0000 or oooo,nnnn = aaaa,nnnn
		case 'B':
		PORTB&=0xf0;
		PORTB|=value;
		case 'C':
		PORTC&=0xf0;
		PORTC|=value;
		case 'D':
		PORTD&=0xf0;
		PORTD|=value;
	}// end of switch
	
/*  ====================================================================                                                        
 *  2nd method of DIO_vwrite_low_nibble
 *	================================================================
 *	unsigned char i;
	switch(portname)
	{
	case 'A':
 *	for (i=0;i<4;i++)
 *	{
 *		DIO_vwritePin(portname,i,value&1);
 *		value>>=1;
 *	}
	case 'B':
 *	for (i=0;i<4;i++)
 *	{
 *		DIO_vwritePin(portname,i,value&1);
 *		value>>=1;
 *	}
	case 'C':
 *	for (i=0;i<4;i++)
 *	{
 *		DIO_vwritePin(portname,i,value&1);
 *		value>>=1;
 *	}
	case 'D':
 *	for (i=0;i<4;i++)
 *	{
 *		DIO_vwritePin(portname,i,value&1);
 *		value>>=1;
 *	}
	}// end of switch
 */	

}// end of Function	  


/*
 *Function Description :  write the first 4-bit of a value to the high nibble of the port
 */


void DIO_vwrite_high_nibble(unsigned char portname,unsigned char value)
{
	value<<=4;			// or value&=0xf0  mask high nibble of value nnnn,nnnn and 1111,0000 = nnnn,0000
	switch(portname)
	{
		case 'A':
		PORTA&=0x0f;		//  aaaa,aaaa and 0000,1111 = 0000,aaaa 
		PORTA|=value;		// 0000,aaaa  or nnnn,0000 = nnnn,aaaa
		case 'B':
		PORTB&=0x0f;
		PORTB|=value;
		case 'C':
		PORTC&=0x0f;
		PORTC|=value;
		case 'D':
		PORTD&=0x0f;
		PORTD|=value;
	}// end of switch
	
/*  ====================================================================                                                        
 *  2nd method of DIO_vwrite_high_nibble
 *	================================================================
 *	unsigned char i;
	switch(portname)
	{
	case 'A':
 *	for (i=4;i<8;i++)
 *	{
 *		DIO_vwritePin(portname,i,value&1);
 *		value>>=1;
 *	}
	case 'B':
 *	for (i=4;i<8;i++)
 *	{
 *		DIO_vwritePin(portname,i,value&1);
 *		value>>=1;
 *	}
	case 'C':
 *	for (i=4;i<8;i++)
 *	{
 *		DIO_vwritePin(portname,i,value&1);
 *		value>>=1;
 *	}
	case 'D':
 *	for (i=4;i<8;i++)
 *	{
 *		DIO_vwritePin(portname,i,value&1);
 *		value>>=1;
 *	}
	}// end of switch
 */		

}// end of Function	  