/********************************************************************
    created:	2019/1/2 19:54:16
    author:		rush
    email:		
	
    purpose:	定义 DLL 应用程序的导出函数。
*********************************************************************/
#pragma once
#include "pch.h"
#include "MdSpi.h"

extern "C"  // 以C的方式导出函数名
{
#pragma  region Api
	MDAPI_API CThostFtdcMdApi* CreateFtdcMdApi(const char* pszFlowPath = "CtpFlow/", const bool bIsUsingUdp = false, const bool bIsMulticast = false);
	MDAPI_API MdSpi*		CreateMdSpi();
	MDAPI_API void			RegisterSpi(CThostFtdcMdApi* api, MdSpi* pSpi);

	MDAPI_API const char*	GetApiVersion();			//获取接口版本

	MDAPI_API void			Release(CThostFtdcMdApi* api);

	MDAPI_API void			Init(CThostFtdcMdApi* api);

	MDAPI_API int			Join(CThostFtdcMdApi* api);

	MDAPI_API const char*	GetTradingDay(CThostFtdcMdApi* pUserApi);

	MDAPI_API void			RegisterFront(CThostFtdcMdApi* pUserApi, char* pszFrontAddress);
	MDAPI_API void			RegisterNameServer(CThostFtdcMdApi* pUserApi, char* pszNsAddress);
	MDAPI_API void			RegisterFensUserInfo(CThostFtdcMdApi* pUserApi, CThostFtdcFensUserInfoField* pFensUserInfo);

	MDAPI_API int			ReqUserLogin(CThostFtdcMdApi* pUserApi, CThostFtdcReqUserLoginField* pReqUserLoginField, int nRequestID);
	MDAPI_API int			ReqUserLogout(CThostFtdcMdApi* pUserApi, CThostFtdcUserLogoutField* pUserLogout, int nRequestID);

	MDAPI_API int			SubscribeMarketData(CThostFtdcMdApi* pUserApi, char* instrumentsID[], int nCount);
	MDAPI_API int			UnSubscribeMarketData(CThostFtdcMdApi* pUserApi, char* ppInstrumentID[], int nCount);

	// quote无意义
	MDAPI_API int			SubscribeForQuoteRsp(CThostFtdcMdApi* pUserApi, char* ppInstrumentID[], int nCount);
	MDAPI_API int			UnSubscribeForQuoteRsp(CThostFtdcMdApi* pUserApi, char* ppInstrumentID[], int nCount);

	MDAPI_API int			ReqQryMulticastInstrument(CThostFtdcMdApi* pUserApi, CThostFtdcQryMulticastInstrumentField* pQryMulticastInstrument, int nRequestID);
#pragma endregion

#pragma region
//============================================ 注册回调函数 ===========================================
	MDAPI_API void			RegOnRspError(MdSpi* spi, CBOnRspError cb);
	MDAPI_API void			RegOnHeartBeatWarning(MdSpi* spi, CBOnHeartBeatWarning cb);

	MDAPI_API void			RegOnRspFrontConnected(MdSpi* spi, CBOnRspFrontConnected cb);
	MDAPI_API void			RegOnRspFrontDisconnected(MdSpi* spi, CBOnRspFrontDisconnected cb);

	MDAPI_API void			RegOnRspUserLogin(MdSpi* spi, CBOnRspUserLogin cb);
	MDAPI_API void			RegOnRspUserLogout(MdSpi* spi, CBOnRspUserLogout cb);

	MDAPI_API void			RegOnRspSubMarketData(MdSpi* spi, CBOnRspSubMarketData cb);
	MDAPI_API void			RegOnRspUnSubMarketData(MdSpi* spi, CBOnRspUnSubMarketData cb);
	MDAPI_API void			RegOnRtnDepthMarketData(MdSpi* spi, CBOnRtnDepthMarketData cb);

	MDAPI_API void			RegOnRspSubForQuoteRsp(MdSpi* spi, CBOnRspSubForQuoteRsp cb);
	MDAPI_API void			RegOnRspUnSubForQuoteRsp(MdSpi* spi, CBOnRspUnSubForQuoteRsp cb);
	MDAPI_API void			RegOnRtnForQuoteRsp(MdSpi* spi, CBOnRtnForQuoteRsp cb);

	MDAPI_API void			RegOnRspQryMulticastInstrument(MdSpi* spi, CBOnRspQryMulticastInstrument cb);
#pragma endregion

}