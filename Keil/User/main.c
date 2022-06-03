#include "stm32f10x.h"	// Device header
#include "uart.h"
#include "timer.h"
#include "oled.h"



int main(void)
{	
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);									//中断分组，放在主程序前
	USART1_Init();
	OLED_Init();
	Timer_Init(72-1, 1000-1);
	
	while(1)
	{
		if(Set_Frame(35))
		{
			OLED_ShowFrame();
		}
	}
}
