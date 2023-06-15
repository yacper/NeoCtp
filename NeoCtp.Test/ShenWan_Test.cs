/********************************************************************
    created:	2023-6-14 11:21:44
    author:		joshua
    email:		
	
    purpose:	申万实盘测试
这是评测版API，其他评测版API可在上期技术官网下载，网址为：www.sfit.com.cn
测试参数如下：
BrokerID：88888
IP 地址： 124.74.247.143
交易端口：10051
行情端口：10061
测试账号：8001888888
密码：demo1234

直连 appid : client_01swwl_1.0.0.1
评测授权码Authcode：1E23PJ404L866T3H


（3）测试时段
     交易日期间，9：00-15：00（上期所）
18：00-22：00（中金所）

编程说明
step1:在API连接后发起认证
void CUser::OnFrontConnected()
{
   cout <<"OnFrontConnected."<< endl;
   static const char *version = m_pUserApi->GetApiVersion();
   cout <<"------当前版本号 ："<< version <<" ------"<< endl;
   ReqAuthenticate();
}
 
int CUser::ReqAuthenticate()
{
   CThostFtdcReqAuthenticateField field;
   memset(&field, 0, sizeof(field));
   strcpy(field.BrokerID, "8000");
   strcpy(field.UserID, "001888");
   strcpy(field.AppID, "client_zhangs_1.0.0.1");
   strcpy(field.AuthCode, "5A5P4V7AZ5LCFEAK");
   return m_pUserApi->ReqAuthenticate(&field, 5);
}
AppID就是客户申请时自己命名的，AuthCode是期货公司发给客户，两者是一一对应的。其实ReqAuthenticate函数早就有了，但以前是通过UserProductInfo和AuthCode这两个字段绑定验证，现在UserProductInfo废弃不用，改为AppID了，填写时注意不要出错。  

step2:认证成功后发起登录
void CUser::OnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticateField, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
   printf("OnRspAuthenticate\n");
   if (pRspInfo != NULL && pRspInfo->ErrorID == 0)
   {
        printf("认证成功,ErrorID=0x%04x, ErrMsg=%s\n\n", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
        ReqUserLogin();
 
   }
 
   else
        cout <<"认证失败，"<<"ErrorID="<< pRspInfo->ErrorID <<"  ,ErrMsg="<< pRspInfo->ErrorMsg << endl;
 
}
 
int CUser::ReqUserLogin()
{
   printf("====ReqUserLogin====,用户登录中...\n\n");
   CThostFtdcReqUserLoginField reqUserLogin;
   memset(&reqUserLogin, 0, sizeof(reqUserLogin));
   strcpy_s(reqUserLogin.BrokerID, "8000");
   strcpy(reqUserLogin.UserID, "001888");
   strcpy(reqUserLogin.Password, "1");
   return m_pUserApi->ReqUserLogin(&reqUserLogin, ++RequestID);
 
}
然后就可以在OnRspUserLogin看是否登录成功了。
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

namespace NeoCtp.Test
{
public class ShenWan_Test
{
    private ICtpTdApi client = null;

    // 测试数据
    string BrokerID   = "88888";
    string TdFontAddr = "tcp://124.74.247.143:10051";
    string MFontAddr  = "tcp://124.74.247.143:10061";
    string UserID     = "8001888888";
    string Psw        = "demo1234";
    string Appid      = "client_01swwl_1.0.0.1";
    string Authcode   = "1E23PJ404L866T3H";

    [OneTimeSetUp]
    public async Task Setup()
    {
        ILogger defaultLogger = null;
        //LogManager.Configuration = new XmlLoggingConfiguration("NLog.config");
        //defaultLogger            = LogManager.GetCurrentClassLogger();


        /// connect
        client = new CtpTdApi(TdFontAddr, BrokerID, UserID, Psw, defaultLogger); // defaultLogger - can be null
        var connected = await client.ConnectAsync();
        connected.Should().BeTrue();

        // 先authenticate，再登录
        var auth = await client.ReqAuthenticateAsync(Appid, Authcode);
        Debug.WriteLine(auth.ToJson(Formatting.Indented));


        // login
        var logined = await client.ReqUserLoginAsync();
        client.IsLogined.Should().BeTrue();
        Debug.WriteLine(client.ToJson(Formatting.Indented));


        // SettlementInfoConfirm 
        var confirm = await client.ReqSettlementInfoConfirmAsync();
        confirm.Rsp2.InvestorID.Should().Be(UserID);
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

        // authenticate
        var auth = await client.ReqAuthenticateAsync(Appid, Authcode);
        Debug.WriteLine(auth.Dump());


        // SettlementInfoConfirm 使用simnow测试账户无此功能
        var confirm = await client.ReqSettlementInfoConfirmAsync();
        confirm.Rsp2.InvestorID.Should().Be(TestConstants.UserID);
    }

#region Enums

    //[Test]
    //public async Task TThostFtdcCombOffsetFlagType_Test()  // 
    //{
    //    var l = Enum.GetValues<TThostFtdcCombOffsetFlagType>();
    //    Enum.

    //    var ee = Convert.ToByte("0");
    //    var e  = (TThostFtdcCombOffsetFlagType)(ee);

    //    e.Should().Be(TThostFtdcCombOffsetFlagType.Open);
    //}

#endregion

#region Account

    [Test]
    public async Task ReqQryTradingAccountAsync_Test() // 查询账户资金
    {
        var acc = await client.ReqQryTradingAccountAsync();
        acc.Rsp2.Should().NotBeNull();

        Debug.WriteLine(acc.Rsp2.Dump());
    }

#endregion


#region Instrument 

    [Test]
    public async Task ReqQryInstrumentAsync_Test()
    {
        var ins = "rb2310";
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


    [Test]
    public async Task ReqOrderInsertAsync_Test_Sucess() // 输入订单，服务器校验成功
    {
        CThostFtdcInputOrderField field = new CThostFtdcInputOrderField()
        {
            InstrumentID   = "rb2310",
            CombOffsetFlag = TThostFtdcOffsetFlagType.Open,

            LimitPrice          = 3700,
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

        client.OnRtnOrderEvent += (s, e) => { Debug.WriteLine("OnRtnOrderEvent " + e.ToJson(Formatting.Indented)); };
        client.OnRtnTradeEvent += (s, e) => { Debug.WriteLine("OnRtnTradeEvent " + e.ToJson(Formatting.Indented)); };

        var acc = await client.ReqOrderInsertAsync(field);
        Debug.WriteLine("OrderInsert " + acc.ToJson(Formatting.Indented));

        await Task.Delay(5000);
    }

    [Test]
    public async Task ReqOrderActionAsync_DelTest() // 撤单
    {
        CThostFtdcInputOrderActionField actionField = new CThostFtdcInputOrderActionField()
        {
            // 必须提供ExchangeID + OrderSysID， 否则无法识别
            ExchangeID = "SHFE",
            OrderSysID = "       38792", // 注意:这样是没用的,exhcange找不到，        9006，前面的空格是必须的
            ActionFlag = TThostFtdcActionFlagType.Delete
        };

        var rsp2 = await client.ReqOrderActionAsync(actionField);
        Debug.WriteLine("ReqOrderActionAsync" + rsp2.ToJson(Formatting.Indented));
    }
}
}