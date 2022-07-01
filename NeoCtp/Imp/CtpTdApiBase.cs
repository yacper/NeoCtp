/********************************************************************
    created:	2020-09-01 2:23:59
    author:		rush
    email:		
	
    purpose:	
*********************************************************************/
using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Toolkit.Mvvm.ComponentModel;

namespace NeoCtp.Imp
{
	public partial class CtpTdApiBase:ObservableObject, ICtpTdApiBase
	{
		public string       BrokerId
		{
			get { return _BrokerID;}
			protected set
			{
				SetProperty(ref _BrokerID, value);
			}
		}
		public string       UserId
		{
			get { return _UserID;}
			protected set
			{
				SetProperty( ref _UserID, value);
			} }
		public string       Password
		{
			get { return _Password;}
			protected set
			{
				SetProperty(ref _Password, value);
			} }
		public string       FrontAddress
		{
			get { return _FrontAddress;}
			protected set
			{
				SetProperty( ref _FrontAddress, value);

			} }

		/// <summary>
		/// 前置编号
		/// </summary>
		public int          FrontId
		{
			get { return _FrontID;}
			protected set
			{
				SetProperty(ref _FrontID, value);
			} }

		/// <summary>
		/// 会话编号
		/// </summary>
		public int			SessionId
		{
			get { return _SessionID;}
			protected set { SetProperty(ref _SessionID, value); }
		}

        public string              MaxOrderRef { get; set; }                           /// 最大报单引用

		//public bool         IsConnected
		//{
		//	get { return _IsConnected;}
		//	protected set{Set("IsConnected", ref _IsConnected, value); }
		//}

		//public bool			IsLogined
		//{
		//	get {  return _IsLogined;  }
		//	protected set{Set("IsLogined", ref _IsLogined, value); }
		//}

		//public DateTime		LoginTime
		//{
		//	get { return _LoginTime; }
		//	protected set{Set("LoginTime", ref _LoginTime, value); }
		//}								// 登录时间

        public CtpTdApiBase(string frontAddress, string brokerId, string userId, string password)
        {
			FrontAddress = frontAddress;
            BrokerId     = brokerId;
			UserId = userId;
			Password = password;
        }


		/// 是否已登录


		///注册回调接口
		///@param pSpi 派生自回调接口类的实例
		public void RegisterSpi(ICtpTdSpi pSpi)
		{
			_Spi = pSpi;
		}

		public void Dispose()
		{
			throw new NotImplementedException();
		}

		/////创建TraderApi
		/////@param pszFlowPath 存贮订阅信息文件的目录，默认为当前目录
		/////@return 创建出的UserApi
		//static ref CThostFtdcTraderApi CreateFtdcTraderApi(const ref char pszFlowPath = ""){}

		///删除接口对象本身
		///@remark 不再使用本接口对象时,调用该函数删除接口对象
		public void Release()
		{
			TdApiCalls.Release(_ApiHandle);
		}

		///初始化
		///@remark 初始化运行环境,只有调用后,接口才开始工作
		public void Init(){TdApiCalls.Init(_ApiHandle);}

		///等待接口线程结束运行
		///@return 线程退出代码
		public int Join()
		{
			return TdApiCalls.Join(_ApiHandle);}

		///获取当前交易日
		///@retrun 获取到的交易日
		///@remark 只有登录成功后,才能得到正确的交易日
		public string GetTradingDay()
		{
			IntPtr ptr = TdApiCalls.GetTradingDay(_ApiHandle);

			return Marshal.PtrToStringAnsi(ptr);
		}

		///注册前置机网络地址
		///@param pszFrontAddress：前置机网络地址。
		///@remark 网络地址的格式为：“protocol://ipaddress:port”，如：”tcp://127.0.0.1:17001”。 
		///@remark “tcp”代表传输协议，“127.0.0.1”代表服务器地址。”17001”代表服务器端口号。
		public void RegisterFront(string pszFrontAddress)
		{
			FrontAddress = pszFrontAddress;
			TdApiCalls.RegisterFront(_ApiHandle, pszFrontAddress);
		}

		///注册名字服务器网络地址
		///@param pszNsAddress：名字服务器网络地址。
		///@remark 网络地址的格式为：“protocol://ipaddress:port”，如：”tcp://127.0.0.1:12001”。 
		///@remark “tcp”代表传输协议，“127.0.0.1”代表服务器地址。”12001”代表服务器端口号。
		///@remark RegisterNameServer优先于RegisterFront
		public void RegisterNameServer(string pszNsAddress)
		{
			TdApiCalls.RegisterFront(_ApiHandle, pszNsAddress);
		}

		///注册名字服务器用户信息
		///@param pFensUserInfo：用户信息。
		public void RegisterFensUserInfo(ref CThostFtdcFensUserInfoField pFensUserInfo)
		{
			BrokerId = pFensUserInfo.BrokerID;
			UserId = pFensUserInfo.UserID;
			TdApiCalls.RegisterFensUserInfo(_ApiHandle, ref pFensUserInfo);
		}



		///订阅私有流。
		///@param nResumeType 私有流重传方式  
		///        THOST_TERT_RESTART:从本交易日开始重传
		///        THOST_TERT_RESUME:从上次收到的续传
		///        THOST_TERT_QUICK:只传送登录后私有流的内容
		///@remark 该方法要在Init方法前调用。若不调用则不会收到私有流的数据。
		public void SubscribePrivateTopic(THOST_TE_RESUME_TYPE nResumeType)
		{
			TdApiCalls.SubscribePrivateTopic(nResumeType);
		}

		///订阅公共流。
		///@param nResumeType 公共流重传方式  
		///        THOST_TERT_RESTART:从本交易日开始重传
		///        THOST_TERT_RESUME:从上次收到的续传
		///        THOST_TERT_QUICK:只传送登录后公共流的内容
		///@remark 该方法要在Init方法前调用。若不调用则不会收到公共流的数据。
		public void SubscribePublicTopic(THOST_TE_RESUME_TYPE nResumeType)
		{
			TdApiCalls.SubscribePublicTopic(nResumeType);
		}

		///客户端认证请求
		public int ReqAuthenticate(ref CThostFtdcReqAuthenticateField pReqAuthenticateField, int nRequestID)
		{
			return TdApiCalls.ReqAuthenticate(_ApiHandle, ref pReqAuthenticateField, nRequestID);
		}

		///注册用户终端信息，用于中继服务器多连接模式
		///需要在终端认证成功后，用户登录前调用该接口
		public int RegisterUserSystemInfo(ref CThostFtdcUserSystemInfoField pUserSystemInfo)
		{
			return TdApiCalls.RegisterUserSystemInfo(_ApiHandle, ref pUserSystemInfo);
		}

		///上报用户终端信息，用于中继服务器操作员登录模式
		///操作员登录后，可以多次调用该接口上报客户信息
		public int SubmitUserSystemInfo(ref CThostFtdcUserSystemInfoField pUserSystemInfo)
		{
			return TdApiCalls.SubmitUserSystemInfo(_ApiHandle, ref pUserSystemInfo);
		}

		///用户登录请求
		public int ReqUserLogin(ref CThostFtdcReqUserLoginField pReqUserLoginField, int nRequestID)
		{
			return TdApiCalls.ReqUserLogin(_ApiHandle, ref pReqUserLoginField, nRequestID);
		}

		///登出请求
		public int ReqUserLogout(ref CThostFtdcUserLogoutField pUserLogout, int nRequestID)
		{
			return TdApiCalls.ReqUserLogout(_ApiHandle, ref pUserLogout, nRequestID);
		}

		///用户口令更新请求
		public int ReqUserPasswordUpdate(ref CThostFtdcUserPasswordUpdateField pUserPasswordUpdate, int nRequestID)
		{
			return TdApiCalls.ReqUserPasswordUpdate(_ApiHandle, ref pUserPasswordUpdate, nRequestID);
		}

		///资金账户口令更新请求
		public int ReqTradingAccountPasswordUpdate(ref CThostFtdcTradingAccountPasswordUpdateField pTradingAccountPasswordUpdate, int nRequestID)
		{
			return TdApiCalls.ReqTradingAccountPasswordUpdate(_ApiHandle, ref pTradingAccountPasswordUpdate, nRequestID);
		}

		///查询用户当前支持的认证模式
		public int ReqUserAuthMethod(ref CThostFtdcReqUserAuthMethodField pReqUserAuthMethod, int nRequestID)
		{
			return TdApiCalls.ReqUserAuthMethod(_ApiHandle, ref pReqUserAuthMethod, nRequestID);
		}

		///用户发出获取图形验证码请求
		public int ReqGenUserCaptcha(ref CThostFtdcReqGenUserCaptchaField pReqGenUserCaptcha, int nRequestID)
		{
			return TdApiCalls.ReqGenUserCaptcha(_ApiHandle, ref pReqGenUserCaptcha, nRequestID);
		}

		///用户发出获取短信验证码请求
		public int ReqGenUserText(ref CThostFtdcReqGenUserTextField pReqGenUserText, int nRequestID)
		{
			return TdApiCalls.ReqGenUserText(_ApiHandle, ref pReqGenUserText, nRequestID);
		}

		///用户发出带有图片验证码的登陆请求
		public int ReqUserLoginWithCaptcha(ref CThostFtdcReqUserLoginWithCaptchaField pReqUserLoginWithCaptcha,
			int nRequestID)
		{
			return TdApiCalls.ReqUserLoginWithCaptcha(_ApiHandle, ref pReqUserLoginWithCaptcha, nRequestID);
		}

		///用户发出带有短信验证码的登陆请求
		public int ReqUserLoginWithText(ref CThostFtdcReqUserLoginWithTextField pReqUserLoginWithText, int nRequestID)
		{
			return TdApiCalls.ReqUserLoginWithText(_ApiHandle, ref pReqUserLoginWithText, nRequestID);
		}

		///用户发出带有动态口令的登陆请求
		public int ReqUserLoginWithOTP(ref CThostFtdcReqUserLoginWithOTPField pReqUserLoginWithOTP, int nRequestID)
		{
			return TdApiCalls.ReqUserLoginWithOTP(_ApiHandle, ref pReqUserLoginWithOTP, nRequestID);
		}

