/*
 * keypad.h
 *
 * Created: 26/04/2022 01:24:28 am
 *  Author: Bahaa Tawfik
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_
#include "DIO.h"

#define NOTPRESSED  0xff     //0b1111,1111 due to pull-up

void keypad_vInit();
char keypad_u8check_press();




#endif /* KEYPAD_H_ */