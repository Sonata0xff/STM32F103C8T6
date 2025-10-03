#ifndef OLED_H
#define OLED_H
#include "stm32f10x.h"
#include "I2C.h"


void InitOLED(GPIO_TypeDef* GPIOx, uint16_t SCL_, uint16_t SDA_);//初始化OLED系统的前置系统，
unsigned char TurnOnScreen();//启动屏幕
void FlashScreen(unsigned char val);//刷新屏幕成指定字符
void TurnOffScreen();//关闭屏幕
void Write1Byte(unsigned char v128, unsigned char v64, unsigned char val);//写入1byte数据
void write8x8Char(unsigned char v128, unsigned char v8, unsigned char val[]);//写入一个8x8字符
void Draw1Pic(unsigned char v128, unsigned char v8, unsigned char *pic, unsigned char hight, unsigned char width);//写入一张图片，右上起点
void WirteInString(unsigned char v128, unsigned char v8, int len, char val[]);//写入字符串，len为字符串长度，行写满自动换行，全部写满自动停止，其余自动丢弃
//其中val是ascii码

#endif