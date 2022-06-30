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
//char gMdFrontAddr[] = "tcp://180.168.146.187:10211";               // 模拟行情前置地址 第一组
char gMdFrontAddr[] = "tcp://180.168.146.187:10131";               // 模拟行情前置地址 24h

char* g_InstrumentID[] = { "rb2210","hc2210" };						// 行情合约代码列表，中、上、大、郑交易所各选一种
int g_InstrumentNum = 2;												// 行情合约订阅数量


//string instrumentPath = "instrument.txt";

CThostFtdcMdApi* g_pMdUserApi = nullptr;                           // 行情指针
MdSpi* g_pMdSpi = nullptr;                           // spi

bool g_FrontConnected = false;	// 网络已连接

// 登录
bool g_Logined = false;		// 已登录
bool g_logoutOK = false;

// 市场数据
int g_subMarketDataTimes = 0;
int g_unSubMarketDataTimes = 0;
bool g_marketDataNoticeOK = false;

// 询价
int g_subQuoteDataTimes = 0;
int g_unSubQuoteDataTimes = 0;
bool g_quoteDataNoticeOK = false;

// 查询组播
bool g_lookMulticastOK = false;

// 线程同步参数
mutex g_Mutex;
condition_variable g_Condition;


#pragma region Log
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
#pragma endregion

#pragma region callbacks
// 错误通知
void WINAPI
OnRspError(CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (bResult)
	{
		char buf[512] = { '\0' };
		sprintf(buf, "返回错误--->>> RequestID=%d ErrorID=%d, ErrorMsg=%s", nRequestID, pRspInfo->ErrorID, pRspInfo->ErrorMsg);
		LogInfo(buf, LogLevel::Error);

		{// 通知阻塞
			g_Condition.notify_one();
		}
	}
}

// 心跳超时警告
void WINAPI OnHeartBeatWarning(int nTimeLapse)
{
	char errorLog[128] = { '\0' };
	sprintf(errorLog, "=====网络心跳超时=====\n 距上次连接时间：%d", nTimeLapse);
	LogInfo(errorLog, LogLevel::Error);
}




class TestEnv :public testing::Environment
{
public:
	void SetUp()
	{
		InitLog();

		// 初始化行情线程
		cout << "初始化行情..." << endl;
		g_pMdUserApi = CreateFtdcMdApi();			// 创建行情实例
		g_pMdSpi = CreateMdSpi();					// 创建行情回调	

		RegisterSpi(g_pMdUserApi, g_pMdSpi);		// 注册回调
		RegisterFront(g_pMdUserApi, gMdFrontAddr);  // 设置行情前置地址

		/// callbacks
		RegOnRspError(g_pMdSpi, OnRspError);
		RegOnHeartBeatWarning(g_pMdSpi, OnHeartBeatWarning);

		//Join(g_pMdUserApi);		// 等待线程退出
	}

	void TearDown()
	{
		Release(g_pMdUserApi);
		g_pMdUserApi = NULL;
		g_pMdSpi = NULL;
	}
};

#pragma endregion

void WINAPI  OnFrontConnected()
{
	g_FrontConnected = true;

	char logBuf[128] = { '\0' };
	sprintf(logBuf, "OnFrontConnected API Version: %s", g_pMdUserApi->GetApiVersion());
	LogInfo(logBuf);

	g_Condition.notify_one();
}


// 断开连接通知
void WINAPI OnFrontDisconnected(int nReason)
{
	g_FrontConnected = false;

	char errorLog[128] = { '\0' };
	sprintf(errorLog, "=====网络连接断开===== \n 错误码：%d", nReason);
	LogInfo(errorLog, LogLevel::Error);
}


// 初始化
TEST(CtpMdApiWrapperTest, 01_Connect)
{
	ASSERT_TRUE(g_pMdUserApi != NULL);
	ASSERT_TRUE(g_pMdSpi != NULL);

	RegOnFrontConnected(g_pMdSpi, OnFrontConnected);
	RegOnFrontDisconnected(g_pMdSpi, OnFrontDisconnected);

	Init(g_pMdUserApi);                                // 连接运行

	// wait 5 secs for connecting
	std::unique_lock<mutex> lck(g_Mutex);
	g_Condition.wait_for(lck, std::chrono::seconds(5), []()-> bool { return g_FrontConnected; });

	ASSERT_TRUE(g_FrontConnected);

	ASSERT_STREQ(GetApiVersion(), "v6.3.19_P1_20200106 15:21:32");
}

