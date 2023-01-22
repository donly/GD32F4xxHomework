#include "bsp_led.h"

void led_gpio_config(void)
{
	// 开启GPIO的端口时钟
	//BSP_RCU_AHB1EN |= 0x00000008;
//	BSP_RCU_AHB1EN |= (1 << 3);

//	// 配置GPIO的模式
//	//BSP_GPIOD_CTL &= 0xFFFF3FFF;
//	BSP_GPIOD_CTL &= ~(0x03 << (2*7));
//	BSP_GPIOD_CTL |= (0x01 << (2*7));
//	
//	// 配置为浮空模式
//	BSP_GPIOD_PUD &= ~(0x03 << (2*7));
//	
//	// 配置GPIO的输出
//	BSP_GPIOD_OMODE &= (0x00 << 7);
//	// 配置为推挽输出
//	BSP_GPIOD_OSPD &= ~(0x03 << (2*7));
//	// 配置输出速度为等级2
//	BSP_GPIOD_OSPD |= (0x02 << (2*7));
	
	// 使能时钟
	rcu_periph_clock_enable(RCU_LED1);
	// 配置GPIO的模式
	gpio_mode_set(PORT_LED1, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, PIN_LED1);
	// 配置GPIO的输出
	gpio_output_options_set(PORT_LED1, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, PIN_LED1);
}

