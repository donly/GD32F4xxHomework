#ifndef _BSP_LED_H
#define _BSP_LED_H

#include "gd32f4xx.h"
#include "systick.h"

#define RCU_LED1 RCU_GPIOE
#define RCU_LED2 RCU_GPIOD
#define RCU_LED3 RCU_GPIOG
#define RCU_LED4 RCU_GPIOA

#define PORT_LED1 GPIOE
#define PORT_LED2 GPIOD
#define PORT_LED3 GPIOG
#define PORT_LED4 GPIOA

#define PIN_LED1 GPIO_PIN_3
#define PIN_LED2 GPIO_PIN_7
#define PIN_LED3 GPIO_PIN_3
#define PIN_LED4 GPIO_PIN_5

#define LED1_OUT PEout(3)
#define LED2_OUT PDout(7)
#define LED3_OUT PGout(3)
#define LED4_OUT PAout(5)

void led_gpio_config(void);

#endif