		///报单录入请求
		public int ReqOrderInsert(ref CThostFtdcInputOrderField pInputOrder, int nRequestID)
		{
			return TdApiCalls.ReqOrderInsert(_ApiHandle, ref pInputOrder, nRequestID);
		}

		///预埋单录入请求
		public int ReqParkedOrderInsert(ref CThostFtdcParkedOrderField pParkedOrder, int nRequestID)
		{
			return TdApiCalls.ReqParkedOrderInsert(_ApiHandle, ref pParkedOrder, nRequestID);
		}

		///预埋撤单录入请求
		public int ReqParkedOrderAction(ref CThostFtdcParkedOrderActionField pParkedOrderAction, int nRequestID)
		{
			return TdApiCalls.ReqParkedOrderAction(_ApiHandle, ref pParkedOrderAction, nRequestID);
		}

		///报单操作请求
		public int ReqOrderAction(ref CThostFtdcInputOrderActionField pInputOrderAction, int nRequestID)
		{
			return TdApiCalls.ReqOrderAction(_ApiHandle, ref pInputOrderAction, nRequestID);
		}

		///查询最大报单数量请求
		public int ReqQueryMaxOrderVolume(ref CThostFtdcQueryMaxOrderVolumeField pQueryMaxOrderVolume, int nRequestID)
		{
			return TdApiCalls.ReqQueryMaxOrderVolume(_ApiHandle, ref pQueryMaxOrderVolume, nRequestID);
		}

		///投资者结算结果确认
		public int ReqSettlementInfoConfirm(ref CThostFtdcSettlementInfoConfirmField pSettlementInfoConfirm,
			int nRequestID)
		{
			return TdApiCalls.ReqSettlementInfoConfirm(_ApiHandle, ref pSettlementInfoConfirm, nRequestID);
		}

		///请求删除预埋单
		public int ReqRemoveParkedOrder(ref CThostFtdcRemoveParkedOrderField pRemoveParkedOrder, int nRequestID)
		{
			return TdApiCalls.ReqRemoveParkedOrder(_ApiHandle, ref pRemoveParkedOrder, nRequestID);
		}

		///请求删除预埋撤单
		public int ReqRemoveParkedOrderAction(ref CThostFtdcRemoveParkedOrderActionField pRemoveParkedOrderAction,
			int nRequestID)
		{
			return TdApiCalls.ReqRemoveParkedOrderAction(_ApiHandle, ref pRemoveParkedOrderAction, nRequestID);
		}

		///执行宣告录入请求
		public int ReqExecOrderInsert(ref CThostFtdcInputExecOrderField pInputExecOrder, int nRequestID)
		{
			return TdApiCalls.ReqExecOrderInsert(_ApiHandle, ref pInputExecOrder, nRequestID);
		}

		///执行宣告操作请求
		public int ReqExecOrderAction(ref CThostFtdcInputExecOrderActionField pInputExecOrderAction, int nRequestID)
		{
			return TdApiCalls.ReqExecOrderAction(_ApiHandle, ref pInputExecOrderAction, nRequestID);
		}

		///询价录入请求
		public int ReqForQuoteInsert(ref CThostFtdcInputForQuoteField pInputForQuote, int nRequestID)
		{
			return TdApiCalls.ReqForQuoteInsert(_ApiHandle, ref pInputForQuote, nRequestID);
		}

		///报价录入请求
		public int ReqQuoteInsert(ref CThostFtdcInputQuoteField pInputQuote, int nRequestID)
		{
			return TdApiCalls.ReqQuoteInsert(_ApiHandle, ref pInputQuote, nRequestID);
		}

		///报价操作请求
		public int ReqQuoteAction(ref CThostFtdcInputQuoteActionField pInputQuoteAction, int nRequestID)
		{
			return TdApiCalls.ReqQuoteAction(_ApiHandle, ref pInputQuoteAction, nRequestID);
		}

		///批量报单操作请求
		public int ReqBatchOrderAction(ref CThostFtdcInputBatchOrderActionField pInputBatchOrderAction, int nRequestID)
		{
			return TdApiCalls.ReqBatchOrderAction(_ApiHandle, ref pInputBatchOrderAction, nRequestID);
		}

		///期权自对冲录入请求
		public int ReqOptionSelfCloseInsert(ref CThostFtdcInputOptionSelfCloseField pInputOptionSelfClose,
			int nRequestID)
		{
			return TdApiCalls.ReqOptionSelfCloseInsert(_ApiHandle, ref pInputOptionSelfClose, nRequestID);
		}

		///期权自对冲操作请求
		public int ReqOptionSelfCloseAction(ref CThostFtdcInputOptionSelfCloseActionField pInputOptionSelfCloseAction,
			int nRequestID)
		{
			return TdApiCalls.ReqOptionSelfCloseAction(_ApiHandle, ref pInputOptionSelfCloseAction, nRequestID);
		}

		///申请组合录入请求
		public int ReqCombActionInsert(ref CThostFtdcInputCombActionField pInputCombAction, int nRequestID)
		{
			return TdApiCalls.ReqCombActionInsert(_ApiHandle, ref pInputCombAction, nRequestID);
		}

		///请求查询报单
		public int ReqQryOrder(ref CThostFtdcQryOrderField pQryOrder, int nRequestID)
		{
			return TdApiCalls.ReqQryOrder(_ApiHandle, ref pQryOrder, nRequestID);
		}

		///请求查询成交
		public int ReqQryTrade(ref CThostFtdcQryTradeField pQryTrade, int nRequestID)
		{
			return TdApiCalls.ReqQryTrade(_ApiHandle, ref pQryTrade, nRequestID);
		}

		///请求查询投资者持仓
		public int ReqQryInvestorPosition(ref CThostFtdcQryInvestorPositionField pQryInvestorPosition, int nRequestID)
		{
			return TdApiCalls.ReqQryInvestorPosition(_ApiHandle, ref pQryInvestorPosition, nRequestID);
		}

		///请求查询资金账户
		public int ReqQryTradingAccount(ref CThostFtdcQryTradingAccountField pQryTradingAccount, int nRequestID)
		{
			return TdApiCalls.ReqQryTradingAccount(_ApiHandle, ref pQryTradingAccount, nRequestID);
		}

		///请求查询投资者
		public int ReqQryInvestor(ref CThostFtdcQryInvestorField pQryInvestor, int nRequestID)
		{
			return TdApiCalls.ReqQryInvestor(_ApiHandle, ref pQryInvestor, nRequestID);
		}

		///请求查询交易编码
		public int ReqQryTradingCode(ref CThostFtdcQryTradingCodeField pQryTradingCode, int nRequestID)
		{
			return TdApiCalls.ReqQryTradingCode(_ApiHandle, ref pQryTradingCode, nRequestID);
		}

		///请求查询合约保证金率
		public int ReqQryInstrumentMarginRate(ref CThostFtdcQryInstrumentMarginRateField pQryInstrumentMarginRate,
			int nRequestID)
		{
			return TdApiCalls.ReqQryInstrumentMarginRate(_ApiHandle, ref pQryInstrumentMarginRate, nRequestID);
		}

		///请求查询合约手续费率
		public int ReqQryInstrumentCommissionRate(
			ref CThostFtdcQryInstrumentCommissionRateField pQryInstrumentCommissionRate, int nRequestID)
		{
			return TdApiCalls.ReqQryInstrumentCommissionRate(_ApiHandle, ref pQryInstrumentCommissionRate, nRequestID);
		}

		///请求查询交易所
		public int ReqQryExchange(ref CThostFtdcQryExchangeField pQryExchange, int nRequestID)
		{
			return TdApiCalls.ReqQryExchange(_ApiHandle, ref pQryExchange, nRequestID);
		}

		///请求查询产品
		public int ReqQryProduct(ref CThostFtdcQryProductField pQryProduct, int nRequestID)
		{
			return TdApiCalls.ReqQryProduct(_ApiHandle, ref pQryProduct, nRequestID);
		}

		///请求查询合约
		public int ReqQryInstrument(ref CThostFtdcQryInstrumentField pQryInstrument, int nRequestID)
		{
			return TdApiCalls.ReqQryInstrument(_ApiHandle, ref pQryInstrument, nRequestID);
		}

		///请求查询行情
		public int ReqQryDepthMarketData(ref CThostFtdcQryDepthMarketDataField pQryDepthMarketData, int nRequestID)
		{
			return TdApiCalls.ReqQryDepthMarketData(_ApiHandle, ref pQryDepthMarketData, nRequestID);
		}

		///请求查询投资者结算结果
		public int ReqQrySettlementInfo(ref CThostFtdcQrySettlementInfoField pQrySettlementInfo, int nRequestID)
		{
			return TdApiCalls.ReqQrySettlementInfo(_ApiHandle, ref pQrySettlementInfo, nRequestID);
		}

		///请求查询转帐银行
		public int ReqQryTransferBank(ref CThostFtdcQryTransferBankField pQryTransferBank, int nRequestID)
		{
			return TdApiCalls.ReqQryTransferBank(_ApiHandle, ref pQryTransferBank, nRequestID);
		}

		///请求查询投资者持仓明细
		public int ReqQryInvestorPositionDetail(ref CThostFtdcQryInvestorPositionDetailField pQryInvestorPositionDetail,
			int nRequestID)
		{
			return TdApiCalls.ReqQryInvestorPositionDetail(_ApiHandle, ref pQryInvestorPositionDetail, nRequestID);
		}

		///请求查询客户通知
		public int ReqQryNotice(ref CThostFtdcQryNoticeField pQryNotice, int nRequestID)
		{
			return TdApiCalls.ReqQryNotice(_ApiHandle, ref pQryNotice, nRequestID);
		}

		///请求查询结算信息确认
		public int ReqQrySettlementInfoConfirm(ref CThostFtdcQrySettlementInfoConfirmField pQrySettlementInfoConfirm,
			int nRequestID)
		{
			return TdApiCalls.ReqQrySettlementInfoConfirm(_ApiHandle, ref pQrySettlementInfoConfirm, nRequestID);
		}

