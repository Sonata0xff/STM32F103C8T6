#include "stm32f10x.h"                  // Device header
#include "timer.h"
#include "I2C.h"
#include "OLED.h"
int main()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	uint16_t scl = GPIO_Pin_0;
	uint16_t sda = GPIO_Pin_1;
	InitOLED(GPIOA, scl, sda);
	TurnOnScreen();
	FlashScreen(0x00);
	Write1Byte(127, 7, 0x80);
	unsigned char char8x8[8] = {0x3e, 0x02, 0x02, 0x3e, 0x02,0x02,0x02,0x02}; 
	write8x8Char(64, 4, char8x8);
	//problem left: can not delet all memory
	while(1);
	return 0;
}
