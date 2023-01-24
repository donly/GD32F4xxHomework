#ifndef _BSP_BASIC_TIMER_H
#define _BSP_BASIC_TIMER_H

#include "gd32f4xx.h"
#include "systick.h"

#define BSP_TIMER_RCU RCU_TIMER5
#define BSP_TIMER TIMER5
#define BSP_TIMER_IRQ TIMER5_DAC_IRQn
#define BSP_TIMER_IRQ_HANDLER TIMER5_DAC_IRQHandler

#define BSP_TIMER2_RCU RCU_TIMER2
#define BSP_TIMER2 TIMER2
#define BSP_TIMER2_IRQ TIMER2_IRQn
#define BSP_TIMER2_IRQ_HANDLER TIMER2_IRQHandler

void basic_timer_config(uint16_t pre, uint16_t per);
void basic_timer2_config(uint16_t pre, uint16_t per);

#endif
