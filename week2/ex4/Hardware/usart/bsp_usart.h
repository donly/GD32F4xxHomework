#ifndef _BSP_USART_H
#define _BSP_USART_H

#include "gd32f4xx.h"
#include "systick.h"

#define BSP_USART_TX_RCU	RCU_GPIOA
#define BSP_USART_RX_RCU	RCU_GPIOA
#define BSP_USART_RCU 		RCU_USART0

#define BSP_USART_TX_PORT GPIOA
#define BSP_USART_RX_PORT GPIOA
#define BSP_USART_AF			GPIO_AF_7
#define BSP_USART_TX_PIN  GPIO_PIN_9
#define BSP_USART_RX_PIN  GPIO_PIN_10

#define BSP_USART 				USART0
#define BSP_USART_IRQ			USART0_IRQn

#define USART_RECV_LEN	  4096

#define USE_USART_DMA			1 // 0:中断接收；1:DMA接收

extern uint8_t g_recv_buff[USART_RECV_LEN];
extern uint16_t g_recv_len;
extern uint8_t g_recv_complete_flag;

void usart_gpio_config(uint32_t brand_rate);
void usart_send_data(uint8_t);
void usart_send_string(uint8_t *ucstr);

#endif
