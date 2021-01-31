

#include "stm32f10x.h"
#include "toogle_pin.h"

void GPIO_ToogleBits(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin)
{
	assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
	GPIOx->ODR ^= GPIO_Pin;
}
