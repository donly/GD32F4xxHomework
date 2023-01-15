#include "bsp_usart.h"
#include <stdio.h>

void usart_gpio_config(uint32_t brand_rate)
{
	// 开启时钟
	rcu_periph_clock_enable(BSP_USART_RCU);
	rcu_periph_clock_enable(BSP_USART_RX_RCU);
	rcu_periph_clock_enable(BSP_USART_TX_RCU);
	
	// 配置GPIO的复用功能，把 PA9,PA10 设置为串口功能
	gpio_af_set(BSP_USART_TX_PORT, BSP_USART_AF, BSP_USART_TX_PIN); 	// TX
	gpio_af_set(BSP_USART_RX_PORT, BSP_USART_AF, BSP_USART_RX_PIN);   // RX
	
	// 配置GPIO的模式
	gpio_mode_set(BSP_USART_TX_PORT, GPIO_MODE_AF, GPIO_PUPD_PULLUP, BSP_USART_TX_PIN); // 配置TX为复用上拉模式
	gpio_mode_set(BSP_USART_RX_PORT, GPIO_MODE_AF, GPIO_PUPD_PULLUP, BSP_USART_RX_PIN); // 配置RX为复用上拉模式
	
	// 配置GPIO的输出
	gpio_output_options_set(BSP_USART_TX_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, BSP_USART_TX_PIN); // 配置 TX 为推挽输出 50MHZ
	gpio_output_options_set(BSP_USART_RX_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, BSP_USART_RX_PIN); // 配置 RX 为推挽输出 50MHZ
	
	// 配置串口
	usart_deinit(BSP_USART);
	usart_baudrate_set(BSP_USART, brand_rate);
	usart_parity_config(BSP_USART, USART_PM_NONE);
	usart_word_length_set(BSP_USART, USART_WL_8BIT);
	usart_stop_bit_set(BSP_USART, USART_STB_1BIT);
	
	// 使能串口
	usart_enable(BSP_USART);
	usart_transmit_config(BSP_USART, USART_TRANSMIT_ENABLE);
}

// 串口发送数据
void usart_send_data(uint8_t ucch)
{
	usart_data_transmit(BSP_USART, (uint8_t)ucch);
	while (RESET == usart_flag_get(BSP_USART, USART_FLAG_TBE)); // 等待发送数据缓冲区 标志置位
	
}

// 串口发送字符串
void usart_send_string(uint8_t *ucstr)
{
	while (ucstr && *ucstr) // 地址为空或者值为空结束
	{
		usart_send_data(*ucstr++);
	}
}

int fputc(int ch, FILE *f)
{
	usart_send_data(ch);
	return ch;
}
