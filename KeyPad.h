#ifndef __KEYPAD__H__
#define __KEYPAD__H__
#include "tm4c123gh6pm.h"
#include "stdint.h"
uint8_t KeyPad_getPressedKey(void);
void KeyPad_init(void);
#endif
