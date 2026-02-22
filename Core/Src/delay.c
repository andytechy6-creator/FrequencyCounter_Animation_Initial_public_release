/*
 * delay.c
 *
 *  Created on: Feb 15, 2026
 *      Author: andyx
 */


#include "delay.h"
#include "main.h"

void delay_ms(uint32_t ms)
{
    LL_mDelay(ms);
}
