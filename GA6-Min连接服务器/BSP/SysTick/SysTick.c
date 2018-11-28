#include "SysTick.h"



static u8  fac_us = 0;                          //us寤舵椂鍊嶄箻鏁?
static u16 fac_ms = 0;                          //ms寤舵椂鍊嶄箻鏁?鍦╱cos涓?浠ｈ〃姣忎釜鑺傛媿鐨刴s鏁?



void delay_init()
{

    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);   //閫夋嫨澶栭儴鏃堕挓  HCLK/8
    fac_us = SystemCoreClock / 8000000;         //涓虹郴缁熸椂閽熺殑1/8

    fac_ms = (u16)fac_us * 1000;                //闈濷S涓?浠ｈ〃姣忎釜ms闇€瑕佺殑systick鏃堕挓鏁?

}


void delay_us(u32 nus)
{
    u32 temp;
    SysTick->LOAD = nus * fac_us;               //鏃堕棿鍔犺浇
    SysTick->VAL = 0x00;                        //娓呯┖璁℃暟鍣?
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk ;  //寮€濮嬪€掓暟

    do
    {
        temp = SysTick->CTRL;
    }
    while((temp & 0x01) && !(temp & (1 << 16))); //绛夊緟鏃堕棿鍒拌揪

    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;  //鍏抽棴璁℃暟鍣?
    SysTick->VAL = 0X00;                         //娓呯┖璁℃暟鍣?
}



void delay_ms(u16 nms)
{
    u32 temp;
    SysTick->LOAD = (u32)nms * fac_ms;          //鏃堕棿鍔犺浇(SysTick->LOAD涓?4bit)
    SysTick->VAL = 0x00;                        //娓呯┖璁℃暟鍣?
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk ;  //寮€濮嬪€掓暟

    do
    {
        temp = SysTick->CTRL;
    }
    while((temp & 0x01) && !(temp & (1 << 16))); //绛夊緟鏃堕棿鍒拌揪

    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;  //鍏抽棴璁℃暟鍣?
    SysTick->VAL = 0X00;                        //娓呯┖璁℃暟鍣?
}





