/********************************************************************
    created:	2020-09-01 0:53:16
    author:		joshua
    email:		
	
    purpose:	
*********************************************************************/
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using RLib.Base;

namespace NeoCtp
{
	public partial class CtpTdApiBase
	{
		public static string GetApiVersion()			// 获取版本号
		{
			IntPtr ptr = MdApiCalls.GetApiVersion();
            return Marshal.PtrToStringAnsi(ptr);
		}
	}


	public interface ICtpTdApiBase:IDisposable, INotifyPropertyChanged
	{
        string              BrokerID { get; }
        string              UserID { get; }
        string              Password { get; }
        string              FrontAddress { get; }

        int                 FrontID { get; }                                /// 前置编号
        int                 SessionID { get; }                              /// 会话编号
        string              MaxOrderRef { get;  }                           /// 最大报单引用


		IReadonlyObservableCollection<CThostFtdcRspInfoField> Erros { get; } // 错误




		///注册回调接口
		///@param pSpi 派生自回调接口类的实例
		void RegisterSpi(ICtpTdSpi pSpi);


		/////创建TraderApi
		/////@param pszFlowPath 存贮订阅信息文件的目录，默认为当前目录
		/////@return 创建出的UserApi
		//static ref CThostFtdcTraderApi CreateFtdcTraderApi(const ref char pszFlowPath = "");

		///删除接口对象本身
		///@remark 不再使用本接口对象时,调用该函数删除接口对象
		void Release();

		///初始化
		///@remark 初始化运行环境,只有调用后,接口才开始工作
		void Init();

		///等待接口线程结束运行
		///@return 线程退出代码
		int Join();

		///获取当前交易日
		///@retrun 获取到的交易日
		///@remark 只有登录成功后,才能得到正确的交易日
		string		GetTradingDay();

		///注册前置机网络地址
		///@param pszFrontAddress：前置机网络地址。
		///@remark 网络地址的格式为：“protocol://ipaddress:port”，如：”tcp://127.0.0.1:17001”。 
		///@remark “tcp”代表传输协议，“127.0.0.1”代表服务器地址。”17001”代表服务器端口号。
		void RegisterFront(string pszFrontAddress);

		///注册名字服务器网络地址
		///@param pszNsAddress：名字服务器网络地址。
		///@remark 网络地址的格式为：“protocol://ipaddress:port”，如：”tcp://127.0.0.1:12001”。 
		///@remark “tcp”代表传输协议，“127.0.0.1”代表服务器地址。”12001”代表服务器端口号。
		///@remark RegisterNameServer优先于RegisterFront
		void RegisterNameServer(string pszNsAddress);

		///注册名字服务器用户信息
		///@param pFensUserInfo：用户信息。
		void RegisterFensUserInfo(ref CThostFtdcFensUserInfoField pFensUserInfo);


	

		///订阅私有流。
		///@param nResumeType 私有流重传方式  
		///        THOST_TERT_RESTART:从本交易日开始重传
		///        THOST_TERT_RESUME:从上次收到的续传
		///        THOST_TERT_QUICK:只传送登录后私有流的内容
		///@remark 该方法要在Init方法前调用。若不调用则不会收到私有流的数据。
		void SubscribePrivateTopic(THOST_TE_RESUME_TYPE nResumeType);

		///订阅公共流。
		///@param nResumeType 公共流重传方式  
		///        THOST_TERT_RESTART:从本交易日开始重传
		///        THOST_TERT_RESUME:从上次收到的续传
		///        THOST_TERT_QUICK:只传送登录后公共流的内容
		///@remark 该方法要在Init方法前调用。若不调用则不会收到公共流的数据。
		void SubscribePublicTopic(THOST_TE_RESUME_TYPE nResumeType);

		///客户端认证请求
		int ReqAuthenticate(ref CThostFtdcReqAuthenticateField pReqAuthenticateField, int nRequestID);

		///注册用户终端信息，用于中继服务器多连接模式
		///需要在终端认证成功后，用户登录前调用该接口
		int RegisterUserSystemInfo(ref CThostFtdcUserSystemInfoField pUserSystemInfo);

		///上报用户终端信息，用于中继服务器操作员登录模式
		///操作员登录后，可以多次调用该接口上报客户信息
		int SubmitUserSystemInfo(ref CThostFtdcUserSystemInfoField pUserSystemInfo);

		///用户登录请求
		int ReqUserLogin(ref CThostFtdcReqUserLoginField pReqUserLoginField, int nRequestID);

