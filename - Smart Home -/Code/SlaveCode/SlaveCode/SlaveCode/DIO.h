/*
 * DIO.h
 *
 * Created: 26/04/2022 01:22:04 am
 *  Author: Bahaa Tawfik
 */
 


#ifndef DIO_H_
#define DIO_H_


/*
Function Name        : DIO_vsetPinDir
Function Returns     : void
Function Arguments   : unsigned char portname,unsigned char pinnumber,unsigned char direction
Function Description : Set the direction of the given pin in the given port (direction 0 = input : 1 = output)
*/

void DIO_vsetPinDir(unsigned char portname,unsigned char pinnumber,unsigned char direction);

/*
Function Name        : DIO_vsetPortDir
Function Returns     : void
Function Arguments   : unsigned char portname,unsigned char direction
Function Description : set the direction of whole port .
*/

void DIO_vsetPortDir(unsigned char portname,unsigned char direction);







/*
Function Name        : DIO_vwritePin
Function Returns     : void
Function Arguments   : unsigned char portname,unsigned char pinnumber,unsigned char value
Function Description : Set the value of the given pin in the given port (outputvalue 0 = low : 1 = high)
*/

void DIO_vwritePin(unsigned char portname,unsigned char pinnumber,unsigned char value);

/*
Function Name        : DIO_vwritePort
Function Returns     : void
Function Arguments   : unsigned char portname,unsigned char value
Function Description : Write the value to all port pins.
*/

void DIO_vwritePort(unsigned char portname,unsigned char value);







/*
Function Name        : DIO_u8readPin
Function Returns     : unsigned char
Function Arguments   : unsigned char portname,unsigned char pinnumber
Function Description : Returns 1 if the value of the given pin is high and zero if the value is low
*/

unsigned char DIO_u8readPin(unsigned char portname,unsigned char pinnumber);

/*
Function Name        : DIO_u8readPort
Function Returns     : unsigned char
Function Arguments   : unsigned char portname
Function Description : read the value of the port .
*/

unsigned char DIO_u8readPort(unsigned char portname);







/*
Function Name        : DIO_vtogglePin
Function Returns     : void
Function Arguments   : unsigned char portname,unsigned char pinnumber
Function Description : Reverse the value of the given pin in the given port.
*/

void DIO_vtogglePin(unsigned char portname,unsigned char pinnumber);
/*
Function Name        : DIO_vtogglePort
Function Returns     : void
Function Arguments   : unsigned char portname
Function Description : Reverse the value of the given port.
*/
void DIO_vtogglePort(unsigned char portname);






/*
Function Name        : DIO_vconnectPullup                                                                
Function Returns     : void                                                                          
Function Arguments   : char portname ,char pinnumber, char connect_pullup              
Function Description : Connect and disconnect pull up resistor to the given pin at the given port                  
*/

void DIO_vconnectPullup(char portname ,char pinnumber, char connect_pullup);




/*
Function Name        : DIO_vwrite_low_nibble                                                            
Function Returns     : void                                                                          
Function Arguments   : unsigned char portname,unsigned char value                                        
Function Description : write the first 4-bit of a value to the low nibble of the port  
*/
void DIO_vwrite_low_nibble(unsigned char portname,unsigned char value);
/*
Function Name        : DIO_vwrite_high_nibble
Function Returns     : void
Function Arguments   : unsigned char portname,unsigned char value
Function Description : write the first 4-bit of a value to the high nibble of the port
*/

void DIO_vwrite_high_nibble(unsigned char portname,unsigned char value);




#endif /* DIO_H_ */