#pragma once
#include "LoginCtp.h"

// 查询报单
class QryOrderCtp : public LoginCtp 
{
public:
	// 查询报单响应
	virtual void OnRspQryOrder(
		CThostFtdcOrderField* pOrder, 
		CThostFtdcRspInfoField* pRspInfo, 
		int nRequestID, 
		bool bIsLast) 
	{
		bool bResult = pRspInfo && pRspInfo->ErrorID != 0;
		if (!bResult) 
		{
			NotifySuccess();
			if (pOrder == nullptr)
				pOrder = new CThostFtdcOrderField();
			else if (pOrder->OrderStatus != THOST_FTDC_OST_AllTraded && pOrder->OrderStatus != THOST_FTDC_OST_Canceled)  // 有报单并没成交
			{
				strcpy_s(m_orderSysID, pOrder->OrderSysID);
			}

			std::cout << "查询报单响应" << std::endl;
			std::cout << "经济公司代码: " << pOrder ->BrokerID << std::endl;
			std::cout << "投资者代码： " << pOrder->InvestorID << std::endl;
			std::cout << "合约代码： " << pOrder->InstrumentID << std::endl;
			std::cout << "订单引用： " << pOrder->OrderRef << std::endl;
			std::cout << "报单编号： " << pOrder->OrderSysID << std::endl;
			std::cout << "报单状态： " << pOrder->OrderStatus << std::endl;
		}
		else 
		{
			NotifyFailed();
			std::cerr << "errCode = " << pRspInfo->ErrorID << ", errMsg =" << pRspInfo->ErrorMsg << std::endl;
		}
	};

	virtual void Run() 
	{
		LoginCtp::Run();
		bool loginOK = LoginCtp::CheckIsOK();
		if (loginOK)
			SendQryOrderRequest();
		else {
			NotifyFailed();
			std::cerr << "登录失败，请检查用户名和密码" << std::endl;
		}
	}

	QryOrderCtp() 
	{
		m_exchange = "SHFE";
	}

	QryOrderCtp(string exchange) 
	{
		m_exchange = exchange;
	}

private:
	void SendQryOrderRequest() 
	{
		CThostFtdcQryOrderField order = { '\0' };
		strcpy_s(order.BrokerID, m_brokerID);
		strcpy_s(order.InvestorID, m_investerID);
		strcpy_s(order.ExchangeID, m_exchange.c_str());

		int rf = m_pTdApi->ReqQryOrder(&order, 0);
		if (!rf) {
			std::cout << "发送查询报单请求成功" << std::endl;
		}
		else {
			NotifyFailed();
			std::cerr << "发送查询报单请求失败" << std::endl;
		}
	}

protected:
	// 默认上期所
	string m_exchange = "SHFE";
	TThostFtdcOrderSysIDType m_orderSysID = {'\0'};
};

TEST(CtpApiTest, 10QryOrder)
{
	QryOrderCtp qryOrdCtp;
	qryOrdCtp.Run();
	bool isOK = qryOrdCtp.CheckIsOK();
	EXPECT_TRUE(isOK);
}
