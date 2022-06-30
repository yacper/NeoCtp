#include "pch.h"
#include "TraderApi.h"

#include <filesystem>
using namespace std;


TRADEAPI_API CThostFtdcTraderApi* CreateFtdcTraderApi(const char* pszFlowPath)
{
	filesystem::path p(pszFlowPath);
	if (!filesystem::exists(pszFlowPath))
		filesystem::create_directory(p);

	// ��ʼ��UserApi
	CThostFtdcTraderApi* pApi = CThostFtdcTraderApi::CreateFtdcTraderApi(pszFlowPath);			// ����UserApi	
	return pApi;
}
TRADEAPI_API TraderSpi* CreateTraderSpi()
{
	TraderSpi* ret = new TraderSpi();
	return ret;
}
TRADEAPI_API void			RegisterSpi(CThostFtdcTraderApi* api, TraderSpi* pSpi)
{
	api->RegisterSpi(pSpi);
}


//��ȡ�ӿڰ汾
TRADEAPI_API const char* GetApiVersion()
{
	return CThostFtdcTraderApi::GetApiVersion();
}

////����
//TRADEAPI_API CThostFtdcTraderApi* Connect(char *frontAddr, char *pszFlowPath, TraderSpi* pSpi)
//{
//	// ��ʼ��UserApi
//	CThostFtdcTraderApi* pApi = CThostFtdcTraderApi::CreateFtdcTraderApi(pszFlowPath);			// ����UserApi	
//																									//CTraderSpi* pSpi = new CTraderSpi();
//	pApi->RegisterSpi((CThostFtdcTraderSpi*)pSpi);			// ע���¼���
//	pApi->SubscribePublicTopic(THOST_TERT_QUICK/*THOST_TERT_RESTART*/);					// ע�ṫ����
//	pApi->SubscribePrivateTopic(THOST_TERT_QUICK/*THOST_TERT_RESTART*/);					// ע��˽����
//	pApi->RegisterFront(frontAddr);							// connect
//	pApi->Init();
//	//pApi->Join();
//	return pApi;
//}

////�Ͽ�
//TRADEAPI_API void DisConnect(CThostFtdcTraderApi* pApi)
//{
//	if (pApi == NULL) return;
//
//	pApi->RegisterSpi(NULL);
//	pApi->Release();
//	pApi = NULL;
//}

///ɾ���ӿڶ�����
///@remark ����ʹ�ñ��ӿڶ���ʱ,���øú���ɾ���ӿڶ���
TRADEAPI_API void Release(CThostFtdcTraderApi* api)
{
	api->Release();
}

///��ʼ��
///@remark ��ʼ�����л���,ֻ�е��ú�,�ӿڲſ�ʼ����
TRADEAPI_API void Init(CThostFtdcTraderApi* api)
{
	api->Init();
}

///�ȴ��ӿ��߳̽�������
///@return �߳��˳�����
TRADEAPI_API int Join(CThostFtdcTraderApi* api)
{
	return api->Join();
}

//��ȡ������
TRADEAPI_API const char* GetTradingDay(CThostFtdcTraderApi* pApi)
{
	if (pApi == NULL) return NULL;

	return pApi->GetTradingDay();
}

TRADEAPI_API void		RegisterFront(CThostFtdcTraderApi* pApi, char* pszFrontAddress)
{
	pApi->RegisterFront(pszFrontAddress);
}

TRADEAPI_API void		RegisterNameServer(CThostFtdcTraderApi* pApi, char* pszNsAddress)
{
	pApi->RegisterNameServer(pszNsAddress);
}

///ע�����ַ������û���Ϣ
///@param pFensUserInfo���û���Ϣ��
TRADEAPI_API void		RegisterFensUserInfo(CThostFtdcTraderApi* pApi, CThostFtdcFensUserInfoField* pFensUserInfo)
{
	pApi->RegisterFensUserInfo(pFensUserInfo);
}

TRADEAPI_API void		SubscribePrivateTopic(CThostFtdcTraderApi* pApi, THOST_TE_RESUME_TYPE nResumeType)
{
	pApi->SubscribePrivateTopic(nResumeType);
}

///���Ĺ�������
///@param nResumeType �������ش���ʽ  
///        THOST_TERT_RESTART:�ӱ������տ�ʼ�ش�
///        THOST_TERT_RESUME:���ϴ��յ�������
///        THOST_TERT_QUICK:ֻ���͵�¼�󹫹���������
///@remark �÷���Ҫ��Init����ǰ���á����������򲻻��յ������������ݡ�
TRADEAPI_API void		SubscribePublicTopic(CThostFtdcTraderApi* pApi, THOST_TE_RESUME_TYPE nResumeType)
{
	pApi->SubscribePublicTopic(nResumeType);
}

TRADEAPI_API int		ReqAuthenticate(CThostFtdcTraderApi* pApi, CThostFtdcReqAuthenticateField* field, int nRequestID)
{
	return pApi->ReqAuthenticate(field, nRequestID);
}

TRADEAPI_API int		RegisterUserSystemInfo(CThostFtdcTraderApi* pApi, CThostFtdcUserSystemInfoField* pUserSystemInfo)
{
	return pApi->RegisterUserSystemInfo(pUserSystemInfo);
}

TRADEAPI_API int		SubmitUserSystemInfo(CThostFtdcTraderApi* pApi, CThostFtdcUserSystemInfoField* pUserSystemInfo)
{
	return pApi->SubmitUserSystemInfo(pUserSystemInfo);
}

////�ͻ�����֤����
//TRADEAPI_API int		ReqAuthenticate(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcUserIDType userID,
//	TThostFtdcProductInfoType productInfo, TThostFtdcAuthCodeType authCode, TThostFtdcAppIDType	appID)
//{
//	if (pApi == NULL) return -1;
//
//	CThostFtdcReqAuthenticateField req;
//	memset(&req, 0, sizeof(req));
//	strcpy_s(req.BrokerID, brokerID);
//	strcpy_s(req.UserID, userID);
//	strcpy_s(req.UserProductInfo, productInfo);
//	strcpy_s(req.AuthCode, authCode);
//	strcpy_s(req.AppID, appID);
//
//	return pApi->ReqAuthenticate(&req, requestID);
//}
TRADEAPI_API int		ReqUserLogin(CThostFtdcTraderApi* pApi, CThostFtdcReqUserLoginField* pReqUserLoginField, int nRequestID)
{
	return pApi->ReqUserLogin(pReqUserLoginField, nRequestID);
}
TRADEAPI_API int		ReqUserLogout(CThostFtdcTraderApi* pApi, CThostFtdcUserLogoutField* pUserLogout, int nRequestID)
{
	return pApi->ReqUserLogout(pUserLogout, nRequestID);
}

////�����û���¼����
//TRADEAPI_API int ReqUserLogin(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcUserIDType userID,
//	TThostFtdcPasswordType password, TThostFtdcPasswordType oneTimePassword, TThostFtdcMacAddressType macAddress, TThostFtdcProductInfoType productInfo,
//	TThostFtdcProductInfoType interfaceInfo, TThostFtdcProtocolInfoType	protocolInfo)
//{
//	if (pApi == NULL) return -1;
//
//	CThostFtdcReqUserLoginField req;
//	memset(&req, 0, sizeof(req));
//	strcpy_s(req.BrokerID, brokerID);
//	strcpy_s(req.UserID, userID);
//	strcpy_s(req.Password, password);
//	if (oneTimePassword != NULL) strcpy_s(req.OneTimePassword, oneTimePassword);
//	if (macAddress != NULL) strcpy_s(req.MacAddress, macAddress);
//	if (productInfo != NULL) strcpy_s(req.UserProductInfo, productInfo);
//	if (interfaceInfo != NULL) strcpy_s(req.InterfaceProductInfo, interfaceInfo);
//	if (protocolInfo != NULL) strcpy_s(req.ProtocolInfo, protocolInfo);
//
//	return pApi->ReqUserLogin(&req, requestID);
//}
////���͵ǳ�����
//TRADEAPI_API int ReqUserLogout(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcUserIDType investorID)
//{
//	if (pApi == NULL) return -1;
//
//	CThostFtdcUserLogoutField req;
//	memset(&req, 0, sizeof(req));
//	strcpy_s(req.BrokerID, brokerID);
//	strcpy_s(req.UserID, investorID);
//	return pApi->ReqUserLogout(&req, requestID);
//}


TRADEAPI_API int		ReqUserPasswordUpdate(CThostFtdcTraderApi* pApi, CThostFtdcUserPasswordUpdateField* pUserPasswordUpdate, int nRequestID)
{
	return pApi->ReqUserPasswordUpdate(pUserPasswordUpdate, nRequestID);
}

///�ʽ��˻������������
TRADEAPI_API int		ReqTradingAccountPasswordUpdate(CThostFtdcTraderApi* pApi, CThostFtdcTradingAccountPasswordUpdateField* pTradingAccountPasswordUpdate, int nRequestID)
{
	return pApi->ReqTradingAccountPasswordUpdate(pTradingAccountPasswordUpdate, nRequestID);
}

///��ѯ�û���ǰ֧�ֵ���֤ģʽ���ù����ݲ�֧�֣�
TRADEAPI_API int		ReqUserAuthMethod(CThostFtdcTraderApi* pApi, CThostFtdcReqUserAuthMethodField* pReqUserAuthMethod, int nRequestID)
{
	return pApi->ReqUserAuthMethod(pReqUserAuthMethod, nRequestID);
}

///�û�������ȡͼ����֤�����󣨸ù����ݲ�֧�֣�
TRADEAPI_API int		ReqGenUserCaptcha(CThostFtdcTraderApi* pApi, CThostFtdcReqGenUserCaptchaField* pReqGenUserCaptcha, int	nRequestID)
{
	return pApi->ReqGenUserCaptcha(pReqGenUserCaptcha, nRequestID);
}

///�û�������ȡ������֤�����󣨸ù����ݲ�֧�֣�
TRADEAPI_API int		ReqGenUserText(CThostFtdcTraderApi* pApi, CThostFtdcReqGenUserTextField* pReqGenUserText, int nRequestID)
{
	return pApi->ReqGenUserText(pReqGenUserText, nRequestID);
}

///�û���������ͼƬ��֤��ĵ�½���󣨸ù����ݲ�֧�֣�
TRADEAPI_API int		ReqUserLoginWithCaptcha(CThostFtdcTraderApi* pApi, CThostFtdcReqUserLoginWithCaptchaField* pReqUserLoginWithCaptcha, int nRequestID)
{
	return pApi->ReqUserLoginWithCaptcha(pReqUserLoginWithCaptcha, nRequestID);
}

///�û��������ж�����֤��ĵ�½���󣨸ù����ݲ�֧�֣�
TRADEAPI_API int		ReqUserLoginWithText(CThostFtdcTraderApi* pApi, CThostFtdcReqUserLoginWithTextField* pReqUserLoginWithText, int	nRequestID)
{
	return pApi->ReqUserLoginWithText(pReqUserLoginWithText, nRequestID);
}


///�û��������ж�̬����ĵ�½���󣨸ù����ݲ�֧�֣�
TRADEAPI_API int		ReqUserLoginWithOTP(CThostFtdcTraderApi* pApi, CThostFtdcReqUserLoginWithOTPField* pReqUserLoginWithOTP, int nRequestID)
{
	return pApi->ReqUserLoginWithOTP(pReqUserLoginWithOTP, nRequestID);
}


