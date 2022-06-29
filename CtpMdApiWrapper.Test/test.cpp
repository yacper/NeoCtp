#include "pch.h"
#include <ostream>
#include <fstream>
#include <mutex>
#include <string>
#include "MdSpi.h"
#include "MdApi.h"
#include "SubMarketData.h"
using namespace std;

// 公共参数
TThostFtdcBrokerIDType gBrokerID = "9999";                         // 模拟经纪商代码
TThostFtdcInvestorIDType gInvesterID = "097266";                         // 投资者账户名
TThostFtdcPasswordType gInvesterPassword = "hello@123";                     // 投资者密码

// 行情参数
CThostFtdcMdApi *g_pMdUserApi = nullptr;                           // 行情指针
MdSpi *g_pMdSpi = nullptr;                           // spi
char gMdFrontAddr[] = "tcp://180.168.146.187:10211";               // 模拟行情前置地址 第一组
//char gMdFrontAddr[] = "tcp://180.168.146.187:10131";               // 模拟行情前置地址 24h
char *g_pInstrumentID[] = {"cu2203,C73000"};								// 行情合约代码列表，中、上、大、郑交易所各选一种
int instrumentNum = 1;                                             // 行情合约订阅数量
string instrumentPath = "instrument.txt";


struct CtpMdApiTestParam
{
	// 登录
	bool isLogin;
	bool isLogout;

	// 行情
	bool isSubMarketData;
	bool isUnSubMarketData;
	bool isMarketDataNotice;

	// 询价
	bool isSubQuoteData;
	bool isUnSubQuoteData;
	bool isQuoteDataNotice;

	// 查询组播
	bool isLookMulticast;
};

CtpMdApiTestParam g_ctpMdApiTestParam = { "\0" };

// 登录
bool g_loginOK = false;
bool g_logoutOK = false;

// 市场数据
bool g_subMarketDataOK = false;
bool g_unSubMarketDataOK = false;
bool g_marketDataNoticeOK = false;

// 询价
bool g_subQuoteDataOK = false;
bool g_unSubQuoteDataOK = false;
bool g_quoteDataNoticeOK = false;

// 查询组播
bool g_lookMulticastOK = false;

// 线程同步参数
mutex mut;
condition_variable cond_va;

std::ofstream outLogFile;

enum LogLevel
{
	Debug = 0,
	Warn,
	Error,
};

char* logLevelName[] = { "Debug","Warn","Error" };

void InitLog() 
{
	//std::remove("log.txt");
	outLogFile.open("log.txt", std::ios::out);
}

void LogInfo(char* log, LogLevel level = LogLevel::Debug, bool show = true)
{
	char timeBuf[100] = { '\0' };
	time_t t = time(NULL);
	tm local = { '\0' };
	localtime_s(&local, &t);
	strftime(timeBuf, sizeof(timeBuf), "%Y/%m/%d %H:%M:%S", &local);

	// log 超过了 2048 可能有问题
	char logBuf[2048] = { '\0' };	
	sprintf(logBuf, "%s [%s]: %s", timeBuf, logLevelName[level], log);
	outLogFile << logBuf << std::endl;

	if (show)
		if (level != LogLevel::Error)
			std::cout << logBuf << std::endl;
		else
			std::cerr << logBuf << std::endl;
}

#pragma region callbacks
void WINAPI  OnFrontConnected()
{
	if (g_ctpMdApiTestParam.isLogin) {
		LogInfo("=====建立网络连接成功=====");
		// 开始登录
		CThostFtdcReqUserLoginField loginReq;
		memset(&loginReq, 0, sizeof(loginReq));
		strcpy(loginReq.BrokerID, gBrokerID);
		strcpy(loginReq.UserID, gInvesterID);
		strcpy(loginReq.Password, gInvesterPassword);
		static int requestID = 0; // 请求编号
		int rt = g_pMdUserApi->ReqUserLogin(&loginReq, requestID);

		if (!rt)
			LogInfo(">>>>>>发送登录请求成功");
		else
			LogInfo("--->>>发送登录请求失败", LogLevel::Error);
	}	

	char logBuf[128] = { '\0' };
	sprintf(logBuf, "API Version: %s", g_pMdUserApi->GetApiVersion());
	LogInfo(logBuf);
}