		///请求查询投资者持仓明细
		public int ReqQryInvestorPositionCombineDetail(
			ref CThostFtdcQryInvestorPositionCombineDetailField pQryInvestorPositionCombineDetail, int nRequestID)
		{
			return TdApiCalls.ReqQryInvestorPositionCombineDetail(_ApiHandle, ref pQryInvestorPositionCombineDetail,
				nRequestID);
		}

		///请求查询保证金监管系统经纪公司资金账户密钥
		public int ReqQryCFMMCTradingAccountKey(ref CThostFtdcQryCFMMCTradingAccountKeyField pQryCFMMCTradingAccountKey,
			int nRequestID)
		{
			return TdApiCalls.ReqQryCFMMCTradingAccountKey(_ApiHandle, ref pQryCFMMCTradingAccountKey, nRequestID);
		}

		///请求查询仓单折抵信息
		public int ReqQryEWarrantOffset(ref CThostFtdcQryEWarrantOffsetField pQryEWarrantOffset, int nRequestID)
		{
			return TdApiCalls.ReqQryEWarrantOffset(_ApiHandle, ref pQryEWarrantOffset, nRequestID);
		}

		///请求查询投资者品种/跨品种保证金
		public int ReqQryInvestorProductGroupMargin(
			ref CThostFtdcQryInvestorProductGroupMarginField pQryInvestorProductGroupMargin, int nRequestID)
		{
			return TdApiCalls.ReqQryInvestorProductGroupMargin(_ApiHandle, ref pQryInvestorProductGroupMargin,
				nRequestID);
		}

		///请求查询交易所保证金率
		public int ReqQryExchangeMarginRate(ref CThostFtdcQryExchangeMarginRateField pQryExchangeMarginRate,
			int nRequestID)
		{
			return TdApiCalls.ReqQryExchangeMarginRate(_ApiHandle, ref pQryExchangeMarginRate, nRequestID);
		}

		///请求查询交易所调整保证金率
		public int ReqQryExchangeMarginRateAdjust(
			ref CThostFtdcQryExchangeMarginRateAdjustField pQryExchangeMarginRateAdjust, int nRequestID)
		{
			return TdApiCalls.ReqQryExchangeMarginRateAdjust(_ApiHandle, ref pQryExchangeMarginRateAdjust, nRequestID);
		}

		///请求查询汇率
		public int ReqQryExchangeRate(ref CThostFtdcQryExchangeRateField pQryExchangeRate, int nRequestID)
		{
			return TdApiCalls.ReqQryExchangeRate(_ApiHandle, ref pQryExchangeRate, nRequestID);
		}

		///请求查询二级代理操作员银期权限
		public int ReqQrySecAgentACIDMap(ref CThostFtdcQrySecAgentACIDMapField pQrySecAgentACIDMap, int nRequestID)
		{
			return TdApiCalls.ReqQrySecAgentACIDMap(_ApiHandle, ref pQrySecAgentACIDMap, nRequestID);
		}

		///请求查询产品报价汇率
		public int ReqQryProductExchRate(ref CThostFtdcQryProductExchRateField pQryProductExchRate, int nRequestID)
		{
			return TdApiCalls.ReqQryProductExchRate(_ApiHandle, ref pQryProductExchRate, nRequestID);
		}

		///请求查询产品组
		public int ReqQryProductGroup(ref CThostFtdcQryProductGroupField pQryProductGroup, int nRequestID)
		{
			return TdApiCalls.ReqQryProductGroup(_ApiHandle, ref pQryProductGroup, nRequestID);
		}

		///请求查询做市商合约手续费率
		public int ReqQryMMInstrumentCommissionRate(
			ref CThostFtdcQryMMInstrumentCommissionRateField pQryMMInstrumentCommissionRate, int nRequestID)
		{
			return TdApiCalls.ReqQryMMInstrumentCommissionRate(_ApiHandle, ref pQryMMInstrumentCommissionRate,
				nRequestID);
		}

		///请求查询做市商期权合约手续费
		public int ReqQryMMOptionInstrCommRate(ref CThostFtdcQryMMOptionInstrCommRateField pQryMMOptionInstrCommRate,
			int nRequestID)
		{
			return TdApiCalls.ReqQryMMOptionInstrCommRate(_ApiHandle, ref pQryMMOptionInstrCommRate, nRequestID);
		}

		///请求查询报单手续费
		public int ReqQryInstrumentOrderCommRate(
			ref CThostFtdcQryInstrumentOrderCommRateField pQryInstrumentOrderCommRate, int nRequestID)
		{
			return TdApiCalls.ReqQryInstrumentOrderCommRate(_ApiHandle, ref pQryInstrumentOrderCommRate, nRequestID);
		}

		///请求查询资金账户
		public int ReqQrySecAgentTradingAccount(ref CThostFtdcQryTradingAccountField pQryTradingAccount, int nRequestID)
		{
			return TdApiCalls.ReqQrySecAgentTradingAccount(_ApiHandle, ref pQryTradingAccount, nRequestID);
		}

		///请求查询二级代理商资金校验模式
		public int ReqQrySecAgentCheckMode(ref CThostFtdcQrySecAgentCheckModeField pQrySecAgentCheckMode,
			int nRequestID)
		{
			return TdApiCalls.ReqQrySecAgentCheckMode(_ApiHandle, ref pQrySecAgentCheckMode, nRequestID);
		}

		///请求查询二级代理商信息
		public int ReqQrySecAgentTradeInfo(ref CThostFtdcQrySecAgentTradeInfoField pQrySecAgentTradeInfo,
			int nRequestID)
		{
			return TdApiCalls.ReqQrySecAgentTradeInfo(_ApiHandle, ref pQrySecAgentTradeInfo, nRequestID);
		}

		///请求查询期权交易成本
		public int ReqQryOptionInstrTradeCost(ref CThostFtdcQryOptionInstrTradeCostField pQryOptionInstrTradeCost,
			int nRequestID)
		{
			return TdApiCalls.ReqQryOptionInstrTradeCost(_ApiHandle, ref pQryOptionInstrTradeCost, nRequestID);
		}

		///请求查询期权合约手续费
		public int ReqQryOptionInstrCommRate(ref CThostFtdcQryOptionInstrCommRateField pQryOptionInstrCommRate,
			int nRequestID)
		{
			return TdApiCalls.ReqQryOptionInstrCommRate(_ApiHandle, ref pQryOptionInstrCommRate, nRequestID);
		}

		///请求查询执行宣告
		public int ReqQryExecOrder(ref CThostFtdcQryExecOrderField pQryExecOrder, int nRequestID)
		{
			return TdApiCalls.ReqQryExecOrder(_ApiHandle, ref pQryExecOrder, nRequestID);
		}

		///请求查询询价
		public int ReqQryForQuote(ref CThostFtdcQryForQuoteField pQryForQuote, int nRequestID)
		{
			return TdApiCalls.ReqQryForQuote(_ApiHandle, ref pQryForQuote, nRequestID);
		}

		///请求查询报价
		public int ReqQryQuote(ref CThostFtdcQryQuoteField pQryQuote, int nRequestID)
		{
			return TdApiCalls.ReqQryQuote(_ApiHandle, ref pQryQuote, nRequestID);
		}

		///请求查询期权自对冲
		public int ReqQryOptionSelfClose(ref CThostFtdcQryOptionSelfCloseField pQryOptionSelfClose, int nRequestID)
		{
			return TdApiCalls.ReqQryOptionSelfClose(_ApiHandle, ref pQryOptionSelfClose, nRequestID);
		}

		///请求查询投资单元
		public int ReqQryInvestUnit(ref CThostFtdcQryInvestUnitField pQryInvestUnit, int nRequestID)
		{
			return TdApiCalls.ReqQryInvestUnit(_ApiHandle, ref pQryInvestUnit, nRequestID);
		}

		///请求查询组合合约安全系数
		public int ReqQryCombInstrumentGuard(ref CThostFtdcQryCombInstrumentGuardField pQryCombInstrumentGuard,
			int nRequestID)
		{
			return TdApiCalls.ReqQryCombInstrumentGuard(_ApiHandle, ref pQryCombInstrumentGuard, nRequestID);
		}

		///请求查询申请组合
		public int ReqQryCombAction(ref CThostFtdcQryCombActionField pQryCombAction, int nRequestID)
		{
			return TdApiCalls.ReqQryCombAction(_ApiHandle, ref pQryCombAction, nRequestID);
		}

		///请求查询转帐流水
		public int ReqQryTransferSerial(ref CThostFtdcQryTransferSerialField pQryTransferSerial, int nRequestID)
		{
			return TdApiCalls.ReqQryTransferSerial(_ApiHandle, ref pQryTransferSerial, nRequestID);
		}

		///请求查询银期签约关系
		public int ReqQryAccountregister(ref CThostFtdcQryAccountregisterField pQryAccountregister, int nRequestID)
		{
			return TdApiCalls.ReqQryAccountregister(_ApiHandle, ref pQryAccountregister, nRequestID);
		}

		///请求查询签约银行
		public int ReqQryContractBank(ref CThostFtdcQryContractBankField pQryContractBank, int nRequestID)
		{
			return TdApiCalls.ReqQryContractBank(_ApiHandle, ref pQryContractBank, nRequestID);
		}

		///请求查询预埋单
		public int ReqQryParkedOrder(ref CThostFtdcQryParkedOrderField pQryParkedOrder, int nRequestID)
		{
			return TdApiCalls.ReqQryParkedOrder(_ApiHandle, ref pQryParkedOrder, nRequestID);
		}

		///请求查询预埋撤单
		public int ReqQryParkedOrderAction(ref CThostFtdcQryParkedOrderActionField pQryParkedOrderAction,
			int nRequestID)
		{
			return TdApiCalls.ReqQryParkedOrderAction(_ApiHandle, ref pQryParkedOrderAction, nRequestID);
		}

