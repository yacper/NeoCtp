#pragma once
#include "pch.h"
#include "TdSpi.h"

extern "C"  // 以C的方式导出函数名
{
#pragma  region Api

	TDAPI_API CThostFtdcTraderApi* CreateFtdcTraderApi(const char* pszFlowPath = "CtpFlow/");
	TDAPI_API TraderSpi*	CreateTdSpi();
	TDAPI_API void			RegisterSpi(CThostFtdcTraderApi* api, TraderSpi* pSpi);

	//获取接口版本
	TDAPI_API const char*	GetApiVersion();

	//连接
	//	TDAPI_API CThostFtdcTraderApi* Connect(char* frontAddr, char* pszFlowPath, TraderSpi* pSpi);
	////断开
	//	TDAPI_API void		DisConnect(CThostFtdcTraderApi* pApi);

		///删除接口对象本身
		///@remark 不再使用本接口对象时,调用该函数删除接口对象
	TDAPI_API void			Release(CThostFtdcTraderApi* api);

	///初始化
	///@remark 初始化运行环境,只有调用后,接口才开始工作
	TDAPI_API void			Init(CThostFtdcTraderApi* api);

	///等待接口线程结束运行
	///@return 线程退出代码
	TDAPI_API int			Join(CThostFtdcTraderApi* api);


	//获取交易日
	TDAPI_API const char*	GetTradingDay(CThostFtdcTraderApi* pApi);


	///注册前置机网络地址
	///@param pszFrontAddress：前置机网络地址。
	///@remark 网络地址的格式为：“protocol://ipaddress:port”，如：”tcp://127.0.0.1:17001”。 
	///@remark “tcp”代表传输协议，“127.0.0.1”代表服务器地址。”17001”代表服务器端口号。
	TDAPI_API void			RegisterFront(CThostFtdcTraderApi* pApi, char* pszFrontAddress);

	///注册名字服务器网络地址
	///@param pszNsAddress：名字服务器网络地址。
	///@remark 网络地址的格式为：“protocol://ipaddress:port”，如：”tcp://127.0.0.1:12001”。 
	///@remark “tcp”代表传输协议，“127.0.0.1”代表服务器地址。”12001”代表服务器端口号。
	///@remark RegisterNameServer优先于RegisterFront
	TDAPI_API void			RegisterNameServer(CThostFtdcTraderApi* pApi, char* pszNsAddress);

	///注册名字服务器用户信息
	///@param pFensUserInfo：用户信息。
	TDAPI_API void			RegisterFensUserInfo(CThostFtdcTraderApi* pApi, CThostFtdcFensUserInfoField* pFensUserInfo);

	///订阅私有流。
	///@param nResumeType 私有流重传方式  
	///        THOST_TERT_RESTART:从本交易日开始重传
	///        THOST_TERT_RESUME:从上次收到的续传
	///        THOST_TERT_QUICK:只传送登录后私有流的内容
	///@remark 该方法要在Init方法前调用。若不调用则不会收到私有流的数据。
	TDAPI_API void			SubscribePrivateTopic(CThostFtdcTraderApi* pApi, THOST_TE_RESUME_TYPE nResumeType);

	///订阅公共流。
	///@param nResumeType 公共流重传方式  
	///        THOST_TERT_RESTART:从本交易日开始重传
	///        THOST_TERT_RESUME:从上次收到的续传
	///        THOST_TERT_QUICK:只传送登录后公共流的内容
	///@remark 该方法要在Init方法前调用。若不调用则不会收到公共流的数据。
	TDAPI_API void			SubscribePublicTopic(CThostFtdcTraderApi* pApi, THOST_TE_RESUME_TYPE nResumeType);



#pragma region Login/out

	//客户端认证请求
	TDAPI_API int			ReqAuthenticate(CThostFtdcTraderApi* pApi, CThostFtdcReqAuthenticateField* field, int nRequestID);


	///注册用户终端信息，用于中继服务器多连接模式
	///需要在终端认证成功后，用户登录前调用该接口
	TDAPI_API int			RegisterUserSystemInfo(CThostFtdcTraderApi* pApi, CThostFtdcUserSystemInfoField* pUserSystemInfo);
	///上报用户终端信息，用于中继服务器操作员登录模式
	///操作员登录后，可以多次调用该接口上报客户信息
	TDAPI_API int			SubmitUserSystemInfo(CThostFtdcTraderApi* pApi, CThostFtdcUserSystemInfoField* pUserSystemInfo);


	//发送用户登录请求
	TDAPI_API int			ReqUserLogin(CThostFtdcTraderApi* pApi, CThostFtdcReqUserLoginField* pReqUserLoginField, int nRequestID);
	//发送登出请求
	TDAPI_API int			ReqUserLogout(CThostFtdcTraderApi* pApi, CThostFtdcUserLogoutField* pUserLogout, int nRequestID);


	///用户口令更新请求
	TDAPI_API int		ReqUserPasswordUpdate(CThostFtdcTraderApi* pApi, CThostFtdcUserPasswordUpdateField* pUserPasswordUpdate, int nRequestID);

	///资金账户口令更新请求
	TDAPI_API int		ReqTradingAccountPasswordUpdate(CThostFtdcTraderApi* pApi, CThostFtdcTradingAccountPasswordUpdateField* pTradingAccountPasswordUpdate, int nRequestID);

	///查询用户当前支持的认证模式
	TDAPI_API int		ReqUserAuthMethod(CThostFtdcTraderApi* pApi, CThostFtdcReqUserAuthMethodField* pReqUserAuthMethod, int nRequestID);

	///用户发出获取图形验证码请求
	TDAPI_API int		ReqGenUserCaptcha(CThostFtdcTraderApi* pApi, CThostFtdcReqGenUserCaptchaField* pReqGenUserCaptcha, int	nRequestID);

	///用户发出获取短信验证码请求
	TDAPI_API int		ReqGenUserText(CThostFtdcTraderApi* pApi, CThostFtdcReqGenUserTextField* pReqGenUserText, int nRequestID);

	///用户发出带有图片验证码的登陆请求
	TDAPI_API int		ReqUserLoginWithCaptcha(CThostFtdcTraderApi* pApi, CThostFtdcReqUserLoginWithCaptchaField* pReqUserLoginWithCaptcha, int nRequestID);

	///用户发出带有短信验证码的登陆请求
	TDAPI_API int		ReqUserLoginWithText(CThostFtdcTraderApi* pApi, CThostFtdcReqUserLoginWithTextField* pReqUserLoginWithText, int	nRequestID);

	///用户发出带有动态口令的登陆请求
	TDAPI_API int		ReqUserLoginWithOTP(CThostFtdcTraderApi* pApi, CThostFtdcReqUserLoginWithOTPField* pReqUserLoginWithOTP, int nRequestID);

#pragma endregion

	///请求查询询价
	TDAPI_API int		ReqQryForQuote(CThostFtdcTraderApi* pApi, CThostFtdcQryForQuoteField* pQryForQuote, int nRequestID);
	///请求查询报价
	TDAPI_API int		ReqQryQuote(CThostFtdcTraderApi* pApi, CThostFtdcQryQuoteField* pQryQuote, int nRequestID);
	///请求查询行情
	TDAPI_API int		ReqQryDepthMarketData(CThostFtdcTraderApi* pApi, CThostFtdcQryDepthMarketDataField* pQryDepthMarketData, int nRequestID);

#pragma region Order management
	///报单录入请求
	TDAPI_API int		ReqOrderInsert(CThostFtdcTraderApi* pApi, CThostFtdcInputOrderField* pInputOrder, int nRequestID);
	///请求查询报单
	TDAPI_API int		ReqQryOrder(CThostFtdcTraderApi* pApi, CThostFtdcQryOrderField* pQryOrder, int nRequestID);
	///查询最大报单数量请求
	TDAPI_API int		ReqQueryMaxOrderVolume(CThostFtdcTraderApi* pApi, CThostFtdcQueryMaxOrderVolumeField* pQueryMaxOrderVolume, int nRequestID);
	///报单操作请求
	TDAPI_API int		ReqOrderAction(CThostFtdcTraderApi* pApi, CThostFtdcInputOrderActionField* pInputOrderAction, int nRequestID);
	///批量报单操作请求
	TDAPI_API int		ReqBatchOrderAction(CThostFtdcTraderApi* pApi, CThostFtdcInputBatchOrderActionField* pInputBatchOrderAction, int nRequestID);

	///预埋单录入请求
	TDAPI_API int		ReqParkedOrderInsert(CThostFtdcTraderApi* pApi, CThostFtdcParkedOrderField* pParkedOrder, int nRequestID);
	///预埋撤单录入请求
	TDAPI_API int		ReqParkedOrderAction(CThostFtdcTraderApi* pApi, CThostFtdcParkedOrderActionField* pParkedOrderAction, int nRequestID);
	///请求删除预埋单
	TDAPI_API int		ReqRemoveParkedOrder(CThostFtdcTraderApi* pApi, CThostFtdcRemoveParkedOrderField* pRemoveParkedOrder, int nRequestID);
	///请求删除预埋撤单
	TDAPI_API int		ReqRemoveParkedOrderAction(CThostFtdcTraderApi* pApi, CThostFtdcRemoveParkedOrderActionField* pRemoveParkedOrderAction, int nRequestID);
	///请求查询预埋单
	TDAPI_API int		ReqQryParkedOrder(CThostFtdcTraderApi* pApi, CThostFtdcQryParkedOrderField* pQryParkedOrder, int nRequestID);
	///请求查询预埋撤单
	TDAPI_API int		ReqQryParkedOrderAction(CThostFtdcTraderApi* pApi, CThostFtdcQryParkedOrderActionField* pQryParkedOrderAction, int nRequestID);

#pragma endregion

	///请求查询成交
	TDAPI_API int		ReqQryTrade(CThostFtdcTraderApi* pApi, CThostFtdcQryTradeField* pQryTrade, int nRequestID);

		///请求查询客户通知
	TDAPI_API int		ReqQryNotice(CThostFtdcTraderApi* pApi, CThostFtdcQryNoticeField* pQryNotice, int nRequestID);
	///请求查询交易通知
	TDAPI_API int		ReqQryTradingNotice(CThostFtdcTraderApi* pApi, CThostFtdcQryTradingNoticeField* pQryTradingNotice, int nRequestID);


	///请求查询执行宣告
	TDAPI_API int		ReqQryExecOrder(CThostFtdcTraderApi* pApi, CThostFtdcQryExecOrderField* pQryExecOrder, int nRequestID);
	///执行宣告录入请求
	TDAPI_API int		ReqExecOrderInsert(CThostFtdcTraderApi* pApi, CThostFtdcInputExecOrderField* pInputExecOrder, int nRequestID);
	///执行宣告操作请求
	TDAPI_API int		ReqExecOrderAction(CThostFtdcTraderApi* pApi, CThostFtdcInputExecOrderActionField* pInputExecOrderAction, int nRequestID);


	///询价录入请求
	TDAPI_API int		ReqForQuoteInsert(CThostFtdcTraderApi* pApi, CThostFtdcInputForQuoteField* pInputForQuote, int nRequestID);
	///报价录入请求
	TDAPI_API int		ReqQuoteInsert(CThostFtdcTraderApi* pApi, CThostFtdcInputQuoteField* pInputQuote, int nRequestID);
	///报价操作请求
	TDAPI_API int		ReqQuoteAction(CThostFtdcTraderApi* pApi, CThostFtdcInputQuoteActionField* pInputQuoteAction, int nRequestID);



	///申请组合录入请求
	TDAPI_API int		ReqCombActionInsert(CThostFtdcTraderApi* pApi, CThostFtdcInputCombActionField* pInputCombAction, int nRequestID);
	///请求查询组合合约安全系数
	TDAPI_API int		ReqQryCombInstrumentGuard(CThostFtdcTraderApi* pApi, CThostFtdcQryCombInstrumentGuardField* pQryCombInstrumentGuard, int nRequestID);
	///请求查询申请组合
	TDAPI_API int		ReqQryCombAction(CThostFtdcTraderApi* pApi, CThostFtdcQryCombActionField* pQryCombAction, int nRequestID);


	///请求查询投资者持仓
	TDAPI_API int		ReqQryInvestorPosition(CThostFtdcTraderApi* pApi, CThostFtdcQryInvestorPositionField* pQryInvestorPosition, int nRequestID);
	///请求查询投资者持仓明细
	TDAPI_API int		ReqQryInvestorPositionDetail(CThostFtdcTraderApi* pApi, CThostFtdcQryInvestorPositionDetailField* pQryInvestorPositionDetail, int nRequestID);
	///请求查询投资者持仓明细
	TDAPI_API int		ReqQryInvestorPositionCombineDetail(CThostFtdcTraderApi* pApi, CThostFtdcQryInvestorPositionCombineDetailField* pQryInvestorPositionCombineDetail, int nRequestID);
	///请求查询资金账户
	TDAPI_API int		ReqQryTradingAccount(CThostFtdcTraderApi* pApi, CThostFtdcQryTradingAccountField* pQryTradingAccount, int nRequestID);
	///请求查询投资者
	TDAPI_API int		ReqQryInvestor(CThostFtdcTraderApi* pApi, CThostFtdcQryInvestorField* pQryInvestor, int nRequestID);
	///请求查询交易编码
	TDAPI_API int		ReqQryTradingCode(CThostFtdcTraderApi* pApi, CThostFtdcQryTradingCodeField* pQryTradingCode, int nRequestID);
	///请求查询投资单元
	TDAPI_API int		ReqQryInvestUnit(CThostFtdcTraderApi* pApi, CThostFtdcQryInvestUnitField* pQryInvestUnit, int nRequestID);


#pragma region 结算
	///请求查询投资者结算结果
	TDAPI_API int		ReqQrySettlementInfo(CThostFtdcTraderApi* pApi, CThostFtdcQrySettlementInfoField* pQrySettlementInfo, int nRequestID);
	///请求查询结算信息确认
	TDAPI_API int		ReqQrySettlementInfoConfirm(CThostFtdcTraderApi* pApi, CThostFtdcQrySettlementInfoConfirmField* pQrySettlementInfoConfirm, int nRequestID);
	///投资者结算结果确认
	TDAPI_API int		ReqSettlementInfoConfirm(CThostFtdcTraderApi* pApi, CThostFtdcSettlementInfoConfirmField* pSettlementInfoConfirm, int nRequestID);
#pragma endregion


#pragma region product/Instrument
	///请求查询产品
	TDAPI_API int		ReqQryProduct(CThostFtdcTraderApi* pApi, CThostFtdcQryProductField* pQryProduct, int nRequestID);
	///请求查询产品报价汇率
	TDAPI_API int		ReqQryProductExchRate(CThostFtdcTraderApi* pApi, CThostFtdcQryProductExchRateField* pQryProductExchRate, int nRequestID);
	///请求查询产品组
	TDAPI_API int		ReqQryProductGroup(CThostFtdcTraderApi* pApi, CThostFtdcQryProductGroupField* pQryProductGroup, int nRequestID);

	///请求查询合约
	TDAPI_API int		ReqQryInstrument(CThostFtdcTraderApi* pApi, CThostFtdcQryInstrumentField* pQryInstrument, int nRequestID);
	///请求查询合约保证金率
	TDAPI_API int		ReqQryInstrumentMarginRate(CThostFtdcTraderApi* pApi, CThostFtdcQryInstrumentMarginRateField* pQryInstrumentMarginRate, int nRequestID);
	///请求查询合约手续费率
	TDAPI_API int		ReqQryInstrumentCommissionRate(CThostFtdcTraderApi* pApi, CThostFtdcQryInstrumentCommissionRateField* pQryInstrumentCommissionRate, int nRequestID);

	///请求查询投资者品种/跨品种保证金
	TDAPI_API int		ReqQryInvestorProductGroupMargin(CThostFtdcTraderApi* pApi, CThostFtdcQryInvestorProductGroupMarginField* pQryInvestorProductGroupMargin, int nRequestID);

	///请求查询做市商合约手续费率
	TDAPI_API int		ReqQryMMInstrumentCommissionRate(CThostFtdcTraderApi* pApi, CThostFtdcQryMMInstrumentCommissionRateField* pQryMMInstrumentCommissionRate, int nRequestID);
	///请求查询做市商期权合约手续费
	TDAPI_API int		ReqQryMMOptionInstrCommRate(CThostFtdcTraderApi* pApi, CThostFtdcQryMMOptionInstrCommRateField* pQryMMOptionInstrCommRate, int nRequestID);

	///请求查询仓单折抵信息
	TDAPI_API int		ReqQryEWarrantOffset(CThostFtdcTraderApi* pApi, CThostFtdcQryEWarrantOffsetField* pQryEWarrantOffset, int nRequestID);

	///请求查询报单手续费
	TDAPI_API int		ReqQryInstrumentOrderCommRate(CThostFtdcTraderApi* pApi, CThostFtdcQryInstrumentOrderCommRateField* pQryInstrumentOrderCommRate, int nRequestID);
#pragma endregion


#pragma region 二级代理/sec agent
	///请求查询资金账户
	TDAPI_API int		ReqQrySecAgentTradingAccount(CThostFtdcTraderApi* pApi, CThostFtdcQryTradingAccountField* pQryTradingAccount, int nRequestID);
	///请求查询二级代理操作员银期权限
	TDAPI_API int		ReqQrySecAgentACIDMap(CThostFtdcTraderApi* pApi, CThostFtdcQrySecAgentACIDMapField* pQrySecAgentACIDMap, int nRequestID);
	///请求查询二级代理商资金校验模式
	TDAPI_API int		ReqQrySecAgentCheckMode(CThostFtdcTraderApi* pApi, CThostFtdcQrySecAgentCheckModeField* pQrySecAgentCheckMode, int nRequestID);
	///请求查询二级代理商信息
	TDAPI_API int		ReqQrySecAgentTradeInfo(CThostFtdcTraderApi* pApi, CThostFtdcQrySecAgentTradeInfoField* pQrySecAgentTradeInfo, int nRequestID);
#pragma endregion


#pragma region 期权option
	///期权自对冲录入请求
	TDAPI_API int		ReqOptionSelfCloseInsert(CThostFtdcTraderApi* pApi, CThostFtdcInputOptionSelfCloseField* pInputOptionSelfClose, int nRequestID);
	///期权自对冲操作请求
	TDAPI_API int		ReqOptionSelfCloseAction(CThostFtdcTraderApi* pApi, CThostFtdcInputOptionSelfCloseActionField* pInputOptionSelfCloseAction, int nRequestID);

	///请求查询期权交易成本
	TDAPI_API int		ReqQryOptionInstrTradeCost(CThostFtdcTraderApi* pApi, CThostFtdcQryOptionInstrTradeCostField* pQryOptionInstrTradeCost, int nRequestID);
	///请求查询期权合约手续费
	TDAPI_API int		ReqQryOptionInstrCommRate(CThostFtdcTraderApi* pApi, CThostFtdcQryOptionInstrCommRateField* pQryOptionInstrCommRate, int nRequestID);
	///请求查询期权自对冲
	TDAPI_API int		ReqQryOptionSelfClose(CThostFtdcTraderApi* pApi, CThostFtdcQryOptionSelfCloseField* pQryOptionSelfClose, int nRequestID);
#pragma endregion


#pragma region Banking
	///请求查询转帐银行
	TDAPI_API int		ReqQryTransferBank(CThostFtdcTraderApi* pApi, CThostFtdcQryTransferBankField* pQryTransferBank, int nRequestID);
	///请求查询银期签约关系
	TDAPI_API int		ReqQryAccountregister(CThostFtdcTraderApi* pApi, CThostFtdcQryAccountregisterField* pQryAccountregister, int nRequestID);
	///请求查询签约银行
	TDAPI_API int		ReqQryContractBank(CThostFtdcTraderApi* pApi, CThostFtdcQryContractBankField* pQryContractBank, int nRequestID);
	///请求查询转帐流水
	TDAPI_API int		ReqQryTransferSerial(CThostFtdcTraderApi* pApi, CThostFtdcQryTransferSerialField* pQryTransferSerial, int nRequestID);
	///期货发起查询银行余额请求
	TDAPI_API int		ReqQueryBankAccountMoneyByFuture(CThostFtdcTraderApi* pApi, CThostFtdcReqQueryAccountField* pReqQueryAccount, int nRequestID);

	///期货发起银行资金转期货请求
	TDAPI_API int		ReqFromBankToFutureByFuture(CThostFtdcTraderApi* pApi, CThostFtdcReqTransferField* pReqTransfer, int nRequestID);
	///期货发起期货资金转银行请求
	TDAPI_API int		ReqFromFutureToBankByFuture(CThostFtdcTraderApi* pApi, CThostFtdcReqTransferField* pReqTransfer, int nRequestID);
#pragma endregion


#pragma region Exchange/交易所
	///请求查询交易所
	TDAPI_API int		ReqQryExchange(CThostFtdcTraderApi* pApi, CThostFtdcQryExchangeField* pQryExchange, int nRequestID);
	///请求查询交易所保证金率
	TDAPI_API int		ReqQryExchangeMarginRate(CThostFtdcTraderApi* pApi, CThostFtdcQryExchangeMarginRateField* pQryExchangeMarginRate, int nRequestID);
	///请求查询交易所调整保证金率
	TDAPI_API int		ReqQryExchangeMarginRateAdjust(CThostFtdcTraderApi* pApi, CThostFtdcQryExchangeMarginRateAdjustField* pQryExchangeMarginRateAdjust, int nRequestID);
	///请求查询汇率
	TDAPI_API int		ReqQryExchangeRate(CThostFtdcTraderApi* pApi, CThostFtdcQryExchangeRateField* pQryExchangeRate, int nRequestID);
#pragma endregion


#pragma region Broker
	///请求查询经纪公司交易参数
	TDAPI_API int		ReqQryBrokerTradingParams(CThostFtdcTraderApi* pApi, CThostFtdcQryBrokerTradingParamsField* pQryBrokerTradingParams, int nRequestID);
	///请求查询经纪公司交易算法
	TDAPI_API int		ReqQryBrokerTradingAlgos(CThostFtdcTraderApi* pApi, CThostFtdcQryBrokerTradingAlgosField* pQryBrokerTradingAlgos, int nRequestID);
#pragma endregion

#pragma region CFMMC
	///请求查询监控中心用户令牌
	TDAPI_API int		ReqQueryCFMMCTradingAccountToken(CThostFtdcTraderApi* pApi, CThostFtdcQueryCFMMCTradingAccountTokenField* pQueryCFMMCTradingAccountToken, int nRequestID);

	///请求查询保证金监管系统经纪公司资金账户密钥
	TDAPI_API int		ReqQryCFMMCTradingAccountKey(CThostFtdcTraderApi* pApi, CThostFtdcQryCFMMCTradingAccountKeyField* pQryCFMMCTradingAccountKey, int nRequestID);
#pragma endregion




#pragma endregion

#pragma region 注册回调函数
	//========================================
	//==================================== 回调函数 =======================================
	TDAPI_API void RegOnRspError(TraderSpi* pSpi, CBOnRspError cb);	//错误应答
	TDAPI_API void RegOnHeartBeatWarning(TraderSpi* pSpi, CBOnHeartBeatWarning cb);		//心跳超时警告。当长时间未收到报文时，该方法被调用。

	TDAPI_API void RegOnRspFrontConnected(TraderSpi* pSpi, CBOnRspFrontConnected cb);		//当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
	TDAPI_API void RegOnRspFrontDisconnected(TraderSpi* pSpi, CBOnRspFrontDisconnected cb);		//当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。

	TDAPI_API void RegOnRspAuthenticate(TraderSpi* pSpi, CBOnRspAuthenticate cb);

	TDAPI_API void RegOnRspUserLogin(TraderSpi* pSpi, CBOnRspUserLogin cb);	//登录请求响应
	TDAPI_API void RegOnRspUserLogout(TraderSpi* pSpi, CBOnRspUserLogout cb);	//登出请求响应

	TDAPI_API void RegOnRspSettlementInfoConfirm(TraderSpi* pSpi, CBOnRspSettlementInfoConfirm cb);	//投资者结算结果确认响应

	TDAPI_API void RegOnRspQryTradingAccount(TraderSpi* pSpi, CBOnRspQryTradingAccount cb);	//请求查询资金账户响应

	TDAPI_API void RegOnRspQryInvestorPosition(TraderSpi* pSpi, CBOnRspQryInvestorPosition cb);	//请求查询投资者持仓响应

	TDAPI_API void RegOnRspQryInstrument(TraderSpi* pSpi, CBOnRspQryInstrument cb);	//请求查询合约响应

	TDAPI_API void RegOnRspOrderInsert(TraderSpi* pSpi, CBOnRspOrderInsert cb);	//报单录入请求响应
	TDAPI_API void RegOnRtnOrder(TraderSpi* pSpi, CBOnRtnOrder cb);	//报单通知
	TDAPI_API void RegOnRtnTrade(TraderSpi* pSpi, CBOnRtnTrade cb);	//成交通知



	TDAPI_API void RegRspUserPasswordUpdate(TraderSpi* pSpi, CBRspUserPasswordUpdate cb);	//用户口令更新请求响应
	TDAPI_API void RegRspTradingAccountPasswordUpdate(TraderSpi* pSpi, CBRspTradingAccountPasswordUpdate cb);	//资金账户口令更新请求响应
	TDAPI_API void RegRspUserAuthMethod(TraderSpi* pSpi, CBRspUserAuthMethod cb);	//查询用户当前支持的认证模式的回复
	TDAPI_API void RegRspGenUserCaptcha(TraderSpi* pSpi, CBRspGenUserCaptcha cb);	//获取图形验证码请求的回复
	TDAPI_API void RegRspGenUserText(TraderSpi* pSpi, CBRspGenUserText cb);	//获取短信验证码请求的回复
	TDAPI_API void RegRspParkedOrderInsert(TraderSpi* pSpi, CBRspParkedOrderInsert cb);	//预埋单录入请求响应
	TDAPI_API void RegRspParkedOrderAction(TraderSpi* pSpi, CBRspParkedOrderAction cb);	//预埋撤单录入请求响应
	TDAPI_API void RegRspOrderAction(TraderSpi* pSpi, CBRspOrderAction cb);	//报单操作请求响应
	TDAPI_API void RegRspQueryMaxOrderVolume(TraderSpi* pSpi, CBRspQueryMaxOrderVolume cb);	//查询最大报单数量响应
	TDAPI_API void RegRspRemoveParkedOrder(TraderSpi* pSpi, CBRspRemoveParkedOrder cb);	//删除预埋单响应
	TDAPI_API void RegRspRemoveParkedOrderAction(TraderSpi* pSpi, CBRspRemoveParkedOrderAction cb);	//删除预埋撤单响应
	TDAPI_API void RegBatchOrderAction(TraderSpi* pSpi, CBRspBatchOrderAction cb);	//批量报单操作请求响应
	TDAPI_API void RegCombActionInsert(TraderSpi* pSpi, CBRspCombActionInsert cb);	//申请组合录入请求响应
	TDAPI_API void RegOnRspQryOrder(TraderSpi* pSpi, CBOnRspQryOrder cb);	//请求查询报单响应
	TDAPI_API void RegRspQryTrade(TraderSpi* pSpi, CBRspQryTrade cb);	//请求查询成交响应
	TDAPI_API void RegRspQryInvestor(TraderSpi* pSpi, CBRspQryInvestor cb);	//请求查询投资者响应
	TDAPI_API void RegRspQryTradingCode(TraderSpi* pSpi, CBRspQryTradingCode cb);	//请求查询交易编码响应
	TDAPI_API void RegRspQryInstrumentMarginRate(TraderSpi* pSpi, CBRspQryInstrumentMarginRate cb);	//请求查询合约保证金率响应
	TDAPI_API void RegRspQryInstrumentCommissionRate(TraderSpi* pSpi, CBRspQryInstrumentCommissionRate cb);	//请求查询合约手续费率响应
	TDAPI_API void RegRspQryExchange(TraderSpi* pSpi, CBRspQryExchange cb);	//请求查询交易所响应
	TDAPI_API void RegRspQryDepthMarketData(TraderSpi* pSpi, CBRspQryDepthMarketData cb);	//请求查询行情响应
	TDAPI_API void RegRspQrySettlementInfo(TraderSpi* pSpi, CBRspQrySettlementInfo cb);	//请求查询投资者结算结果响应
	TDAPI_API void RegRspQryTransferBank(TraderSpi* pSpi, CBRspQryTransferBank cb);	//请求查询转帐银行响应
	TDAPI_API void RegRspQryInvestorPositionDetail(TraderSpi* pSpi, CBRspQryInvestorPositionDetail cb);	//请求查询投资者持仓明细响应
	TDAPI_API void RegRspQryNotice(TraderSpi* pSpi, CBRspQryNotice cb);	//请求查询客户通知响应
	TDAPI_API void RegRspQrySettlementInfoConfirm(TraderSpi* pSpi, CBRspQrySettlementInfoConfirm cb);	//请求查询结算信息确认响应
	TDAPI_API void RegRspQryInvestorPositionCombineDetail(TraderSpi* pSpi, CBRspQryInvestorPositionCombineDetail cb);	//请求查询投资者持仓明细响应
	TDAPI_API void RegRspQryCFMMCTradingAccountKey(TraderSpi* pSpi, CBRspQryCFMMCTradingAccountKey cb);	//查询保证金监管系统经纪公司资金账户密钥响应
	TDAPI_API void RegRspQryEWarrantOffset(TraderSpi* pSpi, CBRspQryEWarrantOffset cb);	//请求查询仓单折抵信息
	TDAPI_API void RegRspQryInvestorProductGroupMargin(TraderSpi* pSpi, CBRspQryInvestorProductGroupMargin cb);	//请求查询投资者品种/跨品种保证金
	TDAPI_API void RegRspQryExchangeMarginRate(TraderSpi* pSpi, CBRspQryExchangeMarginRate cb);	//请求查询交易所保证金率
	TDAPI_API void RegRspQryExchangeMarginRateAdjust(TraderSpi* pSpi, CBRspQryExchangeMarginRateAdjust cb);	//请求查询交易所调整保证金率
	TDAPI_API void RegRspQryExchangeRate(TraderSpi* pSpi, CBRspQryExchangeRate cb);	//请求查询汇率响应
	TDAPI_API void RegRspQrySecAgentACIDMap(TraderSpi* pSpi, CBRspQrySecAgentACIDMap cb);	//请求查询二级代理操作员银期权限响应
	TDAPI_API void RegRspQryProductExchRate(TraderSpi* pSpi, CBRspQryProductExchRate cb);	//请求查询产品报价汇率
	TDAPI_API void RegRspQryProductGroup(TraderSpi* pSpi, CBRspQryProductGroup cb);	//请求查询产品组
	TDAPI_API void RegRspQryMMInstrumentCommissionRate(TraderSpi* pSpi, CBRspQryMMInstrumentCommissionRate cb);	//请求查询做市商合约手续费率响应
	TDAPI_API void RegRspQryMMOptionInstrCommRate(TraderSpi* pSpi, CBRspQryMMOptionInstrCommRate cb);	//请求查询做市商期权合约手续费响应
	TDAPI_API void RegRspQryInstrumentOrderCommRate(TraderSpi* pSpi, CBRspQryInstrumentOrderCommRate cb);	//请求查询报单手续费响应
	TDAPI_API void RegRspQrySecAgentTradingAccount(TraderSpi* pSpi, CBRspQrySecAgentTradingAccount cb);	//请求查询资金账户响应
	TDAPI_API void RegRspQrySecAgentCheckMode(TraderSpi* pSpi, CBRspQrySecAgentCheckMode cb);	//请求查询二级代理商资金校验模式响应
	TDAPI_API void RegRspQrySecAgentTradeInfo(TraderSpi* pSpi, CBRspQrySecAgentTradeInfo cb);	//请求查询二级代理商信息响应
	TDAPI_API void RegRspQryOptionInstrTradeCost(TraderSpi* pSpi, CBRspQryOptionInstrTradeCost cb);	//请求查询期权交易成本响应
	TDAPI_API void RegRspQryOptionInstrCommRate(TraderSpi* pSpi, CBRspQryOptionInstrCommRate cb);	//请求查询期权合约手续费响应
	TDAPI_API void RegRspQryExecOrder(TraderSpi* pSpi, CBRspQryExecOrder cb);	//请求查询执行宣告响应
	TDAPI_API void RegRspQryForQuote(TraderSpi* pSpi, CBRspQryForQuote cb);	//请求查询询价响应
	TDAPI_API void RegRspQryQuote(TraderSpi* pSpi, CBRspQryQuote cb);	//请求查询报价响应
	TDAPI_API void RegRspQryOptionSelfClose(TraderSpi* pSpi, CBRspQryOptionSelfClose cb);	//请求查询期权自对冲响应
	TDAPI_API void RegRspQryInvestUnit(TraderSpi* pSpi, CBRspQryInvestUnit cb);	//请求查询投资单元响应
	TDAPI_API void RegRspQryCombInstrumentGuard(TraderSpi* pSpi, CBRspQryCombInstrumentGuard cb);	//请求查询组合合约安全系数响应
	TDAPI_API void RegRspQryCombAction(TraderSpi* pSpi, CBRspQryCombAction cb);	//请求查询申请组合响应
	TDAPI_API void RegRspQryTransferSerial(TraderSpi* pSpi, CBRspQryTransferSerial cb);	//请求查询转帐流水响应
	TDAPI_API void RegOnRspQryAccountregister(TraderSpi* pSpi, CBOnRspQryAccountregister cb);	//请求查询银期签约关系响应
	TDAPI_API void RegErrRtnOrderInsert(TraderSpi* pSpi, CBErrRtnOrderInsert cb);	//报单录入错误回报
	TDAPI_API void RegErrRtnOrderAction(TraderSpi* pSpi, CBErrRtnOrderAction cb);	//报单操作错误回报
	TDAPI_API void RegRtnInstrumentStatus(TraderSpi* pSpi, CBRtnInstrumentStatus cb);	//合约交易状态通知
	TDAPI_API void RegRtnTradingNotice(TraderSpi* pSpi, CBRtnTradingNotice cb);	//交易通知
	TDAPI_API void RegRtnErrorConditionalOrder(TraderSpi* pSpi, CBRtnErrorConditionalOrder cb);	//提示条件单校验错误
	TDAPI_API void RegRspQryContractBank(TraderSpi* pSpi, CBRspQryContractBank cb);	//请求查询签约银行响应
	TDAPI_API void RegRspQryParkedOrder(TraderSpi* pSpi, CBRspQryParkedOrder cb);	//请求查询预埋单响应
	TDAPI_API void RegRspQryParkedOrderAction(TraderSpi* pSpi, CBRspQryParkedOrderAction cb);	//请求查询预埋撤单响应
	TDAPI_API void RegRspQryTradingNotice(TraderSpi* pSpi, CBRspQryTradingNotice cb);	//请求查询交易通知响应
	TDAPI_API void RegRspQryBrokerTradingParams(TraderSpi* pSpi, CBRspQryBrokerTradingParams cb);	//请求查询经纪公司交易参数响应
	TDAPI_API void RegRspQryBrokerTradingAlgos(TraderSpi* pSpi, CBRspQryBrokerTradingAlgos cb);	//请求查询经纪公司交易算法响应
	TDAPI_API void RegRtnFromBankToFutureByBank(TraderSpi* pSpi, CBRtnFromBankToFutureByBank cb);	//银行发起银行资金转期货通知
	TDAPI_API void RegRtnFromFutureToBankByBank(TraderSpi* pSpi, CBRtnFromFutureToBankByBank cb);	//银行发起期货资金转银行通知
	TDAPI_API void RegRtnRepealFromBankToFutureByBank(TraderSpi* pSpi, CBRtnRepealFromBankToFutureByBank cb);	//银行发起冲正银行转期货通知
	TDAPI_API void RegRtnRepealFromFutureToBankByBank(TraderSpi* pSpi, CBRtnRepealFromFutureToBankByBank cb);	//银行发起冲正期货转银行通知
	TDAPI_API void RegRtnFromBankToFutureByFuture(TraderSpi* pSpi, CBRtnFromBankToFutureByFuture cb);	//期货发起银行资金转期货通知
	TDAPI_API void RegRtnFromFutureToBankByFuture(TraderSpi* pSpi, CBRtnFromFutureToBankByFuture cb);	//期货发起期货资金转银行通知
	TDAPI_API void RegRtnRepealFromBankToFutureByFutureManual(TraderSpi* pSpi, CBRtnRepealFromBankToFutureByFutureManual cb);	//系统运行时期货端手工发起冲正银行转期货请求，银行处理完毕后报盘发回的通知
	TDAPI_API void RegRtnRepealFromFutureToBankByFutureManual(TraderSpi* pSpi, CBRtnRepealFromFutureToBankByFutureManual cb);	//系统运行时期货端手工发起冲正期货转银行请求，银行处理完毕后报盘发回的通知
	TDAPI_API void RegRtnQueryBankBalanceByFuture(TraderSpi* pSpi, CBRtnQueryBankBalanceByFuture cb);	//期货发起查询银行余额通知
	TDAPI_API void RegErrRtnBankToFutureByFuture(TraderSpi* pSpi, CBErrRtnBankToFutureByFuture cb);	//期货发起银行资金转期货错误回报
	TDAPI_API void RegErrRtnFutureToBankByFuture(TraderSpi* pSpi, CBErrRtnFutureToBankByFuture cb);	//期货发起期货资金转银行错误回报
	TDAPI_API void RegErrRtnRepealBankToFutureByFutureManual(TraderSpi* pSpi, CBErrRtnRepealBankToFutureByFutureManual cb);	//系统运行时期货端手工发起冲正银行转期货错误回报
	TDAPI_API void RegErrRtnRepealFutureToBankByFutureManual(TraderSpi* pSpi, CBErrRtnRepealFutureToBankByFutureManual cb);	//系统运行时期货端手工发起冲正期货转银行错误回报
	TDAPI_API void RegErrRtnQueryBankBalanceByFuture(TraderSpi* pSpi, CBErrRtnQueryBankBalanceByFuture cb);	//期货发起查询银行余额错误回报
	TDAPI_API void RegRtnRepealFromBankToFutureByFuture(TraderSpi* pSpi, CBRtnRepealFromBankToFutureByFuture cb);	//期货发起冲正银行转期货请求，银行处理完毕后报盘发回的通知
	TDAPI_API void RegRtnRepealFromFutureToBankByFuture(TraderSpi* pSpi, CBRtnRepealFromFutureToBankByFuture cb);	//期货发起冲正期货转银行请求，银行处理完毕后报盘发回的通知
	TDAPI_API void RegRspFromBankToFutureByFuture(TraderSpi* pSpi, CBRspFromBankToFutureByFuture cb);	//期货发起银行资金转期货应答
	TDAPI_API void RegRspFromFutureToBankByFuture(TraderSpi* pSpi, CBRspFromFutureToBankByFuture cb);	//期货发起期货资金转银行应答
	TDAPI_API void RegRspQueryBankAccountMoneyByFuture(TraderSpi* pSpi, CBRspQueryBankAccountMoneyByFuture cb);	//期货发起查询银行余额应答
	TDAPI_API void RegRspQueryCFMMCTradingAccountToken(TraderSpi* pSpi, CBRspQueryCFMMCTradingAccountToken cb);	//查询监控中心用户令牌应答
	TDAPI_API void RegRtnCFMMCTradingAccountToken(TraderSpi* pSpi, CBRtnCFMMCTradingAccountToken cb);	//查询监控中心用户令牌通知
#pragma endregion

}
