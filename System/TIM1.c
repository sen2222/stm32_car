#include "stm32f10x.h"                  // Device header

/**
 * ��  ��: TIM1���PWM��ʼ��,�����������
 * ��  ��: ��
 * ����ֵ: ��
 */
void TIM1_Init(void)
{
	//����ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	
	//�������GPIO
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;					//�����������
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	
	//����ʱ����Ԫ
	TIM_TimeBaseInitTypeDef TIM_TimeStruct;
	TIM_TimeStruct.TIM_ClockDivision = TIM_CKD_DIV1;				//��ʹ�÷�Ƶ
	TIM_TimeStruct.TIM_CounterMode = TIM_CounterMode_Up;			//���ϼ���
	TIM_TimeStruct.TIM_Period = 100 - 1;							//ARR
	TIM_TimeStruct.TIM_Prescaler = 36 - 1;							//PSC (���Ҫ��20ms�������ź�)
	TIM_TimeStruct.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM1, &TIM_TimeStruct);
	
	
	//��������Ƚ�
	TIM_OCInitTypeDef TIN_OCInitStruct;
	TIM_OCStructInit(&TIN_OCInitStruct);							//�ṹ���ʼ��һ��
	
	TIN_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;					
	TIN_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;			//����Ϊ��
	TIN_OCInitStruct.TIM_OutputState =TIM_OutputState_Enable ;
	TIN_OCInitStruct.TIM_Pulse = 0;								
	
	TIM_OC3Init(TIM1, &TIN_OCInitStruct);							//A10����CH3
	TIM_OC4Init(TIM1, &TIN_OCInitStruct);							//A11����CH4
	
	TIM_CtrlPWMOutputs(TIM1, ENABLE);
	
	//ʹ�ܶ�ʱ��
	TIM_Cmd(TIM1, ENABLE);
}
/**
 * ��  ��: TIM1�ı�CH3,�ı�ռ�ձ�
 * ��  ��: Compare �µ�RCC
 * ����ֵ: ��
 */
void TIM1_SetCompare3(uint16_t Compare)
{
	TIM_SetCompare3(TIM1, Compare);		//����CCR3��ֵ
}

/**
 * ��  ��: TIM1�ı�CH4,�ı�ռ�ձ�
 * ��  ��: Compare �µ�RCC
 * ����ֵ: ��
 */
void TIM1_SetCompare4(uint16_t Compare)
{
	TIM_SetCompare4(TIM1, Compare);		//����CCR4��ֵ
}