//
////�����û�����
//TRADEAPI_API int ReqUserPasswordUpdate(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcUserIDType userID,
//	TThostFtdcUserIDType oldPassword, TThostFtdcPasswordType newPassword)
//{
//	if (pApi == NULL) return -1;
//
//	CThostFtdcUserPasswordUpdateField req;
//	memset(&req, 0, sizeof(req));
//	strcpy_s(req.BrokerID, brokerID);
//	strcpy_s(req.UserID, userID);
//	strcpy_s(req.OldPassword, oldPassword);
//	strcpy_s(req.NewPassword, newPassword);
//	return pApi->ReqUserPasswordUpdate(&req, requestID);
//}
////�ʽ��˻������������
//TRADEAPI_API int ReqTradingAccountPasswordUpdate(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcBrokerIDType brokerID,
//	TThostFtdcAccountIDType accountID, TThostFtdcUserIDType oldPassword, TThostFtdcPasswordType newPassword)
//{
//	if (pApi == NULL) return -1;
//
//	CThostFtdcTradingAccountPasswordUpdateField req;
//	memset(&req, 0, sizeof(req));
//	strcpy_s(req.BrokerID, brokerID);
//	strcpy_s(req.AccountID, accountID);
//	strcpy_s(req.NewPassword, newPassword);
//	strcpy_s(req.OldPassword, oldPassword);
//	return pApi->ReqTradingAccountPasswordUpdate(&req, requestID);
//}
//��ȫ��¼����
TRADEAPI_API int ReqUserSafeLogin(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcUserIDType userID,
								  TThostFtdcPasswordType password, TThostFtdcPasswordType oneTimePassword, TThostFtdcMacAddressType macAddress, TThostFtdcProductInfoType productInfo,
								  TThostFtdcProductInfoType interfaceInfo, TThostFtdcProtocolInfoType	protocolInfo)
{
	if (pApi == NULL) return -1;

	CThostFtdcReqUserLoginField req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID, brokerID);
	strcpy_s(req.UserID, userID);
	strcpy_s(req.Password, password);
	if (oneTimePassword != NULL) strcpy_s(req.OneTimePassword, oneTimePassword);
	if (macAddress != NULL) strcpy_s(req.MacAddress, macAddress);
	if (productInfo != NULL) strcpy_s(req.UserProductInfo, productInfo);
	if (interfaceInfo != NULL) strcpy_s(req.InterfaceProductInfo, interfaceInfo);
	if (protocolInfo != NULL) strcpy_s(req.ProtocolInfo, protocolInfo);

	return pApi->ReqUserLogin(&req, requestID);
}
//��ȫ�����û�����
TRADEAPI_API int ReqUserPasswordSafeUpdate(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcUserIDType userID,
										   TThostFtdcUserIDType oldPassword, TThostFtdcPasswordType newPassword)
{
	if (pApi == NULL) return -1;

	CThostFtdcUserPasswordUpdateField req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID, brokerID);
	strcpy_s(req.UserID, userID);
	strcpy_s(req.OldPassword, oldPassword);
	strcpy_s(req.NewPassword, newPassword);
	return pApi->ReqUserPasswordUpdate(&req, requestID);
}

