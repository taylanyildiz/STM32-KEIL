#include "stm32f10x.h"
#include "stm32f10x_exti.h"

void EXTI_Config(void);
void GPIO_Config(void);
void Delay(uint32_t time);
void EXTI0_IRQHandler(void);

void GPIO_Config()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
}

void EXTI_Config()
{
	EXTI_InitTypeDef EXTI_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);
	
	EXTI_InitStruct.EXTI_Line = EXTI_Line0;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_Init(&EXTI_InitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&NVIC_InitStruct);
	
	
	
}

void Delay(uint32_t time)
{
	while(time--);
}


void EXTI0_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line0) != RESET)
	{
		Delay(1000000);
		GPIO_ResetBits(GPIOA,GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6);
		Delay(1000000);
		GPIO_SetBits(GPIOA,GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6);
		Delay(1000000);
		GPIO_ResetBits(GPIOA,GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6);
		Delay(1000000);
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}



int main()
{
	GPIO_Config();
	EXTI_Config();
	while(1)
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6);
	
	}
}
