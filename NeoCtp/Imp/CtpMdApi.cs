﻿/********************************************************************
    created:	2020-09-27 22:16:54
    author:		rush
    email:		
	
    purpose:	
*********************************************************************/

using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using MoreLinq;
using NeoCtp.Api;
using NeoCtp.Enums;
using NeoCtp.Exceptions;
using NLog;

namespace NeoCtp.Imp
{
public class CtpMdApi : CtpMdApiBase, ICtpMdSpi, ICtpMdApi
{
#region ICtpMdSpi

    public void OnFrontConnected()
    {
        OnFrontConnectedEvent?.Invoke(this, null);
        //         IsConnected = true;
        //((Action<bool>)_GetCallback(-1))?.Invoke(true);
    }

    private event EventHandler OnFrontConnectedEvent;

    public void OnFrontDisconnected(int nReason)
    {
        ConnectionState = EConnectionState.Disconnected;

        OnFrontDisconnectedEvent?.Invoke(this, (EFrontDisconnectedReason)nReason);
    }

    public event EventHandler<CtpRsp> OnRspErrorEvent;

    public void OnRspError(ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast) { OnRspErrorEvent?.Invoke(this, new CtpRsp(pRspInfo, nRequestID, bIsLast)); }

    public event EventHandler<int> OnHeartBeatWarningEvent;
    public void                    OnHeartBeatWarning(int nTimeLapse) { OnHeartBeatWarningEvent?.Invoke(this, nTimeLapse); }

    public event EventHandler<CtpRsp<CThostFtdcRspUserLoginField>> OnRspUserLoginEvent;

