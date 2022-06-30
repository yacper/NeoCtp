#pragma once
#include "ParkedOrderActionCtp.h"

// ����û�гɽ���Ԥ�񳷵�����ֻ���ڷǽ���ʱ�β������ã�
class RemoveParkedOrderActionCtp: public ParkedOrderActionCtp
{
public:

	// ����Ԥ�񳷵���Ӧ
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

			std::cout << "����Ԥ�񳷵���Ӧ" << std::endl;
			std::cout << "���ù�˾���룺 " << pRemoveParkedOrderAction ->BrokerID << std::endl;
			std::cout << "Ͷ���ߴ��룺 " << pRemoveParkedOrderAction->InvestorID << std::endl;
			std::cout << "Ԥ�񳷵���ţ� " << pRemoveParkedOrderAction->ParkedOrderActionID << std::endl;
			std::cout << "Ͷ�ʵ�Ԫ���룺 " << pRemoveParkedOrderAction->InvestUnitID << std::endl;
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
			std::cerr << "Ԥ�񳷵�����ʧ��" << std::endl;
		}
	}

private:
	// ����Ԥ�񳷵�ɾ������
	void SendRemoveParkedOrderActionRequest() 
	{
		CThostFtdcRemoveParkedOrderActionField orderAction = { 0 };
		strcpy_s(orderAction.BrokerID, m_brokerID);
		strcpy_s(orderAction.InvestorID, m_investerID);
		strcpy_s(orderAction.ParkedOrderActionID, m_parkedOrderActionID.c_str());

		int rf = m_pTdApi->ReqRemoveParkedOrderAction(&orderAction, 0);
		if (!rf) {
			std::cout << "����Ԥ�񳷵�ɾ������ɹ�" << std::endl;
		}
		else {
			NotifyFailed();
			std::cerr << "����Ԥ�񳷵�ɾ������ʧ��" << std::endl;
		}
	}
};

// ֻ���ڷǽ���ʱ�βŻ�ɹ�
TEST(CtpApiTest, 13RemoveParkedOrderAction)
{
	RemoveParkedOrderActionCtp removeParkedOrderAction;
	removeParkedOrderAction.Run();
	bool isOK = removeParkedOrderAction.CheckIsOK();
	EXPECT_TRUE(isOK);
}
