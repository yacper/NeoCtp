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

namespace NeoCtp
{
	public enum ECtpRtn  // 本地失败原因
	{
		Sucess = 0,				// 成功
		NetworkFailure = -1,	// 网络连接失败
		ExceedUnHandled= -2,	// 未处理请求超过许可数
		ExceedPerSeceond = -3,	// 每秒发送请求超过许可数
	}

	public enum EFrontDisconnectedReason
	{
		NetworkReadFail =       0x1001, //  网络读失败
		NetworkWriteFail =        0x1002, // 网络写失败
		HeartbeatTimeout=        0x2001, // 接收心跳超时
		SendHeartbeatFail=        0x2002, // 发送心跳失败
		RcvWrongPacket =       0x2003, // 收到错误报文
	}


	public class CtpRsp
	{
		// 本地返回信息
		public ECtpRtn                Rtn       { get; protected set; } // 调用函数后直接返回

		// 服务器返回信息
		public int                    RequestId { get; protected set; }
		public bool                   IsLast    { get; protected set; }
		public CThostFtdcRspInfoField Rsp       { get; protected set; }

        public CtpRsp(ECtpRtn rtn)
        {
            Rtn       = rtn;
        }

        public CtpRsp(CThostFtdcRspInfoField rsp, int nRequestID, bool bIsLast)
        {
            Rsp       = rsp;
            RequestId = nRequestID;
            IsLast    = bIsLast;
        }
	}

	public class CtpRsp<T2>:CtpRsp
	{
		public T2 Rsp2 { get; set; }

        public CtpRsp(ECtpRtn rtn)
			:base(rtn)
        {
        }
        public CtpRsp(T2 rsp2, CThostFtdcRspInfoField rsp, int nRequestID, bool bIsLast)
            : base(rsp, nRequestID, bIsLast)
        {
            Rsp2 = rsp2;
        }
	}

	public class CtpRsp<T2, T3>:CtpRsp<T2>
	{
		public T3 Rsp3 { get; set; }
        public CtpRsp(T3 rsp3, CThostFtdcRspInfoField rsp, int nRequestID, bool bIsLast, T2 rsp2)
            : base(rsp2, rsp, nRequestID, bIsLast)
        {
            Rsp3 = rsp3;
        }
	}

	public interface ICtpMdApi:INotifyPropertyChanged
	{
        string              FrontAddress { get; }

        string              BrokerId { get; }
        string              UserId { get; }
        string              Password { get; }

        //int                 FrontID { get; }                                /// 前置编号
        //int                 SessionID { get; }                              /// 会话编号
        //string              MaxOrderRef { get;  }                           /// 最大报单引用

		int					TimeoutMilliseconds { get; set; }


        string				GetApiVersion();								// 获取版本号

	    ///获取当前交易日
		///@retrun 获取到的交易日
		///@remark 只有登录成功后,才能得到正确的交易日
        string				GetTradingDay();


        event EventHandler<CtpRsp> OnRspErrorEvent;
        event EventHandler<int> OnHeartBeatWarningEvent;

        bool                IsConnected { get; }
		Task				ConnectAsync();
//		Task				Disconnect();
        event EventHandler<EFrontDisconnectedReason> OnFrontDisconnectedEvent;


		bool                                      IsLogined { get; }
        Task<CtpRsp<CThostFtdcRspUserLoginField>> ReqUserLoginAsync();
        Task<CtpRsp<CThostFtdcUserLogoutField>>   ReqUserLogoutAsync();


		ReadOnlyObservableCollection<string>    Subscribed { get; } // 订阅的
        Task<CtpRsp<List<string>>> SubMarketDataAsync(params string[] instruments);
        Task<CtpRsp<List<string>>> UnSubMarketDataAsync(params string[] instruments);
        event EventHandler<CThostFtdcDepthMarketDataField> OnRtnDepthMarketDataEvent;
	}
}
