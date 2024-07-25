#include "stm32f10x.h"                  // Device header
#include "USART3.h"

/**
 * ��  ��: HC05��ʼ��
 * ��  ��: ��
 * ����ֵ: ��
 */
void HC05_Init(void)
{
	//��ʼ������3
	USART3_Init();
} 


/*************************************************��������**********************************************/

/**
 * ��  ��: HC05����һ�ֽ�����
 * ��  ��: Byte Ҫ���͵��ֽ�����
 * ����ֵ: ��
 */
void HC05_SendByte(uint8_t Byte)
{
    USART3_SendByte(Byte);
}
/**
  * ��    ����HC05����һ�����������
  * ��    ����Array Ҫ���͵�����
  * ��    ����Length ����ĳ���
  * �� �� ֵ����
  */
void HC05_SendArray(uint8_t *Array, uint16_t length)
{
	USART3_SendArray(Array, length);
}
/**
 * ��  ��:HC05����һ���ַ���
 * ��  ��:��
 * ����ֵ:��
 */
void HC05_SendString(char *s)
{
    USART3_SendString(s);
}
/**
  * ��    ����HC05��������
  * ��    ����Number Ҫ���͵����֣���Χ��0~4294967295
  * ��    ����Length Ҫ�������ֵĳ��ȣ���Χ��0~10
  * �� �� ֵ����
  */
void UHC05_SendNumber(uint32_t Number, uint8_t Length)
{
	USART3_SendNumber(Number, Length);
}

/*************************************************��������**********************************************/

/**
  * ��    �������ؽ��յ����ݣ�û���յ��ͷŻ�'\0'
  * ��    ������
  * �� �� ֵ��'\0'������û���յ�����
  */
uint8_t HC05_GetRxData(void)
{
	if(USART3_GetRxFlag() == 1) return USART3_GetRxData(); 
	return '\0';
}
