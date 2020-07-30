/********************************************************************
    created:	2020-07-30 19:52:49
    author:		joshua
    email:		
	
    purpose:	
*********************************************************************/
using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace SharpCtp
{
	public class CtpMdApi : ICtpMdApi
	{
		public string              BrokerID { get; protected set; }
        public string              AccountID { get; protected set; }
        public string              Psw { get; protected set; }
        public string              FrontAddress { get; protected set; }



		public void			Connect(DataCallback callback)
		{
            _AddCallback(callback, -1);
			_handle = connect(FrontAddress, "", _MdSpi);
		}

		public void Disconnect(DataCallback callback)
		{
			throw new NotImplementedException();
		}

		public void Dispose()
		{
			throw new NotImplementedException();
		}

		public string GetApiVersion()
		{
			throw new NotImplementedException();
		}

		public string GetTradingDay()
		{
			throw new NotImplementedException();
		}

		public bool IsConnected()
		{
			throw new NotImplementedException();
		}

		public int ReqQryMulticastInstrument(int topicID, string instrumentID, DataCallback calllback)
		{
			throw new NotImplementedException();
		}

		public int ReqUserLogin(string investorID, string password, DataCallback calllback)
		{
			throw new NotImplementedException();
		}

		public int ReqUserLogout(DataCallback callback)
		{
			throw new NotImplementedException();
		}

		public int SubscribeForQuoteRsp(params string[] instruments)
		{
			throw new NotImplementedException();
		}

		public int SubscribeMarketData(params string[] instruments)
		{
			throw new NotImplementedException();
		}

		public int UnSubscribeForQuoteRsp(params string[] instruments)
		{
			throw new NotImplementedException();
		}

		public int UnSubscribeMarketData(params string[] instruments)
		{
			throw new NotImplementedException();
		}

		public	CtpMdApi()
		{

            _LoadAssembly();

		}




        /// <summary>
        /// 加载程序集
        /// </summary>
        private void        _LoadAssembly()
        {
            try
            {
                string path = Path.GetFullPath(string.Format("{0}\\{1}", LibraryWrapper.ProcessorArchitecture, DllName));
                _wrapper = new LibraryWrapper(path, "thostmduserapi_se.dll");

                #region 读取方法入口列表

                string resourceName = string.Format("CTPMarketApi.Entry{0}.txt", LibraryWrapper.IsAmd64 ? "64" : "32");
                var assembly = System.Reflection.Assembly.GetExecutingAssembly();
                Stream stream = assembly.GetManifestResourceStream(resourceName);
                if (stream != null)
                {
                    using (StreamReader reader = new StreamReader(stream))
                    {
                        string text = reader.ReadToEnd();
                        string entryStart = "ordinal hint";
                        int start = text.IndexOf(entryStart);
                        if (start > -1)
                        {
                            string[] arr = text.Substring(start).Split('\n');
                            if (arr.Length > 1)
                            {
                                for (int i = 1; i < arr.Length; i++)
                                {
                                    string[] list = arr[i].Split(new char[] { ' ', '\t' },
                                        StringSplitOptions.RemoveEmptyEntries);
                                    if (list.Length > 4)
                                    {
                                        _entryList.Add(list[3]);
                                    }
                                }
                            }
                        }
                    }
                    stream.Close();
                }
                if (_entryList.Count == 0)
                {
                    throw new Exception(string.Format("Cannot find entry point form resource {0}", resourceName));
                }

                #endregion

                #region 获取非托管方法

                createSpi = GetDelegate<DelegateCreateSpi>("CreateSpi");
                getApiVersion = GetDelegate<DelegateGetString>("GetApiVersion");
                getTradingDay = GetDelegate<DelegatetTradingDay>("GetTradingDay");
                connect = GetDelegate<DelegateConnect>("Connect");
                disconnect = GetDelegate<DelegateDisconnect>("DisConnect");
                userLogin = GetDelegate<DelegateUserLogin>("ReqUserLogin");
                userLogout = GetDelegate<DelegateUserLogout>("ReqUserLogout");
                subscribeMarketData = GetDelegate<DelegateSubscribeMarketData>("SubMarketData");
                unsubscribeMarketData = GetDelegate<DelegateUnsubscribeMarketData>("UnSubscribeMarketData");
                regOnRspError = GetDelegate<DelegateRegOnRspError>("RegOnRspError");
                regOnHeartBeatWarning = GetDelegate<DelegateRegOnHeartBeatWarning>("RegOnHeartBeatWarning");
                regOnFrontConnected = GetDelegate<DelegateRegOnFrontConnected>("RegOnFrontConnected");
                regOnFrontDisconnected = GetDelegate<DelegateRegOnFrontDisconnected>("RegOnFrontDisconnected");
                regOnRspUserLogin = GetDelegate<DelegateRegOnRspUserLogin>("RegOnRspUserLogin");
                regOnRspUserLogout = GetDelegate<DelegateRegOnRspUserLogout>("RegOnRspUserLogout");
                regOnRspSubMarketData = GetDelegate<DelegateRegOnRspSubMarketData>("RegOnRspSubMarketData");
                regOnRspUnSubMarketData = GetDelegate<DelegateRegOnRspUnSubMarketData>("RegOnRspUnSubMarketData");
                regOnRtnDepthMarketData = GetDelegate<DelegateRegOnRtnDepthMarketData>("RegOnRtnDepthMarketData");

                #endregion

                _MdSpi = createSpi();
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }
        /// <summary>
        /// 从列表中查找入口并返回非托管方法委托(注意接口前缀不能相同，否则可能找到错误的入口)
        /// </summary>
        /// <param name="name">方法委托</param>
        /// <returns></returns>
        private T GetDelegate<T>(string name) where T : class
        {
            var entries = _entryList.Where(p => p.StartsWith(string.Format("?{0}@", name)));
            int count = entries.Count();
            if (count > 1)
            {
                throw new Exception(string.Format("More than one entries found with the name: \"{0}\"", name));
            }
            if (count == 0)
            {
                throw new Exception(string.Format("Failed to get entry point for \"{0}\"", name));
            }
            string entryName = entries.FirstOrDefault();
            return _wrapper.GetUnmanagedFunction<T>(entryName);
        }


       #region 委托定义

        //请求委托
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        delegate IntPtr DelegateCreateSpi();

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        delegate IntPtr DelegateGetString();

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        delegate IntPtr DelegatetTradingDay(IntPtr ptr);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        delegate IntPtr DelegateConnect(string pFrontAddr, string flowPath, IntPtr ptr);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        delegate void DelegateDisconnect(IntPtr ptr);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        delegate void DelegateUserLogin(IntPtr ptr, int requestID, string brokerID, string investorID, string password);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        delegate void DelegateUserLogout(IntPtr ptr, int requestID, string brokerID, string investorID);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        delegate void DelegateSubscribeMarketData(IntPtr ptr, string[] instrumentsID, int nCount);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        delegate void DelegateUnsubscribeMarketData(IntPtr ptr, string[] ppInstrumentID, int nCount);

        // 回调委托
        delegate void DelegateRegOnRspError(IntPtr ptr, RspError cb);
        delegate void DelegateRegOnHeartBeatWarning(IntPtr ptr, HeartBeatWarning cb);
        delegate void DelegateRegOnFrontConnected(IntPtr ptr, FrontConnected cb);
        delegate void DelegateRegOnFrontDisconnected(IntPtr ptr, FrontDisconnected cb);
        delegate void DelegateRegOnRspUserLogin(IntPtr ptr, RspUserLogin cb);
        delegate void DelegateRegOnRspUserLogout(IntPtr ptr, RspUserLogout cb);
        delegate void DelegateRegOnRspSubMarketData(IntPtr ptr, RspSubMarketData cb);
        delegate void DelegateRegOnRspUnSubMarketData(IntPtr ptr, RspUnSubMarketData cb);
        delegate void DelegateRegOnRtnDepthMarketData(IntPtr ptr, RtnDepthMarketData cb);

        #endregion

        #region 委托实例

        //请求实例
        DelegateCreateSpi createSpi;
        DelegateGetString getApiVersion;
        DelegatetTradingDay getTradingDay;
        DelegateConnect connect;
        DelegateDisconnect disconnect;
        DelegateUserLogin userLogin;
        DelegateUserLogout userLogout;
        DelegateSubscribeMarketData subscribeMarketData;
        DelegateUnsubscribeMarketData unsubscribeMarketData;
        
        //回调实例
        DelegateRegOnRspError regOnRspError;
        DelegateRegOnHeartBeatWarning regOnHeartBeatWarning;
        DelegateRegOnFrontConnected regOnFrontConnected;
        DelegateRegOnFrontDisconnected regOnFrontDisconnected;
        DelegateRegOnRspUserLogin regOnRspUserLogin;
        DelegateRegOnRspUserLogout regOnRspUserLogout;
        DelegateRegOnRspSubMarketData regOnRspSubMarketData;
        DelegateRegOnRspUnSubMarketData regOnRspUnSubMarketData;
        DelegateRegOnRtnDepthMarketData regOnRtnDepthMarketData;

        #endregion



#region 结构定义

        #region 错误响应

        RspError rspError;

        /// <summary>
        /// 错误应答委托
        /// </summary>
        public delegate void RspError(ref CThostFtdcRspInfoField pRspInfo, int nRequestID, byte bIsLast);

        /// <summary>
        /// 错误应答
        /// </summary>
        public event RspError OnRspError
        {
            add { rspError += value; regOnRspError(_MdSpi, rspError); }
            remove { rspError -= value; regOnRspError(_MdSpi, rspError); }
        }

        #endregion

        #region 心跳响应

        HeartBeatWarning heartBeatWarning;

        /// <summary>
        /// 心跳响应委托
        /// </summary>
        public delegate void HeartBeatWarning(int nTimeLapse);

        /// <summary>
        /// 心跳响应
        /// </summary>
        public event HeartBeatWarning OnHeartBeatWarning
        {
            add { heartBeatWarning += value; regOnHeartBeatWarning(_MdSpi, heartBeatWarning); }
            remove { heartBeatWarning -= value; regOnHeartBeatWarning(_MdSpi, heartBeatWarning); }
        }

        #endregion

        #region 连接响应

        FrontConnected frontConnected;

        /// <summary>
        /// 连接响应委托
        /// </summary>
        public delegate void FrontConnected();

        /// <summary>
        /// 连接响应
        /// </summary>
        public event FrontConnected OnFrontConnected
        {
            add { frontConnected += value; regOnFrontConnected(_MdSpi, frontConnected); }
            remove { frontConnected -= value; regOnFrontConnected(_MdSpi, frontConnected); }
        }

        #endregion

        #region 断开应答

        FrontDisconnected frontDisconnected;

        /// <summary>
        /// 断开应答委托
        /// </summary>
        public delegate void FrontDisconnected(int nReason);

        /// <summary>
        /// 断开应答
        /// </summary>
        public event FrontDisconnected OnFrontDisconnected
        {
            add { frontDisconnected += value; regOnFrontDisconnected(_MdSpi, frontDisconnected); }
            remove { frontDisconnected -= value; regOnFrontDisconnected(_MdSpi, frontDisconnected); }
        }

        #endregion

        #region 登入请求应答

        RspUserLogin rspUserLogin;

        /// <summary>
        /// 登入请求应答委托
        /// </summary>
        public delegate void RspUserLogin(ref CThostFtdcRspUserLoginField pRspUserLogin,
            ref CThostFtdcRspInfoField pRspInfo, int nRequestID, byte bIsLast);
        
        /// <summary>
        /// 登入请求应答
        /// </summary>
        public event RspUserLogin OnRspUserLogin
        {
            add { rspUserLogin += value; regOnRspUserLogin(_MdSpi, rspUserLogin); }
            remove { rspUserLogin -= value; regOnRspUserLogin(_MdSpi, rspUserLogin); }
        }

        #endregion

        #region 登出请求应答

        RspUserLogout rspUserLogout;

        /// <summary>
        /// 登出请求应答委托
        /// </summary>
        /// <param name="pUserLogout">用户登出请求</param>
        /// <param name="pRspInfo">响应信息</param>
        /// <param name="nRequestID">请求编号</param>
        /// <param name="bIsLast">是否为最后一条数据</param>
        public delegate void RspUserLogout(ref CThostFtdcUserLogoutField pUserLogout,
            ref CThostFtdcRspInfoField pRspInfo, int nRequestID, byte bIsLast);
        
        /// <summary>
        /// 登出请求应答
        /// </summary>
        public event RspUserLogout OnRspUserLogout
        {
            add { rspUserLogout += value; regOnRspUserLogout(_MdSpi, rspUserLogout); }
            remove { rspUserLogout -= value; regOnRspUserLogout(_MdSpi, rspUserLogout); }
        }

        #endregion

        #region 订阅行情应答

        RspSubMarketData rspSubMarketData;

        /// <summary>
        /// 订阅行情应答委托
        /// </summary>
        /// <param name="pSpecificInstrument">指定合约</param>
        /// <param name="pRspInfo">应答信息</param>
        /// <param name="nRequestID">请求编号</param>
        /// <param name="bIsLast">是否为最后一条数据</param>
        public delegate void RspSubMarketData(ref CThostFtdcSpecificInstrumentField pSpecificInstrument,
            ref CThostFtdcRspInfoField pRspInfo, int nRequestID, byte bIsLast);
        
        /// <summary>
        /// 订阅行情应答
        /// </summary>
        public event RspSubMarketData OnRspSubMarketData
        {
            add { rspSubMarketData += value; regOnRspSubMarketData(_MdSpi, rspSubMarketData); }
            remove { rspSubMarketData -= value; regOnRspSubMarketData(_MdSpi, rspSubMarketData); }
        }

        #endregion

        #region 退订请求应答

        RspUnSubMarketData rspUnSubMarketData;

        /// <summary>
        /// 退订请求应答委托
        /// </summary>
        /// <param name="pSpecificInstrument">指定合约</param>
        /// <param name="pRspInfo">响应信息</param>
        /// <param name="nRequestID">请求编号</param>
        /// <param name="bIsLast">是否为最后一条数据</param>
        public delegate void RspUnSubMarketData(ref CThostFtdcSpecificInstrumentField pSpecificInstrument,
            ref CThostFtdcRspInfoField pRspInfo, int nRequestID, byte bIsLast);
        
        /// <summary>
        /// 退订请求应答
        /// </summary>
        public event RspUnSubMarketData OnRspUnSubMarketData
        {
            add { rspUnSubMarketData += value; regOnRspUnSubMarketData(_MdSpi, rspUnSubMarketData); }
            remove { rspUnSubMarketData -= value; regOnRspUnSubMarketData(_MdSpi, rspUnSubMarketData); }
        }

        #endregion

        #region 深度行情通知

        RtnDepthMarketData rtnDepthMarketData;

        /// <summary>
        /// 深度行情通知委托
        /// </summary>
        /// <param name="pDepthMarketData">深度行情</param>
        public delegate void RtnDepthMarketData(ref CThostFtdcDepthMarketDataField pDepthMarketData);

        /// <summary>
        /// 深度行情通知
        /// </summary>
        public event RtnDepthMarketData OnRtnDepthMarketData
        {
            add { rtnDepthMarketData += value; regOnRtnDepthMarketData(_MdSpi, rtnDepthMarketData); }
            remove { rtnDepthMarketData -= value; regOnRtnDepthMarketData(_MdSpi, rtnDepthMarketData); }
        }

        #endregion
        

#endregion

		/// <summary>
        /// 获取请求ID
        /// </summary>
        /// <returns></returns>
        private int         _GenRequestID()
        {
	        return Interlocked.Increment(ref _requestID);
        }

        /// <summary>
        /// 添加回调方法
        /// </summary>
        /// <param name="callback">回调函数</param>
        /// <param name="requestID">请求编号</param>
        private int         _AddCallback(object callback, int requestID = 0)
        {
            if (requestID == 0)
            {
                requestID = _GenRequestID();
            }
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

        /// <summary>
        /// 执行回调方法
        /// </summary>
        /// <param name="requestID">请求编号</param>
        /// <param name="dataResult">返回结果</param>
        private void        _InvokeCallback(int requestID, DataResult dataResult)
        {
            if (_dataCallbackDict.ContainsKey(requestID))
            {
                object callback;
                if (_dataCallbackDict.TryRemove(requestID, out callback))
                {
                    if (callback != null)
                    {
                        ((DataCallback)callback)(dataResult);
                    }
                }
            }
        }




#region Members
        /// <summary>
        /// DLL名称
        /// </summary>
        private const string DllName = "MdApi.dll";

        /// <summary>
        /// 交易类句柄
        /// </summary>
        private IntPtr _handle = IntPtr.Zero;
        private IntPtr _MdSpi = IntPtr.Zero;   // MdSpi class


        /// <summary>
        /// 类库加载类
        /// </summary>
        private LibraryWrapper _wrapper;

        /// <summary>
        /// 方法入库地址列表
        /// </summary>
        private List<string> _entryList = new List<string>();

      /// <summary>
        /// 回调方法字典
        /// </summary>
        private ConcurrentDictionary<int, object> _dataDict = new ConcurrentDictionary<int, object>();

        /// <summary>
        /// 数据回调字典
        /// </summary>
        private ConcurrentDictionary<int, object> _dataCallbackDict = new ConcurrentDictionary<int, object>();

        /// <summary>
        /// 请求编号
        /// </summary>
        private int _requestID;

        protected object _LockObj = new object();
#endregion
	}
}
