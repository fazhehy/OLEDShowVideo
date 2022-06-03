#include "stm32f10x.h"                  // Device header
#include <string.h>
#include "iic.h"
#include "oled.h"


uint8_t buffer[1024]={0};
uint8_t temp_buffer[1024]={0};


void OLED_ShowPicture(uint8_t *arr)
{
	uint16_t i=0;
	
	//设置水平地址模式，和起始页，起始列
	OLED_WriteCommand(0x20);
	OLED_WriteCommand(0x00);
	OLED_WriteCommand(0x21);
	OLED_WriteCommand(0x00);
	OLED_WriteCommand(0x7F);
	OLED_WriteCommand(0x22);
	OLED_WriteCommand(0x00);
	OLED_WriteCommand(0x07);
	
	while( I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY) );
	I2C_GenerateSTART(I2C1, ENABLE);
	
	while( !I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT) );
	I2C_Send7bitAddress(I2C1, OLED_ADDRESS, I2C_Direction_Transmitter);
	
	while( !I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) );
	I2C_SendData(I2C1, 0x40);
	
	for(i=0;i<1024;i++){
		while( !I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTING) );
		I2C_SendData(I2C1,arr[i]);
	}
	
	while( !I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED) );
	I2C_GenerateSTOP(I2C1, ENABLE);
}

void writeBuffer(uint8_t data)
{
	static uint16_t n=0;
	temp_buffer[n]=data;
	n++;
	if(n==1024){
		memcpy(buffer,temp_buffer,1024);
		memset(temp_buffer,0,1024);
		n=0;
	}
}

void OLED_ShowFrame(void)
{
	OLED_ShowPicture(buffer);
}

/**
  * @brief  OLED初始化
  * @param  无
  * @retval 无
  */
void OLED_Init(void)
{
	uint32_t i, j;
	
	for (i = 0; i < 1000; i++)			//上电延时
	{
		for (j = 0; j < 1000; j++);
	}
	
	I2C_Configuration();		//端口初始化
	
	OLED_WriteCommand(0xAE);	//关闭显示
	
	OLED_WriteCommand(0xD5);	//设置显示时钟分频比/振荡器频率
	OLED_WriteCommand(0x80);
	
	OLED_WriteCommand(0xA8);	//设置多路复用率
	OLED_WriteCommand(0x3F);
	
	OLED_WriteCommand(0xD3);	//设置显示偏移
	OLED_WriteCommand(0x00);
	
	OLED_WriteCommand(0x40);	//设置显示开始行
	
	OLED_WriteCommand(0xA1);	//设置左右方向，0xA1正常 0xA0左右反置
	
	OLED_WriteCommand(0xC8);	//设置上下方向，0xC8正常 0xC0上下反置

	OLED_WriteCommand(0xDA);	//设置COM引脚硬件配置
	OLED_WriteCommand(0x12);
	
	OLED_WriteCommand(0x81);	//设置对比度控制
	OLED_WriteCommand(0xCF);

	OLED_WriteCommand(0xD9);	//设置预充电周期
	OLED_WriteCommand(0xF1);

	OLED_WriteCommand(0xDB);	//设置VCOMH取消选择级别
	OLED_WriteCommand(0x30);

	OLED_WriteCommand(0xA4);	//设置整个显示打开/关闭

	OLED_WriteCommand(0xA6);	//设置正常/倒转显示

	OLED_WriteCommand(0x8D);	//设置充电泵
	OLED_WriteCommand(0x14);

	OLED_WriteCommand(0xAF);	//开启显示
	
	
	//以下是设置图形加速命令，若无会出现水平和垂直滚动
	OLED_WriteCommand(0x2E);
	OLED_WriteCommand(0x29);
	OLED_WriteCommand(0x00);
	OLED_WriteCommand(0x00);
	OLED_WriteCommand(0x03);
	OLED_WriteCommand(0x00);
	OLED_WriteCommand(0x00);
	
	
	OLED_WriteCommand(0x26);
	OLED_WriteCommand(0x00);
	OLED_WriteCommand(0x00);
	OLED_WriteCommand(0x03);
	OLED_WriteCommand(0x00);
	OLED_WriteCommand(0x00);
	OLED_WriteCommand(0xFF);
//	OLED_WriteCommand(0x2F);
	//相当于清屏
	OLED_ShowPicture(temp_buffer);
}
