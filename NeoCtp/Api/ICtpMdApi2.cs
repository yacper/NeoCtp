/********************************************************************
	created:	2020-09-27 20:23:04
	author:		joshua
	email:		
	
	purpose:	适合c#的简易版
*********************************************************************/
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NeoCtp
{
	public enum ECtpRtn
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
		public ECtpRtn Rtn { get; set; }
		public CThostFtdcRspInfoField Rsp { get; set; }
	}

	public class CtpRsp<T>:CtpRsp
	{
		public T Rsp1 { get; set; }
	}

	public class CtpRtn<T, T2>:CtpRsp<T>
	{
		public T2 Rsp2 { get; set; }
	}

	public interface ICtpMdApi2:INotifyPropertyChanged
	{
        string              FrontAddress { get; }

        string              BrokerID { get; }
        string              UserID { get; }
        string              Password { get; }

        //int                 FrontID { get; }                                /// 前置编号
        //int                 SessionID { get; }                              /// 会话编号
        //string              MaxOrderRef { get;  }                           /// 最大报单引用



        string				GetTradingDay();


        bool                IsConnected { get; }
		void 				Connect(string frontAddr, Action<bool> callback);
        event Action<EFrontDisconnectedReason> FrontDisconnected;


		bool				IsLogined { get; }
		ECtpRtn				ReqUserLogin(string brokerID, string user, string psw, Action<CThostFtdcRspInfoField, CThostFtdcRspUserLoginField> callback);
		ECtpRtn				ReqUserLogout(Action<CThostFtdcRspInfoField, CThostFtdcUserLogoutField> callback);



		IEnumerable<string>	Subscribed { get; }								// 订阅的
        ECtpRtn				SubMarketData(params string[] instruments);
        event Action<CThostFtdcSpecificInstrumentField, CThostFtdcRspInfoField, bool> RspSubMarketData;
        ECtpRtn             UnSubMarketData(params string[] instruments);
        event Action<CThostFtdcSpecificInstrumentField, CThostFtdcRspInfoField, bool> RspUnSubMarketData;


        event Action<CThostFtdcDepthMarketDataField> DepthMarketDataChanged;
	}
}