// 登录应答
void WINAPI OnRspUserLogin(
	CThostFtdcRspUserLoginField* pRspUserLogin,
	CThostFtdcRspInfoField* pRspInfo,
	int nRequestID,
	bool bIsLast)
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult)
	{
		g_Logined = true;

		char buf[1024] = { '\0' };
		sprintf(buf, "=====账户登录成功===== \n 交易日： %s \n 登录时间： %s \n 经纪商： %s \n 帐户名： %s",
				pRspUserLogin->TradingDay, pRspUserLogin->LoginTime, pRspUserLogin->BrokerID, pRspUserLogin->UserID);

		LogInfo(buf);

		//return;



		//if (g_ctpMdApiTestParam.isLookMulticast)
		//{
			//}
	}
	else
	{
		char buf[1024] = { '\0' };
		sprintf(buf, "登录失败。返回错误--->>> ErrorID=%d, ErrorMsg=%s", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
		LogInfo(buf, LogLevel::Error);
	}

	g_Condition.notify_one();
}


// 登录
TEST(CtpMdApiWrapperTest, 02_Login)
{

	RegOnRspUserLogin(g_pMdSpi, OnRspUserLogin);

	// 开始登录
	CThostFtdcReqUserLoginField loginReq;
	memset(&loginReq, 0, sizeof(loginReq));
	strcpy(loginReq.BrokerID, gBrokerID);
	strcpy(loginReq.UserID, gInvesterID);
	strcpy(loginReq.Password, gInvesterPassword);
	int requestID = 0; // 请求编号

	int rt = ReqUserLogin(g_pMdUserApi, &loginReq, requestID);

	if (!rt)
		LogInfo(">>>>>>发送登录请求成功");
	else
		LogInfo("--->>>发送登录请求失败", LogLevel::Error);


	std::unique_lock<mutex> lck(g_Mutex);
	g_Condition.wait_for(lck, std::chrono::seconds(10), []()-> bool { return g_Logined; });

	ASSERT_TRUE(g_Logined);

	RegOnRspUserLogin(g_pMdSpi, nullptr);
}


// 订阅行情应答
void WINAPI OnRspSubMarketData(
	CThostFtdcSpecificInstrumentField* pSpecificInstrument,
	CThostFtdcRspInfoField* pRspInfo,
	int nRequestID,
	bool bIsLast)
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult)
	{

		char logBuf[128] = { '\0' };
		sprintf(logBuf, "=====订阅行情成功  合约代码： %s", pSpecificInstrument->InstrumentID);
		LogInfo(logBuf);

		g_subMarketDataTimes += 1;

		// 如果需要存入文件或者数据库，在这里创建表头,不同的合约单独存储
		char filePath[100] = { '\0' };
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
	else
	{
		char buf[1024] = { '\0' };
		sprintf(buf, "===订阅行情失败===\n返回错误--->>> ErrorID=%d, ErrorMsg=%s", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
		LogInfo(buf, LogLevel::Error);
	}

	g_Condition.notify_one();
}

// 行情详情通知
void WINAPI OnRtnDepthMarketData(CThostFtdcDepthMarketDataField* pDepthMarketData)
{
	// 打印行情，字段较多，截取部分
	char logBuf[1024] = { '\0' };
	sprintf(logBuf, "=====获得深度行情===== \n 交易日： %s  %s.%d\n 交易所代码： %s\n 合约代码： %s\n 合约在交易所的代码： %s\n 最新价： %f\n 数量： %d",
			pDepthMarketData->TradingDay, pDepthMarketData->UpdateTime, pDepthMarketData->UpdateMillisec, pDepthMarketData->ExchangeID, pDepthMarketData->InstrumentID, pDepthMarketData->ExchangeInstID, (float)pDepthMarketData->LastPrice, pDepthMarketData->Volume);
	LogInfo(logBuf);

	// 如果只获取某一个合约行情，可以逐tick地存入文件或数据库
	char filePath[100] = { '\0' };
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


	g_marketDataNoticeOK = true;
	g_Condition.notify_one();
}


// 订阅行情
TEST(CtpMdApiWrapperTest, 03_SubMarketData)
{
	RegOnRspSubMarketData(g_pMdSpi, OnRspSubMarketData);
	RegOnRtnDepthMarketData(g_pMdSpi, OnRtnDepthMarketData);

	// 订阅行情请求
	int rt = SubscribeMarketData(g_pMdUserApi, g_InstrumentID, g_InstrumentNum);
	if (!rt)
		LogInfo(">>>>>>发送订阅行情请求成功");
	else
		LogInfo("--->>>发送订阅行情请求失败", LogLevel::Error);


	std::unique_lock<mutex> lck(g_Mutex);
	g_Condition.wait_for(lck, std::chrono::seconds(10), []()-> bool { return g_subMarketDataTimes && g_marketDataNoticeOK; });


	EXPECT_EQ(g_subMarketDataTimes, 2);
	EXPECT_TRUE(g_marketDataNoticeOK);

	// wait for more datas
	Sleep(3000);

	//RegOnRspSubMarketData(g_pMdSpi, nullptr);
	//RegOnRtnDepthMarketData(g_pMdSpi, nullptr);
}

// 取消订阅行情应答
void WINAPI OnRspUnSubMarketData(
	CThostFtdcSpecificInstrumentField* pSpecificInstrument,
	CThostFtdcRspInfoField* pRspInfo,
	int nRequestID,
	bool bIsLast)
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult)
	{
		g_unSubMarketDataTimes += 1;

		char logBuf[128] = { '\0' };
		sprintf(logBuf, "=====取消订阅行情成功===== \n 合约代码： %s", pSpecificInstrument->InstrumentID);
		LogInfo(logBuf);
	}
	else
	{
		char buf[1024] = { '\0' };
		sprintf(buf, "===取消订阅行情失败===\n返回错误--->>> ErrorID=%d, ErrorMsg=%s", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
		LogInfo(buf, LogLevel::Error);
	}
	g_Condition.notify_one();
}


