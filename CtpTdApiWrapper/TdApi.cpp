#include "pch.h"
#include "TdApi.h"

#include <filesystem>
using namespace std;


TDAPI_API CThostFtdcTraderApi* CreateFtdcTraderApi(const char* pszFlowPath)
{
	filesystem::path p(pszFlowPath);
	if (!filesystem::exists(pszFlowPath))
		filesystem::create_directory(p);

	// ��ʼ��UserApi
	CThostFtdcTraderApi* pApi = CThostFtdcTraderApi::CreateFtdcTraderApi(pszFlowPath);			// ����UserApi	
	return pApi;
}
TDAPI_API TraderSpi* CreateTdSpi()
{
	TraderSpi* ret = new TraderSpi();
	return ret;
}
TDAPI_API void			RegisterSpi(CThostFtdcTraderApi* api, TraderSpi* pSpi)
{
	api->RegisterSpi(pSpi);
}


//��ȡ�ӿڰ汾
TDAPI_API const char* GetApiVersion()
{
	return CThostFtdcTraderApi::GetApiVersion();
}

////����
//TDAPI_API CThostFtdcTraderApi* Connect(char *frontAddr, char *pszFlowPath, TraderSpi* pSpi)
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
//TDAPI_API void DisConnect(CThostFtdcTraderApi* pApi)
//{
//	if (pApi == NULL) return;
//
//	pApi->RegisterSpi(NULL);
//	pApi->Release();
//	pApi = NULL;
//}

///ɾ���ӿڶ�����
///@remark ����ʹ�ñ��ӿڶ���ʱ,���øú���ɾ���ӿڶ���
TDAPI_API void Release(CThostFtdcTraderApi* api)
{
	api->Release();
}

///��ʼ��
///@remark ��ʼ�����л���,ֻ�е��ú�,�ӿڲſ�ʼ����
TDAPI_API void Init(CThostFtdcTraderApi* api)
{
	api->Init();
}

///�ȴ��ӿ��߳̽�������
///@return �߳��˳�����
TDAPI_API int Join(CThostFtdcTraderApi* api)
{
	return api->Join();
}

//��ȡ������
TDAPI_API const char* GetTradingDay(CThostFtdcTraderApi* pApi)
{
	if (pApi == NULL) return NULL;

	return pApi->GetTradingDay();
}

TDAPI_API void		RegisterFront(CThostFtdcTraderApi* pApi, char* pszFrontAddress)
{
	pApi->RegisterFront(pszFrontAddress);
}

TDAPI_API void		RegisterNameServer(CThostFtdcTraderApi* pApi, char* pszNsAddress)
{
	pApi->RegisterNameServer(pszNsAddress);
}

///ע�����ַ������û���Ϣ
///@param pFensUserInfo���û���Ϣ��
TDAPI_API void		RegisterFensUserInfo(CThostFtdcTraderApi* pApi, CThostFtdcFensUserInfoField* pFensUserInfo)
{
	pApi->RegisterFensUserInfo(pFensUserInfo);
}

TDAPI_API void		SubscribePrivateTopic(CThostFtdcTraderApi* pApi, THOST_TE_RESUME_TYPE nResumeType)
{
	pApi->SubscribePrivateTopic(nResumeType);
}

///���Ĺ�������
///@param nResumeType �������ش���ʽ  
///        THOST_TERT_RESTART:�ӱ������տ�ʼ�ش�
///        THOST_TERT_RESUME:���ϴ��յ�������
///        THOST_TERT_QUICK:ֻ���͵�¼�󹫹���������
///@remark �÷���Ҫ��Init����ǰ���á����������򲻻��յ������������ݡ�
TDAPI_API void		SubscribePublicTopic(CThostFtdcTraderApi* pApi, THOST_TE_RESUME_TYPE nResumeType)
{
	pApi->SubscribePublicTopic(nResumeType);
}

TDAPI_API int		ReqAuthenticate(CThostFtdcTraderApi* pApi, CThostFtdcReqAuthenticateField* field, int nRequestID)
{
	return pApi->ReqAuthenticate(field, nRequestID);
}

TDAPI_API int		RegisterUserSystemInfo(CThostFtdcTraderApi* pApi, CThostFtdcUserSystemInfoField* pUserSystemInfo)
{
	return pApi->RegisterUserSystemInfo(pUserSystemInfo);
}

TDAPI_API int		SubmitUserSystemInfo(CThostFtdcTraderApi* pApi, CThostFtdcUserSystemInfoField* pUserSystemInfo)
{
	return pApi->SubmitUserSystemInfo(pUserSystemInfo);
}

////�ͻ�����֤����
//TDAPI_API int		ReqAuthenticate(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcUserIDType userID,
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
TDAPI_API int		ReqUserLogin(CThostFtdcTraderApi* pApi, CThostFtdcReqUserLoginField* pReqUserLoginField, int nRequestID)
{
	return pApi->ReqUserLogin(pReqUserLoginField, nRequestID);
}
TDAPI_API int		ReqUserLogout(CThostFtdcTraderApi* pApi, CThostFtdcUserLogoutField* pUserLogout, int nRequestID)
{
	return pApi->ReqUserLogout(pUserLogout, nRequestID);
}

////�����û���¼����
//TDAPI_API int ReqUserLogin(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcUserIDType userID,
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
//TDAPI_API int ReqUserLogout(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcUserIDType investorID)
//{
//	if (pApi == NULL) return -1;
//
//	CThostFtdcUserLogoutField req;
//	memset(&req, 0, sizeof(req));
//	strcpy_s(req.BrokerID, brokerID);
//	strcpy_s(req.UserID, investorID);
//	return pApi->ReqUserLogout(&req, requestID);
//}


TDAPI_API int		ReqUserPasswordUpdate(CThostFtdcTraderApi* pApi, CThostFtdcUserPasswordUpdateField* pUserPasswordUpdate, int nRequestID)
{
	return pApi->ReqUserPasswordUpdate(pUserPasswordUpdate, nRequestID);
}

///�ʽ��˻������������
TDAPI_API int		ReqTradingAccountPasswordUpdate(CThostFtdcTraderApi* pApi, CThostFtdcTradingAccountPasswordUpdateField* pTradingAccountPasswordUpdate, int nRequestID)
{
	return pApi->ReqTradingAccountPasswordUpdate(pTradingAccountPasswordUpdate, nRequestID);
}

///��ѯ�û���ǰ֧�ֵ���֤ģʽ���ù����ݲ�֧�֣�
TDAPI_API int		ReqUserAuthMethod(CThostFtdcTraderApi* pApi, CThostFtdcReqUserAuthMethodField* pReqUserAuthMethod, int nRequestID)
{
	return pApi->ReqUserAuthMethod(pReqUserAuthMethod, nRequestID);
}

///�û�������ȡͼ����֤�����󣨸ù����ݲ�֧�֣�
TDAPI_API int		ReqGenUserCaptcha(CThostFtdcTraderApi* pApi, CThostFtdcReqGenUserCaptchaField* pReqGenUserCaptcha, int	nRequestID)
{
	return pApi->ReqGenUserCaptcha(pReqGenUserCaptcha, nRequestID);
}

///�û�������ȡ������֤�����󣨸ù����ݲ�֧�֣�
TDAPI_API int		ReqGenUserText(CThostFtdcTraderApi* pApi, CThostFtdcReqGenUserTextField* pReqGenUserText, int nRequestID)
{
	return pApi->ReqGenUserText(pReqGenUserText, nRequestID);
}

///�û���������ͼƬ��֤��ĵ�½���󣨸ù����ݲ�֧�֣�
TDAPI_API int		ReqUserLoginWithCaptcha(CThostFtdcTraderApi* pApi, CThostFtdcReqUserLoginWithCaptchaField* pReqUserLoginWithCaptcha, int nRequestID)
{
	return pApi->ReqUserLoginWithCaptcha(pReqUserLoginWithCaptcha, nRequestID);
}

///�û��������ж�����֤��ĵ�½���󣨸ù����ݲ�֧�֣�
TDAPI_API int		ReqUserLoginWithText(CThostFtdcTraderApi* pApi, CThostFtdcReqUserLoginWithTextField* pReqUserLoginWithText, int	nRequestID)
{
	return pApi->ReqUserLoginWithText(pReqUserLoginWithText, nRequestID);
}


///�û��������ж�̬����ĵ�½���󣨸ù����ݲ�֧�֣�
TDAPI_API int		ReqUserLoginWithOTP(CThostFtdcTraderApi* pApi, CThostFtdcReqUserLoginWithOTPField* pReqUserLoginWithOTP, int nRequestID)
{
	return pApi->ReqUserLoginWithOTP(pReqUserLoginWithOTP, nRequestID);
}


//
////�����û�����
//TDAPI_API int ReqUserPasswordUpdate(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcUserIDType userID,
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
//TDAPI_API int ReqTradingAccountPasswordUpdate(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcBrokerIDType brokerID,
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
////��ȫ��¼����
//TDAPI_API int ReqUserSafeLogin(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcUserIDType userID,
//								  TThostFtdcPasswordType password, TThostFtdcPasswordType oneTimePassword, TThostFtdcMacAddressType macAddress, TThostFtdcProductInfoType productInfo,
//								  TThostFtdcProductInfoType interfaceInfo, TThostFtdcProtocolInfoType	protocolInfo)
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
////��ȫ�����û�����
//TDAPI_API int ReqUserPasswordSafeUpdate(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcUserIDType userID,
//										   TThostFtdcUserIDType oldPassword, TThostFtdcPasswordType newPassword)
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

