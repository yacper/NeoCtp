/********************************************************************
	created:	2020-09-01 11:49:34
	author:		joshua
	email:		
	
	purpose:	
*********************************************************************/
using System;
using System.Diagnostics;
using System.Threading;
using NUnit.Framework;

namespace SharpCtp.Test
{
	class CtpTdApiTest
	{
		public class TestCtpTdSpi : ICtpTdSpi
		{
			///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
			public void OnFrontConnected()
			{
				CThostFtdcReqUserLoginField f = new CThostFtdcReqUserLoginField()
				{
					BrokerID = _brokerID,
					UserID = _UserID,
					Password = _password
				};
				_api.ReqUserLogin(ref f, 1);

			}

			///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
			///@param nReason 错误原因
			///        0x1001 网络读失败
			///        0x1002 网络写失败
			///        0x2001 接收心跳超时
			///        0x2002 发送心跳失败
			///        0x2003 收到错误报文
			public void OnFrontDisconnected(int nReason)
			{
				Trace.WriteLine($"OnFrontDisconnected Error:{CtpHelper.GetError(nReason)?.prompt}");
			}

			///心跳超时警告。当长时间未收到报文时，该方法被调用。
			///@param nTimeLapse 距离上次接收报文的时间
			public void OnHeartBeatWarning(int nTimeLapse)
			{
				Trace.WriteLine($"OnHeartBeatWarning: timeLapse {nTimeLapse}");
			}