// 取消订阅深度
TEST(CtpMdApiWrapperTest, 04_UnSubMarketData)
{
	RegOnRspUnSubMarketData(g_pMdSpi, OnRspUnSubMarketData);

	// 取消订阅行情
	int rt = g_pMdUserApi->UnSubscribeMarketData(g_InstrumentID, g_InstrumentNum);
	if (!rt)
		LogInfo(">>>>>>发送取消订阅行情请求成功");
	else
		LogInfo("--->>>发送取消订阅行情请求失败", LogLevel::Error);


	std::unique_lock<mutex> lck(g_Mutex);
	// unsub 函数要被调用2次
	g_Condition.wait_for(lck, std::chrono::seconds(5), []()-> bool { return g_unSubMarketDataTimes == g_InstrumentNum; });

	EXPECT_EQ(g_unSubMarketDataTimes, g_InstrumentNum);
}

// 订阅询价应答
void WINAPI OnRspSubForQuoteRsp(
	CThostFtdcSpecificInstrumentField* pSpecificInstrument,
	CThostFtdcRspInfoField* pRspInfo,
	int nRequestID,
	bool bIsLast)
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult)
	{
		g_subQuoteDataTimes += 1;

		char logBuf[128] = { '\0' };
		sprintf(logBuf, "=====订阅询价成功===== 合约代码： %s", pSpecificInstrument->InstrumentID);
		LogInfo(logBuf);
	}
	else
	{
		char buf[1024] = { '\0' };
		sprintf(buf, "===订阅询价失败===\n返回错误--->>> ErrorID=%d, ErrorMsg=%s", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
		LogInfo(buf, LogLevel::Error);
	}
	g_Condition.notify_one();
}

void WINAPI OnRtnForQuoteRsp(CThostFtdcForQuoteRspField* pForQuoteRsp)
{
	// 部分询价结果
	char logBuf[1024] = { '\0' };
	sprintf(logBuf, "=====获得询价结果=====\n 交易日： %s\n 交易所代码： %s\n 合约代码： %s\n 询价编号： %s",
			pForQuoteRsp->TradingDay, pForQuoteRsp->ExchangeID, pForQuoteRsp->InstrumentID, pForQuoteRsp->ForQuoteSysID);

	LogInfo(logBuf);

	g_quoteDataNoticeOK = true;
	g_Condition.notify_one();
}

// 订阅询价
TEST(CtpMdApiWrapperTest, 05_SubForQuote)
{
	RegOnRspSubForQuoteRsp(g_pMdSpi, OnRspSubForQuoteRsp);
	RegOnRtnForQuoteRsp(g_pMdSpi, OnRtnForQuoteRsp);

	// 订阅询价
	int rt = SubscribeForQuoteRsp(g_pMdUserApi, g_InstrumentID, g_InstrumentNum);

	if (!rt)
		LogInfo(">>>>>>发送订阅询价请求成功");
	else
		LogInfo("--->>>发送订阅询价请求失败", LogLevel::Error);


	std::unique_lock<mutex> lck(g_Mutex);
	g_Condition.wait_for(lck, std::chrono::seconds(5), []()-> bool { return g_subQuoteDataTimes == g_InstrumentNum && g_quoteDataNoticeOK; });

	EXPECT_EQ(g_subQuoteDataTimes, g_InstrumentNum);
	EXPECT_FALSE(g_quoteDataNoticeOK);  // 总是false，quote 不会rtn，没有意义
}


// 取消订阅询价应答
void WINAPI OnRspUnSubForQuoteRsp(CThostFtdcSpecificInstrumentField* pSpecificInstrument, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult)
	{
		g_unSubQuoteDataTimes += 1;

		char logBuf[128] = { '\0' };
		sprintf(logBuf, "=====取消订阅询价成功===== 合约代码： %s", pSpecificInstrument->InstrumentID);
		LogInfo(logBuf);
	}
	else
	{
		char buf[1024] = { '\0' };
		sprintf(buf, "===取消订阅询价失败===\n返回错误--->>> ErrorID=%d, ErrorMsg=%s", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
		LogInfo(buf, LogLevel::Error);
	}
	g_Condition.notify_one();
}


