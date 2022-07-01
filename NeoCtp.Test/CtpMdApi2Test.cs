/********************************************************************
    created:	2020-11-11 20:21:44
    author:		joshua
    email:		
	
    purpose:	
*********************************************************************/
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using NUnit.Framework;
using SharpCtp.Imp;

namespace SharpCtp.Test
{
	public class CtpMdApi2Test
	{
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

        private static List<string> _subDatas = new List<string>
        {
            "au2012",

        };

   /// <summary>
        /// 初始化测试用例
        /// </summary>
        //[ClassInitialize]
        public static void Connect(TestContext context)
        {
			_api = new CtpMdApi2();
            _api.Connect(_frontAddr, (ok) =>
            {
	            if (ok)
	            {
		            _api.ReqUserLogin(_brokerID, _UserID, _password, (pRspInfo, pRspUserLogin) =>
		            {
						if (pRspInfo.ErrorID != 0)
						{
							Trace.WriteLine($"OnRspUserLogin:{pRspInfo.ErrorMsg}");

							return;
						}


						Trace.WriteLine("");
						Trace.WriteLine($"//-------OnRspUserLogin------");
						Trace.WriteLine($"BrockerID:	{pRspUserLogin.BrokerID}");
						Trace.WriteLine($"UserID:		{pRspUserLogin.UserID}");
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




						_api.SubMarketData(_subDatas.ToArray());

		            });
	            }

            });

            _api.RspSubMarketData+=(pSpecificInstrument, pRspInfo, islast)=>
            {

				if (pRspInfo.ErrorID == 0)
				{
					Trace.WriteLine($"订阅{pSpecificInstrument.InstrumentID}成功");
					//Assert.AreEqual(instrumentID, pSpecificInstrument.InstrumentID);
				}
				else
				{
					Trace.WriteLine($"订阅{pSpecificInstrument.InstrumentID}失败");
				}
            }
            ;
			_api.RspUnSubMarketData+=(pSpecificInstrument, pRspInfo, islast)=>
            {

				if (pRspInfo.ErrorID == 0)
				{
					Trace.WriteLine($"退订{pSpecificInstrument.InstrumentID}成功");
					//Assert.AreEqual(instrumentID, pSpecificInstrument.InstrumentID);
				}
				else
				{
					Trace.WriteLine($"退订{pSpecificInstrument.InstrumentID}失败");
				}
            }
            ;

            _api.DepthMarketDataChanged += (pDepthMarketData) =>
            {

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

            };
        }

		static ICtpMdApi2 _api;
	}
}
