#ifndef OLED_H
#define OLED_H
#include "stm32f10x.h"
#include "I2C.h"


void InitOLED(GPIO_TypeDef* GPIOx, uint16_t SCL_, uint16_t SDA_);//��ʼ��OLEDϵͳ��ǰ��ϵͳ��
unsigned char TurnOnScreen();//������Ļ
void FlashScreen(unsigned char val);//ˢ����Ļ��ָ���ַ�
void TurnOffScreen();//�ر���Ļ
void Write1Byte(unsigned char v128, unsigned char v64, unsigned char val);//д��1byte����
void write8x8Char(unsigned char v128, unsigned char v8, unsigned char val[]);//д��һ��8x8�ַ�
void Draw1Pic(unsigned char v128, unsigned char v8, unsigned char *pic, unsigned char hight, unsigned char width);//д��һ��ͼƬ���������
void WirteInString(unsigned char v128, unsigned char v8, int len, char val[]);//д���ַ�����lenΪ�ַ������ȣ���д���Զ����У�ȫ��д���Զ�ֹͣ�������Զ�����
//����val��ascii��

#endif