// 断开连接通知
void WINAPI OnFrontDisconnected(int nReason)
{
	char errorLog[128] = { '\0' };
	sprintf(errorLog, "=====网络连接断开===== \n 错误码：%d", nReason);
	LogInfo(errorLog, LogLevel::Error);
}

// 心跳超时警告
void WINAPI OnHeartBeatWarning(int nTimeLapse)
{
	char errorLog[128] = { '\0' };
	sprintf(errorLog, "=====网络心跳超时=====\n 距上次连接时间：%d", nTimeLapse);
	LogInfo(errorLog, LogLevel::Error);
}

// 登录应答
void WINAPI OnRspUserLogin(
	CThostFtdcRspUserLoginField *pRspUserLogin, 
	CThostFtdcRspInfoField *pRspInfo, 
	int nRequestID, 
	bool bIsLast)
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult)
	{
		g_loginOK = true;		
		cond_va.notify_one();

		char buf[1024] = { '\0' };
		sprintf(buf, "=====账户登录成功===== \n 交易日： %s \n 登录时间： %s \n 经纪商： %s \n 帐户名： %s", 
				pRspUserLogin->TradingDay, pRspUserLogin->LoginTime, pRspUserLogin->BrokerID,pRspUserLogin->UserID);

		LogInfo(buf);
		
		// 订阅行情请求
		if (g_ctpMdApiTestParam.isSubMarketData) {
			int rt = g_pMdUserApi->SubscribeMarketData(g_pInstrumentID, instrumentNum);
			if (!rt)
				LogInfo(">>>>>>发送订阅行情请求成功");
			else
				LogInfo("--->>>发送订阅行情请求失败", LogLevel::Error);
		}

		// 订阅询价
		if (g_ctpMdApiTestParam.isSubQuoteData) {
			int rt = g_pMdUserApi->SubscribeForQuoteRsp(g_pInstrumentID, instrumentNum);

			if (!rt)
				LogInfo(">>>>>>发送订阅询价请求成功");
			else
				LogInfo("--->>>发送订阅询价请求失败", LogLevel::Error);
		}

		// 登出请求
		if (g_ctpMdApiTestParam.isLogout) {
			CThostFtdcUserLogoutField logout = { "\0" };
			std::strcpy(logout.BrokerID, gBrokerID);
			std::strcpy(logout.UserID, gInvesterID);
			static int requestID = 0; // 请求编号
			int rt = g_pMdUserApi->ReqUserLogout(&logout, requestID);

			if (!rt)
				LogInfo(">>>>>>发送登出请求成功");
			else
				LogInfo("--->>>发送登出请求失败", LogLevel::Error);
		}

		if (g_ctpMdApiTestParam.isLookMulticast) {
			CThostFtdcQryMulticastInstrumentField multicastInstrumentField = { '\0'};
			multicastInstrumentField.TopicID = 1001;		//对应上期所的组播行情topic			
			strcpy(multicastInstrumentField.InstrumentID, g_pInstrumentID[0]);
			int rt = g_pMdUserApi->ReqQryMulticastInstrument(&multicastInstrumentField, 1);

			if (!rt)
				LogInfo(">>>>>>发送查询组播请求成功");
			else
				LogInfo("--->>>发送查询组播请求失败", LogLevel::Error);
		}
	}
	else {
		char buf[1024] = { '\0' };
		sprintf(buf, "登录失败。返回错误--->>> ErrorID=%d, ErrorMsg=%s", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
		LogInfo(buf, LogLevel::Error);
	}
}

