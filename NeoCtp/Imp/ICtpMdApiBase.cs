/********************************************************************
    created:	2020-07-30 19:52:49
    author:		rush
    email:		
	
    purpose:	改接口包含了原CTP的MdApi和MdSpi方法, 在一个类中实现
*********************************************************************/
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace NeoCtp
{
	public partial class CtpMdApiBase
	{
		public static string GetApiVersion()			// 获取版本号
		{
			IntPtr ptr = MdApiCalls.GetApiVersion();

            return Marshal.PtrToStringAnsi(ptr);
		}
	}

	internal interface ICtpMdApiBase:IDisposable, INotifyPropertyChanged
	{
        string              BrokerId { get; }
        string              UserId { get; }
        string              Password { get; }
        string              FrontAddress { get; }

        //int                 FrontID { get; }                                /// 前置编号
        //int                 SessionID { get; }                              /// 会话编号
        //string              MaxOrderRef { get;  }                           /// 最大报单引用


        void                RegisterSpi(ICtpMdSpi spi);


        ///删除接口对象本身
        ///@remark 不再使用本接口对象时,调用该函数删除接口对象
        void				Release();

        ///初始化
        ///@remark 初始化运行环境,只有调用后,接口才开始工作
        void				Init();

        ///等待接口线程结束运行
        ///@return 线程退出代码
        int					Join();


		///获取当前交易日
		///@retrun 获取到的交易日
		///@remark 只有登录成功后,才能得到正确的交易日
        string              GetTradingDay();

		///注册前置机网络地址
		///@param pszFrontAddress：前置机网络地址。
		///@remark 网络地址的格式为：“protocol://ipaddress:port”，如：”tcp://127.0.0.1:17001”。 
		///@remark “tcp”代表传输协议，“127.0.0.1”代表服务器地址。”17001”代表服务器端口号。
		void				RegisterFront(string pszFrontAddress);

		///注册名字服务器网络地址
		///@param pszNsAddress：名字服务器网络地址。
		///@remark 网络地址的格式为：“protocol://ipaddress:port”，如：”tcp://127.0.0.1:12001”。 
		///@remark “tcp”代表传输协议，“127.0.0.1”代表服务器地址。”12001”代表服务器端口号。
		///@remark RegisterNameServer优先于RegisterFront
		void				RegisterNameServer(string pszNsAddress);

		///注册名字服务器用户信息
		///@param pFensUserInfo：用户信息。
		void				RegisterFensUserInfo(ref CThostFtdcFensUserInfoField pFensUserInfo);



		/// <summary>
		/// 用户登录
		/// </summary>
		/// <param name="investorID">投资者账号</param>
		/// <param name="password">密码</param>
		int                ReqUserLogin(ref CThostFtdcReqUserLoginField pReqUserLoginField, int nRequestID);

        /// <summary>
        /// 用户登出
        /// </summary>
        /// <param name="callback">登出回调</param>
        int                ReqUserLogout(ref CThostFtdcUserLogoutField pUserLogout, int nRequestID);

        /// <summary>
        /// 订阅行情
        /// </summary>
        /// <param name="instruments">合约代码，传空订阅所有</param>
        int                 SubscribeMarketData(params string[] instruments);

        /// <summary>
        /// 退订行情
        /// </summary>
        /// <param name="instruments">合约代码，传空退订所有</param>
        int                 UnSubscribeMarketData(params string[] instruments);

        ///订阅询价。
        ///@param ppInstrumentID 合约ID  
        ///@param nCount 要订阅/退订行情的合约个数
        ///@remark 
        int                 SubscribeForQuoteRsp(params string[] instruments);

	///退订询价。
	///@param ppInstrumentID 合约ID  
	///@param nCount 要订阅/退订行情的合约个数
	///@remark 
		int                 UnSubscribeForQuoteRsp(params string[] instruments);


	///请求查询组播合约
		int                 ReqQryMulticastInstrument(ref CThostFtdcQryMulticastInstrumentField pQryMulticastInstrument, int nRequestID);


     
	}
}
