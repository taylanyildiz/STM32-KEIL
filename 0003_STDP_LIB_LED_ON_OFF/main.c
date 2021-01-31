#include "stm32f10x.h"                  // Device header
void GPIO_CONFIG(void);
void delay(uint32_t time);

static GPIO_InitTypeDef GPIO_InitStructure;
void GPIO_CONFIG()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_3 | GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
}

void delay(uint32_t time)
{
	while(time--);
}

int main()
{
	GPIO_CONFIG();
	
	while(1)
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_2| GPIO_Pin_3 | GPIO_Pin_4);
		delay(1000);
		GPIO_ResetBits(GPIOA,GPIO_Pin_2| GPIO_Pin_3 | GPIO_Pin_4);
		delay(1000);
		
	}
	
}
