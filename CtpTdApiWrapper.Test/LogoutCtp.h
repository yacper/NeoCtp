#pragma once
#include "Login.h"

class LogoutCtp : public Login
{
public:

	virtual void Run() 
	{
		Login::Run();
		bool isLogin = Login::CheckIsOK();
		if (isLogin)		
			SendLogoutRequest();		
		else {
			NotifyFailed();
			std::cerr << "�û���¼ʧ��" << std::endl;
		}
	}

	virtual void OnRspUserLogout(
		CThostFtdcUserLogoutField* pUserLogout, 
		CThostFtdcRspInfoField* pRspInfo, 
		int nRequestID, 
		bool bIsLast) 
	{
		bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
		if (!bResult) {
			NotifySuccess();
			std::cout << "�ǳ�������Ӧ" << std::endl;
			std::cout << "�û�����" << pUserLogout->UserID << std::endl;
		}
		else 
		{
			NotifyFailed();
			std::cerr << "���ش���--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
		}
	}

	void SendLogoutRequest() 
	{
		CThostFtdcUserLogoutField logoutField = { '\0' };
		strcpy_s(logoutField.BrokerID, gBrokerID);
		strcpy_s(logoutField.UserID, gInvesterID);

		int rf = m_pTdApi->ReqUserLogout(&logoutField, 0);
		if (!rf)
			std::cout << "���͵ǳ�����ɹ�" << std::endl;
		else 
		{
			NotifyFailed();
			std::cerr << "���͵ǳ�����ʧ��" << std::endl;
		}
	}
};

TEST(CtpApiTest, 03Logout)
{
	LogoutCtp logoutCtp;
	logoutCtp.Run();
	bool isOK = logoutCtp.CheckIsOK();
	EXPECT_TRUE(isOK);
}