////��ѯ�û���ǰ֧�ֵ���֤ģʽ
//TDAPI_API int ReqUserAuthMethod(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcUserIDType userID, TThostFtdcDateType tradingDay)
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
//TDAPI_API int ReqGenUserCaptcha(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcUserIDType userID, TThostFtdcDateType tradingDay)
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
//TDAPI_API int ReqGenUserText(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcUserIDType userID, TThostFtdcDateType tradingDay)
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
//TDAPI_API int ReqUserLoginWithCaptcha(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcReqUserLoginWithCaptchaField *pReqUserLoginWithCaptcha)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqUserLoginWithCaptcha(pReqUserLoginWithCaptcha, requestID);
//}
////�û��������ж�����֤��ĵ�½����
//TDAPI_API int ReqUserLoginWithText(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcReqUserLoginWithTextField *pReqUserLoginWithText)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqUserLoginWithText(pReqUserLoginWithText, requestID);
//}
////�û��������ж�̬����ĵ�½����
//TDAPI_API int ReqUserLoginWithOTP(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcReqUserLoginWithOTPField *pReqUserLoginWithOTP)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqUserLoginWithOTP(pReqUserLoginWithOTP, requestID);
//}
//����¼������
//TDAPI_API int ReqOrderInsert(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcInputOrderField *pOrder)
//{
//	if (pApi == NULL) return -1;
//
//	int siez = sizeof(CThostFtdcInputOrderField);
//	strcpy_s(pOrder->BusinessUnit, "HF");
//	return pApi->ReqOrderInsert(pOrder, requestID);
//}
////������������
//TDAPI_API int ReqOrderAction(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcInputOrderActionField *pOrder)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqOrderAction(pOrder, requestID);
//}
////��ѯ��󱨵���������
//TDAPI_API int ReqQueryMaxOrderVolume(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcQueryMaxOrderVolumeField *pMaxOrderVolume)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqQueryMaxOrderVolume(pMaxOrderVolume, requestID);
//}
////Ͷ���߽�����ȷ��
//TDAPI_API int ReqSettlementInfoConfirm(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcInvestorIDType investorID)
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
//TDAPI_API int ReqExecOrderInsert(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcInputExecOrderField *pInputExecOrder)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqExecOrderInsert(pInputExecOrder, requestID);
//}
////ִ�������������
//TDAPI_API int ReqExecOrderAction(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcInputExecOrderActionField *pInputExecOrderAction)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqExecOrderAction(pInputExecOrderAction, requestID);
//}
////ѯ��¼������
//TDAPI_API int ReqForQuoteInsert(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcInputForQuoteField *pInputForQuote)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqForQuoteInsert(pInputForQuote, requestID);
//}
////����¼������
//TDAPI_API int ReqQuoteInsert(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcInputQuoteField *pInputQuote)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqQuoteInsert(pInputQuote, requestID);
//}
////���۲�������
//TDAPI_API int ReqQuoteAction(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcInputQuoteActionField *pInputQuoteAction)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqQuoteAction(pInputQuoteAction, requestID);
//}
////����������������
//TDAPI_API int ReqBatchOrderAction(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcInputBatchOrderActionField *pInputBatchOrderAction)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqBatchOrderAction(pInputBatchOrderAction, requestID);
//}
////��Ȩ�ԶԳ�¼������
//TDAPI_API int ReqOptionSelfCloseInsert(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcInputOptionSelfCloseField *pInputOptionSelfClose)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqOptionSelfCloseInsert(pInputOptionSelfClose, requestID);
//}
////��Ȩ�ԶԳ��������
//TDAPI_API int ReqOptionSelfCloseAction(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcInputOptionSelfCloseActionField *pInputOptionSelfCloseAction)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqOptionSelfCloseAction(pInputOptionSelfCloseAction, requestID);
//}
////�������¼������
//TDAPI_API int ReqCombActionInsert(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcInputCombActionField *pInputCombAction)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqCombActionInsert(pInputCombAction, requestID);
//}
////�����ѯ����
//TDAPI_API int ReqQryOrder(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcQryOrderField *pQryOrder)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqQryOrder(pQryOrder, requestID);
//}
////�����ѯ�ɽ�
//TDAPI_API int ReqQryTrade(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcQryTradeField *pQryTrade)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqQryTrade(pQryTrade, requestID);
//}
////�����ѯͶ���ֲ߳�
//TDAPI_API int ReqQryInvestorPosition(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcInvestorIDType investorID, TThostFtdcInstrumentIDType instrumentID)
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
//TDAPI_API int ReqQryTradingAccount(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcInvestorIDType investorID)
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
//TDAPI_API int ReqQryInvestor(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcInvestorIDType investorID)
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
//TDAPI_API int ReqQryTradingCode(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcInvestorIDType investorID, TThostFtdcClientIDType clientID, TThostFtdcExchangeIDType	exchangeID)
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
//TDAPI_API int ReqQryInstrumentMarginRate(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcInvestorIDType investorID, TThostFtdcInstrumentIDType instrumentID, TThostFtdcHedgeFlagType	hedgeFlag)
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
//TDAPI_API int ReqQryInstrumentCommissionRate(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcInvestorIDType investorID, TThostFtdcInstrumentIDType instrumentID)
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
//TDAPI_API int ReqQryExchange(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcExchangeIDType exchangeID)
//{
//	if (pApi == NULL) return -1;
//
//	CThostFtdcQryExchangeField  req;
//	memset(&req, 0, sizeof(req));
//	strcpy_s(req.ExchangeID, exchangeID);
//	return pApi->ReqQryExchange(&req, requestID);
//}
////�����ѯ��Լ
//TDAPI_API int ReqQryInstrument(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcInstrumentIDType instrumentID)
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
//TDAPI_API int ReqQryDepthMarketData(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcInstrumentIDType instrumentID)
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
//TDAPI_API int ReqQrySettlementInfo(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcInvestorIDType investorID, TThostFtdcDateType	tradingDay)
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
//TDAPI_API int ReqQryInvestorPositionDetail(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcInvestorIDType investorID, TThostFtdcInstrumentIDType instrumentID)
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
//TDAPI_API int ReqQryNotice(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcBrokerIDType brokerID)
//{
//	if (pApi == NULL) return -1;
//
//	CThostFtdcQryNoticeField  req;
//	memset(&req, 0, sizeof(req));
//	strcpy_s(req.BrokerID, brokerID);
//	return pApi->ReqQryNotice(&req, requestID);
//}
////�����ѯ������Ϣȷ��
//TDAPI_API int ReqQrySettlementInfoConfirm(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcInvestorIDType investorID)
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
//TDAPI_API int ReqQryInvestorPositionCombineDetail(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcInvestorIDType investorID, TThostFtdcInstrumentIDType instrumentID)
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
//TDAPI_API int ReqQryCFMMCTradingAccountKey(CThostFtdcTraderApi* pApi, CThostFtdcQryCFMMCTradingAccountKeyField* key, int nRequestID)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqQryCFMMCTradingAccountKey(key, nRequestID);
//}
////�����ѯ�ֵ��۵���Ϣ
//TDAPI_API int ReqQryEWarrantOffset(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcQryEWarrantOffsetField *pQryEWarrantOffset)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqQryEWarrantOffset(pQryEWarrantOffset, requestID);
//}
////�����ѯͶ����Ʒ��/��Ʒ�ֱ�֤��
//TDAPI_API int ReqQryInvestorProductGroupMargin(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcQryInvestorProductGroupMarginField *pQryInvestorProductGroupMargin)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqQryInvestorProductGroupMargin(pQryInvestorProductGroupMargin, requestID);
//}
////�����ѯ��������֤����
//TDAPI_API int ReqQryExchangeMarginRate(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcInstrumentIDType instrumentID, TThostFtdcHedgeFlagType hedgeFlag)
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
//TDAPI_API int ReqQryExchangeMarginRateAdjust(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcInstrumentIDType instrumentID, TThostFtdcHedgeFlagType hedgeFlag)
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
//TDAPI_API int ReqQryExchangeRate(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcQryExchangeRateField *pQryExchangeRate)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqQryExchangeRate(pQryExchangeRate, requestID);
//}
////�����ѯ�����������Ա����Ȩ��
//TDAPI_API int ReqQrySecAgentACIDMap(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcQrySecAgentACIDMapField *pQrySecAgentACIDMap)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqQrySecAgentACIDMap(pQrySecAgentACIDMap, requestID);
//}
////�����ѯ��Ʒ���ۻ���
//TDAPI_API int ReqQryProductExchRate(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcInstrumentIDType productID)
//{
//	if (pApi == NULL) return -1;
//
//	CThostFtdcQryProductExchRateField req;
//	memset(&req, 0, sizeof(req));
//	strcpy_s(req.ProductID, productID);
//	return pApi->ReqQryProductExchRate(&req, requestID);
//}
////�����ѯ��Ʒ��
//TDAPI_API int ReqQryProductGroup(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcInstrumentIDType productID, TThostFtdcExchangeIDType exchangeID)
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
//TDAPI_API int ReqQryMMInstrumentCommissionRate(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcInvestorIDType investorID, TThostFtdcInstrumentIDType instrumentID)
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
//TDAPI_API int ReqQryMMOptionInstrCommRate(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcInvestorIDType investorID, TThostFtdcInstrumentIDType instrumentID)
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
//TDAPI_API int ReqQryInstrumentOrderCommRate(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcInvestorIDType investorID, TThostFtdcInstrumentIDType instrumentID)
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
//TDAPI_API int ReqQrySecAgentTradingAccount(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcQryTradingAccountField *pQryTradingAccount)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqQrySecAgentTradingAccount(pQryTradingAccount, requestID);
//}
////�����ѯ�����������ʽ�У��ģʽ
//TDAPI_API int ReqQrySecAgentCheckMode(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcQrySecAgentCheckModeField *pQrySecAgentCheckMode)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqQrySecAgentCheckMode(pQrySecAgentCheckMode, requestID);
//}
////�����ѯ��Ȩ���׳ɱ�
//TDAPI_API int ReqQryOptionInstrTradeCost(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcQryOptionInstrTradeCostField *pQryOptionInstrTradeCost)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqQryOptionInstrTradeCost(pQryOptionInstrTradeCost, requestID);
//}
////�����ѯ��Ȩ��Լ������
//TDAPI_API int ReqQryOptionInstrCommRate(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcInvestorIDType investorID, TThostFtdcInstrumentIDType instrumentID)
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
//TDAPI_API int ReqQryExecOrder(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcQryExecOrderField *pQryExecOrder)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqQryExecOrder(pQryExecOrder, requestID);
//}
////�����ѯѯ��
//TDAPI_API int ReqQryForQuote(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcQryForQuoteField *pQryForQuote)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqQryForQuote(pQryForQuote, requestID);
//}
////�����ѯ����
//TDAPI_API int ReqQryQuote(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcQryQuoteField *pQryQuote)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqQryQuote(pQryQuote, requestID);
//}
////�����ѯ��Ȩ�ԶԳ�
//TDAPI_API int ReqQryOptionSelfClose(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcQryOptionSelfCloseField *pQryOptionSelfClose)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqQryOptionSelfClose(pQryOptionSelfClose, requestID);
//}
////�����ѯͶ�ʵ�Ԫ
//TDAPI_API int ReqQryInvestUnit(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcQryInvestUnitField *pQryInvestUnit)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqQryInvestUnit(pQryInvestUnit, requestID);
//}
////�����ѯ��Ϻ�Լ��ȫϵ��
//TDAPI_API int ReqQryCombInstrumentGuard(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcQryCombInstrumentGuardField *pQryCombInstrumentGuard)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqQryCombInstrumentGuard(pQryCombInstrumentGuard, requestID);
//}
////�����ѯ�������
//TDAPI_API int ReqQryCombAction(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcQryCombActionField *pQryCombAction)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqQryCombAction(pQryCombAction, requestID);
//}
////�����ѯ����֪ͨ
//TDAPI_API int ReqQryTradingNotice(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcInvestorIDType investorID)
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
//TDAPI_API int ReqQryBrokerTradingParams(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcInvestorIDType investorID)
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
//TDAPI_API int ReqQryBrokerTradingAlgos(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcExchangeIDType exchangeID, TThostFtdcInstrumentIDType instrumentID)
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
//TDAPI_API int ReqParkedOrderInsert(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcParkedOrderField *ParkedOrder)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqParkedOrderInsert(ParkedOrder, requestID);
//}
////Ԥ�񳷵�¼������
//TDAPI_API int ReqParkedOrderAction(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcParkedOrderActionField *ParkedOrderAction)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqParkedOrderAction(ParkedOrderAction, requestID);
//}
////����ɾ��Ԥ��
//TDAPI_API int ReqRemoveParkedOrder(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcInvestorIDType investorID, TThostFtdcParkedOrderIDType parkedOrderID)
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
//TDAPI_API int ReqRemoveParkedOrderAction(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcInvestorIDType investorID, TThostFtdcParkedOrderActionIDType parkedOrderActionID)
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
//TDAPI_API int ReqQryTransferBank(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcBankIDType bankID, TThostFtdcBankBrchIDType bankBrchID)
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
//TDAPI_API int ReqQryTransferSerial(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcAccountIDType accountID, TThostFtdcBankIDType bankID)
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
//TDAPI_API int ReqQryAccountregister(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcAccountIDType accountID, TThostFtdcBankIDType bankID)
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
//TDAPI_API int ReqQryContractBank(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcBankIDType bankID, TThostFtdcBankBrchIDType bankBrchID)
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
//TDAPI_API int ReqQryParkedOrder(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcInvestorIDType investorID, TThostFtdcInstrumentIDType instrumentID, TThostFtdcExchangeIDType exchangeID)
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
//TDAPI_API int ReqQryParkedOrderAction(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcInvestorIDType investorID, TThostFtdcInstrumentIDType instrumentID, TThostFtdcExchangeIDType exchangeID)
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
//TDAPI_API int ReqQueryCFMMCTradingAccountToken(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcBrokerIDType brokerID, TThostFtdcInvestorIDType investorID)
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
//TDAPI_API int ReqFromBankToFutureByFuture(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcReqTransferField *reqTransfer)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqFromBankToFutureByFuture(reqTransfer, requestID);
//}
////�ڻ������ڻ��ʽ�ת��������
//TDAPI_API int ReqFromFutureToBankByFuture(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcReqTransferField *reqTransfer)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqFromFutureToBankByFuture(reqTransfer, requestID);
//}
////�ڻ������ѯ�����������
//TDAPI_API int ReqQueryBankAccountMoneyByFuture(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcReqQueryAccountField *reqQueryAccount)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqQueryBankAccountMoneyByFuture(reqQueryAccount, requestID);
//}
TDAPI_API int		ReqOrderInsert(CThostFtdcTraderApi* pApi, CThostFtdcInputOrderField* pInputOrder, int nRequestID)
{
	return pApi->ReqOrderInsert(pInputOrder, nRequestID);
}
///�����ѯ����
TDAPI_API int		ReqQryOrder(CThostFtdcTraderApi* pApi, CThostFtdcQryOrderField* pQryOrder, int nRequestID)
{
	return pApi->ReqQryOrder(pQryOrder, nRequestID);
}
///��ѯ��󱨵���������
TDAPI_API int		ReqQueryMaxOrderVolume(CThostFtdcTraderApi* pApi, CThostFtdcQueryMaxOrderVolumeField* pQueryMaxOrderVolume, int nRequestID)
{
	return pApi->ReqQueryMaxOrderVolume(pQueryMaxOrderVolume, nRequestID);
}
///������������
TDAPI_API int		ReqOrderAction(CThostFtdcTraderApi* pApi, CThostFtdcInputOrderActionField* pInputOrderAction, int nRequestID)
{
	return pApi->ReqOrderAction(pInputOrderAction, nRequestID);
}
///����������������
TDAPI_API int		ReqBatchOrderAction(CThostFtdcTraderApi* pApi, CThostFtdcInputBatchOrderActionField* pInputBatchOrderAction, int nRequestID)
{
	return pApi->ReqBatchOrderAction(pInputBatchOrderAction, nRequestID);
}

