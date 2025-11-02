#include "stm32f10x.h"                  // Device header
#include "timer.h"
#include "I2C.h"
#include "OLED.h"
#include "head.h"
int main()
{
	//oledc初始化
	char title1[] = "src:";
	char title2[] = "dst:";
	TimerInitWithOutIT();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	uint16_t SCL = GPIO_Pin_11;
	uint16_t SDA = GPIO_Pin_12;
	InitOLED(GPIOA, SCL, SDA);
	TurnOnScreen();
	FlashScreen(0x00);
	WriteIn16x8String(0, 0, 4, title1);
	WriteIn16x8String(0, 2, 4, title2);
	//设置目标地址与源地址数组，并在old上显示
	u8 src[5] = {0x00, 0x00, 0x00, 0x00, 0x00};
	u8 dst[5] = {0xff, 0xff, 0xff, 0xff, 0xff};
	//DMA初始化
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	DMA_InitTypeDef dma_config = {
		.DMA_PeripheralBaseAddr = (uint32_t)dst,
		.DMA_MemoryBaseAddr = (uint32_t)src,
		.DMA_DIR = DMA_DIR_PeripheralDST,
		.DMA_BufferSize = 5,
		.DMA_PeripheralInc = DMA_PeripheralInc_Enable,
		.DMA_MemoryInc = DMA_PeripheralInc_Enable,
		.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte,
		.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte,
		.DMA_Mode = DMA_Mode_Normal,
		.DMA_Priority = DMA_Priority_VeryHigh,
		.DMA_M2M = DMA_M2M_Enable
	};
	DMA_Init(DMA1_Channel1, &dma_config);
	//开始搬运
	char bufChar[2];
	while(1) {
		for (unsigned char i = 0; i < 5; i++) {
			if (src[i] == 0xff) src[i] = 0x00;
			else src[i] += 1;
		}
		Delay_xms_wit(2000);
		//DMA转移数据
		DMA_SetCurrDataCounter(DMA1_Channel1, 5);
		DMA_Cmd(DMA1_Channel1, ENABLE);
		while(DMA_GetCurrDataCounter(DMA1_Channel1));
		DMA_Cmd(DMA1_Channel1, DISABLE);
		//oled显示
		for (unsigned char i = 0; i < 5; i++) {
			Uint8toStr(src[i], bufChar);
			WriteIn16x8String(i * 3, 1, 2, bufChar);
		}
		Delay_xms_wit(2000);
		for (unsigned char i = 0; i < 5; i++) {
			Uint8toStr(dst[i], bufChar);
			WriteIn16x8String(i * 3, 3, 2, bufChar);
		}
	}
	return 0;
}
