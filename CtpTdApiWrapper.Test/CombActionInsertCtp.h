#pragma once
#include "LoginCtp.h"

class CombActionInsertCtp : public LoginCtp 
{
public:

	virtual void OnErrRtnCombActionInsert(
		CThostFtdcInputCombActionField* pInputCombAction, 
		CThostFtdcRspInfoField* pRspInfo) 
	{

	};


	virtual void OnRspCombActionInsert(
		CThostFtdcInputCombActionField* pInputCombAction, 
		CThostFtdcRspInfoField* pRspInfo, 
		int nRequestID, 
		bool bIsLast) 
	{

	};

	virtual void Run() 
	{
		LoginCtp::Run();
		bool loginOK = LoginCtp::CheckIsOK();
		if (loginOK)
			SendCombActionInstallRequest();
		else 
		{
			NotifyFailed();
			std::cerr << "��¼ʧ�ܣ������û���������" << std::endl;
		}
	}

private:
	// �������¼������
	void SendCombActionInstallRequest() 
	{
		CThostFtdcInputCombActionField action = { '\0' };
		//action

		int rf = m_pTdApi->ReqCombActionInsert(&action, 0);
		if (!rf) {
			std::cout << "�����������¼������ɹ�" << std::endl;
		}
		else {
			NotifyFailed();
			std::cerr << "�����������¼������ʧ��" << std::endl;
		}
	}

};