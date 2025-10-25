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


模板代码稍后将进入