    public void OnRspUserLogin(ref CThostFtdcRspUserLoginField pRspUserLogin, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
    {
        OnRspUserLoginEvent?.Invoke(this, new(pRspUserLogin, pRspInfo, nRequestID, bIsLast));
    }

    public event EventHandler<CtpRsp<CThostFtdcUserLogoutField>> OnRspUserLogoutEvent;

    public void OnRspUserLogout(ref CThostFtdcUserLogoutField pUserLogout, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
    {
        OnRspUserLogoutEvent?.Invoke(this, new(pUserLogout, pRspInfo, nRequestID, bIsLast));
    }

    public event EventHandler<CtpRsp<CThostFtdcSpecificInstrumentField>> OnRspSubMarketDataEvent;

    public void OnRspSubMarketData(ref CThostFtdcSpecificInstrumentField pSpecificInstrument,
        ref                            CThostFtdcRspInfoField            pRspInfo, int nRequestID, bool bIsLast)
    {
        OnRspSubMarketDataEvent?.Invoke(this, new(pSpecificInstrument, pRspInfo, nRequestID, bIsLast));
    }

    public event EventHandler<CtpRsp<CThostFtdcSpecificInstrumentField>> OnRspUnSubMarketDataEvent;

    public void OnRspUnSubMarketData(ref CThostFtdcSpecificInstrumentField pSpecificInstrument,
        ref                              CThostFtdcRspInfoField            pRspInfo, int nRequestID, bool bIsLast)
    {
        OnRspUnSubMarketDataEvent?.Invoke(this, new(pSpecificInstrument, pRspInfo, nRequestID, bIsLast));
    }

    public void OnRtnDepthMarketData(ref CThostFtdcDepthMarketDataField pDepthMarketData) { OnRtnDepthMarketDataEvent?.Invoke(this, pDepthMarketData); }


    public void OnRspSubForQuoteRsp(ref CThostFtdcSpecificInstrumentField pSpecificInstrument,
        ref                             CThostFtdcRspInfoField            pRspInfo, int nRequestID, bool bIsLast)
    {
    }

    public void OnRspUnSubForQuoteRsp(ref CThostFtdcSpecificInstrumentField pSpecificInstrument,
        ref                               CThostFtdcRspInfoField            pRspInfo, int nRequestID, bool bIsLast)
    {
    }

    public void OnRtnForQuoteRsp(ref CThostFtdcForQuoteRspField pForQuoteRsp) { }

    public void OnRspQryMulticastInstrument(ref CThostFtdcMulticastInstrumentField pMulticastInstrument,
        ref                                     CThostFtdcRspInfoField             pRspInfo, int nRequestID, bool bIsLast)
    {
    }

#endregion


    public CtpMdApi(string frontAddress,            string brokerId,            string userId, string password, ILogger logger = null,
        string             pszFlowPath = "CtpFlow", bool   bIsUsingUdp = false, bool   bIsMulticast = false)
        : base(frontAddress, brokerId, userId, password,
               pszFlowPath, bIsUsingUdp, bIsMulticast)
    {
        Logger = logger;

        RegisterSpi(this);
        RegisterFront(FrontAddress);
    }

    public    EConnectionState ConnectionState { get => ConnectionState_; set => SetProperty(ref ConnectionState_, value); }
    protected EConnectionState ConnectionState_;

    //public bool                IsConnected
    //      {
    //       get { return _IsConnected; }

    //	protected set { SetProperty(ref _IsConnected, value); }

    //      }

    public ILogger Logger { get; protected set; }

    public bool IsLogined { get { return _IsLogined; } protected set { SetProperty(ref _IsLogined, value); } }


    public int TimeoutMilliseconds { get; set; } = 5000;


    string ICtpMdApi.GetApiVersion() => CtpMdApiBase.GetApiVersion();

    public Task<bool> ConnectAsync()
    {
        if (ConnectionState == EConnectionState.Connected)
            return Task.FromResult(true);

        ConnectionState = EConnectionState.Connecting;
        var taskSource = new TaskCompletionSource<bool>();

        EventHandler onFrontConnectedHandler = null;
        onFrontConnectedHandler = (s, e) =>
        {
            lock (Lock_)
            {
                if (ConnectionState == EConnectionState.Disconnected)
                    return;

                OnFrontConnectedEvent -= onFrontConnectedHandler;
                OnConnected_();
                taskSource.TrySetResult(true);
            }

        };

        CancellationTokenSource tokenSource = new CancellationTokenSource(TimeoutMilliseconds);
        tokenSource.Token.Register(() =>
        {
            lock (Lock_)
            {
                /// 超时失败
                OnFrontConnectedEvent -= onFrontConnectedHandler;

                if (ConnectionState == EConnectionState.Connecting)
                {
                    //todo: 待验证
                    Release();
                    ConnectionState = EConnectionState.Disconnected;
                }

                taskSource.TrySetCanceled();
            }
        });

        this.OnFrontConnectedEvent += onFrontConnectedHandler;

        Init();
        return taskSource.Task;
    }

    public Task DisconnectAsync()
    {
        if (ConnectionState != EConnectionState.Connected)
            return Task.CompletedTask;

        ConnectionState = EConnectionState.Disconnecting;

        var taskSource = new TaskCompletionSource();
        //EventHandler connectionClosedHandler = null;
        //connectionClosedHandler = (s, e) =>
        //{
        //    TwsCallbackHandler_.ConnectionClosedEvent -= connectionClosedHandler;

        //// Abort the reader thread
        //ThreadRunning_ = false;

        //    OnDisconnected();
        //    taskSource.TrySetResult();
        //};
        //this.TwsCallbackHandler_.ConnectionClosedEvent += connectionClosedHandler;

        //// Set the operation to cancel after 5 seconds
        //CancellationTokenSource tokenSource = new CancellationTokenSource(TimeoutMilliseconds);
        //tokenSource.Token.Register(() =>
        //{
        //    TwsCallbackHandler_.ConnectionClosedEvent -= connectionClosedHandler;
        //    taskSource.TrySetCanceled();
        //});

        //this.ClientSocket_.eDisconnect();

        return taskSource.Task;
    }


    protected void OnConnected_()
    {
        Logger?.Info($"Connected:{this.Dump()}");

        ConnectionState = EConnectionState.Connected;
    }

    protected void OnDisconnected()
    {
        Logger?.Info($"DisConnected:{this.Dump()}");

        //RealtimeBarsSubscriptions_.Clear();
        //RealtimeBarsSubscriptionReqs_.Clear();
        //TickByTickSubscriptionReqs_.Clear();
        //TickByTickSubscriptions_.Clear();
        //ReqContracts.Clear();

        ConnectionState = EConnectionState.Disconnected;
    }

    public event EventHandler<EFrontDisconnectedReason> OnFrontDisconnectedEvent;


    public Task<CtpRsp<CThostFtdcRspUserLoginField>> ReqUserLoginAsync()
    {
        var taskSource = new TaskCompletionSource<CtpRsp<CThostFtdcRspUserLoginField>>();
        var reqId      = GetNextRequestId();


        EventHandler<CtpRsp<CThostFtdcRspUserLoginField>> onRspUserLoginHandler = null;
        EventHandler<CtpRsp>                              onRspErrorHandler     = null;
        onRspUserLoginHandler = (s, e) =>
        {
            clearHandler();
            IsLogined = true;

            taskSource.TrySetResult(e);
        };
        onRspErrorHandler = (s, e) =>
        {
            if (e.RequestId == reqId)
            {
                clearHandler();

                taskSource.TrySetException(new CtpException(e));
            }
        };

        void clearHandler()
        {
            OnRspUserLoginEvent -= onRspUserLoginHandler;
            OnRspErrorEvent     -= onRspErrorHandler;
        }


        CThostFtdcReqUserLoginField field = new CThostFtdcReqUserLoginField()
        {
            BrokerID = BrokerId,
            UserID   = UserId,
            Password = Password
        };

        ECtpRtn ret = (ECtpRtn)ReqUserLogin(ref field, reqId);
        if (ret != ECtpRtn.Sucess) { taskSource.TrySetResult(new(ret)); }
        else
        {
            OnRspUserLoginEvent += onRspUserLoginHandler;
            OnRspErrorEvent     += onRspErrorHandler;

            CancellationTokenSource tokenSource = new CancellationTokenSource(TimeoutMilliseconds);
            tokenSource.Token.Register(() =>
            {
                clearHandler();
                taskSource.TrySetCanceled();
            });
        }

        return taskSource.Task;
    }

    public Task<CtpRsp<CThostFtdcUserLogoutField>> ReqUserLogoutAsync()
    {
        var taskSource = new TaskCompletionSource<CtpRsp<CThostFtdcUserLogoutField>>();
        var reqId      = GetNextRequestId();

        EventHandler<CtpRsp<CThostFtdcUserLogoutField>> onRspUserLogoutHandler = null;
        EventHandler<CtpRsp>                            onRspErrorHandler      = null;
        onRspUserLogoutHandler = (s, e) =>
        {
            clearHandler();
            IsLogined = false;

            taskSource.TrySetResult(e);
        };
        onRspErrorHandler = (s, e) =>
        {
            if (e.RequestId == reqId)
            {
                clearHandler();

                taskSource.TrySetException(new CtpException(e));
            }
        };

        void clearHandler()
        {
            OnRspUserLogoutEvent -= onRspUserLogoutHandler;
            OnRspErrorEvent      -= onRspErrorHandler;
        }

        CThostFtdcUserLogoutField field = new CThostFtdcUserLogoutField()
        {
            BrokerID = BrokerId,
            UserID   = UserId
        };

        ECtpRtn ret = (ECtpRtn)ReqUserLogout(ref field, reqId);
        if (ret != ECtpRtn.Sucess) { taskSource.TrySetResult(new(ret)); }
        else
        {
            OnRspUserLogoutEvent += onRspUserLogoutHandler;
            OnRspErrorEvent      += onRspErrorHandler;

            CancellationTokenSource tokenSource = new CancellationTokenSource(TimeoutMilliseconds);
            tokenSource.Token.Register(() =>
            {
                clearHandler();
                taskSource.TrySetCanceled();
            });
        }

        return taskSource.Task;
    }


    public ReadOnlyObservableCollection<string> Subscribed { get => new(Subscribed_); } // 订阅的

    public Task<CtpRsp<List<string>>> SubMarketDataAsync(params string[] instruments)
    {
        var                   taskSource     = new TaskCompletionSource<CtpRsp<List<string>>>();
        ConcurrentBag<string> instrumentsBag = new ConcurrentBag<string>();
        var                   reqId          = GetNextRequestId();

        EventHandler<CtpRsp<CThostFtdcSpecificInstrumentField>> onRspSubMarketDataHandler = null;
        EventHandler<CtpRsp>                                    onRspErrorHandler         = null;

        onRspSubMarketDataHandler = (s, e) =>
        {
            instrumentsBag.Add(e.Rsp2.InstrumentID);

            if (e.IsLast)
            {
                clearHandler();

                instrumentsBag.ForEach(p => Subscribed_.Add(p));
                taskSource.TrySetResult(new(instrumentsBag.ToList(), e.Rsp, e.RequestId, e.IsLast));
            }
        };
        onRspErrorHandler = (s, e) =>
        {
            if (e.RequestId == reqId)
            {
                clearHandler();

                taskSource.TrySetException(new CtpException(e));
            }
        };

        void clearHandler()
        {
            OnRspSubMarketDataEvent -= onRspSubMarketDataHandler;
            OnRspErrorEvent         -= onRspErrorHandler;
        }

        ECtpRtn ret = (ECtpRtn)SubscribeMarketData(instruments);
        if (ret != ECtpRtn.Sucess) { taskSource.TrySetResult(new(ret)); }
        else
        {
            OnRspSubMarketDataEvent += onRspSubMarketDataHandler;
            OnRspErrorEvent         += onRspErrorHandler;

            CancellationTokenSource tokenSource = new CancellationTokenSource(TimeoutMilliseconds);
            tokenSource.Token.Register(() =>
            {
                clearHandler();
                taskSource.TrySetCanceled();
            });
        }

        return taskSource.Task;
    }

    public Task<CtpRsp<List<string>>> UnSubMarketDataAsync(params string[] instruments)
    {
        var                   taskSource     = new TaskCompletionSource<CtpRsp<List<string>>>();
        ConcurrentBag<string> instrumentsBag = new ConcurrentBag<string>();
        var                   reqId          = GetNextRequestId();

        EventHandler<CtpRsp<CThostFtdcSpecificInstrumentField>> OnRspUnSubMarketDataEvent = null;
        EventHandler<CtpRsp>                                    onRspErrorHandler         = null;

        OnRspUnSubMarketDataEvent = (s, e) =>
        {
            instrumentsBag.Add(e.Rsp2.InstrumentID);

            if (e.IsLast)
            {
                clearHandler();

                instrumentsBag.ForEach(p => Subscribed_.Remove(p));
                taskSource.TrySetResult(new(instrumentsBag.ToList(), e.Rsp, e.RequestId, e.IsLast));
            }
        };
        onRspErrorHandler = (s, e) =>
        {
            if (e.RequestId == reqId)
            {
                clearHandler();

                taskSource.TrySetException(new CtpException(e));
            }
        };

        void clearHandler()
        {
            OnRspSubMarketDataEvent -= OnRspUnSubMarketDataEvent;
            OnRspErrorEvent         -= onRspErrorHandler;
        }

        ECtpRtn ret = (ECtpRtn)UnSubscribeMarketData(instruments);
        if (ret != ECtpRtn.Sucess) { taskSource.TrySetResult(new(ret)); }
        else
        {
            OnRspSubMarketDataEvent += OnRspUnSubMarketDataEvent;
            OnRspErrorEvent         += onRspErrorHandler;

            CancellationTokenSource tokenSource = new CancellationTokenSource(TimeoutMilliseconds);
            tokenSource.Token.Register(() =>
            {
                clearHandler();
                taskSource.TrySetCanceled();
            });
        }

        return taskSource.Task;
    }

    public event EventHandler<CThostFtdcDepthMarketDataField> OnRtnDepthMarketDataEvent;


#region 回调方法

    /// <summary>
    /// 添加回调方法
    /// </summary>
    /// <param name="callback">回调函数</param>
    /// <param name="requestID">请求编号</param>
    private int _AddCallback(object callback, int requestID = 0)
    {
        if (requestID == 0) { requestID = GetNextRequestId(); }

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

    private object _GetCallback(int requestID)
    {
        object callback;
        _dataCallbackDict.TryRemove(requestID, out callback);

        return callback;
    }

    private T _GetCallback<T>(int requestID)
    {
        object callback;
        _dataCallbackDict.TryRemove(requestID, out callback);

        return (T)callback;
    }

    //private void ExecuteCallback(int requestID, DataResult dataResult)
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

#endregion

    protected int GetNextRequestId() => Interlocked.Increment(ref _RequestID);

#region Members

    private ConcurrentDictionary<int, object> _dataCallbackDict = new ConcurrentDictionary<int, object>();

//		protected ConcurrentDictionary<string, object> _Subscribed = new ConcurrentDictionary<string, object>();

    protected ObservableCollection<string> Subscribed_ = new();

    protected bool _IsLogined;
    protected bool _IsConnected;

    protected int _RequestID = 0;

    protected object Lock_ = new object();

#endregion
}
}