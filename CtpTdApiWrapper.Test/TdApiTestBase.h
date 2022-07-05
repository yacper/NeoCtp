#pragma once
#include "pch.h"
#include "TestConstants.h"
using namespace std;


void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (bResult)
	{
		char buf[512] = { '\0' };
		sprintf(buf, "���ش���--->>> RequestID=%d ErrorID=%d, ErrorMsg=%s", nRequestID, pRspInfo->ErrorID, pRspInfo->ErrorMsg);
		std::cout << buf << std::endl;

		{// ֪ͨ����
			//g_Condition.notify_one();
		}
	}
}

void OnHeartBeatWarning(int nTimeLapse)
{
	char errorLog[128] = { '\0' };
	sprintf(errorLog, "OnHeartBeatWarning =====����������ʱ===== ���ϴ�����ʱ�䣺%d", nTimeLapse);
	std::cout << errorLog << std::endl;
}

class TdApiTestBase 
{
public:

	void InitTdApi()
	{
		//strcpy(m_tradeFrontAddr, gTradeFrontAddr);

	/*	strcpy(gBrokerID, gBrokerID);
		strcpy(gInvesterID, gInvesterID);
		strcpy(m_investerPassword, gInvesterPassword);*/


		cout << "���ӽ��׷�����..." << endl;
		if (m_pTdApi == NULL)
		{
			m_pTdApi = CreateFtdcTraderApi();									// ��������ʵ��		
			m_pTdSpi = CreateTdSpi();
			RegisterSpi(m_pTdApi, m_pTdSpi);

			RegOnRspError(m_pTdSpi, OnRspError);
			RegOnHeartBeatWarning(m_pTdSpi, OnHeartBeatWarning);

			SubscribePublicTopic(m_pTdApi, THOST_TERT_RESUME);
			SubscribePrivateTopic(m_pTdApi, THOST_TERT_RESUME);

			RegisterFront(m_pTdApi, gTradeFrontAddr);

			Init(m_pTdApi);
		}
	}

	// �ص��ɹ������
	void NotifySuccess()
	{
		m_isCheckOK = true;
		m_cndt_v.notify_one();
	}

	// �ص�ʧ��֪ͨ
	void NotifyFailed()
	{
		m_isCheckOK = false;
		m_cndt_v.notify_one();
	}

	// ���ڼ�⵱ǰ�Ƿ�ɹ�
	virtual bool CheckIsOK()
	{
		if (m_isCheckOK)
		{
			m_isCheckOK = false;
			return true;
		}

		std::unique_lock<mutex> lck(m_mtx);
		m_cndt_v.wait_for(lck, chrono::seconds(m_time));

		bool isOK = m_isCheckOK;
		m_isCheckOK = false;
		return isOK;
	}

	~TdApiTestBase()
	{
		TearDown();
	}

private:

	void TearDown()
	{
		//Join(m_pTdApi);
		Release(m_pTdApi);
		m_pTdApi = NULL;
		m_pTdSpi = NULL;
	}

public:
	//// ��������
	//TThostFtdcBrokerIDType gBrokerID = "9999";								 // ģ�⾭���̴���
	//TThostFtdcInvestorIDType gInvesterID = "180935";                         // Ͷ�����˻���
	//TThostFtdcPasswordType m_investerPassword = "hello@123";                  // Ͷ��������

	// �������
	CThostFtdcTraderApi* m_pTdApi = nullptr;											// ����ָ��
	TraderSpi* m_pTdSpi = nullptr;											 // spi

//	char m_tradeFrontAddr[28] = { '\0' };				 // ģ�⽻��ǰ�õ�ַ ��һ��

private:
	bool m_isCheckOK = false;
	std::mutex m_mtx;
	std::condition_variable m_cndt_v;

	int m_time = 7;															 // ��ʱʱ��	
};

TdApiTestBase* TestBase = NULL;
