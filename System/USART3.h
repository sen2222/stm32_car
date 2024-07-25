#ifndef __USART3_H
#define __USART3_H

void USART3_Init(void);

//∑¢ÀÕ
void USART3_SendByte(uint8_t c);
void USART3_SendArray(uint8_t *Array, uint16_t length);
void USART3_SendString(char *s);
void USART3_SendNumber(uint32_t Number, uint8_t Length);

//Ω” ’
uint8_t USART3_GetRxFlag(void);
char USART3_GetRxData(void);


#endif
