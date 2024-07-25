#include "stm32f10x.h"                  // Device header
#include "TIM2.h"
/**
 * 函  数: 舵机初始化,控制方向
 * 参  数: 无
 * 返回值: 无
 */
void Servo_Init(void)
{
	//初始化PWM2输出
	TIM2_Init();
}

/**
 * 函  数: 舵机转向
 * 参  数: Angle 转动的角度(45~135)
 * 返回值: 无
 */
void Servo_SetAngle(float Angle)
{
	TIM2_SetCH1CCR(Angle / 180 * 2000 + 500);
}
/**
 * 函  数: 车头摆正,舵机回到90度
 * 参  数: 无
 * 返回值: 无
 */
void Servo_Setstraight(void)
{
	Servo_SetAngle(81);
}

/**
 * 函  数: 右转
 * 参  数: 无
 * 返回值: 无
 */
void Servo_SetRight(void)
{
	Servo_SetAngle(144);
}

/**
 * 函  数: 左转
 * 参  数: 无
 * 返回值: 无
 */
void Servo_SetLeft(void)
{
	Servo_SetAngle(36);
}

