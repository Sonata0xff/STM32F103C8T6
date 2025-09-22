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
	FlashScreen();
	//problem left: can not delet all memory
	while(1);
	return 0;
}
