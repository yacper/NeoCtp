/********************************************************************
    created:	2020-11-11 22:40:38
    author:		rush
    email:		
	
    purpose:	https://blog.51cto.com/quantfabric/2966425
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
        //string              MaxOrderRef { get;  }

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
        event EventHandler<int> OnHeartBeatWarningEvent;

         EConnectionState ConnectionState { get; }
        //bool             IsConnected     { get; }
		Task<bool>          ConnectAsync();
		Task				DisconnectAsync();
        event EventHandler<EFrontDisconnectedReason> OnFrontDisconnectedEvent;


		bool                                      IsLogined { get; }
        Task<CtpRsp<CThostFtdcRspUserLoginField>> ReqUserLoginAsync();
        Task<CtpRsp<CThostFtdcUserLogoutField>>   ReqUserLogoutAsync();


		///投资者结算结果确认
		Task<CtpRsp<CThostFtdcSettlementInfoConfirmField>> ReqSettlementInfoConfirmAsync();


		///请求查询资金账户
		Task<CtpRsp<CThostFtdcTradingAccountField>> ReqQryTradingAccountAsync();


#region Instrument

		Task<CtpRsp<CThostFtdcInstrumentField>> ReqQryInstrumentAsync(string instrumentID);
        

#endregion

#region Position

         ///请求查询投资者持仓 不填参数可以查询所有position
        Task<CtpRsp<List<CThostFtdcInvestorPositionField>>> ReqQryInvestorPositionAsync(string instrumentID = null);

       

#endregion

#region Order

		Task<CtpRsp<List<CThostFtdcOrderField>>> ReqQryOrderAsync(CThostFtdcQryOrderField pQryOrder);
		Task<CtpRsp<List<CThostFtdcTradeField>>> ReqQryTradeAsync(CThostFtdcQryTradeField pQryTrade);

 
		///报单录入请求
		Task<Tuple<CThostFtdcOrderField?, CtpRsp<CThostFtdcInputOrderField>>>	ReqOrderInsertAsync(CThostFtdcInputOrderField pInputOrder);

        event EventHandler<CThostFtdcOrderField> OnRtnOrderEvent;		// order 状态通知

        event EventHandler<CThostFtdcTradeField> OnRtnTradeEvent;	// trade 成交通知


        Task<Tuple<CThostFtdcOrderField?,CtpRsp<CThostFtdcInputOrderActionField>>> ReqOrderActionAsync(CThostFtdcInputOrderActionField pInputOrderAction);


		//void				ReqOrderInsert(CThostFtdcInputOrderField pInputOrder, Action<CThostFtdcInputOrderField> callback);
		//void				ReqLimitOrderInsert(Action<CThostFtdcInputOrderField> callback, string instrumentID, TThostFtdcOffsetFlagType offsetFlag, TThostFtdcDirectionType dir, 
		//	int volume, double price, double? stopPrice=null,
		//	TThostFtdcTimeConditionType tic= TThostFtdcTimeConditionType.GFD);
		//void				ReqMarketOrderInsert(Action<CThostFtdcInputOrderField> callback, string instrumentID, TThostFtdcOffsetFlagType offsetFlag, TThostFtdcDirectionType dir, int volume);
		//void				ReqConditionOrderInsert(Action<CThostFtdcInputOrderField> callback, string instrumentID,
		//	TThostFtdcContingentConditionType conditionType, double conditionPrice,
		//	TThostFtdcOffsetFlagType offsetFlag, TThostFtdcDirectionType dir, int volume,
		//	TThostFtdcOrderPriceTypeType priceType, double price, TThostFtdcTimeConditionType tic= TThostFtdcTimeConditionType.GFD
		//	);

       

#endregion





		///报单操作请求
		int					ReqOrderAction(ref CThostFtdcInputOrderActionField pInputOrderAction, int nRequestID);


		///预埋单录入请求
		int					ReqParkedOrderInsert(ref CThostFtdcParkedOrderField pParkedOrder, int nRequestID);

		///预埋撤单录入请求
		int					ReqParkedOrderAction(ref CThostFtdcParkedOrderActionField pParkedOrderAction, int nRequestID);


		///查询最大报单数量请求
		int					ReqQueryMaxOrderVolume(ref CThostFtdcQueryMaxOrderVolumeField pQueryMaxOrderVolume, int nRequestID);


	}
}
