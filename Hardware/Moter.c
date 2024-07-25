#include "stm32f10x.h"                  // Device header
#include "TIM1.h"
int8_t CarSpeed = 0;

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
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;
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
void LeftMoter_SetSpeed(int8_t Speed)
{
    if(Speed > 0)
    {
        GPIO_SetBits(GPIOB, GPIO_Pin_3);  // 设置引脚 3 为高电平
        GPIO_ResetBits(GPIOB, GPIO_Pin_4); // 设置引脚 4 为低电平
        TIM1_SetCompare3(Speed);           // 设置 PWM 占空比
    }
    else
    {
        GPIO_ResetBits(GPIOB, GPIO_Pin_3); // 设置引脚 3 为低电平
        GPIO_SetBits(GPIOB, GPIO_Pin_4);   // 设置引脚 4 为高电平
        TIM1_SetCompare3(-Speed);          // 设置 PWM 占空比
    }
}

/**
 * 函  数: 左轮改变转动方向或速度
 * 参  数: Speed 占空比(0~100)
 * 返回值: 无
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
 * 函  数: 停车
 * 参  数: 无
 * 返回值: 无
 */
void Moter_Stop(void)
{
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
	int8_t tmp;
	if(CarSpeed <= 80)
	{
		tmp = CarSpeed + 20;
		LeftMoter_SetSpeed(tmp);
		RightMoter_SetSpeed(tmp);
	}
}

/**
 * 函  数: 减20的速度
 * 参  数: 无
 * 返回值: 无
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
 * 函  数: 前进
 * 参  数: 无
 * 返回值: 无
 */
void Moter_Up(void)
{
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
	LeftMoter_SetSpeed(-60);
	RightMoter_SetSpeed(-60);
}

