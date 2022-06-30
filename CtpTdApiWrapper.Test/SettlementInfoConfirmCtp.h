#pragma once
#include<iostream>
#include<filesystem>
#include <string>
#include <gtest/gtest.h>
#include "LoginCtp.h"

// 结算确认（在每天开仓前需要先确认上一个交易日的结算信息）
class SettlementInfoConfirmCtp : public LoginCtp
{

public:
	virtual void OnRspSettlementInfoConfirm(
		CThostFtdcSettlementInfoConfirmField* pSettlementInfoConfirm, 
		CThostFtdcRspInfoField* pRspInfo, 
		int nRequestID, 
		bool bIsLast) 
	{
		bool bResult = pRspInfo && pRspInfo->ErrorID != 0;
		if (!bResult) {

			NotifySuccess();
			SaveSettlementResult();

			if (pSettlementInfoConfirm == nullptr)
				pSettlementInfoConfirm = new CThostFtdcSettlementInfoConfirmField();

			std::cout << "请求结算响应" << std::endl;
			std::cout << "经济公司代码： " << pSettlementInfoConfirm->BrokerID << std::endl;
			std::cout << "投资者代码： " << pSettlementInfoConfirm->InvestorID << std::endl;
			std::cout << "确认日期： " << pSettlementInfoConfirm->ConfirmDate << std::endl;
			std::cout << "确认时间： " << pSettlementInfoConfirm->ConfirmTime << std::endl;
			std::cout << "结算编号： " << pSettlementInfoConfirm->SettlementID << std::endl;
			std::cout << "投资者账号： " << pSettlementInfoConfirm->AccountID << std::endl;
			std::cout << "币种代码： " << pSettlementInfoConfirm->CurrencyID << std::endl;
		}
		else 
		{
			NotifyFailed();
			std::cerr << "errCode = " << pRspInfo->ErrorID << ", errMsg = " << pRspInfo->ErrorMsg << std::endl;
		}
	};

	virtual void Run() 
	{
		LoginCtp::Run();
		bool loginOK =  LoginCtp::CheckIsOK();
		if (loginOK) {
			if (CheckIsSettlement()) {  // 已经结算过直接通知
				NotifySuccess();
			}
			else {
				SendSettlementInfoConfirmRequest();
			}			
		}
		else {
			NotifyFailed();
			std::cerr << "登录失败，请检查瞪了的用户名和密码" << std::endl;
		}
	}

private:
	// 发送结算确认请求
	void SendSettlementInfoConfirmRequest() 
	{
		CThostFtdcSettlementInfoConfirmField confirm = { '\0' };
		strcpy_s(confirm.BrokerID, m_brokerID);
		strcpy_s(confirm.InvestorID, m_investerID);

		int rf = m_pTdApi->ReqSettlementInfoConfirm(&confirm, 0);
		if (!rf)
			std::cout << "发送结算确认请求消息成功" << std::endl;
		else 
		{
			NotifyFailed();
			std::cerr << "发送结算确认请求消息失败" << std::endl;
		}
	}

	// 保存结算结果，主要是写文件
	void SaveSettlementResult()
	{
		// 先读取文件内容
		char content[512];
		ifstream ifsfile;
		ifsfile.open(dbFile, ios::in);
		ifsfile >> content;
		ifsfile.close();

		string localTime = GetLocalTime();
		if (strlen(content) == 0)  // 文件内容格式，年月日,账号A-账号B-账号C
			sprintf(content, "%s,%s", localTime.c_str(), m_investerID);
		else
			sprintf(content, "%s-%s", content, m_investerID);

		ofstream ofsfile;
		ofsfile.open(dbFile, ios::out);
		ofsfile << content << std::endl;
		ofsfile.close();
	}

	// 检测是否已经结算
	bool CheckIsSettlement()
	{
		struct stat sta;
		int rf = stat(dbFile, &sta);
		if (rf != 0)
			return false;

		string content;
		ifstream infile;
		infile.open(dbFile);
		std::getline(infile, content);
		infile.close();

		if (!CheckContentTimeout(content.c_str()))
			return false;

		if (!CheckAccountIsSettlement(content.c_str()))
			return false;

		return true;
	}

	// 检测内容是否超时
	bool CheckContentTimeout(const char* content)
	{
		return strstr(content, GetLocalTime().c_str()) != nullptr;;
	}

	// 检测当前账号是否已经结算
	bool CheckAccountIsSettlement(const char* content)
	{
		return strstr(content, m_investerID) != nullptr;
	}

	// 获取当前的年月日 
	string GetLocalTime()
	{
		char buffer[12];
		time_t now = time(0);
		tm* ltm = localtime(&now);
		sprintf(buffer, "%d %d %d", (1900 + ltm->tm_year), (1 + ltm->tm_mon), ltm->tm_mday);
		return string(buffer);
	}

private:
	char dbFile[50] = "SettlementInfoConfirm.db";
};

TEST(CtpApiTest, 04SettlementInfoConfirm)
{
	SettlementInfoConfirmCtp  confirmCtp;
	confirmCtp.Run();
	bool isOK = confirmCtp.CheckIsOK();
	EXPECT_TRUE(isOK);
}
