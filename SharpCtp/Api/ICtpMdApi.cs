/********************************************************************
    created:	2020-07-30 19:52:49
    author:		joshua
    email:		
	
    purpose:	改接口包含了原CTP的MdApi和MdSpi方法, 在一个类中实现
*********************************************************************/
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SharpCtp
{
	public interface ICtpMdApi:IDisposable
	{
        string              BrokerID { get; }
        string              AccountID { get; }
        string              Psw { get; }
        string              FrontAddress { get; }


		string              GetApiVersion();

		/// <summary>
        /// 是否已连接
        /// </summary>
        /// <returns></returns>
        bool                IsConnected();

        /// <summary>
        /// 连接服务器
        /// </summary>
        /// <param name="callback">连接服务器回调</param>
        /// <param name="brokerID">经纪商代码</param>
        /// <param name="frontAddress">前置服务器地址</param>
        void                Connect(DataCallback callback);

        /// <summary>
        /// 断开连接
        /// </summary>
        /// <param name="callback">断开连接回调</param>
        void                Disconnect(DataCallback callback);

		///获取当前交易日
		///@retrun 获取到的交易日
		///@remark 只有登录成功后,才能得到正确的交易日
        string              GetTradingDay();

        /// <summary>
        /// 用户登录
        /// </summary>
        /// <param name="investorID">投资者账号</param>
        /// <param name="password">密码</param>
        int                ReqUserLogin(string investorID, string password, DataCallback calllback);

        /// <summary>
        /// 用户登出
        /// </summary>
        /// <param name="callback">登出回调</param>
        int                ReqUserLogout(DataCallback callback);

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
		int                 ReqQryMulticastInstrument(int topicID, string instrumentID, DataCallback calllback);

#region Callbacks

        

#endregion
    }
}
