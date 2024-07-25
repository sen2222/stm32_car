#include "stm32f10x.h"                  // Device header
#include "TIM1.h"
int8_t CarSpeed = 0;

/**
 * ��  ��: ֱ�����������ʼ��
 * ��  ��: ��
 * ����ֵ: ��
 */
void Moter_Init(void)
{
	//����ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	//����GPIO
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;					//�����������
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	//��ʼ��TIM1
	TIM1_Init();
}

/**
 * ��  ��: ���ָı�ת��������ٶ�
 * ��  ��: Speed ռ�ձ�(0~100)
 * ����ֵ: ��
 */
void LeftMoter_SetSpeed(int8_t Speed)
{
    if(Speed > 0)
    {
        GPIO_SetBits(GPIOB, GPIO_Pin_3);  // �������� 3 Ϊ�ߵ�ƽ
        GPIO_ResetBits(GPIOB, GPIO_Pin_4); // �������� 4 Ϊ�͵�ƽ
        TIM1_SetCompare3(Speed);           // ���� PWM ռ�ձ�
    }
    else
    {
        GPIO_ResetBits(GPIOB, GPIO_Pin_3); // �������� 3 Ϊ�͵�ƽ
        GPIO_SetBits(GPIOB, GPIO_Pin_4);   // �������� 4 Ϊ�ߵ�ƽ
        TIM1_SetCompare3(-Speed);          // ���� PWM ռ�ձ�
    }
}

/**
 * ��  ��: ���ָı�ת��������ٶ�
 * ��  ��: Speed ռ�ձ�(0~100)
 * ����ֵ: ��
 */
void RightMoter_SetSpeed(int8_t Speed)
{
	if(Speed > 0)
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_5);		
		GPIO_ResetBits(GPIOB, GPIO_Pin_6);		
		TIM1_SetCompare4(Speed);				
	}
	else
	{
		GPIO_ResetBits(GPIOB, GPIO_Pin_5);		
		GPIO_SetBits(GPIOB, GPIO_Pin_6);		
		TIM1_SetCompare4(-Speed);				
	}
}

/**
 * ��  ��: ͣ��
 * ��  ��: ��
 * ����ֵ: ��
 */
void Moter_Stop(void)
{
	LeftMoter_SetSpeed(0);
	RightMoter_SetSpeed(0);
}
/**
 * ��  ��: ��20���ٶ�
 * ��  ��: ��
 * ����ֵ: ��
 */
void Moter_AddSpeed(void)
{
	int8_t tmp;
	if(CarSpeed <= 80)
	{
		tmp = CarSpeed + 20;
		LeftMoter_SetSpeed(tmp);
		RightMoter_SetSpeed(tmp);
	}
}

/**
 * ��  ��: ��20���ٶ�
 * ��  ��: ��
 * ����ֵ: ��
 */
void Moter_SubSpeed(void)
{
	int8_t tmp;
	if(CarSpeed >= -80)
	{
		tmp = CarSpeed - 20;
		LeftMoter_SetSpeed(tmp);
		RightMoter_SetSpeed(tmp);
	}
}
/**
 * ��  ��: ǰ��
 * ��  ��: ��
 * ����ֵ: ��
 */
void Moter_Up(void)
{
	LeftMoter_SetSpeed(60);
	RightMoter_SetSpeed(60);
}
/**
 * ��  ��: ����
 * ��  ��: ��
 * ����ֵ: ��
 */
void Moter_Down(void)
{
	LeftMoter_SetSpeed(-60);
	RightMoter_SetSpeed(-60);
}

