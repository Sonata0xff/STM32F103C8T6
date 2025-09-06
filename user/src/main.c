#include "stm32f10x.h"                  // Device header
#include "timer.h"
#include "I2C.h"
int main()
{
	unsigned char tmp = 0xad;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	IIC_Init(GPIOA, GPIO_Pin_0, GPIO_Pin_1);
	StartFunc();
	MainSend1Byte(tmp);
	EndFunc();
	while(1);
	return 0;
}
