#pragma once
enum OperateEnum			// 操作枚举，长度为64位
{
	Auth = 1 << 0,									// 验证
	Login = 1 << 1,									// 登录
	Logout = 1 << 2,								// 登出
	UpdateLoginPwd = 1 << 3,						// 更新登录密码
	UpdateTrdAccountPwd = 1 << 4,					// 更新交易账户密码

	OrderInsert = 1 << 5,							// 报单录入
	ParkedOrderInsert = 1 << 6,						// 预埋单录入
	ParkedOrderAction = 1 << 7,						// 预埋撤单录入
	RemoveParkedOrder = 1 << 8,						// 删除预埋单

	OrderAction = 1 << 9,							// 报单操作
	QryOrder = 1 << 10,								// 查询保单
	QueryMaxOrderVolume = 1 << 11,					// 查询最大订单量
	SettlementInfoConfirm = 1 << 12,				// 投资者结算结果确认

	ForQuoteInsert = 1 << 13,						// 查询价
	QryQuote = 1 << 14,								// 查询报价
	QryCombAction = 1 << 15,						// 查询组合
	QryCombInstrumentGuard = 1 << 16,				// 查询组合合约的安全系数
	QryTransferSerial = 1 << 17,					// 查询转账流水
	QryAccountregister = 1 << 18,					// 查询银期签约关系

	QryContractBank = 1 << 19,						// 查询签约银行
	QryParkedOrder = 1 << 20,						// 查询预埋订单
	QryParkedOrderAction = 1 << 21,					// 查询预埋撤单
	QryTradingNotice = 1 << 22,						// 查询交易通知
	QryBrokerTradingParams = 1 << 23,				// 查询经济公司交易参数

	QryBrokerTradingAlgos = 1 << 24,				// 查询经济公司的交易算法
	QueryBankBalanceByFuture = 1 << 25,				// 查询期货银行余额
	QueryCFMMCTradingAccountToken = 1 << 26,		// 查询监控中心用户令牌
	ReqFromBankToFutureByFuture = 1 << 27,			// 期货请求银行转期货请求
	ReqFromFutureToBankByFuture = 1 << 28,			// 期货请求期货转银行请求

	ReqQryInvestUnit = 1 << 29,						// 请求查询投资单元
	ReqQrySecAgentTradeInfo = 1 << 30,				// 请求查询二级代理商信息
	ReqQrySecAgentCheckMode = 1 << 31,				// 请求查询二级代理商资金验证模式
	ReqQrySecAgentTradingAccount = 1 << 32,			// 请求查询资金账户
	ReqQryInstrumentOrderCommRate = 1 << 33,		// 请求报单手续费
	ReqQryMMInstrumentCommissionRate = 1 << 34,		// 请求查询做市商手续费

	ReqQryProductGroup = 1 << 35,					// 请求查询产品组
	ReqQryProductExchRate = 1 << 36,				// 请求查询产品报价汇率
	ReqQryExchangeRate = 1 << 37,					// 请求查询汇率
	ReqQryExchangeMarginRateAdjust = 1 << 38,		// 请求交易所调整的保证金
	ReqQryExchangeMarginRate = 1 << 39,				// 请求查询交易所保证金率
	ReqQryInvestorProductGroupMargin = 1 << 40,		// 请求查询投资者品种/跨品种保证金

	ReqQryEWarrantOffset = 1 << 41,					// 请求查询持仓信息
	ReqQryCFMMCTradingAccountKey = 1 << 42,			// 请求查询保证金监管系统经纪公司资金账户密钥
	ReqQryInvestorPositionCombineDetail = 1 << 43,	// 请求查询投资者组合合约持仓明细
	ReqQryInvestorPositionDetail = 1 << 44,			// 请求查询投资者合约持仓明细
	ReqQryTransferBank = 1 << 45,					// 请求查询转账银行

	ReqQrySettlementInfo = 1 << 46,					// 请求查询投资者结算信息
	ReqQryDepthMarketData = 1 << 47,				// 请求查询行情数据
	ReqQryInstrument = 1 << 48,						// 请求查询合约
	ReqQryExchange = 1 << 49,						// 请求查询交易所
	ReqQryInstrumentCommissionRate = 1 << 50,		// 请求查询合约手续费
	ReqQryInstrumentMarginRate = 1 << 51,			// 请求查询合约的保证金率

	ReqQryTradingCode = 1 << 52,					// 请求查询交易者编号
	ReqQryInvestor = 1 << 53,						// 请求查询投资者
	ReqQryTradingAccount = 1 << 54,					// 请求查询资金账户
	ReqQryInvestorPosition = 1 << 55,				// 请求查询投资者持仓
	ReqQryTrade = 1 << 56,							// 请求查询交易
};