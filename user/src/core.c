#include "head.h"

void EXTI9_5_IRQHandler()
{
	if (EXTI_GetITStatus(EXTI_Line5) == SET) {
		EXTI_ClearITPendingBit(EXTI_Line5);
		if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)) GPIO_ResetBits(GPIOA, GPIO_Pin_0);
		else GPIO_SetBits(GPIOA, GPIO_Pin_0);
	} else return; 
}