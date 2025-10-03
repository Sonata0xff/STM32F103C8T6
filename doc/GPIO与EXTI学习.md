1.EXTI外部中断简介与使用：
(1)EXTI外部中断：
    使用GPIO端口的电平跳变作为中断信号进行中断申请
(2)EXTI中断配置：
    1.RCC_APB2PeriphClockCmd开启GPIOx的外设时钟
    2.GPIO_Init初始化中断所监听的GPIO端口，模式根据数据手册中要求GPIO为EXTI时的配置而设置
    3.RCC_APB2PeriphClockCmd开启AFIO外设时钟
    4.GPIO_EXTILineConfig配置AFIO所监听的中断GPIO端口
    5.EXTI_Init初始化外部中断，中断具体配置见入参EXTI_InitTypeDef配置
    6.NVIC_PriorityGroupConfig配置中断优先级策略，一共四种
    7.NVIC_Init初始化中断，具体配置见入参NVIC_InitTypeDef配置
(3)定时器调用流程：
1.GPIOx -> AFIO -> EXTI+中断事件控制 -> 中断 -> NVIC
                 /              \
   PVD,RTC,USB,ETH                 事件 -> 外部设备

以下为一个样例代码，其中GPIOA_Pin_0作为输出端，连接LED。GPIOB_Pin_5作为中断发起端口，连接一个按钮。
当按钮被按下时，PB5引脚被拉低，下降沿触发中断，中断函数通过设置PA0引脚来改变LED的亮灭：
主进程代码：
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef outport = {
		.GPIO_Pin = GPIO_Pin_0,
		.GPIO_Speed = GPIO_Speed_50MHz,
		.GPIO_Mode = GPIO_Mode_Out_PP
	};
	GPIO_Init(GPIOA, &outport);
	GPIO_SetBits(GPIOA, GPIO_Pin_0);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitTypeDef inport = {
		.GPIO_Pin = GPIO_Pin_5,
		.GPIO_Speed = GPIO_Speed_50MHz,
		.GPIO_Mode = GPIO_Mode_IPU
	};
	GPIO_Init(GPIOB, &inport);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource5);
	EXTI_InitTypeDef exti_config = {
		.EXTI_Line = EXTI_Line5,
		.EXTI_Mode = EXTI_Mode_Interrupt,
		.EXTI_Trigger = EXTI_Trigger_Falling,
		.EXTI_LineCmd = ENABLE
	};
	EXTI_Init(&exti_config);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef nvic_config = {
		.NVIC_IRQChannel = EXTI9_5_IRQn,
		.NVIC_IRQChannelPreemptionPriority = 1,
		.NVIC_IRQChannelSubPriority = 1,
		.NVIC_IRQChannelCmd = ENABLE
	};
	NVIC_Init(&nvic_config);
    while(1);
中断函数编写：
    void EXTI9_5_IRQHandler()
    {
        if (EXTI_GetITStatus(EXTI_Line5) == SET) {
            EXTI_ClearITPendingBit(EXTI_Line5);
            if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)) GPIO_ResetBits(GPIOA, GPIO_Pin_0);
            else GPIO_SetBits(GPIOA, GPIO_Pin_0);
        } else return; 
    }
