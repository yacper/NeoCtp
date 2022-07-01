using System;
using System.Diagnostics;
using System.Threading;
using NeoCtp;
using NUnit.Framework;

namespace SharpCtp.Test
{
	//[TestClass()]
    public class CtpMdApiTest
    {
		public class TestCtpMdSpi : ICtpMdSpi
		{
			public void		OnFrontConnected()
			{
				CThostFtdcReqUserLoginField f = new CThostFtdcReqUserLoginField()
				{
                    BrokerID = _brokerID,
                    UserID = _UserID,
                    Password = _password
				};
				_apiBase.ReqUserLogin(ref f, 1);
			}

			public void		OnFrontDisconnected(int nReason)
			{
				Trace.WriteLine($"OnFrontDisconnected Error:{CtpHelper.GetError(nReason)?.prompt}");
			}

			public void		OnRspError(ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
			{
				Trace.WriteLine($"OnRspError:{pRspInfo.ErrorMsg}");
			}

			public void		OnHeartBeatWarning(int nTimeLapse)
			{
				Trace.WriteLine($"OnHeartBeatWarning: timeLapse {nTimeLapse}");
			}

			public void		OnRspUserLogin(ref CThostFtdcRspUserLoginField pRspUserLogin, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
			{
				if (pRspInfo.ErrorID != 0)
				{
					Trace.WriteLine($"OnRspUserLogin:{pRspInfo.ErrorMsg}");

					return;
				}


				Trace.WriteLine("");
                Trace.WriteLine($"//-------OnRspUserLogin------");
                Trace.WriteLine($"BrockerID:	{pRspUserLogin.BrokerID}");
                Trace.WriteLine($"UserId:		{pRspUserLogin.UserID}");
				Trace.WriteLine("");
                Trace.WriteLine($"TradingDay:	{pRspUserLogin.TradingDay}");
                Trace.WriteLine($"LoginTime:	{pRspUserLogin.LoginTime}");
                Trace.WriteLine($"SystemName:	{pRspUserLogin.SystemName}");
                Trace.WriteLine($"FrontID:	{pRspUserLogin.FrontID}");
                Trace.WriteLine($"SessionID:	{pRspUserLogin.SessionID}");
                Trace.WriteLine($"MaxOrderRef:{pRspUserLogin.MaxOrderRef}");
                Trace.WriteLine($"SHFETime:	{pRspUserLogin.SHFETime}");
                Trace.WriteLine($"DCETime:	{pRspUserLogin.DCETime}");
                Trace.WriteLine($"CZCETime:	{pRspUserLogin.CZCETime}");
                Trace.WriteLine($"FFEXTime:	{pRspUserLogin.FFEXTime}");
                Trace.WriteLine($"INETime:	{pRspUserLogin.INETime}");
                Trace.WriteLine($"-------OnRspUserLogin------//");
				Trace.WriteLine("");


				//string instrumentID = "au2012";
				string instrumentID = "1";
                int a = _apiBase.SubscribeMarketData(instrumentID);

			}

			public void		OnRspUserLogout(ref CThostFtdcUserLogoutField pUserLogout, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
			{
				Trace.WriteLine($"OnRspUserLogout:{pRspInfo.ErrorMsg}");
			}

			public void		OnRspQryMulticastInstrument(ref CThostFtdcMulticastInstrumentField pMulticastInstrument, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
			{
				throw new NotImplementedException();
			}

			public void OnRspSubMarketData(ref CThostFtdcSpecificInstrumentField pSpecificInstrument, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
			{
				if (pRspInfo.ErrorID == 0)
				{
					Trace.WriteLine($"订阅{pSpecificInstrument.InstrumentID}成功");
					//Assert.AreEqual(instrumentID, pSpecificInstrument.InstrumentID);

					//退订行情
					//_apiBase.UnsubscribeMarketData(instrumentID);
					//Thread.Sleep(50);
				}
				else
				{

				}
			}

			public void		OnRspUnSubMarketData(ref CThostFtdcSpecificInstrumentField pSpecificInstrument, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
			{
				if (pRspInfo.ErrorID == 0)
				{
					Trace.WriteLine($"退订{pSpecificInstrument.InstrumentID}成功");
					//Assert.AreEqual(instrumentID, pSpecificInstrument.InstrumentID);

					//退订行情
					//_apiBase.UnsubscribeMarketData(instrumentID);
					//Thread.Sleep(50);
				}
				else
				{

				}
			}

			public void OnRspSubForQuoteRsp(ref CThostFtdcSpecificInstrumentField pSpecificInstrument, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
			{
				if (pRspInfo.ErrorID == 0)
				{
					Trace.WriteLine($"订阅Quote成功: {pSpecificInstrument.InstrumentID}");
					//Assert.AreEqual(instrumentID, pSpecificInstrument.InstrumentID);

					//退订行情
					//_apiBase.UnsubscribeMarketData(instrumentID);
					//Thread.Sleep(50);
				}
				else
				{

				}
			}

			public void OnRspUnSubForQuoteRsp(ref CThostFtdcSpecificInstrumentField pSpecificInstrument, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
			{
				if (pRspInfo.ErrorID == 0)
				{
					Trace.WriteLine($"退订Quote成功: {pSpecificInstrument.InstrumentID}");
					//Assert.AreEqual(instrumentID, pSpecificInstrument.InstrumentID);

					//退订行情
					//_apiBase.UnsubscribeMarketData(instrumentID);
					//Thread.Sleep(50);
				}
				else
				{

				}
			}

			public void OnRtnDepthMarketData(ref CThostFtdcDepthMarketDataField pDepthMarketData)
			{
				//Console.WriteLine($"{pDepthMarketData.InstrumentID} 昨收价：{pDepthMarketData.PreClosePrice}，现价：{pDepthMarketData.LastPrice}");

				Trace.WriteLine("");
                Trace.WriteLine($"//-------OnRtnDepthMarketData------");
                Trace.WriteLine($"TradingDay Time:{pDepthMarketData.TradingDay} {pDepthMarketData.UpdateTime} {pDepthMarketData.UpdateMillisec}ms");
                Trace.WriteLine($"InstrumentID:	{pDepthMarketData.InstrumentID}");
                Trace.WriteLine($"ExchangeID:		{pDepthMarketData.ExchangeID}");
                Trace.WriteLine($"ExchangeInstID:	{pDepthMarketData.ExchangeInstID}");
				Trace.WriteLine("");
                Trace.WriteLine($"OHLC:			({pDepthMarketData.OpenPrice}, {pDepthMarketData.HighestPrice}, {pDepthMarketData.LowestPrice}, {pDepthMarketData.LastPrice})");
                Trace.WriteLine($"Volume:			{pDepthMarketData.Volume}");
                Trace.WriteLine($"Turnover:		{pDepthMarketData.Turnover}");
				Trace.WriteLine("");

                Trace.WriteLine($"Bid1:		{pDepthMarketData.BidPrice1}({pDepthMarketData.BidVolume1}) <-> {pDepthMarketData.AskPrice1}({pDepthMarketData.AskVolume1})  Ask1");
                Trace.WriteLine($"Bid2:		{pDepthMarketData.BidPrice2}({pDepthMarketData.BidVolume2}) <-> {pDepthMarketData.AskPrice2}({pDepthMarketData.AskVolume2})  Ask2");
                Trace.WriteLine($"Bid3:		{pDepthMarketData.BidPrice3}({pDepthMarketData.BidVolume3}) <-> {pDepthMarketData.AskPrice3}({pDepthMarketData.AskVolume3})  Ask3");
                Trace.WriteLine($"Bid4:		{pDepthMarketData.BidPrice4}({pDepthMarketData.BidVolume4}) <-> {pDepthMarketData.AskPrice4}({pDepthMarketData.AskVolume4})  Ask4");
                Trace.WriteLine($"Bid5:		{pDepthMarketData.BidPrice5}({pDepthMarketData.BidVolume5}) <-> {pDepthMarketData.AskPrice5}({pDepthMarketData.AskVolume5})  Ask5");
                Trace.WriteLine($"-------OnRtnDepthMarketData------//");
				Trace.WriteLine("");
			}

			public void OnRtnForQuoteRsp(ref CThostFtdcForQuoteRspField pForQuoteRsp)
			{
				throw new NotImplementedException();
			}
		}


		/// <summary>
		/// 行情接口实例
		/// </summary>
		private static ICtpMdApiBase _apiBase;
        private static ICtpMdSpi _spi;

        /// <summary>
        /// 连接地址
        /// </summary>
        //private static string _frontAddr = "tcp://180.168.146.187:10131";
        private static string _frontAddr = "tcp://180.168.146.187:10110";

        /// <summary>
        /// 经纪商代码
        /// </summary>
        private static string _brokerID = "9999";

        /// <summary>
        /// 投资者账号
        /// </summary>
        private static string _UserID = "097266";

        /// <summary>
        /// 密码
        /// </summary>
        private static string _password = "hello@123";

        /// <summary>
        /// 是否连接
        /// </summary>
        private bool _isConnected;

        /// <summary>
        /// 是否登录
        /// </summary>
        private bool _isLogin;

        /// <summary>
        /// 初始化测试用例
        /// </summary>
        public static void Initialize(TestContext context)
        {
			_apiBase = new CtpMdApiBase();
            _spi = new TestCtpMdSpi();
            _apiBase.RegisterSpi(_spi);
            _apiBase.RegisterFront(_frontAddr);
            _apiBase.Init();

			Thread.Sleep(2000);
		}


        /// <summary>
        /// 清理测试用例
        /// </summary>
        public static void Cleanup()
        {
            //if (_isLogin)
            //{
            //    _apiBase.UserLogout(-4);
            //}
            //else if (_isConnected)
            //{
            //    _apiBase.Disconnect();
            //}
            //Thread.Sleep(100);
        }

        /// <summary>
        /// 测试获取接口版本
        /// </summary>
        [Test]
        public void TestGetApiVersion()
        {
            string result = CtpMdApiBase.GetApiVersion();
            Assert.IsTrue(!string.IsNullOrEmpty(result));
        }

        /// <summary>
        /// 测试获取交易日
        /// </summary>
        [Test]
        public void TestGetTradingDay()
        {
			string result = _apiBase.GetTradingDay();
			Assert.AreEqual(8, result.Length);
		}

        /// <summary>
        /// 测试订阅行情
        /// </summary>
        //[TestMethod]
        public void TestSubscribeMarketData()
        {
			string instrumentID = "au2012";
			//_apiBase.OnRspSubMarketData += new MarketApi.RspSubMarketData((ref CThostFtdcSpecificInstrumentField pSpecificInstrument,
			//ref CThostFtdcRspInfoField pRspInfo, int nRequestID, byte bIsLast) =>
			//{
			//	Console.WriteLine("订阅{0}成功", instrumentID);
			//	Assert.AreEqual(instrumentID, pSpecificInstrument.InstrumentID);

			//	//退订行情
			//	_apiBase.UnsubscribeMarketData(instrumentID);
			//	Thread.Sleep(50);
			//});
			//_apiBase.OnRspUnSubMarketData += new MarketApi.RspUnSubMarketData((ref CThostFtdcSpecificInstrumentField pSpecificInstrument,
			//ref CThostFtdcRspInfoField pRspInfo, int nRequestID, byte bIsLast) =>
			//{
			//	Console.WriteLine("退订{0}成功", instrumentID);
			//	Assert.AreEqual(instrumentID, pSpecificInstrument.InstrumentID);
			//});

			//_apiBase.OnRtnDepthMarketData += new MarketApi.RtnDepthMarketData((ref CThostFtdcDepthMarketDataField pDepthMarketData) =>
			//{
			//	Console.WriteLine("昨收价：{0}，现价：{1}", pDepthMarketData.PreClosePrice, pDepthMarketData.LastPrice);
			//	Assert.AreEqual(instrumentID, pDepthMarketData.InstrumentID);
			//});

			//订阅行情
			_apiBase.SubscribeMarketData(instrumentID);
			//Thread.Sleep(2000);

        }

        [Test]
        public void TestSubscribeQuote()
        {
			//Thread.Sleep(10000);

	  //      return;

	        _apiBase.Join();

			Assert.AreEqual(2, 2);
        }
    }
		
}
