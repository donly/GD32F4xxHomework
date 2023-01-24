/*!
    \file    main.c
    \brief   led

    \version 2023-01-22, V1.0.0, Week2 Ex4 for GD32F4xx
*/

/*
    Copyright (c) 2023, 东哥

    Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors
       may be used to endorse or promote products derived from this software without
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
OF SUCH DAMAGE.
*/


#include <stdio.h>
#include "main.h"
#include "bsp_led.h"
#include "sys.h"
#include "bsp_usart.h"
#include "string.h"
#include "bsp_dma.h"

/*!
    \brief    main function
    \param[in]  none
    \param[out] none
    \retval     none
*/
int main(void)
{
	uint8_t* idx;
	uint8_t  val;
	
	nvic_priority_group_set(NVIC_PRIGROUP_PRE2_SUB2);
	systick_config();
	led_gpio_config();
	usart_gpio_config(9600U);
	
	#if USE_USART_DMA
	dma_config();
	#endif
	
	while(1) {
		if (g_recv_complete_flag)
		{
			g_recv_complete_flag = 0;
			
			if (g_recv_len < 7) break; 
			
			idx = &g_recv_buff[3];
			char *tmp = strrchr((char *)g_recv_buff, ' ');
			
			if (tmp != NULL)
			{
				val = strcmp(strtok(tmp, "\r\t\n "), "on") == 0;
				switch(*idx)
				{
					case '1':
						LED1_OUT = val;
						break;
					case '2':
						LED2_OUT = val;
						break;
					case '3':
						LED3_OUT = val;
						break;
					case '4':
						LED4_OUT = val;
						break;
					default:
						printf("invalid led!\r\n"); 
						break;
				}
			}
			memset(g_recv_buff, 0, g_recv_len);
			g_recv_len = 0;
		}
  }
}
