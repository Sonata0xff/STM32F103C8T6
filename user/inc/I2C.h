#ifndef I2C_H
#define I2C_H

#include "stm32f10x.h"
#include "timer.h"
void IIC_Init(GPIO_TypeDef* GPIOx, uint16_t SCL_, uint16_t SDA_);
void StartFunc();
void EndFunc();

void MainSend1Bit(unsigned char bit);
unsigned char SlaveRecAck();
unsigned char MainSend1Byte(unsigned char byte);

unsigned char SlaveSend1Bit();
void MainRecAck(unsigned char ack);
unsigned char SlaveSend1Byte(unsigned char ack);
#endif
