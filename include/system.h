/*
 * system.h
 *
 *  Created on: Jul 6, 2017
 *      Author: ideras
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_

#ifndef __ASSEMBLER__

typedef unsigned char  bool;
typedef unsigned int   uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char  uint8_t;
typedef signed   char  int8_t;
typedef signed   int   int32_t;
typedef unsigned short int16_t;

typedef volatile uint16_t *vga_ptr_t;

#define true  1
#define false 0

#define VGA_START_ADDR      ((vga_ptr_t)0xb800)
#define VGA_END_ADDR        ((vga_ptr_t)0xcabf)
#define BTN_STATE_REG_ADDR  ((volatile unsigned char *)0xffff0004)
#define MS_COUNTER_REG_ADDR ((volatile unsigned int  *)0xffff0008)

#else

#define VGA_START_ADDR      0xb800
#define VGA_END_ADDR        0xcabf
#define KEYPAD_STATE_REG_ADDR  0xffff0004
#define MS_COUNTER_REG_ADDR    0xffff0008
#define KEYPAD_COUNT           8

#endif

#endif /* SYSTEM_H_ */
