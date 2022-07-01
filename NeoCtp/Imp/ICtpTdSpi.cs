/********************************************************************
    created:	2020-09-01 1:02:04
    author:		rush
    email:		
	
    purpose:	
*********************************************************************/
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NeoCtp
{
	public interface ICtpTdSpi
	{
		///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
		void OnFrontConnected();

		///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
		///@param nReason 错误原因
		///        0x1001 网络读失败
		///        0x1002 网络写失败
		///        0x2001 接收心跳超时
		///        0x2002 发送心跳失败
		///        0x2003 收到错误报文
		void OnFrontDisconnected(int nReason);

		///心跳超时警告。当长时间未收到报文时，该方法被调用。
		///@param nTimeLapse 距离上次接收报文的时间
		void OnHeartBeatWarning(int nTimeLapse);


		///客户端认证响应
		void OnRspAuthenticate(ref CThostFtdcRspAuthenticateField pRspAuthenticateField, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);

		///登录请求响应
		void OnRspUserLogin(ref CThostFtdcRspUserLoginField pRspUserLogin, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
		///登出请求响应
		void OnRspUserLogout(ref CThostFtdcUserLogoutField pUserLogout, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);

		///用户口令更新请求响应
		void OnRspUserPasswordUpdate(ref CThostFtdcUserPasswordUpdateField pUserPasswordUpdate, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
		///资金账户口令更新请求响应
		void OnRspTradingAccountPasswordUpdate(ref CThostFtdcTradingAccountPasswordUpdateField pTradingAccountPasswordUpdate, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);

		///查询用户当前支持的认证模式的回复
		void OnRspUserAuthMethod(ref CThostFtdcRspUserAuthMethodField pRspUserAuthMethod, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);

		///获取图形验证码请求的回复
		void OnRspGenUserCaptcha(ref CThostFtdcRspGenUserCaptchaField pRspGenUserCaptcha, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
		///获取短信验证码请求的回复
		void OnRspGenUserText(ref CThostFtdcRspGenUserTextField pRspGenUserText, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);



		///报单录入请求响应
		void OnRspOrderInsert(ref CThostFtdcInputOrderField pInputOrder, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
		///预埋单录入请求响应
		void OnRspParkedOrderInsert(ref CThostFtdcParkedOrderField pParkedOrder, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
		///预埋撤单录入请求响应
		void OnRspParkedOrderAction(ref CThostFtdcParkedOrderActionField pParkedOrderAction, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);

		///报单操作请求响应
		void OnRspOrderAction(ref CThostFtdcInputOrderActionField pInputOrderAction, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);

		///查询最大报单数量响应
		void OnRspQueryMaxOrderVolume(ref CThostFtdcQueryMaxOrderVolumeField pQueryMaxOrderVolume, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);

		///投资者结算结果确认响应
		void OnRspSettlementInfoConfirm(ref CThostFtdcSettlementInfoConfirmField pSettlementInfoConfirm, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);

		///删除预埋单响应
		void OnRspRemoveParkedOrder(ref CThostFtdcRemoveParkedOrderField pRemoveParkedOrder, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);

		///删除预埋撤单响应
		void OnRspRemoveParkedOrderAction(ref CThostFtdcRemoveParkedOrderActionField pRemoveParkedOrderAction, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);

		///执行宣告录入请求响应
		void OnRspExecOrderInsert(ref CThostFtdcInputExecOrderField pInputExecOrder, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);

		///执行宣告操作请求响应
		void OnRspExecOrderAction(ref CThostFtdcInputExecOrderActionField pInputExecOrderAction, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);

		///询价录入请求响应
		void OnRspForQuoteInsert(ref CThostFtdcInputForQuoteField pInputForQuote, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);

		///报价录入请求响应
		void OnRspQuoteInsert(ref CThostFtdcInputQuoteField pInputQuote, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);

		///报价操作请求响应
		void OnRspQuoteAction(ref CThostFtdcInputQuoteActionField pInputQuoteAction, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);

		///批量报单操作请求响应
		void OnRspBatchOrderAction(ref CThostFtdcInputBatchOrderActionField pInputBatchOrderAction, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);

		///期权自对冲录入请求响应
		void OnRspOptionSelfCloseInsert(ref CThostFtdcInputOptionSelfCloseField pInputOptionSelfClose, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);

		///期权自对冲操作请求响应
		void OnRspOptionSelfCloseAction(ref CThostFtdcInputOptionSelfCloseActionField pInputOptionSelfCloseAction, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);

		///申请组合录入请求响应
		void OnRspCombActionInsert(ref CThostFtdcInputCombActionField pInputCombAction, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);

		///请求查询报单响应
		void OnRspQryOrder(ref CThostFtdcOrderField pOrder, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);

		///请求查询成交响应
		void OnRspQryTrade(ref CThostFtdcTradeField pTrade, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);

		///请求查询投资者持仓响应
		void OnRspQryInvestorPosition(ref CThostFtdcInvestorPositionField pInvestorPosition, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);

		///请求查询资金账户响应
		void OnRspQryTradingAccount(ref CThostFtdcTradingAccountField pTradingAccount, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);

		///请求查询投资者响应
		void OnRspQryInvestor(ref CThostFtdcInvestorField pInvestor, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);

		///请求查询交易编码响应
		void OnRspQryTradingCode(ref CThostFtdcTradingCodeField pTradingCode, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);

		///请求查询合约保证金率响应
		void OnRspQryInstrumentMarginRate(ref CThostFtdcInstrumentMarginRateField pInstrumentMarginRate, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);

		///请求查询合约手续费率响应
		void OnRspQryInstrumentCommissionRate(ref CThostFtdcInstrumentCommissionRateField pInstrumentCommissionRate, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);


		///请求查询交易所响应
		void OnRspQryExchange(ref CThostFtdcExchangeField pExchange, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);

		///请求查询产品响应
		void OnRspQryProduct(ref CThostFtdcProductField pProduct, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);

		///请求查询合约响应
		void OnRspQryInstrument(ref CThostFtdcInstrumentField pInstrument, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);


		///请求查询行情响应
		void OnRspQryDepthMarketData(ref CThostFtdcDepthMarketDataField pDepthMarketData, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);


		///请求查询投资者结算结果响应
		void OnRspQrySettlementInfo(ref CThostFtdcSettlementInfoField pSettlementInfo, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
		///请求查询转帐银行响应
		void OnRspQryTransferBank(ref CThostFtdcTransferBankField pTransferBank, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);

		///请求查询投资者持仓明细响应
		void OnRspQryInvestorPositionDetail(ref CThostFtdcInvestorPositionDetailField pInvestorPositionDetail, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);

		///请求查询客户通知响应
		void OnRspQryNotice(ref CThostFtdcNoticeField pNotice, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);

		///请求查询结算信息确认响应
		void OnRspQrySettlementInfoConfirm(ref CThostFtdcSettlementInfoConfirmField pSettlementInfoConfirm, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);

		///请求查询投资者持仓明细响应
		void OnRspQryInvestorPositionCombineDetail(ref CThostFtdcInvestorPositionCombineDetailField pInvestorPositionCombineDetail, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);

		///查询保证金监管系统经纪公司资金账户密钥响应
		void OnRspQryCFMMCTradingAccountKey(ref CThostFtdcCFMMCTradingAccountKeyField pCFMMCTradingAccountKey, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);

		///请求查询仓单折抵信息响应
		void OnRspQryEWarrantOffset(ref CThostFtdcEWarrantOffsetField pEWarrantOffset, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);

		///请求查询投资者品种/跨品种保证金响应
		void OnRspQryInvestorProductGroupMargin(ref CThostFtdcInvestorProductGroupMarginField pInvestorProductGroupMargin, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);

		///请求查询交易所保证金率响应
		void OnRspQryExchangeMarginRate(ref CThostFtdcExchangeMarginRateField pExchangeMarginRate, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);

		///请求查询交易所调整保证金率响应
		void OnRspQryExchangeMarginRateAdjust(ref CThostFtdcExchangeMarginRateAdjustField pExchangeMarginRateAdjust, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);

		///请求查询汇率响应
		void OnRspQryExchangeRate(ref CThostFtdcExchangeRateField pExchangeRate, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);

		///请求查询二级代理操作员银期权限响应
		void OnRspQrySecAgentACIDMap(ref CThostFtdcSecAgentACIDMapField pSecAgentACIDMap, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);

		///请求查询产品报价汇率
		void OnRspQryProductExchRate(ref CThostFtdcProductExchRateField pProductExchRate, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);

		///请求查询产品组
		void OnRspQryProductGroup(ref CThostFtdcProductGroupField pProductGroup, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);

		///请求查询做市商合约手续费率响应
		void OnRspQryMMInstrumentCommissionRate(ref CThostFtdcMMInstrumentCommissionRateField pMMInstrumentCommissionRate, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);

		///请求查询做市商期权合约手续费响应
		void OnRspQryMMOptionInstrCommRate(ref CThostFtdcMMOptionInstrCommRateField pMMOptionInstrCommRate, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);

		///请求查询报单手续费响应
		void OnRspQryInstrumentOrderCommRate(ref CThostFtdcInstrumentOrderCommRateField pInstrumentOrderCommRate, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);

		///请求查询资金账户响应
		void OnRspQrySecAgentTradingAccount(ref CThostFtdcTradingAccountField pTradingAccount, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);

		///请求查询二级代理商资金校验模式响应
		void OnRspQrySecAgentCheckMode(ref CThostFtdcSecAgentCheckModeField pSecAgentCheckMode, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);

		///请求查询二级代理商信息响应
		void OnRspQrySecAgentTradeInfo(ref CThostFtdcSecAgentTradeInfoField pSecAgentTradeInfo, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);

		///请求查询期权交易成本响应
		void OnRspQryOptionInstrTradeCost(ref CThostFtdcOptionInstrTradeCostField pOptionInstrTradeCost, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);

		///请求查询期权合约手续费响应
		void OnRspQryOptionInstrCommRate(ref CThostFtdcOptionInstrCommRateField pOptionInstrCommRate, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);

		///请求查询执行宣告响应
		void OnRspQryExecOrder(ref CThostFtdcExecOrderField pExecOrder, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);

		///请求查询询价响应
		void OnRspQryForQuote(ref CThostFtdcForQuoteField pForQuote, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);

		///请求查询报价响应
		void OnRspQryQuote(ref CThostFtdcQuoteField pQuote, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);

		///请求查询期权自对冲响应
		void OnRspQryOptionSelfClose(ref CThostFtdcOptionSelfCloseField pOptionSelfClose, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);

		///请求查询投资单元响应
		void OnRspQryInvestUnit(ref CThostFtdcInvestUnitField pInvestUnit, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);

		///请求查询组合合约安全系数响应
		void OnRspQryCombInstrumentGuard(ref CThostFtdcCombInstrumentGuardField pCombInstrumentGuard, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);

		///请求查询申请组合响应
		void OnRspQryCombAction(ref CThostFtdcCombActionField pCombAction, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);

		///请求查询转帐流水响应
		void OnRspQryTransferSerial(ref CThostFtdcTransferSerialField pTransferSerial, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);

		///请求查询银期签约关系响应
		void OnRspQryAccountregister(ref CThostFtdcAccountregisterField pAccountregister, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);



		///错误应答
		void OnRspError(ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);

		///报单通知
		void OnRtnOrder(ref CThostFtdcOrderField pOrder);

		///成交通知
		void OnRtnTrade(ref CThostFtdcTradeField pTrade);

		///报单录入错误回报
		void OnErrRtnOrderInsert(ref CThostFtdcInputOrderField pInputOrder, ref CThostFtdcRspInfoField pRspInfo);

		///报单操作错误回报
		void OnErrRtnOrderAction(ref CThostFtdcOrderActionField pOrderAction, ref CThostFtdcRspInfoField pRspInfo);

		///合约交易状态通知
		void OnRtnInstrumentStatus(ref CThostFtdcInstrumentStatusField pInstrumentStatus);

		///交易所公告通知
		void OnRtnBulletin(ref CThostFtdcBulletinField pBulletin) ;

		///交易通知
		void OnRtnTradingNotice(ref CThostFtdcTradingNoticeInfoField pTradingNoticeInfo);

		///提示条件单校验错误
		void OnRtnErrorConditionalOrder(ref CThostFtdcErrorConditionalOrderField pErrorConditionalOrder);

		///执行宣告通知
		void OnRtnExecOrder(ref CThostFtdcExecOrderField pExecOrder);

		///执行宣告录入错误回报
		void OnErrRtnExecOrderInsert(ref CThostFtdcInputExecOrderField pInputExecOrder, ref CThostFtdcRspInfoField pRspInfo);

		///执行宣告操作错误回报
		void OnErrRtnExecOrderAction(ref CThostFtdcExecOrderActionField pExecOrderAction, ref CThostFtdcRspInfoField pRspInfo);

		///询价录入错误回报
		void OnErrRtnForQuoteInsert(ref CThostFtdcInputForQuoteField pInputForQuote, ref CThostFtdcRspInfoField pRspInfo);

		///报价通知
		void OnRtnQuote(ref CThostFtdcQuoteField pQuote);

		///报价录入错误回报
		void OnErrRtnQuoteInsert(ref CThostFtdcInputQuoteField pInputQuote, ref CThostFtdcRspInfoField pRspInfo);

		///报价操作错误回报
		void OnErrRtnQuoteAction(ref CThostFtdcQuoteActionField pQuoteAction, ref CThostFtdcRspInfoField pRspInfo);

		///询价通知
		void OnRtnForQuoteRsp(ref CThostFtdcForQuoteRspField pForQuoteRsp);

		///保证金监控中心用户令牌
		void OnRtnCFMMCTradingAccountToken(ref CThostFtdcCFMMCTradingAccountTokenField pCFMMCTradingAccountToken);

		///批量报单操作错误回报
		void OnErrRtnBatchOrderAction(ref CThostFtdcBatchOrderActionField pBatchOrderAction, ref CThostFtdcRspInfoField pRspInfo);

		///期权自对冲通知
		void OnRtnOptionSelfClose(ref CThostFtdcOptionSelfCloseField pOptionSelfClose);

		///期权自对冲录入错误回报
		void OnErrRtnOptionSelfCloseInsert(ref CThostFtdcInputOptionSelfCloseField pInputOptionSelfClose, ref CThostFtdcRspInfoField pRspInfo);

		///期权自对冲操作错误回报
		void OnErrRtnOptionSelfCloseAction(ref CThostFtdcOptionSelfCloseActionField pOptionSelfCloseAction, ref CThostFtdcRspInfoField pRspInfo);

		///申请组合通知
		void OnRtnCombAction(ref CThostFtdcCombActionField pCombAction);

		///申请组合录入错误回报
		void OnErrRtnCombActionInsert(ref CThostFtdcInputCombActionField pInputCombAction, ref CThostFtdcRspInfoField pRspInfo);

		///请求查询签约银行响应
		void OnRspQryContractBank(ref CThostFtdcContractBankField pContractBank, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);

		///请求查询预埋单响应
		void OnRspQryParkedOrder(ref CThostFtdcParkedOrderField pParkedOrder, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);

		///请求查询预埋撤单响应
		void OnRspQryParkedOrderAction(ref CThostFtdcParkedOrderActionField pParkedOrderAction, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);

		///请求查询交易通知响应
		void OnRspQryTradingNotice(ref CThostFtdcTradingNoticeField pTradingNotice, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);

		///请求查询经纪公司交易参数响应
		void OnRspQryBrokerTradingParams(ref CThostFtdcBrokerTradingParamsField pBrokerTradingParams, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);

		///请求查询经纪公司交易算法响应
		void OnRspQryBrokerTradingAlgos(ref CThostFtdcBrokerTradingAlgosField pBrokerTradingAlgos, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);

		///请求查询监控中心用户令牌
		void OnRspQueryCFMMCTradingAccountToken(ref CThostFtdcQueryCFMMCTradingAccountTokenField pQueryCFMMCTradingAccountToken, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);

		///银行发起银行资金转期货通知
		void OnRtnFromBankToFutureByBank(ref CThostFtdcRspTransferField pRspTransfer);

		///银行发起期货资金转银行通知
		void OnRtnFromFutureToBankByBank(ref CThostFtdcRspTransferField pRspTransfer);

		///银行发起冲正银行转期货通知
		void OnRtnRepealFromBankToFutureByBank(ref CThostFtdcRspRepealField pRspRepeal);

		///银行发起冲正期货转银行通知
		void OnRtnRepealFromFutureToBankByBank(ref CThostFtdcRspRepealField pRspRepeal);

		///期货发起银行资金转期货通知
		void OnRtnFromBankToFutureByFuture(ref CThostFtdcRspTransferField pRspTransfer);

		///期货发起期货资金转银行通知
		void OnRtnFromFutureToBankByFuture(ref CThostFtdcRspTransferField pRspTransfer);

		///系统运行时期货端手工发起冲正银行转期货请求，银行处理完毕后报盘发回的通知
		void OnRtnRepealFromBankToFutureByFutureManual(ref CThostFtdcRspRepealField pRspRepeal);

		///系统运行时期货端手工发起冲正期货转银行请求，银行处理完毕后报盘发回的通知
		void OnRtnRepealFromFutureToBankByFutureManual(ref CThostFtdcRspRepealField pRspRepeal);

		///期货发起查询银行余额通知
		void OnRtnQueryBankBalanceByFuture(ref CThostFtdcNotifyQueryAccountField pNotifyQueryAccount);

		///期货发起银行资金转期货错误回报
		void OnErrRtnBankToFutureByFuture(ref CThostFtdcReqTransferField pReqTransfer, ref CThostFtdcRspInfoField pRspInfo);

		///期货发起期货资金转银行错误回报
		void OnErrRtnFutureToBankByFuture(ref CThostFtdcReqTransferField pReqTransfer, ref CThostFtdcRspInfoField pRspInfo);

		///系统运行时期货端手工发起冲正银行转期货错误回报
		void OnErrRtnRepealBankToFutureByFutureManual(ref CThostFtdcReqRepealField pReqRepeal, ref CThostFtdcRspInfoField pRspInfo);

		///系统运行时期货端手工发起冲正期货转银行错误回报
		void OnErrRtnRepealFutureToBankByFutureManual(ref CThostFtdcReqRepealField pReqRepeal, ref CThostFtdcRspInfoField pRspInfo);

		///期货发起查询银行余额错误回报
		void OnErrRtnQueryBankBalanceByFuture(ref CThostFtdcReqQueryAccountField pReqQueryAccount, ref CThostFtdcRspInfoField pRspInfo);

		///期货发起冲正银行转期货请求，银行处理完毕后报盘发回的通知
		void OnRtnRepealFromBankToFutureByFuture(ref CThostFtdcRspRepealField pRspRepeal);

		///期货发起冲正期货转银行请求，银行处理完毕后报盘发回的通知
		void OnRtnRepealFromFutureToBankByFuture(ref CThostFtdcRspRepealField pRspRepeal);

		///期货发起银行资金转期货应答
		void OnRspFromBankToFutureByFuture(ref CThostFtdcReqTransferField pReqTransfer, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);

		///期货发起期货资金转银行应答
		void OnRspFromFutureToBankByFuture(ref CThostFtdcReqTransferField pReqTransfer, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);

		///期货发起查询银行余额应答
		void OnRspQueryBankAccountMoneyByFuture(ref CThostFtdcReqQueryAccountField pReqQueryAccount, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);

		///银行发起银期开户通知
		void OnRtnOpenAccountByBank(ref CThostFtdcOpenAccountField pOpenAccount);

		///银行发起银期销户通知
		void OnRtnCancelAccountByBank(ref CThostFtdcCancelAccountField pCancelAccount);

		///银行发起变更银行账号通知
		void OnRtnChangeAccountByBank(ref CThostFtdcChangeAccountField pChangeAccount);
#pragma endregion


	}


}
