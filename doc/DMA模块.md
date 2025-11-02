

source:
xx xx xx xx xx
dir:
xx xx xx xx xx


1.DMA模块目的：
让数据通过DMA，绕过CPU直接从一个存储器地址向另一个存储器地址上复制数据。摆脱CPU的控制，将数据搬运操作完全交由硬件电路负责，从而加速数据搬运速度。
2.技术要点：
    (1)STM32的存储器分为如下几大类：
        1.ROM：flash，不可直接写，需通过flash接口控制器才能直接写入，但可以直接读取
        2.RAM：SRAM，用于临时存放代码与数据的地方，类比pc中的内存
        3.外设：全称外设寄存器，属于存储器中一种。
    (2)DMA搬运方向分为两大类：
        1.外设-存储器(这里存储器特指：RAM+ROM)
        2.存储器-存储器(M2M)
    (3)当DMA的搬运方向为存储器-存储器时，外设地址只能作为目的地址，内存地址仅能作为起始地址

2.模板代码：
模拟场景：分别在SRAM中声明两组数据地址：src与dst.在代码中不写任何与内存复制相关的代码(例如:strcpy、for+等号赋值、等)，仅通过调用DMA模块完成将src中数据向dst数组中转移。
        所有转移后的结果通过oled打印
#include "stm32f10x.h"                  // Device header
#include "timer.h"
#include "I2C.h"
#include "OLED.h"
#include "head.h"
int main()
{
	//oledc³õÊ¼»¯
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
	//ÉèÖÃÄ¿±êµØÖ·ÓëÔ´µØÖ·Êý×é£¬²¢ÔÚoldÉÏÏÔÊ¾
	u8 src[5] = {0x00, 0x00, 0x00, 0x00, 0x00};
	u8 dst[5] = {0xff, 0xff, 0xff, 0xff, 0xff};
	//DMA³õÊ¼»¯
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
	//¿ªÊ¼°áÔË
	char bufChar[2];
	while(1) {
		for (unsigned char i = 0; i < 5; i++) {
			if (src[i] == 0xff) src[i] = 0x00;
			else src[i] += 1;
		}
		Delay_xms_wit(2000);
		//DMA×ªÒÆÊý¾Ý
		DMA_SetCurrDataCounter(DMA1_Channel1, 5);
		DMA_Cmd(DMA1_Channel1, ENABLE);
		while(DMA_GetCurrDataCounter(DMA1_Channel1));
		DMA_Cmd(DMA1_Channel1, DISABLE);
		//oledÏÔÊ¾
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
