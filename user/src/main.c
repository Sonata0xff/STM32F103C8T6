#include "stm32f10x.h"                  // Device header
#include "timer.h"
#include "I2C.h"
#include "OLED.h"
#include "head.h"
int main()
{
	//oledc初始化
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
		.GPIO_Mode = GPIO_Mode_AIN //模拟输入
	};
	GPIO_Init(GPIOA, &adc_port);
	//adc init
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);//打开外设时钟
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);//配置ADC预分频器,12Mhz
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
	ADC_Cmd(ADC1, ENABLE);//ADC启动
	ADC_StartCalibration(ADC1);//启动校准程序
	while(ADC_GetCalibrationStatus(ADC1) == SET);//等待校准完成
	//chars write in
	u16 adc_value = 0;
	char str[5];
	while (1) {
		//adc_value = Get_ADC_VALUE();
		ADC_SoftwareStartConvCmd(ADC1, ENABLE);//软件触发转换
		while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);//等待转换完成
		adc_value = ADC_GetConversionValue(ADC1);//获取转化值
		words2Str(adc_value, str);
		WriteIn16x8String(8, 0, 5, str);
		Delay_xms_wit(500);
	}
	return 0;
}
