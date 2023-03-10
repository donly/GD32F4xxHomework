#ifndef _BSP_KEH_H
#define _BSP_KEH_H

#include "gd32f4xx.h"
#include "systick.h"

#define BSP_KEY_RCU RCU_GPIOA
#define BSP_KEY_PORT GPIOA
#define BSP_KEY_PIN GPIO_PIN_0

#define BSP_KEY_EXTI_IRQ_N 				EXTI0_IRQn
#define BSP_KEY_EXTI_PORT_SOURCE 	EXTI_SOURCE_GPIOA
#define BSP_KEY_EXTI_PIN_SOURCE 	EXTI_SOURCE_PIN0
#define BSP_KEY_EXTI_LINE 				EXTI_0
#define BSP_KEY_EXTI_IRQ_HANDLER  EXTI0_IRQHandler

void key_gpio_config(void);
void key_scan(void);

#endif
