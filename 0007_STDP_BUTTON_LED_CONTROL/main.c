#include "stm32f10x.h"
#include "toogle_pin.h"
void GPIO_Config(void);

void GPIO_Config()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct; // struct yapisinda bir nesne olusturuldu
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD; // MODE INPUT PULL DOWN SECILDI
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4; // PIN 4 SECILDI
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz; // HIZI SECILDI
	
	GPIO_Init(GPIOA,&GPIO_InitStruct); // A PORTU VE POINTER OLARAK ADRES YOLLANDI
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_OD; // MODE OUTPUT OPEN DRAIN 
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz; // HIZI
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_4 | GPIO_Pin_3; // PINLER
	
	GPIO_Init(GPIOB,&GPIO_InitStruct); // B PORTU VE POINTER OLARAK ADRES YOLLANDI
	
}

int main()
{
	GPIO_Config();
	while(1)
	{
		/*
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4))
		{
			
			GPIO_SetBits(GPIOB,GPIO_Pin_5 | GPIO_Pin_4 | GPIO_Pin_3);
		}
		else
		{
			GPIO_ResetBits(GPIOB,GPIO_Pin_5 | GPIO_Pin_4 | GPIO_Pin_3);
		}
		*/
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4))
		{
			while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4));
			GPIO_ToogleBits(GPIOB,GPIO_Pin_5 | GPIO_Pin_4 | GPIO_Pin_3);
		}
	}
}
