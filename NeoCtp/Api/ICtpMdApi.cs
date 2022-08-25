/********************************************************************
	created:	2020-09-27 20:23:04
	author:		joshua
	email:		
	
	purpose:	适合c#的简易版
*********************************************************************/
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using NeoCtp.Api;
using NeoCtp.Enums;

namespace NeoCtp
{
	public interface ICtpMdApi:INotifyPropertyChanged
	{
        string              FrontAddress { get; }

        string              BrokerId { get; }
        string              UserId { get; }
        string              Password { get; }

        string              FlowPath    { get; }
        bool                IsUsingUdp  { get; }
        bool                IsMulticast { get; }


        //int                 FrontId { get; }                                /// 前置编号
        //int                 SessionId { get; }                              /// 会话编号
        //string              MaxOrderRef { get;  }                           /// 最大报单引用

		int					TimeoutMilliseconds { get; set; }


        string				GetApiVersion();								// 获取版本号

	    ///获取当前交易日
		///@retrun 获取到的交易日
		///@remark 只有登录成功后,才能得到正确的交易日
        string				GetTradingDay();


        event EventHandler<CtpRsp> OnRspErrorEvent;
        event EventHandler<int> OnHeartBeatWarningEvent;

        EConnectionState                             ConnectionState { get; }
        Task<bool>                                   ConnectAsync(string frontAddress = null);
        Task                                         DisconnectAsync();
        event EventHandler<EFrontDisconnectedReason> OnFrontDisconnectedEvent;


		bool                                      IsLogined { get; }
        Task<CtpRsp<CThostFtdcRspUserLoginField>> ReqUserLoginAsync(string brokerId = null, string userId = null, string password = null);
        Task<CtpRsp<CThostFtdcUserLogoutField>>   ReqUserLogoutAsync();


		ReadOnlyObservableCollection<string>    Subscribed { get; } // 订阅的
        Task<CtpRsp<List<string>>> SubMarketDataAsync(params string[] instruments);
        Task<CtpRsp<List<string>>> UnSubMarketDataAsync(params string[] instruments);
        event EventHandler<CThostFtdcDepthMarketDataField> OnRtnDepthMarketDataEvent;
	}
}
