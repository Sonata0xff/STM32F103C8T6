一、adc模块目的：
    将指定端口的0~3.3v电压转换为一组16bit数据，数据表示范围：0~4095




1.ADC_Init 
根据ADC_InitStruct 中指定的参数初始化外设ADCx的寄存器

2.ADC_Cmd
使能或者失能指定的ADC 

3.ADC_StartCalibration
开始指定ADC的校准程序 

4.ADC_SoftwareStartConvCmd
使能或者失能指定的ADC的软件转换启动功能 

5.ADC_RegularChannelConfig
设置指定 ADC 的规则组通道，设置它们的转化顺序和采样时间

6.ADC_GetConversionValue
返回最近一次ADCx规则组的转换结果

7.ADC_SoftwareStartinjectedConvCmd
使能或者失能ADCx软件启动注入组转换功能 

8.ADC_InjectedChannleConfig
设置指定 ADC 的注入组通道，设置它们的转化顺序和采样时间

9.ADC_InjectedSequencerLengthConfig
设置注入组通道的转换序列长度

10.ADC_SetinjectedOffset
设置注入组通道的转换偏移值 

11.ADC_GetInjectedConversionValue
返回ADC指定注入通道的转换结果 

12.ADC_GetCalibrationStatus
获取指定ADC的校准状态 


1.初始化：
(1)ADC_Init 
根据ADC_InitStruct 中指定的参数初始化外设ADCx的寄存器

(2)ADC_StartCalibration
开始指定ADC的校准程序

(3)ADC_RegularChannelConfig
设置指定 ADC 的规则组通道，设置它们的转化顺序和采样时间

(4)ADC_InjectedChannleConfig
设置指定 ADC 的注入组通道，设置它们的转化顺序和采样时间

(5)ADC_InjectedSequencerLengthConfig
设置注入组通道的转换序列长度

(6)ADC_SetinjectedOffset
设置注入组通道的转换偏移值

(7)ADC_SetinjectedOffset
设置注入组通道的转换偏移值

(8)ADC_GetCalibrationStatus
获取指定ADC的校准状态



2.使用：
(1)ADC_GetConversionValue
返回最近一次ADCx规则组的转换结果

(2)ADC_GetInjectedConversionValue
返回ADC指定注入通道的转换结果

3.启动：
(1)ADC_Cmd
使能或者失能指定的ADC

(2)ADC_SoftwareStartConvCmd
使能或者失能指定的ADC的软件转换启动功能

(3)ADC_SoftwareStartinjectedConvCmd
使能或者失能ADCx软件启动注入组转换功能


二、adc模块的模板代码：
场景：外部将从PA0输入一个0~3.3V的电压信号，并将对应的结果输出至oled屏幕。
#include "stm32f10x.h"                  // Device header
#include "timer.h"
#include "I2C.h"
#include "OLED.h"
#include "head.h"
int main()
{
	//oledc³õÊ¼»¯
	char title[] = "ADC_VAL:";
	TimerInitWithOutIT();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	uint16_t SCL = GPIO_Pin_11;
	uint16_t SDA = GPIO_Pin_12;
	InitOLED(GPIOA, SCL, SDA);
	TurnOnScreen();
	FlashScreen(0x00);
	WriteIn16x8String(0, 0, 8, title);
	//adc gpio init
	GPIO_InitTypeDef adc_port = {
		.GPIO_Pin = GPIO_Pin_0,
		.GPIO_Speed = GPIO_Speed_50MHz,
		.GPIO_Mode = GPIO_Mode_AIN //Ä£ÄâÊäÈë
	};
	GPIO_Init(GPIOA, &adc_port);
	//adc init
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);//´ò¿ªÍâÉèÊ±ÖÓ
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);//ÅäÖÃADCÔ¤·ÖÆµÆ÷,12Mhz
	ADC_InitTypeDef adc_config = {
		.ADC_Mode = ADC_Mode_Independent,
		.ADC_ScanConvMode = DISABLE,
		.ADC_ContinuousConvMode = DISABLE,
		.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None,
		.ADC_DataAlign = ADC_DataAlign_Right,
		.ADC_NbrOfChannel = 1
	};
	ADC_Init(ADC1, &adc_config);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
	ADC_Cmd(ADC1, ENABLE);//ADCÆô¶¯
	ADC_StartCalibration(ADC1);//Æô¶¯Ð£×¼³ÌÐò
	while(ADC_GetCalibrationStatus(ADC1) == SET);//µÈ´ýÐ£×¼Íê³É
	//chars write in
	u16 adc_value = 0;
	char str[5];
	while (1) {
		//adc_value = Get_ADC_VALUE();
		ADC_SoftwareStartConvCmd(ADC1, ENABLE);//Èí¼þ´¥·¢×ª»»
		while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);//µÈ´ý×ª»»Íê³É
		adc_value = ADC_GetConversionValue(ADC1);//»ñÈ¡×ª»¯Öµ
		words2Str(adc_value, str);
		WriteIn16x8String(8, 0, 5, str);
		Delay_xms_wit(500);
	}
	return 0;
}
