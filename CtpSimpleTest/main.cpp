#include <iostream>
#include <stdio.h>
#include <string>
#include <unordered_map>
#include "CustomMdSpi.h"
#include "CustomTradeSpi.h"
#include "TickToKlineHelper.h"

using namespace std;

// 链接库
#pragma comment (lib, "thostmduserapi_se.lib")
#pragma comment (lib, "thosttraderapi_se.lib")

// ---- 全局变量 ---- //
// 公共参数
TThostFtdcBrokerIDType gBrokerID = "9999";                         // 模拟经纪商代码
TThostFtdcInvestorIDType gInvesterID = "";                         // 投资者账户名
TThostFtdcPasswordType gInvesterPassword = "";                     // 投资者密码

// 行情参数
CThostFtdcMdApi *g_pMdUserApi = nullptr;                           // 行情指针
//char gMdFrontAddr[] = "tcp://180.168.146.187:10211";               // 模拟行情前置地址 第一组
char gMdFrontAddr[] = "tcp://180.168.146.187:10131";               // 模拟行情前置地址 24h
char *g_pInstrumentID[] = {"rb2219", "hc2010", "i2009", "j2009"}; // 行情合约代码列表，中、上、大、郑交易所各选一种
//char* g_pInstrumentID[] = {"rb2210", "hc2210"}; // 行情合约代码列表，中、上、大、郑交易所各选一种
int instrumentNum = 1;                                             // 行情合约订阅数量
unordered_map<string, TickToKlineHelper> g_KlineHash;              // 不同合约的k线存储表

// 交易参数
CThostFtdcTraderApi *g_pTradeUserApi = nullptr;                    // 交易指针
char gTradeFrontAddr[] = "tcp://180.168.146.187:10201";            // 模拟交易前置地址 第一组
//char gTradeFrontAddr[] = "tcp://180.168.146.187:10130";            // 模拟交易前置地址 24h

TThostFtdcInstrumentIDType g_pTradeInstrumentID = "rb2210";        // 所交易的合约代码
TThostFtdcDirectionType gTradeDirection = THOST_FTDC_D_Sell;       // 买卖方向
TThostFtdcPriceType gLimitPrice = 22735;                           // 交易价格

int main()
{
	// 账号密码
	//cout << "请输入账号： ";
	//scanf("%s", gInvesterID);
	//cout << "请输入密码： ";
	//scanf("%s", gInvesterPassword);

	strcpy(gInvesterID, "097266");
	strcpy(gInvesterPassword, "hello@1234");


	// 初始化行情线程
	cout << "初始化行情..." << endl;
	g_pMdUserApi = CThostFtdcMdApi::CreateFtdcMdApi("", false, false);   // 创建行情实例
	CThostFtdcMdSpi *pMdUserSpi = new CustomMdSpi;       // 创建行情回调实例
	g_pMdUserApi->RegisterSpi(pMdUserSpi);               // 注册事件类
	g_pMdUserApi->RegisterFront(gMdFrontAddr);           // 设置行情前置地址
	g_pMdUserApi->Init();                                // 连接运行
	


	//// 初始化交易线程
	//cout << "初始化交易..." << endl;
	//g_pTradeUserApi = CThostFtdcTraderApi::CreateFtdcTraderApi(); // 创建交易实例
	////CThostFtdcTraderSpi *pTradeSpi = new CustomTradeSpi;
	//CustomTradeSpi *pTradeSpi = new CustomTradeSpi;               // 创建交易回调实例
	//g_pTradeUserApi->RegisterSpi(pTradeSpi);                      // 注册事件类
	//g_pTradeUserApi->SubscribePublicTopic(THOST_TERT_RESTART);    // 订阅公共流
	//g_pTradeUserApi->SubscribePrivateTopic(THOST_TERT_RESTART);   // 订阅私有流
	//g_pTradeUserApi->RegisterFront(gTradeFrontAddr);              // 设置交易前置地址
	//g_pTradeUserApi->Init();                                      // 连接运行
	//	

	// 等到线程退出
	g_pMdUserApi->Join();
	delete pMdUserSpi;
	g_pMdUserApi->Release();

	//g_pTradeUserApi->Join();
	//delete pTradeSpi;
	//g_pTradeUserApi->Release();

	// 转换本地k线数据
	//TickToKlineHelper tickToKlineHelper;
	//tickToKlineHelper.KLineFromLocalData("market_data.csv", "K_line_data.csv");
	
	getchar();
	return 0;
}