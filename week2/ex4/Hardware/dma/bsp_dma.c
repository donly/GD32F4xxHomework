#include "bsp_dma.h"
#include "bsp_usart.h"

void dma_config(void)
{
	dma_single_data_parameter_struct dma_data_param;
	
	rcu_periph_clock_enable(BSP_DMA_RCU);
	
	dma_deinit(BSP_DMA, BSP_DMA_CH);
	
	dma_single_data_para_struct_init(&dma_data_param);
	dma_data_param.periph_addr = (uint32_t)&USART_DATA(BSP_USART);
	dma_data_param.memory0_addr = (uint32_t)g_recv_buff;
	dma_data_param.memory_inc = DMA_MEMORY_INCREASE_ENABLE;
	dma_data_param.periph_memory_width = DMA_PERIPH_WIDTH_8BIT;
	dma_data_param.number = USART_RECV_LEN;
	dma_data_param.priority = DMA_PRIORITY_ULTRA_HIGH;
	
	// 配置 DMA
	dma_single_data_mode_init(BSP_DMA, BSP_DMA_CH, &dma_data_param);
	// 使能 DMA 通道外设
	dma_channel_subperipheral_select(BSP_DMA, BSP_DMA_CH, DMA_SUBPERI4);
	// 使能 DMA 通道
	dma_channel_enable(BSP_DMA, BSP_DMA_CH);
	// 使能DMA通道中断 
	dma_interrupt_enable(BSP_DMA, BSP_DMA_CH, DMA_CHXCTL_FTFIE);
	// 配置中断优先级
	nvic_irq_enable(BSP_DMA_CH_IRQ, 2, 1);
	// 使能串口DMA接收
	usart_dma_receive_config(BSP_USART, USART_DENR_ENABLE);
}

void BSP_DMA_CH_IRQ_HANDLER(void)
{
	if (dma_interrupt_flag_get(BSP_DMA, BSP_DMA_CH, DMA_INT_FLAG_FTF) == SET)
	{
		dma_interrupt_flag_clear(BSP_DMA, BSP_DMA_CH, DMA_INT_FLAG_FTF);
		//g_recv_complete_flag = 1;
	}
}
