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
        LogManager.Configuration = new XmlLoggingConfiguration("NLog.config");
        defaultLogger            = LogManager.GetCurrentClassLogger();

        /// connect
        client = new CtpTdApi(TestConstants.MdFrontAddr, TestConstants.BrokerID, TestConstants.UserID, TestConstants.Password, defaultLogger); // defaultLogger - can be null
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