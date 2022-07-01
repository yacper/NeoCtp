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
		std::cout << "登录请求成功响应" << std::endl;
		std::cout << "交易日： " << pRspUserLogin->TradingDay << std::endl;
		std::cout << "登录成功时间： " << pRspUserLogin->LoginTime << std::endl;
		std::cout << "交易系统名称： " << pRspUserLogin->SystemName << std::endl;
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
	// 登录回调
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
			std::cerr << "初始化失败，请检查网络" << std::endl;
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
	Login loginCtp;
	TestBase = &loginCtp;
	loginCtp.Run();
	bool isOK = loginCtp.CheckIsOK();
	EXPECT_TRUE(isOK);
}
