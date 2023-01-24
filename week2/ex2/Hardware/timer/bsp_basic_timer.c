#include "bsp_basic_timer.h"
#include "bsp_led.h"
#include <stdio.h>

void basic_timer_config(uint16_t pre, uint16_t per)
{
	timer_parameter_struct timer_init_param;
	
	// 开启定时器时钟
	rcu_periph_clock_enable(BSP_TIMER_RCU);
	
	// 配置时钟
	rcu_timer_clock_prescaler_config(RCU_TIMER_PSC_MUL4);
	
	// 复位定时器
	timer_deinit(BSP_TIMER);
	
	timer_struct_para_init(&timer_init_param);
	timer_init_param.prescaler = pre - 1;
	timer_init_param.period = per - 1;
	
	// 初始化定时器
	timer_init(BSP_TIMER, &timer_init_param);
	
	// 配置中断优先级
	nvic_irq_enable(BSP_TIMER_IRQ, 3, 2);
	// 使能更新事件中断
	timer_interrupt_enable(BSP_TIMER, TIMER_INT_UP);
	// 使能定时器
	timer_enable(BSP_TIMER);
}

void basic_timer2_config(uint16_t pre, uint16_t per)
{
	timer_parameter_struct timer_init_param;
	
	// 开启定时器时钟
	rcu_periph_clock_enable(BSP_TIMER2_RCU);
	
	// 配置时钟
	rcu_timer_clock_prescaler_config(RCU_TIMER_PSC_MUL4);
	
	// 复位定时器
	timer_deinit(BSP_TIMER2);
	
	timer_struct_para_init(&timer_init_param);
	timer_init_param.prescaler = pre - 1;
	timer_init_param.period = per - 1;
	
	// 初始化定时器
	timer_init(BSP_TIMER2, &timer_init_param);
	
	// 配置中断优先级
	nvic_irq_enable(BSP_TIMER2_IRQ, 3, 2);
	// 使能更新事件中断
	timer_interrupt_enable(BSP_TIMER2, TIMER_INT_UP);
	// 使能定时器
	timer_enable(BSP_TIMER2);
}

void BSP_TIMER_IRQ_HANDLER(void)
{
	if (timer_interrupt_flag_get(BSP_TIMER, TIMER_INT_FLAG_UP) == SET)
	{
		timer_interrupt_flag_clear(BSP_TIMER, TIMER_INT_FLAG_UP);
		// 执行功能
		gpio_bit_toggle(PORT_LED1, PIN_LED1);
		//printf("BSP_TIMER_IRQHANDLER!\r\n");
	}
}

void BSP_TIMER2_IRQ_HANDLER(void)
{
	if (timer_interrupt_flag_get(BSP_TIMER2, TIMER_INT_FLAG_UP) == SET)
	{
		timer_interrupt_flag_clear(BSP_TIMER2, TIMER_INT_FLAG_UP);
		// 执行功能
		gpio_bit_toggle(PORT_LED2, PIN_LED2);
		//printf("BSP_TIMER_IRQHANDLER!\r\n");
	}
}
