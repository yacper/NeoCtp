#pragma once
#include <gtest/gtest.h>
#include "Login.h"
void OnRspQryTradingAccount(
	CThostFtdcTradingAccountField *pTradingAccount,
	CThostFtdcRspInfoField *pRspInfo,
	int nRequestID,
	bool bIsLast)
{
	bool bResult = pRspInfo && pRspInfo->ErrorID != 0;
	if (!bResult)
	{
		TestBase->NotifySuccess();

		std::cout << "=====查询投资者资金账户成功=====" << std::endl;
		std::cout << "投资者账号： " << pTradingAccount->AccountID << std::endl;
		std::cout << "可用资金： " << pTradingAccount->Available << std::endl;
		std::cout << "可取资金： " << pTradingAccount->WithdrawQuota << std::endl;
		std::cout << "当前保证金: " << pTradingAccount->CurrMargin << std::endl;
		std::cout << "平仓盈亏： " << pTradingAccount->CloseProfit << std::endl;
	}
	else
	{
		TestBase->NotifyFailed();
		std::cerr << "Error Code: " << pRspInfo->ErrorID << ", Error Msg =" << pRspInfo->ErrorMsg << std::endl;
	}
};



class QryTradingAccount: public Login
{
public:
	virtual void Run()
	{
		Login::Run();
		RegOnRspQryTradingAccount(m_pTdSpi, OnRspQryTradingAccount);
		bool loginOK = Login::CheckIsOK();
		if (loginOK)
			SendQryTradingAccount();
		else
		{
			NotifyFailed();
			std::cerr << "登录失败, 请检查账号密码..." << std::endl;
		}
	}

private:
	void SendQryTradingAccount()
	{
		CThostFtdcQryTradingAccountField tradingAccountReq;
		memset(&tradingAccountReq, 0, sizeof(tradingAccountReq));
		strcpy(tradingAccountReq.BrokerID, gBrokerID);
		strcpy(tradingAccountReq.InvestorID, gInvesterID);
		int requestID = 3; // 请求编号
		std::this_thread::sleep_for(std::chrono::milliseconds(700)); // 有时候需要停顿一会才能查询成功
		int rt = ReqQryTradingAccount(m_pTdApi, &tradingAccountReq, requestID);
		if (!rt)
			std::cout << ">>>>>>发送投资者资金账户查询请求成功" << std::endl;
		else
		{
			NotifyFailed();
			std::cerr << "--->>>发送投资者资金账户查询请求失败" << std::endl;
		}
	}
};

TEST(CtpApiTest, 05QryAccountregister)
{
	QryTradingAccount qryAccCtp;
	TestBase = &qryAccCtp;
	qryAccCtp.Run();
	bool isOK = qryAccCtp.CheckIsOK();
	EXPECT_TRUE(isOK);
}