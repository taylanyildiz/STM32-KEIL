#include "stm32f10x.h"
#include "toogle_pin.h" //TOOGLE TERSLEME 

void GPIO_Config(void);
void delay(uint32_t time);
void GPIO_Config()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
}

void delay(uint32_t time)
{
	while(time--);
}

int main()
{
	int count = 0;
	GPIO_Config();
	while(1)
	{
			if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4))
			{
				while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4));
				delay(7200000);
				count++;
			}
			if(count == 1)
			{
				GPIO_SetBits(GPIOB,GPIO_Pin_1);
			}
			else if(count == 2)
			{
				GPIO_SetBits(GPIOB,GPIO_Pin_2);
			}
			else if(count == 3)
			{
				GPIO_SetBits(GPIOB,GPIO_Pin_3);
			}
			else
			{
				count = 0;
				delay(1400000);
				GPIO_ResetBits(GPIOB,GPIO_Pin_3);
				delay(1400000);
				GPIO_ResetBits(GPIOB,GPIO_Pin_2);
				delay(1400000);
				GPIO_ResetBits(GPIOB,GPIO_Pin_1);
			}
			
			
	}
}
