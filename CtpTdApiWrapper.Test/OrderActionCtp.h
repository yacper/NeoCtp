#pragma once
#include<string>
#include "OrderInsert.h"

// ����������ֻ���ȱ�����Ȼ���ٳ�����
class OrderActionCtp : public OrderInsert 
{
public:
	OrderActionCtp(std::string instrument, std::string exchange, double price, int volume):OrderInsert(instrument, exchange, price, volume)
	{

	}

	// ��������������Ӧ����ִ��ReqOrderAction�����ֶ���д����֮���CTP������ͨ���˽ӿڷ���
	virtual void OnRspOrderAction(
		CThostFtdcInputOrderActionField* pInputOrderAction, 
		CThostFtdcRspInfoField* pRspInfo, 
		int nRequestID, 
		bool bIsLast) 
	{
		// ��ӡ��ʧ�ܵ���Ϣ
		NotifyFailed();
		std::cerr << "��������ʧ�ܣ�����ϸ��鳷������Ĳ���" << std::endl;
		std::cerr << "�����룺" << pRspInfo->ErrorID << "��������Ϣ��" << pRspInfo->ErrorMsg << std::endl;

	};

	// ������������ر�����ִ��ReqOrderAction�����ֶ���д����֮���CTP������ͨ���˽ӿڷ���
	virtual void OnErrRtnOrderAction(
		CThostFtdcOrderActionField* pOrderAction, 
		CThostFtdcRspInfoField* pRspInfo) 
	{
		// ��ӡ��ʧ�ܵ���Ϣ
		NotifyFailed();
		std::cerr << "��������ʧ�ܣ�����ϸ��鳷������Ĳ���" << std::endl;
		std::cerr << "�����룺" << pRspInfo->ErrorID << "��������Ϣ��" << pRspInfo->ErrorMsg << std::endl;

	};

	// �����ɹ���ص�����������᲻�Ḳ�Ǹ������ ���ԣ�
	virtual void OnRtnOrder(CThostFtdcOrderField* pOrder) 
	{
		NotifySuccess();
		std::cout << "��������ɹ�֪ͨ" << std::endl;
	};

	virtual void Run() 
	{
		OrderInsert::Run();
		bool orderInsertOK = OrderInsert::CheckIsOK();
		if (orderInsertOK)
			SendOrderActionRequest();
		else {
			NotifyFailed();
			std::cerr << "��������ʧ��" << std::endl;
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
			std::cout << "���ͳ�������ɹ�" << std::endl;
		}
		else {
			NotifyFailed();
			std::cerr << "���ͳ�������ʧ��" << std::endl;
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
