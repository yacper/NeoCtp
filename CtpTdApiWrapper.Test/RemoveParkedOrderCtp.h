#pragma once
#include "ParkedOrderInsertCtp.h"

// ɾ��Ԥ��
class RemoveParkedOrderCtp : public ParkedOrderInsertCtp 
{
public:

	// ɾ��Ԥ������ر�
	virtual void OnRspRemoveParkedOrder(
		CThostFtdcRemoveParkedOrderField* pRemoveParkedOrder, 
		CThostFtdcRspInfoField* pRspInfo, 
		int nRequestID, 
		bool bIsLast) 
	{
		bool bResult = pRspInfo && pRspInfo->ErrorID != 0;
		if (!bResult) {
			NotifySuccess();
			std::cout << "ɾ��Ԥ��������Ӧ" << std::endl;
			std::cout << "���ù�˾���룺 " << pRemoveParkedOrder->BrokerID << std::endl;
			std::cout << "Ͷ���ߴ��룺 " << pRemoveParkedOrder->InvestorID << std::endl;
			std::cout << "Ԥ�񵥱�ţ� " << pRemoveParkedOrder->ParkedOrderID << std::endl;
			std::cout << "Ͷ�ʵ�Ԫ���룺 " << pRemoveParkedOrder->InvestUnitID << std::endl;
		}
		else {
			NotifyFailed();
			std::cerr << "errCode = " << pRspInfo->ErrorID << ", errMsg = " << pRspInfo->ErrorMsg << std::endl;
		}
	};

	virtual void Run() 
	{
		ParkedOrderInsertCtp::Run();
		bool orderInsertOK = ParkedOrderInsertCtp::CheckIsOK();
		if (orderInsertOK)
			SendRemoveParkedOrderRequest();
		else {
			NotifyFailed();
			std::cerr << "Ԥ��ʧ��" << std::endl;
		}
	}

private:
	void SendRemoveParkedOrderRequest() 
	{
		CThostFtdcRemoveParkedOrderField order = { 0 };
		strcpy_s(order.BrokerID, m_brokerID);
		strcpy_s(order.InvestorID, m_investerID);
		strcpy_s(order.ParkedOrderID, m_parkedOrderID);

		int rf = m_pTdApi->ReqRemoveParkedOrder(&order, 0);
		if (!rf) {
			std::cout << "����ɾ��Ԥ������ɹ�" << std::endl;
		}
		else {
			NotifyFailed();
			std::cerr << "����ɾ��Ԥ������ʧ��" << std::endl;
		}
	}
};

// ֻ���ڷǽ��׽׶β��Բ��ܳɹ�
TEST(CtpApiTest, 09RemoveParkedOrder)
{
	RemoveParkedOrderCtp removeParkedOrderCtp;
	removeParkedOrderCtp.Run();
	bool isOK = removeParkedOrderCtp.CheckIsOK();
	EXPECT_TRUE(isOK);
}
