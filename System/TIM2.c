#include "stm32f10x.h"                  // Device header

/**
 * ��  ��: TIM2���PWM��ʼ��,���ƶ��
 * ��  ��: ��
 * ����ֵ: ��
 */
void TIM2_Init(void)
{
	//����ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	//����GPIO��
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;					//�����������
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	//����ʱ����Ԫ
	TIM_TimeBaseInitTypeDef TIM_TimeStruct;
	TIM_TimeStruct.TIM_ClockDivision = TIM_CKD_DIV1;				//��ʹ�÷�Ƶ
	TIM_TimeStruct.TIM_CounterMode = TIM_CounterMode_Up;			//���ϼ���
	TIM_TimeStruct.TIM_Period = 20000 - 1;							//ARR
	TIM_TimeStruct.TIM_Prescaler = 72 - 1;							//PSC (���Ҫ��20ms�������ź�)
	TIM_TimeStruct.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &TIM_TimeStruct);
	
	
	//��������Ƚ�
	TIM_OCInitTypeDef TIN_OCInitStruct;
	TIM_OCStructInit(&TIN_OCInitStruct);							//�ṹ���ʼ��һ��
	
	TIN_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;					
	TIN_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;			//����Ϊ��
	TIN_OCInitStruct.TIM_OutputState =TIM_OutputState_Enable ;
	TIN_OCInitStruct.TIM_Pulse = 1400;								//��ʼ��Ϊ90��
	
	TIM_OC1Init(TIM2, &TIN_OCInitStruct);							//A0����CH1
	
	
	//��ʹ��
	TIM_Cmd(TIM2, ENABLE);
}

/**
 * ��  ��: �޸�RCC��ֵ������ռ�ձ�
 * ��  ��: Compare �µ�RCC
 * ����ֵ: ��
 */
void TIM2_SetCH1CCR(uint16_t Compare)
{
    TIM_SetCompare1(TIM2, Compare);
}