// 登出应答
void WINAPI OnRspUserLogout(
	CThostFtdcUserLogoutField *pUserLogout,
	CThostFtdcRspInfoField *pRspInfo, 
	int nRequestID, 
	bool bIsLast)
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult)
	{
		char buf[512] = { '\0' };
		sprintf(buf, "=====账户登出成功=====\n 经纪商： %s \n 帐户名： %s", pUserLogout->BrokerID, pUserLogout->UserID);
		LogInfo(buf);

		g_logoutOK = true;		
		cond_va.notify_one();
	}
	else {
		char buf[1024] = { '\0' };
		sprintf(buf, "登出失败。返回错误--->>> ErrorID=%d, ErrorMsg=%s", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
		LogInfo(buf, LogLevel::Error);
	}
}

// 错误通知
void WINAPI  OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (bResult) {
		char buf[512] = { '\0' };
		sprintf(buf, "返回错误--->>> ErrorID=%d, ErrorMsg=%s", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
		LogInfo(buf, LogLevel::Error);
	}
}

// 订阅行情应答
void WINAPI OnRspSubMarketData(
	CThostFtdcSpecificInstrumentField *pSpecificInstrument, 
	CThostFtdcRspInfoField *pRspInfo, 
	int nRequestID, 
	bool bIsLast)
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult)
	{
		g_subMarketDataOK = true;		
		cond_va.notify_one();

		char logBuf[128] = { '\0' };
		sprintf(logBuf, "=====订阅行情成功===== \n 合约代码： %s", pSpecificInstrument->InstrumentID);
		LogInfo(logBuf);
		// 如果需要存入文件或者数据库，在这里创建表头,不同的合约单独存储
		char filePath[100] = {'\0'};
		sprintf(filePath, "%s_market_data.csv", pSpecificInstrument->InstrumentID);
		std::ofstream outFile;
		outFile.open(filePath, std::ios::out); // 新开文件
		outFile << "合约代码" << ","
			<< "更新时间" << ","
			<< "最新价" << ","
			<< "成交量" << ","
			<< "买价一" << ","
			<< "买量一" << ","
			<< "卖价一" << ","
			<< "卖量一" << ","
			<< "持仓量" << ","
			<< "换手率"
			<< std::endl;
		outFile.close();
	}
	else {
		char buf[1024] = { '\0' };
		sprintf(buf, "===订阅行情失败===\n返回错误--->>> ErrorID=%d, ErrorMsg=%s", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
		LogInfo(buf, LogLevel::Error);
	}
}

// 取消订阅行情应答
void WINAPI OnRspUnSubMarketData(
	CThostFtdcSpecificInstrumentField *pSpecificInstrument, 
	CThostFtdcRspInfoField *pRspInfo,
	int nRequestID, 
	bool bIsLast)
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult)
	{
		g_unSubMarketDataOK = true;		
		cond_va.notify_one();

		char logBuf[128] = { '\0' };
		sprintf(logBuf, "=====取消订阅行情成功===== \n 合约代码： %s", pSpecificInstrument->InstrumentID);
		LogInfo(logBuf);
	}
	else {
		char buf[1024] = { '\0' };
		sprintf(buf, "===取消订阅行情失败===\n返回错误--->>> ErrorID=%d, ErrorMsg=%s", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
		LogInfo(buf, LogLevel::Error);
	}
}

