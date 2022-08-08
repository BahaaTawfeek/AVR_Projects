/*
 * spi_driver.h
 *
 * Created: 1/05/2022 12:06
 *  Author: Bahaa Tawfik
 */


#ifndef SPI_DRIVER_H_
#define SPI_DRIVER_H_

#define Master_ACK   0xFF
#define Slave_ACK    0xFF


/**********************************************************************************************************/
/*	Function Name        : SPI_MasterInit								*/
/*	Function Returns     : void								   */
/*	Function Arguments   : void 					  */
/*	Function Description : Initialize the SPI Communication as a Master          */
/*********************************************************************************************************/
void SPI_MasterInit(void);


/**********************************************************************************************************/
/*	Function Name        : SPI_SlaveInit								*/
/*	Function Returns     : void								   */
/*	Function Arguments   : void 					  */
/*	Function Description : Initialize the SPI Communication as a Slave          */
/*********************************************************************************************************/
void SPI_SlaveInit(void);


/*********************************************************************************************************/
/*	Function Name        : SPI_MasterTransmitchar								*/
/*	Function Returns     : unsigned char								   */
/*	Function Arguments   : unsigned char Data 					  */
/*	Function Description : SPI as a Master  or slave Transmit char      */
/*********************************************************************************************************/
unsigned char SPI_Transmitchar(unsigned char Data);


/**********************************************************************************************************/
/*	Function Name        : SPI_SlaveReceivechar								*/
/*	Function Returns     : unsigned char								   */
/*	Function Arguments   : unsigned char Data 					  */
/*	Function Description : SPI as a Slave or master Receive char     */
/*********************************************************************************************************/
unsigned char SPI_Receivechar(unsigned char Data);


/**********************************************************************************************************/
/*	Function Name        : SPI_MasterTransmitstring								*/
/*	Function Returns     : void								   */
/*	Function Arguments   : unsigned char *ptr 					  */
/*	Function Description : SPI  as a Master or slave Transmit String     */
/*********************************************************************************************************/
void SPI_Transmitstring(unsigned char *ptr);







/************************************************************************/
/*    
void SPI_master_init();
void SPI_slave_init();
void SPI_send_char(unsigned char data);
unsigned char SPI_receive_char();                                                                  */
/************************************************************************/



#endif /* SPI_DRIVER_H_ */