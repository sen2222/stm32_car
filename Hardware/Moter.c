#include "stm32f10x.h"                  // Device header
#include "TIM1.h"
#include "HC05.h"
int16_t CarSpeed = 0;

/**
 * 函  数: 直流电机驱动初始化
 * 参  数: 无
 * 返回值: 无
 */
void Moter_Init(void)
{
	//开启时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	//配置GPIO
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;					//复用推挽输出
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_8 | GPIO_Pin_9 ;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	//初始化TIM1
	TIM1_Init();
}

/**
 * 函  数: 左轮改变转动方向或速度
 * 参  数: Speed 占空比(0~100)
 * 返回值: 无
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
 * 函  数: 左轮改变转动方向或速度
 * 参  数: Speed 占空比(0~100)
 * 返回值: 无
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
 * 函  数: 停车
 * 参  数: 无
 * 返回值: 无
 */
void Moter_Stop(void)
{
	CarSpeed = 0;
	LeftMoter_SetSpeed(0);
	RightMoter_SetSpeed(0);
}
/**
 * 函  数: 加20的速度
 * 参  数: 无
 * 返回值: 无
 */
void Moter_AddSpeed(void)
{
    if(CarSpeed <= 80)  // 更新速度的最大值，以防止超过100
    {
        CarSpeed += 20;
        UHC05_SendNumber(CarSpeed, 3);
        LeftMoter_SetSpeed(CarSpeed);
        RightMoter_SetSpeed(CarSpeed);
    }
}

/**
 * 函  数: 减20的速度
 * 参  数: 无
 * 返回值: 无
 */
void Moter_SubSpeed(void)
{
    if(CarSpeed >= -80)  // 更新速度的最小值，以防止超过-100
    {
        CarSpeed -= 20;
        UHC05_SendNumber(CarSpeed, 3);
        LeftMoter_SetSpeed(CarSpeed);
        RightMoter_SetSpeed(CarSpeed);
    }
}

/**
 * 函  数: 前进
 * 参  数: 无
 * 返回值: 无
 */
void Moter_Up(void)
{
	CarSpeed = 60;
	LeftMoter_SetSpeed(60);
	RightMoter_SetSpeed(60);
}
/**
 * 函  数: 后退
 * 参  数: 无
 * 返回值: 无
 */
void Moter_Down(void)
{
	CarSpeed = -60;
	LeftMoter_SetSpeed(-60);
	RightMoter_SetSpeed(-60);
}

