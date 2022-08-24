#include "pch.h"
#include "TdApi.h"

#include <filesystem>
using namespace std;


TDAPI_API CThostFtdcTraderApi* CreateFtdcTraderApi(const char* pszFlowPath)
{
	filesystem::path p(pszFlowPath);
	if (!filesystem::exists(pszFlowPath))
		filesystem::create_directory(p);

	// 初始化UserApi
	CThostFtdcTraderApi* pApi = CThostFtdcTraderApi::CreateFtdcTraderApi(pszFlowPath);			// 创建UserApi	
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


//获取接口版本
TDAPI_API const char* GetApiVersion()
{
	return CThostFtdcTraderApi::GetApiVersion();
}

////连接
//TDAPI_API CThostFtdcTraderApi* Connect(char *frontAddr, char *pszFlowPath, TraderSpi* pSpi)
//{
//	// 初始化UserApi
//	CThostFtdcTraderApi* pApi = CThostFtdcTraderApi::CreateFtdcTraderApi(pszFlowPath);			// 创建UserApi	
//																									//CTraderSpi* pSpi = new CTraderSpi();
//	pApi->RegisterSpi((CThostFtdcTraderSpi*)pSpi);			// 注册事件类
//	pApi->SubscribePublicTopic(THOST_TERT_QUICK/*THOST_TERT_RESTART*/);					// 注册公有流
//	pApi->SubscribePrivateTopic(THOST_TERT_QUICK/*THOST_TERT_RESTART*/);					// 注册私有流
//	pApi->RegisterFront(frontAddr);							// connect
//	pApi->Init();
//	//pApi->Join();
//	return pApi;
//}

////断开
//TDAPI_API void DisConnect(CThostFtdcTraderApi* pApi)
//{
//	if (pApi == NULL) return;
//
//	pApi->RegisterSpi(NULL);
//	pApi->Release();
//	pApi = NULL;
//}

///删除接口对象本身
///@remark 不再使用本接口对象时,调用该函数删除接口对象
TDAPI_API void Release(CThostFtdcTraderApi* api)
{
	api->Release();
}

///初始化
///@remark 初始化运行环境,只有调用后,接口才开始工作
TDAPI_API void Init(CThostFtdcTraderApi* api)
{
	api->Init();
}

///等待接口线程结束运行
///@return 线程退出代码
TDAPI_API int Join(CThostFtdcTraderApi* api)
{
	return api->Join();
}

//获取交易日
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

///注册名字服务器用户信息
///@param pFensUserInfo：用户信息。
TDAPI_API void		RegisterFensUserInfo(CThostFtdcTraderApi* pApi, CThostFtdcFensUserInfoField* pFensUserInfo)
{
	pApi->RegisterFensUserInfo(pFensUserInfo);
}

TDAPI_API void		SubscribePrivateTopic(CThostFtdcTraderApi* pApi, THOST_TE_RESUME_TYPE nResumeType)
{
	pApi->SubscribePrivateTopic(nResumeType);
}

///订阅公共流。
///@param nResumeType 公共流重传方式  
///        THOST_TERT_RESTART:从本交易日开始重传
///        THOST_TERT_RESUME:从上次收到的续传
///        THOST_TERT_QUICK:只传送登录后公共流的内容
///@remark 该方法要在Init方法前调用。若不调用则不会收到公共流的数据。
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

////客户端认证请求
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

////发送用户登录请求
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
////发送登出请求
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

///资金账户口令更新请求
TDAPI_API int		ReqTradingAccountPasswordUpdate(CThostFtdcTraderApi* pApi, CThostFtdcTradingAccountPasswordUpdateField* pTradingAccountPasswordUpdate, int nRequestID)
{
	return pApi->ReqTradingAccountPasswordUpdate(pTradingAccountPasswordUpdate, nRequestID);
}

///查询用户当前支持的认证模式（该功能暂不支持）
TDAPI_API int		ReqUserAuthMethod(CThostFtdcTraderApi* pApi, CThostFtdcReqUserAuthMethodField* pReqUserAuthMethod, int nRequestID)
{
	return pApi->ReqUserAuthMethod(pReqUserAuthMethod, nRequestID);
}

///用户发出获取图形验证码请求（该功能暂不支持）
TDAPI_API int		ReqGenUserCaptcha(CThostFtdcTraderApi* pApi, CThostFtdcReqGenUserCaptchaField* pReqGenUserCaptcha, int	nRequestID)
{
	return pApi->ReqGenUserCaptcha(pReqGenUserCaptcha, nRequestID);
}

///用户发出获取短信验证码请求（该功能暂不支持）
TDAPI_API int		ReqGenUserText(CThostFtdcTraderApi* pApi, CThostFtdcReqGenUserTextField* pReqGenUserText, int nRequestID)
{
	return pApi->ReqGenUserText(pReqGenUserText, nRequestID);
}

///用户发出带有图片验证码的登陆请求（该功能暂不支持）
TDAPI_API int		ReqUserLoginWithCaptcha(CThostFtdcTraderApi* pApi, CThostFtdcReqUserLoginWithCaptchaField* pReqUserLoginWithCaptcha, int nRequestID)
{
	return pApi->ReqUserLoginWithCaptcha(pReqUserLoginWithCaptcha, nRequestID);
}

///用户发出带有短信验证码的登陆请求（该功能暂不支持）
TDAPI_API int		ReqUserLoginWithText(CThostFtdcTraderApi* pApi, CThostFtdcReqUserLoginWithTextField* pReqUserLoginWithText, int	nRequestID)
{
	return pApi->ReqUserLoginWithText(pReqUserLoginWithText, nRequestID);
}


///用户发出带有动态口令的登陆请求（该功能暂不支持）
TDAPI_API int		ReqUserLoginWithOTP(CThostFtdcTraderApi* pApi, CThostFtdcReqUserLoginWithOTPField* pReqUserLoginWithOTP, int nRequestID)
{
	return pApi->ReqUserLoginWithOTP(pReqUserLoginWithOTP, nRequestID);
}


//
////更新用户口令
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
////资金账户口令更新请求
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
////安全登录请求
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
////安全更新用户口令
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

////查询用户当前支持的认证模式
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
////用户发出获取图形验证码请求
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
////用户发出获取短信验证码请求
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
////用户发出带有图片验证码的登陆请求
//TDAPI_API int ReqUserLoginWithCaptcha(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcReqUserLoginWithCaptchaField *pReqUserLoginWithCaptcha)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqUserLoginWithCaptcha(pReqUserLoginWithCaptcha, requestID);
//}
////用户发出带有短信验证码的登陆请求
//TDAPI_API int ReqUserLoginWithText(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcReqUserLoginWithTextField *pReqUserLoginWithText)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqUserLoginWithText(pReqUserLoginWithText, requestID);
//}
////用户发出带有动态口令的登陆请求
//TDAPI_API int ReqUserLoginWithOTP(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcReqUserLoginWithOTPField *pReqUserLoginWithOTP)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqUserLoginWithOTP(pReqUserLoginWithOTP, requestID);
//}
//报单录入请求
//TDAPI_API int ReqOrderInsert(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcInputOrderField *pOrder)
//{
//	if (pApi == NULL) return -1;
//
//	int siez = sizeof(CThostFtdcInputOrderField);
//	strcpy_s(pOrder->BusinessUnit, "HF");
//	return pApi->ReqOrderInsert(pOrder, requestID);
//}
////报单操作请求
//TDAPI_API int ReqOrderAction(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcInputOrderActionField *pOrder)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqOrderAction(pOrder, requestID);
//}
////查询最大报单数量请求
//TDAPI_API int ReqQueryMaxOrderVolume(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcQueryMaxOrderVolumeField *pMaxOrderVolume)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqQueryMaxOrderVolume(pMaxOrderVolume, requestID);
//}
////投资者结算结果确认
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
////执行宣告录入请求
//TDAPI_API int ReqExecOrderInsert(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcInputExecOrderField *pInputExecOrder)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqExecOrderInsert(pInputExecOrder, requestID);
//}
////执行宣告操作请求
//TDAPI_API int ReqExecOrderAction(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcInputExecOrderActionField *pInputExecOrderAction)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqExecOrderAction(pInputExecOrderAction, requestID);
//}
////询价录入请求
//TDAPI_API int ReqForQuoteInsert(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcInputForQuoteField *pInputForQuote)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqForQuoteInsert(pInputForQuote, requestID);
//}
////报价录入请求
//TDAPI_API int ReqQuoteInsert(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcInputQuoteField *pInputQuote)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqQuoteInsert(pInputQuote, requestID);
//}
////报价操作请求
//TDAPI_API int ReqQuoteAction(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcInputQuoteActionField *pInputQuoteAction)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqQuoteAction(pInputQuoteAction, requestID);
//}
////批量报单操作请求
//TDAPI_API int ReqBatchOrderAction(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcInputBatchOrderActionField *pInputBatchOrderAction)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqBatchOrderAction(pInputBatchOrderAction, requestID);
//}
////期权自对冲录入请求
//TDAPI_API int ReqOptionSelfCloseInsert(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcInputOptionSelfCloseField *pInputOptionSelfClose)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqOptionSelfCloseInsert(pInputOptionSelfClose, requestID);
//}
////期权自对冲操作请求
//TDAPI_API int ReqOptionSelfCloseAction(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcInputOptionSelfCloseActionField *pInputOptionSelfCloseAction)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqOptionSelfCloseAction(pInputOptionSelfCloseAction, requestID);
//}
////申请组合录入请求
//TDAPI_API int ReqCombActionInsert(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcInputCombActionField *pInputCombAction)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqCombActionInsert(pInputCombAction, requestID);
//}
////请求查询报单
//TDAPI_API int ReqQryOrder(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcQryOrderField *pQryOrder)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqQryOrder(pQryOrder, requestID);
//}
////请求查询成交
//TDAPI_API int ReqQryTrade(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcQryTradeField *pQryTrade)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqQryTrade(pQryTrade, requestID);
//}
////请求查询投资者持仓
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
////请求查询资金账户
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
////请求查询投资者
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
////请求查询交易编码
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
////请求查询合约保证金率
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
//		req.HedgeFlag = hedgeFlag;						//*不*能采用null进行所有查询
//	return pApi->ReqQryInstrumentMarginRate(&req, requestID);
//}
////请求查询合约手续费率
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
////请求查询交易所
//TDAPI_API int ReqQryExchange(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcExchangeIDType exchangeID)
//{
//	if (pApi == NULL) return -1;
//
//	CThostFtdcQryExchangeField  req;
//	memset(&req, 0, sizeof(req));
//	strcpy_s(req.ExchangeID, exchangeID);
//	return pApi->ReqQryExchange(&req, requestID);
//}
////请求查询合约
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
////请求查询行情
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
////请求查询投资者结算结果
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
////查询持仓明细
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
////请求查询客户通知
//TDAPI_API int ReqQryNotice(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcBrokerIDType brokerID)
//{
//	if (pApi == NULL) return -1;
//
//	CThostFtdcQryNoticeField  req;
//	memset(&req, 0, sizeof(req));
//	strcpy_s(req.BrokerID, brokerID);
//	return pApi->ReqQryNotice(&req, requestID);
//}
////请求查询结算信息确认
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
////请求查询**组合**持仓明细
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
////请求查询保证金监管系统经纪公司资金账户密钥
//TDAPI_API int ReqQryCFMMCTradingAccountKey(CThostFtdcTraderApi* pApi, CThostFtdcQryCFMMCTradingAccountKeyField* key, int nRequestID)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqQryCFMMCTradingAccountKey(key, nRequestID);
//}
////请求查询仓单折抵信息
//TDAPI_API int ReqQryEWarrantOffset(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcQryEWarrantOffsetField *pQryEWarrantOffset)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqQryEWarrantOffset(pQryEWarrantOffset, requestID);
//}
////请求查询投资者品种/跨品种保证金
//TDAPI_API int ReqQryInvestorProductGroupMargin(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcQryInvestorProductGroupMarginField *pQryInvestorProductGroupMargin)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqQryInvestorProductGroupMargin(pQryInvestorProductGroupMargin, requestID);
//}
////请求查询交易所保证金率
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
////请求查询交易所调整保证金率
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
////请求查询汇率
//TDAPI_API int ReqQryExchangeRate(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcQryExchangeRateField *pQryExchangeRate)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqQryExchangeRate(pQryExchangeRate, requestID);
//}
////请求查询二级代理操作员银期权限
//TDAPI_API int ReqQrySecAgentACIDMap(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcQrySecAgentACIDMapField *pQrySecAgentACIDMap)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqQrySecAgentACIDMap(pQrySecAgentACIDMap, requestID);
//}
////请求查询产品报价汇率
//TDAPI_API int ReqQryProductExchRate(CThostFtdcTraderApi* pApi, int requestID, TThostFtdcInstrumentIDType productID)
//{
//	if (pApi == NULL) return -1;
//
//	CThostFtdcQryProductExchRateField req;
//	memset(&req, 0, sizeof(req));
//	strcpy_s(req.ProductID, productID);
//	return pApi->ReqQryProductExchRate(&req, requestID);
//}
////请求查询产品组
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
////请求查询做市商合约手续费率
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
////请求查询做市商期权合约手续费
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
////请求查询报单手续费
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
////请求查询资金账户
//TDAPI_API int ReqQrySecAgentTradingAccount(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcQryTradingAccountField *pQryTradingAccount)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqQrySecAgentTradingAccount(pQryTradingAccount, requestID);
//}
////请求查询二级代理商资金校验模式
//TDAPI_API int ReqQrySecAgentCheckMode(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcQrySecAgentCheckModeField *pQrySecAgentCheckMode)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqQrySecAgentCheckMode(pQrySecAgentCheckMode, requestID);
//}
////请求查询期权交易成本
//TDAPI_API int ReqQryOptionInstrTradeCost(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcQryOptionInstrTradeCostField *pQryOptionInstrTradeCost)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqQryOptionInstrTradeCost(pQryOptionInstrTradeCost, requestID);
//}
////请求查询期权合约手续费
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
////请求查询执行宣告
//TDAPI_API int ReqQryExecOrder(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcQryExecOrderField *pQryExecOrder)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqQryExecOrder(pQryExecOrder, requestID);
//}
////请求查询询价
//TDAPI_API int ReqQryForQuote(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcQryForQuoteField *pQryForQuote)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqQryForQuote(pQryForQuote, requestID);
//}
////请求查询报价
//TDAPI_API int ReqQryQuote(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcQryQuoteField *pQryQuote)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqQryQuote(pQryQuote, requestID);
//}
////请求查询期权自对冲
//TDAPI_API int ReqQryOptionSelfClose(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcQryOptionSelfCloseField *pQryOptionSelfClose)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqQryOptionSelfClose(pQryOptionSelfClose, requestID);
//}
////请求查询投资单元
//TDAPI_API int ReqQryInvestUnit(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcQryInvestUnitField *pQryInvestUnit)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqQryInvestUnit(pQryInvestUnit, requestID);
//}
////请求查询组合合约安全系数
//TDAPI_API int ReqQryCombInstrumentGuard(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcQryCombInstrumentGuardField *pQryCombInstrumentGuard)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqQryCombInstrumentGuard(pQryCombInstrumentGuard, requestID);
//}
////请求查询申请组合
//TDAPI_API int ReqQryCombAction(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcQryCombActionField *pQryCombAction)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqQryCombAction(pQryCombAction, requestID);
//}
////请求查询交易通知
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
////请求查询经纪公司交易参数
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
////请求查询经纪公司交易算法
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
////预埋单录入请求
//TDAPI_API int ReqParkedOrderInsert(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcParkedOrderField *ParkedOrder)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqParkedOrderInsert(ParkedOrder, requestID);
//}
////预埋撤单录入请求
//TDAPI_API int ReqParkedOrderAction(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcParkedOrderActionField *ParkedOrderAction)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqParkedOrderAction(ParkedOrderAction, requestID);
//}
////请求删除预埋单
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
////请求删除预埋撤单
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
////请求查询转帐银行
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
////请求查询转帐流水
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
////请求查询银期签约关系
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
////请求查询签约银行
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
////请求查询预埋单
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
////请求查询预埋撤单
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
////请求查询监控中心用户令牌
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
////期货发起银行资金转期货请求
//TDAPI_API int ReqFromBankToFutureByFuture(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcReqTransferField *reqTransfer)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqFromBankToFutureByFuture(reqTransfer, requestID);
//}
////期货发起期货资金转银行请求
//TDAPI_API int ReqFromFutureToBankByFuture(CThostFtdcTraderApi* pApi, int requestID, CThostFtdcReqTransferField *reqTransfer)
//{
//	if (pApi == NULL) return -1;
//
//	return pApi->ReqFromFutureToBankByFuture(reqTransfer, requestID);
//}
////期货发起查询银行余额请求
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
///请求查询报单
TDAPI_API int		ReqQryOrder(CThostFtdcTraderApi* pApi, CThostFtdcQryOrderField* pQryOrder, int nRequestID)
{
	return pApi->ReqQryOrder(pQryOrder, nRequestID);
}
///查询最大报单数量请求
TDAPI_API int		ReqQueryMaxOrderVolume(CThostFtdcTraderApi* pApi, CThostFtdcQueryMaxOrderVolumeField* pQueryMaxOrderVolume, int nRequestID)
{
	return pApi->ReqQueryMaxOrderVolume(pQueryMaxOrderVolume, nRequestID);
}
///报单操作请求
TDAPI_API int		ReqOrderAction(CThostFtdcTraderApi* pApi, CThostFtdcInputOrderActionField* pInputOrderAction, int nRequestID)
{
	return pApi->ReqOrderAction(pInputOrderAction, nRequestID);
}
///批量报单操作请求
TDAPI_API int		ReqBatchOrderAction(CThostFtdcTraderApi* pApi, CThostFtdcInputBatchOrderActionField* pInputBatchOrderAction, int nRequestID)
{
	return pApi->ReqBatchOrderAction(pInputBatchOrderAction, nRequestID);
}

///预埋单录入请求
TDAPI_API int		ReqParkedOrderInsert(CThostFtdcTraderApi* pApi, CThostFtdcParkedOrderField* pParkedOrder, int nRequestID)
{
	return pApi->ReqParkedOrderInsert(pParkedOrder, nRequestID);
}
///预埋撤单录入请求
TDAPI_API int		ReqParkedOrderAction(CThostFtdcTraderApi* pApi, CThostFtdcParkedOrderActionField* pParkedOrderAction, int nRequestID)
{
	return pApi->ReqParkedOrderAction(pParkedOrderAction, nRequestID);
}
///请求删除预埋单
TDAPI_API int		ReqRemoveParkedOrder(CThostFtdcTraderApi* pApi, CThostFtdcRemoveParkedOrderField* pRemoveParkedOrder, int nRequestID)
{
	return pApi->ReqRemoveParkedOrder(pRemoveParkedOrder, nRequestID);
}
///请求删除预埋撤单
TDAPI_API int		ReqRemoveParkedOrderAction(CThostFtdcTraderApi* pApi, CThostFtdcRemoveParkedOrderActionField* pRemoveParkedOrderAction, int nRequestID)
{
	return pApi->ReqRemoveParkedOrderAction(pRemoveParkedOrderAction, nRequestID);
}
///请求查询预埋单
TDAPI_API int		ReqQryParkedOrder(CThostFtdcTraderApi* pApi, CThostFtdcQryParkedOrderField* pQryParkedOrder, int nRequestID)
{
	return pApi->ReqQryParkedOrder(pQryParkedOrder, nRequestID);
}
///请求查询预埋撤单
TDAPI_API int		ReqQryParkedOrderAction(CThostFtdcTraderApi* pApi, CThostFtdcQryParkedOrderActionField* pQryParkedOrderAction, int nRequestID)
{
	return pApi->ReqQryParkedOrderAction(pQryParkedOrderAction, nRequestID);
}

///请求查询客户通知
TDAPI_API int		ReqQryNotice(CThostFtdcTraderApi* pApi, CThostFtdcQryNoticeField* pQryNotice, int nRequestID)
{
	return pApi->ReqQryNotice(pQryNotice, nRequestID);
}
///请求查询交易通知
TDAPI_API int		ReqQryTradingNotice(CThostFtdcTraderApi* pApi, CThostFtdcQryTradingNoticeField* pQryTradingNotice, int nRequestID)
{
	return pApi->ReqQryTradingNotice(pQryTradingNotice, nRequestID);
}


///请求查询执行宣告
TDAPI_API int		ReqQryExecOrder(CThostFtdcTraderApi* pApi, CThostFtdcQryExecOrderField* pQryExecOrder, int nRequestID)
{
	return pApi->ReqQryExecOrder(pQryExecOrder, nRequestID);
}
///执行宣告录入请求
TDAPI_API int		ReqExecOrderInsert(CThostFtdcTraderApi* pApi, CThostFtdcInputExecOrderField* pInputExecOrder, int nRequestID)
{
	return pApi->ReqExecOrderInsert(pInputExecOrder, nRequestID);
}
///执行宣告操作请求
TDAPI_API int		ReqExecOrderAction(CThostFtdcTraderApi* pApi, CThostFtdcInputExecOrderActionField* pInputExecOrderAction, int nRequestID)
{
	return pApi->ReqExecOrderAction(pInputExecOrderAction, nRequestID);
}


///询价录入请求
TDAPI_API int		ReqForQuoteInsert(CThostFtdcTraderApi* pApi, CThostFtdcInputForQuoteField* pInputForQuote, int nRequestID)
{
	return pApi->ReqForQuoteInsert(pInputForQuote, nRequestID);

}
///报价录入请求
TDAPI_API int		ReqQuoteInsert(CThostFtdcTraderApi* pApi, CThostFtdcInputQuoteField* pInputQuote, int nRequestID)
{
	return pApi->ReqQuoteInsert(pInputQuote, nRequestID);
}
///报价操作请求
TDAPI_API int		ReqQuoteAction(CThostFtdcTraderApi* pApi, CThostFtdcInputQuoteActionField* pInputQuoteAction, int nRequestID)
{
	return pApi->ReqQuoteAction(pInputQuoteAction, nRequestID);
}



///申请组合录入请求
TDAPI_API int		ReqCombActionInsert(CThostFtdcTraderApi* pApi, CThostFtdcInputCombActionField* pInputCombAction, int nRequestID)
{
	return pApi->ReqCombActionInsert(pInputCombAction, nRequestID);
}
///请求查询组合合约安全系数
TDAPI_API int		ReqQryCombInstrumentGuard(CThostFtdcTraderApi* pApi, CThostFtdcQryCombInstrumentGuardField* pQryCombInstrumentGuard, int nRequestID)
{
	return pApi->ReqQryCombInstrumentGuard(pQryCombInstrumentGuard, nRequestID);
}
///请求查询申请组合
TDAPI_API int		ReqQryCombAction(CThostFtdcTraderApi* pApi, CThostFtdcQryCombActionField* pQryCombAction, int nRequestID)
{
	return pApi->ReqQryCombAction(pQryCombAction, nRequestID);
}


///请求查询成交
TDAPI_API int		ReqQryTrade(CThostFtdcTraderApi* pApi, CThostFtdcQryTradeField* pQryTrade, int nRequestID)
{
	return pApi->ReqQryTrade(pQryTrade, nRequestID);
}


///请求查询投资者持仓
TDAPI_API int		ReqQryInvestorPosition(CThostFtdcTraderApi* pApi, CThostFtdcQryInvestorPositionField* pQryInvestorPosition, int nRequestID)
{
	return pApi->ReqQryInvestorPosition(pQryInvestorPosition, nRequestID);
}
///请求查询投资者持仓明细
TDAPI_API int		ReqQryInvestorPositionDetail(CThostFtdcTraderApi* pApi, CThostFtdcQryInvestorPositionDetailField* pQryInvestorPositionDetail, int nRequestID)
{
	return pApi->ReqQryInvestorPositionDetail(pQryInvestorPositionDetail, nRequestID);
}
///请求查询投资者持仓明细
TDAPI_API int		ReqQryInvestorPositionCombineDetail(CThostFtdcTraderApi* pApi, CThostFtdcQryInvestorPositionCombineDetailField* pQryInvestorPositionCombineDetail, int nRequestID)
{
	return pApi->ReqQryInvestorPositionCombineDetail(pQryInvestorPositionCombineDetail, nRequestID);
}
///请求查询资金账户
TDAPI_API int		ReqQryTradingAccount(CThostFtdcTraderApi* pApi, CThostFtdcQryTradingAccountField* pQryTradingAccount, int nRequestID)
{
	return pApi->ReqQryTradingAccount(pQryTradingAccount, nRequestID);
}
///请求查询投资者
TDAPI_API int		ReqQryInvestor(CThostFtdcTraderApi* pApi, CThostFtdcQryInvestorField* pQryInvestor, int nRequestID)
{
	return pApi->ReqQryInvestor(pQryInvestor, nRequestID);
}
///请求查询交易编码
TDAPI_API int		ReqQryTradingCode(CThostFtdcTraderApi* pApi, CThostFtdcQryTradingCodeField* pQryTradingCode, int nRequestID)
{
	return pApi->ReqQryTradingCode(pQryTradingCode, nRequestID);
}
///请求查询投资者结算结果
TDAPI_API int		ReqQrySettlementInfo(CThostFtdcTraderApi* pApi, CThostFtdcQrySettlementInfoField* pQrySettlementInfo, int nRequestID)
{
	return pApi->ReqQrySettlementInfo(pQrySettlementInfo, nRequestID);
}
///请求查询结算信息确认
TDAPI_API int		ReqQrySettlementInfoConfirm(CThostFtdcTraderApi* pApi, CThostFtdcQrySettlementInfoConfirmField* pQrySettlementInfoConfirm, int nRequestID)
{
	return pApi->ReqQrySettlementInfoConfirm(pQrySettlementInfoConfirm, nRequestID);
}
///投资者结算结果确认
TDAPI_API int		ReqSettlementInfoConfirm(CThostFtdcTraderApi* pApi, CThostFtdcSettlementInfoConfirmField* pSettlementInfoConfirm, int nRequestID)
{
	return pApi->ReqSettlementInfoConfirm(pSettlementInfoConfirm, nRequestID);
}


#pragma region 产品/合约/Instrument
///请求查询产品
TDAPI_API int		ReqQryProduct(CThostFtdcTraderApi* pApi, CThostFtdcQryProductField* pQryProduct, int nRequestID)
{
	return pApi->ReqQryProduct(pQryProduct, nRequestID);
}
///请求查询产品报价汇率
TDAPI_API int		ReqQryProductExchRate(CThostFtdcTraderApi* pApi, CThostFtdcQryProductExchRateField* pQryProductExchRate, int nRequestID)
{
	return pApi->ReqQryProductExchRate(pQryProductExchRate, nRequestID);
}
///请求查询产品组
TDAPI_API int		ReqQryProductGroup(CThostFtdcTraderApi* pApi, CThostFtdcQryProductGroupField* pQryProductGroup, int nRequestID)
{
	return pApi->ReqQryProductGroup(pQryProductGroup, nRequestID);
}

///请求查询合约
TDAPI_API int		ReqQryInstrument(CThostFtdcTraderApi* pApi, CThostFtdcQryInstrumentField* pQryInstrument, int nRequestID)
{
	return pApi->ReqQryInstrument(pQryInstrument, nRequestID);
}
///请求查询合约保证金率
TDAPI_API int		ReqQryInstrumentMarginRate(CThostFtdcTraderApi* pApi, CThostFtdcQryInstrumentMarginRateField* pQryInstrumentMarginRate, int nRequestID)
{
	return pApi->ReqQryInstrumentMarginRate(pQryInstrumentMarginRate, nRequestID);
}
///请求查询合约手续费率
TDAPI_API int		ReqQryInstrumentCommissionRate(CThostFtdcTraderApi* pApi, CThostFtdcQryInstrumentCommissionRateField* pQryInstrumentCommissionRate, int nRequestID)
{
	return pApi->ReqQryInstrumentCommissionRate(pQryInstrumentCommissionRate, nRequestID);
}
#pragma endregion



///请求查询询价
TDAPI_API int		ReqQryForQuote(CThostFtdcTraderApi* pApi, CThostFtdcQryForQuoteField* pQryForQuote, int nRequestID)
{
	return pApi->ReqQryForQuote(pQryForQuote, nRequestID);
}
///请求查询报价
TDAPI_API int		ReqQryQuote(CThostFtdcTraderApi* pApi, CThostFtdcQryQuoteField* pQryQuote, int nRequestID)
{
	return pApi->ReqQryQuote(pQryQuote, nRequestID);
}
///请求查询行情
TDAPI_API int		ReqQryDepthMarketData(CThostFtdcTraderApi* pApi, CThostFtdcQryDepthMarketDataField* pQryDepthMarketData, int nRequestID)
{
	return pApi->ReqQryDepthMarketData(pQryDepthMarketData, nRequestID);
}





///请求查询仓单折抵信息
TDAPI_API int		ReqQryEWarrantOffset(CThostFtdcTraderApi* pApi, CThostFtdcQryEWarrantOffsetField* pQryEWarrantOffset, int nRequestID)
{
	return pApi->ReqQryEWarrantOffset(pQryEWarrantOffset, nRequestID);
}

///请求查询投资者品种/跨品种保证金
TDAPI_API int		ReqQryInvestorProductGroupMargin(CThostFtdcTraderApi* pApi, CThostFtdcQryInvestorProductGroupMarginField* pQryInvestorProductGroupMargin, int nRequestID)
{
	return pApi->ReqQryInvestorProductGroupMargin(pQryInvestorProductGroupMargin, nRequestID);
}




///请求查询做市商合约手续费率
TDAPI_API int		ReqQryMMInstrumentCommissionRate(CThostFtdcTraderApi* pApi, CThostFtdcQryMMInstrumentCommissionRateField* pQryMMInstrumentCommissionRate, int nRequestID)
{
	return pApi->ReqQryMMInstrumentCommissionRate(pQryMMInstrumentCommissionRate, nRequestID);
}
///请求查询做市商期权合约手续费
TDAPI_API int		ReqQryMMOptionInstrCommRate(CThostFtdcTraderApi* pApi, CThostFtdcQryMMOptionInstrCommRateField* pQryMMOptionInstrCommRate, int nRequestID)
{
	return pApi->ReqQryMMOptionInstrCommRate(pQryMMOptionInstrCommRate, nRequestID);
}

///请求查询报单手续费
TDAPI_API int		ReqQryInstrumentOrderCommRate(CThostFtdcTraderApi* pApi, CThostFtdcQryInstrumentOrderCommRateField* pQryInstrumentOrderCommRate, int nRequestID)
{
	return pApi->ReqQryInstrumentOrderCommRate(pQryInstrumentOrderCommRate, nRequestID);
}


#pragma region 二级代理/sec agent
///请求查询资金账户
TDAPI_API int		ReqQrySecAgentTradingAccount(CThostFtdcTraderApi* pApi, CThostFtdcQryTradingAccountField* pQryTradingAccount, int nRequestID)
{
	return pApi->ReqQrySecAgentTradingAccount(pQryTradingAccount, nRequestID);
}
///请求查询二级代理操作员银期权限
TDAPI_API int		ReqQrySecAgentACIDMap(CThostFtdcTraderApi* pApi, CThostFtdcQrySecAgentACIDMapField* pQrySecAgentACIDMap, int nRequestID)
{
	return pApi->ReqQrySecAgentACIDMap(pQrySecAgentACIDMap, nRequestID);
}
///请求查询二级代理商资金校验模式
TDAPI_API int		ReqQrySecAgentCheckMode(CThostFtdcTraderApi* pApi, CThostFtdcQrySecAgentCheckModeField* pQrySecAgentCheckMode, int nRequestID)
{
	return pApi->ReqQrySecAgentCheckMode(pQrySecAgentCheckMode, nRequestID);
}
///请求查询二级代理商信息
TDAPI_API int		ReqQrySecAgentTradeInfo(CThostFtdcTraderApi* pApi, CThostFtdcQrySecAgentTradeInfoField* pQrySecAgentTradeInfo, int nRequestID)
{
	return pApi->ReqQrySecAgentTradeInfo(pQrySecAgentTradeInfo, nRequestID);
}
#pragma endregion


#pragma region 期权option
///期权自对冲录入请求
TDAPI_API int		ReqOptionSelfCloseInsert(CThostFtdcTraderApi* pApi, CThostFtdcInputOptionSelfCloseField* pInputOptionSelfClose, int nRequestID)
{
	return pApi->ReqOptionSelfCloseInsert(pInputOptionSelfClose, nRequestID);
}
///期权自对冲操作请求
TDAPI_API int		ReqOptionSelfCloseAction(CThostFtdcTraderApi* pApi, CThostFtdcInputOptionSelfCloseActionField* pInputOptionSelfCloseAction, int nRequestID)
{
	return pApi->ReqOptionSelfCloseAction(pInputOptionSelfCloseAction, nRequestID);
}

///请求查询期权交易成本
TDAPI_API int		ReqQryOptionInstrTradeCost(CThostFtdcTraderApi* pApi, CThostFtdcQryOptionInstrTradeCostField* pQryOptionInstrTradeCost, int nRequestID)
{
	return pApi->ReqQryOptionInstrTradeCost(pQryOptionInstrTradeCost, nRequestID);
}
///请求查询期权合约手续费
TDAPI_API int		ReqQryOptionInstrCommRate(CThostFtdcTraderApi* pApi, CThostFtdcQryOptionInstrCommRateField* pQryOptionInstrCommRate, int nRequestID)
{
	return pApi->ReqQryOptionInstrCommRate(pQryOptionInstrCommRate, nRequestID);
}
///请求查询期权自对冲
TDAPI_API int		ReqQryOptionSelfClose(CThostFtdcTraderApi* pApi, CThostFtdcQryOptionSelfCloseField* pQryOptionSelfClose, int nRequestID)
{
	return pApi->ReqQryOptionSelfClose(pQryOptionSelfClose, nRequestID);
}
#pragma endregion




///请求查询投资单元（暂不支持该功能）
TDAPI_API int		ReqQryInvestUnit(CThostFtdcTraderApi* pApi, CThostFtdcQryInvestUnitField* pQryInvestUnit, int nRequestID)
{
	return pApi->ReqQryInvestUnit(pQryInvestUnit, nRequestID);
}



#pragma region Banking
///请求查询转帐银行
TDAPI_API int		ReqQryTransferBank(CThostFtdcTraderApi* pApi, CThostFtdcQryTransferBankField* pQryTransferBank, int nRequestID)
{
	return pApi->ReqQryTransferBank(pQryTransferBank, nRequestID);
}
///请求查询银期签约关系
TDAPI_API int		ReqQryAccountregister(CThostFtdcTraderApi* pApi, CThostFtdcQryAccountregisterField* pQryAccountregister, int nRequestID)
{
	return pApi->ReqQryAccountregister(pQryAccountregister, nRequestID);
}
///请求查询签约银行
TDAPI_API int		ReqQryContractBank(CThostFtdcTraderApi* pApi, CThostFtdcQryContractBankField* pQryContractBank, int nRequestID)
{
	return pApi->ReqQryContractBank(pQryContractBank, nRequestID);
}
///请求查询转帐流水
TDAPI_API int		ReqQryTransferSerial(CThostFtdcTraderApi* pApi, CThostFtdcQryTransferSerialField* pQryTransferSerial, int nRequestID)
{
	return pApi->ReqQryTransferSerial(pQryTransferSerial, nRequestID);
}
///期货发起查询银行余额请求
TDAPI_API int		ReqQueryBankAccountMoneyByFuture(CThostFtdcTraderApi* pApi, CThostFtdcReqQueryAccountField* pReqQueryAccount, int nRequestID)
{
	return pApi->ReqQueryBankAccountMoneyByFuture(pReqQueryAccount, nRequestID);
}

///期货发起银行资金转期货请求
TDAPI_API int		ReqFromBankToFutureByFuture(CThostFtdcTraderApi* pApi, CThostFtdcReqTransferField* pReqTransfer, int nRequestID)
{
	return pApi->ReqFromBankToFutureByFuture(pReqTransfer, nRequestID);
}
///期货发起期货资金转银行请求
TDAPI_API int		ReqFromFutureToBankByFuture(CThostFtdcTraderApi* pApi, CThostFtdcReqTransferField* pReqTransfer, int nRequestID)
{
	return pApi->ReqFromFutureToBankByFuture(pReqTransfer, nRequestID);
}
#pragma endregion


#pragma region Exchange/交易所
///请求查询交易所
TDAPI_API int		ReqQryExchange(CThostFtdcTraderApi* pApi, CThostFtdcQryExchangeField* pQryExchange, int nRequestID)
{
	return pApi->ReqQryExchange(pQryExchange, nRequestID);
}
///请求查询交易所保证金率
TDAPI_API int		ReqQryExchangeMarginRate(CThostFtdcTraderApi* pApi, CThostFtdcQryExchangeMarginRateField* pQryExchangeMarginRate, int nRequestID)
{
	return pApi->ReqQryExchangeMarginRate(pQryExchangeMarginRate, nRequestID);
}
///请求查询交易所调整保证金率
TDAPI_API int		ReqQryExchangeMarginRateAdjust(CThostFtdcTraderApi* pApi, CThostFtdcQryExchangeMarginRateAdjustField* pQryExchangeMarginRateAdjust, int nRequestID)
{
	return pApi->ReqQryExchangeMarginRateAdjust(pQryExchangeMarginRateAdjust, nRequestID);
}
///请求查询汇率
TDAPI_API int		ReqQryExchangeRate(CThostFtdcTraderApi* pApi, CThostFtdcQryExchangeRateField* pQryExchangeRate, int nRequestID)
{
	return pApi->ReqQryExchangeRate(pQryExchangeRate, nRequestID);
}
#pragma endregion


#pragma region Broker
///请求查询经纪公司交易参数
TDAPI_API int		ReqQryBrokerTradingParams(CThostFtdcTraderApi* pApi, CThostFtdcQryBrokerTradingParamsField* pQryBrokerTradingParams, int nRequestID)
{
	return pApi->ReqQryBrokerTradingParams(pQryBrokerTradingParams, nRequestID);
}
///请求查询经纪公司交易算法
TDAPI_API int		ReqQryBrokerTradingAlgos(CThostFtdcTraderApi* pApi, CThostFtdcQryBrokerTradingAlgosField* pQryBrokerTradingAlgos, int nRequestID)
{
	return pApi->ReqQryBrokerTradingAlgos(pQryBrokerTradingAlgos, nRequestID);
}
#pragma endregion

#pragma region CFMMC
///请求查询监控中心用户令牌
TDAPI_API int		ReqQueryCFMMCTradingAccountToken(CThostFtdcTraderApi* pApi, CThostFtdcQueryCFMMCTradingAccountTokenField* pQueryCFMMCTradingAccountToken, int nRequestID)
{
	return pApi->ReqQueryCFMMCTradingAccountToken(pQueryCFMMCTradingAccountToken, nRequestID);
}

///请求查询保证金监管系统经纪公司资金账户密钥
TDAPI_API int		ReqQryCFMMCTradingAccountKey(CThostFtdcTraderApi* pApi, CThostFtdcQryCFMMCTradingAccountKeyField* pQryCFMMCTradingAccountKey, int nRequestID)
{
	return pApi->ReqQryCFMMCTradingAccountKey(pQryCFMMCTradingAccountKey, nRequestID);
}
#pragma endregion


#pragma endregion

#pragma region 回调函数
//========================================
//==================================== 回调函数 =======================================

TDAPI_API void   RegOnRspFrontConnected(TraderSpi* pSpi, CBOnRspFrontConnected cb)		//当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
{
	pSpi->cbOnFrontConnected = cb;
}

TDAPI_API void   RegOnRspFrontDisconnected(TraderSpi* pSpi, CBOnRspFrontDisconnected cb)		//当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
{
	pSpi->cbOnFrontDisconnected = cb;
}

TDAPI_API void   RegOnHeartBeatWarning(TraderSpi* pSpi, CBOnHeartBeatWarning cb)		//心跳超时警告。当长时间未收到报文时，该方法被调用。
{
	pSpi->cbOnHeartBeatWarning = cb;
}

TDAPI_API void   RegOnRspAuthenticate(TraderSpi* pSpi, CBOnRspAuthenticate cb)
{
	pSpi->cbOnRspAuthenticate = cb;
}

TDAPI_API void   RegOnRspUserLogin(TraderSpi* pSpi, CBOnRspUserLogin cb)	//登录请求响应
{
	pSpi->cbOnRspUserLogin = cb;
}
TDAPI_API void   RegOnRspUserLogout(TraderSpi* pSpi, CBOnRspUserLogout cb)	//登出请求响应
{
	pSpi->cbOnRspUserLogout = cb;
}
TDAPI_API void   RegRspUserPasswordUpdate(TraderSpi* pSpi, CBRspUserPasswordUpdate cb)	//用户口令更新请求响应
{
	pSpi->cbRspUserPasswordUpdate = cb;
}
TDAPI_API void   RegRspTradingAccountPasswordUpdate(TraderSpi* pSpi, CBRspTradingAccountPasswordUpdate cb)	//资金账户口令更新请求响应
{
	pSpi->cbRspTradingAccountPasswordUpdate = cb;
}
TDAPI_API void   RegRspUserAuthMethod(TraderSpi* pSpi, CBRspUserAuthMethod cb)	//查询用户当前支持的认证模式的回复
{
	pSpi->cbRspUserAuthMethod = cb;
}
TDAPI_API void   RegRspGenUserCaptcha(TraderSpi* pSpi, CBRspGenUserCaptcha cb)	//获取图形验证码请求的回复
{
	pSpi->cbRspGenUserCaptcha = cb;
}
TDAPI_API void   RegRspGenUserText(TraderSpi* pSpi, CBRspGenUserText cb)	//获取短信验证码请求的回复
{
	pSpi->cbRspGenUserText = cb;
}
TDAPI_API void   RegOnRspOrderInsert(TraderSpi* pSpi, CBOnRspOrderInsert cb)	//报单录入请求响应
{
	pSpi->cbRspOrderInsert = cb;
}
TDAPI_API void   RegRspParkedOrderInsert(TraderSpi* pSpi, CBRspParkedOrderInsert cb)	//预埋单录入请求响应
{
	pSpi->cbRspParkedOrderInsert = cb;
}
TDAPI_API void   RegRspParkedOrderAction(TraderSpi* pSpi, CBRspParkedOrderAction cb)	//预埋撤单录入请求响应
{
	pSpi->cbRspParkedOrderAction = cb;
}
TDAPI_API void   RegOnRspOrderAction(TraderSpi* pSpi, CBOnRspOrderAction cb)	//报单操作请求响应
{
	pSpi->cbRspOrderAction = cb;
}
TDAPI_API void   RegRspQueryMaxOrderVolume(TraderSpi* pSpi, CBRspQueryMaxOrderVolume cb)	//查询最大报单数量响应
{
	pSpi->cbRspQueryMaxOrderVolume = cb;
}
TDAPI_API void   RegOnRspSettlementInfoConfirm(TraderSpi* pSpi, CBOnRspSettlementInfoConfirm cb)	//投资者结算结果确认响应
{
	pSpi->cbRspSettlementInfoConfirm = cb;
}
TDAPI_API void   RegRspRemoveParkedOrder(TraderSpi* pSpi, CBRspRemoveParkedOrder cb)	//删除预埋单响应
{
	pSpi->cbRspRemoveParkedOrder = cb;
}
TDAPI_API void   RegRspRemoveParkedOrderAction(TraderSpi* pSpi, CBRspRemoveParkedOrderAction cb)	//删除预埋撤单响应
{
	pSpi->cbRspRemoveParkedOrderAction = cb;
}
TDAPI_API void   RegBatchOrderAction(TraderSpi* pSpi, CBRspBatchOrderAction cb)	//批量报单操作请求响应
{
	pSpi->cbRspBatchOrderAction = cb;
}
TDAPI_API void   RegCombActionInsert(TraderSpi* pSpi, CBRspCombActionInsert cb)	//申请组合录入请求响应
{
	pSpi->cbRspCombActionInsert = cb;
}
TDAPI_API void   RegOnRspQryOrder(TraderSpi* pSpi, CBOnRspQryOrder cb)	//请求查询报单响应
{
	pSpi->cbRspQryOrder = cb;
}
TDAPI_API void   RegOnRspQryTrade(TraderSpi* pSpi, CBOnRspQryTrade cb)	//请求查询成交响应
{
	pSpi->cbRspQryTrade = cb;
}
TDAPI_API void   RegOnRspQryInvestorPosition(TraderSpi* pSpi, CBOnRspQryInvestorPosition cb)	//请求查询投资者持仓响应
{
	pSpi->cbRspQryInvestorPosition = cb;
}
TDAPI_API void   RegOnRspQryTradingAccount(TraderSpi* pSpi, CBOnRspQryTradingAccount cb)	//请求查询资金账户响应
{
	pSpi->cbRspQryTradingAccount = cb;
}
TDAPI_API void   RegRspQryInvestor(TraderSpi* pSpi, CBRspQryInvestor cb)	//请求查询投资者响应
{
	pSpi->cbRspQryInvestor = cb;
}
TDAPI_API void   RegRspQryTradingCode(TraderSpi* pSpi, CBRspQryTradingCode cb)	//请求查询交易编码响应
{
	pSpi->cbRspQryTradingCode = cb;
}
TDAPI_API void   RegRspQryInstrumentMarginRate(TraderSpi* pSpi, CBRspQryInstrumentMarginRate cb)	//请求查询合约保证金率响应
{
	pSpi->cbRspQryInstrumentMarginRate = cb;
}
TDAPI_API void   RegRspQryInstrumentCommissionRate(TraderSpi* pSpi, CBRspQryInstrumentCommissionRate cb)	//请求查询合约手续费率响应
{
	pSpi->cbRspQryInstrumentCommissionRate = cb;
}
TDAPI_API void   RegRspQryExchange(TraderSpi* pSpi, CBRspQryExchange cb)	//请求查询交易所响应
{
	pSpi->cbRspQryExchange = cb;
}
TDAPI_API void   RegOnRspQryInstrument(TraderSpi* pSpi, CBOnRspQryInstrument cb)	//请求查询合约响应
{
	pSpi->cbRspQryInstrument = cb;
}
TDAPI_API void   RegRspQryDepthMarketData(TraderSpi* pSpi, CBRspQryDepthMarketData cb)	//请求查询行情响应
{
	pSpi->cbRspQryDepthMarketData = cb;
}
TDAPI_API void   RegRspQrySettlementInfo(TraderSpi* pSpi, CBRspQrySettlementInfo cb)	//请求查询投资者结算结果响应
{
	pSpi->cbRspQrySettlementInfo = cb;
}
TDAPI_API void   RegRspQryTransferBank(TraderSpi* pSpi, CBRspQryTransferBank cb)	//请求查询转帐银行响应
{
	pSpi->cbRspQryTransferBank = cb;
}
TDAPI_API void   RegRspQryInvestorPositionDetail(TraderSpi* pSpi, CBRspQryInvestorPositionDetail cb)	//请求查询投资者持仓明细响应
{
	pSpi->cbRspQryInvestorPositionDetail = cb;
}
TDAPI_API void   RegRspQryNotice(TraderSpi* pSpi, CBRspQryNotice cb)	//请求查询客户通知响应
{
	pSpi->cbRspQryNotice = cb;
}
TDAPI_API void   RegRspQrySettlementInfoConfirm(TraderSpi* pSpi, CBRspQrySettlementInfoConfirm cb)	//请求查询结算信息确认响应
{
	pSpi->cbRspQrySettlementInfoConfirm = cb;
}
TDAPI_API void   RegRspQryInvestorPositionCombineDetail(TraderSpi* pSpi, CBRspQryInvestorPositionCombineDetail cb)	//请求查询投资者持仓明细响应
{
	pSpi->cbRspQryInvestorPositionCombineDetail = cb;
}
TDAPI_API void   RegRspQryCFMMCTradingAccountKey(TraderSpi* pSpi, CBRspQryCFMMCTradingAccountKey cb)	//查询保证金监管系统经纪公司资金账户密钥响应
{
	pSpi->cbRspQryCFMMCTradingAccountKey = cb;
}
TDAPI_API void   RegRspQryEWarrantOffset(TraderSpi* pSpi, CBRspQryEWarrantOffset cb)	//请求查询仓单折抵信息
{
	pSpi->cbRspQryEWarrantOffset = cb;
}
TDAPI_API void   RegRspQryInvestorProductGroupMargin(TraderSpi* pSpi, CBRspQryInvestorProductGroupMargin cb)	//请求查询投资者品种/跨品种保证金
{
	pSpi->cbRspQryInvestorProductGroupMargin = cb;
}
TDAPI_API void   RegRspQryExchangeMarginRate(TraderSpi* pSpi, CBRspQryExchangeMarginRate cb)	//请求查询交易所保证金率
{
	pSpi->cbRspQryExchangeMarginRate = cb;
}
TDAPI_API void   RegRspQryExchangeMarginRateAdjust(TraderSpi* pSpi, CBRspQryExchangeMarginRateAdjust cb)	//请求查询交易所调整保证金率
{
	pSpi->cbRspQryExchangeMarginRateAdjust = cb;
}
TDAPI_API void   RegRspQryExchangeRate(TraderSpi* pSpi, CBRspQryExchangeRate cb)	//请求查询汇率响应
{
	pSpi->cbRspQryExchangeRate = cb;
}
TDAPI_API void   RegRspQrySecAgentACIDMap(TraderSpi* pSpi, CBRspQrySecAgentACIDMap cb)	//请求查询二级代理操作员银期权限响应
{
	pSpi->cbRspQrySecAgentACIDMap = cb;
}
TDAPI_API void   RegRspQryProductExchRate(TraderSpi* pSpi, CBRspQryProductExchRate cb)	//请求查询产品报价汇率
{
	pSpi->cbRspQryProductExchRate = cb;
}
TDAPI_API void   RegRspQryProductGroup(TraderSpi* pSpi, CBRspQryProductGroup cb)	//请求查询产品组
{
	pSpi->cbRspQryProductGroup = cb;
}
TDAPI_API void   RegRspQryMMInstrumentCommissionRate(TraderSpi* pSpi, CBRspQryMMInstrumentCommissionRate cb)	//请求查询做市商合约手续费率响应
{
	pSpi->cbRspQryMMInstrumentCommissionRate = cb;
}
TDAPI_API void   RegRspQryMMOptionInstrCommRate(TraderSpi* pSpi, CBRspQryMMOptionInstrCommRate cb)	//请求查询做市商期权合约手续费响应
{
	pSpi->cbRspQryMMOptionInstrCommRate = cb;
}
TDAPI_API void   RegRspQryInstrumentOrderCommRate(TraderSpi* pSpi, CBRspQryInstrumentOrderCommRate cb)	//请求查询报单手续费响应
{
	pSpi->cbRspQryInstrumentOrderCommRate = cb;
}
TDAPI_API void   RegRspQrySecAgentTradingAccount(TraderSpi* pSpi, CBRspQrySecAgentTradingAccount cb)	//请求查询资金账户响应
{
	pSpi->cbRspQrySecAgentTradingAccount = cb;
}
TDAPI_API void   RegRspQrySecAgentCheckMode(TraderSpi* pSpi, CBRspQrySecAgentCheckMode cb)	//请求查询二级代理商资金校验模式响应
{
	pSpi->cbRspQrySecAgentCheckMode = cb;
}
TDAPI_API void   RegRspQrySecAgentTradeInfo(TraderSpi* pSpi, CBRspQrySecAgentTradeInfo cb)	//请求查询二级代理商信息响应
{
	pSpi->cbRspQrySecAgentTradeInfo = cb;
}
TDAPI_API void   RegRspQryOptionInstrTradeCost(TraderSpi* pSpi, CBRspQryOptionInstrTradeCost cb)	//请求查询期权交易成本响应
{
	pSpi->cbRspQryOptionInstrTradeCost = cb;
}
TDAPI_API void   RegRspQryOptionInstrCommRate(TraderSpi* pSpi, CBRspQryOptionInstrCommRate cb)	//请求查询期权合约手续费响应
{
	pSpi->cbRspQryOptionInstrCommRate = cb;
}
TDAPI_API void   RegRspQryExecOrder(TraderSpi* pSpi, CBRspQryExecOrder cb)	//请求查询执行宣告响应
{
	pSpi->cbRspQryExecOrder = cb;
}
TDAPI_API void   RegRspQryForQuote(TraderSpi* pSpi, CBRspQryForQuote cb)	//请求查询询价响应
{
	pSpi->cbRspQryForQuote = cb;
}
TDAPI_API void   RegRspQryQuote(TraderSpi* pSpi, CBRspQryQuote cb)	//请求查询报价响应
{
	pSpi->cbRspQryQuote = cb;
}
TDAPI_API void   RegRspQryOptionSelfClose(TraderSpi* pSpi, CBRspQryOptionSelfClose cb)	//请求查询期权自对冲响应
{
	pSpi->cbRspQryOptionSelfClose = cb;
}
TDAPI_API void   RegRspQryInvestUnit(TraderSpi* pSpi, CBRspQryInvestUnit cb)	//请求查询投资单元响应
{
	pSpi->cbRspQryInvestUnit = cb;
}
TDAPI_API void   RegRspQryCombInstrumentGuard(TraderSpi* pSpi, CBRspQryCombInstrumentGuard cb)	//请求查询组合合约安全系数响应
{
	pSpi->cbRspQryCombInstrumentGuard = cb;
}
TDAPI_API void   RegRspQryCombAction(TraderSpi* pSpi, CBRspQryCombAction cb)	//请求查询申请组合响应
{
	pSpi->cbRspQryCombAction = cb;
}
TDAPI_API void   RegRspQryTransferSerial(TraderSpi* pSpi, CBRspQryTransferSerial cb)	//请求查询转帐流水响应
{
	pSpi->cbRspQryTransferSerial = cb;
}
TDAPI_API void   RegOnRspQryAccountregister(TraderSpi* pSpi, CBOnRspQryAccountregister cb)	//请求查询银期签约关系响应
{
	pSpi->cbRspQryAccountregister = cb;
}
TDAPI_API void   RegOnRspError(TraderSpi* pSpi, CBOnRspError cb)	//错误应答
{
	pSpi->cbRspError = cb;
}
TDAPI_API void   RegOnRtnOrder(TraderSpi* pSpi, CBOnRtnOrder cb)	//报单通知
{
	pSpi->cbRtnOrder = cb;
}
TDAPI_API void   RegOnRtnTrade(TraderSpi* pSpi, CBOnRtnTrade cb)	//成交通知
{
	pSpi->cbRtnTrade = cb;
}
TDAPI_API void   RegOnErrRtnOrderInsert(TraderSpi* pSpi, CBOnErrRtnOrderInsert cb)	//报单录入错误回报
{
	pSpi->cbErrRtnOrderInsert = cb;
}
TDAPI_API void   RegOnErrRtnOrderAction(TraderSpi* pSpi, CBOnErrRtnOrderAction cb)	//报单操作错误回报
{
	pSpi->cbErrRtnOrderAction = cb;
}
TDAPI_API void   RegRtnInstrumentStatus(TraderSpi* pSpi, CBRtnInstrumentStatus cb)	//合约交易状态通知
{
	pSpi->cbRtnInstrumentStatus = cb;
}
TDAPI_API void   RegRtnTradingNotice(TraderSpi* pSpi, CBRtnTradingNotice cb)	//交易通知
{
	pSpi->cbRtnTradingNotice = cb;
}
TDAPI_API void   RegRtnErrorConditionalOrder(TraderSpi* pSpi, CBRtnErrorConditionalOrder cb)	//提示条件单校验错误
{
	pSpi->cbRtnErrorConditionalOrder = cb;
}
TDAPI_API void   RegRspQryContractBank(TraderSpi* pSpi, CBRspQryContractBank cb)	//请求查询签约银行响应
{
	pSpi->cbRspQryContractBank = cb;
}
TDAPI_API void   RegRspQryParkedOrder(TraderSpi* pSpi, CBRspQryParkedOrder cb)	//请求查询预埋单响应
{
	pSpi->cbRspQryParkedOrder = cb;
}
TDAPI_API void   RegRspQryParkedOrderAction(TraderSpi* pSpi, CBRspQryParkedOrderAction cb)	//请求查询预埋撤单响应
{
	pSpi->cbRspQryParkedOrderAction = cb;
}
TDAPI_API void   RegRspQryTradingNotice(TraderSpi* pSpi, CBRspQryTradingNotice cb)	//请求查询交易通知响应
{
	pSpi->cbRspQryTradingNotice = cb;
}
TDAPI_API void   RegRspQryBrokerTradingParams(TraderSpi* pSpi, CBRspQryBrokerTradingParams cb)	//请求查询经纪公司交易参数响应
{
	pSpi->cbRspQryBrokerTradingParams = cb;
}
TDAPI_API void   RegRspQryBrokerTradingAlgos(TraderSpi* pSpi, CBRspQryBrokerTradingAlgos cb)	//请求查询经纪公司交易算法响应
{
	pSpi->cbRspQryBrokerTradingAlgos = cb;
}
TDAPI_API void   RegRtnFromBankToFutureByBank(TraderSpi* pSpi, CBRtnFromBankToFutureByBank cb)	//银行发起银行资金转期货通知
{
	pSpi->cbRtnFromBankToFutureByBank = cb;
}
TDAPI_API void   RegRtnFromFutureToBankByBank(TraderSpi* pSpi, CBRtnFromFutureToBankByBank cb)	//银行发起期货资金转银行通知
{
	pSpi->cbRtnFromFutureToBankByBank = cb;
}
TDAPI_API void   RegRtnRepealFromBankToFutureByBank(TraderSpi* pSpi, CBRtnRepealFromBankToFutureByBank cb)	//银行发起冲正银行转期货通知
{
	pSpi->cbRtnRepealFromBankToFutureByBank = cb;
}
TDAPI_API void   RegRtnRepealFromFutureToBankByBank(TraderSpi* pSpi, CBRtnRepealFromFutureToBankByBank cb)	//银行发起冲正期货转银行通知
{
	pSpi->cbRtnRepealFromFutureToBankByBank = cb;
}
TDAPI_API void   RegRtnFromBankToFutureByFuture(TraderSpi* pSpi, CBRtnFromBankToFutureByFuture cb)	//期货发起银行资金转期货通知
{
	pSpi->cbRtnFromBankToFutureByFuture = cb;
}
TDAPI_API void   RegRtnFromFutureToBankByFuture(TraderSpi* pSpi, CBRtnFromFutureToBankByFuture cb)	//期货发起期货资金转银行通知
{
	pSpi->cbRtnFromFutureToBankByFuture = cb;
}
TDAPI_API void   RegRtnRepealFromBankToFutureByFutureManual(TraderSpi* pSpi, CBRtnRepealFromBankToFutureByFutureManual cb)	//系统运行时期货端手工发起冲正银行转期货请求，银行处理完毕后报盘发回的通知
{
	pSpi->cbRtnRepealFromBankToFutureByFutureManual = cb;
}
TDAPI_API void   RegRtnRepealFromFutureToBankByFutureManual(TraderSpi* pSpi, CBRtnRepealFromFutureToBankByFutureManual cb)	//系统运行时期货端手工发起冲正期货转银行请求，银行处理完毕后报盘发回的通知
{
	pSpi->cbRtnRepealFromFutureToBankByFutureManual = cb;
}
TDAPI_API void   RegRtnQueryBankBalanceByFuture(TraderSpi* pSpi, CBRtnQueryBankBalanceByFuture cb)	//期货发起查询银行余额通知
{
	pSpi->cbRtnQueryBankBalanceByFuture = cb;
}
TDAPI_API void   RegErrRtnBankToFutureByFuture(TraderSpi* pSpi, CBErrRtnBankToFutureByFuture cb)	//期货发起银行资金转期货错误回报
{
	pSpi->cbErrRtnBankToFutureByFuture = cb;
}
TDAPI_API void   RegErrRtnFutureToBankByFuture(TraderSpi* pSpi, CBErrRtnFutureToBankByFuture cb)	//期货发起期货资金转银行错误回报
{
	pSpi->cbErrRtnFutureToBankByFuture = cb;
}
TDAPI_API void   RegErrRtnRepealBankToFutureByFutureManual(TraderSpi* pSpi, CBErrRtnRepealBankToFutureByFutureManual cb)	//系统运行时期货端手工发起冲正银行转期货错误回报
{
	pSpi->cbErrRtnRepealBankToFutureByFutureManual = cb;
}
TDAPI_API void   RegErrRtnRepealFutureToBankByFutureManual(TraderSpi* pSpi, CBErrRtnRepealFutureToBankByFutureManual cb)	//系统运行时期货端手工发起冲正期货转银行错误回报
{
	pSpi->cbErrRtnRepealFutureToBankByFutureManual = cb;
}
TDAPI_API void   RegErrRtnQueryBankBalanceByFuture(TraderSpi* pSpi, CBErrRtnQueryBankBalanceByFuture cb)	//期货发起查询银行余额错误回报
{
	pSpi->cbErrRtnQueryBankBalanceByFuture = cb;
}
TDAPI_API void   RegRtnRepealFromBankToFutureByFuture(TraderSpi* pSpi, CBRtnRepealFromBankToFutureByFuture cb)	//期货发起冲正银行转期货请求，银行处理完毕后报盘发回的通知
{
	pSpi->cbRtnRepealFromBankToFutureByFuture = cb;
}
TDAPI_API void   RegRtnRepealFromFutureToBankByFuture(TraderSpi* pSpi, CBRtnRepealFromFutureToBankByFuture cb)	//期货发起冲正期货转银行请求，银行处理完毕后报盘发回的通知
{
	pSpi->cbRtnRepealFromFutureToBankByFuture = cb;
}
TDAPI_API void   RegRspFromBankToFutureByFuture(TraderSpi* pSpi, CBRspFromBankToFutureByFuture cb)	//期货发起银行资金转期货应答
{
	pSpi->cbRspFromBankToFutureByFuture = cb;
}
TDAPI_API void   RegRspFromFutureToBankByFuture(TraderSpi* pSpi, CBRspFromFutureToBankByFuture cb)	//期货发起期货资金转银行应答
{
	pSpi->cbRspFromFutureToBankByFuture = cb;
}
TDAPI_API void   RegRspQueryBankAccountMoneyByFuture(TraderSpi* pSpi, CBRspQueryBankAccountMoneyByFuture cb)	//期货发起查询银行余额应答
{
	pSpi->cbRspQueryBankAccountMoneyByFuture = cb;
}
TDAPI_API void   RegRspQueryCFMMCTradingAccountToken(TraderSpi* pSpi, CBRspQueryCFMMCTradingAccountToken cb)	//查询监控中心用户令牌应答
{
	pSpi->cbRspQueryCFMMCTradingAccountToken = cb;
}
TDAPI_API void   RegRtnCFMMCTradingAccountToken(TraderSpi* pSpi, CBRtnCFMMCTradingAccountToken cb)	//查询监控中心用户令牌通知
{
	pSpi->cbRtnCFMMCTradingAccountToken = cb;
}



