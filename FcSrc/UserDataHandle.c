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

/*-----������ʹ�ú���ע�����Ӧ���ڵ���������-------*/

void (*Uart1DataHandleVectors[])(void) = {	//���ݴ����������� �Ż���if����
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

u8 DataFrameCheck(u8* DataBuffer)	//����У��
{
	u8 sumcheck = 0;
	u8 addcheck = 0;
	
	for(u8 i = 0; i < (DataBuffer[3] - 2); i++)
	{
		sumcheck += DataBuffer[i]; //��֡ͷ��ʼ����ÿһ�ֽڽ�����ͣ�ֱ��DATA������
		addcheck += sumcheck; //ÿһ�ֽڵ���Ͳ���������һ��sumcheck���ۼ�
	}
	//����������sumcheck��addcheck�ͽ��յ���check������ȣ�����У��ͨ������֮��������
	if(sumcheck == DataBuffer[DataBuffer[3] - 2] && addcheck == DataBuffer[DataBuffer[3] - 1])
	return (1); //У��ͨ��
	else
	return (0); //У��ʧ��
}

void Uart1UserDataHandle()	//У��ͨ���� �˺���ͨ�� ���ݴ����������� ֱ�ӽ������� ����ʹ�ú���
{
	//������ ���� ����ʹ�ú��� ������ʹ�ú��������� �еĵ�ַ
	if(UartUserData.U1Buffer[2] < sizeof(Uart1DataHandleVectors) / sizeof(void(*)(void)))		//��������Ч
	{
		(*Uart1DataHandleVectors[UartUserData.U1Buffer[2]])();
	}
}

void Uart2UserDataHandle()	//У��ͨ���� �˺���ͨ�� ���ݴ����������� ֱ�ӽ������� ����ʹ�ú���
{
	//������ ���� ����ʹ�ú��� ������ʹ�ú��������� �еĵ�ַ
	if(UartUserData.U2Buffer[2] < sizeof(Uart2DataHandleVectors) / sizeof(void(*)(void)))		//��������Ч
	{
		(*Uart2DataHandleVectors[UartUserData.U2Buffer[2]])();
	}
}

void Uart3UserDataHandle()	//У��ͨ���� �˺���ͨ�� ���ݴ����������� ֱ�ӽ������� ����ʹ�ú���
{
	//������ ���� ����ʹ�ú��� ������ʹ�ú��������� �еĵ�ַ
	if(UartUserData.U3Buffer[2] < sizeof(Uart3DataHandleVectors) / sizeof(void(*)(void)))		//��������Ч
	{
		(*Uart3DataHandleVectors[UartUserData.U3Buffer[2]])();
	}
}

/*--------------------------------������ȡ------------------------------------*/

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

/*--------------------------�����û�����ʹ�ú�������-------------------------------------*/

void Uart2GetCurrentLocation()
{
	UartUserData.U2DataHeadArr = &(UartUserData.U2Buffer[4]);		//����ָ��������ʼ��ַ
	
	u8 data1;
	s8 data2;
	float data3;
	float data4;
	u32 data5;
	s32 data6;	//������6������
	//......
	
	static int cnt = 0;
	cnt++;
	DrvUart2SendBuf((u8*)&cnt, 2);
	
	data1 = GetOneU8(&UartUserData.U2DataHeadArr);
	data2 = GetOneS8(&UartUserData.U2DataHeadArr);
	data3 = GetOneFloat(&UartUserData.U2DataHeadArr);
	data4 = GetOneFloat(&UartUserData.U2DataHeadArr);
	data5 = GetOneU32(&UartUserData.U2DataHeadArr);
	data6 = GetOneS32(&UartUserData.U2DataHeadArr);		//��˳����ȡ
	//.......
	
	//֮��ø������
	
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

