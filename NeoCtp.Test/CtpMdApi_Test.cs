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
using FluentAssertions;
using NeoCtp.Enums;
using NUnit.Framework;
using NeoCtp.Imp;
using NeoCtp.Tests;
using NLog;
using NLog.Config;

namespace NeoCtp.Test
{
public class CtpMdApi_Test
{
    private ICtpMdApi client = null;


    [OneTimeSetUp]
    public async Task Setup()
    {
        ILogger defaultLogger = null;
        LogManager.Configuration = new XmlLoggingConfiguration("NLog.config");
        defaultLogger            = LogManager.GetCurrentClassLogger();

        /// connect
        client = new CtpMdApi(TestConstants.MdFrontAddr, TestConstants.BrokerID, TestConstants.UserID, TestConstants.Password, defaultLogger); // defaultLogger - can be null
        var connected = await client.ConnectAsync();
        connected.Should().BeTrue();

        var logined = await client.ReqUserLoginAsync();
        client.IsLogined.Should().BeTrue();


        Debug.WriteLine(client.Dump());
    }

    [OneTimeTearDown]
    public async Task TearDown()
    {
        await client.DisconnectAsync();

        client.ConnectionState.Should().Be(EConnectionState.Disconnected);
        Debug.WriteLine(client.Dump());
    }

    [Test]
    public async Task Reconnect_Test()
    {
        await client.DisconnectAsync();
        client.ConnectionState.Should().Be(EConnectionState.Disconnected);
        Debug.WriteLine(client.Dump());

        /// reconnect
        bool connected = await client.ConnectAsync();
        connected.Should().BeTrue();
        Debug.WriteLine(client.Dump());

        // wait some time for account info
        await Task.Delay(5000);
    }

#region User

    [Test]
    public async Task SubMarketDataAsync_Test()
    {
        List<string> instruments = new() { "rb2210", "hc2210" };

        var marketDataFields = new List<CThostFtdcDepthMarketDataField>();
        client.OnRtnDepthMarketDataEvent += (s, e) =>
        {
            marketDataFields.Add(e);
            Debug.WriteLine(e);
        };

        await client.SubMarketDataAsync(instruments.ToArray());
        //await client.SubMarketDataAsync(instruments.ToArray());

        client.Subscribed.Should().NotBeEmpty();
        marketDataFields.Should().NotBeEmpty();

        // cancel
        await client.UnSubMarketDataAsync(instruments.ToArray());
        client.Subscribed.Should().BeEmpty();
        await Task.Delay(5000);
    }

#endregion


    // /// <summary>
    //      /// 初始化测试用例
    //      /// </summary>
    //      //[ClassInitialize]
    //      public static void Connect(TestContext context)
    //      {
    //	_api = new CtpMdApi2();
    //          _api.Connect(_frontAddr, (ok) =>
    //          {
    //           if (ok)
    //           {
    //            _api.ReqUserLogin(_brokerID, _UserID, _password, (pRspInfo, pRspUserLogin) =>
    //            {
    //				if (pRspInfo.ErrorID != 0)
    //				{
    //					Trace.WriteLine($"OnRspUserLogin:{pRspInfo.ErrorMsg}");

    //					return;
    //				}


    //				Trace.WriteLine("");
    //				Trace.WriteLine($"//-------OnRspUserLogin------");
    //				Trace.WriteLine($"BrockerID:	{pRspUserLogin.BrokerID}");
    //				Trace.WriteLine($"UserId:		{pRspUserLogin.UserID}");
    //				Trace.WriteLine("");
    //				Trace.WriteLine($"TradingDay:	{pRspUserLogin.TradingDay}");
    //				Trace.WriteLine($"LoginTime:	{pRspUserLogin.LoginTime}");
    //				Trace.WriteLine($"SystemName:	{pRspUserLogin.SystemName}");
    //				Trace.WriteLine($"FrontId:	{pRspUserLogin.FrontID}");
    //				Trace.WriteLine($"SessionId:	{pRspUserLogin.SessionID}");
    //				Trace.WriteLine($"MaxOrderRef:{pRspUserLogin.MaxOrderRef}");
    //				Trace.WriteLine($"SHFETime:	{pRspUserLogin.SHFETime}");
    //				Trace.WriteLine($"DCETime:	{pRspUserLogin.DCETime}");
    //				Trace.WriteLine($"CZCETime:	{pRspUserLogin.CZCETime}");
    //				Trace.WriteLine($"FFEXTime:	{pRspUserLogin.FFEXTime}");
    //				Trace.WriteLine($"INETime:	{pRspUserLogin.INETime}");
    //				Trace.WriteLine($"-------OnRspUserLogin------//");
    //				Trace.WriteLine("");


