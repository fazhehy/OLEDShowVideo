#include "stm32f10x.h"                  // Device header
#include "oled.h"

uint16_t ms=0;

/*
时间计算公式
Tout=(ARR+1)*(PSC+1)/72000000 (s)
*/

/**
  * @brief  定时器更新中断初始化
  * @param  ARR 重装载值
  * @param  PSC 预分频值
  * @retval 无
 **/
void Timer_Init(uint16_t PSC,uint16_t ARR)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);//使能APB1时钟
	
	TIM_InternalClockConfig(TIM2);//配置为内部时钟，可不写
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;//时钟分频，设置定时器时钟 CK_INT 频率与数字滤波器采样时钟频率分频比
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;//向上计数模式
	TIM_TimeBaseInitStructure.TIM_Period=ARR;//重装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler=PSC;//预分频
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter=0x00;//重复计数器，属于高级控制寄存器专用寄存器位，利用它可以非常容易控制输出 PWM 的个数。这里不用设置
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
	
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);//使能定时器中断，配置为更新中断
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);//若无此句，将不能从0开始计数
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM2中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM2,ENABLE);//使能定时器
}

uint8_t Set_Frame(uint8_t frame)
{
	uint8_t temp=1000/frame;
	
	if(temp==ms)
	{
		ms=0;
		return 1;
	}
	
	return 0;
}



void TIM2_IRQHandler()
{

	if(TIM_GetITStatus(TIM2,TIM_IT_Update))//判断中断标志位
	{
		ms++;
//		OLED_ShowFrame();
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);//清除中断标志位
	}
}