// 订阅询价应答
void WINAPI OnRspSubForQuoteRsp(
	CThostFtdcSpecificInstrumentField *pSpecificInstrument,
	CThostFtdcRspInfoField *pRspInfo,
	int nRequestID,
	bool bIsLast)
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult)
	{
		g_subQuoteDataOK = true;		
		cond_va.notify_one();

		char logBuf[128] = { '\0' };
		sprintf(logBuf, "=====订阅询价成功===== \n 合约代码： %s", pSpecificInstrument->InstrumentID);
		LogInfo(logBuf);

		// 取消订阅询价
		if (g_ctpMdApiTestParam.isUnSubQuoteData) {
			char* pInstrumentID[1] = { pSpecificInstrument->InstrumentID };
			int rt = g_pMdUserApi->UnSubscribeForQuoteRsp(pInstrumentID, 1);
			if (!rt)
				LogInfo(">>>>>>发送取消订阅询价请求成功");
			else
				LogInfo("--->>>发送取消订阅询价请求失败", LogLevel::Error);
		}
	}
	else {
		char buf[1024] = { '\0' };
		sprintf(buf, "===订阅询价失败===\n返回错误--->>> ErrorID=%d, ErrorMsg=%s", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
		LogInfo(buf, LogLevel::Error);
	}
}

// 取消订阅询价应答
void WINAPI OnRspUnSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult)
	{
		g_unSubQuoteDataOK = true;		
		cond_va.notify_one();

		char logBuf[128] = { '\0' };
		sprintf(logBuf, "=====取消订阅询价成功===== \n 合约代码： %s", pSpecificInstrument->InstrumentID);
		LogInfo(logBuf);
	}
	else {
		char buf[1024] = { '\0' };
		sprintf(buf, "===取消订阅询价失败===\n返回错误--->>> ErrorID=%d, ErrorMsg=%s", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
		LogInfo(buf, LogLevel::Error);
	}
}

// 行情详情通知
void WINAPI OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData)
{
	g_marketDataNoticeOK = true;	
	cond_va.notify_one();	

	// 打印行情，字段较多，截取部分
	char logBuf[1024] = { '\0' };
	sprintf(logBuf, "=====获得深度行情===== \n 交易日： %s\n 交易所代码： %s\n 合约代码： %s\n 合约在交易所的代码： %s\n 最新价： %f\n 数量： %d",
		pDepthMarketData->TradingDay, pDepthMarketData->ExchangeID,pDepthMarketData->InstrumentID, pDepthMarketData->ExchangeInstID , (float)pDepthMarketData->LastPrice, pDepthMarketData->Volume);
	LogInfo(logBuf);	
	// 如果只获取某一个合约行情，可以逐tick地存入文件或数据库
	char filePath[100] = {'\0'};
	sprintf(filePath, "%s_market_data.csv", pDepthMarketData->InstrumentID);
	std::ofstream outFile;
	outFile.open(filePath, std::ios::app); // 文件追加写入 
	outFile << pDepthMarketData->InstrumentID << "," 
		<< pDepthMarketData->UpdateTime << "." << pDepthMarketData->UpdateMillisec << "," 
		<< pDepthMarketData->LastPrice << "," 
		<< pDepthMarketData->Volume << "," 
		<< pDepthMarketData->BidPrice1 << "," 
		<< pDepthMarketData->BidVolume1 << "," 
		<< pDepthMarketData->AskPrice1 << "," 
		<< pDepthMarketData->AskVolume1 << "," 
		<< pDepthMarketData->OpenInterest << "," 
		<< pDepthMarketData->Turnover << std::endl;
	outFile.close();

	// 防止被阻塞,强制取消订阅
	if (g_ctpMdApiTestParam.isUnSubMarketData) {
		// 取消订阅行情
		char* pInstrumentID[1] = { pDepthMarketData->InstrumentID };
		int rt = g_pMdUserApi->UnSubscribeMarketData(pInstrumentID, 1);
		if (!rt)
			LogInfo(">>>>>>发送取消订阅行情请求成功");
		else
			LogInfo("--->>>发送取消订阅行情请求失败", LogLevel::Error);
	}
}

