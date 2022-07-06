/********************************************************************
    created:	2020-11-11 22:40:38
    author:		rush
    email:		
	
    purpose:	
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
        int                 SessionId { get; }                              /// 会话编号
        string              MaxOrderRef { get;  }                           /// 最大报单引用

        string              BrokerId { get; }
        string              UserId { get; }
        string              Password { get; }

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
		void				ReqQryTradingAccount(Action<CtpRsp<CThostFtdcTradingAccountField>> callback);


		///请求查询投资者持仓
		void				ReqQryInvestorPosition(string instrumentID, Action<CtpRsp<List<CThostFtdcInstrumentField>>> callback);





		void				ReqQryInstrument(string instrumentID, Action<CtpRsp<CThostFtdcInstrumentField>> callback);



		///报单录入请求
		void				ReqOrderInsert(CThostFtdcInputOrderField pInputOrder, Action<CThostFtdcInputOrderField> callback);
		void				ReqLimitOrderInsert(Action<CThostFtdcInputOrderField> callback, string instrumentID, TThostFtdcOffsetFlagType offsetFlag, TThostFtdcDirectionType dir, 
			int volume, double price, double? stopPrice=null,
			TThostFtdcTimeConditionType tic= TThostFtdcTimeConditionType.GFD);
		void				ReqMarketOrderInsert(Action<CThostFtdcInputOrderField> callback, string instrumentID, TThostFtdcOffsetFlagType offsetFlag, TThostFtdcDirectionType dir, int volume);
		void				ReqConditionOrderInsert(Action<CThostFtdcInputOrderField> callback, string instrumentID,
			TThostFtdcContingentConditionType conditionType, double conditionPrice,
			TThostFtdcOffsetFlagType offsetFlag, TThostFtdcDirectionType dir, int volume,
			TThostFtdcOrderPriceTypeType priceType, double price, TThostFtdcTimeConditionType tic= TThostFtdcTimeConditionType.GFD
			);

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
