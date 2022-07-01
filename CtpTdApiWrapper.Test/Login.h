#pragma once
#include "Connect.h"

void OnRspUserLogin(
	CThostFtdcRspUserLoginField* pRspUserLogin,
	CThostFtdcRspInfoField* pRspInfo,
	int nRequestID,
	bool bIsLast)
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult)
	{
		TestBase->NotifySuccess();
		std::cout << "��¼����ɹ���Ӧ" << std::endl;
		std::cout << "�����գ� " << pRspUserLogin->TradingDay << std::endl;
		std::cout << "��¼�ɹ�ʱ�䣺 " << pRspUserLogin->LoginTime << std::endl;
		std::cout << "����ϵͳ���ƣ� " << pRspUserLogin->SystemName << std::endl;
	}
	else
	{
		TestBase->NotifyFailed();
		std::cerr << "OnRspUserLogin Error--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
	}
}

class Login : public Connect
{
public:
	// ��¼�ص�
	virtual void Run()
	{
		Connect::Run();

		bool initOK = Connect::CheckIsOK();
		if (initOK)
		{
			RegOnRspUserLogin(m_pTdSpi, OnRspUserLogin);
			SendLoginRequest();
		}
		else
		{
			NotifyFailed();
			std::cerr << "��ʼ��ʧ�ܣ���������" << std::endl;
		}
	}

private:

	void SendLoginRequest()
	{
		CThostFtdcReqUserLoginField loginField = { '\0' };
		strcpy_s(loginField.BrokerID, gBrokerID);
		strcpy_s(loginField.UserID, gInvesterID);
		strcpy_s(loginField.Password, gInvesterPassword);

		int rf = ReqUserLogin(m_pTdApi, &loginField, 0);
		if (!rf)
			std::cout << "���͵�¼����ɹ�" << std::endl;
		else
		{
			// ֱ�ӷ���ʧ��
			NotifyFailed();
			std::cout << "���͵�¼����ʧ��" << std::endl;
		}
	}

};

TEST(CtpApiTest, 02LoginCtp)
{
	Login loginCtp;
	TestBase = &loginCtp;
	loginCtp.Run();
	bool isOK = loginCtp.CheckIsOK();
	EXPECT_TRUE(isOK);
}
