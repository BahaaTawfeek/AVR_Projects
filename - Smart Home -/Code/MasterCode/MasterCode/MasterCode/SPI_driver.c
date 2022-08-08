/*
 * SPI.c
 *
 * Created: 1/05/2022 12:06
 *  Author: Bahaa Tawfik
 */


#include <avr/io.h>
#include <avr/interrupt.h>
#include "DIO.h"
#include "std_macros.h"
#define F_CPU 8000000UL
#include <util/delay.h>






/************************************************************************/
/* 
#define MOSI 7
#define MISO 6
#define CS	4
#define CLK 5                                                    */
/************************************************************************/



/*	Function Description : Initialize the SPI Communication as a Master          */
void SPI_MasterInit(void)
{
	/************************************************************************/
	/*     DRB |= (1<<MOSI)|(1<<CS)|(1<<CLK);
	      SPCR = 1<<MSTR | 1<<SPE;                                          */
	/************************************************************************/
	/*Set SS / MOSI / SCK  as output pins for master*/
	DIO_vsetPinDir('B',4,1);
	DIO_vsetPinDir('B',5,1);
	DIO_vsetPinDir('B',7,1);
	/*Enable Master mode*/
	SetBit(SPCR,MSTR);
	/*Set clock to fosc/16*/
	SetBit(SPCR,SPR0);
	/*Enable SPI*/
    SetBit(SPCR,SPE);
	/*set SS to high */
	DIO_vwritePin('B',4,1);
}


/*	Function Description : Initialize the SPI Communication as a Slave          */
void SPI_SlaveInit(void)
{
	/************************************************************************/
	/* 
	SetBit(DDRB,MISO);	// MISO
	SetBit(SPCR,SPE);	// enable SPI                                                                     */
	/************************************************************************/
	/*Enable SPI*/
	SetBit(SPCR,SPE);
	/*Set MISO as output*/
	DIO_vsetPinDir('B',6,1);
}



/*	Function Description : SPI as a Master or slave Transmit char      */
unsigned char SPI_Transmitchar(unsigned char Data)
{
	/*Clear SS to send data to slave*/
	DIO_vwritePin('B',4,0);
	/*Put data on SPDR*/
	SPDR=Data;
	/*Wait until the transmission is finished*/
     while(ReadBit(SPSR,SPIF)==0);	
	 /*read SPDR*/
	 return SPDR ;
}


/*	Function Description : SPI as a Slave or master Receive char     */
unsigned char SPI_Receivechar(unsigned char Data)
{
	/*Put data on SPDR*/
	SPDR=Data;
	/*Wait until data is received in SPI register*/
	while(ReadBit(SPSR,SPIF)==0);
	/*read the received data*/
	return SPDR ;
}


/*	Function Description : SPI  as a Master or slave Transmit String     */
void SPI_Transmitstring(unsigned char *ptr)
{
	while((*ptr)!=0)
	{
		SPI_Transmitchar(*ptr);
		_delay_ms(300);
		ptr++;
	}
}






/************************************************************************/
/* 
   void SPI_send_char(unsigned char data){
	   SPDR = data;
	   while(ReadBit(SPSR,SPIF) == 0);
   }
   
   unsigned char SPI_receive_char(unsigned char data){
	   SPDR = data;//move the given data to SPI Data register
	   while(ReadBit(SPSR,SPIF) == 0);
	   return SPDR; //return the value of SPI Data register after the  receiving is done
   }

                                                                  */
/************************************************************************/



