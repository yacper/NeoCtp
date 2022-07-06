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
using System.Threading;
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

        public string FlowPath    { get => FlowPath_;    set => SetProperty(ref FlowPath_, value); }

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

//        public string MaxOrderRef { get => OrderRef_; protected set => SetProperty(ref OrderRef_, value); }                           /// 最大报单引用

        public bool IsLogined { get { return _IsLogined; } protected set { SetProperty(ref _IsLogined, value); } }

        public DateTime LoginTime     { get => LoginTime_; protected set => SetProperty(ref LoginTime_, value); }

        public TimeSpan LoginDuration { get => IsLogined ? DateTime.Now - LoginTime : TimeSpan.Zero; }

        public DateTime SHFETime { get=>SHFETime_ + LoginDuration;   protected set => SetProperty(ref SHFETime_, value); }
        public DateTime DCETime  { get=>DCETime_+ LoginDuration;     protected set => SetProperty(ref DCETime_, value); }
        public DateTime CZCETime { get => CZCETime_ + LoginDuration; protected set => SetProperty(ref CZCETime_, value); }
        public DateTime FFEXTime { get=>FFEXTime_+LoginDuration;     protected set => SetProperty(ref FFEXTime_, value); }
        public DateTime INETime  { get => INETime_ + LoginDuration;  protected set => SetProperty(ref INETime_, value); }

	    protected int GetNextRequestId() => Interlocked.Increment(ref RequestID_);
        protected int GetNextOrderRef() => Interlocked.Increment(ref OrderRef_);
	
     
		/// 是否已登录


		///注册回调接口
		///@param pSpi 派生自回调接口类的实例
		public void RegisterSpi(ICtpTdSpi pSpi)
		{
			TdSpi_ = pSpi;
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
			TdApiCalls.Release(ApiHandle_);
		}

		///初始化
		///@remark 初始化运行环境,只有调用后,接口才开始工作
		public void Init(){TdApiCalls.Init(ApiHandle_);}

		///等待接口线程结束运行
		///@return 线程退出代码
		public int Join()
		{
			return TdApiCalls.Join(ApiHandle_);}

		///获取当前交易日
		///@retrun 获取到的交易日
		///@remark 只有登录成功后,才能得到正确的交易日
		public string GetTradingDay()
		{
			IntPtr ptr = TdApiCalls.GetTradingDay(ApiHandle_);

            return Marshal.PtrToStringUTF8(ptr);
			//return Marshal.PtrToStringAnsi(ptr);
		}

		///注册前置机网络地址
		///@param pszFrontAddress：前置机网络地址。
		///@remark 网络地址的格式为：“protocol://ipaddress:port”，如：”tcp://127.0.0.1:17001”。 
		///@remark “tcp”代表传输协议，“127.0.0.1”代表服务器地址。”17001”代表服务器端口号。
		public void RegisterFront(string pszFrontAddress)
		{
			FrontAddress = pszFrontAddress;
			TdApiCalls.RegisterFront(ApiHandle_, pszFrontAddress);
		}

		///注册名字服务器网络地址
		///@param pszNsAddress：名字服务器网络地址。
		///@remark 网络地址的格式为：“protocol://ipaddress:port”，如：”tcp://127.0.0.1:12001”。 
		///@remark “tcp”代表传输协议，“127.0.0.1”代表服务器地址。”12001”代表服务器端口号。
		///@remark RegisterNameServer优先于RegisterFront
		public void RegisterNameServer(string pszNsAddress)
		{
			TdApiCalls.RegisterFront(ApiHandle_, pszNsAddress);
		}

		///注册名字服务器用户信息
		///@param pFensUserInfo：用户信息。
		public void RegisterFensUserInfo(ref CThostFtdcFensUserInfoField pFensUserInfo)
		{
			BrokerId = pFensUserInfo.BrokerID;
			UserId = pFensUserInfo.UserID;
			TdApiCalls.RegisterFensUserInfo(ApiHandle_, ref pFensUserInfo);
		}



		///订阅私有流。
		///@param nResumeType 私有流重传方式  
		///        THOST_TERT_RESTART:从本交易日开始重传
		///        THOST_TERT_RESUME:从上次收到的续传
		///        THOST_TERT_QUICK:只传送登录后私有流的内容
		///@remark 该方法要在Init方法前调用。若不调用则不会收到私有流的数据。
		public void SubscribePrivateTopic(THOST_TE_RESUME_TYPE nResumeType)
		{
			TdApiCalls.SubscribePrivateTopic(ApiHandle_, nResumeType);
		}

		///订阅公共流。
		///@param nResumeType 公共流重传方式  
		///        THOST_TERT_RESTART:从本交易日开始重传
		///        THOST_TERT_RESUME:从上次收到的续传
		///        THOST_TERT_QUICK:只传送登录后公共流的内容
		///@remark 该方法要在Init方法前调用。若不调用则不会收到公共流的数据。
		public void SubscribePublicTopic(THOST_TE_RESUME_TYPE nResumeType)
		{
			TdApiCalls.SubscribePublicTopic(ApiHandle_, nResumeType);
		}

		///客户端认证请求
		public int ReqAuthenticate(ref CThostFtdcReqAuthenticateField pReqAuthenticateField, int nRequestID)
		{
			return TdApiCalls.ReqAuthenticate(ApiHandle_, ref pReqAuthenticateField, nRequestID);
		}

		///注册用户终端信息，用于中继服务器多连接模式
		///需要在终端认证成功后，用户登录前调用该接口
		public int RegisterUserSystemInfo(ref CThostFtdcUserSystemInfoField pUserSystemInfo)
		{
			return TdApiCalls.RegisterUserSystemInfo(ApiHandle_, ref pUserSystemInfo);
		}

		///上报用户终端信息，用于中继服务器操作员登录模式
		///操作员登录后，可以多次调用该接口上报客户信息
		public int SubmitUserSystemInfo(ref CThostFtdcUserSystemInfoField pUserSystemInfo)
		{
			return TdApiCalls.SubmitUserSystemInfo(ApiHandle_, ref pUserSystemInfo);
		}

		///用户登录请求
		public int ReqUserLogin(ref CThostFtdcReqUserLoginField pReqUserLoginField, int nRequestID)
		{
			return TdApiCalls.ReqUserLogin(ApiHandle_, ref pReqUserLoginField, nRequestID);
		}

		///登出请求
		public int ReqUserLogout(ref CThostFtdcUserLogoutField pUserLogout, int nRequestID)
		{
			return TdApiCalls.ReqUserLogout(ApiHandle_, ref pUserLogout, nRequestID);
		}

		///用户口令更新请求
		public int ReqUserPasswordUpdate(ref CThostFtdcUserPasswordUpdateField pUserPasswordUpdate, int nRequestID)
		{
			return TdApiCalls.ReqUserPasswordUpdate(ApiHandle_, ref pUserPasswordUpdate, nRequestID);
		}

		///资金账户口令更新请求
		public int ReqTradingAccountPasswordUpdate(ref CThostFtdcTradingAccountPasswordUpdateField pTradingAccountPasswordUpdate, int nRequestID)
		{
			return TdApiCalls.ReqTradingAccountPasswordUpdate(ApiHandle_, ref pTradingAccountPasswordUpdate, nRequestID);
		}

		///查询用户当前支持的认证模式
		public int ReqUserAuthMethod(ref CThostFtdcReqUserAuthMethodField pReqUserAuthMethod, int nRequestID)
		{
			return TdApiCalls.ReqUserAuthMethod(ApiHandle_, ref pReqUserAuthMethod, nRequestID);
		}

		///用户发出获取图形验证码请求
		public int ReqGenUserCaptcha(ref CThostFtdcReqGenUserCaptchaField pReqGenUserCaptcha, int nRequestID)
		{
			return TdApiCalls.ReqGenUserCaptcha(ApiHandle_, ref pReqGenUserCaptcha, nRequestID);
		}

		///用户发出获取短信验证码请求
		public int ReqGenUserText(ref CThostFtdcReqGenUserTextField pReqGenUserText, int nRequestID)
		{
			return TdApiCalls.ReqGenUserText(ApiHandle_, ref pReqGenUserText, nRequestID);
		}

		///用户发出带有图片验证码的登陆请求
		public int ReqUserLoginWithCaptcha(ref CThostFtdcReqUserLoginWithCaptchaField pReqUserLoginWithCaptcha,
			int nRequestID)
		{
			return TdApiCalls.ReqUserLoginWithCaptcha(ApiHandle_, ref pReqUserLoginWithCaptcha, nRequestID);
		}

		///用户发出带有短信验证码的登陆请求
		public int ReqUserLoginWithText(ref CThostFtdcReqUserLoginWithTextField pReqUserLoginWithText, int nRequestID)
		{
			return TdApiCalls.ReqUserLoginWithText(ApiHandle_, ref pReqUserLoginWithText, nRequestID);
		}

		///用户发出带有动态口令的登陆请求
		public int ReqUserLoginWithOTP(ref CThostFtdcReqUserLoginWithOTPField pReqUserLoginWithOTP, int nRequestID)
		{
			return TdApiCalls.ReqUserLoginWithOTP(ApiHandle_, ref pReqUserLoginWithOTP, nRequestID);
		}

		///报单录入请求
		public int ReqOrderInsert(ref CThostFtdcInputOrderField pInputOrder, int nRequestID)
		{
			return TdApiCalls.ReqOrderInsert(ApiHandle_, ref pInputOrder, nRequestID);
		}

		///预埋单录入请求
		public int ReqParkedOrderInsert(ref CThostFtdcParkedOrderField pParkedOrder, int nRequestID)
		{
			return TdApiCalls.ReqParkedOrderInsert(ApiHandle_, ref pParkedOrder, nRequestID);
		}

		///预埋撤单录入请求
		public int ReqParkedOrderAction(ref CThostFtdcParkedOrderActionField pParkedOrderAction, int nRequestID)
		{
			return TdApiCalls.ReqParkedOrderAction(ApiHandle_, ref pParkedOrderAction, nRequestID);
		}

		///报单操作请求
		public int ReqOrderAction(ref CThostFtdcInputOrderActionField pInputOrderAction, int nRequestID)
		{
			return TdApiCalls.ReqOrderAction(ApiHandle_, ref pInputOrderAction, nRequestID);
		}

		///查询最大报单数量请求
		public int ReqQueryMaxOrderVolume(ref CThostFtdcQueryMaxOrderVolumeField pQueryMaxOrderVolume, int nRequestID)
		{
			return TdApiCalls.ReqQueryMaxOrderVolume(ApiHandle_, ref pQueryMaxOrderVolume, nRequestID);
		}

		///投资者结算结果确认
		public int ReqSettlementInfoConfirm(ref CThostFtdcSettlementInfoConfirmField pSettlementInfoConfirm, int nRequestID)
		{
			return TdApiCalls.ReqSettlementInfoConfirm(ApiHandle_, ref pSettlementInfoConfirm, nRequestID);
		}

		///请求删除预埋单
		public int ReqRemoveParkedOrder(ref CThostFtdcRemoveParkedOrderField pRemoveParkedOrder, int nRequestID)
		{
			return TdApiCalls.ReqRemoveParkedOrder(ApiHandle_, ref pRemoveParkedOrder, nRequestID);
		}

		///请求删除预埋撤单
		public int ReqRemoveParkedOrderAction(ref CThostFtdcRemoveParkedOrderActionField pRemoveParkedOrderAction,
			int nRequestID)
		{
			return TdApiCalls.ReqRemoveParkedOrderAction(ApiHandle_, ref pRemoveParkedOrderAction, nRequestID);
		}

		///执行宣告录入请求
		public int ReqExecOrderInsert(ref CThostFtdcInputExecOrderField pInputExecOrder, int nRequestID)
		{
			return TdApiCalls.ReqExecOrderInsert(ApiHandle_, ref pInputExecOrder, nRequestID);
		}

		///执行宣告操作请求
		public int ReqExecOrderAction(ref CThostFtdcInputExecOrderActionField pInputExecOrderAction, int nRequestID)
		{
			return TdApiCalls.ReqExecOrderAction(ApiHandle_, ref pInputExecOrderAction, nRequestID);
		}

		///询价录入请求
		public int ReqForQuoteInsert(ref CThostFtdcInputForQuoteField pInputForQuote, int nRequestID)
		{
			return TdApiCalls.ReqForQuoteInsert(ApiHandle_, ref pInputForQuote, nRequestID);
		}

		///报价录入请求
		public int ReqQuoteInsert(ref CThostFtdcInputQuoteField pInputQuote, int nRequestID)
		{
			return TdApiCalls.ReqQuoteInsert(ApiHandle_, ref pInputQuote, nRequestID);
		}

		///报价操作请求
		public int ReqQuoteAction(ref CThostFtdcInputQuoteActionField pInputQuoteAction, int nRequestID)
		{
			return TdApiCalls.ReqQuoteAction(ApiHandle_, ref pInputQuoteAction, nRequestID);
		}

		///批量报单操作请求
		public int ReqBatchOrderAction(ref CThostFtdcInputBatchOrderActionField pInputBatchOrderAction, int nRequestID)
		{
			return TdApiCalls.ReqBatchOrderAction(ApiHandle_, ref pInputBatchOrderAction, nRequestID);
		}

		///期权自对冲录入请求
		public int ReqOptionSelfCloseInsert(ref CThostFtdcInputOptionSelfCloseField pInputOptionSelfClose,
			int nRequestID)
		{
			return TdApiCalls.ReqOptionSelfCloseInsert(ApiHandle_, ref pInputOptionSelfClose, nRequestID);
		}

		///期权自对冲操作请求
		public int ReqOptionSelfCloseAction(ref CThostFtdcInputOptionSelfCloseActionField pInputOptionSelfCloseAction,
			int nRequestID)
		{
			return TdApiCalls.ReqOptionSelfCloseAction(ApiHandle_, ref pInputOptionSelfCloseAction, nRequestID);
		}

		///申请组合录入请求
		public int ReqCombActionInsert(ref CThostFtdcInputCombActionField pInputCombAction, int nRequestID)
		{
			return TdApiCalls.ReqCombActionInsert(ApiHandle_, ref pInputCombAction, nRequestID);
		}

		///请求查询报单
		public int ReqQryOrder(ref CThostFtdcQryOrderField pQryOrder, int nRequestID)
		{
			return TdApiCalls.ReqQryOrder(ApiHandle_, ref pQryOrder, nRequestID);
		}

		///请求查询成交
		public int ReqQryTrade(ref CThostFtdcQryTradeField pQryTrade, int nRequestID)
		{
			return TdApiCalls.ReqQryTrade(ApiHandle_, ref pQryTrade, nRequestID);
		}

		///请求查询投资者持仓
		public int ReqQryInvestorPosition(ref CThostFtdcQryInvestorPositionField pQryInvestorPosition, int nRequestID)
		{
			return TdApiCalls.ReqQryInvestorPosition(ApiHandle_, ref pQryInvestorPosition, nRequestID);
		}

		///请求查询资金账户
		public int ReqQryTradingAccount(ref CThostFtdcQryTradingAccountField pQryTradingAccount, int nRequestID)
		{
			return TdApiCalls.ReqQryTradingAccount(ApiHandle_, ref pQryTradingAccount, nRequestID);
		}

		///请求查询投资者
		public int ReqQryInvestor(ref CThostFtdcQryInvestorField pQryInvestor, int nRequestID)
		{
			return TdApiCalls.ReqQryInvestor(ApiHandle_, ref pQryInvestor, nRequestID);
		}

		///请求查询交易编码
		public int ReqQryTradingCode(ref CThostFtdcQryTradingCodeField pQryTradingCode, int nRequestID)
		{
			return TdApiCalls.ReqQryTradingCode(ApiHandle_, ref pQryTradingCode, nRequestID);
		}

		///请求查询合约保证金率
		public int ReqQryInstrumentMarginRate(ref CThostFtdcQryInstrumentMarginRateField pQryInstrumentMarginRate,
			int nRequestID)
		{
			return TdApiCalls.ReqQryInstrumentMarginRate(ApiHandle_, ref pQryInstrumentMarginRate, nRequestID);
		}

		///请求查询合约手续费率
		public int ReqQryInstrumentCommissionRate(
			ref CThostFtdcQryInstrumentCommissionRateField pQryInstrumentCommissionRate, int nRequestID)
		{
			return TdApiCalls.ReqQryInstrumentCommissionRate(ApiHandle_, ref pQryInstrumentCommissionRate, nRequestID);
		}

		///请求查询交易所
		public int ReqQryExchange(ref CThostFtdcQryExchangeField pQryExchange, int nRequestID)
		{
			return TdApiCalls.ReqQryExchange(ApiHandle_, ref pQryExchange, nRequestID);
		}

		///请求查询产品
		public int ReqQryProduct(ref CThostFtdcQryProductField pQryProduct, int nRequestID)
		{
			return TdApiCalls.ReqQryProduct(ApiHandle_, ref pQryProduct, nRequestID);
		}

		///请求查询合约
		public int ReqQryInstrument(ref CThostFtdcQryInstrumentField pQryInstrument, int nRequestID)
		{
			return TdApiCalls.ReqQryInstrument(ApiHandle_, ref pQryInstrument, nRequestID);
		}

		///请求查询行情
		public int ReqQryDepthMarketData(ref CThostFtdcQryDepthMarketDataField pQryDepthMarketData, int nRequestID)
		{
			return TdApiCalls.ReqQryDepthMarketData(ApiHandle_, ref pQryDepthMarketData, nRequestID);
		}

		///请求查询投资者结算结果
		public int ReqQrySettlementInfo(ref CThostFtdcQrySettlementInfoField pQrySettlementInfo, int nRequestID)
		{
			return TdApiCalls.ReqQrySettlementInfo(ApiHandle_, ref pQrySettlementInfo, nRequestID);
		}

		///请求查询转帐银行
		public int ReqQryTransferBank(ref CThostFtdcQryTransferBankField pQryTransferBank, int nRequestID)
		{
			return TdApiCalls.ReqQryTransferBank(ApiHandle_, ref pQryTransferBank, nRequestID);
		}

		///请求查询投资者持仓明细
		public int ReqQryInvestorPositionDetail(ref CThostFtdcQryInvestorPositionDetailField pQryInvestorPositionDetail,
			int nRequestID)
		{
			return TdApiCalls.ReqQryInvestorPositionDetail(ApiHandle_, ref pQryInvestorPositionDetail, nRequestID);
		}

		///请求查询客户通知
		public int ReqQryNotice(ref CThostFtdcQryNoticeField pQryNotice, int nRequestID)
		{
			return TdApiCalls.ReqQryNotice(ApiHandle_, ref pQryNotice, nRequestID);
		}

		///请求查询结算信息确认
		public int ReqQrySettlementInfoConfirm(ref CThostFtdcQrySettlementInfoConfirmField pQrySettlementInfoConfirm,
			int nRequestID)
		{
			return TdApiCalls.ReqQrySettlementInfoConfirm(ApiHandle_, ref pQrySettlementInfoConfirm, nRequestID);
		}

		///请求查询投资者持仓明细
		public int ReqQryInvestorPositionCombineDetail(
			ref CThostFtdcQryInvestorPositionCombineDetailField pQryInvestorPositionCombineDetail, int nRequestID)
		{
			return TdApiCalls.ReqQryInvestorPositionCombineDetail(ApiHandle_, ref pQryInvestorPositionCombineDetail,
				nRequestID);
		}

		///请求查询保证金监管系统经纪公司资金账户密钥
		public int ReqQryCFMMCTradingAccountKey(ref CThostFtdcQryCFMMCTradingAccountKeyField pQryCFMMCTradingAccountKey,
			int nRequestID)
		{
			return TdApiCalls.ReqQryCFMMCTradingAccountKey(ApiHandle_, ref pQryCFMMCTradingAccountKey, nRequestID);
		}

		///请求查询仓单折抵信息
		public int ReqQryEWarrantOffset(ref CThostFtdcQryEWarrantOffsetField pQryEWarrantOffset, int nRequestID)
		{
			return TdApiCalls.ReqQryEWarrantOffset(ApiHandle_, ref pQryEWarrantOffset, nRequestID);
		}

		///请求查询投资者品种/跨品种保证金
		public int ReqQryInvestorProductGroupMargin(
			ref CThostFtdcQryInvestorProductGroupMarginField pQryInvestorProductGroupMargin, int nRequestID)
		{
			return TdApiCalls.ReqQryInvestorProductGroupMargin(ApiHandle_, ref pQryInvestorProductGroupMargin,
				nRequestID);
		}

		///请求查询交易所保证金率
		public int ReqQryExchangeMarginRate(ref CThostFtdcQryExchangeMarginRateField pQryExchangeMarginRate,
			int nRequestID)
		{
			return TdApiCalls.ReqQryExchangeMarginRate(ApiHandle_, ref pQryExchangeMarginRate, nRequestID);
		}

		///请求查询交易所调整保证金率
		public int ReqQryExchangeMarginRateAdjust(
			ref CThostFtdcQryExchangeMarginRateAdjustField pQryExchangeMarginRateAdjust, int nRequestID)
		{
			return TdApiCalls.ReqQryExchangeMarginRateAdjust(ApiHandle_, ref pQryExchangeMarginRateAdjust, nRequestID);
		}

		///请求查询汇率
		public int ReqQryExchangeRate(ref CThostFtdcQryExchangeRateField pQryExchangeRate, int nRequestID)
		{
			return TdApiCalls.ReqQryExchangeRate(ApiHandle_, ref pQryExchangeRate, nRequestID);
		}

		///请求查询二级代理操作员银期权限
		public int ReqQrySecAgentACIDMap(ref CThostFtdcQrySecAgentACIDMapField pQrySecAgentACIDMap, int nRequestID)
		{
			return TdApiCalls.ReqQrySecAgentACIDMap(ApiHandle_, ref pQrySecAgentACIDMap, nRequestID);
		}

		///请求查询产品报价汇率
		public int ReqQryProductExchRate(ref CThostFtdcQryProductExchRateField pQryProductExchRate, int nRequestID)
		{
			return TdApiCalls.ReqQryProductExchRate(ApiHandle_, ref pQryProductExchRate, nRequestID);
		}

		///请求查询产品组
		public int ReqQryProductGroup(ref CThostFtdcQryProductGroupField pQryProductGroup, int nRequestID)
		{
			return TdApiCalls.ReqQryProductGroup(ApiHandle_, ref pQryProductGroup, nRequestID);
		}

		///请求查询做市商合约手续费率
		public int ReqQryMMInstrumentCommissionRate(
			ref CThostFtdcQryMMInstrumentCommissionRateField pQryMMInstrumentCommissionRate, int nRequestID)
		{
			return TdApiCalls.ReqQryMMInstrumentCommissionRate(ApiHandle_, ref pQryMMInstrumentCommissionRate,
				nRequestID);
		}

		///请求查询做市商期权合约手续费
		public int ReqQryMMOptionInstrCommRate(ref CThostFtdcQryMMOptionInstrCommRateField pQryMMOptionInstrCommRate,
			int nRequestID)
		{
			return TdApiCalls.ReqQryMMOptionInstrCommRate(ApiHandle_, ref pQryMMOptionInstrCommRate, nRequestID);
		}

		///请求查询报单手续费
		public int ReqQryInstrumentOrderCommRate(
			ref CThostFtdcQryInstrumentOrderCommRateField pQryInstrumentOrderCommRate, int nRequestID)
		{
			return TdApiCalls.ReqQryInstrumentOrderCommRate(ApiHandle_, ref pQryInstrumentOrderCommRate, nRequestID);
		}

		///请求查询资金账户
		public int ReqQrySecAgentTradingAccount(ref CThostFtdcQryTradingAccountField pQryTradingAccount, int nRequestID)
		{
			return TdApiCalls.ReqQrySecAgentTradingAccount(ApiHandle_, ref pQryTradingAccount, nRequestID);
		}

		///请求查询二级代理商资金校验模式
		public int ReqQrySecAgentCheckMode(ref CThostFtdcQrySecAgentCheckModeField pQrySecAgentCheckMode,
			int nRequestID)
		{
			return TdApiCalls.ReqQrySecAgentCheckMode(ApiHandle_, ref pQrySecAgentCheckMode, nRequestID);
		}

		///请求查询二级代理商信息
		public int ReqQrySecAgentTradeInfo(ref CThostFtdcQrySecAgentTradeInfoField pQrySecAgentTradeInfo,
			int nRequestID)
		{
			return TdApiCalls.ReqQrySecAgentTradeInfo(ApiHandle_, ref pQrySecAgentTradeInfo, nRequestID);
		}

		///请求查询期权交易成本
		public int ReqQryOptionInstrTradeCost(ref CThostFtdcQryOptionInstrTradeCostField pQryOptionInstrTradeCost,
			int nRequestID)
		{
			return TdApiCalls.ReqQryOptionInstrTradeCost(ApiHandle_, ref pQryOptionInstrTradeCost, nRequestID);
		}

		///请求查询期权合约手续费
		public int ReqQryOptionInstrCommRate(ref CThostFtdcQryOptionInstrCommRateField pQryOptionInstrCommRate,
			int nRequestID)
		{
			return TdApiCalls.ReqQryOptionInstrCommRate(ApiHandle_, ref pQryOptionInstrCommRate, nRequestID);
		}

		///请求查询执行宣告
		public int ReqQryExecOrder(ref CThostFtdcQryExecOrderField pQryExecOrder, int nRequestID)
		{
			return TdApiCalls.ReqQryExecOrder(ApiHandle_, ref pQryExecOrder, nRequestID);
		}

		///请求查询询价
		public int ReqQryForQuote(ref CThostFtdcQryForQuoteField pQryForQuote, int nRequestID)
		{
			return TdApiCalls.ReqQryForQuote(ApiHandle_, ref pQryForQuote, nRequestID);
		}

		///请求查询报价
		public int ReqQryQuote(ref CThostFtdcQryQuoteField pQryQuote, int nRequestID)
		{
			return TdApiCalls.ReqQryQuote(ApiHandle_, ref pQryQuote, nRequestID);
		}

		///请求查询期权自对冲
		public int ReqQryOptionSelfClose(ref CThostFtdcQryOptionSelfCloseField pQryOptionSelfClose, int nRequestID)
		{
			return TdApiCalls.ReqQryOptionSelfClose(ApiHandle_, ref pQryOptionSelfClose, nRequestID);
		}

		///请求查询投资单元
		public int ReqQryInvestUnit(ref CThostFtdcQryInvestUnitField pQryInvestUnit, int nRequestID)
		{
			return TdApiCalls.ReqQryInvestUnit(ApiHandle_, ref pQryInvestUnit, nRequestID);
		}

		///请求查询组合合约安全系数
		public int ReqQryCombInstrumentGuard(ref CThostFtdcQryCombInstrumentGuardField pQryCombInstrumentGuard,
			int nRequestID)
		{
			return TdApiCalls.ReqQryCombInstrumentGuard(ApiHandle_, ref pQryCombInstrumentGuard, nRequestID);
		}

		///请求查询申请组合
		public int ReqQryCombAction(ref CThostFtdcQryCombActionField pQryCombAction, int nRequestID)
		{
			return TdApiCalls.ReqQryCombAction(ApiHandle_, ref pQryCombAction, nRequestID);
		}

		///请求查询转帐流水
		public int ReqQryTransferSerial(ref CThostFtdcQryTransferSerialField pQryTransferSerial, int nRequestID)
		{
			return TdApiCalls.ReqQryTransferSerial(ApiHandle_, ref pQryTransferSerial, nRequestID);
		}

		///请求查询银期签约关系
		public int ReqQryAccountregister(ref CThostFtdcQryAccountregisterField pQryAccountregister, int nRequestID)
		{
			return TdApiCalls.ReqQryAccountregister(ApiHandle_, ref pQryAccountregister, nRequestID);
		}

		///请求查询签约银行
		public int ReqQryContractBank(ref CThostFtdcQryContractBankField pQryContractBank, int nRequestID)
		{
			return TdApiCalls.ReqQryContractBank(ApiHandle_, ref pQryContractBank, nRequestID);
		}

		///请求查询预埋单
		public int ReqQryParkedOrder(ref CThostFtdcQryParkedOrderField pQryParkedOrder, int nRequestID)
		{
			return TdApiCalls.ReqQryParkedOrder(ApiHandle_, ref pQryParkedOrder, nRequestID);
		}

		///请求查询预埋撤单
		public int ReqQryParkedOrderAction(ref CThostFtdcQryParkedOrderActionField pQryParkedOrderAction,
			int nRequestID)
		{
			return TdApiCalls.ReqQryParkedOrderAction(ApiHandle_, ref pQryParkedOrderAction, nRequestID);
		}

		///请求查询交易通知
		public int ReqQryTradingNotice(ref CThostFtdcQryTradingNoticeField pQryTradingNotice, int nRequestID)
		{
			return TdApiCalls.ReqQryTradingNotice(ApiHandle_, ref pQryTradingNotice, nRequestID);
		}

		///请求查询经纪公司交易参数
		public int ReqQryBrokerTradingParams(ref CThostFtdcQryBrokerTradingParamsField pQryBrokerTradingParams,
			int nRequestID)
		{
			return TdApiCalls.ReqQryBrokerTradingParams(ApiHandle_, ref pQryBrokerTradingParams, nRequestID);
		}

		///请求查询经纪公司交易算法
		public int ReqQryBrokerTradingAlgos(ref CThostFtdcQryBrokerTradingAlgosField pQryBrokerTradingAlgos,
			int nRequestID)
		{
			return TdApiCalls.ReqQryBrokerTradingAlgos(ApiHandle_, ref pQryBrokerTradingAlgos, nRequestID);
		}

		///请求查询监控中心用户令牌
		public int ReqQueryCFMMCTradingAccountToken(
			ref CThostFtdcQueryCFMMCTradingAccountTokenField pQueryCFMMCTradingAccountToken, int nRequestID)
		{
			return TdApiCalls.ReqQueryCFMMCTradingAccountToken(ApiHandle_, ref pQueryCFMMCTradingAccountToken, nRequestID);
		}

		///期货发起银行资金转期货请求
		public int ReqFromBankToFutureByFuture(ref CThostFtdcReqTransferField pReqTransfer, int nRequestID)
		{
			return TdApiCalls.ReqFromBankToFutureByFuture(ApiHandle_, ref pReqTransfer, nRequestID);
		}

		///期货发起期货资金转银行请求
		public int ReqFromFutureToBankByFuture(ref CThostFtdcReqTransferField pReqTransfer, int nRequestID)
		{
			return TdApiCalls.ReqFromFutureToBankByFuture(ApiHandle_, ref pReqTransfer, nRequestID);
		}

		///期货发起查询银行余额请求
		public int ReqQueryBankAccountMoneyByFuture(ref CThostFtdcReqQueryAccountField pReqQueryAccount, int nRequestID)
		{
			return TdApiCalls.ReqQueryBankAccountMoneyByFuture(ApiHandle_, ref pReqQueryAccount, nRequestID);
		}



