/********************************************************************
    created:	2020-08-11 11:52:49
    author:		neo
    email:		
	
    purpose:	该接口包含了原CTP的TraderSpi方法
*********************************************************************/
#pragma once
#include "pch.h"

extern "C"{

#pragma region 
	//回调委托声明

///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
typedef void (WINAPI *CBOnRspFrontConnected)();

///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
typedef void (WINAPI *CBOnRspFrontDisconnected)(int nReason);

///心跳超时警告。当长时间未收到报文时，该方法被调用。
typedef void (WINAPI *CBOnHeartBeatWarning)(int nTimeLapse);
///客户端认证响应
typedef void (WINAPI *CBOnRspAuthenticate)(CThostFtdcRspAuthenticateField *pRspAuthenticateField, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///登录请求响应
typedef void (WINAPI *CBOnRspUserLogin)(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///登出请求响应
typedef void (WINAPI *CBOnRspUserLogout)(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///用户口令更新请求响应
typedef void (WINAPI *CBRspUserPasswordUpdate)(CThostFtdcUserPasswordUpdateField *pUserPasswordUpdate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///资金账户口令更新请求响应
typedef void (WINAPI *CBRspTradingAccountPasswordUpdate)(CThostFtdcTradingAccountPasswordUpdateField *pTradingAccountPasswordUpdate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///查询用户当前支持的认证模式的回复
typedef void (WINAPI *CBRspUserAuthMethod)(CThostFtdcRspUserAuthMethodField *pRspUserAuthMethod, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///获取图形验证码请求的回复
typedef void (WINAPI *CBRspGenUserCaptcha)(CThostFtdcRspGenUserCaptchaField *pRspGenUserCaptcha, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///获取短信验证码请求的回复
typedef void (WINAPI *CBRspGenUserText)(CThostFtdcRspGenUserTextField *pRspGenUserText, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///报单录入请求响应
typedef void (WINAPI *CBOnRspOrderInsert)(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///预埋单录入请求响应
typedef void (WINAPI *CBRspParkedOrderInsert)(CThostFtdcParkedOrderField *pParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///预埋撤单录入请求响应
typedef void (WINAPI *CBRspParkedOrderAction)(CThostFtdcParkedOrderActionField *pParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///报单操作请求响应
typedef void (WINAPI *CBOnRspOrderAction)(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///查询最大报单数量响应
typedef void (WINAPI *CBRspQueryMaxOrderVolume)(CThostFtdcQryMaxOrderVolumeField *pQueryMaxOrderVolume, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///投资者结算结果确认响应
typedef void (WINAPI *CBOnRspSettlementInfoConfirm)(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///删除预埋单响应
typedef void (WINAPI *CBRspRemoveParkedOrder)(CThostFtdcRemoveParkedOrderField *pRemoveParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///删除预埋撤单响应
typedef void (WINAPI *CBRspRemoveParkedOrderAction)(CThostFtdcRemoveParkedOrderActionField *pRemoveParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///执行宣告录入请求响应
typedef void (WINAPI *CBRspExecOrderInsert)(CThostFtdcInputExecOrderField *pInputExecOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///执行宣告操作请求响应
typedef void (WINAPI *CBRspExecOrderAction)(CThostFtdcInputExecOrderActionField *pInputExecOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///询价录入请求响应
typedef void (WINAPI *CBRspForQuoteInsert)(CThostFtdcInputForQuoteField *pInputForQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///报价录入请求响应
typedef void (WINAPI *CBRspQuoteInsert)(CThostFtdcInputQuoteField *pInputQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///报价操作请求响应
typedef void (WINAPI *CBRspQuoteAction)(CThostFtdcInputQuoteActionField *pInputQuoteAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///批量报单操作请求响应
typedef void (WINAPI *CBRspBatchOrderAction)(CThostFtdcInputBatchOrderActionField *pInputBatchOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///期权自对冲录入请求响应
typedef void (WINAPI *CBRspOptionSelfCloseInsert)(CThostFtdcInputOptionSelfCloseField *pInputOptionSelfClose, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///期权自对冲操作请求响应
typedef void (WINAPI *CBRspOptionSelfCloseAction)(CThostFtdcInputOptionSelfCloseActionField *pInputOptionSelfCloseAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///申请组合录入请求响应
typedef void (WINAPI *CBRspCombActionInsert)(CThostFtdcInputCombActionField *pInputCombAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///请求查询报单响应
typedef void (WINAPI *CBOnRspQryOrder)(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///请求查询成交响应
typedef void (WINAPI *CBOnRspQryTrade)(CThostFtdcTradeField *pTrade, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///请求查询投资者持仓响应
typedef void (WINAPI *CBOnRspQryInvestorPosition)(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///请求查询资金账户响应
typedef void (WINAPI *CBOnRspQryTradingAccount)(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///请求查询投资者响应
typedef void (WINAPI *CBRspQryInvestor)(CThostFtdcInvestorField *pInvestor, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///请求查询交易编码响应
typedef void (WINAPI *CBRspQryTradingCode)(CThostFtdcTradingCodeField *pTradingCode, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///请求查询合约保证金率响应
typedef void (WINAPI *CBRspQryInstrumentMarginRate)(CThostFtdcInstrumentMarginRateField *pInstrumentMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///请求查询合约手续费率响应
typedef void (WINAPI *CBRspQryInstrumentCommissionRate)(CThostFtdcInstrumentCommissionRateField *pInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///请求查询交易所响应
typedef void (WINAPI *CBRspQryExchange)(CThostFtdcExchangeField *pExchange, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///请求查询合约响应
typedef void (WINAPI *CBOnRspQryInstrument)(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///请求查询行情响应
typedef void (WINAPI *CBRspQryDepthMarketData)(CThostFtdcDepthMarketDataField *pDepthMarketData, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///请求查询投资者结算结果响应
typedef void (WINAPI *CBRspQrySettlementInfo)(CThostFtdcSettlementInfoField *pSettlementInfo, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///请求查询转帐银行响应
typedef void (WINAPI *CBRspQryTransferBank)(CThostFtdcTransferBankField *pTransferBank, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///请求查询投资者持仓明细响应
typedef void (WINAPI *CBRspQryInvestorPositionDetail)(CThostFtdcInvestorPositionDetailField *pInvestorPositionDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///请求查询客户通知响应
typedef void (WINAPI *CBRspQryNotice)(CThostFtdcNoticeField *pNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///请求查询结算信息确认响应
typedef void (WINAPI *CBRspQrySettlementInfoConfirm)(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///请求查询投资者持仓明细响应
typedef void (WINAPI *CBRspQryInvestorPositionCombineDetail)(CThostFtdcInvestorPositionCombineDetailField *pInvestorPositionCombineDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///查询保证金监管系统经纪公司资金账户密钥响应
typedef void (WINAPI *CBRspQryCFMMCTradingAccountKey)(CThostFtdcCFMMCTradingAccountKeyField *pCFMMCTradingAccountKey, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///请求查询仓单折抵信息响应
typedef void (WINAPI *CBRspQryEWarrantOffset)(CThostFtdcEWarrantOffsetField *pEWarrantOffset, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///请求查询投资者品种/跨品种保证金响应
typedef void (WINAPI *CBRspQryInvestorProductGroupMargin)(CThostFtdcInvestorProductGroupMarginField *pInvestorProductGroupMargin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///请求查询交易所保证金率响应
typedef void (WINAPI *CBRspQryExchangeMarginRate)(CThostFtdcExchangeMarginRateField *pExchangeMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///请求查询交易所调整保证金率响应
typedef void (WINAPI *CBRspQryExchangeMarginRateAdjust)(CThostFtdcExchangeMarginRateAdjustField *pExchangeMarginRateAdjust, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///请求查询汇率响应
typedef void (WINAPI *CBRspQryExchangeRate)(CThostFtdcExchangeRateField *pExchangeRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///请求查询二级代理操作员银期权限响应
typedef void (WINAPI *CBRspQrySecAgentACIDMap)(CThostFtdcSecAgentACIDMapField *pSecAgentACIDMap, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///请求查询产品报价汇率
typedef void (WINAPI *CBRspQryProductExchRate)(CThostFtdcProductExchRateField *pProductExchRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///请求查询产品组
typedef void (WINAPI *CBRspQryProductGroup)(CThostFtdcProductGroupField *pProductGroup, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///请求查询做市商合约手续费率响应
typedef void (WINAPI *CBRspQryMMInstrumentCommissionRate)(CThostFtdcMMInstrumentCommissionRateField *pMMInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///请求查询做市商期权合约手续费响应
typedef void (WINAPI *CBRspQryMMOptionInstrCommRate)(CThostFtdcMMOptionInstrCommRateField *pMMOptionInstrCommRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///请求查询报单手续费响应
typedef void (WINAPI *CBRspQryInstrumentOrderCommRate)(CThostFtdcInstrumentOrderCommRateField *pInstrumentOrderCommRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///请求查询资金账户响应
typedef void (WINAPI *CBRspQrySecAgentTradingAccount)(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///请求查询二级代理商资金校验模式响应
typedef void (WINAPI *CBRspQrySecAgentCheckMode)(CThostFtdcSecAgentCheckModeField *pSecAgentCheckMode, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///请求查询二级代理商信息响应
typedef void (WINAPI *CBRspQrySecAgentTradeInfo)(CThostFtdcSecAgentTradeInfoField *pSecAgentTradeInfo, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///请求查询期权交易成本响应
typedef void (WINAPI *CBRspQryOptionInstrTradeCost)(CThostFtdcOptionInstrTradeCostField *pOptionInstrTradeCost, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///请求查询期权合约手续费响应
typedef void (WINAPI *CBRspQryOptionInstrCommRate)(CThostFtdcOptionInstrCommRateField *pOptionInstrCommRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///请求查询执行宣告响应
typedef void (WINAPI *CBRspQryExecOrder)(CThostFtdcExecOrderField *pExecOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///请求查询询价响应
typedef void (WINAPI *CBRspQryForQuote)(CThostFtdcForQuoteField *pForQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///请求查询报价响应
typedef void (WINAPI *CBRspQryQuote)(CThostFtdcQuoteField *pQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///请求查询期权自对冲响应
typedef void (WINAPI *CBRspQryOptionSelfClose)(CThostFtdcOptionSelfCloseField *pOptionSelfClose, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///请求查询投资单元响应
typedef void (WINAPI *CBRspQryInvestUnit)(CThostFtdcInvestUnitField *pInvestUnit, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///请求查询组合合约安全系数响应
typedef void (WINAPI *CBRspQryCombInstrumentGuard)(CThostFtdcCombInstrumentGuardField *pCombInstrumentGuard, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///请求查询申请组合响应
typedef void (WINAPI *CBRspQryCombAction)(CThostFtdcCombActionField *pCombAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///请求查询转帐流水响应
typedef void (WINAPI *CBRspQryTransferSerial)(CThostFtdcTransferSerialField *pTransferSerial, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///请求查询银期签约关系响应
typedef void (WINAPI *CBOnRspQryAccountregister)(CThostFtdcAccountregisterField *pAccountregister, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///错误应答
typedef void (WINAPI *CBOnRspError)(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///报单通知
typedef void (WINAPI *CBOnRtnOrder)(CThostFtdcOrderField *pOrder);
///成交通知
typedef void (WINAPI *CBOnRtnTrade)(CThostFtdcTradeField *pTrade);
///报单录入错误回报
typedef void (WINAPI *CBOnErrRtnOrderInsert)(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo);
///报单操作错误回报
typedef void (WINAPI *CBOnErrRtnOrderAction)(CThostFtdcOrderActionField *pOrderAction, CThostFtdcRspInfoField *pRspInfo);
///合约交易状态通知
typedef void (WINAPI *CBRtnInstrumentStatus)(CThostFtdcInstrumentStatusField *pInstrumentStatus);
///交易通知
typedef void (WINAPI *CBRtnTradingNotice)(CThostFtdcTradingNoticeInfoField *pTradingNoticeInfo);
///提示条件单校验错误
typedef void (WINAPI *CBRtnErrorConditionalOrder)(CThostFtdcErrorConditionalOrderField *pErrorConditionalOrder);
///执行宣告通知
typedef void (WINAPI *CBRtnExecOrder)(CThostFtdcExecOrderField *pExecOrder);
///执行宣告录入错误回报
typedef void (WINAPI *CBErrRtnExecOrderInsert)(CThostFtdcInputExecOrderField *pInputExecOrder, CThostFtdcRspInfoField *pRspInfo);
///执行宣告操作错误回报
typedef void (WINAPI *CBErrRtnExecOrderAction)(CThostFtdcExecOrderActionField *pExecOrderAction, CThostFtdcRspInfoField *pRspInfo);
///询价录入错误回报
typedef void (WINAPI *CBErrRtnForQuoteInsert)(CThostFtdcInputForQuoteField *pInputForQuote, CThostFtdcRspInfoField *pRspInfo);
///报价通知
typedef void (WINAPI *CBRtnQuote)(CThostFtdcQuoteField *pQuote);
///报价录入错误回报
typedef void (WINAPI *CBErrRtnQuoteInsert)(CThostFtdcInputQuoteField *pInputQuote, CThostFtdcRspInfoField *pRspInfo);
///报价操作错误回报
typedef void (WINAPI *CBErrRtnQuoteAction)(CThostFtdcQuoteActionField *pQuoteAction, CThostFtdcRspInfoField *pRspInfo);
///询价通知
typedef void (WINAPI *CBRtnForQuoteRsp)(CThostFtdcForQuoteRspField *pForQuoteRsp);
///保证金监控中心用户令牌
typedef void (WINAPI *CBRtnCFMMCTradingAccountToken)(CThostFtdcCFMMCTradingAccountTokenField *pCFMMCTradingAccountToken);
///批量报单操作错误回报
typedef void (WINAPI *CBErrRtnBatchOrderAction)(CThostFtdcBatchOrderActionField *pBatchOrderAction, CThostFtdcRspInfoField *pRspInfo);
///期权自对冲通知
typedef void (WINAPI *CBRtnOptionSelfClose)(CThostFtdcOptionSelfCloseField *pOptionSelfClose);
///期权自对冲录入错误回报
typedef void (WINAPI *CBErrRtnOptionSelfCloseInsert)(CThostFtdcInputOptionSelfCloseField *pInputOptionSelfClose, CThostFtdcRspInfoField *pRspInfo);
///期权自对冲操作错误回报
typedef void (WINAPI *CBErrRtnOptionSelfCloseAction)(CThostFtdcOptionSelfCloseActionField *pOptionSelfCloseAction, CThostFtdcRspInfoField *pRspInfo);
///申请组合通知
typedef void (WINAPI *CBRtnCombAction)(CThostFtdcCombActionField *pCombAction);
///申请组合录入错误回报
typedef void (WINAPI *CBErrRtnCombActionInsert)(CThostFtdcInputCombActionField *pInputCombAction, CThostFtdcRspInfoField *pRspInfo);
///请求查询签约银行响应
typedef void (WINAPI *CBRspQryContractBank)(CThostFtdcContractBankField *pContractBank, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///请求查询预埋单响应
typedef void (WINAPI *CBRspQryParkedOrder)(CThostFtdcParkedOrderField *pParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///请求查询预埋撤单响应
typedef void (WINAPI *CBRspQryParkedOrderAction)(CThostFtdcParkedOrderActionField *pParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///请求查询交易通知响应
typedef void (WINAPI *CBRspQryTradingNotice)(CThostFtdcTradingNoticeField *pTradingNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///请求查询经纪公司交易参数响应
typedef void (WINAPI *CBRspQryBrokerTradingParams)(CThostFtdcBrokerTradingParamsField *pBrokerTradingParams, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///请求查询经纪公司交易算法响应
typedef void (WINAPI *CBRspQryBrokerTradingAlgos)(CThostFtdcBrokerTradingAlgosField *pBrokerTradingAlgos, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///请求查询监控中心用户令牌
typedef void (WINAPI *CBRspQueryCFMMCTradingAccountToken)(CThostFtdcQueryCFMMCTradingAccountTokenField *pQueryCFMMCTradingAccountToken, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///银行发起银行资金转期货通知
typedef void (WINAPI *CBRtnFromBankToFutureByBank)(CThostFtdcRspTransferField *pRspTransfer);
///银行发起期货资金转银行通知
typedef void (WINAPI *CBRtnFromFutureToBankByBank)(CThostFtdcRspTransferField *pRspTransfer);
///银行发起冲正银行转期货通知
typedef void (WINAPI *CBRtnRepealFromBankToFutureByBank)(CThostFtdcRspRepealField *pRspRepeal);
///银行发起冲正期货转银行通知
typedef void (WINAPI *CBRtnRepealFromFutureToBankByBank)(CThostFtdcRspRepealField *pRspRepeal);
///期货发起银行资金转期货通知
typedef void (WINAPI *CBRtnFromBankToFutureByFuture)(CThostFtdcRspTransferField *pRspTransfer);
///期货发起期货资金转银行通知
typedef void (WINAPI *CBRtnFromFutureToBankByFuture)(CThostFtdcRspTransferField *pRspTransfer);
///系统运行时期货端手工发起冲正银行转期货请求，银行处理完毕后报盘发回的通知
typedef void (WINAPI *CBRtnRepealFromBankToFutureByFutureManual)(CThostFtdcRspRepealField *pRspRepeal);
///系统运行时期货端手工发起冲正期货转银行请求，银行处理完毕后报盘发回的通知
typedef void (WINAPI *CBRtnRepealFromFutureToBankByFutureManual)(CThostFtdcRspRepealField *pRspRepeal);
///期货发起查询银行余额通知
typedef void (WINAPI *CBRtnQueryBankBalanceByFuture)(CThostFtdcNotifyQueryAccountField *pNotifyQueryAccount);
///期货发起银行资金转期货错误回报
typedef void (WINAPI *CBErrRtnBankToFutureByFuture)(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo);
///期货发起期货资金转银行错误回报
typedef void (WINAPI *CBErrRtnFutureToBankByFuture)(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo);
///系统运行时期货端手工发起冲正银行转期货错误回报
typedef void (WINAPI *CBErrRtnRepealBankToFutureByFutureManual)(CThostFtdcReqRepealField *pReqRepeal, CThostFtdcRspInfoField *pRspInfo);
///系统运行时期货端手工发起冲正期货转银行错误回报
typedef void (WINAPI *CBErrRtnRepealFutureToBankByFutureManual)(CThostFtdcReqRepealField *pReqRepeal, CThostFtdcRspInfoField *pRspInfo);
///期货发起查询银行余额错误回报
typedef void (WINAPI *CBErrRtnQueryBankBalanceByFuture)(CThostFtdcReqQueryAccountField *pReqQueryAccount, CThostFtdcRspInfoField *pRspInfo);
///期货发起冲正银行转期货请求，银行处理完毕后报盘发回的通知
typedef void (WINAPI *CBRtnRepealFromBankToFutureByFuture)(CThostFtdcRspRepealField *pRspRepeal);
///期货发起冲正期货转银行请求，银行处理完毕后报盘发回的通知
typedef void (WINAPI *CBRtnRepealFromFutureToBankByFuture)(CThostFtdcRspRepealField *pRspRepeal);
///期货发起银行资金转期货应答
typedef void (WINAPI *CBRspFromBankToFutureByFuture)(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///期货发起期货资金转银行应答
typedef void (WINAPI *CBRspFromFutureToBankByFuture)(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///期货发起查询银行余额应答
typedef void (WINAPI *CBRspQueryBankAccountMoneyByFuture)(CThostFtdcReqQueryAccountField *pReqQueryAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
///银行发起银期开户通知
typedef void (WINAPI *CBRtnOpenAccountByBank)(CThostFtdcOpenAccountField *pOpenAccount);
///银行发起银期销户通知
typedef void (WINAPI *CBRtnCancelAccountByBank)(CThostFtdcCancelAccountField *pCancelAccount);
///银行发起变更银行账号通知
typedef void (WINAPI *CBRtnChangeAccountByBank)(CThostFtdcChangeAccountField *pChangeAccount);

}

#pragma endregion

class TraderSpi : public CThostFtdcTraderSpi
{
public:
#pragma region 
	//回调委托实例
	///委托实例
	CBOnRspFrontConnected cbOnFrontConnected = 0;		///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
	CBOnRspFrontDisconnected cbOnFrontDisconnected = 0;		///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
	CBOnHeartBeatWarning cbOnHeartBeatWarning = 0;		///心跳超时警告。当长时间未收到报文时，该方法被调用。
	CBOnRspAuthenticate cbOnRspAuthenticate = 0;	///客户端认证响应
	CBOnRspUserLogin cbOnRspUserLogin = 0;	///登录请求响应
	CBOnRspUserLogout cbOnRspUserLogout = 0;	///登出请求响应
	CBRspUserPasswordUpdate cbRspUserPasswordUpdate = 0;	///用户口令更新请求响应
	CBRspTradingAccountPasswordUpdate cbRspTradingAccountPasswordUpdate = 0;	///资金账户口令更新请求响应
	CBRspUserAuthMethod cbRspUserAuthMethod = 0; ///查询用户当前支持的认证模式的回复
	CBRspGenUserCaptcha cbRspGenUserCaptcha = 0; ///获取图形验证码请求的回复
	CBRspGenUserText cbRspGenUserText = 0; ///获取短信验证码请求的回复
	CBOnRspOrderInsert cbRspOrderInsert = 0;	///报单录入请求响应
	CBRspParkedOrderInsert cbRspParkedOrderInsert = 0;	///预埋单录入请求响应
	CBRspParkedOrderAction cbRspParkedOrderAction = 0;	///预埋撤单录入请求响应
	CBOnRspOrderAction cbRspOrderAction = 0;	///报单操作请求响应
	CBRspQueryMaxOrderVolume cbRspQueryMaxOrderVolume = 0;	///查询最大报单数量响应
	CBOnRspSettlementInfoConfirm cbRspSettlementInfoConfirm = 0;	///投资者结算结果确认响应
	CBRspRemoveParkedOrder cbRspRemoveParkedOrder = 0;	///删除预埋单响应
	CBRspRemoveParkedOrderAction cbRspRemoveParkedOrderAction = 0;	///删除预埋撤单响应
	CBRspExecOrderInsert cbRspExecOrderInsert = 0;	///执行宣告录入请求响应
	CBRspExecOrderAction cbRspExecOrderAction = 0;	///执行宣告操作请求响应
	CBRspForQuoteInsert cbRspForQuoteInsert = 0;	///询价录入请求响应
	CBRspQuoteInsert cbRspQuoteInsert = 0;	///报价录入请求响应
	CBRspQuoteAction cbRspQuoteAction = 0;	///报价操作请求响应
	CBRspBatchOrderAction cbRspBatchOrderAction = 0;	///批量报单操作请求响应
	CBRspOptionSelfCloseInsert cbRspOptionSelfCloseInsert = 0;	///期权自对冲录入请求响应
	CBRspOptionSelfCloseAction cbRspOptionSelfCloseAction = 0; ///期权自对冲操作请求响应
	CBRspCombActionInsert cbRspCombActionInsert = 0;	///申请组合录入请求响应
	CBOnRspQryOrder cbRspQryOrder = 0;	///请求查询报单响应
	CBOnRspQryTrade cbRspQryTrade = 0;	///请求查询成交响应
	CBOnRspQryInvestorPosition cbRspQryInvestorPosition = 0;	///请求查询投资者持仓响应
	CBOnRspQryTradingAccount cbRspQryTradingAccount = 0;	///请求查询资金账户响应
	CBRspQryInvestor cbRspQryInvestor = 0;	///请求查询投资者响应
	CBRspQryTradingCode cbRspQryTradingCode = 0;	///请求查询交易编码响应
	CBRspQryInstrumentMarginRate cbRspQryInstrumentMarginRate = 0;	///请求查询合约保证金率响应
	CBRspQryInstrumentCommissionRate cbRspQryInstrumentCommissionRate = 0;	///请求查询合约手续费率响应
	CBRspQryExchange cbRspQryExchange = 0;	///请求查询交易所响应
	CBOnRspQryInstrument cbRspQryInstrument = 0;	///请求查询合约响应
	CBRspQryDepthMarketData cbRspQryDepthMarketData = 0;	///请求查询行情响应
	CBRspQrySettlementInfo cbRspQrySettlementInfo = 0;	///请求查询投资者结算结果响应
	CBRspQryTransferBank cbRspQryTransferBank = 0;	///请求查询转帐银行响应
	CBRspQryInvestorPositionDetail cbRspQryInvestorPositionDetail = 0;	///请求查询投资者持仓明细响应
	CBRspQryNotice cbRspQryNotice = 0;	///请求查询客户通知响应
	CBRspQrySettlementInfoConfirm cbRspQrySettlementInfoConfirm = 0;	///请求查询结算信息确认响应
	CBRspQryInvestorPositionCombineDetail cbRspQryInvestorPositionCombineDetail = 0;	///请求查询投资者持仓明细响应
	CBRspQryCFMMCTradingAccountKey cbRspQryCFMMCTradingAccountKey = 0;	///查询保证金监管系统经纪公司资金账户密钥响应
	CBRspQryEWarrantOffset cbRspQryEWarrantOffset = 0;	///请求查询仓单折抵信息响应
	CBRspQryInvestorProductGroupMargin cbRspQryInvestorProductGroupMargin = 0;	///请求查询投资者品种/跨品种保证金响应
	CBRspQryExchangeMarginRate cbRspQryExchangeMarginRate = 0;	///请求查询交易所保证金率响应
	CBRspQryExchangeMarginRateAdjust cbRspQryExchangeMarginRateAdjust = 0;	///请求查询交易所调整保证金率响应
	CBRspQryExchangeRate cbRspQryExchangeRate = 0;	///请求查询汇率响应
	CBRspQrySecAgentACIDMap cbRspQrySecAgentACIDMap = 0;	///请求查询二级代理操作员银期权限响应
	CBRspQryProductExchRate cbRspQryProductExchRate = 0;	///请求查询产品报价汇率
	CBRspQryProductGroup cbRspQryProductGroup = 0;	///请求查询产品组
	CBRspQryMMInstrumentCommissionRate cbRspQryMMInstrumentCommissionRate = 0;	///请求查询做市商合约手续费率响应
	CBRspQryMMOptionInstrCommRate cbRspQryMMOptionInstrCommRate = 0;	///请求查询做市商期权合约手续费响应
	CBRspQryInstrumentOrderCommRate cbRspQryInstrumentOrderCommRate = 0;	///请求查询报单手续费响应
	CBRspQrySecAgentTradingAccount cbRspQrySecAgentTradingAccount = 0;	///请求查询资金账户响应
	CBRspQrySecAgentCheckMode cbRspQrySecAgentCheckMode = 0;	///请求查询二级代理商资金校验模式响应
	CBRspQrySecAgentTradeInfo cbRspQrySecAgentTradeInfo = 0;	///请求查询二级代理商信息响应
	CBRspQryOptionInstrTradeCost cbRspQryOptionInstrTradeCost = 0;	///请求查询期权交易成本响应
	CBRspQryOptionInstrCommRate cbRspQryOptionInstrCommRate = 0;	///请求查询期权合约手续费响应
	CBRspQryExecOrder cbRspQryExecOrder = 0;	///请求查询执行宣告响应
	CBRspQryForQuote cbRspQryForQuote = 0;	///请求查询询价响应
	CBRspQryQuote cbRspQryQuote = 0;	///请求查询报价响应
	CBRspQryOptionSelfClose cbRspQryOptionSelfClose = 0;	///请求查询期权自对冲响应
	CBRspQryInvestUnit cbRspQryInvestUnit = 0;	///请求查询投资单元响应
	CBRspQryCombInstrumentGuard cbRspQryCombInstrumentGuard = 0;	///请求查询组合合约安全系数响应
	CBRspQryCombAction cbRspQryCombAction = 0;	///请求查询申请组合响应
	CBRspQryTransferSerial cbRspQryTransferSerial = 0;	///请求查询转帐流水响应
	CBOnRspQryAccountregister cbRspQryAccountregister = 0;///请求查询银期签约关系响应
	CBOnRspError cbRspError = 0;	///错误应答
	CBOnRtnOrder cbRtnOrder = 0;	///报单通知
	CBOnRtnTrade cbRtnTrade = 0;	///成交通知
	CBOnErrRtnOrderInsert cbErrRtnOrderInsert = 0;	///报单录入错误回报
	CBOnErrRtnOrderAction cbErrRtnOrderAction = 0;	///报单操作错误回报
	CBRtnInstrumentStatus cbRtnInstrumentStatus = 0;	///合约交易状态通知
	CBRtnTradingNotice cbRtnTradingNotice = 0;	///交易通知
	CBRtnErrorConditionalOrder cbRtnErrorConditionalOrder = 0;	///提示条件单校验错误
	CBRtnExecOrder cbRtnExecOrder = 0;	///执行宣告通知
	CBErrRtnExecOrderInsert cbErrRtnExecOrderInsert = 0;	///执行宣告录入错误回报
	CBErrRtnExecOrderAction cbErrRtnExecOrderAction = 0;	///执行宣告操作错误回报
	CBErrRtnForQuoteInsert cbErrRtnForQuoteInsert = 0;	///询价录入错误回报
	CBRtnQuote cbRtnQuote = 0;	///报价通知
	CBErrRtnQuoteInsert cbErrRtnQuoteInsert = 0;	///报价录入错误回报
	CBErrRtnQuoteAction cbErrRtnQuoteAction = 0;	///报价操作错误回报
	CBRtnForQuoteRsp cbRtnForQuoteRsp = 0;	///询价通知
	CBRtnCFMMCTradingAccountToken cbRtnCFMMCTradingAccountToken = 0;	///保证金监控中心用户令牌
	CBErrRtnBatchOrderAction cbErrRtnBatchOrderAction = 0;	///批量报单操作错误回报
	CBRtnOptionSelfClose cbRtnOptionSelfClose = 0;	///期权自对冲通知
	CBErrRtnOptionSelfCloseInsert cbErrRtnOptionSelfCloseInsert = 0;	///期权自对冲录入错误回报
	CBErrRtnOptionSelfCloseAction cbErrRtnOptionSelfCloseAction = 0;	///期权自对冲操作错误回报
	CBRtnCombAction cbRtnCombAction = 0;	///申请组合通知
	CBErrRtnCombActionInsert cbErrRtnCombActionInsert = 0;	///申请组合录入错误回报
	CBRspQryContractBank cbRspQryContractBank = 0;	///请求查询签约银行响应
	CBRspQryParkedOrder cbRspQryParkedOrder = 0;	///请求查询预埋单响应
	CBRspQryParkedOrderAction cbRspQryParkedOrderAction = 0;	///请求查询预埋撤单响应
	CBRspQryTradingNotice cbRspQryTradingNotice = 0;	///请求查询交易通知响应
	CBRspQryBrokerTradingParams cbRspQryBrokerTradingParams = 0;	///请求查询经纪公司交易参数响应
	CBRspQryBrokerTradingAlgos cbRspQryBrokerTradingAlgos = 0;	///请求查询经纪公司交易算法响应
	CBRspQueryCFMMCTradingAccountToken cbRspQueryCFMMCTradingAccountToken = 0;	///请求查询监控中心用户令牌
	CBRtnFromBankToFutureByBank cbRtnFromBankToFutureByBank = 0;	///银行发起银行资金转期货通知
	CBRtnFromFutureToBankByBank cbRtnFromFutureToBankByBank = 0;	///银行发起期货资金转银行通知
	CBRtnRepealFromBankToFutureByBank cbRtnRepealFromBankToFutureByBank = 0;	///银行发起冲正银行转期货通知
	CBRtnRepealFromFutureToBankByBank cbRtnRepealFromFutureToBankByBank = 0;	///银行发起冲正期货转银行通知
	CBRtnFromBankToFutureByFuture cbRtnFromBankToFutureByFuture = 0;	///期货发起银行资金转期货通知
	CBRtnFromFutureToBankByFuture cbRtnFromFutureToBankByFuture = 0;	///期货发起期货资金转银行通知
	CBRtnRepealFromBankToFutureByFutureManual cbRtnRepealFromBankToFutureByFutureManual = 0;	///系统运行时期货端手工发起冲正银行转期货请求，银行处理完毕后报盘发回的通知
	CBRtnRepealFromFutureToBankByFutureManual cbRtnRepealFromFutureToBankByFutureManual = 0;	///系统运行时期货端手工发起冲正期货转银行请求，银行处理完毕后报盘发回的通知
	CBRtnQueryBankBalanceByFuture cbRtnQueryBankBalanceByFuture = 0;	///期货发起查询银行余额通知
	CBErrRtnBankToFutureByFuture cbErrRtnBankToFutureByFuture = 0;	///期货发起银行资金转期货错误回报
	CBErrRtnFutureToBankByFuture cbErrRtnFutureToBankByFuture = 0;	///期货发起期货资金转银行错误回报
	CBErrRtnRepealBankToFutureByFutureManual cbErrRtnRepealBankToFutureByFutureManual = 0;	///系统运行时期货端手工发起冲正银行转期货错误回报
	CBErrRtnRepealFutureToBankByFutureManual cbErrRtnRepealFutureToBankByFutureManual = 0;	///系统运行时期货端手工发起冲正期货转银行错误回报
	CBErrRtnQueryBankBalanceByFuture cbErrRtnQueryBankBalanceByFuture = 0;	///期货发起查询银行余额错误回报
	CBRtnRepealFromBankToFutureByFuture cbRtnRepealFromBankToFutureByFuture = 0;	///期货发起冲正银行转期货请求，银行处理完毕后报盘发回的通知
	CBRtnRepealFromFutureToBankByFuture cbRtnRepealFromFutureToBankByFuture = 0;	///期货发起冲正期货转银行请求，银行处理完毕后报盘发回的通知
	CBRspFromBankToFutureByFuture cbRspFromBankToFutureByFuture = 0;	///期货发起银行资金转期货应答
	CBRspFromFutureToBankByFuture cbRspFromFutureToBankByFuture = 0;	///期货发起期货资金转银行应答
	CBRspQueryBankAccountMoneyByFuture cbRspQueryBankAccountMoneyByFuture = 0;	///期货发起查询银行余额应答
	CBRtnOpenAccountByBank cbRtnOpenAccountByBank = 0;	///银行发起银期开户通知
	CBRtnCancelAccountByBank cbRtnCancelAccountByBank = 0;	///银行发起银期销户通知
	CBRtnChangeAccountByBank cbRtnChangeAccountByBank = 0;	///银行发起变更银行账号通知
#pragma endregion


#pragma region Interface
	///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
	virtual void OnFrontConnected() ;
	
	///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
	///@param nReason 错误原因
	///        0x1001 网络读失败
	///        0x1002 网络写失败
	///        0x2001 接收心跳超时
	///        0x2002 发送心跳失败
	///        0x2003 收到错误报文
	virtual void OnFrontDisconnected(int nReason) ;
		
	///心跳超时警告。当长时间未收到报文时，该方法被调用。
	///@param nTimeLapse 距离上次接收报文的时间
	virtual void OnHeartBeatWarning(int nTimeLapse) ;
	

	///客户端认证响应
	virtual void OnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticateField, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///登录请求响应
	virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;
	///登出请求响应
	virtual void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///用户口令更新请求响应
	virtual void OnRspUserPasswordUpdate(CThostFtdcUserPasswordUpdateField *pUserPasswordUpdate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;
	///资金账户口令更新请求响应
	virtual void OnRspTradingAccountPasswordUpdate(CThostFtdcTradingAccountPasswordUpdateField *pTradingAccountPasswordUpdate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///查询用户当前支持的认证模式的回复
	virtual void OnRspUserAuthMethod(CThostFtdcRspUserAuthMethodField *pRspUserAuthMethod, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///获取图形验证码请求的回复
	virtual void OnRspGenUserCaptcha(CThostFtdcRspGenUserCaptchaField *pRspGenUserCaptcha, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;
	///获取短信验证码请求的回复
	virtual void OnRspGenUserText(CThostFtdcRspGenUserTextField *pRspGenUserText, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;



	///报单录入请求响应
	virtual void OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;
	///预埋单录入请求响应
	virtual void OnRspParkedOrderInsert(CThostFtdcParkedOrderField *pParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;
	///预埋撤单录入请求响应
	virtual void OnRspParkedOrderAction(CThostFtdcParkedOrderActionField *pParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///报单操作请求响应
	virtual void OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///查询最大报单数量响应
	virtual void OnRspQueryMaxOrderVolume(CThostFtdcQryMaxOrderVolumeField *pQueryMaxOrderVolume, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///投资者结算结果确认响应
	virtual void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///删除预埋单响应
	virtual void OnRspRemoveParkedOrder(CThostFtdcRemoveParkedOrderField *pRemoveParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///删除预埋撤单响应
	virtual void OnRspRemoveParkedOrderAction(CThostFtdcRemoveParkedOrderActionField *pRemoveParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///执行宣告录入请求响应
	virtual void OnRspExecOrderInsert(CThostFtdcInputExecOrderField *pInputExecOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///执行宣告操作请求响应
	virtual void OnRspExecOrderAction(CThostFtdcInputExecOrderActionField *pInputExecOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///询价录入请求响应
	virtual void OnRspForQuoteInsert(CThostFtdcInputForQuoteField *pInputForQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///报价录入请求响应
	virtual void OnRspQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///报价操作请求响应
	virtual void OnRspQuoteAction(CThostFtdcInputQuoteActionField *pInputQuoteAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///批量报单操作请求响应
	virtual void OnRspBatchOrderAction(CThostFtdcInputBatchOrderActionField *pInputBatchOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///期权自对冲录入请求响应
	virtual void OnRspOptionSelfCloseInsert(CThostFtdcInputOptionSelfCloseField *pInputOptionSelfClose, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///期权自对冲操作请求响应
	virtual void OnRspOptionSelfCloseAction(CThostFtdcInputOptionSelfCloseActionField *pInputOptionSelfCloseAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///申请组合录入请求响应
	virtual void OnRspCombActionInsert(CThostFtdcInputCombActionField *pInputCombAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///请求查询报单响应
	virtual void OnRspQryOrder(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///请求查询成交响应
	virtual void OnRspQryTrade(CThostFtdcTradeField *pTrade, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///请求查询投资者持仓响应
	virtual void OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///请求查询资金账户响应
	virtual void OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///请求查询投资者响应
	virtual void OnRspQryInvestor(CThostFtdcInvestorField *pInvestor, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///请求查询交易编码响应
	virtual void OnRspQryTradingCode(CThostFtdcTradingCodeField *pTradingCode, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///请求查询合约保证金率响应
	virtual void OnRspQryInstrumentMarginRate(CThostFtdcInstrumentMarginRateField *pInstrumentMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///请求查询合约手续费率响应
	virtual void OnRspQryInstrumentCommissionRate(CThostFtdcInstrumentCommissionRateField *pInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;


	///请求查询交易所响应
	virtual void OnRspQryExchange(CThostFtdcExchangeField *pExchange, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///请求查询产品响应
	virtual void OnRspQryProduct(CThostFtdcProductField *pProduct, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///请求查询合约响应
	virtual void OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;


	///请求查询行情响应
	virtual void OnRspQryDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;


	///请求查询投资者结算结果响应
	virtual void OnRspQrySettlementInfo(CThostFtdcSettlementInfoField *pSettlementInfo, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;
	///请求查询转帐银行响应
	virtual void OnRspQryTransferBank(CThostFtdcTransferBankField *pTransferBank, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///请求查询投资者持仓明细响应
	virtual void OnRspQryInvestorPositionDetail(CThostFtdcInvestorPositionDetailField *pInvestorPositionDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///请求查询客户通知响应
	virtual void OnRspQryNotice(CThostFtdcNoticeField *pNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///请求查询结算信息确认响应
	virtual void OnRspQrySettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///请求查询投资者持仓明细响应
	virtual void OnRspQryInvestorPositionCombineDetail(CThostFtdcInvestorPositionCombineDetailField *pInvestorPositionCombineDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///查询保证金监管系统经纪公司资金账户密钥响应
	virtual void OnRspQryCFMMCTradingAccountKey(CThostFtdcCFMMCTradingAccountKeyField *pCFMMCTradingAccountKey, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///请求查询仓单折抵信息响应
	virtual void OnRspQryEWarrantOffset(CThostFtdcEWarrantOffsetField *pEWarrantOffset, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///请求查询投资者品种/跨品种保证金响应
	virtual void OnRspQryInvestorProductGroupMargin(CThostFtdcInvestorProductGroupMarginField *pInvestorProductGroupMargin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///请求查询交易所保证金率响应
	virtual void OnRspQryExchangeMarginRate(CThostFtdcExchangeMarginRateField *pExchangeMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///请求查询交易所调整保证金率响应
	virtual void OnRspQryExchangeMarginRateAdjust(CThostFtdcExchangeMarginRateAdjustField *pExchangeMarginRateAdjust, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///请求查询汇率响应
	virtual void OnRspQryExchangeRate(CThostFtdcExchangeRateField *pExchangeRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///请求查询二级代理操作员银期权限响应
	virtual void OnRspQrySecAgentACIDMap(CThostFtdcSecAgentACIDMapField *pSecAgentACIDMap, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///请求查询产品报价汇率
	virtual void OnRspQryProductExchRate(CThostFtdcProductExchRateField *pProductExchRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///请求查询产品组
	virtual void OnRspQryProductGroup(CThostFtdcProductGroupField *pProductGroup, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///请求查询做市商合约手续费率响应
	virtual void OnRspQryMMInstrumentCommissionRate(CThostFtdcMMInstrumentCommissionRateField *pMMInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///请求查询做市商期权合约手续费响应
	virtual void OnRspQryMMOptionInstrCommRate(CThostFtdcMMOptionInstrCommRateField *pMMOptionInstrCommRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///请求查询报单手续费响应
	virtual void OnRspQryInstrumentOrderCommRate(CThostFtdcInstrumentOrderCommRateField *pInstrumentOrderCommRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///请求查询资金账户响应
	virtual void OnRspQrySecAgentTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///请求查询二级代理商资金校验模式响应
	virtual void OnRspQrySecAgentCheckMode(CThostFtdcSecAgentCheckModeField *pSecAgentCheckMode, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///请求查询二级代理商信息响应
	virtual void OnRspQrySecAgentTradeInfo(CThostFtdcSecAgentTradeInfoField *pSecAgentTradeInfo, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///请求查询期权交易成本响应
	virtual void OnRspQryOptionInstrTradeCost(CThostFtdcOptionInstrTradeCostField *pOptionInstrTradeCost, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///请求查询期权合约手续费响应
	virtual void OnRspQryOptionInstrCommRate(CThostFtdcOptionInstrCommRateField *pOptionInstrCommRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///请求查询执行宣告响应
	virtual void OnRspQryExecOrder(CThostFtdcExecOrderField *pExecOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///请求查询询价响应
	virtual void OnRspQryForQuote(CThostFtdcForQuoteField *pForQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///请求查询报价响应
	virtual void OnRspQryQuote(CThostFtdcQuoteField *pQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///请求查询期权自对冲响应
	virtual void OnRspQryOptionSelfClose(CThostFtdcOptionSelfCloseField *pOptionSelfClose, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///请求查询投资单元响应
	virtual void OnRspQryInvestUnit(CThostFtdcInvestUnitField *pInvestUnit, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///请求查询组合合约安全系数响应
	virtual void OnRspQryCombInstrumentGuard(CThostFtdcCombInstrumentGuardField *pCombInstrumentGuard, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///请求查询申请组合响应
	virtual void OnRspQryCombAction(CThostFtdcCombActionField *pCombAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///请求查询转帐流水响应
	virtual void OnRspQryTransferSerial(CThostFtdcTransferSerialField *pTransferSerial, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///请求查询银期签约关系响应
	virtual void OnRspQryAccountregister(CThostFtdcAccountregisterField *pAccountregister, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;



	///错误应答
	virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///报单通知
	virtual void OnRtnOrder(CThostFtdcOrderField *pOrder)  ;

	///成交通知
	virtual void OnRtnTrade(CThostFtdcTradeField *pTrade)  ;

	///报单录入错误回报
	virtual void OnErrRtnOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo)  ;

	///报单操作错误回报
	virtual void OnErrRtnOrderAction(CThostFtdcOrderActionField *pOrderAction, CThostFtdcRspInfoField *pRspInfo)  ;

	///合约交易状态通知
	virtual void OnRtnInstrumentStatus(CThostFtdcInstrumentStatusField *pInstrumentStatus)  ;

	///交易所公告通知
	virtual void OnRtnBulletin(CThostFtdcBulletinField* pBulletin) {};

	///交易通知
	virtual void OnRtnTradingNotice(CThostFtdcTradingNoticeInfoField *pTradingNoticeInfo)  ;

	///提示条件单校验错误
	virtual void OnRtnErrorConditionalOrder(CThostFtdcErrorConditionalOrderField *pErrorConditionalOrder)  ;

	///执行宣告通知
	virtual void OnRtnExecOrder(CThostFtdcExecOrderField *pExecOrder)  ;

	///执行宣告录入错误回报
	virtual void OnErrRtnExecOrderInsert(CThostFtdcInputExecOrderField *pInputExecOrder, CThostFtdcRspInfoField *pRspInfo)  ;

	///执行宣告操作错误回报
	virtual void OnErrRtnExecOrderAction(CThostFtdcExecOrderActionField *pExecOrderAction, CThostFtdcRspInfoField *pRspInfo)  ;

	///询价录入错误回报
	virtual void OnErrRtnForQuoteInsert(CThostFtdcInputForQuoteField *pInputForQuote, CThostFtdcRspInfoField *pRspInfo)  ;

	///报价通知
	virtual void OnRtnQuote(CThostFtdcQuoteField *pQuote)  ;

	///报价录入错误回报
	virtual void OnErrRtnQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, CThostFtdcRspInfoField *pRspInfo)  ;

	///报价操作错误回报
	virtual void OnErrRtnQuoteAction(CThostFtdcQuoteActionField *pQuoteAction, CThostFtdcRspInfoField *pRspInfo)  ;

	///询价通知
	virtual void OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp)  ;

	///保证金监控中心用户令牌
	virtual void OnRtnCFMMCTradingAccountToken(CThostFtdcCFMMCTradingAccountTokenField *pCFMMCTradingAccountToken)  ;

	///批量报单操作错误回报
	virtual void OnErrRtnBatchOrderAction(CThostFtdcBatchOrderActionField *pBatchOrderAction, CThostFtdcRspInfoField *pRspInfo)  ;

	///期权自对冲通知
	virtual void OnRtnOptionSelfClose(CThostFtdcOptionSelfCloseField *pOptionSelfClose)  ;

	///期权自对冲录入错误回报
	virtual void OnErrRtnOptionSelfCloseInsert(CThostFtdcInputOptionSelfCloseField *pInputOptionSelfClose, CThostFtdcRspInfoField *pRspInfo)  ;

	///期权自对冲操作错误回报
	virtual void OnErrRtnOptionSelfCloseAction(CThostFtdcOptionSelfCloseActionField *pOptionSelfCloseAction, CThostFtdcRspInfoField *pRspInfo)  ;

	///申请组合通知
	virtual void OnRtnCombAction(CThostFtdcCombActionField *pCombAction)  ;

	///申请组合录入错误回报
	virtual void OnErrRtnCombActionInsert(CThostFtdcInputCombActionField *pInputCombAction, CThostFtdcRspInfoField *pRspInfo)  ;

	///请求查询签约银行响应
	virtual void OnRspQryContractBank(CThostFtdcContractBankField *pContractBank, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///请求查询预埋单响应
	virtual void OnRspQryParkedOrder(CThostFtdcParkedOrderField *pParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///请求查询预埋撤单响应
	virtual void OnRspQryParkedOrderAction(CThostFtdcParkedOrderActionField *pParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///请求查询交易通知响应
	virtual void OnRspQryTradingNotice(CThostFtdcTradingNoticeField *pTradingNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///请求查询经纪公司交易参数响应
	virtual void OnRspQryBrokerTradingParams(CThostFtdcBrokerTradingParamsField *pBrokerTradingParams, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///请求查询经纪公司交易算法响应
	virtual void OnRspQryBrokerTradingAlgos(CThostFtdcBrokerTradingAlgosField *pBrokerTradingAlgos, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///请求查询监控中心用户令牌
	virtual void OnRspQueryCFMMCTradingAccountToken(CThostFtdcQueryCFMMCTradingAccountTokenField *pQueryCFMMCTradingAccountToken, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///银行发起银行资金转期货通知
	virtual void OnRtnFromBankToFutureByBank(CThostFtdcRspTransferField *pRspTransfer)  ;

	///银行发起期货资金转银行通知
	virtual void OnRtnFromFutureToBankByBank(CThostFtdcRspTransferField *pRspTransfer)  ;

	///银行发起冲正银行转期货通知
	virtual void OnRtnRepealFromBankToFutureByBank(CThostFtdcRspRepealField *pRspRepeal)  ;

	///银行发起冲正期货转银行通知
	virtual void OnRtnRepealFromFutureToBankByBank(CThostFtdcRspRepealField *pRspRepeal)  ;

	///期货发起银行资金转期货通知
	virtual void OnRtnFromBankToFutureByFuture(CThostFtdcRspTransferField *pRspTransfer)  ;

	///期货发起期货资金转银行通知
	virtual void OnRtnFromFutureToBankByFuture(CThostFtdcRspTransferField *pRspTransfer)  ;

	///系统运行时期货端手工发起冲正银行转期货请求，银行处理完毕后报盘发回的通知
	virtual void OnRtnRepealFromBankToFutureByFutureManual(CThostFtdcRspRepealField *pRspRepeal)  ;

	///系统运行时期货端手工发起冲正期货转银行请求，银行处理完毕后报盘发回的通知
	virtual void OnRtnRepealFromFutureToBankByFutureManual(CThostFtdcRspRepealField *pRspRepeal)  ;

	///期货发起查询银行余额通知
	virtual void OnRtnQueryBankBalanceByFuture(CThostFtdcNotifyQueryAccountField *pNotifyQueryAccount)  ;

	///期货发起银行资金转期货错误回报
	virtual void OnErrRtnBankToFutureByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo)  ;

	///期货发起期货资金转银行错误回报
	virtual void OnErrRtnFutureToBankByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo)  ;

	///系统运行时期货端手工发起冲正银行转期货错误回报
	virtual void OnErrRtnRepealBankToFutureByFutureManual(CThostFtdcReqRepealField *pReqRepeal, CThostFtdcRspInfoField *pRspInfo)  ;

	///系统运行时期货端手工发起冲正期货转银行错误回报
	virtual void OnErrRtnRepealFutureToBankByFutureManual(CThostFtdcReqRepealField *pReqRepeal, CThostFtdcRspInfoField *pRspInfo)  ;

	///期货发起查询银行余额错误回报
	virtual void OnErrRtnQueryBankBalanceByFuture(CThostFtdcReqQueryAccountField *pReqQueryAccount, CThostFtdcRspInfoField *pRspInfo)  ;

	///期货发起冲正银行转期货请求，银行处理完毕后报盘发回的通知
	virtual void OnRtnRepealFromBankToFutureByFuture(CThostFtdcRspRepealField *pRspRepeal)  ;

	///期货发起冲正期货转银行请求，银行处理完毕后报盘发回的通知
	virtual void OnRtnRepealFromFutureToBankByFuture(CThostFtdcRspRepealField *pRspRepeal)  ;

	///期货发起银行资金转期货应答
	virtual void OnRspFromBankToFutureByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///期货发起期货资金转银行应答
	virtual void OnRspFromFutureToBankByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///期货发起查询银行余额应答
	virtual void OnRspQueryBankAccountMoneyByFuture(CThostFtdcReqQueryAccountField *pReqQueryAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)  ;

	///银行发起银期开户通知
	virtual void OnRtnOpenAccountByBank(CThostFtdcOpenAccountField *pOpenAccount)  ;

	///银行发起银期销户通知
	virtual void OnRtnCancelAccountByBank(CThostFtdcCancelAccountField *pCancelAccount)  ;

	///银行发起变更银行账号通知
	virtual void OnRtnChangeAccountByBank(CThostFtdcChangeAccountField *pChangeAccount)  ;
#pragma endregion


private:
	CThostFtdcRspInfoField* repareInfo(CThostFtdcRspInfoField *pRspInfo);
};

