#ifndef __SYSTICK_H
#define __SYSTICK_H
#include "stm32f10x_it.h"



void delay_init(void);
void delay_ms(u16 nms);
void delay_us(u32 nus);

#endif




























