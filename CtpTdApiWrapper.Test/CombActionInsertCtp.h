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
			std::cerr << "登录失败，请检查用户名和密码" << std::endl;
		}
	}

private:
	// 申请组合录入请求
	void SendCombActionInstallRequest() 
	{
		CThostFtdcInputCombActionField action = { '\0' };
		//action

		int rf = m_pTdApi->ReqCombActionInsert(&action, 0);
		if (!rf) {
			std::cout << "发送申请组合录入请求成功" << std::endl;
		}
		else {
			NotifyFailed();
			std::cerr << "发送申请组合录入请求失败" << std::endl;
		}
	}

};
