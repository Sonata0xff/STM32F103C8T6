#include "head.h"
void TIM1_CC_IRQHandler()
{
	uint16_t val = TIM_GetCapture1(TIM1);
	if (val == 1000 - 1 || val == 1000) GPIO_SetBits(GPIOA, GPIO_Pin_0);
	else GPIO_ResetBits(GPIOA, GPIO_Pin_0);
	TIM_SetCounter(TIM1, 0x0000);
	TIM_ClearITPendingBit(TIM1, TIM_IT_CC1);
}