		///登出请求
		int ReqUserLogout(ref CThostFtdcUserLogoutField pUserLogout, int nRequestID);

		///用户口令更新请求
		int ReqUserPasswordUpdate(ref CThostFtdcUserPasswordUpdateField pUserPasswordUpdate, int nRequestID);

		///资金账户口令更新请求
		int ReqTradingAccountPasswordUpdate(ref CThostFtdcTradingAccountPasswordUpdateField pTradingAccountPasswordUpdate, int nRequestID);

		///查询用户当前支持的认证模式
		int ReqUserAuthMethod(ref CThostFtdcReqUserAuthMethodField pReqUserAuthMethod, int nRequestID);

		///用户发出获取图形验证码请求
		int ReqGenUserCaptcha(ref CThostFtdcReqGenUserCaptchaField pReqGenUserCaptcha, int nRequestID);

		///用户发出获取短信验证码请求
		int ReqGenUserText(ref CThostFtdcReqGenUserTextField pReqGenUserText, int nRequestID);

		///用户发出带有图片验证码的登陆请求
		int ReqUserLoginWithCaptcha(ref CThostFtdcReqUserLoginWithCaptchaField pReqUserLoginWithCaptcha, int nRequestID);

		///用户发出带有短信验证码的登陆请求
		int ReqUserLoginWithText(ref CThostFtdcReqUserLoginWithTextField pReqUserLoginWithText, int nRequestID);

		///用户发出带有动态口令的登陆请求
		int ReqUserLoginWithOTP(ref CThostFtdcReqUserLoginWithOTPField pReqUserLoginWithOTP, int nRequestID);



#region 账户
		///请求查询资金账户
		int ReqQryTradingAccount(ref CThostFtdcQryTradingAccountField pQryTradingAccount, int nRequestID);

		///请求查询投资者
		int ReqQryInvestor(ref CThostFtdcQryInvestorField pQryInvestor, int nRequestID);

		///请求查询交易编码
		int ReqQryTradingCode(ref CThostFtdcQryTradingCodeField pQryTradingCode, int nRequestID);

		

#endregion


		///请求查询投资者持仓
		int ReqQryInvestorPosition(ref CThostFtdcQryInvestorPositionField pQryInvestorPosition, int nRequestID);
		///请求查询投资者持仓明细
		int ReqQryInvestorPositionDetail(ref CThostFtdcQryInvestorPositionDetailField pQryInvestorPositionDetail, int nRequestID);
		///请求查询投资者持仓明细
		int ReqQryInvestorPositionCombineDetail(ref CThostFtdcQryInvestorPositionCombineDetailField pQryInvestorPositionCombineDetail, int nRequestID);




		///请求查询产品
		int ReqQryProduct(ref CThostFtdcQryProductField pQryProduct, int nRequestID);
		///请求查询产品报价汇率
		int ReqQryProductExchRate(ref CThostFtdcQryProductExchRateField pQryProductExchRate, int nRequestID);
		///请求查询产品组
		int ReqQryProductGroup(ref CThostFtdcQryProductGroupField pQryProductGroup, int nRequestID);



		///请求查询合约
		int ReqQryInstrument(ref CThostFtdcQryInstrumentField pQryInstrument, int nRequestID);
		///请求查询合约手续费率
		int ReqQryInstrumentCommissionRate(ref CThostFtdcQryInstrumentCommissionRateField pQryInstrumentCommissionRate, int nRequestID);
		///请求查询合约保证金率
		int ReqQryInstrumentMarginRate(ref CThostFtdcQryInstrumentMarginRateField pQryInstrumentMarginRate, int nRequestID);
		///请求查询报单手续费
		int ReqQryInstrumentOrderCommRate(ref CThostFtdcQryInstrumentOrderCommRateField pQryInstrumentOrderCommRate, int nRequestID);












		///报单录入请求
		int ReqOrderInsert(ref CThostFtdcInputOrderField pInputOrder, int nRequestID);

		///预埋单录入请求
		int ReqParkedOrderInsert(ref CThostFtdcParkedOrderField pParkedOrder, int nRequestID);

		///预埋撤单录入请求
		int ReqParkedOrderAction(ref CThostFtdcParkedOrderActionField pParkedOrderAction, int nRequestID);

		///报单操作请求
		int ReqOrderAction(ref CThostFtdcInputOrderActionField pInputOrderAction, int nRequestID);

		///查询最大报单数量请求
		int ReqQueryMaxOrderVolume(ref CThostFtdcQueryMaxOrderVolumeField pQueryMaxOrderVolume, int nRequestID);

