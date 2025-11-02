#ifndef HEAD_H
#define HEAD_H
#include "stm32f10x.h"                  // Device header
void words2Str(u16 value, char str[5]);
void Uint8toStr(u8 value, char str[2]);
#endif