////��ѯ�û���ǰ֧�ֵ���֤ģʽ
//TRADEAPI_API int ReqUserAuthMethod(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcUserIDType userID, TThostFtdcDateType tradingDay)
//{
//	if (pApi == NULL) return -1;
//
//	CThostFtdcReqUserAuthMethodField req;
//	memset(&req, 0, sizeof(req));
//	strcpy_s(req.BrokerID, brokerID);
//	strcpy_s(req.UserID, userID);
//	strcpy_s(req.TradingDay, tradingDay);
//
//	return pApi->ReqUserAuthMethod(&req, requestID);
//}
////�û�������ȡͼ����֤������
//TRADEAPI_API int ReqGenUserCaptcha(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcUserIDType userID, TThostFtdcDateType tradingDay)
//{
//	if (pApi == NULL) return -1;
//
//	CThostFtdcReqGenUserCaptchaField req;
//	memset(&req, 0, sizeof(req));
//	strcpy_s(req.BrokerID, brokerID);
//	strcpy_s(req.UserID, userID);
//	strcpy_s(req.TradingDay, tradingDay);
//
//	return pApi->ReqGenUserCaptcha(&req, requestID);
//}
////�û�������ȡ������֤������
//TRADEAPI_API int ReqGenUserText(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcUserIDType userID, TThostFtdcDateType tradingDay)
//{
//	if (pApi == NULL) return -1;
//
//	CThostFtdcReqGenUserTextField req;
//	memset(&req, 0, sizeof(req));
//	strcpy_s(req.BrokerID, brokerID);
//	strcpy_s(req.UserID, userID);
//	strcpy_s(req.TradingDay, tradingDay);
//
//	return pApi->ReqGenUserText(&req, requestID);
//}
////�û���������ͼƬ��֤��ĵ�½����
//TRADEAPI_API int ReqUserLoginWithCaptcha(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcReqUserLoginWithCaptchaField *pReqUserLoginWithCaptcha)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqUserLoginWithCaptcha(pReqUserLoginWithCaptcha, requestID);
//}
////�û��������ж�����֤��ĵ�½����
//TRADEAPI_API int ReqUserLoginWithText(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcReqUserLoginWithTextField *pReqUserLoginWithText)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqUserLoginWithText(pReqUserLoginWithText, requestID);
//}
////�û��������ж�̬����ĵ�½����
//TRADEAPI_API int ReqUserLoginWithOTP(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcReqUserLoginWithOTPField *pReqUserLoginWithOTP)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqUserLoginWithOTP(pReqUserLoginWithOTP, requestID);
//}
//����¼������
//TRADEAPI_API int ReqOrderInsert(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcInputOrderField *pOrder)
//{
//	if (pApi == NULL) return -1;
//
//	int siez = sizeof(CThostFtdcInputOrderField);
//	strcpy_s(pOrder->BusinessUnit, "HF");
//	return pApi->ReqOrderInsert(pOrder, requestID);
//}
////������������
//TRADEAPI_API int ReqOrderAction(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcInputOrderActionField *pOrder)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqOrderAction(pOrder, requestID);
//}
////��ѯ��󱨵���������
//TRADEAPI_API int ReqQueryMaxOrderVolume(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcQueryMaxOrderVolumeField *pMaxOrderVolume)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqQueryMaxOrderVolume(pMaxOrderVolume, requestID);
//}
////Ͷ���߽�����ȷ��
//TRADEAPI_API int ReqSettlementInfoConfirm(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcInvestorIDType investorID)
//{
//	
//	if (pApi == NULL) return -1;
//
//	CThostFtdcSettlementInfoConfirmField req;
//	memset(&req, 0, sizeof(req));
//	strcpy_s(req.BrokerID, brokerID);
//	strcpy_s(req.InvestorID, investorID);
//	return pApi->ReqSettlementInfoConfirm(&req, requestID);
//}
////ִ������¼������
//TRADEAPI_API int ReqExecOrderInsert(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcInputExecOrderField *pInputExecOrder)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqExecOrderInsert(pInputExecOrder, requestID);
//}
////ִ�������������
//TRADEAPI_API int ReqExecOrderAction(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcInputExecOrderActionField *pInputExecOrderAction)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqExecOrderAction(pInputExecOrderAction, requestID);
//}
////ѯ��¼������
//TRADEAPI_API int ReqForQuoteInsert(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcInputForQuoteField *pInputForQuote)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqForQuoteInsert(pInputForQuote, requestID);
//}
////����¼������
//TRADEAPI_API int ReqQuoteInsert(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcInputQuoteField *pInputQuote)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqQuoteInsert(pInputQuote, requestID);
//}
////���۲�������
//TRADEAPI_API int ReqQuoteAction(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcInputQuoteActionField *pInputQuoteAction)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqQuoteAction(pInputQuoteAction, requestID);
//}
////����������������
//TRADEAPI_API int ReqBatchOrderAction(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcInputBatchOrderActionField *pInputBatchOrderAction)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqBatchOrderAction(pInputBatchOrderAction, requestID);
//}
////��Ȩ�ԶԳ�¼������
//TRADEAPI_API int ReqOptionSelfCloseInsert(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcInputOptionSelfCloseField *pInputOptionSelfClose)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqOptionSelfCloseInsert(pInputOptionSelfClose, requestID);
//}
////��Ȩ�ԶԳ��������
//TRADEAPI_API int ReqOptionSelfCloseAction(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcInputOptionSelfCloseActionField *pInputOptionSelfCloseAction)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqOptionSelfCloseAction(pInputOptionSelfCloseAction, requestID);
//}
////�������¼������
//TRADEAPI_API int ReqCombActionInsert(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcInputCombActionField *pInputCombAction)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqCombActionInsert(pInputCombAction, requestID);
//}
////�����ѯ����
//TRADEAPI_API int ReqQryOrder(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcQryOrderField *pQryOrder)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqQryOrder(pQryOrder, requestID);
//}
////�����ѯ�ɽ�
//TRADEAPI_API int ReqQryTrade(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcQryTradeField *pQryTrade)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqQryTrade(pQryTrade, requestID);
//}
////�����ѯͶ���ֲ߳�
//TRADEAPI_API int ReqQryInvestorPosition(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcInvestorIDType investorID, TThostFtdcInstrumentIDType instrumentID)
//{
//	if (pApi == NULL) return -1;
//
//	CThostFtdcQryInvestorPositionField req;
//	memset(&req, 0, sizeof(req));
//	strcpy_s(req.BrokerID, brokerID);
//	strcpy_s(req.InvestorID, investorID);
//	if (instrumentID != NULL)
//		strcpy_s(req.InstrumentID, instrumentID);
//	return pApi->ReqQryInvestorPosition(&req, requestID);
//}
////�����ѯ�ʽ��˻�
//TRADEAPI_API int ReqQryTradingAccount(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcInvestorIDType investorID)
//{
//	if (pApi == NULL) return -1;
//
//	CThostFtdcQryTradingAccountField req;
//	memset(&req, 0, sizeof(req));
//	strcpy_s(req.BrokerID, brokerID);
//	strcpy_s(req.InvestorID, investorID);
//	return pApi->ReqQryTradingAccount(&req, requestID);
//}
////�����ѯͶ����
//TRADEAPI_API int ReqQryInvestor(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcInvestorIDType investorID)
//{
//	if (pApi == NULL) return -1;
//
//	CThostFtdcQryInvestorField req;
//	memset(&req, 0, sizeof(req));
//	strcpy_s(req.BrokerID, brokerID);
//	strcpy_s(req.InvestorID, investorID);
//	return pApi->ReqQryInvestor(&req, requestID);
//}
////�����ѯ���ױ���
//TRADEAPI_API int ReqQryTradingCode(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcInvestorIDType investorID, TThostFtdcClientIDType clientID, TThostFtdcExchangeIDType	exchangeID)
//{
//	if (pApi == NULL) return -1;
//
//	CThostFtdcQryTradingCodeField req;
//	memset(&req, 0, sizeof(req));
//	strcpy_s(req.BrokerID, brokerID);
//	strcpy_s(req.InvestorID, investorID);
//	if (clientID != NULL)
//		strcpy_s(req.ClientID, clientID);
//	if (exchangeID != NULL)
//		strcpy_s(req.ExchangeID, exchangeID);
//	return pApi->ReqQryTradingCode(&req, requestID);
//}
////�����ѯ��Լ��֤����
//TRADEAPI_API int ReqQryInstrumentMarginRate(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcInvestorIDType investorID, TThostFtdcInstrumentIDType instrumentID, TThostFtdcHedgeFlagType	hedgeFlag)
//{
//	if (pApi == NULL) return -1;
//
//	CThostFtdcQryInstrumentMarginRateField req;
//	memset(&req, 0, sizeof(req));
//	strcpy_s(req.BrokerID, brokerID);
//	strcpy_s(req.InvestorID, investorID);
//	if (instrumentID != NULL)
//		strcpy_s(req.InstrumentID, instrumentID);
//	if (hedgeFlag != NULL)
//		req.HedgeFlag = hedgeFlag;						//*��*�ܲ���null�������в�ѯ
//	return pApi->ReqQryInstrumentMarginRate(&req, requestID);
//}
////�����ѯ��Լ��������
//TRADEAPI_API int ReqQryInstrumentCommissionRate(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcInvestorIDType investorID, TThostFtdcInstrumentIDType instrumentID)
//{
//	if (pApi == NULL) return -1;
//
//	CThostFtdcQryInstrumentCommissionRateField  req;
//	memset(&req, 0, sizeof(req));
//	strcpy_s(req.BrokerID, brokerID);
//	strcpy_s(req.InvestorID, investorID);
//	if (instrumentID != NULL)
//		strcpy_s(req.InstrumentID, instrumentID);
//	return pApi->ReqQryInstrumentCommissionRate(&req, requestID);
//}
////�����ѯ������
//TRADEAPI_API int ReqQryExchange(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcExchangeIDType exchangeID)
//{
//	if (pApi == NULL) return -1;
//
//	CThostFtdcQryExchangeField  req;
//	memset(&req, 0, sizeof(req));
//	strcpy_s(req.ExchangeID, exchangeID);
//	return pApi->ReqQryExchange(&req, requestID);
//}
////�����ѯ��Լ
//TRADEAPI_API int ReqQryInstrument(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcInstrumentIDType instrumentID)
//{
//	if (pApi == NULL) return -1;
//
//	CThostFtdcQryInstrumentField req;
//	memset(&req, 0, sizeof(req));
//	if (instrumentID != NULL)
//		strcpy_s(req.InstrumentID, instrumentID);
//	return pApi->ReqQryInstrument(&req, requestID);
//}
////�����ѯ����
//TRADEAPI_API int ReqQryDepthMarketData(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcInstrumentIDType instrumentID)
//{
//	if (pApi == NULL) return -1;
//
//	CThostFtdcQryDepthMarketDataField req;
//	memset(&req, 0, sizeof(req));
//	if (instrumentID != NULL)
//		strcpy_s(req.InstrumentID, instrumentID);
//	return pApi->ReqQryDepthMarketData(&req, requestID);
//}
////�����ѯͶ���߽�����
//TRADEAPI_API int ReqQrySettlementInfo(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcInvestorIDType investorID, TThostFtdcDateType	tradingDay)
//{
//	if (pApi == NULL) return -1;
//
//	CThostFtdcQrySettlementInfoField req;
//	memset(&req, 0, sizeof(req));
//	strcpy_s(req.BrokerID, brokerID);
//	strcpy_s(req.InvestorID, investorID);
//	if (tradingDay != NULL)
//		strcpy_s(req.TradingDay, tradingDay);
//	return pApi->ReqQrySettlementInfo(&req, requestID);
//}
////��ѯ�ֲ���ϸ
//TRADEAPI_API int ReqQryInvestorPositionDetail(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcInvestorIDType investorID, TThostFtdcInstrumentIDType instrumentID)
//{
//	if (pApi == NULL) return -1;
//
//	CThostFtdcQryInvestorPositionDetailField req;
//	memset(&req, 0, sizeof(req));
//	strcpy_s(req.BrokerID, brokerID);
//	strcpy_s(req.InvestorID, investorID);
//	if (instrumentID != NULL)
//		strcpy_s(req.InstrumentID, instrumentID);
//	return pApi->ReqQryInvestorPositionDetail(&req, requestID);
//}
////�����ѯ�ͻ�֪ͨ
//TRADEAPI_API int ReqQryNotice(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcBrokerIDType brokerID)
//{
//	if (pApi == NULL) return -1;
//
//	CThostFtdcQryNoticeField  req;
//	memset(&req, 0, sizeof(req));
//	strcpy_s(req.BrokerID, brokerID);
//	return pApi->ReqQryNotice(&req, requestID);
//}
////�����ѯ������Ϣȷ��
//TRADEAPI_API int ReqQrySettlementInfoConfirm(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcInvestorIDType investorID)
//{
//	if (pApi == NULL) return -1;
//
//	CThostFtdcQrySettlementInfoConfirmField  req;
//	memset(&req, 0, sizeof(req));
//	strcpy_s(req.BrokerID, brokerID);
//	strcpy_s(req.InvestorID, investorID);
//	return pApi->ReqQrySettlementInfoConfirm(&req, requestID);
//}
////�����ѯ**���**�ֲ���ϸ
//TRADEAPI_API int ReqQryInvestorPositionCombineDetail(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcInvestorIDType investorID, TThostFtdcInstrumentIDType instrumentID)
//{
//	if (pApi == NULL) return -1;
//
//	CThostFtdcQryInvestorPositionCombineDetailField req;
//	memset(&req, 0, sizeof(req));
//	strcpy_s(req.BrokerID, brokerID);
//	strcpy_s(req.InvestorID, investorID);
//	if (instrumentID != NULL)
//		strcpy_s(req.CombInstrumentID, instrumentID);
//	return pApi->ReqQryInvestorPositionCombineDetail(&req, requestID);
//}
////�����ѯ��֤����ϵͳ���͹�˾�ʽ��˻���Կ
//TRADEAPI_API int ReqQryCFMMCTradingAccountKey(CThostFtdcTraderApi* pApi, CThostFtdcQryCFMMCTradingAccountKeyField* key, int nRequestID)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqQryCFMMCTradingAccountKey(key, nRequestID);
//}
////�����ѯ�ֵ��۵���Ϣ
//TRADEAPI_API int ReqQryEWarrantOffset(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcQryEWarrantOffsetField *pQryEWarrantOffset)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqQryEWarrantOffset(pQryEWarrantOffset, requestID);
//}
////�����ѯͶ����Ʒ��/��Ʒ�ֱ�֤��
//TRADEAPI_API int ReqQryInvestorProductGroupMargin(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcQryInvestorProductGroupMarginField *pQryInvestorProductGroupMargin)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqQryInvestorProductGroupMargin(pQryInvestorProductGroupMargin, requestID);
//}
////�����ѯ��������֤����
//TRADEAPI_API int ReqQryExchangeMarginRate(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcInstrumentIDType instrumentID, TThostFtdcHedgeFlagType hedgeFlag)
//{
//	if (pApi == NULL) return -1;
//
//	CThostFtdcQryExchangeMarginRateField req;
//	memset(&req, 0, sizeof(req));
//	strcpy_s(req.BrokerID, brokerID);
//	if (instrumentID != NULL)
//		strcpy_s(req.InstrumentID, instrumentID);
//	req.HedgeFlag = hedgeFlag;
//	return pApi->ReqQryExchangeMarginRate(&req, requestID);
//}
////�����ѯ������������֤����
//TRADEAPI_API int ReqQryExchangeMarginRateAdjust(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcInstrumentIDType instrumentID, TThostFtdcHedgeFlagType hedgeFlag)
//{
//	if (pApi == NULL) return -1;
//
//	CThostFtdcQryExchangeMarginRateAdjustField req;
//	memset(&req, 0, sizeof(req));
//	strcpy_s(req.BrokerID, brokerID);
//	if (instrumentID != NULL)
//		strcpy_s(req.InstrumentID, instrumentID);
//	req.HedgeFlag = hedgeFlag;
//	return pApi->ReqQryExchangeMarginRateAdjust(&req, requestID);
//}
////�����ѯ����
//TRADEAPI_API int ReqQryExchangeRate(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcQryExchangeRateField *pQryExchangeRate)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqQryExchangeRate(pQryExchangeRate, requestID);
//}
////�����ѯ�����������Ա����Ȩ��
//TRADEAPI_API int ReqQrySecAgentACIDMap(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcQrySecAgentACIDMapField *pQrySecAgentACIDMap)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqQrySecAgentACIDMap(pQrySecAgentACIDMap, requestID);
//}
////�����ѯ��Ʒ���ۻ���
//TRADEAPI_API int ReqQryProductExchRate(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcInstrumentIDType productID)
//{
//	if (pApi == NULL) return -1;
//
//	CThostFtdcQryProductExchRateField req;
//	memset(&req, 0, sizeof(req));
//	strcpy_s(req.ProductID, productID);
//	return pApi->ReqQryProductExchRate(&req, requestID);
//}
////�����ѯ��Ʒ��
//TRADEAPI_API int ReqQryProductGroup(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcInstrumentIDType productID, TThostFtdcExchangeIDType exchangeID)
//{
//	if (pApi == NULL) return -1;
//
//	CThostFtdcQryProductGroupField req;
//	memset(&req, 0, sizeof(req));
//	strcpy_s(req.ProductID, productID);
//	strcpy_s(req.ExchangeID, exchangeID);
//	return pApi->ReqQryProductGroup(&req, requestID);
//}
////�����ѯ�����̺�Լ��������
//TRADEAPI_API int ReqQryMMInstrumentCommissionRate(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcInvestorIDType investorID, TThostFtdcInstrumentIDType instrumentID)
//{
//	if (pApi == NULL) return -1;
//
//	CThostFtdcQryMMInstrumentCommissionRateField req;
//	memset(&req, 0, sizeof(req));
//	strcpy_s(req.BrokerID, brokerID);
//	strcpy_s(req.InvestorID, investorID);
//	if (instrumentID != NULL)
//		strcpy_s(req.InstrumentID, instrumentID);
//	return pApi->ReqQryMMInstrumentCommissionRate(&req, requestID);
//}
////�����ѯ��������Ȩ��Լ������
//TRADEAPI_API int ReqQryMMOptionInstrCommRate(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcInvestorIDType investorID, TThostFtdcInstrumentIDType instrumentID)
//{
//	if (pApi == NULL) return -1;
//
//	CThostFtdcQryMMOptionInstrCommRateField req;
//	memset(&req, 0, sizeof(req));
//	strcpy_s(req.BrokerID, brokerID);
//	strcpy_s(req.InvestorID, investorID);
//	if (instrumentID != NULL)
//		strcpy_s(req.InstrumentID, instrumentID);
//	return pApi->ReqQryMMOptionInstrCommRate(&req, requestID);
//}
////�����ѯ����������
//TRADEAPI_API int ReqQryInstrumentOrderCommRate(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcInvestorIDType investorID, TThostFtdcInstrumentIDType instrumentID)
//{
//	if (pApi == NULL) return -1;
//
//	CThostFtdcQryInstrumentOrderCommRateField req;
//	memset(&req, 0, sizeof(req));
//	strcpy_s(req.BrokerID, brokerID);
//	strcpy_s(req.InvestorID, investorID);
//	if (instrumentID != NULL)
//		strcpy_s(req.InstrumentID, instrumentID);
//	return pApi->ReqQryInstrumentOrderCommRate(&req, requestID);
//}
////�����ѯ�ʽ��˻�
//TRADEAPI_API int ReqQrySecAgentTradingAccount(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcQryTradingAccountField *pQryTradingAccount)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqQrySecAgentTradingAccount(pQryTradingAccount, requestID);
//}
////�����ѯ�����������ʽ�У��ģʽ
//TRADEAPI_API int ReqQrySecAgentCheckMode(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcQrySecAgentCheckModeField *pQrySecAgentCheckMode)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqQrySecAgentCheckMode(pQrySecAgentCheckMode, requestID);
//}
////�����ѯ��Ȩ���׳ɱ�
//TRADEAPI_API int ReqQryOptionInstrTradeCost(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcQryOptionInstrTradeCostField *pQryOptionInstrTradeCost)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqQryOptionInstrTradeCost(pQryOptionInstrTradeCost, requestID);
//}
////�����ѯ��Ȩ��Լ������
//TRADEAPI_API int ReqQryOptionInstrCommRate(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcInvestorIDType investorID, TThostFtdcInstrumentIDType instrumentID)
//{
//	if (pApi == NULL) return -1;
//
//	CThostFtdcQryOptionInstrCommRateField req;
//	memset(&req, 0, sizeof(req));
//	strcpy_s(req.BrokerID, brokerID);
//	strcpy_s(req.InvestorID, investorID);
//	if (instrumentID != NULL)
//		strcpy_s(req.InstrumentID, instrumentID);
//	return pApi->ReqQryOptionInstrCommRate(&req, requestID);
//}
////�����ѯִ������
//TRADEAPI_API int ReqQryExecOrder(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcQryExecOrderField *pQryExecOrder)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqQryExecOrder(pQryExecOrder, requestID);
//}
////�����ѯѯ��
//TRADEAPI_API int ReqQryForQuote(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcQryForQuoteField *pQryForQuote)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqQryForQuote(pQryForQuote, requestID);
//}
////�����ѯ����
//TRADEAPI_API int ReqQryQuote(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcQryQuoteField *pQryQuote)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqQryQuote(pQryQuote, requestID);
//}
////�����ѯ��Ȩ�ԶԳ�
//TRADEAPI_API int ReqQryOptionSelfClose(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcQryOptionSelfCloseField *pQryOptionSelfClose)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqQryOptionSelfClose(pQryOptionSelfClose, requestID);
//}
////�����ѯͶ�ʵ�Ԫ
//TRADEAPI_API int ReqQryInvestUnit(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcQryInvestUnitField *pQryInvestUnit)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqQryInvestUnit(pQryInvestUnit, requestID);
//}
////�����ѯ��Ϻ�Լ��ȫϵ��
//TRADEAPI_API int ReqQryCombInstrumentGuard(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcQryCombInstrumentGuardField *pQryCombInstrumentGuard)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqQryCombInstrumentGuard(pQryCombInstrumentGuard, requestID);
//}
////�����ѯ�������
//TRADEAPI_API int ReqQryCombAction(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcQryCombActionField *pQryCombAction)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqQryCombAction(pQryCombAction, requestID);
//}
////�����ѯ����֪ͨ
//TRADEAPI_API int ReqQryTradingNotice(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcInvestorIDType investorID)
//{
//	if (pApi == NULL) return -1;
//
//	CThostFtdcQryTradingNoticeField req;
//	memset(&req, 0, sizeof(req));
//	strcpy_s(req.BrokerID, brokerID);
//	strcpy_s(req.InvestorID, investorID);
//	return pApi->ReqQryTradingNotice(&req, requestID);
//}
////�����ѯ���͹�˾���ײ���
//TRADEAPI_API int ReqQryBrokerTradingParams(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcInvestorIDType investorID)
//{
//	if (pApi == NULL) return -1;
//
//	CThostFtdcQryBrokerTradingParamsField  req;
//	memset(&req, 0, sizeof(req));
//	strcpy_s(req.BrokerID, brokerID);
//	strcpy_s(req.InvestorID, investorID);
//	return pApi->ReqQryBrokerTradingParams(&req, requestID);
//}
////�����ѯ���͹�˾�����㷨
//TRADEAPI_API int ReqQryBrokerTradingAlgos(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcExchangeIDType exchangeID, TThostFtdcInstrumentIDType instrumentID)
//{
//	if (pApi == NULL) return -1;
//
//	CThostFtdcQryBrokerTradingAlgosField  req;
//	memset(&req, 0, sizeof(req));
//	strcpy_s(req.BrokerID, brokerID);
//	if (exchangeID != NULL)
//		strcpy_s(req.ExchangeID, exchangeID);
//	if (instrumentID != NULL)
//		strcpy_s(req.InstrumentID, instrumentID);
//
//	return pApi->ReqQryBrokerTradingAlgos(&req, requestID);
//}
////Ԥ��¼������
//TRADEAPI_API int ReqParkedOrderInsert(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcParkedOrderField *ParkedOrder)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqParkedOrderInsert(ParkedOrder, requestID);
//}
////Ԥ�񳷵�¼������
//TRADEAPI_API int ReqParkedOrderAction(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcParkedOrderActionField *ParkedOrderAction)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqParkedOrderAction(ParkedOrderAction, requestID);
//}
////����ɾ��Ԥ��
//TRADEAPI_API int ReqRemoveParkedOrder(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcInvestorIDType investorID, TThostFtdcParkedOrderIDType parkedOrderID)
//{
//	if (pApi == NULL) return -1;
//
//	CThostFtdcRemoveParkedOrderField  req;
//	memset(&req, 0, sizeof(req));
//	strcpy_s(req.BrokerID, brokerID);
//	strcpy_s(req.InvestorID, investorID);
//	strcpy_s(req.ParkedOrderID, parkedOrderID);
//	return pApi->ReqRemoveParkedOrder(&req, requestID);
//}
////����ɾ��Ԥ�񳷵�
//TRADEAPI_API int ReqRemoveParkedOrderAction(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcInvestorIDType investorID, TThostFtdcParkedOrderActionIDType parkedOrderActionID)
//{
//	if (pApi == NULL) return -1;
//
//	CThostFtdcRemoveParkedOrderActionField  req;
//	memset(&req, 0, sizeof(req));
//	strcpy_s(req.BrokerID, brokerID);
//	strcpy_s(req.InvestorID, investorID);
//	strcpy_s(req.ParkedOrderActionID, parkedOrderActionID);
//	return pApi->ReqRemoveParkedOrderAction(&req, requestID);
//}
//
////�����ѯת������
//TRADEAPI_API int ReqQryTransferBank(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcBankIDType bankID, TThostFtdcBankBrchIDType bankBrchID)
//{
//	if (pApi == NULL) return -1;
//
//	CThostFtdcQryTransferBankField  req;
//	memset(&req, 0, sizeof(req));
//	strcpy_s(req.BankID, bankID);
//	strcpy_s(req.BankBrchID, bankBrchID);
//	return pApi->ReqQryTransferBank(&req, requestID);
//}
////�����ѯת����ˮ
//TRADEAPI_API int ReqQryTransferSerial(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcAccountIDType accountID, TThostFtdcBankIDType bankID)
//{
//	if (pApi == NULL) return -1;
//
//	CThostFtdcQryTransferSerialField  req;
//	memset(&req, 0, sizeof(req));
//	strcpy_s(req.BrokerID, brokerID);
//	strcpy_s(req.AccountID, accountID);
//	strcpy_s(req.BankID, bankID);
//	return pApi->ReqQryTransferSerial(&req, requestID);
//}
////�����ѯ����ǩԼ��ϵ
//TRADEAPI_API int ReqQryAccountregister(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcAccountIDType accountID, TThostFtdcBankIDType bankID)
//{
//	if (pApi == NULL) return -1;
//
//	CThostFtdcQryAccountregisterField  req;
//	memset(&req, 0, sizeof(req));
//	strcpy_s(req.BrokerID, brokerID);
//	strcpy_s(req.AccountID, accountID);
//	strcpy_s(req.BankID, bankID);
//	return pApi->ReqQryAccountregister(&req, requestID);
//}
////�����ѯǩԼ����
//TRADEAPI_API int ReqQryContractBank(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcBankIDType bankID, TThostFtdcBankBrchIDType bankBrchID)
//{
//	if (pApi == NULL) return -1;
//
//	CThostFtdcQryContractBankField  req;
//	memset(&req, 0, sizeof(req));
//	strcpy_s(req.BrokerID, brokerID);
//	if (bankID != NULL)
//		strcpy_s(req.BankID, bankID);
//	if (bankBrchID != NULL)
//		strcpy_s(req.BankBrchID, bankBrchID);
//	return pApi->ReqQryContractBank(&req, requestID);
//}
////�����ѯԤ��
//TRADEAPI_API int ReqQryParkedOrder(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcInvestorIDType investorID, TThostFtdcInstrumentIDType instrumentID, TThostFtdcExchangeIDType exchangeID)
//{
//	if (pApi == NULL) return -1;
//
//	CThostFtdcQryParkedOrderField  req;
//	memset(&req, 0, sizeof(req));
//	strcpy_s(req.BrokerID, brokerID);
//	strcpy_s(req.InvestorID, investorID);
//	if (instrumentID != NULL)
//		strcpy_s(req.InstrumentID, instrumentID);
//	if (exchangeID != NULL)
//		strcpy_s(req.ExchangeID, exchangeID);
//	return pApi->ReqQryParkedOrder(&req, requestID);
//}
////�����ѯԤ�񳷵�
//TRADEAPI_API int ReqQryParkedOrderAction(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcInvestorIDType investorID, TThostFtdcInstrumentIDType instrumentID, TThostFtdcExchangeIDType exchangeID)
//{
//	if (pApi == NULL) return -1;
//
//	CThostFtdcQryParkedOrderActionField  req;
//	memset(&req, 0, sizeof(req));
//	strcpy_s(req.BrokerID, brokerID);
//	strcpy_s(req.InvestorID, investorID);
//	if (instrumentID != NULL)
//		strcpy_s(req.InstrumentID, instrumentID);
//	if (exchangeID != NULL)
//		strcpy_s(req.ExchangeID, exchangeID);
//	return pApi->ReqQryParkedOrderAction(&req, requestID);
//}
////�����ѯ��������û�����
//TRADEAPI_API int ReqQueryCFMMCTradingAccountToken(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcInvestorIDType investorID)
//{
//	if (pApi == NULL) return -1;
//
//	CThostFtdcQueryCFMMCTradingAccountTokenField req;
//	memset(&req, 0, sizeof(req));
//	strcpy_s(req.BrokerID, brokerID);
//	strcpy_s(req.InvestorID, investorID);
//	return pApi->ReqQueryCFMMCTradingAccountToken(&req, requestID);
//}
////�ڻ����������ʽ�ת�ڻ�����
//TRADEAPI_API int ReqFromBankToFutureByFuture(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcReqTransferField *reqTransfer)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqFromBankToFutureByFuture(reqTransfer, requestID);
//}
////�ڻ������ڻ��ʽ�ת��������
//TRADEAPI_API int ReqFromFutureToBankByFuture(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcReqTransferField *reqTransfer)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqFromFutureToBankByFuture(reqTransfer, requestID);
//}
////�ڻ������ѯ�����������
//TRADEAPI_API int ReqQueryBankAccountMoneyByFuture(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcReqQueryAccountField *reqQueryAccount)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqQueryBankAccountMoneyByFuture(reqQueryAccount, requestID);
//}
TRADEAPI_API int		ReqOrderInsert(CThostFtdcTraderApi* pApi, CThostFtdcInputOrderField* pInputOrder, int nRequestID)
{
	return pApi->ReqOrderInsert(pInputOrder, nRequestID);
}
///�����ѯ����
TRADEAPI_API int		ReqQryOrder(CThostFtdcTraderApi* pApi, CThostFtdcQryOrderField* pQryOrder, int nRequestID)
{
	return pApi->ReqQryOrder(pQryOrder, nRequestID);
}
///��ѯ��󱨵���������
TRADEAPI_API int		ReqQueryMaxOrderVolume(CThostFtdcTraderApi* pApi, CThostFtdcQueryMaxOrderVolumeField* pQueryMaxOrderVolume, int nRequestID)
{
	return pApi->ReqQueryMaxOrderVolume(pQueryMaxOrderVolume, nRequestID);
}
///������������
TRADEAPI_API int		ReqOrderAction(CThostFtdcTraderApi* pApi, CThostFtdcInputOrderActionField* pInputOrderAction, int nRequestID)
{
	return pApi->ReqOrderAction(pInputOrderAction, nRequestID);
}
///����������������
TRADEAPI_API int		ReqBatchOrderAction(CThostFtdcTraderApi* pApi, CThostFtdcInputBatchOrderActionField* pInputBatchOrderAction, int nRequestID)
{
	return pApi->ReqBatchOrderAction(pInputBatchOrderAction, nRequestID);
}

