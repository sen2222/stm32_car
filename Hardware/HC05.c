#include "stm32f10x.h"                  // Device header
#include "USART3.h"

/**
 * 函  数: HC05初始化
 * 参  数: 无
 * 返回值: 无
 */
void HC05_Init(void)
{
	//初始化串口3
	USART3_Init();
} 


/*************************************************蓝牙发送**********************************************/

/**
 * 函  数: HC05发送一字节数据
 * 参  数: Byte 要发送的字节数据
 * 返回值: 无
 */
void HC05_SendByte(uint8_t Byte)
{
    USART3_SendByte(Byte);
}
/**
  * 函    数：HC05发送一个数组的数据
  * 参    数：Array 要发送的数组
  * 参    数：Length 数组的长度
  * 返 回 值：无
  */
void HC05_SendArray(uint8_t *Array, uint16_t length)
{
	USART3_SendArray(Array, length);
}
/**
 * 函  数:HC05发送一个字符串
 * 参  数:无
 * 返回值:无
 */
void HC05_SendString(char *s)
{
    USART3_SendString(s);
}
/**
  * 函    数：HC05发送数字
  * 参    数：Number 要发送的数字，范围：0~4294967295
  * 参    数：Length 要发送数字的长度，范围：0~10
  * 返 回 值：无
  */
void UHC05_SendNumber(uint32_t Number, uint8_t Length)
{
	USART3_SendNumber(Number, Length);
}

/*************************************************蓝牙接收**********************************************/

/**
  * 函    数：返回接收的数据，没接收到就放回'\0'
  * 参    数：无
  * 返 回 值：'\0'：串口没接收到数据
  */
uint8_t HC05_GetRxData(void)
{
	if(USART3_GetRxFlag() == 1) return USART3_GetRxData(); 
	return '\0';
}
