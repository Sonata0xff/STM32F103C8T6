#include "OLED.h"
unsigned char ScreenOn = 0;
//��ʼ������
void InitOLED(GPIO_TypeDef* GPIOx, uint16_t SCL_, uint16_t SDA_)
{
	IIC_Init(GPIOx, SCL_, SDA_);
}
unsigned char TurnOnScreen()
{
	if (ScreenOn) return 0;
	
	StartFunc();//��ʼͨѶ
	
	if (MainSend1Byte(0x78) != 0x00) return 1;//�����豸��ַ
	
	if (MainSend1Byte(0x00) != 0x00) return 2;//���Ϳ����ֽ�
	
	if (MainSend1Byte(0xae) != 0x00) return 3;//�ر���Ļ
	
	if (MainSend1Byte(0x20) != 0x00) return 4;//����DDRѰַģʽ
	if (MainSend1Byte(0x02) != 0x00) return 5;//����Ϊҳģʽ
	
	if (MainSend1Byte(0x81) != 0x00) return 6;//������Ļ�Աȶ�
	if (MainSend1Byte(0xff) != 0x00) return 7;//������Ļ�Աȶ�Ϊ0xff
	
	if (MainSend1Byte(0xda) != 0x00) return 8;//���ý��������
	if (MainSend1Byte(0x12) != 0x00) return 9;//����Ϊ�������
	
	if (MainSend1Byte(0xb0) != 0x00) return 10;//������ʼҳ
	
	if (MainSend1Byte(0x00) != 0x00) return 11;//���ÿ�ʼ�еĵ���λ
	if (MainSend1Byte(0x10) != 0x00) return 12;//���ÿ�ʼ�еĸ���λ
	
	if (MainSend1Byte(0x8d) != 0x00) return 13;//����ǰ��׼����1
	if (MainSend1Byte(0x14) != 0x00) return 14;//����ǰ��׼����2
	
	if (MainSend1Byte(0xaf) != 0x00) return 13;//������Ļ
	EndFunc();//����ͨѶ
	Delay_xms_wit(100);//��ʱ100ms
	ScreenOn = 1;
	return 0;
}

void FlashScreen(unsigned char val)
{
	if (ScreenOn == 0) return;
	
	for (unsigned char i = 0xb0; i <= 0xb7; i++) {
		StartFunc();//��ʼͨѶ
		MainSend1Byte(0x78);//�����豸��ַ
		MainSend1Byte(0x00);//���Ϳ����ֽ�
		MainSend1Byte(i);//����ҳ��ַ
		MainSend1Byte(0x00);//������ʼcol
		MainSend1Byte(0x10);//������ʼcol
		EndFunc();//����ͨѶ
		StartFunc();//��ʼͨѶ
		MainSend1Byte(0x78);//�����豸��ַ
		MainSend1Byte(0x40);//���������ֽ�
		for (int j = 0; j < 128; j++) MainSend1Byte(val);//ˢ�³�ָ���ַ�
		EndFunc();//����ͨѶ
	}
}

void TurnOffScreen()
{
	if (ScreenOn == 0) return;
	
	StartFunc();//��ʼͨѶ
	MainSend1Byte(0x78);//�����豸��ַ
	MainSend1Byte(0x00);//���Ϳ����ֽ�
	MainSend1Byte(0xae);//�ر���Ļ
	EndFunc();//����ͨѶ
	ScreenOn = 0;
}
void Write1Bit(unsigned char v128, unsigned char v64, unsigned char val)
{
	
}
void write8x8Char(unsigned char v128, unsigned char v64, char* val)
{
	
}
void Draw1Pic(unsigned char v128, unsigned char v64, char** pic, unsigned char hight, unsigned char width)
{
	
}