//  
void WINAPI OnRtnForQuoteRsp(CThostFtdcForQuoteRspField* pForQuoteRsp)
{
	// 部分询价结果
	char logBuf[1024] = { '\0' };
	sprintf(logBuf, "=====获得询价结果=====\n 交易日： %s\n 交易所代码： %s\n 合约代码： %s\n 询价编号： %s",
		pForQuoteRsp->TradingDay, pForQuoteRsp->ExchangeID, pForQuoteRsp->InstrumentID, pForQuoteRsp->ForQuoteSysID);
	
	LogInfo(logBuf);

	g_quoteDataNoticeOK = true;		
	cond_va.notify_one();
}

void WINAPI OnRspQryMulticastInstrument(CThostFtdcMulticastInstrumentField* pMulticastInstrument, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) {
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);

	if (!bResult) {
		char logBuf[1024] = { '\0' };		
		sprintf(logBuf, "主题号： %d\n 合约代码：%s\n 合约编号：%d\n 基准价：%f\n 合约数量乘数：%d\n 最小变动价位: %f",
			pMulticastInstrument->TopicID, pMulticastInstrument->InstrumentID, pMulticastInstrument->InstrumentNo, pMulticastInstrument->CodePrice, pMulticastInstrument->VolumeMultiple, pMulticastInstrument->PriceTick);

		LogInfo(logBuf);

		g_lookMulticastOK = true;		
		cond_va.notify_one();
	}
	else {
		char buf[1024] = { '\0' };
		sprintf(buf, "===查看合约组播失败===\n返回错误--->>> ErrorID=%d, ErrorMsg=%s", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
		LogInfo(buf, LogLevel::Error);
	}
}

void Init() {
	InitLog();

	/*mut = mutex();
	cond_va = condition_variable();*/

	// 初始化行情线程
	cout << "初始化行情..." << endl;
	g_pMdUserApi = CreateFtdcMdApi();			// 创建行情实例
	g_pMdSpi = CreateMdSpi();					// 创建行情回调	

	g_pMdUserApi->RegisterSpi(g_pMdSpi);		// 注册回调
	g_pMdUserApi->RegisterFront(gMdFrontAddr);  // 设置行情前置地址

	/// callbacks
	RegOnFrontConnected(g_pMdSpi, OnFrontConnected);
	RegOnFrontDisconnected(g_pMdSpi, OnFrontDisconnected);

	RegOnRspError(g_pMdSpi, OnRspError);
	RegOnHeartBeatWarning(g_pMdSpi, OnHeartBeatWarning);


	RegOnRspUserLogin(g_pMdSpi, OnRspUserLogin);
	RegOnRspUserLogout(g_pMdSpi, OnRspUserLogout);

	RegOnRspSubMarketData(g_pMdSpi, OnRspSubMarketData);
	RegOnRspUnSubMarketData(g_pMdSpi, OnRspUnSubMarketData);

	RegOnRspSubForQuoteRsp(g_pMdSpi, OnRspSubForQuoteRsp);
	RegOnRspUnSubForQuoteRsp(g_pMdSpi, OnRspUnSubForQuoteRsp);

	RegOnRspQryMulticastInstrument(g_pMdSpi, OnRspQryMulticastInstrument);

	RegOnRtnDepthMarketData(g_pMdSpi, OnRtnDepthMarketData);

	RegOnRtnForQuoteRsp(g_pMdSpi, OnRtnForQuoteRsp);
	
	g_pMdUserApi->Init();                                // 连接运行
}

void Release() 
{
	/*g_pMdUserApi->Release();
	g_pMdUserApi = NULL;*/
}

#pragma endregion

