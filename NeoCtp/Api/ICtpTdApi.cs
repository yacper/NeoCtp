﻿/********************************************************************
    created:	2020-11-11 22:40:38
    author:		rush
    email:		
	
    purpose:	https://blog.51cto.com/quantfabric/2966425
                https://www.cnblogs.com/dengchj/p/8442913.html

数据处理：
                https://zhuanlan.zhihu.com/p/123384992
                https://zhuanlan.zhihu.com/p/126775219
                https://zhuanlan.zhihu.com/p/380143402

*********************************************************************/
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using NeoCtp.Api;
using NeoCtp.Enums;

namespace NeoCtp
{
	public interface ICtpTdApi
	{
        string              FrontAddress { get; }

        string              BrokerId { get; }
        string              UserId { get; }
        string              Password { get; }


        int                 FrontId { get; }                                /// 前置编号
        int                 SessionId { get; }                              /// 会话编号
        int                 MaxOrderRef { get;  }                           // 最大报单引用

        /// 最大报单引用

        DateTime			LoginTime { get; }

		// update every second
        TimeSpan			LoginDuration { get; }
        DateTime			SHFETime { get; }
        DateTime			DCETime { get; }
        DateTime			CZCETime { get; }
        DateTime			FFEXTime { get; }
        DateTime			INETime { get; }


		int					TimeoutMilliseconds { get; set; }

        event EventHandler<CtpRsp> OnRspErrorEvent;
        event EventHandler<int> OnHeartBeatWarningEvent; // ///当长时间未收到报文时，该方法被调用。///@param nTimeLapse 距离上次接收报文的时间

        EConnectionState ConnectionState { get; }
		Task<bool>          ConnectAsync(string frontAddress = null);
		Task				DisconnectAsync();
        event EventHandler<EFrontDisconnectedReason> OnFrontDisconnectedEvent;


		bool                                      IsLogined { get; }
        Task<CtpRsp<CThostFtdcRspUserLoginField>> ReqUserLoginAsync(string brokerId = null, string userId = null, string password = null);
        Task<CtpRsp<CThostFtdcUserLogoutField>>   ReqUserLogoutAsync();


        Task<CtpRsp<CThostFtdcRspAuthenticateField>> ReqAuthenticateAsync(string appId = null, string authCode = null);        // 认证

#region Accont

		///投资者结算结果确认
		Task<CtpRsp<CThostFtdcSettlementInfoConfirmField>> ReqSettlementInfoConfirmAsync();


		///请求查询资金账户
		Task<CtpRsp<CThostFtdcTradingAccountField>> ReqQryTradingAccountAsync();
#endregion

#region Instrument

		Task<CtpRsp<CThostFtdcInstrumentField>> ReqQryInstrumentAsync(string instrumentID);
        

#endregion

#region Position

         ///请求查询投资者持仓 不填参数可以查询所有position
         // 持仓的查询与更新 https://zhuanlan.zhihu.com/p/334757236 https://zhuanlan.zhihu.com/p/348396367
        Task<CtpRsp<List<CThostFtdcInvestorPositionField>>> ReqQryInvestorPositionAsync(CThostFtdcQryInvestorPositionField? field = null);

        Task<CtpRsp<List<CThostFtdcInvestorPositionDetailField>>> ReqQryInvestorPositionDetailAsync(CThostFtdcQryInvestorPositionDetailField? field = null);
       

#endregion

#region Order

		Task<CtpRsp<List<CThostFtdcOrderField>>> ReqQryOrderAsync(CThostFtdcQryOrderField? pQryOrder = null); // 不填返回所有, 包括已成单子
		Task<CtpRsp<List<CThostFtdcTradeField>>> ReqQryTradeAsync(CThostFtdcQryTradeField? pQryTrade = null); // 不填返回所有

 
		///报单录入请求
        // 交易所校验通过后返回， 忽略掉本地校验后的rtn
		Task<CtpRsp<CThostFtdcOrderField?>>	ReqOrderInsertAsync(CThostFtdcInputOrderField pInputOrder);  

        event EventHandler<CThostFtdcOrderField> OnRtnOrderEvent;		// order 状态通知
        event EventHandler<CThostFtdcTradeField> OnRtnTradeEvent;	    // trade 交易明细通知

        event EventHandler<Tuple<CThostFtdcInputOrderField, CThostFtdcRspInfoField>>  OnErrRtnOrderInsertEvent; // 报单插入错误回报
        event EventHandler<Tuple<CThostFtdcOrderActionField, CThostFtdcRspInfoField>> OnErrRtnOrderActionEvent; //报单操作错误回报


        // 撤单 不支持改单
        Task<CtpRsp<CThostFtdcOrderField?>> ReqOrderActionAsync(CThostFtdcInputOrderActionField pInputOrderAction);
#endregion



		///预埋单录入请求
		int					ReqParkedOrderInsert(ref CThostFtdcParkedOrderField pParkedOrder, int nRequestID);

		///预埋撤单录入请求
		int					ReqParkedOrderAction(ref CThostFtdcParkedOrderActionField pParkedOrderAction, int nRequestID);


		///查询最大报单数量请求
		int					ReqQueryMaxOrderVolume(ref CThostFtdcQryMaxOrderVolumeField pQueryMaxOrderVolume, int nRequestID);


	}
}
