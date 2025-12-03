一、USART模块学习
(1)定义：
    1.USART拥有四根线：
        (1)GND：接地
        (2)VCC：供电
        (3)TX：数据发送线
        (4)RX：数据接受线


(2)STM32中的USART外设：
1.基础应用：全双工异步通信
2.应用方式：
    (1)设置接收器与发射器
3.接收器原理：
    (1)涉及的寄存器：//只说明通信时直接相关(例如波特率设置寄存器则不会列出)
        1.USART_DR：数据寄存器，用户代码在发送或接受数据时会与其直接交互
        2.USART_TDR：数据输出寄存器，用于数据输出缓存
        3.USART_RDR：数据接受寄存器，用于数据接受缓存
        4.发送移位寄存器：数据发送，该寄存器直接与通信线路交互
        5.接受移位寄存器：数据接受，该寄存器直接与通信线路交互
    (2)数据流：
        发送机用户代码->USART_DR->USART_TDR->发送移位寄存器->通信线路->接受移位寄存器->USART_RDR->USART_DR->接收机用户代码

4.发送器通信模型：
    (1)抽象发送通信模型：
        1.发送队列send Queue
            (1)大小为N
            (2)发送队列中每一个元素是一个二元值，1表示对应的数据寄存器空闲，反之表示被占用。
            (3)当一个元素从0->1时，可以发送中断申请。
            (4)发送代码每次都会先将元素放置在队尾。然后进行快速移动，如果此时元素的下一位是1，则将该元素以及对应数据移动到下一位(即现在的这一位从0->1,下一位从1->0)，直到下一位为0停止快速移动。
            (5)队头元素从0->1代表数据发送至通信线路上，一次通信完成。
    (2)STM32中的通信模型：
        1.sendQueue大小为2。即[TEX, TC]
        2.对应两个寄存器：USART_DR(USART_TDR)，发送移位寄存器。
        3.先发低位
        4.每次激活TE会先发一个空闲帧
        5.每次发送结束后，如果SBK位被设置，则会发送一个断开帧。

5.接收器通信模型：
    (1)当数据从通信线路->移位寄存器->RDR寄存器后，RXNE被置位表明数据可被读取。RXNE被置位后，读取DR或者手动可复位RXNE
    (2)检测到帧错误、噪音、等，会将错误标志将置起
    (3)接收到断开帧，将被当作帧错误处理
    (4)接收到空闲帧，当作常规数据帧处理。但是如果配置了果IDLEIE位，接收到后会产生中断。

6.断开帧与空闲帧：
    (1)空闲帧：长度与数据帧相同，值为全1
    (2)断开帧：长度为数据帧长度+1，全0加一个逻辑"1"保证下一帧的起始位可被检测到。

7.波特率计算：
    (1)波特率 = fck / (16 * USARTDIV)，其中USARTDIV是无符号定点数





示例代码：
实现接收器和发送器，每次接收一帧数据，然后将该数据通过USART回传回上位机，以及写入OLED.大约每500ms回传一次数据.并将接收结果刷新到OLED中
int main()
{
	//oledc³õÊ¼»¯
	char title1[] = "rec:";
	TimerInitWithOutIT();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	uint16_t SCL = GPIO_Pin_11;
	uint16_t SDA = GPIO_Pin_12;
	InitOLED(GPIOA, SCL, SDA);
	TurnOnScreen();
	FlashScreen(0x00);
	WriteIn16x8String(0, 0, 4, title1);
	//ÉèÖÃÄ¿±êµØÖ·ÓëÔ´µØÖ·Êý×é£¬²¢ÔÚoledÉÏÏÔÊ¾
	
	//GPIO³õÊ¼»¯ for USART
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
	
	//USART³õÊ¼»¯
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
	//USARTÆô¶¯
	USART_Cmd(USART2, ENABLE);
	
	//ÒµÎñ´úÂë
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