///Ԥ��¼������
TDAPI_API int		ReqParkedOrderInsert(CThostFtdcTraderApi* pApi, CThostFtdcParkedOrderField* pParkedOrder, int nRequestID)
{
	return pApi->ReqParkedOrderInsert(pParkedOrder, nRequestID);
}
///Ԥ�񳷵�¼������
TDAPI_API int		ReqParkedOrderAction(CThostFtdcTraderApi* pApi, CThostFtdcParkedOrderActionField* pParkedOrderAction, int nRequestID)
{
	return pApi->ReqParkedOrderAction(pParkedOrderAction, nRequestID);
}
///����ɾ��Ԥ��
TDAPI_API int		ReqRemoveParkedOrder(CThostFtdcTraderApi* pApi, CThostFtdcRemoveParkedOrderField* pRemoveParkedOrder, int nRequestID)
{
	return pApi->ReqRemoveParkedOrder(pRemoveParkedOrder, nRequestID);
}
///����ɾ��Ԥ�񳷵�
TDAPI_API int		ReqRemoveParkedOrderAction(CThostFtdcTraderApi* pApi, CThostFtdcRemoveParkedOrderActionField* pRemoveParkedOrderAction, int nRequestID)
{
	return pApi->ReqRemoveParkedOrderAction(pRemoveParkedOrderAction, nRequestID);
}
///�����ѯԤ��
TDAPI_API int		ReqQryParkedOrder(CThostFtdcTraderApi* pApi, CThostFtdcQryParkedOrderField* pQryParkedOrder, int nRequestID)
{
	return pApi->ReqQryParkedOrder(pQryParkedOrder, nRequestID);
}
///�����ѯԤ�񳷵�
TDAPI_API int		ReqQryParkedOrderAction(CThostFtdcTraderApi* pApi, CThostFtdcQryParkedOrderActionField* pQryParkedOrderAction, int nRequestID)
{
	return pApi->ReqQryParkedOrderAction(pQryParkedOrderAction, nRequestID);
}

