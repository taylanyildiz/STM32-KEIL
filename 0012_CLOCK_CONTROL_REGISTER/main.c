#include "stm32f10x.h"
#include "stdbool.h"

static bool Sset = true;
static bool Rreset = false;

void CLOCK_Config(void);
void GPIO_Config(void);
void Toogle_Pin(uint16_t pin);
void delay(uint32_t time);
void Write_Pin(uint16_t pin,bool set);
bool Read_Pin(uint16_t pin);
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

void Toogle_Pin(uint16_t pin)
{
	GPIOA->ODR ^= 1<<pin;
}

void delay(uint32_t time)
{
	while(time--);
}

void GPIO_Config()
{
	RCC->APB2ENR |= 0x00000004; // ABP2 GPIOA ENABLE
	GPIOA->CRL |= 0x00070000; // A PORT 4 ENABLE OUTPUT 50MHZ OPEN DRAIN 
	GPIOA->CRH |= 0x80000000; // A PORT 15 ENABLE INPUT PULL-UP PULL-DOWN
	GPIOA->CRL |= 0x00700000; // A PORT 5 ENABLE OUTPUT 50MHZ OPEN DRAIN
	//GPIOA->ODR |= 0x00000010; // PORT 4 SET 1<<4
}

void Write_Pin(uint16_t pin,bool set)
{
	if(set != false)
		GPIOA->BSRR |= 1<<pin; // SET pin
	if(set == false)
		GPIOA->BSRR = 1 << ( pin + 16); // RESET pin 
}

bool Read_Pin(uint16_t pin)
{
	if(GPIOA->IDR & 1<<pin)
		return true;
	else
		return false;
}

int main()
{
	CLOCK_Config();
	GPIO_Config();
	
	while(1)
	{
		//Toogle_Pin(4);
		Write_Pin(4,Sset);
		delay(1000);
		Write_Pin(4,Rreset);
		if(Read_Pin(15))
		{
			while(Read_Pin(15));
			delay(1000);
			Toogle_Pin(5);
		}
	}
	
}
