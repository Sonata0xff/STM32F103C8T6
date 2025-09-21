#include "stm32f10x.h"                  // Device header
#include "timer.h"
#include "I2C.h"
int main()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef gpio_a12 = {
		.GPIO_Pin = GPIO_Pin_12,
		.GPIO_Speed = GPIO_Speed_50MHz,
		.GPIO_Mode = GPIO_Mode_Out_PP
	};
	uint16_t scl = GPIO_Pin_0;
	uint16_t sda = GPIO_Pin_1;
	GPIO_Init(GPIOA, &gpio_a12);
	GPIO_ResetBits(GPIOA, GPIO_Pin_12);
	//GPIO_SetBits(GPIOA, GPIO_Pin_12);
	IIC_Init(GPIOA, scl, sda);
	// start
	StartFunc();
	//address send
	if (MainSend1Byte(0x78) != 0x00) {
		GPIO_SetBits(GPIOA, GPIO_Pin_12);
		while(1);
	}
	//control byte
	if (MainSend1Byte(0x00) != 0x00) {
		GPIO_SetBits(GPIOA, GPIO_Pin_12);
		while(1);
	}
	//set display off
	if (MainSend1Byte(0xae) != 0x00) {
		GPIO_SetBits(GPIOA, GPIO_Pin_12);
		while(1);
	}
	//set display ratio
	if (MainSend1Byte(0x20) != 0x00) {
		GPIO_SetBits(GPIOA, GPIO_Pin_12);
		while(1);
	}
	if (MainSend1Byte(0x00) != 0x00) {
		GPIO_SetBits(GPIOA, GPIO_Pin_12);
		while(1);
	}
	//set multiplex ratio
	if (MainSend1Byte(0xb0) != 0x00) {
		GPIO_SetBits(GPIOA, GPIO_Pin_12);
		while(1);
	}
	if (MainSend1Byte(0xc8) != 0x00) {
		GPIO_SetBits(GPIOA, GPIO_Pin_12);
		while(1);
	}
	//set display offset
	if (MainSend1Byte(0x40) != 0x00) {
		GPIO_SetBits(GPIOA, GPIO_Pin_12);
		while(1);
	}
	if (MainSend1Byte(0x81) != 0x00) {
		GPIO_SetBits(GPIOA, GPIO_Pin_12);
		while(1);
	}
	//set display start line
	if (MainSend1Byte(0xff) != 0x00) {
		GPIO_SetBits(GPIOA, GPIO_Pin_12);
		while(1);
	}
	//set Charge pump
	if (MainSend1Byte(0xa1) != 0x00) {
		GPIO_SetBits(GPIOA, GPIO_Pin_12);
		while(1);
	}
	if (MainSend1Byte(0xa6) != 0x00) {
		GPIO_SetBits(GPIOA, GPIO_Pin_12);
		while(1);
	}
	//set segment remap
	if (MainSend1Byte(0xa8) != 0x00) {
		GPIO_SetBits(GPIOA, GPIO_Pin_12);
		while(1);
	}
	//Set com Output dir
	if (MainSend1Byte(0x3f) != 0x00) {
		GPIO_SetBits(GPIOA, GPIO_Pin_12);
		while(1);
	}
	//Set Com Pins Hardware config
	if (MainSend1Byte(0xa4) != 0x00) {
		GPIO_SetBits(GPIOA, GPIO_Pin_12);
		while(1);
	}
	if (MainSend1Byte(0xd3) != 0x00) {
		GPIO_SetBits(GPIOA, GPIO_Pin_12);
		while(1);
	}
	//set constrast control
	if (MainSend1Byte(0x00) != 0x00) {
		GPIO_SetBits(GPIOA, GPIO_Pin_12);
		while(1);
	}
	if (MainSend1Byte(0xd5) != 0x00) {
		GPIO_SetBits(GPIOA, GPIO_Pin_12);
		while(1);
	}
	//Set Pre-Charge Period
	if (MainSend1Byte(0x80) != 0x00) {
		GPIO_SetBits(GPIOA, GPIO_Pin_12);
		while(1);
	}
	if (MainSend1Byte(0xd9) != 0x00) {
		GPIO_SetBits(GPIOA, GPIO_Pin_12);
		while(1);
	}
	//Set VCOMH Deselect level
	if (MainSend1Byte(0x22) != 0x00) {
		GPIO_SetBits(GPIOA, GPIO_Pin_12);
		while(1);
	}
	if (MainSend1Byte(0xda) != 0x00) {
		GPIO_SetBits(GPIOA, GPIO_Pin_12);
		while(1);
	}
	//Set Entire Display on
	if (MainSend1Byte(0x12) != 0x00) {
		GPIO_SetBits(GPIOA, GPIO_Pin_12);
		while(1);
	}
	//Set Normal display
	if (MainSend1Byte(0xdb) != 0x00) {
		GPIO_SetBits(GPIOA, GPIO_Pin_12);
		while(1);
	}
	//delay for stable
	//Delay_xms_wit(2);
	//Set display on
	if (MainSend1Byte(0x20) != 0x00) {
		GPIO_SetBits(GPIOA, GPIO_Pin_12);
		while(1);
	}
	if (MainSend1Byte(0x8d) != 0x00) {
		GPIO_SetBits(GPIOA, GPIO_Pin_12);
		while(1);
	}
	if (MainSend1Byte(0x14) != 0x00) {
		GPIO_SetBits(GPIOA, GPIO_Pin_12);
		while(1);
	}
	if (MainSend1Byte(0xaf) != 0x00) {
		GPIO_SetBits(GPIOA, GPIO_Pin_12);
		while(1);
	}
	EndFunc();
	Delay_xms_wit(100);
	// start
	StartFunc();
	//address send
	if (MainSend1Byte(0x78) != 0x00) {
		GPIO_SetBits(GPIOA, GPIO_Pin_12);
		while(1);
	}
	//control byte
	if (MainSend1Byte(0x40) != 0x00) {
		GPIO_SetBits(GPIOA, GPIO_Pin_12);
		while(1);
	}
	//write data
	for (int i = 0;i < 64; i++) {
		if (MainSend1Byte(0xf0) != 0x00) {
			GPIO_SetBits(GPIOA, GPIO_Pin_12);
			while(1);
		}
		Delay_xms_wit(5);
	}
	for (int i = 64;i < 128; i++) {
		if (MainSend1Byte(0x0f) != 0x00) {
			GPIO_SetBits(GPIOA, GPIO_Pin_12);
			while(1);
		}
		Delay_xms_wit(5);
	}
	//end func
	EndFunc();
	while(1);
	return 0;
}
