#include "stm32f10x.h"                  // Device header
#include "timer.h"
#include "I2C.h"
#include "OLED.h"
#include "head.h"
int main()
{
	/*init GPIO*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef ti1_port = {
		.GPIO_Pin = GPIO_Pin_8,
		.GPIO_Speed = GPIO_Speed_50MHz,
		.GPIO_Mode = GPIO_Mode_IN_FLOATING
	};
	GPIO_InitTypeDef ti2_port = {
		.GPIO_Pin = GPIO_Pin_9,
		.GPIO_Speed = GPIO_Speed_50MHz,
		.GPIO_Mode = GPIO_Mode_IN_FLOATING
	};
	GPIO_InitTypeDef ex_port = {
		.GPIO_Pin = GPIO_Pin_0,
		.GPIO_Speed = GPIO_Speed_50MHz,
		.GPIO_Mode = GPIO_Mode_Out_PP
	};
	GPIO_Init(GPIOA, &ti1_port);
	GPIO_Init(GPIOA, &ti2_port);
	GPIO_Init(GPIOA, &ex_port);
	/*timer init*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	TIM_EncoderInterfaceConfig(TIM1, TIM_EncoderMode_TI12, TIM_ICPolarity_BothEdge, TIM_ICPolarity_BothEdge);
	TIM_TimeBaseInitTypeDef base_config = {
		.TIM_Prescaler = 1 - 1,
		.TIM_CounterMode = TIM_CounterMode_Up,
		.TIM_Period = 1000 - 1,
		.TIM_ClockDivision = TIM_CKD_DIV2,
		.TIM_RepetitionCounter = 0
	};
	TIM_TimeBaseInit(TIM1, &base_config);
	/*start counter*/
	TIM_Cmd(TIM1, ENABLE);
	while(1) {
		if (TIM_GetFlagStatus(TIM1, TIM_FLAG_Update) == RESET) continue;
		TIM_ClearFlag(TIM1, TIM_FLAG_Update);
		if (GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_0) != 0) GPIO_ResetBits(GPIOA, GPIO_Pin_0);
		else GPIO_SetBits(GPIOA, GPIO_Pin_0);
	}
	return 0;
}
