#pragma once
#include "InitCtp.h"

class LoginCtp : public InitCtp 
{
public:	
	// 登录回调
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
			std::cout << "登录请求成功响应" << std::endl;
			std::cout << "交易日： " << pRspUserLogin->TradingDay << std::endl;
			std::cout << "登录成功时间： " << pRspUserLogin->LoginTime << std::endl;
			std::cout << "交易系统名称： " << pRspUserLogin->SystemName << std::endl;
		}
		else 
		{
			NotifyFailed();
			std::cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
		}
	}

	virtual void Run() 
	{
		InitCtp::Run();
		bool initOK = InitCtp::CheckIsOK();
		if (initOK)
			SendLoginRequest();		
		else 
		{
			NotifyFailed();
			std::cerr << "初始化失败，请检查网络" << std::endl;
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
			std::cout << "发送登录请求成功" << std::endl;
		else 
		{
			// 直接发送失败
			NotifyFailed();
			std::cout << "发送登录请求失败" << std::endl;
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
