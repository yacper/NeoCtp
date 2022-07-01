#pragma once
#include<iostream>
#include<filesystem>
#include <string>
#include <gtest/gtest.h>
#include "Login.h"
class SettlementInfoConfirm;

void OnRspSettlementInfoConfirm(
	CThostFtdcSettlementInfoConfirmField* pSettlementInfoConfirm,
	CThostFtdcRspInfoField* pRspInfo,
	int nRequestID,
	bool bIsLast)
{
	bool bResult = pRspInfo && pRspInfo->ErrorID != 0;
	if (!bResult)
	{

		TestBase->NotifySuccess();
		//((SettlementInfoConfirm*)TestBase)->SaveSettlementResult();

		if (pSettlementInfoConfirm == nullptr)
			pSettlementInfoConfirm = new CThostFtdcSettlementInfoConfirmField();

		std::cout << "���������Ӧ" << std::endl;
		std::cout << "���ù�˾���룺 " << pSettlementInfoConfirm->BrokerID << std::endl;
		std::cout << "Ͷ���ߴ��룺 " << pSettlementInfoConfirm->InvestorID << std::endl;
		std::cout << "ȷ�����ڣ� " << pSettlementInfoConfirm->ConfirmDate << std::endl;
		std::cout << "ȷ��ʱ�䣺 " << pSettlementInfoConfirm->ConfirmTime << std::endl;
		std::cout << "�����ţ� " << pSettlementInfoConfirm->SettlementID << std::endl;
		std::cout << "Ͷ�����˺ţ� " << pSettlementInfoConfirm->AccountID << std::endl;
		std::cout << "���ִ��룺 " << pSettlementInfoConfirm->CurrencyID << std::endl;
	}
	else
	{
		TestBase->NotifyFailed();
		std::cerr << "errCode = " << pRspInfo->ErrorID << ", errMsg = " << pRspInfo->ErrorMsg << std::endl;
	}
};




// ����ȷ�ϣ���ÿ�쿪��ǰ��Ҫ��ȷ����һ�������յĽ�����Ϣ��
class SettlementInfoConfirm : public Login
{

public:
	virtual void Run()
	{
		Login::Run();

		RegOnRspSettlementInfoConfirm(m_pTdSpi, OnRspSettlementInfoConfirm);

		bool loginOK = Login::CheckIsOK();
		if (loginOK)
		{
			if (CheckIsSettlement())
			{  // �Ѿ������ֱ��֪ͨ
				NotifySuccess();
			}
			else
			{
				SendSettlementInfoConfirmRequest();
			}
		}
		else
		{
			NotifyFailed();
			std::cerr << "��¼ʧ�ܣ�������˵��û���������" << std::endl;
		}
	}

public:
	// ���ͽ���ȷ������
	void SendSettlementInfoConfirmRequest()
	{
		CThostFtdcSettlementInfoConfirmField confirm = { '\0' };
		strcpy_s(confirm.BrokerID, gBrokerID);
		strcpy_s(confirm.InvestorID, gInvesterID);

		int rf = ReqSettlementInfoConfirm(m_pTdApi, &confirm, 0);
		if (!rf)
			std::cout << "���ͽ���ȷ��������Ϣ�ɹ�" << std::endl;
		else
		{
			NotifyFailed();
			std::cerr << "���ͽ���ȷ��������Ϣʧ��" << std::endl;
		}
	}

	// �������������Ҫ��д�ļ�
	void SaveSettlementResult()
	{
		// �ȶ�ȡ�ļ�����
		char content[512];
		ifstream ifsfile;
		ifsfile.open(dbFile, ios::in);
		ifsfile >> content;
		ifsfile.close();

		string localTime = GetLocalTime();
		if (strlen(content) == 0)  // �ļ����ݸ�ʽ��������,�˺�A-�˺�B-�˺�C
			sprintf(content, "%s,%s", localTime.c_str(), gInvesterID);
		else
			sprintf(content, "%s-%s", content, gInvesterID);

		ofstream ofsfile;
		ofsfile.open(dbFile, ios::out);
		ofsfile << content << std::endl;
		ofsfile.close();
		
	}

	// ����Ƿ��Ѿ�����
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

	// ��������Ƿ�ʱ
	bool CheckContentTimeout(const char* content)
	{
		return strstr(content, GetLocalTime().c_str()) != nullptr;;
	}

	// ��⵱ǰ�˺��Ƿ��Ѿ�����
	bool CheckAccountIsSettlement(const char* content)
	{
		return strstr(content, gInvesterID) != nullptr;
	}

	// ��ȡ��ǰ�������� 
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
	SettlementInfoConfirm  confirmCtp;
	TestBase = &confirmCtp;
	confirmCtp.Run();
	bool isOK = confirmCtp.CheckIsOK();
	EXPECT_TRUE(isOK);
}
