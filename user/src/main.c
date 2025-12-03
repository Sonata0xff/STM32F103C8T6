#include "stm32f10x.h"                  // Device header
#include "timer.h"
#include "I2C.h"
#include "OLED.h"
#include "head.h"

int main()
{
	//oledc初始化
	char title1[] = "rec:";
	TimerInitWithOutIT();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	uint16_t SCL = GPIO_Pin_11;
	uint16_t SDA = GPIO_Pin_12;
	InitOLED(GPIOA, SCL, SDA);
	TurnOnScreen();
	FlashScreen(0x00);
	WriteIn16x8String(0, 0, 4, title1);
	//设置目标地址与源地址数组，并在oled上显示
	
	//GPIO初始化 for USART
	GPIO_InitTypeDef tx_config = {
		.GPIO_Pin = GPIO_Pin_2,
		.GPIO_Speed = GPIO_Speed_50MHz,
		.GPIO_Mode = GPIO_Mode_AF_PP
	};
	GPIO_InitTypeDef rx_coonfiig = {
		.GPIO_Pin = GPIO_Pin_3,
		.GPIO_Speed = GPIO_Speed_50MHz,
		.GPIO_Mode = GPIO_Mode_IN_FLOATING
	};
	GPIO_Init(GPIOA, &tx_config);
	GPIO_Init(GPIOA, &rx_coonfiig);
	
	//USART初始化
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	USART_InitTypeDef usartConfig = {
		.USART_BaudRate = 9600,
		.USART_WordLength = USART_WordLength_8b,
		.USART_StopBits = USART_StopBits_1,
		.USART_Parity = USART_Parity_No,
		.USART_Mode = (USART_Mode_Rx | USART_Mode_Tx),
		.USART_HardwareFlowControl = USART_HardwareFlowControl_None
	};
	USART_Init(USART2, &usartConfig);
	USART_SetPrescaler(USART2, 1);
	//USART_ITConfig(USART2, USART_IT_TC, ENABLE);
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef usart_it = {
		.NVIC_IRQChannel = USART2_IRQn,
		.NVIC_IRQChannelPreemptionPriority = 1,
		.NVIC_IRQChannelSubPriority = 1,
		.NVIC_IRQChannelCmd = ENABLE
	};
	NVIC_Init(&usart_it);
	//USART启动
	USART_Cmd(USART2, ENABLE);
	
	//业务代码
	while(1){
		char res = GetUSARTValue();
		WirteIn16x8Char(4, 0, res);
		Delay_xms_wit(500);
		if (USART_GetFlagStatus(USART2, USART_FLAG_TC) == SET) {
			USART_SendData(USART2, res);
		}
	};
	
	
	return 0;
}
