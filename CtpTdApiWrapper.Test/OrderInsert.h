#pragma once
#include<gtest/gtest.h>
#include "SettlementInfoConfirm.h"

// 报单请求（由于在报单请求之前必须确认昨日的结算才能发送报单请求）
class OrderInsert : public SettlementInfoConfirm 
{
public:

	// 报单录入错误回报，当执行ReqOrderInsert后有字段填写不对之类的CTP报错则通过此接口
	virtual void OnErrRtnOrderInsert(
		CThostFtdcInputOrderField* pInputOrder, 
		CThostFtdcRspInfoField* pRspInfo) 
	{
		NotifyFailed();

		bool bResult = pRspInfo && pRspInfo->ErrorID != 0;
		if (!bResult)
		{
			if (pInputOrder == nullptr)
				pInputOrder = new CThostFtdcInputOrderField();

			// 将所有字段打印出来
			std::cerr << "报单请求失败响应，请仔细检查每个字段" << std::endl;
			std::cout << "经纪公司代码: " << pInputOrder->BrokerID << std::endl;
			std::cout << "投资者代码: " << pInputOrder->InvestorID << std::endl;
			std::cout << "合约代码: " << pInputOrder->InstrumentID << std::endl;
			std::cout << "订单引用: " << pInputOrder->OrderRef << std::endl;
			std::cout << "用户代码: " << pInputOrder->UserID << std::endl;
			std::cout << "报价价格条件: " << pInputOrder->OrderPriceType << std::endl;
			std::cout << "买卖方向: " << pInputOrder->Direction << std::endl;
			std::cout << "组合开平标志: " << pInputOrder->CombOffsetFlag << std::endl;
			std::cout << "组合投机套保标志: " << pInputOrder->CombHedgeFlag << std::endl;
			std::cout << "价格: " << pInputOrder->LimitPrice << std::endl;
			std::cout << "数量: " << pInputOrder->VolumeTotalOriginal << std::endl;
			std::cout << "有效类型: " << pInputOrder->TimeCondition << std::endl;
			std::cout << "GDT日期: " << pInputOrder->GTDDate << std::endl;
			std::cout << "成交量类型: " << pInputOrder->VolumeCondition << std::endl;
			std::cout << "最小成交量: " << pInputOrder->MinVolume << std::endl;
			std::cout << "触发条件: " << pInputOrder->ContingentCondition << std::endl;
			std::cout << "止损价: " << pInputOrder->StopPrice << std::endl;
			std::cout << "强平原因: " << pInputOrder->ForceCloseReason << std::endl;
			std::cout << "自动挂起标志: " << pInputOrder->IsAutoSuspend << std::endl;
			std::cout << "业务单元: " << pInputOrder->BusinessUnit << std::endl;
			std::cout << "请求编号: " << pInputOrder->RequestID << std::endl;
			std::cout << "用户强平标志: " << pInputOrder->UserForceClose << std::endl;
			std::cout << "互换单标志: " << pInputOrder->IsSwapOrder << std::endl;
			std::cout << "交易所代码: " << pInputOrder->ExchangeID << std::endl;
			std::cout << "投资单元代码: " << pInputOrder->InvestUnitID << std::endl;
			std::cout << "资金账户: " << pInputOrder->AccountID << std::endl;
			std::cout << "币种代码: " << pInputOrder->CurrencyID << std::endl;
			std::cout << "交易编码: " << pInputOrder->ClientID << std::endl;
			std::cout << "IP地址: " << pInputOrder->IPAddress << std::endl;
			std::cout << "mac 地址: " << pInputOrder->MacAddress << std::endl;
		}
		else
			std::cerr << "OnRspOrderInsert, errCode = " << pRspInfo->ErrorID << ", errMsg =" << pRspInfo->ErrorMsg << std::endl;

	};

