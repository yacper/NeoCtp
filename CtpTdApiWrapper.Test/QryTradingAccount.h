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

		std::cout << "=====��ѯͶ�����ʽ��˻��ɹ�=====" << std::endl;
		std::cout << "Ͷ�����˺ţ� " << pTradingAccount->AccountID << std::endl;
		std::cout << "�����ʽ� " << pTradingAccount->Available << std::endl;
		std::cout << "��ȡ�ʽ� " << pTradingAccount->WithdrawQuota << std::endl;
		std::cout << "��ǰ��֤��: " << pTradingAccount->CurrMargin << std::endl;
		std::cout << "ƽ��ӯ���� " << pTradingAccount->CloseProfit << std::endl;
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
			std::cerr << "��¼ʧ��, �����˺�����..." << std::endl;
		}
	}

private:
	void SendQryTradingAccount()
	{
		CThostFtdcQryTradingAccountField tradingAccountReq;
		memset(&tradingAccountReq, 0, sizeof(tradingAccountReq));
		strcpy(tradingAccountReq.BrokerID, gBrokerID);
		strcpy(tradingAccountReq.InvestorID, gInvesterID);
		int requestID = 3; // ������
		std::this_thread::sleep_for(std::chrono::milliseconds(700)); // ��ʱ����Ҫͣ��һ����ܲ�ѯ�ɹ�
		int rt = ReqQryTradingAccount(m_pTdApi, &tradingAccountReq, requestID);
		if (!rt)
			std::cout << ">>>>>>����Ͷ�����ʽ��˻���ѯ����ɹ�" << std::endl;
		else
		{
			NotifyFailed();
			std::cerr << "--->>>����Ͷ�����ʽ��˻���ѯ����ʧ��" << std::endl;
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