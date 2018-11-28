#ifndef __USART_H
#define __USART_H

#include "includes.h"

#define USART1_REC_MAXLEN 200	//最大接收数据长度

void USART1_Init_Config(u32 bound);
void UART1_SendString(char* s);
void USART2_Init_Config(u32 bound);
void UART2_SendString(char* s);
void UART1_SendLR(void);
void UART2_SendLR(void);

void UART2_SendN(u8* s, s8 len);


void UART2_Send_Command(char* s);
u8 UART2_Send_AT_Command(char *b,char *a,u8 wait_time,u32 interval_time);

//串口1发送回车换行
#define UART1_SendLR() UART1_SendString("\r\n")

//串口2发送回车换行
#define UART2_SendLR() UART2_SendString("\r\n")
//	


#endif


