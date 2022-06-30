#pragma once
#include "OrderInsertCtp.h"

// 预埋撤单录入 （撤掉已经提交到交易所的报单）
class ParkedOrderActionCtp : public OrderInsertCtp
{
public:
	// 预埋撤单响应
	virtual void OnRspQryParkedOrderAction(
		CThostFtdcParkedOrderActionField* pParkedOrderAction, 
		CThostFtdcRspInfoField* pRspInfo, 
		int nRequestID, 
		bool bIsLast) 
	{
		bool bResult = pRspInfo && pRspInfo->ErrorID != 0;
		if (!bResult) {
			NotifySuccess();
			
			if (!pParkedOrderAction)
				pParkedOrderAction = new CThostFtdcParkedOrderActionField();

			// 预埋撤单成功提交到交易所 && 预埋撤单没有转换成报单
			if (pParkedOrderAction->Status == THOST_FTDC_PAOS_NotSend && pParkedOrderAction->ParkedOrderActionID && pParkedOrderAction->ParkedOrderActionID[0] != '\0') 
			{
				m_parkedOrderActionID = pParkedOrderAction->ParkedOrderActionID;
			}

			std::cout << "预埋撤单响应" << std::endl;			
			std::cout << "经济公司代码： " << pParkedOrderAction->BrokerID << std::endl;
			std::cout << "投资者代码： " << pParkedOrderAction->InvestorID << std::endl;
			std::cout << "报单操作引用： " << pParkedOrderAction->OrderActionRef << std::endl;
			std::cout << "报单引用： " << pParkedOrderAction->OrderRef << std::endl;
			std::cout << "请求编号： " << pParkedOrderAction->RequestID << std::endl;
			std::cout << "交易所代码： " << pParkedOrderAction->ExchangeID << std::endl;
			std::cout << "报单编号： " << pParkedOrderAction->OrderSysID << std::endl;
			std::cout << "预埋单状态： " << pParkedOrderAction->Status << std::endl;
			std::cout << "错误信息： " << pParkedOrderAction->ErrorMsg << std::endl;
		}
		else {
			NotifyFailed();
			std::cerr << "errCode =" << pRspInfo->ErrorID << ", errMsg =" << pRspInfo->ErrorMsg << std::endl;
		}
	};

	virtual void Run() 
	{
		OrderInsertCtp::Run();
		bool orderInsertOK = OrderInsertCtp::CheckIsOK();
		if (orderInsertOK)
			SendParkedOrderActionRequest();
		else {
			NotifyFailed();
			std::cerr << "报单失败" << std::endl;
		}
	}

private:
	void SendParkedOrderActionRequest() 
	{
		CThostFtdcParkedOrderActionField order = { 0 };
		strcpy_s(order.BrokerID, m_brokerID);
		strcpy_s(order.InvestorID, m_investerID);
		strcpy_s(order.ExchangeID, m_exchangeID);
		strcpy_s(order.OrderSysID, m_orderSysID);
		strcpy_s(order.UserID, m_investerID);
		strcpy_s(order.InstrumentID, m_instrumentID);
		order.ActionFlag = THOST_FTDC_AF_Delete;

		int rf = m_pTdApi->ReqParkedOrderAction(&order, 0);
		if (!rf) 
			std::cout << "发送预埋撤单请求成功" << std::endl;
		else {
			NotifyFailed();
			std::cerr << "发送预埋撤单请求失败" << std::endl;
		}
	}

protected:
	string m_parkedOrderActionID = { '\0' };
	
};

// 只能在非交易时段才会成功
TEST(CtpApiTest, 11ParkedOrderAction)
{
	ParkedOrderActionCtp parkedOrderAction;
	parkedOrderAction.Run();
	bool isOK = parkedOrderAction.CheckIsOK();
	EXPECT_TRUE(isOK);
}
 