			///客户端认证响应
			public void OnRspAuthenticate(ref CThostFtdcRspAuthenticateField pRspAuthenticateField,
				ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
			{

			}

			///登录请求响应
			public void OnRspUserLogin(ref CThostFtdcRspUserLoginField pRspUserLogin, ref CThostFtdcRspInfoField pRspInfo,
				int nRequestID, bool bIsLast)
			{

				if (pRspInfo.ErrorID != 0)
				{
					Trace.WriteLine($"OnRspUserLogin:{pRspInfo.ErrorMsg}");

					return;
				}


				Trace.WriteLine("");
				Trace.WriteLine($"//-------OnRspUserLogin------");
				Trace.WriteLine($"BrockerID:	{pRspUserLogin.BrokerID}");
				Trace.WriteLine($"UserId:		{pRspUserLogin.UserID}");
				Trace.WriteLine("");
				Trace.WriteLine($"TradingDay:	{pRspUserLogin.TradingDay}");
				Trace.WriteLine($"LoginTime:	{pRspUserLogin.LoginTime}");
				Trace.WriteLine($"SystemName:	{pRspUserLogin.SystemName}");
				Trace.WriteLine($"FrontId:	{pRspUserLogin.FrontID}");
				Trace.WriteLine($"SessionId:	{pRspUserLogin.SessionID}");
				Trace.WriteLine($"MaxOrderRef:{pRspUserLogin.MaxOrderRef}");
				Trace.WriteLine($"SHFETime:	{pRspUserLogin.SHFETime}");
				Trace.WriteLine($"DCETime:	{pRspUserLogin.DCETime}");
				Trace.WriteLine($"CZCETime:	{pRspUserLogin.CZCETime}");
				Trace.WriteLine($"FFEXTime:	{pRspUserLogin.FFEXTime}");
				Trace.WriteLine($"INETime:	{pRspUserLogin.INETime}");
				Trace.WriteLine($"-------OnRspUserLogin------//");
				Trace.WriteLine("");


			}

			///登出请求响应
			public void OnRspUserLogout(ref CThostFtdcUserLogoutField pUserLogout, ref CThostFtdcRspInfoField pRspInfo,
				int nRequestID, bool bIsLast)
			{

			}

			///用户口令更新请求响应
			public void OnRspUserPasswordUpdate(ref CThostFtdcUserPasswordUpdateField pUserPasswordUpdate,
				ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
			{

			}

			///资金账户口令更新请求响应
			public void OnRspTradingAccountPasswordUpdate(
				ref CThostFtdcTradingAccountPasswordUpdateField pTradingAccountPasswordUpdate,
				ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
			{

			}

			///查询用户当前支持的认证模式的回复
			public void OnRspUserAuthMethod(ref CThostFtdcRspUserAuthMethodField pRspUserAuthMethod,
				ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
			{

			}

			///获取图形验证码请求的回复
			public void OnRspGenUserCaptcha(ref CThostFtdcRspGenUserCaptchaField pRspGenUserCaptcha,
				ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
			{

			}

			///获取短信验证码请求的回复
			public void OnRspGenUserText(ref CThostFtdcRspGenUserTextField pRspGenUserText,
				ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
			{

			}



			///报单录入请求响应
			public void OnRspOrderInsert(ref CThostFtdcInputOrderField pInputOrder, ref CThostFtdcRspInfoField pRspInfo,
				int nRequestID, bool bIsLast)
			{

			}

			///预埋单录入请求响应
			public void OnRspParkedOrderInsert(ref CThostFtdcParkedOrderField pParkedOrder,
				ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
			{

			}

			///预埋撤单录入请求响应
			public void OnRspParkedOrderAction(ref CThostFtdcParkedOrderActionField pParkedOrderAction,
				ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
			{

			}

			///报单操作请求响应
			public void OnRspOrderAction(ref CThostFtdcInputOrderActionField pInputOrderAction,
				ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
			{

			}

			///查询最大报单数量响应
			public void OnRspQueryMaxOrderVolume(ref CThostFtdcQueryMaxOrderVolumeField pQueryMaxOrderVolume,
				ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
			{

			}

			///投资者结算结果确认响应
			public void OnRspSettlementInfoConfirm(ref CThostFtdcSettlementInfoConfirmField pSettlementInfoConfirm, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast) { }

			///删除预埋单响应
			public void OnRspRemoveParkedOrder(ref CThostFtdcRemoveParkedOrderField pRemoveParkedOrder, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast) { }

			///删除预埋撤单响应
			public void OnRspRemoveParkedOrderAction(ref CThostFtdcRemoveParkedOrderActionField pRemoveParkedOrderAction, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast) { }

			///执行宣告录入请求响应
			public void OnRspExecOrderInsert(ref CThostFtdcInputExecOrderField pInputExecOrder, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast) { }

			///执行宣告操作请求响应
			public void OnRspExecOrderAction(ref CThostFtdcInputExecOrderActionField pInputExecOrderAction, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast) { }

			///询价录入请求响应
			public void OnRspForQuoteInsert(ref CThostFtdcInputForQuoteField pInputForQuote, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast) { }

			///报价录入请求响应
			public void OnRspQuoteInsert(ref CThostFtdcInputQuoteField pInputQuote, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast) { }

			///报价操作请求响应
			public void OnRspQuoteAction(ref CThostFtdcInputQuoteActionField pInputQuoteAction, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast) { }

			///批量报单操作请求响应
			public void OnRspBatchOrderAction(ref CThostFtdcInputBatchOrderActionField pInputBatchOrderAction, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast) { }

			///期权自对冲录入请求响应
			public void OnRspOptionSelfCloseInsert(ref CThostFtdcInputOptionSelfCloseField pInputOptionSelfClose, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast) { }

			///期权自对冲操作请求响应
			public void OnRspOptionSelfCloseAction(ref CThostFtdcInputOptionSelfCloseActionField pInputOptionSelfCloseAction, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast) { }

			///申请组合录入请求响应
			public void OnRspCombActionInsert(ref CThostFtdcInputCombActionField pInputCombAction, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast) { }

			///请求查询报单响应
			public void OnRspQryOrder(ref CThostFtdcOrderField pOrder, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast) { }

			///请求查询成交响应
			public void OnRspQryTrade(ref CThostFtdcTradeField pTrade, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast) { }

			///请求查询投资者持仓响应
			public void OnRspQryInvestorPosition(ref CThostFtdcInvestorPositionField pInvestorPosition, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast) { }

			///请求查询资金账户响应
			public void OnRspQryTradingAccount(ref CThostFtdcTradingAccountField pTradingAccount, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast) { }

			///请求查询投资者响应
			public void OnRspQryInvestor(ref CThostFtdcInvestorField pInvestor, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast) { }

			///请求查询交易编码响应
			public void OnRspQryTradingCode(ref CThostFtdcTradingCodeField pTradingCode, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast) { }

			///请求查询合约保证金率响应
			public void OnRspQryInstrumentMarginRate(ref CThostFtdcInstrumentMarginRateField pInstrumentMarginRate, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast) { }

			///请求查询合约手续费率响应
			public void OnRspQryInstrumentCommissionRate(ref CThostFtdcInstrumentCommissionRateField pInstrumentCommissionRate, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast) { }


			///请求查询交易所响应
			public void OnRspQryExchange(ref CThostFtdcExchangeField pExchange, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast) { }

			///请求查询产品响应
			public void OnRspQryProduct(ref CThostFtdcProductField pProduct, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast) { }

			///请求查询合约响应
			public void OnRspQryInstrument(ref CThostFtdcInstrumentField pInstrument, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast) { }


			///请求查询行情响应
			public void OnRspQryDepthMarketData(ref CThostFtdcDepthMarketDataField pDepthMarketData, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast) { }


			///请求查询投资者结算结果响应
			public void OnRspQrySettlementInfo(ref CThostFtdcSettlementInfoField pSettlementInfo, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast) { }
			///请求查询转帐银行响应
			public void OnRspQryTransferBank(ref CThostFtdcTransferBankField pTransferBank, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast) { }

			///请求查询投资者持仓明细响应
			public void OnRspQryInvestorPositionDetail(ref CThostFtdcInvestorPositionDetailField pInvestorPositionDetail, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast) { }

			///请求查询客户通知响应
			public void OnRspQryNotice(ref CThostFtdcNoticeField pNotice, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast) { }

			///请求查询结算信息确认响应
			public void OnRspQrySettlementInfoConfirm(ref CThostFtdcSettlementInfoConfirmField pSettlementInfoConfirm, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast) { }

			///请求查询投资者持仓明细响应
			public void OnRspQryInvestorPositionCombineDetail(ref CThostFtdcInvestorPositionCombineDetailField pInvestorPositionCombineDetail, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast) { }

			///查询保证金监管系统经纪公司资金账户密钥响应
			public void OnRspQryCFMMCTradingAccountKey(ref CThostFtdcCFMMCTradingAccountKeyField pCFMMCTradingAccountKey, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast) { }

			///请求查询仓单折抵信息响应
			public void OnRspQryEWarrantOffset(ref CThostFtdcEWarrantOffsetField pEWarrantOffset, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast) { }

			///请求查询投资者品种/跨品种保证金响应
			public void OnRspQryInvestorProductGroupMargin(ref CThostFtdcInvestorProductGroupMarginField pInvestorProductGroupMargin, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast) { }

			///请求查询交易所保证金率响应
			public void OnRspQryExchangeMarginRate(ref CThostFtdcExchangeMarginRateField pExchangeMarginRate, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast) { }

			///请求查询交易所调整保证金率响应
			public void OnRspQryExchangeMarginRateAdjust(ref CThostFtdcExchangeMarginRateAdjustField pExchangeMarginRateAdjust, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast) { }

			///请求查询汇率响应
			public void OnRspQryExchangeRate(ref CThostFtdcExchangeRateField pExchangeRate, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast) { }

			///请求查询二级代理操作员银期权限响应
			public void OnRspQrySecAgentACIDMap(ref CThostFtdcSecAgentACIDMapField pSecAgentACIDMap, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast) { }

			///请求查询产品报价汇率
			public void OnRspQryProductExchRate(ref CThostFtdcProductExchRateField pProductExchRate, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast) { }

			///请求查询产品组
			public void OnRspQryProductGroup(ref CThostFtdcProductGroupField pProductGroup, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast) { }

			///请求查询做市商合约手续费率响应
			public void OnRspQryMMInstrumentCommissionRate(ref CThostFtdcMMInstrumentCommissionRateField pMMInstrumentCommissionRate, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast) { }

			///请求查询做市商期权合约手续费响应
			public void OnRspQryMMOptionInstrCommRate(ref CThostFtdcMMOptionInstrCommRateField pMMOptionInstrCommRate, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast) { }

			///请求查询报单手续费响应
			public void OnRspQryInstrumentOrderCommRate(ref CThostFtdcInstrumentOrderCommRateField pInstrumentOrderCommRate, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast) { }

			///请求查询资金账户响应
			public void OnRspQrySecAgentTradingAccount(ref CThostFtdcTradingAccountField pTradingAccount, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast) { }

			///请求查询二级代理商资金校验模式响应
			public void OnRspQrySecAgentCheckMode(ref CThostFtdcSecAgentCheckModeField pSecAgentCheckMode, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast) { }

			///请求查询二级代理商信息响应
			public void OnRspQrySecAgentTradeInfo(ref CThostFtdcSecAgentTradeInfoField pSecAgentTradeInfo, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast) { }

			///请求查询期权交易成本响应
			public void OnRspQryOptionInstrTradeCost(ref CThostFtdcOptionInstrTradeCostField pOptionInstrTradeCost, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast) { }

			///请求查询期权合约手续费响应
			public void OnRspQryOptionInstrCommRate(ref CThostFtdcOptionInstrCommRateField pOptionInstrCommRate, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast) { }

			///请求查询执行宣告响应
			public void OnRspQryExecOrder(ref CThostFtdcExecOrderField pExecOrder, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast) { }

			///请求查询询价响应
			public void OnRspQryForQuote(ref CThostFtdcForQuoteField pForQuote, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast) { }

			///请求查询报价响应
			public void OnRspQryQuote(ref CThostFtdcQuoteField pQuote, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast) { }

			///请求查询期权自对冲响应
			public void OnRspQryOptionSelfClose(ref CThostFtdcOptionSelfCloseField pOptionSelfClose, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast) { }

			///请求查询投资单元响应
			public void OnRspQryInvestUnit(ref CThostFtdcInvestUnitField pInvestUnit, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast) { }

			///请求查询组合合约安全系数响应
			public void OnRspQryCombInstrumentGuard(ref CThostFtdcCombInstrumentGuardField pCombInstrumentGuard, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast) { }

			///请求查询申请组合响应
			public void OnRspQryCombAction(ref CThostFtdcCombActionField pCombAction, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast) { }

			///请求查询转帐流水响应
			public void OnRspQryTransferSerial(ref CThostFtdcTransferSerialField pTransferSerial, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast) { }

			///请求查询银期签约关系响应
			public void OnRspQryAccountregister(ref CThostFtdcAccountregisterField pAccountregister, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast) { }



			///错误应答
			public void OnRspError(ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast) { }

			///报单通知
			public void OnRtnOrder(ref CThostFtdcOrderField pOrder) { }

			///成交通知
			public void OnRtnTrade(ref CThostFtdcTradeField pTrade) { }

			///报单录入错误回报
			public void OnErrRtnOrderInsert(ref CThostFtdcInputOrderField pInputOrder, ref CThostFtdcRspInfoField pRspInfo) { }

			///报单操作错误回报
			public void OnErrRtnOrderAction(ref CThostFtdcOrderActionField pOrderAction, ref CThostFtdcRspInfoField pRspInfo) { }

			///合约交易状态通知
			public void OnRtnInstrumentStatus(ref CThostFtdcInstrumentStatusField pInstrumentStatus) { }

			///交易所公告通知
			public void OnRtnBulletin(ref CThostFtdcBulletinField pBulletin) { }

			///交易通知
			public void OnRtnTradingNotice(ref CThostFtdcTradingNoticeInfoField pTradingNoticeInfo) { }

			///提示条件单校验错误
			public void OnRtnErrorConditionalOrder(ref CThostFtdcErrorConditionalOrderField pErrorConditionalOrder) { }

			///执行宣告通知
			public void OnRtnExecOrder(ref CThostFtdcExecOrderField pExecOrder) { }

			///执行宣告录入错误回报
			public void OnErrRtnExecOrderInsert(ref CThostFtdcInputExecOrderField pInputExecOrder, ref CThostFtdcRspInfoField pRspInfo) { }

			///执行宣告操作错误回报
			public void OnErrRtnExecOrderAction(ref CThostFtdcExecOrderActionField pExecOrderAction, ref CThostFtdcRspInfoField pRspInfo) { }

			///询价录入错误回报
			public void OnErrRtnForQuoteInsert(ref CThostFtdcInputForQuoteField pInputForQuote, ref CThostFtdcRspInfoField pRspInfo) { }

			///报价通知
			public void OnRtnQuote(ref CThostFtdcQuoteField pQuote) { }

			///报价录入错误回报
			public void OnErrRtnQuoteInsert(ref CThostFtdcInputQuoteField pInputQuote, ref CThostFtdcRspInfoField pRspInfo) { }

			///报价操作错误回报
			public void OnErrRtnQuoteAction(ref CThostFtdcQuoteActionField pQuoteAction, ref CThostFtdcRspInfoField pRspInfo) { }

			///询价通知
			public void OnRtnForQuoteRsp(ref CThostFtdcForQuoteRspField pForQuoteRsp) { }

			///保证金监控中心用户令牌
			public void OnRtnCFMMCTradingAccountToken(ref CThostFtdcCFMMCTradingAccountTokenField pCFMMCTradingAccountToken) { }

			///批量报单操作错误回报
			public void OnErrRtnBatchOrderAction(ref CThostFtdcBatchOrderActionField pBatchOrderAction, ref CThostFtdcRspInfoField pRspInfo) { }

			///期权自对冲通知
			public void OnRtnOptionSelfClose(ref CThostFtdcOptionSelfCloseField pOptionSelfClose) { }

			///期权自对冲录入错误回报
			public void OnErrRtnOptionSelfCloseInsert(ref CThostFtdcInputOptionSelfCloseField pInputOptionSelfClose, ref CThostFtdcRspInfoField pRspInfo) { }

			///期权自对冲操作错误回报
			public void OnErrRtnOptionSelfCloseAction(ref CThostFtdcOptionSelfCloseActionField pOptionSelfCloseAction, ref CThostFtdcRspInfoField pRspInfo) { }

			///申请组合通知
			public void OnRtnCombAction(ref CThostFtdcCombActionField pCombAction) { }

			///申请组合录入错误回报
			public void OnErrRtnCombActionInsert(ref CThostFtdcInputCombActionField pInputCombAction, ref CThostFtdcRspInfoField pRspInfo) { }

			///请求查询签约银行响应
			public void OnRspQryContractBank(ref CThostFtdcContractBankField pContractBank, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast) { }

			///请求查询预埋单响应
			public void OnRspQryParkedOrder(ref CThostFtdcParkedOrderField pParkedOrder, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast) { }

			///请求查询预埋撤单响应
			public void OnRspQryParkedOrderAction(ref CThostFtdcParkedOrderActionField pParkedOrderAction, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast) { }

			///请求查询交易通知响应
			public void OnRspQryTradingNotice(ref CThostFtdcTradingNoticeField pTradingNotice, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast) { }

			///请求查询经纪公司交易参数响应
			public void OnRspQryBrokerTradingParams(ref CThostFtdcBrokerTradingParamsField pBrokerTradingParams, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast) { }

			///请求查询经纪公司交易算法响应
			public void OnRspQryBrokerTradingAlgos(ref CThostFtdcBrokerTradingAlgosField pBrokerTradingAlgos, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast) { }

			///请求查询监控中心用户令牌
			public void OnRspQueryCFMMCTradingAccountToken(ref CThostFtdcQueryCFMMCTradingAccountTokenField pQueryCFMMCTradingAccountToken, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast) { }

			///银行发起银行资金转期货通知
			public void OnRtnFromBankToFutureByBank(ref CThostFtdcRspTransferField pRspTransfer) { }

			///银行发起期货资金转银行通知
			public void OnRtnFromFutureToBankByBank(ref CThostFtdcRspTransferField pRspTransfer) { }

			///银行发起冲正银行转期货通知
			public void OnRtnRepealFromBankToFutureByBank(ref CThostFtdcRspRepealField pRspRepeal) { }

			///银行发起冲正期货转银行通知
			public void OnRtnRepealFromFutureToBankByBank(ref CThostFtdcRspRepealField pRspRepeal) { }

			///期货发起银行资金转期货通知
			public void OnRtnFromBankToFutureByFuture(ref CThostFtdcRspTransferField pRspTransfer) { }

			///期货发起期货资金转银行通知
			public void OnRtnFromFutureToBankByFuture(ref CThostFtdcRspTransferField pRspTransfer) { }

			///系统运行时期货端手工发起冲正银行转期货请求，银行处理完毕后报盘发回的通知
			public void OnRtnRepealFromBankToFutureByFutureManual(ref CThostFtdcRspRepealField pRspRepeal) { }

			///系统运行时期货端手工发起冲正期货转银行请求，银行处理完毕后报盘发回的通知
			public void OnRtnRepealFromFutureToBankByFutureManual(ref CThostFtdcRspRepealField pRspRepeal) { }

			///期货发起查询银行余额通知
			public void OnRtnQueryBankBalanceByFuture(ref CThostFtdcNotifyQueryAccountField pNotifyQueryAccount) { }

			///期货发起银行资金转期货错误回报
			public void OnErrRtnBankToFutureByFuture(ref CThostFtdcReqTransferField pReqTransfer, ref CThostFtdcRspInfoField pRspInfo) { }

			///期货发起期货资金转银行错误回报
			public void OnErrRtnFutureToBankByFuture(ref CThostFtdcReqTransferField pReqTransfer, ref CThostFtdcRspInfoField pRspInfo) { }

			///系统运行时期货端手工发起冲正银行转期货错误回报
			public void OnErrRtnRepealBankToFutureByFutureManual(ref CThostFtdcReqRepealField pReqRepeal, ref CThostFtdcRspInfoField pRspInfo) { }

			///系统运行时期货端手工发起冲正期货转银行错误回报
			public void OnErrRtnRepealFutureToBankByFutureManual(ref CThostFtdcReqRepealField pReqRepeal, ref CThostFtdcRspInfoField pRspInfo) { }

			///期货发起查询银行余额错误回报
			public void OnErrRtnQueryBankBalanceByFuture(ref CThostFtdcReqQueryAccountField pReqQueryAccount, ref CThostFtdcRspInfoField pRspInfo) { }

			///期货发起冲正银行转期货请求，银行处理完毕后报盘发回的通知
			public void OnRtnRepealFromBankToFutureByFuture(ref CThostFtdcRspRepealField pRspRepeal) { }

			///期货发起冲正期货转银行请求，银行处理完毕后报盘发回的通知
			public void OnRtnRepealFromFutureToBankByFuture(ref CThostFtdcRspRepealField pRspRepeal) { }

			///期货发起银行资金转期货应答
			public void OnRspFromBankToFutureByFuture(ref CThostFtdcReqTransferField pReqTransfer, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast) { }

			///期货发起期货资金转银行应答
			public void OnRspFromFutureToBankByFuture(ref CThostFtdcReqTransferField pReqTransfer, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast) { }

			///期货发起查询银行余额应答
			public void OnRspQueryBankAccountMoneyByFuture(ref CThostFtdcReqQueryAccountField pReqQueryAccount, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast) { }

			///银行发起银期开户通知
			public void OnRtnOpenAccountByBank(ref CThostFtdcOpenAccountField pOpenAccount) { }

			///银行发起银期销户通知
			public void OnRtnCancelAccountByBank(ref CThostFtdcCancelAccountField pCancelAccount) { }

			///银行发起变更银行账号通知
			public void OnRtnChangeAccountByBank(ref CThostFtdcChangeAccountField pChangeAccount) { }

		}




		private static ICtpTdApi _api;
		private static ICtpTdSpi _spi;

		private static string _frontAddr = "tcp://180.168.146.187:10130"; // 24h
		//private static string _frontAddr = "tcp://180.168.146.187:10100";
		private static string _brokerID = "9999";
		private static string _UserID = "097266";
		private static string _password = "hello@123";

		//[ClassInitialize]
		public static void Initialize(TestContext context)
		{
			_api = new CtpTdApi();
			_spi = new TestCtpTdSpi();
			_api.RegisterSpi(_spi);
			_api.RegisterFront(_frontAddr);
			_api.Init();

			Thread.Sleep(2000);
		}


		/// <summary>
		/// 清理测试用例
		/// </summary>
		//[ClassCleanup]
		public static void Cleanup()
		{
			//if (_isLogin)
			//{
			//    _apiBase.UserLogout(-4);
			//}
			//else if (_isConnected)
			//{
			//    _apiBase.Disconnect();
			//}
			//Thread.Sleep(100);
		}

		/// <summary>
		/// 测试获取接口版本
		/// </summary>
		[Test]
		public void TestGetApiVersion()
		{
			string result = CtpTdApi.GetApiVersion();
			Assert.IsTrue(!string.IsNullOrEmpty(result));
		}

		/// <summary>
		/// 测试获取交易日
		/// </summary>
		[Test]
		public void TestGetTradingDay()
		{
			string result = _api.GetTradingDay();
			Assert.AreEqual(8, result.Length);
		}

	}
}
