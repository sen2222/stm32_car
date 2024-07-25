#include "stm32f10x.h"                  // Device header

/**
 * 函  数: TIM2输出PWM初始化,控制舵机
 * 参  数: 无
 * 返回值: 无
 */
void TIM2_Init(void)
{
	//开启时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	//配置GPIO口
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;					//复用推挽输出
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	//配置时基单元
	TIM_TimeBaseInitTypeDef TIM_TimeStruct;
	TIM_TimeStruct.TIM_ClockDivision = TIM_CKD_DIV1;				//不使用分频
	TIM_TimeStruct.TIM_CounterMode = TIM_CounterMode_Up;			//向上计数
	TIM_TimeStruct.TIM_Period = 20000 - 1;							//ARR
	TIM_TimeStruct.TIM_Prescaler = 72 - 1;							//PSC (舵机要求20ms的周期信号)
	TIM_TimeStruct.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &TIM_TimeStruct);
	
	
	//配置输出比较
	TIM_OCInitTypeDef TIN_OCInitStruct;
	TIM_OCStructInit(&TIN_OCInitStruct);							//结构体初始化一下
	
	TIN_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;					
	TIN_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;			//极性为高
	TIN_OCInitStruct.TIM_OutputState =TIM_OutputState_Enable ;
	TIN_OCInitStruct.TIM_Pulse = 1400;								//初始化为90度
	
	TIM_OC1Init(TIM2, &TIN_OCInitStruct);							//A0口是CH1
	
	
	//开使能
	TIM_Cmd(TIM2, ENABLE);
}

/**
 * 函  数: 修改RCC的值，控制占空比
 * 参  数: Compare 新的RCC
 * 返回值: 无
 */
void TIM2_SetCH1CCR(uint16_t Compare)
{
    TIM_SetCompare1(TIM2, Compare);
}
