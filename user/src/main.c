#include "stm32f10x.h"                  // Device header
#include "timer.h"
#include "I2C.h"
#include "OLED.h"
#include "head.h"
int main()
{
	/*get pwm value*/
	uint16_t timer_period_us = 1000;
	float emp_precent = 0.5;
	uint16_t wholePeriod = (uint16_t)(timer_period_us / 2);
	uint16_t lowPeriod = (uint16_t)(wholePeriod * emp_precent);
	/*init outport gpio*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef outport_config = {
		.GPIO_Pin = GPIO_Pin_8,
		.GPIO_Speed = GPIO_Speed_50MHz,
		.GPIO_Mode = GPIO_Mode_AF_PP
	};
	GPIO_Init(GPIOA, &outport_config);
	/*init timer1*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	TIM_InternalClockConfig(TIM1);
	TIM_TimeBaseInitTypeDef base_config = {
		.TIM_Prescaler = 72 - 1,
		.TIM_CounterMode = TIM_CounterMode_CenterAligned1,
		.TIM_Period = wholePeriod,
		.TIM_ClockDivision = TIM_CKD_DIV2,
		.TIM_RepetitionCounter = 0
	};
	TIM_TimeBaseInit(TIM1, &base_config);
	TIM_OCInitTypeDef oc_config = {
		.TIM_OCMode = TIM_OCMode_Toggle,
		.TIM_OutputState = TIM_OutputState_Enable,
		.TIM_OutputNState = TIM_OutputNState_Disable,
		.TIM_Pulse = lowPeriod,
		.TIM_OCPolarity = TIM_OCPolarity_High,
		.TIM_OCNPolarity = TIM_OCNPolarity_High,
		.TIM_OCIdleState = TIM_OCIdleState_Reset,
		.TIM_OCNIdleState = TIM_OCNIdleState_Reset
	};
	TIM_CtrlPWMOutputs(TIM1, ENABLE);
	TIM_OC1Init(TIM1, &oc_config);
	/*start system*/
	TIM_Cmd(TIM1, ENABLE);
	while(1);
	return 0;
}