///Ԥ��¼������
TRADEAPI_API int		ReqParkedOrderInsert(CThostFtdcTraderApi* pApi, CThostFtdcParkedOrderField* pParkedOrder, int nRequestID)
{
	return pApi->ReqParkedOrderInsert(pParkedOrder, nRequestID);
}
///Ԥ�񳷵�¼������
TRADEAPI_API int		ReqParkedOrderAction(CThostFtdcTraderApi* pApi, CThostFtdcParkedOrderActionField* pParkedOrderAction, int nRequestID)
{
	return pApi->ReqParkedOrderAction(pParkedOrderAction, nRequestID);
}
///����ɾ��Ԥ��
TRADEAPI_API int		ReqRemoveParkedOrder(CThostFtdcTraderApi* pApi, CThostFtdcRemoveParkedOrderField* pRemoveParkedOrder, int nRequestID)
{
	return pApi->ReqRemoveParkedOrder(pRemoveParkedOrder, nRequestID);
}
///����ɾ��Ԥ�񳷵�
TRADEAPI_API int		ReqRemoveParkedOrderAction(CThostFtdcTraderApi* pApi, CThostFtdcRemoveParkedOrderActionField* pRemoveParkedOrderAction, int nRequestID)
{
	return pApi->ReqRemoveParkedOrderAction(pRemoveParkedOrderAction, nRequestID);
}
///�����ѯԤ��
TRADEAPI_API int		ReqQryParkedOrder(CThostFtdcTraderApi* pApi, CThostFtdcQryParkedOrderField* pQryParkedOrder, int nRequestID)
{
	return pApi->ReqQryParkedOrder(pQryParkedOrder, nRequestID);
}
///�����ѯԤ�񳷵�
TRADEAPI_API int		ReqQryParkedOrderAction(CThostFtdcTraderApi* pApi, CThostFtdcQryParkedOrderActionField* pQryParkedOrderAction, int nRequestID)
{
	return pApi->ReqQryParkedOrderAction(pQryParkedOrderAction, nRequestID);
}

