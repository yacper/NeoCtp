#pragma once
#include "Login.h"

// 查询预埋单
class QryParkedOrderCtp : public Login 
{
public:

	// 查询埋单回调
	virtual void OnRspQryParkedOrder(
		CThostFtdcParkedOrderField* pParkedOrder, 
		CThostFtdcRspInfoField* pRspInfo, 
		int nRequestID, 
		bool bIsLast) 
	{
		bool bResult = pRspInfo && pRspInfo->ErrorID != 0;
		if (!bResult) 
		{
			NotifySuccess();

			if (!pParkedOrder)
				pParkedOrder = new CThostFtdcParkedOrderField();

			// 预埋单号存在 && 预埋单的状态为未发送
			if (pParkedOrder->ParkedOrderID && pParkedOrder->ParkedOrderID[0] != '\0' && pParkedOrder->Status == THOST_FTDC_PAOS_NotSend)  
			{
				m_parkedOrderID = pParkedOrder->ParkedOrderID;
			}
			std::cout << "发送查询预埋单响应" << std::endl;
			std::cout << "经纪公司代码: " << pParkedOrder ->BrokerID << std::endl;
			std::cout << "投资者代码: " << pParkedOrder->InvestorID << std::endl;
			std::cout << "合约代码: " << pParkedOrder->InstrumentID << std::endl;
			std::cout << "报单引用: " << pParkedOrder->OrderRef << std::endl;
			std::cout << "交易所代码: " << pParkedOrder->ExchangeID << std::endl;
			std::cout << "预埋报单编号: " << pParkedOrder->ParkedOrderID << std::endl;
			std::cout << "预埋单状态: " << pParkedOrder->Status << std::endl;
			std::cout << "错误信息: " << pParkedOrder->ErrorMsg << std::endl;
		}
		else 
		{
			NotifyFailed();
			std::cerr << "errCode: " << pRspInfo ->ErrorID << ", errMsg =" << pRspInfo->ErrorMsg << std::endl;
		}
	};

	virtual void Run() 
	{
		Login::Run();
		bool loginOK = Login::CheckIsOK();
		if (loginOK)
			SendQryParkedOrderRequest();
		else 
		{
			NotifyFailed();
			std::cout << "登录失败，请检查用户名和密码" << std::endl;
		}
	}

private:
	void SendQryParkedOrderRequest() 
	{
		CThostFtdcQryParkedOrderField order = { '\0' };
		strcpy_s(order.BrokerID, gBrokerID);
		strcpy_s(order.InvestorID, gInvesterID);
		strcpy_s(order.InstrumentID, m_instrument.c_str());
		strcpy_s(order.ExchangeID, m_exchange.c_str());

		int rf = m_pTdApi->ReqQryParkedOrder(&order, 0);
		if (!rf)
			std::cout << "发送查询预埋单成功" << std::endl;		
		else 
		{
			NotifyFailed();
			std::cerr << "发送查询预埋单失败" << std::endl;
		}
	}

protected:
	std::string m_instrument = "ag2206";
	std::string m_exchange = "SHFE";
	std::string m_parkedOrderID = {'\0'};
};


TEST(CtpApiTest, 12QryParkedOrder)
{
	QryParkedOrderCtp qryParkedOrderCtp;
	qryParkedOrderCtp.Run();
	bool isOK = qryParkedOrderCtp.CheckIsOK();
	
}