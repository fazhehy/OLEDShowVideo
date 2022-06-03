#ifndef __OLED_H
#define __OLED_H

void OLED_Init(void);
void writeBuffer(uint8_t data);
void OLED_ShowPicture(uint8_t *arr);
void OLED_ShowFrame(void);

#endif