///�����ѯ�ͻ�֪ͨ
TRADEAPI_API int		ReqQryNotice(CThostFtdcTraderApi* pApi, CThostFtdcQryNoticeField* pQryNotice, int nRequestID)
{
	return pApi->ReqQryNotice(pQryNotice, nRequestID);
}
///�����ѯ����֪ͨ
TRADEAPI_API int		ReqQryTradingNotice(CThostFtdcTraderApi* pApi, CThostFtdcQryTradingNoticeField* pQryTradingNotice, int nRequestID)
{
	return pApi->ReqQryTradingNotice(pQryTradingNotice, nRequestID);
}


///�����ѯִ������
TRADEAPI_API int		ReqQryExecOrder(CThostFtdcTraderApi* pApi, CThostFtdcQryExecOrderField* pQryExecOrder, int nRequestID)
{
	return pApi->ReqQryExecOrder(pQryExecOrder, nRequestID);
}
///ִ������¼������
TRADEAPI_API int		ReqExecOrderInsert(CThostFtdcTraderApi* pApi, CThostFtdcInputExecOrderField* pInputExecOrder, int nRequestID)
{
	return pApi->ReqExecOrderInsert(pInputExecOrder, nRequestID);
}
///ִ�������������
TRADEAPI_API int		ReqExecOrderAction(CThostFtdcTraderApi* pApi, CThostFtdcInputExecOrderActionField* pInputExecOrderAction, int nRequestID)
{
	return pApi->ReqExecOrderAction(pInputExecOrderAction, nRequestID);
}


///ѯ��¼������
TRADEAPI_API int		ReqForQuoteInsert(CThostFtdcTraderApi* pApi, CThostFtdcInputForQuoteField* pInputForQuote, int nRequestID)
{
	return pApi->ReqForQuoteInsert(pInputForQuote, nRequestID);

}
///����¼������
TRADEAPI_API int		ReqQuoteInsert(CThostFtdcTraderApi* pApi, CThostFtdcInputQuoteField* pInputQuote, int nRequestID)
{
	return pApi->ReqQuoteInsert(pInputQuote, nRequestID);
}
///���۲�������
TRADEAPI_API int		ReqQuoteAction(CThostFtdcTraderApi* pApi, CThostFtdcInputQuoteActionField* pInputQuoteAction, int nRequestID)
{
	return pApi->ReqQuoteAction(pInputQuoteAction, nRequestID);
}



///�������¼������
TRADEAPI_API int		ReqCombActionInsert(CThostFtdcTraderApi* pApi, CThostFtdcInputCombActionField* pInputCombAction, int nRequestID)
{
	return pApi->ReqCombActionInsert(pInputCombAction, nRequestID);
}
///�����ѯ��Ϻ�Լ��ȫϵ��
TRADEAPI_API int		ReqQryCombInstrumentGuard(CThostFtdcTraderApi* pApi, CThostFtdcQryCombInstrumentGuardField* pQryCombInstrumentGuard, int nRequestID)
{
	return pApi->ReqQryCombInstrumentGuard(pQryCombInstrumentGuard, nRequestID);
}
///�����ѯ�������
TRADEAPI_API int		ReqQryCombAction(CThostFtdcTraderApi* pApi, CThostFtdcQryCombActionField* pQryCombAction, int nRequestID)
{
	return pApi->ReqQryCombAction(pQryCombAction, nRequestID);
}


///�����ѯ�ɽ�
TRADEAPI_API int		ReqQryTrade(CThostFtdcTraderApi* pApi, CThostFtdcQryTradeField* pQryTrade, int nRequestID)
{
	return pApi->ReqQryTrade(pQryTrade, nRequestID);
}


///�����ѯͶ���ֲ߳�
TRADEAPI_API int		ReqQryInvestorPosition(CThostFtdcTraderApi* pApi, CThostFtdcQryInvestorPositionField* pQryInvestorPosition, int nRequestID)
{
	return pApi->ReqQryInvestorPosition(pQryInvestorPosition, nRequestID);
}
///�����ѯͶ���ֲ߳���ϸ
TRADEAPI_API int		ReqQryInvestorPositionDetail(CThostFtdcTraderApi* pApi, CThostFtdcQryInvestorPositionDetailField* pQryInvestorPositionDetail, int nRequestID)
{
	return pApi->ReqQryInvestorPositionDetail(pQryInvestorPositionDetail, nRequestID);
}
///�����ѯͶ���ֲ߳���ϸ
TRADEAPI_API int		ReqQryInvestorPositionCombineDetail(CThostFtdcTraderApi* pApi, CThostFtdcQryInvestorPositionCombineDetailField* pQryInvestorPositionCombineDetail, int nRequestID)
{
	return pApi->ReqQryInvestorPositionCombineDetail(pQryInvestorPositionCombineDetail, nRequestID);
}
///�����ѯ�ʽ��˻�
TRADEAPI_API int		ReqQryTradingAccount(CThostFtdcTraderApi* pApi, CThostFtdcQryTradingAccountField* pQryTradingAccount, int nRequestID)
{
	return pApi->ReqQryTradingAccount(pQryTradingAccount, nRequestID);
}
///�����ѯͶ����
TRADEAPI_API int		ReqQryInvestor(CThostFtdcTraderApi* pApi, CThostFtdcQryInvestorField* pQryInvestor, int nRequestID)
{
	return pApi->ReqQryInvestor(pQryInvestor, nRequestID);
}
///�����ѯ���ױ���
TRADEAPI_API int		ReqQryTradingCode(CThostFtdcTraderApi* pApi, CThostFtdcQryTradingCodeField* pQryTradingCode, int nRequestID)
{
	return pApi->ReqQryTradingCode(pQryTradingCode, nRequestID);
}
///�����ѯͶ���߽�����
TRADEAPI_API int		ReqQrySettlementInfo(CThostFtdcTraderApi* pApi, CThostFtdcQrySettlementInfoField* pQrySettlementInfo, int nRequestID)
{
	return pApi->ReqQrySettlementInfo(pQrySettlementInfo, nRequestID);
}
///�����ѯ������Ϣȷ��
TRADEAPI_API int		ReqQrySettlementInfoConfirm(CThostFtdcTraderApi* pApi, CThostFtdcQrySettlementInfoConfirmField* pQrySettlementInfoConfirm, int nRequestID)
{
	return pApi->ReqQrySettlementInfoConfirm(pQrySettlementInfoConfirm, nRequestID);
}
///Ͷ���߽�����ȷ��
TRADEAPI_API int		ReqSettlementInfoConfirm(CThostFtdcTraderApi* pApi, CThostFtdcSettlementInfoConfirmField* pSettlementInfoConfirm, int nRequestID)
{
	return pApi->ReqSettlementInfoConfirm(pSettlementInfoConfirm, nRequestID);
}


#pragma region ��Ʒ/��Լ/Instrument
///�����ѯ��Ʒ
TRADEAPI_API int		ReqQryProduct(CThostFtdcTraderApi* pApi, CThostFtdcQryProductField* pQryProduct, int nRequestID)
{
	return pApi->ReqQryProduct(pQryProduct, nRequestID);
}
///�����ѯ��Ʒ���ۻ���
TRADEAPI_API int		ReqQryProductExchRate(CThostFtdcTraderApi* pApi, CThostFtdcQryProductExchRateField* pQryProductExchRate, int nRequestID)
{
	return pApi->ReqQryProductExchRate(pQryProductExchRate, nRequestID);
}
///�����ѯ��Ʒ��
TRADEAPI_API int		ReqQryProductGroup(CThostFtdcTraderApi* pApi, CThostFtdcQryProductGroupField* pQryProductGroup, int nRequestID)
{
	return pApi->ReqQryProductGroup(pQryProductGroup, nRequestID);
}

///�����ѯ��Լ
TRADEAPI_API int		ReqQryInstrument(CThostFtdcTraderApi* pApi, CThostFtdcQryInstrumentField* pQryInstrument, int nRequestID)
{
	return pApi->ReqQryInstrument(pQryInstrument, nRequestID);
}
///�����ѯ��Լ��֤����
TRADEAPI_API int		ReqQryInstrumentMarginRate(CThostFtdcTraderApi* pApi, CThostFtdcQryInstrumentMarginRateField* pQryInstrumentMarginRate, int nRequestID)
{
	return pApi->ReqQryInstrumentMarginRate(pQryInstrumentMarginRate, nRequestID);
}
///�����ѯ��Լ��������
TRADEAPI_API int		ReqQryInstrumentCommissionRate(CThostFtdcTraderApi* pApi, CThostFtdcQryInstrumentCommissionRateField* pQryInstrumentCommissionRate, int nRequestID)
{
	return pApi->ReqQryInstrumentCommissionRate(pQryInstrumentCommissionRate, nRequestID);
}
#pragma endregion



///�����ѯѯ��
TRADEAPI_API int		ReqQryForQuote(CThostFtdcTraderApi* pApi, CThostFtdcQryForQuoteField* pQryForQuote, int nRequestID)
{
	return pApi->ReqQryForQuote(pQryForQuote, nRequestID);
}
///�����ѯ����
TRADEAPI_API int		ReqQryQuote(CThostFtdcTraderApi* pApi, CThostFtdcQryQuoteField* pQryQuote, int nRequestID)
{
	return pApi->ReqQryQuote(pQryQuote, nRequestID);
}
///�����ѯ����
TRADEAPI_API int		ReqQryDepthMarketData(CThostFtdcTraderApi* pApi, CThostFtdcQryDepthMarketDataField* pQryDepthMarketData, int nRequestID)
{
	return pApi->ReqQryDepthMarketData(pQryDepthMarketData, nRequestID);
}





///�����ѯ�ֵ��۵���Ϣ
TRADEAPI_API int		ReqQryEWarrantOffset(CThostFtdcTraderApi* pApi, CThostFtdcQryEWarrantOffsetField* pQryEWarrantOffset, int nRequestID)
{
	return pApi->ReqQryEWarrantOffset(pQryEWarrantOffset, nRequestID);
}

///�����ѯͶ����Ʒ��/��Ʒ�ֱ�֤��
TRADEAPI_API int		ReqQryInvestorProductGroupMargin(CThostFtdcTraderApi* pApi, CThostFtdcQryInvestorProductGroupMarginField* pQryInvestorProductGroupMargin, int nRequestID)
{
	return pApi->ReqQryInvestorProductGroupMargin(pQryInvestorProductGroupMargin, nRequestID);
}




///�����ѯ�����̺�Լ��������
TRADEAPI_API int		ReqQryMMInstrumentCommissionRate(CThostFtdcTraderApi* pApi, CThostFtdcQryMMInstrumentCommissionRateField* pQryMMInstrumentCommissionRate, int nRequestID)
{
	return pApi->ReqQryMMInstrumentCommissionRate(pQryMMInstrumentCommissionRate, nRequestID);
}
///�����ѯ��������Ȩ��Լ������
TRADEAPI_API int		ReqQryMMOptionInstrCommRate(CThostFtdcTraderApi* pApi, CThostFtdcQryMMOptionInstrCommRateField* pQryMMOptionInstrCommRate, int nRequestID)
{
	return pApi->ReqQryMMOptionInstrCommRate(pQryMMOptionInstrCommRate, nRequestID);
}