    //				_api.SubMarketData(_subDatas.ToArray());

    //            });
    //           }

    //          });

    //          _api.RspSubMarketData+=(pSpecificInstrument, pRspInfo, islast)=>
    //          {

    //		if (pRspInfo.ErrorID == 0)
    //		{
    //			Trace.WriteLine($"订阅{pSpecificInstrument.InstrumentID}成功");
    //			//Assert.AreEqual(instrumentID, pSpecificInstrument.InstrumentID);
    //		}
    //		else
    //		{
    //			Trace.WriteLine($"订阅{pSpecificInstrument.InstrumentID}失败");
    //		}
    //          }
    //          ;
    //	_api.RspUnSubMarketData+=(pSpecificInstrument, pRspInfo, islast)=>
    //          {

    //		if (pRspInfo.ErrorID == 0)
    //		{
    //			Trace.WriteLine($"退订{pSpecificInstrument.InstrumentID}成功");
    //			//Assert.AreEqual(instrumentID, pSpecificInstrument.InstrumentID);
    //		}
    //		else
    //		{
    //			Trace.WriteLine($"退订{pSpecificInstrument.InstrumentID}失败");
    //		}
    //          }
    //          ;

    //          _api.DepthMarketDataChanged += (pDepthMarketData) =>
    //          {

    //		Trace.WriteLine("");
    //              Trace.WriteLine($"//-------OnRtnDepthMarketData------");
    //              Trace.WriteLine($"TradingDay Time:{pDepthMarketData.TradingDay} {pDepthMarketData.UpdateTime} {pDepthMarketData.UpdateMillisec}ms");
    //              Trace.WriteLine($"InstrumentID:	{pDepthMarketData.InstrumentID}");
    //              Trace.WriteLine($"ExchangeID:		{pDepthMarketData.ExchangeID}");
    //              Trace.WriteLine($"ExchangeInstID:	{pDepthMarketData.ExchangeInstID}");
    //		Trace.WriteLine("");
    //              Trace.WriteLine($"OHLC:			({pDepthMarketData.OpenPrice}, {pDepthMarketData.HighestPrice}, {pDepthMarketData.LowestPrice}, {pDepthMarketData.LastPrice})");
    //              Trace.WriteLine($"Volume:			{pDepthMarketData.Volume}");
    //              Trace.WriteLine($"Turnover:		{pDepthMarketData.Turnover}");
    //		Trace.WriteLine("");

    //              Trace.WriteLine($"Bid1:		{pDepthMarketData.BidPrice1}({pDepthMarketData.BidVolume1}) <-> {pDepthMarketData.AskPrice1}({pDepthMarketData.AskVolume1})  Ask1");
    //              Trace.WriteLine($"Bid2:		{pDepthMarketData.BidPrice2}({pDepthMarketData.BidVolume2}) <-> {pDepthMarketData.AskPrice2}({pDepthMarketData.AskVolume2})  Ask2");
    //              Trace.WriteLine($"Bid3:		{pDepthMarketData.BidPrice3}({pDepthMarketData.BidVolume3}) <-> {pDepthMarketData.AskPrice3}({pDepthMarketData.AskVolume3})  Ask3");
    //              Trace.WriteLine($"Bid4:		{pDepthMarketData.BidPrice4}({pDepthMarketData.BidVolume4}) <-> {pDepthMarketData.AskPrice4}({pDepthMarketData.AskVolume4})  Ask4");
    //              Trace.WriteLine($"Bid5:		{pDepthMarketData.BidPrice5}({pDepthMarketData.BidVolume5}) <-> {pDepthMarketData.AskPrice5}({pDepthMarketData.AskVolume5})  Ask5");
    //              Trace.WriteLine($"-------OnRtnDepthMarketData------//");
    //		Trace.WriteLine("");

    //          };
    //      }

    //static ICtpMdApi2 _api;
}
}