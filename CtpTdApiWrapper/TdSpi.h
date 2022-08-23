/********************************************************************
    created:	2020-08-11 11:52:49
    author:		neo
    email:		
	
    purpose:	�ýӿڰ�����ԭCTP��TraderSpi����
*********************************************************************/
#pragma once
#include "pch.h"

extern "C"{

#pragma region �ص�ί������

///���ͻ����뽻�׺�̨������ͨ������ʱ����δ��¼ǰ�����÷��������á�
typedef void (WINAPI *CBOnRspFrontConnected)();

///���ͻ����뽻�׺�̨ͨ�����ӶϿ�ʱ���÷��������á���������������API���Զ��������ӣ��ͻ��˿ɲ��������
typedef void (WINAPI *CBOnRspFrontDisconnected)(int nReason);

///������ʱ���档����ʱ��δ�յ�����ʱ���÷��������á�
typedef void (WINAPI *CBOnHeartBeatWarning)(int nTimeLapse);
///�ͻ�����֤��Ӧ
typedef void (WINAPI *CBOnRspAuthenticate)(CThostFtdcRspAuthenticateField *pRspAuthenticateField, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///��¼������Ӧ
typedef void (WINAPI *CBOnRspUserLogin)(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///�ǳ�������Ӧ
typedef void (WINAPI *CBOnRspUserLogout)(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///�û��������������Ӧ
typedef void (WINAPI *CBRspUserPasswordUpdate)(CThostFtdcUserPasswordUpdateField *pUserPasswordUpdate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///�ʽ��˻��������������Ӧ
typedef void (WINAPI *CBRspTradingAccountPasswordUpdate)(CThostFtdcTradingAccountPasswordUpdateField *pTradingAccountPasswordUpdate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///��ѯ�û���ǰ֧�ֵ���֤ģʽ�Ļظ�
typedef void (WINAPI *CBRspUserAuthMethod)(CThostFtdcRspUserAuthMethodField *pRspUserAuthMethod, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///��ȡͼ����֤������Ļظ�
typedef void (WINAPI *CBRspGenUserCaptcha)(CThostFtdcRspGenUserCaptchaField *pRspGenUserCaptcha, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///��ȡ������֤������Ļظ�
typedef void (WINAPI *CBRspGenUserText)(CThostFtdcRspGenUserTextField *pRspGenUserText, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///����¼��������Ӧ
typedef void (WINAPI *CBOnRspOrderInsert)(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///Ԥ��¼��������Ӧ
typedef void (WINAPI *CBRspParkedOrderInsert)(CThostFtdcParkedOrderField *pParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///Ԥ�񳷵�¼��������Ӧ
typedef void (WINAPI *CBRspParkedOrderAction)(CThostFtdcParkedOrderActionField *pParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///��������������Ӧ
typedef void (WINAPI *CBRspOrderAction)(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///��ѯ��󱨵�������Ӧ
typedef void (WINAPI *CBRspQueryMaxOrderVolume)(CThostFtdcQueryMaxOrderVolumeField *pQueryMaxOrderVolume, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///Ͷ���߽�����ȷ����Ӧ
typedef void (WINAPI *CBOnRspSettlementInfoConfirm)(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///ɾ��Ԥ����Ӧ
typedef void (WINAPI *CBRspRemoveParkedOrder)(CThostFtdcRemoveParkedOrderField *pRemoveParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///ɾ��Ԥ�񳷵���Ӧ
typedef void (WINAPI *CBRspRemoveParkedOrderAction)(CThostFtdcRemoveParkedOrderActionField *pRemoveParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///ִ������¼��������Ӧ
typedef void (WINAPI *CBRspExecOrderInsert)(CThostFtdcInputExecOrderField *pInputExecOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///ִ���������������Ӧ
typedef void (WINAPI *CBRspExecOrderAction)(CThostFtdcInputExecOrderActionField *pInputExecOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///ѯ��¼��������Ӧ
typedef void (WINAPI *CBRspForQuoteInsert)(CThostFtdcInputForQuoteField *pInputForQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///����¼��������Ӧ
typedef void (WINAPI *CBRspQuoteInsert)(CThostFtdcInputQuoteField *pInputQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///���۲���������Ӧ
typedef void (WINAPI *CBRspQuoteAction)(CThostFtdcInputQuoteActionField *pInputQuoteAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///������������������Ӧ
typedef void (WINAPI *CBRspBatchOrderAction)(CThostFtdcInputBatchOrderActionField *pInputBatchOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///��Ȩ�ԶԳ�¼��������Ӧ
typedef void (WINAPI *CBRspOptionSelfCloseInsert)(CThostFtdcInputOptionSelfCloseField *pInputOptionSelfClose, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///��Ȩ�ԶԳ����������Ӧ
typedef void (WINAPI *CBRspOptionSelfCloseAction)(CThostFtdcInputOptionSelfCloseActionField *pInputOptionSelfCloseAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///�������¼��������Ӧ
typedef void (WINAPI *CBRspCombActionInsert)(CThostFtdcInputCombActionField *pInputCombAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///�����ѯ������Ӧ
typedef void (WINAPI *CBOnRspQryOrder)(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///�����ѯ�ɽ���Ӧ
typedef void (WINAPI *CBOnRspQryTrade)(CThostFtdcTradeField *pTrade, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///�����ѯͶ���ֲ߳���Ӧ
typedef void (WINAPI *CBOnRspQryInvestorPosition)(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///�����ѯ�ʽ��˻���Ӧ
typedef void (WINAPI *CBOnRspQryTradingAccount)(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///�����ѯͶ������Ӧ
typedef void (WINAPI *CBRspQryInvestor)(CThostFtdcInvestorField *pInvestor, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///�����ѯ���ױ�����Ӧ
typedef void (WINAPI *CBRspQryTradingCode)(CThostFtdcTradingCodeField *pTradingCode, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///�����ѯ��Լ��֤������Ӧ
typedef void (WINAPI *CBRspQryInstrumentMarginRate)(CThostFtdcInstrumentMarginRateField *pInstrumentMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///�����ѯ��Լ����������Ӧ
typedef void (WINAPI *CBRspQryInstrumentCommissionRate)(CThostFtdcInstrumentCommissionRateField *pInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///�����ѯ��������Ӧ
typedef void (WINAPI *CBRspQryExchange)(CThostFtdcExchangeField *pExchange, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///�����ѯ��Լ��Ӧ
typedef void (WINAPI *CBOnRspQryInstrument)(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///�����ѯ������Ӧ
typedef void (WINAPI *CBRspQryDepthMarketData)(CThostFtdcDepthMarketDataField *pDepthMarketData, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///�����ѯͶ���߽�������Ӧ
typedef void (WINAPI *CBRspQrySettlementInfo)(CThostFtdcSettlementInfoField *pSettlementInfo, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///�����ѯת��������Ӧ
typedef void (WINAPI *CBRspQryTransferBank)(CThostFtdcTransferBankField *pTransferBank, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///�����ѯͶ���ֲ߳���ϸ��Ӧ
typedef void (WINAPI *CBRspQryInvestorPositionDetail)(CThostFtdcInvestorPositionDetailField *pInvestorPositionDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///�����ѯ�ͻ�֪ͨ��Ӧ
typedef void (WINAPI *CBRspQryNotice)(CThostFtdcNoticeField *pNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///�����ѯ������Ϣȷ����Ӧ
typedef void (WINAPI *CBRspQrySettlementInfoConfirm)(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///�����ѯͶ���ֲ߳���ϸ��Ӧ
typedef void (WINAPI *CBRspQryInvestorPositionCombineDetail)(CThostFtdcInvestorPositionCombineDetailField *pInvestorPositionCombineDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///��ѯ��֤����ϵͳ���͹�˾�ʽ��˻���Կ��Ӧ
typedef void (WINAPI *CBRspQryCFMMCTradingAccountKey)(CThostFtdcCFMMCTradingAccountKeyField *pCFMMCTradingAccountKey, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///�����ѯ�ֵ��۵���Ϣ��Ӧ
typedef void (WINAPI *CBRspQryEWarrantOffset)(CThostFtdcEWarrantOffsetField *pEWarrantOffset, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///�����ѯͶ����Ʒ��/��Ʒ�ֱ�֤����Ӧ
typedef void (WINAPI *CBRspQryInvestorProductGroupMargin)(CThostFtdcInvestorProductGroupMarginField *pInvestorProductGroupMargin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///�����ѯ��������֤������Ӧ
typedef void (WINAPI *CBRspQryExchangeMarginRate)(CThostFtdcExchangeMarginRateField *pExchangeMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///�����ѯ������������֤������Ӧ
typedef void (WINAPI *CBRspQryExchangeMarginRateAdjust)(CThostFtdcExchangeMarginRateAdjustField *pExchangeMarginRateAdjust, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///�����ѯ������Ӧ
typedef void (WINAPI *CBRspQryExchangeRate)(CThostFtdcExchangeRateField *pExchangeRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///�����ѯ�����������Ա����Ȩ����Ӧ
typedef void (WINAPI *CBRspQrySecAgentACIDMap)(CThostFtdcSecAgentACIDMapField *pSecAgentACIDMap, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///�����ѯ��Ʒ���ۻ���
typedef void (WINAPI *CBRspQryProductExchRate)(CThostFtdcProductExchRateField *pProductExchRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///�����ѯ��Ʒ��
typedef void (WINAPI *CBRspQryProductGroup)(CThostFtdcProductGroupField *pProductGroup, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///�����ѯ�����̺�Լ����������Ӧ
typedef void (WINAPI *CBRspQryMMInstrumentCommissionRate)(CThostFtdcMMInstrumentCommissionRateField *pMMInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///�����ѯ��������Ȩ��Լ��������Ӧ
typedef void (WINAPI *CBRspQryMMOptionInstrCommRate)(CThostFtdcMMOptionInstrCommRateField *pMMOptionInstrCommRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///�����ѯ������������Ӧ
typedef void (WINAPI *CBRspQryInstrumentOrderCommRate)(CThostFtdcInstrumentOrderCommRateField *pInstrumentOrderCommRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///�����ѯ�ʽ��˻���Ӧ
typedef void (WINAPI *CBRspQrySecAgentTradingAccount)(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///�����ѯ�����������ʽ�У��ģʽ��Ӧ
typedef void (WINAPI *CBRspQrySecAgentCheckMode)(CThostFtdcSecAgentCheckModeField *pSecAgentCheckMode, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///�����ѯ������������Ϣ��Ӧ
typedef void (WINAPI *CBRspQrySecAgentTradeInfo)(CThostFtdcSecAgentTradeInfoField *pSecAgentTradeInfo, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///�����ѯ��Ȩ���׳ɱ���Ӧ
typedef void (WINAPI *CBRspQryOptionInstrTradeCost)(CThostFtdcOptionInstrTradeCostField *pOptionInstrTradeCost, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///�����ѯ��Ȩ��Լ��������Ӧ
typedef void (WINAPI *CBRspQryOptionInstrCommRate)(CThostFtdcOptionInstrCommRateField *pOptionInstrCommRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///�����ѯִ��������Ӧ
typedef void (WINAPI *CBRspQryExecOrder)(CThostFtdcExecOrderField *pExecOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///�����ѯѯ����Ӧ
typedef void (WINAPI *CBRspQryForQuote)(CThostFtdcForQuoteField *pForQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///�����ѯ������Ӧ
typedef void (WINAPI *CBRspQryQuote)(CThostFtdcQuoteField *pQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///�����ѯ��Ȩ�ԶԳ���Ӧ
typedef void (WINAPI *CBRspQryOptionSelfClose)(CThostFtdcOptionSelfCloseField *pOptionSelfClose, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///�����ѯͶ�ʵ�Ԫ��Ӧ
typedef void (WINAPI *CBRspQryInvestUnit)(CThostFtdcInvestUnitField *pInvestUnit, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///�����ѯ��Ϻ�Լ��ȫϵ����Ӧ
typedef void (WINAPI *CBRspQryCombInstrumentGuard)(CThostFtdcCombInstrumentGuardField *pCombInstrumentGuard, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///�����ѯ���������Ӧ
typedef void (WINAPI *CBRspQryCombAction)(CThostFtdcCombActionField *pCombAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///�����ѯת����ˮ��Ӧ
typedef void (WINAPI *CBRspQryTransferSerial)(CThostFtdcTransferSerialField *pTransferSerial, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///�����ѯ����ǩԼ��ϵ��Ӧ
typedef void (WINAPI *CBOnRspQryAccountregister)(CThostFtdcAccountregisterField *pAccountregister, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///����Ӧ��
typedef void (WINAPI *CBOnRspError)(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///����֪ͨ
typedef void (WINAPI *CBOnRtnOrder)(CThostFtdcOrderField *pOrder);
///�ɽ�֪ͨ
typedef void (WINAPI *CBOnRtnTrade)(CThostFtdcTradeField *pTrade);
///����¼�����ر�
typedef void (WINAPI *CBOnErrRtnOrderInsert)(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo);
///������������ر�
typedef void (WINAPI *CBOnErrRtnOrderAction)(CThostFtdcOrderActionField *pOrderAction, CThostFtdcRspInfoField *pRspInfo);
///��Լ����״̬֪ͨ
typedef void (WINAPI *CBRtnInstrumentStatus)(CThostFtdcInstrumentStatusField *pInstrumentStatus);
///����֪ͨ
typedef void (WINAPI *CBRtnTradingNotice)(CThostFtdcTradingNoticeInfoField *pTradingNoticeInfo);
///��ʾ������У�����
typedef void (WINAPI *CBRtnErrorConditionalOrder)(CThostFtdcErrorConditionalOrderField *pErrorConditionalOrder);
///ִ������֪ͨ
typedef void (WINAPI *CBRtnExecOrder)(CThostFtdcExecOrderField *pExecOrder);
///ִ������¼�����ر�
typedef void (WINAPI *CBErrRtnExecOrderInsert)(CThostFtdcInputExecOrderField *pInputExecOrder, CThostFtdcRspInfoField *pRspInfo);
///ִ�������������ر�
typedef void (WINAPI *CBErrRtnExecOrderAction)(CThostFtdcExecOrderActionField *pExecOrderAction, CThostFtdcRspInfoField *pRspInfo);
///ѯ��¼�����ر�
typedef void (WINAPI *CBErrRtnForQuoteInsert)(CThostFtdcInputForQuoteField *pInputForQuote, CThostFtdcRspInfoField *pRspInfo);
///����֪ͨ
typedef void (WINAPI *CBRtnQuote)(CThostFtdcQuoteField *pQuote);
///����¼�����ر�
typedef void (WINAPI *CBErrRtnQuoteInsert)(CThostFtdcInputQuoteField *pInputQuote, CThostFtdcRspInfoField *pRspInfo);
///���۲�������ر�
typedef void (WINAPI *CBErrRtnQuoteAction)(CThostFtdcQuoteActionField *pQuoteAction, CThostFtdcRspInfoField *pRspInfo);
///ѯ��֪ͨ
typedef void (WINAPI *CBRtnForQuoteRsp)(CThostFtdcForQuoteRspField *pForQuoteRsp);
///��֤���������û�����
typedef void (WINAPI *CBRtnCFMMCTradingAccountToken)(CThostFtdcCFMMCTradingAccountTokenField *pCFMMCTradingAccountToken);
///����������������ر�
typedef void (WINAPI *CBErrRtnBatchOrderAction)(CThostFtdcBatchOrderActionField *pBatchOrderAction, CThostFtdcRspInfoField *pRspInfo);
///��Ȩ�ԶԳ�֪ͨ
typedef void (WINAPI *CBRtnOptionSelfClose)(CThostFtdcOptionSelfCloseField *pOptionSelfClose);
///��Ȩ�ԶԳ�¼�����ر�
typedef void (WINAPI *CBErrRtnOptionSelfCloseInsert)(CThostFtdcInputOptionSelfCloseField *pInputOptionSelfClose, CThostFtdcRspInfoField *pRspInfo);
///��Ȩ�ԶԳ��������ر�
typedef void (WINAPI *CBErrRtnOptionSelfCloseAction)(CThostFtdcOptionSelfCloseActionField *pOptionSelfCloseAction, CThostFtdcRspInfoField *pRspInfo);
///�������֪ͨ
typedef void (WINAPI *CBRtnCombAction)(CThostFtdcCombActionField *pCombAction);
///�������¼�����ر�
typedef void (WINAPI *CBErrRtnCombActionInsert)(CThostFtdcInputCombActionField *pInputCombAction, CThostFtdcRspInfoField *pRspInfo);
///�����ѯǩԼ������Ӧ
typedef void (WINAPI *CBRspQryContractBank)(CThostFtdcContractBankField *pContractBank, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///�����ѯԤ����Ӧ
typedef void (WINAPI *CBRspQryParkedOrder)(CThostFtdcParkedOrderField *pParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///�����ѯԤ�񳷵���Ӧ
typedef void (WINAPI *CBRspQryParkedOrderAction)(CThostFtdcParkedOrderActionField *pParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///�����ѯ����֪ͨ��Ӧ
typedef void (WINAPI *CBRspQryTradingNotice)(CThostFtdcTradingNoticeField *pTradingNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///�����ѯ���͹�˾���ײ�����Ӧ
typedef void (WINAPI *CBRspQryBrokerTradingParams)(CThostFtdcBrokerTradingParamsField *pBrokerTradingParams, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///�����ѯ���͹�˾�����㷨��Ӧ
typedef void (WINAPI *CBRspQryBrokerTradingAlgos)(CThostFtdcBrokerTradingAlgosField *pBrokerTradingAlgos, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///�����ѯ��������û�����
typedef void (WINAPI *CBRspQueryCFMMCTradingAccountToken)(CThostFtdcQueryCFMMCTradingAccountTokenField *pQueryCFMMCTradingAccountToken, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///���з��������ʽ�ת�ڻ�֪ͨ
typedef void (WINAPI *CBRtnFromBankToFutureByBank)(CThostFtdcRspTransferField *pRspTransfer);
///���з����ڻ��ʽ�ת����֪ͨ
typedef void (WINAPI *CBRtnFromFutureToBankByBank)(CThostFtdcRspTransferField *pRspTransfer);
///���з����������ת�ڻ�֪ͨ
typedef void (WINAPI *CBRtnRepealFromBankToFutureByBank)(CThostFtdcRspRepealField *pRspRepeal);
///���з�������ڻ�ת����֪ͨ
typedef void (WINAPI *CBRtnRepealFromFutureToBankByBank)(CThostFtdcRspRepealField *pRspRepeal);
///�ڻ����������ʽ�ת�ڻ�֪ͨ
typedef void (WINAPI *CBRtnFromBankToFutureByFuture)(CThostFtdcRspTransferField *pRspTransfer);
///�ڻ������ڻ��ʽ�ת����֪ͨ
typedef void (WINAPI *CBRtnFromFutureToBankByFuture)(CThostFtdcRspTransferField *pRspTransfer);
///ϵͳ����ʱ�ڻ����ֹ������������ת�ڻ��������д�����Ϻ��̷��ص�֪ͨ
typedef void (WINAPI *CBRtnRepealFromBankToFutureByFutureManual)(CThostFtdcRspRepealField *pRspRepeal);
///ϵͳ����ʱ�ڻ����ֹ���������ڻ�ת�����������д�����Ϻ��̷��ص�֪ͨ
typedef void (WINAPI *CBRtnRepealFromFutureToBankByFutureManual)(CThostFtdcRspRepealField *pRspRepeal);
///�ڻ������ѯ�������֪ͨ
typedef void (WINAPI *CBRtnQueryBankBalanceByFuture)(CThostFtdcNotifyQueryAccountField *pNotifyQueryAccount);
///�ڻ����������ʽ�ת�ڻ�����ر�
typedef void (WINAPI *CBErrRtnBankToFutureByFuture)(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo);
///�ڻ������ڻ��ʽ�ת���д���ر�
typedef void (WINAPI *CBErrRtnFutureToBankByFuture)(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo);
///ϵͳ����ʱ�ڻ����ֹ������������ת�ڻ�����ر�
typedef void (WINAPI *CBErrRtnRepealBankToFutureByFutureManual)(CThostFtdcReqRepealField *pReqRepeal, CThostFtdcRspInfoField *pRspInfo);
///ϵͳ����ʱ�ڻ����ֹ���������ڻ�ת���д���ر�
typedef void (WINAPI *CBErrRtnRepealFutureToBankByFutureManual)(CThostFtdcReqRepealField *pReqRepeal, CThostFtdcRspInfoField *pRspInfo);
///�ڻ������ѯ����������ر�
typedef void (WINAPI *CBErrRtnQueryBankBalanceByFuture)(CThostFtdcReqQueryAccountField *pReqQueryAccount, CThostFtdcRspInfoField *pRspInfo);
///�ڻ������������ת�ڻ��������д�����Ϻ��̷��ص�֪ͨ
typedef void (WINAPI *CBRtnRepealFromBankToFutureByFuture)(CThostFtdcRspRepealField *pRspRepeal);
///�ڻ���������ڻ�ת�����������д�����Ϻ��̷��ص�֪ͨ
typedef void (WINAPI *CBRtnRepealFromFutureToBankByFuture)(CThostFtdcRspRepealField *pRspRepeal);
///�ڻ����������ʽ�ת�ڻ�Ӧ��
typedef void (WINAPI *CBRspFromBankToFutureByFuture)(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///�ڻ������ڻ��ʽ�ת����Ӧ��
typedef void (WINAPI *CBRspFromFutureToBankByFuture)(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///�ڻ������ѯ�������Ӧ��
typedef void (WINAPI *CBRspQueryBankAccountMoneyByFuture)(CThostFtdcReqQueryAccountField *pReqQueryAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///���з������ڿ���֪ͨ
typedef void (WINAPI *CBRtnOpenAccountByBank)(CThostFtdcOpenAccountField *pOpenAccount);
///���з�����������֪ͨ
typedef void (WINAPI *CBRtnCancelAccountByBank)(CThostFtdcCancelAccountField *pCancelAccount);
///���з����������˺�֪ͨ
typedef void (WINAPI *CBRtnChangeAccountByBank)(CThostFtdcChangeAccountField *pChangeAccount);

}

#pragma endregion

class TraderSpi : public CThostFtdcTraderSpi
{
public:
#pragma region �ص�ί��ʵ��
	///ί��ʵ��
	CBOnRspFrontConnected cbOnFrontConnected = 0;		///���ͻ����뽻�׺�̨������ͨ������ʱ����δ��¼ǰ�����÷��������á�
	CBOnRspFrontDisconnected cbOnFrontDisconnected = 0;		///���ͻ����뽻�׺�̨ͨ�����ӶϿ�ʱ���÷��������á���������������API���Զ��������ӣ��ͻ��˿ɲ��������
	CBOnHeartBeatWarning cbOnHeartBeatWarning = 0;		///������ʱ���档����ʱ��δ�յ�����ʱ���÷��������á�
	CBOnRspAuthenticate cbOnRspAuthenticate = 0;	///�ͻ�����֤��Ӧ
	CBOnRspUserLogin cbOnRspUserLogin = 0;	///��¼������Ӧ
	CBOnRspUserLogout cbOnRspUserLogout = 0;	///�ǳ�������Ӧ
	CBRspUserPasswordUpdate cbRspUserPasswordUpdate = 0;	///�û��������������Ӧ
	CBRspTradingAccountPasswordUpdate cbRspTradingAccountPasswordUpdate = 0;	///�ʽ��˻��������������Ӧ
	CBRspUserAuthMethod cbRspUserAuthMethod = 0; ///��ѯ�û���ǰ֧�ֵ���֤ģʽ�Ļظ�
	CBRspGenUserCaptcha cbRspGenUserCaptcha = 0; ///��ȡͼ����֤������Ļظ�
	CBRspGenUserText cbRspGenUserText = 0; ///��ȡ������֤������Ļظ�
	CBOnRspOrderInsert cbRspOrderInsert = 0;	///����¼��������Ӧ
	CBRspParkedOrderInsert cbRspParkedOrderInsert = 0;	///Ԥ��¼��������Ӧ
	CBRspParkedOrderAction cbRspParkedOrderAction = 0;	///Ԥ�񳷵�¼��������Ӧ
	CBRspOrderAction cbRspOrderAction = 0;	///��������������Ӧ
	CBRspQueryMaxOrderVolume cbRspQueryMaxOrderVolume = 0;	///��ѯ��󱨵�������Ӧ
	CBOnRspSettlementInfoConfirm cbRspSettlementInfoConfirm = 0;	///Ͷ���߽�����ȷ����Ӧ
	CBRspRemoveParkedOrder cbRspRemoveParkedOrder = 0;	///ɾ��Ԥ����Ӧ
	CBRspRemoveParkedOrderAction cbRspRemoveParkedOrderAction = 0;	///ɾ��Ԥ�񳷵���Ӧ
	CBRspExecOrderInsert cbRspExecOrderInsert = 0;	///ִ������¼��������Ӧ
	CBRspExecOrderAction cbRspExecOrderAction = 0;	///ִ���������������Ӧ
	CBRspForQuoteInsert cbRspForQuoteInsert = 0;	///ѯ��¼��������Ӧ
	CBRspQuoteInsert cbRspQuoteInsert = 0;	///����¼��������Ӧ
	CBRspQuoteAction cbRspQuoteAction = 0;	///���۲���������Ӧ
	CBRspBatchOrderAction cbRspBatchOrderAction = 0;	///������������������Ӧ
	CBRspOptionSelfCloseInsert cbRspOptionSelfCloseInsert = 0;	///��Ȩ�ԶԳ�¼��������Ӧ
	CBRspOptionSelfCloseAction cbRspOptionSelfCloseAction = 0; ///��Ȩ�ԶԳ����������Ӧ
	CBRspCombActionInsert cbRspCombActionInsert = 0;	///�������¼��������Ӧ
	CBOnRspQryOrder cbRspQryOrder = 0;	///�����ѯ������Ӧ
	CBOnRspQryTrade cbRspQryTrade = 0;	///�����ѯ�ɽ���Ӧ
	CBOnRspQryInvestorPosition cbRspQryInvestorPosition = 0;	///�����ѯͶ���ֲ߳���Ӧ
	CBOnRspQryTradingAccount cbRspQryTradingAccount = 0;	///�����ѯ�ʽ��˻���Ӧ
	CBRspQryInvestor cbRspQryInvestor = 0;	///�����ѯͶ������Ӧ
	CBRspQryTradingCode cbRspQryTradingCode = 0;	///�����ѯ���ױ�����Ӧ
	CBRspQryInstrumentMarginRate cbRspQryInstrumentMarginRate = 0;	///�����ѯ��Լ��֤������Ӧ
	CBRspQryInstrumentCommissionRate cbRspQryInstrumentCommissionRate = 0;	///�����ѯ��Լ����������Ӧ
	CBRspQryExchange cbRspQryExchange = 0;	///�����ѯ��������Ӧ
	CBOnRspQryInstrument cbRspQryInstrument = 0;	///�����ѯ��Լ��Ӧ
	CBRspQryDepthMarketData cbRspQryDepthMarketData = 0;	///�����ѯ������Ӧ
	CBRspQrySettlementInfo cbRspQrySettlementInfo = 0;	///�����ѯͶ���߽�������Ӧ
	CBRspQryTransferBank cbRspQryTransferBank = 0;	///�����ѯת��������Ӧ
	CBRspQryInvestorPositionDetail cbRspQryInvestorPositionDetail = 0;	///�����ѯͶ���ֲ߳���ϸ��Ӧ
	CBRspQryNotice cbRspQryNotice = 0;	///�����ѯ�ͻ�֪ͨ��Ӧ
	CBRspQrySettlementInfoConfirm cbRspQrySettlementInfoConfirm = 0;	///�����ѯ������Ϣȷ����Ӧ
	CBRspQryInvestorPositionCombineDetail cbRspQryInvestorPositionCombineDetail = 0;	///�����ѯͶ���ֲ߳���ϸ��Ӧ
	CBRspQryCFMMCTradingAccountKey cbRspQryCFMMCTradingAccountKey = 0;	///��ѯ��֤����ϵͳ���͹�˾�ʽ��˻���Կ��Ӧ
	CBRspQryEWarrantOffset cbRspQryEWarrantOffset = 0;	///�����ѯ�ֵ��۵���Ϣ��Ӧ
	CBRspQryInvestorProductGroupMargin cbRspQryInvestorProductGroupMargin = 0;	///�����ѯͶ����Ʒ��/��Ʒ�ֱ�֤����Ӧ
	CBRspQryExchangeMarginRate cbRspQryExchangeMarginRate = 0;	///�����ѯ��������֤������Ӧ
	CBRspQryExchangeMarginRateAdjust cbRspQryExchangeMarginRateAdjust = 0;	///�����ѯ������������֤������Ӧ
	CBRspQryExchangeRate cbRspQryExchangeRate = 0;	///�����ѯ������Ӧ
	CBRspQrySecAgentACIDMap cbRspQrySecAgentACIDMap = 0;	///�����ѯ�����������Ա����Ȩ����Ӧ
	CBRspQryProductExchRate cbRspQryProductExchRate = 0;	///�����ѯ��Ʒ���ۻ���
	CBRspQryProductGroup cbRspQryProductGroup = 0;	///�����ѯ��Ʒ��
	CBRspQryMMInstrumentCommissionRate cbRspQryMMInstrumentCommissionRate = 0;	///�����ѯ�����̺�Լ����������Ӧ
	CBRspQryMMOptionInstrCommRate cbRspQryMMOptionInstrCommRate = 0;	///�����ѯ��������Ȩ��Լ��������Ӧ
	CBRspQryInstrumentOrderCommRate cbRspQryInstrumentOrderCommRate = 0;	///�����ѯ������������Ӧ
	CBRspQrySecAgentTradingAccount cbRspQrySecAgentTradingAccount = 0;	///�����ѯ�ʽ��˻���Ӧ
	CBRspQrySecAgentCheckMode cbRspQrySecAgentCheckMode = 0;	///�����ѯ�����������ʽ�У��ģʽ��Ӧ
	CBRspQrySecAgentTradeInfo cbRspQrySecAgentTradeInfo = 0;	///�����ѯ������������Ϣ��Ӧ
	CBRspQryOptionInstrTradeCost cbRspQryOptionInstrTradeCost = 0;	///�����ѯ��Ȩ���׳ɱ���Ӧ
	CBRspQryOptionInstrCommRate cbRspQryOptionInstrCommRate = 0;	///�����ѯ��Ȩ��Լ��������Ӧ
	CBRspQryExecOrder cbRspQryExecOrder = 0;	///�����ѯִ��������Ӧ
	CBRspQryForQuote cbRspQryForQuote = 0;	///�����ѯѯ����Ӧ
	CBRspQryQuote cbRspQryQuote = 0;	///�����ѯ������Ӧ
	CBRspQryOptionSelfClose cbRspQryOptionSelfClose = 0;	///�����ѯ��Ȩ�ԶԳ���Ӧ
	CBRspQryInvestUnit cbRspQryInvestUnit = 0;	///�����ѯͶ�ʵ�Ԫ��Ӧ
	CBRspQryCombInstrumentGuard cbRspQryCombInstrumentGuard = 0;	///�����ѯ��Ϻ�Լ��ȫϵ����Ӧ
	CBRspQryCombAction cbRspQryCombAction = 0;	///�����ѯ���������Ӧ
	CBRspQryTransferSerial cbRspQryTransferSerial = 0;	///�����ѯת����ˮ��Ӧ
	CBOnRspQryAccountregister cbRspQryAccountregister = 0;///�����ѯ����ǩԼ��ϵ��Ӧ
	CBOnRspError cbRspError = 0;	///����Ӧ��
	CBOnRtnOrder cbRtnOrder = 0;	///����֪ͨ
	CBOnRtnTrade cbRtnTrade = 0;	///�ɽ�֪ͨ
	CBOnErrRtnOrderInsert cbErrRtnOrderInsert = 0;	///����¼�����ر�
	CBOnErrRtnOrderAction cbErrRtnOrderAction = 0;	///������������ر�
	CBRtnInstrumentStatus cbRtnInstrumentStatus = 0;	///��Լ����״̬֪ͨ
	CBRtnTradingNotice cbRtnTradingNotice = 0;	///����֪ͨ
	CBRtnErrorConditionalOrder cbRtnErrorConditionalOrder = 0;	///��ʾ������У�����
	CBRtnExecOrder cbRtnExecOrder = 0;	///ִ������֪ͨ
	CBErrRtnExecOrderInsert cbErrRtnExecOrderInsert = 0;	///ִ������¼�����ر�
	CBErrRtnExecOrderAction cbErrRtnExecOrderAction = 0;	///ִ�������������ر�
	CBErrRtnForQuoteInsert cbErrRtnForQuoteInsert = 0;	///ѯ��¼�����ر�
	CBRtnQuote cbRtnQuote = 0;	///����֪ͨ
	CBErrRtnQuoteInsert cbErrRtnQuoteInsert = 0;	///����¼�����ر�
	CBErrRtnQuoteAction cbErrRtnQuoteAction = 0;	///���۲�������ر�
	CBRtnForQuoteRsp cbRtnForQuoteRsp = 0;	///ѯ��֪ͨ
	CBRtnCFMMCTradingAccountToken cbRtnCFMMCTradingAccountToken = 0;	///��֤���������û�����
	CBErrRtnBatchOrderAction cbErrRtnBatchOrderAction = 0;	///����������������ر�
	CBRtnOptionSelfClose cbRtnOptionSelfClose = 0;	///��Ȩ�ԶԳ�֪ͨ
	CBErrRtnOptionSelfCloseInsert cbErrRtnOptionSelfCloseInsert = 0;	///��Ȩ�ԶԳ�¼�����ر�
	CBErrRtnOptionSelfCloseAction cbErrRtnOptionSelfCloseAction = 0;	///��Ȩ�ԶԳ��������ر�
	CBRtnCombAction cbRtnCombAction = 0;	///�������֪ͨ
	CBErrRtnCombActionInsert cbErrRtnCombActionInsert = 0;	///�������¼�����ر�
	CBRspQryContractBank cbRspQryContractBank = 0;	///�����ѯǩԼ������Ӧ
	CBRspQryParkedOrder cbRspQryParkedOrder = 0;	///�����ѯԤ����Ӧ
	CBRspQryParkedOrderAction cbRspQryParkedOrderAction = 0;	///�����ѯԤ�񳷵���Ӧ
	CBRspQryTradingNotice cbRspQryTradingNotice = 0;	///�����ѯ����֪ͨ��Ӧ
	CBRspQryBrokerTradingParams cbRspQryBrokerTradingParams = 0;	///�����ѯ���͹�˾���ײ�����Ӧ
	CBRspQryBrokerTradingAlgos cbRspQryBrokerTradingAlgos = 0;	///�����ѯ���͹�˾�����㷨��Ӧ
	CBRspQueryCFMMCTradingAccountToken cbRspQueryCFMMCTradingAccountToken = 0;	///�����ѯ��������û�����
	CBRtnFromBankToFutureByBank cbRtnFromBankToFutureByBank = 0;	///���з��������ʽ�ת�ڻ�֪ͨ
	CBRtnFromFutureToBankByBank cbRtnFromFutureToBankByBank = 0;	///���з����ڻ��ʽ�ת����֪ͨ
	CBRtnRepealFromBankToFutureByBank cbRtnRepealFromBankToFutureByBank = 0;	///���з����������ת�ڻ�֪ͨ
	CBRtnRepealFromFutureToBankByBank cbRtnRepealFromFutureToBankByBank = 0;	///���з�������ڻ�ת����֪ͨ
	CBRtnFromBankToFutureByFuture cbRtnFromBankToFutureByFuture = 0;	///�ڻ����������ʽ�ת�ڻ�֪ͨ
	CBRtnFromFutureToBankByFuture cbRtnFromFutureToBankByFuture = 0;	///�ڻ������ڻ��ʽ�ת����֪ͨ
	CBRtnRepealFromBankToFutureByFutureManual cbRtnRepealFromBankToFutureByFutureManual = 0;	///ϵͳ����ʱ�ڻ����ֹ������������ת�ڻ��������д�����Ϻ��̷��ص�֪ͨ
	CBRtnRepealFromFutureToBankByFutureManual cbRtnRepealFromFutureToBankByFutureManual = 0;	///ϵͳ����ʱ�ڻ����ֹ���������ڻ�ת�����������д�����Ϻ��̷��ص�֪ͨ
	CBRtnQueryBankBalanceByFuture cbRtnQueryBankBalanceByFuture = 0;	///�ڻ������ѯ�������֪ͨ
	CBErrRtnBankToFutureByFuture cbErrRtnBankToFutureByFuture = 0;	///�ڻ����������ʽ�ת�ڻ�����ر�
	CBErrRtnFutureToBankByFuture cbErrRtnFutureToBankByFuture = 0;	///�ڻ������ڻ��ʽ�ת���д���ر�
	CBErrRtnRepealBankToFutureByFutureManual cbErrRtnRepealBankToFutureByFutureManual = 0;	///ϵͳ����ʱ�ڻ����ֹ������������ת�ڻ�����ر�
	CBErrRtnRepealFutureToBankByFutureManual cbErrRtnRepealFutureToBankByFutureManual = 0;	///ϵͳ����ʱ�ڻ����ֹ���������ڻ�ת���д���ر�
	CBErrRtnQueryBankBalanceByFuture cbErrRtnQueryBankBalanceByFuture = 0;	///�ڻ������ѯ����������ر�
	CBRtnRepealFromBankToFutureByFuture cbRtnRepealFromBankToFutureByFuture = 0;	///�ڻ������������ת�ڻ��������д�����Ϻ��̷��ص�֪ͨ
	CBRtnRepealFromFutureToBankByFuture cbRtnRepealFromFutureToBankByFuture = 0;	///�ڻ���������ڻ�ת�����������д�����Ϻ��̷��ص�֪ͨ
	CBRspFromBankToFutureByFuture cbRspFromBankToFutureByFuture = 0;	///�ڻ����������ʽ�ת�ڻ�Ӧ��
	CBRspFromFutureToBankByFuture cbRspFromFutureToBankByFuture = 0;	///�ڻ������ڻ��ʽ�ת����Ӧ��
	CBRspQueryBankAccountMoneyByFuture cbRspQueryBankAccountMoneyByFuture = 0;	///�ڻ������ѯ�������Ӧ��
	CBRtnOpenAccountByBank cbRtnOpenAccountByBank = 0;	///���з������ڿ���֪ͨ
	CBRtnCancelAccountByBank cbRtnCancelAccountByBank = 0;	///���з�����������֪ͨ
	CBRtnChangeAccountByBank cbRtnChangeAccountByBank = 0;	///���з����������˺�֪ͨ
#pragma endregion


#pragma region Interface
	///���ͻ����뽻�׺�̨������ͨ������ʱ����δ��¼ǰ�����÷��������á�
	virtual void OnFrontConnected() ;
	
	///���ͻ����뽻�׺�̨ͨ�����ӶϿ�ʱ���÷��������á���������������API���Զ��������ӣ��ͻ��˿ɲ��������
	///@param nReason ����ԭ��
	///        0x1001 �����ʧ��
	///        0x1002 ����дʧ��
	///        0x2001 ����������ʱ
	///        0x2002 ��������ʧ��
	///        0x2003 �յ�������
	virtual void OnFrontDisconnected(int nReason) ;
		
	///������ʱ���档����ʱ��δ�յ�����ʱ���÷��������á�
	///@param nTimeLapse �����ϴν��ձ��ĵ�ʱ��
	virtual void OnHeartBeatWarning(int nTimeLapse) ;
	

	///�ͻ�����֤��Ӧ
	virtual void OnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticateField, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///��¼������Ӧ
	virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;
	///�ǳ�������Ӧ
	virtual void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///�û��������������Ӧ
	virtual void OnRspUserPasswordUpdate(CThostFtdcUserPasswordUpdateField *pUserPasswordUpdate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;
	///�ʽ��˻��������������Ӧ
	virtual void OnRspTradingAccountPasswordUpdate(CThostFtdcTradingAccountPasswordUpdateField *pTradingAccountPasswordUpdate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///��ѯ�û���ǰ֧�ֵ���֤ģʽ�Ļظ�
	virtual void OnRspUserAuthMethod(CThostFtdcRspUserAuthMethodField *pRspUserAuthMethod, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///��ȡͼ����֤������Ļظ�
	virtual void OnRspGenUserCaptcha(CThostFtdcRspGenUserCaptchaField *pRspGenUserCaptcha, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;
	///��ȡ������֤������Ļظ�
	virtual void OnRspGenUserText(CThostFtdcRspGenUserTextField *pRspGenUserText, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;



	///����¼��������Ӧ
	virtual void OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;
	///Ԥ��¼��������Ӧ
	virtual void OnRspParkedOrderInsert(CThostFtdcParkedOrderField *pParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;
	///Ԥ�񳷵�¼��������Ӧ
	virtual void OnRspParkedOrderAction(CThostFtdcParkedOrderActionField *pParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///��������������Ӧ
	virtual void OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///��ѯ��󱨵�������Ӧ
	virtual void OnRspQueryMaxOrderVolume(CThostFtdcQueryMaxOrderVolumeField *pQueryMaxOrderVolume, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///Ͷ���߽�����ȷ����Ӧ
	virtual void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///ɾ��Ԥ����Ӧ
	virtual void OnRspRemoveParkedOrder(CThostFtdcRemoveParkedOrderField *pRemoveParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///ɾ��Ԥ�񳷵���Ӧ
	virtual void OnRspRemoveParkedOrderAction(CThostFtdcRemoveParkedOrderActionField *pRemoveParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///ִ������¼��������Ӧ
	virtual void OnRspExecOrderInsert(CThostFtdcInputExecOrderField *pInputExecOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///ִ���������������Ӧ
	virtual void OnRspExecOrderAction(CThostFtdcInputExecOrderActionField *pInputExecOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///ѯ��¼��������Ӧ
	virtual void OnRspForQuoteInsert(CThostFtdcInputForQuoteField *pInputForQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///����¼��������Ӧ
	virtual void OnRspQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///���۲���������Ӧ
	virtual void OnRspQuoteAction(CThostFtdcInputQuoteActionField *pInputQuoteAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///������������������Ӧ
	virtual void OnRspBatchOrderAction(CThostFtdcInputBatchOrderActionField *pInputBatchOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///��Ȩ�ԶԳ�¼��������Ӧ
	virtual void OnRspOptionSelfCloseInsert(CThostFtdcInputOptionSelfCloseField *pInputOptionSelfClose, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///��Ȩ�ԶԳ����������Ӧ
	virtual void OnRspOptionSelfCloseAction(CThostFtdcInputOptionSelfCloseActionField *pInputOptionSelfCloseAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///�������¼��������Ӧ
	virtual void OnRspCombActionInsert(CThostFtdcInputCombActionField *pInputCombAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///�����ѯ������Ӧ
	virtual void OnRspQryOrder(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///�����ѯ�ɽ���Ӧ
	virtual void OnRspQryTrade(CThostFtdcTradeField *pTrade, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///�����ѯͶ���ֲ߳���Ӧ
	virtual void OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///�����ѯ�ʽ��˻���Ӧ
	virtual void OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///�����ѯͶ������Ӧ
	virtual void OnRspQryInvestor(CThostFtdcInvestorField *pInvestor, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///�����ѯ���ױ�����Ӧ
	virtual void OnRspQryTradingCode(CThostFtdcTradingCodeField *pTradingCode, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///�����ѯ��Լ��֤������Ӧ
	virtual void OnRspQryInstrumentMarginRate(CThostFtdcInstrumentMarginRateField *pInstrumentMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///�����ѯ��Լ����������Ӧ
	virtual void OnRspQryInstrumentCommissionRate(CThostFtdcInstrumentCommissionRateField *pInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;


	///�����ѯ��������Ӧ
	virtual void OnRspQryExchange(CThostFtdcExchangeField *pExchange, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///�����ѯ��Ʒ��Ӧ
	virtual void OnRspQryProduct(CThostFtdcProductField *pProduct, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///�����ѯ��Լ��Ӧ
	virtual void OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;


	///�����ѯ������Ӧ
	virtual void OnRspQryDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;


	///�����ѯͶ���߽�������Ӧ
	virtual void OnRspQrySettlementInfo(CThostFtdcSettlementInfoField *pSettlementInfo, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;
	///�����ѯת��������Ӧ
	virtual void OnRspQryTransferBank(CThostFtdcTransferBankField *pTransferBank, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///�����ѯͶ���ֲ߳���ϸ��Ӧ
	virtual void OnRspQryInvestorPositionDetail(CThostFtdcInvestorPositionDetailField *pInvestorPositionDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///�����ѯ�ͻ�֪ͨ��Ӧ
	virtual void OnRspQryNotice(CThostFtdcNoticeField *pNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///�����ѯ������Ϣȷ����Ӧ
	virtual void OnRspQrySettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///�����ѯͶ���ֲ߳���ϸ��Ӧ
	virtual void OnRspQryInvestorPositionCombineDetail(CThostFtdcInvestorPositionCombineDetailField *pInvestorPositionCombineDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///��ѯ��֤����ϵͳ���͹�˾�ʽ��˻���Կ��Ӧ
	virtual void OnRspQryCFMMCTradingAccountKey(CThostFtdcCFMMCTradingAccountKeyField *pCFMMCTradingAccountKey, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///�����ѯ�ֵ��۵���Ϣ��Ӧ
	virtual void OnRspQryEWarrantOffset(CThostFtdcEWarrantOffsetField *pEWarrantOffset, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///�����ѯͶ����Ʒ��/��Ʒ�ֱ�֤����Ӧ
	virtual void OnRspQryInvestorProductGroupMargin(CThostFtdcInvestorProductGroupMarginField *pInvestorProductGroupMargin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///�����ѯ��������֤������Ӧ
	virtual void OnRspQryExchangeMarginRate(CThostFtdcExchangeMarginRateField *pExchangeMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///�����ѯ������������֤������Ӧ
	virtual void OnRspQryExchangeMarginRateAdjust(CThostFtdcExchangeMarginRateAdjustField *pExchangeMarginRateAdjust, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///�����ѯ������Ӧ
	virtual void OnRspQryExchangeRate(CThostFtdcExchangeRateField *pExchangeRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///�����ѯ�����������Ա����Ȩ����Ӧ
	virtual void OnRspQrySecAgentACIDMap(CThostFtdcSecAgentACIDMapField *pSecAgentACIDMap, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///�����ѯ��Ʒ���ۻ���
	virtual void OnRspQryProductExchRate(CThostFtdcProductExchRateField *pProductExchRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///�����ѯ��Ʒ��
	virtual void OnRspQryProductGroup(CThostFtdcProductGroupField *pProductGroup, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///�����ѯ�����̺�Լ����������Ӧ
	virtual void OnRspQryMMInstrumentCommissionRate(CThostFtdcMMInstrumentCommissionRateField *pMMInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///�����ѯ��������Ȩ��Լ��������Ӧ
	virtual void OnRspQryMMOptionInstrCommRate(CThostFtdcMMOptionInstrCommRateField *pMMOptionInstrCommRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///�����ѯ������������Ӧ
	virtual void OnRspQryInstrumentOrderCommRate(CThostFtdcInstrumentOrderCommRateField *pInstrumentOrderCommRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///�����ѯ�ʽ��˻���Ӧ
	virtual void OnRspQrySecAgentTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///�����ѯ�����������ʽ�У��ģʽ��Ӧ
	virtual void OnRspQrySecAgentCheckMode(CThostFtdcSecAgentCheckModeField *pSecAgentCheckMode, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///�����ѯ������������Ϣ��Ӧ
	virtual void OnRspQrySecAgentTradeInfo(CThostFtdcSecAgentTradeInfoField *pSecAgentTradeInfo, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///�����ѯ��Ȩ���׳ɱ���Ӧ
	virtual void OnRspQryOptionInstrTradeCost(CThostFtdcOptionInstrTradeCostField *pOptionInstrTradeCost, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///�����ѯ��Ȩ��Լ��������Ӧ
	virtual void OnRspQryOptionInstrCommRate(CThostFtdcOptionInstrCommRateField *pOptionInstrCommRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///�����ѯִ��������Ӧ
	virtual void OnRspQryExecOrder(CThostFtdcExecOrderField *pExecOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///�����ѯѯ����Ӧ
	virtual void OnRspQryForQuote(CThostFtdcForQuoteField *pForQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///�����ѯ������Ӧ
	virtual void OnRspQryQuote(CThostFtdcQuoteField *pQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///�����ѯ��Ȩ�ԶԳ���Ӧ
	virtual void OnRspQryOptionSelfClose(CThostFtdcOptionSelfCloseField *pOptionSelfClose, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///�����ѯͶ�ʵ�Ԫ��Ӧ
	virtual void OnRspQryInvestUnit(CThostFtdcInvestUnitField *pInvestUnit, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///�����ѯ��Ϻ�Լ��ȫϵ����Ӧ
	virtual void OnRspQryCombInstrumentGuard(CThostFtdcCombInstrumentGuardField *pCombInstrumentGuard, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///�����ѯ���������Ӧ
	virtual void OnRspQryCombAction(CThostFtdcCombActionField *pCombAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///�����ѯת����ˮ��Ӧ
	virtual void OnRspQryTransferSerial(CThostFtdcTransferSerialField *pTransferSerial, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///�����ѯ����ǩԼ��ϵ��Ӧ
	virtual void OnRspQryAccountregister(CThostFtdcAccountregisterField *pAccountregister, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;



	///����Ӧ��
	virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///����֪ͨ
	virtual void OnRtnOrder(CThostFtdcOrderField *pOrder)  ;

	///�ɽ�֪ͨ
	virtual void OnRtnTrade(CThostFtdcTradeField *pTrade)  ;

	///����¼�����ر�
	virtual void OnErrRtnOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo)  ;

	///������������ر�
	virtual void OnErrRtnOrderAction(CThostFtdcOrderActionField *pOrderAction, CThostFtdcRspInfoField *pRspInfo)  ;

	///��Լ����״̬֪ͨ
	virtual void OnRtnInstrumentStatus(CThostFtdcInstrumentStatusField *pInstrumentStatus)  ;

	///����������֪ͨ
	virtual void OnRtnBulletin(CThostFtdcBulletinField* pBulletin) {};

	///����֪ͨ
	virtual void OnRtnTradingNotice(CThostFtdcTradingNoticeInfoField *pTradingNoticeInfo)  ;

	///��ʾ������У�����
	virtual void OnRtnErrorConditionalOrder(CThostFtdcErrorConditionalOrderField *pErrorConditionalOrder)  ;

	///ִ������֪ͨ
	virtual void OnRtnExecOrder(CThostFtdcExecOrderField *pExecOrder)  ;

	///ִ������¼�����ر�
	virtual void OnErrRtnExecOrderInsert(CThostFtdcInputExecOrderField *pInputExecOrder, CThostFtdcRspInfoField *pRspInfo)  ;

	///ִ�������������ر�
	virtual void OnErrRtnExecOrderAction(CThostFtdcExecOrderActionField *pExecOrderAction, CThostFtdcRspInfoField *pRspInfo)  ;

	///ѯ��¼�����ر�
	virtual void OnErrRtnForQuoteInsert(CThostFtdcInputForQuoteField *pInputForQuote, CThostFtdcRspInfoField *pRspInfo)  ;

	///����֪ͨ
	virtual void OnRtnQuote(CThostFtdcQuoteField *pQuote)  ;

	///����¼�����ر�
	virtual void OnErrRtnQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, CThostFtdcRspInfoField *pRspInfo)  ;

	///���۲�������ر�
	virtual void OnErrRtnQuoteAction(CThostFtdcQuoteActionField *pQuoteAction, CThostFtdcRspInfoField *pRspInfo)  ;

	///ѯ��֪ͨ
	virtual void OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp)  ;

	///��֤���������û�����
	virtual void OnRtnCFMMCTradingAccountToken(CThostFtdcCFMMCTradingAccountTokenField *pCFMMCTradingAccountToken)  ;

	///����������������ر�
	virtual void OnErrRtnBatchOrderAction(CThostFtdcBatchOrderActionField *pBatchOrderAction, CThostFtdcRspInfoField *pRspInfo)  ;

	///��Ȩ�ԶԳ�֪ͨ
	virtual void OnRtnOptionSelfClose(CThostFtdcOptionSelfCloseField *pOptionSelfClose)  ;

	///��Ȩ�ԶԳ�¼�����ر�
	virtual void OnErrRtnOptionSelfCloseInsert(CThostFtdcInputOptionSelfCloseField *pInputOptionSelfClose, CThostFtdcRspInfoField *pRspInfo)  ;

	///��Ȩ�ԶԳ��������ر�
	virtual void OnErrRtnOptionSelfCloseAction(CThostFtdcOptionSelfCloseActionField *pOptionSelfCloseAction, CThostFtdcRspInfoField *pRspInfo)  ;

	///�������֪ͨ
	virtual void OnRtnCombAction(CThostFtdcCombActionField *pCombAction)  ;

	///�������¼�����ر�
	virtual void OnErrRtnCombActionInsert(CThostFtdcInputCombActionField *pInputCombAction, CThostFtdcRspInfoField *pRspInfo)  ;

	///�����ѯǩԼ������Ӧ
	virtual void OnRspQryContractBank(CThostFtdcContractBankField *pContractBank, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///�����ѯԤ����Ӧ
	virtual void OnRspQryParkedOrder(CThostFtdcParkedOrderField *pParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///�����ѯԤ�񳷵���Ӧ
	virtual void OnRspQryParkedOrderAction(CThostFtdcParkedOrderActionField *pParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///�����ѯ����֪ͨ��Ӧ
	virtual void OnRspQryTradingNotice(CThostFtdcTradingNoticeField *pTradingNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///�����ѯ���͹�˾���ײ�����Ӧ
	virtual void OnRspQryBrokerTradingParams(CThostFtdcBrokerTradingParamsField *pBrokerTradingParams, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///�����ѯ���͹�˾�����㷨��Ӧ
	virtual void OnRspQryBrokerTradingAlgos(CThostFtdcBrokerTradingAlgosField *pBrokerTradingAlgos, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///�����ѯ��������û�����
	virtual void OnRspQueryCFMMCTradingAccountToken(CThostFtdcQueryCFMMCTradingAccountTokenField *pQueryCFMMCTradingAccountToken, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///���з��������ʽ�ת�ڻ�֪ͨ
	virtual void OnRtnFromBankToFutureByBank(CThostFtdcRspTransferField *pRspTransfer)  ;

	///���з����ڻ��ʽ�ת����֪ͨ
	virtual void OnRtnFromFutureToBankByBank(CThostFtdcRspTransferField *pRspTransfer)  ;

	///���з����������ת�ڻ�֪ͨ
	virtual void OnRtnRepealFromBankToFutureByBank(CThostFtdcRspRepealField *pRspRepeal)  ;

	///���з�������ڻ�ת����֪ͨ
	virtual void OnRtnRepealFromFutureToBankByBank(CThostFtdcRspRepealField *pRspRepeal)  ;

	///�ڻ����������ʽ�ת�ڻ�֪ͨ
	virtual void OnRtnFromBankToFutureByFuture(CThostFtdcRspTransferField *pRspTransfer)  ;

	///�ڻ������ڻ��ʽ�ת����֪ͨ
	virtual void OnRtnFromFutureToBankByFuture(CThostFtdcRspTransferField *pRspTransfer)  ;

	///ϵͳ����ʱ�ڻ����ֹ������������ת�ڻ��������д�����Ϻ��̷��ص�֪ͨ
	virtual void OnRtnRepealFromBankToFutureByFutureManual(CThostFtdcRspRepealField *pRspRepeal)  ;

	///ϵͳ����ʱ�ڻ����ֹ���������ڻ�ת�����������д�����Ϻ��̷��ص�֪ͨ
	virtual void OnRtnRepealFromFutureToBankByFutureManual(CThostFtdcRspRepealField *pRspRepeal)  ;

	///�ڻ������ѯ�������֪ͨ
	virtual void OnRtnQueryBankBalanceByFuture(CThostFtdcNotifyQueryAccountField *pNotifyQueryAccount)  ;

	///�ڻ����������ʽ�ת�ڻ�����ر�
	virtual void OnErrRtnBankToFutureByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo)  ;

	///�ڻ������ڻ��ʽ�ת���д���ر�
	virtual void OnErrRtnFutureToBankByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo)  ;

	///ϵͳ����ʱ�ڻ����ֹ������������ת�ڻ�����ر�
	virtual void OnErrRtnRepealBankToFutureByFutureManual(CThostFtdcReqRepealField *pReqRepeal, CThostFtdcRspInfoField *pRspInfo)  ;

	///ϵͳ����ʱ�ڻ����ֹ���������ڻ�ת���д���ر�
	virtual void OnErrRtnRepealFutureToBankByFutureManual(CThostFtdcReqRepealField *pReqRepeal, CThostFtdcRspInfoField *pRspInfo)  ;

	///�ڻ������ѯ����������ر�
	virtual void OnErrRtnQueryBankBalanceByFuture(CThostFtdcReqQueryAccountField *pReqQueryAccount, CThostFtdcRspInfoField *pRspInfo)  ;

	///�ڻ������������ת�ڻ��������д�����Ϻ��̷��ص�֪ͨ
	virtual void OnRtnRepealFromBankToFutureByFuture(CThostFtdcRspRepealField *pRspRepeal)  ;

	///�ڻ���������ڻ�ת�����������д�����Ϻ��̷��ص�֪ͨ
	virtual void OnRtnRepealFromFutureToBankByFuture(CThostFtdcRspRepealField *pRspRepeal)  ;

	///�ڻ����������ʽ�ת�ڻ�Ӧ��
	virtual void OnRspFromBankToFutureByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///�ڻ������ڻ��ʽ�ת����Ӧ��
	virtual void OnRspFromFutureToBankByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///�ڻ������ѯ�������Ӧ��
	virtual void OnRspQueryBankAccountMoneyByFuture(CThostFtdcReqQueryAccountField *pReqQueryAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///���з������ڿ���֪ͨ
	virtual void OnRtnOpenAccountByBank(CThostFtdcOpenAccountField *pOpenAccount)  ;

	///���з�����������֪ͨ
	virtual void OnRtnCancelAccountByBank(CThostFtdcCancelAccountField *pCancelAccount)  ;

	///���з����������˺�֪ͨ
	virtual void OnRtnChangeAccountByBank(CThostFtdcChangeAccountField *pChangeAccount)  ;
#pragma endregion


private:
	CThostFtdcRspInfoField* repareInfo(CThostFtdcRspInfoField *pRspInfo);
};

