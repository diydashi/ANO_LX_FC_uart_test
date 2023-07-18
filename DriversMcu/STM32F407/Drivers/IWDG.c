#include "IWDG.h"

//ʹ��IWDG����40KHz LSI�£�ÿ��100ms����IWDG��λ
void IWDG_Configuration() 
{
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);  //ʹ�ܻ���ʧ�ܶԼĴ��� IWDG_PR �� IWDG_RLR ��д����
	IWDG_SetPrescaler(IWDG_Prescaler_4);  //���� IWDG Ԥ��Ƶֵ
	IWDG_SetReload(1000);  //���� IWDG ��װ��ֵ
	IWDG_ReloadCounter();  //���� IWDG ��װ�ؼĴ�����ֵ��װ�� IWDG ������,ι��
	IWDG_Enable();  //ʹ�� IWDG
}

//ι������ֹCPU��λ
void IWDG_FeedDog()
{
	IWDG_ReloadCounter();
}