///�����ѯ����������
TRADEAPI_API int		ReqQryInstrumentOrderCommRate(CThostFtdcTraderApi* pApi, CThostFtdcQryInstrumentOrderCommRateField* pQryInstrumentOrderCommRate, int nRequestID)
{
	return pApi->ReqQryInstrumentOrderCommRate(pQryInstrumentOrderCommRate, nRequestID);
}


#pragma region ��������/sec agent
///�����ѯ�ʽ��˻�
TRADEAPI_API int		ReqQrySecAgentTradingAccount(CThostFtdcTraderApi* pApi, CThostFtdcQryTradingAccountField* pQryTradingAccount, int nRequestID)
{
	return pApi->ReqQrySecAgentTradingAccount(pQryTradingAccount, nRequestID);
}
///�����ѯ�����������Ա����Ȩ��
TRADEAPI_API int		ReqQrySecAgentACIDMap(CThostFtdcTraderApi* pApi, CThostFtdcQrySecAgentACIDMapField* pQrySecAgentACIDMap, int nRequestID)
{
	return pApi->ReqQrySecAgentACIDMap(pQrySecAgentACIDMap, nRequestID);
}
///�����ѯ�����������ʽ�У��ģʽ
TRADEAPI_API int		ReqQrySecAgentCheckMode(CThostFtdcTraderApi* pApi, CThostFtdcQrySecAgentCheckModeField* pQrySecAgentCheckMode, int nRequestID)
{
	return pApi->ReqQrySecAgentCheckMode(pQrySecAgentCheckMode, nRequestID);
}
///�����ѯ������������Ϣ
TRADEAPI_API int		ReqQrySecAgentTradeInfo(CThostFtdcTraderApi* pApi, CThostFtdcQrySecAgentTradeInfoField* pQrySecAgentTradeInfo, int nRequestID)
{
	return pApi->ReqQrySecAgentTradeInfo(pQrySecAgentTradeInfo, nRequestID);
}
#pragma endregion


#pragma region ��Ȩoption
///��Ȩ�ԶԳ�¼������
TRADEAPI_API int		ReqOptionSelfCloseInsert(CThostFtdcTraderApi* pApi, CThostFtdcInputOptionSelfCloseField* pInputOptionSelfClose, int nRequestID)
{
	return pApi->ReqOptionSelfCloseInsert(pInputOptionSelfClose, nRequestID);
}
///��Ȩ�ԶԳ��������
TRADEAPI_API int		ReqOptionSelfCloseAction(CThostFtdcTraderApi* pApi, CThostFtdcInputOptionSelfCloseActionField* pInputOptionSelfCloseAction, int nRequestID)
{
	return pApi->ReqOptionSelfCloseAction(pInputOptionSelfCloseAction, nRequestID);
}

///�����ѯ��Ȩ���׳ɱ�
TRADEAPI_API int		ReqQryOptionInstrTradeCost(CThostFtdcTraderApi* pApi, CThostFtdcQryOptionInstrTradeCostField* pQryOptionInstrTradeCost, int nRequestID)
{
	return pApi->ReqQryOptionInstrTradeCost(pQryOptionInstrTradeCost, nRequestID);
}
///�����ѯ��Ȩ��Լ������
TRADEAPI_API int		ReqQryOptionInstrCommRate(CThostFtdcTraderApi* pApi, CThostFtdcQryOptionInstrCommRateField* pQryOptionInstrCommRate, int nRequestID)
{
	return pApi->ReqQryOptionInstrCommRate(pQryOptionInstrCommRate, nRequestID);
}
///�����ѯ��Ȩ�ԶԳ�
TRADEAPI_API int		ReqQryOptionSelfClose(CThostFtdcTraderApi* pApi, CThostFtdcQryOptionSelfCloseField* pQryOptionSelfClose, int nRequestID)
{
	return pApi->ReqQryOptionSelfClose(pQryOptionSelfClose, nRequestID);
}
#pragma endregion




///�����ѯͶ�ʵ�Ԫ���ݲ�֧�ָù��ܣ�
TRADEAPI_API int		ReqQryInvestUnit(CThostFtdcTraderApi* pApi, CThostFtdcQryInvestUnitField* pQryInvestUnit, int nRequestID)
{
	return pApi->ReqQryInvestUnit(pQryInvestUnit, nRequestID);
}



#pragma region Banking
///�����ѯת������
TRADEAPI_API int		ReqQryTransferBank(CThostFtdcTraderApi* pApi, CThostFtdcQryTransferBankField* pQryTransferBank, int nRequestID)
{
	return pApi->ReqQryTransferBank(pQryTransferBank, nRequestID);
}
///�����ѯ����ǩԼ��ϵ
TRADEAPI_API int		ReqQryAccountregister(CThostFtdcTraderApi* pApi, CThostFtdcQryAccountregisterField* pQryAccountregister, int nRequestID)
{
	return pApi->ReqQryAccountregister(pQryAccountregister, nRequestID);
}
///�����ѯǩԼ����
TRADEAPI_API int		ReqQryContractBank(CThostFtdcTraderApi* pApi, CThostFtdcQryContractBankField* pQryContractBank, int nRequestID)
{
	return pApi->ReqQryContractBank(pQryContractBank, nRequestID);
}
///�����ѯת����ˮ
TRADEAPI_API int		ReqQryTransferSerial(CThostFtdcTraderApi* pApi, CThostFtdcQryTransferSerialField* pQryTransferSerial, int nRequestID)
{
	return pApi->ReqQryTransferSerial(pQryTransferSerial, nRequestID);
}
///�ڻ������ѯ�����������
TRADEAPI_API int		ReqQueryBankAccountMoneyByFuture(CThostFtdcTraderApi* pApi, CThostFtdcReqQueryAccountField* pReqQueryAccount, int nRequestID)
{
	return pApi->ReqQueryBankAccountMoneyByFuture(pReqQueryAccount, nRequestID);
}

///�ڻ����������ʽ�ת�ڻ�����
TRADEAPI_API int		ReqFromBankToFutureByFuture(CThostFtdcTraderApi* pApi, CThostFtdcReqTransferField* pReqTransfer, int nRequestID)
{
	return pApi->ReqFromBankToFutureByFuture(pReqTransfer, nRequestID);
}
///�ڻ������ڻ��ʽ�ת��������
TRADEAPI_API int		ReqFromFutureToBankByFuture(CThostFtdcTraderApi* pApi, CThostFtdcReqTransferField* pReqTransfer, int nRequestID)
{
	return pApi->ReqFromFutureToBankByFuture(pReqTransfer, nRequestID);
}
#pragma endregion


#pragma region Exchange/������
///�����ѯ������
TRADEAPI_API int		ReqQryExchange(CThostFtdcTraderApi* pApi, CThostFtdcQryExchangeField* pQryExchange, int nRequestID)
{
	return pApi->ReqQryExchange(pQryExchange, nRequestID);
}
///�����ѯ��������֤����
TRADEAPI_API int		ReqQryExchangeMarginRate(CThostFtdcTraderApi* pApi, CThostFtdcQryExchangeMarginRateField* pQryExchangeMarginRate, int nRequestID)
{
	return pApi->ReqQryExchangeMarginRate(pQryExchangeMarginRate, nRequestID);
}
///�����ѯ������������֤����
TRADEAPI_API int		ReqQryExchangeMarginRateAdjust(CThostFtdcTraderApi* pApi, CThostFtdcQryExchangeMarginRateAdjustField* pQryExchangeMarginRateAdjust, int nRequestID)
{
	return pApi->ReqQryExchangeMarginRateAdjust(pQryExchangeMarginRateAdjust, nRequestID);
}
///�����ѯ����
TRADEAPI_API int		ReqQryExchangeRate(CThostFtdcTraderApi* pApi, CThostFtdcQryExchangeRateField* pQryExchangeRate, int nRequestID)
{
	return pApi->ReqQryExchangeRate(pQryExchangeRate, nRequestID);
}
#pragma endregion


#pragma region Broker
///�����ѯ���͹�˾���ײ���
TRADEAPI_API int		ReqQryBrokerTradingParams(CThostFtdcTraderApi* pApi, CThostFtdcQryBrokerTradingParamsField* pQryBrokerTradingParams, int nRequestID)
{
	return pApi->ReqQryBrokerTradingParams(pQryBrokerTradingParams, nRequestID);
}
///�����ѯ���͹�˾�����㷨
TRADEAPI_API int		ReqQryBrokerTradingAlgos(CThostFtdcTraderApi* pApi, CThostFtdcQryBrokerTradingAlgosField* pQryBrokerTradingAlgos, int nRequestID)
{
	return pApi->ReqQryBrokerTradingAlgos(pQryBrokerTradingAlgos, nRequestID);
}
#pragma endregion

#pragma region CFMMC
///�����ѯ��������û�����
TRADEAPI_API int		ReqQueryCFMMCTradingAccountToken(CThostFtdcTraderApi* pApi, CThostFtdcQueryCFMMCTradingAccountTokenField* pQueryCFMMCTradingAccountToken, int nRequestID)
{
	return pApi->ReqQueryCFMMCTradingAccountToken(pQueryCFMMCTradingAccountToken, nRequestID);
}

///�����ѯ��֤����ϵͳ���͹�˾�ʽ��˻���Կ
TRADEAPI_API int		ReqQryCFMMCTradingAccountKey(CThostFtdcTraderApi* pApi, CThostFtdcQryCFMMCTradingAccountKeyField* pQryCFMMCTradingAccountKey, int nRequestID)
{
	return pApi->ReqQryCFMMCTradingAccountKey(pQryCFMMCTradingAccountKey, nRequestID);
}
#pragma endregion


#pragma endregion

#pragma region �ص�����
//========================================
//==================================== �ص����� =======================================

TRADEAPI_API void   RegOnFrontConnected(TraderSpi* pSpi, CBOnFrontConnected cb)		//���ͻ����뽻�׺�̨������ͨ������ʱ����δ��¼ǰ�����÷��������á�
{
	pSpi->cbOnFrontConnected = cb;
}

TRADEAPI_API void   RegOnFrontDisconnected(TraderSpi* pSpi, CBOnFrontDisconnected cb)		//���ͻ����뽻�׺�̨ͨ�����ӶϿ�ʱ���÷��������á���������������API���Զ��������ӣ��ͻ��˿ɲ�������
{
	pSpi->cbOnFrontDisconnected = cb;
}

TRADEAPI_API void   RegOnHeartBeatWarning(TraderSpi* pSpi, CBOnHeartBeatWarning cb)		//������ʱ���档����ʱ��δ�յ�����ʱ���÷��������á�
{
	pSpi->cbOnHeartBeatWarning = cb;
}

TRADEAPI_API void   RegRspAuthenticate(TraderSpi* pSpi, CBRspAuthenticate cb)
{
	pSpi->cbRspAuthenticate = cb;
}

