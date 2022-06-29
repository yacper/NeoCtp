#include "pch.h"
#include "MdApi.h"
#include <filesystem>
using namespace std;


MDAPI_API CThostFtdcMdApi* CreateFtdcMdApi(const char* pszFlowPath, const bool bIsUsingUdp, const bool bIsMulticast)
{
	filesystem::path p(pszFlowPath);
	if (!filesystem::exists(pszFlowPath))
		filesystem::create_directory(p);


	CThostFtdcMdApi* api = CThostFtdcMdApi::CreateFtdcMdApi(pszFlowPath, bIsUsingUdp, bIsMulticast);

	return api;
}

MDAPI_API MdSpi*			CreateMdSpi()
{
	return new MdSpi();
}

MDAPI_API void				RegisterSpi(CThostFtdcMdApi* api, MdSpi* pSpi)
{
	api->RegisterSpi(pSpi);
}

//��ȡ�ӿڰ汾
MDAPI_API const char* GetApiVersion()
{
	return CThostFtdcMdApi::GetApiVersion();
}

MDAPI_API void Release(CThostFtdcMdApi* api)
{
	api->Release();
}

MDAPI_API void Init(CThostFtdcMdApi* api)
{
	api->Init();
}

MDAPI_API int Join(CThostFtdcMdApi* api)
{
	return api->Join();
}

MDAPI_API const char *GetTradingDay(CThostFtdcMdApi* pUserApi)
{
	if (pUserApi == NULL) return NULL;

	return pUserApi->GetTradingDay();
}

MDAPI_API void RegisterFront(CThostFtdcMdApi* pUserApi, char* pszFrontAddress)
{
	pUserApi->RegisterFront(pszFrontAddress);
}
	
MDAPI_API void RegisterNameServer(CThostFtdcMdApi* pUserApi, char* pszNsAddress)
{
	pUserApi->RegisterNameServer(pszNsAddress);
}
	
MDAPI_API void RegisterFensUserInfo(CThostFtdcMdApi* pUserApi, CThostFtdcFensUserInfoField* pFensUserInfo)
{
	pUserApi->RegisterFensUserInfo(pFensUserInfo);
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

//��¼
MDAPI_API int ReqUserLogin(CThostFtdcMdApi* pUserApi, CThostFtdcReqUserLoginField *pReqUserLoginField, int nRequestID)
{
	if (pUserApi == NULL) return -1;
	
	return pUserApi->ReqUserLogin(pReqUserLoginField, nRequestID);
}

//�ǳ�����
MDAPI_API int ReqUserLogout(CThostFtdcMdApi* pUserApi, CThostFtdcUserLogoutField *pUserLogout, int nRequestID)
{
	if (pUserApi == NULL) return -1;
	
	return pUserApi->ReqUserLogout(pUserLogout, nRequestID);
}

///�����ѯ�鲥��Լ
MDAPI_API int ReqQryMulticastInstrument(CThostFtdcMdApi* pUserApi, CThostFtdcQryMulticastInstrumentField *pQryMulticastInstrument, int nRequestID)
{
	if (pUserApi == NULL) return -1;

	return pUserApi->ReqQryMulticastInstrument(pQryMulticastInstrument, nRequestID);
}


#pragma endregion

#pragma region �ص�����

//============================================ ע��ص����� ===========================================
MDAPI_API void				RegOnRspError(MdSpi* spi, CBOnRspError cb)
{
	spi->cbOnRspError = cb;
}
//����
MDAPI_API void				RegOnHeartBeatWarning(MdSpi* spi, CBOnHeartBeatWarning cb)
{
	spi->cbOnHeartBeatWarning = cb;
}

//����Ӧ��
MDAPI_API void				RegOnFrontConnected(MdSpi* spi, CBOnFrontConnected cb)
{
	spi->cbOnFrontConnected = cb;
}
//���ӶϿ�
MDAPI_API void				RegOnFrontDisconnected(MdSpi* spi, CBOnFrontDisconnected cb)
{
	spi->cbOnFrontDisconnected = cb;
}
//��¼����Ӧ��
MDAPI_API void				RegOnRspUserLogin(MdSpi* spi, CBOnRspUserLogin cb)
{
	spi->cbOnRspUserLogin = cb;
}
//�ǳ�����Ӧ��
MDAPI_API void				RegOnRspUserLogout(MdSpi* spi, CBOnRspUserLogout cb)
{
	spi->cbOnRspUserLogout = cb;
}
//��������Ӧ��
MDAPI_API void				RegOnRspSubMarketData(MdSpi* spi, CBOnRspSubMarketData cb)
{
	spi->cbOnRspSubMarketData = cb;
}

//�˶�����Ӧ��
MDAPI_API void				RegOnRspUnSubMarketData(MdSpi* spi, CBOnRspUnSubMarketData cb)
{
	spi->cbOnRspUnSubMarketData = cb;
}


MDAPI_API void				RegOnRspSubForQuoteRsp(MdSpi* spi, CBOnRspSubForQuoteRsp cb)
{
	spi->cbOnRspSubForQuoteRsp = cb;
}

MDAPI_API void				RegOnRspUnSubForQuoteRsp(MdSpi* spi, CBOnRspUnSubForQuoteRsp cb)
{
	spi->cbOnRspUnSubForQuoteRsp = cb;
}

//�������֪ͨ
MDAPI_API void				RegOnRtnDepthMarketData(MdSpi* spi, CBOnRtnDepthMarketData cb)
{
	spi->cbOnRtnDepthMarketData = cb;
}

//ѯ��֪ͨ���ݲ�֧�֣�
MDAPI_API void				RegOnRtnForQuoteRsp(MdSpi* spi, CBOnRtnForQuoteRsp cb)
{
	spi->cbOnRtnForQuoteRsp = cb;
}
MDAPI_API void				RegOnRspQryMulticastInstrument(MdSpi* spi, CBOnRspQryMulticastInstrument cb)
{
	spi->cbOnRspQryMulticastInstrument = cb;
}
#pragma endregion

