#pragma once
#include "Login.h"

// 预埋单。
// TODO：1.检测预埋单的状态，已发送/未发送 
//		 2.已经发送状态后预埋单会走报单流程吗？ 
//		 3.预埋单撤单是否能撤已发送的订单/撤未发送订单
class ParkedOrderInsertCtp : public Login 
{
public:

	// 报单录入失败
	virtual void OnRspOrderInsert(
		CThostFtdcInputOrderField* pInputOrder, 
		CThostFtdcRspInfoField* pRspInfo, 
		int nRequestID, 
		bool bIsLast) 
	{
		int a = 100;
	};

	// 报单录入失败
	virtual void OnErrRtnOrderInsert(
		CThostFtdcInputOrderField* pInputOrder, 
		CThostFtdcRspInfoField* pRspInfo) 
	{
		int a = 100;
	};

	// 报单录入成功回调
	virtual void OnRtnOrder(CThostFtdcOrderField* pOrder) 
	{
		int a = 100;
	};

	// 预埋单响应
	virtual void OnRspParkedOrderInsert(
		CThostFtdcParkedOrderField* pParkedOrder, 
		CThostFtdcRspInfoField* pRspInfo, 
		int nRequestID, 
		bool bIsLast) 
	{
		bool bResult = pRspInfo && pRspInfo->ErrorID != 0;
		if (!bResult) {
			NotifySuccess();
			strcpy_s(m_parkedOrderID, pParkedOrder->ParkedOrderID);
			std::cout << "预埋单请求响应" << std::endl;
			std::cout << "经济公司代码： " << pParkedOrder->BrokerID << std::endl;
			std::cout << "投资者代码： " << pParkedOrder->InvestorID << std::endl;
			std::cout << "合约代码： " << pParkedOrder->InstrumentID << std::endl;
			std::cout << "预埋单状态： " << pParkedOrder->Status << std::endl;
		}
		else {
			NotifyFailed();
			std::cerr << "errCode =" << pRspInfo->ErrorID << ", errMsg = " << pRspInfo->ErrorMsg << std::endl;
 		}
	};

	virtual void Run() 
	{
		Login::Run();
		bool loginOK = Login::CheckIsOK();
		if (loginOK)
			SendParkedOrderInsertRequest();
		else {
			NotifyFailed();
			std::cerr << "用户登录失败，请检查账号密码" << std::endl;
		}
	}

private:
	void SendParkedOrderInsertRequest() 
	{
		CThostFtdcParkedOrderField order = { 0 };
		strcpy(order.BrokerID, gBrokerID);
		strcpy(order.InvestorID, gInvesterID);
		strcpy(order.InstrumentID, m_instrumentID);
		strcpy(order.UserID, gInvesterID);
		strcpy(order.ExchangeID, m_exchangeID);
		order.OrderPriceType = THOST_FTDC_OPT_LimitPrice;
		order.Direction = THOST_FTDC_D_Buy;
		strcpy(order.CombOffsetFlag, "0");
		strcpy(order.CombHedgeFlag, "1");
		order.LimitPrice = m_price;
		order.VolumeTotalOriginal = m_volume;
		order.TimeCondition = THOST_FTDC_TC_GFD;
		strcpy(order.GTDDate, "");
		order.VolumeCondition = THOST_FTDC_VC_CV;
		order.MinVolume = 0;
		order.ContingentCondition = THOST_FTDC_CC_Immediately;
		order.StopPrice = 0;
		order.ForceCloseReason = THOST_FTDC_FCC_NotForceClose;
		order.IsAutoSuspend = 0;

		int rf = m_pTdApi->ReqParkedOrderInsert(&order, 0);
		if (!rf) 
			std::cout << "发送预埋单请求成功" << std::endl;		
		else {
			NotifyFailed();
			std::cerr << "发送预埋单请求失败" << std::endl;
		}
	}

protected:

	char m_instrumentID[7] = "ag2206";
	char m_exchangeID[5] = "SHFE";
	double m_price = 5000;
	int m_volume = 1;
	TThostFtdcParkedOrderIDType m_parkedOrderID = { '\0' };
};

// 只能在非交易时段可以测试成功
TEST(CtpApiTest, 08ParkedOrderInsert)
{
	ParkedOrderInsertCtp parkedOrderCtp;
	parkedOrderCtp.Run();
	bool isOK = parkedOrderCtp.CheckIsOK();
	EXPECT_TRUE(isOK);
  
}