		///请求查询交易通知
		public int ReqQryTradingNotice(ref CThostFtdcQryTradingNoticeField pQryTradingNotice, int nRequestID)
		{
			return TdApiCalls.ReqQryTradingNotice(_ApiHandle, ref pQryTradingNotice, nRequestID);
		}

		///请求查询经纪公司交易参数
		public int ReqQryBrokerTradingParams(ref CThostFtdcQryBrokerTradingParamsField pQryBrokerTradingParams,
			int nRequestID)
		{
			return TdApiCalls.ReqQryBrokerTradingParams(_ApiHandle, ref pQryBrokerTradingParams, nRequestID);
		}

		///请求查询经纪公司交易算法
		public int ReqQryBrokerTradingAlgos(ref CThostFtdcQryBrokerTradingAlgosField pQryBrokerTradingAlgos,
			int nRequestID)
		{
			return TdApiCalls.ReqQryBrokerTradingAlgos(_ApiHandle, ref pQryBrokerTradingAlgos, nRequestID);
		}

		///请求查询监控中心用户令牌
		public int ReqQueryCFMMCTradingAccountToken(
			ref CThostFtdcQueryCFMMCTradingAccountTokenField pQueryCFMMCTradingAccountToken, int nRequestID)
		{
			return TdApiCalls.ReqQueryCFMMCTradingAccountToken(_ApiHandle, ref pQueryCFMMCTradingAccountToken, nRequestID);
		}

		///期货发起银行资金转期货请求
		public int ReqFromBankToFutureByFuture(ref CThostFtdcReqTransferField pReqTransfer, int nRequestID)
		{
			return TdApiCalls.ReqFromBankToFutureByFuture(_ApiHandle, ref pReqTransfer, nRequestID);
		}

		///期货发起期货资金转银行请求
		public int ReqFromFutureToBankByFuture(ref CThostFtdcReqTransferField pReqTransfer, int nRequestID)
		{
			return TdApiCalls.ReqFromFutureToBankByFuture(_ApiHandle, ref pReqTransfer, nRequestID);
		}

		///期货发起查询银行余额请求
		public int ReqQueryBankAccountMoneyByFuture(ref CThostFtdcReqQueryAccountField pReqQueryAccount, int nRequestID)
		{
			return TdApiCalls.ReqQueryBankAccountMoneyByFuture(_ApiHandle, ref pReqQueryAccount, nRequestID);
		}



#region C&D
        public              CtpTdApiBase(string pszFlowPath = "CtpTdFiles/")
        {
	        _ApiHandle = TdApiCalls.CreateFtdcTraderApi(pszFlowPath);
			_SpiHandle = TdApiCalls.CreateSpi();

			TdApiCalls.RegisterSpi(_ApiHandle, _SpiHandle);
            _BindEvents();
		}

        private void        _BindEvents()
		{
			//TdApiCalls.RegOnRspError(_SpiHandle, _OnRspError);
			TdApiCalls.RegOnHeartBeatWarning(_SpiHandle, _CbOnHeartBeatWarning);

			TdApiCalls.RegOnFrontConnected(_SpiHandle, _OnFrontConnected);
			TdApiCalls.RegOnFrontDisconnected(_SpiHandle, _OnFrontDisconnected);

			TdApiCalls.RegRspAuthenticate(_SpiHandle, _CBRspAuthenticate);

			TdApiCalls.RegOnRspUserLogin(_SpiHandle, _OnRspUserLogin);
			TdApiCalls.RegOnRspUserLogout(_SpiHandle, _OnRspUserLogout);

			TdApiCalls.RegRspUserPasswordUpdate(_SpiHandle, _CBRspUserPasswordUpdate);  //用户口令更新请求响应
			TdApiCalls.RegRspTradingAccountPasswordUpdate(_SpiHandle, _CBRspTradingAccountPasswordUpdate);			
			TdApiCalls.RegRspUserAuthMethod(_SpiHandle, _CBRspUserAuthMethod);
			TdApiCalls.RegRspGenUserCaptcha(_SpiHandle, _CBRspGenUserCaptcha);
			TdApiCalls.RegRspGenUserText(_SpiHandle, _CBRspGenUserText);
			TdApiCalls.RegRspOrderInsert(_SpiHandle, _CBRspOrderInsert);
			TdApiCalls.RegRspParkedOrderInsert(_SpiHandle, _CBRspParkedOrderInsert);
			TdApiCalls.RegRspParkedOrderAction(_SpiHandle, _CBRspParkedOrderAction);
			TdApiCalls.RegRspOrderAction(_SpiHandle, _CBRspOrderAction);
			TdApiCalls.RegRspQueryMaxOrderVolume(_SpiHandle, _CBRspQueryMaxOrderVolume);
			TdApiCalls.RegRspSettlementInfoConfirm(_SpiHandle, _CBRspSettlementInfoConfirm);
			TdApiCalls.RegRspRemoveParkedOrder(_SpiHandle, _CBRspRemoveParkedOrder);
			TdApiCalls.RegRspRemoveParkedOrderAction(_SpiHandle, _CBRspRemoveParkedOrderAction);
			TdApiCalls.RegBatchOrderAction(_SpiHandle, _CBRspBatchOrderAction);
			TdApiCalls.RegCombActionInsert(_SpiHandle, _CBRspCombActionInsert);
			TdApiCalls.RegRspQryOrder(_SpiHandle, _CBRspQryOrder);
			TdApiCalls.RegRspQryTrade(_SpiHandle, _CBRspQryTrade);
			TdApiCalls.RegRspQryInvestorPosition(_SpiHandle, _CBRspQryInvestorPosition);
			TdApiCalls.RegRspQryTradingAccount(_SpiHandle, _CBRspQryTradingAccount);
			TdApiCalls.RegRspQryInvestor(_SpiHandle, _CBRspQryInvestor);
			TdApiCalls.RegRspQryTradingCode(_SpiHandle, _CBRspQryTradingCode);
			TdApiCalls.RegRspQryInstrumentMarginRate(_SpiHandle, _CBRspQryInstrumentMarginRate);
			TdApiCalls.RegRspQryInstrumentCommissionRate(_SpiHandle, _CBRspQryInstrumentCommissionRate);
			TdApiCalls.RegRspQryExchange(_SpiHandle, _CBRspQryExchange);
			TdApiCalls.RegRspQryInstrument(_SpiHandle, _CBRspQryInstrument);
			TdApiCalls.RegRspQryDepthMarketData(_SpiHandle, _CBRspQryDepthMarketData);
			TdApiCalls.RegRspQrySettlementInfo(_SpiHandle, _CBRspQrySettlementInfo);
			TdApiCalls.RegRspQryTransferBank(_SpiHandle, _CBRspQryTransferBank);
			TdApiCalls.RegRspQryInvestorPositionDetail(_SpiHandle, _CBRspQryInvestorPositionDetail);
			TdApiCalls.RegRspQryNotice(_SpiHandle, _CBRspQryNotice);
			TdApiCalls.RegRspQrySettlementInfoConfirm(_SpiHandle, _CBRspQrySettlementInfoConfirm);
			TdApiCalls.RegRspQryInvestorPositionCombineDetail(_SpiHandle, _CBRspQryInvestorPositionCombineDetail);
			TdApiCalls.RegRspQryCFMMCTradingAccountKey(_SpiHandle, _CBRspQryCFMMCTradingAccountKey);
			TdApiCalls.RegRspQryEWarrantOffset(_SpiHandle, _CBRspQryEWarrantOffset);
			TdApiCalls.RegRspQryInvestorProductGroupMargin(_SpiHandle, _CBRspQryInvestorProductGroupMargin);
			TdApiCalls.RegRspQryExchangeMarginRate(_SpiHandle, _CBRspQryExchangeMarginRate);
			TdApiCalls.RegRspQryExchangeMarginRateAdjust(_SpiHandle, _CBRspQryExchangeMarginRateAdjust);
			TdApiCalls.RegRspQryExchangeRate(_SpiHandle, _CBRspQryExchangeRate);
			TdApiCalls.RegRspQrySecAgentACIDMap(_SpiHandle, _CBRspQrySecAgentACIDMap);
			TdApiCalls.RegRspQryProductExchRate(_SpiHandle, _CBRspQryProductExchRate);
			TdApiCalls.RegRspQryProductGroup(_SpiHandle, _CBRspQryProductGroup);
			TdApiCalls.RegRspQryMMInstrumentCommissionRate(_SpiHandle, _CBRspQryMMInstrumentCommissionRate);
			TdApiCalls.RegRspQryMMOptionInstrCommRate(_SpiHandle, _CBRspQryMMOptionInstrCommRate);
			TdApiCalls.RegRspQryInstrumentOrderCommRate(_SpiHandle, _CBRspQryInstrumentOrderCommRate);
			TdApiCalls.RegRspQrySecAgentTradingAccount(_SpiHandle, _CBRspQrySecAgentTradingAccount);
			TdApiCalls.RegRspQrySecAgentCheckMode(_SpiHandle, _CBRspQrySecAgentCheckMode);
			TdApiCalls.RegRspQrySecAgentTradeInfo(_SpiHandle, _CBRspQrySecAgentTradeInfo);
			TdApiCalls.RegRspQryOptionInstrTradeCost(_SpiHandle, _CBRspQryOptionInstrTradeCost);
			TdApiCalls.RegRspQryOptionInstrCommRate(_SpiHandle, _CBRspQryOptionInstrCommRate);
			TdApiCalls.RegRspQryExecOrder(_SpiHandle, _CBRspQryExecOrder);
			TdApiCalls.RegRspQryForQuote(_SpiHandle, _CBRspQryForQuote);
			TdApiCalls.RegRspQryQuote(_SpiHandle, _CBRspQryQuote);
			TdApiCalls.RegRspQryOptionSelfClose(_SpiHandle, _CBRspQryOptionSelfClose);
			TdApiCalls.RegRspQryInvestUnit(_SpiHandle, _CBRspQryInvestUnit);
			TdApiCalls.RegRspQryCombInstrumentGuard(_SpiHandle, _CBRspQryCombInstrumentGuard);
			TdApiCalls.RegRspQryCombAction(_SpiHandle, _CBRspQryCombAction);
			TdApiCalls.RegRspQryTransferSerial(_SpiHandle, _CBRspQryTransferSerial);
			TdApiCalls.RegRspQryAccountregister(_SpiHandle, _CBRspQryAccountregister);
			TdApiCalls.RegRspError(_SpiHandle, _CBRspError);
			TdApiCalls.RegRtnOrder(_SpiHandle, _CBRtnOrder);
			TdApiCalls.RegRtnTrade(_SpiHandle, _CBRtnTrade);
			TdApiCalls.RegErrRtnOrderInsert(_SpiHandle, _CBErrRtnOrderInsert);
			TdApiCalls.RegErrRtnOrderAction(_SpiHandle, _CBErrRtnOrderAction);
			TdApiCalls.RegRtnInstrumentStatus(_SpiHandle, _CBRtnInstrumentStatus);
			TdApiCalls.RegRtnTradingNotice(_SpiHandle, _CBRtnTradingNotice);
			TdApiCalls.RegRtnErrorConditionalOrder(_SpiHandle, _CBRtnErrorConditionalOrder);
			TdApiCalls.RegRspQryContractBank(_SpiHandle, _CBRspQryContractBank);
			TdApiCalls.RegRspQryParkedOrder(_SpiHandle, _CBRspQryParkedOrder);
			TdApiCalls.RegRspQryParkedOrderAction(_SpiHandle, _CBRspQryParkedOrderAction);
			TdApiCalls.RegRspQryTradingNotice(_SpiHandle, _CBRspQryTradingNotice);
			TdApiCalls.RegRspQryBrokerTradingParams(_SpiHandle, _CBRspQryBrokerTradingParams);
			TdApiCalls.RegRspQryBrokerTradingAlgos(_SpiHandle, _CBRspQryBrokerTradingAlgos);
			TdApiCalls.RegRtnFromBankToFutureByBank(_SpiHandle, _CBRtnFromBankToFutureByBank);
			TdApiCalls.RegRtnFromFutureToBankByBank(_SpiHandle, _CBRtnFromFutureToBankByBank);
			TdApiCalls.RegRtnRepealFromBankToFutureByBank(_SpiHandle, _CBRtnRepealFromBankToFutureByBank);
			TdApiCalls.RegRtnRepealFromFutureToBankByBank(_SpiHandle, _CBRtnRepealFromFutureToBankByBank);
			TdApiCalls.RegRtnFromBankToFutureByFuture(_SpiHandle, _CBRtnFromBankToFutureByFuture);
			TdApiCalls.RegRtnFromFutureToBankByFuture(_SpiHandle, _CBRtnFromFutureToBankByFuture);
			TdApiCalls.RegRtnRepealFromBankToFutureByFutureManual(_SpiHandle, _CBRtnRepealFromBankToFutureByFutureManual);
			TdApiCalls.RegRtnRepealFromFutureToBankByFutureManual(_SpiHandle, _CBRtnRepealFromFutureToBankByFutureManual);
			TdApiCalls.RegRtnQueryBankBalanceByFuture(_SpiHandle, _CBRtnQueryBankBalanceByFuture);
			TdApiCalls.RegErrRtnBankToFutureByFuture(_SpiHandle, _CBErrRtnBankToFutureByFuture);
			TdApiCalls.RegErrRtnFutureToBankByFuture(_SpiHandle, _CBErrRtnFutureToBankByFuture);
			TdApiCalls.RegErrRtnRepealBankToFutureByFutureManual(_SpiHandle, _CBErrRtnRepealBankToFutureByFutureManual);
			TdApiCalls.RegErrRtnRepealFutureToBankByFutureManual(_SpiHandle, _CBErrRtnRepealFutureToBankByFutureManual);
			TdApiCalls.RegErrRtnQueryBankBalanceByFuture(_SpiHandle, _CBErrRtnQueryBankBalanceByFuture);
			TdApiCalls.RegRtnRepealFromBankToFutureByFuture(_SpiHandle, _CBRtnRepealFromBankToFutureByFuture);
			TdApiCalls.RegRtnRepealFromFutureToBankByFuture(_SpiHandle, _CBRtnRepealFromFutureToBankByFuture);
			TdApiCalls.RegRspFromBankToFutureByFuture(_SpiHandle, _CBRspFromBankToFutureByFuture);
			TdApiCalls.RegRspFromFutureToBankByFuture(_SpiHandle, _CBRspFromFutureToBankByFuture);
			TdApiCalls.RegRspQueryBankAccountMoneyByFuture(_SpiHandle, _CBRspQueryBankAccountMoneyByFuture);

		
		}

