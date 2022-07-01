#pragma once
#include<gtest/gtest.h>
#include "SettlementInfoConfirmCtp.h"

// �������������ڱ�������֮ǰ����ȷ�����յĽ�����ܷ��ͱ�������
class OrderInsertCtp : public SettlementInfoConfirmCtp 
{
public:

	// ����¼�����ر�����ִ��ReqOrderInsert�����ֶ���д����֮���CTP������ͨ���˽ӿ�
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

			// �������ֶδ�ӡ����
			std::cerr << "��������ʧ����Ӧ������ϸ���ÿ���ֶ�" << std::endl;
			std::cout << "���͹�˾����: " << pInputOrder->BrokerID << std::endl;
			std::cout << "Ͷ���ߴ���: " << pInputOrder->InvestorID << std::endl;
			std::cout << "��Լ����: " << pInputOrder->InstrumentID << std::endl;
			std::cout << "��������: " << pInputOrder->OrderRef << std::endl;
			std::cout << "�û�����: " << pInputOrder->UserID << std::endl;
			std::cout << "���ۼ۸�����: " << pInputOrder->OrderPriceType << std::endl;
			std::cout << "��������: " << pInputOrder->Direction << std::endl;
			std::cout << "��Ͽ�ƽ��־: " << pInputOrder->CombOffsetFlag << std::endl;
			std::cout << "���Ͷ���ױ���־: " << pInputOrder->CombHedgeFlag << std::endl;
			std::cout << "�۸�: " << pInputOrder->LimitPrice << std::endl;
			std::cout << "����: " << pInputOrder->VolumeTotalOriginal << std::endl;
			std::cout << "��Ч����: " << pInputOrder->TimeCondition << std::endl;
			std::cout << "GDT����: " << pInputOrder->GTDDate << std::endl;
			std::cout << "�ɽ�������: " << pInputOrder->VolumeCondition << std::endl;
			std::cout << "��С�ɽ���: " << pInputOrder->MinVolume << std::endl;
			std::cout << "��������: " << pInputOrder->ContingentCondition << std::endl;
			std::cout << "ֹ���: " << pInputOrder->StopPrice << std::endl;
			std::cout << "ǿƽԭ��: " << pInputOrder->ForceCloseReason << std::endl;
			std::cout << "�Զ������־: " << pInputOrder->IsAutoSuspend << std::endl;
			std::cout << "ҵ��Ԫ: " << pInputOrder->BusinessUnit << std::endl;
			std::cout << "������: " << pInputOrder->RequestID << std::endl;
			std::cout << "�û�ǿƽ��־: " << pInputOrder->UserForceClose << std::endl;
			std::cout << "��������־: " << pInputOrder->IsSwapOrder << std::endl;
			std::cout << "����������: " << pInputOrder->ExchangeID << std::endl;
			std::cout << "Ͷ�ʵ�Ԫ����: " << pInputOrder->InvestUnitID << std::endl;
			std::cout << "�ʽ��˻�: " << pInputOrder->AccountID << std::endl;
			std::cout << "���ִ���: " << pInputOrder->CurrencyID << std::endl;
			std::cout << "���ױ���: " << pInputOrder->ClientID << std::endl;
			std::cout << "IP��ַ: " << pInputOrder->IPAddress << std::endl;
			std::cout << "mac ��ַ: " << pInputOrder->MacAddress << std::endl;
		}
		else
			std::cerr << "OnRspOrderInsert, errCode = " << pRspInfo->ErrorID << ", errMsg =" << pRspInfo->ErrorMsg << std::endl;

	};

	// �����ֶγ���ʱ��CTP �����ͨ������ӿڻص�
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

			// �������ֶδ�ӡ����
			std::cerr << "��������ʧ����Ӧ������ϸ���ÿ���ֶ�" << std::endl;
			std::cout << "���͹�˾����: " << pInputOrder->BrokerID << std::endl;
			std::cout << "Ͷ���ߴ���: " << pInputOrder->InvestorID << std::endl;
			std::cout << "��Լ����: " << pInputOrder->InstrumentID << std::endl;
			std::cout << "��������: " << pInputOrder->OrderRef << std::endl;
			std::cout << "�û�����: " << pInputOrder->UserID << std::endl;
			std::cout << "���ۼ۸�����: " << pInputOrder->OrderPriceType << std::endl;
			std::cout << "��������: " << pInputOrder->Direction << std::endl;
			std::cout << "��Ͽ�ƽ��־: " << pInputOrder->CombOffsetFlag << std::endl;
			std::cout << "���Ͷ���ױ���־: " << pInputOrder->CombHedgeFlag << std::endl;
			std::cout << "�۸�: " << pInputOrder->LimitPrice << std::endl;
			std::cout << "����: " << pInputOrder->VolumeTotalOriginal << std::endl;
			std::cout << "��Ч����: " << pInputOrder->TimeCondition << std::endl;
			std::cout << "GDT����: " << pInputOrder->GTDDate << std::endl;
			std::cout << "�ɽ�������: " << pInputOrder->VolumeCondition << std::endl;
			std::cout << "��С�ɽ���: " << pInputOrder->MinVolume << std::endl;
			std::cout << "��������: " << pInputOrder->ContingentCondition << std::endl;
			std::cout << "ֹ���: " << pInputOrder->StopPrice << std::endl;
			std::cout << "ǿƽԭ��: " << pInputOrder->ForceCloseReason << std::endl;
			std::cout << "�Զ������־: " << pInputOrder->IsAutoSuspend << std::endl;
			std::cout << "ҵ��Ԫ: " << pInputOrder->BusinessUnit << std::endl;
			std::cout << "������: " << pInputOrder->RequestID << std::endl;
			std::cout << "�û�ǿƽ��־: " << pInputOrder->UserForceClose << std::endl;
			std::cout << "��������־: " << pInputOrder->IsSwapOrder << std::endl;
			std::cout << "����������: " << pInputOrder->ExchangeID << std::endl;
			std::cout << "Ͷ�ʵ�Ԫ����: " << pInputOrder->InvestUnitID << std::endl;
			std::cout << "�ʽ��˻�: " << pInputOrder->AccountID << std::endl;
			std::cout << "���ִ���: " << pInputOrder->CurrencyID << std::endl;
			std::cout << "���ױ���: " << pInputOrder->ClientID << std::endl;
			std::cout << "IP��ַ: " << pInputOrder->IPAddress << std::endl;
			std::cout << "mac ��ַ: " << pInputOrder->MacAddress << std::endl;
		}
		else
			std::cerr << "OnRspOrderInsert, errCode = " << pRspInfo->ErrorID << ", errMsg =" << pRspInfo->ErrorMsg << std::endl;
	};

	// �����Ѿ��ύ���������ɹ���ʧ�ܶ���ر�������ö�Σ�
	virtual void OnRtnOrder(CThostFtdcOrderField* pOrder) 
	{
		if (pOrder->OrderStatus == THOST_FTDC_OST_Canceled)   // ����ʧ��
		{
			// ��ӡ��������Ϣ
			NotifyFailed();
			std::cerr << "����ʧ�ܣ�msg = " << pOrder->StatusMsg << std::endl;
		}
		else												  // �����ɹ�
		{ 
			// ��һ�λص�
			if (pOrder->OrderSysID != NULL && pOrder->OrderSysID[0] != '\0') {
				NotifySuccess();
				strcpy_s(m_orderSysID, pOrder->OrderSysID);
			}

			// ��ⱨ��״̬
			if (pOrder->OrderStatus == THOST_FTDC_OST_AllTraded) { // ����ȫ���ɹ�
				strcpy_s(m_orderSysID, 0);
			}
			
			// ��ӡ��������ص���Ϣ
			std::cout << "��������ɹ�" << std::endl;
			std::cout << "���ù�˾���룺 " << pOrder->BrokerID << std::endl;
			std::cout << "Ͷ���ߴ��룺 " << pOrder->InvestorID << std::endl;
			std::cout << "��Լ���룺 " << pOrder->InstrumentID << std::endl;
			std::cout << "�������ã� " << pOrder->OrderRef << std::endl;
			std::cout << "�û����룺 " << pOrder->UserID << std::endl;
			std::cout << "�����۸������� " << pOrder->OrderPriceType << std::endl;
			std::cout << "�������� " << pOrder->Direction << std::endl;
			std::cout << "��Ͽ�ƽ��־�� " << pOrder->CombOffsetFlag << std::endl;
			std::cout << "���Ͷ���ױ���־�� " << pOrder->CombHedgeFlag << std::endl;
			std::cout << "�۸� " << pOrder->LimitPrice << std::endl;
			std::cout << "������ " << pOrder->VolumeTotalOriginal << std::endl;
			std::cout << "��Ч���ͣ� " << pOrder->TimeCondition << std::endl;
			std::cout << "GDT���ڣ� " << pOrder->GTDDate << std::endl;
			std::cout << "�ɽ������ͣ� " << pOrder->VolumeCondition << std::endl;
			std::cout << "��С�ɽ����� " << pOrder->MinVolume << std::endl;
			std::cout << "�����ţ� " << pOrder->SettlementID << std::endl;
			std::cout << "������ţ� " << pOrder->OrderSysID << std::endl;
			std::cout << "������Դ�� " << pOrder->OrderSource << std::endl;
			std::cout << "����״̬�� " << pOrder->OrderStatus << std::endl;
			std::cout << "�������ͣ� " << pOrder->OrderType << std::endl;
			std::cout << "��ɽ������� " << pOrder->VolumeTraded << std::endl;
			std::cout << "ʣ�������� " << pOrder->VolumeTotal << std::endl;
			std::cout << "�������ڣ� " << pOrder->InsertDate << std::endl;
			std::cout << "ί��ʱ�䣺 " << pOrder->InsertTime << std::endl;
			std::cout << "����ʱ�䣺 " << pOrder->ActiveTime << std::endl;
			std::cout << "����ʱ�䣺 " << pOrder->SuspendTime << std::endl;
		}		
	};

	// �����������ɽ�֪ͨ������ö��
	virtual void OnRtnTrade(CThostFtdcTradeField* pTrade) 
	{
		// ֱ�ӽ���Ϣ��ӡ��
		std::cout << "�����ɽ�֪ͨ" << std::endl;
		std::cout << "���ù�˾���룺 " << pTrade ->BrokerID << std::endl;
		std::cout << "Ͷ���ߴ��룺 " << pTrade->InvestorID << std::endl;
		std::cout << "��Լ���룺 " << pTrade->InstrumentID << std::endl;
		std::cout << "�������ã� " << pTrade->OrderRef << std::endl;
		std::cout << "�û����룺 " << pTrade->UserID << std::endl;
		std::cout << "���������룺 " << pTrade->ExchangeID << std::endl;
		std::cout << "�ɽ���ţ� " << pTrade->TradeID << std::endl;
		std::cout << "�������� " << pTrade->Direction << std::endl;
		std::cout << "������ţ� " << pTrade->OrderSysID << std::endl;
		std::cout << "��Ա��ţ� " << pTrade->ParticipantID << std::endl;
		std::cout << "��Լ�ڽ��������룺 " << pTrade->ExchangeInstID << std::endl;
		std::cout << "��ƽ��־�� " << pTrade->OffsetFlag << std::endl;
		std::cout << "Ͷ���ױ���־�� " << pTrade->HedgeFlag << std::endl;
		std::cout << "�۸� " << pTrade->Price << std::endl;
		std::cout << "������ " << pTrade->Volume << std::endl;
		std::cout << "�ɽ����ͣ� " << pTrade->TradeType << std::endl;
		std::cout << "�ɽ�����Դ�� " << pTrade->PriceSource << std::endl;
		std::cout << "�������ر�ţ� " << pTrade->OrderLocalID << std::endl;
		std::cout << "�����ţ� " << pTrade->SettlementID << std::endl;
		std::cout << "�ɽ���Դ�� " << pTrade->TradeSource << std::endl;
	};

	virtual void Run() 
	{
		SettlementInfoConfirmCtp::Run();
		bool settlementOK = SettlementInfoConfirmCtp::CheckIsOK();
		if (settlementOK) 
			SendOrderInsertRequest();		
		else {
			NotifyFailed();
			std::cerr << "ǰһ�ս���ʧ�ܣ������˺�����" << std::endl;
		}
	}

	char* GetOrderSysID() 
	{
		return m_orderSysID;
	}

	OrderInsertCtp() 
	{
		strcpy_s(m_instrumentID, "ag2206");
		strcpy_s(m_exchangeID, "SHFE");
		m_price = 5000;
		m_volume = 1;
	}

	OrderInsertCtp(string instrument, string exchange, double price, int volume)
	{
		strcpy_s(m_instrumentID, instrument.c_str());
		strcpy_s(m_exchangeID, exchange.c_str());
		m_price = price;
		m_volume = volume;
	}

