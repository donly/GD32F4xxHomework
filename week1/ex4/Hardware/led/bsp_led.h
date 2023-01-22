#ifndef _BSP_LED_H
#define _BSP_LED_H

#include "gd32f4xx.h"
#include "systick.h"

//#define BSP_RCU_BASE (unsigned int)0x40023800
//#define BSP_RCU_AHB1EN *(unsigned int *)(BSP_RCU_BASE + 0x30U)
//	
//#define BSP_GPIOD_BASE (unsigned int)0x40020C00	
//#define BSP_GPIOD_CTL *(unsigned int *)(BSP_GPIOD_BASE + 0x00)

//#define BSP_GPIOD_PUD *(unsigned int *)(BSP_GPIOD_BASE + 0x0CU)
//#define BSP_GPIOD_OCTL *(unsigned int *)(BSP_GPIOD_BASE + 0x14U)
//#define BSP_GPIOD_OMODE *(unsigned int *)(BSP_GPIOD_BASE + 0x04U)
//#define BSP_GPIOD_OSPD *(unsigned int *)(BSP_GPIOD_BASE + 0x08U)
	
#define RCU_LED1 RCU_GPIOE
#define PORT_LED1 GPIOE
#define PIN_LED1 GPIO_PIN_3

void led_gpio_config(void);

#endif
