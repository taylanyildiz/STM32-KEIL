#include "stm32f10x.h"                  // Device header

void CLK_CONFIG(void);
void delay(uint32_t time);

void CLK_CONFIG()
{
	RCC->CR |= 0x00030000; // HSE ON -- HSE FLAG ON
	while(!(RCC->CR & 0x00020000)); // HSE FLAG WAIT
	RCC->CR |= 0x00080000; // CSS ON
	RCC->CFGR |= 0x00010000; // PLL_SRC -> 1 HSE ON
	RCC->CFGR |= 0X00020000; // PLL_HSE GIRIS BOLUCU /2
	RCC->CFGR |= 0x000C0000; // PLL_MUL CARPICI *4
	RCC->CFGR |= 0x00000090; // AHB PRESCALER /4
	RCC->CFGR |= 0x00000400; // HCLK DIVIDED BY 2 APB1 PRESCALER
	RCC->CFGR |= 0x00002000; // HCLK DIVIDED BY 2 APB2 PRESCALER
	RCC->CIR |= 0x00080000; // HSE RDYC FLAG INDIRILIR
	RCC->CIR |= 0x00800000; // CSS FLAG CLEAR
	RCC->APB2ENR |= 0x00000004; // A PORTUNU AKTIF EDER	
}

void delay(uint32_t time)
{
	time = time*2318;
	while(time)
		time--;
}


int main()
{
	CLK_CONFIG();
	
	GPIOA->CRL |= 0x00010000;
	
	
	
	while(1)
	{
		/*
		GPIOA->ODR |= 0x00000010;
		delay(1000);
		GPIOA->ODR = 0x00000000;
		delay(1000);
		*/
		
		GPIOA->BSRR = 0x00000010;
		delay(1000);
		GPIOA->BSRR = 0x00100000;
		delay(1000);
		
	}
	
}
