#pragma once
#include <gtest/gtest.h>
#include "LoginCtp.h"

class QryAccountregisterCtp : public LoginCtp 
{
public:
	virtual void OnRspQryAccountregister(
		CThostFtdcAccountregisterField* pAccountregister, 
		CThostFtdcRspInfoField* pRspInfo, 
		int nRequestID, 
		bool bIsLast) 
	{
		bool bResult = pRspInfo && pRspInfo->ErrorID != 0;
		if (!bResult) 
		{
			NotifySuccess();
			if (pAccountregister == nullptr)
				pAccountregister = new CThostFtdcAccountregisterField();

			std::cout << "�����ѯ����ǩԼ��ϵ��Ӧ" << std::endl;
			std::cout << "�������ڣ� " << pAccountregister ->TradeDay << std::endl;
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
			NotifyFailed();
			std::cerr << "Error Code: " << pRspInfo->ErrorID << ", Error Msg =" << pRspInfo->ErrorMsg << std::endl;
		}
	};

	virtual void Run() 
	{
		LoginCtp::Run();
		bool loginOK = LoginCtp::CheckIsOK();
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
		strcpy_s(accountregisterField.BrokerID, m_brokerID);
		strcpy_s(accountregisterField.AccountID, m_investerID);
		strcpy_s(accountregisterField.BankID, "1");
		strcpy_s(accountregisterField.CurrencyID, "CNY");

		int rf = m_pTdApi->ReqQryAccountregister(&accountregisterField, 0);
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
	QryAccountregisterCtp qryAccCtp;
	qryAccCtp.Run();
	bool isOK = qryAccCtp.CheckIsOK();
	EXPECT_TRUE(isOK);
}