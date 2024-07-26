#include "stm32f10x.h"                  // Device header
#include "TIM1.h"
#include "HC05.h"
int16_t CarSpeed = 0;

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
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_8 | GPIO_Pin_9 ;
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
void LeftMoter_SetSpeed(int16_t Speed)
{
    if(Speed > 0)
    {
        GPIO_SetBits(GPIOB, GPIO_Pin_8);  
        GPIO_ResetBits(GPIOB, GPIO_Pin_9);
        TIM1_SetCompare3(Speed);          
    }
    else
    {
        GPIO_ResetBits(GPIOB, GPIO_Pin_8);
        GPIO_SetBits(GPIOB, GPIO_Pin_9);  
        TIM1_SetCompare3(-Speed);         
    }
}

/**
 * ��  ��: ���ָı�ת��������ٶ�
 * ��  ��: Speed ռ�ձ�(0~100)
 * ����ֵ: ��
 */
void RightMoter_SetSpeed(int16_t Speed)
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
	CarSpeed = 0;
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
    if(CarSpeed <= 80)  // �����ٶȵ����ֵ���Է�ֹ����100
    {
        CarSpeed += 20;
        UHC05_SendNumber(CarSpeed, 3);
        LeftMoter_SetSpeed(CarSpeed);
        RightMoter_SetSpeed(CarSpeed);
    }
}

/**
 * ��  ��: ��20���ٶ�
 * ��  ��: ��
 * ����ֵ: ��
 */
void Moter_SubSpeed(void)
{
    if(CarSpeed >= -80)  // �����ٶȵ���Сֵ���Է�ֹ����-100
    {
        CarSpeed -= 20;
        UHC05_SendNumber(CarSpeed, 3);
        LeftMoter_SetSpeed(CarSpeed);
        RightMoter_SetSpeed(CarSpeed);
    }
}

/**
 * ��  ��: ǰ��
 * ��  ��: ��
 * ����ֵ: ��
 */
void Moter_Up(void)
{
	CarSpeed = 60;
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
	CarSpeed = -60;
	LeftMoter_SetSpeed(-60);
	RightMoter_SetSpeed(-60);
}

