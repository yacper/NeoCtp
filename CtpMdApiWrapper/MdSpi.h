/********************************************************************
    created:	2019/1/2 19:54:16
    author:		rush
    email:		
	
    purpose:	MdSpi����չ��Ϊ�˷������ص�����
*********************************************************************/
#pragma once
#include "pch.h"

#pragma region �ص�ί������
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
//}
#pragma endregion

class /*MDAPI_API*/ MdSpi : public CThostFtdcMdSpi
{
public:

#pragma region �ص�ί��ʵ��
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
}