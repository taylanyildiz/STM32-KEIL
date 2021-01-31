#include "stm32f10x.h"


void CLOCK_Config(void);
void GPIO_Config(void);
void EXTI_Config(void);
void delay(uint32_t time);


void CLOCK_Config()
{
	RCC->CR |= 0x00030000; // HSEON -- HSERDY
	while(!(RCC->CR & 0x00020000));// WAIT HSEFLAG
	RCC->CR |= 0x00080000; // CSSON
	RCC->CFGR |= 0x00020000; // HSE DIVEDER FOR PLL ENTRY DIVEDED BY 2
	RCC->CFGR |= 0x00010000; // PLLSRC HSE ENTRY
	RCC->CFGR |= 0x00080000; // PLLMUL BY 4
	RCC->CFGR |= 0x00000090; // HPRE AHB SYSCLK DIVIDED BY 4
	RCC->CFGR |= 0x00002000; // APB2 HCLK DIVIDED BY 2
	RCC->CFGR |= 0x00000400; // APB1 HCLK DIVIDED BY 2
	RCC->CR |= 0x01000000; // PLL-ON
	while(!(RCC->CR & 0x02000000)); // WAIT PLLFLAG
	RCC->CIR = 0x00980000; // INTERRUPT CLEAR
}

void GPIO_Config()
{
	RCC->APB2ENR |= 0x00000004; // ABP2 GPIOA ENABLE
	RCC->APB2ENR |= 0x00000008; // ABP2 GPIOB ENABLE

	GPIOB->CRL |= 0x00000700; // PB2 OUTPUT OPEN DRAIN 50 MHZ
	GPIOB->CRL |= 0x00007000; // PB3 OUTPUT OPEN DRAIN 50 MHZ
	GPIOB->CRL |= 0x00070000; // PB4 OUTPUT OPEN DRAIN 50 MHZ
}

void EXTI_Config()
{
	RCC->APB2ENR |= 0x00000001; //AFIOEN ENABLE (EXTI)



	NVIC_EnableIRQ(EXTI0_IRQn);
	NVIC_EnableIRQ(EXTI1_IRQn);
	NVIC_EnableIRQ(EXTI2_IRQn);


	

	AFIO->EXTICR[0]= 0x00000000; // A PORT EXTI0
	AFIO->EXTICR[1]= 0x00000000; // A PORT EXTI1
	AFIO->EXTICR[2]= 0x00000000; // A PORT EXTI2

	NVIC_SetPriority(EXTI0_IRQn, 0);
	NVIC_SetPriority(EXTI1_IRQn, 5);
	NVIC_SetPriority(EXTI2_IRQn, 3);
	
	EXTI->IMR |= 0x00000007; // INTERRUPT MODE ENABLE 3 PIN
	EXTI->RTSR |=0x00000007; // TRIGGER RISING YUKSELEN KENAR

}

void delay(uint32_t time)
{
	while(time--);
}

void EXTI0_IRQHandler()
{
	if(EXTI->PR & 0x0000001)
	{
		GPIOB->ODR = 1<<2;
		delay(100000);
		GPIOB->ODR = 1 << (2 + 16);
		delay(100000);
		GPIOB->ODR = 1<<3;
		delay(100000);
		GPIOB->ODR = 1 << (3 + 16);
		delay(100000);
		GPIOB->ODR = 1<<4;
		delay(100000);
		GPIOB->ODR = 1 << (4 + 16);
		delay(100000);

		EXTI->PR = 0x00000001;
	}
}

void EXTI1_IRQHandler()
{
	if(EXTI->PR & 0x00000002)
	{
		GPIOB->ODR =  1<<4;
		delay(100000);
		GPIOB->ODR = 1 << (4 + 16);
		delay(100000);
		GPIOB->ODR = 1<<3;
		delay(100000);
		GPIOB->ODR = 1 << (3 + 16);
		delay(100000);
		GPIOB->ODR = 1<<2;
		delay(100000);
		GPIOB->ODR = 1 << (2 + 16);
		delay(100000);
		EXTI->PR = 0x00000002;
	}
}

void EXTI2_IRQHandler()
{
	if(EXTI->PR & 0x00000004)
	{
		GPIOB->ODR = 1 << 3;
		delay(100000);
		GPIOB->ODR = 1 << (3 + 16);
		delay(100000);
		GPIOB->ODR = 1 << 2;
		delay(100000);
		GPIOB->ODR = 1 << (2 + 16);
		delay(100000);
		GPIOB->ODR = 1 << 4;
		delay(100000);
		GPIOB->ODR = 1 << (4 + 16);
		delay(100000);
		EXTI->PR = 0x00000004;
	}
}

int main()
{
	CLOCK_Config();
	GPIO_Config();
	EXTI_Config();
	while(1)
	{
		GPIOB->ODR = 1 << (2 + 16)| 1<< (3 + 16) | 1<< (4 + 16);
		if(EXTI->PR & 0x0000001)
		{
			GPIOB->ODR = 1 << 2;
			delay(100000);
			GPIOB->ODR = 1 << (2 + 16);
			delay(100000);
			GPIOB->ODR = 1 << 3;
			delay(100000);
			GPIOB->ODR = 1 << (3 + 16);
			delay(100000);
			GPIOB->ODR = 1 << 4;
			delay(100000);
			GPIOB->ODR = 1 << (4 + 16);
			delay(100000);

			EXTI->PR = 0x00000001;
		}
		else
		{
			GPIOB->ODR = 1 << 4;
			delay(100000);
			GPIOB->ODR = 1 << (4 + 16);
			delay(100000);
		}
		
			
	}
}