// 初始化
//TEST(CtpMdApiWrapperTest, 01Init) {
//
//	g_ctpMdApiTestParam = { '\0' };	
//	Init();
//
//	EXPECT_TRUE(g_pMdUserApi != NULL);
//	EXPECT_TRUE(g_pMdSpi != NULL);
//
//	Sleep(1000);
//	Release();
//}
//
//// 登录
//TEST(CtpMdApiWrapperTest, 02Login) {
//	g_ctpMdApiTestParam = { '\0' };
//	g_ctpMdApiTestParam.isLogin = true;
//	Init();		
//	
//	std::unique_lock<mutex> lck(mut);
//	cond_va.wait_for(lck, std::chrono::seconds(5), []()-> bool { return g_loginOK; });
//
//	EXPECT_TRUE(g_pMdUserApi != NULL);
//	EXPECT_TRUE(g_pMdSpi != NULL);
//	EXPECT_TRUE(g_loginOK);
//
//	Release();
//}
//
//// 登出
//TEST(CtpMdApiWrapperTest, 03Logout) {
//	g_ctpMdApiTestParam = { '\0' };
//	g_ctpMdApiTestParam.isLogin = true;
//	g_ctpMdApiTestParam.isLogout = true;
//	Init();
//	
//	std::unique_lock<mutex> lck(mut);
//	cond_va.wait_for(lck, std::chrono::seconds(5), []()-> bool { return g_logoutOK; });
//
//	EXPECT_TRUE(g_pMdUserApi != NULL);
//	EXPECT_TRUE(g_pMdSpi != NULL);
//	EXPECT_TRUE(g_loginOK);
//	EXPECT_TRUE(g_logoutOK);
//
//	Release();
//}
//
//// 订阅行情
//TEST(CtpMdApiWrapperTest, 04SubMarketData) {
//	g_ctpMdApiTestParam = { '\0' };
//	g_ctpMdApiTestParam.isLogin = true;
//	g_ctpMdApiTestParam.isSubMarketData = true;
//	g_ctpMdApiTestParam.isUnSubMarketData = true;
//	Init();
//	
//	std::unique_lock<mutex> lck(mut);
//	cond_va.wait_for(lck, std::chrono::seconds(5), []()-> bool { return g_subMarketDataOK && g_marketDataNoticeOK && g_unSubMarketDataOK; });
//
//
//	EXPECT_TRUE(g_pMdUserApi != NULL);
//	EXPECT_TRUE(g_pMdSpi != NULL);
//	EXPECT_TRUE(g_loginOK);
//	EXPECT_TRUE(g_subMarketDataOK);
//	EXPECT_TRUE(g_unSubMarketDataOK);
//
//	Release();
//}
//
//// 取消订阅行情
//TEST(CtpMdApiWrapperTest, 05UnSubMarketData) {
//	g_ctpMdApiTestParam = { '\0' };
//	g_ctpMdApiTestParam.isLogin = true;
//	g_ctpMdApiTestParam.isSubMarketData = true;
//	g_ctpMdApiTestParam.isUnSubMarketData = true;
//	Init();
//	
//	std::unique_lock<mutex> lck(mut);
//	cond_va.wait_for(lck, std::chrono::seconds(5), []()-> bool { return g_subMarketDataOK && g_marketDataNoticeOK && g_unSubMarketDataOK; });
//
//	EXPECT_TRUE(g_pMdUserApi != NULL);
//	EXPECT_TRUE(g_pMdSpi != NULL);
//	EXPECT_TRUE(g_loginOK);
//	EXPECT_TRUE(g_subMarketDataOK);
//	EXPECT_TRUE(g_unSubMarketDataOK);
//
//	Release();
//}
//
//// 行情通知
//TEST(CtpMdApiWrapperTest, 06DepthMarketDataNotify) {
//	g_ctpMdApiTestParam = { '\0' };
//	g_ctpMdApiTestParam.isLogin = true;
//	g_ctpMdApiTestParam.isSubMarketData = true;
//	g_ctpMdApiTestParam.isMarketDataNotice = true;
//	Init();
//	//LogInfo("行情通知: 开始加锁");
//	std::unique_lock<mutex> lck(mut);
//	cond_va.wait_for(lck, std::chrono::seconds(5), []()-> bool { return g_marketDataNoticeOK && g_subMarketDataOK && g_unSubMarketDataOK; });
//	LogInfo("行情通知: 已经完成");
//	EXPECT_TRUE(g_pMdUserApi != NULL);
//	EXPECT_TRUE(g_pMdSpi != NULL);
//	EXPECT_TRUE(g_loginOK);
//	EXPECT_TRUE(g_subMarketDataOK);
//	EXPECT_TRUE(g_marketDataNoticeOK);
//
//	Release();
//}
//
//// 订阅询价
//TEST(CtpMdApiWrapperTest, 07SubForQuote) {
//	g_ctpMdApiTestParam = { '\0' };
//	g_ctpMdApiTestParam.isLogin = true;
//	g_ctpMdApiTestParam.isSubQuoteData = true;	
//	Init();
//	
//	std::unique_lock<mutex> lck(mut);
//	cond_va.wait_for(lck, std::chrono::seconds(5), []()-> bool { return g_subQuoteDataOK; });
//
//	EXPECT_TRUE(g_pMdUserApi != NULL);
//	EXPECT_TRUE(g_pMdSpi != NULL);
//	EXPECT_TRUE(g_loginOK);
//	EXPECT_TRUE(g_subQuoteDataOK);	 
//
//	Release();
//}
//
//// 取消订阅询价
//TEST(CtpMdApiWrapperTest, 08UnSubForQuote) {
//	g_ctpMdApiTestParam = { '\0' };
//	g_ctpMdApiTestParam.isLogin = true;
//	g_ctpMdApiTestParam.isSubQuoteData = true;
//	g_ctpMdApiTestParam.isUnSubQuoteData = true;
//	Init();
//	
//	std::unique_lock<mutex> lck(mut);
//	cond_va.wait_for(lck, std::chrono::seconds(5), []()-> bool { return g_unSubQuoteDataOK; });
//
//	EXPECT_TRUE(g_pMdUserApi != NULL);
//	EXPECT_TRUE(g_pMdSpi != NULL);
//	EXPECT_TRUE(g_loginOK);
//	EXPECT_TRUE(g_subQuoteDataOK);
//	EXPECT_TRUE(g_unSubQuoteDataOK);
//
//	Release();
//}
//
//// 询价通知
//TEST(CtpMdApiWrapperTest, 09ForQuoteNotify) {
//	g_ctpMdApiTestParam = { '\0' };
//	g_ctpMdApiTestParam.isLogin = true;
//	g_ctpMdApiTestParam.isSubQuoteData = true;
//	g_ctpMdApiTestParam.isQuoteDataNotice = true;
//	Init();
//	
//	std::unique_lock<mutex> lck(mut);
//	cond_va.wait_for(lck, std::chrono::seconds(5), []()-> bool { return g_quoteDataNoticeOK; });
//
//	EXPECT_TRUE(g_pMdUserApi != NULL);
//	EXPECT_TRUE(g_pMdSpi != NULL);
//	EXPECT_TRUE(g_loginOK);
//	EXPECT_TRUE(g_subQuoteDataOK);
//	EXPECT_TRUE(g_quoteDataNoticeOK);
//
//	Release();
//}
//
//// 查询组播
//TEST(CtpMdApiWrapperTest, 10LookMulticast) {	
//	g_ctpMdApiTestParam = { '\0' };
//	g_ctpMdApiTestParam.isLogin = true;
//	g_ctpMdApiTestParam.isLookMulticast = true;	
//	Init();
//	
//	std::unique_lock<mutex> lck(mut);
//	cond_va.wait_for(lck, std::chrono::seconds(5), []()-> bool { return g_lookMulticastOK; });
//
//	EXPECT_TRUE(g_pMdUserApi != NULL);
//	EXPECT_TRUE(g_pMdSpi != NULL);
//	EXPECT_TRUE(g_loginOK);
//	EXPECT_TRUE(g_lookMulticastOK);
//
//	Release();
//}
//
//
