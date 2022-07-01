//using System;
//using System.Collections.Generic;
//using System.Linq;
//using System.Text;
//using System.Threading;
//using System.Threading.Tasks;
//using NUnit.Framework;

//namespace SharpCtp.Test
//{
//	public class CtpTdApi_Test
//	{

//		private static ICtpTdApi2 _api;

//		private static string _frontAddr = "tcp://180.168.146.187:10130"; // 24h
//		//private static string _frontAddr = "tcp://180.168.146.187:10100";
//		private static string _brokerID = "9999";
//		private static string _UserID = "097266";
//		private static string _password = "hello@123";

//		//[ClassInitialize]
//		public static void Initialize(TestContext context)
//		{
//			_api = new CtpTdApi2();
//			_api.Connect(_frontAddr, (rsp) =>
//			{
//				if (rsp.Rtn == ECtpRtn.Sucess)
//				{
//					_api.ReqUserLogin(_brokerID, _UserID, _password, (rsp2) =>
//					{
//						if (rsp2.Rtn == ECtpRtn.Sucess && rsp2.Rsp.ErrorID == 0)
//						{
//							_api.ReqSettlementInfoConfirm((rsp3) =>
//							{
//								Console.WriteLine("投资者结算结果确认成功");
//								Console.WriteLine("确认日期:"+rsp3.Rsp1.ConfirmDate);
//								Console.WriteLine("确认时间:"+rsp3.Rsp1.ConfirmTime);

//								_api.ReqQryTradingAccount((rsp4) =>
//								{
//									Console.WriteLine("投资者账户");
//									Console.WriteLine("投资者账户可用资金" + rsp4.Rsp1.Available);




//								});




//							});

//						}

//					});

//				}


//			});





//			Thread.Sleep(2000);
//		}



//	}
//}
