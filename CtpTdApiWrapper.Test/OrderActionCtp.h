#pragma once
#include<string>
#include "OrderInsert.h"

// 撤单操作（只能先报单，然后再撤单）
class OrderActionCtp : public OrderInsert 
{
public:
	OrderActionCtp(std::string instrument, std::string exchange, double price, int volume):OrderInsert(instrument, exchange, price, volume)
	{

	}

	// 报单操作请求响应，当执行ReqOrderAction后有字段填写不对之类的CTP报错则通过此接口返回
	virtual void OnRspOrderAction(
		CThostFtdcInputOrderActionField* pInputOrderAction, 
		CThostFtdcRspInfoField* pRspInfo, 
		int nRequestID, 
		bool bIsLast) 
	{
		// 打印出失败的信息
		NotifyFailed();
		std::cerr << "撤单请求失败，请仔细检查撤单请求的参数" << std::endl;
		std::cerr << "错误码：" << pRspInfo->ErrorID << "，错误消息：" << pRspInfo->ErrorMsg << std::endl;

	};

	// 报单操作错误回报，当执行ReqOrderAction后有字段填写不对之类的CTP报错则通过此接口返回
	virtual void OnErrRtnOrderAction(
		CThostFtdcOrderActionField* pOrderAction, 
		CThostFtdcRspInfoField* pRspInfo) 
	{
		// 打印出失败的信息
		NotifyFailed();
		std::cerr << "撤单请求失败，请仔细检查撤单请求的参数" << std::endl;
		std::cerr << "错误码：" << pRspInfo->ErrorID << "，错误消息：" << pRspInfo->ErrorMsg << std::endl;

	};

	// 撤单成功后回调（疑问这里会不会覆盖父类调用 测试）
	virtual void OnRtnOrder(CThostFtdcOrderField* pOrder) 
	{
		NotifySuccess();
		std::cout << "撤单请求成功通知" << std::endl;
	};

	virtual void Run() 
	{
		OrderInsert::Run();
		bool orderInsertOK = OrderInsert::CheckIsOK();
		if (orderInsertOK)
			SendOrderActionRequest();
		else {
			NotifyFailed();
			std::cerr << "报单请求失败" << std::endl;
		}
	}

private:
	void SendOrderActionRequest() 
	{
		CThostFtdcInputOrderActionField action = { '\0' };
		strcpy_s(action.BrokerID, gBrokerID);
		strcpy_s(action.InvestorID, gInvesterID);
		strcpy_s(action.UserID, gInvesterID);
		strcpy_s(action.OrderSysID, m_orderSysID);
		strcpy_s(action.ExchangeID, m_exchangeID);
		strcpy_s(action.InstrumentID, m_instrumentID);
		action.ActionFlag = THOST_FTDC_AF_Delete;

		int rf = m_pTdApi->ReqOrderAction(&action, 0);
		if (!rf) {
			std::cout << "发送撤单请求成功" << std::endl;
		}
		else {
			NotifyFailed();
			std::cerr << "发送撤单请求失败" << std::endl;
		}
	}

};

TEST(CtpApiTest, 07OrderAction)
{
	OrderActionCtp ordActionCtp = OrderActionCtp("ag2206", "SHFE", 5000, 2);
	ordActionCtp.Run();
	bool isOK = ordActionCtp.CheckIsOK();
	EXPECT_TRUE(isOK);
}