private:
	// ���ͱ�������
	void SendOrderInsertRequest() 
	{
		CThostFtdcInputOrderField ord = { '\0' };
		strcpy_s(ord.BrokerID, gBrokerID);
		strcpy_s(ord.InvestorID, gInvesterID);
		strcpy_s(ord.ExchangeID, m_exchangeID);
		strcpy_s(ord.InstrumentID, m_instrumentID);
		strcpy_s(ord.UserID, gInvesterID);
		ord.OrderPriceType = THOST_FTDC_OPT_LimitPrice;//�޼�
		ord.Direction = THOST_FTDC_D_Buy;//��
		ord.CombOffsetFlag[0] = THOST_FTDC_OF_Open;//��
		ord.CombHedgeFlag[0] = THOST_FTDC_HF_Speculation;//Ͷ��
		ord.LimitPrice = m_price;
		ord.VolumeTotalOriginal = m_volume;
		ord.TimeCondition = THOST_FTDC_TC_GFD;///������Ч
		ord.VolumeCondition = THOST_FTDC_VC_AV;///��������
		ord.MinVolume = 1;
		ord.ContingentCondition = THOST_FTDC_CC_Immediately;
		ord.StopPrice = 0;
		ord.ForceCloseReason = THOST_FTDC_FCC_NotForceClose;
		ord.IsAutoSuspend = 0;

		int rf = m_pTdApi->ReqOrderInsert(&ord, 0);
		if (!rf)
			std::cout << "���ͱ�������ɹ�" << std::endl;
		else 
		{
			NotifyFailed();
			std::cerr << "���ͱ�������ʧ��" << std::endl;
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
	OrderInsertCtp orderInsertCtp;
	orderInsertCtp.Run();
	bool isOK = orderInsertCtp.CheckIsOK();
	EXPECT_TRUE(isOK);
}





