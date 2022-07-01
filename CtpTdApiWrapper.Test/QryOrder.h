#pragma once
#include "Login.h"

// ��ѯ������Ӧ
void OnRspQryOrder(
	CThostFtdcOrderField* pOrder,
	CThostFtdcRspInfoField* pRspInfo,
	int nRequestID,
	bool bIsLast)
{
	bool bResult = pRspInfo && pRspInfo->ErrorID != 0;
	if (!bResult)
	{
		TestBase->NotifySuccess();
		if (pOrder == nullptr)
			pOrder = new CThostFtdcOrderField();
		else if (pOrder->OrderStatus != THOST_FTDC_OST_AllTraded && pOrder->OrderStatus != THOST_FTDC_OST_Canceled)  // �б�����û�ɽ�
		{
			//strcpy_s(m_orderSysID, pOrder->OrderSysID);
		}

		std::cout << "��ѯ������Ӧ" << std::endl;
		std::cout << "���ù�˾����: " << pOrder->BrokerID << std::endl;
		std::cout << "Ͷ���ߴ��룺 " << pOrder->InvestorID << std::endl;
		std::cout << "��Լ���룺 " << pOrder->InstrumentID << std::endl;
		std::cout << "�������ã� " << pOrder->OrderRef << std::endl;
		std::cout << "������ţ� " << pOrder->OrderSysID << std::endl;
		std::cout << "����״̬�� " << pOrder->OrderStatus << std::endl;
	}
	else
	{
		TestBase->NotifyFailed();
		std::cerr << "errCode = " << pRspInfo->ErrorID << ", errMsg =" << pRspInfo->ErrorMsg << std::endl;
	}
};



// ��ѯ����
class QryOrder : public Login
{
public:
	virtual void Run()
	{
		Login::Run();
		RegOnRspQryOrder(m_pTdSpi, OnRspQryOrder);

		bool loginOK = Login::CheckIsOK();
		if (loginOK)
			SendQryOrderRequest();
		else
		{
			NotifyFailed();
			std::cerr << "��¼ʧ�ܣ������û���������" << std::endl;
		}
	}

	QryOrder()
	{
		m_exchange = "SHFE";
	}

	QryOrder(string exchange)
	{
		m_exchange = exchange;
	}

private:
	void SendQryOrderRequest()
	{
		CThostFtdcQryOrderField order = { '\0' };
		strcpy_s(order.BrokerID, gBrokerID);
		strcpy_s(order.InvestorID, gInvesterID);
		strcpy_s(order.ExchangeID, m_exchange.c_str());

		int rf = ReqQryOrder(m_pTdApi, &order, 0);
		if (!rf)
		{
			std::cout << "���Ͳ�ѯ��������ɹ�" << std::endl;
		}
		else
		{
			NotifyFailed();
			std::cerr << "���Ͳ�ѯ��������ʧ��" << std::endl;
		}
	}

protected:
	// Ĭ��������
	string m_exchange = "SHFE";
	TThostFtdcOrderSysIDType m_orderSysID = { '\0' };
};

TEST(CtpApiTest, 10QryOrder)
{
	QryOrder qryOrdCtp;
	TestBase=&qryOrdCtp;
	qryOrdCtp.Run();
	bool isOK = qryOrdCtp.CheckIsOK();
	EXPECT_TRUE(isOK);
}
