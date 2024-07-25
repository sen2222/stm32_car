#include "stm32f10x.h" 
#include <stdio.h>
#include <stdarg.h>

char USART3_RxData;
uint8_t USART3_Flag;

/**
 * ��  ��:USART3��ʼ��
 * ��  ��:��
 * ����ֵ:��
 */
void USART3_Init(void)
{
    // ʹ�� GPIOB �� USART3 ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
    
    // ���� GPIOB ����
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10; 										// PB10 USART3_TX
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP; 									// �����������
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStruct);
    
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11; 										// PB11 USART3_RX
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU; 										// ��������
    GPIO_Init(GPIOB, &GPIO_InitStruct);
    
    // ���� USART3
    USART_InitTypeDef USART_InitStruct;
    USART_InitStruct.USART_BaudRate = 115200; 										// ���ò�����Ϊ 115200
    USART_InitStruct.USART_WordLength = USART_WordLength_8b; 						// 8 ����λ
    USART_InitStruct.USART_StopBits = USART_StopBits_1; 							// 1 ֹͣλ
    USART_InitStruct.USART_Parity = USART_Parity_No; 								// ��У��λ
    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None; 	// ��Ӳ��������
    USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; 					// ʹ�ܽ��պͷ���
    USART_Init(USART3, &USART_InitStruct);
	
	
	//�����������ݵ��ж�
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
	
	//�����ж�
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);										//�жϷ���
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	
	
	NVIC_Init(&NVIC_InitStruct);
    
    // ʹ�� USART3
    USART_Cmd(USART3, ENABLE);
}

/*****************************************����*****************************************************/


/**
 * ��  ��:USART3����һ�ֽ�����
 * ��  ��:��
 * ����ֵ:��
 */
void USART3_SendByte(uint8_t c)
{
    USART_SendData(USART3, c);
	while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);			//�ȴ����ݻ���������
}

/**
  * ��    �������ڷ���һ�����������
  * ��    ����Array Ҫ���͵�����
  * ��    ����Length ����ĳ���
  * �� �� ֵ����
  */
void USART3_SendArray(uint8_t *Array, uint16_t length)
{
	uint8_t i = 0;
	for(; i < length; i++) USART3_SendByte(Array[i]);
}


/**
 * ��  ��:USART3����һ���ַ���
 * ��  ��:��
 * ����ֵ:��
 */
void USART3_SendString(char *s)
{
    while (*s)
    {
        USART3_SendByte(*s++);
    }
}
/**
  * ��    �����η��������ڲ�ʹ�ã�
  * �� �� ֵ������ֵ����X��Y�η�
  */
static uint32_t USART3_Pow(uint32_t X, uint32_t Y)
{
	uint32_t Result = 1;	//���ý����ֵΪ1
	while (Y --)			//ִ��Y��
	{
		Result *= X;		//��X�۳˵����
	}
	return Result;
}

/**
  * ��    �������ڷ�������
  * ��    ����Number Ҫ���͵����֣���Χ��0~4294967295
  * ��    ����Length Ҫ�������ֵĳ��ȣ���Χ��0~10
  * �� �� ֵ����
  */
void USART3_SendNumber(uint32_t Number, uint8_t Length)
{
	uint8_t i;
	for (i = 0; i < Length; i ++)												//�������ֳ��ȱ������ֵ�ÿһλ
	{
		USART3_SendByte(Number / USART3_Pow(10, Length - i - 1) % 10 + '0');	//���ε���USART3_SendByte����ÿλ����
	}
}

/**
  * ��    ����ʹ��printf��Ҫ�ض���ĵײ㺯��
  * ��    ��������ԭʼ��ʽ���ɣ�����䶯
  * �� �� ֵ������ԭʼ��ʽ���ɣ�����䶯
  */
int fputc(int ch, FILE *f)
{
	USART3_SendByte(ch);			//��printf�ĵײ��ض����Լ��ķ����ֽں���
	return ch;
}

/*****************************************����*****************************************************/

/**
  * ��    �������ؽ��ձ�־λ״̬����ձ�־λ
  * ��    ������
  * �� �� ֵ��0������û���յ����ݣ�1�����ڽ��յ����ݲ��Զ��ѱ�־λ��0
  */
uint8_t USART3_GetRxFlag(void)
{
	if(USART3_Flag == 1)
	{
		USART3_Flag = 0;
		return 1;
	}
	return 0;
}

// ��ȡ���ڽ��յ�������
char USART3_GetRxData(void)
{
    return USART3_RxData;                                   // ���ش��ڽ��յ�������
}


// USART3 �жϴ�����
void USART3_IRQHandler(void)
{
    if (USART_GetITStatus(USART3, USART_IT_RXNE) == SET)    	// ��� USART3 �����жϱ�־λΪ SET
    {
        USART3_RxData = USART_ReceiveData(USART3);         		// ��ȡ���յ�������
        USART3_Flag = 1;                                  		// ��λ���ڽ��ձ�־λ
        USART_ClearITPendingBit(USART3, USART_IT_RXNE);     	// ��� USART3 �����жϱ�־λ
    }
}
