#ifndef __USERDATAHANDLE_H
#define __USERDATAHANDLE_H

#include "stm32f4xx.h"

struct UartUserData_t {
	u8 U1Buffer[100];		//���λ�������ȡ��ԭʼ����
	u8* U1DataHeadArr;	//��Ч������ʼ��ַ
	
	u8 U2Buffer[100];
	u8* U2DataHeadArr;
	
	u8 U3Buffer[100];
	u8* U3DataHeadArr;
};
extern struct UartUserData_t UartUserData;


extern void (*Uart1DataHandleVectors[])(void);	
extern void (*Uart2DataHandleVectors[])(void);
extern void (*Uart3DataHandleVectors[])(void);	//Ԥ���� ����ʹ�ú��������� �Ż���if����

void Uart1UserDataHandle(void);		
void Uart2UserDataHandle(void);
void Uart3UserDataHandle(void);	//У��ͨ���� �˺���ͨ�� ����ʹ�ú��������� ֱ�ӽ������� ����ʹ�ú���

u8 DataFrameCheck(u8* DataBuffer);		//����У��

/*--------------------�����û�����ʹ�ú�������---------------------*/
void Uart2GetCurrentLocation(void);
void Uart2GetTargetLocation(void);

void Uart3GetData(void);

#endif
