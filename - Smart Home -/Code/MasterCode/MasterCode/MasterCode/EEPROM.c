/*
 * EEPROM.c
 *
 * Created: 08/05/2022 09:44:21 م
 *  Author: Bahaa
 */ 
#include <avr/io.h>
#include "EEPROM.h"
#include "std_macros.h"


/*
 *Function Description : write one byte of Data  to the given  address.
 */

void EEPROM_vwrite(unsigned short address , unsigned char data)
{
// set uo address Register
	EEARL = (unsigned char) address;
	EEARH = (unsigned char)(address>>8);
	
// set uo data Register
	EEDR = data;
	
// set EEMWE bit number 2  and EEWE bit number 1    or    EECR|= SetBit(1<<EEMWE)|SetBit(1<<EEWE)
	SetBit(EECR,EEMWE);
	SetBit(EECR,EEWE);
	
/* wait for complete write operation     or   while( !( ReadBit(EECR,EEWE)) )*/
	
	/* wait for completion of write operation  */
	while(ReadBit(EECR,EEWE)==1);
}


/*
 *
 *Function Description : read one byte of Data  from the given  address.
 */

unsigned char EEPROM_u8read(unsigned short address)
{
// set uo address Register
	EEARL = (unsigned char) address;
	EEARH = (unsigned char)(address>>8);
	
// start EEPROM Read by setting EEMWE bit number 0      or    EECR|= SetBit(1<<EERE)
	SetBit(EECR,EERE);
// return data from data register
	return EEDR;	
}


