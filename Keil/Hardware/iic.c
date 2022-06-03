#include "stm32f10x.h"                  // Device header
#include "iic.h"


void I2C_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	I2C_InitTypeDef I2C_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	//PB6——SCL PB7——SDA
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_OD;
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	I2C_DeInit(I2C1);
	I2C_InitStructure.I2C_Ack                 = I2C_Ack_Enable;
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_InitStructure.I2C_ClockSpeed          = 400000;
	I2C_InitStructure.I2C_DutyCycle           = I2C_DutyCycle_2;
	I2C_InitStructure.I2C_Mode                = I2C_Mode_I2C;
	I2C_InitStructure.I2C_OwnAddress1         = 0x30;
	
	I2C_Init(I2C1, &I2C_InitStructure);
	I2C_Cmd(I2C1, ENABLE);
}


//向OLED寄存器地址写一个byte的数据
void I2C_WriteByte(uint8_t addr,uint8_t data)
{
	while( I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY) );
	I2C_GenerateSTART(I2C1, ENABLE);
	
	while( !I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT) );
	I2C_Send7bitAddress(I2C1, OLED_ADDRESS, I2C_Direction_Transmitter);
	
	while( !I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) );
	I2C_SendData(I2C1, addr);
	
	while( !I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTING) );
	I2C_SendData(I2C1, data);
	
	while( !I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED) );
	I2C_GenerateSTOP(I2C1, ENABLE);
}

//写指令
void OLED_WriteCommand(unsigned char command)
{
	I2C_WriteByte(0x00,command);
}

//写数据
void OLED_WriteData(unsigned char data)
{
	I2C_WriteByte(0x40,data);
}

