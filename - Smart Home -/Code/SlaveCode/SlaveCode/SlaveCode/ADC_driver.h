/*
 * ADC_driver.h
 *
 * 
 * Created: 29/04/2022 
 *  Author: Bahaa Tawfik
 */


#ifndef ADC_DRIVER_H_
#define ADC_DRIVER_H_

/**********************************************************************************************************/
/*	Function Name        : ADC_vinit								*/
/*	Function Returns     : void								   */
/*	Function Arguments   : void 					  */
/*	Function Description : Initialize ADC          */
/*********************************************************************************************************/

void ADC_vinit(void);

/**********************************************************************************************************/
/*	Function Name        : ADC_u16Read								*/
/*	Function Returns     : unsigned short					*/
/*	Function Arguments   : unsigned char pinnumber 					  */
/*	Function Description : read ADC value after conversion         */
/*********************************************************************************************************/
unsigned short ADC_u16Read( unsigned char pinnumber );



#endif /* ADC_DRIVER_H_ */