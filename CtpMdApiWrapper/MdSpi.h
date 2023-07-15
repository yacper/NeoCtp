/********************************************************************
    created:	2019/1/2 19:54:16
    author:		rush
    email:		
	
    purpose:	MdSpi的扩展，为了方便插入回调函数
*********************************************************************/
#pragma once
#include "pch.h"

#pragma region 
//回调委托申明
extern "C"
{
	typedef void (WINAPI* CBOnRspError)(CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);
	typedef void (WINAPI* CBOnHeartBeatWarning)(int nTimeLapse);

	typedef void (WINAPI* CBOnRspFrontConnected)(void);
	typedef void (WINAPI* CBOnRspFrontDisconnected)(int nReason);

	typedef void (WINAPI* CBOnRspUserLogin)(CThostFtdcRspUserLoginField* pRspUserLogin, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);
	typedef void (WINAPI* CBOnRspUserLogout)(CThostFtdcUserLogoutField* pUserLogout, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);

	typedef void (WINAPI* CBOnRspSubMarketData)(CThostFtdcSpecificInstrumentField* pSpecificInstrument, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);
	typedef void (WINAPI* CBOnRspUnSubMarketData)(CThostFtdcSpecificInstrumentField* pSpecificInstrument, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);
	typedef void (WINAPI* CBOnRtnDepthMarketData)(CThostFtdcDepthMarketDataField* pDepthMarketData);

	typedef void (WINAPI* CBOnRspSubForQuoteRsp)(CThostFtdcSpecificInstrumentField* pSpecificInstrument, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);
	typedef void (WINAPI* CBOnRspUnSubForQuoteRsp)(CThostFtdcSpecificInstrumentField* pSpecificInstrument, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);
	typedef void (WINAPI* CBOnRtnForQuoteRsp)(CThostFtdcForQuoteRspField* pForQuoteRsp);

	typedef void (WINAPI* CBOnRspQryMulticastInstrument)(CThostFtdcMulticastInstrumentField* pMulticastInstrument, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);
}
#pragma endregion

class /*MDAPI_API*/ MdSpi : public CThostFtdcMdSpi
{
public:

#pragma region 
	//回调委托实例
	CBOnRspError cbOnRspError = nullptr;
	CBOnHeartBeatWarning cbOnHeartBeatWarning = 0;

	CBOnRspFrontConnected cbOnFrontConnected = 0;
	CBOnRspFrontDisconnected cbOnFrontDisconnected = 0;

	CBOnRspUserLogin cbOnRspUserLogin = 0;
	CBOnRspUserLogout cbOnRspUserLogout = 0;

	CBOnRspQryMulticastInstrument cbOnRspQryMulticastInstrument = 0;

	CBOnRspSubMarketData cbOnRspSubMarketData = 0;
	CBOnRspUnSubMarketData cbOnRspUnSubMarketData = 0;

	CBOnRspSubForQuoteRsp cbOnRspSubForQuoteRsp = 0;
	CBOnRspUnSubForQuoteRsp cbOnRspUnSubForQuoteRsp = 0;

	CBOnRtnDepthMarketData cbOnRtnDepthMarketData = 0;

	CBOnRtnForQuoteRsp cbOnRtnForQuoteRsp = 0;
#pragma endregion



	///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
	virtual void OnFrontConnected() override;
	
	///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
	///@param nReason 错误原因
	///        0x1001 网络读失败
	///        0x1002 网络写失败
	///        0x2001 接收心跳超时
	///        0x2002 发送心跳失败
	///        0x2003 收到错误报文
	virtual void OnFrontDisconnected(int nReason)override;


	///错误应答
	virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;
		
	///心跳超时警告。当长时间未收到报文时，该方法被调用。
	///@param nTimeLapse 距离上次接收报文的时间
	virtual void OnHeartBeatWarning(int nTimeLapse)override;
	

	///登录请求响应
	virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;

	///登出请求响应
	virtual void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;


	///请求查询组播合约响应
	virtual void OnRspQryMulticastInstrument(CThostFtdcMulticastInstrumentField *pMulticastInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;




	///订阅行情应答
	virtual void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;

	///取消订阅行情应答
	virtual void OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;


	///订阅询价应答
	virtual void OnRspSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;

	///取消订阅询价应答
	virtual void OnRspUnSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;


	///深度行情通知
	virtual void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData) override;

	///询价通知
	virtual void OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp) override;

};