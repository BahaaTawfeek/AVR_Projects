/*
 * DIO.h
 *
 * Created: 26/04/2022 01:22:04 am
 *  Author: Bahaa Tawfik
 */
 


#ifndef DIO_H_
#define DIO_H_

void DIO_vsetPinDir(unsigned char portname,unsigned char pinnumber,unsigned char direction);
void DIO_vsetPortDir(unsigned char portname,unsigned char direction);

void DIO_vwritePin(unsigned char portname,unsigned char pinnumber,unsigned char value);
void DIO_vwritePort(unsigned char portname,unsigned char value);

unsigned char DIO_u8readPin(unsigned char portname,unsigned char pinnumber);
unsigned char DIO_u8readPort(unsigned char portname);

void DIO_vtogglePin(unsigned char portname,unsigned char pinnumber);
//void DIO_vtogglePort(unsigned char portname);


void DIO_vconnectPullup(char portname ,char pinnumber, char connect_pullup);

void DIO_vwrite_low_nibble(unsigned char portname,unsigned char value);
void DIO_vwrite_high_nibble(unsigned char portname,unsigned char value);



#endif /* DIO_H_ */