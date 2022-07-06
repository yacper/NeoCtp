#pragma once
#include "pch.h"
#include "TdSpi.h"

extern "C"  // ��C�ķ�ʽ����������
{
#pragma  region Api

	TDAPI_API CThostFtdcTraderApi* CreateFtdcTraderApi(const char* pszFlowPath = "CtpFlow/");
	TDAPI_API TraderSpi*	CreateTdSpi();
	TDAPI_API void			RegisterSpi(CThostFtdcTraderApi* api, TraderSpi* pSpi);

	//��ȡ�ӿڰ汾
	TDAPI_API const char*	GetApiVersion();

	//����
	//	TDAPI_API CThostFtdcTraderApi* Connect(char* frontAddr, char* pszFlowPath, TraderSpi* pSpi);
	////�Ͽ�
	//	TDAPI_API void		DisConnect(CThostFtdcTraderApi* pApi);

		///ɾ���ӿڶ�����
		///@remark ����ʹ�ñ��ӿڶ���ʱ,���øú���ɾ���ӿڶ���
	TDAPI_API void			Release(CThostFtdcTraderApi* api);

	///��ʼ��
	///@remark ��ʼ�����л���,ֻ�е��ú�,�ӿڲſ�ʼ����
	TDAPI_API void			Init(CThostFtdcTraderApi* api);

	///�ȴ��ӿ��߳̽�������
	///@return �߳��˳�����
	TDAPI_API int			Join(CThostFtdcTraderApi* api);


	//��ȡ������
	TDAPI_API const char*	GetTradingDay(CThostFtdcTraderApi* pApi);


	///ע��ǰ�û������ַ
	///@param pszFrontAddress��ǰ�û������ַ��
	///@remark �����ַ�ĸ�ʽΪ����protocol://ipaddress:port�����磺��tcp://127.0.0.1:17001���� 
	///@remark ��tcp��������Э�飬��127.0.0.1�������������ַ����17001������������˿ںš�
	TDAPI_API void			RegisterFront(CThostFtdcTraderApi* pApi, char* pszFrontAddress);

	///ע�����ַ����������ַ
	///@param pszNsAddress�����ַ����������ַ��
	///@remark �����ַ�ĸ�ʽΪ����protocol://ipaddress:port�����磺��tcp://127.0.0.1:12001���� 
	///@remark ��tcp��������Э�飬��127.0.0.1�������������ַ����12001������������˿ںš�
	///@remark RegisterNameServer������RegisterFront
	TDAPI_API void			RegisterNameServer(CThostFtdcTraderApi* pApi, char* pszNsAddress);

	///ע�����ַ������û���Ϣ
	///@param pFensUserInfo���û���Ϣ��
	TDAPI_API void			RegisterFensUserInfo(CThostFtdcTraderApi* pApi, CThostFtdcFensUserInfoField* pFensUserInfo);

	///����˽������
	///@param nResumeType ˽�����ش���ʽ  
	///        THOST_TERT_RESTART:�ӱ������տ�ʼ�ش�
	///        THOST_TERT_RESUME:���ϴ��յ�������
	///        THOST_TERT_QUICK:ֻ���͵�¼��˽����������
	///@remark �÷���Ҫ��Init����ǰ���á����������򲻻��յ�˽���������ݡ�
	TDAPI_API void			SubscribePrivateTopic(CThostFtdcTraderApi* pApi, THOST_TE_RESUME_TYPE nResumeType);

	///���Ĺ�������
	///@param nResumeType �������ش���ʽ  
	///        THOST_TERT_RESTART:�ӱ������տ�ʼ�ش�
	///        THOST_TERT_RESUME:���ϴ��յ�������
	///        THOST_TERT_QUICK:ֻ���͵�¼�󹫹���������
	///@remark �÷���Ҫ��Init����ǰ���á����������򲻻��յ������������ݡ�
	TDAPI_API void			SubscribePublicTopic(CThostFtdcTraderApi* pApi, THOST_TE_RESUME_TYPE nResumeType);



#pragma region Login/out

	//�ͻ�����֤����
	TDAPI_API int			ReqAuthenticate(CThostFtdcTraderApi* pApi, CThostFtdcReqAuthenticateField* field, int nRequestID);


	///ע���û��ն���Ϣ�������м̷�����������ģʽ
	///��Ҫ���ն���֤�ɹ����û���¼ǰ���øýӿ�
	TDAPI_API int			RegisterUserSystemInfo(CThostFtdcTraderApi* pApi, CThostFtdcUserSystemInfoField* pUserSystemInfo);
	///�ϱ��û��ն���Ϣ�������м̷���������Ա��¼ģʽ
	///����Ա��¼�󣬿��Զ�ε��øýӿ��ϱ��ͻ���Ϣ
	TDAPI_API int			SubmitUserSystemInfo(CThostFtdcTraderApi* pApi, CThostFtdcUserSystemInfoField* pUserSystemInfo);


	//�����û���¼����
	TDAPI_API int			ReqUserLogin(CThostFtdcTraderApi* pApi, CThostFtdcReqUserLoginField* pReqUserLoginField, int nRequestID);
	//���͵ǳ�����
	TDAPI_API int			ReqUserLogout(CThostFtdcTraderApi* pApi, CThostFtdcUserLogoutField* pUserLogout, int nRequestID);


	///�û������������
	TDAPI_API int		ReqUserPasswordUpdate(CThostFtdcTraderApi* pApi, CThostFtdcUserPasswordUpdateField* pUserPasswordUpdate, int nRequestID);

	///�ʽ��˻������������
	TDAPI_API int		ReqTradingAccountPasswordUpdate(CThostFtdcTraderApi* pApi, CThostFtdcTradingAccountPasswordUpdateField* pTradingAccountPasswordUpdate, int nRequestID);

	///��ѯ�û���ǰ֧�ֵ���֤ģʽ
	TDAPI_API int		ReqUserAuthMethod(CThostFtdcTraderApi* pApi, CThostFtdcReqUserAuthMethodField* pReqUserAuthMethod, int nRequestID);

	///�û�������ȡͼ����֤������
	TDAPI_API int		ReqGenUserCaptcha(CThostFtdcTraderApi* pApi, CThostFtdcReqGenUserCaptchaField* pReqGenUserCaptcha, int	nRequestID);

	///�û�������ȡ������֤������
	TDAPI_API int		ReqGenUserText(CThostFtdcTraderApi* pApi, CThostFtdcReqGenUserTextField* pReqGenUserText, int nRequestID);

	///�û���������ͼƬ��֤��ĵ�½����
	TDAPI_API int		ReqUserLoginWithCaptcha(CThostFtdcTraderApi* pApi, CThostFtdcReqUserLoginWithCaptchaField* pReqUserLoginWithCaptcha, int nRequestID);

	///�û��������ж�����֤��ĵ�½����
	TDAPI_API int		ReqUserLoginWithText(CThostFtdcTraderApi* pApi, CThostFtdcReqUserLoginWithTextField* pReqUserLoginWithText, int	nRequestID);

	///�û��������ж�̬����ĵ�½����
	TDAPI_API int		ReqUserLoginWithOTP(CThostFtdcTraderApi* pApi, CThostFtdcReqUserLoginWithOTPField* pReqUserLoginWithOTP, int nRequestID);

#pragma endregion

	///�����ѯѯ��
	TDAPI_API int		ReqQryForQuote(CThostFtdcTraderApi* pApi, CThostFtdcQryForQuoteField* pQryForQuote, int nRequestID);
	///�����ѯ����
	TDAPI_API int		ReqQryQuote(CThostFtdcTraderApi* pApi, CThostFtdcQryQuoteField* pQryQuote, int nRequestID);
	///�����ѯ����
	TDAPI_API int		ReqQryDepthMarketData(CThostFtdcTraderApi* pApi, CThostFtdcQryDepthMarketDataField* pQryDepthMarketData, int nRequestID);

#pragma region Order management
	///����¼������
	TDAPI_API int		ReqOrderInsert(CThostFtdcTraderApi* pApi, CThostFtdcInputOrderField* pInputOrder, int nRequestID);
	///�����ѯ����
	TDAPI_API int		ReqQryOrder(CThostFtdcTraderApi* pApi, CThostFtdcQryOrderField* pQryOrder, int nRequestID);
	///��ѯ��󱨵���������
	TDAPI_API int		ReqQueryMaxOrderVolume(CThostFtdcTraderApi* pApi, CThostFtdcQueryMaxOrderVolumeField* pQueryMaxOrderVolume, int nRequestID);
	///������������
	TDAPI_API int		ReqOrderAction(CThostFtdcTraderApi* pApi, CThostFtdcInputOrderActionField* pInputOrderAction, int nRequestID);
	///����������������
	TDAPI_API int		ReqBatchOrderAction(CThostFtdcTraderApi* pApi, CThostFtdcInputBatchOrderActionField* pInputBatchOrderAction, int nRequestID);

	///Ԥ��¼������
	TDAPI_API int		ReqParkedOrderInsert(CThostFtdcTraderApi* pApi, CThostFtdcParkedOrderField* pParkedOrder, int nRequestID);
	///Ԥ�񳷵�¼������
	TDAPI_API int		ReqParkedOrderAction(CThostFtdcTraderApi* pApi, CThostFtdcParkedOrderActionField* pParkedOrderAction, int nRequestID);
	///����ɾ��Ԥ��
	TDAPI_API int		ReqRemoveParkedOrder(CThostFtdcTraderApi* pApi, CThostFtdcRemoveParkedOrderField* pRemoveParkedOrder, int nRequestID);
	///����ɾ��Ԥ�񳷵�
	TDAPI_API int		ReqRemoveParkedOrderAction(CThostFtdcTraderApi* pApi, CThostFtdcRemoveParkedOrderActionField* pRemoveParkedOrderAction, int nRequestID);
	///�����ѯԤ��
	TDAPI_API int		ReqQryParkedOrder(CThostFtdcTraderApi* pApi, CThostFtdcQryParkedOrderField* pQryParkedOrder, int nRequestID);
	///�����ѯԤ�񳷵�
	TDAPI_API int		ReqQryParkedOrderAction(CThostFtdcTraderApi* pApi, CThostFtdcQryParkedOrderActionField* pQryParkedOrderAction, int nRequestID);

#pragma endregion

	///�����ѯ�ɽ�
	TDAPI_API int		ReqQryTrade(CThostFtdcTraderApi* pApi, CThostFtdcQryTradeField* pQryTrade, int nRequestID);

		///�����ѯ�ͻ�֪ͨ
	TDAPI_API int		ReqQryNotice(CThostFtdcTraderApi* pApi, CThostFtdcQryNoticeField* pQryNotice, int nRequestID);
	///�����ѯ����֪ͨ
	TDAPI_API int		ReqQryTradingNotice(CThostFtdcTraderApi* pApi, CThostFtdcQryTradingNoticeField* pQryTradingNotice, int nRequestID);


	///�����ѯִ������
	TDAPI_API int		ReqQryExecOrder(CThostFtdcTraderApi* pApi, CThostFtdcQryExecOrderField* pQryExecOrder, int nRequestID);
	///ִ������¼������
	TDAPI_API int		ReqExecOrderInsert(CThostFtdcTraderApi* pApi, CThostFtdcInputExecOrderField* pInputExecOrder, int nRequestID);
	///ִ�������������
	TDAPI_API int		ReqExecOrderAction(CThostFtdcTraderApi* pApi, CThostFtdcInputExecOrderActionField* pInputExecOrderAction, int nRequestID);


	///ѯ��¼������
	TDAPI_API int		ReqForQuoteInsert(CThostFtdcTraderApi* pApi, CThostFtdcInputForQuoteField* pInputForQuote, int nRequestID);
	///����¼������
	TDAPI_API int		ReqQuoteInsert(CThostFtdcTraderApi* pApi, CThostFtdcInputQuoteField* pInputQuote, int nRequestID);
	///���۲�������
	TDAPI_API int		ReqQuoteAction(CThostFtdcTraderApi* pApi, CThostFtdcInputQuoteActionField* pInputQuoteAction, int nRequestID);



	///�������¼������
	TDAPI_API int		ReqCombActionInsert(CThostFtdcTraderApi* pApi, CThostFtdcInputCombActionField* pInputCombAction, int nRequestID);
	///�����ѯ��Ϻ�Լ��ȫϵ��
	TDAPI_API int		ReqQryCombInstrumentGuard(CThostFtdcTraderApi* pApi, CThostFtdcQryCombInstrumentGuardField* pQryCombInstrumentGuard, int nRequestID);
	///�����ѯ�������
	TDAPI_API int		ReqQryCombAction(CThostFtdcTraderApi* pApi, CThostFtdcQryCombActionField* pQryCombAction, int nRequestID);


	///�����ѯͶ���ֲ߳�
	TDAPI_API int		ReqQryInvestorPosition(CThostFtdcTraderApi* pApi, CThostFtdcQryInvestorPositionField* pQryInvestorPosition, int nRequestID);
	///�����ѯͶ���ֲ߳���ϸ
	TDAPI_API int		ReqQryInvestorPositionDetail(CThostFtdcTraderApi* pApi, CThostFtdcQryInvestorPositionDetailField* pQryInvestorPositionDetail, int nRequestID);
	///�����ѯͶ���ֲ߳���ϸ
	TDAPI_API int		ReqQryInvestorPositionCombineDetail(CThostFtdcTraderApi* pApi, CThostFtdcQryInvestorPositionCombineDetailField* pQryInvestorPositionCombineDetail, int nRequestID);
	///�����ѯ�ʽ��˻�
	TDAPI_API int		ReqQryTradingAccount(CThostFtdcTraderApi* pApi, CThostFtdcQryTradingAccountField* pQryTradingAccount, int nRequestID);
	///�����ѯͶ����
	TDAPI_API int		ReqQryInvestor(CThostFtdcTraderApi* pApi, CThostFtdcQryInvestorField* pQryInvestor, int nRequestID);
	///�����ѯ���ױ���
	TDAPI_API int		ReqQryTradingCode(CThostFtdcTraderApi* pApi, CThostFtdcQryTradingCodeField* pQryTradingCode, int nRequestID);
	///�����ѯͶ�ʵ�Ԫ
	TDAPI_API int		ReqQryInvestUnit(CThostFtdcTraderApi* pApi, CThostFtdcQryInvestUnitField* pQryInvestUnit, int nRequestID);


#pragma region ����
	///�����ѯͶ���߽�����
	TDAPI_API int		ReqQrySettlementInfo(CThostFtdcTraderApi* pApi, CThostFtdcQrySettlementInfoField* pQrySettlementInfo, int nRequestID);
	///�����ѯ������Ϣȷ��
	TDAPI_API int		ReqQrySettlementInfoConfirm(CThostFtdcTraderApi* pApi, CThostFtdcQrySettlementInfoConfirmField* pQrySettlementInfoConfirm, int nRequestID);
	///Ͷ���߽�����ȷ��
	TDAPI_API int		ReqSettlementInfoConfirm(CThostFtdcTraderApi* pApi, CThostFtdcSettlementInfoConfirmField* pSettlementInfoConfirm, int nRequestID);
#pragma endregion


#pragma region product/Instrument
	///�����ѯ��Ʒ
	TDAPI_API int		ReqQryProduct(CThostFtdcTraderApi* pApi, CThostFtdcQryProductField* pQryProduct, int nRequestID);
	///�����ѯ��Ʒ���ۻ���
	TDAPI_API int		ReqQryProductExchRate(CThostFtdcTraderApi* pApi, CThostFtdcQryProductExchRateField* pQryProductExchRate, int nRequestID);
	///�����ѯ��Ʒ��
	TDAPI_API int		ReqQryProductGroup(CThostFtdcTraderApi* pApi, CThostFtdcQryProductGroupField* pQryProductGroup, int nRequestID);

	///�����ѯ��Լ
	TDAPI_API int		ReqQryInstrument(CThostFtdcTraderApi* pApi, CThostFtdcQryInstrumentField* pQryInstrument, int nRequestID);
	///�����ѯ��Լ��֤����
	TDAPI_API int		ReqQryInstrumentMarginRate(CThostFtdcTraderApi* pApi, CThostFtdcQryInstrumentMarginRateField* pQryInstrumentMarginRate, int nRequestID);
	///�����ѯ��Լ��������
	TDAPI_API int		ReqQryInstrumentCommissionRate(CThostFtdcTraderApi* pApi, CThostFtdcQryInstrumentCommissionRateField* pQryInstrumentCommissionRate, int nRequestID);

	///�����ѯͶ����Ʒ��/��Ʒ�ֱ�֤��
	TDAPI_API int		ReqQryInvestorProductGroupMargin(CThostFtdcTraderApi* pApi, CThostFtdcQryInvestorProductGroupMarginField* pQryInvestorProductGroupMargin, int nRequestID);

	///�����ѯ�����̺�Լ��������
	TDAPI_API int		ReqQryMMInstrumentCommissionRate(CThostFtdcTraderApi* pApi, CThostFtdcQryMMInstrumentCommissionRateField* pQryMMInstrumentCommissionRate, int nRequestID);
	///�����ѯ��������Ȩ��Լ������
	TDAPI_API int		ReqQryMMOptionInstrCommRate(CThostFtdcTraderApi* pApi, CThostFtdcQryMMOptionInstrCommRateField* pQryMMOptionInstrCommRate, int nRequestID);

	///�����ѯ�ֵ��۵���Ϣ
	TDAPI_API int		ReqQryEWarrantOffset(CThostFtdcTraderApi* pApi, CThostFtdcQryEWarrantOffsetField* pQryEWarrantOffset, int nRequestID);

	///�����ѯ����������
	TDAPI_API int		ReqQryInstrumentOrderCommRate(CThostFtdcTraderApi* pApi, CThostFtdcQryInstrumentOrderCommRateField* pQryInstrumentOrderCommRate, int nRequestID);
#pragma endregion


#pragma region ��������/sec agent
	///�����ѯ�ʽ��˻�
	TDAPI_API int		ReqQrySecAgentTradingAccount(CThostFtdcTraderApi* pApi, CThostFtdcQryTradingAccountField* pQryTradingAccount, int nRequestID);
	///�����ѯ�����������Ա����Ȩ��
	TDAPI_API int		ReqQrySecAgentACIDMap(CThostFtdcTraderApi* pApi, CThostFtdcQrySecAgentACIDMapField* pQrySecAgentACIDMap, int nRequestID);
	///�����ѯ�����������ʽ�У��ģʽ
	TDAPI_API int		ReqQrySecAgentCheckMode(CThostFtdcTraderApi* pApi, CThostFtdcQrySecAgentCheckModeField* pQrySecAgentCheckMode, int nRequestID);
	///�����ѯ������������Ϣ
	TDAPI_API int		ReqQrySecAgentTradeInfo(CThostFtdcTraderApi* pApi, CThostFtdcQrySecAgentTradeInfoField* pQrySecAgentTradeInfo, int nRequestID);
#pragma endregion


#pragma region ��Ȩoption
	///��Ȩ�ԶԳ�¼������
	TDAPI_API int		ReqOptionSelfCloseInsert(CThostFtdcTraderApi* pApi, CThostFtdcInputOptionSelfCloseField* pInputOptionSelfClose, int nRequestID);
	///��Ȩ�ԶԳ��������
	TDAPI_API int		ReqOptionSelfCloseAction(CThostFtdcTraderApi* pApi, CThostFtdcInputOptionSelfCloseActionField* pInputOptionSelfCloseAction, int nRequestID);

	///�����ѯ��Ȩ���׳ɱ�
	TDAPI_API int		ReqQryOptionInstrTradeCost(CThostFtdcTraderApi* pApi, CThostFtdcQryOptionInstrTradeCostField* pQryOptionInstrTradeCost, int nRequestID);
	///�����ѯ��Ȩ��Լ������
	TDAPI_API int		ReqQryOptionInstrCommRate(CThostFtdcTraderApi* pApi, CThostFtdcQryOptionInstrCommRateField* pQryOptionInstrCommRate, int nRequestID);
	///�����ѯ��Ȩ�ԶԳ�
	TDAPI_API int		ReqQryOptionSelfClose(CThostFtdcTraderApi* pApi, CThostFtdcQryOptionSelfCloseField* pQryOptionSelfClose, int nRequestID);
#pragma endregion


#pragma region Banking
	///�����ѯת������
	TDAPI_API int		ReqQryTransferBank(CThostFtdcTraderApi* pApi, CThostFtdcQryTransferBankField* pQryTransferBank, int nRequestID);
	///�����ѯ����ǩԼ��ϵ
	TDAPI_API int		ReqQryAccountregister(CThostFtdcTraderApi* pApi, CThostFtdcQryAccountregisterField* pQryAccountregister, int nRequestID);
	///�����ѯǩԼ����
	TDAPI_API int		ReqQryContractBank(CThostFtdcTraderApi* pApi, CThostFtdcQryContractBankField* pQryContractBank, int nRequestID);
	///�����ѯת����ˮ
	TDAPI_API int		ReqQryTransferSerial(CThostFtdcTraderApi* pApi, CThostFtdcQryTransferSerialField* pQryTransferSerial, int nRequestID);
	///�ڻ������ѯ�����������
	TDAPI_API int		ReqQueryBankAccountMoneyByFuture(CThostFtdcTraderApi* pApi, CThostFtdcReqQueryAccountField* pReqQueryAccount, int nRequestID);

	///�ڻ����������ʽ�ת�ڻ�����
	TDAPI_API int		ReqFromBankToFutureByFuture(CThostFtdcTraderApi* pApi, CThostFtdcReqTransferField* pReqTransfer, int nRequestID);
	///�ڻ������ڻ��ʽ�ת��������
	TDAPI_API int		ReqFromFutureToBankByFuture(CThostFtdcTraderApi* pApi, CThostFtdcReqTransferField* pReqTransfer, int nRequestID);
#pragma endregion


#pragma region Exchange/������
	///�����ѯ������
	TDAPI_API int		ReqQryExchange(CThostFtdcTraderApi* pApi, CThostFtdcQryExchangeField* pQryExchange, int nRequestID);
	///�����ѯ��������֤����
	TDAPI_API int		ReqQryExchangeMarginRate(CThostFtdcTraderApi* pApi, CThostFtdcQryExchangeMarginRateField* pQryExchangeMarginRate, int nRequestID);
	///�����ѯ������������֤����
	TDAPI_API int		ReqQryExchangeMarginRateAdjust(CThostFtdcTraderApi* pApi, CThostFtdcQryExchangeMarginRateAdjustField* pQryExchangeMarginRateAdjust, int nRequestID);
	///�����ѯ����
	TDAPI_API int		ReqQryExchangeRate(CThostFtdcTraderApi* pApi, CThostFtdcQryExchangeRateField* pQryExchangeRate, int nRequestID);
#pragma endregion


#pragma region Broker
	///�����ѯ���͹�˾���ײ���
	TDAPI_API int		ReqQryBrokerTradingParams(CThostFtdcTraderApi* pApi, CThostFtdcQryBrokerTradingParamsField* pQryBrokerTradingParams, int nRequestID);
	///�����ѯ���͹�˾�����㷨
	TDAPI_API int		ReqQryBrokerTradingAlgos(CThostFtdcTraderApi* pApi, CThostFtdcQryBrokerTradingAlgosField* pQryBrokerTradingAlgos, int nRequestID);
#pragma endregion

#pragma region CFMMC
	///�����ѯ��������û�����
	TDAPI_API int		ReqQueryCFMMCTradingAccountToken(CThostFtdcTraderApi* pApi, CThostFtdcQueryCFMMCTradingAccountTokenField* pQueryCFMMCTradingAccountToken, int nRequestID);

	///�����ѯ��֤����ϵͳ���͹�˾�ʽ��˻���Կ
	TDAPI_API int		ReqQryCFMMCTradingAccountKey(CThostFtdcTraderApi* pApi, CThostFtdcQryCFMMCTradingAccountKeyField* pQryCFMMCTradingAccountKey, int nRequestID);
#pragma endregion




#pragma endregion

#pragma region ע��ص�����
	//========================================
	//==================================== �ص����� =======================================
	TDAPI_API void RegOnRspError(TraderSpi* pSpi, CBOnRspError cb);	//����Ӧ��
	TDAPI_API void RegOnHeartBeatWarning(TraderSpi* pSpi, CBOnHeartBeatWarning cb);		//������ʱ���档����ʱ��δ�յ�����ʱ���÷��������á�

	TDAPI_API void RegOnRspFrontConnected(TraderSpi* pSpi, CBOnRspFrontConnected cb);		//���ͻ����뽻�׺�̨������ͨ������ʱ����δ��¼ǰ�����÷��������á�
	TDAPI_API void RegOnRspFrontDisconnected(TraderSpi* pSpi, CBOnRspFrontDisconnected cb);		//���ͻ����뽻�׺�̨ͨ�����ӶϿ�ʱ���÷��������á���������������API���Զ��������ӣ��ͻ��˿ɲ�������

	TDAPI_API void RegOnRspAuthenticate(TraderSpi* pSpi, CBOnRspAuthenticate cb);

	TDAPI_API void RegOnRspUserLogin(TraderSpi* pSpi, CBOnRspUserLogin cb);	//��¼������Ӧ
	TDAPI_API void RegOnRspUserLogout(TraderSpi* pSpi, CBOnRspUserLogout cb);	//�ǳ�������Ӧ

	TDAPI_API void RegOnRspSettlementInfoConfirm(TraderSpi* pSpi, CBOnRspSettlementInfoConfirm cb);	//Ͷ���߽�����ȷ����Ӧ

	TDAPI_API void RegOnRspQryTradingAccount(TraderSpi* pSpi, CBOnRspQryTradingAccount cb);	//�����ѯ�ʽ��˻���Ӧ

	TDAPI_API void RegOnRspQryInvestorPosition(TraderSpi* pSpi, CBOnRspQryInvestorPosition cb);	//�����ѯͶ���ֲ߳���Ӧ

	TDAPI_API void RegOnRspQryInstrument(TraderSpi* pSpi, CBOnRspQryInstrument cb);	//�����ѯ��Լ��Ӧ

	TDAPI_API void RegOnRspQryOrder(TraderSpi* pSpi, CBOnRspQryOrder cb);	//�����ѯ������Ӧ
	TDAPI_API void RegOnRspQryTrade(TraderSpi* pSpi, CBOnRspQryTrade cb);	//�����ѯ�ɽ���Ӧ
	TDAPI_API void RegOnRspOrderInsert(TraderSpi* pSpi, CBOnRspOrderInsert cb);	//����¼��������Ӧ
	TDAPI_API void RegOnRtnOrder(TraderSpi* pSpi, CBOnRtnOrder cb);	//����֪ͨ
	TDAPI_API void RegOnRtnTrade(TraderSpi* pSpi, CBOnRtnTrade cb);	//�ɽ�֪ͨ



	TDAPI_API void RegRspUserPasswordUpdate(TraderSpi* pSpi, CBRspUserPasswordUpdate cb);	//�û��������������Ӧ
	TDAPI_API void RegRspTradingAccountPasswordUpdate(TraderSpi* pSpi, CBRspTradingAccountPasswordUpdate cb);	//�ʽ��˻��������������Ӧ
	TDAPI_API void RegRspUserAuthMethod(TraderSpi* pSpi, CBRspUserAuthMethod cb);	//��ѯ�û���ǰ֧�ֵ���֤ģʽ�Ļظ�
	TDAPI_API void RegRspGenUserCaptcha(TraderSpi* pSpi, CBRspGenUserCaptcha cb);	//��ȡͼ����֤������Ļظ�
	TDAPI_API void RegRspGenUserText(TraderSpi* pSpi, CBRspGenUserText cb);	//��ȡ������֤������Ļظ�
	TDAPI_API void RegRspParkedOrderInsert(TraderSpi* pSpi, CBRspParkedOrderInsert cb);	//Ԥ��¼��������Ӧ
	TDAPI_API void RegRspParkedOrderAction(TraderSpi* pSpi, CBRspParkedOrderAction cb);	//Ԥ�񳷵�¼��������Ӧ
	TDAPI_API void RegRspOrderAction(TraderSpi* pSpi, CBRspOrderAction cb);	//��������������Ӧ
	TDAPI_API void RegRspQueryMaxOrderVolume(TraderSpi* pSpi, CBRspQueryMaxOrderVolume cb);	//��ѯ��󱨵�������Ӧ
	TDAPI_API void RegRspRemoveParkedOrder(TraderSpi* pSpi, CBRspRemoveParkedOrder cb);	//ɾ��Ԥ����Ӧ
	TDAPI_API void RegRspRemoveParkedOrderAction(TraderSpi* pSpi, CBRspRemoveParkedOrderAction cb);	//ɾ��Ԥ�񳷵���Ӧ
	TDAPI_API void RegBatchOrderAction(TraderSpi* pSpi, CBRspBatchOrderAction cb);	//������������������Ӧ
	TDAPI_API void RegCombActionInsert(TraderSpi* pSpi, CBRspCombActionInsert cb);	//�������¼��������Ӧ
	TDAPI_API void RegRspQryInvestor(TraderSpi* pSpi, CBRspQryInvestor cb);	//�����ѯͶ������Ӧ
	TDAPI_API void RegRspQryTradingCode(TraderSpi* pSpi, CBRspQryTradingCode cb);	//�����ѯ���ױ�����Ӧ
	TDAPI_API void RegRspQryInstrumentMarginRate(TraderSpi* pSpi, CBRspQryInstrumentMarginRate cb);	//�����ѯ��Լ��֤������Ӧ
	TDAPI_API void RegRspQryInstrumentCommissionRate(TraderSpi* pSpi, CBRspQryInstrumentCommissionRate cb);	//�����ѯ��Լ����������Ӧ
	TDAPI_API void RegRspQryExchange(TraderSpi* pSpi, CBRspQryExchange cb);	//�����ѯ��������Ӧ
	TDAPI_API void RegRspQryDepthMarketData(TraderSpi* pSpi, CBRspQryDepthMarketData cb);	//�����ѯ������Ӧ
	TDAPI_API void RegRspQrySettlementInfo(TraderSpi* pSpi, CBRspQrySettlementInfo cb);	//�����ѯͶ���߽�������Ӧ
	TDAPI_API void RegRspQryTransferBank(TraderSpi* pSpi, CBRspQryTransferBank cb);	//�����ѯת��������Ӧ
	TDAPI_API void RegRspQryInvestorPositionDetail(TraderSpi* pSpi, CBRspQryInvestorPositionDetail cb);	//�����ѯͶ���ֲ߳���ϸ��Ӧ
	TDAPI_API void RegRspQryNotice(TraderSpi* pSpi, CBRspQryNotice cb);	//�����ѯ�ͻ�֪ͨ��Ӧ
	TDAPI_API void RegRspQrySettlementInfoConfirm(TraderSpi* pSpi, CBRspQrySettlementInfoConfirm cb);	//�����ѯ������Ϣȷ����Ӧ
	TDAPI_API void RegRspQryInvestorPositionCombineDetail(TraderSpi* pSpi, CBRspQryInvestorPositionCombineDetail cb);	//�����ѯͶ���ֲ߳���ϸ��Ӧ
	TDAPI_API void RegRspQryCFMMCTradingAccountKey(TraderSpi* pSpi, CBRspQryCFMMCTradingAccountKey cb);	//��ѯ��֤����ϵͳ���͹�˾�ʽ��˻���Կ��Ӧ
	TDAPI_API void RegRspQryEWarrantOffset(TraderSpi* pSpi, CBRspQryEWarrantOffset cb);	//�����ѯ�ֵ��۵���Ϣ
	TDAPI_API void RegRspQryInvestorProductGroupMargin(TraderSpi* pSpi, CBRspQryInvestorProductGroupMargin cb);	//�����ѯͶ����Ʒ��/��Ʒ�ֱ�֤��
	TDAPI_API void RegRspQryExchangeMarginRate(TraderSpi* pSpi, CBRspQryExchangeMarginRate cb);	//�����ѯ��������֤����
	TDAPI_API void RegRspQryExchangeMarginRateAdjust(TraderSpi* pSpi, CBRspQryExchangeMarginRateAdjust cb);	//�����ѯ������������֤����
	TDAPI_API void RegRspQryExchangeRate(TraderSpi* pSpi, CBRspQryExchangeRate cb);	//�����ѯ������Ӧ
	TDAPI_API void RegRspQrySecAgentACIDMap(TraderSpi* pSpi, CBRspQrySecAgentACIDMap cb);	//�����ѯ�����������Ա����Ȩ����Ӧ
	TDAPI_API void RegRspQryProductExchRate(TraderSpi* pSpi, CBRspQryProductExchRate cb);	//�����ѯ��Ʒ���ۻ���
	TDAPI_API void RegRspQryProductGroup(TraderSpi* pSpi, CBRspQryProductGroup cb);	//�����ѯ��Ʒ��
	TDAPI_API void RegRspQryMMInstrumentCommissionRate(TraderSpi* pSpi, CBRspQryMMInstrumentCommissionRate cb);	//�����ѯ�����̺�Լ����������Ӧ
	TDAPI_API void RegRspQryMMOptionInstrCommRate(TraderSpi* pSpi, CBRspQryMMOptionInstrCommRate cb);	//�����ѯ��������Ȩ��Լ��������Ӧ
	TDAPI_API void RegRspQryInstrumentOrderCommRate(TraderSpi* pSpi, CBRspQryInstrumentOrderCommRate cb);	//�����ѯ������������Ӧ
	TDAPI_API void RegRspQrySecAgentTradingAccount(TraderSpi* pSpi, CBRspQrySecAgentTradingAccount cb);	//�����ѯ�ʽ��˻���Ӧ
	TDAPI_API void RegRspQrySecAgentCheckMode(TraderSpi* pSpi, CBRspQrySecAgentCheckMode cb);	//�����ѯ�����������ʽ�У��ģʽ��Ӧ
	TDAPI_API void RegRspQrySecAgentTradeInfo(TraderSpi* pSpi, CBRspQrySecAgentTradeInfo cb);	//�����ѯ������������Ϣ��Ӧ
	TDAPI_API void RegRspQryOptionInstrTradeCost(TraderSpi* pSpi, CBRspQryOptionInstrTradeCost cb);	//�����ѯ��Ȩ���׳ɱ���Ӧ
	TDAPI_API void RegRspQryOptionInstrCommRate(TraderSpi* pSpi, CBRspQryOptionInstrCommRate cb);	//�����ѯ��Ȩ��Լ��������Ӧ
	TDAPI_API void RegRspQryExecOrder(TraderSpi* pSpi, CBRspQryExecOrder cb);	//�����ѯִ��������Ӧ
	TDAPI_API void RegRspQryForQuote(TraderSpi* pSpi, CBRspQryForQuote cb);	//�����ѯѯ����Ӧ
	TDAPI_API void RegRspQryQuote(TraderSpi* pSpi, CBRspQryQuote cb);	//�����ѯ������Ӧ
	TDAPI_API void RegRspQryOptionSelfClose(TraderSpi* pSpi, CBRspQryOptionSelfClose cb);	//�����ѯ��Ȩ�ԶԳ���Ӧ
	TDAPI_API void RegRspQryInvestUnit(TraderSpi* pSpi, CBRspQryInvestUnit cb);	//�����ѯͶ�ʵ�Ԫ��Ӧ
	TDAPI_API void RegRspQryCombInstrumentGuard(TraderSpi* pSpi, CBRspQryCombInstrumentGuard cb);	//�����ѯ��Ϻ�Լ��ȫϵ����Ӧ
	TDAPI_API void RegRspQryCombAction(TraderSpi* pSpi, CBRspQryCombAction cb);	//�����ѯ���������Ӧ
	TDAPI_API void RegRspQryTransferSerial(TraderSpi* pSpi, CBRspQryTransferSerial cb);	//�����ѯת����ˮ��Ӧ
	TDAPI_API void RegOnRspQryAccountregister(TraderSpi* pSpi, CBOnRspQryAccountregister cb);	//�����ѯ����ǩԼ��ϵ��Ӧ
	TDAPI_API void RegErrRtnOrderInsert(TraderSpi* pSpi, CBErrRtnOrderInsert cb);	//����¼�����ر�
	TDAPI_API void RegErrRtnOrderAction(TraderSpi* pSpi, CBErrRtnOrderAction cb);	//������������ر�
	TDAPI_API void RegRtnInstrumentStatus(TraderSpi* pSpi, CBRtnInstrumentStatus cb);	//��Լ����״̬֪ͨ
	TDAPI_API void RegRtnTradingNotice(TraderSpi* pSpi, CBRtnTradingNotice cb);	//����֪ͨ
	TDAPI_API void RegRtnErrorConditionalOrder(TraderSpi* pSpi, CBRtnErrorConditionalOrder cb);	//��ʾ������У�����
	TDAPI_API void RegRspQryContractBank(TraderSpi* pSpi, CBRspQryContractBank cb);	//�����ѯǩԼ������Ӧ
	TDAPI_API void RegRspQryParkedOrder(TraderSpi* pSpi, CBRspQryParkedOrder cb);	//�����ѯԤ����Ӧ
	TDAPI_API void RegRspQryParkedOrderAction(TraderSpi* pSpi, CBRspQryParkedOrderAction cb);	//�����ѯԤ�񳷵���Ӧ
	TDAPI_API void RegRspQryTradingNotice(TraderSpi* pSpi, CBRspQryTradingNotice cb);	//�����ѯ����֪ͨ��Ӧ
	TDAPI_API void RegRspQryBrokerTradingParams(TraderSpi* pSpi, CBRspQryBrokerTradingParams cb);	//�����ѯ���͹�˾���ײ�����Ӧ
	TDAPI_API void RegRspQryBrokerTradingAlgos(TraderSpi* pSpi, CBRspQryBrokerTradingAlgos cb);	//�����ѯ���͹�˾�����㷨��Ӧ
	TDAPI_API void RegRtnFromBankToFutureByBank(TraderSpi* pSpi, CBRtnFromBankToFutureByBank cb);	//���з��������ʽ�ת�ڻ�֪ͨ
	TDAPI_API void RegRtnFromFutureToBankByBank(TraderSpi* pSpi, CBRtnFromFutureToBankByBank cb);	//���з����ڻ��ʽ�ת����֪ͨ
	TDAPI_API void RegRtnRepealFromBankToFutureByBank(TraderSpi* pSpi, CBRtnRepealFromBankToFutureByBank cb);	//���з����������ת�ڻ�֪ͨ
	TDAPI_API void RegRtnRepealFromFutureToBankByBank(TraderSpi* pSpi, CBRtnRepealFromFutureToBankByBank cb);	//���з�������ڻ�ת����֪ͨ
	TDAPI_API void RegRtnFromBankToFutureByFuture(TraderSpi* pSpi, CBRtnFromBankToFutureByFuture cb);	//�ڻ����������ʽ�ת�ڻ�֪ͨ
	TDAPI_API void RegRtnFromFutureToBankByFuture(TraderSpi* pSpi, CBRtnFromFutureToBankByFuture cb);	//�ڻ������ڻ��ʽ�ת����֪ͨ
	TDAPI_API void RegRtnRepealFromBankToFutureByFutureManual(TraderSpi* pSpi, CBRtnRepealFromBankToFutureByFutureManual cb);	//ϵͳ����ʱ�ڻ����ֹ������������ת�ڻ��������д�����Ϻ��̷��ص�֪ͨ
	TDAPI_API void RegRtnRepealFromFutureToBankByFutureManual(TraderSpi* pSpi, CBRtnRepealFromFutureToBankByFutureManual cb);	//ϵͳ����ʱ�ڻ����ֹ���������ڻ�ת�����������д�����Ϻ��̷��ص�֪ͨ
	TDAPI_API void RegRtnQueryBankBalanceByFuture(TraderSpi* pSpi, CBRtnQueryBankBalanceByFuture cb);	//�ڻ������ѯ�������֪ͨ
	TDAPI_API void RegErrRtnBankToFutureByFuture(TraderSpi* pSpi, CBErrRtnBankToFutureByFuture cb);	//�ڻ����������ʽ�ת�ڻ�����ر�
	TDAPI_API void RegErrRtnFutureToBankByFuture(TraderSpi* pSpi, CBErrRtnFutureToBankByFuture cb);	//�ڻ������ڻ��ʽ�ת���д���ر�
	TDAPI_API void RegErrRtnRepealBankToFutureByFutureManual(TraderSpi* pSpi, CBErrRtnRepealBankToFutureByFutureManual cb);	//ϵͳ����ʱ�ڻ����ֹ������������ת�ڻ�����ر�
	TDAPI_API void RegErrRtnRepealFutureToBankByFutureManual(TraderSpi* pSpi, CBErrRtnRepealFutureToBankByFutureManual cb);	//ϵͳ����ʱ�ڻ����ֹ���������ڻ�ת���д���ر�
	TDAPI_API void RegErrRtnQueryBankBalanceByFuture(TraderSpi* pSpi, CBErrRtnQueryBankBalanceByFuture cb);	//�ڻ������ѯ����������ر�
	TDAPI_API void RegRtnRepealFromBankToFutureByFuture(TraderSpi* pSpi, CBRtnRepealFromBankToFutureByFuture cb);	//�ڻ������������ת�ڻ��������д�����Ϻ��̷��ص�֪ͨ
	TDAPI_API void RegRtnRepealFromFutureToBankByFuture(TraderSpi* pSpi, CBRtnRepealFromFutureToBankByFuture cb);	//�ڻ���������ڻ�ת�����������д�����Ϻ��̷��ص�֪ͨ
	TDAPI_API void RegRspFromBankToFutureByFuture(TraderSpi* pSpi, CBRspFromBankToFutureByFuture cb);	//�ڻ����������ʽ�ת�ڻ�Ӧ��
	TDAPI_API void RegRspFromFutureToBankByFuture(TraderSpi* pSpi, CBRspFromFutureToBankByFuture cb);	//�ڻ������ڻ��ʽ�ת����Ӧ��
	TDAPI_API void RegRspQueryBankAccountMoneyByFuture(TraderSpi* pSpi, CBRspQueryBankAccountMoneyByFuture cb);	//�ڻ������ѯ�������Ӧ��
	TDAPI_API void RegRspQueryCFMMCTradingAccountToken(TraderSpi* pSpi, CBRspQueryCFMMCTradingAccountToken cb);	//��ѯ��������û�����Ӧ��
	TDAPI_API void RegRtnCFMMCTradingAccountToken(TraderSpi* pSpi, CBRtnCFMMCTradingAccountToken cb);	//��ѯ��������û�����֪ͨ
#pragma endregion

}
