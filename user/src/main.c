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
		.GPIO_Pin = GPIO_Pin_11,
		.GPIO_Speed = GPIO_Speed_50MHz,
		.GPIO_Mode = GPIO_Mode_AIN //模拟输入
	};
	GPIO_Init(GPIOA, &adc_port);
	//adc init
	
	//chars write in
	u16 adc_value = 0;
	char str[5];
	while (1) {
		//adc_value = Get_ADC_VALUE();
		words2Str(adc_value, str);
		WriteIn16x8String(8, 0, 5, str);
		Delay_xms_wit(2);
	}
	return 0;
}
