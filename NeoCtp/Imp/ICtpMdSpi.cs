/********************************************************************
    created:	2020-09-01 1:54:01
    author:		rush
    email:		
	
    purpose:	
*********************************************************************/
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NeoCtp
{
	public interface ICtpMdSpi // 回调接口
	{
		///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
		void				OnFrontConnected() ;

		///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
		///@param nReason 错误原因
		///        0x1001 网络读失败
		///        0x1002 网络写失败
		///        0x2001 接收心跳超时
		///        0x2002 发送心跳失败
		///        0x2003 收到错误报文
		 void				OnFrontDisconnected(int nReason);


		///错误应答
		void				OnRspError(ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast) ;

		///心跳超时警告。当长时间未收到报文时，该方法被调用。
		///@param nTimeLapse 距离上次接收报文的时间
		void				OnHeartBeatWarning(int nTimeLapse);


		///登录请求响应
		void				OnRspUserLogin(ref CThostFtdcRspUserLoginField pRspUserLogin, ref CThostFtdcRspInfoField  pRspInfo, int nRequestID, bool bIsLast);

		///登出请求响应
		void				OnRspUserLogout(ref CThostFtdcUserLogoutField pUserLogout, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);


		///请求查询组播合约响应
		void				OnRspQryMulticastInstrument(ref CThostFtdcMulticastInstrumentField pMulticastInstrument, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);


		///订阅行情应答
		void				OnRspSubMarketData(ref CThostFtdcSpecificInstrumentField pSpecificInstrument, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);

		///取消订阅行情应答
		void				OnRspUnSubMarketData(ref CThostFtdcSpecificInstrumentField pSpecificInstrument, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);


		///订阅询价应答
		void				OnRspSubForQuoteRsp(ref CThostFtdcSpecificInstrumentField pSpecificInstrument, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);

		///取消订阅询价应答
		void				OnRspUnSubForQuoteRsp(ref CThostFtdcSpecificInstrumentField pSpecificInstrument, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast);


		///深度行情通知
		void				OnRtnDepthMarketData(ref CThostFtdcDepthMarketDataField pDepthMarketData);

		///询价通知
		void				OnRtnForQuoteRsp(ref CThostFtdcForQuoteRspField pForQuoteRsp);

	}
}