		//protected virtual void _OnRspError(ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		//{
		//    _MdSpi?.OnRspError(ref pRspInfo, nRequestID, bIsLast);

		//    //if (_dataCallbackDict.ContainsKey(nRequestID))
		//    //{
		//    //    var callback = _dataCallbackDict[nRequestID];
		//    //    if (callback != null)
		//    //    {
		//    //        DataResult result = new DataResult();
		//    //        _SetError(result, pRspInfo);
		//    //        _InvokeCallback(nRequestID, result);
		//    //    }
		//    //}
		//}

		protected virtual void _CbOnHeartBeatWarning(int nTimeLapse)
		{
			_Spi?.OnHeartBeatWarning(nTimeLapse);
		}

		/// <summary>
		/// 连接成功回调
		/// </summary>
		private void _OnFrontConnected()
		{
			//IsConnected = true;
			_Spi?.OnFrontConnected();
		}

		/// <summary>
		/// 断开连接回调
		/// </summary>
		/// <param name="nReason">原因</param>
		protected virtual void _OnFrontDisconnected(int nReason)
		{
			//IsConnected = false;
			_Spi?.OnFrontDisconnected(nReason);
		}

		private void _OnRspUserLogin(ref CThostFtdcRspUserLoginField pRspUserLogin, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			//if (pRspInfo.ErrorID != 0)
			//{
			//	_Erros.Add(pRspInfo);

			//	return;
			//}

			//BrokerId = pRspUserLogin.BrokerId;
			//UserId = pRspUserLogin.UserId;
			//FrontId = pRspUserLogin.FrontId;
			//SessionId = pRspUserLogin.SessionId;
			//LoginTime = DateTime.Parse(pRspUserLogin.LoginTime);

			//IsLogined = true;

			_Spi?.OnRspUserLogin(ref pRspUserLogin, ref pRspInfo, nRequestID, bIsLast);
		}

		/// <summary>
		/// 登出回调
		/// </summary>
		/// <param name="pUserLogout">登出返回结果</param>
		/// <param name="pRspInfo">错误信息</param>
		/// <param name="nRequestID">请求编号</param>
		/// <param name="bIsLast">是否为最后一条数据</param>
		private void _OnRspUserLogout(ref CThostFtdcUserLogoutField pUserLogout, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			_Spi?.OnRspUserLogout(ref pUserLogout, ref pRspInfo, nRequestID, bIsLast);

			//DataResult result = new DataResult();
			//if (pRspInfo.ErrorID > 0)
			//{
			//    _SetError(result, pRspInfo);
			//}
			//else
			//{
			//    result.IsSuccess = true;
			//}
			//_InvokeCallback(-4, result);
		}

		private void _CBRspAuthenticate(ref CThostFtdcRspAuthenticateField pRspAuthenticateField, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			_Spi?.OnRspAuthenticate(ref pRspAuthenticateField, ref pRspInfo, nRequestID, bIsLast);
		}

		///登录请求响应
		private void _CBRspUserLogin(ref CThostFtdcRspUserLoginField pRspUserLogin, ref CThostFtdcRspInfoField pRspInfo,
			int nRequestID, bool bIsLast)
		{
			_Spi?.OnRspUserLogin(ref pRspUserLogin, ref pRspInfo, nRequestID, bIsLast);
		}

		///登出请求响应
		private void _CBRspUserLogout(ref CThostFtdcUserLogoutField pUserLogout, ref CThostFtdcRspInfoField pRspInfo,
			int nRequestID, bool bIsLast)
		{
			_Spi?.OnRspUserLogout(ref pUserLogout, ref pRspInfo, nRequestID, bIsLast);
		}

		///用户口令更新请求响应
		private void _CBRspUserPasswordUpdate(ref CThostFtdcUserPasswordUpdateField pUserPasswordUpdate,
			ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			_Spi?.OnRspUserPasswordUpdate(ref pUserPasswordUpdate, ref pRspInfo, nRequestID, bIsLast);
		}

		///资金账户口令更新请求响应
		private void _CBRspTradingAccountPasswordUpdate(
			ref CThostFtdcTradingAccountPasswordUpdateField pTradingAccountPasswordUpdate,
			ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			_Spi?.OnRspTradingAccountPasswordUpdate(ref pTradingAccountPasswordUpdate, ref pRspInfo, nRequestID, bIsLast);
		}

		///查询用户当前支持的认证模式的回复
		private void _CBRspUserAuthMethod(ref CThostFtdcRspUserAuthMethodField pRspUserAuthMethod,
			ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			_Spi?.OnRspUserAuthMethod(ref pRspUserAuthMethod, ref pRspInfo, nRequestID, bIsLast);
		}
		///获取图形验证码请求的回复
		private void _CBRspGenUserCaptcha(ref CThostFtdcRspGenUserCaptchaField pRspGenUserCaptcha, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			_Spi?.OnRspGenUserCaptcha(ref pRspGenUserCaptcha, ref pRspInfo, nRequestID, bIsLast);
		}
		///获取短信验证码请求的回复
		private void _CBRspGenUserText(ref CThostFtdcRspGenUserTextField pRspGenUserText, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			_Spi?.OnRspGenUserText(ref pRspGenUserText, ref pRspInfo, nRequestID, bIsLast);
		}

		///报单录入请求响应
		private void _CBRspOrderInsert(ref CThostFtdcInputOrderField pInputOrder, ref CThostFtdcRspInfoField pRspInfo,
			int nRequestID, bool bIsLast)
		{
			_Spi?.OnRspOrderInsert(ref pInputOrder, ref pRspInfo, nRequestID, bIsLast);
		}

