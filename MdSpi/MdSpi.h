// MdSpi����չ��Ϊ�˷������ص�����
#pragma once
#include "pch.h"

#ifdef MDSPI_EXPORTS
#define MDAPI_API __declspec(dllexport)
#else
#define MDAPI_API __declspec(dllimport)
#endif


#pragma region �ص�ί������


typedef int (WINAPI *CBOnRspError)(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
typedef int (WINAPI *CBOnHeartBeatWarning)(int nTimeLapse);

typedef int (WINAPI *CBOnFrontConnected)(void);
typedef int (WINAPI *CBOnFrontDisconnected)(int nReason);

typedef int (WINAPI *CBOnRspUserLogin)(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
typedef int (WINAPI *CBOnRspUserLogout)(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

typedef int (WINAPI *CBOnRspQryMulticastInstrument)(CThostFtdcMulticastInstrumentField *pMulticastInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

typedef int (WINAPI *CBOnRspSubMarketData)(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
typedef int (WINAPI *CBOnRspUnSubMarketData)(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

typedef int (WINAPI *CBOnRspSubForQuoteRsp)(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
typedef int (WINAPI *CBOnRspUnSubForQuoteRsp)(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

typedef int (WINAPI *CBOnRtnDepthMarketData)(CThostFtdcDepthMarketDataField *pDepthMarketData);

typedef int (WINAPI *CBOnRtnForQuoteRsp)(CThostFtdcForQuoteRspField *pForQuoteRsp);
#pragma endregion

class /*MDAPI_API*/ MdSpi : public CThostFtdcMdSpi
{
public:

#pragma region �ص�ί��ʵ��
	CBOnRspError cbOnRspError = 0;
	CBOnHeartBeatWarning cbOnHeartBeatWarning = 0;

	CBOnFrontConnected cbOnFrontConnected = 0;
	CBOnFrontDisconnected cbOnFrontDisconnected = 0;

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

	MdSpi(void);


	///���ͻ����뽻�׺�̨������ͨ������ʱ����δ��¼ǰ�����÷��������á�
	virtual void OnFrontConnected() override;
	
	///���ͻ����뽻�׺�̨ͨ�����ӶϿ�ʱ���÷��������á���������������API���Զ��������ӣ��ͻ��˿ɲ�������
	///@param nReason ����ԭ��
	///        0x1001 �����ʧ��
	///        0x1002 ����дʧ��
	///        0x2001 ����������ʱ
	///        0x2002 ��������ʧ��
	///        0x2003 �յ�������
	virtual void OnFrontDisconnected(int nReason)override;


	///����Ӧ��
	virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;
		
	///������ʱ���档����ʱ��δ�յ�����ʱ���÷��������á�
	///@param nTimeLapse �����ϴν��ձ��ĵ�ʱ��
	virtual void OnHeartBeatWarning(int nTimeLapse)override;
	

	///��¼������Ӧ
	virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;

	///�ǳ�������Ӧ
	virtual void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;


	///�����ѯ�鲥��Լ��Ӧ
	virtual void OnRspQryMulticastInstrument(CThostFtdcMulticastInstrumentField *pMulticastInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;




	///��������Ӧ��
	virtual void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;

	///ȡ����������Ӧ��
	virtual void OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;


	///����ѯ��Ӧ��
	virtual void OnRspSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;

	///ȡ������ѯ��Ӧ��
	virtual void OnRspUnSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;


	///�������֪ͨ
	virtual void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData) override;

	///ѯ��֪ͨ
	virtual void OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp) override;

};