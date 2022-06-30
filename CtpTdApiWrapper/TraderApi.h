#pragma once
#include "pch.h"
#include "TraderSpi.h"

extern "C"  // ��C�ķ�ʽ����������
{
#pragma  region Api

	TRADEAPI_API CThostFtdcTraderApi* CreateFtdcTraderApi(const char* pszFlowPath = "Flow/");
	TRADEAPI_API TraderSpi*	CreateTraderSpi();
	TRADEAPI_API void		RegisterSpi(CThostFtdcTraderApi* api, TraderSpi* pSpi);

	//��ȡ�ӿڰ汾
	TRADEAPI_API const char* GetApiVersion();

	//����
	//	TRADEAPI_API CThostFtdcTraderApi* Connect(char* frontAddr, char* pszFlowPath, TraderSpi* pSpi);
	////�Ͽ�
	//	TRADEAPI_API void		DisConnect(CThostFtdcTraderApi* pApi);

		///ɾ���ӿڶ�����
		///@remark ����ʹ�ñ��ӿڶ���ʱ,���øú���ɾ���ӿڶ���
	TRADEAPI_API void		Release(CThostFtdcTraderApi* api);

	///��ʼ��
	///@remark ��ʼ�����л���,ֻ�е��ú�,�ӿڲſ�ʼ����
	TRADEAPI_API void		Init(CThostFtdcTraderApi* api);

	///�ȴ��ӿ��߳̽�������
	///@return �߳��˳�����
	TRADEAPI_API int		Join(CThostFtdcTraderApi* api);


	//��ȡ������
	TRADEAPI_API const char* GetTradingDay(CThostFtdcTraderApi* pApi);


	///ע��ǰ�û������ַ
	///@param pszFrontAddress��ǰ�û������ַ��
	///@remark �����ַ�ĸ�ʽΪ����protocol://ipaddress:port�����磺��tcp://127.0.0.1:17001���� 
	///@remark ��tcp��������Э�飬��127.0.0.1�������������ַ����17001������������˿ںš�
	TRADEAPI_API void		RegisterFront(CThostFtdcTraderApi* pApi, char* pszFrontAddress);

	///ע�����ַ����������ַ
	///@param pszNsAddress�����ַ����������ַ��
	///@remark �����ַ�ĸ�ʽΪ����protocol://ipaddress:port�����磺��tcp://127.0.0.1:12001���� 
	///@remark ��tcp��������Э�飬��127.0.0.1�������������ַ����12001������������˿ںš�
	///@remark RegisterNameServer������RegisterFront
	TRADEAPI_API void		RegisterNameServer(CThostFtdcTraderApi* pApi, char* pszNsAddress);

	///ע�����ַ������û���Ϣ
	///@param pFensUserInfo���û���Ϣ��
	TRADEAPI_API void		RegisterFensUserInfo(CThostFtdcTraderApi* pApi, CThostFtdcFensUserInfoField* pFensUserInfo);

	///����˽������
	///@param nResumeType ˽�����ش���ʽ  
	///        THOST_TERT_RESTART:�ӱ������տ�ʼ�ش�
	///        THOST_TERT_RESUME:���ϴ��յ�������
	///        THOST_TERT_QUICK:ֻ���͵�¼��˽����������
	///@remark �÷���Ҫ��Init����ǰ���á����������򲻻��յ�˽���������ݡ�
	TRADEAPI_API void		SubscribePrivateTopic(THOST_TE_RESUME_TYPE nResumeType);

	///���Ĺ�������
	///@param nResumeType �������ش���ʽ  
	///        THOST_TERT_RESTART:�ӱ������տ�ʼ�ش�
	///        THOST_TERT_RESUME:���ϴ��յ�������
	///        THOST_TERT_QUICK:ֻ���͵�¼�󹫹���������
	///@remark �÷���Ҫ��Init����ǰ���á����������򲻻��յ������������ݡ�
	TRADEAPI_API void		SubscribePublicTopic(THOST_TE_RESUME_TYPE nResumeType);



#pragma region Login/out

	//�ͻ�����֤����
	TRADEAPI_API int		ReqAuthenticate(CThostFtdcTraderApi* pApi, CThostFtdcReqAuthenticateField* field, int nRequestID);


	///ע���û��ն���Ϣ�������м̷�����������ģʽ
	///��Ҫ���ն���֤�ɹ����û���¼ǰ���øýӿ�
	TRADEAPI_API int		RegisterUserSystemInfo(CThostFtdcTraderApi* pApi, CThostFtdcUserSystemInfoField* pUserSystemInfo);
	///�ϱ��û��ն���Ϣ�������м̷���������Ա��¼ģʽ
	///����Ա��¼�󣬿��Զ�ε��øýӿ��ϱ��ͻ���Ϣ
	TRADEAPI_API int		SubmitUserSystemInfo(CThostFtdcTraderApi* pApi, CThostFtdcUserSystemInfoField* pUserSystemInfo);


	//�����û���¼����
	TRADEAPI_API int		ReqUserLogin(CThostFtdcTraderApi* pApi, CThostFtdcReqUserLoginField* pReqUserLoginField, int nRequestID);
	//���͵ǳ�����
	TRADEAPI_API int		ReqUserLogout(CThostFtdcTraderApi* pApi, CThostFtdcUserLogoutField* pUserLogout, int nRequestID);


	///�û������������
	TRADEAPI_API int		ReqUserPasswordUpdate(CThostFtdcTraderApi* pApi, CThostFtdcUserPasswordUpdateField* pUserPasswordUpdate, int nRequestID);

	///�ʽ��˻������������
	TRADEAPI_API int		ReqTradingAccountPasswordUpdate(CThostFtdcTraderApi* pApi, CThostFtdcTradingAccountPasswordUpdateField* pTradingAccountPasswordUpdate, int nRequestID);

	///��ѯ�û���ǰ֧�ֵ���֤ģʽ
	TRADEAPI_API int		ReqUserAuthMethod(CThostFtdcTraderApi* pApi, CThostFtdcReqUserAuthMethodField* pReqUserAuthMethod, int nRequestID);

	///�û�������ȡͼ����֤������
	TRADEAPI_API int		ReqGenUserCaptcha(CThostFtdcTraderApi* pApi, CThostFtdcReqGenUserCaptchaField* pReqGenUserCaptcha, int	nRequestID);

	///�û�������ȡ������֤������
	TRADEAPI_API int		ReqGenUserText(CThostFtdcTraderApi* pApi, CThostFtdcReqGenUserTextField* pReqGenUserText, int nRequestID);

	///�û���������ͼƬ��֤��ĵ�½����
	TRADEAPI_API int		ReqUserLoginWithCaptcha(CThostFtdcTraderApi* pApi, CThostFtdcReqUserLoginWithCaptchaField* pReqUserLoginWithCaptcha, int nRequestID);

	///�û��������ж�����֤��ĵ�½����
	TRADEAPI_API int		ReqUserLoginWithText(CThostFtdcTraderApi* pApi, CThostFtdcReqUserLoginWithTextField* pReqUserLoginWithText, int	nRequestID);

	///�û��������ж�̬����ĵ�½����
	TRADEAPI_API int		ReqUserLoginWithOTP(CThostFtdcTraderApi* pApi, CThostFtdcReqUserLoginWithOTPField* pReqUserLoginWithOTP, int nRequestID);

#pragma endregion

	///�����ѯѯ��
	TRADEAPI_API int		ReqQryForQuote(CThostFtdcTraderApi* pApi, CThostFtdcQryForQuoteField* pQryForQuote, int nRequestID);
	///�����ѯ����
	TRADEAPI_API int		ReqQryQuote(CThostFtdcTraderApi* pApi, CThostFtdcQryQuoteField* pQryQuote, int nRequestID);
	///�����ѯ����
	TRADEAPI_API int		ReqQryDepthMarketData(CThostFtdcTraderApi* pApi, CThostFtdcQryDepthMarketDataField* pQryDepthMarketData, int nRequestID);

	///����¼������
	TRADEAPI_API int		ReqOrderInsert(CThostFtdcTraderApi* pApi, CThostFtdcInputOrderField* pInputOrder, int nRequestID);
	///�����ѯ����
	TRADEAPI_API int		ReqQryOrder(CThostFtdcTraderApi* pApi, CThostFtdcQryOrderField* pQryOrder, int nRequestID);
	///��ѯ��󱨵���������
	TRADEAPI_API int		ReqQueryMaxOrderVolume(CThostFtdcTraderApi* pApi, CThostFtdcQueryMaxOrderVolumeField* pQueryMaxOrderVolume, int nRequestID);
	///������������
	TRADEAPI_API int		ReqOrderAction(CThostFtdcTraderApi* pApi, CThostFtdcInputOrderActionField* pInputOrderAction, int nRequestID);
	///����������������
	TRADEAPI_API int		ReqBatchOrderAction(CThostFtdcTraderApi* pApi, CThostFtdcInputBatchOrderActionField* pInputBatchOrderAction, int nRequestID);

	///�����ѯ�ɽ�
	TRADEAPI_API int		ReqQryTrade(CThostFtdcTraderApi* pApi, CThostFtdcQryTradeField* pQryTrade, int nRequestID);

	///Ԥ��¼������
	TRADEAPI_API int		ReqParkedOrderInsert(CThostFtdcTraderApi* pApi, CThostFtdcParkedOrderField* pParkedOrder, int nRequestID);
	///Ԥ�񳷵�¼������
	TRADEAPI_API int		ReqParkedOrderAction(CThostFtdcTraderApi* pApi, CThostFtdcParkedOrderActionField* pParkedOrderAction, int nRequestID);
	///����ɾ��Ԥ��
	TRADEAPI_API int		ReqRemoveParkedOrder(CThostFtdcTraderApi* pApi, CThostFtdcRemoveParkedOrderField* pRemoveParkedOrder, int nRequestID);
	///����ɾ��Ԥ�񳷵�
	TRADEAPI_API int		ReqRemoveParkedOrderAction(CThostFtdcTraderApi* pApi, CThostFtdcRemoveParkedOrderActionField* pRemoveParkedOrderAction, int nRequestID);
	///�����ѯԤ��
	TRADEAPI_API int		ReqQryParkedOrder(CThostFtdcTraderApi* pApi, CThostFtdcQryParkedOrderField* pQryParkedOrder, int nRequestID);
	///�����ѯԤ�񳷵�
	TRADEAPI_API int		ReqQryParkedOrderAction(CThostFtdcTraderApi* pApi, CThostFtdcQryParkedOrderActionField* pQryParkedOrderAction, int nRequestID);

	///�����ѯ�ͻ�֪ͨ
	TRADEAPI_API int		ReqQryNotice(CThostFtdcTraderApi* pApi, CThostFtdcQryNoticeField* pQryNotice, int nRequestID);
	///�����ѯ����֪ͨ
	TRADEAPI_API int		ReqQryTradingNotice(CThostFtdcTraderApi* pApi, CThostFtdcQryTradingNoticeField* pQryTradingNotice, int nRequestID);


	///�����ѯִ������
	TRADEAPI_API int		ReqQryExecOrder(CThostFtdcTraderApi* pApi, CThostFtdcQryExecOrderField* pQryExecOrder, int nRequestID);
	///ִ������¼������
	TRADEAPI_API int		ReqExecOrderInsert(CThostFtdcTraderApi* pApi, CThostFtdcInputExecOrderField* pInputExecOrder, int nRequestID);
	///ִ�������������
	TRADEAPI_API int		ReqExecOrderAction(CThostFtdcTraderApi* pApi, CThostFtdcInputExecOrderActionField* pInputExecOrderAction, int nRequestID);


	///ѯ��¼������
	TRADEAPI_API int		ReqForQuoteInsert(CThostFtdcTraderApi* pApi, CThostFtdcInputForQuoteField* pInputForQuote, int nRequestID);
	///����¼������
	TRADEAPI_API int		ReqQuoteInsert(CThostFtdcTraderApi* pApi, CThostFtdcInputQuoteField* pInputQuote, int nRequestID);
	///���۲�������
	TRADEAPI_API int		ReqQuoteAction(CThostFtdcTraderApi* pApi, CThostFtdcInputQuoteActionField* pInputQuoteAction, int nRequestID);



	///�������¼������
	TRADEAPI_API int		ReqCombActionInsert(CThostFtdcTraderApi* pApi, CThostFtdcInputCombActionField* pInputCombAction, int nRequestID);
	///�����ѯ��Ϻ�Լ��ȫϵ��
	TRADEAPI_API int		ReqQryCombInstrumentGuard(CThostFtdcTraderApi* pApi, CThostFtdcQryCombInstrumentGuardField* pQryCombInstrumentGuard, int nRequestID);
	///�����ѯ�������
	TRADEAPI_API int		ReqQryCombAction(CThostFtdcTraderApi* pApi, CThostFtdcQryCombActionField* pQryCombAction, int nRequestID);


	///�����ѯͶ���ֲ߳�
	TRADEAPI_API int		ReqQryInvestorPosition(CThostFtdcTraderApi* pApi, CThostFtdcQryInvestorPositionField* pQryInvestorPosition, int nRequestID);
	///�����ѯͶ���ֲ߳���ϸ
	TRADEAPI_API int		ReqQryInvestorPositionDetail(CThostFtdcTraderApi* pApi, CThostFtdcQryInvestorPositionDetailField* pQryInvestorPositionDetail, int nRequestID);
	///�����ѯͶ���ֲ߳���ϸ
	TRADEAPI_API int		ReqQryInvestorPositionCombineDetail(CThostFtdcTraderApi* pApi, CThostFtdcQryInvestorPositionCombineDetailField* pQryInvestorPositionCombineDetail, int nRequestID);
	///�����ѯ�ʽ��˻�
	TRADEAPI_API int		ReqQryTradingAccount(CThostFtdcTraderApi* pApi, CThostFtdcQryTradingAccountField* pQryTradingAccount, int nRequestID);
	///�����ѯͶ����
	TRADEAPI_API int		ReqQryInvestor(CThostFtdcTraderApi* pApi, CThostFtdcQryInvestorField* pQryInvestor, int nRequestID);
	///�����ѯ���ױ���
	TRADEAPI_API int		ReqQryTradingCode(CThostFtdcTraderApi* pApi, CThostFtdcQryTradingCodeField* pQryTradingCode, int nRequestID);
	///�����ѯͶ���߽�����
	TRADEAPI_API int		ReqQrySettlementInfo(CThostFtdcTraderApi* pApi, CThostFtdcQrySettlementInfoField* pQrySettlementInfo, int nRequestID);
	///�����ѯ������Ϣȷ��
	TRADEAPI_API int		ReqQrySettlementInfoConfirm(CThostFtdcTraderApi* pApi, CThostFtdcQrySettlementInfoConfirmField* pQrySettlementInfoConfirm, int nRequestID);
	///Ͷ���߽�����ȷ��
	TRADEAPI_API int		ReqSettlementInfoConfirm(CThostFtdcTraderApi* pApi, CThostFtdcSettlementInfoConfirmField* pSettlementInfoConfirm, int nRequestID);
	///�����ѯͶ�ʵ�Ԫ
	TRADEAPI_API int		ReqQryInvestUnit(CThostFtdcTraderApi* pApi, CThostFtdcQryInvestUnitField* pQryInvestUnit, int nRequestID);


#pragma region product/Instrument
	///�����ѯ��Ʒ
	TRADEAPI_API int		ReqQryProduct(CThostFtdcTraderApi* pApi, CThostFtdcQryProductField* pQryProduct, int nRequestID);
	///�����ѯ��Ʒ���ۻ���
	TRADEAPI_API int		ReqQryProductExchRate(CThostFtdcTraderApi* pApi, CThostFtdcQryProductExchRateField* pQryProductExchRate, int nRequestID);
	///�����ѯ��Ʒ��
	TRADEAPI_API int		ReqQryProductGroup(CThostFtdcTraderApi* pApi, CThostFtdcQryProductGroupField* pQryProductGroup, int nRequestID);

	///�����ѯ��Լ
	TRADEAPI_API int		ReqQryInstrument(CThostFtdcTraderApi* pApi, CThostFtdcQryInstrumentField* pQryInstrument, int nRequestID);
	///�����ѯ��Լ��֤����
	TRADEAPI_API int		ReqQryInstrumentMarginRate(CThostFtdcTraderApi* pApi, CThostFtdcQryInstrumentMarginRateField* pQryInstrumentMarginRate, int nRequestID);
	///�����ѯ��Լ��������
	TRADEAPI_API int		ReqQryInstrumentCommissionRate(CThostFtdcTraderApi* pApi, CThostFtdcQryInstrumentCommissionRateField* pQryInstrumentCommissionRate, int nRequestID);

	///�����ѯͶ����Ʒ��/��Ʒ�ֱ�֤��
	TRADEAPI_API int		ReqQryInvestorProductGroupMargin(CThostFtdcTraderApi* pApi, CThostFtdcQryInvestorProductGroupMarginField* pQryInvestorProductGroupMargin, int nRequestID);

	///�����ѯ�����̺�Լ��������
	TRADEAPI_API int		ReqQryMMInstrumentCommissionRate(CThostFtdcTraderApi* pApi, CThostFtdcQryMMInstrumentCommissionRateField* pQryMMInstrumentCommissionRate, int nRequestID);
	///�����ѯ��������Ȩ��Լ������
	TRADEAPI_API int		ReqQryMMOptionInstrCommRate(CThostFtdcTraderApi* pApi, CThostFtdcQryMMOptionInstrCommRateField* pQryMMOptionInstrCommRate, int nRequestID);

	///�����ѯ�ֵ��۵���Ϣ
	TRADEAPI_API int		ReqQryEWarrantOffset(CThostFtdcTraderApi* pApi, CThostFtdcQryEWarrantOffsetField* pQryEWarrantOffset, int nRequestID);

	///�����ѯ����������
	TRADEAPI_API int		ReqQryInstrumentOrderCommRate(CThostFtdcTraderApi* pApi, CThostFtdcQryInstrumentOrderCommRateField* pQryInstrumentOrderCommRate, int nRequestID);
#pragma endregion


#pragma region ��������/sec agent
	///�����ѯ�ʽ��˻�
	TRADEAPI_API int		ReqQrySecAgentTradingAccount(CThostFtdcTraderApi* pApi, CThostFtdcQryTradingAccountField* pQryTradingAccount, int nRequestID);
	///�����ѯ�����������Ա����Ȩ��
	TRADEAPI_API int		ReqQrySecAgentACIDMap(CThostFtdcTraderApi* pApi, CThostFtdcQrySecAgentACIDMapField* pQrySecAgentACIDMap, int nRequestID);
	///�����ѯ�����������ʽ�У��ģʽ
	TRADEAPI_API int		ReqQrySecAgentCheckMode(CThostFtdcTraderApi* pApi, CThostFtdcQrySecAgentCheckModeField* pQrySecAgentCheckMode, int nRequestID);
	///�����ѯ������������Ϣ
	TRADEAPI_API int		ReqQrySecAgentTradeInfo(CThostFtdcTraderApi* pApi, CThostFtdcQrySecAgentTradeInfoField* pQrySecAgentTradeInfo, int nRequestID);
#pragma endregion


#pragma region ��Ȩoption
	///��Ȩ�ԶԳ�¼������
	TRADEAPI_API int		ReqOptionSelfCloseInsert(CThostFtdcTraderApi* pApi, CThostFtdcInputOptionSelfCloseField* pInputOptionSelfClose, int nRequestID);
	///��Ȩ�ԶԳ��������
	TRADEAPI_API int		ReqOptionSelfCloseAction(CThostFtdcTraderApi* pApi, CThostFtdcInputOptionSelfCloseActionField* pInputOptionSelfCloseAction, int nRequestID);

	///�����ѯ��Ȩ���׳ɱ�
	TRADEAPI_API int		ReqQryOptionInstrTradeCost(CThostFtdcTraderApi* pApi, CThostFtdcQryOptionInstrTradeCostField* pQryOptionInstrTradeCost, int nRequestID);
	///�����ѯ��Ȩ��Լ������
	TRADEAPI_API int		ReqQryOptionInstrCommRate(CThostFtdcTraderApi* pApi, CThostFtdcQryOptionInstrCommRateField* pQryOptionInstrCommRate, int nRequestID);
	///�����ѯ��Ȩ�ԶԳ�
	TRADEAPI_API int		ReqQryOptionSelfClose(CThostFtdcTraderApi* pApi, CThostFtdcQryOptionSelfCloseField* pQryOptionSelfClose, int nRequestID);
#pragma endregion


#pragma region Banking
	///�����ѯת������
	TRADEAPI_API int		ReqQryTransferBank(CThostFtdcTraderApi* pApi, CThostFtdcQryTransferBankField* pQryTransferBank, int nRequestID);
	///�����ѯ����ǩԼ��ϵ
	TRADEAPI_API int		ReqQryAccountregister(CThostFtdcTraderApi* pApi, CThostFtdcQryAccountregisterField* pQryAccountregister, int nRequestID);
	///�����ѯǩԼ����
	TRADEAPI_API int		ReqQryContractBank(CThostFtdcTraderApi* pApi, CThostFtdcQryContractBankField* pQryContractBank, int nRequestID);
	///�����ѯת����ˮ
	TRADEAPI_API int		ReqQryTransferSerial(CThostFtdcTraderApi* pApi, CThostFtdcQryTransferSerialField* pQryTransferSerial, int nRequestID);
	///�ڻ������ѯ�����������
	TRADEAPI_API int		ReqQueryBankAccountMoneyByFuture(CThostFtdcTraderApi* pApi, CThostFtdcReqQueryAccountField* pReqQueryAccount, int nRequestID);

	///�ڻ����������ʽ�ת�ڻ�����
	TRADEAPI_API int		ReqFromBankToFutureByFuture(CThostFtdcTraderApi* pApi, CThostFtdcReqTransferField* pReqTransfer, int nRequestID);
	///�ڻ������ڻ��ʽ�ת��������
	TRADEAPI_API int		ReqFromFutureToBankByFuture(CThostFtdcTraderApi* pApi, CThostFtdcReqTransferField* pReqTransfer, int nRequestID);
#pragma endregion


#pragma region Exchange/������
	///�����ѯ������
	TRADEAPI_API int		ReqQryExchange(CThostFtdcTraderApi* pApi, CThostFtdcQryExchangeField* pQryExchange, int nRequestID);
	///�����ѯ��������֤����
	TRADEAPI_API int		ReqQryExchangeMarginRate(CThostFtdcTraderApi* pApi, CThostFtdcQryExchangeMarginRateField* pQryExchangeMarginRate, int nRequestID);
	///�����ѯ������������֤����
	TRADEAPI_API int		ReqQryExchangeMarginRateAdjust(CThostFtdcTraderApi* pApi, CThostFtdcQryExchangeMarginRateAdjustField* pQryExchangeMarginRateAdjust, int nRequestID);
	///�����ѯ����
	TRADEAPI_API int		ReqQryExchangeRate(CThostFtdcTraderApi* pApi, CThostFtdcQryExchangeRateField* pQryExchangeRate, int nRequestID);
#pragma endregion


#pragma region Broker
	///�����ѯ���͹�˾���ײ���
	TRADEAPI_API int		ReqQryBrokerTradingParams(CThostFtdcTraderApi* pApi, CThostFtdcQryBrokerTradingParamsField* pQryBrokerTradingParams, int nRequestID);
	///�����ѯ���͹�˾�����㷨
	TRADEAPI_API int		ReqQryBrokerTradingAlgos(CThostFtdcTraderApi* pApi, CThostFtdcQryBrokerTradingAlgosField* pQryBrokerTradingAlgos, int nRequestID);
#pragma endregion

#pragma region CFMMC
	///�����ѯ��������û�����
	TRADEAPI_API int		ReqQueryCFMMCTradingAccountToken(CThostFtdcTraderApi* pApi, CThostFtdcQueryCFMMCTradingAccountTokenField* pQueryCFMMCTradingAccountToken, int nRequestID);

	///�����ѯ��֤����ϵͳ���͹�˾�ʽ��˻���Կ
	TRADEAPI_API int		ReqQryCFMMCTradingAccountKey(CThostFtdcTraderApi* pApi, CThostFtdcQryCFMMCTradingAccountKeyField* pQryCFMMCTradingAccountKey, int nRequestID);
#pragma endregion




#pragma endregion

#pragma region ע��ص�����
	//========================================
	//==================================== �ص����� =======================================

	TRADEAPI_API void RegOnFrontConnected(TraderSpi* pSpi, CBOnFrontConnected cb);		//���ͻ����뽻�׺�̨������ͨ������ʱ����δ��¼ǰ�����÷��������á�
	TRADEAPI_API void RegOnFrontDisconnected(TraderSpi* pSpi, CBOnFrontDisconnected cb);		//���ͻ����뽻�׺�̨ͨ�����ӶϿ�ʱ���÷��������á���������������API���Զ��������ӣ��ͻ��˿ɲ�������
	TRADEAPI_API void RegOnHeartBeatWarning(TraderSpi* pSpi, CBOnHeartBeatWarning cb);		//������ʱ���档����ʱ��δ�յ�����ʱ���÷��������á�
	TRADEAPI_API void RegRspAuthenticate(TraderSpi* pSpi, CBRspAuthenticate cb);

	TRADEAPI_API void RegRspUserLogin(TraderSpi* pSpi, CBRspUserLogin cb);	//��¼������Ӧ
	TRADEAPI_API void RegRspUserLogout(TraderSpi* pSpi, CBRspUserLogout cb);	//�ǳ�������Ӧ

	TRADEAPI_API void RegRspUserPasswordUpdate(TraderSpi* pSpi, CBRspUserPasswordUpdate cb);	//�û��������������Ӧ
	TRADEAPI_API void RegRspTradingAccountPasswordUpdate(TraderSpi* pSpi, CBRspTradingAccountPasswordUpdate cb);	//�ʽ��˻��������������Ӧ
	TRADEAPI_API void RegRspUserAuthMethod(TraderSpi* pSpi, CBRspUserAuthMethod cb);	//��ѯ�û���ǰ֧�ֵ���֤ģʽ�Ļظ�
	TRADEAPI_API void RegRspGenUserCaptcha(TraderSpi* pSpi, CBRspGenUserCaptcha cb);	//��ȡͼ����֤������Ļظ�
	TRADEAPI_API void RegRspGenUserText(TraderSpi* pSpi, CBRspGenUserText cb);	//��ȡ������֤������Ļظ�
	TRADEAPI_API void RegRspOrderInsert(TraderSpi* pSpi, CBRspOrderInsert cb);	//����¼��������Ӧ
	TRADEAPI_API void RegRspParkedOrderInsert(TraderSpi* pSpi, CBRspParkedOrderInsert cb);	//Ԥ��¼��������Ӧ
	TRADEAPI_API void RegRspParkedOrderAction(TraderSpi* pSpi, CBRspParkedOrderAction cb);	//Ԥ�񳷵�¼��������Ӧ
	TRADEAPI_API void RegRspOrderAction(TraderSpi* pSpi, CBRspOrderAction cb);	//��������������Ӧ
	TRADEAPI_API void RegRspQueryMaxOrderVolume(TraderSpi* pSpi, CBRspQueryMaxOrderVolume cb);	//��ѯ��󱨵�������Ӧ
	TRADEAPI_API void RegRspSettlementInfoConfirm(TraderSpi* pSpi, CBRspSettlementInfoConfirm cb);	//Ͷ���߽�����ȷ����Ӧ
	TRADEAPI_API void RegRspRemoveParkedOrder(TraderSpi* pSpi, CBRspRemoveParkedOrder cb);	//ɾ��Ԥ����Ӧ
	TRADEAPI_API void RegRspRemoveParkedOrderAction(TraderSpi* pSpi, CBRspRemoveParkedOrderAction cb);	//ɾ��Ԥ�񳷵���Ӧ
	TRADEAPI_API void RegBatchOrderAction(TraderSpi* pSpi, CBRspBatchOrderAction cb);	//������������������Ӧ
	TRADEAPI_API void RegCombActionInsert(TraderSpi* pSpi, CBRspCombActionInsert cb);	//�������¼��������Ӧ
	TRADEAPI_API void RegRspQryOrder(TraderSpi* pSpi, CBRspQryOrder cb);	//�����ѯ������Ӧ
	TRADEAPI_API void RegRspQryTrade(TraderSpi* pSpi, CBRspQryTrade cb);	//�����ѯ�ɽ���Ӧ
	TRADEAPI_API void RegRspQryInvestorPosition(TraderSpi* pSpi, CBRspQryInvestorPosition cb);	//�����ѯͶ���ֲ߳���Ӧ
	TRADEAPI_API void RegRspQryTradingAccount(TraderSpi* pSpi, CBRspQryTradingAccount cb);	//�����ѯ�ʽ��˻���Ӧ
	TRADEAPI_API void RegRspQryInvestor(TraderSpi* pSpi, CBRspQryInvestor cb);	//�����ѯͶ������Ӧ
	TRADEAPI_API void RegRspQryTradingCode(TraderSpi* pSpi, CBRspQryTradingCode cb);	//�����ѯ���ױ�����Ӧ
	TRADEAPI_API void RegRspQryInstrumentMarginRate(TraderSpi* pSpi, CBRspQryInstrumentMarginRate cb);	//�����ѯ��Լ��֤������Ӧ
	TRADEAPI_API void RegRspQryInstrumentCommissionRate(TraderSpi* pSpi, CBRspQryInstrumentCommissionRate cb);	//�����ѯ��Լ����������Ӧ
	TRADEAPI_API void RegRspQryExchange(TraderSpi* pSpi, CBRspQryExchange cb);	//�����ѯ��������Ӧ
	TRADEAPI_API void RegRspQryInstrument(TraderSpi* pSpi, CBRspQryInstrument cb);	//�����ѯ��Լ��Ӧ
	TRADEAPI_API void RegRspQryDepthMarketData(TraderSpi* pSpi, CBRspQryDepthMarketData cb);	//�����ѯ������Ӧ
	TRADEAPI_API void RegRspQrySettlementInfo(TraderSpi* pSpi, CBRspQrySettlementInfo cb);	//�����ѯͶ���߽�������Ӧ
	TRADEAPI_API void RegRspQryTransferBank(TraderSpi* pSpi, CBRspQryTransferBank cb);	//�����ѯת��������Ӧ
	TRADEAPI_API void RegRspQryInvestorPositionDetail(TraderSpi* pSpi, CBRspQryInvestorPositionDetail cb);	//�����ѯͶ���ֲ߳���ϸ��Ӧ
	TRADEAPI_API void RegRspQryNotice(TraderSpi* pSpi, CBRspQryNotice cb);	//�����ѯ�ͻ�֪ͨ��Ӧ
	TRADEAPI_API void RegRspQrySettlementInfoConfirm(TraderSpi* pSpi, CBRspQrySettlementInfoConfirm cb);	//�����ѯ������Ϣȷ����Ӧ
	TRADEAPI_API void RegRspQryInvestorPositionCombineDetail(TraderSpi* pSpi, CBRspQryInvestorPositionCombineDetail cb);	//�����ѯͶ���ֲ߳���ϸ��Ӧ
	TRADEAPI_API void RegRspQryCFMMCTradingAccountKey(TraderSpi* pSpi, CBRspQryCFMMCTradingAccountKey cb);	//��ѯ��֤����ϵͳ���͹�˾�ʽ��˻���Կ��Ӧ
	TRADEAPI_API void RegRspQryEWarrantOffset(TraderSpi* pSpi, CBRspQryEWarrantOffset cb);	//�����ѯ�ֵ��۵���Ϣ
	TRADEAPI_API void RegRspQryInvestorProductGroupMargin(TraderSpi* pSpi, CBRspQryInvestorProductGroupMargin cb);	//�����ѯͶ����Ʒ��/��Ʒ�ֱ�֤��
	TRADEAPI_API void RegRspQryExchangeMarginRate(TraderSpi* pSpi, CBRspQryExchangeMarginRate cb);	//�����ѯ��������֤����
	TRADEAPI_API void RegRspQryExchangeMarginRateAdjust(TraderSpi* pSpi, CBRspQryExchangeMarginRateAdjust cb);	//�����ѯ������������֤����
	TRADEAPI_API void RegRspQryExchangeRate(TraderSpi* pSpi, CBRspQryExchangeRate cb);	//�����ѯ������Ӧ
	TRADEAPI_API void RegRspQrySecAgentACIDMap(TraderSpi* pSpi, CBRspQrySecAgentACIDMap cb);	//�����ѯ�����������Ա����Ȩ����Ӧ
	TRADEAPI_API void RegRspQryProductExchRate(TraderSpi* pSpi, CBRspQryProductExchRate cb);	//�����ѯ��Ʒ���ۻ���
	TRADEAPI_API void RegRspQryProductGroup(TraderSpi* pSpi, CBRspQryProductGroup cb);	//�����ѯ��Ʒ��
	TRADEAPI_API void RegRspQryMMInstrumentCommissionRate(TraderSpi* pSpi, CBRspQryMMInstrumentCommissionRate cb);	//�����ѯ�����̺�Լ����������Ӧ
	TRADEAPI_API void RegRspQryMMOptionInstrCommRate(TraderSpi* pSpi, CBRspQryMMOptionInstrCommRate cb);	//�����ѯ��������Ȩ��Լ��������Ӧ
	TRADEAPI_API void RegRspQryInstrumentOrderCommRate(TraderSpi* pSpi, CBRspQryInstrumentOrderCommRate cb);	//�����ѯ������������Ӧ
	TRADEAPI_API void RegRspQrySecAgentTradingAccount(TraderSpi* pSpi, CBRspQrySecAgentTradingAccount cb);	//�����ѯ�ʽ��˻���Ӧ
	TRADEAPI_API void RegRspQrySecAgentCheckMode(TraderSpi* pSpi, CBRspQrySecAgentCheckMode cb);	//�����ѯ�����������ʽ�У��ģʽ��Ӧ
	TRADEAPI_API void RegRspQrySecAgentTradeInfo(TraderSpi* pSpi, CBRspQrySecAgentTradeInfo cb);	//�����ѯ������������Ϣ��Ӧ
	TRADEAPI_API void RegRspQryOptionInstrTradeCost(TraderSpi* pSpi, CBRspQryOptionInstrTradeCost cb);	//�����ѯ��Ȩ���׳ɱ���Ӧ
	TRADEAPI_API void RegRspQryOptionInstrCommRate(TraderSpi* pSpi, CBRspQryOptionInstrCommRate cb);	//�����ѯ��Ȩ��Լ��������Ӧ
	TRADEAPI_API void RegRspQryExecOrder(TraderSpi* pSpi, CBRspQryExecOrder cb);	//�����ѯִ��������Ӧ
	TRADEAPI_API void RegRspQryForQuote(TraderSpi* pSpi, CBRspQryForQuote cb);	//�����ѯѯ����Ӧ
	TRADEAPI_API void RegRspQryQuote(TraderSpi* pSpi, CBRspQryQuote cb);	//�����ѯ������Ӧ
	TRADEAPI_API void RegRspQryOptionSelfClose(TraderSpi* pSpi, CBRspQryOptionSelfClose cb);	//�����ѯ��Ȩ�ԶԳ���Ӧ
	TRADEAPI_API void RegRspQryInvestUnit(TraderSpi* pSpi, CBRspQryInvestUnit cb);	//�����ѯͶ�ʵ�Ԫ��Ӧ
	TRADEAPI_API void RegRspQryCombInstrumentGuard(TraderSpi* pSpi, CBRspQryCombInstrumentGuard cb);	//�����ѯ��Ϻ�Լ��ȫϵ����Ӧ
	TRADEAPI_API void RegRspQryCombAction(TraderSpi* pSpi, CBRspQryCombAction cb);	//�����ѯ���������Ӧ
	TRADEAPI_API void RegRspQryTransferSerial(TraderSpi* pSpi, CBRspQryTransferSerial cb);	//�����ѯת����ˮ��Ӧ
	TRADEAPI_API void RegRspQryAccountregister(TraderSpi* pSpi, CBRspQryAccountregister cb);	//�����ѯ����ǩԼ��ϵ��Ӧ
	TRADEAPI_API void RegRspError(TraderSpi* pSpi, CBRspError cb);	//����Ӧ��
	TRADEAPI_API void RegRtnOrder(TraderSpi* pSpi, CBRtnOrder cb);	//����֪ͨ
	TRADEAPI_API void RegRtnTrade(TraderSpi* pSpi, CBRtnTrade cb);	//�ɽ�֪ͨ
	TRADEAPI_API void RegErrRtnOrderInsert(TraderSpi* pSpi, CBErrRtnOrderInsert cb);	//����¼�����ر�
	TRADEAPI_API void RegErrRtnOrderAction(TraderSpi* pSpi, CBErrRtnOrderAction cb);	//������������ر�
	TRADEAPI_API void RegRtnInstrumentStatus(TraderSpi* pSpi, CBRtnInstrumentStatus cb);	//��Լ����״̬֪ͨ
	TRADEAPI_API void RegRtnTradingNotice(TraderSpi* pSpi, CBRtnTradingNotice cb);	//����֪ͨ
	TRADEAPI_API void RegRtnErrorConditionalOrder(TraderSpi* pSpi, CBRtnErrorConditionalOrder cb);	//��ʾ������У�����
	TRADEAPI_API void RegRspQryContractBank(TraderSpi* pSpi, CBRspQryContractBank cb);	//�����ѯǩԼ������Ӧ
	TRADEAPI_API void RegRspQryParkedOrder(TraderSpi* pSpi, CBRspQryParkedOrder cb);	//�����ѯԤ����Ӧ
	TRADEAPI_API void RegRspQryParkedOrderAction(TraderSpi* pSpi, CBRspQryParkedOrderAction cb);	//�����ѯԤ�񳷵���Ӧ
	TRADEAPI_API void RegRspQryTradingNotice(TraderSpi* pSpi, CBRspQryTradingNotice cb);	//�����ѯ����֪ͨ��Ӧ
	TRADEAPI_API void RegRspQryBrokerTradingParams(TraderSpi* pSpi, CBRspQryBrokerTradingParams cb);	//�����ѯ���͹�˾���ײ�����Ӧ
	TRADEAPI_API void RegRspQryBrokerTradingAlgos(TraderSpi* pSpi, CBRspQryBrokerTradingAlgos cb);	//�����ѯ���͹�˾�����㷨��Ӧ
	TRADEAPI_API void RegRtnFromBankToFutureByBank(TraderSpi* pSpi, CBRtnFromBankToFutureByBank cb);	//���з��������ʽ�ת�ڻ�֪ͨ
	TRADEAPI_API void RegRtnFromFutureToBankByBank(TraderSpi* pSpi, CBRtnFromFutureToBankByBank cb);	//���з����ڻ��ʽ�ת����֪ͨ
	TRADEAPI_API void RegRtnRepealFromBankToFutureByBank(TraderSpi* pSpi, CBRtnRepealFromBankToFutureByBank cb);	//���з����������ת�ڻ�֪ͨ
	TRADEAPI_API void RegRtnRepealFromFutureToBankByBank(TraderSpi* pSpi, CBRtnRepealFromFutureToBankByBank cb);	//���з�������ڻ�ת����֪ͨ
	TRADEAPI_API void RegRtnFromBankToFutureByFuture(TraderSpi* pSpi, CBRtnFromBankToFutureByFuture cb);	//�ڻ����������ʽ�ת�ڻ�֪ͨ
	TRADEAPI_API void RegRtnFromFutureToBankByFuture(TraderSpi* pSpi, CBRtnFromFutureToBankByFuture cb);	//�ڻ������ڻ��ʽ�ת����֪ͨ
	TRADEAPI_API void RegRtnRepealFromBankToFutureByFutureManual(TraderSpi* pSpi, CBRtnRepealFromBankToFutureByFutureManual cb);	//ϵͳ����ʱ�ڻ����ֹ������������ת�ڻ��������д�����Ϻ��̷��ص�֪ͨ
	TRADEAPI_API void RegRtnRepealFromFutureToBankByFutureManual(TraderSpi* pSpi, CBRtnRepealFromFutureToBankByFutureManual cb);	//ϵͳ����ʱ�ڻ����ֹ���������ڻ�ת�����������д�����Ϻ��̷��ص�֪ͨ
	TRADEAPI_API void RegRtnQueryBankBalanceByFuture(TraderSpi* pSpi, CBRtnQueryBankBalanceByFuture cb);	//�ڻ������ѯ�������֪ͨ
	TRADEAPI_API void RegErrRtnBankToFutureByFuture(TraderSpi* pSpi, CBErrRtnBankToFutureByFuture cb);	//�ڻ����������ʽ�ת�ڻ�����ر�
	TRADEAPI_API void RegErrRtnFutureToBankByFuture(TraderSpi* pSpi, CBErrRtnFutureToBankByFuture cb);	//�ڻ������ڻ��ʽ�ת���д���ر�
	TRADEAPI_API void RegErrRtnRepealBankToFutureByFutureManual(TraderSpi* pSpi, CBErrRtnRepealBankToFutureByFutureManual cb);	//ϵͳ����ʱ�ڻ����ֹ������������ת�ڻ�����ر�
	TRADEAPI_API void RegErrRtnRepealFutureToBankByFutureManual(TraderSpi* pSpi, CBErrRtnRepealFutureToBankByFutureManual cb);	//ϵͳ����ʱ�ڻ����ֹ���������ڻ�ת���д���ر�
	TRADEAPI_API void RegErrRtnQueryBankBalanceByFuture(TraderSpi* pSpi, CBErrRtnQueryBankBalanceByFuture cb);	//�ڻ������ѯ����������ر�
	TRADEAPI_API void RegRtnRepealFromBankToFutureByFuture(TraderSpi* pSpi, CBRtnRepealFromBankToFutureByFuture cb);	//�ڻ������������ת�ڻ��������д�����Ϻ��̷��ص�֪ͨ
	TRADEAPI_API void RegRtnRepealFromFutureToBankByFuture(TraderSpi* pSpi, CBRtnRepealFromFutureToBankByFuture cb);	//�ڻ���������ڻ�ת�����������д�����Ϻ��̷��ص�֪ͨ
	TRADEAPI_API void RegRspFromBankToFutureByFuture(TraderSpi* pSpi, CBRspFromBankToFutureByFuture cb);	//�ڻ����������ʽ�ת�ڻ�Ӧ��
	TRADEAPI_API void RegRspFromFutureToBankByFuture(TraderSpi* pSpi, CBRspFromFutureToBankByFuture cb);	//�ڻ������ڻ��ʽ�ת����Ӧ��
	TRADEAPI_API void RegRspQueryBankAccountMoneyByFuture(TraderSpi* pSpi, CBRspQueryBankAccountMoneyByFuture cb);	//�ڻ������ѯ�������Ӧ��
	TRADEAPI_API void RegRspQueryCFMMCTradingAccountToken(TraderSpi* pSpi, CBRspQueryCFMMCTradingAccountToken cb);	//��ѯ��������û�����Ӧ��
	TRADEAPI_API void RegRtnCFMMCTradingAccountToken(TraderSpi* pSpi, CBRtnCFMMCTradingAccountToken cb);	//��ѯ��������û�����֪ͨ
#pragma endregion

}
