#pragma once
#include "LoginCtp.h"

// Ԥ�񵥡�
// TODO��1.���Ԥ�񵥵�״̬���ѷ���/δ���� 
//		 2.�Ѿ�����״̬��Ԥ�񵥻��߱��������� 
//		 3.Ԥ�񵥳����Ƿ��ܳ��ѷ��͵Ķ���/��δ���Ͷ���
class ParkedOrderInsertCtp : public LoginCtp 
{
public:

	// ����¼��ʧ��
	virtual void OnRspOrderInsert(
		CThostFtdcInputOrderField* pInputOrder, 
		CThostFtdcRspInfoField* pRspInfo, 
		int nRequestID, 
		bool bIsLast) 
	{
		int a = 100;
	};

	// ����¼��ʧ��
	virtual void OnErrRtnOrderInsert(
		CThostFtdcInputOrderField* pInputOrder, 
		CThostFtdcRspInfoField* pRspInfo) 
	{
		int a = 100;
	};

	// ����¼��ɹ��ص�
	virtual void OnRtnOrder(CThostFtdcOrderField* pOrder) 
	{
		int a = 100;
	};

	// Ԥ����Ӧ
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
			std::cout << "Ԥ��������Ӧ" << std::endl;
			std::cout << "���ù�˾���룺 " << pParkedOrder->BrokerID << std::endl;
			std::cout << "Ͷ���ߴ��룺 " << pParkedOrder->InvestorID << std::endl;
			std::cout << "��Լ���룺 " << pParkedOrder->InstrumentID << std::endl;
			std::cout << "Ԥ��״̬�� " << pParkedOrder->Status << std::endl;
		}
		else {
			NotifyFailed();
			std::cerr << "errCode =" << pRspInfo->ErrorID << ", errMsg = " << pRspInfo->ErrorMsg << std::endl;
 		}
	};

	virtual void Run() 
	{
		LoginCtp::Run();
		bool loginOK = LoginCtp::CheckIsOK();
		if (loginOK)
			SendParkedOrderInsertRequest();
		else {
			NotifyFailed();
			std::cerr << "�û���¼ʧ�ܣ������˺�����" << std::endl;
		}
	}

private:
	void SendParkedOrderInsertRequest() 
	{
		CThostFtdcParkedOrderField order = { 0 };
		strcpy(order.BrokerID, m_brokerID);
		strcpy(order.InvestorID, m_investerID);
		strcpy(order.InstrumentID, m_instrumentID);
		strcpy(order.UserID, m_investerID);
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
			std::cout << "����Ԥ������ɹ�" << std::endl;		
		else {
			NotifyFailed();
			std::cerr << "����Ԥ������ʧ��" << std::endl;
		}
	}

protected:

	char m_instrumentID[7] = "ag2206";
	char m_exchangeID[5] = "SHFE";
	double m_price = 5000;
	int m_volume = 1;
	TThostFtdcParkedOrderIDType m_parkedOrderID = { '\0' };
};

// ֻ���ڷǽ���ʱ�ο��Բ��Գɹ�
TEST(CtpApiTest, 08ParkedOrderInsert)
{
	ParkedOrderInsertCtp parkedOrderCtp;
	parkedOrderCtp.Run();
	bool isOK = parkedOrderCtp.CheckIsOK();
	EXPECT_TRUE(isOK);
  
}
