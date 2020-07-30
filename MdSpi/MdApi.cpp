// MdApi.cpp : 定义 DLL 应用程序的导出函数。
//
#include "pch.h"
#include "MdSpi.h"
#include <iostream>
//#include <vector>		//动态数组,支持赋值
//using namespace std;

// 请求编号
//int iRequestID = 0;

#pragma region 请求方法

//创建回调类
MDAPI_API MdSpi*	CreateSpi()
{
	MdSpi* pUserSpi = new MdSpi();
	return pUserSpi;
}

//获取接口版本
MDAPI_API const char* GetApiVersion()
{
	return CThostFtdcMdApi::GetApiVersion();
}

//连接
MDAPI_API CThostFtdcMdApi*  Connect(char* frontAddr, char *pszFlowPath, MdSpi* pUserSpi)
{
	// 初始化UserApi
	CThostFtdcMdApi* pUserApi = CThostFtdcMdApi::CreateFtdcMdApi(pszFlowPath);			// 创建UserApi

	pUserApi->RegisterSpi((CThostFtdcMdSpi*)pUserSpi);						// 注册事件类
	pUserApi->RegisterFront(frontAddr);					// connect
	pUserApi->Init();
	//	pUserApi->Join();
	return pUserApi;
}

//断开连接
MDAPI_API void DisConnect(CThostFtdcMdApi* pUserApi)
{
	if (pUserApi == NULL) return;

	pUserApi->Release();
}

//获取当前交易日:只有登录成功后,才能得到正确的交易日
MDAPI_API const char *GetTradingDay(CThostFtdcMdApi* pUserApi)
{
	if (pUserApi == NULL) return NULL;

	return pUserApi->GetTradingDay();
}

//登录
MDAPI_API void ReqUserLogin(CThostFtdcMdApi* pUserApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcInvestorIDType investorID, TThostFtdcPasswordType password)
{
	if (pUserApi == NULL) return;

	CThostFtdcReqUserLoginField req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID, brokerID);
	strcpy_s(req.UserID, investorID);
	strcpy_s(req.Password, password);
	pUserApi->ReqUserLogin(&req, requestID);
}

//登出请求
MDAPI_API void ReqUserLogout(CThostFtdcMdApi* pUserApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcInvestorIDType investorID)
{
	if (pUserApi == NULL) return;

	CThostFtdcUserLogoutField req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID, brokerID);
	strcpy_s(req.UserID, investorID);
	pUserApi->ReqUserLogout(&req, requestID);
}
//订阅行情
MDAPI_API int SubscribeMarketData(CThostFtdcMdApi* pUserApi, char* instrumentsID[], int nCount)
{
	if (pUserApi == NULL) return -1;

	return pUserApi->SubscribeMarketData(instrumentsID, nCount);
}

//退订行情
MDAPI_API int UnSubscribeMarketData(CThostFtdcMdApi* pUserApi, char *ppInstrumentID[], int nCount)
{
	if (pUserApi == NULL) return -1;

	return pUserApi->UnSubscribeMarketData(ppInstrumentID, nCount);
}

//订阅询价。
///@param ppInstrumentID 合约ID  
///@param nCount 要订阅/退订行情的合约个数
///@remark 
MDAPI_API int SubscribeForQuoteRsp(CThostFtdcMdApi* pUserApi, char* ppInstrumentID[], int nCount)
{
	if (pUserApi == NULL) return -1;

	return pUserApi->SubscribeForQuoteRsp(ppInstrumentID, nCount);
}

	///退订询价。
	///@param ppInstrumentID 合约ID  
	///@param nCount 要订阅/退订行情的合约个数
	///@remark 
MDAPI_API int UnSubscribeForQuoteRsp(CThostFtdcMdApi* pUserApi, char* ppInstrumentID[], int nCount)
{
	if (pUserApi == NULL) return -1;

	return pUserApi->UnSubscribeForQuoteRsp(ppInstrumentID, nCount);
}

///请求查询组播合约
MDAPI_API int ReqQryMulticastInstrument(CThostFtdcMdApi* pUserApi, CThostFtdcQryMulticastInstrumentField* pQryMulticastInstrument, int nRequestID)
{
	if (pUserApi == NULL) return -1;

	return pUserApi->ReqQryMulticastInstrument(pQryMulticastInstrument, nRequestID);
}

#pragma endregion

#pragma region 回调函数

//============================================ 注册回调函数 ===========================================
MDAPI_API void WINAPI RegOnRspError(MdSpi* pUserSpi, CBOnRspError cb)
{
	pUserSpi->cbOnRspError = cb;
}
//心跳
MDAPI_API void WINAPI RegOnHeartBeatWarning(MdSpi* pUserSpi, CBOnHeartBeatWarning cb)
{
	pUserSpi->cbOnHeartBeatWarning = cb;
}

//连接应答
MDAPI_API void WINAPI RegOnFrontConnected(MdSpi* pUserSpi, CBOnFrontConnected cb)
{
	pUserSpi->cbOnFrontConnected = cb;
}
//连接断开
MDAPI_API void WINAPI RegOnFrontDisconnected(MdSpi* pUserSpi, CBOnFrontDisconnected cb)
{
	pUserSpi->cbOnFrontDisconnected = cb;
}
//登录请求应答
MDAPI_API void WINAPI RegOnRspUserLogin(MdSpi* pUserSpi, CBOnRspUserLogin cb)
{
	pUserSpi->cbOnRspUserLogin = cb;
}
//登出请求应答
MDAPI_API void WINAPI RegOnRspUserLogout(MdSpi* pUserSpi, CBOnRspUserLogout cb)
{
	pUserSpi->cbOnRspUserLogout = cb;
}
//订阅行情应答
MDAPI_API void WINAPI RegOnRspSubMarketData(MdSpi* pUserSpi, CBOnRspSubMarketData cb)
{
	pUserSpi->cbOnRspSubMarketData = cb;
}

//退订行情应答
MDAPI_API void WINAPI RegOnRspUnSubMarketData(MdSpi* pUserSpi, CBOnRspUnSubMarketData cb)
{
	pUserSpi->cbOnRspUnSubMarketData = cb;
}


MDAPI_API void WINAPI RegOnRspSubForQuoteRsp(MdSpi* pUserSpi, CBOnRspSubForQuoteRsp cb)
{
	pUserSpi->cbOnRspSubForQuoteRsp = cb;
}

MDAPI_API void WINAPI RegOnRspUnSubForQuoteRsp(MdSpi* pUserSpi, CBOnRspUnSubForQuoteRsp cb)
{
	pUserSpi->cbOnRspUnSubForQuoteRsp = cb;
}

//深度行情通知
MDAPI_API void WINAPI RegOnRtnDepthMarketData(MdSpi* pUserSpi, CBOnRtnDepthMarketData cb)
{
	pUserSpi->cbOnRtnDepthMarketData = cb;
}

MDAPI_API void WINAPI RegOnRtnForQuoteRsp(MdSpi* pUserSpi, CBOnRtnForQuoteRsp cb)
{
	pUserSpi->cbOnRtnForQuoteRsp = cb;
}
#pragma endregion