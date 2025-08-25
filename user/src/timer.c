#include "timer.h"
unsigned char TimeTag_ = 0x00;

void TIM2_IRQHandler(void)
{
	TIM2->SR &= 0xfffe; //close the it
	TimeTag_ = 0x1; //set count flag
}

void TimerInit(void)
{
	//struct def
	NVIC_InitTypeDef nvic_init = {
		.NVIC_IRQChannel = TIM2_IRQn,
		.NVIC_IRQChannelPreemptionPriority = 2,
		.NVIC_IRQChannelSubPriority = 1,
		.NVIC_IRQChannelCmd = ENABLE
	};
	TimeTag_ = 0x00;
	
	//APB init
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	//Timer init
	TIM2->SMCR &= 0xfff8; // set internal clock
	TIM2->CR1 &= 0xfcff; //set clock divison
	TIM2->CR1 |= 0x0004; //set urs to ignore other it
	TIM2->CR1 &= 0xffef; //set dir to up
	TIM2->DIER |= 0x0001; //set UIE to open update it
	TIM2->PSC = 72-1;// set Prescaler to us
	TIM2->CR1 |= 0x0080;// set ARPE to enable preload
	TIM2->CR1 &= 0xfffd;// set udis to allow other update event
	TIM2->EGR |= 0x0001;// pack config into register
	
	//it init
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_Init(&nvic_init);
}
void Delay_xus(uint16_t us) // delay have to be bigger than 3us,then is accurate
{
	TimeTag_ = 0x00; //reset count flag
	TIM2->PSC = 72-1;// reset prescaler to us
	TIM2->ARR = us-3;// set delay time
	TIM2->EGR |= 0x0001;// pack config into register
	TIM2->CR1 |= 0x0001; // start the counter
	while(TimeTag_ == 0x00);
	TIM2->CR1 &= 0xfffe;// stop the counter
	
}

void Delay_xms(uint16_t ms)
{
	TimeTag_ = 0x00; //reset count flag
	TIM2->PSC = 7200-1;// reset prescaler to us
	TIM2->ARR = ms * 10 - 1;// set delay time
	TIM2->EGR |= 0x0001;// pack config into register
	TIM2->CR1 |= 0x0001; // start the counter
	while(TimeTag_ == 0x00);
	TIM2->CR1 &= 0xfffe;// stop the counter
}
