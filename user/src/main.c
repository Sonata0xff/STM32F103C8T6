#include "stm32f10x.h"                  // Device header
#include "timer.h"
#include "I2C.h"
#include "OLED.h"
#include "head.h"
int main()
{
	/*GPIO outport init*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef gpioA0_config = {
		.GPIO_Pin = GPIO_Pin_0,
		.GPIO_Speed = GPIO_Speed_50MHz,
		.GPIO_Mode = GPIO_Mode_Out_PP
	};
	GPIO_Init(GPIOA, &gpioA0_config);
	GPIO_SetBits(GPIOA, GPIO_Pin_0);
	/*GPIO remap inputport init*/
	GPIO_InitTypeDef input_port_config = {
		.GPIO_Pin = GPIO_Pin_8,
		.GPIO_Speed = GPIO_Speed_50MHz,
		.GPIO_Mode = GPIO_Mode_IN_FLOATING
	};
	GPIO_Init(GPIOA, &input_port_config);
	/*TIM1 init*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	TIM_InternalClockConfig(TIM1);
	TIM_TimeBaseInitTypeDef base_config = {
		.TIM_Prescaler = 71,
		.TIM_CounterMode = TIM_CounterMode_Up,
		.TIM_Period = 10000,
		.TIM_ClockDivision = TIM_CKD_DIV2,
		.TIM_RepetitionCounter = 0
	};
	TIM_TimeBaseInit(TIM1, &base_config);
	TIM_ICInitTypeDef ic_config = {
		.TIM_Channel = TIM_Channel_1,
		.TIM_ICPolarity = TIM_ICPolarity_Rising,
		.TIM_ICSelection = TIM_ICSelection_DirectTI,
		.TIM_ICPrescaler = TIM_ICPSC_DIV1,
		.TIM_ICFilter = 1
	};
	TIM_ICInit(TIM1, &ic_config);
	TIM_ITConfig(TIM1, TIM_IT_CC1, ENABLE);
	/*NVIC init*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef nvic_config = {
		.NVIC_IRQChannel = TIM1_CC_IRQn,
		.NVIC_IRQChannelPreemptionPriority = 1,
		.NVIC_IRQChannelSubPriority = 1,
		.NVIC_IRQChannelCmd = ENABLE
	};
	NVIC_Init(&nvic_config);
	/*Start func*/
	
	TIM_CCxCmd(TIM1, TIM_Channel_1, TIM_CCx_Enable);
	TIM_Cmd(TIM1, ENABLE);
	while(1);
	return 0;
}
