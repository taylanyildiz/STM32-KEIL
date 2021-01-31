	#include "stm32f10x.h"
	#include "stm32f10x_exti.h"
	#include "misc.h"
	void GPIO_Config(void);
	void EXTI_Config(void);
	void delay(uint32_t time);

	void delay(uint32_t time)
	{
		while(time--);
	}
	void GPIO_Config()
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

		GPIO_InitTypeDef GPIO_InitStruct;

		// A PORT PA0-PA1 INPUT PULL DOWN SPEED 50MHZ
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
		GPIO_Init(GPIOA,&GPIO_InitStruct);
		// B PORT PB3-PB4-PB5 OUTPUT OPEN DRAIN SPEED 50MHZ;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_OD;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
		GPIO_Init(GPIOB,&GPIO_InitStruct);

	}

	void EXTI_Config()
	{
		// EXTERNAL INTERRUPT ENABLE
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
		EXTI_InitTypeDef EXTI_InitStruct;
		NVIC_InitTypeDef NVIC_InitStruct;



		EXTI_InitStruct.EXTI_Line = EXTI_Line1 | EXTI_Line2; // 1. VE 2. INTERRUPT SECILDI
		EXTI_InitStruct.EXTI_LineCmd = ENABLE; // ENABLE EDILDI
		EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt; // MODE INTERRUPT ALINDI
		EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising; // YUKSELEN KENAR SECILDI
		EXTI_Init(&EXTI_InitStruct); // AKTIVE EDILDI


		//INTERRUPT YONETICISI NVIC

		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1); // INTERRUPTA ONCELIK GRUBU BELIRLENDI

		// BIRINCI INTERRUPT
		NVIC_InitStruct.NVIC_IRQChannel = EXTI1_IRQn;
		NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
		NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1; // HANGISI DUSUK OLURSA ONCELIK ATANIR
		NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
		NVIC_Init(&NVIC_InitStruct);

		//IKINCI INTERRUPT
		NVIC_InitStruct.NVIC_IRQChannel = EXTI2_IRQn;
		NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
		NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
		NVIC_Init(&NVIC_InitStruct);


	}

	void EXTI1_IRQHandler()
	{
		if(EXTI_GetITStatus(EXTI_Line1) != RESET)
		{
			GPIO_ResetBits(GPIOB,GPIO_Pin_All);
			GPIO_SetBits(GPIOB,GPIO_Pin_3);
			delay(1000000);
			GPIO_SetBits(GPIOB,GPIO_Pin_4);
			delay(1000000);
			GPIO_SetBits(GPIOB,GPIO_Pin_5);
			delay(1000000);

			EXTI_ClearITPendingBit(EXTI_Line1);
		}
	}

	void EXTI2_IRQHandler()
	{
		if(EXTI_GetITStatus(EXTI_Line2) != RESET)
		{
			GPIO_ResetBits(GPIOB,GPIO_Pin_All);
			GPIO_SetBits(GPIOB,GPIO_Pin_5);
			delay(1000000);
			GPIO_SetBits(GPIOB,GPIO_Pin_4);
			delay(1000000);
			GPIO_SetBits(GPIOB,GPIO_Pin_3);
			delay(1000000);
			EXTI_ClearITPendingBit(EXTI_Line2);
		}
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