	// 当有字段出错时，CTP 报错会通过这个接口回调
	virtual void OnRspOrderInsert(
		CThostFtdcInputOrderField* pInputOrder, 
		CThostFtdcRspInfoField* pRspInfo, 
		int nRequestID, 
		bool bIsLast) 
	{
		NotifyFailed();

		bool bResult = pRspInfo && pRspInfo->ErrorID != 0;
		if (!bResult) 
		{
			if (pInputOrder == nullptr)
				pInputOrder = new CThostFtdcInputOrderField();

			// 将所有字段打印出来
			std::cerr << "报单请求失败响应，请仔细检查每个字段" << std::endl;
			std::cout << "经纪公司代码: " << pInputOrder->BrokerID << std::endl;
			std::cout << "投资者代码: " << pInputOrder->InvestorID << std::endl;
			std::cout << "合约代码: " << pInputOrder->InstrumentID << std::endl;
			std::cout << "订单引用: " << pInputOrder->OrderRef << std::endl;
			std::cout << "用户代码: " << pInputOrder->UserID << std::endl;
			std::cout << "报价价格条件: " << pInputOrder->OrderPriceType << std::endl;
			std::cout << "买卖方向: " << pInputOrder->Direction << std::endl;
			std::cout << "组合开平标志: " << pInputOrder->CombOffsetFlag << std::endl;
			std::cout << "组合投机套保标志: " << pInputOrder->CombHedgeFlag << std::endl;
			std::cout << "价格: " << pInputOrder->LimitPrice << std::endl;
			std::cout << "数量: " << pInputOrder->VolumeTotalOriginal << std::endl;
			std::cout << "有效类型: " << pInputOrder->TimeCondition << std::endl;
			std::cout << "GDT日期: " << pInputOrder->GTDDate << std::endl;
			std::cout << "成交量类型: " << pInputOrder->VolumeCondition << std::endl;
			std::cout << "最小成交量: " << pInputOrder->MinVolume << std::endl;
			std::cout << "触发条件: " << pInputOrder->ContingentCondition << std::endl;
			std::cout << "止损价: " << pInputOrder->StopPrice << std::endl;
			std::cout << "强平原因: " << pInputOrder->ForceCloseReason << std::endl;
			std::cout << "自动挂起标志: " << pInputOrder->IsAutoSuspend << std::endl;
			std::cout << "业务单元: " << pInputOrder->BusinessUnit << std::endl;
			std::cout << "请求编号: " << pInputOrder->RequestID << std::endl;
			std::cout << "用户强平标志: " << pInputOrder->UserForceClose << std::endl;
			std::cout << "互换单标志: " << pInputOrder->IsSwapOrder << std::endl;
			std::cout << "交易所代码: " << pInputOrder->ExchangeID << std::endl;
			std::cout << "投资单元代码: " << pInputOrder->InvestUnitID << std::endl;
			std::cout << "资金账户: " << pInputOrder->AccountID << std::endl;
			std::cout << "币种代码: " << pInputOrder->CurrencyID << std::endl;
			std::cout << "交易编码: " << pInputOrder->ClientID << std::endl;
			std::cout << "IP地址: " << pInputOrder->IPAddress << std::endl;
			std::cout << "mac 地址: " << pInputOrder->MacAddress << std::endl;
		}
		else
			std::cerr << "OnRspOrderInsert, errCode = " << pRspInfo->ErrorID << ", errMsg =" << pRspInfo->ErrorMsg << std::endl;
	};

	// 订单已经提交到交易所成功或失败都会回报（会调用多次）
	virtual void OnRtnOrder(CThostFtdcOrderField* pOrder) 
	{
		if (pOrder->OrderStatus == THOST_FTDC_OST_Canceled)   // 报单失败
		{
			// 打印出错误信息
			NotifyFailed();
			std::cerr << "报单失败：msg = " << pOrder->StatusMsg << std::endl;
		}
		else												  // 报单成功
		{ 
			// 第一次回调
			if (pOrder->OrderSysID != NULL && pOrder->OrderSysID[0] != '\0') {
				NotifySuccess();
				strcpy_s(m_orderSysID, pOrder->OrderSysID);
			}

			// 检测报单状态
			if (pOrder->OrderStatus == THOST_FTDC_OST_AllTraded) { // 报单全部成功
				strcpy_s(m_orderSysID, 0);
			}
			
			// 打印出报单相关的信息
			std::cout << "报单请求成功" << std::endl;
			std::cout << "经济公司代码： " << pOrder->BrokerID << std::endl;
			std::cout << "投资者代码： " << pOrder->InvestorID << std::endl;
			std::cout << "合约代码： " << pOrder->InstrumentID << std::endl;
			std::cout << "报单引用： " << pOrder->OrderRef << std::endl;
			std::cout << "用户代码： " << pOrder->UserID << std::endl;
			std::cout << "报单价格条件： " << pOrder->OrderPriceType << std::endl;
			std::cout << "买卖方向： " << pOrder->Direction << std::endl;
			std::cout << "组合开平标志： " << pOrder->CombOffsetFlag << std::endl;
			std::cout << "组合投机套保标志： " << pOrder->CombHedgeFlag << std::endl;
			std::cout << "价格： " << pOrder->LimitPrice << std::endl;
			std::cout << "数量： " << pOrder->VolumeTotalOriginal << std::endl;
			std::cout << "有效类型： " << pOrder->TimeCondition << std::endl;
			std::cout << "GDT日期： " << pOrder->GTDDate << std::endl;
			std::cout << "成交量类型： " << pOrder->VolumeCondition << std::endl;
			std::cout << "最小成交量： " << pOrder->MinVolume << std::endl;
			std::cout << "结算编号： " << pOrder->SettlementID << std::endl;
			std::cout << "报单编号： " << pOrder->OrderSysID << std::endl;
			std::cout << "报单来源： " << pOrder->OrderSource << std::endl;
			std::cout << "报单状态： " << pOrder->OrderStatus << std::endl;
			std::cout << "报单类型： " << pOrder->OrderType << std::endl;
			std::cout << "今成交数量： " << pOrder->VolumeTraded << std::endl;
			std::cout << "剩余数量： " << pOrder->VolumeTotal << std::endl;
			std::cout << "报单日期： " << pOrder->InsertDate << std::endl;
			std::cout << "委托时间： " << pOrder->InsertTime << std::endl;
			std::cout << "激活时间： " << pOrder->ActiveTime << std::endl;
			std::cout << "挂起时间： " << pOrder->SuspendTime << std::endl;
		}		
	};

