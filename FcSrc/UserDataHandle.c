#include "UserDataHandle.h"
#include "Drv_Uart.h"
#include <string.h>

struct UartUserData_t UartUserData = {
	{0},
	&(UartUserData.U1Buffer[4]),
	
	{0},
	&(UartUserData.U2Buffer[4]),
	
	{0},
	&(UartUserData.U3Buffer[4]),
};

void EmptyDataHandleVector(void){}

/*-----将数据使用函数注册进对应串口的向量表里-------*/

void (*Uart1DataHandleVectors[])(void) = {	//数据处理函数向量表 优化掉if长蛇
	EmptyDataHandleVector
	
	
};

void (*Uart2DataHandleVectors[])(void) = {
	Uart2GetCurrentLocation,		//0
	Uart2GetTargetLocation			//1
	
	
};

void (*Uart3DataHandleVectors[])(void) = {
	Uart3GetData								//0
	
	
};

/*------------------------------------------------------------*/

u8 DataFrameCheck(u8* DataBuffer)	//数据校验
{
	u8 sumcheck = 0;
	u8 addcheck = 0;
	
	for(u8 i = 0; i < (DataBuffer[3] - 2); i++)
	{
		sumcheck += DataBuffer[i]; //从帧头开始，对每一字节进行求和，直到DATA区结束
		addcheck += sumcheck; //每一字节的求和操作，进行一次sumcheck的累加
	}
	//如果计算出的sumcheck和addcheck和接收到的check数据相等，代表校验通过，反之数据有误
	if(sumcheck == DataBuffer[DataBuffer[3] - 2] && addcheck == DataBuffer[DataBuffer[3] - 1])
	return (1); //校验通过
	else
	return (0); //校验失败
}

void Uart1UserDataHandle()	//校验通过后 此函数通过 数据处理函数向量表 直接进入具体的 数据使用函数
{
	//功能码 决定 数据使用函数 在数据使用函数向量表 中的地址
	if(UartUserData.U1Buffer[2] < sizeof(Uart1DataHandleVectors) / sizeof(void(*)(void)))		//功能码有效
	{
		(*Uart1DataHandleVectors[UartUserData.U1Buffer[2]])();
	}
}

void Uart2UserDataHandle()	//校验通过后 此函数通过 数据处理函数向量表 直接进入具体的 数据使用函数
{
	//功能码 决定 数据使用函数 在数据使用函数向量表 中的地址
	if(UartUserData.U2Buffer[2] < sizeof(Uart2DataHandleVectors) / sizeof(void(*)(void)))		//功能码有效
	{
		(*Uart2DataHandleVectors[UartUserData.U2Buffer[2]])();
	}
}

void Uart3UserDataHandle()	//校验通过后 此函数通过 数据处理函数向量表 直接进入具体的 数据使用函数
{
	//功能码 决定 数据使用函数 在数据使用函数向量表 中的地址
	if(UartUserData.U3Buffer[2] < sizeof(Uart3DataHandleVectors) / sizeof(void(*)(void)))		//功能码有效
	{
		(*Uart3DataHandleVectors[UartUserData.U3Buffer[2]])();
	}
}

/*--------------------------------数据提取------------------------------------*/

u8 GetOneU8(u8** ArrOfHeadArr)
{
	u8 result = *((u8*)(*ArrOfHeadArr));
	(*ArrOfHeadArr) += sizeof(u8);
	return result;
}

s8 GetOneS8(u8** ArrOfHeadArr)
{
	s8 result = *((s8*)(*ArrOfHeadArr));
	(*ArrOfHeadArr) += sizeof(s8);
	return result;
}

u16 GetOneU16(u8** ArrOfHeadArr)
{
	u16 result = *((u16*)(*ArrOfHeadArr));
	(*ArrOfHeadArr) += sizeof(u16);
	return result;
}

s16 GetOneS16(u8** ArrOfHeadArr)
{
	s16 result = *((s16*)(*ArrOfHeadArr));
	(*ArrOfHeadArr) += sizeof(s16);
	return result;
}

u32 GetOneU32(u8** ArrOfHeadArr)
{
	u32 result = *((u32*)(*ArrOfHeadArr));
	(*ArrOfHeadArr) += sizeof(u32);
	return result;
}

s32 GetOneS32(u8** ArrOfHeadArr)
{
	s32 result = *((s32*)(*ArrOfHeadArr));
	(*ArrOfHeadArr) += sizeof(s32);
	return result;
}

//unsigned _int64 GetOneU64(u8** ArrOfHeadArr)
//{
//	unsigned _int64 result = *((unsigned _int64*)(*ArrOfHeadArr));
//	(*ArrOfHeadArr) += sizeof(unsigned _int64);
//	return result;
//}

//signed _int64 GetOneS64(u8** ArrOfHeadArr)
//{
//	signed _int64 result = *((signed _int64*)(*ArrOfHeadArr));
//	(*ArrOfHeadArr) += sizeof(signed _int64);
//	return result;
//}

float GetOneFloat(u8** ArrOfHeadArr)
{
	float result;
	memcpy((void*)(&result), (const void*)(*ArrOfHeadArr), sizeof(float));
	(*ArrOfHeadArr) += sizeof(float);
	return result;
}

double GetOneDouble(u8** ArrOfHeadArr)
{
	double result;
	memcpy((void*)(&result), (const void*)(*ArrOfHeadArr), sizeof(double));
	(*ArrOfHeadArr) += sizeof(double);
	return result;
}

void GetOneString(u8** ArrOfHeadArr, char* string, u8 length)
{
	memcpy((void*)string, (const void*)(*ArrOfHeadArr), length);
	(*ArrOfHeadArr) += length;
}

/*--------------------------以下用户数据使用函数定义-------------------------------------*/

void Uart2GetCurrentLocation()
{
	UartUserData.U2DataHeadArr = &(UartUserData.U2Buffer[4]);		//重新指向数据起始地址
	
	u8 data1;
	s8 data2;
	float data3;
	float data4;
	u32 data5;
	s32 data6;	//假设有6个数据
	//......
	
	static int cnt = 0;
	cnt++;
	DrvUart2SendBuf((u8*)&cnt, 2);
	
	data1 = GetOneU8(&UartUserData.U2DataHeadArr);
	data2 = GetOneS8(&UartUserData.U2DataHeadArr);
	data3 = GetOneFloat(&UartUserData.U2DataHeadArr);
	data4 = GetOneFloat(&UartUserData.U2DataHeadArr);
	data5 = GetOneU32(&UartUserData.U2DataHeadArr);
	data6 = GetOneS32(&UartUserData.U2DataHeadArr);		//按顺序提取
	//.......
	
	//之后该干嘛干嘛
	
}

void Uart2GetTargetLocation()
{
	UartUserData.U2DataHeadArr = &(UartUserData.U2Buffer[4]);
	//......
	
}

void Uart3GetData()
{
	UartUserData.U3DataHeadArr = &(UartUserData.U3Buffer[4]);
	//......
	
}

