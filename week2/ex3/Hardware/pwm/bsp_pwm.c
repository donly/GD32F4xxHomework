#include "bsp_pwm.h"

uint8_t g_breathing_flag = 0; // 0=停止；1=开始

static void pwm_gpio_config(void)
{
	// 使能时钟
	rcu_periph_clock_enable(BSP_PWM_RCU);
	// 配置GPIO的模式
	gpio_mode_set(BSP_PWM_PORT, GPIO_MODE_AF, GPIO_PUPD_NONE, BSP_PWM_PIN);
	// 配置GPIO的输出
	gpio_output_options_set(BSP_PWM_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, BSP_PWM_PIN);
	gpio_af_set(BSP_PWM_PORT, BSP_PWM_AF, BSP_PWM_PIN);
}

void pwm_config(uint16_t pre, uint16_t per)
{
	// 定义定时器结构体
	timer_parameter_struct timer_init_param;
	timer_oc_parameter_struct timer_oc_int_param;
	
	pwm_gpio_config();
	
	// 配置时钟
	rcu_periph_clock_enable(BSP_PWM_TIMER_RCU);
	rcu_timer_clock_prescaler_config(RCU_TIMER_PSC_MUL4);
	timer_deinit(BSP_PWM_TIMER);
	timer_struct_para_init(&timer_init_param);
	timer_init_param.prescaler = pre - 1;
	timer_init_param.period = per - 1;
	timer_init(BSP_PWM_TIMER, &timer_init_param);
	
	// 输出结构体
	timer_channel_output_struct_para_init(&timer_oc_int_param);
	timer_oc_int_param.outputstate = TIMER_CCX_ENABLE;
	timer_channel_output_config(BSP_PWM_TIMER, BSP_PWM_CHANNEL, &timer_oc_int_param);
	
	timer_channel_output_pulse_value_config(BSP_PWM_TIMER, BSP_PWM_CHANNEL, 0);
	timer_channel_output_mode_config(BSP_PWM_TIMER, BSP_PWM_CHANNEL, TIMER_OC_MODE_PWM0);
	timer_channel_output_shadow_config(BSP_PWM_TIMER, BSP_PWM_CHANNEL, TIMER_OC_SHADOW_DISABLE);
	
	//timer_primary_output_config(TIMER0, ENABLE);  // 只有高级定时器才需要
	timer_auto_reload_shadow_enable(BSP_PWM_TIMER);
	
	timer_enable(BSP_PWM_TIMER);
}

void pwm_breathing_led(void)
{
	static uint8_t dir = 0; 	// 方向
	static uint16_t val = 0; 	// 值
	static uint16_t step = 300;
	
	if (g_breathing_flag == 0)
	{
		gpio_bit_write(BSP_PWM_PORT, BSP_PWM_PIN, RESET);
		return;
	}
	
	if (dir == 0) {
		val += step;
		if (val > 10000) dir = 1;
	} else {
		val -= step;
		if (val <= 0) dir = 0;
	}
	
	timer_channel_output_pulse_value_config(BSP_PWM_TIMER, BSP_PWM_CHANNEL, val);
	delay_1ms(50);
}