		///投资者结算结果确认
		int ReqSettlementInfoConfirm(ref CThostFtdcSettlementInfoConfirmField pSettlementInfoConfirm, int nRequestID);

		///请求删除预埋单
		int ReqRemoveParkedOrder(ref CThostFtdcRemoveParkedOrderField pRemoveParkedOrder, int nRequestID);

		///请求删除预埋撤单
		int ReqRemoveParkedOrderAction(ref CThostFtdcRemoveParkedOrderActionField pRemoveParkedOrderAction, int nRequestID);

		///执行宣告录入请求
		int ReqExecOrderInsert(ref CThostFtdcInputExecOrderField pInputExecOrder, int nRequestID);

		///执行宣告操作请求
		int ReqExecOrderAction(ref CThostFtdcInputExecOrderActionField pInputExecOrderAction, int nRequestID);

		///询价录入请求
		int ReqForQuoteInsert(ref CThostFtdcInputForQuoteField pInputForQuote, int nRequestID);

		///报价录入请求
		int ReqQuoteInsert(ref CThostFtdcInputQuoteField pInputQuote, int nRequestID);

		///报价操作请求
		int ReqQuoteAction(ref CThostFtdcInputQuoteActionField pInputQuoteAction, int nRequestID);

		///批量报单操作请求
		int ReqBatchOrderAction(ref CThostFtdcInputBatchOrderActionField pInputBatchOrderAction, int nRequestID);

		///期权自对冲录入请求
		int ReqOptionSelfCloseInsert(ref CThostFtdcInputOptionSelfCloseField pInputOptionSelfClose, int nRequestID);

		///期权自对冲操作请求
		int ReqOptionSelfCloseAction(ref CThostFtdcInputOptionSelfCloseActionField pInputOptionSelfCloseAction, int nRequestID);

		///申请组合录入请求
		int ReqCombActionInsert(ref CThostFtdcInputCombActionField pInputCombAction, int nRequestID);

		///请求查询报单
		int ReqQryOrder(ref CThostFtdcQryOrderField pQryOrder, int nRequestID);

		///请求查询成交
		int ReqQryTrade(ref CThostFtdcQryTradeField pQryTrade, int nRequestID);





		///请求查询交易所
		int ReqQryExchange(ref CThostFtdcQryExchangeField pQryExchange, int nRequestID);





		///请求查询行情
		int ReqQryDepthMarketData(ref CThostFtdcQryDepthMarketDataField pQryDepthMarketData, int nRequestID);

		///请求查询投资者结算结果
		int ReqQrySettlementInfo(ref CThostFtdcQrySettlementInfoField pQrySettlementInfo, int nRequestID);

		///请求查询转帐银行
		int ReqQryTransferBank(ref CThostFtdcQryTransferBankField pQryTransferBank, int nRequestID);


		///请求查询客户通知
		int ReqQryNotice(ref CThostFtdcQryNoticeField pQryNotice, int nRequestID);

		///请求查询结算信息确认
		int ReqQrySettlementInfoConfirm(ref CThostFtdcQrySettlementInfoConfirmField pQrySettlementInfoConfirm, int nRequestID);


		///请求查询保证金监管系统经纪公司资金账户密钥
		int ReqQryCFMMCTradingAccountKey(ref CThostFtdcQryCFMMCTradingAccountKeyField pQryCFMMCTradingAccountKey, int nRequestID);

		///请求查询仓单折抵信息
		int ReqQryEWarrantOffset(ref CThostFtdcQryEWarrantOffsetField pQryEWarrantOffset, int nRequestID);

		///请求查询投资者品种/跨品种保证金
		int ReqQryInvestorProductGroupMargin(ref CThostFtdcQryInvestorProductGroupMarginField pQryInvestorProductGroupMargin, int nRequestID);

		///请求查询交易所保证金率
		int ReqQryExchangeMarginRate(ref CThostFtdcQryExchangeMarginRateField pQryExchangeMarginRate, int nRequestID);

		///请求查询交易所调整保证金率
		int ReqQryExchangeMarginRateAdjust(ref CThostFtdcQryExchangeMarginRateAdjustField pQryExchangeMarginRateAdjust, int nRequestID);

		///请求查询汇率
		int ReqQryExchangeRate(ref CThostFtdcQryExchangeRateField pQryExchangeRate, int nRequestID);

		///请求查询二级代理操作员银期权限
		int ReqQrySecAgentACIDMap(ref CThostFtdcQrySecAgentACIDMapField pQrySecAgentACIDMap, int nRequestID);



