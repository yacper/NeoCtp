/********************************************************************
    created:	2020-09-27 22:16:54
    author:		joshua
    email:		
	
    purpose:	
*********************************************************************/
using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace NeoCtp.Imp
{
	public class CtpMdApi2 :CtpMdApi, ICtpMdSpi, ICtpMdApi2
	{
#region ICtpMdSpi
		public void OnFrontConnected()
		{
            IsConnected = true;
			((Action<bool>)_GetCallback(-1))?.Invoke(true);
		}

		public void OnFrontDisconnected(int nReason)
		{
            IsConnected = false;

			FrontDisconnected?.Invoke((EFrontDisconnectedReason)nReason);
		}


		public void OnRspError(ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{

		}

		public void OnHeartBeatWarning(int nTimeLapse)
		{

		}


		public void OnRspUserLogin(ref CThostFtdcRspUserLoginField pRspUserLogin, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			if (pRspInfo.ErrorID == 0)
			{
				IsLogined = true;
			}

			var callback = _GetCallback<Action<CThostFtdcRspInfoField, CThostFtdcRspUserLoginField>>(-3);		// 注意：该nRequestID经实测，和发送时候的值不同，返回永远是0
			callback?.Invoke(pRspInfo, pRspUserLogin);
		}

		public void OnRspUserLogout(ref CThostFtdcUserLogoutField pUserLogout, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			if (pRspInfo.ErrorID == 0)
				IsLogined = false;

			var callback = _GetCallback<Action<CThostFtdcRspInfoField, CThostFtdcUserLogoutField>>(-4);
			callback?.Invoke(pRspInfo, pUserLogout);
		}


		public void OnRspQryMulticastInstrument(ref CThostFtdcMulticastInstrumentField pMulticastInstrument,
			ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{

		}


		public IEnumerable<string>	Subscribed
		{
			get { return _Subscribed.Keys.ToArray(); }
		}								// 订阅的

		public void OnRspSubMarketData(ref CThostFtdcSpecificInstrumentField pSpecificInstrument,
			ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			if (pRspInfo.ErrorID == 0)
			{
				_Subscribed.TryAdd(pSpecificInstrument.InstrumentID, null);
				RaisePropertyChanged("Subscribed");
			}

			RspSubMarketData?.Invoke(pSpecificInstrument, pRspInfo, bIsLast);
		}

		public void OnRspUnSubMarketData(ref CThostFtdcSpecificInstrumentField pSpecificInstrument,
			ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{

			if (pRspInfo.ErrorID == 0)
			{
				object o;
				_Subscribed.TryRemove(pSpecificInstrument.InstrumentID,out o);
				RaisePropertyChanged("Subscribed");
			}

			RspUnSubMarketData?.Invoke(pSpecificInstrument, pRspInfo, bIsLast);
		}


		public void OnRspSubForQuoteRsp(ref CThostFtdcSpecificInstrumentField pSpecificInstrument,
			ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{

		}

		public void OnRspUnSubForQuoteRsp(ref CThostFtdcSpecificInstrumentField pSpecificInstrument,
			ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{

		}


		public void OnRtnDepthMarketData(ref CThostFtdcDepthMarketDataField pDepthMarketData)
		{
			
			//Trace.WriteLine(pDepthMarketData.ActionDay);
			DepthMarketDataChanged?.Invoke(pDepthMarketData);
		}

		public void OnRtnForQuoteRsp(ref CThostFtdcForQuoteRspField pForQuoteRsp)
		{

		}

#endregion



		public bool                IsConnected
        {
	        get { return _IsConnected; }

			protected set { Set("IsConnected", ref _IsConnected, value); }

        }


		public bool IsLogined
		{
			get
			{
				return _IsLogined;
			}

			protected set { Set("IsLogined", ref _IsLogined, value); }
		}


       

        public void			Connect(string frontAddr, Action<bool> callback)
        {
            RegisterSpi(this);

            RegisterFront(frontAddr);
            _AddCallback(callback, -1);
            this.Init();
        }

        public event Action<EFrontDisconnectedReason> FrontDisconnected;



		public ECtpRtn ReqUserLogin(string brokerID, string user, string psw, Action<CThostFtdcRspInfoField, CThostFtdcRspUserLoginField> callback)
		{
			CThostFtdcReqUserLoginField field = new CThostFtdcReqUserLoginField()
			{
				BrokerID = brokerID,
				UserID = user,
				Password = psw
			};


			ECtpRtn ret = (ECtpRtn)ReqUserLogin(ref field, -3);

			if (ret != ECtpRtn.Sucess)
				return ret;

			_AddCallback(callback, -3);

			return ret;
		}

		public ECtpRtn ReqUserLogout(Action<CThostFtdcRspInfoField, CThostFtdcUserLogoutField> callback)
		{
			CThostFtdcUserLogoutField filed = new CThostFtdcUserLogoutField()
			{
				BrokerID = BrokerID,
				UserID = UserID
			};

			ECtpRtn ret = (ECtpRtn) ReqUserLogout(ref filed, -4);

			if (ret != ECtpRtn.Sucess)
				return ret;

			_AddCallback(callback, -4);

			return ret;
		}


		public ECtpRtn SubMarketData(params string[] instruments)
		{
			return (ECtpRtn) SubscribeMarketData(instruments);
		}
        public event Action<CThostFtdcSpecificInstrumentField, CThostFtdcRspInfoField, bool> RspSubMarketData;

        public ECtpRtn UnSubMarketData(params string[] instruments)
        {
			return (ECtpRtn) UnSubscribeMarketData(instruments);
        }
        public event Action<CThostFtdcSpecificInstrumentField, CThostFtdcRspInfoField, bool> RspUnSubMarketData;



        public event Action<CThostFtdcDepthMarketDataField> DepthMarketDataChanged;


		protected int		_GenReqId()
		{
			return Interlocked.Increment(ref _RequestID);
		}

#region 回调方法

        /// <summary>
        /// 添加回调方法
        /// </summary>
        /// <param name="callback">回调函数</param>
        /// <param name="requestID">请求编号</param>
        private int _AddCallback(object callback, int requestID = 0)
        {
            if (requestID == 0)
            {
                requestID = _GenReqId();
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


		#region Members
        private ConcurrentDictionary<int, object> _dataCallbackDict = new ConcurrentDictionary<int, object>();

		protected ConcurrentDictionary<string, object> _Subscribed = new ConcurrentDictionary<string, object>();

		protected bool _IsLogined;
		protected bool _IsConnected;

		protected int _RequestID;

		#endregion
	}

	
}
