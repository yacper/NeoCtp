#pragma once
#include "ParkedOrderActionCtp.h"

// 撤销没有成交的预埋撤单请求（只有在非交易时段才起作用）
class RemoveParkedOrderActionCtp: public ParkedOrderActionCtp
{
public:

	// 撤销预埋撤单响应
	virtual void OnRspRemoveParkedOrderAction(
		CThostFtdcRemoveParkedOrderActionField* pRemoveParkedOrderAction, 
		CThostFtdcRspInfoField* pRspInfo, 
		int nRequestID, 
		bool bIsLast) 
	{
		bool bResult = pRspInfo && pRspInfo->ErrorID != 0;
		if (!bResult) {
			NotifySuccess();
			if (!pRemoveParkedOrderAction)
				pRemoveParkedOrderAction = new CThostFtdcRemoveParkedOrderActionField();

			std::cout << "撤销预埋撤单响应" << std::endl;
			std::cout << "经济公司代码： " << pRemoveParkedOrderAction ->BrokerID << std::endl;
			std::cout << "投资者代码： " << pRemoveParkedOrderAction->InvestorID << std::endl;
			std::cout << "预埋撤单编号： " << pRemoveParkedOrderAction->ParkedOrderActionID << std::endl;
			std::cout << "投资单元编码： " << pRemoveParkedOrderAction->InvestUnitID << std::endl;
		}
		else 
		{
			NotifyFailed();
			std::cerr << "errCode = " << pRspInfo->ErrorID << ", errMsg = " << pRspInfo->ErrorMsg << std::endl;
		}
	};

	virtual void Run() 
	{
		ParkedOrderActionCtp::Run();
		bool orderActionOK = ParkedOrderActionCtp::CheckIsOK();
		if (orderActionOK)
			SendRemoveParkedOrderActionRequest();
		else
		{
			NotifyFailed();
			std::cerr << "预埋撤单请求失败" << std::endl;
		}
	}

private:
	// 发送预埋撤单删除请求
	void SendRemoveParkedOrderActionRequest() 
	{
		CThostFtdcRemoveParkedOrderActionField orderAction = { 0 };
		strcpy_s(orderAction.BrokerID, gBrokerID);
		strcpy_s(orderAction.InvestorID, gInvesterID);
		strcpy_s(orderAction.ParkedOrderActionID, m_parkedOrderActionID.c_str());

		int rf = m_pTdApi->ReqRemoveParkedOrderAction(&orderAction, 0);
		if (!rf) {
			std::cout << "发送预埋撤单删除请求成功" << std::endl;
		}
		else {
			NotifyFailed();
			std::cerr << "发送预埋撤单删除请求失败" << std::endl;
		}
	}
};

// 只能在非交易时段才会成功
TEST(CtpApiTest, 13RemoveParkedOrderAction)
{
	RemoveParkedOrderActionCtp removeParkedOrderAction;
	removeParkedOrderAction.Run();
	bool isOK = removeParkedOrderAction.CheckIsOK();
	EXPECT_TRUE(isOK);
}
