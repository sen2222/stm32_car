#include "stm32f10x.h" 
#include <stdio.h>
#include <stdarg.h>

char USART3_RxData;
uint8_t USART3_Flag;

/**
 * 函  数:USART3初始化
 * 参  数:无
 * 返回值:无
 */
void USART3_Init(void)
{
    // 使能 GPIOB 和 USART3 时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
    
    // 配置 GPIOB 引脚
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10; 										// PB10 USART3_TX
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP; 									// 复用推挽输出
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStruct);
    
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11; 										// PB11 USART3_RX
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU; 										// 上拉输入
    GPIO_Init(GPIOB, &GPIO_InitStruct);
    
    // 配置 USART3
    USART_InitTypeDef USART_InitStruct;
    USART_InitStruct.USART_BaudRate = 115200; 										// 设置波特率为 115200
    USART_InitStruct.USART_WordLength = USART_WordLength_8b; 						// 8 数据位
    USART_InitStruct.USART_StopBits = USART_StopBits_1; 							// 1 停止位
    USART_InitStruct.USART_Parity = USART_Parity_No; 								// 无校验位
    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None; 	// 无硬件流控制
    USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; 					// 使能接收和发送
    USART_Init(USART3, &USART_InitStruct);
	
	
	//开启接收数据的中断
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
	
	//配置中断
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);										//中断分组
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	
	
	NVIC_Init(&NVIC_InitStruct);
    
    // 使能 USART3
    USART_Cmd(USART3, ENABLE);
}

/*****************************************发送*****************************************************/


/**
 * 函  数:USART3发送一字节数据
 * 参  数:无
 * 返回值:无
 */
void USART3_SendByte(uint8_t c)
{
    USART_SendData(USART3, c);
	while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);			//等待数据缓冲区发完
}

/**
  * 函    数：串口发送一个数组的数据
  * 参    数：Array 要发送的数组
  * 参    数：Length 数组的长度
  * 返 回 值：无
  */
void USART3_SendArray(uint8_t *Array, uint16_t length)
{
	uint8_t i = 0;
	for(; i < length; i++) USART3_SendByte(Array[i]);
}


/**
 * 函  数:USART3发送一个字符串
 * 参  数:无
 * 返回值:无
 */
void USART3_SendString(char *s)
{
    while (*s)
    {
        USART3_SendByte(*s++);
    }
}
/**
  * 函    数：次方函数（内部使用）
  * 返 回 值：返回值等于X的Y次方
  */
static uint32_t USART3_Pow(uint32_t X, uint32_t Y)
{
	uint32_t Result = 1;	//设置结果初值为1
	while (Y --)			//执行Y次
	{
		Result *= X;		//将X累乘到结果
	}
	return Result;
}

/**
  * 函    数：串口发送数字
  * 参    数：Number 要发送的数字，范围：0~4294967295
  * 参    数：Length 要发送数字的长度，范围：0~10
  * 返 回 值：无
  */
void USART3_SendNumber(uint32_t Number, uint8_t Length)
{
	uint8_t i;
	for (i = 0; i < Length; i ++)												//根据数字长度遍历数字的每一位
	{
		USART3_SendByte(Number / USART3_Pow(10, Length - i - 1) % 10 + '0');	//依次调用USART3_SendByte发送每位数字
	}
}

/**
  * 函    数：使用printf需要重定向的底层函数
  * 参    数：保持原始格式即可，无需变动
  * 返 回 值：保持原始格式即可，无需变动
  */
int fputc(int ch, FILE *f)
{
	USART3_SendByte(ch);			//将printf的底层重定向到自己的发送字节函数
	return ch;
}

/*****************************************接收*****************************************************/

/**
  * 函    数：返回接收标志位状态并清空标志位
  * 参    数：无
  * 返 回 值：0：串口没接收到数据，1：串口接收到数据并自动把标志位清0
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

// 获取串口接收到的数据
char USART3_GetRxData(void)
{
    return USART3_RxData;                                   // 返回串口接收到的数据
}


// USART3 中断处理函数
void USART3_IRQHandler(void)
{
    if (USART_GetITStatus(USART3, USART_IT_RXNE) == SET)    	// 如果 USART3 接收中断标志位为 SET
    {
        USART3_RxData = USART_ReceiveData(USART3);         		// 获取接收到的数据
        USART3_Flag = 1;                                  		// 置位串口接收标志位
        USART_ClearITPendingBit(USART3, USART_IT_RXNE);     	// 清除 USART3 接收中断标志位
    }
}