#region C&D
        public              CtpTdApiBase(string frontAddress, string brokerId, string userId, string password,
            string pszFlowPath = "CtpTdFlow/")
        {
	        FrontAddress = frontAddress;
            BrokerId     = brokerId;
			UserId = userId;
			Password = password;

            FlowPath = pszFlowPath;

        }

        protected void        BindEvents_()
		{
			TdApiCalls.RegOnRspError(SpiHandle_, _CBOnRspError);
			TdApiCalls.RegOnHeartBeatWarning(SpiHandle_, _CbOnHeartBeatWarning);

			TdApiCalls.RegOnRspFrontConnected(SpiHandle_, _OnFrontConnected);
			TdApiCalls.RegOnRspFrontDisconnected(SpiHandle_, _OnFrontDisconnected);

			TdApiCalls.RegOnRspAuthenticate(SpiHandle_, _CBRspAuthenticate);

			TdApiCalls.RegOnRspUserLogin(SpiHandle_, _OnRspUserLogin);
			TdApiCalls.RegOnRspUserLogout(SpiHandle_, _OnRspUserLogout);

			TdApiCalls.RegOnRspSettlementInfoConfirm(SpiHandle_, _CBOnRspSettlementInfoConfirm);

			TdApiCalls.RegOnRspQryTradingAccount(SpiHandle_, _CBOnRspQryTradingAccount);

			TdApiCalls.RegOnRspQryInvestorPosition(SpiHandle_, _CBOnRspQryInvestorPosition);


			TdApiCalls.RegOnRspQryInstrument(SpiHandle_, _CBOnRspQryInstrument);

			TdApiCalls.RegOnRspOrderInsert(SpiHandle_, _CBOnRspOrderInsert);
	        TdApiCalls.RegOnRtnOrder(SpiHandle_, _CBOnRtnOrder);
			TdApiCalls.RegOnRtnTrade(SpiHandle_, _CBOnRtnTrade);


            return;



			TdApiCalls.RegRspUserPasswordUpdate(SpiHandle_, _CBRspUserPasswordUpdate);  //用户口令更新请求响应
			TdApiCalls.RegRspTradingAccountPasswordUpdate(SpiHandle_, _CBRspTradingAccountPasswordUpdate);			
			TdApiCalls.RegRspUserAuthMethod(SpiHandle_, _CBRspUserAuthMethod);
			TdApiCalls.RegRspGenUserCaptcha(SpiHandle_, _CBRspGenUserCaptcha);
			TdApiCalls.RegRspGenUserText(SpiHandle_, _CBRspGenUserText);
			TdApiCalls.RegRspParkedOrderInsert(SpiHandle_, _CBRspParkedOrderInsert);
			TdApiCalls.RegRspParkedOrderAction(SpiHandle_, _CBRspParkedOrderAction);
			TdApiCalls.RegRspOrderAction(SpiHandle_, _CBRspOrderAction);
			TdApiCalls.RegRspQueryMaxOrderVolume(SpiHandle_, _CBRspQueryMaxOrderVolume);
			TdApiCalls.RegRspRemoveParkedOrder(SpiHandle_, _CBRspRemoveParkedOrder);
			TdApiCalls.RegRspRemoveParkedOrderAction(SpiHandle_, _CBRspRemoveParkedOrderAction);
			TdApiCalls.RegBatchOrderAction(SpiHandle_, _CBRspBatchOrderAction);
			TdApiCalls.RegCombActionInsert(SpiHandle_, _CBRspCombActionInsert);
			TdApiCalls.RegRspQryOrder(SpiHandle_, _CBRspQryOrder);
			TdApiCalls.RegRspQryTrade(SpiHandle_, _CBRspQryTrade);
			TdApiCalls.RegRspQryInvestor(SpiHandle_, _CBRspQryInvestor);
			TdApiCalls.RegRspQryTradingCode(SpiHandle_, _CBRspQryTradingCode);
			TdApiCalls.RegRspQryInstrumentMarginRate(SpiHandle_, _CBRspQryInstrumentMarginRate);
			TdApiCalls.RegRspQryInstrumentCommissionRate(SpiHandle_, _CBRspQryInstrumentCommissionRate);
			TdApiCalls.RegRspQryExchange(SpiHandle_, _CBRspQryExchange);
			TdApiCalls.RegRspQryDepthMarketData(SpiHandle_, _CBRspQryDepthMarketData);
			TdApiCalls.RegRspQrySettlementInfo(SpiHandle_, _CBRspQrySettlementInfo);
			TdApiCalls.RegRspQryTransferBank(SpiHandle_, _CBRspQryTransferBank);
			TdApiCalls.RegRspQryInvestorPositionDetail(SpiHandle_, _CBRspQryInvestorPositionDetail);
			TdApiCalls.RegRspQryNotice(SpiHandle_, _CBRspQryNotice);
			TdApiCalls.RegRspQrySettlementInfoConfirm(SpiHandle_, _CBRspQrySettlementInfoConfirm);
			TdApiCalls.RegRspQryInvestorPositionCombineDetail(SpiHandle_, _CBRspQryInvestorPositionCombineDetail);
			TdApiCalls.RegRspQryCFMMCTradingAccountKey(SpiHandle_, _CBRspQryCFMMCTradingAccountKey);
			TdApiCalls.RegRspQryEWarrantOffset(SpiHandle_, _CBRspQryEWarrantOffset);
			TdApiCalls.RegRspQryInvestorProductGroupMargin(SpiHandle_, _CBRspQryInvestorProductGroupMargin);
			TdApiCalls.RegRspQryExchangeMarginRate(SpiHandle_, _CBRspQryExchangeMarginRate);
			TdApiCalls.RegRspQryExchangeMarginRateAdjust(SpiHandle_, _CBRspQryExchangeMarginRateAdjust);
			TdApiCalls.RegRspQryExchangeRate(SpiHandle_, _CBRspQryExchangeRate);
			TdApiCalls.RegRspQrySecAgentACIDMap(SpiHandle_, _CBRspQrySecAgentACIDMap);
			TdApiCalls.RegRspQryProductExchRate(SpiHandle_, _CBRspQryProductExchRate);
			TdApiCalls.RegRspQryProductGroup(SpiHandle_, _CBRspQryProductGroup);
			TdApiCalls.RegRspQryMMInstrumentCommissionRate(SpiHandle_, _CBRspQryMMInstrumentCommissionRate);
			TdApiCalls.RegRspQryMMOptionInstrCommRate(SpiHandle_, _CBRspQryMMOptionInstrCommRate);
			TdApiCalls.RegRspQryInstrumentOrderCommRate(SpiHandle_, _CBRspQryInstrumentOrderCommRate);
			TdApiCalls.RegRspQrySecAgentTradingAccount(SpiHandle_, _CBRspQrySecAgentTradingAccount);
			TdApiCalls.RegRspQrySecAgentCheckMode(SpiHandle_, _CBRspQrySecAgentCheckMode);
			TdApiCalls.RegRspQrySecAgentTradeInfo(SpiHandle_, _CBRspQrySecAgentTradeInfo);
			TdApiCalls.RegRspQryOptionInstrTradeCost(SpiHandle_, _CBRspQryOptionInstrTradeCost);
			TdApiCalls.RegRspQryOptionInstrCommRate(SpiHandle_, _CBRspQryOptionInstrCommRate);
			TdApiCalls.RegRspQryExecOrder(SpiHandle_, _CBRspQryExecOrder);
			TdApiCalls.RegRspQryForQuote(SpiHandle_, _CBRspQryForQuote);
			TdApiCalls.RegRspQryQuote(SpiHandle_, _CBRspQryQuote);
			TdApiCalls.RegRspQryOptionSelfClose(SpiHandle_, _CBRspQryOptionSelfClose);
			TdApiCalls.RegRspQryInvestUnit(SpiHandle_, _CBRspQryInvestUnit);
			TdApiCalls.RegRspQryCombInstrumentGuard(SpiHandle_, _CBRspQryCombInstrumentGuard);
			TdApiCalls.RegRspQryCombAction(SpiHandle_, _CBRspQryCombAction);
			TdApiCalls.RegRspQryTransferSerial(SpiHandle_, _CBRspQryTransferSerial);
			TdApiCalls.RegRspQryAccountregister(SpiHandle_, _CBRspQryAccountregister);
			TdApiCalls.RegOnRspError(SpiHandle_, _CBOnRspError);
					TdApiCalls.RegErrRtnOrderInsert(SpiHandle_, _CBErrRtnOrderInsert);
			TdApiCalls.RegErrRtnOrderAction(SpiHandle_, _CBErrRtnOrderAction);
			TdApiCalls.RegRtnInstrumentStatus(SpiHandle_, _CBRtnInstrumentStatus);
			TdApiCalls.RegRtnTradingNotice(SpiHandle_, _CBRtnTradingNotice);
			TdApiCalls.RegRtnErrorConditionalOrder(SpiHandle_, _CBRtnErrorConditionalOrder);
			TdApiCalls.RegRspQryContractBank(SpiHandle_, _CBRspQryContractBank);
			TdApiCalls.RegRspQryParkedOrder(SpiHandle_, _CBRspQryParkedOrder);
			TdApiCalls.RegRspQryParkedOrderAction(SpiHandle_, _CBRspQryParkedOrderAction);
			TdApiCalls.RegRspQryTradingNotice(SpiHandle_, _CBRspQryTradingNotice);
			TdApiCalls.RegRspQryBrokerTradingParams(SpiHandle_, _CBRspQryBrokerTradingParams);
			TdApiCalls.RegRspQryBrokerTradingAlgos(SpiHandle_, _CBRspQryBrokerTradingAlgos);
			TdApiCalls.RegRtnFromBankToFutureByBank(SpiHandle_, _CBRtnFromBankToFutureByBank);
			TdApiCalls.RegRtnFromFutureToBankByBank(SpiHandle_, _CBRtnFromFutureToBankByBank);
			TdApiCalls.RegRtnRepealFromBankToFutureByBank(SpiHandle_, _CBRtnRepealFromBankToFutureByBank);
			TdApiCalls.RegRtnRepealFromFutureToBankByBank(SpiHandle_, _CBRtnRepealFromFutureToBankByBank);
			TdApiCalls.RegRtnFromBankToFutureByFuture(SpiHandle_, _CBRtnFromBankToFutureByFuture);
			TdApiCalls.RegRtnFromFutureToBankByFuture(SpiHandle_, _CBRtnFromFutureToBankByFuture);
			TdApiCalls.RegRtnRepealFromBankToFutureByFutureManual(SpiHandle_, _CBRtnRepealFromBankToFutureByFutureManual);
			TdApiCalls.RegRtnRepealFromFutureToBankByFutureManual(SpiHandle_, _CBRtnRepealFromFutureToBankByFutureManual);
			TdApiCalls.RegRtnQueryBankBalanceByFuture(SpiHandle_, _CBRtnQueryBankBalanceByFuture);
			TdApiCalls.RegErrRtnBankToFutureByFuture(SpiHandle_, _CBErrRtnBankToFutureByFuture);
			TdApiCalls.RegErrRtnFutureToBankByFuture(SpiHandle_, _CBErrRtnFutureToBankByFuture);
			TdApiCalls.RegErrRtnRepealBankToFutureByFutureManual(SpiHandle_, _CBErrRtnRepealBankToFutureByFutureManual);
			TdApiCalls.RegErrRtnRepealFutureToBankByFutureManual(SpiHandle_, _CBErrRtnRepealFutureToBankByFutureManual);
			TdApiCalls.RegErrRtnQueryBankBalanceByFuture(SpiHandle_, _CBErrRtnQueryBankBalanceByFuture);
			TdApiCalls.RegRtnRepealFromBankToFutureByFuture(SpiHandle_, _CBRtnRepealFromBankToFutureByFuture);
			TdApiCalls.RegRtnRepealFromFutureToBankByFuture(SpiHandle_, _CBRtnRepealFromFutureToBankByFuture);
			TdApiCalls.RegRspFromBankToFutureByFuture(SpiHandle_, _CBRspFromBankToFutureByFuture);
			TdApiCalls.RegRspFromFutureToBankByFuture(SpiHandle_, _CBRspFromFutureToBankByFuture);
			TdApiCalls.RegRspQueryBankAccountMoneyByFuture(SpiHandle_, _CBRspQueryBankAccountMoneyByFuture);

		
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
			TdSpi_?.OnHeartBeatWarning(nTimeLapse);
		}

		/// <summary>
		/// 连接成功回调
		/// </summary>
		private void _OnFrontConnected()
		{
			//IsConnected = true;
			TdSpi_?.OnFrontConnected();
		}

		/// <summary>
		/// 断开连接回调
		/// </summary>
		/// <param name="nReason">原因</param>
		protected virtual void _OnFrontDisconnected(int nReason)
		{
			//IsConnected = false;
			TdSpi_?.OnFrontDisconnected(nReason);
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

			TdSpi_?.OnRspUserLogin(ref pRspUserLogin, ref pRspInfo, nRequestID, bIsLast);
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
			TdSpi_?.OnRspUserLogout(ref pUserLogout, ref pRspInfo, nRequestID, bIsLast);

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
			TdSpi_?.OnRspAuthenticate(ref pRspAuthenticateField, ref pRspInfo, nRequestID, bIsLast);
		}

		///登录请求响应
		private void _CBRspUserLogin(ref CThostFtdcRspUserLoginField pRspUserLogin, ref CThostFtdcRspInfoField pRspInfo,
			int nRequestID, bool bIsLast)
		{
			TdSpi_?.OnRspUserLogin(ref pRspUserLogin, ref pRspInfo, nRequestID, bIsLast);
		}

		///登出请求响应
		private void _CBRspUserLogout(ref CThostFtdcUserLogoutField pUserLogout, ref CThostFtdcRspInfoField pRspInfo,
			int nRequestID, bool bIsLast)
		{
			TdSpi_?.OnRspUserLogout(ref pUserLogout, ref pRspInfo, nRequestID, bIsLast);
		}

		///用户口令更新请求响应
		private void _CBRspUserPasswordUpdate(ref CThostFtdcUserPasswordUpdateField pUserPasswordUpdate,
			ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			TdSpi_?.OnRspUserPasswordUpdate(ref pUserPasswordUpdate, ref pRspInfo, nRequestID, bIsLast);
		}

		///资金账户口令更新请求响应
		private void _CBRspTradingAccountPasswordUpdate(
			ref CThostFtdcTradingAccountPasswordUpdateField pTradingAccountPasswordUpdate,
			ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			TdSpi_?.OnRspTradingAccountPasswordUpdate(ref pTradingAccountPasswordUpdate, ref pRspInfo, nRequestID, bIsLast);
		}

		///查询用户当前支持的认证模式的回复
		private void _CBRspUserAuthMethod(ref CThostFtdcRspUserAuthMethodField pRspUserAuthMethod,
			ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			TdSpi_?.OnRspUserAuthMethod(ref pRspUserAuthMethod, ref pRspInfo, nRequestID, bIsLast);
		}
		///获取图形验证码请求的回复
		private void _CBRspGenUserCaptcha(ref CThostFtdcRspGenUserCaptchaField pRspGenUserCaptcha, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			TdSpi_?.OnRspGenUserCaptcha(ref pRspGenUserCaptcha, ref pRspInfo, nRequestID, bIsLast);
		}
		///获取短信验证码请求的回复
		private void _CBRspGenUserText(ref CThostFtdcRspGenUserTextField pRspGenUserText, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			TdSpi_?.OnRspGenUserText(ref pRspGenUserText, ref pRspInfo, nRequestID, bIsLast);
		}

		///报单录入请求响应
		private void _CBOnRspOrderInsert(ref CThostFtdcInputOrderField pInputOrder, ref CThostFtdcRspInfoField pRspInfo,
			int nRequestID, bool bIsLast)
		{
			TdSpi_?.OnRspOrderInsert(ref pInputOrder, ref pRspInfo, nRequestID, bIsLast);
		}

		///预埋单录入请求响应
		private void _CBRspParkedOrderInsert(ref CThostFtdcParkedOrderField pParkedOrder,
			ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			TdSpi_?.OnRspParkedOrderInsert(ref pParkedOrder, ref pRspInfo, nRequestID, bIsLast);
		}

		///预埋撤单录入请求响应
		private void _CBRspParkedOrderAction(ref CThostFtdcParkedOrderActionField pParkedOrderAction, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			TdSpi_?.OnRspParkedOrderAction(ref pParkedOrderAction, ref pRspInfo, nRequestID, bIsLast);
		}
		///报单操作请求响应
		private void _CBRspOrderAction(ref CThostFtdcInputOrderActionField pInputOrderAction, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			TdSpi_?.OnRspOrderAction(ref pInputOrderAction, ref pRspInfo, nRequestID, bIsLast);
		}
		///查询最大报单数量响应
		private void _CBRspQueryMaxOrderVolume(ref CThostFtdcQueryMaxOrderVolumeField pQueryMaxOrderVolume, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			TdSpi_?.OnRspQueryMaxOrderVolume(ref pQueryMaxOrderVolume, ref pRspInfo, nRequestID, bIsLast);
		}
		///投资者结算结果确认响应
		private void _CBOnRspSettlementInfoConfirm(ref CThostFtdcSettlementInfoConfirmField pSettlementInfoConfirm, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			TdSpi_?.OnRspSettlementInfoConfirm(ref pSettlementInfoConfirm, ref pRspInfo, nRequestID, bIsLast);
		}
		///删除预埋单响应
		private void _CBRspRemoveParkedOrder(ref CThostFtdcRemoveParkedOrderField pRemoveParkedOrder, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			TdSpi_?.OnRspRemoveParkedOrder(ref pRemoveParkedOrder, ref pRspInfo, nRequestID, bIsLast);
		}
		///删除预埋撤单响应
		private void _CBRspRemoveParkedOrderAction(ref CThostFtdcRemoveParkedOrderActionField pRemoveParkedOrderAction, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			TdSpi_?.OnRspRemoveParkedOrderAction(ref pRemoveParkedOrderAction, ref pRspInfo, nRequestID, bIsLast);
		}
		///执行宣告录入请求响应
		private void _CBRspExecOrderInsert(ref CThostFtdcInputExecOrderField pInputExecOrder, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			TdSpi_?.OnRspExecOrderInsert(ref pInputExecOrder, ref pRspInfo, nRequestID, bIsLast);
		}
		///执行宣告操作请求响应
		private void _CBRspExecOrderAction(ref CThostFtdcInputExecOrderActionField pInputExecOrderAction, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			TdSpi_?.OnRspExecOrderAction(ref pInputExecOrderAction, ref pRspInfo, nRequestID, bIsLast);
		}
		///询价录入请求响应
		private void _CBRspForQuoteInsert(ref CThostFtdcInputForQuoteField pInputForQuote, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			TdSpi_?.OnRspForQuoteInsert(ref pInputForQuote, ref pRspInfo, nRequestID, bIsLast);
		}
		///报价录入请求响应
		private void _CBRspQuoteInsert(ref CThostFtdcInputQuoteField pInputQuote, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			TdSpi_?.OnRspQuoteInsert(ref pInputQuote, ref pRspInfo, nRequestID, bIsLast);
		}
		///报价操作请求响应
		private void _CBRspQuoteAction(ref CThostFtdcInputQuoteActionField pInputQuoteAction, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			TdSpi_?.OnRspQuoteAction(ref pInputQuoteAction, ref pRspInfo, nRequestID, bIsLast);
		}
		///批量报单操作请求响应
		private void _CBRspBatchOrderAction(ref CThostFtdcInputBatchOrderActionField pInputBatchOrderAction, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			TdSpi_?.OnRspBatchOrderAction(ref pInputBatchOrderAction, ref pRspInfo, nRequestID, bIsLast);
		}
		///期权自对冲录入请求响应
		private void _CBRspOptionSelfCloseInsert(ref CThostFtdcInputOptionSelfCloseField pInputOptionSelfClose, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			TdSpi_?.OnRspOptionSelfCloseInsert(ref pInputOptionSelfClose, ref pRspInfo, nRequestID, bIsLast);
		}
		///期权自对冲操作请求响应
		private void _CBRspOptionSelfCloseAction(ref CThostFtdcInputOptionSelfCloseActionField pInputOptionSelfCloseAction, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			TdSpi_?.OnRspOptionSelfCloseAction(ref pInputOptionSelfCloseAction, ref pRspInfo, nRequestID, bIsLast);
		}
		///申请组合录入请求响应
		private void _CBRspCombActionInsert(ref CThostFtdcInputCombActionField pInputCombAction, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			TdSpi_?.OnRspCombActionInsert(ref pInputCombAction, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询报单响应
		private void _CBRspQryOrder(ref CThostFtdcOrderField pOrder, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			TdSpi_?.OnRspQryOrder(ref pOrder, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询成交响应
		private void _CBRspQryTrade(ref CThostFtdcTradeField pTrade, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			TdSpi_?.OnRspQryTrade(ref pTrade, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询投资者持仓响应
		private void _CBOnRspQryInvestorPosition(ref CThostFtdcInvestorPositionField pInvestorPosition, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			TdSpi_?.OnRspQryInvestorPosition(ref pInvestorPosition, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询资金账户响应
		private void _CBOnRspQryTradingAccount(ref CThostFtdcTradingAccountField pTradingAccount, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			TdSpi_?.OnRspQryTradingAccount(ref pTradingAccount, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询投资者响应
		private void _CBRspQryInvestor(ref CThostFtdcInvestorField pInvestor, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			TdSpi_?.OnRspQryInvestor(ref pInvestor, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询交易编码响应
		private void _CBRspQryTradingCode(ref CThostFtdcTradingCodeField pTradingCode, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			TdSpi_?.OnRspQryTradingCode(ref pTradingCode, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询合约保证金率响应
		private void _CBRspQryInstrumentMarginRate(ref CThostFtdcInstrumentMarginRateField pInstrumentMarginRate, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			TdSpi_?.OnRspQryInstrumentMarginRate(ref pInstrumentMarginRate, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询合约手续费率响应
		private void _CBRspQryInstrumentCommissionRate(ref CThostFtdcInstrumentCommissionRateField pInstrumentCommissionRate, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			TdSpi_?.OnRspQryInstrumentCommissionRate(ref pInstrumentCommissionRate, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询交易所响应
		private void _CBRspQryExchange(ref CThostFtdcExchangeField pExchange, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			TdSpi_?.OnRspQryExchange(ref pExchange, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询合约响应
		private void _CBOnRspQryInstrument(ref CThostFtdcInstrumentField pInstrument, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			TdSpi_?.OnRspQryInstrument(ref pInstrument, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询行情响应
		private void _CBRspQryDepthMarketData(ref CThostFtdcDepthMarketDataField pDepthMarketData, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			TdSpi_?.OnRspQryDepthMarketData(ref pDepthMarketData, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询投资者结算结果响应
		private void _CBRspQrySettlementInfo(ref CThostFtdcSettlementInfoField pSettlementInfo, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			TdSpi_?.OnRspQrySettlementInfo(ref pSettlementInfo, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询转帐银行响应
		private void _CBRspQryTransferBank(ref CThostFtdcTransferBankField pTransferBank, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			TdSpi_?.OnRspQryTransferBank(ref pTransferBank, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询投资者持仓明细响应
		private void _CBRspQryInvestorPositionDetail(ref CThostFtdcInvestorPositionDetailField pInvestorPositionDetail, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			TdSpi_?.OnRspQryInvestorPositionDetail(ref pInvestorPositionDetail, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询客户通知响应
		private void _CBRspQryNotice(ref CThostFtdcNoticeField pNotice, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			TdSpi_?.OnRspQryNotice(ref pNotice, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询结算信息确认响应
		private void _CBRspQrySettlementInfoConfirm(ref CThostFtdcSettlementInfoConfirmField pSettlementInfoConfirm, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			TdSpi_?.OnRspQrySettlementInfoConfirm(ref pSettlementInfoConfirm, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询投资者持仓明细响应
		private void _CBRspQryInvestorPositionCombineDetail(ref CThostFtdcInvestorPositionCombineDetailField pInvestorPositionCombineDetail, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			TdSpi_?.OnRspQryInvestorPositionCombineDetail(ref pInvestorPositionCombineDetail, ref pRspInfo, nRequestID, bIsLast);
		}
		///查询保证金监管系统经纪公司资金账户密钥响应
		private void _CBRspQryCFMMCTradingAccountKey(ref CThostFtdcCFMMCTradingAccountKeyField pCFMMCTradingAccountKey, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			TdSpi_?.OnRspQryCFMMCTradingAccountKey(ref pCFMMCTradingAccountKey, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询仓单折抵信息响应
		private void _CBRspQryEWarrantOffset(ref CThostFtdcEWarrantOffsetField pEWarrantOffset, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			TdSpi_?.OnRspQryEWarrantOffset(ref pEWarrantOffset, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询投资者品种/跨品种保证金响应
		private void _CBRspQryInvestorProductGroupMargin(ref CThostFtdcInvestorProductGroupMarginField pInvestorProductGroupMargin, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			TdSpi_?.OnRspQryInvestorProductGroupMargin(ref pInvestorProductGroupMargin, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询交易所保证金率响应
		private void _CBRspQryExchangeMarginRate(ref CThostFtdcExchangeMarginRateField pExchangeMarginRate, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			TdSpi_?.OnRspQryExchangeMarginRate(ref pExchangeMarginRate, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询交易所调整保证金率响应
		private void _CBRspQryExchangeMarginRateAdjust(ref CThostFtdcExchangeMarginRateAdjustField pExchangeMarginRateAdjust, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			TdSpi_?.OnRspQryExchangeMarginRateAdjust(ref pExchangeMarginRateAdjust, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询汇率响应
		private void _CBRspQryExchangeRate(ref CThostFtdcExchangeRateField pExchangeRate, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			TdSpi_?.OnRspQryExchangeRate(ref pExchangeRate, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询二级代理操作员银期权限响应
		private void _CBRspQrySecAgentACIDMap(ref CThostFtdcSecAgentACIDMapField pSecAgentACIDMap, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			TdSpi_?.OnRspQrySecAgentACIDMap(ref pSecAgentACIDMap, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询产品报价汇率
		private void _CBRspQryProductExchRate(ref CThostFtdcProductExchRateField pProductExchRate, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			TdSpi_?.OnRspQryProductExchRate(ref pProductExchRate, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询产品组
		private void _CBRspQryProductGroup(ref CThostFtdcProductGroupField pProductGroup, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			TdSpi_?.OnRspQryProductGroup(ref pProductGroup, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询做市商合约手续费率响应
		private void _CBRspQryMMInstrumentCommissionRate(ref CThostFtdcMMInstrumentCommissionRateField pMMInstrumentCommissionRate, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			TdSpi_?.OnRspQryMMInstrumentCommissionRate(ref pMMInstrumentCommissionRate, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询做市商期权合约手续费响应
		private void _CBRspQryMMOptionInstrCommRate(ref CThostFtdcMMOptionInstrCommRateField pMMOptionInstrCommRate, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			TdSpi_?.OnRspQryMMOptionInstrCommRate(ref pMMOptionInstrCommRate, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询报单手续费响应
		private void _CBRspQryInstrumentOrderCommRate(ref CThostFtdcInstrumentOrderCommRateField pInstrumentOrderCommRate, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			TdSpi_?.OnRspQryInstrumentOrderCommRate(ref pInstrumentOrderCommRate, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询资金账户响应
		private void _CBRspQrySecAgentTradingAccount(ref CThostFtdcTradingAccountField pTradingAccount, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			TdSpi_?.OnRspQrySecAgentTradingAccount(ref pTradingAccount, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询二级代理商资金校验模式响应
		private void _CBRspQrySecAgentCheckMode(ref CThostFtdcSecAgentCheckModeField pSecAgentCheckMode, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			TdSpi_?.OnRspQrySecAgentCheckMode(ref pSecAgentCheckMode, ref pRspInfo, nRequestID, bIsLast);

		}
		///请求查询二级代理商信息响应
		private void _CBRspQrySecAgentTradeInfo(ref CThostFtdcSecAgentTradeInfoField pSecAgentTradeInfo, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			TdSpi_?.OnRspQrySecAgentTradeInfo(ref pSecAgentTradeInfo, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询期权交易成本响应
		private void _CBRspQryOptionInstrTradeCost(ref CThostFtdcOptionInstrTradeCostField pOptionInstrTradeCost, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			TdSpi_?.OnRspQryOptionInstrTradeCost(ref pOptionInstrTradeCost, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询期权合约手续费响应
		private void _CBRspQryOptionInstrCommRate(ref CThostFtdcOptionInstrCommRateField pOptionInstrCommRate, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			TdSpi_?.OnRspQryOptionInstrCommRate(ref pOptionInstrCommRate, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询执行宣告响应
		private void _CBRspQryExecOrder(ref CThostFtdcExecOrderField pExecOrder, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			TdSpi_?.OnRspQryExecOrder(ref pExecOrder, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询询价响应
		private void _CBRspQryForQuote(ref CThostFtdcForQuoteField pForQuote, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			TdSpi_?.OnRspQryForQuote(ref pForQuote, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询报价响应
		private void _CBRspQryQuote(ref CThostFtdcQuoteField pQuote, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			TdSpi_?.OnRspQryQuote(ref pQuote, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询期权自对冲响应
		private void _CBRspQryOptionSelfClose(ref CThostFtdcOptionSelfCloseField pOptionSelfClose, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			TdSpi_?.OnRspQryOptionSelfClose(ref pOptionSelfClose, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询投资单元响应
		private void _CBRspQryInvestUnit(ref CThostFtdcInvestUnitField pInvestUnit, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			TdSpi_?.OnRspQryInvestUnit(ref pInvestUnit, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询组合合约安全系数响应
		private void _CBRspQryCombInstrumentGuard(ref CThostFtdcCombInstrumentGuardField pCombInstrumentGuard, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			TdSpi_?.OnRspQryCombInstrumentGuard(ref pCombInstrumentGuard, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询申请组合响应
		private void _CBRspQryCombAction(ref CThostFtdcCombActionField pCombAction, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			TdSpi_?.OnRspQryCombAction(ref pCombAction, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询转帐流水响应
		private void _CBRspQryTransferSerial(ref CThostFtdcTransferSerialField pTransferSerial, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			TdSpi_?.OnRspQryTransferSerial(ref pTransferSerial, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询银期签约关系响应
		private void _CBRspQryAccountregister(ref CThostFtdcAccountregisterField pAccountregister, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			TdSpi_?.OnRspQryAccountregister(ref pAccountregister, ref pRspInfo, nRequestID, bIsLast);
		}
		///错误应答
		private void _CBOnRspError(ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			TdSpi_?.OnRspError(ref pRspInfo, nRequestID, bIsLast);
		}
		///报单通知
		private void _CBOnRtnOrder(ref CThostFtdcOrderField pOrder)
		{
			TdSpi_?.OnRtnOrder(ref pOrder);
		}
		///成交通知
		private void _CBOnRtnTrade(ref CThostFtdcTradeField pTrade)
		{
			TdSpi_?.OnRtnTrade(ref pTrade);
		}
		///报单录入错误回报
		private void _CBErrRtnOrderInsert(ref CThostFtdcInputOrderField pInputOrder, ref CThostFtdcRspInfoField pRspInfo)
		{
			TdSpi_?.OnErrRtnOrderInsert(ref pInputOrder, ref pRspInfo);
		}
		///报单操作错误回报
		private void _CBErrRtnOrderAction(ref CThostFtdcOrderActionField pOrderAction, ref CThostFtdcRspInfoField pRspInfo)
		{
			TdSpi_?.OnErrRtnOrderAction(ref pOrderAction, ref pRspInfo);
		}
		///合约交易状态通知
		private void _CBRtnInstrumentStatus(ref CThostFtdcInstrumentStatusField pInstrumentStatus)
		{
			TdSpi_?.OnRtnInstrumentStatus(ref pInstrumentStatus);
		}
		///交易通知
		private void _CBRtnTradingNotice(ref CThostFtdcTradingNoticeInfoField pTradingNoticeInfo)
		{
			TdSpi_?.OnRtnTradingNotice(ref pTradingNoticeInfo);
		}
		///提示条件单校验错误
		private void _CBRtnErrorConditionalOrder(ref CThostFtdcErrorConditionalOrderField pErrorConditionalOrder)
		{
			TdSpi_?.OnRtnErrorConditionalOrder(ref pErrorConditionalOrder);
		}
		///执行宣告通知
		private void _CBRtnExecOrder(ref CThostFtdcExecOrderField pExecOrder)
		{
			TdSpi_?.OnRtnExecOrder(ref pExecOrder);
		}
		///执行宣告录入错误回报
		private void _CBErrRtnExecOrderInsert(ref CThostFtdcInputExecOrderField pInputExecOrder, ref CThostFtdcRspInfoField pRspInfo)
		{
			TdSpi_?.OnErrRtnExecOrderInsert(ref pInputExecOrder, ref pRspInfo);
		}
		///执行宣告操作错误回报
		private void _CBErrRtnExecOrderAction(ref CThostFtdcExecOrderActionField pExecOrderAction, ref CThostFtdcRspInfoField pRspInfo)
		{
			TdSpi_?.OnErrRtnExecOrderAction(ref pExecOrderAction, ref pRspInfo);
		}
		///询价录入错误回报
		private void _CBErrRtnForQuoteInsert(ref CThostFtdcInputForQuoteField pInputForQuote, ref CThostFtdcRspInfoField pRspInfo)
		{
			TdSpi_?.OnErrRtnForQuoteInsert(ref pInputForQuote, ref pRspInfo);
		}
		///报价通知
		private void _CBRtnQuote(ref CThostFtdcQuoteField pQuote)
		{
			TdSpi_?.OnRtnQuote(ref pQuote);
		}
		///报价录入错误回报
		private void _CBErrRtnQuoteInsert(ref CThostFtdcInputQuoteField pInputQuote, ref CThostFtdcRspInfoField pRspInfo)
		{
			TdSpi_?.OnErrRtnQuoteInsert(ref pInputQuote, ref pRspInfo);
		}
		///报价操作错误回报
		private void _CBErrRtnQuoteAction(ref CThostFtdcQuoteActionField pQuoteAction, ref CThostFtdcRspInfoField pRspInfo)
		{
			TdSpi_?.OnErrRtnQuoteAction(ref pQuoteAction, ref pRspInfo);
		}
		///询价通知
		private void _CBRtnForQuoteRsp(ref CThostFtdcForQuoteRspField pForQuoteRsp)
		{
			TdSpi_?.OnRtnForQuoteRsp(ref pForQuoteRsp);
		}
		///保证金监控中心用户令牌
		private void _CBRtnCFMMCTradingAccountToken(ref CThostFtdcCFMMCTradingAccountTokenField pCFMMCTradingAccountToken)
		{
			TdSpi_?.OnRtnCFMMCTradingAccountToken(ref pCFMMCTradingAccountToken);
		}
		///批量报单操作错误回报
		private void _CBErrRtnBatchOrderAction(ref CThostFtdcBatchOrderActionField pBatchOrderAction, ref CThostFtdcRspInfoField pRspInfo)
		{
			TdSpi_?.OnErrRtnBatchOrderAction(ref pBatchOrderAction, ref pRspInfo);
		}
		///期权自对冲通知
		private void _CBRtnOptionSelfClose(ref CThostFtdcOptionSelfCloseField pOptionSelfClose)
		{
			TdSpi_?.OnRtnOptionSelfClose(ref pOptionSelfClose);
		}
		///期权自对冲录入错误回报
		private void _CBErrRtnOptionSelfCloseInsert(ref CThostFtdcInputOptionSelfCloseField pInputOptionSelfClose, ref CThostFtdcRspInfoField pRspInfo)
		{
			TdSpi_?.OnErrRtnOptionSelfCloseInsert(ref pInputOptionSelfClose, ref pRspInfo);
		}
		///期权自对冲操作错误回报
		private void _CBErrRtnOptionSelfCloseAction(ref CThostFtdcOptionSelfCloseActionField pOptionSelfCloseAction, ref CThostFtdcRspInfoField pRspInfo)
		{
			TdSpi_?.OnErrRtnOptionSelfCloseAction(ref pOptionSelfCloseAction, ref pRspInfo);
		}
		///申请组合通知
		private void _CBRtnCombAction(ref CThostFtdcCombActionField pCombAction)
		{
			TdSpi_?.OnRtnCombAction(ref pCombAction);
		}
		///申请组合录入错误回报
		private void _CBErrRtnCombActionInsert(ref CThostFtdcInputCombActionField pInputCombAction, ref CThostFtdcRspInfoField pRspInfo)
		{
			TdSpi_?.OnErrRtnCombActionInsert(ref pInputCombAction, ref pRspInfo);
		}
		///请求查询签约银行响应
		private void _CBRspQryContractBank(ref CThostFtdcContractBankField pContractBank, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			TdSpi_?.OnRspQryContractBank(ref pContractBank, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询预埋单响应
		private void _CBRspQryParkedOrder(ref CThostFtdcParkedOrderField pParkedOrder, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			TdSpi_?.OnRspQryParkedOrder(ref pParkedOrder, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询预埋撤单响应
		private void _CBRspQryParkedOrderAction(ref CThostFtdcParkedOrderActionField pParkedOrderAction, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			TdSpi_?.OnRspQryParkedOrderAction(ref pParkedOrderAction, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询交易通知响应
		private void _CBRspQryTradingNotice(ref CThostFtdcTradingNoticeField pTradingNotice, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			TdSpi_?.OnRspQryTradingNotice(ref pTradingNotice, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询经纪公司交易参数响应
		private void _CBRspQryBrokerTradingParams(ref CThostFtdcBrokerTradingParamsField pBrokerTradingParams, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			TdSpi_?.OnRspQryBrokerTradingParams(ref pBrokerTradingParams, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询经纪公司交易算法响应
		private void _CBRspQryBrokerTradingAlgos(ref CThostFtdcBrokerTradingAlgosField pBrokerTradingAlgos, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			TdSpi_?.OnRspQryBrokerTradingAlgos(ref pBrokerTradingAlgos, ref pRspInfo, nRequestID, bIsLast);
		}
		///请求查询监控中心用户令牌
		private void _CBRspQueryCFMMCTradingAccountToken(ref CThostFtdcQueryCFMMCTradingAccountTokenField pQueryCFMMCTradingAccountToken, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			TdSpi_?.OnRspQueryCFMMCTradingAccountToken(ref pQueryCFMMCTradingAccountToken, ref pRspInfo, nRequestID, bIsLast);
		}
		///银行发起银行资金转期货通知
		private void _CBRtnFromBankToFutureByBank(ref CThostFtdcRspTransferField pRspTransfer)
		{
			TdSpi_?.OnRtnFromBankToFutureByBank(ref pRspTransfer);
		}
		///银行发起期货资金转银行通知
		private void _CBRtnFromFutureToBankByBank(ref CThostFtdcRspTransferField pRspTransfer)
		{
			TdSpi_?.OnRtnFromFutureToBankByBank(ref pRspTransfer);
		}
		///银行发起冲正银行转期货通知
		private void _CBRtnRepealFromBankToFutureByBank(ref CThostFtdcRspRepealField pRspRepeal)
		{
			TdSpi_?.OnRtnRepealFromBankToFutureByBank(ref pRspRepeal);
		}
		///银行发起冲正期货转银行通知
		private void _CBRtnRepealFromFutureToBankByBank(ref CThostFtdcRspRepealField pRspRepeal)
		{
			TdSpi_?.OnRtnRepealFromFutureToBankByBank(ref pRspRepeal);
		}
		///期货发起银行资金转期货通知
		private void _CBRtnFromBankToFutureByFuture(ref CThostFtdcRspTransferField pRspTransfer)
		{
			TdSpi_?.OnRtnFromBankToFutureByFuture(ref pRspTransfer);
		}
		///期货发起期货资金转银行通知
		private void _CBRtnFromFutureToBankByFuture(ref CThostFtdcRspTransferField pRspTransfer)
		{
			TdSpi_?.OnRtnFromFutureToBankByFuture(ref pRspTransfer);
		}
		///系统运行时期货端手工发起冲正银行转期货请求，银行处理完毕后报盘发回的通知
		private void _CBRtnRepealFromBankToFutureByFutureManual(ref CThostFtdcRspRepealField pRspRepeal)
		{
			TdSpi_?.OnRtnRepealFromBankToFutureByFutureManual(ref pRspRepeal);
		}
		///系统运行时期货端手工发起冲正期货转银行请求，银行处理完毕后报盘发回的通知
		private void _CBRtnRepealFromFutureToBankByFutureManual(ref CThostFtdcRspRepealField pRspRepeal)
		{
			TdSpi_?.OnRtnRepealFromFutureToBankByFutureManual(ref pRspRepeal);
		}
		///期货发起查询银行余额通知
		private void _CBRtnQueryBankBalanceByFuture(ref CThostFtdcNotifyQueryAccountField pNotifyQueryAccount)
		{
			TdSpi_?.OnRtnQueryBankBalanceByFuture(ref pNotifyQueryAccount);
		}
		///期货发起银行资金转期货错误回报
		private void _CBErrRtnBankToFutureByFuture(ref CThostFtdcReqTransferField pReqTransfer, ref CThostFtdcRspInfoField pRspInfo)
		{
			TdSpi_?.OnErrRtnBankToFutureByFuture(ref pReqTransfer, ref pRspInfo);
		}
		///期货发起期货资金转银行错误回报
		private void _CBErrRtnFutureToBankByFuture(ref CThostFtdcReqTransferField pReqTransfer, ref CThostFtdcRspInfoField pRspInfo)
		{
			TdSpi_?.OnErrRtnFutureToBankByFuture(ref pReqTransfer, ref pRspInfo);
		}
		///系统运行时期货端手工发起冲正银行转期货错误回报
		private void _CBErrRtnRepealBankToFutureByFutureManual(ref CThostFtdcReqRepealField pReqRepeal, ref CThostFtdcRspInfoField pRspInfo)
		{
			TdSpi_?.OnErrRtnRepealBankToFutureByFutureManual(ref pReqRepeal, ref pRspInfo);
		}
		///系统运行时期货端手工发起冲正期货转银行错误回报
		private void _CBErrRtnRepealFutureToBankByFutureManual(ref CThostFtdcReqRepealField pReqRepeal, ref CThostFtdcRspInfoField pRspInfo)
		{
			TdSpi_?.OnErrRtnRepealFutureToBankByFutureManual(ref pReqRepeal, ref pRspInfo);
		}
		///期货发起查询银行余额错误回报
		private void _CBErrRtnQueryBankBalanceByFuture(ref CThostFtdcReqQueryAccountField pReqQueryAccount, ref CThostFtdcRspInfoField pRspInfo)
		{
			TdSpi_?.OnErrRtnQueryBankBalanceByFuture(ref pReqQueryAccount, ref pRspInfo);
		}
		///期货发起冲正银行转期货请求，银行处理完毕后报盘发回的通知
		private void _CBRtnRepealFromBankToFutureByFuture(ref CThostFtdcRspRepealField pRspRepeal)
		{
			TdSpi_?.OnRtnRepealFromBankToFutureByFuture(ref pRspRepeal);
		}
		///期货发起冲正期货转银行请求，银行处理完毕后报盘发回的通知
		private void _CBRtnRepealFromFutureToBankByFuture(ref CThostFtdcRspRepealField pRspRepeal)
		{
			TdSpi_?.OnRtnRepealFromFutureToBankByFuture(ref pRspRepeal);
		}
		///期货发起银行资金转期货应答
		private void _CBRspFromBankToFutureByFuture(ref CThostFtdcReqTransferField pReqTransfer, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			TdSpi_?.OnRspFromBankToFutureByFuture(ref pReqTransfer, ref pRspInfo, nRequestID, bIsLast);
		}
		///期货发起期货资金转银行应答
		private void _CBRspFromFutureToBankByFuture(ref CThostFtdcReqTransferField pReqTransfer, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			TdSpi_?.OnRspFromFutureToBankByFuture(ref pReqTransfer, ref pRspInfo, nRequestID, bIsLast);
		}
		///期货发起查询银行余额应答
		private void _CBRspQueryBankAccountMoneyByFuture(ref CThostFtdcReqQueryAccountField pReqQueryAccount, ref CThostFtdcRspInfoField pRspInfo, int nRequestID, bool bIsLast)
		{
			TdSpi_?.OnRspQueryBankAccountMoneyByFuture(ref pReqQueryAccount, ref pRspInfo, nRequestID, bIsLast);
		}
		///银行发起银期开户通知
		private void _CBRtnOpenAccountByBank(ref CThostFtdcOpenAccountField pOpenAccount)
		{
			TdSpi_?.OnRtnOpenAccountByBank(ref pOpenAccount);
		}
		///银行发起银期销户通知
		private void _CBRtnCancelAccountByBank(ref CThostFtdcCancelAccountField pCancelAccount)
		{
			TdSpi_?.OnRtnCancelAccountByBank(ref pCancelAccount);
		}
		///银行发起变更银行账号通知
		private void _CBRtnChangeAccountByBank(ref CThostFtdcChangeAccountField pChangeAccount)
		{
			TdSpi_?.OnRtnChangeAccountByBank(ref pChangeAccount);
		}



		#endregion




		#region Members
		/// <summary>
		/// 交易类句柄
		/// </summary>
		protected IntPtr ApiHandle_ = IntPtr.Zero;
        protected IntPtr SpiHandle_ = IntPtr.Zero;   // C++ MdSpi Wrapper class


        protected int RequestID_ = 0;

      /// <summary>
        /// 回调方法字典
        /// </summary>
        private ConcurrentDictionary<int, object> _dataDict = new ConcurrentDictionary<int, object>();

        /// <summary>
        /// 数据回调字典
        /// </summary>
        private ConcurrentDictionary<int, object> _dataCallbackDict = new ConcurrentDictionary<int, object>();


        protected ICtpTdSpi TdSpi_;


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

	
        protected string   FlowPath_;
        protected   int   OrderRef_;
        private   DateTime LoginTime_;
        private   DateTime SHFETime_;
        private   DateTime DCETime_;


        protected bool     _IsLogined;
        private   DateTime CZCETime_;
        private   DateTime FFEXTime_;
        private   DateTime INETime_;

#endregion
	}
}
