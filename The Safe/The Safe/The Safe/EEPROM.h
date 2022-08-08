/*
 * EEPROM.h
 *
 * Created: 08/05/2022 09:44:03 م
 *  Author: Bahaa
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_


void EEPROM_vwrite(unsigned short address , unsigned char data);
unsigned char EEPROM_u8read(unsigned short address);



#endif /* EEPROM_H_ */