	// 交易所订单成交通知，会调用多次
	virtual void OnRtnTrade(CThostFtdcTradeField* pTrade) 
	{
		// 直接将信息打印出
		std::cout << "报单成交通知" << std::endl;
		std::cout << "经济公司代码： " << pTrade ->BrokerID << std::endl;
		std::cout << "投资者代码： " << pTrade->InvestorID << std::endl;
		std::cout << "合约代码： " << pTrade->InstrumentID << std::endl;
		std::cout << "订单引用： " << pTrade->OrderRef << std::endl;
		std::cout << "用户代码： " << pTrade->UserID << std::endl;
		std::cout << "交易所代码： " << pTrade->ExchangeID << std::endl;
		std::cout << "成交编号： " << pTrade->TradeID << std::endl;
		std::cout << "买卖方向： " << pTrade->Direction << std::endl;
		std::cout << "报单编号： " << pTrade->OrderSysID << std::endl;
		std::cout << "会员编号： " << pTrade->ParticipantID << std::endl;
		std::cout << "合约在交易所代码： " << pTrade->ExchangeInstID << std::endl;
		std::cout << "开平标志： " << pTrade->OffsetFlag << std::endl;
		std::cout << "投机套保标志： " << pTrade->HedgeFlag << std::endl;
		std::cout << "价格： " << pTrade->Price << std::endl;
		std::cout << "数量： " << pTrade->Volume << std::endl;
		std::cout << "成交类型： " << pTrade->TradeType << std::endl;
		std::cout << "成交价来源： " << pTrade->PriceSource << std::endl;
		std::cout << "订单本地编号： " << pTrade->OrderLocalID << std::endl;
		std::cout << "结算编号： " << pTrade->SettlementID << std::endl;
		std::cout << "成交来源： " << pTrade->TradeSource << std::endl;
	};

	virtual void Run() 
	{
		SettlementInfoConfirm::Run();
		bool settlementOK = SettlementInfoConfirm::CheckIsOK();
		if (settlementOK) 
			SendOrderInsertRequest();		
		else {
			NotifyFailed();
			std::cerr << "前一日结算失败，请检查账号密码" << std::endl;
		}
	}

	char* GetOrderSysID() 
	{
		return m_orderSysID;
	}

	OrderInsert() 
	{
		strcpy_s(m_instrumentID, "ag2206");
		strcpy_s(m_exchangeID, "SHFE");
		m_price = 5000;
		m_volume = 1;
	}

	OrderInsert(string instrument, string exchange, double price, int volume)
	{
		strcpy_s(m_instrumentID, instrument.c_str());
		strcpy_s(m_exchangeID, exchange.c_str());
		m_price = price;
		m_volume = volume;
	}

private:
	// 发送报单请求
	void SendOrderInsertRequest() 
	{
		CThostFtdcInputOrderField ord = { '\0' };
		strcpy_s(ord.BrokerID, gBrokerID);
		strcpy_s(ord.InvestorID, gInvesterID);
		strcpy_s(ord.ExchangeID, m_exchangeID);
		strcpy_s(ord.InstrumentID, m_instrumentID);
		strcpy_s(ord.UserID, gInvesterID);
		ord.OrderPriceType = THOST_FTDC_OPT_LimitPrice;//限价
		ord.Direction = THOST_FTDC_D_Buy;//买
		ord.CombOffsetFlag[0] = THOST_FTDC_OF_Open;//开
		ord.CombHedgeFlag[0] = THOST_FTDC_HF_Speculation;//投机
		ord.LimitPrice = m_price;
		ord.VolumeTotalOriginal = m_volume;
		ord.TimeCondition = THOST_FTDC_TC_GFD;///当日有效
		ord.VolumeCondition = THOST_FTDC_VC_AV;///任意数量
		ord.MinVolume = 1;
		ord.ContingentCondition = THOST_FTDC_CC_Immediately;
		ord.StopPrice = 0;
		ord.ForceCloseReason = THOST_FTDC_FCC_NotForceClose;
		ord.IsAutoSuspend = 0;

		int rf = m_pTdApi->ReqOrderInsert(&ord, 0);
		if (!rf)
			std::cout << "发送报单请求成功" << std::endl;
		else 
		{
			NotifyFailed();
			std::cerr << "发送报单请求失败" << std::endl;
		}
	}
	
protected:
	char m_instrumentID[7] = "ag2206";
	char m_exchangeID[5] = "SHFE";
	double m_price = 5000;	
	int m_volume = 1;
	TThostFtdcOrderSysIDType m_orderSysID = { '\0' };
};

TEST(CtpApiTest, 06OrderInsert)
{
	OrderInsert orderInsertCtp;
	orderInsertCtp.Run();
	bool isOK = orderInsertCtp.CheckIsOK();
	EXPECT_TRUE(isOK);
}