		///预埋单录入请求响应
		private void _CBRspParkedOrderInsert(ref CThostFtdcParkedOrderField pParkedOrder,
			ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			_Spi?.OnRspParkedOrderInsert(ref pParkedOrder, ref pRspInfo, nRequestID, bIsLast);
		}

		///预埋撤单录入请求响应
		private void _CBRspParkedOrderAction(ref CThostFtdcParkedOrderActionField pParkedOrderAction, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			_Spi?.OnRspParkedOrderAction(ref pParkedOrderAction, ref pRspInfo, nRequestID, bIsLast);
		}
		///报单操作请求响应
		private void _CBRspOrderAction(ref CThostFtdcInputOrderActionField pInputOrderAction, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			_Spi?.OnRspOrderAction(ref pInputOrderAction, ref pRspInfo, nRequestID, bIsLast);
		}
		///查询最大报单数量响应
		private void _CBRspQueryMaxOrderVolume(ref CThostFtdcQueryMaxOrderVolumeField pQueryMaxOrderVolume, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			_Spi?.OnRspQueryMaxOrderVolume(ref pQueryMaxOrderVolume, ref pRspInfo, nRequestID, bIsLast);
		}
		///投资者结算结果确认响应
		private void _CBRspSettlementInfoConfirm(ref CThostFtdcSettlementInfoConfirmField pSettlementInfoConfirm, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			_Spi?.OnRspSettlementInfoConfirm(ref pSettlementInfoConfirm, ref pRspInfo, nRequestID, bIsLast);
		}
		///删除预埋单响应
		private void _CBRspRemoveParkedOrder(ref CThostFtdcRemoveParkedOrderField pRemoveParkedOrder, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			_Spi?.OnRspRemoveParkedOrder(ref pRemoveParkedOrder, ref pRspInfo, nRequestID, bIsLast);
		}
		///删除预埋撤单响应
		private void _CBRspRemoveParkedOrderAction(ref CThostFtdcRemoveParkedOrderActionField pRemoveParkedOrderAction, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			_Spi?.OnRspRemoveParkedOrderAction(ref pRemoveParkedOrderAction, ref pRspInfo, nRequestID, bIsLast);
		}
		///执行宣告录入请求响应
		private void _CBRspExecOrderInsert(ref CThostFtdcInputExecOrderField pInputExecOrder, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			_Spi?.OnRspExecOrderInsert(ref pInputExecOrder, ref pRspInfo, nRequestID, bIsLast);
		}
		///执行宣告操作请求响应
		private void _CBRspExecOrderAction(ref CThostFtdcInputExecOrderActionField pInputExecOrderAction, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			_Spi?.OnRspExecOrderAction(ref pInputExecOrderAction, ref pRspInfo, nRequestID, bIsLast);
		}
		///询价录入请求响应
		private void _CBRspForQuoteInsert(ref CThostFtdcInputForQuoteField pInputForQuote, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			_Spi?.OnRspForQuoteInsert(ref pInputForQuote, ref pRspInfo, nRequestID, bIsLast);
		}
		///报价录入请求响应
		private void _CBRspQuoteInsert(ref CThostFtdcInputQuoteField pInputQuote, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			_Spi?.OnRspQuoteInsert(ref pInputQuote, ref pRspInfo, nRequestID, bIsLast);
		}
		///报价操作请求响应
		private void _CBRspQuoteAction(ref CThostFtdcInputQuoteActionField pInputQuoteAction, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			_Spi?.OnRspQuoteAction(ref pInputQuoteAction, ref pRspInfo, nRequestID, bIsLast);
		}
		///批量报单操作请求响应
		private void _CBRspBatchOrderAction(ref CThostFtdcInputBatchOrderActionField pInputBatchOrderAction, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			_Spi?.OnRspBatchOrderAction(ref pInputBatchOrderAction, ref pRspInfo, nRequestID, bIsLast);
		}
		///期权自对冲录入请求响应
		private void _CBRspOptionSelfCloseInsert(ref CThostFtdcInputOptionSelfCloseField pInputOptionSelfClose, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			_Spi?.OnRspOptionSelfCloseInsert(ref pInputOptionSelfClose, ref pRspInfo, nRequestID, bIsLast);
		}
		///期权自对冲操作请求响应
		private void _CBRspOptionSelfCloseAction(ref CThostFtdcInputOptionSelfCloseActionField pInputOptionSelfCloseAction, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			_Spi?.OnRspOptionSelfCloseAction(ref pInputOptionSelfCloseAction, ref pRspInfo, nRequestID, bIsLast);
		}
		///申请组合录入请求响应
		private void _CBRspCombActionInsert(ref CThostFtdcInputCombActionField pInputCombAction, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			_Spi?.OnRspCombActionInsert(ref pInputCombAction, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询报单响应
		private void _CBRspQryOrder(ref CThostFtdcOrderField pOrder, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			_Spi?.OnRspQryOrder(ref pOrder, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询成交响应
		private void _CBRspQryTrade(ref CThostFtdcTradeField pTrade, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			_Spi?.OnRspQryTrade(ref pTrade, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询投资者持仓响应
		private void _CBRspQryInvestorPosition(ref CThostFtdcInvestorPositionField pInvestorPosition, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			_Spi?.OnRspQryInvestorPosition(ref pInvestorPosition, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询资金账户响应
		private void _CBRspQryTradingAccount(ref CThostFtdcTradingAccountField pTradingAccount, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			_Spi?.OnRspQryTradingAccount(ref pTradingAccount, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询投资者响应
		private void _CBRspQryInvestor(ref CThostFtdcInvestorField pInvestor, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			_Spi?.OnRspQryInvestor(ref pInvestor, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询交易编码响应
		private void _CBRspQryTradingCode(ref CThostFtdcTradingCodeField pTradingCode, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			_Spi?.OnRspQryTradingCode(ref pTradingCode, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询合约保证金率响应
		private void _CBRspQryInstrumentMarginRate(ref CThostFtdcInstrumentMarginRateField pInstrumentMarginRate, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			_Spi?.OnRspQryInstrumentMarginRate(ref pInstrumentMarginRate, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询合约手续费率响应
		private void _CBRspQryInstrumentCommissionRate(ref CThostFtdcInstrumentCommissionRateField pInstrumentCommissionRate, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			_Spi?.OnRspQryInstrumentCommissionRate(ref pInstrumentCommissionRate, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询交易所响应
		private void _CBRspQryExchange(ref CThostFtdcExchangeField pExchange, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			_Spi?.OnRspQryExchange(ref pExchange, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询合约响应
		private void _CBRspQryInstrument(ref CThostFtdcInstrumentField pInstrument, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			_Spi?.OnRspQryInstrument(ref pInstrument, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询行情响应
		private void _CBRspQryDepthMarketData(ref CThostFtdcDepthMarketDataField pDepthMarketData, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			_Spi?.OnRspQryDepthMarketData(ref pDepthMarketData, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询投资者结算结果响应
		private void _CBRspQrySettlementInfo(ref CThostFtdcSettlementInfoField pSettlementInfo, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			_Spi?.OnRspQrySettlementInfo(ref pSettlementInfo, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询转帐银行响应
		private void _CBRspQryTransferBank(ref CThostFtdcTransferBankField pTransferBank, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			_Spi?.OnRspQryTransferBank(ref pTransferBank, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询投资者持仓明细响应
		private void _CBRspQryInvestorPositionDetail(ref CThostFtdcInvestorPositionDetailField pInvestorPositionDetail, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			_Spi?.OnRspQryInvestorPositionDetail(ref pInvestorPositionDetail, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询客户通知响应
		private void _CBRspQryNotice(ref CThostFtdcNoticeField pNotice, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			_Spi?.OnRspQryNotice(ref pNotice, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询结算信息确认响应
		private void _CBRspQrySettlementInfoConfirm(ref CThostFtdcSettlementInfoConfirmField pSettlementInfoConfirm, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			_Spi?.OnRspQrySettlementInfoConfirm(ref pSettlementInfoConfirm, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询投资者持仓明细响应
		private void _CBRspQryInvestorPositionCombineDetail(ref CThostFtdcInvestorPositionCombineDetailField pInvestorPositionCombineDetail, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			_Spi?.OnRspQryInvestorPositionCombineDetail(ref pInvestorPositionCombineDetail, ref pRspInfo, nRequestID, bIsLast);
		}
		///查询保证金监管系统经纪公司资金账户密钥响应
		private void _CBRspQryCFMMCTradingAccountKey(ref CThostFtdcCFMMCTradingAccountKeyField pCFMMCTradingAccountKey, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			_Spi?.OnRspQryCFMMCTradingAccountKey(ref pCFMMCTradingAccountKey, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询仓单折抵信息响应
		private void _CBRspQryEWarrantOffset(ref CThostFtdcEWarrantOffsetField pEWarrantOffset, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			_Spi?.OnRspQryEWarrantOffset(ref pEWarrantOffset, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询投资者品种/跨品种保证金响应
		private void _CBRspQryInvestorProductGroupMargin(ref CThostFtdcInvestorProductGroupMarginField pInvestorProductGroupMargin, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			_Spi?.OnRspQryInvestorProductGroupMargin(ref pInvestorProductGroupMargin, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询交易所保证金率响应
		private void _CBRspQryExchangeMarginRate(ref CThostFtdcExchangeMarginRateField pExchangeMarginRate, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			_Spi?.OnRspQryExchangeMarginRate(ref pExchangeMarginRate, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询交易所调整保证金率响应
		private void _CBRspQryExchangeMarginRateAdjust(ref CThostFtdcExchangeMarginRateAdjustField pExchangeMarginRateAdjust, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			_Spi?.OnRspQryExchangeMarginRateAdjust(ref pExchangeMarginRateAdjust, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询汇率响应
		private void _CBRspQryExchangeRate(ref CThostFtdcExchangeRateField pExchangeRate, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			_Spi?.OnRspQryExchangeRate(ref pExchangeRate, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询二级代理操作员银期权限响应
		private void _CBRspQrySecAgentACIDMap(ref CThostFtdcSecAgentACIDMapField pSecAgentACIDMap, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			_Spi?.OnRspQrySecAgentACIDMap(ref pSecAgentACIDMap, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询产品报价汇率
		private void _CBRspQryProductExchRate(ref CThostFtdcProductExchRateField pProductExchRate, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			_Spi?.OnRspQryProductExchRate(ref pProductExchRate, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询产品组
		private void _CBRspQryProductGroup(ref CThostFtdcProductGroupField pProductGroup, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			_Spi?.OnRspQryProductGroup(ref pProductGroup, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询做市商合约手续费率响应
		private void _CBRspQryMMInstrumentCommissionRate(ref CThostFtdcMMInstrumentCommissionRateField pMMInstrumentCommissionRate, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			_Spi?.OnRspQryMMInstrumentCommissionRate(ref pMMInstrumentCommissionRate, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询做市商期权合约手续费响应
		private void _CBRspQryMMOptionInstrCommRate(ref CThostFtdcMMOptionInstrCommRateField pMMOptionInstrCommRate, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			_Spi?.OnRspQryMMOptionInstrCommRate(ref pMMOptionInstrCommRate, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询报单手续费响应
		private void _CBRspQryInstrumentOrderCommRate(ref CThostFtdcInstrumentOrderCommRateField pInstrumentOrderCommRate, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			_Spi?.OnRspQryInstrumentOrderCommRate(ref pInstrumentOrderCommRate, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询资金账户响应
		private void _CBRspQrySecAgentTradingAccount(ref CThostFtdcTradingAccountField pTradingAccount, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			_Spi?.OnRspQrySecAgentTradingAccount(ref pTradingAccount, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询二级代理商资金校验模式响应
		private void _CBRspQrySecAgentCheckMode(ref CThostFtdcSecAgentCheckModeField pSecAgentCheckMode, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			_Spi?.OnRspQrySecAgentCheckMode(ref pSecAgentCheckMode, ref pRspInfo, nRequestID, bIsLast);

		}
		///请求查询二级代理商信息响应
		private void _CBRspQrySecAgentTradeInfo(ref CThostFtdcSecAgentTradeInfoField pSecAgentTradeInfo, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			_Spi?.OnRspQrySecAgentTradeInfo(ref pSecAgentTradeInfo, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询期权交易成本响应
		private void _CBRspQryOptionInstrTradeCost(ref CThostFtdcOptionInstrTradeCostField pOptionInstrTradeCost, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			_Spi?.OnRspQryOptionInstrTradeCost(ref pOptionInstrTradeCost, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询期权合约手续费响应
		private void _CBRspQryOptionInstrCommRate(ref CThostFtdcOptionInstrCommRateField pOptionInstrCommRate, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			_Spi?.OnRspQryOptionInstrCommRate(ref pOptionInstrCommRate, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询执行宣告响应
		private void _CBRspQryExecOrder(ref CThostFtdcExecOrderField pExecOrder, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			_Spi?.OnRspQryExecOrder(ref pExecOrder, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询询价响应
		private void _CBRspQryForQuote(ref CThostFtdcForQuoteField pForQuote, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			_Spi?.OnRspQryForQuote(ref pForQuote, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询报价响应
		private void _CBRspQryQuote(ref CThostFtdcQuoteField pQuote, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			_Spi?.OnRspQryQuote(ref pQuote, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询期权自对冲响应
		private void _CBRspQryOptionSelfClose(ref CThostFtdcOptionSelfCloseField pOptionSelfClose, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			_Spi?.OnRspQryOptionSelfClose(ref pOptionSelfClose, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询投资单元响应
		private void _CBRspQryInvestUnit(ref CThostFtdcInvestUnitField pInvestUnit, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			_Spi?.OnRspQryInvestUnit(ref pInvestUnit, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询组合合约安全系数响应
		private void _CBRspQryCombInstrumentGuard(ref CThostFtdcCombInstrumentGuardField pCombInstrumentGuard, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			_Spi?.OnRspQryCombInstrumentGuard(ref pCombInstrumentGuard, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询申请组合响应
		private void _CBRspQryCombAction(ref CThostFtdcCombActionField pCombAction, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			_Spi?.OnRspQryCombAction(ref pCombAction, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询转帐流水响应
		private void _CBRspQryTransferSerial(ref CThostFtdcTransferSerialField pTransferSerial, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			_Spi?.OnRspQryTransferSerial(ref pTransferSerial, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询银期签约关系响应
		private void _CBRspQryAccountregister(ref CThostFtdcAccountregisterField pAccountregister, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			_Spi?.OnRspQryAccountregister(ref pAccountregister, ref pRspInfo, nRequestID, bIsLast);
		}
		///错误应答
		private void _CBRspError(ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			_Spi?.OnRspError(ref pRspInfo, nRequestID, bIsLast);
		}
		///报单通知
		private void _CBRtnOrder(ref CThostFtdcOrderField pOrder)
		{
			_Spi?.OnRtnOrder(ref pOrder);
		}
		///成交通知
		private void _CBRtnTrade(ref CThostFtdcTradeField pTrade)
		{
			_Spi?.OnRtnTrade(ref pTrade);
		}
		///报单录入错误回报
		private void _CBErrRtnOrderInsert(ref CThostFtdcInputOrderField pInputOrder, ref CThostFtdcRspInfoField pRspInfo)
		{
			_Spi?.OnErrRtnOrderInsert(ref pInputOrder, ref pRspInfo);
		}
		///报单操作错误回报
		private void _CBErrRtnOrderAction(ref CThostFtdcOrderActionField pOrderAction, ref CThostFtdcRspInfoField pRspInfo)
		{
			_Spi?.OnErrRtnOrderAction(ref pOrderAction, ref pRspInfo);
		}
		///合约交易状态通知
		private void _CBRtnInstrumentStatus(ref CThostFtdcInstrumentStatusField pInstrumentStatus)
		{
			_Spi?.OnRtnInstrumentStatus(ref pInstrumentStatus);
		}
		///交易通知
		private void _CBRtnTradingNotice(ref CThostFtdcTradingNoticeInfoField pTradingNoticeInfo)
		{
			_Spi?.OnRtnTradingNotice(ref pTradingNoticeInfo);
		}
		///提示条件单校验错误
		private void _CBRtnErrorConditionalOrder(ref CThostFtdcErrorConditionalOrderField pErrorConditionalOrder)
		{
			_Spi?.OnRtnErrorConditionalOrder(ref pErrorConditionalOrder);
		}
		///执行宣告通知
		private void _CBRtnExecOrder(ref CThostFtdcExecOrderField pExecOrder)
		{
			_Spi?.OnRtnExecOrder(ref pExecOrder);
		}
		///执行宣告录入错误回报
		private void _CBErrRtnExecOrderInsert(ref CThostFtdcInputExecOrderField pInputExecOrder, ref CThostFtdcRspInfoField pRspInfo)
		{
			_Spi?.OnErrRtnExecOrderInsert(ref pInputExecOrder, ref pRspInfo);
		}
		///执行宣告操作错误回报
		private void _CBErrRtnExecOrderAction(ref CThostFtdcExecOrderActionField pExecOrderAction, ref CThostFtdcRspInfoField pRspInfo)
		{
			_Spi?.OnErrRtnExecOrderAction(ref pExecOrderAction, ref pRspInfo);
		}
		///询价录入错误回报
		private void _CBErrRtnForQuoteInsert(ref CThostFtdcInputForQuoteField pInputForQuote, ref CThostFtdcRspInfoField pRspInfo)
		{
			_Spi?.OnErrRtnForQuoteInsert(ref pInputForQuote, ref pRspInfo);
		}
		///报价通知
		private void _CBRtnQuote(ref CThostFtdcQuoteField pQuote)
		{
			_Spi?.OnRtnQuote(ref pQuote);
		}
		///报价录入错误回报
		private void _CBErrRtnQuoteInsert(ref CThostFtdcInputQuoteField pInputQuote, ref CThostFtdcRspInfoField pRspInfo)
		{
			_Spi?.OnErrRtnQuoteInsert(ref pInputQuote, ref pRspInfo);
		}
		///报价操作错误回报
		private void _CBErrRtnQuoteAction(ref CThostFtdcQuoteActionField pQuoteAction, ref CThostFtdcRspInfoField pRspInfo)
		{
			_Spi?.OnErrRtnQuoteAction(ref pQuoteAction, ref pRspInfo);
		}
		///询价通知
		private void _CBRtnForQuoteRsp(ref CThostFtdcForQuoteRspField pForQuoteRsp)
		{
			_Spi?.OnRtnForQuoteRsp(ref pForQuoteRsp);
		}
		///保证金监控中心用户令牌
		private void _CBRtnCFMMCTradingAccountToken(ref CThostFtdcCFMMCTradingAccountTokenField pCFMMCTradingAccountToken)
		{
			_Spi?.OnRtnCFMMCTradingAccountToken(ref pCFMMCTradingAccountToken);
		}
		///批量报单操作错误回报
		private void _CBErrRtnBatchOrderAction(ref CThostFtdcBatchOrderActionField pBatchOrderAction, ref CThostFtdcRspInfoField pRspInfo)
		{
			_Spi?.OnErrRtnBatchOrderAction(ref pBatchOrderAction, ref pRspInfo);
		}
		///期权自对冲通知
		private void _CBRtnOptionSelfClose(ref CThostFtdcOptionSelfCloseField pOptionSelfClose)
		{
			_Spi?.OnRtnOptionSelfClose(ref pOptionSelfClose);
		}
		///期权自对冲录入错误回报
		private void _CBErrRtnOptionSelfCloseInsert(ref CThostFtdcInputOptionSelfCloseField pInputOptionSelfClose, ref CThostFtdcRspInfoField pRspInfo)
		{
			_Spi?.OnErrRtnOptionSelfCloseInsert(ref pInputOptionSelfClose, ref pRspInfo);
		}
		///期权自对冲操作错误回报
		private void _CBErrRtnOptionSelfCloseAction(ref CThostFtdcOptionSelfCloseActionField pOptionSelfCloseAction, ref CThostFtdcRspInfoField pRspInfo)
		{
			_Spi?.OnErrRtnOptionSelfCloseAction(ref pOptionSelfCloseAction, ref pRspInfo);
		}
		///申请组合通知
		private void _CBRtnCombAction(ref CThostFtdcCombActionField pCombAction)
		{
			_Spi?.OnRtnCombAction(ref pCombAction);
		}
		///申请组合录入错误回报
		private void _CBErrRtnCombActionInsert(ref CThostFtdcInputCombActionField pInputCombAction, ref CThostFtdcRspInfoField pRspInfo)
		{
			_Spi?.OnErrRtnCombActionInsert(ref pInputCombAction, ref pRspInfo);
		}
		///请求查询签约银行响应
		private void _CBRspQryContractBank(ref CThostFtdcContractBankField pContractBank, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			_Spi?.OnRspQryContractBank(ref pContractBank, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询预埋单响应
		private void _CBRspQryParkedOrder(ref CThostFtdcParkedOrderField pParkedOrder, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			_Spi?.OnRspQryParkedOrder(ref pParkedOrder, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询预埋撤单响应
		private void _CBRspQryParkedOrderAction(ref CThostFtdcParkedOrderActionField pParkedOrderAction, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			_Spi?.OnRspQryParkedOrderAction(ref pParkedOrderAction, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询交易通知响应
		private void _CBRspQryTradingNotice(ref CThostFtdcTradingNoticeField pTradingNotice, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			_Spi?.OnRspQryTradingNotice(ref pTradingNotice, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询经纪公司交易参数响应
		private void _CBRspQryBrokerTradingParams(ref CThostFtdcBrokerTradingParamsField pBrokerTradingParams, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			_Spi?.OnRspQryBrokerTradingParams(ref pBrokerTradingParams, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询经纪公司交易算法响应
		private void _CBRspQryBrokerTradingAlgos(ref CThostFtdcBrokerTradingAlgosField pBrokerTradingAlgos, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			_Spi?.OnRspQryBrokerTradingAlgos(ref pBrokerTradingAlgos, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询监控中心用户令牌
		private void _CBRspQueryCFMMCTradingAccountToken(ref CThostFtdcQueryCFMMCTradingAccountTokenField pQueryCFMMCTradingAccountToken, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			_Spi?.OnRspQueryCFMMCTradingAccountToken(ref pQueryCFMMCTradingAccountToken, ref pRspInfo, nRequestID, bIsLast);
		}
		///银行发起银行资金转期货通知
		private void _CBRtnFromBankToFutureByBank(ref CThostFtdcRspTransferField pRspTransfer)
		{
			_Spi?.OnRtnFromBankToFutureByBank(ref pRspTransfer);
		}
		///银行发起期货资金转银行通知
		private void _CBRtnFromFutureToBankByBank(ref CThostFtdcRspTransferField pRspTransfer)
		{
			_Spi?.OnRtnFromFutureToBankByBank(ref pRspTransfer);
		}
		///银行发起冲正银行转期货通知
		private void _CBRtnRepealFromBankToFutureByBank(ref CThostFtdcRspRepealField pRspRepeal)
		{
			_Spi?.OnRtnRepealFromBankToFutureByBank(ref pRspRepeal);
		}
		///银行发起冲正期货转银行通知
		private void _CBRtnRepealFromFutureToBankByBank(ref CThostFtdcRspRepealField pRspRepeal)
		{
			_Spi?.OnRtnRepealFromFutureToBankByBank(ref pRspRepeal);
		}
		///期货发起银行资金转期货通知
		private void _CBRtnFromBankToFutureByFuture(ref CThostFtdcRspTransferField pRspTransfer)
		{
			_Spi?.OnRtnFromBankToFutureByFuture(ref pRspTransfer);
		}
		///期货发起期货资金转银行通知
		private void _CBRtnFromFutureToBankByFuture(ref CThostFtdcRspTransferField pRspTransfer)
		{
			_Spi?.OnRtnFromFutureToBankByFuture(ref pRspTransfer);
		}
		///系统运行时期货端手工发起冲正银行转期货请求，银行处理完毕后报盘发回的通知
		private void _CBRtnRepealFromBankToFutureByFutureManual(ref CThostFtdcRspRepealField pRspRepeal)
		{
			_Spi?.OnRtnRepealFromBankToFutureByFutureManual(ref pRspRepeal);
		}
		///系统运行时期货端手工发起冲正期货转银行请求，银行处理完毕后报盘发回的通知
		private void _CBRtnRepealFromFutureToBankByFutureManual(ref CThostFtdcRspRepealField pRspRepeal)
		{
			_Spi?.OnRtnRepealFromFutureToBankByFutureManual(ref pRspRepeal);
		}
		///期货发起查询银行余额通知
		private void _CBRtnQueryBankBalanceByFuture(ref CThostFtdcNotifyQueryAccountField pNotifyQueryAccount)
		{
			_Spi?.OnRtnQueryBankBalanceByFuture(ref pNotifyQueryAccount);
		}
		///期货发起银行资金转期货错误回报
		private void _CBErrRtnBankToFutureByFuture(ref CThostFtdcReqTransferField pReqTransfer, ref CThostFtdcRspInfoField pRspInfo)
		{
			_Spi?.OnErrRtnBankToFutureByFuture(ref pReqTransfer, ref pRspInfo);
		}
		///期货发起期货资金转银行错误回报
		private void _CBErrRtnFutureToBankByFuture(ref CThostFtdcReqTransferField pReqTransfer, ref CThostFtdcRspInfoField pRspInfo)
		{
			_Spi?.OnErrRtnFutureToBankByFuture(ref pReqTransfer, ref pRspInfo);
		}
		///系统运行时期货端手工发起冲正银行转期货错误回报
		private void _CBErrRtnRepealBankToFutureByFutureManual(ref CThostFtdcReqRepealField pReqRepeal, ref CThostFtdcRspInfoField pRspInfo)
		{
			_Spi?.OnErrRtnRepealBankToFutureByFutureManual(ref pReqRepeal, ref pRspInfo);
		}
		///系统运行时期货端手工发起冲正期货转银行错误回报
		private void _CBErrRtnRepealFutureToBankByFutureManual(ref CThostFtdcReqRepealField pReqRepeal, ref CThostFtdcRspInfoField pRspInfo)
		{
			_Spi?.OnErrRtnRepealFutureToBankByFutureManual(ref pReqRepeal, ref pRspInfo);
		}
		///期货发起查询银行余额错误回报
		private void _CBErrRtnQueryBankBalanceByFuture(ref CThostFtdcReqQueryAccountField pReqQueryAccount, ref CThostFtdcRspInfoField pRspInfo)
		{
			_Spi?.OnErrRtnQueryBankBalanceByFuture(ref pReqQueryAccount, ref pRspInfo);
		}
		///期货发起冲正银行转期货请求，银行处理完毕后报盘发回的通知
		private void _CBRtnRepealFromBankToFutureByFuture(ref CThostFtdcRspRepealField pRspRepeal)
		{
			_Spi?.OnRtnRepealFromBankToFutureByFuture(ref pRspRepeal);
		}
		///期货发起冲正期货转银行请求，银行处理完毕后报盘发回的通知
		private void _CBRtnRepealFromFutureToBankByFuture(ref CThostFtdcRspRepealField pRspRepeal)
		{
			_Spi?.OnRtnRepealFromFutureToBankByFuture(ref pRspRepeal);
		}
		///期货发起银行资金转期货应答
		private void _CBRspFromBankToFutureByFuture(ref CThostFtdcReqTransferField pReqTransfer, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			_Spi?.OnRspFromBankToFutureByFuture(ref pReqTransfer, ref pRspInfo, nRequestID, bIsLast);
		}
		///期货发起期货资金转银行应答
		private void _CBRspFromFutureToBankByFuture(ref CThostFtdcReqTransferField pReqTransfer, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			_Spi?.OnRspFromFutureToBankByFuture(ref pReqTransfer, ref pRspInfo, nRequestID, bIsLast);
		}
		///期货发起查询银行余额应答
		private void _CBRspQueryBankAccountMoneyByFuture(ref CThostFtdcReqQueryAccountField pReqQueryAccount, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			_Spi?.OnRspQueryBankAccountMoneyByFuture(ref pReqQueryAccount, ref pRspInfo, nRequestID, bIsLast);
		}
		///银行发起银期开户通知
		private void _CBRtnOpenAccountByBank(ref CThostFtdcOpenAccountField pOpenAccount)
		{
			_Spi?.OnRtnOpenAccountByBank(ref pOpenAccount);
		}
		///银行发起银期销户通知
		private void _CBRtnCancelAccountByBank(ref CThostFtdcCancelAccountField pCancelAccount)
		{
			_Spi?.OnRtnCancelAccountByBank(ref pCancelAccount);
		}
		///银行发起变更银行账号通知
		private void _CBRtnChangeAccountByBank(ref CThostFtdcChangeAccountField pChangeAccount)
		{
			_Spi?.OnRtnChangeAccountByBank(ref pChangeAccount);
		}



		#endregion




		#region Members
		/// <summary>
		/// 交易类句柄
		/// </summary>
		private IntPtr _ApiHandle = IntPtr.Zero;
        private IntPtr _SpiHandle = IntPtr.Zero;   // C++ MdSpi Wrapper class


      /// <summary>
        /// 回调方法字典
        /// </summary>
        private ConcurrentDictionary<int, object> _dataDict = new ConcurrentDictionary<int, object>();

        /// <summary>
        /// 数据回调字典
        /// </summary>
        private ConcurrentDictionary<int, object> _dataCallbackDict = new ConcurrentDictionary<int, object>();


        private ICtpTdSpi _Spi;


        protected string    _BrokerID;
        protected string    _UserID;
        protected string    _Password;
        protected string    _FrontAddress;

		/// <summary>
		/// 前置编号
		/// </summary>
		protected int       _FrontID;

		/// <summary>
		/// 会话编号
		/// </summary>
		protected int       _SessionID;

		/// <summary>
		/// 最大报单引用
		/// </summary>
		protected string    _MaxOrderRef;
#endregion
	}
}
