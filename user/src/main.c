#include "stm32f10x.h"                  // Device header
#include "timer.h"
#include "I2C.h"
#include "OLED.h"
#include "head.h"
int main()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef outport = {
		.GPIO_Pin = GPIO_Pin_0,
		.GPIO_Speed = GPIO_Speed_50MHz,
		.GPIO_Mode = GPIO_Mode_Out_PP
	};
	GPIO_Init(GPIOA, &outport);
	GPIO_SetBits(GPIOA, GPIO_Pin_0);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitTypeDef inport = {
		.GPIO_Pin = GPIO_Pin_5,
		.GPIO_Speed = GPIO_Speed_50MHz,
		.GPIO_Mode = GPIO_Mode_IPU
	};
	GPIO_Init(GPIOB, &inport);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource5);
	EXTI_InitTypeDef exti_config = {
		.EXTI_Line = EXTI_Line5,
		.EXTI_Mode = EXTI_Mode_Interrupt,
		.EXTI_Trigger = EXTI_Trigger_Falling,
		.EXTI_LineCmd = ENABLE
	};
	EXTI_Init(&exti_config);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef nvic_config = {
		.NVIC_IRQChannel = EXTI9_5_IRQn,
		.NVIC_IRQChannelPreemptionPriority = 1,
		.NVIC_IRQChannelSubPriority = 1,
		.NVIC_IRQChannelCmd = ENABLE
	};
	NVIC_Init(&nvic_config);
	while(1);
	return 0;
}
