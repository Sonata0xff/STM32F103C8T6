#include "OLED.h"
unsigned char ScreenOn = 0;
//初始化函数
void InitOLED(GPIO_TypeDef* GPIOx, uint16_t SCL_, uint16_t SDA_)
{
	IIC_Init(GPIOx, SCL_, SDA_);
}
unsigned char TurnOnScreen()
{
	if (ScreenOn) return 0;
	
	StartFunc();//开始通讯
	
	if (MainSend1Byte(0x78) != 0x00) return 1;//发送设备地址
	
	if (MainSend1Byte(0x00) != 0x00) return 2;//发送控制字节
	
	if (MainSend1Byte(0xae) != 0x00) return 3;//关闭屏幕
	
	if (MainSend1Byte(0x20) != 0x00) return 4;//设置DDR寻址模式
	if (MainSend1Byte(0x02) != 0x00) return 5;//设置为页模式
	
	if (MainSend1Byte(0x81) != 0x00) return 6;//设置屏幕对比度
	if (MainSend1Byte(0xff) != 0x00) return 7;//设置屏幕对比度为0xff
	
	if (MainSend1Byte(0xda) != 0x00) return 8;//设置交替行输出
	if (MainSend1Byte(0x12) != 0x00) return 9;//设置为序列输出
	
	if (MainSend1Byte(0xb0) != 0x00) return 10;//设置起始页
	
	if (MainSend1Byte(0x00) != 0x00) return 11;//设置开始列的低四位
	if (MainSend1Byte(0x10) != 0x00) return 12;//设置开始列的高四位
	
	if (MainSend1Byte(0x8d) != 0x00) return 13;//启动前标准流程1
	if (MainSend1Byte(0x14) != 0x00) return 14;//启动前标准流程2
	
	if (MainSend1Byte(0xaf) != 0x00) return 13;//启动屏幕
	EndFunc();//结束通讯
	Delay_xms_wit(100);//延时100ms
	ScreenOn = 1;
	return 0;
}

void FlashScreen(unsigned char val)
{
	if (ScreenOn == 0) return;
	
	for (unsigned char i = 0xb0; i <= 0xb7; i++) {
		StartFunc();//开始通讯
		MainSend1Byte(0x78);//发送设备地址
		MainSend1Byte(0x00);//发送控制字节
		MainSend1Byte(i);//设置页地址
		MainSend1Byte(0x00);//设置起始col
		MainSend1Byte(0x10);//设置起始col
		EndFunc();//结束通讯
		StartFunc();//开始通讯
		MainSend1Byte(0x78);//发送设备地址
		MainSend1Byte(0x40);//发送数据字节
		for (int j = 0; j < 128; j++) MainSend1Byte(val);//刷新称指定字符
		EndFunc();//结束通讯
	}
}

void TurnOffScreen()
{
	if (ScreenOn == 0) return;
	
	StartFunc();//开始通讯
	MainSend1Byte(0x78);//发送设备地址
	MainSend1Byte(0x00);//发送控制字节
	MainSend1Byte(0xae);//关闭屏幕
	EndFunc();//结束通讯
	ScreenOn = 0;
}
void Write1Byte(unsigned char v128, unsigned char v8, unsigned char val)
{
	if (ScreenOn == 0) return;
	if (v128 >= 128 || v8 >= 8) return;
	v8 += 0xb0;
	unsigned char upHalf = ((v128 >> 4) + 0x10);
	unsigned char downHalf = v128 & 0x0f;
	StartFunc();//开始通讯
	MainSend1Byte(0x78);//发送设备地址
	MainSend1Byte(0x00);//发送控制字节
	MainSend1Byte(v8);//设置页地址
	MainSend1Byte(downHalf);//设置列地址低位
	MainSend1Byte(upHalf);//设置列地址高位
	EndFunc();//结束通讯
	StartFunc();//开始通讯
	MainSend1Byte(0x78);//发送设备地址
	MainSend1Byte(0x40);//发送数据字节
	MainSend1Byte(val);//发送数据
	EndFunc();//结束通讯
}
void write8x8Char(unsigned char v128, unsigned char v8, unsigned char val[])
{
	if (ScreenOn == 0) return;
	if (v128 >= 128 || v8 >= 8) return;
	v8 += 0xb0;
	unsigned char upHalf = ((v128 >> 4) + 0x10);
	unsigned char downHalf = v128 & 0x0f;
	StartFunc();//开始通讯
	MainSend1Byte(0x78);//发送设备地址
	MainSend1Byte(0x00);//发送控制字节
	MainSend1Byte(v8);//设置页地址
	MainSend1Byte(downHalf);//设置列地址低位
	MainSend1Byte(upHalf);//设置列地址高位
	EndFunc();//结束通讯
	StartFunc();//开始通讯
	MainSend1Byte(0x78);//发送设备地址
	MainSend1Byte(0x40);//发送数据字节
	for (unsigned char i = 0; i < 8; i++) MainSend1Byte(val[i]);//发送数据
	EndFunc();//结束通讯
}
/*
pic format:[row][col]
x x x x x
y y y y y
z z z z z
*/
void Draw1Pic(unsigned char v128, unsigned char v8, unsigned char *pic, unsigned char hight, unsigned char width)
{
	if (ScreenOn == 0) return;
	if (v128 + width - 1 >= 128 || v8 + hight - 1 >= 8) return;
	unsigned char upHalf = ((v128 >> 4) + 0x10);
	unsigned char downHalf = v128 & 0x0f;
	for (unsigned char i = 0; i < hight; i++) {
		StartFunc();
		MainSend1Byte(0x78);
		MainSend1Byte(0x00);
		MainSend1Byte(v8 + i - 1 + 0xb0);//设置页地址
		MainSend1Byte(downHalf);//设置列地址低位
		MainSend1Byte(upHalf);//设置列地址高位
		EndFunc();
		StartFunc();
		MainSend1Byte(0x78);
		MainSend1Byte(0x40);//发送数据字节
		for (unsigned char j = 0; j < width; j++) MainSend1Byte(*(pic + i*hight + j));//写入数据
		EndFunc();
	}
}