///�����ѯ�ͻ�֪ͨ
TDAPI_API int		ReqQryNotice(CThostFtdcTraderApi* pApi, CThostFtdcQryNoticeField* pQryNotice, int nRequestID)
{
	return pApi->ReqQryNotice(pQryNotice, nRequestID);
}
///�����ѯ����֪ͨ
TDAPI_API int		ReqQryTradingNotice(CThostFtdcTraderApi* pApi, CThostFtdcQryTradingNoticeField* pQryTradingNotice, int nRequestID)
{
	return pApi->ReqQryTradingNotice(pQryTradingNotice, nRequestID);
}


///�����ѯִ������
TDAPI_API int		ReqQryExecOrder(CThostFtdcTraderApi* pApi, CThostFtdcQryExecOrderField* pQryExecOrder, int nRequestID)
{
	return pApi->ReqQryExecOrder(pQryExecOrder, nRequestID);
}
///ִ������¼������
TDAPI_API int		ReqExecOrderInsert(CThostFtdcTraderApi* pApi, CThostFtdcInputExecOrderField* pInputExecOrder, int nRequestID)
{
	return pApi->ReqExecOrderInsert(pInputExecOrder, nRequestID);
}
///ִ�������������
TDAPI_API int		ReqExecOrderAction(CThostFtdcTraderApi* pApi, CThostFtdcInputExecOrderActionField* pInputExecOrderAction, int nRequestID)
{
	return pApi->ReqExecOrderAction(pInputExecOrderAction, nRequestID);
}


///ѯ��¼������
TDAPI_API int		ReqForQuoteInsert(CThostFtdcTraderApi* pApi, CThostFtdcInputForQuoteField* pInputForQuote, int nRequestID)
{
	return pApi->ReqForQuoteInsert(pInputForQuote, nRequestID);

}
///����¼������
TDAPI_API int		ReqQuoteInsert(CThostFtdcTraderApi* pApi, CThostFtdcInputQuoteField* pInputQuote, int nRequestID)
{
	return pApi->ReqQuoteInsert(pInputQuote, nRequestID);
}
///���۲�������
TDAPI_API int		ReqQuoteAction(CThostFtdcTraderApi* pApi, CThostFtdcInputQuoteActionField* pInputQuoteAction, int nRequestID)
{
	return pApi->ReqQuoteAction(pInputQuoteAction, nRequestID);
}



///�������¼������
TDAPI_API int		ReqCombActionInsert(CThostFtdcTraderApi* pApi, CThostFtdcInputCombActionField* pInputCombAction, int nRequestID)
{
	return pApi->ReqCombActionInsert(pInputCombAction, nRequestID);
}
///�����ѯ��Ϻ�Լ��ȫϵ��
TDAPI_API int		ReqQryCombInstrumentGuard(CThostFtdcTraderApi* pApi, CThostFtdcQryCombInstrumentGuardField* pQryCombInstrumentGuard, int nRequestID)
{
	return pApi->ReqQryCombInstrumentGuard(pQryCombInstrumentGuard, nRequestID);
}
///�����ѯ�������
TDAPI_API int		ReqQryCombAction(CThostFtdcTraderApi* pApi, CThostFtdcQryCombActionField* pQryCombAction, int nRequestID)
{
	return pApi->ReqQryCombAction(pQryCombAction, nRequestID);
}


///�����ѯ�ɽ�
TDAPI_API int		ReqQryTrade(CThostFtdcTraderApi* pApi, CThostFtdcQryTradeField* pQryTrade, int nRequestID)
{
	return pApi->ReqQryTrade(pQryTrade, nRequestID);
}


///�����ѯͶ���ֲ߳�
TDAPI_API int		ReqQryInvestorPosition(CThostFtdcTraderApi* pApi, CThostFtdcQryInvestorPositionField* pQryInvestorPosition, int nRequestID)
{
	return pApi->ReqQryInvestorPosition(pQryInvestorPosition, nRequestID);
}
///�����ѯͶ���ֲ߳���ϸ
TDAPI_API int		ReqQryInvestorPositionDetail(CThostFtdcTraderApi* pApi, CThostFtdcQryInvestorPositionDetailField* pQryInvestorPositionDetail, int nRequestID)
{
	return pApi->ReqQryInvestorPositionDetail(pQryInvestorPositionDetail, nRequestID);
}
///�����ѯͶ���ֲ߳���ϸ
TDAPI_API int		ReqQryInvestorPositionCombineDetail(CThostFtdcTraderApi* pApi, CThostFtdcQryInvestorPositionCombineDetailField* pQryInvestorPositionCombineDetail, int nRequestID)
{
	return pApi->ReqQryInvestorPositionCombineDetail(pQryInvestorPositionCombineDetail, nRequestID);
}
///�����ѯ�ʽ��˻�
TDAPI_API int		ReqQryTradingAccount(CThostFtdcTraderApi* pApi, CThostFtdcQryTradingAccountField* pQryTradingAccount, int nRequestID)
{
	return pApi->ReqQryTradingAccount(pQryTradingAccount, nRequestID);
}
///�����ѯͶ����
TDAPI_API int		ReqQryInvestor(CThostFtdcTraderApi* pApi, CThostFtdcQryInvestorField* pQryInvestor, int nRequestID)
{
	return pApi->ReqQryInvestor(pQryInvestor, nRequestID);
}
///�����ѯ���ױ���
TDAPI_API int		ReqQryTradingCode(CThostFtdcTraderApi* pApi, CThostFtdcQryTradingCodeField* pQryTradingCode, int nRequestID)
{
	return pApi->ReqQryTradingCode(pQryTradingCode, nRequestID);
}
///�����ѯͶ���߽�����
TDAPI_API int		ReqQrySettlementInfo(CThostFtdcTraderApi* pApi, CThostFtdcQrySettlementInfoField* pQrySettlementInfo, int nRequestID)
{
	return pApi->ReqQrySettlementInfo(pQrySettlementInfo, nRequestID);
}
///�����ѯ������Ϣȷ��
TDAPI_API int		ReqQrySettlementInfoConfirm(CThostFtdcTraderApi* pApi, CThostFtdcQrySettlementInfoConfirmField* pQrySettlementInfoConfirm, int nRequestID)
{
	return pApi->ReqQrySettlementInfoConfirm(pQrySettlementInfoConfirm, nRequestID);
}
///Ͷ���߽�����ȷ��
TDAPI_API int		ReqSettlementInfoConfirm(CThostFtdcTraderApi* pApi, CThostFtdcSettlementInfoConfirmField* pSettlementInfoConfirm, int nRequestID)
{
	return pApi->ReqSettlementInfoConfirm(pSettlementInfoConfirm, nRequestID);
}


#pragma region ��Ʒ/��Լ/Instrument
///�����ѯ��Ʒ
TDAPI_API int		ReqQryProduct(CThostFtdcTraderApi* pApi, CThostFtdcQryProductField* pQryProduct, int nRequestID)
{
	return pApi->ReqQryProduct(pQryProduct, nRequestID);
}
///�����ѯ��Ʒ���ۻ���
TDAPI_API int		ReqQryProductExchRate(CThostFtdcTraderApi* pApi, CThostFtdcQryProductExchRateField* pQryProductExchRate, int nRequestID)
{
	return pApi->ReqQryProductExchRate(pQryProductExchRate, nRequestID);
}
///�����ѯ��Ʒ��
TDAPI_API int		ReqQryProductGroup(CThostFtdcTraderApi* pApi, CThostFtdcQryProductGroupField* pQryProductGroup, int nRequestID)
{
	return pApi->ReqQryProductGroup(pQryProductGroup, nRequestID);
}

///�����ѯ��Լ
TDAPI_API int		ReqQryInstrument(CThostFtdcTraderApi* pApi, CThostFtdcQryInstrumentField* pQryInstrument, int nRequestID)
{
	return pApi->ReqQryInstrument(pQryInstrument, nRequestID);
}
///�����ѯ��Լ��֤����
TDAPI_API int		ReqQryInstrumentMarginRate(CThostFtdcTraderApi* pApi, CThostFtdcQryInstrumentMarginRateField* pQryInstrumentMarginRate, int nRequestID)
{
	return pApi->ReqQryInstrumentMarginRate(pQryInstrumentMarginRate, nRequestID);
}
///�����ѯ��Լ��������
TDAPI_API int		ReqQryInstrumentCommissionRate(CThostFtdcTraderApi* pApi, CThostFtdcQryInstrumentCommissionRateField* pQryInstrumentCommissionRate, int nRequestID)
{
	return pApi->ReqQryInstrumentCommissionRate(pQryInstrumentCommissionRate, nRequestID);
}
#pragma endregion



///�����ѯѯ��
TDAPI_API int		ReqQryForQuote(CThostFtdcTraderApi* pApi, CThostFtdcQryForQuoteField* pQryForQuote, int nRequestID)
{
	return pApi->ReqQryForQuote(pQryForQuote, nRequestID);
}
///�����ѯ����
TDAPI_API int		ReqQryQuote(CThostFtdcTraderApi* pApi, CThostFtdcQryQuoteField* pQryQuote, int nRequestID)
{
	return pApi->ReqQryQuote(pQryQuote, nRequestID);
}
///�����ѯ����
TDAPI_API int		ReqQryDepthMarketData(CThostFtdcTraderApi* pApi, CThostFtdcQryDepthMarketDataField* pQryDepthMarketData, int nRequestID)
{
	return pApi->ReqQryDepthMarketData(pQryDepthMarketData, nRequestID);
}





