#ifndef __INCLUDES_H
#define __INCLUDES_H

//包含的头文件
#include <stdio.h>
#include "stm32f10x.h"
#include "usart.h"
#include "SysTick.h"
#include "timer.h"
#include "string.h"
#include "key.h"
#include "gprs.h"




//定义bool类型
typedef enum
{
	FALSE=0,
	TRUE=1
}bool;
//定义FALSE和TRUE的值
#define FALSE 0
#define TRUE  1


//数组长度
#define BUF_MAX  100

#define RECI_MAX   3









#endif									//防止重复定义


