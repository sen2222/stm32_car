#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "HC05.h"
#include "Servo.h"
#include "Moter.h"

int main(void)
{

	char HC_Data;
	/*模块初始化*/
	Servo_Init();
	Moter_Init();
	HC05_Init();
	
	
	
	printf("hello\r\n");
	
	while (1)
	{
		HC_Data = HC05_GetRxData();
		if(HC_Data != '\0')
		{
			switch (HC_Data)
			{
				case 'L':
					Servo_SetLeft();  		 // 左转
					break;
					
				case 'R':
					Servo_SetRight();  		// 右转
					break;
					
				case 'S':
					Servo_Setstraight(); 	// 回正
					break;
					
				case 'u':
					Moter_Up();				//前进
					break;
					
				case 'd':
					Moter_Down();			//后退
					break;
					
				case 'o':
					Moter_Stop();
					break;
				
			}
			
			
		}
	}
}
