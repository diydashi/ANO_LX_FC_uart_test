#ifndef __USERDATAHANDLE_H
#define __USERDATAHANDLE_H

#include "stm32f4xx.h"

struct UartUserData_t {
	u8 U1Buffer[100];		//环形缓冲区提取的原始数据
	u8* U1DataHeadArr;	//有效数据起始地址
	
	u8 U2Buffer[100];
	u8* U2DataHeadArr;
	
	u8 U3Buffer[100];
	u8* U3DataHeadArr;
};
extern struct UartUserData_t UartUserData;


extern void (*Uart1DataHandleVectors[])(void);	
extern void (*Uart2DataHandleVectors[])(void);
extern void (*Uart3DataHandleVectors[])(void);	//预定义 数据使用函数向量表 优化掉if长蛇

void Uart1UserDataHandle(void);		
void Uart2UserDataHandle(void);
void Uart3UserDataHandle(void);	//校验通过后 此函数通过 数据使用函数向量表 直接进入具体的 数据使用函数

u8 DataFrameCheck(u8* DataBuffer);		//数据校验

/*--------------------以下用户数据使用函数声明---------------------*/
void Uart2GetCurrentLocation(void);
void Uart2GetTargetLocation(void);

void Uart3GetData(void);

#endif
