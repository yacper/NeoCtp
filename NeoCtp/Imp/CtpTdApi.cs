using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Timers;
using NeoCtp.Api;
using NeoCtp.Enums;
using NeoCtp.Exceptions;
using NLog;
using Timer = System.Timers.Timer;

namespace NeoCtp.Imp
{
public class CtpTdApi : CtpTdApiBase, ICtpTdApi, ICtpTdSpi
{
#region ICtpTdSpi

    public void OnFrontConnected()
    {
        OnFrontConnectedEvent?.Invoke(this, null);
        //         IsConnected = true;
        //((Action<bool>)_GetCallback(-1))?.Invoke(true);
    }

    private event EventHandler OnFrontConnectedEvent;

    public void OnFrontDisconnected(int nReason)
    {
        ConnectionState = EConnectionState.Disconnected;

        OnFrontDisconnectedEvent?.Invoke(this, (EFrontDisconnectedReason)nReason);
    }

    public event EventHandler<CtpRsp> OnRspErrorEvent;

    ///错误应答
    public void OnRspError(ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast) { OnRspErrorEvent?.Invoke(this, new CtpRsp(pRspInfo, nRequestID, bIsLast)); }

    public event EventHandler<int> OnHeartBeatWarningEvent;
    public void                    OnHeartBeatWarning(int nTimeLapse) { OnHeartBeatWarningEvent?.Invoke(this, nTimeLapse); }


    public event EventHandler<CtpRsp<CThostFtdcRspUserLoginField>> OnRspUserLoginEvent;