		///请求查询做市商合约手续费率
		int ReqQryMMInstrumentCommissionRate(ref CThostFtdcQryMMInstrumentCommissionRateField pQryMMInstrumentCommissionRate, int nRequestID);

		///请求查询做市商期权合约手续费
		int ReqQryMMOptionInstrCommRate(ref CThostFtdcQryMMOptionInstrCommRateField pQryMMOptionInstrCommRate, int nRequestID);


		///请求查询资金账户
		int ReqQrySecAgentTradingAccount(ref CThostFtdcQryTradingAccountField pQryTradingAccount, int nRequestID);

		///请求查询二级代理商资金校验模式
		int ReqQrySecAgentCheckMode(ref CThostFtdcQrySecAgentCheckModeField pQrySecAgentCheckMode, int nRequestID);

		///请求查询二级代理商信息
		int ReqQrySecAgentTradeInfo(ref CThostFtdcQrySecAgentTradeInfoField pQrySecAgentTradeInfo, int nRequestID);

		///请求查询期权交易成本
		int ReqQryOptionInstrTradeCost(ref CThostFtdcQryOptionInstrTradeCostField pQryOptionInstrTradeCost, int nRequestID);

		///请求查询期权合约手续费
		int ReqQryOptionInstrCommRate(ref CThostFtdcQryOptionInstrCommRateField pQryOptionInstrCommRate, int nRequestID);

		///请求查询执行宣告
		int ReqQryExecOrder(ref CThostFtdcQryExecOrderField pQryExecOrder, int nRequestID);

		///请求查询询价
		int ReqQryForQuote(ref CThostFtdcQryForQuoteField pQryForQuote, int nRequestID);

		///请求查询报价
		int ReqQryQuote(ref CThostFtdcQryQuoteField pQryQuote, int nRequestID);

		///请求查询期权自对冲
		int ReqQryOptionSelfClose(ref CThostFtdcQryOptionSelfCloseField pQryOptionSelfClose, int nRequestID);

		///请求查询投资单元
		int ReqQryInvestUnit(ref CThostFtdcQryInvestUnitField pQryInvestUnit, int nRequestID);

		///请求查询组合合约安全系数
		int ReqQryCombInstrumentGuard(ref CThostFtdcQryCombInstrumentGuardField pQryCombInstrumentGuard, int nRequestID);

		///请求查询申请组合
		int ReqQryCombAction(ref CThostFtdcQryCombActionField pQryCombAction, int nRequestID);

		///请求查询转帐流水
		int ReqQryTransferSerial(ref CThostFtdcQryTransferSerialField pQryTransferSerial, int nRequestID);

		///请求查询银期签约关系
		int ReqQryAccountregister(ref CThostFtdcQryAccountregisterField pQryAccountregister, int nRequestID);

		///请求查询签约银行
		int ReqQryContractBank(ref CThostFtdcQryContractBankField pQryContractBank, int nRequestID);

		///请求查询预埋单
		int ReqQryParkedOrder(ref CThostFtdcQryParkedOrderField pQryParkedOrder, int nRequestID);

		///请求查询预埋撤单
		int ReqQryParkedOrderAction(ref CThostFtdcQryParkedOrderActionField pQryParkedOrderAction, int nRequestID);

		///请求查询交易通知
		int ReqQryTradingNotice(ref CThostFtdcQryTradingNoticeField pQryTradingNotice, int nRequestID);

		///请求查询经纪公司交易参数
		int ReqQryBrokerTradingParams(ref CThostFtdcQryBrokerTradingParamsField pQryBrokerTradingParams, int nRequestID);

		///请求查询经纪公司交易算法
		int ReqQryBrokerTradingAlgos(ref CThostFtdcQryBrokerTradingAlgosField pQryBrokerTradingAlgos, int nRequestID);

		///请求查询监控中心用户令牌
		int ReqQueryCFMMCTradingAccountToken(ref CThostFtdcQueryCFMMCTradingAccountTokenField pQueryCFMMCTradingAccountToken, int nRequestID);

		///期货发起银行资金转期货请求
		int ReqFromBankToFutureByFuture(ref CThostFtdcReqTransferField pReqTransfer, int nRequestID);

		///期货发起期货资金转银行请求
		int ReqFromFutureToBankByFuture(ref CThostFtdcReqTransferField pReqTransfer, int nRequestID);

		///期货发起查询银行余额请求
		int ReqQueryBankAccountMoneyByFuture(ref CThostFtdcReqQueryAccountField pReqQueryAccount, int nRequestID);

	}
}
