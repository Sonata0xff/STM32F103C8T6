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
	unsigned char pic[4][4] = {{0xff, 0xff, 0xff, 0xff},
							   {0xff, 0xff, 0xff, 0xff},
							   {0xff, 0xff, 0xff, 0xff},
							   {0xff, 0xff, 0xff, 0xff}};
	Draw1Pic(0,0,&pic[0][0],4,4);
	while(1);
	return 0;
}
