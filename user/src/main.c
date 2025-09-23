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
	Delay_xms_wit(500);
	FlashScreen(0x00);
	Delay_xms_wit(500);
	Delay_xms_wit(500);
	Delay_xms_wit(500);
	FlashScreen(0xff);
	Delay_xms_wit(500);
	Delay_xms_wit(500);
	Delay_xms_wit(500);
	FlashScreen(0xaa);
	Delay_xms_wit(500);
	Delay_xms_wit(500);
	Delay_xms_wit(500);
	TurnOffScreen();
	Delay_xms_wit(500);
	Delay_xms_wit(500);
	Delay_xms_wit(500);
	TurnOnScreen();
	Delay_xms_wit(500);
	FlashScreen(0x00);
	Delay_xms_wit(500);
	Delay_xms_wit(500);
	Delay_xms_wit(500);
	FlashScreen(0xff);
	Delay_xms_wit(500);
	Delay_xms_wit(500);
	Delay_xms_wit(500);
	FlashScreen(0xaa);
	Delay_xms_wit(500);
	Delay_xms_wit(500);
	Delay_xms_wit(500);
	TurnOffScreen();
	//FlashScreenWh();
	//problem left: can not delet all memory
	while(1);
	return 0;
}
