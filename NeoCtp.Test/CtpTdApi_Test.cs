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

namespace NeoCtp.Test;
public class CtpTdApi_Test
{
    private ICtpTdApi client = null;


    [OneTimeSetUp]
    public async Task Setup()
    {
        ILogger defaultLogger = null;
        //LogManager.Configuration = new XmlLoggingConfiguration("NLog.config");
        //defaultLogger            = LogManager.GetCurrentClassLogger();

        /// connect
        client = new CtpTdApi(TestConstants.GetTdFrontAddr(), TestConstants.BrokerID, TestConstants.UserID, TestConstants.Password, defaultLogger); // defaultLogger - can be null
        var connected = await client.ConnectAsync();
        connected.Should().BeTrue();

        // login
        var logined = await client.ReqUserLoginAsync();
        client.IsLogined.Should().BeTrue();
        Debug.WriteLine(client.Dump());


        // SettlementInfoConfirm 使用simnow测试账户无此功能
        var confirm = await client.ReqSettlementInfoConfirmAsync();
        confirm.Rsp2.InvestorID.Should().Be(TestConstants.UserID);

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
        await client.ReqUserLogoutAsync();
        client.IsLogined.Should().Be(false);
        Debug.WriteLine(client.Dump());


        await client.DisconnectAsync();
        client.ConnectionState.Should().Be(EConnectionState.Disconnected);
        Debug.WriteLine(client.Dump());

        /// reconnect
        bool connected = await client.ConnectAsync();
        connected.Should().BeTrue();
        Debug.WriteLine(client.Dump());

       // login
        var logined = await client.ReqUserLoginAsync();
        client.IsLogined.Should().BeTrue();
        Debug.WriteLine(client.Dump());


        // SettlementInfoConfirm 使用simnow测试账户无此功能
        var confirm = await client.ReqSettlementInfoConfirmAsync();
        confirm.Rsp2.InvestorID.Should().Be(TestConstants.UserID);
    }

#region Account
    [Test]
    public async Task ReqQryTradingAccountAsync_Test()
    {
        var acc = await client.ReqQryTradingAccountAsync();
        acc.Rsp2.Should().NotBeNull();

        Debug.WriteLine(acc.Dump());
    }

    [Test]
    public async Task ReqQryInstrumentAsync_Test()
    {
        var ins = "rb2210";
        var acc = await client.ReqQryInstrumentAsync(ins);
        acc.Rsp2.Should().NotBeNull();

        Debug.WriteLine(acc.Dump());
    }




    [Test]
    public async Task ReqQryInvestorPositionAsync_Test()
    {
        var acc = await client.ReqQryInvestorPositionAsync("rb2210");
        //.acc.Rsp2.Should().n

        Debug.WriteLine(acc.Dump());

    }

    [Test]
    public async Task ReqQryOrderAsync_Test()
    {
        CThostFtdcQryOrderField field = new();
        var                     acc   = await client.ReqQryOrderAsync(field);
        //.acc.Rsp2.Should().n

        Debug.WriteLine(acc.Dump());
    }

    [Test]
    public async Task ReqQryTradeAsync_Test()
    {
        CThostFtdcQryTradeField field = new();
        var                     acc   = await client.ReqQryTradeAsync(field);
        //.acc.Rsp2.Should().n

        Debug.WriteLine(acc.Dump());
    }






    [Test]
    public async Task ReqOrderInsertAsync_Test()
    {
        CThostFtdcInputOrderField field = new CThostFtdcInputOrderField()
        {
            InstrumentID   = "rb2210",
            CombOffsetFlag = TThostFtdcOffsetFlagType.Open,

            LimitPrice          = 4200,
            VolumeTotalOriginal = 1,
            Direction           = TThostFtdcDirectionType.Buy,
            TimeCondition       = TThostFtdcTimeConditionType.GFD, //当日有效

            OrderPriceType      = TThostFtdcOrderPriceTypeType.LimitPrice,       // 默认限价
            VolumeCondition     = TThostFtdcVolumeConditionType.AV,              // 任何数量
            MinVolume           = 1,                                             // 最小成交量1
            ContingentCondition = TThostFtdcContingentConditionType.Immediately, // 触发条件：立即
            ForceCloseReason    = TThostFtdcForceCloseReasonType.NotForceClose,  // 强平原因：非强平
            IsAutoSuspend       = 0,                                             // 自动挂起标志：否
            UserForceClose      = 0,                                             // 用户强平标志：否

            CombHedgeFlag = TThostFtdcHedgeFlagType.Speculation
        };


        var acc = await client.ReqOrderInsertAsync(field);
        //.acc.Rsp2.Should().n

        Debug.WriteLine(acc.Dump());

    }

    [Test]
    public async Task ReqOrderActionAsync_Test()
    {
        CThostFtdcInputOrderActionField field = new CThostFtdcInputOrderActionField()
        {
            InstrumentID   = "rb2210",
            //OrderRef = 
            ActionFlag = TThostFtdcActionFlagType.Delete
        };


        var acc = await client.ReqOrderActionAsync(field);
        //.acc.Rsp2.Should().n

        Debug.WriteLine(acc.Dump());

    }




     //[Test]
    //public async Task SubMarketDataAsync_Test()
    //{
    //    List<string> instruments = new() { "rb2210", "hc2210" };

    //    var marketDataFields = new List<CThostFtdcDepthMarketDataField>();
    //    client.OnRtnDepthMarketDataEvent += (s, e) =>
    //    {
    //        marketDataFields.Add(e);
    //        Debug.WriteLine(e);
    //    };

    //    await client.SubMarketDataAsync(instruments.ToArray());
    //    //await client.SubMarketDataAsync(instruments.ToArray());

    //    client.Subscribed.Should().NotBeEmpty();
    //    marketDataFields.Should().NotBeEmpty();

    //    // cancel
    //    await client.UnSubMarketDataAsync(instruments.ToArray());
    //    client.Subscribed.Should().BeEmpty();
    //    await Task.Delay(5000);
    //}

#endregion
}