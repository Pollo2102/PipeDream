#ifndef _KEYPAD_H
#define _KEYPAD_H

#include "system.h"

void delay_ms(uint32_t ms);
void keypad_init();
uint8_t keypad_getkey();

#endif
