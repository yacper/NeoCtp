// MdApi.cpp : ���� DLL Ӧ�ó���ĵ���������
//
#include "pch.h"
#include "MdSpi.h"
#include <iostream>
//#include <vector>		//��̬����,֧�ָ�ֵ
//using namespace std;

// ������
//int iRequestID = 0;

#pragma region ���󷽷�

//�����ص���
MDAPI_API MdSpi*	CreateSpi()
{
	MdSpi* pUserSpi = new MdSpi();
	return pUserSpi;
}

//��ȡ�ӿڰ汾
MDAPI_API const char* GetApiVersion()
{
	return CThostFtdcMdApi::GetApiVersion();
}

//����
MDAPI_API CThostFtdcMdApi*  Connect(char* frontAddr, char *pszFlowPath, MdSpi* pUserSpi)
{
	// ��ʼ��UserApi
	CThostFtdcMdApi* pUserApi = CThostFtdcMdApi::CreateFtdcMdApi(pszFlowPath);			// ����UserApi

	pUserApi->RegisterSpi((CThostFtdcMdSpi*)pUserSpi);						// ע���¼���
	pUserApi->RegisterFront(frontAddr);					// connect
	pUserApi->Init();
	//	pUserApi->Join();
	return pUserApi;
}

//�Ͽ�����
MDAPI_API void DisConnect(CThostFtdcMdApi* pUserApi)
{
	if (pUserApi == NULL) return;

	pUserApi->Release();
}

//��ȡ��ǰ������:ֻ�е�¼�ɹ���,���ܵõ���ȷ�Ľ�����
MDAPI_API const char *GetTradingDay(CThostFtdcMdApi* pUserApi)
{
	if (pUserApi == NULL) return NULL;

	return pUserApi->GetTradingDay();
}

//��¼
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

//�ǳ�����
MDAPI_API void ReqUserLogout(CThostFtdcMdApi* pUserApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcInvestorIDType investorID)
{
	if (pUserApi == NULL) return;

	CThostFtdcUserLogoutField req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID, brokerID);
	strcpy_s(req.UserID, investorID);
	pUserApi->ReqUserLogout(&req, requestID);
}
//��������
MDAPI_API int SubscribeMarketData(CThostFtdcMdApi* pUserApi, char* instrumentsID[], int nCount)
{
	if (pUserApi == NULL) return -1;

	return pUserApi->SubscribeMarketData(instrumentsID, nCount);
}

//�˶�����
MDAPI_API int UnSubscribeMarketData(CThostFtdcMdApi* pUserApi, char *ppInstrumentID[], int nCount)
{
	if (pUserApi == NULL) return -1;

	return pUserApi->UnSubscribeMarketData(ppInstrumentID, nCount);
}

//����ѯ�ۡ�
///@param ppInstrumentID ��ԼID  
///@param nCount Ҫ����/�˶�����ĺ�Լ����
///@remark 
MDAPI_API int SubscribeForQuoteRsp(CThostFtdcMdApi* pUserApi, char* ppInstrumentID[], int nCount)
{
	if (pUserApi == NULL) return -1;

	return pUserApi->SubscribeForQuoteRsp(ppInstrumentID, nCount);
}

	///�˶�ѯ�ۡ�
	///@param ppInstrumentID ��ԼID  
	///@param nCount Ҫ����/�˶�����ĺ�Լ����
	///@remark 
MDAPI_API int UnSubscribeForQuoteRsp(CThostFtdcMdApi* pUserApi, char* ppInstrumentID[], int nCount)
{
	if (pUserApi == NULL) return -1;

	return pUserApi->UnSubscribeForQuoteRsp(ppInstrumentID, nCount);
}

///�����ѯ�鲥��Լ
MDAPI_API int ReqQryMulticastInstrument(CThostFtdcMdApi* pUserApi, CThostFtdcQryMulticastInstrumentField* pQryMulticastInstrument, int nRequestID)
{
	if (pUserApi == NULL) return -1;

	return pUserApi->ReqQryMulticastInstrument(pQryMulticastInstrument, nRequestID);
}

#pragma endregion

#pragma region �ص�����

//============================================ ע��ص����� ===========================================
MDAPI_API void WINAPI RegOnRspError(MdSpi* pUserSpi, CBOnRspError cb)
{
	pUserSpi->cbOnRspError = cb;
}
//����
MDAPI_API void WINAPI RegOnHeartBeatWarning(MdSpi* pUserSpi, CBOnHeartBeatWarning cb)
{
	pUserSpi->cbOnHeartBeatWarning = cb;
}

//����Ӧ��
MDAPI_API void WINAPI RegOnFrontConnected(MdSpi* pUserSpi, CBOnFrontConnected cb)
{
	pUserSpi->cbOnFrontConnected = cb;
}
//���ӶϿ�
MDAPI_API void WINAPI RegOnFrontDisconnected(MdSpi* pUserSpi, CBOnFrontDisconnected cb)
{
	pUserSpi->cbOnFrontDisconnected = cb;
}
//��¼����Ӧ��
MDAPI_API void WINAPI RegOnRspUserLogin(MdSpi* pUserSpi, CBOnRspUserLogin cb)
{
	pUserSpi->cbOnRspUserLogin = cb;
}
//�ǳ�����Ӧ��
MDAPI_API void WINAPI RegOnRspUserLogout(MdSpi* pUserSpi, CBOnRspUserLogout cb)
{
	pUserSpi->cbOnRspUserLogout = cb;
}
//��������Ӧ��
MDAPI_API void WINAPI RegOnRspSubMarketData(MdSpi* pUserSpi, CBOnRspSubMarketData cb)
{
	pUserSpi->cbOnRspSubMarketData = cb;
}

//�˶�����Ӧ��
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

//�������֪ͨ
MDAPI_API void WINAPI RegOnRtnDepthMarketData(MdSpi* pUserSpi, CBOnRtnDepthMarketData cb)
{
	pUserSpi->cbOnRtnDepthMarketData = cb;
}

MDAPI_API void WINAPI RegOnRtnForQuoteRsp(MdSpi* pUserSpi, CBOnRtnForQuoteRsp cb)
{
	pUserSpi->cbOnRtnForQuoteRsp = cb;
}
#pragma endregion