TRADEAPI_API void   RegRspUserLogin(TraderSpi* pSpi, CBRspUserLogin cb)	//��¼������Ӧ
{
	pSpi->cbRspUserLogin = cb;
}
TRADEAPI_API void   RegRspUserLogout(TraderSpi* pSpi, CBRspUserLogout cb)	//�ǳ�������Ӧ
{
	pSpi->cbRspUserLogout = cb;
}
TRADEAPI_API void   RegRspUserPasswordUpdate(TraderSpi* pSpi, CBRspUserPasswordUpdate cb)	//�û��������������Ӧ
{
	pSpi->cbRspUserPasswordUpdate = cb;
}
TRADEAPI_API void   RegRspTradingAccountPasswordUpdate(TraderSpi* pSpi, CBRspTradingAccountPasswordUpdate cb)	//�ʽ��˻��������������Ӧ
{
	pSpi->cbRspTradingAccountPasswordUpdate = cb;
}
TRADEAPI_API void   RegRspUserAuthMethod(TraderSpi* pSpi, CBRspUserAuthMethod cb)	//��ѯ�û���ǰ֧�ֵ���֤ģʽ�Ļظ�
{
	pSpi->cbRspUserAuthMethod = cb;
}
TRADEAPI_API void   RegRspGenUserCaptcha(TraderSpi* pSpi, CBRspGenUserCaptcha cb)	//��ȡͼ����֤������Ļظ�
{
	pSpi->cbRspGenUserCaptcha = cb;
}
TRADEAPI_API void   RegRspGenUserText(TraderSpi* pSpi, CBRspGenUserText cb)	//��ȡ������֤������Ļظ�
{
	pSpi->cbRspGenUserText = cb;
}
TRADEAPI_API void   RegRspOrderInsert(TraderSpi* pSpi, CBRspOrderInsert cb)	//����¼��������Ӧ
{
	pSpi->cbRspOrderInsert = cb;
}
TRADEAPI_API void   RegRspParkedOrderInsert(TraderSpi* pSpi, CBRspParkedOrderInsert cb)	//Ԥ��¼��������Ӧ
{
	pSpi->cbRspParkedOrderInsert = cb;
}
TRADEAPI_API void   RegRspParkedOrderAction(TraderSpi* pSpi, CBRspParkedOrderAction cb)	//Ԥ�񳷵�¼��������Ӧ
{
	pSpi->cbRspParkedOrderAction = cb;
}
TRADEAPI_API void   RegRspOrderAction(TraderSpi* pSpi, CBRspOrderAction cb)	//��������������Ӧ
{
	pSpi->cbRspOrderAction = cb;
}
TRADEAPI_API void   RegRspQueryMaxOrderVolume(TraderSpi* pSpi, CBRspQueryMaxOrderVolume cb)	//��ѯ��󱨵�������Ӧ
{
	pSpi->cbRspQueryMaxOrderVolume = cb;
}
TRADEAPI_API void   RegRspSettlementInfoConfirm(TraderSpi* pSpi, CBRspSettlementInfoConfirm cb)	//Ͷ���߽�����ȷ����Ӧ
{
	pSpi->cbRspSettlementInfoConfirm = cb;
}
TRADEAPI_API void   RegRspRemoveParkedOrder(TraderSpi* pSpi, CBRspRemoveParkedOrder cb)	//ɾ��Ԥ����Ӧ
{
	pSpi->cbRspRemoveParkedOrder = cb;
}
TRADEAPI_API void   RegRspRemoveParkedOrderAction(TraderSpi* pSpi, CBRspRemoveParkedOrderAction cb)	//ɾ��Ԥ�񳷵���Ӧ
{
	pSpi->cbRspRemoveParkedOrderAction = cb;
}
TRADEAPI_API void   RegBatchOrderAction(TraderSpi* pSpi, CBRspBatchOrderAction cb)	//������������������Ӧ
{
	pSpi->cbRspBatchOrderAction = cb;
}
TRADEAPI_API void   RegCombActionInsert(TraderSpi* pSpi, CBRspCombActionInsert cb)	//�������¼��������Ӧ
{
	pSpi->cbRspCombActionInsert = cb;
}
TRADEAPI_API void   RegRspQryOrder(TraderSpi* pSpi, CBRspQryOrder cb)	//�����ѯ������Ӧ
{
	pSpi->cbRspQryOrder = cb;
}
TRADEAPI_API void   RegRspQryTrade(TraderSpi* pSpi, CBRspQryTrade cb)	//�����ѯ�ɽ���Ӧ
{
	pSpi->cbRspQryTrade = cb;
}
TRADEAPI_API void   RegRspQryInvestorPosition(TraderSpi* pSpi, CBRspQryInvestorPosition cb)	//�����ѯͶ���ֲ߳���Ӧ
{
	pSpi->cbRspQryInvestorPosition = cb;
}
TRADEAPI_API void   RegRspQryTradingAccount(TraderSpi* pSpi, CBRspQryTradingAccount cb)	//�����ѯ�ʽ��˻���Ӧ
{
	pSpi->cbRspQryTradingAccount = cb;
}
TRADEAPI_API void   RegRspQryInvestor(TraderSpi* pSpi, CBRspQryInvestor cb)	//�����ѯͶ������Ӧ
{
	pSpi->cbRspQryInvestor = cb;
}
TRADEAPI_API void   RegRspQryTradingCode(TraderSpi* pSpi, CBRspQryTradingCode cb)	//�����ѯ���ױ�����Ӧ
{
	pSpi->cbRspQryTradingCode = cb;
}
TRADEAPI_API void   RegRspQryInstrumentMarginRate(TraderSpi* pSpi, CBRspQryInstrumentMarginRate cb)	//�����ѯ��Լ��֤������Ӧ
{
	pSpi->cbRspQryInstrumentMarginRate = cb;
}
TRADEAPI_API void   RegRspQryInstrumentCommissionRate(TraderSpi* pSpi, CBRspQryInstrumentCommissionRate cb)	//�����ѯ��Լ����������Ӧ
{
	pSpi->cbRspQryInstrumentCommissionRate = cb;
}
TRADEAPI_API void   RegRspQryExchange(TraderSpi* pSpi, CBRspQryExchange cb)	//�����ѯ��������Ӧ
{
	pSpi->cbRspQryExchange = cb;
}
TRADEAPI_API void   RegRspQryInstrument(TraderSpi* pSpi, CBRspQryInstrument cb)	//�����ѯ��Լ��Ӧ
{
	pSpi->cbRspQryInstrument = cb;
}
TRADEAPI_API void   RegRspQryDepthMarketData(TraderSpi* pSpi, CBRspQryDepthMarketData cb)	//�����ѯ������Ӧ
{
	pSpi->cbRspQryDepthMarketData = cb;
}
TRADEAPI_API void   RegRspQrySettlementInfo(TraderSpi* pSpi, CBRspQrySettlementInfo cb)	//�����ѯͶ���߽�������Ӧ
{
	pSpi->cbRspQrySettlementInfo = cb;
}
TRADEAPI_API void   RegRspQryTransferBank(TraderSpi* pSpi, CBRspQryTransferBank cb)	//�����ѯת��������Ӧ
{
	pSpi->cbRspQryTransferBank = cb;
}
TRADEAPI_API void   RegRspQryInvestorPositionDetail(TraderSpi* pSpi, CBRspQryInvestorPositionDetail cb)	//�����ѯͶ���ֲ߳���ϸ��Ӧ
{
	pSpi->cbRspQryInvestorPositionDetail = cb;
}
TRADEAPI_API void   RegRspQryNotice(TraderSpi* pSpi, CBRspQryNotice cb)	//�����ѯ�ͻ�֪ͨ��Ӧ
{
	pSpi->cbRspQryNotice = cb;
}
TRADEAPI_API void   RegRspQrySettlementInfoConfirm(TraderSpi* pSpi, CBRspQrySettlementInfoConfirm cb)	//�����ѯ������Ϣȷ����Ӧ
{
	pSpi->cbRspQrySettlementInfoConfirm = cb;
}
TRADEAPI_API void   RegRspQryInvestorPositionCombineDetail(TraderSpi* pSpi, CBRspQryInvestorPositionCombineDetail cb)	//�����ѯͶ���ֲ߳���ϸ��Ӧ
{
	pSpi->cbRspQryInvestorPositionCombineDetail = cb;
}
TRADEAPI_API void   RegRspQryCFMMCTradingAccountKey(TraderSpi* pSpi, CBRspQryCFMMCTradingAccountKey cb)	//��ѯ��֤����ϵͳ���͹�˾�ʽ��˻���Կ��Ӧ
{
	pSpi->cbRspQryCFMMCTradingAccountKey = cb;
}
TRADEAPI_API void   RegRspQryEWarrantOffset(TraderSpi* pSpi, CBRspQryEWarrantOffset cb)	//�����ѯ�ֵ��۵���Ϣ
{
	pSpi->cbRspQryEWarrantOffset = cb;
}
TRADEAPI_API void   RegRspQryInvestorProductGroupMargin(TraderSpi* pSpi, CBRspQryInvestorProductGroupMargin cb)	//�����ѯͶ����Ʒ��/��Ʒ�ֱ�֤��
{
	pSpi->cbRspQryInvestorProductGroupMargin = cb;
}
TRADEAPI_API void   RegRspQryExchangeMarginRate(TraderSpi* pSpi, CBRspQryExchangeMarginRate cb)	//�����ѯ��������֤����
{
	pSpi->cbRspQryExchangeMarginRate = cb;
}
TRADEAPI_API void   RegRspQryExchangeMarginRateAdjust(TraderSpi* pSpi, CBRspQryExchangeMarginRateAdjust cb)	//�����ѯ������������֤����
{
	pSpi->cbRspQryExchangeMarginRateAdjust = cb;
}
TRADEAPI_API void   RegRspQryExchangeRate(TraderSpi* pSpi, CBRspQryExchangeRate cb)	//�����ѯ������Ӧ
{
	pSpi->cbRspQryExchangeRate = cb;
}
TRADEAPI_API void   RegRspQrySecAgentACIDMap(TraderSpi* pSpi, CBRspQrySecAgentACIDMap cb)	//�����ѯ�����������Ա����Ȩ����Ӧ
{
	pSpi->cbRspQrySecAgentACIDMap = cb;
}
TRADEAPI_API void   RegRspQryProductExchRate(TraderSpi* pSpi, CBRspQryProductExchRate cb)	//�����ѯ��Ʒ���ۻ���
{
	pSpi->cbRspQryProductExchRate = cb;
}
TRADEAPI_API void   RegRspQryProductGroup(TraderSpi* pSpi, CBRspQryProductGroup cb)	//�����ѯ��Ʒ��
{
	pSpi->cbRspQryProductGroup = cb;
}
TRADEAPI_API void   RegRspQryMMInstrumentCommissionRate(TraderSpi* pSpi, CBRspQryMMInstrumentCommissionRate cb)	//�����ѯ�����̺�Լ����������Ӧ
{
	pSpi->cbRspQryMMInstrumentCommissionRate = cb;
}
TRADEAPI_API void   RegRspQryMMOptionInstrCommRate(TraderSpi* pSpi, CBRspQryMMOptionInstrCommRate cb)	//�����ѯ��������Ȩ��Լ��������Ӧ
{
	pSpi->cbRspQryMMOptionInstrCommRate = cb;
}
TRADEAPI_API void   RegRspQryInstrumentOrderCommRate(TraderSpi* pSpi, CBRspQryInstrumentOrderCommRate cb)	//�����ѯ������������Ӧ
{
	pSpi->cbRspQryInstrumentOrderCommRate = cb;
}
TRADEAPI_API void   RegRspQrySecAgentTradingAccount(TraderSpi* pSpi, CBRspQrySecAgentTradingAccount cb)	//�����ѯ�ʽ��˻���Ӧ
{
	pSpi->cbRspQrySecAgentTradingAccount = cb;
}
TRADEAPI_API void   RegRspQrySecAgentCheckMode(TraderSpi* pSpi, CBRspQrySecAgentCheckMode cb)	//�����ѯ�����������ʽ�У��ģʽ��Ӧ
{
	pSpi->cbRspQrySecAgentCheckMode = cb;
}
TRADEAPI_API void   RegRspQrySecAgentTradeInfo(TraderSpi* pSpi, CBRspQrySecAgentTradeInfo cb)	//�����ѯ������������Ϣ��Ӧ
{
	pSpi->cbRspQrySecAgentTradeInfo = cb;
}
TRADEAPI_API void   RegRspQryOptionInstrTradeCost(TraderSpi* pSpi, CBRspQryOptionInstrTradeCost cb)	//�����ѯ��Ȩ���׳ɱ���Ӧ
{
	pSpi->cbRspQryOptionInstrTradeCost = cb;
}
TRADEAPI_API void   RegRspQryOptionInstrCommRate(TraderSpi* pSpi, CBRspQryOptionInstrCommRate cb)	//�����ѯ��Ȩ��Լ��������Ӧ
{
	pSpi->cbRspQryOptionInstrCommRate = cb;
}
TRADEAPI_API void   RegRspQryExecOrder(TraderSpi* pSpi, CBRspQryExecOrder cb)	//�����ѯִ��������Ӧ
{
	pSpi->cbRspQryExecOrder = cb;
}
TRADEAPI_API void   RegRspQryForQuote(TraderSpi* pSpi, CBRspQryForQuote cb)	//�����ѯѯ����Ӧ
{
	pSpi->cbRspQryForQuote = cb;
}
TRADEAPI_API void   RegRspQryQuote(TraderSpi* pSpi, CBRspQryQuote cb)	//�����ѯ������Ӧ
{
	pSpi->cbRspQryQuote = cb;
}
TRADEAPI_API void   RegRspQryOptionSelfClose(TraderSpi* pSpi, CBRspQryOptionSelfClose cb)	//�����ѯ��Ȩ�ԶԳ���Ӧ
{
	pSpi->cbRspQryOptionSelfClose = cb;
}
TRADEAPI_API void   RegRspQryInvestUnit(TraderSpi* pSpi, CBRspQryInvestUnit cb)	//�����ѯͶ�ʵ�Ԫ��Ӧ
{
	pSpi->cbRspQryInvestUnit = cb;
}
TRADEAPI_API void   RegRspQryCombInstrumentGuard(TraderSpi* pSpi, CBRspQryCombInstrumentGuard cb)	//�����ѯ��Ϻ�Լ��ȫϵ����Ӧ
{
	pSpi->cbRspQryCombInstrumentGuard = cb;
}
TRADEAPI_API void   RegRspQryCombAction(TraderSpi* pSpi, CBRspQryCombAction cb)	//�����ѯ���������Ӧ
{
	pSpi->cbRspQryCombAction = cb;
}
TRADEAPI_API void   RegRspQryTransferSerial(TraderSpi* pSpi, CBRspQryTransferSerial cb)	//�����ѯת����ˮ��Ӧ
{
	pSpi->cbRspQryTransferSerial = cb;
}
TRADEAPI_API void   RegRspQryAccountregister(TraderSpi* pSpi, CBRspQryAccountregister cb)	//�����ѯ����ǩԼ��ϵ��Ӧ
{
	pSpi->cbRspQryAccountregister = cb;
}
TRADEAPI_API void   RegRspError(TraderSpi* pSpi, CBRspError cb)	//����Ӧ��
{
	pSpi->cbRspError = cb;
}
TRADEAPI_API void   RegRtnOrder(TraderSpi* pSpi, CBRtnOrder cb)	//����֪ͨ
{
	pSpi->cbRtnOrder = cb;
}
TRADEAPI_API void   RegRtnTrade(TraderSpi* pSpi, CBRtnTrade cb)	//�ɽ�֪ͨ
{
	pSpi->cbRtnTrade = cb;
}
TRADEAPI_API void   RegErrRtnOrderInsert(TraderSpi* pSpi, CBErrRtnOrderInsert cb)	//����¼�����ر�
{
	pSpi->cbErrRtnOrderInsert = cb;
}
TRADEAPI_API void   RegErrRtnOrderAction(TraderSpi* pSpi, CBErrRtnOrderAction cb)	//������������ر�
{
	pSpi->cbErrRtnOrderAction = cb;
}
TRADEAPI_API void   RegRtnInstrumentStatus(TraderSpi* pSpi, CBRtnInstrumentStatus cb)	//��Լ����״̬֪ͨ
{
	pSpi->cbRtnInstrumentStatus = cb;
}
TRADEAPI_API void   RegRtnTradingNotice(TraderSpi* pSpi, CBRtnTradingNotice cb)	//����֪ͨ
{
	pSpi->cbRtnTradingNotice = cb;
}
TRADEAPI_API void   RegRtnErrorConditionalOrder(TraderSpi* pSpi, CBRtnErrorConditionalOrder cb)	//��ʾ������У�����
{
	pSpi->cbRtnErrorConditionalOrder = cb;
}
TRADEAPI_API void   RegRspQryContractBank(TraderSpi* pSpi, CBRspQryContractBank cb)	//�����ѯǩԼ������Ӧ
{
	pSpi->cbRspQryContractBank = cb;
}
TRADEAPI_API void   RegRspQryParkedOrder(TraderSpi* pSpi, CBRspQryParkedOrder cb)	//�����ѯԤ����Ӧ
{
	pSpi->cbRspQryParkedOrder = cb;
}
TRADEAPI_API void   RegRspQryParkedOrderAction(TraderSpi* pSpi, CBRspQryParkedOrderAction cb)	//�����ѯԤ�񳷵���Ӧ
{
	pSpi->cbRspQryParkedOrderAction = cb;
}
TRADEAPI_API void   RegRspQryTradingNotice(TraderSpi* pSpi, CBRspQryTradingNotice cb)	//�����ѯ����֪ͨ��Ӧ
{
	pSpi->cbRspQryTradingNotice = cb;
}
TRADEAPI_API void   RegRspQryBrokerTradingParams(TraderSpi* pSpi, CBRspQryBrokerTradingParams cb)	//�����ѯ���͹�˾���ײ�����Ӧ
{
	pSpi->cbRspQryBrokerTradingParams = cb;
}
TRADEAPI_API void   RegRspQryBrokerTradingAlgos(TraderSpi* pSpi, CBRspQryBrokerTradingAlgos cb)	//�����ѯ���͹�˾�����㷨��Ӧ
{
	pSpi->cbRspQryBrokerTradingAlgos = cb;
}
TRADEAPI_API void   RegRtnFromBankToFutureByBank(TraderSpi* pSpi, CBRtnFromBankToFutureByBank cb)	//���з��������ʽ�ת�ڻ�֪ͨ
{
	pSpi->cbRtnFromBankToFutureByBank = cb;
}
TRADEAPI_API void   RegRtnFromFutureToBankByBank(TraderSpi* pSpi, CBRtnFromFutureToBankByBank cb)	//���з����ڻ��ʽ�ת����֪ͨ
{
	pSpi->cbRtnFromFutureToBankByBank = cb;
}
TRADEAPI_API void   RegRtnRepealFromBankToFutureByBank(TraderSpi* pSpi, CBRtnRepealFromBankToFutureByBank cb)	//���з����������ת�ڻ�֪ͨ
{
	pSpi->cbRtnRepealFromBankToFutureByBank = cb;
}
TRADEAPI_API void   RegRtnRepealFromFutureToBankByBank(TraderSpi* pSpi, CBRtnRepealFromFutureToBankByBank cb)	//���з�������ڻ�ת����֪ͨ
{
	pSpi->cbRtnRepealFromFutureToBankByBank = cb;
}
TRADEAPI_API void   RegRtnFromBankToFutureByFuture(TraderSpi* pSpi, CBRtnFromBankToFutureByFuture cb)	//�ڻ����������ʽ�ת�ڻ�֪ͨ
{
	pSpi->cbRtnFromBankToFutureByFuture = cb;
}
TRADEAPI_API void   RegRtnFromFutureToBankByFuture(TraderSpi* pSpi, CBRtnFromFutureToBankByFuture cb)	//�ڻ������ڻ��ʽ�ת����֪ͨ
{
	pSpi->cbRtnFromFutureToBankByFuture = cb;
}
TRADEAPI_API void   RegRtnRepealFromBankToFutureByFutureManual(TraderSpi* pSpi, CBRtnRepealFromBankToFutureByFutureManual cb)	//ϵͳ����ʱ�ڻ����ֹ������������ת�ڻ��������д�����Ϻ��̷��ص�֪ͨ
{
	pSpi->cbRtnRepealFromBankToFutureByFutureManual = cb;
}
TRADEAPI_API void   RegRtnRepealFromFutureToBankByFutureManual(TraderSpi* pSpi, CBRtnRepealFromFutureToBankByFutureManual cb)	//ϵͳ����ʱ�ڻ����ֹ���������ڻ�ת�����������д�����Ϻ��̷��ص�֪ͨ
{
	pSpi->cbRtnRepealFromFutureToBankByFutureManual = cb;
}
TRADEAPI_API void   RegRtnQueryBankBalanceByFuture(TraderSpi* pSpi, CBRtnQueryBankBalanceByFuture cb)	//�ڻ������ѯ�������֪ͨ
{
	pSpi->cbRtnQueryBankBalanceByFuture = cb;
}
TRADEAPI_API void   RegErrRtnBankToFutureByFuture(TraderSpi* pSpi, CBErrRtnBankToFutureByFuture cb)	//�ڻ����������ʽ�ת�ڻ�����ر�
{
	pSpi->cbErrRtnBankToFutureByFuture = cb;
}
TRADEAPI_API void   RegErrRtnFutureToBankByFuture(TraderSpi* pSpi, CBErrRtnFutureToBankByFuture cb)	//�ڻ������ڻ��ʽ�ת���д���ر�
{
	pSpi->cbErrRtnFutureToBankByFuture = cb;
}
TRADEAPI_API void   RegErrRtnRepealBankToFutureByFutureManual(TraderSpi* pSpi, CBErrRtnRepealBankToFutureByFutureManual cb)	//ϵͳ����ʱ�ڻ����ֹ������������ת�ڻ�����ر�
{
	pSpi->cbErrRtnRepealBankToFutureByFutureManual = cb;
}
TRADEAPI_API void   RegErrRtnRepealFutureToBankByFutureManual(TraderSpi* pSpi, CBErrRtnRepealFutureToBankByFutureManual cb)	//ϵͳ����ʱ�ڻ����ֹ���������ڻ�ת���д���ر�
{
	pSpi->cbErrRtnRepealFutureToBankByFutureManual = cb;
}
TRADEAPI_API void   RegErrRtnQueryBankBalanceByFuture(TraderSpi* pSpi, CBErrRtnQueryBankBalanceByFuture cb)	//�ڻ������ѯ����������ر�
{
	pSpi->cbErrRtnQueryBankBalanceByFuture = cb;
}
TRADEAPI_API void   RegRtnRepealFromBankToFutureByFuture(TraderSpi* pSpi, CBRtnRepealFromBankToFutureByFuture cb)	//�ڻ������������ת�ڻ��������д�����Ϻ��̷��ص�֪ͨ
{
	pSpi->cbRtnRepealFromBankToFutureByFuture = cb;
}
TRADEAPI_API void   RegRtnRepealFromFutureToBankByFuture(TraderSpi* pSpi, CBRtnRepealFromFutureToBankByFuture cb)	//�ڻ���������ڻ�ת�����������д�����Ϻ��̷��ص�֪ͨ
{
	pSpi->cbRtnRepealFromFutureToBankByFuture = cb;
}
TRADEAPI_API void   RegRspFromBankToFutureByFuture(TraderSpi* pSpi, CBRspFromBankToFutureByFuture cb)	//�ڻ����������ʽ�ת�ڻ�Ӧ��
{
	pSpi->cbRspFromBankToFutureByFuture = cb;
}
TRADEAPI_API void   RegRspFromFutureToBankByFuture(TraderSpi* pSpi, CBRspFromFutureToBankByFuture cb)	//�ڻ������ڻ��ʽ�ת����Ӧ��
{
	pSpi->cbRspFromFutureToBankByFuture = cb;
}
TRADEAPI_API void   RegRspQueryBankAccountMoneyByFuture(TraderSpi* pSpi, CBRspQueryBankAccountMoneyByFuture cb)	//�ڻ������ѯ�������Ӧ��
{
	pSpi->cbRspQueryBankAccountMoneyByFuture = cb;
}
TRADEAPI_API void   RegRspQueryCFMMCTradingAccountToken(TraderSpi* pSpi, CBRspQueryCFMMCTradingAccountToken cb)	//��ѯ��������û�����Ӧ��
{
	pSpi->cbRspQueryCFMMCTradingAccountToken = cb;
}
TRADEAPI_API void   RegRtnCFMMCTradingAccountToken(TraderSpi* pSpi, CBRtnCFMMCTradingAccountToken cb)	//��ѯ��������û�����֪ͨ
{
	pSpi->cbRtnCFMMCTradingAccountToken = cb;
}



