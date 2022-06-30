#pragma once
#include "LoginCtp.h"

// ��ѯԤ��
class QryParkedOrderCtp : public LoginCtp 
{
public:

	// ��ѯ�񵥻ص�
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

			// Ԥ�񵥺Ŵ��� && Ԥ�񵥵�״̬Ϊδ����
			if (pParkedOrder->ParkedOrderID && pParkedOrder->ParkedOrderID[0] != '\0' && pParkedOrder->Status == THOST_FTDC_PAOS_NotSend)  
			{
				m_parkedOrderID = pParkedOrder->ParkedOrderID;
			}
			std::cout << "���Ͳ�ѯԤ����Ӧ" << std::endl;
			std::cout << "���͹�˾����: " << pParkedOrder ->BrokerID << std::endl;
			std::cout << "Ͷ���ߴ���: " << pParkedOrder->InvestorID << std::endl;
			std::cout << "��Լ����: " << pParkedOrder->InstrumentID << std::endl;
			std::cout << "��������: " << pParkedOrder->OrderRef << std::endl;
			std::cout << "����������: " << pParkedOrder->ExchangeID << std::endl;
			std::cout << "Ԥ�񱨵����: " << pParkedOrder->ParkedOrderID << std::endl;
			std::cout << "Ԥ��״̬: " << pParkedOrder->Status << std::endl;
			std::cout << "������Ϣ: " << pParkedOrder->ErrorMsg << std::endl;
		}
		else 
		{
			NotifyFailed();
			std::cerr << "errCode: " << pRspInfo ->ErrorID << ", errMsg =" << pRspInfo->ErrorMsg << std::endl;
		}
	};

	virtual void Run() 
	{
		LoginCtp::Run();
		bool loginOK = LoginCtp::CheckIsOK();
		if (loginOK)
			SendQryParkedOrderRequest();
		else 
		{
			NotifyFailed();
			std::cout << "��¼ʧ�ܣ������û���������" << std::endl;
		}
	}

private:
	void SendQryParkedOrderRequest() 
	{
		CThostFtdcQryParkedOrderField order = { '\0' };
		strcpy_s(order.BrokerID, m_brokerID);
		strcpy_s(order.InvestorID, m_investerID);
		strcpy_s(order.InstrumentID, m_instrument.c_str());
		strcpy_s(order.ExchangeID, m_exchange.c_str());

		int rf = m_pTdApi->ReqQryParkedOrder(&order, 0);
		if (!rf)
			std::cout << "���Ͳ�ѯԤ�񵥳ɹ�" << std::endl;		
		else 
		{
			NotifyFailed();
			std::cerr << "���Ͳ�ѯԤ��ʧ��" << std::endl;
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