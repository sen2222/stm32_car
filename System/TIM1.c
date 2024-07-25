#include "stm32f10x.h"                  // Device header

/**
 * 函  数: TIM1输出PWM初始化,控制驱动马达
 * 参  数: 无
 * 返回值: 无
 */
void TIM1_Init(void)
{
	//开启时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	
	//配置输出GPIO
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;					//复用推挽输出
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	
	//配置时基单元
	TIM_TimeBaseInitTypeDef TIM_TimeStruct;
	TIM_TimeStruct.TIM_ClockDivision = TIM_CKD_DIV1;				//不使用分频
	TIM_TimeStruct.TIM_CounterMode = TIM_CounterMode_Up;			//向上计数
	TIM_TimeStruct.TIM_Period = 100 - 1;							//ARR
	TIM_TimeStruct.TIM_Prescaler = 36 - 1;							//PSC (舵机要求20ms的周期信号)
	TIM_TimeStruct.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM1, &TIM_TimeStruct);
	
	
	//配置输出比较
	TIM_OCInitTypeDef TIN_OCInitStruct;
	TIM_OCStructInit(&TIN_OCInitStruct);							//结构体初始化一下
	
	TIN_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;					
	TIN_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;			//极性为高
	TIN_OCInitStruct.TIM_OutputState =TIM_OutputState_Enable ;
	TIN_OCInitStruct.TIM_Pulse = 0;								
	
	TIM_OC3Init(TIM1, &TIN_OCInitStruct);							//A10口是CH3
	TIM_OC4Init(TIM1, &TIN_OCInitStruct);							//A11口是CH4
	
	TIM_CtrlPWMOutputs(TIM1, ENABLE);
	
	//使能定时器
	TIM_Cmd(TIM1, ENABLE);
}
/**
 * 函  数: TIM1改变CH3,改变占空比
 * 参  数: Compare 新的RCC
 * 返回值: 无
 */
void TIM1_SetCompare3(uint16_t Compare)
{
	TIM_SetCompare3(TIM1, Compare);		//设置CCR3的值
}

/**
 * 函  数: TIM1改变CH4,改变占空比
 * 参  数: Compare 新的RCC
 * 返回值: 无
 */
void TIM1_SetCompare4(uint16_t Compare)
{
	TIM_SetCompare4(TIM1, Compare);		//设置CCR4的值
}

