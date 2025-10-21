#include "stm32f10x.h"                  // Device header
#include "timer.h"
#include "I2C.h"
#include "OLED.h"
#include "head.h"
int main()
{
	/*init GPIO*/
	TimerInitWithOutIT();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	uint16_t SCL = GPIO_Pin_11;
	uint16_t SDA = GPIO_Pin_12;
	InitOLED(GPIOA, SCL, SDA);
	TurnOnScreen();
	unsigned char tmpData[] = "hello,world!sssssss";
	char tmpData2 = '&';
	FlashScreen(0x00);
	WirteIn16x8Char(0,0, tmpData2);
	while(1);
	return 0;
}
