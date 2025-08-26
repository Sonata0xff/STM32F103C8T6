#ifndef TIMER_H
#define TIMER_H

#include "stm32f10x.h"
void TimerInit(void);
void Delay_xus(uint16_t us);
void Delay_xms(uint16_t ms);

void TimerInitWithOutIT(void);
void Delay_xus_wit(uint16_t us);
void Delay_xms_wit(uint16_t ms);
#endif
