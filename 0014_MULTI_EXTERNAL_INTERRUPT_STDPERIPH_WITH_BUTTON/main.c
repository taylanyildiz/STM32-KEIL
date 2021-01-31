#include "stm32f10x.h"

void GPIO_Config(void);
void EXTI_Config(void);

void Delay(uint32_t time);
void GPIO_Config()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

	GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_Init(GPIOA,&GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_Init(GPIOB,&GPIO_InitStruct);



}

void EXTI_Config()
{
	EXTI_InitTypeDef EXTI_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	

	EXTI_InitStruct.EXTI_Line = EXTI_Line0 | EXTI_Line1;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_Init(&EXTI_InitStruct);

	NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd =ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStruct);

	NVIC_InitStruct.NVIC_IRQChannel = EXTI1_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd =ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&NVIC_InitStruct);

}

void Delay(uint32_t time)
{
	while(time--);
}



int main()
{
	GPIO_Config();
	EXTI_Config();

	while(1)
	{
		GPIO_ResetBits(GPIOB,GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5);
	}
}


void EXTI0_IRQHandler()
{
	if(EXTI_GetITStatus(EXTI_Line0) != RESET)
	{
		GPIO_SetBits(GPIOB,GPIO_Pin_3);
		Delay(400000);
		GPIO_ResetBits(GPIOB,GPIO_Pin_3);
		Delay(400000);
		GPIO_SetBits(GPIOB,GPIO_Pin_4);
		Delay(400000);
		GPIO_ResetBits(GPIOB,GPIO_Pin_4);
		Delay(400000);
		GPIO_SetBits(GPIOB,GPIO_Pin_5);
		Delay(400000);
		GPIO_ResetBits(GPIOB,GPIO_Pin_5);
		Delay(400000);
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}
void EXTI1_IRQHandler()
{
	if(EXTI_GetITStatus(EXTI_Line1) != RESET)
	{
		GPIO_SetBits(GPIOB,GPIO_Pin_5);
		Delay(400000);
		GPIO_ResetBits(GPIOB,GPIO_Pin_5);
		Delay(400000);
		GPIO_SetBits(GPIOB,GPIO_Pin_4);
		Delay(400000);
		GPIO_ResetBits(GPIOB,GPIO_Pin_4);
		Delay(400000);
		GPIO_SetBits(GPIOB,GPIO_Pin_3);
		Delay(400000);
		GPIO_ResetBits(GPIOB,GPIO_Pin_3);
		Delay(400000);
		EXTI_ClearITPendingBit(EXTI_Line1);
	}
}



