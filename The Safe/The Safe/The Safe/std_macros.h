/*
 * std_macros.h
 *
 * Created: 26/04/2022 01:21:48 am
 *  Author: Bahaa Tawfik
 */



#ifndef STD_MACROS_H_
#define STD_MACROS_H_

#define Register_Siz 8

#define SetBit(Reg,Bit)			Reg|=(1<<Bit) 
#define ClearBit(Reg,Bit)		Reg&=(~(1<<Bit))
#define ToggleBit(Reg,Bit)		Reg^=(1<<Bit); 
#define ReadBit(Reg,Bit)	    (Reg&(1<<Bit))>>Bit  

#define Is_Bit_Set(Reg,Bit)		(Reg&(1<<Bit))>>Bit 
#define Is_Bit_Clear(Reg,Bit)   !((Reg&(1<<Bit))>>Bit)
 
#define RTR(Reg,Num)			Reg=(Reg<<(Register_Siz - Bit))|(Reg>>(Bit))
#define RTL(Reg,Num)			Reg=(Reg>>(Register_Siz - Bit))|(Reg<<(Bit))  





#endif /* STD_MACROS_H_ */