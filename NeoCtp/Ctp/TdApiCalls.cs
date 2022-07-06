/********************************************************************
    created:	2020-08-11 15:18:04
    author:		rush
    email:		
	
    purpose:	([(])(.+)([*])  $1 ref $2
*********************************************************************/
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace NeoCtp
{
	internal class TdApiCalls
	{

		[DllImport("CtpTdApiWrapper", EntryPoint = "CreateFtdcTraderApi", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static IntPtr CreateFtdcTraderApi(string pszFlowPath = "");
		[DllImport("CtpTdApiWrapper", EntryPoint = "CreateTdSpi", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static IntPtr CreateTdSpi();
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegisterSpi", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void		RegisterSpi(IntPtr api, IntPtr pSpi);

		[DllImport("CtpTdApiWrapper", EntryPoint = "GetApiVersion", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static IntPtr GetApiVersion();

		[DllImport("CtpTdApiWrapper", EntryPoint = "Release", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void Release(IntPtr api);
		[DllImport("CtpTdApiWrapper", EntryPoint = "Init", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void Init(IntPtr api);
		[DllImport("CtpTdApiWrapper", EntryPoint = "Join", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static int Join(IntPtr api);

		[DllImport("CtpTdApiWrapper", EntryPoint = "GetTradingDay", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static IntPtr GetTradingDay(IntPtr api);

		[DllImport("CtpTdApiWrapper", EntryPoint = "RegisterFront", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void RegisterFront(IntPtr api, string pszFrontAddress);
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegisterNameServer", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void RegisterNameServer(IntPtr api, string pszNsAddress);
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegisterFensUserInfo", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void RegisterFensUserInfo(IntPtr api, ref CThostFtdcFensUserInfoField pFensUserInfo);

		[DllImport("CtpTdApiWrapper", EntryPoint = "SubscribePrivateTopic", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void SubscribePrivateTopic(IntPtr api, THOST_TE_RESUME_TYPE nResumeType);
		[DllImport("CtpTdApiWrapper", EntryPoint = "SubscribePublicTopic", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void SubscribePublicTopic(IntPtr api, THOST_TE_RESUME_TYPE nResumeType);

		#region Login/out

		//客户端认证请求
		[DllImport("CtpTdApiWrapper", EntryPoint = "ReqAuthenticate", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static int ReqAuthenticate(IntPtr pApi, ref CThostFtdcReqAuthenticateField field, int nRequestID);


		///注册用户终端信息，用于中继服务器多连接模式
		///需要在终端认证成功后，用户登录前调用该接口
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegisterUserSystemInfo", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static int RegisterUserSystemInfo(IntPtr pApi, ref CThostFtdcUserSystemInfoField pUserSystemInfo);
		///上报用户终端信息，用于中继服务器操作员登录模式
		///操作员登录后，可以多次调用该接口上报客户信息
		[DllImport("CtpTdApiWrapper", EntryPoint = "SubmitUserSystemInfo", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static int SubmitUserSystemInfo(IntPtr pApi, ref CThostFtdcUserSystemInfoField pUserSystemInfo);


		//发送用户登录请求
		[DllImport("CtpTdApiWrapper", EntryPoint = "ReqUserLogin", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static int ReqUserLogin(IntPtr pApi, ref CThostFtdcReqUserLoginField pReqUserLoginField, int nRequestID);
		//发送登出请求
		[DllImport("CtpTdApiWrapper", EntryPoint = "ReqUserLogout", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static int ReqUserLogout(IntPtr pApi, ref CThostFtdcUserLogoutField pUserLogout, int nRequestID);


		///用户口令更新请求
		[DllImport("CtpTdApiWrapper", EntryPoint = "ReqUserPasswordUpdate", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static int ReqUserPasswordUpdate(IntPtr pApi, ref CThostFtdcUserPasswordUpdateField pUserPasswordUpdate, int nRequestID);

		///资金账户口令更新请求
		[DllImport("CtpTdApiWrapper", EntryPoint = "ReqTradingAccountPasswordUpdate", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static int ReqTradingAccountPasswordUpdate(IntPtr pApi, ref CThostFtdcTradingAccountPasswordUpdateField pTradingAccountPasswordUpdate, int nRequestID);

		///查询用户当前支持的认证模式
		[DllImport("CtpTdApiWrapper", EntryPoint = "ReqUserAuthMethod", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static int ReqUserAuthMethod(IntPtr pApi, ref CThostFtdcReqUserAuthMethodField pReqUserAuthMethod, int nRequestID);

		///用户发出获取图形验证码请求
		[DllImport("CtpTdApiWrapper", EntryPoint = "ReqGenUserCaptcha", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static int ReqGenUserCaptcha(IntPtr pApi, ref CThostFtdcReqGenUserCaptchaField pReqGenUserCaptcha, int nRequestID);

		///用户发出获取短信验证码请求
		[DllImport("CtpTdApiWrapper", EntryPoint = "ReqGenUserText", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static int ReqGenUserText(IntPtr pApi, ref CThostFtdcReqGenUserTextField pReqGenUserText, int nRequestID);

		///用户发出带有图片验证码的登陆请求
		[DllImport("CtpTdApiWrapper", EntryPoint = "ReqUserLoginWithCaptcha", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static int ReqUserLoginWithCaptcha(IntPtr pApi, ref CThostFtdcReqUserLoginWithCaptchaField pReqUserLoginWithCaptcha, int nRequestID);

		///用户发出带有短信验证码的登陆请求
		[DllImport("CtpTdApiWrapper", EntryPoint = "ReqUserLoginWithText", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static int ReqUserLoginWithText(IntPtr pApi, ref CThostFtdcReqUserLoginWithTextField pReqUserLoginWithText, int nRequestID);

		///用户发出带有动态口令的登陆请求
		[DllImport("CtpTdApiWrapper", EntryPoint = "ReqUserLoginWithOTP", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static int ReqUserLoginWithOTP(IntPtr pApi, ref CThostFtdcReqUserLoginWithOTPField pReqUserLoginWithOTP, int nRequestID);
		#endregion


		///请求查询询价
		[DllImport("CtpTdApiWrapper", EntryPoint = "ReqQryForQuote", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static int ReqQryForQuote(IntPtr pApi, ref CThostFtdcQryForQuoteField pQryForQuote, int nRequestID);
		///请求查询报价
		[DllImport("CtpTdApiWrapper", EntryPoint = "ReqQryQuote", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static int ReqQryQuote(IntPtr pApi, ref CThostFtdcQryQuoteField pQryQuote, int nRequestID);
		///请求查询行情
		[DllImport("CtpTdApiWrapper", EntryPoint = "ReqQryDepthMarketData", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static int ReqQryDepthMarketData(IntPtr pApi, ref CThostFtdcQryDepthMarketDataField pQryDepthMarketData, int nRequestID);

		///报单录入请求
		[DllImport("CtpTdApiWrapper", EntryPoint = "ReqOrderInsert", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static int ReqOrderInsert(IntPtr pApi, ref CThostFtdcInputOrderField pInputOrder, int nRequestID);
		///请求查询报单
		[DllImport("CtpTdApiWrapper", EntryPoint = "ReqQryOrder", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static int ReqQryOrder(IntPtr pApi, ref CThostFtdcQryOrderField pQryOrder, int nRequestID);
		///查询最大报单数量请求
		[DllImport("CtpTdApiWrapper", EntryPoint = "ReqQueryMaxOrderVolume", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static int ReqQueryMaxOrderVolume(IntPtr pApi, ref CThostFtdcQueryMaxOrderVolumeField pQueryMaxOrderVolume, int nRequestID);
		///报单操作请求
		[DllImport("CtpTdApiWrapper", EntryPoint = "ReqOrderAction", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static int ReqOrderAction(IntPtr pApi, ref CThostFtdcInputOrderActionField pInputOrderAction, int nRequestID);
		///批量报单操作请求
		[DllImport("CtpTdApiWrapper", EntryPoint = "ReqBatchOrderAction", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static int ReqBatchOrderAction(IntPtr pApi, ref CThostFtdcInputBatchOrderActionField pInputBatchOrderAction, int nRequestID);

		///请求查询成交
		[DllImport("CtpTdApiWrapper", EntryPoint = "ReqQryTrade", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static int ReqQryTrade(IntPtr pApi, ref CThostFtdcQryTradeField pQryTrade, int nRequestID);

		///预埋单录入请求
		[DllImport("CtpTdApiWrapper", EntryPoint = "ReqParkedOrderInsert", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static int ReqParkedOrderInsert(IntPtr pApi, ref CThostFtdcParkedOrderField pParkedOrder, int nRequestID);
		///预埋撤单录入请求
		[DllImport("CtpTdApiWrapper", EntryPoint = "ReqParkedOrderAction", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static int ReqParkedOrderAction(IntPtr pApi, ref CThostFtdcParkedOrderActionField pParkedOrderAction, int nRequestID);
		///请求删除预埋单
		[DllImport("CtpTdApiWrapper", EntryPoint = "ReqRemoveParkedOrder", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static int ReqRemoveParkedOrder(IntPtr pApi, ref CThostFtdcRemoveParkedOrderField pRemoveParkedOrder, int nRequestID);
		///请求删除预埋撤单
		[DllImport("CtpTdApiWrapper", EntryPoint = "ReqRemoveParkedOrderAction", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static int ReqRemoveParkedOrderAction(IntPtr pApi, ref CThostFtdcRemoveParkedOrderActionField pRemoveParkedOrderAction, int nRequestID);
		///请求查询预埋单
		[DllImport("CtpTdApiWrapper", EntryPoint = "ReqQryParkedOrder", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static int ReqQryParkedOrder(IntPtr pApi, ref CThostFtdcQryParkedOrderField pQryParkedOrder, int nRequestID);
		///请求查询预埋撤单
		[DllImport("CtpTdApiWrapper", EntryPoint = "ReqQryParkedOrderAction", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static int ReqQryParkedOrderAction(IntPtr pApi, ref CThostFtdcQryParkedOrderActionField pQryParkedOrderAction, int nRequestID);

		///请求查询客户通知
		[DllImport("CtpTdApiWrapper", EntryPoint = "ReqQryNotice", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static int ReqQryNotice(IntPtr pApi, ref CThostFtdcQryNoticeField pQryNotice, int nRequestID);
		///请求查询交易通知
		[DllImport("CtpTdApiWrapper", EntryPoint = "ReqQryTradingNotice", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static int ReqQryTradingNotice(IntPtr pApi, ref CThostFtdcQryTradingNoticeField pQryTradingNotice, int nRequestID);


		///请求查询执行宣告
		[DllImport("CtpTdApiWrapper", EntryPoint = "ReqQryExecOrder", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static int ReqQryExecOrder(IntPtr pApi, ref CThostFtdcQryExecOrderField pQryExecOrder, int nRequestID);
		///执行宣告录入请求
		[DllImport("CtpTdApiWrapper", EntryPoint = "ReqExecOrderInsert", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static int ReqExecOrderInsert(IntPtr pApi, ref CThostFtdcInputExecOrderField pInputExecOrder, int nRequestID);
		///执行宣告操作请求
		[DllImport("CtpTdApiWrapper", EntryPoint = "ReqExecOrderAction", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static int ReqExecOrderAction(IntPtr pApi, ref CThostFtdcInputExecOrderActionField pInputExecOrderAction, int nRequestID);


		///询价录入请求
		[DllImport("CtpTdApiWrapper", EntryPoint = "ReqForQuoteInsert", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static int ReqForQuoteInsert(IntPtr pApi, ref CThostFtdcInputForQuoteField pInputForQuote, int nRequestID);
		///报价录入请求
		[DllImport("CtpTdApiWrapper", EntryPoint = "ReqQuoteInsert", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static int ReqQuoteInsert(IntPtr pApi, ref CThostFtdcInputQuoteField pInputQuote, int nRequestID);
		///报价操作请求
		[DllImport("CtpTdApiWrapper", EntryPoint = "ReqQuoteAction", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static int ReqQuoteAction(IntPtr pApi, ref CThostFtdcInputQuoteActionField pInputQuoteAction, int nRequestID);



		///申请组合录入请求
		[DllImport("CtpTdApiWrapper", EntryPoint = "ReqCombActionInsert", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static int ReqCombActionInsert(IntPtr pApi, ref CThostFtdcInputCombActionField pInputCombAction, int nRequestID);
		///请求查询组合合约安全系数
		[DllImport("CtpTdApiWrapper", EntryPoint = "ReqQryCombInstrumentGuard", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static int ReqQryCombInstrumentGuard(IntPtr pApi, ref CThostFtdcQryCombInstrumentGuardField pQryCombInstrumentGuard, int nRequestID);
		///请求查询申请组合
		[DllImport("CtpTdApiWrapper", EntryPoint = "ReqQryCombAction", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static int ReqQryCombAction(IntPtr pApi, ref CThostFtdcQryCombActionField pQryCombAction, int nRequestID);


		///请求查询投资者持仓
		[DllImport("CtpTdApiWrapper", EntryPoint = "ReqQryInvestorPosition", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static int ReqQryInvestorPosition(IntPtr pApi, ref CThostFtdcQryInvestorPositionField pQryInvestorPosition, int nRequestID);
		///请求查询投资者持仓明细
		[DllImport("CtpTdApiWrapper", EntryPoint = "ReqQryInvestorPositionDetail", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static int ReqQryInvestorPositionDetail(IntPtr pApi, ref CThostFtdcQryInvestorPositionDetailField pQryInvestorPositionDetail, int nRequestID);
		///请求查询投资者持仓明细
		[DllImport("CtpTdApiWrapper", EntryPoint = "ReqQryInvestorPositionCombineDetail", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static int ReqQryInvestorPositionCombineDetail(IntPtr pApi, ref CThostFtdcQryInvestorPositionCombineDetailField pQryInvestorPositionCombineDetail, int nRequestID);
		///请求查询资金账户
		[DllImport("CtpTdApiWrapper", EntryPoint = "ReqQryTradingAccount", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static int ReqQryTradingAccount(IntPtr pApi, ref CThostFtdcQryTradingAccountField pQryTradingAccount, int nRequestID);
		///请求查询投资者
		[DllImport("CtpTdApiWrapper", EntryPoint = "ReqQryInvestor", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static int ReqQryInvestor(IntPtr pApi, ref CThostFtdcQryInvestorField pQryInvestor, int nRequestID);
		///请求查询交易编码
		[DllImport("CtpTdApiWrapper", EntryPoint = "ReqQryTradingCode", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static int ReqQryTradingCode(IntPtr pApi, ref CThostFtdcQryTradingCodeField pQryTradingCode, int nRequestID);
		///请求查询投资者结算结果
		[DllImport("CtpTdApiWrapper", EntryPoint = "ReqQrySettlementInfo", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static int ReqQrySettlementInfo(IntPtr pApi, ref CThostFtdcQrySettlementInfoField pQrySettlementInfo, int nRequestID);
		///请求查询结算信息确认
		[DllImport("CtpTdApiWrapper", EntryPoint = "ReqQrySettlementInfoConfirm", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static int ReqQrySettlementInfoConfirm(IntPtr pApi, ref CThostFtdcQrySettlementInfoConfirmField pQrySettlementInfoConfirm, int nRequestID);
		///投资者结算结果确认
		[DllImport("CtpTdApiWrapper", EntryPoint = "ReqSettlementInfoConfirm", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static int ReqSettlementInfoConfirm(IntPtr pApi, ref CThostFtdcSettlementInfoConfirmField pSettlementInfoConfirm, int nRequestID);
		///请求查询投资单元
		[DllImport("CtpTdApiWrapper", EntryPoint = "ReqQryInvestUnit", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static int ReqQryInvestUnit(IntPtr pApi, ref CThostFtdcQryInvestUnitField pQryInvestUnit, int nRequestID);


#pragma region product/Instrument
		///请求查询产品
		[DllImport("CtpTdApiWrapper", EntryPoint = "ReqQryProduct", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static int ReqQryProduct(IntPtr pApi, ref CThostFtdcQryProductField pQryProduct, int nRequestID);
		///请求查询产品报价汇率
		[DllImport("CtpTdApiWrapper", EntryPoint = "ReqQryProductExchRate", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static int ReqQryProductExchRate(IntPtr pApi, ref CThostFtdcQryProductExchRateField pQryProductExchRate, int nRequestID);
		///请求查询产品组
		[DllImport("CtpTdApiWrapper", EntryPoint = "ReqQryProductGroup", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static int ReqQryProductGroup(IntPtr pApi, ref CThostFtdcQryProductGroupField pQryProductGroup, int nRequestID);

		///请求查询合约
		[DllImport("CtpTdApiWrapper", EntryPoint = "ReqQryInstrument", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static int ReqQryInstrument(IntPtr pApi, ref CThostFtdcQryInstrumentField pQryInstrument, int nRequestID);
		///请求查询合约保证金率
		[DllImport("CtpTdApiWrapper", EntryPoint = "ReqQryInstrumentMarginRate", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static int ReqQryInstrumentMarginRate(IntPtr pApi, ref CThostFtdcQryInstrumentMarginRateField pQryInstrumentMarginRate, int nRequestID);
		///请求查询合约手续费率
		[DllImport("CtpTdApiWrapper", EntryPoint = "ReqQryInstrumentCommissionRate", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static int ReqQryInstrumentCommissionRate(IntPtr pApi, ref CThostFtdcQryInstrumentCommissionRateField pQryInstrumentCommissionRate, int nRequestID);

		///请求查询投资者品种/跨品种保证金
		[DllImport("CtpTdApiWrapper", EntryPoint = "ReqQryInvestorProductGroupMargin", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static int ReqQryInvestorProductGroupMargin(IntPtr pApi, ref CThostFtdcQryInvestorProductGroupMarginField pQryInvestorProductGroupMargin, int nRequestID);

		///请求查询做市商合约手续费率
		[DllImport("CtpTdApiWrapper", EntryPoint = "ReqQryMMInstrumentCommissionRate", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static int ReqQryMMInstrumentCommissionRate(IntPtr pApi, ref CThostFtdcQryMMInstrumentCommissionRateField pQryMMInstrumentCommissionRate, int nRequestID);
		///请求查询做市商期权合约手续费
		[DllImport("CtpTdApiWrapper", EntryPoint = "ReqQryMMOptionInstrCommRate", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static int ReqQryMMOptionInstrCommRate(IntPtr pApi, ref CThostFtdcQryMMOptionInstrCommRateField pQryMMOptionInstrCommRate, int nRequestID);

		///请求查询仓单折抵信息
		[DllImport("CtpTdApiWrapper", EntryPoint = "ReqQryEWarrantOffset", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static int ReqQryEWarrantOffset(IntPtr pApi, ref CThostFtdcQryEWarrantOffsetField pQryEWarrantOffset, int nRequestID);

		///请求查询报单手续费
		[DllImport("CtpTdApiWrapper", EntryPoint = "ReqQryInstrumentOrderCommRate", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static int ReqQryInstrumentOrderCommRate(IntPtr pApi, ref CThostFtdcQryInstrumentOrderCommRateField pQryInstrumentOrderCommRate, int nRequestID);
#pragma endregion


#pragma region 二级代理/sec agent
		///请求查询资金账户
		[DllImport("CtpTdApiWrapper", EntryPoint = "ReqQrySecAgentTradingAccount", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static int ReqQrySecAgentTradingAccount(IntPtr pApi, ref CThostFtdcQryTradingAccountField pQryTradingAccount, int nRequestID);
		///请求查询二级代理操作员银期权限
		[DllImport("CtpTdApiWrapper", EntryPoint = "ReqQrySecAgentACIDMap", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static int ReqQrySecAgentACIDMap(IntPtr pApi, ref CThostFtdcQrySecAgentACIDMapField pQrySecAgentACIDMap, int nRequestID);
		///请求查询二级代理商资金校验模式
		[DllImport("CtpTdApiWrapper", EntryPoint = "ReqQrySecAgentCheckMode", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static int ReqQrySecAgentCheckMode(IntPtr pApi, ref CThostFtdcQrySecAgentCheckModeField pQrySecAgentCheckMode, int nRequestID);
		///请求查询二级代理商信息
		[DllImport("CtpTdApiWrapper", EntryPoint = "ReqQrySecAgentTradeInfo", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static int ReqQrySecAgentTradeInfo(IntPtr pApi, ref CThostFtdcQrySecAgentTradeInfoField pQrySecAgentTradeInfo, int nRequestID);
#pragma endregion


#pragma region 期权option
		///期权自对冲录入请求
		[DllImport("CtpTdApiWrapper", EntryPoint = "ReqOptionSelfCloseInsert", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static int ReqOptionSelfCloseInsert(IntPtr pApi, ref CThostFtdcInputOptionSelfCloseField pInputOptionSelfClose, int nRequestID);
		///期权自对冲操作请求
		[DllImport("CtpTdApiWrapper", EntryPoint = "ReqOptionSelfCloseAction", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static int ReqOptionSelfCloseAction(IntPtr pApi, ref CThostFtdcInputOptionSelfCloseActionField pInputOptionSelfCloseAction, int nRequestID);

		///请求查询期权交易成本
		[DllImport("CtpTdApiWrapper", EntryPoint = "ReqQryOptionInstrTradeCost", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static int ReqQryOptionInstrTradeCost(IntPtr pApi, ref CThostFtdcQryOptionInstrTradeCostField pQryOptionInstrTradeCost, int nRequestID);
		///请求查询期权合约手续费
		[DllImport("CtpTdApiWrapper", EntryPoint = "ReqQryOptionInstrCommRate", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static int ReqQryOptionInstrCommRate(IntPtr pApi, ref CThostFtdcQryOptionInstrCommRateField pQryOptionInstrCommRate, int nRequestID);
		///请求查询期权自对冲
		[DllImport("CtpTdApiWrapper", EntryPoint = "ReqQryOptionSelfClose", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static int ReqQryOptionSelfClose(IntPtr pApi, ref CThostFtdcQryOptionSelfCloseField pQryOptionSelfClose, int nRequestID);
#pragma endregion


#pragma region Banking
		///请求查询转帐银行
		[DllImport("CtpTdApiWrapper", EntryPoint = "ReqQryTransferBank", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static int ReqQryTransferBank(IntPtr pApi, ref CThostFtdcQryTransferBankField pQryTransferBank, int nRequestID);
		///请求查询银期签约关系
		[DllImport("CtpTdApiWrapper", EntryPoint = "ReqQryAccountregister", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static int ReqQryAccountregister(IntPtr pApi, ref CThostFtdcQryAccountregisterField pQryAccountregister, int nRequestID);
		///请求查询签约银行
		[DllImport("CtpTdApiWrapper", EntryPoint = "ReqQryContractBank", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static int ReqQryContractBank(IntPtr pApi, ref CThostFtdcQryContractBankField pQryContractBank, int nRequestID);
		///请求查询转帐流水
		[DllImport("CtpTdApiWrapper", EntryPoint = "ReqQryTransferSerial", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static int ReqQryTransferSerial(IntPtr pApi, ref CThostFtdcQryTransferSerialField pQryTransferSerial, int nRequestID);
		///期货发起查询银行余额请求
		[DllImport("CtpTdApiWrapper", EntryPoint = "ReqQueryBankAccountMoneyByFuture", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static int ReqQueryBankAccountMoneyByFuture(IntPtr pApi, ref CThostFtdcReqQueryAccountField pReqQueryAccount, int nRequestID);

		///期货发起银行资金转期货请求
		[DllImport("CtpTdApiWrapper", EntryPoint = "ReqFromBankToFutureByFuture", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static int ReqFromBankToFutureByFuture(IntPtr pApi, ref CThostFtdcReqTransferField pReqTransfer, int nRequestID);
		///期货发起期货资金转银行请求
		[DllImport("CtpTdApiWrapper", EntryPoint = "ReqFromFutureToBankByFuture", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static int ReqFromFutureToBankByFuture(IntPtr pApi, ref CThostFtdcReqTransferField pReqTransfer, int nRequestID);
#pragma endregion


#region Exchange/交易所
		///请求查询交易所
		[DllImport("CtpTdApiWrapper", EntryPoint = "ReqQryExchange", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static int ReqQryExchange(IntPtr pApi, ref CThostFtdcQryExchangeField pQryExchange, int nRequestID);
		///请求查询交易所保证金率
		[DllImport("CtpTdApiWrapper", EntryPoint = "ReqQryExchangeMarginRate", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static int ReqQryExchangeMarginRate(IntPtr pApi, ref CThostFtdcQryExchangeMarginRateField pQryExchangeMarginRate, int nRequestID);
		///请求查询交易所调整保证金率
		[DllImport("CtpTdApiWrapper", EntryPoint = "ReqQryExchangeMarginRateAdjust", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static int ReqQryExchangeMarginRateAdjust(IntPtr pApi, ref CThostFtdcQryExchangeMarginRateAdjustField pQryExchangeMarginRateAdjust, int nRequestID);
		///请求查询汇率
		[DllImport("CtpTdApiWrapper", EntryPoint = "ReqQryExchangeRate", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static int ReqQryExchangeRate(IntPtr pApi, ref CThostFtdcQryExchangeRateField pQryExchangeRate, int nRequestID);
#endregion


#pragma region Broker
		///请求查询经纪公司交易参数
		[DllImport("CtpTdApiWrapper", EntryPoint = "ReqQryBrokerTradingParams", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static int ReqQryBrokerTradingParams(IntPtr pApi, ref CThostFtdcQryBrokerTradingParamsField pQryBrokerTradingParams, int nRequestID);
		///请求查询经纪公司交易算法
		[DllImport("CtpTdApiWrapper", EntryPoint = "ReqQryBrokerTradingAlgos", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static int ReqQryBrokerTradingAlgos(IntPtr pApi, ref CThostFtdcQryBrokerTradingAlgosField pQryBrokerTradingAlgos, int nRequestID);
#pragma endregion

#region  CFMMC
		///请求查询监控中心用户令牌
		[DllImport("CtpTdApiWrapper", EntryPoint = "ReqQueryCFMMCTradingAccountToken", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static int ReqQueryCFMMCTradingAccountToken(IntPtr pApi, ref CThostFtdcQueryCFMMCTradingAccountTokenField pQueryCFMMCTradingAccountToken, int nRequestID);

		///请求查询保证金监管系统经纪公司资金账户密钥
		[DllImport("CtpTdApiWrapper", EntryPoint = "ReqQryCFMMCTradingAccountKey", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static int ReqQryCFMMCTradingAccountKey(IntPtr pApi, ref CThostFtdcQryCFMMCTradingAccountKeyField pQryCFMMCTradingAccountKey, int nRequestID);
		#endregion



#pragma region 回调函数 [(] [*](.+)[)][(] -> 
		//========================================

		///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
		internal delegate void CBOnRspFrontConnected();

		///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
		internal delegate void CBOnFrontDisconnected(int nReason);

		///心跳超时警告。当长时间未收到报文时，该方法被调用。
		internal delegate void CBOnHeartBeatWarning(int nTimeLapse);
		///客户端认证响应
		internal delegate void CBOnRspAuthenticate(ref CThostFtdcRspAuthenticateField pRspAuthenticateField, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
		///登录请求响应
		internal delegate void CBOnRspUserLogin( ref CThostFtdcRspUserLoginField pRspUserLogin, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
		///登出请求响应
		internal delegate void CBOnRspUserLogout( ref CThostFtdcUserLogoutField pUserLogout, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
		///用户口令更新请求响应
		internal delegate void CBRspUserPasswordUpdate( ref CThostFtdcUserPasswordUpdateField pUserPasswordUpdate, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
		///资金账户口令更新请求响应
		internal delegate void CBRspTradingAccountPasswordUpdate( ref CThostFtdcTradingAccountPasswordUpdateField pTradingAccountPasswordUpdate, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
		///查询用户当前支持的认证模式的回复
		internal delegate void CBRspUserAuthMethod( ref CThostFtdcRspUserAuthMethodField pRspUserAuthMethod, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
		///获取图形验证码请求的回复
		internal delegate void CBRspGenUserCaptcha( ref CThostFtdcRspGenUserCaptchaField pRspGenUserCaptcha, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
		///获取短信验证码请求的回复
		internal delegate void CBRspGenUserText( ref CThostFtdcRspGenUserTextField pRspGenUserText, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
		///报单录入请求响应
		internal delegate void CBOnRspOrderInsert( ref CThostFtdcInputOrderField pInputOrder, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
		///预埋单录入请求响应
		internal delegate void CBRspParkedOrderInsert( ref CThostFtdcParkedOrderField pParkedOrder, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
		///预埋撤单录入请求响应
		internal delegate void CBRspParkedOrderAction( ref CThostFtdcParkedOrderActionField pParkedOrderAction, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
		///报单操作请求响应
		internal delegate void CBRspOrderAction( ref CThostFtdcInputOrderActionField pInputOrderAction, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
		///查询最大报单数量响应
		internal delegate void CBRspQueryMaxOrderVolume( ref CThostFtdcQueryMaxOrderVolumeField pQueryMaxOrderVolume, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
		///投资者结算结果确认响应
		internal delegate void CBOnRspSettlementInfoConfirm( ref CThostFtdcSettlementInfoConfirmField pSettlementInfoConfirm, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
		///删除预埋单响应
		internal delegate void CBRspRemoveParkedOrder( ref CThostFtdcRemoveParkedOrderField pRemoveParkedOrder, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
		///删除预埋撤单响应
		internal delegate void CBRspRemoveParkedOrderAction( ref CThostFtdcRemoveParkedOrderActionField pRemoveParkedOrderAction, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
		///执行宣告录入请求响应
		internal delegate void CBRspExecOrderInsert( ref CThostFtdcInputExecOrderField pInputExecOrder, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
		///执行宣告操作请求响应
		internal delegate void CBRspExecOrderAction( ref CThostFtdcInputExecOrderActionField pInputExecOrderAction, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
		///询价录入请求响应
		internal delegate void CBRspForQuoteInsert( ref CThostFtdcInputForQuoteField pInputForQuote, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
		///报价录入请求响应
		internal delegate void CBRspQuoteInsert( ref CThostFtdcInputQuoteField pInputQuote, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
		///报价操作请求响应
		internal delegate void CBRspQuoteAction( ref CThostFtdcInputQuoteActionField pInputQuoteAction, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
		///批量报单操作请求响应
		internal delegate void CBRspBatchOrderAction( ref CThostFtdcInputBatchOrderActionField pInputBatchOrderAction, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
		///期权自对冲录入请求响应
		internal delegate void CBRspOptionSelfCloseInsert( ref CThostFtdcInputOptionSelfCloseField pInputOptionSelfClose, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
		///期权自对冲操作请求响应
		internal delegate void CBRspOptionSelfCloseAction( ref CThostFtdcInputOptionSelfCloseActionField pInputOptionSelfCloseAction, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
		///申请组合录入请求响应
		internal delegate void CBRspCombActionInsert( ref CThostFtdcInputCombActionField pInputCombAction, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
		///请求查询报单响应
		internal delegate void CBRspQryOrder( ref CThostFtdcOrderField pOrder, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
		///请求查询成交响应
		internal delegate void CBRspQryTrade( ref CThostFtdcTradeField pTrade, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
		///请求查询投资者持仓响应
		internal delegate void CBRspQryInvestorPosition( ref CThostFtdcInvestorPositionField pInvestorPosition, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
		///请求查询资金账户响应
		internal delegate void CBRspQryTradingAccount( ref CThostFtdcTradingAccountField pTradingAccount, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
		///请求查询投资者响应
		internal delegate void CBRspQryInvestor( ref CThostFtdcInvestorField pInvestor, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
		///请求查询交易编码响应
		internal delegate void CBRspQryTradingCode( ref CThostFtdcTradingCodeField pTradingCode, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
		///请求查询合约保证金率响应
		internal delegate void CBRspQryInstrumentMarginRate( ref CThostFtdcInstrumentMarginRateField pInstrumentMarginRate, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
		///请求查询合约手续费率响应
		internal delegate void CBRspQryInstrumentCommissionRate( ref CThostFtdcInstrumentCommissionRateField pInstrumentCommissionRate, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
		///请求查询交易所响应
		internal delegate void CBRspQryExchange( ref CThostFtdcExchangeField pExchange, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
		///请求查询合约响应
		internal delegate void CBRspQryInstrument( ref CThostFtdcInstrumentField pInstrument, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
		///请求查询行情响应
		internal delegate void CBRspQryDepthMarketData( ref CThostFtdcDepthMarketDataField pDepthMarketData, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
		///请求查询投资者结算结果响应
		internal delegate void CBRspQrySettlementInfo( ref CThostFtdcSettlementInfoField pSettlementInfo, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
		///请求查询转帐银行响应
		internal delegate void CBRspQryTransferBank( ref CThostFtdcTransferBankField pTransferBank, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
		///请求查询投资者持仓明细响应
		internal delegate void CBRspQryInvestorPositionDetail( ref CThostFtdcInvestorPositionDetailField pInvestorPositionDetail, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
		///请求查询客户通知响应
		internal delegate void CBRspQryNotice( ref CThostFtdcNoticeField pNotice, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
		///请求查询结算信息确认响应
		internal delegate void CBRspQrySettlementInfoConfirm( ref CThostFtdcSettlementInfoConfirmField pSettlementInfoConfirm, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
		///请求查询投资者持仓明细响应
		internal delegate void CBRspQryInvestorPositionCombineDetail( ref CThostFtdcInvestorPositionCombineDetailField pInvestorPositionCombineDetail, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
		///查询保证金监管系统经纪公司资金账户密钥响应
		internal delegate void CBRspQryCFMMCTradingAccountKey( ref CThostFtdcCFMMCTradingAccountKeyField pCFMMCTradingAccountKey, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
		///请求查询仓单折抵信息响应
		internal delegate void CBRspQryEWarrantOffset( ref CThostFtdcEWarrantOffsetField pEWarrantOffset, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
		///请求查询投资者品种/跨品种保证金响应
		internal delegate void CBRspQryInvestorProductGroupMargin( ref CThostFtdcInvestorProductGroupMarginField pInvestorProductGroupMargin, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
		///请求查询交易所保证金率响应
		internal delegate void CBRspQryExchangeMarginRate( ref CThostFtdcExchangeMarginRateField pExchangeMarginRate, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
		///请求查询交易所调整保证金率响应
		internal delegate void CBRspQryExchangeMarginRateAdjust( ref CThostFtdcExchangeMarginRateAdjustField pExchangeMarginRateAdjust, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
		///请求查询汇率响应
		internal delegate void CBRspQryExchangeRate( ref CThostFtdcExchangeRateField pExchangeRate, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
		///请求查询二级代理操作员银期权限响应
		internal delegate void CBRspQrySecAgentACIDMap( ref CThostFtdcSecAgentACIDMapField pSecAgentACIDMap, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
		///请求查询产品报价汇率
		internal delegate void CBRspQryProductExchRate( ref CThostFtdcProductExchRateField pProductExchRate, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
		///请求查询产品组
		internal delegate void CBRspQryProductGroup( ref CThostFtdcProductGroupField pProductGroup, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
		///请求查询做市商合约手续费率响应
		internal delegate void CBRspQryMMInstrumentCommissionRate( ref CThostFtdcMMInstrumentCommissionRateField pMMInstrumentCommissionRate, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
		///请求查询做市商期权合约手续费响应
		internal delegate void CBRspQryMMOptionInstrCommRate( ref CThostFtdcMMOptionInstrCommRateField pMMOptionInstrCommRate, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
		///请求查询报单手续费响应
		internal delegate void CBRspQryInstrumentOrderCommRate( ref CThostFtdcInstrumentOrderCommRateField pInstrumentOrderCommRate, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
		///请求查询资金账户响应
		internal delegate void CBRspQrySecAgentTradingAccount( ref CThostFtdcTradingAccountField pTradingAccount, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
		///请求查询二级代理商资金校验模式响应
		internal delegate void CBRspQrySecAgentCheckMode( ref CThostFtdcSecAgentCheckModeField pSecAgentCheckMode, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
		///请求查询二级代理商信息响应
		internal delegate void CBRspQrySecAgentTradeInfo( ref CThostFtdcSecAgentTradeInfoField pSecAgentTradeInfo, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
		///请求查询期权交易成本响应
		internal delegate void CBRspQryOptionInstrTradeCost( ref CThostFtdcOptionInstrTradeCostField pOptionInstrTradeCost, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
		///请求查询期权合约手续费响应
		internal delegate void CBRspQryOptionInstrCommRate( ref CThostFtdcOptionInstrCommRateField pOptionInstrCommRate, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
		///请求查询执行宣告响应
		internal delegate void CBRspQryExecOrder( ref CThostFtdcExecOrderField pExecOrder, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
		///请求查询询价响应
		internal delegate void CBRspQryForQuote( ref CThostFtdcForQuoteField pForQuote, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
		///请求查询报价响应
		internal delegate void CBRspQryQuote( ref CThostFtdcQuoteField pQuote, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
		///请求查询期权自对冲响应
		internal delegate void CBRspQryOptionSelfClose( ref CThostFtdcOptionSelfCloseField pOptionSelfClose, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
		///请求查询投资单元响应
		internal delegate void CBRspQryInvestUnit( ref CThostFtdcInvestUnitField pInvestUnit, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
		///请求查询组合合约安全系数响应
		internal delegate void CBRspQryCombInstrumentGuard( ref CThostFtdcCombInstrumentGuardField pCombInstrumentGuard, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
		///请求查询申请组合响应
		internal delegate void CBRspQryCombAction( ref CThostFtdcCombActionField pCombAction, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
		///请求查询转帐流水响应
		internal delegate void CBRspQryTransferSerial( ref CThostFtdcTransferSerialField pTransferSerial, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
		///请求查询银期签约关系响应
		internal delegate void CBRspQryAccountregister( ref CThostFtdcAccountregisterField pAccountregister, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);

		///错误应答
		internal delegate void CBOnRspError( ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
		//internal delegate void CBOnRspError( ref CThostFtdcRspInfoField pRspInfo, int nRequestID, [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.I1)] bIsLast);

		///报单通知
		internal delegate void CBRtnOrder( ref CThostFtdcOrderField pOrder);
		///成交通知
		internal delegate void CBRtnTrade( ref CThostFtdcTradeField pTrade);
		///报单录入错误回报
		internal delegate void CBErrRtnOrderInsert( ref CThostFtdcInputOrderField pInputOrder, ref CThostFtdcRspInfoField pRspInfo);
		///报单操作错误回报
		internal delegate void CBErrRtnOrderAction( ref CThostFtdcOrderActionField pOrderAction, ref CThostFtdcRspInfoField pRspInfo);
		///合约交易状态通知
		internal delegate void CBRtnInstrumentStatus( ref CThostFtdcInstrumentStatusField pInstrumentStatus);
		///交易通知
		internal delegate void CBRtnTradingNotice( ref CThostFtdcTradingNoticeInfoField pTradingNoticeInfo);
		///提示条件单校验错误
		internal delegate void CBRtnErrorConditionalOrder( ref CThostFtdcErrorConditionalOrderField pErrorConditionalOrder);
		///执行宣告通知
		internal delegate void CBRtnExecOrder( ref CThostFtdcExecOrderField pExecOrder);
		///执行宣告录入错误回报
		internal delegate void CBErrRtnExecOrderInsert( ref CThostFtdcInputExecOrderField pInputExecOrder, ref CThostFtdcRspInfoField pRspInfo);
		///执行宣告操作错误回报
		internal delegate void CBErrRtnExecOrderAction( ref CThostFtdcExecOrderActionField pExecOrderAction, ref CThostFtdcRspInfoField pRspInfo);
		///询价录入错误回报
		internal delegate void CBErrRtnForQuoteInsert( ref CThostFtdcInputForQuoteField pInputForQuote, ref CThostFtdcRspInfoField pRspInfo);
		///报价通知
		internal delegate void CBRtnQuote( ref CThostFtdcQuoteField pQuote);
		///报价录入错误回报
		internal delegate void CBErrRtnQuoteInsert( ref CThostFtdcInputQuoteField pInputQuote, ref CThostFtdcRspInfoField pRspInfo);
		///报价操作错误回报
		internal delegate void CBErrRtnQuoteAction( ref CThostFtdcQuoteActionField pQuoteAction, ref CThostFtdcRspInfoField pRspInfo);
		///询价通知
		internal delegate void CBRtnForQuoteRsp( ref CThostFtdcForQuoteRspField pForQuoteRsp);
		///保证金监控中心用户令牌
		internal delegate void CBRtnCFMMCTradingAccountToken( ref CThostFtdcCFMMCTradingAccountTokenField pCFMMCTradingAccountToken);
		///批量报单操作错误回报
		internal delegate void CBErrRtnBatchOrderAction( ref CThostFtdcBatchOrderActionField pBatchOrderAction, ref CThostFtdcRspInfoField pRspInfo);
		///期权自对冲通知
		internal delegate void CBRtnOptionSelfClose( ref CThostFtdcOptionSelfCloseField pOptionSelfClose);
		///期权自对冲录入错误回报
		internal delegate void CBErrRtnOptionSelfCloseInsert( ref CThostFtdcInputOptionSelfCloseField pInputOptionSelfClose, ref CThostFtdcRspInfoField pRspInfo);
		///期权自对冲操作错误回报
		internal delegate void CBErrRtnOptionSelfCloseAction( ref CThostFtdcOptionSelfCloseActionField pOptionSelfCloseAction, ref CThostFtdcRspInfoField pRspInfo);
		///申请组合通知
		internal delegate void CBRtnCombAction( ref CThostFtdcCombActionField pCombAction);
		///申请组合录入错误回报
		internal delegate void CBErrRtnCombActionInsert( ref CThostFtdcInputCombActionField pInputCombAction, ref CThostFtdcRspInfoField pRspInfo);
		///请求查询签约银行响应
		internal delegate void CBRspQryContractBank( ref CThostFtdcContractBankField pContractBank, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
		///请求查询预埋单响应
		internal delegate void CBRspQryParkedOrder( ref CThostFtdcParkedOrderField pParkedOrder, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
		///请求查询预埋撤单响应
		internal delegate void CBRspQryParkedOrderAction( ref CThostFtdcParkedOrderActionField pParkedOrderAction, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
		///请求查询交易通知响应
		internal delegate void CBRspQryTradingNotice( ref CThostFtdcTradingNoticeField pTradingNotice, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
		///请求查询经纪公司交易参数响应
		internal delegate void CBRspQryBrokerTradingParams( ref CThostFtdcBrokerTradingParamsField pBrokerTradingParams, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
		///请求查询经纪公司交易算法响应
		internal delegate void CBRspQryBrokerTradingAlgos( ref CThostFtdcBrokerTradingAlgosField pBrokerTradingAlgos, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
		///请求查询监控中心用户令牌
		internal delegate void CBRspQueryCFMMCTradingAccountToken( ref CThostFtdcQueryCFMMCTradingAccountTokenField pQueryCFMMCTradingAccountToken, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
		///银行发起银行资金转期货通知
		internal delegate void CBRtnFromBankToFutureByBank( ref CThostFtdcRspTransferField pRspTransfer);
		///银行发起期货资金转银行通知
		internal delegate void CBRtnFromFutureToBankByBank( ref CThostFtdcRspTransferField pRspTransfer);
		///银行发起冲正银行转期货通知
		internal delegate void CBRtnRepealFromBankToFutureByBank( ref CThostFtdcRspRepealField pRspRepeal);
		///银行发起冲正期货转银行通知
		internal delegate void CBRtnRepealFromFutureToBankByBank( ref CThostFtdcRspRepealField pRspRepeal);
		///期货发起银行资金转期货通知
		internal delegate void CBRtnFromBankToFutureByFuture( ref CThostFtdcRspTransferField pRspTransfer);
		///期货发起期货资金转银行通知
		internal delegate void CBRtnFromFutureToBankByFuture( ref CThostFtdcRspTransferField pRspTransfer);
		///系统运行时期货端手工发起冲正银行转期货请求，银行处理完毕后报盘发回的通知
		internal delegate void CBRtnRepealFromBankToFutureByFutureManual( ref CThostFtdcRspRepealField pRspRepeal);
		///系统运行时期货端手工发起冲正期货转银行请求，银行处理完毕后报盘发回的通知
		internal delegate void CBRtnRepealFromFutureToBankByFutureManual( ref CThostFtdcRspRepealField pRspRepeal);
		///期货发起查询银行余额通知
		internal delegate void CBRtnQueryBankBalanceByFuture( ref CThostFtdcNotifyQueryAccountField pNotifyQueryAccount);
		///期货发起银行资金转期货错误回报
		internal delegate void CBErrRtnBankToFutureByFuture( ref CThostFtdcReqTransferField pReqTransfer, ref CThostFtdcRspInfoField pRspInfo);
		///期货发起期货资金转银行错误回报
		internal delegate void CBErrRtnFutureToBankByFuture( ref CThostFtdcReqTransferField pReqTransfer, ref CThostFtdcRspInfoField pRspInfo);
		///系统运行时期货端手工发起冲正银行转期货错误回报
		internal delegate void CBErrRtnRepealBankToFutureByFutureManual( ref CThostFtdcReqRepealField pReqRepeal, ref CThostFtdcRspInfoField pRspInfo);
		///系统运行时期货端手工发起冲正期货转银行错误回报
		internal delegate void CBErrRtnRepealFutureToBankByFutureManual( ref CThostFtdcReqRepealField pReqRepeal, ref CThostFtdcRspInfoField pRspInfo);
		///期货发起查询银行余额错误回报
		internal delegate void CBErrRtnQueryBankBalanceByFuture( ref CThostFtdcReqQueryAccountField pReqQueryAccount, ref CThostFtdcRspInfoField pRspInfo);
		///期货发起冲正银行转期货请求，银行处理完毕后报盘发回的通知
		internal delegate void CBRtnRepealFromBankToFutureByFuture( ref CThostFtdcRspRepealField pRspRepeal);
		///期货发起冲正期货转银行请求，银行处理完毕后报盘发回的通知
		internal delegate void CBRtnRepealFromFutureToBankByFuture( ref CThostFtdcRspRepealField pRspRepeal);
		///期货发起银行资金转期货应答
		internal delegate void CBRspFromBankToFutureByFuture( ref CThostFtdcReqTransferField pReqTransfer, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
		///期货发起期货资金转银行应答
		internal delegate void CBRspFromFutureToBankByFuture( ref CThostFtdcReqTransferField pReqTransfer, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
		///期货发起查询银行余额应答
		internal delegate void CBRspQueryBankAccountMoneyByFuture( ref CThostFtdcReqQueryAccountField pReqQueryAccount, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
		///银行发起银期开户通知
		internal delegate void CBRtnOpenAccountByBank( ref CThostFtdcOpenAccountField pOpenAccount);
		///银行发起银期销户通知
		internal delegate void CBRtnCancelAccountByBank( ref CThostFtdcCancelAccountField pCancelAccount);
		///银行发起变更银行账号通知
		internal delegate void CBRtnChangeAccountByBank( ref CThostFtdcChangeAccountField pChangeAccount);



		//==================================== 回调函数 =======================================
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegOnRspError", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void RegOnRspError(IntPtr pSpi, CBOnRspError cbOn); //错误应答
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegOnHeartBeatWarning", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void RegOnHeartBeatWarning(IntPtr pSpi, CBOnHeartBeatWarning cb); //心跳超时警告。当长时间未收到报文时，该方法被调用。
	

		[DllImport("CtpTdApiWrapper", EntryPoint = "RegOnRspFrontConnected", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void RegOnRspFrontConnected(IntPtr pSpi, CBOnRspFrontConnected cb); //当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegOnRspFrontDisconnected", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void RegOnRspFrontDisconnected(IntPtr pSpi, CBOnFrontDisconnected cb); //当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。

	    [DllImport("CtpTdApiWrapper", EntryPoint = "RegOnRspAuthenticate", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void RegOnRspAuthenticate(IntPtr pSpi, CBOnRspAuthenticate cbOn);

		[DllImport("CtpTdApiWrapper", EntryPoint = "RegOnRspUserLogin", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void RegOnRspUserLogin(IntPtr pSpi, CBOnRspUserLogin cbOn); //登录请求响应
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegOnRspUserLogout", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void RegOnRspUserLogout(IntPtr pSpi, CBOnRspUserLogout cbOn); //登出请求响应

		[DllImport("CtpTdApiWrapper", EntryPoint = "RegOnRspSettlementInfoConfirm", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void RegOnRspSettlementInfoConfirm(IntPtr pSpi, CBOnRspSettlementInfoConfirm cbOn); //投资者结算结果确认响应



		[DllImport("CtpTdApiWrapper", EntryPoint = "RegOnRspOrderInsert", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void RegOnRspOrderInsert(IntPtr pSpi, CBOnRspOrderInsert cbOn); //报单录入请求响应


		[DllImport("CtpTdApiWrapper", EntryPoint = "RegRspUserPasswordUpdate", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegRspUserPasswordUpdate(IntPtr pSpi, CBRspUserPasswordUpdate cb);  //用户口令更新请求响应
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegRspTradingAccountPasswordUpdate", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegRspTradingAccountPasswordUpdate(IntPtr pSpi, CBRspTradingAccountPasswordUpdate cb);  //资金账户口令更新请求响应
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegRspUserAuthMethod", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegRspUserAuthMethod(IntPtr pSpi, CBRspUserAuthMethod cb);  //查询用户当前支持的认证模式的回复
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegRspGenUserCaptcha", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegRspGenUserCaptcha(IntPtr pSpi, CBRspGenUserCaptcha cb);  //获取图形验证码请求的回复
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegRspGenUserText", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegRspGenUserText(IntPtr pSpi, CBRspGenUserText cb);    //获取短信验证码请求的回复

		[DllImport("CtpTdApiWrapper", EntryPoint = "RegRspParkedOrderInsert", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegRspParkedOrderInsert(IntPtr pSpi, CBRspParkedOrderInsert cb);    //预埋单录入请求响应
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegRspParkedOrderAction", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegRspParkedOrderAction(IntPtr pSpi, CBRspParkedOrderAction cb);    //预埋撤单录入请求响应
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegRspOrderAction", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegRspOrderAction(IntPtr pSpi, CBRspOrderAction cb);    //报单操作请求响应
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegRspQueryMaxOrderVolume", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegRspQueryMaxOrderVolume(IntPtr pSpi, CBRspQueryMaxOrderVolume cb);    //查询最大报单数量响应

		[DllImport("CtpTdApiWrapper", EntryPoint = "RegRspRemoveParkedOrder", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegRspRemoveParkedOrder(IntPtr pSpi, CBRspRemoveParkedOrder cb);    //删除预埋单响应
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegRspRemoveParkedOrderAction", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegRspRemoveParkedOrderAction(IntPtr pSpi, CBRspRemoveParkedOrderAction cb);    //删除预埋撤单响应
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegBatchOrderAction", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegBatchOrderAction(IntPtr pSpi, CBRspBatchOrderAction cb); //批量报单操作请求响应
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegCombActionInsert", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegCombActionInsert(IntPtr pSpi, CBRspCombActionInsert cb); //申请组合录入请求响应
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegRspQryOrder", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegRspQryOrder(IntPtr pSpi, CBRspQryOrder cb);  //请求查询报单响应
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegRspQryTrade", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegRspQryTrade(IntPtr pSpi, CBRspQryTrade cb);  //请求查询成交响应
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegRspQryInvestorPosition", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegRspQryInvestorPosition(IntPtr pSpi, CBRspQryInvestorPosition cb);    //请求查询投资者持仓响应
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegRspQryTradingAccount", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegRspQryTradingAccount(IntPtr pSpi, CBRspQryTradingAccount cb);    //请求查询资金账户响应
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegRspQryInvestor", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegRspQryInvestor(IntPtr pSpi, CBRspQryInvestor cb);    //请求查询投资者响应
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegRspQryTradingCode", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegRspQryTradingCode(IntPtr pSpi, CBRspQryTradingCode cb);  //请求查询交易编码响应
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegRspQryInstrumentMarginRate", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegRspQryInstrumentMarginRate(IntPtr pSpi, CBRspQryInstrumentMarginRate cb);    //请求查询合约保证金率响应
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegRspQryInstrumentCommissionRate", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegRspQryInstrumentCommissionRate(IntPtr pSpi, CBRspQryInstrumentCommissionRate cb);    //请求查询合约手续费率响应
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegRspQryExchange", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegRspQryExchange(IntPtr pSpi, CBRspQryExchange cb);    //请求查询交易所响应
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegRspQryInstrument", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegRspQryInstrument(IntPtr pSpi, CBRspQryInstrument cb);    //请求查询合约响应
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegRspQryDepthMarketData", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegRspQryDepthMarketData(IntPtr pSpi, CBRspQryDepthMarketData cb);  //请求查询行情响应
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegRspQrySettlementInfo", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegRspQrySettlementInfo(IntPtr pSpi, CBRspQrySettlementInfo cb);    //请求查询投资者结算结果响应
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegRspQryTransferBank", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegRspQryTransferBank(IntPtr pSpi, CBRspQryTransferBank cb);    //请求查询转帐银行响应
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegRspQryInvestorPositionDetail", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegRspQryInvestorPositionDetail(IntPtr pSpi, CBRspQryInvestorPositionDetail cb);    //请求查询投资者持仓明细响应
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegRspQryNotice", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegRspQryNotice(IntPtr pSpi, CBRspQryNotice cb);    //请求查询客户通知响应
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegRspQrySettlementInfoConfirm", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegRspQrySettlementInfoConfirm(IntPtr pSpi, CBRspQrySettlementInfoConfirm cb);  //请求查询结算信息确认响应
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegRspQryInvestorPositionCombineDetail", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegRspQryInvestorPositionCombineDetail(IntPtr pSpi, CBRspQryInvestorPositionCombineDetail cb);  //请求查询投资者持仓明细响应
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegRspQryCFMMCTradingAccountKey", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegRspQryCFMMCTradingAccountKey(IntPtr pSpi, CBRspQryCFMMCTradingAccountKey cb);    //查询保证金监管系统经纪公司资金账户密钥响应
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegRspQryEWarrantOffset", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegRspQryEWarrantOffset(IntPtr pSpi, CBRspQryEWarrantOffset cb);    //请求查询仓单折抵信息
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegRspQryInvestorProductGroupMargin", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegRspQryInvestorProductGroupMargin(IntPtr pSpi, CBRspQryInvestorProductGroupMargin cb);    //请求查询投资者品种/跨品种保证金
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegRspQryExchangeMarginRate", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegRspQryExchangeMarginRate(IntPtr pSpi, CBRspQryExchangeMarginRate cb);    //请求查询交易所保证金率
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegRspQryExchangeMarginRateAdjust", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegRspQryExchangeMarginRateAdjust(IntPtr pSpi, CBRspQryExchangeMarginRateAdjust cb);    //请求查询交易所调整保证金率
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegRspQryExchangeRate", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegRspQryExchangeRate(IntPtr pSpi, CBRspQryExchangeRate cb);    //请求查询汇率响应
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegRspQrySecAgentACIDMap", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegRspQrySecAgentACIDMap(IntPtr pSpi, CBRspQrySecAgentACIDMap cb);  //请求查询二级代理操作员银期权限响应
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegRspQryProductExchRate", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegRspQryProductExchRate(IntPtr pSpi, CBRspQryProductExchRate cb);  //请求查询产品报价汇率
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegRspQryProductGroup", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegRspQryProductGroup(IntPtr pSpi, CBRspQryProductGroup cb);    //请求查询产品组
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegRspQryMMInstrumentCommissionRate", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegRspQryMMInstrumentCommissionRate(IntPtr pSpi, CBRspQryMMInstrumentCommissionRate cb);    //请求查询做市商合约手续费率响应
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegRspQryMMOptionInstrCommRate", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegRspQryMMOptionInstrCommRate(IntPtr pSpi, CBRspQryMMOptionInstrCommRate cb);  //请求查询做市商期权合约手续费响应
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegRspQryInstrumentOrderCommRate", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegRspQryInstrumentOrderCommRate(IntPtr pSpi, CBRspQryInstrumentOrderCommRate cb);  //请求查询报单手续费响应
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegRspQrySecAgentTradingAccount", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegRspQrySecAgentTradingAccount(IntPtr pSpi, CBRspQrySecAgentTradingAccount cb);    //请求查询资金账户响应
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegRspQrySecAgentCheckMode", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegRspQrySecAgentCheckMode(IntPtr pSpi, CBRspQrySecAgentCheckMode cb);  //请求查询二级代理商资金校验模式响应
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegRspQrySecAgentTradeInfo", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegRspQrySecAgentTradeInfo(IntPtr pSpi, CBRspQrySecAgentTradeInfo cb);  //请求查询二级代理商信息响应
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegRspQryOptionInstrTradeCost", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegRspQryOptionInstrTradeCost(IntPtr pSpi, CBRspQryOptionInstrTradeCost cb);    //请求查询期权交易成本响应
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegRspQryOptionInstrCommRate", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegRspQryOptionInstrCommRate(IntPtr pSpi, CBRspQryOptionInstrCommRate cb);  //请求查询期权合约手续费响应
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegRspQryExecOrder", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegRspQryExecOrder(IntPtr pSpi, CBRspQryExecOrder cb);  //请求查询执行宣告响应
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegRspQryForQuote", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegRspQryForQuote(IntPtr pSpi, CBRspQryForQuote cb);    //请求查询询价响应
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegRspQryQuote", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegRspQryQuote(IntPtr pSpi, CBRspQryQuote cb);  //请求查询报价响应
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegRspQryOptionSelfClose", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegRspQryOptionSelfClose(IntPtr pSpi, CBRspQryOptionSelfClose cb);  //请求查询期权自对冲响应
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegRspQryInvestUnit", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegRspQryInvestUnit(IntPtr pSpi, CBRspQryInvestUnit cb);    //请求查询投资单元响应
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegRspQryCombInstrumentGuard", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegRspQryCombInstrumentGuard(IntPtr pSpi, CBRspQryCombInstrumentGuard cb);  //请求查询组合合约安全系数响应
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegRspQryCombAction", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegRspQryCombAction(IntPtr pSpi, CBRspQryCombAction cb);    //请求查询申请组合响应
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegRspQryTransferSerial", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegRspQryTransferSerial(IntPtr pSpi, CBRspQryTransferSerial cb);    //请求查询转帐流水响应
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegRspQryAccountregister", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegRspQryAccountregister(IntPtr pSpi, CBRspQryAccountregister cb);  //请求查询银期签约关系响应
	[DllImport("CtpTdApiWrapper", EntryPoint = "RegRtnOrder", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegRtnOrder(IntPtr pSpi, CBRtnOrder cb);    //报单通知
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegRtnTrade", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegRtnTrade(IntPtr pSpi, CBRtnTrade cb);    //成交通知
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegErrRtnOrderInsert", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegErrRtnOrderInsert(IntPtr pSpi, CBErrRtnOrderInsert cb);  //报单录入错误回报
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegErrRtnOrderAction", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegErrRtnOrderAction(IntPtr pSpi, CBErrRtnOrderAction cb);  //报单操作错误回报
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegRtnInstrumentStatus", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegRtnInstrumentStatus(IntPtr pSpi, CBRtnInstrumentStatus cb);  //合约交易状态通知
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegRtnTradingNotice", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegRtnTradingNotice(IntPtr pSpi, CBRtnTradingNotice cb);    //交易通知
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegRtnErrorConditionalOrder", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegRtnErrorConditionalOrder(IntPtr pSpi, CBRtnErrorConditionalOrder cb);    //提示条件单校验错误
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegRspQryContractBank", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegRspQryContractBank(IntPtr pSpi, CBRspQryContractBank cb);    //请求查询签约银行响应
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegRspQryParkedOrder", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegRspQryParkedOrder(IntPtr pSpi, CBRspQryParkedOrder cb);  //请求查询预埋单响应
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegRspQryParkedOrderAction", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegRspQryParkedOrderAction(IntPtr pSpi, CBRspQryParkedOrderAction cb);  //请求查询预埋撤单响应
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegRspQryTradingNotice", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegRspQryTradingNotice(IntPtr pSpi, CBRspQryTradingNotice cb);  //请求查询交易通知响应
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegRspQryBrokerTradingParams", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegRspQryBrokerTradingParams(IntPtr pSpi, CBRspQryBrokerTradingParams cb);  //请求查询经纪公司交易参数响应
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegRspQryBrokerTradingAlgos", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegRspQryBrokerTradingAlgos(IntPtr pSpi, CBRspQryBrokerTradingAlgos cb);    //请求查询经纪公司交易算法响应
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegRtnFromBankToFutureByBank", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegRtnFromBankToFutureByBank(IntPtr pSpi, CBRtnFromBankToFutureByBank cb);  //银行发起银行资金转期货通知
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegRtnFromFutureToBankByBank", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegRtnFromFutureToBankByBank(IntPtr pSpi, CBRtnFromFutureToBankByBank cb);  //银行发起期货资金转银行通知
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegRtnRepealFromBankToFutureByBank", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegRtnRepealFromBankToFutureByBank(IntPtr pSpi, CBRtnRepealFromBankToFutureByBank cb);  //银行发起冲正银行转期货通知
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegRtnRepealFromFutureToBankByBank", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegRtnRepealFromFutureToBankByBank(IntPtr pSpi, CBRtnRepealFromFutureToBankByBank cb);  //银行发起冲正期货转银行通知
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegRtnFromBankToFutureByFuture", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegRtnFromBankToFutureByFuture(IntPtr pSpi, CBRtnFromBankToFutureByFuture cb);  //期货发起银行资金转期货通知
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegRtnFromFutureToBankByFuture", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegRtnFromFutureToBankByFuture(IntPtr pSpi, CBRtnFromFutureToBankByFuture cb);  //期货发起期货资金转银行通知
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegRtnRepealFromBankToFutureByFutureManual", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegRtnRepealFromBankToFutureByFutureManual(IntPtr pSpi, CBRtnRepealFromBankToFutureByFutureManual cb);  //系统运行时期货端手工发起冲正银行转期货请求，银行处理完毕后报盘发回的通知
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegRtnRepealFromFutureToBankByFutureManual", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegRtnRepealFromFutureToBankByFutureManual(IntPtr pSpi, CBRtnRepealFromFutureToBankByFutureManual cb);  //系统运行时期货端手工发起冲正期货转银行请求，银行处理完毕后报盘发回的通知
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegRtnQueryBankBalanceByFuture", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegRtnQueryBankBalanceByFuture(IntPtr pSpi, CBRtnQueryBankBalanceByFuture cb);  //期货发起查询银行余额通知
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegErrRtnBankToFutureByFuture", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegErrRtnBankToFutureByFuture(IntPtr pSpi, CBErrRtnBankToFutureByFuture cb);    //期货发起银行资金转期货错误回报
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegErrRtnFutureToBankByFuture", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegErrRtnFutureToBankByFuture(IntPtr pSpi, CBErrRtnFutureToBankByFuture cb);    //期货发起期货资金转银行错误回报
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegErrRtnRepealBankToFutureByFutureManual", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegErrRtnRepealBankToFutureByFutureManual(IntPtr pSpi, CBErrRtnRepealBankToFutureByFutureManual cb);    //系统运行时期货端手工发起冲正银行转期货错误回报
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegErrRtnRepealFutureToBankByFutureManual", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegErrRtnRepealFutureToBankByFutureManual(IntPtr pSpi, CBErrRtnRepealFutureToBankByFutureManual cb);    //系统运行时期货端手工发起冲正期货转银行错误回报
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegErrRtnQueryBankBalanceByFuture", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegErrRtnQueryBankBalanceByFuture(IntPtr pSpi, CBErrRtnQueryBankBalanceByFuture cb);    //期货发起查询银行余额错误回报
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegRtnRepealFromBankToFutureByFuture", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegRtnRepealFromBankToFutureByFuture(IntPtr pSpi, CBRtnRepealFromBankToFutureByFuture cb);  //期货发起冲正银行转期货请求，银行处理完毕后报盘发回的通知
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegRtnRepealFromFutureToBankByFuture", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegRtnRepealFromFutureToBankByFuture(IntPtr pSpi, CBRtnRepealFromFutureToBankByFuture cb);  //期货发起冲正期货转银行请求，银行处理完毕后报盘发回的通知
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegRspFromBankToFutureByFuture", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegRspFromBankToFutureByFuture(IntPtr pSpi, CBRspFromBankToFutureByFuture cb);  //期货发起银行资金转期货应答
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegRspFromFutureToBankByFuture", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegRspFromFutureToBankByFuture(IntPtr pSpi, CBRspFromFutureToBankByFuture cb);  //期货发起期货资金转银行应答
		[DllImport("CtpTdApiWrapper", EntryPoint = "RegRspQueryBankAccountMoneyByFuture", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void 
			RegRspQueryBankAccountMoneyByFuture(IntPtr pSpi, CBRspQueryBankAccountMoneyByFuture cb);    //期货发起查询银行余额应答
#pragma endregion


	}
}
