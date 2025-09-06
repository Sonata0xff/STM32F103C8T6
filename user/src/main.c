#include "stm32f10x.h"                  // Device header
#include "timer.h"
int main()
{
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef gpioa = {
		.GPIO_Pin = GPIO_Pin_0,
		.GPIO_Speed = GPIO_Speed_50MHz,
		.GPIO_Mode = GPIO_Mode_Out_PP
	};
	GPIO_Init(GPIOA, &gpioa);
	GPIO_ResetBits(GPIOA, GPIO_Pin_0);
	//TimerInit();
	TimerInitWithOutIT();
	while(1) {
		GPIO_SetBits(GPIOA, GPIO_Pin_0);
		Delay_xus_wit(4);
		GPIO_ResetBits(GPIOA, GPIO_Pin_0);
		Delay_xus_wit(4);
	};
	return 0;
}