///�����ѯ�ֵ��۵���Ϣ
TDAPI_API int		ReqQryEWarrantOffset(CThostFtdcTraderApi* pApi, CThostFtdcQryEWarrantOffsetField* pQryEWarrantOffset, int nRequestID)
{
	return pApi->ReqQryEWarrantOffset(pQryEWarrantOffset, nRequestID);
}

///�����ѯͶ����Ʒ��/��Ʒ�ֱ�֤��
TDAPI_API int		ReqQryInvestorProductGroupMargin(CThostFtdcTraderApi* pApi, CThostFtdcQryInvestorProductGroupMarginField* pQryInvestorProductGroupMargin, int nRequestID)
{
	return pApi->ReqQryInvestorProductGroupMargin(pQryInvestorProductGroupMargin, nRequestID);
}




///�����ѯ�����̺�Լ��������
TDAPI_API int		ReqQryMMInstrumentCommissionRate(CThostFtdcTraderApi* pApi, CThostFtdcQryMMInstrumentCommissionRateField* pQryMMInstrumentCommissionRate, int nRequestID)
{
	return pApi->ReqQryMMInstrumentCommissionRate(pQryMMInstrumentCommissionRate, nRequestID);
}
///�����ѯ��������Ȩ��Լ������
TDAPI_API int		ReqQryMMOptionInstrCommRate(CThostFtdcTraderApi* pApi, CThostFtdcQryMMOptionInstrCommRateField* pQryMMOptionInstrCommRate, int nRequestID)
{
	return pApi->ReqQryMMOptionInstrCommRate(pQryMMOptionInstrCommRate, nRequestID);
}

///�����ѯ����������
TDAPI_API int		ReqQryInstrumentOrderCommRate(CThostFtdcTraderApi* pApi, CThostFtdcQryInstrumentOrderCommRateField* pQryInstrumentOrderCommRate, int nRequestID)
{
	return pApi->ReqQryInstrumentOrderCommRate(pQryInstrumentOrderCommRate, nRequestID);
}


#pragma region ��������/sec agent
///�����ѯ�ʽ��˻�
TDAPI_API int		ReqQrySecAgentTradingAccount(CThostFtdcTraderApi* pApi, CThostFtdcQryTradingAccountField* pQryTradingAccount, int nRequestID)
{
	return pApi->ReqQrySecAgentTradingAccount(pQryTradingAccount, nRequestID);
}
///�����ѯ�����������Ա����Ȩ��
TDAPI_API int		ReqQrySecAgentACIDMap(CThostFtdcTraderApi* pApi, CThostFtdcQrySecAgentACIDMapField* pQrySecAgentACIDMap, int nRequestID)
{
	return pApi->ReqQrySecAgentACIDMap(pQrySecAgentACIDMap, nRequestID);
}
///�����ѯ�����������ʽ�У��ģʽ
TDAPI_API int		ReqQrySecAgentCheckMode(CThostFtdcTraderApi* pApi, CThostFtdcQrySecAgentCheckModeField* pQrySecAgentCheckMode, int nRequestID)
{
	return pApi->ReqQrySecAgentCheckMode(pQrySecAgentCheckMode, nRequestID);
}
///�����ѯ������������Ϣ
TDAPI_API int		ReqQrySecAgentTradeInfo(CThostFtdcTraderApi* pApi, CThostFtdcQrySecAgentTradeInfoField* pQrySecAgentTradeInfo, int nRequestID)
{
	return pApi->ReqQrySecAgentTradeInfo(pQrySecAgentTradeInfo, nRequestID);
}
#pragma endregion


#pragma region ��Ȩoption
///��Ȩ�ԶԳ�¼������
TDAPI_API int		ReqOptionSelfCloseInsert(CThostFtdcTraderApi* pApi, CThostFtdcInputOptionSelfCloseField* pInputOptionSelfClose, int nRequestID)
{
	return pApi->ReqOptionSelfCloseInsert(pInputOptionSelfClose, nRequestID);
}
///��Ȩ�ԶԳ��������
TDAPI_API int		ReqOptionSelfCloseAction(CThostFtdcTraderApi* pApi, CThostFtdcInputOptionSelfCloseActionField* pInputOptionSelfCloseAction, int nRequestID)
{
	return pApi->ReqOptionSelfCloseAction(pInputOptionSelfCloseAction, nRequestID);
}

///�����ѯ��Ȩ���׳ɱ�
TDAPI_API int		ReqQryOptionInstrTradeCost(CThostFtdcTraderApi* pApi, CThostFtdcQryOptionInstrTradeCostField* pQryOptionInstrTradeCost, int nRequestID)
{
	return pApi->ReqQryOptionInstrTradeCost(pQryOptionInstrTradeCost, nRequestID);
}
///�����ѯ��Ȩ��Լ������
TDAPI_API int		ReqQryOptionInstrCommRate(CThostFtdcTraderApi* pApi, CThostFtdcQryOptionInstrCommRateField* pQryOptionInstrCommRate, int nRequestID)
{
	return pApi->ReqQryOptionInstrCommRate(pQryOptionInstrCommRate, nRequestID);
}
///�����ѯ��Ȩ�ԶԳ�
TDAPI_API int		ReqQryOptionSelfClose(CThostFtdcTraderApi* pApi, CThostFtdcQryOptionSelfCloseField* pQryOptionSelfClose, int nRequestID)
{
	return pApi->ReqQryOptionSelfClose(pQryOptionSelfClose, nRequestID);
}
#pragma endregion




///�����ѯͶ�ʵ�Ԫ���ݲ�֧�ָù��ܣ�
TDAPI_API int		ReqQryInvestUnit(CThostFtdcTraderApi* pApi, CThostFtdcQryInvestUnitField* pQryInvestUnit, int nRequestID)
{
	return pApi->ReqQryInvestUnit(pQryInvestUnit, nRequestID);
}



#pragma region Banking
///�����ѯת������
TDAPI_API int		ReqQryTransferBank(CThostFtdcTraderApi* pApi, CThostFtdcQryTransferBankField* pQryTransferBank, int nRequestID)
{
	return pApi->ReqQryTransferBank(pQryTransferBank, nRequestID);
}
///�����ѯ����ǩԼ��ϵ
TDAPI_API int		ReqQryAccountregister(CThostFtdcTraderApi* pApi, CThostFtdcQryAccountregisterField* pQryAccountregister, int nRequestID)
{
	return pApi->ReqQryAccountregister(pQryAccountregister, nRequestID);
}
///�����ѯǩԼ����
TDAPI_API int		ReqQryContractBank(CThostFtdcTraderApi* pApi, CThostFtdcQryContractBankField* pQryContractBank, int nRequestID)
{
	return pApi->ReqQryContractBank(pQryContractBank, nRequestID);
}
///�����ѯת����ˮ
TDAPI_API int		ReqQryTransferSerial(CThostFtdcTraderApi* pApi, CThostFtdcQryTransferSerialField* pQryTransferSerial, int nRequestID)
{
	return pApi->ReqQryTransferSerial(pQryTransferSerial, nRequestID);
}
///�ڻ������ѯ�����������
TDAPI_API int		ReqQueryBankAccountMoneyByFuture(CThostFtdcTraderApi* pApi, CThostFtdcReqQueryAccountField* pReqQueryAccount, int nRequestID)
{
	return pApi->ReqQueryBankAccountMoneyByFuture(pReqQueryAccount, nRequestID);
}

///�ڻ����������ʽ�ת�ڻ�����
TDAPI_API int		ReqFromBankToFutureByFuture(CThostFtdcTraderApi* pApi, CThostFtdcReqTransferField* pReqTransfer, int nRequestID)
{
	return pApi->ReqFromBankToFutureByFuture(pReqTransfer, nRequestID);
}
///�ڻ������ڻ��ʽ�ת��������
TDAPI_API int		ReqFromFutureToBankByFuture(CThostFtdcTraderApi* pApi, CThostFtdcReqTransferField* pReqTransfer, int nRequestID)
{
	return pApi->ReqFromFutureToBankByFuture(pReqTransfer, nRequestID);
}
#pragma endregion


#pragma region Exchange/������
///�����ѯ������
TDAPI_API int		ReqQryExchange(CThostFtdcTraderApi* pApi, CThostFtdcQryExchangeField* pQryExchange, int nRequestID)
{
	return pApi->ReqQryExchange(pQryExchange, nRequestID);
}
///�����ѯ��������֤����
TDAPI_API int		ReqQryExchangeMarginRate(CThostFtdcTraderApi* pApi, CThostFtdcQryExchangeMarginRateField* pQryExchangeMarginRate, int nRequestID)
{
	return pApi->ReqQryExchangeMarginRate(pQryExchangeMarginRate, nRequestID);
}
///�����ѯ������������֤����
TDAPI_API int		ReqQryExchangeMarginRateAdjust(CThostFtdcTraderApi* pApi, CThostFtdcQryExchangeMarginRateAdjustField* pQryExchangeMarginRateAdjust, int nRequestID)
{
	return pApi->ReqQryExchangeMarginRateAdjust(pQryExchangeMarginRateAdjust, nRequestID);
}
///�����ѯ����
TDAPI_API int		ReqQryExchangeRate(CThostFtdcTraderApi* pApi, CThostFtdcQryExchangeRateField* pQryExchangeRate, int nRequestID)
{
	return pApi->ReqQryExchangeRate(pQryExchangeRate, nRequestID);
}
#pragma endregion


