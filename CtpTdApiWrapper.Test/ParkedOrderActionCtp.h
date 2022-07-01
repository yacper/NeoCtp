#pragma once
#include "OrderInsertCtp.h"

// Ԥ�񳷵�¼�� �������Ѿ��ύ���������ı�����
class ParkedOrderActionCtp : public OrderInsertCtp
{
public:
	// Ԥ�񳷵���Ӧ
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

			// Ԥ�񳷵��ɹ��ύ�������� && Ԥ�񳷵�û��ת���ɱ���
			if (pParkedOrderAction->Status == THOST_FTDC_PAOS_NotSend && pParkedOrderAction->ParkedOrderActionID && pParkedOrderAction->ParkedOrderActionID[0] != '\0') 
			{
				m_parkedOrderActionID = pParkedOrderAction->ParkedOrderActionID;
			}

			std::cout << "Ԥ�񳷵���Ӧ" << std::endl;			
			std::cout << "���ù�˾���룺 " << pParkedOrderAction->BrokerID << std::endl;
			std::cout << "Ͷ���ߴ��룺 " << pParkedOrderAction->InvestorID << std::endl;
			std::cout << "�����������ã� " << pParkedOrderAction->OrderActionRef << std::endl;
			std::cout << "�������ã� " << pParkedOrderAction->OrderRef << std::endl;
			std::cout << "�����ţ� " << pParkedOrderAction->RequestID << std::endl;
			std::cout << "���������룺 " << pParkedOrderAction->ExchangeID << std::endl;
			std::cout << "������ţ� " << pParkedOrderAction->OrderSysID << std::endl;
			std::cout << "Ԥ��״̬�� " << pParkedOrderAction->Status << std::endl;
			std::cout << "������Ϣ�� " << pParkedOrderAction->ErrorMsg << std::endl;
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
			std::cerr << "����ʧ��" << std::endl;
		}
	}

private:
	void SendParkedOrderActionRequest() 
	{
		CThostFtdcParkedOrderActionField order = { 0 };
		strcpy_s(order.BrokerID, gBrokerID);
		strcpy_s(order.InvestorID, gInvesterID);
		strcpy_s(order.ExchangeID, m_exchangeID);
		strcpy_s(order.OrderSysID, m_orderSysID);
		strcpy_s(order.UserID, gInvesterID);
		strcpy_s(order.InstrumentID, m_instrumentID);
		order.ActionFlag = THOST_FTDC_AF_Delete;

		int rf = m_pTdApi->ReqParkedOrderAction(&order, 0);
		if (!rf) 
			std::cout << "����Ԥ�񳷵�����ɹ�" << std::endl;
		else {
			NotifyFailed();
			std::cerr << "����Ԥ�񳷵�����ʧ��" << std::endl;
		}
	}

protected:
	string m_parkedOrderActionID = { '\0' };
	
};

// ֻ���ڷǽ���ʱ�βŻ�ɹ�
TEST(CtpApiTest, 11ParkedOrderAction)
{
	ParkedOrderActionCtp parkedOrderAction;
	parkedOrderAction.Run();
	bool isOK = parkedOrderAction.CheckIsOK();
	EXPECT_TRUE(isOK);
}
 