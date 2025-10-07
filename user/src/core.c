#include "head.h"
void TIM1_UP_IRQHandler()
{
	if (GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_0)) GPIO_ResetBits(GPIOA, GPIO_Pin_0);
	else GPIO_SetBits(GPIOA, GPIO_Pin_0);
	TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
}