#pragma region Broker
///�����ѯ���͹�˾���ײ���
TDAPI_API int		ReqQryBrokerTradingParams(CThostFtdcTraderApi* pApi, CThostFtdcQryBrokerTradingParamsField* pQryBrokerTradingParams, int nRequestID)
{
	return pApi->ReqQryBrokerTradingParams(pQryBrokerTradingParams, nRequestID);
}
///�����ѯ���͹�˾�����㷨
TDAPI_API int		ReqQryBrokerTradingAlgos(CThostFtdcTraderApi* pApi, CThostFtdcQryBrokerTradingAlgosField* pQryBrokerTradingAlgos, int nRequestID)
{
	return pApi->ReqQryBrokerTradingAlgos(pQryBrokerTradingAlgos, nRequestID);
}
#pragma endregion

#pragma region CFMMC
///�����ѯ��������û�����
TDAPI_API int		ReqQueryCFMMCTradingAccountToken(CThostFtdcTraderApi* pApi, CThostFtdcQueryCFMMCTradingAccountTokenField* pQueryCFMMCTradingAccountToken, int nRequestID)
{
	return pApi->ReqQueryCFMMCTradingAccountToken(pQueryCFMMCTradingAccountToken, nRequestID);
}

///�����ѯ��֤����ϵͳ���͹�˾�ʽ��˻���Կ
TDAPI_API int		ReqQryCFMMCTradingAccountKey(CThostFtdcTraderApi* pApi, CThostFtdcQryCFMMCTradingAccountKeyField* pQryCFMMCTradingAccountKey, int nRequestID)
{
	return pApi->ReqQryCFMMCTradingAccountKey(pQryCFMMCTradingAccountKey, nRequestID);
}
#pragma endregion


#pragma endregion

#pragma region �ص�����
//========================================
//==================================== �ص����� =======================================

TDAPI_API void   RegOnRspFrontConnected(TraderSpi* pSpi, CBOnRspFrontConnected cb)		//���ͻ����뽻�׺�̨������ͨ������ʱ����δ��¼ǰ�����÷��������á�
{
	pSpi->cbOnFrontConnected = cb;
}

TDAPI_API void   RegOnRspFrontDisconnected(TraderSpi* pSpi, CBOnRspFrontDisconnected cb)		//���ͻ����뽻�׺�̨ͨ�����ӶϿ�ʱ���÷��������á���������������API���Զ��������ӣ��ͻ��˿ɲ�������
{
	pSpi->cbOnFrontDisconnected = cb;
}

TDAPI_API void   RegOnHeartBeatWarning(TraderSpi* pSpi, CBOnHeartBeatWarning cb)		//������ʱ���档����ʱ��δ�յ�����ʱ���÷��������á�
{
	pSpi->cbOnHeartBeatWarning = cb;
}

TDAPI_API void   RegOnRspAuthenticate(TraderSpi* pSpi, CBOnRspAuthenticate cb)
{
	pSpi->cbOnRspAuthenticate = cb;
}

