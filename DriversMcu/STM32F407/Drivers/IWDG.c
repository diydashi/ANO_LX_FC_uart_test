#include "IWDG.h"

//使能IWDG，在40KHz LSI下，每隔100ms产生IWDG复位
void IWDG_Configuration() 
{
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);  //使能或者失能对寄存器 IWDG_PR 和 IWDG_RLR 的写操作
	IWDG_SetPrescaler(IWDG_Prescaler_4);  //设置 IWDG 预分频值
	IWDG_SetReload(1000);  //设置 IWDG 重装载值
	IWDG_ReloadCounter();  //按照 IWDG 重装载寄存器的值重装载 IWDG 计数器,喂狗
	IWDG_Enable();  //使能 IWDG
}

//喂狗，防止CPU复位
void IWDG_FeedDog()
{
	IWDG_ReloadCounter();
}
