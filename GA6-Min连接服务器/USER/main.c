/**********************************************************************************
   STM32F103C8T6  	 
 * 硬件连接说明
	 使用单片串口2与GPRS模块通信  注：使用串口2可以避免下载和通信不会冲突
	 STM32      GPRS模块
	 打板子接线方法:               mini板子接线方法:
     PA3 (RXD2)->U_RX               PA3 (RXD2)->U_TX
	 PA2 (TXD2)->U_TX               PA2 (TXD2)->U_RX
	 GND	   ->GND                GND	   ->GND
	 
	 PA9(TXD1)--->调试信息端口
	 PA10(RXD1)-->调试信息端口
设计：
(1)LED0-7设置的引脚为:PB4-7 PB12-15
(2)KEY0-3设置的引脚为:PA4-7

果云技术:杜工
  
**********************************************************************************/

//#include <stdio.h>
#include "includes.h"


//串口2接收的数据缓冲区
char Data_Buf[BUF_MAX];
char Date_Re[RECI_MAX];

//接收标志1为接收完毕，0表示未接收完毕
u8 Received_flag;




/*******************************************************************************
* 函数名 : main 
* 描述   : 主函数
* 输入   : 
* 输出   : 
* 返回   : 
* 注意   : 串口2负责与AIR200模块通信，串口1用于串口调试，
*******************************************************************************/
int main(void)
{
	
	//发送Android的状态信息数据包(包头、编号1、灯灭、采集时间1min、温度值、温度值校验位、包尾)
	uint_8 SendData[7] = {0xEE,0x01,0x00,0x04,0x00,0x00,0xFF};
	char Ip_Port[41] = {"AT+CIPSTART=\"TCP\",\"47.94.153.56\",8888"};	
	
	//关中断
	__disable_irq();

	
	//初始化SYStick时钟
	delay_init();
	//初始化USART
	USART1_Init_Config(9600);
	USART2_Init_Config(115200);
	
	
	
	//开中断
	__enable_irq();
	
	for(;;)
	{
		
		//测试指令AT AT+CPIN?
		if(GPRS_init() == 1)
		{
			//判断指令：AT+CIPSTATUS=0  AT+CGATT=1  AT+CGACT=1,1 AT+CIPSTART="TCP","47.94.153.56",8888
			if(GPRS_Judg_Conn(Ip_Port) == 1)
			{
				//发送指令： AT+CIPSEND=1
				if(GPRS_Send_Data(SendData) == 1)
				{
//					light_change(LIGHT_GREEN);
				}
			}
		}	
	
	}

}


