/*
* LED.c
*
*
* Created: 27/04/2022 03:04 am
*  Author: Bahaa Tawfik
*/
#include "DIO.h"
void LED_vInit(unsigned char portname,unsigned char pinnumber)
{
	DIO_vsetPinDir(portname,pinnumber,1);//Set the given pin in the given port as an output
}
void LED_vTurnOn(unsigned char portname,unsigned char pinnumber)
{
	DIO_vwritePin(portname,pinnumber,1);//Set the given pin in the given port to one(on)
}
void LED_vTurnOff(unsigned char portname,unsigned char pinnumber)
{
	DIO_vwritePin(portname,pinnumber,0);//Set the given pin in the given port to zero(off)
}
void LED_vToggle(unsigned char portname,unsigned char pinnumber)
{
	DIO_vtogglePin(portname,pinnumber);//Set the given pin in the given port to zero if it is one or set it to one if it is zero
}

unsigned char LED_u8ReadStatus(unsigned char portname,unsigned char pinnumber)
{
	return DIO_u8readPin(portname,pinnumber);//return the current status of the given pin
}


