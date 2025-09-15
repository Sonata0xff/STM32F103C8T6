#include "I2C.h"

#define NULL 0

#define FIST_DELAY 3
#define SECOND_DELAY 2

GPIO_TypeDef* gpiox = NULL;
uint16_t SCL = 0;
uint16_t SDA = 0;
unsigned char initFlag = 0;

void IIC_Init(GPIO_TypeDef* GPIOx, uint16_t SCL_, uint16_t SDA_)
{
	gpiox = GPIOx;
	SCL = SCL_;
	SDA = SDA_;
	GPIO_InitTypeDef gpio_scl = {
		.GPIO_Pin = SCL,
		.GPIO_Speed = GPIO_Speed_50MHz,
		.GPIO_Mode = GPIO_Mode_Out_PP
	};
	GPIO_InitTypeDef gpio_sda = {
		.GPIO_Pin = SDA,
		.GPIO_Speed = GPIO_Speed_50MHz,
		.GPIO_Mode = GPIO_Mode_Out_OD
	};
	GPIO_Init(gpiox, &gpio_scl);
	GPIO_SetBits(gpiox, SCL);
	GPIO_Init(gpiox, &gpio_sda);
	GPIO_SetBits(gpiox, SDA);
	TimerInitWithOutIT();
	initFlag = 1;
}
void StartFunc()
{
	Delay_xus_wit(FIST_DELAY);
	GPIO_ResetBits(gpiox, SDA);
	Delay_xus_wit(SECOND_DELAY);
	GPIO_ResetBits(gpiox, SCL);
}

void EndFunc()
{
	Delay_xus_wit(FIST_DELAY);
	GPIO_SetBits(gpiox, SCL);
	Delay_xus_wit(SECOND_DELAY);
	GPIO_SetBits(gpiox, SDA);
}

void MainSend1Bit(unsigned char bit)
{
	if (bit) GPIO_SetBits(gpiox, SDA);
	Delay_xus_wit(FIST_DELAY);
	GPIO_SetBits(gpiox, SCL);
	Delay_xus_wit(SECOND_DELAY);
	GPIO_ResetBits(gpiox, SCL);
	GPIO_ResetBits(gpiox, SDA);
}

unsigned char SlaveRecAck()
{
	unsigned char res;
	GPIO_SetBits(gpiox, SDA);
	Delay_xus_wit(FIST_DELAY);
	GPIO_SetBits(gpiox, SCL);
	Delay_xus_wit(SECOND_DELAY); 
	res = GPIO_ReadInputDataBit(gpiox, SDA);
	GPIO_ResetBits(gpiox, SCL);
	GPIO_ResetBits(gpiox, SDA);
	return res;
}

unsigned char MainSend1Byte(unsigned char byte)
{
	unsigned char loopC;
	for (loopC = 128; loopC > 0; loopC >>= 1) {
		if (loopC & byte) MainSend1Bit(1);
		else MainSend1Bit(0);
	}
	return SlaveRecAck();
}

unsigned char SlaveSend1Bit()
{
	unsigned char res;
	GPIO_SetBits(gpiox, SDA);
	Delay_xus_wit(FIST_DELAY);
	GPIO_SetBits(gpiox, SCL);
	res = GPIO_ReadInputDataBit(gpiox, SDA);
	Delay_xus_wit(SECOND_DELAY);
	GPIO_ResetBits(gpiox, SCL);
	GPIO_ResetBits(gpiox, SDA);
	return res;
}

void MainRecAck(unsigned char ack)
{
	if (ack) GPIO_SetBits(gpiox, SDA);
	Delay_xus_wit(FIST_DELAY);
	GPIO_SetBits(gpiox, SCL);
	Delay_xus_wit(SECOND_DELAY);
	GPIO_ResetBits(gpiox, SCL);
	GPIO_ResetBits(gpiox, SDA);
}

unsigned char SlaveSend1Byte(unsigned char ack)
{
	unsigned char res = 0, loopC;
	for (loopC = 128; loopC > 0; loopC >>= 1) {
		if (SlaveSend1Bit()) res |= loopC;
	}
	MainRecAck(ack);
	return res;
}
