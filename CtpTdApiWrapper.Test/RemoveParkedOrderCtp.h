#pragma once
#include "ParkedOrderInsertCtp.h"

// 删除预埋单
class RemoveParkedOrderCtp : public ParkedOrderInsertCtp 
{
public:

	// 删除预埋单请求回报
	virtual void OnRspRemoveParkedOrder(
		CThostFtdcRemoveParkedOrderField* pRemoveParkedOrder, 
		CThostFtdcRspInfoField* pRspInfo, 
		int nRequestID, 
		bool bIsLast) 
	{
		bool bResult = pRspInfo && pRspInfo->ErrorID != 0;
		if (!bResult) {
			NotifySuccess();
			std::cout << "删除预埋单请求响应" << std::endl;
			std::cout << "经济公司代码： " << pRemoveParkedOrder->BrokerID << std::endl;
			std::cout << "投资者代码： " << pRemoveParkedOrder->InvestorID << std::endl;
			std::cout << "预埋单编号： " << pRemoveParkedOrder->ParkedOrderID << std::endl;
			std::cout << "投资单元代码： " << pRemoveParkedOrder->InvestUnitID << std::endl;
		}
		else {
			NotifyFailed();
			std::cerr << "errCode = " << pRspInfo->ErrorID << ", errMsg = " << pRspInfo->ErrorMsg << std::endl;
		}
	};

	virtual void Run() 
	{
		ParkedOrderInsertCtp::Run();
		bool orderInsertOK = ParkedOrderInsertCtp::CheckIsOK();
		if (orderInsertOK)
			SendRemoveParkedOrderRequest();
		else {
			NotifyFailed();
			std::cerr << "预埋单失败" << std::endl;
		}
	}

private:
	void SendRemoveParkedOrderRequest() 
	{
		CThostFtdcRemoveParkedOrderField order = { 0 };
		strcpy_s(order.BrokerID, m_brokerID);
		strcpy_s(order.InvestorID, m_investerID);
		strcpy_s(order.ParkedOrderID, m_parkedOrderID);

		int rf = m_pTdApi->ReqRemoveParkedOrder(&order, 0);
		if (!rf) {
			std::cout << "发送删除预埋单请求成功" << std::endl;
		}
		else {
			NotifyFailed();
			std::cerr << "发送删除预埋单请求失败" << std::endl;
		}
	}
};

// 只有在非交易阶段测试才能成功
TEST(CtpApiTest, 09RemoveParkedOrder)
{
	RemoveParkedOrderCtp removeParkedOrderCtp;
	removeParkedOrderCtp.Run();
	bool isOK = removeParkedOrderCtp.CheckIsOK();
	EXPECT_TRUE(isOK);
}
