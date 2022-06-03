#ifndef __IIC_H
#define __IIC_H

#define OLED_ADDRESS 0x78

void I2C_Configuration(void);
void I2C_WriteByte(uint8_t addr,uint8_t data);
void OLED_WriteCommand(unsigned char command);
void OLED_WriteData(unsigned char data);

#endif
