#pragma once
#include "ThostFtdcTraderApi.h"   // ����6.3.19�汾 
#include "ThostFtdcUserApiDataType.h"   // ����6.3.19�汾 
#include "ThostFtdcUserApiStruct.h"   // ����6.3.19�汾 

// ��������
TThostFtdcBrokerIDType gBrokerID = "9999";                         // ģ�⾭���̴���
TThostFtdcInvestorIDType gInvesterID = "097266";                         // Ͷ�����˻���
TThostFtdcPasswordType gInvesterPassword = "hello@1234";                     // Ͷ��������

// �������
//char gTradeFrontAddr[] = "tcp://180.168.146.187:10201";            // ģ�⽻��ǰ�õ�ַ ��һ��
char gTradeFrontAddr[] = "tcp://180.168.146.187:10130";            // ģ�⽻��ǰ�õ�ַ 24h

char *g_pInstrumentID[] = {"rb2210", "hc2205", "i2205", "j2205"}; // �����Լ�����б��С��ϡ���֣��������ѡһ��
int instrumentNum = 4;                                             // �����Լ��������

