/********************************************************************
    created:	2020-07-30 19:52:49
    author:		rush
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
using Force.DeepCloner;
using Microsoft.Toolkit.Mvvm.ComponentModel;
using NeoCtp.Enums;

namespace NeoCtp
{
public partial class CtpMdApiBase : ObservableObject, ICtpMdApiBase
{
#region C&D

    public CtpMdApiBase(string frontAddress,               string brokerId,            string userId, string password,
        string                 pszFlowPath = "CtpMdFlow/", bool   bIsUsingUdp = false, bool   bIsMulticast = false)
    {
        FrontAddress = frontAddress;
        BrokerId     = brokerId;
        UserId       = userId;
        Password     = password;

        FlowPath    = pszFlowPath;
        IsUsingUdp  = bIsUsingUdp;
        IsMulticast = bIsMulticast;
    }

#endregion


    public string BrokerId     { get { return _BrokerID; }     protected set { SetProperty(ref _BrokerID, value); } }
    public string UserId       { get { return _UserID; }       protected set { SetProperty(ref _UserID, value); } }
    public string Password     { get { return _Password; }     protected set { SetProperty(ref _Password, value); } }
    public string FrontAddress { get { return _FrontAddress; } protected set { SetProperty(ref _FrontAddress, value); } }

    public string FlowPath    { get => FlowPath_;    set => SetProperty(ref FlowPath_, value); }
    public bool   IsUsingUdp  { get => IsUsingUdp_;  set => SetProperty(ref IsUsingUdp_, value); }
    public bool   IsMulticast { get => IsMulticast_; set => SetProperty(ref IsMulticast_, value); }

    protected string FlowPath_;


    /// <summary>
    /// 前置编号
    /// </summary>
    public int FrontID { get { return _FrontID; } protected set { SetProperty(ref _FrontID, value); } }

    /// <summary>
    /// 会话编号
    /// </summary>
    public int SessionID { get { return _SessionID; } protected set { SetProperty(ref _SessionID, value); } }

    /// <summary>
    /// 最大报单引用
    /// </summary>
    public string MaxOrderRef { get { return _MaxOrderRef; } protected set { SetProperty(ref _MaxOrderRef, value); } }


    public void RegisterSpi(ICtpMdSpi spi)
    {
        lock (this) { _MdSpi = spi; }
    }


    public void Dispose() { throw new NotImplementedException(); }

    public void Release() { MdApiCalls.Release(ApiHandle_); }

    ///初始化
    ///@remark 初始化运行环境,只有调用后,接口才开始工作
    public void Init()
    {
        MdApiCalls.Init(ApiHandle_);
        return;
        ReaderThread_ = new Thread(
                                   () =>
                                   {
                                       MdApiCalls.Init(ApiHandle_);
                                       //MdApiCalls.Join(ApiHandle_);
                                       while (true) { Thread.Sleep(500); }
                                   })
            ;
        this.ReaderThread_.Start();

        //Task.Run(() =>
        //{
        //    MdApiCalls.Init(ApiHandle_);
        //    MdApiCalls.Join(ApiHandle_);
        //});
    }

    protected Thread ReaderThread_;

    ///等待接口线程结束运行
    ///@return 线程退出代码
    public int Join()
    {
        if (ApiHandle_ == IntPtr.Zero) return (int)ECtpExecuteRtn.NetworkFailure;
        return MdApiCalls.Join(ApiHandle_);
    }

    public string GetTradingDay()
    {
        IntPtr ptr = MdApiCalls.GetTradingDay(ApiHandle_);

        return Marshal.PtrToStringAuto(ptr);
        //return Marshal.PtrToStringAnsi(ptr);
    }


    public void RegisterFront(string pszFrontAddress)
    {
        FrontAddress = pszFrontAddress;
        MdApiCalls.RegisterFront(ApiHandle_, pszFrontAddress);
    }

    ///注册名字服务器网络地址
    ///@param pszNsAddress：名字服务器网络地址。
    ///@remark 网络地址的格式为：“protocol://ipaddress:port”，如：”tcp://127.0.0.1:12001”。 
    ///@remark “tcp”代表传输协议，“127.0.0.1”代表服务器地址。”12001”代表服务器端口号。
    ///@remark RegisterNameServer优先于RegisterFront
    public void RegisterNameServer(string pszNsAddress) { MdApiCalls.RegisterFront(ApiHandle_, pszNsAddress); }

    ///注册名字服务器用户信息
    ///@param pFensUserInfo：用户信息。
    public void RegisterFensUserInfo(ref CThostFtdcFensUserInfoField pFensUserInfo)
    {
        BrokerId = pFensUserInfo.BrokerID;
        UserId   = pFensUserInfo.UserID;
        MdApiCalls.RegisterFensUserInfo(ApiHandle_, ref pFensUserInfo);
    }


    public int ReqUserLogin(ref CThostFtdcReqUserLoginField pReqUserLoginField, int nRequestID)
    {
        //BrokerId = pReqUserLoginField.BrokerId;
        //UserId = pReqUserLoginField.UserId;
        //Password = pReqUserLoginField.Password;

        if (ApiHandle_ == IntPtr.Zero) return (int)ECtpExecuteRtn.NetworkFailure;
        return MdApiCalls.ReqUserLogin(ApiHandle_, ref pReqUserLoginField, nRequestID);
    }

    /// <summary>
    /// 用户登出
    /// </summary>
    /// <param name="callback">登出回调</param>
    public int ReqUserLogout(ref CThostFtdcUserLogoutField pUserLogout, int nRequestID)
    {
        if (ApiHandle_ == IntPtr.Zero) return (int)ECtpExecuteRtn.NetworkFailure;
        return MdApiCalls.ReqUserLogout(ApiHandle_, ref pUserLogout, nRequestID);
    }


    public int SubscribeForQuoteRsp(params string[] instruments)
    {
        if (ApiHandle_ == IntPtr.Zero) return (int)ECtpExecuteRtn.NetworkFailure;
        return MdApiCalls.SubscribeForQuoteRsp(ApiHandle_, instruments, instruments == null ? 0 : instruments.Length);
    }

    public int UnSubscribeForQuoteRsp(params string[] instruments)
    {
        if (ApiHandle_ == IntPtr.Zero) return (int)ECtpExecuteRtn.NetworkFailure;
        return MdApiCalls.UnSubscribeForQuoteRsp(ApiHandle_, instruments, instruments == null ? 0 : instruments.Length);
    }

    public int SubscribeMarketData(params string[] instruments)
    {
        if (ApiHandle_ == IntPtr.Zero) return (int)ECtpExecuteRtn.NetworkFailure;
        return MdApiCalls.SubscribeMarketData(ApiHandle_, instruments, instruments == null ? 0 : instruments.Length);
    }

    public int UnSubscribeMarketData(params string[] instruments)
    {
        if (ApiHandle_ == IntPtr.Zero) return (int)ECtpExecuteRtn.NetworkFailure;
        return MdApiCalls.UnSubscribeMarketData(ApiHandle_, instruments, instruments == null ? 0 : instruments.Length);
    }

    public int ReqQryMulticastInstrument(ref CThostFtdcQryMulticastInstrumentField pQryMulticastInstrument, int nRequestID)
    {
        if (ApiHandle_ == IntPtr.Zero) return (int)ECtpExecuteRtn.NetworkFailure;
        return MdApiCalls.ReqQryMulticastInstrument(ApiHandle_, ref pQryMulticastInstrument, nRequestID);
    }


    private MdApiCalls.CbOnRspError                  cbOnRspErrorDele;
    private MdApiCalls.CbOnHeartBeatWarning          cbOnHeartBeatWarningDele;
    private MdApiCalls.CbOnFrontConnected            cbOnFrontConnectedDele;
    private MdApiCalls.CbOnFrontDisconnected         cbOnFrontDisconnectedDele;
    private MdApiCalls.CbOnRspUserLogin              cbOnRspUserLoginDele;
    private MdApiCalls.CbOnRspUserLogout             cbOnRspUserLogoutDele;
    private MdApiCalls.CbOnRspSubMarketData          cbOnRspSubMarketDataDele;
    private MdApiCalls.CbOnRspUnSubMarketData        cbOnRspUnSubMarketDataDele;
    private MdApiCalls.CbOnRspSubForQuoteRsp         cbOnRspSubForQuoteRspDele;
    private MdApiCalls.CbOnRspUnSubForQuoteRsp       cbOnRspUnSubForQuoteRspDele;
    private MdApiCalls.CbOnRtnDepthMarketData        cbOnRtnDepthMarketDataDele;
    private MdApiCalls.CbOnRtnForQuoteRsp            cbOnRtnForQuoteRspDele;
    private MdApiCalls.CbOnRspQryMulticastInstrument cbOnRspQryMulticastInstrumentDele;

    protected void BindEvents_()
    {
        // 必须添加deletate引用，否则会被gc回收
        cbOnRspErrorDele = new(_OnRspError);
        MdApiCalls.RegOnRspError(SpiHandle_, cbOnRspErrorDele);
        cbOnHeartBeatWarningDele = new(_CbOnHeartBeatWarning);
        MdApiCalls.RegOnHeartBeatWarning(SpiHandle_, cbOnHeartBeatWarningDele);

        cbOnFrontConnectedDele = new(_OnFrontConnected);
        MdApiCalls.RegOnFrontConnected(SpiHandle_, cbOnFrontConnectedDele);
        cbOnFrontDisconnectedDele = new(_OnFrontDisconnected);
        MdApiCalls.RegOnFrontDisconnected(SpiHandle_, cbOnFrontDisconnectedDele);

        cbOnRspUserLoginDele = new(_OnRspUserLogin);
        MdApiCalls.RegOnRspUserLogin(SpiHandle_, cbOnRspUserLoginDele);
        cbOnRspUserLogoutDele = new(_OnRspUserLogout);
        MdApiCalls.RegOnRspUserLogout(SpiHandle_, cbOnRspUserLogoutDele);

        cbOnRspSubMarketDataDele = new(_OnRspSubMarketData);
        MdApiCalls.RegOnRspSubMarketData(SpiHandle_, cbOnRspSubMarketDataDele);
        cbOnRspUnSubMarketDataDele = new(_OnRspUnSubMarketData);
        MdApiCalls.RegOnRspUnSubMarketData(SpiHandle_, cbOnRspUnSubMarketDataDele);

        cbOnRspSubForQuoteRspDele = new(_OnRspSubForQuoteRsp);
        MdApiCalls.RegOnRspSubForQuoteRsp(SpiHandle_, cbOnRspSubForQuoteRspDele);
        cbOnRspUnSubForQuoteRspDele = new(_OnRspUnSubForQuoteRsp);
        MdApiCalls.RegOnRspUnSubForQuoteRsp(SpiHandle_, cbOnRspUnSubForQuoteRspDele);

        cbOnRspQryMulticastInstrumentDele = new(_OnRspQryMulticastInstrument);
        MdApiCalls.RegOnRspQryMulticastInstrument(SpiHandle_, cbOnRspQryMulticastInstrumentDele);

        /// 通知
        cbOnRtnDepthMarketDataDele = new(_OnRtnDepthMarketData);
        MdApiCalls.RegOnRtnDepthMarketData(SpiHandle_, cbOnRtnDepthMarketDataDele);

        cbOnRtnForQuoteRspDele = new(_OnRtnForQuoteRsp);
        MdApiCalls.RegOnRtnForQuoteRsp(SpiHandle_, cbOnRtnForQuoteRspDele);
    }

    /// <summary>
    /// 错误回调
    /// </summary>
    /// <param name="pRspInfo">错误信息</param>
    /// <param name="nRequestID">请求编号</param>
    /// <param name="bIsLast">是否为最后一条数据</param>
    protected virtual void _OnRspError(ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
    {
        _MdSpi?.OnRspError(pRspInfo, nRequestID, bIsLast);

        //if (_dataCallbackDict.ContainsKey(nRequestID))
        //{
        //    var callback = _dataCallbackDict[nRequestID];
        //    if (callback != null)
        //    {
        //        DataResult result = new DataResult();
        //        _SetError(result, pRspInfo);
        //        _InvokeCallback(nRequestID, result);
        //    }
        //}
    }

    protected virtual void _CbOnHeartBeatWarning(int nTimeLapse) { _MdSpi?.OnHeartBeatWarning(nTimeLapse); }

    /// <summary>
    /// 连接成功回调
    /// </summary>
    private void _OnFrontConnected()
    {
        _MdSpi?.OnFrontConnected();

        //_InvokeCallback(-1, new DataResult()
        //{
        //    IsSuccess = true
        //});
        //IsConnected = true;
    }

    /// <summary>
    /// 断开连接回调
    /// </summary>
    /// <param name="nReason">原因</param>
    protected virtual void _OnFrontDisconnected(int nReason) { _MdSpi?.OnFrontDisconnected(nReason); }

    /// <summary>
    /// 登录回调
    /// </summary>
    /// <param name="pRspUserLogin">登录返回结果</param>
    /// <param name="pRspInfo">错误信息</param>
    /// <param name="nRequestID">请求编号</param>
    /// <param name="bIsLast">是否为最后一条数据</param>
    private void _OnRspUserLogin(ref CThostFtdcRspUserLoginField pRspUserLogin, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
    {
        _MdSpi?.OnRspUserLogin(pRspUserLogin, pRspInfo, nRequestID, bIsLast);

        //DataResult result = new DataResult();
        //if (pRspInfo.ErrorID > 0)
        //{
        //    _SetError(result, pRspInfo);
        //}
        //else
        //{
        //    FrontId = pRspUserLogin.FrontId;
        //    SessionId = pRspUserLogin.SessionId;
        //    MaxOrderRef = pRspUserLogin.MaxOrderRef;
        //    result.IsSuccess = true;
        //}
        //_InvokeCallback(-3, result);
    }

    /// <summary>
    /// 登出回调
    /// </summary>
    /// <param name="pUserLogout">登出返回结果</param>
    /// <param name="pRspInfo">错误信息</param>
    /// <param name="nRequestID">请求编号</param>
    /// <param name="bIsLast">是否为最后一条数据</param>
    private void _OnRspUserLogout(ref CThostFtdcUserLogoutField pUserLogout, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
    {
        _MdSpi?.OnRspUserLogout(pUserLogout, pRspInfo, nRequestID, bIsLast);

        //DataResult result = new DataResult();
        //if (pRspInfo.ErrorID > 0)
        //{
        //    _SetError(result, pRspInfo);
        //}
        //else
        //{
        //    result.IsSuccess = true;
        //}
        //_InvokeCallback(-4, result);
    }


    protected virtual void _OnRspSubMarketData(ref CThostFtdcSpecificInstrumentField pSpecificInstrument, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
    {
        _MdSpi?.OnRspSubMarketData(pSpecificInstrument, pRspInfo, nRequestID, bIsLast);
    }

    protected virtual void _OnRspUnSubMarketData(ref CThostFtdcSpecificInstrumentField pSpecificInstrument, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
    {
        _MdSpi?.OnRspUnSubMarketData(pSpecificInstrument, pRspInfo, nRequestID, bIsLast);
    }


    protected virtual void _OnRspSubForQuoteRsp(ref CThostFtdcSpecificInstrumentField pSpecificInstrument,
        ref                                         CThostFtdcRspInfoField            pRspInfo, int nRequestID, bool bIsLast)
    {
        _MdSpi?.OnRspSubForQuoteRsp(pSpecificInstrument, pRspInfo, nRequestID, bIsLast);
    }

    protected virtual void _OnRspUnSubForQuoteRsp(ref CThostFtdcSpecificInstrumentField pSpecificInstrument,
        ref                                           CThostFtdcRspInfoField            pRspInfo, int nRequestID, bool bIsLast)
    {
        _MdSpi?.OnRspUnSubForQuoteRsp(pSpecificInstrument, pRspInfo, nRequestID, bIsLast);
    }


    protected virtual void _OnRspQryMulticastInstrument(ref CThostFtdcMulticastInstrumentField pMulticastInstrument, ref CThostFtdcRspInfoField pRspInfo,
        int                                                                                    nRequestID,           bool                       bIsLast)
    {
        _MdSpi?.OnRspQryMulticastInstrument(pMulticastInstrument, pRspInfo, nRequestID, bIsLast);
    }


    protected virtual void _OnRtnDepthMarketData(ref CThostFtdcDepthMarketDataField pDepthMarketData) { _MdSpi?.OnRtnDepthMarketData(pDepthMarketData); }

    protected virtual void _OnRtnForQuoteRsp(ref CThostFtdcForQuoteRspField pQuoteRsp) { _MdSpi?.OnRtnForQuoteRsp(pQuoteRsp); }


    ///// <summary>
    //      /// 设置错误信息
    //      /// </summary>
    //      /// <param name="result">返回结果</param>
    //      /// <param name="pRspInfo">错误信息</param>
    //      private void _SetError(DataResult result, CThostFtdcRspInfoField pRspInfo)
    //      {
    //          result.ErrorCode = pRspInfo.ErrorID.ToString();
    //          result.Error = pRspInfo.ErrorMsg;
    //          result.IsSuccess = false;
    //      }


    // public event EventHandler<CThostFtdcDepthMarketDataField> OnDepthMarketData;

    //#region 委托定义

    // //请求委托
    // [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    // delegate IntPtr DelegateCreateSpi();

    // [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    // delegate IntPtr DelegateGetApiVersion();

    // [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    // delegate IntPtr DelegateGetTradingDay(IntPtr ptr);

    // [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    // delegate IntPtr DelegateConnect(string pFrontAddr, string flowPath, IntPtr ptr);

    // [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    // delegate void DelegateDisconnect(IntPtr ptr);

    // [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    // delegate int DelegateReqUserLogin(IntPtr ptr, int requestID, string brokerID, string investorID, string password);

    // [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    // delegate int DelegateReqUserLogout(IntPtr ptr, int requestID, string brokerID, string investorID);

    // [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    // delegate void DelegateSubscribeMarketData(IntPtr ptr, string[] instrumentsID, int nCount);

    // [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    // delegate void DelegateUnsubscribeMarketData(IntPtr ptr, string[] ppInstrumentID, int nCount);

    // [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    // delegate void DelegateSubscribeForQuoteRsp(IntPtr ptr, string[] instrumentsID, int nCount);

    // [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    // delegate void DelegateUnSubscribeForQuoteRsp(IntPtr ptr, string[] ppInstrumentID, int nCount);

    // [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    // delegate void DelegateReqQryMulticastInstrument(IntPtr ptr, int topicID, string ppInstrumentID, int requestID);

    // // 回调委托
    // delegate void DelegateRegOnRspError(IntPtr ptr, RspError cb);
    // delegate void DelegateRegOnHeartBeatWarning(IntPtr ptr, HeartBeatWarning cb);
    // delegate void DelegateRegOnFrontConnected(IntPtr ptr, FrontConnected cb);
    // delegate void DelegateRegOnFrontDisconnected(IntPtr ptr, FrontDisconnected cb);
    // delegate void DelegateRegOnRspUserLogin(IntPtr ptr, RspUserLogin cb);
    // delegate void DelegateRegOnRspUserLogout(IntPtr ptr, RspUserLogout cb);
    // delegate void DelegateRegOnRspSubMarketData(IntPtr ptr, RspSubMarketData cb);
    // delegate void DelegateRegOnRspUnSubMarketData(IntPtr ptr, RspUnSubMarketData cb);
    // delegate void DelegateRegOnRspSubForQuoteRsp(IntPtr ptr, RspSubForQuoteRsp cb);
    // delegate void DelegateRegOnRspUnSubForQuoteRsp(IntPtr ptr, RspUnSubForQuoteRsp cb);
    // delegate void DelegateRegOnRtnDepthMarketData(IntPtr ptr, RtnDepthMarketData cb);
    // delegate void DelegateRegOnRtnForQuoteRsp(IntPtr ptr, RtnForQuoteRsp cb);

    // #endregion

    //#region 委托实例

    ////请求实例
    //DelegateCreateSpi createSpi;
    //DelegateGetApiVersion getApiVersion;
    //DelegateGetTradingDay getTradingDay;
    //DelegateConnect connect;
    //DelegateDisconnect disconnect;
    //DelegateReqUserLogin reqUserLogin;
    //DelegateReqUserLogout reqUserLogout;
    //DelegateSubscribeMarketData subscribeMarketData;
    //DelegateUnsubscribeMarketData unsubscribeMarketData;
    //DelegateSubscribeForQuoteRsp subscribeForQuoteRsp;
    //DelegateUnSubscribeForQuoteRsp unsubscribeForQuoteRsp;
    //DelegateReqQryMulticastInstrument reqQryMulticastInstrument;

    ////回调实例
    //DelegateRegOnRspError regOnRspError;
    //DelegateRegOnHeartBeatWarning regOnHeartBeatWarning;
    //DelegateRegOnFrontConnected regOnFrontConnected;
    //DelegateRegOnFrontDisconnected regOnFrontDisconnected;
    //DelegateRegOnRspUserLogin regOnRspUserLogin;
    //DelegateRegOnRspUserLogout regOnRspUserLogout;
    //DelegateRegOnRspSubMarketData regOnRspSubMarketData;
    //DelegateRegOnRspUnSubMarketData regOnRspUnSubMarketData;
    //DelegateRegOnRspSubForQuoteRsp regOnRspSubForQuoteRsp;
    //DelegateRegOnRspUnSubForQuoteRsp regOnRspUnSubForQuoteRsp;
    //DelegateRegOnRtnDepthMarketData regOnRtnDepthMarketData;
    //DelegateRegOnRtnForQuoteRsp regOnRtnForQuoteRsp;

    //#endregion


//#region 结构定义

//        #region 错误响应
//        RspError rspError;

//        /// <summary>
//        /// 错误应答委托
//        /// </summary>
//        public delegate void RspError(ref CThostFtdcRspInfoField pRspInfo, int nRequestID, byte bIsLast);

//        /// <summary>
//        /// 错误应答
//        /// </summary>
//        public event RspError OnRspError
//        {
//            add { rspError += value; regOnRspError(TdSpi_, rspError); }
//            remove { rspError -= value; regOnRspError(TdSpi_, rspError); }
//        }

//        #endregion

//        #region 心跳响应

//        HeartBeatWarning heartBeatWarning;

//        /// <summary>
//        /// 心跳响应委托
//        /// </summary>
//        public delegate void HeartBeatWarning(int nTimeLapse);

//        /// <summary>
//        /// 心跳响应
//        /// </summary>
//        public event HeartBeatWarning OnHeartBeatWarning
//        {
//            add { heartBeatWarning += value; regOnHeartBeatWarning(TdSpi_, heartBeatWarning); }
//            remove { heartBeatWarning -= value; regOnHeartBeatWarning(TdSpi_, heartBeatWarning); }
//        }

//        #endregion

//        #region 连接响应

//        FrontConnected frontConnected;

//        /// <summary>
//        /// 连接响应委托
//        /// </summary>
//        public delegate void FrontConnected();

//        /// <summary>
//        /// 连接响应
//        /// </summary>
//        public event FrontConnected OnFrontConnected
//        {
//            add { frontConnected += value; regOnFrontConnected(TdSpi_, frontConnected); }
//            remove { frontConnected -= value; regOnFrontConnected(TdSpi_, frontConnected); }
//        }

//        #endregion

//        #region 断开应答

//        FrontDisconnected frontDisconnected;

//        /// <summary>
//        /// 断开应答委托
//        /// </summary>
//        public delegate void FrontDisconnected(int nReason);

//        /// <summary>
//        /// 断开应答
//        /// </summary>
//        public event FrontDisconnected OnFrontDisconnected
//        {
//            add { frontDisconnected += value; regOnFrontDisconnected(TdSpi_, frontDisconnected); }
//            remove { frontDisconnected -= value; regOnFrontDisconnected(TdSpi_, frontDisconnected); }
//        }

//        #endregion

//        #region 登入请求应答

//        RspUserLogin rspUserLogin;

//        /// <summary>
//        /// 登入请求应答委托
//        /// </summary>
//        public delegate void RspUserLogin(ref CThostFtdcRspUserLoginField pRspUserLogin, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);

//        /// <summary>
//        /// 登入请求应答
//        /// </summary>
//        public event RspUserLogin OnRspUserLogin
//        {
//            add { rspUserLogin += value; regOnRspUserLogin(TdSpi_, rspUserLogin); }
//            remove { rspUserLogin -= value; regOnRspUserLogin(TdSpi_, rspUserLogin); }
//        }

//        #endregion

//        #region 登出请求应答

//        RspUserLogout rspUserLogout;

//        /// <summary>
//        /// 登出请求应答委托
//        /// </summary>
//        /// <param name="pUserLogout">用户登出请求</param>
//        /// <param name="pRspInfo">响应信息</param>
//        /// <param name="nRequestID">请求编号</param>
//        /// <param name="bIsLast">是否为最后一条数据</param>
//        public delegate void RspUserLogout(ref CThostFtdcUserLogoutField pUserLogout,
//            ref CThostFtdcRspInfoField pRspInfo, int nRequestID, byte bIsLast);

//        /// <summary>
//        /// 登出请求应答
//        /// </summary>
//        public event RspUserLogout OnRspUserLogout
//        {
//            add { rspUserLogout += value; regOnRspUserLogout(TdSpi_, rspUserLogout); }
//            remove { rspUserLogout -= value; regOnRspUserLogout(TdSpi_, rspUserLogout); }
//        }

//        #endregion

//        #region 订阅行情应答

//        RspSubMarketData rspSubMarketData;


//        public virtual void OnRspSubMarketData(ref CThostFtdcSpecificInstrumentField pSpecificInstrument, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
//        {

//        }

//        /// <summary>
//        /// 订阅行情应答
//        /// </summary>
//        public event RspSubMarketData OnRspSubMarketData
//        {
//            add { rspSubMarketData += value; regOnRspSubMarketData(TdSpi_, rspSubMarketData); }
//            remove { rspSubMarketData -= value; regOnRspSubMarketData(TdSpi_, rspSubMarketData); }
//        }

//        #endregion

//        #region 退订请求应答

//        RspUnSubMarketData rspUnSubMarketData;

//        /// <summary>
//        /// 退订请求应答委托
//        /// </summary>
//        /// <param name="pSpecificInstrument">指定合约</param>
//        /// <param name="pRspInfo">响应信息</param>
//        /// <param name="nRequestID">请求编号</param>
//        /// <param name="bIsLast">是否为最后一条数据</param>
//        public delegate void RspUnSubMarketData(ref CThostFtdcSpecificInstrumentField pSpecificInstrument,
//            ref CThostFtdcRspInfoField pRspInfo, int nRequestID, byte bIsLast);

//        /// <summary>
//        /// 退订请求应答
//        /// </summary>
//        public event RspUnSubMarketData OnRspUnSubMarketData
//        {
//            add { rspUnSubMarketData += value; regOnRspUnSubMarketData(TdSpi_, rspUnSubMarketData); }
//            remove { rspUnSubMarketData -= value; regOnRspUnSubMarketData(TdSpi_, rspUnSubMarketData); }
//        }

//        #endregion


//        #region 订阅Quote应答

//        RspSubForQuoteRsp rspSubForQuoteRsp;

//        /// <summary>
//        /// 订阅行情应答委托
//        /// </summary>
//        /// <param name="pSpecificInstrument">指定合约</param>
//        /// <param name="pRspInfo">应答信息</param>
//        /// <param name="nRequestID">请求编号</param>
//        /// <param name="bIsLast">是否为最后一条数据</param>
//        public delegate void RspSubForQuoteRsp(ref CThostFtdcSpecificInstrumentField pSpecificInstrument,
//            ref CThostFtdcRspInfoField pRspInfo, int nRequestID, byte bIsLast);

//        /// <summary>
//        /// 订阅行情应答
//        /// </summary>
//        public event RspSubForQuoteRsp OnRspSubForQuoteRsp
//        {
//            add { rspSubForQuoteRsp += value; regOnRspSubForQuoteRsp(TdSpi_, rspSubForQuoteRsp); }
//            remove { rspSubForQuoteRsp -= value; regOnRspSubForQuoteRsp(TdSpi_, rspSubForQuoteRsp); }
//        }

//        #endregion

//        #region 退订请求应答

//        RspUnSubForQuoteRsp rspUnSubForQuoteRsp;

//        /// <summary>
//        /// 退订请求应答委托
//        /// </summary>
//        /// <param name="pSpecificInstrument">指定合约</param>
//        /// <param name="pRspInfo">响应信息</param>
//        /// <param name="nRequestID">请求编号</param>
//        /// <param name="bIsLast">是否为最后一条数据</param>
//        public delegate void RspUnSubForQuoteRsp(ref CThostFtdcSpecificInstrumentField pSpecificInstrument, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, byte bIsLast);

//        /// <summary>
//        /// 退订请求应答
//        /// </summary>
//        public event RspUnSubForQuoteRsp OnRspUnSubForQuoteRsp
//        {
//            add { rspUnSubForQuoteRsp += value; regOnRspUnSubForQuoteRsp(TdSpi_, rspUnSubForQuoteRsp); }
//            remove { rspUnSubForQuoteRsp -= value; regOnRspUnSubForQuoteRsp(TdSpi_, rspUnSubForQuoteRsp); }
//        }

//        #endregion


//        #region 深度行情通知

//        RtnDepthMarketData rtnDepthMarketData;

//        /// <summary>
//        /// 深度行情通知委托
//        /// </summary>
//        /// <param name="pDepthMarketData">深度行情</param>
//        public delegate void RtnDepthMarketData(ref CThostFtdcDepthMarketDataField pDepthMarketData);

//        /// <summary>
//        /// 深度行情通知
//        /// </summary>
//        public event RtnDepthMarketData OnRtnDepthMarketData
//        {
//            add { rtnDepthMarketData += value; regOnRtnDepthMarketData(TdSpi_, rtnDepthMarketData); }
//            remove { rtnDepthMarketData -= value; regOnRtnDepthMarketData(TdSpi_, rtnDepthMarketData); }
//        }

//        #endregion

//        #region Quote通知

//        RtnForQuoteRsp rtnForQuoteRsp;

//        /// <summary>
//        /// Quote通知
//        /// </summary>
//        /// <param name="pQuoteRsp">QuoteRsp</param>
//        public delegate void RtnForQuoteRsp(ref CThostFtdcForQuoteRspField pQuoteRsp);

//        /// <summary>
//        ///
//        /// </summary>
//        public event RtnForQuoteRsp OnRtnForQuoteRsp
//        {
//            add { rtnForQuoteRsp += value; regOnRtnForQuoteRsp(TdSpi_, rtnForQuoteRsp); }
//            remove { rtnForQuoteRsp -= value; regOnRtnForQuoteRsp(TdSpi_, rtnForQuoteRsp); }
//        }

//        #endregion

//#endregion

    ///// <summary>
    //      /// 获取请求ID
    //      /// </summary>
    //      /// <returns></returns>
    //      private int         _GenRequestID()
    //      {
    //       return Interlocked.Increment(ref _requestID);
    //      }

    //      /// <summary>
    //      /// 添加回调方法
    //      /// </summary>
    //      /// <param name="callback">回调函数</param>
    //      /// <param name="requestID">请求编号</param>
    //      private int         _AddCallback(object callback, int requestID = 0)
    //      {
    //          if (requestID == 0)
    //          {
    //              requestID = _GenRequestID();
    //          }
    //          if (callback != null)
    //          {
    //              if (_dataCallbackDict.ContainsKey(requestID))
    //              {
    //                  object tmp;
    //                  _dataCallbackDict.TryRemove(requestID, out tmp);
    //              }
    //              _dataCallbackDict.TryAdd(requestID, callback);
    //          }
    //          return requestID;
    //      }

    //      /// <summary>
    //      /// 执行回调方法
    //      /// </summary>
    //      /// <param name="requestID">请求编号</param>
    //      /// <param name="dataResult">返回结果</param>
    //      private void        _InvokeCallback(int requestID, DataResult dataResult)
    //      {
    //          if (_dataCallbackDict.ContainsKey(requestID))
    //          {
    //              object callback;
    //              if (_dataCallbackDict.TryRemove(requestID, out callback))
    //              {
    //                  if (callback != null)
    //                  {
    //                      ((DataCallback)callback)(dataResult);
    //                  }
    //              }
    //          }
    //      }


#region Members

    /// <summary>
    /// 交易类句柄
    /// </summary>
    protected IntPtr ApiHandle_ = IntPtr.Zero;

    protected IntPtr SpiHandle_ = IntPtr.Zero; // C++ MdSpi Wrapper class


    protected ICtpMdSpi _MdSpi;


    protected string _BrokerID;
    protected string _UserID;
    protected string _Password;
    protected string _FrontAddress;

    /// <summary>
    /// 前置编号
    /// </summary>
    protected int _FrontID;

    /// <summary>
    /// 会话编号
    /// </summary>
    protected int _SessionID;

    /// <summary>
    /// 最大报单引用
    /// </summary>
    protected string _MaxOrderRef;

    private bool IsUsingUdp_;
    private bool IsMulticast_;

#endregion
}
}