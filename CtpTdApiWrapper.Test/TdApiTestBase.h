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
		sprintf(buf, "返回错误--->>> RequestID=%d ErrorID=%d, ErrorMsg=%s", nRequestID, pRspInfo->ErrorID, pRspInfo->ErrorMsg);
		std::cout << buf << std::endl;

		{// 通知阻塞
			//g_Condition.notify_one();
		}
	}
}

void OnHeartBeatWarning(int nTimeLapse)
{
	char errorLog[128] = { '\0' };
	sprintf(errorLog, "OnHeartBeatWarning =====网络心跳超时===== 距上次连接时间：%d", nTimeLapse);
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


		cout << "连接交易服务器..." << endl;
		if (m_pTdApi == NULL)
		{
			m_pTdApi = CreateFtdcTraderApi();									// 创建行情实例		
			m_pTdSpi = CreateTraderSpi();
			RegisterSpi(m_pTdApi, m_pTdSpi);

			RegOnRspError(m_pTdSpi, OnRspError);
			RegOnHeartBeatWarning(m_pTdSpi, OnHeartBeatWarning);

			SubscribePublicTopic(m_pTdApi, THOST_TERT_RESUME);
			SubscribePrivateTopic(m_pTdApi, THOST_TERT_RESUME);

			RegisterFront(m_pTdApi, gTradeFrontAddr);

			Init(m_pTdApi);
		}
	}

	// 回调成功后调用
	void NotifySuccess()
	{
		m_isCheckOK = true;
		m_cndt_v.notify_one();
	}

	// 回调失败通知
	void NotifyFailed()
	{
		m_isCheckOK = false;
		m_cndt_v.notify_one();
	}

	// 用于检测当前是否成功
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
	//// 公共参数
	//TThostFtdcBrokerIDType gBrokerID = "9999";								 // 模拟经纪商代码
	//TThostFtdcInvestorIDType gInvesterID = "180935";                         // 投资者账户名
	//TThostFtdcPasswordType m_investerPassword = "hello@123";                  // 投资者密码

	// 行情参数
	CThostFtdcTraderApi* m_pTdApi = nullptr;											// 行情指针
	TraderSpi* m_pTdSpi = nullptr;											 // spi

//	char m_tradeFrontAddr[28] = { '\0' };				 // 模拟交易前置地址 第一组

private:
	bool m_isCheckOK = false;
	std::mutex m_mtx;
	std::condition_variable m_cndt_v;

	int m_time = 7;															 // 超时时间	
};

TdApiTestBase* TestBase = NULL;
