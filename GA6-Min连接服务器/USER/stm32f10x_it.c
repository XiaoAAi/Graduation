/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"

/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

extern char Data_Buf[BUF_MAX];
extern char Date_Re[RECI_MAX];
extern u8 Received_flag;









/*******************************************************************************
* 函数名  : USART1_IRQHandler
* 描述    : 串口1中断服务程序
* 输入    : 无
* 返回    : 无 
* 说明    : 1)、只启动了USART1中断接收，未启动USART1中断发送。
*           2)、接收到0x0d 0x0a(回车、"\r\n")代表帧数据接收完成
*******************************************************************************/
void USART1_IRQHandler(void)                	
{
	u8 temp = 0;
	__disable_irq();
	
	if(USART_GetFlagStatus(USART1, USART_IT_RXNE) != RESET)
	{
		temp = USART_ReceiveData(USART1);
		USART_SendData(USART1, temp);
		
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	}
	
	__enable_irq();
}





/*******************************************************************************
* 函数名  : USART2_IRQHandler
* 描述    : 串口1中断服务程序
* 输入    : 无
* 返回    : 无 
* 说明    : 
*******************************************************************************/
void USART2_IRQHandler(void)                	
{
    u8 ch;
    static u8 Received_count = 0;
    static u8 data_count = 0;
		__disable_irq();
	
		if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
		{
			ch = USART_ReceiveData(USART2);
			if(ch != '\0')
			{
				Data_Buf[data_count] = ch;
				data_count++;
				if(data_count > BUF_MAX)
				{
					data_count = 0;
				}
			}

				//用于接受服务器转发的数据
				if(ch == 0xEE)
				{
					Received_count = 0;
					//Received_flag = 0;
				}
				else
				{
					if(ch == 0xEF)
					{
						Received_flag = 1;
						//直接通过GPRS进行发送（考虑到GPRS是直接和服务器相连接的，可以省掉不必要的操作）
						//这也是KL25向服务器发送确认指令，标志服务器发送成功
//        			GPRS_Send_Data((uint_8 *)"EE");
					}
					else
					{
						Date_Re[Received_count] = ch;
						Received_count++;
					}

				}				
			USART_ClearITPendingBit(USART2, USART_IT_RXNE);			
		}
		__enable_irq();
	
} 	




//功能： systick中断
void SysTick_Handler(void)
{

}






/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
