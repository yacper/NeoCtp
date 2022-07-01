#pragma once
#include <gtest/gtest.h>
#include "Login.h"
void OnRspQryAccountregister(
	CThostFtdcAccountregisterField* pAccountregister,
	CThostFtdcRspInfoField* pRspInfo,
	int nRequestID,
	bool bIsLast)
{
	bool bResult = pRspInfo && pRspInfo->ErrorID != 0;
	if (!bResult)
	{
		TestBase->NotifySuccess();
		if (pAccountregister == nullptr)
			pAccountregister = new CThostFtdcAccountregisterField();

		std::cout << "�����ѯ����ǩԼ��ϵ��Ӧ" << std::endl;
		std::cout << "�������ڣ� " << pAccountregister->TradeDay << std::endl;
		std::cout << "���б��룺 " << pAccountregister->BankID << std::endl;
		std::cout << "�ڻ���˾���룺 " << pAccountregister->BrokerID << std::endl;
		std::cout << "Ͷ�����˺ţ� " << pAccountregister->AccountID << std::endl;
		std::cout << "֤�����ͣ� " << pAccountregister->IdCardType << std::endl;
		std::cout << "֤�����룺 " << pAccountregister->IdentifiedCardNo << std::endl;
		std::cout << "ǩԼ���ڣ� " << pAccountregister->RegDate << std::endl;
		std::cout << "��Լ���ڣ� " << pAccountregister->OutDate << std::endl;
	}
	else
	{
		TestBase->NotifyFailed();
		std::cerr << "Error Code: " << pRspInfo->ErrorID << ", Error Msg =" << pRspInfo->ErrorMsg << std::endl;
	}
};



class QryAccountregister : public Login
{
public:
	virtual void Run()
	{
		Login::Run();
		RegOnRspQryAccountregister(m_pTdSpi, OnRspQryAccountregister);
		bool loginOK = Login::CheckIsOK();
		if (loginOK)
			SendQryAccountregisterRequest();
		else
		{
			NotifyFailed();
			std::cerr << "��¼ʧ��, �����˺�����..." << std::endl;
		}
	}

private:
	// �����ѯ����ǩԼ��ϵ
	void SendQryAccountregisterRequest()
	{
		CThostFtdcQryAccountregisterField accountregisterField = { 0 };
		strcpy_s(accountregisterField.BrokerID, gBrokerID);
		strcpy_s(accountregisterField.AccountID, gInvesterID);
		strcpy_s(accountregisterField.BankID, "1");
		strcpy_s(accountregisterField.CurrencyID, "CNY");

		int rf = ReqQryAccountregister(m_pTdApi, &accountregisterField, 0);
		if (!rf)
			std::cout << "�����ѯ����ǩԼ��ϵ��Ϣ���ͳɹ�" << std::endl;
		else
		{
			NotifyFailed();
			std::cerr << "�����ѯ����ǩԼ��ϵ��Ϣ����ʧ��" << std::endl;
		}
	}
};

TEST(CtpApiTest, 05QryAccountregister)
{
	QryAccountregister qryAccCtp;
	TestBase = &qryAccCtp;
	qryAccCtp.Run();
	bool isOK = qryAccCtp.CheckIsOK();
	EXPECT_TRUE(isOK);
}