TDAPI_API void   RegOnRspUserLogin(TraderSpi* pSpi, CBOnRspUserLogin cb)	//��¼������Ӧ
{
	pSpi->cbOnRspUserLogin = cb;
}
TDAPI_API void   RegOnRspUserLogout(TraderSpi* pSpi, CBOnRspUserLogout cb)	//�ǳ�������Ӧ
{
	pSpi->cbOnRspUserLogout = cb;
}
TDAPI_API void   RegRspUserPasswordUpdate(TraderSpi* pSpi, CBRspUserPasswordUpdate cb)	//�û��������������Ӧ
{
	pSpi->cbRspUserPasswordUpdate = cb;
}
TDAPI_API void   RegRspTradingAccountPasswordUpdate(TraderSpi* pSpi, CBRspTradingAccountPasswordUpdate cb)	//�ʽ��˻��������������Ӧ
{
	pSpi->cbRspTradingAccountPasswordUpdate = cb;
}
TDAPI_API void   RegRspUserAuthMethod(TraderSpi* pSpi, CBRspUserAuthMethod cb)	//��ѯ�û���ǰ֧�ֵ���֤ģʽ�Ļظ�
{
	pSpi->cbRspUserAuthMethod = cb;
}
TDAPI_API void   RegRspGenUserCaptcha(TraderSpi* pSpi, CBRspGenUserCaptcha cb)	//��ȡͼ����֤������Ļظ�
{
	pSpi->cbRspGenUserCaptcha = cb;
}
TDAPI_API void   RegRspGenUserText(TraderSpi* pSpi, CBRspGenUserText cb)	//��ȡ������֤������Ļظ�
{
	pSpi->cbRspGenUserText = cb;
}
TDAPI_API void   RegOnRspOrderInsert(TraderSpi* pSpi, CBOnRspOrderInsert cb)	//����¼��������Ӧ
{
	pSpi->cbRspOrderInsert = cb;
}
TDAPI_API void   RegRspParkedOrderInsert(TraderSpi* pSpi, CBRspParkedOrderInsert cb)	//Ԥ��¼��������Ӧ
{
	pSpi->cbRspParkedOrderInsert = cb;
}
TDAPI_API void   RegRspParkedOrderAction(TraderSpi* pSpi, CBRspParkedOrderAction cb)	//Ԥ�񳷵�¼��������Ӧ
{
	pSpi->cbRspParkedOrderAction = cb;
}
TDAPI_API void   RegRspOrderAction(TraderSpi* pSpi, CBRspOrderAction cb)	//��������������Ӧ
{
	pSpi->cbRspOrderAction = cb;
}
TDAPI_API void   RegRspQueryMaxOrderVolume(TraderSpi* pSpi, CBRspQueryMaxOrderVolume cb)	//��ѯ��󱨵�������Ӧ
{
	pSpi->cbRspQueryMaxOrderVolume = cb;
}
TDAPI_API void   RegOnRspSettlementInfoConfirm(TraderSpi* pSpi, CBOnRspSettlementInfoConfirm cb)	//Ͷ���߽�����ȷ����Ӧ
{
	pSpi->cbRspSettlementInfoConfirm = cb;
}
TDAPI_API void   RegRspRemoveParkedOrder(TraderSpi* pSpi, CBRspRemoveParkedOrder cb)	//ɾ��Ԥ����Ӧ
{
	pSpi->cbRspRemoveParkedOrder = cb;
}
TDAPI_API void   RegRspRemoveParkedOrderAction(TraderSpi* pSpi, CBRspRemoveParkedOrderAction cb)	//ɾ��Ԥ�񳷵���Ӧ
{
	pSpi->cbRspRemoveParkedOrderAction = cb;
}
TDAPI_API void   RegBatchOrderAction(TraderSpi* pSpi, CBRspBatchOrderAction cb)	//������������������Ӧ
{
	pSpi->cbRspBatchOrderAction = cb;
}
TDAPI_API void   RegCombActionInsert(TraderSpi* pSpi, CBRspCombActionInsert cb)	//�������¼��������Ӧ
{
	pSpi->cbRspCombActionInsert = cb;
}
TDAPI_API void   RegOnRspQryOrder(TraderSpi* pSpi, CBOnRspQryOrder cb)	//�����ѯ������Ӧ
{
	pSpi->cbRspQryOrder = cb;
}
TDAPI_API void   RegOnRspQryTrade(TraderSpi* pSpi, CBOnRspQryTrade cb)	//�����ѯ�ɽ���Ӧ
{
	pSpi->cbRspQryTrade = cb;
}
TDAPI_API void   RegOnRspQryInvestorPosition(TraderSpi* pSpi, CBOnRspQryInvestorPosition cb)	//�����ѯͶ���ֲ߳���Ӧ
{
	pSpi->cbRspQryInvestorPosition = cb;
}
TDAPI_API void   RegOnRspQryTradingAccount(TraderSpi* pSpi, CBOnRspQryTradingAccount cb)	//�����ѯ�ʽ��˻���Ӧ
{
	pSpi->cbRspQryTradingAccount = cb;
}
TDAPI_API void   RegRspQryInvestor(TraderSpi* pSpi, CBRspQryInvestor cb)	//�����ѯͶ������Ӧ
{
	pSpi->cbRspQryInvestor = cb;
}
TDAPI_API void   RegRspQryTradingCode(TraderSpi* pSpi, CBRspQryTradingCode cb)	//�����ѯ���ױ�����Ӧ
{
	pSpi->cbRspQryTradingCode = cb;
}
TDAPI_API void   RegRspQryInstrumentMarginRate(TraderSpi* pSpi, CBRspQryInstrumentMarginRate cb)	//�����ѯ��Լ��֤������Ӧ
{
	pSpi->cbRspQryInstrumentMarginRate = cb;
}
TDAPI_API void   RegRspQryInstrumentCommissionRate(TraderSpi* pSpi, CBRspQryInstrumentCommissionRate cb)	//�����ѯ��Լ����������Ӧ
{
	pSpi->cbRspQryInstrumentCommissionRate = cb;
}
TDAPI_API void   RegRspQryExchange(TraderSpi* pSpi, CBRspQryExchange cb)	//�����ѯ��������Ӧ
{
	pSpi->cbRspQryExchange = cb;
}
TDAPI_API void   RegOnRspQryInstrument(TraderSpi* pSpi, CBOnRspQryInstrument cb)	//�����ѯ��Լ��Ӧ
{
	pSpi->cbRspQryInstrument = cb;
}
TDAPI_API void   RegRspQryDepthMarketData(TraderSpi* pSpi, CBRspQryDepthMarketData cb)	//�����ѯ������Ӧ
{
	pSpi->cbRspQryDepthMarketData = cb;
}
TDAPI_API void   RegRspQrySettlementInfo(TraderSpi* pSpi, CBRspQrySettlementInfo cb)	//�����ѯͶ���߽�������Ӧ
{
	pSpi->cbRspQrySettlementInfo = cb;
}
TDAPI_API void   RegRspQryTransferBank(TraderSpi* pSpi, CBRspQryTransferBank cb)	//�����ѯת��������Ӧ
{
	pSpi->cbRspQryTransferBank = cb;
}
TDAPI_API void   RegRspQryInvestorPositionDetail(TraderSpi* pSpi, CBRspQryInvestorPositionDetail cb)	//�����ѯͶ���ֲ߳���ϸ��Ӧ
{
	pSpi->cbRspQryInvestorPositionDetail = cb;
}
TDAPI_API void   RegRspQryNotice(TraderSpi* pSpi, CBRspQryNotice cb)	//�����ѯ�ͻ�֪ͨ��Ӧ
{
	pSpi->cbRspQryNotice = cb;
}
TDAPI_API void   RegRspQrySettlementInfoConfirm(TraderSpi* pSpi, CBRspQrySettlementInfoConfirm cb)	//�����ѯ������Ϣȷ����Ӧ
{
	pSpi->cbRspQrySettlementInfoConfirm = cb;
}
TDAPI_API void   RegRspQryInvestorPositionCombineDetail(TraderSpi* pSpi, CBRspQryInvestorPositionCombineDetail cb)	//�����ѯͶ���ֲ߳���ϸ��Ӧ
{
	pSpi->cbRspQryInvestorPositionCombineDetail = cb;
}
TDAPI_API void   RegRspQryCFMMCTradingAccountKey(TraderSpi* pSpi, CBRspQryCFMMCTradingAccountKey cb)	//��ѯ��֤����ϵͳ���͹�˾�ʽ��˻���Կ��Ӧ
{
	pSpi->cbRspQryCFMMCTradingAccountKey = cb;
}
TDAPI_API void   RegRspQryEWarrantOffset(TraderSpi* pSpi, CBRspQryEWarrantOffset cb)	//�����ѯ�ֵ��۵���Ϣ
{
	pSpi->cbRspQryEWarrantOffset = cb;
}
TDAPI_API void   RegRspQryInvestorProductGroupMargin(TraderSpi* pSpi, CBRspQryInvestorProductGroupMargin cb)	//�����ѯͶ����Ʒ��/��Ʒ�ֱ�֤��
{
	pSpi->cbRspQryInvestorProductGroupMargin = cb;
}
TDAPI_API void   RegRspQryExchangeMarginRate(TraderSpi* pSpi, CBRspQryExchangeMarginRate cb)	//�����ѯ��������֤����
{
	pSpi->cbRspQryExchangeMarginRate = cb;
}
TDAPI_API void   RegRspQryExchangeMarginRateAdjust(TraderSpi* pSpi, CBRspQryExchangeMarginRateAdjust cb)	//�����ѯ������������֤����
{
	pSpi->cbRspQryExchangeMarginRateAdjust = cb;
}
TDAPI_API void   RegRspQryExchangeRate(TraderSpi* pSpi, CBRspQryExchangeRate cb)	//�����ѯ������Ӧ
{
	pSpi->cbRspQryExchangeRate = cb;
}
TDAPI_API void   RegRspQrySecAgentACIDMap(TraderSpi* pSpi, CBRspQrySecAgentACIDMap cb)	//�����ѯ�����������Ա����Ȩ����Ӧ
{
	pSpi->cbRspQrySecAgentACIDMap = cb;
}
TDAPI_API void   RegRspQryProductExchRate(TraderSpi* pSpi, CBRspQryProductExchRate cb)	//�����ѯ��Ʒ���ۻ���
{
	pSpi->cbRspQryProductExchRate = cb;
}
TDAPI_API void   RegRspQryProductGroup(TraderSpi* pSpi, CBRspQryProductGroup cb)	//�����ѯ��Ʒ��
{
	pSpi->cbRspQryProductGroup = cb;
}
TDAPI_API void   RegRspQryMMInstrumentCommissionRate(TraderSpi* pSpi, CBRspQryMMInstrumentCommissionRate cb)	//�����ѯ�����̺�Լ����������Ӧ
{
	pSpi->cbRspQryMMInstrumentCommissionRate = cb;
}
TDAPI_API void   RegRspQryMMOptionInstrCommRate(TraderSpi* pSpi, CBRspQryMMOptionInstrCommRate cb)	//�����ѯ��������Ȩ��Լ��������Ӧ
{
	pSpi->cbRspQryMMOptionInstrCommRate = cb;
}
TDAPI_API void   RegRspQryInstrumentOrderCommRate(TraderSpi* pSpi, CBRspQryInstrumentOrderCommRate cb)	//�����ѯ������������Ӧ
{
	pSpi->cbRspQryInstrumentOrderCommRate = cb;
}
TDAPI_API void   RegRspQrySecAgentTradingAccount(TraderSpi* pSpi, CBRspQrySecAgentTradingAccount cb)	//�����ѯ�ʽ��˻���Ӧ
{
	pSpi->cbRspQrySecAgentTradingAccount = cb;
}
TDAPI_API void   RegRspQrySecAgentCheckMode(TraderSpi* pSpi, CBRspQrySecAgentCheckMode cb)	//�����ѯ�����������ʽ�У��ģʽ��Ӧ
{
	pSpi->cbRspQrySecAgentCheckMode = cb;
}
TDAPI_API void   RegRspQrySecAgentTradeInfo(TraderSpi* pSpi, CBRspQrySecAgentTradeInfo cb)	//�����ѯ������������Ϣ��Ӧ
{
	pSpi->cbRspQrySecAgentTradeInfo = cb;
}
TDAPI_API void   RegRspQryOptionInstrTradeCost(TraderSpi* pSpi, CBRspQryOptionInstrTradeCost cb)	//�����ѯ��Ȩ���׳ɱ���Ӧ
{
	pSpi->cbRspQryOptionInstrTradeCost = cb;
}
TDAPI_API void   RegRspQryOptionInstrCommRate(TraderSpi* pSpi, CBRspQryOptionInstrCommRate cb)	//�����ѯ��Ȩ��Լ��������Ӧ
{
	pSpi->cbRspQryOptionInstrCommRate = cb;
}
TDAPI_API void   RegRspQryExecOrder(TraderSpi* pSpi, CBRspQryExecOrder cb)	//�����ѯִ��������Ӧ
{
	pSpi->cbRspQryExecOrder = cb;
}
TDAPI_API void   RegRspQryForQuote(TraderSpi* pSpi, CBRspQryForQuote cb)	//�����ѯѯ����Ӧ
{
	pSpi->cbRspQryForQuote = cb;
}
TDAPI_API void   RegRspQryQuote(TraderSpi* pSpi, CBRspQryQuote cb)	//�����ѯ������Ӧ
{
	pSpi->cbRspQryQuote = cb;
}
TDAPI_API void   RegRspQryOptionSelfClose(TraderSpi* pSpi, CBRspQryOptionSelfClose cb)	//�����ѯ��Ȩ�ԶԳ���Ӧ
{
	pSpi->cbRspQryOptionSelfClose = cb;
}
TDAPI_API void   RegRspQryInvestUnit(TraderSpi* pSpi, CBRspQryInvestUnit cb)	//�����ѯͶ�ʵ�Ԫ��Ӧ
{
	pSpi->cbRspQryInvestUnit = cb;
}
TDAPI_API void   RegRspQryCombInstrumentGuard(TraderSpi* pSpi, CBRspQryCombInstrumentGuard cb)	//�����ѯ��Ϻ�Լ��ȫϵ����Ӧ
{
	pSpi->cbRspQryCombInstrumentGuard = cb;
}
TDAPI_API void   RegRspQryCombAction(TraderSpi* pSpi, CBRspQryCombAction cb)	//�����ѯ���������Ӧ
{
	pSpi->cbRspQryCombAction = cb;
}
TDAPI_API void   RegRspQryTransferSerial(TraderSpi* pSpi, CBRspQryTransferSerial cb)	//�����ѯת����ˮ��Ӧ
{
	pSpi->cbRspQryTransferSerial = cb;
}
TDAPI_API void   RegOnRspQryAccountregister(TraderSpi* pSpi, CBOnRspQryAccountregister cb)	//�����ѯ����ǩԼ��ϵ��Ӧ
{
	pSpi->cbRspQryAccountregister = cb;
}
TDAPI_API void   RegOnRspError(TraderSpi* pSpi, CBOnRspError cb)	//����Ӧ��
{
	pSpi->cbRspError = cb;
}
TDAPI_API void   RegOnRtnOrder(TraderSpi* pSpi, CBOnRtnOrder cb)	//����֪ͨ
{
	pSpi->cbRtnOrder = cb;
}
TDAPI_API void   RegOnRtnTrade(TraderSpi* pSpi, CBOnRtnTrade cb)	//�ɽ�֪ͨ
{
	pSpi->cbRtnTrade = cb;
}
TDAPI_API void   RegErrRtnOrderInsert(TraderSpi* pSpi, CBErrRtnOrderInsert cb)	//����¼�����ر�
{
	pSpi->cbErrRtnOrderInsert = cb;
}
TDAPI_API void   RegErrRtnOrderAction(TraderSpi* pSpi, CBErrRtnOrderAction cb)	//������������ر�
{
	pSpi->cbErrRtnOrderAction = cb;
}
TDAPI_API void   RegRtnInstrumentStatus(TraderSpi* pSpi, CBRtnInstrumentStatus cb)	//��Լ����״̬֪ͨ
{
	pSpi->cbRtnInstrumentStatus = cb;
}
TDAPI_API void   RegRtnTradingNotice(TraderSpi* pSpi, CBRtnTradingNotice cb)	//����֪ͨ
{
	pSpi->cbRtnTradingNotice = cb;
}
TDAPI_API void   RegRtnErrorConditionalOrder(TraderSpi* pSpi, CBRtnErrorConditionalOrder cb)	//��ʾ������У�����
{
	pSpi->cbRtnErrorConditionalOrder = cb;
}
TDAPI_API void   RegRspQryContractBank(TraderSpi* pSpi, CBRspQryContractBank cb)	//�����ѯǩԼ������Ӧ
{
	pSpi->cbRspQryContractBank = cb;
}
TDAPI_API void   RegRspQryParkedOrder(TraderSpi* pSpi, CBRspQryParkedOrder cb)	//�����ѯԤ����Ӧ
{
	pSpi->cbRspQryParkedOrder = cb;
}
TDAPI_API void   RegRspQryParkedOrderAction(TraderSpi* pSpi, CBRspQryParkedOrderAction cb)	//�����ѯԤ�񳷵���Ӧ
{
	pSpi->cbRspQryParkedOrderAction = cb;
}
TDAPI_API void   RegRspQryTradingNotice(TraderSpi* pSpi, CBRspQryTradingNotice cb)	//�����ѯ����֪ͨ��Ӧ
{
	pSpi->cbRspQryTradingNotice = cb;
}
TDAPI_API void   RegRspQryBrokerTradingParams(TraderSpi* pSpi, CBRspQryBrokerTradingParams cb)	//�����ѯ���͹�˾���ײ�����Ӧ
{
	pSpi->cbRspQryBrokerTradingParams = cb;
}
TDAPI_API void   RegRspQryBrokerTradingAlgos(TraderSpi* pSpi, CBRspQryBrokerTradingAlgos cb)	//�����ѯ���͹�˾�����㷨��Ӧ
{
	pSpi->cbRspQryBrokerTradingAlgos = cb;
}
TDAPI_API void   RegRtnFromBankToFutureByBank(TraderSpi* pSpi, CBRtnFromBankToFutureByBank cb)	//���з��������ʽ�ת�ڻ�֪ͨ
{
	pSpi->cbRtnFromBankToFutureByBank = cb;
}
TDAPI_API void   RegRtnFromFutureToBankByBank(TraderSpi* pSpi, CBRtnFromFutureToBankByBank cb)	//���з����ڻ��ʽ�ת����֪ͨ
{
	pSpi->cbRtnFromFutureToBankByBank = cb;
}
TDAPI_API void   RegRtnRepealFromBankToFutureByBank(TraderSpi* pSpi, CBRtnRepealFromBankToFutureByBank cb)	//���з����������ת�ڻ�֪ͨ
{
	pSpi->cbRtnRepealFromBankToFutureByBank = cb;
}
TDAPI_API void   RegRtnRepealFromFutureToBankByBank(TraderSpi* pSpi, CBRtnRepealFromFutureToBankByBank cb)	//���з�������ڻ�ת����֪ͨ
{
	pSpi->cbRtnRepealFromFutureToBankByBank = cb;
}
TDAPI_API void   RegRtnFromBankToFutureByFuture(TraderSpi* pSpi, CBRtnFromBankToFutureByFuture cb)	//�ڻ����������ʽ�ת�ڻ�֪ͨ
{
	pSpi->cbRtnFromBankToFutureByFuture = cb;
}
TDAPI_API void   RegRtnFromFutureToBankByFuture(TraderSpi* pSpi, CBRtnFromFutureToBankByFuture cb)	//�ڻ������ڻ��ʽ�ת����֪ͨ
{
	pSpi->cbRtnFromFutureToBankByFuture = cb;
}
TDAPI_API void   RegRtnRepealFromBankToFutureByFutureManual(TraderSpi* pSpi, CBRtnRepealFromBankToFutureByFutureManual cb)	//ϵͳ����ʱ�ڻ����ֹ������������ת�ڻ��������д�����Ϻ��̷��ص�֪ͨ
{
	pSpi->cbRtnRepealFromBankToFutureByFutureManual = cb;
}
TDAPI_API void   RegRtnRepealFromFutureToBankByFutureManual(TraderSpi* pSpi, CBRtnRepealFromFutureToBankByFutureManual cb)	//ϵͳ����ʱ�ڻ����ֹ���������ڻ�ת�����������д�����Ϻ��̷��ص�֪ͨ
{
	pSpi->cbRtnRepealFromFutureToBankByFutureManual = cb;
}
TDAPI_API void   RegRtnQueryBankBalanceByFuture(TraderSpi* pSpi, CBRtnQueryBankBalanceByFuture cb)	//�ڻ������ѯ�������֪ͨ
{
	pSpi->cbRtnQueryBankBalanceByFuture = cb;
}
TDAPI_API void   RegErrRtnBankToFutureByFuture(TraderSpi* pSpi, CBErrRtnBankToFutureByFuture cb)	//�ڻ����������ʽ�ת�ڻ�����ر�
{
	pSpi->cbErrRtnBankToFutureByFuture = cb;
}
TDAPI_API void   RegErrRtnFutureToBankByFuture(TraderSpi* pSpi, CBErrRtnFutureToBankByFuture cb)	//�ڻ������ڻ��ʽ�ת���д���ر�
{
	pSpi->cbErrRtnFutureToBankByFuture = cb;
}
TDAPI_API void   RegErrRtnRepealBankToFutureByFutureManual(TraderSpi* pSpi, CBErrRtnRepealBankToFutureByFutureManual cb)	//ϵͳ����ʱ�ڻ����ֹ������������ת�ڻ�����ر�
{
	pSpi->cbErrRtnRepealBankToFutureByFutureManual = cb;
}
TDAPI_API void   RegErrRtnRepealFutureToBankByFutureManual(TraderSpi* pSpi, CBErrRtnRepealFutureToBankByFutureManual cb)	//ϵͳ����ʱ�ڻ����ֹ���������ڻ�ת���д���ر�
{
	pSpi->cbErrRtnRepealFutureToBankByFutureManual = cb;
}
TDAPI_API void   RegErrRtnQueryBankBalanceByFuture(TraderSpi* pSpi, CBErrRtnQueryBankBalanceByFuture cb)	//�ڻ������ѯ����������ر�
{
	pSpi->cbErrRtnQueryBankBalanceByFuture = cb;
}
TDAPI_API void   RegRtnRepealFromBankToFutureByFuture(TraderSpi* pSpi, CBRtnRepealFromBankToFutureByFuture cb)	//�ڻ������������ת�ڻ��������д�����Ϻ��̷��ص�֪ͨ
{
	pSpi->cbRtnRepealFromBankToFutureByFuture = cb;
}
TDAPI_API void   RegRtnRepealFromFutureToBankByFuture(TraderSpi* pSpi, CBRtnRepealFromFutureToBankByFuture cb)	//�ڻ���������ڻ�ת�����������д�����Ϻ��̷��ص�֪ͨ
{
	pSpi->cbRtnRepealFromFutureToBankByFuture = cb;
}
TDAPI_API void   RegRspFromBankToFutureByFuture(TraderSpi* pSpi, CBRspFromBankToFutureByFuture cb)	//�ڻ����������ʽ�ת�ڻ�Ӧ��
{
	pSpi->cbRspFromBankToFutureByFuture = cb;
}
TDAPI_API void   RegRspFromFutureToBankByFuture(TraderSpi* pSpi, CBRspFromFutureToBankByFuture cb)	//�ڻ������ڻ��ʽ�ת����Ӧ��
{
	pSpi->cbRspFromFutureToBankByFuture = cb;
}
TDAPI_API void   RegRspQueryBankAccountMoneyByFuture(TraderSpi* pSpi, CBRspQueryBankAccountMoneyByFuture cb)	//�ڻ������ѯ�������Ӧ��
{
	pSpi->cbRspQueryBankAccountMoneyByFuture = cb;
}
TDAPI_API void   RegRspQueryCFMMCTradingAccountToken(TraderSpi* pSpi, CBRspQueryCFMMCTradingAccountToken cb)	//��ѯ��������û�����Ӧ��
{
	pSpi->cbRspQueryCFMMCTradingAccountToken = cb;
}
TDAPI_API void   RegRtnCFMMCTradingAccountToken(TraderSpi* pSpi, CBRtnCFMMCTradingAccountToken cb)	//��ѯ��������û�����֪ͨ
{
	pSpi->cbRtnCFMMCTradingAccountToken = cb;
}