// 取消订阅询价
TEST(CtpMdApiWrapperTest, 06_UnSubForQuote)
{
	RegOnRspUnSubForQuoteRsp(g_pMdSpi, OnRspUnSubForQuoteRsp);
	//取消订阅询价
	int rt = g_pMdUserApi->UnSubscribeForQuoteRsp(g_InstrumentID, g_InstrumentNum);
	if (!rt)
		LogInfo(">>>>>>发送取消订阅询价请求成功");
	else
		LogInfo("--->>>发送取消订阅询价请求失败", LogLevel::Error);


	std::unique_lock<mutex> lck(g_Mutex);
	g_Condition.wait_for(lck, std::chrono::seconds(5), []()-> bool { return g_unSubQuoteDataTimes == g_InstrumentNum; });

	EXPECT_EQ(g_unSubQuoteDataTimes, g_InstrumentNum);
}

void WINAPI OnRspQryMulticastInstrument(CThostFtdcMulticastInstrumentField* pMulticastInstrument, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);

	if (!bResult)
	{
		char logBuf[1024] = { '\0' };
		sprintf(logBuf, "主题号： %d\n 合约代码：%s\n 合约编号：%d\n 基准价：%f\n 合约数量乘数：%d\n 最小变动价位: %f",
				pMulticastInstrument->TopicID, pMulticastInstrument->InstrumentID, pMulticastInstrument->InstrumentNo, pMulticastInstrument->CodePrice, pMulticastInstrument->VolumeMultiple, pMulticastInstrument->PriceTick);

		LogInfo(logBuf);

		g_lookMulticastOK = true;
	}
	else
	{
		char buf[1024] = { '\0' };
		sprintf(buf, "===查看合约组播失败===\n返回错误--->>> ErrorID=%d, ErrorMsg=%s", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
		LogInfo(buf, LogLevel::Error);
	}
	g_Condition.notify_one();
}

// 查询组播
TEST(CtpMdApiWrapperTest, 07_LookMulticast)
{
	RegOnRspQryMulticastInstrument(g_pMdSpi, OnRspQryMulticastInstrument);

	CThostFtdcQryMulticastInstrumentField multicastInstrumentField = { '\0' };
	multicastInstrumentField.TopicID = 1001;		//对应上期所的组播行情topic			
	strcpy(multicastInstrumentField.InstrumentID, g_InstrumentID[0]);
	int rt = g_pMdUserApi->ReqQryMulticastInstrument(&multicastInstrumentField, 1);
	if (!rt)
		LogInfo(">>>>>>发送查询组播请求成功");
	else
		LogInfo("--->>>发送查询组播请求失败", LogLevel::Error);


	std::unique_lock<mutex> lck(g_Mutex);
	g_Condition.wait_for(lck, std::chrono::seconds(5), []()-> bool { return g_lookMulticastOK; });

	EXPECT_FALSE(g_lookMulticastOK);  // 正常是 ErrorID=77, ErrorMsg=CTP:无此功能
}



// 登出应答
void WINAPI OnRspUserLogout(
	CThostFtdcUserLogoutField* pUserLogout,
	CThostFtdcRspInfoField* pRspInfo,
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
	}
	else
	{
		char buf[1024] = { '\0' };
		sprintf(buf, "登出失败。返回错误--->>> ErrorID=%d, ErrorMsg=%s", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
		LogInfo(buf, LogLevel::Error);
	}

	g_Condition.notify_one();
}


// 登出
TEST(CtpMdApiWrapperTest, 08_Logout)
{
	RegOnRspUserLogout(g_pMdSpi, OnRspUserLogout);

	// 登出请求
	CThostFtdcUserLogoutField logout = { "\0" };
	std::strcpy(logout.BrokerID, gBrokerID);
	std::strcpy(logout.UserID, gInvesterID);
	int rt = ReqUserLogout(g_pMdUserApi, &logout, 33);
	if (!rt)
		LogInfo(">>>>>>发送登出请求成功");
	else
		LogInfo("--->>>发送登出请求失败", LogLevel::Error);


	std::unique_lock<mutex> lck(g_Mutex);
	g_Condition.wait_for(lck, std::chrono::seconds(5), []()-> bool { return g_logoutOK; });

	// logout 功能在测试中无法使用
	EXPECT_FALSE(g_logoutOK);  //返回错误--->>> RequestID=0 ErrorID=77, ErrorMsg=CTP:无此功能 
}




int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);

	testing::Environment* env = new TestEnv();
	testing::AddGlobalTestEnvironment(env);


	RUN_ALL_TESTS();
	getchar();
	return 0;
}
