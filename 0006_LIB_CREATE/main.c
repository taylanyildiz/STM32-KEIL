#include "stm32f10x.h"
#include "clock_config.h"

int main()
{
	SetPinA();
	while(1)
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_4);
		delay(1000);
		GPIO_ResetBits(GPIOA,GPIO_Pin_4);
		delay(1000);
	}
	
} 
