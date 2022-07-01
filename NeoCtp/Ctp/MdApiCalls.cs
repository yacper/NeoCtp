/********************************************************************
    created:	2020-07-31 19:11:52
    author:		rush
    email:		
	
    purpose:	
*********************************************************************/
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace NeoCtp
{
	internal class MdApiCalls
	{
        [DllImport("CtpMdApiWrapper", EntryPoint = "CreateFtdcMdApi", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        internal extern static IntPtr   CreateFtdcMdApi(string pszFlowPath = "", bool bIsUsingUdp = false, bool bIsMulticast = false);
        [DllImport("CtpMdApiWrapper", EntryPoint = "CreateMdSpi", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        internal extern static IntPtr   CreateMdSpi();
		[DllImport("CtpMdApiWrapper", EntryPoint = "RegisterSpi", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		internal extern static void RegisterSpi(IntPtr api, IntPtr pSpi);

        [DllImport("CtpMdApiWrapper", EntryPoint = "GetApiVersion", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        internal extern static IntPtr   GetApiVersion();

        [DllImport("CtpMdApiWrapper", EntryPoint = "Release", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        internal extern static void     Release(IntPtr api);

        [DllImport("CtpMdApiWrapper", EntryPoint = "Init", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        internal extern static void     Init(IntPtr api);

        [DllImport("CtpMdApiWrapper", EntryPoint = "Join", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        internal extern static int     Join(IntPtr api);

        [DllImport("CtpMdApiWrapper", EntryPoint = "GetTradingDay", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        internal extern static IntPtr   GetTradingDay(IntPtr api);

        [DllImport("CtpMdApiWrapper", EntryPoint = "RegisterFront", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        internal extern static void     RegisterFront(IntPtr api, string pszFrontAddress);

        [DllImport("CtpMdApiWrapper", EntryPoint = "RegisterNameServer", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        internal extern static void     RegisterNameServer(IntPtr api, string pszNsAddress);

        [DllImport("CtpMdApiWrapper", EntryPoint = "RegisterFensUserInfo", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        internal extern static void     RegisterFensUserInfo(IntPtr api, ref CThostFtdcFensUserInfoField pFensUserInfo);

        [DllImport("CtpMdApiWrapper", EntryPoint = "SubscribeMarketData", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        internal extern static int      SubscribeMarketData(IntPtr api, string[] instruments, int count);

        [DllImport("CtpMdApiWrapper", EntryPoint = "UnSubscribeMarketData", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        internal extern static int      UnSubscribeMarketData(IntPtr api, string[] instruments, int count);

        [DllImport("CtpMdApiWrapper", EntryPoint = "SubscribeForQuoteRsp", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        internal extern static int      SubscribeForQuoteRsp(IntPtr api, string[] instruments, int count);

        [DllImport("CtpMdApiWrapper", EntryPoint = "UnSubscribeForQuoteRsp", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        internal extern static int      UnSubscribeForQuoteRsp(IntPtr api, string[] instruments, int count);

        [DllImport("CtpMdApiWrapper", EntryPoint = "ReqUserLoginAsync", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        internal extern static int      ReqUserLogin(IntPtr api, ref CThostFtdcReqUserLoginField pReqUserLoginField, int nRequestID);

        [DllImport("CtpMdApiWrapper", EntryPoint = "ReqUserLogoutAsync", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        internal extern static int      ReqUserLogout(IntPtr api, ref CThostFtdcUserLogoutField pUserLogout, int nRequestID);

        [DllImport("CtpMdApiWrapper", EntryPoint = "ReqQryMulticastInstrument", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        internal extern static int      ReqQryMulticastInstrument(IntPtr api, ref CThostFtdcQryMulticastInstrumentField pQryMulticastInstrument, int nRequestID);

        /// 注册回调函数
        internal delegate void          CbOnRspError(ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
        internal delegate void          CbOnHeartBeatWarning(int nTimeLapse);
        internal delegate void          CbOnFrontConnected();
        internal delegate void          CbOnFrontDisconnected(int nReason);
        internal delegate void          CbOnRspUserLogin(ref CThostFtdcRspUserLoginField pRspUserLogin, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
        internal delegate void          CbOnRspUserLogout(ref CThostFtdcUserLogoutField pUserLogout, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
		internal delegate void          CbOnRspSubMarketData(ref CThostFtdcSpecificInstrumentField pSpecificInstrument, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
        internal delegate void          CbOnRspUnSubMarketData(ref CThostFtdcSpecificInstrumentField pSpecificInstrument, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
        internal delegate void          CbOnRspSubForQuoteRsp(ref CThostFtdcSpecificInstrumentField pSpecificInstrument, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
        internal delegate void          CbOnRspUnSubForQuoteRsp(ref CThostFtdcSpecificInstrumentField pSpecificInstrument, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);
        internal delegate void          CbOnRtnDepthMarketData(ref CThostFtdcDepthMarketDataField pDepthMarketData);
        internal delegate void          CbOnRtnForQuoteRsp(ref CThostFtdcForQuoteRspField pQuoteRsp);
        internal delegate void          CbOnRspQryMulticastInstrument(ref CThostFtdcMulticastInstrumentField pMulticastInstrument, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);

        [DllImport("CtpMdApiWrapper", EntryPoint = "RegOnRspError", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        internal extern static void      RegOnRspError(IntPtr spi, CbOnRspError cb);
        [DllImport("CtpMdApiWrapper", EntryPoint = "RegOnHeartBeatWarning", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        internal extern static void      RegOnHeartBeatWarning(IntPtr spi, CbOnHeartBeatWarning cb);

        [DllImport("CtpMdApiWrapper", EntryPoint = "RegOnFrontConnected", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        internal extern static void      RegOnFrontConnected(IntPtr spi, CbOnFrontConnected cb);
        [DllImport("CtpMdApiWrapper", EntryPoint = "RegOnFrontDisconnected", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        internal extern static void      RegOnFrontDisconnected(IntPtr spi, CbOnFrontDisconnected cb);

        [DllImport("CtpMdApiWrapper", EntryPoint = "RegOnRspUserLogin", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        internal extern static void      RegOnRspUserLogin(IntPtr spi, CbOnRspUserLogin cb);
        [DllImport("CtpMdApiWrapper", EntryPoint = "RegOnRspUserLogout", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        internal extern static void      RegOnRspUserLogout(IntPtr spi, CbOnRspUserLogout cb);

        [DllImport("CtpMdApiWrapper", EntryPoint = "RegOnRspSubMarketData", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        internal extern static void      RegOnRspSubMarketData(IntPtr spi, CbOnRspSubMarketData cb);
        [DllImport("CtpMdApiWrapper", EntryPoint = "RegOnRspUnSubMarketData", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        internal extern static void      RegOnRspUnSubMarketData(IntPtr spi, CbOnRspUnSubMarketData cb);

        [DllImport("CtpMdApiWrapper", EntryPoint = "RegOnRspSubForQuoteRsp", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        internal extern static void      RegOnRspSubForQuoteRsp(IntPtr spi, CbOnRspSubForQuoteRsp cb);
        [DllImport("CtpMdApiWrapper", EntryPoint = "RegOnRspUnSubForQuoteRsp", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        internal extern static void      RegOnRspUnSubForQuoteRsp(IntPtr spi, CbOnRspUnSubForQuoteRsp cb);

        [DllImport("CtpMdApiWrapper", EntryPoint = "RegOnRspQryMulticastInstrument", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        internal extern static void      RegOnRspQryMulticastInstrument(IntPtr spi, CbOnRspQryMulticastInstrument cb);

        ///  通知
        [DllImport("CtpMdApiWrapper", EntryPoint = "RegOnRtnDepthMarketData", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        internal extern static void      RegOnRtnDepthMarketData(IntPtr spi, CbOnRtnDepthMarketData cb);

        [DllImport("CtpMdApiWrapper", EntryPoint = "RegOnRtnForQuoteRsp", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        internal extern static void      RegOnRtnForQuoteRsp(IntPtr spi, CbOnRtnForQuoteRsp cb);

	}



}
