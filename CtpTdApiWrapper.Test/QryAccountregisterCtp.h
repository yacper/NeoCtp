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

			std::cout << "请求查询银期签约关系响应" << std::endl;
			std::cout << "交易日期： " << pAccountregister ->TradeDay << std::endl;
			std::cout << "银行编码： " << pAccountregister->BankID << std::endl;
			std::cout << "期货公司编码： " << pAccountregister->BrokerID << std::endl;
			std::cout << "投资者账号： " << pAccountregister->AccountID << std::endl;
			std::cout << "证件类型： " << pAccountregister->IdCardType << std::endl;
			std::cout << "证件号码： " << pAccountregister->IdentifiedCardNo << std::endl;
			std::cout << "签约日期： " << pAccountregister->RegDate << std::endl;
			std::cout << "解约日期： " << pAccountregister->OutDate << std::endl;
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
			std::cerr << "登录失败, 请检查账号密码..." << std::endl;
		}
	}

private:
	// 请求查询银期签约关系
	void SendQryAccountregisterRequest() 
	{
		CThostFtdcQryAccountregisterField accountregisterField = { 0 };
		strcpy_s(accountregisterField.BrokerID, m_brokerID);
		strcpy_s(accountregisterField.AccountID, m_investerID);
		strcpy_s(accountregisterField.BankID, "1");
		strcpy_s(accountregisterField.CurrencyID, "CNY");

		int rf = m_pTdApi->ReqQryAccountregister(&accountregisterField, 0);
		if (!rf)
			std::cout << "请求查询银期签约关系消息发送成功" << std::endl;
		else 
		{
			NotifyFailed();
			std::cerr << "请求查询银期签约关系消息发送失败" << std::endl;
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