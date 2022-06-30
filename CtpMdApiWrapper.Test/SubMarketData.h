#pragma once
#include "pch.h"
#include <ostream>
#include <fstream>
#include <mutex>
#include <string>
#include "MdSpi.h"
#include "MdApi.h"
#include "ParsingInstrument.h"
using namespace std;

//class SubMarketData: public CThostFtdcMdSpi
//{
//public:
//	SubMarketData() 
//	{
//		Init();
//		g_pMdUserApi->Join();
//	}
//
//	void Init() {		
//
//		parsing = new ParsingInstrument(instrumentPath);		
//		char** instas = parsing->Instruments();		
//		int idx = 0;
//		for (instas; *instas != NULL; instas++)
//		{
//			if (idx == 681)
//				break;
//			instruments[idx] = new char[8]();
//			strcpy_s(instruments[idx], 8, *instas);
//			idx++;
//		}
//		
//
//		// ��ʼ�������߳�
//		cout << "��ʼ������..." << endl;
//		g_pMdUserApi = CreateFtdcMdApi();			// ��������ʵ��		
//		g_pMdUserApi->RegisterSpi(this);		// ע��ص�
//		g_pMdUserApi->RegisterFront(gMdFrontAddr);  // ��������ǰ�õ�ַ
//
//		g_pMdUserApi->Init();                                // ��������
//	}
//
//
//	virtual void OnFrontConnected()
//	{
//		CThostFtdcReqUserLoginField loginReq;
//		memset(&loginReq, 0, sizeof(loginReq));
//		strcpy(loginReq.BrokerID, gBrokerID);
//		strcpy(loginReq.UserID, gInvesterID);
//		strcpy(loginReq.Password, gInvesterPassword);
//		static int requestID = 0; // ������
//		int rt = g_pMdUserApi->ReqUserLogin(&loginReq, requestID);
//
//		if (!rt)
//			std::cout << ">>>>>>���͵�¼����ɹ�" << std::endl;
//		else
//			std::cerr << "--->>>���͵�¼����ʧ��" << std::endl;
//	}
//
//
//	// �Ͽ�����֪ͨ
//	virtual void OnFrontDisconnected(int nReason)
//	{
//		std::cerr << "=====�������ӶϿ�===== \n �����룺" << nReason << std::endl;		
//	}
//
//	// ������ʱ����
//	virtual void OnHeartBeatWarning(int nTimeLapse)
//	{
//		char errorLog[128] = { '\0' };
//		sprintf(errorLog, "=====����������ʱ=====\n ���ϴ�����ʱ�䣺%d", nTimeLapse);
//		std::cout << "=====����������ʱ=====\n ���ϴ�����ʱ�䣺" << nTimeLapse << std::endl;		
//	}
//
//	// ��¼Ӧ��
//	virtual void OnRspUserLogin(
//		CThostFtdcRspUserLoginField* pRspUserLogin,
//		CThostFtdcRspInfoField* pRspInfo,
//		int nRequestID,
//		bool bIsLast)
//	{
//		bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
//		if (!bResult)
//		{
//			char buf[1024] = { '\0' };			
//			sprintf(buf, "=====�˻���¼�ɹ�===== \n �����գ� %s \n ��¼ʱ�䣺 %s \n �����̣� %s \n �ʻ����� %s",
//				pRspUserLogin->TradingDay, pRspUserLogin->LoginTime, pRspUserLogin->BrokerID, pRspUserLogin->UserID);
//
//			std::cout << buf << std::endl;
//
//			// ������������
//			int rt = g_pMdUserApi->SubscribeMarketData(instruments, 680);
//			if (!rt)
//				std::cout << ">>>>>>���Ͷ�����������ɹ�" << std::endl;
//			else
//				std::cerr << "--->>>���Ͷ�����������ʧ��" << std::endl;
//		}
//		else {
//			char buf[1024] = { '\0' };
//			sprintf(buf, "��¼ʧ�ܡ����ش���--->>> ErrorID=%d, ErrorMsg=%s", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
//			std::cerr << buf << std::endl;
//		}
//	}
//
//
//	// ����֪ͨ
//	virtual void OnRspError(CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
//	{
//		bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
//		if (bResult) {
//			char buf[512] = { '\0' };
//			sprintf(buf, "���ش���--->>> ErrorID=%d, ErrorMsg=%s", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
//			std::cerr << buf << std::endl;
//		}
//	}
//
//	// ��������Ӧ��
//	virtual void OnRspSubMarketData(
//		CThostFtdcSpecificInstrumentField* pSpecificInstrument,
//		CThostFtdcRspInfoField* pRspInfo,
//		int nRequestID,
//		bool bIsLast)
//	{
//		bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
//		if (!bResult)
//		{
//			char logBuf[128] = { '\0' };
//			sprintf(logBuf, "=====��������ɹ�===== \n ��Լ���룺 %s", pSpecificInstrument->InstrumentID);
//			std::cout << logBuf << std::endl;
//			// �����Ҫ�����ļ��������ݿ⣬�����ﴴ����ͷ,��ͬ�ĺ�Լ�����洢
//			char filePath[100] = { '\0' };
//			sprintf(filePath, "out/%s_market_data.csv", pSpecificInstrument->InstrumentID);
//			std::ofstream outFile;
//			outFile.open(filePath, std::ios::out); // �¿��ļ�
//			outFile << "��Լ����" << ","
//				<< "����ʱ��" << ","
//				<< "���¼�" << ","
//				<< "�ɽ���" << ","
//				<< "���һ" << ","
//				<< "����һ" << ","
//				<< "����һ" << ","
//				<< "����һ" << ","
//				<< "�ֲ���" << ","
//				<< "������"
//				<< std::endl;
//			outFile.close();
//		}
//		else {
//			char buf[1024] = { '\0' };
//			sprintf(buf, "===��������ʧ��===\n���ش���--->>> ErrorID=%d, ErrorMsg=%s", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
//			std::cerr << buf << std::endl;
//		}
//	}
//
//	virtual void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField* pDepthMarketData)
//	{
//
//		// ��ӡ���飬�ֶν϶࣬��ȡ����
//		char logBuf[1024] = { '\0' };
//		sprintf(logBuf, "=====����������===== \n �����գ� %s\n ���������룺 %s\n ��Լ���룺 %s\n ��Լ�ڽ������Ĵ��룺 %s\n ���¼ۣ� %f\n ������ %d",
//			pDepthMarketData->TradingDay, pDepthMarketData->ExchangeID, pDepthMarketData->InstrumentID, pDepthMarketData->ExchangeInstID, (float)pDepthMarketData->LastPrice, pDepthMarketData->Volume);
//		std::cout <<logBuf << std::endl;
//		// ���ֻ��ȡĳһ����Լ���飬������tick�ش����ļ������ݿ�
//		char filePath[100] = { '\0' };
//		sprintf(filePath, "out/%s_market_data.csv", pDepthMarketData->InstrumentID);
//		std::ofstream outFile;
//		outFile.open(filePath, std::ios::app); // �ļ�׷��д�� 
//		outFile << pDepthMarketData->InstrumentID << ","
//			<< pDepthMarketData->UpdateTime << "." << pDepthMarketData->UpdateMillisec << ","
//			<< pDepthMarketData->LastPrice << ","
//			<< pDepthMarketData->Volume << ","
//			<< pDepthMarketData->BidPrice1 << ","
//			<< pDepthMarketData->BidVolume1 << ","
//			<< pDepthMarketData->AskPrice1 << ","
//			<< pDepthMarketData->AskVolume1 << ","
//			<< pDepthMarketData->OpenInterest << ","
//			<< pDepthMarketData->Turnover << std::endl;
//		outFile.close();
//	}
//
//private:
//	TThostFtdcBrokerIDType gBrokerID = "9999";                         // ģ�⾭���̴���
//	TThostFtdcInvestorIDType gInvesterID = "097266";                         // Ͷ�����˻���
//	TThostFtdcPasswordType gInvesterPassword = "hello@123";                     // Ͷ��������
//
//	// �������
//	CThostFtdcMdApi* g_pMdUserApi = nullptr;                           // ����ָ��
//	MdSpi* g_pMdSpi = nullptr;                           // spi
//	char* gMdFrontAddr = "tcp://180.168.146.187:10211";               // ģ������ǰ�õ�ַ ��һ��
//	//char* gMdFrontAddr = "tcp://180.168.146.187:10131";               // ģ������ǰ�õ�ַ 24h
//
//	char* (instruments)[680] = {'\0'};											// ���к�Լ����
//	int instrumentNum = 680;                                             // �����Լ��������
//	string instrumentPath = "instrument.txt";
//	ParsingInstrument *parsing = nullptr;
//};
//
//TEST(CtpMdApiWrapperTest, 20SubAllMarkData) {
//	SubMarketData subMarketData = SubMarketData();	
//}
