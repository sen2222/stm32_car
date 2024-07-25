#include "stm32f10x.h"                  // Device header
#include "TIM2.h"
/**
 * ��  ��: �����ʼ��,���Ʒ���
 * ��  ��: ��
 * ����ֵ: ��
 */
void Servo_Init(void)
{
	//��ʼ��PWM2���
	TIM2_Init();
}

/**
 * ��  ��: ���ת��
 * ��  ��: Angle ת���ĽǶ�(45~135)
 * ����ֵ: ��
 */
void Servo_SetAngle(float Angle)
{
	TIM2_SetCH1CCR(Angle / 180 * 2000 + 500);
}
/**
 * ��  ��: ��ͷ����,����ص�90��
 * ��  ��: ��
 * ����ֵ: ��
 */
void Servo_Setstraight(void)
{
	Servo_SetAngle(81);
}

/**
 * ��  ��: ��ת
 * ��  ��: ��
 * ����ֵ: ��
 */
void Servo_SetRight(void)
{
	Servo_SetAngle(144);
}

/**
 * ��  ��: ��ת
 * ��  ��: ��
 * ����ֵ: ��
 */
void Servo_SetLeft(void)
{
	Servo_SetAngle(36);
}

