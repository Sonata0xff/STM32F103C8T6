timer模块讲解：
1.利用更新中断的定时器：
    (1)该功能默认以STM32F103C8T6的TIM2定时器为资源进行定时
    (2)涉及的函数：
        1.void TimerInit(void); //该函数对定时器进行初始化操作
        2.void Delay_xus(uint16_t us); //该函数进行微秒级定时，仅支持大于3us的整数定时
        3.void Delay_xms(uint16_t ms); //该函数进行毫秒级定时，仅支持大于等于1ms的整数定时
        4.void TIM2_IRQHandler(void); //TIM2定时器的更新中断处理函数
    (3)该功能的调用方法：
        1.TimerInit(); //初始化定时器
        2.Delay_xus(n);//阻塞运行该函数的线程n微秒
        3.Delay_xms(n);//阻塞运行该函数的线程n毫秒


2.无需更新中断的定时器：
    (1)该功能默认以STM32F103C8T6的TIM2定时器为资源进行定时
    (2)涉及的函数：
        1.void TimerInitWithOutIT(void); //该函数对定时器进行初始化操作
        2.void Delay_xus_wit(uint16_t us); //该函数对定时器进行微秒级定时，仅支持大于等于1us的整数定时，并且有大约+0.1~+0.3us的定时误差
        3.void Delay_xms_wit(uint16_t ms); //该函数对定时器进行毫秒级定时，仅支持大于等于1ms的整数定时
    (3)该功能的调用方法：
        1.TimerInitWithOutIT(); //初始化定时器
        2.Delay_xus_wit(n); //阻塞当前线程n微秒
        3.Delay_xms_wit(n); //阻塞当前线程n毫秒

3.定时器原理分析：
(1)对于TimerInit函数而言，分为三个阶段：
    1.APB总线初始化
    2.定时器配置
    3.中断初始化
其中，
    (2)定时器初始化：
        1.设置SMCR寄存器的SMS位，来配置驱动时钟为内部时钟，频率为72Mhz
        2.设置CR1寄存器的CKD位，配置时钟分频因子来配置滤波器相关内容
        3.设置CR1寄存器的URS位，让其忽略除计数器溢出以外的其他方式引起的更新中断。具体而言，