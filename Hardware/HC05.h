#ifndef __HC05_H
#define __HC05_H

#include <stdio.h>
#include <stdarg.h>

void HC05_Init(void);
void HC05_SendByte(uint8_t Byte);
void HC05_SendArray(uint8_t *Array, uint16_t length);
void HC05_SendString(char *s);
void UHC05_SendNumber(uint32_t Number, uint8_t Length);
uint8_t HC05_GetRxData(void);


#endif
