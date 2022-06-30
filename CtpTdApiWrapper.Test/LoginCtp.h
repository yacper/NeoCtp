#pragma once
#include "Connect.h"

class LoginCtp : public Connect 
{
public:	
	// ��¼�ص�
	virtual void OnRspUserLogin(
		CThostFtdcRspUserLoginField* pRspUserLogin, 
		CThostFtdcRspInfoField* pRspInfo, 
		int nRequestID, 
		bool bIsLast)
	{
		bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
		if (!bResult) 
		{
			NotifySuccess();
			std::cout << "��¼����ɹ���Ӧ" << std::endl;
			std::cout << "�����գ� " << pRspUserLogin->TradingDay << std::endl;
			std::cout << "��¼�ɹ�ʱ�䣺 " << pRspUserLogin->LoginTime << std::endl;
			std::cout << "����ϵͳ���ƣ� " << pRspUserLogin->SystemName << std::endl;
		}
		else 
		{
			NotifyFailed();
			std::cerr << "���ش���--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
		}
	}

	virtual void Run() 
	{
		Connect::Run();
		bool initOK = Connect::CheckIsOK();
		if (initOK)
			SendLoginRequest();		
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
		strcpy_s(loginField.BrokerID, m_brokerID);
		strcpy_s(loginField.UserID, m_investerID);
		strcpy_s(loginField.Password, m_investerPassword);

		int rf = m_pTdApi->ReqUserLogin(&loginField, 0);
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
	LoginCtp loginCtp;
	loginCtp.Run();
	bool isOK = loginCtp.CheckIsOK();
	EXPECT_TRUE(isOK);
}
