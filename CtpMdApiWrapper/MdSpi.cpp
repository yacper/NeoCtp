#include "pch.h"
#include "MdSpi.h"

using namespace std;


void MdSpi::OnRspError(CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	if (cbOnRspError != NULL)
		cbOnRspError(pRspInfo, nRequestID, bIsLast);
}
void MdSpi::OnHeartBeatWarning(int nTimeLapse)
{
	if (cbOnHeartBeatWarning != NULL)
		cbOnHeartBeatWarning(nTimeLapse);
}

void MdSpi::OnFrontDisconnected(int nReason)
{
	if (cbOnFrontDisconnected != NULL)
		cbOnFrontDisconnected(nReason);
}
void MdSpi::OnFrontConnected()
{
	if (cbOnFrontConnected != NULL)
		cbOnFrontConnected();
}


void MdSpi::OnRspUserLogin(CThostFtdcRspUserLoginField* pRspUserLogin,
						   CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	if (cbOnRspUserLogin != NULL)
		cbOnRspUserLogin(pRspUserLogin, pRspInfo, nRequestID, bIsLast);
}
void MdSpi::OnRspUserLogout(CThostFtdcUserLogoutField* pUserLogout, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	if (cbOnRspUserLogout != NULL)
		cbOnRspUserLogout(pUserLogout, pRspInfo, nRequestID, bIsLast);
}


void MdSpi::OnRspQryMulticastInstrument(CThostFtdcMulticastInstrumentField* pMulticastInstrument, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	if (cbOnRspQryMulticastInstrument != NULL)
		cbOnRspQryMulticastInstrument(pMulticastInstrument, pRspInfo, nRequestID, bIsLast);
}


void MdSpi::OnRspSubMarketData(CThostFtdcSpecificInstrumentField* pSpecificInstrument, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	//cerr << __FUNCTION__ << endl;
	if (cbOnRspSubMarketData != NULL)
		cbOnRspSubMarketData(pSpecificInstrument, pRspInfo, nRequestID, bIsLast);
}
void MdSpi::OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField* pSpecificInstrument, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	//cerr << __FUNCTION__ << endl;
	if (cbOnRspUnSubMarketData != NULL)
		cbOnRspUnSubMarketData(pSpecificInstrument, pRspInfo, nRequestID, bIsLast);
}


void MdSpi::OnRspSubForQuoteRsp(CThostFtdcSpecificInstrumentField* pSpecificInstrument, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	if (cbOnRspSubForQuoteRsp != NULL)
		cbOnRspSubForQuoteRsp(pSpecificInstrument, pRspInfo, nRequestID, bIsLast);
};
void MdSpi::OnRspUnSubForQuoteRsp(CThostFtdcSpecificInstrumentField* pSpecificInstrument, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	if (cbOnRspUnSubForQuoteRsp != NULL)
		cbOnRspUnSubForQuoteRsp(pSpecificInstrument, pRspInfo, nRequestID, bIsLast);
};

void MdSpi::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField* pDepthMarketData)
{
	//cerr << "�������" << endl;
	if (cbOnRtnDepthMarketData != NULL)
		cbOnRtnDepthMarketData(pDepthMarketData);
}


void MdSpi::OnRtnForQuoteRsp(CThostFtdcForQuoteRspField* pForQuoteRsp)
{
	if (cbOnRtnForQuoteRsp != NULL)
		cbOnRtnForQuoteRsp(pForQuoteRsp);
};