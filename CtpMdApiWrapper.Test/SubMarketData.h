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
//		// 初始化行情线程
//		cout << "初始化行情..." << endl;
//		g_pMdUserApi = CreateFtdcMdApi();			// 创建行情实例		
//		g_pMdUserApi->RegisterSpi(this);		// 注册回调
//		g_pMdUserApi->RegisterFront(gMdFrontAddr);  // 设置行情前置地址
//
//		g_pMdUserApi->Init();                                // 连接运行
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
//		static int requestID = 0; // 请求编号
//		int rt = g_pMdUserApi->ReqUserLogin(&loginReq, requestID);
//
//		if (!rt)
//			std::cout << ">>>>>>发送登录请求成功" << std::endl;
//		else
//			std::cerr << "--->>>发送登录请求失败" << std::endl;
//	}
//
//
//	// 断开连接通知
//	virtual void OnFrontDisconnected(int nReason)
//	{
//		std::cerr << "=====网络连接断开===== \n 错误码：" << nReason << std::endl;		
//	}
//
//	// 心跳超时警告
//	virtual void OnHeartBeatWarning(int nTimeLapse)
//	{
//		char errorLog[128] = { '\0' };
//		sprintf(errorLog, "=====网络心跳超时=====\n 距上次连接时间：%d", nTimeLapse);
//		std::cout << "=====网络心跳超时=====\n 距上次连接时间：" << nTimeLapse << std::endl;		
//	}
//
//	// 登录应答
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
//			sprintf(buf, "=====账户登录成功===== \n 交易日： %s \n 登录时间： %s \n 经纪商： %s \n 帐户名： %s",
//				pRspUserLogin->TradingDay, pRspUserLogin->LoginTime, pRspUserLogin->BrokerID, pRspUserLogin->UserID);
//
//			std::cout << buf << std::endl;
//
//			// 订阅行情请求
//			int rt = g_pMdUserApi->SubscribeMarketData(instruments, 680);
//			if (!rt)
//				std::cout << ">>>>>>发送订阅行情请求成功" << std::endl;
//			else
//				std::cerr << "--->>>发送订阅行情请求失败" << std::endl;
//		}
//		else {
//			char buf[1024] = { '\0' };
//			sprintf(buf, "登录失败。返回错误--->>> ErrorID=%d, ErrorMsg=%s", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
//			std::cerr << buf << std::endl;
//		}
//	}
//
//
//	// 错误通知
//	virtual void OnRspError(CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
//	{
//		bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
//		if (bResult) {
//			char buf[512] = { '\0' };
//			sprintf(buf, "返回错误--->>> ErrorID=%d, ErrorMsg=%s", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
//			std::cerr << buf << std::endl;
//		}
//	}
//
//	// 订阅行情应答
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
//			sprintf(logBuf, "=====订阅行情成功===== \n 合约代码： %s", pSpecificInstrument->InstrumentID);
//			std::cout << logBuf << std::endl;
//			// 如果需要存入文件或者数据库，在这里创建表头,不同的合约单独存储
//			char filePath[100] = { '\0' };
//			sprintf(filePath, "out/%s_market_data.csv", pSpecificInstrument->InstrumentID);
//			std::ofstream outFile;
//			outFile.open(filePath, std::ios::out); // 新开文件
//			outFile << "合约代码" << ","
//				<< "更新时间" << ","
//				<< "最新价" << ","
//				<< "成交量" << ","
//				<< "买价一" << ","
//				<< "买量一" << ","
//				<< "卖价一" << ","
//				<< "卖量一" << ","
//				<< "持仓量" << ","
//				<< "换手率"
//				<< std::endl;
//			outFile.close();
//		}
//		else {
//			char buf[1024] = { '\0' };
//			sprintf(buf, "===订阅行情失败===\n返回错误--->>> ErrorID=%d, ErrorMsg=%s", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
//			std::cerr << buf << std::endl;
//		}
//	}
//
//	virtual void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField* pDepthMarketData)
//	{
//
//		// 打印行情，字段较多，截取部分
//		char logBuf[1024] = { '\0' };
//		sprintf(logBuf, "=====获得深度行情===== \n 交易日： %s\n 交易所代码： %s\n 合约代码： %s\n 合约在交易所的代码： %s\n 最新价： %f\n 数量： %d",
//			pDepthMarketData->TradingDay, pDepthMarketData->ExchangeID, pDepthMarketData->InstrumentID, pDepthMarketData->ExchangeInstID, (float)pDepthMarketData->LastPrice, pDepthMarketData->Volume);
//		std::cout <<logBuf << std::endl;
//		// 如果只获取某一个合约行情，可以逐tick地存入文件或数据库
//		char filePath[100] = { '\0' };
//		sprintf(filePath, "out/%s_market_data.csv", pDepthMarketData->InstrumentID);
//		std::ofstream outFile;
//		outFile.open(filePath, std::ios::app); // 文件追加写入 
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
//	TThostFtdcBrokerIDType gBrokerID = "9999";                         // 模拟经纪商代码
//	TThostFtdcInvestorIDType gInvesterID = "097266";                         // 投资者账户名
//	TThostFtdcPasswordType gInvesterPassword = "hello@123";                     // 投资者密码
//
//	// 行情参数
//	CThostFtdcMdApi* g_pMdUserApi = nullptr;                           // 行情指针
//	MdSpi* g_pMdSpi = nullptr;                           // spi
//	char* gMdFrontAddr = "tcp://180.168.146.187:10211";               // 模拟行情前置地址 第一组
//	//char* gMdFrontAddr = "tcp://180.168.146.187:10131";               // 模拟行情前置地址 24h
//
//	char* (instruments)[680] = {'\0'};											// 所有合约集合
//	int instrumentNum = 680;                                             // 行情合约订阅数量
//	string instrumentPath = "instrument.txt";
//	ParsingInstrument *parsing = nullptr;
//};
//
//TEST(CtpMdApiWrapperTest, 20SubAllMarkData) {
//	SubMarketData subMarketData = SubMarketData();	
//}
