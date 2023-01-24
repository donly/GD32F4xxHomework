#include "bsp_key.h"
#include "sys.h"
#include <stdio.h>
#include "bsp_led.h"
#include "bsp_pwm.h"

void key_gpio_config(void)
{
	// 开启 GPIO 的端口时钟
	rcu_periph_clock_enable(BSP_KEY_RCU);
	// 系统配置时钟
	rcu_periph_clock_enable(RCU_SYSCFG);
	// 配置 GPIO 模式为浮空模式
	gpio_mode_set(BSP_KEY_PORT, GPIO_MODE_INPUT, GPIO_PUPD_PULLDOWN, BSP_KEY_PIN);
	// 按键默认状态是低电平，配置为下拉
	
	nvic_irq_enable(BSP_KEY_EXTI_IRQ_N, 3U, 3U);
	// 连接中断线到 GPIO
	syscfg_exti_line_config(BSP_KEY_EXTI_PORT_SOURCE, BSP_KEY_EXTI_PIN_SOURCE);
	
	// 对中断进行初始化
	exti_init(BSP_KEY_EXTI_LINE, EXTI_INTERRUPT, EXTI_TRIG_BOTH);
	
	// 使能中断
	exti_interrupt_enable(BSP_KEY_EXTI_LINE);
	
	// 清除中断标志位
	exti_interrupt_flag_clear(BSP_KEY_EXTI_LINE);
}

void key_scan(void)
{
	// 获取按键引脚的电平状态
	if (gpio_input_bit_get(BSP_KEY_PORT, BSP_KEY_PIN) == SET)
	{
		// 延迟消抖
		delay_1ms(20);
		if (gpio_input_bit_get(BSP_KEY_PORT, BSP_KEY_PIN) == SET)
		{
			// 执行功能
			g_breathing_flag = !g_breathing_flag;
			// 等待按键松开
			while(gpio_input_bit_get(BSP_KEY_PORT, BSP_KEY_PIN) == SET);
			//printf("key released.\n\r");
		}
	}
}

// 中断服务函数
void BSP_KEY_EXTI_IRQ_HANDLER(void)
{
	// 中断标志位为 1，按键按下
	if (exti_interrupt_flag_get(BSP_KEY_EXTI_LINE) == SET)
	{
		if (gpio_input_bit_get(BSP_KEY_PORT, BSP_KEY_PIN) == SET)
		{
			//printf("key press!\r\n");
			g_breathing_flag = !g_breathing_flag;
		}
		else {
			//printf("key release!\r\n");
		}
		
		// 清中断标志位
		exti_interrupt_flag_clear(BSP_KEY_EXTI_LINE);
	}
}