    public void OnRspUserLogin(ref CThostFtdcRspUserLoginField pRspUserLogin, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
    {
        OnRspUserLoginEvent?.Invoke(this, new(pRspUserLogin, pRspInfo, nRequestID, bIsLast));
    }

    public event EventHandler<CtpRsp<CThostFtdcUserLogoutField>> OnRspUserLogoutEvent;

    public void OnRspUserLogout(ref CThostFtdcUserLogoutField pUserLogout, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
    {
        OnRspUserLogoutEvent?.Invoke(this, new(pUserLogout, pRspInfo, nRequestID, bIsLast));
    }


    public void OnRspAuthenticate(ref CThostFtdcRspAuthenticateField pRspAuthenticateField, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast) { }


    public void OnRspUserPasswordUpdate(ref           CThostFtdcUserPasswordUpdateField           pUserPasswordUpdate,           ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast) { }
    public void OnRspTradingAccountPasswordUpdate(ref CThostFtdcTradingAccountPasswordUpdateField pTradingAccountPasswordUpdate, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast) { }

    public void OnRspUserAuthMethod(ref CThostFtdcRspUserAuthMethodField pRspUserAuthMethod, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast) { }

    public void OnRspGenUserCaptcha(ref CThostFtdcRspGenUserCaptchaField pRspGenUserCaptcha, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast) { }
    public void OnRspGenUserText(ref    CThostFtdcRspGenUserTextField    pRspGenUserText,    ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast) { }


    ///投资者结算结果确认响应
    public void OnRspSettlementInfoConfirm(ref CThostFtdcSettlementInfoConfirmField pSettlementInfoConfirm,
        ref                                    CThostFtdcRspInfoField               pRspInfo, int nRequestID, bool bIsLast)
    {
        //CtpRsp<CThostFtdcSettlementInfoConfirmField> rsp = new CtpRsp<CThostFtdcSettlementInfoConfirmField>
        //{
        //	Rsp = pRspInfo,
        //	Rsp2 = pSettlementInfoConfirm
        //};

        //         _ExecuteCallback(nRequestID, rsp);
    }


    ///报单录入请求响应
    public void OnRspOrderInsert(ref CThostFtdcInputOrderField pInputOrder, ref CThostFtdcRspInfoField pRspInfo,
        int                                                    nRequestID,  bool                       bIsLast)
    {
        //CtpRsp<CThostFtdcInputOrderField> rsp = new CtpRsp<CThostFtdcInputOrderField>
        //{
        //	Rsp = pRspInfo,
        //	Rsp2 =pInputOrder 
        //};

        //         _ExecuteCallback(nRequestID, rsp);
    }

    ///预埋单录入请求响应
    public void OnRspParkedOrderInsert(ref CThostFtdcParkedOrderField pParkedOrder, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast) { }

    ///预埋撤单录入请求响应
    public void OnRspParkedOrderAction(ref CThostFtdcParkedOrderActionField pParkedOrderAction, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast) { }

    ///报单操作请求响应
    public void OnRspOrderAction(ref CThostFtdcInputOrderActionField pInputOrderAction, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast) { }

    ///查询最大报单数量响应
    public void OnRspQueryMaxOrderVolume(ref CThostFtdcQueryMaxOrderVolumeField pQueryMaxOrderVolume, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast) { }


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
    public void OnRspQryInvestorPosition(ref CThostFtdcInvestorPositionField pInvestorPosition,
        ref                                  CThostFtdcRspInfoField          pRspInfo, int nRequestID, bool bIsLast)
    {
        //CtpRsp<List<CThostFtdcInvestorPositionField>> rsp = null;

        //if (!bIsLast)
        //{
        //	object o;
        //	if (_dataDict.TryGetValue(nRequestID, out o))
        //	{
        //		rsp = (CtpRsp<List<CThostFtdcInvestorPositionField>>)o;
        //	}
        //	else
        //	{
        //		rsp = new CtpRsp<List<CThostFtdcInvestorPositionField>>
        //		{
        //			Rsp = pRspInfo,
        //			Rsp2 = new List<CThostFtdcInvestorPositionField>() { pInvestorPosition },
        //		};

        //		_dataDict.TryAdd(nRequestID, rsp);
        //	}

        //	rsp.Rsp2.Add(pInvestorPosition);
        //}
        //else
        //{

        //	object o;
        //	if (_dataDict.TryRemove(nRequestID, out o))
        //	{
        //		rsp = (CtpRsp<List<CThostFtdcInvestorPositionField>>)o;
        //	}
        //	else
        //	{
        //		rsp = new CtpRsp<List<CThostFtdcInvestorPositionField>>
        //		{
        //			Rsp = pRspInfo,
        //			Rsp2 = new List<CThostFtdcInvestorPositionField>() { pInvestorPosition },
        //		};

        //	}

        //	_ExecuteCallback(nRequestID, rsp);
        //}
    }

    ///请求查询资金账户响应
    public void OnRspQryTradingAccount(ref CThostFtdcTradingAccountField pTradingAccount,
        ref                                CThostFtdcRspInfoField        pRspInfo, int nRequestID, bool bIsLast)
    {
        //CtpRsp<CThostFtdcTradingAccountField> rsp = new CtpRsp<CThostFtdcTradingAccountField>
        //{
        //	Rsp = pRspInfo,
        //	Rsp2 =pTradingAccount 
        //};

        //         _ExecuteCallback(nRequestID, rsp);
    }

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
    public void OnRspQryInstrument(ref CThostFtdcInstrumentField pInstrument, ref CThostFtdcRspInfoField pRspInfo,
        int                                                      nRequestID,  bool                       bIsLast)
    {
        //CtpRsp<CThostFtdcInstrumentField> rsp = new CtpRsp<CThostFtdcInstrumentField>
        //{
        //	Rsp = pRspInfo,
        //	Rsp2 =pInstrument 
        //};

        //         _ExecuteCallback(nRequestID, rsp);
    }


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
    public void OnRspQryInvestorPositionCombineDetail(ref CThostFtdcInvestorPositionCombineDetailField pInvestorPositionCombineDetail, ref CThostFtdcRspInfoField pRspInfo, int nRequestID,
        bool                                                                                           bIsLast)
    {
    }

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
    public void OnRspQueryCFMMCTradingAccountToken(ref CThostFtdcQueryCFMMCTradingAccountTokenField pQueryCFMMCTradingAccountToken, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
    {
    }

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

#endregion

    public ILogger Logger { get; protected set; }


    public CtpTdApi(string frontAddress, string brokerId, string userId, string password, ILogger logger = null, string pszFlowPath = "CtpTdFlow/")
        : base(frontAddress, brokerId, userId, password, pszFlowPath)
    {
        Logger = logger;
    }

    public    EConnectionState ConnectionState { get => ConnectionState_; set => SetProperty(ref ConnectionState_, value); }
    protected EConnectionState ConnectionState_;


    //public bool          IsConnected
    //      {
    //       get { return _IsConnected; }

    //	protected set { SetProperty(ref _IsConnected, value); }

    //      }


    public bool IsLogined { get { return _IsLogined; } protected set { SetProperty(ref _IsLogined, value); } }


    public int TimeoutMilliseconds { get; set; }


    public Task<bool> ConnectAsync()
    {
        if (ConnectionState == EConnectionState.Connected)
            return Task.FromResult(true);

        ConnectionState = EConnectionState.Connecting;

        ApiHandle_ = TdApiCalls.CreateFtdcTraderApi(FlowPath);
        SpiHandle_ = TdApiCalls.CreateTdSpi();
        TdApiCalls.RegisterSpi(ApiHandle_, SpiHandle_);
        BindEvents_();
        RegisterSpi(this);
        SubscribePublicTopic(THOST_TE_RESUME_TYPE.THOST_TERT_RESTART);
        SubscribePrivateTopic(THOST_TE_RESUME_TYPE.THOST_TERT_RESTART);
        RegisterFront(FrontAddress);


        var taskSource = new TaskCompletionSource<bool>();

        EventHandler onFrontConnectedHandler = null;
        onFrontConnectedHandler = (s, e) =>
        {
            lock (Lock_)
            {
                if (ConnectionState == EConnectionState.Disconnected)
                    return;

                OnFrontConnectedEvent -= onFrontConnectedHandler;
                OnConnected_();
                taskSource.TrySetResult(true);
            }
        };

        CancellationTokenSource tokenSource = new CancellationTokenSource(TimeoutMilliseconds);
        tokenSource.Token.Register(() =>
        {
            lock (Lock_)
            {
                /// 超时失败
                OnFrontConnectedEvent -= onFrontConnectedHandler;

                if (ConnectionState == EConnectionState.Connecting)
                {
                    //todo: 待验证
                    Release();
                    ConnectionState = EConnectionState.Disconnected;
                }

                taskSource.TrySetCanceled();
            }
        });

        this.OnFrontConnectedEvent += onFrontConnectedHandler;

        Init();
        return taskSource.Task;
    }

    public Task DisconnectAsync()
    {
        if (ConnectionState != EConnectionState.Connected)
            return Task.CompletedTask;

        ConnectionState = EConnectionState.Disconnecting;

        Release();

        OnDisconnected_();

        return Task.CompletedTask;

    }

    protected void OnConnected_()
    {
        Logger?.Info($"Connected:{this.Dump()}");

        ConnectionState = EConnectionState.Connected;
    }

    protected void OnDisconnected_()
    {
        Logger?.Info($"DisConnected:{this.Dump()}");

        //RealtimeBarsSubscriptions_.Clear();
        //RealtimeBarsSubscriptionReqs_.Clear();
        //TickByTickSubscriptionReqs_.Clear();
        //TickByTickSubscriptions_.Clear();
        //ReqContracts.Clear();

        IsLogined = false;

        ApiHandle_ = IntPtr.Zero;
        SpiHandle_ = IntPtr.Zero;
        TdSpi_     = null;

        ConnectionState = EConnectionState.Disconnected;
    }


    public event EventHandler<EFrontDisconnectedReason> OnFrontDisconnectedEvent;


    public Task<CtpRsp<CThostFtdcRspUserLoginField>> ReqUserLoginAsync()
    {
        var taskSource = new TaskCompletionSource<CtpRsp<CThostFtdcRspUserLoginField>>();
        var reqId      = GetNextRequestId();


        EventHandler<CtpRsp<CThostFtdcRspUserLoginField>> onRspUserLoginHandler = null;
        EventHandler<CtpRsp>                              onRspErrorHandler     = null;
        onRspUserLoginHandler = (s, e) =>
        {
            clearHandler();

            taskSource.TrySetResult(e);
        };
        onRspErrorHandler = (s, e) =>
        {
            if (e.RequestId == reqId)
            {
                clearHandler();

                taskSource.TrySetException(new CtpException(e));
            }
        };

        void clearHandler()
        {
            OnRspUserLoginEvent -= onRspUserLoginHandler;
            OnRspErrorEvent     -= onRspErrorHandler;
        }


        CThostFtdcReqUserLoginField field = new CThostFtdcReqUserLoginField()
        {
            BrokerID = BrokerId,
            UserID   = UserId,
            Password = Password
        };

        ECtpRtn ret = (ECtpRtn)ReqUserLogin(ref field, reqId);
        if (ret != ECtpRtn.Sucess) { taskSource.TrySetResult(new(ret)); }
        else
        {
            OnRspUserLoginEvent += onRspUserLoginHandler;
            OnRspErrorEvent     += onRspErrorHandler;

            CancellationTokenSource tokenSource = new CancellationTokenSource(TimeoutMilliseconds);
            tokenSource.Token.Register(() =>
            {
                clearHandler();
                taskSource.TrySetCanceled();
            });
        }

        return taskSource.Task;
    }

    public Task<CtpRsp<CThostFtdcUserLogoutField>> ReqUserLogoutAsync()
    {
        var taskSource = new TaskCompletionSource<CtpRsp<CThostFtdcUserLogoutField>>();
        var reqId      = GetNextRequestId();

        EventHandler<CtpRsp<CThostFtdcUserLogoutField>> onRspUserLogoutHandler = null;
        EventHandler<CtpRsp>                            onRspErrorHandler      = null;
        onRspUserLogoutHandler = (s, e) =>
        {
            clearHandler();

            taskSource.TrySetResult(e);
        };
        onRspErrorHandler = (s, e) =>
        {
            if (e.RequestId == reqId)
            {
                clearHandler();

                taskSource.TrySetException(new CtpException(e));
            }
        };

        void clearHandler()
        {
            OnRspUserLogoutEvent -= onRspUserLogoutHandler;
            OnRspErrorEvent      -= onRspErrorHandler;
        }

        CThostFtdcUserLogoutField field = new CThostFtdcUserLogoutField()
        {
            BrokerID = BrokerId,
            UserID   = UserId
        };

        ECtpRtn ret = (ECtpRtn)ReqUserLogout(ref field, reqId);
        if (ret != ECtpRtn.Sucess) { taskSource.TrySetResult(new(ret)); }
        else
        {
            OnRspUserLogoutEvent += onRspUserLogoutHandler;
            OnRspErrorEvent      += onRspErrorHandler;

            CancellationTokenSource tokenSource = new CancellationTokenSource(TimeoutMilliseconds);
            tokenSource.Token.Register(() =>
            {
                clearHandler();
                taskSource.TrySetCanceled();
            });
        }

        return taskSource.Task;
    }


    ///投资者结算结果确认
    public void ReqSettlementInfoConfirm(Action<CtpRsp<CThostFtdcSettlementInfoConfirmField>> callback)
    {
        int requestID = _AddCallback(callback);
        _AddMethod(requestID, new Action(() =>
        {
            CThostFtdcSettlementInfoConfirmField filed = new CThostFtdcSettlementInfoConfirmField()
            {
                BrokerID   = BrokerId,
                InvestorID = UserId
            };

            int ret = ReqSettlementInfoConfirm(ref filed, requestID);
            _RemoveMethod(requestID, ret);
        }));
    }


    public void ReqQryTradingAccount(Action<CtpRsp<CThostFtdcTradingAccountField>> callback)
    {
        int requestID = _AddCallback(callback);
        _AddMethod(requestID, new Action(() =>
        {
            CThostFtdcQryTradingAccountField filed = new CThostFtdcQryTradingAccountField()
            {
                BrokerID   = BrokerId,
                InvestorID = UserId
            };

            int ret = ReqQryTradingAccount(ref filed, requestID);
            _RemoveMethod(requestID, ret);
        }));
    }


    ///请求查询投资者持仓
    public void ReqQryInvestorPosition(string instrumentID, Action<CtpRsp<List<CThostFtdcInstrumentField>>> callback)
    {
        int requestID = _AddCallback(callback);
        _AddMethod(requestID, new Action(() =>
        {
            CThostFtdcQryInvestorPositionField filed = new CThostFtdcQryInvestorPositionField()
            {
                BrokerID     = BrokerId,
                InvestorID   = UserId,
                InstrumentID = instrumentID
            };

            int ret = ReqQryInvestorPosition(ref filed, requestID);
            _RemoveMethod(requestID, ret);
        }));
    }

    public void ReqQryInstrument(string instrumentID, Action<CtpRsp<CThostFtdcInstrumentField>> callback)
    {
        int requestID = _AddCallback(callback);
        _AddMethod(requestID, new Action(() =>
        {
            CThostFtdcQryInstrumentField filed = new CThostFtdcQryInstrumentField()
            {
                InstrumentID = instrumentID
            };

            int ret = ReqQryInstrument(ref filed, requestID);
            _RemoveMethod(requestID, ret);
        }));
    }


    public void ReqOrderInsert(CThostFtdcInputOrderField pInputOrder, Action<CThostFtdcInputOrderField> callback)
    {
        pInputOrder.BrokerID   = BrokerId;
        pInputOrder.InvestorID = UserId;
        pInputOrder.UserID     = UserId;
        pInputOrder.OrderRef   = MaxOrderRef;


        int requestID = _AddCallback(callback);
        _AddMethod(requestID, new Action(() =>
        {
            int ret = ReqOrderInsert(ref pInputOrder, requestID);
            _RemoveMethod(requestID, ret);
        }));
    }

    /// <param name="offsetFlag">平仓:仅上期所平今时使用CloseToday/其它情况均使用Close</param>
    public void ReqLimitOrderInsert(Action<CThostFtdcInputOrderField> callback, string instrumentID, TThostFtdcOffsetFlagType offsetFlag, TThostFtdcDirectionType dir,
        int                                                           volume,   double price,        double?                  stopPrice = null,
        TThostFtdcTimeConditionType                                   tic = TThostFtdcTimeConditionType.GFD)
    {
        CThostFtdcInputOrderField field = new CThostFtdcInputOrderField()
        {
            InstrumentID   = instrumentID,
            CombOffsetFlag = offsetFlag,

            LimitPrice          = price,
            VolumeTotalOriginal = volume,
            Direction           = dir,
            TimeCondition       = tic,


            OrderPriceType      = TThostFtdcOrderPriceTypeType.LimitPrice,       // 默认限价
            VolumeCondition     = TThostFtdcVolumeConditionType.AV,              // 任何数量
            MinVolume           = 1,                                             // 最小成交量1
            ContingentCondition = TThostFtdcContingentConditionType.Immediately, // 触发条件：立即
            ForceCloseReason    = TThostFtdcForceCloseReasonType.NotForceClose,  // 强平原因：非强平
            IsAutoSuspend       = 0,                                             // 自动挂起标志：否
            UserForceClose      = 0,                                             // 用户强平标志：否

            CombHedgeFlag = TThostFtdcHedgeFlagType.Speculation
        };

        if (stopPrice != null)
            field.StopPrice = stopPrice.Value;


        ReqOrderInsert(field, callback);
    }


    public void ReqMarketOrderInsert(Action<CThostFtdcInputOrderField> callback,   string                  instrumentID,
        TThostFtdcOffsetFlagType                                       offsetFlag, TThostFtdcDirectionType dir, int volume)
    {
        CThostFtdcInputOrderField field = new CThostFtdcInputOrderField()
        {
            InstrumentID   = instrumentID,
            CombOffsetFlag = offsetFlag,

            VolumeTotalOriginal = volume,
            Direction           = dir,
            TimeCondition       = TThostFtdcTimeConditionType.IOC, //立即完成,否则撤单


            OrderPriceType      = TThostFtdcOrderPriceTypeType.AnyPrice,         // 任意价格
            VolumeCondition     = TThostFtdcVolumeConditionType.AV,              // 任何数量
            MinVolume           = 1,                                             // 最小成交量1
            ContingentCondition = TThostFtdcContingentConditionType.Immediately, // 触发条件：立即
            ForceCloseReason    = TThostFtdcForceCloseReasonType.NotForceClose,  // 强平原因：非强平
            IsAutoSuspend       = 0,                                             // 自动挂起标志：否
            UserForceClose      = 0,                                             // 用户强平标志：否

            CombHedgeFlag = TThostFtdcHedgeFlagType.Speculation
        };


        ReqOrderInsert(field, callback);
    }

    public void ReqConditionOrderInsert(Action<CThostFtdcInputOrderField> callback,      string                  instrumentID,
        TThostFtdcContingentConditionType                                 conditionType, double                  conditionPrice,
        TThostFtdcOffsetFlagType                                          offsetFlag,    TThostFtdcDirectionType dir,   int                         volume,
        TThostFtdcOrderPriceTypeType                                      priceType,     double                  price, TThostFtdcTimeConditionType tic = TThostFtdcTimeConditionType.GFD
    )
    {
        CThostFtdcInputOrderField field = new CThostFtdcInputOrderField()
        {
            InstrumentID   = instrumentID,
            CombOffsetFlag = offsetFlag,

            VolumeTotalOriginal = volume,
            Direction           = dir,
            TimeCondition       = tic, //立即完成,否则撤单

            LimitPrice = price,
            StopPrice  = conditionPrice,


            OrderPriceType      = priceType,                                    // 任意价格
            VolumeCondition     = TThostFtdcVolumeConditionType.AV,             // 任何数量
            MinVolume           = 1,                                            // 最小成交量1
            ContingentCondition = conditionType,                                // 触发条件：立即
            ForceCloseReason    = TThostFtdcForceCloseReasonType.NotForceClose, // 强平原因：非强平
            IsAutoSuspend       = 0,                                            // 自动挂起标志：否
            UserForceClose      = 0,                                            // 用户强平标志：否

            CombHedgeFlag = TThostFtdcHedgeFlagType.Speculation
        };


        ReqOrderInsert(field, callback);
    }

    protected int _GenReqId() { return Interlocked.Increment(ref _RequestID); }

#region 回调方法

    /// <summary>
    /// 添加回调方法
    /// </summary>
    /// <param name="callback">回调函数</param>
    /// <param name="requestID">请求编号</param>
    private int _AddCallback(object callback, int requestID = 0)
    {
        if (requestID == 0) { requestID = _GenReqId(); }

        if (callback != null)
        {
            if (_dataCallbackDict.ContainsKey(requestID))
            {
                object tmp;
                _dataCallbackDict.TryRemove(requestID, out tmp);
            }

            _dataCallbackDict.TryAdd(requestID, callback);
        }

        return requestID;
    }

    private object _GetCallback(int requestID)
    {
        object callback;
        _dataCallbackDict.TryRemove(requestID, out callback);

        return callback;
    }

    private T _GetCallback<T>(int requestID)
    {
        object callback;
        _dataCallbackDict.TryRemove(requestID, out callback);

        return (T)callback;
    }

    private void _ExecuteCallback(int requestID, CtpRsp rsp)
    {
        if (_dataCallbackDict.ContainsKey(requestID))
        {
            object callback;
            if (_dataCallbackDict.TryRemove(requestID, out callback))
            {
                if (callback != null)
                {
                    //todo: dynamic invoke速度比较慢，以后有时间优化
                    (callback as Delegate).DynamicInvoke(rsp);
                    //((DataCallback)callback)(dataResult){ }
                }
            }
        }
    }

#endregion

    /// <summary>
    /// 添加查询委托方法
    /// </summary>
    /// <param name="requestID"></param>
    /// <param name="action"></param>
    private void _AddMethod(int requestID, Action action)
    {
        if ((DateTime.Now - _QueryTime).TotalSeconds > 1)
        {
            action.Invoke();
            _QueryTime = DateTime.Now;
        }
        else
        {
            lock (this)
            {
                _QueryMethodDict.Add(requestID, action);
                if (!_timer.Enabled) { _timer.Start(); }
            }
        }
    }

    /// <summary>
    /// 执行委托方法
    /// </summary>
    /// <param name="sender"></param>
    /// <param name="e"></param>
    private void _ExecuteMethod(object sender, ElapsedEventArgs e)
    {
        if (_QueryMethodDict.Count > 0)
        {
            var action = _QueryMethodDict.Values.FirstOrDefault();
            action.Invoke();
            _QueryTime = DateTime.Now;
        }
    }

    /// <summary>
    /// 移除委托方法
    /// </summary>
    /// <param name="requestID"></param>
    /// <param name="ret"></param>
    private void _RemoveMethod(int requestID, int ret)
    {
        if (ret != 0)
        {
            //object callback;
            //if (_dataCallbackDict.TryGetValue(requestID, out callback))
            //	(callback as CtpRsp).Rtn = (ECtpRtn)ret;
            _ExecuteCallback(requestID, new CtpRsp((ECtpRtn)ret));
        }


        lock (this)
        {
            if (ret == 0) { _executeFailCount = 0; }
            else { _executeFailCount++; }

            if (ret == 0 || _executeFailCount > 1)
            {
                _QueryMethodDict.Remove(requestID);
                if (_QueryMethodDict.Count == 0)
                {
                    if (_timer != null && _timer.Enabled) { _timer.Stop(); }
                }
            }
        }
    }


    //public CtpTdApi()
    //{

    //    _timer = new Timer();
    //    _timer.Interval = 1000;			// 间隔1s
    //    _timer.Elapsed += _ExecuteMethod;

    //}


    protected int GetNextRequestId() => Interlocked.Increment(ref _RequestID);

#region Members

    /// <summary>
    /// 查询方法字典
    /// </summary>
    private Dictionary<int, Action> _QueryMethodDict = new Dictionary<int, Action>();

    private ConcurrentDictionary<int, object> _dataCallbackDict = new ConcurrentDictionary<int, object>();

    private ConcurrentDictionary<int, object> _dataDict = new ConcurrentDictionary<int, object>(); // 数据字典

    protected ConcurrentDictionary<string, object> _Subscribed = new ConcurrentDictionary<string, object>();

    protected bool     _IsConnected;
    protected bool     _IsLogined;
    protected DateTime _LoginTime;


    protected int _RequestID = 0;


    private DateTime _QueryTime = DateTime.MinValue;

    /// <summary>
    /// 执行失败次数
    /// </summary>
    private int _executeFailCount;

    /// <summary>
    /// 查询时间限制定时器
    /// </summary>
    private Timer _timer;

    protected object Lock_ = new object();

#endregion
}
}