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
using Newtonsoft.Json;
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
    public async Task ReqQryTradingAccountAsync_Test()  // 查询账户资金
    {
        var acc = await client.ReqQryTradingAccountAsync();
        acc.Rsp2.Should().NotBeNull();

        Debug.WriteLine(acc.Rsp2.ToJson(Formatting.Indented));
    }
#endregion

#region Instrument 

    [Test]
    public async Task ReqQryInstrumentAsync_Test()
    {
        var ins = "rb2210";
        var acc = await client.ReqQryInstrumentAsync(ins);
        acc.Rsp2.ExchangeID.Should().Be("SHFE");

        Debug.WriteLine(acc.ToJson(Formatting.Indented));

        /*
    "InstrumentID": "rb2210",
    "ExchangeID": "SHFE",
    "InstrumentName": "rb2210",
    "ExchangeInstID": "rb2210",
    "ProductID": "rb",
    "ProductClass": "Futures",
    "DeliveryYear": 2022,
    "DeliveryMonth": 10,
    "MaxMarketOrderVolume": 30,
    "MinMarketOrderVolume": 1,
    "MaxLimitOrderVolume": 500,
    "MinLimitOrderVolume": 1,
    "VolumeMultiple": 10,
    "PriceTick": 1.0,
    "CreateDate": "20210913",
    "OpenDate": "20211018",
    "ExpireDate": "20221017",
    "StartDelivDate": "20221018",
    "EndDelivDate": "20221020",
    "InstLifePhase": "Started",
    "IsTrading": 1,
    "PositionType": "Gross",
    "PositionDateType": "UseHistory",
    "LongMarginRatio": 0.16,
    "ShortMarginRatio": 0.16,
    "MaxMarginSideAlgorithm": "YES",
    "UnderlyingInstrID": "rb",
    "StrikePrice": 0.0,
    "UnderlyingMultiple": 1.0
        */
    }
#endregion

#region position 
    [Test]
    public async Task ReqQryInvestorPositionAsync_Test()
    {
        var acc = await client.ReqQryInvestorPositionAsync("rb2210");
        //.acc.Rsp2.Should().n

        Debug.WriteLine(acc.Dump());
    }

    [Test]
    public async Task ReqQryInvestorPositionAsync_Test_All()
    {
        var acc = await client.ReqQryInvestorPositionAsync();
        //.acc.Rsp2.Should().n

        Debug.WriteLine("ReqQryInvestorPositionAsync " + acc.ToJson(Formatting.Indented));
    }

#endregion

#region Order

  [Test]
    public async Task ReqOrderInsertAsync_Test_LocalRejected()        // 输入订单, 本地校验失败
    {
        CThostFtdcInputOrderField field = new CThostFtdcInputOrderField()
        {
            InstrumentID   = "rb2110",
            CombOffsetFlag = TThostFtdcOffsetFlagType.Open,

            LimitPrice          = 5200,
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

        client.OnRtnOrderEvent += (s, e) =>
        {
            Debug.WriteLine("OnRtnOrderEvent " + e.ToJson(Formatting.Indented));
        };
        client.OnRtnTradeEvent += (s, e) =>
        {
            Debug.WriteLine("OnRtnTradeEvent " + e.ToJson(Formatting.Indented));
        };

        var acc = await client.ReqOrderInsertAsync(field);
        Debug.WriteLine("OrderInsert " + acc.ToJson(Formatting.Indented));

        await Task.Delay(10000);

    }

    [Test]
    public async Task ReqOrderInsertAsync_Test_ServerRejected()        // 输入订单，服务器校验失败
    {
        CThostFtdcInputOrderField field = new CThostFtdcInputOrderField()
        {
            InstrumentID   = "rb2210",
            CombOffsetFlag = TThostFtdcOffsetFlagType.Open,

            LimitPrice          = 5200,
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

        client.OnRtnOrderEvent += (s, e) =>
        {
            Debug.WriteLine("OnRtnOrderEvent " + e.ToJson(Formatting.Indented));
        };
        client.OnRtnTradeEvent += (s, e) =>
        {
            Debug.WriteLine("OnRtnTradeEvent " + e.ToJson(Formatting.Indented));
        };

        var acc = await client.ReqOrderInsertAsync(field);
        Debug.WriteLine("OrderInsert " + acc.ToJson(Formatting.Indented));

        await Task.Delay(10000);

    }

    [Test]
    public async Task ReqOrderInsertAsync_Test_Sucess()        // 输入订单，服务器校验成功
    {
        CThostFtdcInputOrderField field = new CThostFtdcInputOrderField()
        {
            InstrumentID   = "rb2210",
            CombOffsetFlag = TThostFtdcOffsetFlagType.Open,

            LimitPrice          = 3800,
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

        client.OnRtnOrderEvent += (s, e) =>
        {
            Debug.WriteLine("OnRtnOrderEvent " + e.ToJson(Formatting.Indented));
        };
        client.OnRtnTradeEvent += (s, e) =>
        {
            Debug.WriteLine("OnRtnTradeEvent " + e.ToJson(Formatting.Indented));
        };

        var acc = await client.ReqOrderInsertAsync(field);
        Debug.WriteLine("OrderInsert " + acc.ToJson(Formatting.Indented));

        await Task.Delay(5000);

    }


    [Test]
    public async Task ReqQryOrderAsync_Test()
    {
        var                     acc   = await client.ReqQryOrderAsync();
        //.acc.Rsp2.Should().n

        Debug.WriteLine("ReqQryOrderAsync" + acc.ToJson(Formatting.Indented));
    }

    [Test]
    public async Task ReqQryTradeAsync_Test()
    {
        var                     acc   = await client.ReqQryTradeAsync();
        //.acc.Rsp2.Should().n

        Debug.WriteLine("ReqQryTradeAsync" + acc.ToJson(Formatting.Indented));
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
#endregion
}