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
			std::cerr << "用户登录失败" << std::endl;
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
			std::cout << "登出请求响应" << std::endl;
			std::cout << "用户代码" << pUserLogout->UserID << std::endl;
		}
		else 
		{
			NotifyFailed();
			std::cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
		}
	}

	void SendLogoutRequest() 
	{
		CThostFtdcUserLogoutField logoutField = { '\0' };
		strcpy_s(logoutField.BrokerID, gBrokerID);
		strcpy_s(logoutField.UserID, gInvesterID);

		int rf = m_pTdApi->ReqUserLogout(&logoutField, 0);
		if (!rf)
			std::cout << "发送登出请求成功" << std::endl;
		else 
		{
			NotifyFailed();
			std::cerr << "发送登出请求失败" << std::endl;
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
