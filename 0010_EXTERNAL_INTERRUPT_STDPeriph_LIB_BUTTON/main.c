#include "stm32f10x.h"
#include "stm32f10x_exti.h"


void EXTI0_IRQHandler(void) ;
void GPIO_Config(void);
void EXTI_Config(void);
void delay(uint32_t time);
void Interrtupt(void);
void EXTI_Config()
{
	EXTI_InitTypeDef EXTI_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE); // EXTERNAL INTERRUPT

	//EXTI INTERRUPT PIN SECIM
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0); // A portunun 0.biti secildi.
	EXTI_InitStruct.EXTI_Line = EXTI_Line0; // 0. pin
	EXTI_InitStruct.EXTI_LineCmd = ENABLE; // aktif
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt; //event yada interrupt secilir
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising; // yükselen kenar
	EXTI_Init(&EXTI_InitStruct);

	//INTERRUPT YONETICISI AYARLARI
	NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0; // BIRDEN FAZLA INTERRUPT KULLANILDIGI ZAMAN ONCELIK VERIR
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0; // BIRDEN FAZLA INTERRUPT KULLANILDIGI ZAMAN ONCELIK VERIR
	NVIC_Init(&NVIC_InitStruct);

}

void GPIO_Config()
{
	GPIO_InitTypeDef GPIO_InitStruct;


	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);// A PORT
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); // B PORT


	// B PORT CIKIS
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	// A PORT GIRIS
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_Init(GPIOA,&GPIO_InitStruct);

}

void delay(uint32_t time)
{
	while(time) time--;
}

void EXTI0_IRQHandler(void) 
{
    /* Make sure that interrupt flag is set */
    if (EXTI_GetITStatus(EXTI_Line0) != RESET) 
		{
			
			GPIO_ResetBits(GPIOB,GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6);
			delay(720000);
			GPIO_SetBits(GPIOB,GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6);
			delay(720000);
			GPIO_ResetBits(GPIOB,GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6);
			delay(720000);
			GPIO_SetBits(GPIOB,GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6);
			delay(720000);
			GPIO_ResetBits(GPIOB,GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6);
			delay(720000);
			EXTI_ClearITPendingBit(EXTI_Line0);			
      EXTI_ClearITPendingBit(EXTI_Line0);
			
    }
}

void Interrtupt()
{
	if(EXTI_GetITStatus(EXTI_Line0) == SET)
	{
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}

int main()
{
	GPIO_Config();
	EXTI_Config();
	while(1)
	{
		GPIO_SetBits(GPIOB,GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6);
	}
}
