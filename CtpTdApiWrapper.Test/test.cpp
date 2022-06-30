#include "pch.h"
#include <ostream>
#include <fstream>
#include <mutex>
#include "..\CtpTdApiWrapper\TraderApi.h"
#include "..\CtpTdApiWrapper\TraderSpi.h"
using namespace std;

// 公共参数
TThostFtdcBrokerIDType gBrokerID = "9999";                         // 模拟经纪商代码
TThostFtdcInvestorIDType gInvesterID = "180935";                         // 投资者账户名
TThostFtdcPasswordType gInvesterPassword = "hello@123";                     // 投资者密码

// 行情参数
CThostFtdcTraderApi *g_pTdApi = nullptr;                           // 行情指针
TraderSpi *g_pTdSpi = nullptr;                           // spi
//char gTradeFrontAddr[] = "tcp://180.168.146.187:10201";            // 模拟交易前置地址 第一组
char gTradeFrontAddr[] = "tcp://180.168.146.187:10130";            // 模拟交易前置地址 24h
//char *g_pInstrumentID[] = {"rb2205"}; // 行情合约代码列表，中、上、大、郑交易所各选一种
int instrumentNum = 1;                                     // 行情合约订阅数量

struct CtpTdApiWrapperParams
{
	bool isAuth;
	bool isLogin;	
	bool isLogout;
	bool isUpdateLoginPwd;
	bool isUpdateTrdAccountPwd;
	
	bool isOrderInsert;
	bool isParkedOrderInsert;
	bool isParkedOrderAction;
	bool isRemoveParkedOrder;

	bool isOrderAction;
	bool isQryOrder;
	bool isQueryMaxOrderVolume;
	bool isSettlementInfoConfirm;

	bool isForQuoteInsert;								// 查询价
	bool isQryQuote;									// 查询报价
	bool isQryCombAction;								// 查询组合
	bool isQryCombInstrumentGuard;						// 查询组合合约的安全系数
	bool isQryTransferSerial;							// 查询转账流水
	bool isQryAccountregister;							// 查询银期签约关系

	bool isQryContractBank;								// 查询签约银行
	bool isQryParkedOrder;								// 查询预埋订单
	bool isQryParkedOrderAction;						// 查询预埋撤单
	bool isQryTradingNotice;							// 查询交易通知
	bool isQryBrokerTradingParams;						// 查询经济公司交易参数

	bool isQryBrokerTradingAlgos;						// 查询经济公司的交易算法
	bool isQueryBankBalanceByFuture;					// 查询期货银行余额
	bool isQueryCFMMCTradingAccountToken;				// 查询监控中心用户令牌
	bool isReqFromBankToFutureByFuture;					// 期货请求银行转期货请求
	bool isReqFromFutureToBankByFuture;					// 期货请求期货转银行请求

	bool isReqQryInvestUnit;							// 请求查询投资单元
	bool isReqQrySecAgentTradeInfo;						// 请求查询二级代理商信息
	bool isReqQrySecAgentCheckMode;						// 请求查询二级代理商资金验证模式
	bool isReqQrySecAgentTradingAccount;				// 请求查询资金账户
	bool isReqQryInstrumentOrderCommRate;				// 请求报单手续费
	bool isReqQryMMInstrumentCommissionRate;			// 请求查询做市商手续费

	bool isReqQryProductGroup;							// 请求查询产品组
	bool isReqQryProductExchRate;						// 请求查询产品报价汇率
	bool isReqQryExchangeRate;							// 请求查询汇率
	bool isReqQryExchangeMarginRateAdjust;				// 请求交易所调整的保证金
	bool isReqQryExchangeMarginRate;					// 请求查询交易所保证金率
	bool isReqQryInvestorProductGroupMargin;			// 请求查询投资者品种/跨品种保证金

	bool isReqQryEWarrantOffset;						// 请求查询持仓信息
	bool isReqQryCFMMCTradingAccountKey;				// 请求查询保证金监管系统经纪公司资金账户密钥
	bool isReqQryInvestorPositionCombineDetail;			// 请求查询投资者组合合约持仓明细
	bool isReqQryInvestorPositionDetail;				// 请求查询投资者合约持仓明细
	bool isReqQryTransferBank;							// 请求查询转账银行

	bool isReqQrySettlementInfo;						// 请求查询投资者结算信息
	bool isReqQryDepthMarketData;						// 请求查询行情数据
	bool isReqQryInstrument;							// 请求查询合约
	bool isReqQryExchange;								// 请求查询交易所
	bool isReqQryInstrumentCommissionRate;				// 请求查询合约手续费
	bool isReqQryInstrumentMarginRate;					// 请求查询合约的保证金率

	bool isReqQryTradingCode;							// 请求查询交易者编号
	bool isReqQryInvestor;								// 请求查询投资者
	bool isReqQryTradingAccount;						// 请求查询资金账户
	bool isReqQryInvestorPosition;						// 请求查询投资者持仓
	bool isReqQryTrade;									// 请求查询交易

};

CtpTdApiWrapperParams g_CtpTdApiWrapperParams = { '\0' };

// 线程同步参数
mutex g_mtx;
condition_variable g_cond_va;

// 用于检测的变量
bool g_initOK = false;
bool g_authOK = false;
bool g_loginOK = false;
bool g_logoutOK = false;
bool g_updateLoginPwdOK = false;
bool g_updateTrdAccountPwdOK = false;

bool g_orderInsertOK = false;
bool g_parkedOrderInsertOK = false;
bool g_parkedOrderActionOK = false;
bool g_removeParkedOrderOK = false;

bool g_orderActionOK = false;
bool g_qryOrderOK = false;
bool g_queryMaxOrderVolumeOK = false;
bool g_settlementInfoConfirmOK = false;

bool g_forQuoteInsertOK = false;
bool g_qryQuoteOK = false;
bool g_qryCombActionOK = false;
bool g_qryCombInstrumentGuardOK = false;
bool g_qryTransferSerialOK = false;
bool g_qryAccountregisterOK = false;

bool g_instrumentStatusOK = false;
bool g_TradingNoticeOK = false;
bool g_qryContractBankOK = false;
bool g_qryParkedOrderOK = false;
bool g_qryParkedOrderActionOK = false;

bool g_qryTradingNoticeOK = false;
bool g_qryBrokerTradingParamsOK = false;
bool g_qryBrokerTradingAlgosOK = false;
bool g_queryBankBalanceByFutureOK = false;
bool g_queryCFMMCTradingAccountTokenOK = false;

bool g_reqFromBankToFutureByFutureOK = false;
bool g_reqFromFutureToBankByFutureOK = false;
bool g_reqQryInvestUnitOK = false;
bool g_reqQrySecAgentTradeInfoOK = false;
bool g_reqQrySecAgentCheckModeOK = false;

bool g_reqQrySecAgentTradingAccountOK = false;
bool g_reqQryInstrumentOrderCommRateOK = false;
bool g_reqQryMMInstrumentCommissionRateOK = false;
bool g_reqQryProductGroupOK = false;
bool g_reqQryProductExchRateOK = false;

bool g_reqQryExchangeRateOK = false;
bool g_reqQryExchangeMarginRateAdjustOK = false;
bool g_reqQryExchangeMarginRateOK = false;
bool g_reqQryInvestorProductGroupMarginOK = false;
bool g_reqQryEWarrantOffsetOK = false;

bool g_reqQryCFMMCTradingAccountKeyOK = false;
bool g_reqQryInvestorPositionCombineDetailOK = false;
bool g_reqQryInvestorPositionDetailOK = false;
bool g_reqQryTransferBankOK = false;
bool g_reqQrySettlementInfoOK = false;

bool g_reqQryDepthMarketDataOK = false;
bool g_reqQryInstrumentOK = false;
bool g_reqQryExchangeOK = false;
bool g_reqQryInstrumentCommissionRateOK = false;
bool g_reqQryInstrumentMarginRateOK = false;

bool g_reqQryTradingCodeOK = false;
bool g_reqQryInvestorOK = false;
bool g_reqQryTradingAccountOK = false;
bool g_reqQryInvestorPositionOK = false;
bool g_reqQryTradeOK = false;

#pragma region callbacks
void WINAPI  OnFrontConnected()
{
	g_initOK = true;
	g_cond_va.notify_one();

	std::cout << "=====建立网络连接成功=====" << std::endl;

	// 检测需要验证
	if (g_CtpTdApiWrapperParams.isAuth) 
	{
		CThostFtdcReqAuthenticateField authField = { '\0' };
		strcpy_s(authField.AppID, "");
		strcpy_s(authField.AuthCode, "123456");
		strcpy_s(authField.BrokerID, gBrokerID);
		strcpy_s(authField.UserID, gInvesterID);
		int rf = g_pTdApi->ReqAuthenticate(&authField, 0);

		if (!rf)
			cout << ">>>>>>发送验证请求成功" << endl;
		else
			cerr << "---->>>发送认证请求失败" << endl;
	}

	// 检测需要登录
	if (g_CtpTdApiWrapperParams.isLogin) 
	{
		CThostFtdcReqUserLoginField loginReq;
		memset(&loginReq, 0, sizeof(loginReq));
		strcpy_s(loginReq.BrokerID, gBrokerID);
		strcpy_s(loginReq.UserID, gInvesterID);
		strcpy_s(loginReq.Password, gInvesterPassword);
		static int requestID = 0; // 请求编号
		int rt = g_pTdApi->ReqUserLogin(&loginReq, requestID);
		if (!rt)
			std::cout << ">>>>>> 发送登录请求成功" << std::endl;
		else
			std::cerr << "--->>>发送登录请求失败" << std::endl;
	}	
}

// 断开连接通知
void WINAPI OnFrontDisconnected(int nReason)
{
	std::cerr << "=====网络连接断开=====" << std::endl;
	std::cerr << "错误码： " << nReason << std::endl;
}

// 心跳超时警告
void WINAPI OnHeartBeatWarning(int nTimeLapse)
{
	std::cerr << "=====网络心跳超时=====" << std::endl;
	std::cerr << "距上次连接时间： " << nTimeLapse << std::endl;
}

// 验证应答
void WINAPI OnRspAuthenticate(
	CThostFtdcRspAuthenticateField* pRspAuthenticateField, 
	CThostFtdcRspInfoField* pRspInfo, 
	int nRequestID, 
	bool bIsLast) 
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult) 
	{
		g_authOK = true;
		g_cond_va.notify_one();

		std::cout << "=====账户验证成功=====" << std::endl;
		std::cout << "经纪公司代码： " << pRspAuthenticateField->BrokerID<< std::endl;
		std::cout << "用户代码： " << pRspAuthenticateField->UserID << std::endl;
		std::cout << "用户端产品信息： " << pRspAuthenticateField->UserProductInfo << std::endl;
		std::cout << "App代码： " << pRspAuthenticateField->AppID << std::endl;
		std::cout << "App类型： " << pRspAuthenticateField->AppType << std::endl;
	}
	else 
		std::cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// 登录应答
void WINAPI OnRspUserLogin(
	CThostFtdcRspUserLoginField *pRspUserLogin, 
	CThostFtdcRspInfoField *pRspInfo, 
	int nRequestID, 
	bool bIsLast)
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult)
	{
		g_loginOK = true;
		g_cond_va.notify_one();

		std::cout << "=====账户登录成功=====" << std::endl;
		std::cout << "交易日： " << pRspUserLogin->TradingDay << std::endl;
		std::cout << "登录时间： " << pRspUserLogin->LoginTime << std::endl;
		std::cout << "经纪商： " << pRspUserLogin->BrokerID << std::endl;
		std::cout << "帐户名： " << pRspUserLogin->UserID << std::endl;

		if (g_CtpTdApiWrapperParams.isLogout) 
		{
			CThostFtdcUserLogoutField logoutField = { '\0' };
			strcpy_s(logoutField.BrokerID, gBrokerID);
			strcpy_s(logoutField.UserID, gInvesterID);
			int rt = g_pTdApi->ReqUserLogout(&logoutField, 0);

			if (!rt)
				std::cout << ">>>>>>发送登出请求成功" << std::endl;			
			else 
				std::cerr << ">>>>>>发送登出请求失败" << std::endl;			
		}

		// 更新登录密码
		if (g_CtpTdApiWrapperParams.isUpdateLoginPwd) {
			CThostFtdcUserPasswordUpdateField userPwdUpdateFiled = { '\0' };
			strcpy_s(userPwdUpdateFiled.BrokerID, gBrokerID);
			strcpy_s(userPwdUpdateFiled.UserID, gInvesterID);
			strcpy_s(userPwdUpdateFiled.OldPassword, gInvesterPassword);
			strcpy_s(userPwdUpdateFiled.NewPassword, gInvesterPassword);		// 注释：需要测试该功能，必须设置新的密码（不能和老密码一样）

			int rt = g_pTdApi->ReqUserPasswordUpdate(&userPwdUpdateFiled, 0);
			if (!rt)
				std::cout << ">>>>>>发送更新密码请求成功" << std::endl;
			else
				std::cerr << "--->>>发送更新密码请求失败" << std::endl;
		}

		// 更新交易账户密码
		if (g_CtpTdApiWrapperParams.isUpdateTrdAccountPwd) {

			CThostFtdcTradingAccountPasswordUpdateField tradingAccountPwdFiled = { '\0' };
			strcpy_s(tradingAccountPwdFiled.BrokerID, gBrokerID);
			strcpy_s(tradingAccountPwdFiled.AccountID, gInvesterID);
			strcpy_s(tradingAccountPwdFiled.OldPassword, "Welcome123");					// 不清楚 simNow 交易账户和密码
			strcpy_s(tradingAccountPwdFiled.NewPassword, "hello@123");
			strcpy_s(tradingAccountPwdFiled.CurrencyID, "CNY");

			int rf = g_pTdApi->ReqTradingAccountPasswordUpdate(&tradingAccountPwdFiled, 0);
			if (!rf)
				std::cout << ">>>>>>>>发送更改交易账户密码请求成功" << std::endl;
			else
				std::cerr << "----->>>>发送修改交易账户密码请求失败" << std::endl;
		}

		// 报单请求
		if (g_CtpTdApiWrapperParams.isOrderInsert) 
		{
			CThostFtdcInputOrderField orderField = { '\0' };
			strcpy_s(orderField.BrokerID, gBrokerID);
			strcpy_s(orderField.InvestorID, gInvesterID);
			strcpy_s(orderField.ExchangeID, "SHFE");
			strcpy_s(orderField.InstrumentID, "ag2206");
			strcpy_s(orderField.UserID, gInvesterID);
			orderField.OrderPriceType = THOST_FTDC_OPT_LimitPrice;//限价
			orderField.Direction = THOST_FTDC_D_Buy;//买
			orderField.CombOffsetFlag[0] = THOST_FTDC_OF_Open;//开
			orderField.CombHedgeFlag[0] = THOST_FTDC_HF_Speculation;//投机
			orderField.LimitPrice = 4902;
			orderField.VolumeTotalOriginal = 1;
			orderField.TimeCondition = THOST_FTDC_TC_GFD;///当日有效
			orderField.VolumeCondition = THOST_FTDC_VC_AV;///任意数量
			orderField.MinVolume = 1;
			orderField.ContingentCondition = THOST_FTDC_CC_Immediately;
			orderField.StopPrice = 0;
			orderField.ForceCloseReason = THOST_FTDC_FCC_NotForceClose;
			orderField.IsAutoSuspend = 0;

			int rf = g_pTdApi->ReqOrderInsert(&orderField, 0);
			if (!rf)
				std::cout << "<<<<<<发送报单请求成功" << std::endl;
			else
				std::cerr << "----->发送报单请求失败" << std::endl;
		}

		// 预埋单
		if (g_CtpTdApiWrapperParams.isParkedOrderInsert) 
		{
			CThostFtdcParkedOrderField orderField = { '\0' };
			strcpy_s(orderField.BrokerID, gBrokerID);
			strcpy_s(orderField.InvestorID, gInvesterID);
			strcpy_s(orderField.ExchangeID, "SHFE");
			strcpy_s(orderField.InstrumentID, "ag2206");
			strcpy_s(orderField.UserID, gInvesterID);
			orderField.OrderPriceType = THOST_FTDC_OPT_LimitPrice;//限价
			orderField.Direction = THOST_FTDC_D_Buy;//买
			orderField.CombOffsetFlag[0] = THOST_FTDC_OF_Open;//开
			orderField.CombHedgeFlag[0] = THOST_FTDC_HF_Speculation;//投机
			orderField.LimitPrice = 4950;
			orderField.VolumeTotalOriginal = 1;
			orderField.TimeCondition = THOST_FTDC_TC_GFD;///当日有效
			orderField.VolumeCondition = THOST_FTDC_VC_AV;///任意数量
			orderField.MinVolume = 1;
			orderField.ContingentCondition = THOST_FTDC_CC_Immediately;
			orderField.StopPrice = 0;
			orderField.ForceCloseReason = THOST_FTDC_FCC_NotForceClose;
			orderField.IsAutoSuspend = 0;

			int rf = g_pTdApi->ReqParkedOrderInsert(&orderField, 0);
			if (!rf)
				std::cout << "<<<<<<发送预埋单请求成功" << std::endl;
			else
				std::cerr << "----->发送预埋带请求失败" << std::endl;
		}

		// 查询报单
		if (g_CtpTdApiWrapperParams.isQryOrder) 
		{
			CThostFtdcQryOrderField qryOrderField = { '\0' };
			strcpy_s(qryOrderField.BrokerID, gBrokerID);
			strcpy_s(qryOrderField.InvestorID, gInvesterID);
			strcpy_s(qryOrderField.InstrumentID, "ag2206");
			strcpy_s(qryOrderField.ExchangeID, "SHFE");

			int rf = g_pTdApi->ReqQryOrder(&qryOrderField, 0);
			if (!rf)
				std::cout << "<<<<<<查询报单请求发送成功" << std::endl;
			else
				std::cerr << "----->查询报单请求发送失败" << std::endl;
		}

		// 查询最大报单量
		if (g_CtpTdApiWrapperParams.isQueryMaxOrderVolume) 
		{
			CThostFtdcQueryMaxOrderVolumeField maxOrderVolumField = { '\0' };
			strcpy_s(maxOrderVolumField.BrokerID, gBrokerID);
			strcpy_s(maxOrderVolumField.InvestorID, gInvesterID);
			strcpy_s(maxOrderVolumField.InstrumentID, "ag2206");
			strcpy_s(maxOrderVolumField.ExchangeID, "SHFE");
			maxOrderVolumField.Direction = THOST_FTDC_D_Buy;
			maxOrderVolumField.OffsetFlag = THOST_FTDC_OF_Open;
			maxOrderVolumField.HedgeFlag = THOST_FTDC_HF_Speculation;
			
			int rf = g_pTdApi->ReqQueryMaxOrderVolume(&maxOrderVolumField, 0);
			if (!rf)
				std::cout << "<<<<<<发送查询最大报单量请求成功" << std::endl;
			else
				std::cerr << "------>发送查询最大报单量请求失败" << std::endl;
		}

		// 请求投资者结算结果确认
		if (g_CtpTdApiWrapperParams.isSettlementInfoConfirm) 
		{
			CThostFtdcSettlementInfoConfirmField settlementInfoConfirmField = { '\0' };
			strcpy_s(settlementInfoConfirmField.BrokerID, gBrokerID);
			strcpy_s(settlementInfoConfirmField.InvestorID, gInvesterID);

			int rf = g_pTdApi->ReqSettlementInfoConfirm(&settlementInfoConfirmField, 0);
			if (!rf)
				std::cout << "投资者结算结果确认请求发送成功" << std::endl;
			else
				std::cerr << "投资者结算结果确认请求发送失败" << std::endl;
		}

		// 询价请求
		if (g_CtpTdApiWrapperParams.isForQuoteInsert) 
		{
			CThostFtdcInputForQuoteField quoteField = { '\0' };
			strcpy_s(quoteField.BrokerID, gBrokerID);
			strcpy_s(quoteField.InvestorID, gInvesterID);
			strcpy_s(quoteField.InstrumentID, "ag2206");
			strcpy_s(quoteField.UserID, gInvesterID);
			strcpy_s(quoteField.ExchangeID, "SHFE");

			int rf = g_pTdApi->ReqForQuoteInsert(&quoteField, 0);			
			if (!rf)
				std::cout << "询价请求发送成功" << std::endl;
			else
				std::cerr << "询价请求发送失败" << std::endl;
		}

		// 查询组合
		if (g_CtpTdApiWrapperParams.isQryCombAction) 
		{
			CThostFtdcQryCombActionField qryCombActionField = { '\0' };
			strcpy(qryCombActionField.BrokerID, gBrokerID);
			strcpy(qryCombActionField.InvestorID, gInvesterID);
			strcpy(qryCombActionField.InstrumentID, "ag2206");//不填写则返回全部
			strcpy(qryCombActionField.ExchangeID, "SHFE");

			int rf = g_pTdApi->ReqQryCombAction(&qryCombActionField, 0);
			if (!rf)
				std::cout << "查询组合请求发送成功" << std::endl;
			else
				std::cerr << "查询组合请求发送失败" << std::endl;
		}

		// 查询组合合约的安全系数
		if (g_CtpTdApiWrapperParams.isQryCombInstrumentGuard) 
		{
			CThostFtdcQryCombInstrumentGuardField combInstrumentGuardField = { '\0' };
			strcpy_s(combInstrumentGuardField.BrokerID, gBrokerID);
			strcpy_s(combInstrumentGuardField.ExchangeID, "SHFE");
			strcpy_s(combInstrumentGuardField.InstrumentID, "ag2206");

			int rf = g_pTdApi->ReqQryCombInstrumentGuard(&combInstrumentGuardField, 0);
			if (!rf)
				std::cout << "查询组合合约的安全系数请求发送成功" << std::endl;
			else
				std::cerr << "查询组合合约的安全系数请求发送失败" << std::endl;
		}

		// 查询资金转账流水
		if (g_CtpTdApiWrapperParams.isQryTransferSerial) 
		{
			CThostFtdcQryTransferSerialField serialField = { '\0' };
			strcpy_s(serialField.BrokerID, gBrokerID);
			strcpy_s(serialField.AccountID, gInvesterID);

			int rf = g_pTdApi->ReqQryTransferSerial(&serialField, 0);
			if (!rf)
				std::cout << "查询资金转账流水请求发送成功" << std::endl;
			else
				std::cerr << "查询资金转账流水请求发送失败" << std::endl;
		}

		// 查询银期签约关系
		if (g_CtpTdApiWrapperParams.isQryAccountregister) 
		{
			CThostFtdcQryAccountregisterField accountregisterField = { '\0' };
			strcpy_s(accountregisterField.BrokerID, gBrokerID);
			strcpy_s(accountregisterField.AccountID, gInvesterID);

			int rf = g_pTdApi->ReqQryAccountregister(&accountregisterField, 0);
			if (!rf)
				std::cout << "查询银期签约关系请求发送成功" << std::endl;
			else
				std::cerr << "查询银期签约关系请求发送失败" << std::endl;
		}

		// 查询签约银行
		if (g_CtpTdApiWrapperParams.isQryContractBank) 
		{
			CThostFtdcQryContractBankField contractBankField = { '\0' };
			strcpy_s(contractBankField.BrokerID, gBrokerID);
			
			int rf = g_pTdApi->ReqQryContractBank(&contractBankField, 0);
			if (!rf)
				std::cout << "查询签约银行请求发送成功" << std::endl;
			else
				std::cerr << "查询签约银行请求发送失败" << std::endl;
		}

		// 查询预埋单
		if (g_CtpTdApiWrapperParams.isQryParkedOrder) 
		{
			CThostFtdcQryParkedOrderField parkedOrderField = { '\0' };
			strcpy_s(parkedOrderField.BrokerID, gBrokerID);
			strcpy_s(parkedOrderField.InvestorID, gInvesterID);
			strcpy_s(parkedOrderField.ExchangeID, "SHFE");
			strcpy_s(parkedOrderField.InstrumentID, "ag2206");

			int rf = g_pTdApi->ReqQryParkedOrder(&parkedOrderField, 0);
			if (!rf)
				std::cout << "查询预埋单请求发送成功" << std::endl;
			else
				std::cerr << "查询预埋单请求发送失败" << std::endl;
		}

		// 查询预埋撤单
		if (g_CtpTdApiWrapperParams.isQryParkedOrderAction) 
		{
			CThostFtdcQryParkedOrderActionField actionField = { '\0' };
			strcpy_s(actionField.BrokerID, gBrokerID);
			strcpy_s(actionField.InvestorID, gInvesterID);
			strcpy_s(actionField.ExchangeID, "SHFE");
			strcpy_s(actionField.InstrumentID, "ag2206");

			int rf = g_pTdApi->ReqQryParkedOrderAction(&actionField, 0);
			if (!rf)
				std::cout << "预埋撤单请求发送成功" << std::endl;
			else
				std::cerr << "预埋撤单请求发送失败" << std::endl;
		}

		// 查询交易通知
		if (g_CtpTdApiWrapperParams.isQryTradingNotice) 
		{
			CThostFtdcQryTradingNoticeField noticeField = { '\0' };
			strcpy_s(noticeField.BrokerID, gBrokerID);
			strcpy_s(noticeField.InvestorID, gInvesterID);

			int rf = g_pTdApi->ReqQryTradingNotice(&noticeField, 0);
			if (!rf)
				std::cout << "交易通知请求发送成功" << std::endl;
			else
				std::cerr << "交易通知请求发送失败" << std::endl;
		}

		// 查询经济公司交易参数
		if (g_CtpTdApiWrapperParams.isQryBrokerTradingParams) 
		{
			CThostFtdcQryBrokerTradingParamsField paramsField = { '\0' };
			strcpy_s(paramsField.BrokerID, gBrokerID);
			strcpy_s(paramsField.InvestorID, gInvesterID);

			int rf = g_pTdApi->ReqQryBrokerTradingParams(&paramsField, 0);
			if (!rf)
				std::cout << "查询经济公司交易参数请求发送成功" << std::endl;
			else
				std::cerr << "查询经济公司交易参数请求发送失败" << std::endl;
		}

		// 查询经济公司的交易算法
		if (g_CtpTdApiWrapperParams.isQryBrokerTradingAlgos) 
		{
			CThostFtdcQryBrokerTradingAlgosField algosField = { '\0' };
			strcpy_s(algosField.BrokerID, gBrokerID);
			strcpy_s(algosField.ExchangeID, "SHFE");
			strcpy_s(algosField.InstrumentID, "ag2206");

			int rf = g_pTdApi->ReqQryBrokerTradingAlgos(&algosField, 0);
			if (!rf)
				std::cout << "查询经济公司的交易算法请求发送成功" << std::endl;
			else
				std::cerr << "查询经济公司的交易算法请求发送失败" << std::endl;
		}

		// 查询期货银行账户金额
		if (g_CtpTdApiWrapperParams.isQueryBankBalanceByFuture) 
		{
			CThostFtdcReqQueryAccountField accountField = { '\0' };
			strcpy_s(accountField.BrokerID, gBrokerID);
			strcpy_s(accountField.AccountID, gInvesterID);
			strcpy_s(accountField.Password, gInvesterPassword);

			int rf = g_pTdApi->ReqQueryBankAccountMoneyByFuture(&accountField, 0);
			if (!rf)
				std::cout << "查询期货银行账户金额请求发送成功" << std::endl;
			else
				std::cerr << "查询期货银行账户金额请求发送失败" << std::endl;
		}

		// 查询监控中心交易令牌
		if (g_CtpTdApiWrapperParams.isQueryCFMMCTradingAccountToken) 
		{
			CThostFtdcQueryCFMMCTradingAccountTokenField tokenField = { '\0' };
			strcpy_s(tokenField.BrokerID, gBrokerID);
			strcpy_s(tokenField.InvestorID, gInvesterID);

			int rf = g_pTdApi->ReqQueryCFMMCTradingAccountToken(&tokenField, 0);
			if (!rf)
				std::cout << "查询期货银行账户金额请求发送成功" << std::endl;
			else
				std::cerr << "查询期货银行账户金额请求发送失败" << std::endl;
		}

		// 期货请求银行转期货请求
		if (g_CtpTdApiWrapperParams.isReqFromBankToFutureByFuture) 
		{
			CThostFtdcReqTransferField transferField = { '\0' };
			strcpy_s(transferField.BrokerID, gBrokerID);
			strcpy_s(transferField.AccountID, gInvesterID);
			strcpy_s(transferField.Password, gInvesterPassword);

			int rf = g_pTdApi->ReqFromBankToFutureByFuture(&transferField, 0);
			if (!rf)
				std::cout << "期货请求银行转期货请求发送成功" << std::endl;
			else
				std::cerr << "期货请求银行转期货请求发送失败" << std::endl;
		}

		// 期货请求期货转银行请求
		if (g_CtpTdApiWrapperParams.isReqFromFutureToBankByFuture)
		{
			CThostFtdcReqTransferField transferField = { '\0' };
			strcpy_s(transferField.BrokerID, gBrokerID);
			strcpy_s(transferField.AccountID, gInvesterID);
			strcpy_s(transferField.Password, gInvesterPassword);

			int rf = g_pTdApi->ReqFromFutureToBankByFuture(&transferField, 0);
			if (!rf)
				std::cout << "期货请求期货转银行请求发送成功" << std::endl;
			else
				std::cerr << "期货请求期货转银行请求发送失败" << std::endl;
		}

		// 查询投资单元
		if (g_CtpTdApiWrapperParams.isReqQryInvestUnit) {
			CThostFtdcQryInvestUnitField unitField = { '\0' };
			strcpy_s(unitField.BrokerID, gBrokerID);
			strcpy_s(unitField.InvestorID, gInvesterID);

			int rf = g_pTdApi->ReqQryInvestUnit(&unitField, 0);
			if (!rf)
				std::cout << "查询投资单元请求发送成功" << std::endl;
			else
				std::cerr << "查询投资单元请求发送失败" << std::endl;
		}

		// 请求查询二级代理商信息
		if (g_CtpTdApiWrapperParams.isReqQrySecAgentTradeInfo) 
		{
			CThostFtdcQrySecAgentTradeInfoField agentTradeInfoField = { '\0' };
			strcpy_s(agentTradeInfoField.BrokerID, gBrokerID);
			strcpy_s(agentTradeInfoField.BrokerSecAgentID, "00000000");

			int rf = g_pTdApi->ReqQrySecAgentTradeInfo(&agentTradeInfoField, 0);
			if (!rf)
				std::cout << "请求查询二级代理商信息发送成功" << std::endl;
			else
				std::cerr << "请求查询二级代理商信息发送失败" << std::endl;
		}

		// 请求查询二级代理商资金验证模式
		if (g_CtpTdApiWrapperParams.isReqQrySecAgentCheckMode) 
		{
			CThostFtdcQrySecAgentCheckModeField agentCheckModeField = { '\0' };
			strcpy_s(agentCheckModeField.BrokerID, gBrokerID);
			strcpy_s(agentCheckModeField.InvestorID, gInvesterID);

			int rf = g_pTdApi->ReqQrySecAgentCheckMode(&agentCheckModeField, 0);
			if (!rf)
				std::cout << "请求查询二级代理商资金验证模式信息发送成功" << std::endl;
			else
				std::cerr << "请求查询二级代理商资金验证模式信息发送失败" << std::endl;
		}

		// 请求查询资金账户
		if (g_CtpTdApiWrapperParams.isReqQrySecAgentTradingAccount) {
			CThostFtdcQryTradingAccountField accountField = { '\0' };
			strcpy_s(accountField.BrokerID, gBrokerID);
			strcpy_s(accountField.InvestorID, gInvesterID);

			int rf = g_pTdApi->ReqQrySecAgentTradingAccount(&accountField, 0);
			if (!rf)
				std::cout << "请求查询资金账户信息发送成功" << std::endl;
			else
				std::cerr << "请求查询资金账户信息发送失败" << std::endl;
		}

		// 请求查询报单手续费
		if (g_CtpTdApiWrapperParams.isReqQryInstrumentOrderCommRate) 
		{
			CThostFtdcQryInstrumentOrderCommRateField rateField = { '\0' };
			strcpy_s(rateField.BrokerID, gBrokerID);
			strcpy_s(rateField.InvestorID, gInvesterID);			
			strcpy_s(rateField.InstrumentID, "ag2206");

			int rf = g_pTdApi->ReqQryInstrumentOrderCommRate(&rateField, 0);
			if (!rf)
				std::cout << "请求查询报单手续费信息发送成功" << std::endl;
			else
				std::cerr << "请求查询报单手续费信息发送失败" << std::endl;
		}

		// 请求查询做市商合约手续费率
		if (g_CtpTdApiWrapperParams.isReqQryMMInstrumentCommissionRate) 
		{
			CThostFtdcQryMMInstrumentCommissionRateField rateField = { '\0' };
			strcpy_s(rateField.BrokerID, gBrokerID);
			strcpy_s(rateField.InvestorID, gInvesterID);
			strcpy_s(rateField.InstrumentID, "ag2206");

			int rf = g_pTdApi->ReqQryMMInstrumentCommissionRate(&rateField, 0);
			if (!rf)
				std::cout << "请求查询做市商合约手续费率信息发送成功" << std::endl;
			else
				std::cerr << "请求查询做市商合约手续费率信息发送失败" << std::endl;
		}

		// 请求查询产品组
		if (g_CtpTdApiWrapperParams.isReqQryProductGroup) 
		{
			CThostFtdcQryProductGroupField productGroupField = { '\0' };
			strcpy_s(productGroupField.ProductID, "ag2206");
			strcpy_s(productGroupField.ExchangeID, "SHFE");

			int rf = g_pTdApi->ReqQryProductGroup(&productGroupField, 0);
			if (!rf)
				std::cout << "请求查询产品组信息发送成功" << std::endl;
			else
				std::cerr << "请求查询产品组信息发送失败" << std::endl;
		}

		// 请求产品报价汇率
		if (g_CtpTdApiWrapperParams.isReqQryProductExchRate) 
		{
			CThostFtdcQryProductExchRateField rateField = { '\0' };
			strcpy_s(rateField.ExchangeID, "SHFE");
			strcpy_s(rateField.ProductID, "ag2206");

			int rf = g_pTdApi->ReqQryProductExchRate(&rateField, 0);
			if (!rf)
				std::cout << "请求产品报价汇率信息发送成功" << std::endl;
			else
				std::cerr << "请求产品报价汇率信息发送失败" << std::endl;
		}

		// 请求查询汇率
		if (g_CtpTdApiWrapperParams.isReqQryExchangeRate) 
		{
			CThostFtdcQryExchangeRateField rateField = { '\0' };
			strcpy_s(rateField.BrokerID, gBrokerID);
			strcpy_s(rateField.FromCurrencyID, "CNY");
			strcpy_s(rateField.ToCurrencyID, "USD");

			int rf = g_pTdApi->ReqQryExchangeRate(&rateField, 0);
			if (!rf)
				std::cout << "请求产品报价汇率信息发送成功" << std::endl;
			else
				std::cerr << "请求产品报价汇率信息发送失败" << std::endl;
		}

		// 请求查询交易所调整的保障金
		if (g_CtpTdApiWrapperParams.isReqQryExchangeMarginRateAdjust) 
		{
			CThostFtdcQryExchangeMarginRateAdjustField adjustField = { '\0' };
			strcpy_s(adjustField.BrokerID, gBrokerID);			
			strcpy_s(adjustField.InstrumentID, "ag2206");
			adjustField.HedgeFlag = THOST_FTDC_HF_Speculation;

			int rf = g_pTdApi->ReqQryExchangeMarginRateAdjust(&adjustField, 0);
			if (!rf)
				std::cout << "请求产品报价汇率信息发送成功" << std::endl;
			else
				std::cerr << "请求产品报价汇率信息发送失败" << std::endl;
		}

		// 请求查询交易所保证金率
		if (g_CtpTdApiWrapperParams.isReqQryExchangeMarginRate) 
		{
			CThostFtdcQryExchangeMarginRateField rateField = { '\0' };
			strcpy_s(rateField.BrokerID, gBrokerID);
			strcpy_s(rateField.InstrumentID, "ag2206");
			strcpy_s(rateField.ExchangeID, "SHFE");			
			rateField.HedgeFlag = THOST_FTDC_HF_Speculation;

			int rf = g_pTdApi->ReqQryExchangeMarginRate(&rateField, 0);
			if (!rf)
				std::cout << "请求查询交易所保证金率信息发送成功" << std::endl;
			else
				std::cerr << "请求查询交易所保证金率信息发送失败" << std::endl;
		}

		// 请求投资者品种/跨品种保证金
		if (g_CtpTdApiWrapperParams.isReqQryInvestorProductGroupMargin) 
		{
			CThostFtdcQryInvestorProductGroupMarginField marginField = { '\0' };
			strcpy_s(marginField.BrokerID, gBrokerID);
			strcpy_s(marginField.InvestorID, gInvesterID);
			strcpy_s(marginField.ProductGroupID, "ag2206");
			strcpy_s(marginField.ExchangeID, "SHFE");
			marginField.HedgeFlag = THOST_FTDC_HF_Speculation;

			int rf = g_pTdApi->ReqQryInvestorProductGroupMargin(&marginField, 0);
			if (!rf)
				std::cout << "请求投资者品种/跨品种保证金信息发送成功" << std::endl;
			else
				std::cerr << "请求投资者品种/跨品种保证金信息发送失败" << std::endl;
		}
		// 请求查询持仓信息
		if (g_CtpTdApiWrapperParams.isReqQryEWarrantOffset) 
		{
			CThostFtdcQryEWarrantOffsetField offsetField = { '\0' };
			strcpy_s(offsetField.BrokerID, gBrokerID);
			strcpy_s(offsetField.ExchangeID, "SHFE");
			strcpy_s(offsetField.InstrumentID, "ag2206");
			strcpy_s(offsetField.InvestorID, gInvesterID);

			int rf = g_pTdApi->ReqQryEWarrantOffset(&offsetField, 0);
			if (!rf)
				std::cout << "请求查询持仓信息发送成功" << std::endl;
			else
				std::cerr << "请求查询持仓信息发送失败" << std::endl;
		}

		// 请求查询保证金监管系统经纪公司资金账户密钥
		if (g_CtpTdApiWrapperParams.isReqQryCFMMCTradingAccountKey) 
		{
			CThostFtdcQryCFMMCTradingAccountKeyField keyField = { '\0' };
			strcpy_s(keyField.BrokerID, gBrokerID);			
			strcpy_s(keyField.InvestorID, gInvesterID);

			int rf = g_pTdApi->ReqQryCFMMCTradingAccountKey(&keyField, 0);
			if (!rf)
				std::cout << "请求查询持仓信息发送成功" << std::endl;
			else
				std::cerr << "请求查询持仓信息发送失败" << std::endl;
		}

		// 请求查询投资者组合持仓明细
		if (g_CtpTdApiWrapperParams.isReqQryInvestorPositionCombineDetail) 
		{
			CThostFtdcQryInvestorPositionCombineDetailField detailField = { '\0' };
			strcpy_s(detailField.BrokerID, gBrokerID);
			strcpy_s(detailField.InvestorID, gInvesterID);
			strcpy_s(detailField.CombInstrumentID, "ag2206");
			strcpy_s(detailField.ExchangeID, "SHFE");

			int rf = g_pTdApi->ReqQryInvestorPositionCombineDetail(&detailField, 0);
			if (!rf)
				std::cout << "请求查询投资者组合持仓明细信息发送成功" << std::endl;
			else
				std::cerr << "请求查询投资者组合持仓明细信息发送失败" << std::endl;
		}

		// 请求查询投资者持仓明细
		if (g_CtpTdApiWrapperParams.isReqQryInvestorPositionDetail) 
		{
			CThostFtdcQryInvestorPositionDetailField detailField = { '\0' };
			strcpy_s(detailField.BrokerID, gBrokerID);
			strcpy_s(detailField.InvestorID, gInvesterID);
			strcpy_s(detailField.InstrumentID, "ag2206");
			strcpy_s(detailField.ExchangeID, "SHFE");

			int rf = g_pTdApi->ReqQryInvestorPositionDetail(&detailField, 0);
			if (!rf)
				std::cout << "请求查询投资者组合持仓明细信息发送成功" << std::endl;
			else
				std::cerr << "请求查询投资者组合持仓明细信息发送失败" << std::endl;
		}

		// 请求查询转账银行
		if (g_CtpTdApiWrapperParams.isReqQryTransferBank) 
		{
			CThostFtdcQryTransferBankField bankField = { '\0' };
			strcpy_s(bankField.BankID, "999");
			//strcpy_s(bankField.BankBrchID, "");

			int rf = g_pTdApi->ReqQryTransferBank(&bankField, 0);
			if (!rf)
				std::cout << "请求查询转账银行信息发送成功" << std::endl;
			else
				std::cerr << "请求查询转账银行信息发送失败" << std::endl;
		}

		// 请求查询投资者结算信息
		if (g_CtpTdApiWrapperParams.isReqQrySettlementInfo) 
		{
			CThostFtdcQrySettlementInfoField settlementInfoField = { '\0' };
			strcpy_s(settlementInfoField.BrokerID, gBrokerID);
			strcpy_s(settlementInfoField.InvestorID, gInvesterID);
			strcpy_s(settlementInfoField.TradingDay, "20220216");

			int rf = g_pTdApi->ReqQrySettlementInfo(&settlementInfoField, 0);
			if (!rf)
				std::cout << "请求查询投资者结算信息发送成功" << std::endl;
			else
				std::cerr << "请求查询投资者结算信息发送失败" << std::endl;
		}

		// 请求查询行情
		if (g_CtpTdApiWrapperParams.isReqQryDepthMarketData) 
		{
			CThostFtdcQryDepthMarketDataField marketDataField = { '\0' };
			strcpy_s(marketDataField.InstrumentID, "ag2206");
			strcpy_s(marketDataField.ExchangeID, "SHFE");

			int rf = g_pTdApi->ReqQryDepthMarketData(&marketDataField, 0);
			if (!rf)
				std::cout << "请求查询行情信息发送成功" << std::endl;
			else
				std::cerr << "请求查询行情信息发送失败" << std::endl;
		}

		// 请求查询合约
		if (g_CtpTdApiWrapperParams.isReqQryInstrument) 
		{
			CThostFtdcQryInstrumentField instrumentField = { '\0' };
			strcpy_s(instrumentField.InstrumentID, "ag2206");
			strcpy_s(instrumentField.ExchangeID, "SHFE");

			int rf = g_pTdApi->ReqQryInstrument(&instrumentField, 0);
			if (!rf)
				std::cout << "请求查询合约信息发送成功" << std::endl;
			else
				std::cerr << "请求查询合约信息发送失败" << std::endl;
		}

		// 请求查询交易所
		if (g_CtpTdApiWrapperParams.isReqQryExchange) 
		{
			CThostFtdcQryExchangeField exchangeField = { '\0' };			
			strcpy_s(exchangeField.ExchangeID, "SHFE");

			int rf = g_pTdApi->ReqQryExchange(&exchangeField, 0);
			if (!rf)
				std::cout << "请求查询交易所信息发送成功" << std::endl;
			else
				std::cerr << "请求查询交易所信息发送失败" << std::endl;
		}

		// 请求合约的手续费
		if (g_CtpTdApiWrapperParams.isReqQryInstrumentCommissionRate) 
		{
			CThostFtdcQryInstrumentCommissionRateField commissionRateField = { '\0' };
			strcpy_s(commissionRateField.BrokerID, gBrokerID);
			strcpy_s(commissionRateField.InvestorID, gInvesterID);
			strcpy_s(commissionRateField.InstrumentID, "ag2206");
			strcpy_s(commissionRateField.ExchangeID, "SHFE");

			int rf = g_pTdApi->ReqQryInstrumentCommissionRate(&commissionRateField, 0);
			if (!rf)
				std::cout << "请求查询合约手续费信息发送成功" << std::endl;
			else
				std::cerr << "请求查询合约手续费信息发送失败" << std::endl;
		}

		// 请求查询合约的保证金率
		if (g_CtpTdApiWrapperParams.isReqQryInstrumentMarginRate) 
		{
			CThostFtdcQryInstrumentMarginRateField marginRateField = { '\0' };
			strcpy_s(marginRateField.BrokerID, gBrokerID);
			strcpy_s(marginRateField.InvestorID, gInvesterID);
			strcpy_s(marginRateField.InstrumentID, "ag2206");
			strcpy_s(marginRateField.ExchangeID, "SHFE");
			marginRateField.HedgeFlag = THOST_FTDC_HF_Speculation;

			int rf = g_pTdApi->ReqQryInstrumentMarginRate(&marginRateField, 0);
			if (!rf)
				std::cout << "请求查询合约的保证金率信息发送成功" << std::endl;
			else
				std::cerr << "请求查询合约的保证金率信息发送失败" << std::endl;
		}

		// 请求查询交易者编号
		if (g_CtpTdApiWrapperParams.isReqQryTradingCode) 
		{
			CThostFtdcQryTradingCodeField tradingCodeField = { '\0' };
			strcpy_s(tradingCodeField.BrokerID, gBrokerID);
			strcpy_s(tradingCodeField.InvestorID, gInvesterID);
			strcpy_s(tradingCodeField.ExchangeID, "SHFE");
			strcpy_s(tradingCodeField.ClientID, "");
			tradingCodeField.ClientIDType = THOST_FTDC_CIDT_Speculation;			

			int rf = g_pTdApi->ReqQryTradingCode(&tradingCodeField, 0);
			if (!rf)
				std::cout << "请求查询交易者编号信息发送成功" << std::endl;
			else
				std::cerr << "请求查询交易者编号信息发送失败" << std::endl;
		}

		// 请求查询投资者
		if (g_CtpTdApiWrapperParams.isReqQryInvestor) 
		{
			CThostFtdcQryInvestorField investorField = { '\0' };
			strcpy_s(investorField.BrokerID, gBrokerID);
			strcpy_s(investorField.InvestorID, gInvesterID);			

			int rf = g_pTdApi->ReqQryInvestor(&investorField, 0);
			if (!rf)
				std::cout << "请求查询交易者编号信息发送成功" << std::endl;
			else
				std::cerr << "请求查询交易者编号信息发送失败" << std::endl;
		}

		// 请求查询资金账户
		if (g_CtpTdApiWrapperParams.isReqQryTradingAccount) 
		{
			CThostFtdcQryTradingAccountField accountField = { '\0' };
			strcpy_s(accountField.BrokerID, gBrokerID);
			strcpy_s(accountField.InvestorID, gInvesterID);
			strcpy_s(accountField.CurrencyID, "CNY");

			int rf = g_pTdApi->ReqQryTradingAccount(&accountField, 0);
			if (!rf)
				std::cout << "请求查询资金账户信息发送成功" << std::endl;
			else
				std::cerr << "请求查询资金账户信息发送失败" << std::endl;
		}

		// 请求查询投资者持仓
		if (g_CtpTdApiWrapperParams.isReqQryInvestorPosition) 
		{
			CThostFtdcQryInvestorPositionField positionField = { '\0' };
			strcpy_s(positionField.BrokerID, gBrokerID);
			strcpy_s(positionField.InvestorID, gInvesterID);			
			strcpy_s(positionField.InstrumentID, "ag2206");
			strcpy_s(positionField.ExchangeID, "SHFE");

			int rf = g_pTdApi->ReqQryInvestorPosition(&positionField, 0);
			if (!rf)
				std::cout << "请求查询投资者持仓信息发送成功" << std::endl;
			else
				std::cerr << "请求查询投资者持仓信息发送失败" << std::endl;
		}

		// 请求查询交易
		if (g_CtpTdApiWrapperParams.isReqQryTrade) 
		{
			CThostFtdcQryTradeField tradingField = { '\0' };
			strcpy_s(tradingField.BrokerID, gBrokerID);
			strcpy_s(tradingField.InvestorID, gInvesterID);
			strcpy_s(tradingField.InstrumentID, "ag2206");
			strcpy_s(tradingField.ExchangeID, "SHFE");

			int rf = g_pTdApi->ReqQryTrade(&tradingField, 0);
			if (!rf)
				std::cout << "请求查询交易信息发送成功" << std::endl;
			else
				std::cerr << "请求查询交易信息发送失败" << std::endl;
		}

		//// 开始订阅行情
		//int rt = g_pTdApi->SubscribeMarketData(g_pInstrumentID, instrumentNum);
		//if (!rt)
		//	std::cout << ">>>>>>发送订阅行情请求成功" << std::endl;
		//else
		//	std::cerr << "--->>>发送订阅行情请求失败" << std::endl;
	}
	else
		std::cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// 登出应答
void WINAPI OnRspUserLogout(
	CThostFtdcUserLogoutField *pUserLogout,
	CThostFtdcRspInfoField *pRspInfo, 
	int nRequestID, 
	bool bIsLast)
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult)
	{
		g_logoutOK = true;
		g_cond_va.notify_one();

		std::cout << "=====账户登出成功=====" << std::endl;
		std::cout << "经纪商： " << pUserLogout->BrokerID << std::endl;
		std::cout << "帐户名： " << pUserLogout->UserID << std::endl;
	}
	else
		std::cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// 更新密码应答
void WINAPI OnRspUserPasswordUpdate(
	CThostFtdcUserPasswordUpdateField* pUserPasswordUpdate, 
	CThostFtdcRspInfoField* pRspInfo, 
	int nRequestID, 
	bool bIsLast) 
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult) 
	{
		g_updateLoginPwdOK = true;
		g_cond_va.notify_one();

		std::cout << "=====用户更新密码成功=====" << std::endl;
		std::cout << "经纪公司代码： " << pUserPasswordUpdate->BrokerID << std::endl;
		std::cout << "用户代码： " << pUserPasswordUpdate->UserID << std::endl;
		std::cout << "原始密码： " << pUserPasswordUpdate->OldPassword << std::endl;
		std::cout << "更新后的密码： " << pUserPasswordUpdate->NewPassword << std::endl;
	}
	else
		std::cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// 交易账户更新密码应答
void WINAPI OnRspTradingAccountPasswordUpdate(
	CThostFtdcTradingAccountPasswordUpdateField* pTradingAccountPasswordUpdate, 
	CThostFtdcRspInfoField* pRspInfo, 
	int nRequestID, 
	bool bIsLast)
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult)
	{
		g_updateTrdAccountPwdOK = true;
		g_cond_va.notify_one();

		std::cout << "=====用户更新密码成功=====" << std::endl;
		std::cout << "经纪公司代码： " << pTradingAccountPasswordUpdate->BrokerID << std::endl;
		std::cout << "投资者帐号： " << pTradingAccountPasswordUpdate->AccountID << std::endl;
		std::cout << "原始密码： " << pTradingAccountPasswordUpdate->OldPassword << std::endl;
		std::cout << "更新后的密码： " << pTradingAccountPasswordUpdate->NewPassword << std::endl;
		std::cout << "币种代码： " << pTradingAccountPasswordUpdate->CurrencyID << std::endl;

	}
	else
		std::cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// 报单请求失败该函数被回调
void WINAPI OnRspInsertOrder(
	CThostFtdcInputOrderField* pInputOrder, 
	CThostFtdcRspInfoField* pRspInfo, 
	int nRequestID, 
	bool bIsLast) 
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult) 
	{
		std::cout << "=====报单请求失败=====" << std::endl;
		std::cout << "经纪公司代码： " << pInputOrder->BrokerID << std::endl;
		std::cout << "投资者代码： " << pInputOrder->InvestorID << std::endl;
		std::cout << "合约代码： " << pInputOrder->InstrumentID << std::endl;
		std::cout << "报单引用： " << pInputOrder->OrderRef << std::endl;
		std::cout << "用户代码： " << pInputOrder->UserID << std::endl;
		std::cout << "报单价格条件： " << pInputOrder->OrderPriceType << std::endl;
		std::cout << "买卖方向： " << pInputOrder->Direction << std::endl;
		std::cout << "组合开平标志： " << pInputOrder->CombOffsetFlag << std::endl;
		std::cout << "组合投机套保标志： " << pInputOrder->CombHedgeFlag << std::endl;
		std::cout << "价格： " << pInputOrder->LimitPrice << std::endl;
		std::cout << "数量： " << pInputOrder->VolumeTotalOriginal << std::endl;
		std::cout << "有效期类型： " << pInputOrder->TimeCondition << std::endl;
		std::cout << "GTD日期： " << pInputOrder->GTDDate << std::endl;
		std::cout << "成交量类型： " << pInputOrder->VolumeCondition << std::endl;
		std::cout << "最小成交量： " << pInputOrder->MinVolume << std::endl;
		std::cout << "触发条件： " << pInputOrder->ContingentCondition << std::endl;
		std::cout << "止损价格： " << pInputOrder->StopPrice << std::endl;
		std::cout << "清平原因： " << pInputOrder->ForceCloseReason << std::endl;
		std::cout << "自动挂起标志： " << pInputOrder->IsAutoSuspend << std::endl;
		std::cout << "业务单元： " << pInputOrder->BusinessUnit << std::endl;
		std::cout << "请求编号： " << pInputOrder->RequestID << std::endl;
		std::cout << "用户强平标志： " << pInputOrder->UserForceClose << std::endl;
		std::cout << "互换单标志： " << pInputOrder->IsSwapOrder << std::endl;
		std::cout << "交易所代码： " << pInputOrder->ExchangeID << std::endl;
		std::cout << "投资单元代码： " << pInputOrder->InvestUnitID << std::endl;
		std::cout << "资金账户： " << pInputOrder->AccountID << std::endl;
		std::cout << "币种代码： " << pInputOrder->CurrencyID << std::endl;
		std::cout << "交易编码： " << pInputOrder->ClientID << std::endl;
		std::cout << "IP地址： " << pInputOrder->IPAddress << std::endl;
		std::cout << "Mac地址： " << pInputOrder->MacAddress << std::endl;		
	}
	else
		std::cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// 报单被 ctp 拒绝会回调
void WINAPI OnErrRtnOrderInsert(
	CThostFtdcInputOrderField* pInputOrder, 
	CThostFtdcRspInfoField* pRspInfo) 
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult)
	{
		std::cout << "=====报单请求失败=====" << std::endl;
		std::cout << "经纪公司代码： " << pInputOrder->BrokerID << std::endl;
		std::cout << "投资者代码： " << pInputOrder->InvestorID << std::endl;
		std::cout << "合约代码： " << pInputOrder->InstrumentID << std::endl;
		std::cout << "报单引用： " << pInputOrder->OrderRef << std::endl;
		std::cout << "用户代码： " << pInputOrder->UserID << std::endl;
		std::cout << "报单价格条件： " << pInputOrder->OrderPriceType << std::endl;
		std::cout << "买卖方向： " << pInputOrder->Direction << std::endl;
		std::cout << "组合开平标志： " << pInputOrder->CombOffsetFlag << std::endl;
		std::cout << "组合投机套保标志： " << pInputOrder->CombHedgeFlag << std::endl;
		std::cout << "价格： " << pInputOrder->LimitPrice << std::endl;
		std::cout << "数量： " << pInputOrder->VolumeTotalOriginal << std::endl;
		std::cout << "有效期类型： " << pInputOrder->TimeCondition << std::endl;
		std::cout << "GTD日期： " << pInputOrder->GTDDate << std::endl;
		std::cout << "成交量类型： " << pInputOrder->VolumeCondition << std::endl;
		std::cout << "最小成交量： " << pInputOrder->MinVolume << std::endl;
		std::cout << "触发条件： " << pInputOrder->ContingentCondition << std::endl;
		std::cout << "止损价格： " << pInputOrder->StopPrice << std::endl;
		std::cout << "清平原因： " << pInputOrder->ForceCloseReason << std::endl;
		std::cout << "自动挂起标志： " << pInputOrder->IsAutoSuspend << std::endl;
		std::cout << "业务单元： " << pInputOrder->BusinessUnit << std::endl;
		std::cout << "请求编号： " << pInputOrder->RequestID << std::endl;
		std::cout << "用户强平标志： " << pInputOrder->UserForceClose << std::endl;
		std::cout << "互换单标志： " << pInputOrder->IsSwapOrder << std::endl;
		std::cout << "交易所代码： " << pInputOrder->ExchangeID << std::endl;
		std::cout << "投资单元代码： " << pInputOrder->InvestUnitID << std::endl;
		std::cout << "资金账户： " << pInputOrder->AccountID << std::endl;
		std::cout << "币种代码： " << pInputOrder->CurrencyID << std::endl;
		std::cout << "交易编码： " << pInputOrder->ClientID << std::endl;
		std::cout << "IP地址： " << pInputOrder->IPAddress << std::endl;
		std::cout << "Mac地址： " << pInputOrder->MacAddress << std::endl;
	}
	else
		std::cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
};

// 报单通知，通知机制： ctp 柜台验证通过就会通知一次(这次订单是没有上报成功的)
void WINAPI OnRtnOrder(
	CThostFtdcOrderField* pOrder)
{
	//  报单已经提交到交易所
	if (pOrder->OrderSysID != NULL && pOrder->OrderSysID[0] != '\0') {
		g_orderInsertOK = true;
		g_cond_va.notify_one();

		// 当前订单已经报到交易所开始撤单
		if (g_CtpTdApiWrapperParams.isOrderAction) {
			CThostFtdcInputOrderActionField orderActionField = { '\0' };
			strcpy_s(orderActionField.BrokerID, gBrokerID);
			strcpy_s(orderActionField.InvestorID, pOrder->InvestorID);
			strcpy_s(orderActionField.UserID, pOrder->UserID);
			strcpy_s(orderActionField.OrderSysID, pOrder->OrderSysID);
			strcpy_s(orderActionField.ExchangeID, pOrder->ExchangeID);
			strcpy_s(orderActionField.InstrumentID, pOrder->InstrumentID);
			orderActionField.ActionFlag = THOST_FTDC_AF_Delete;
			
			int rf = g_pTdApi->ReqOrderAction(&orderActionField, 0);
			if (!rf)
				std::cout << "<<<<<<发送撤单请求成功" << std::endl;
			else 
				std::cout << "------>发送撤单请求失败" << std::endl;

			g_CtpTdApiWrapperParams.isOrderAction = false;
		}
		else {
			g_orderActionOK = true;
			g_cond_va.notify_one();
		}

		// 查询报价
		if (g_CtpTdApiWrapperParams.isQryQuote) {
			CThostFtdcQryQuoteField qryQuoteField = { '\0' };
			strcpy_s(qryQuoteField.BrokerID, gBrokerID);
			strcpy_s(qryQuoteField.InvestorID, gInvesterID);
			strcpy_s(qryQuoteField.InstrumentID, pOrder->InstrumentID);
			strcpy_s(qryQuoteField.ExchangeID, pOrder->ExchangeID);
			strcpy_s(qryQuoteField.QuoteSysID, pOrder->OrderSysID);

			int rf = g_pTdApi->ReqQryQuote(&qryQuoteField, 0);
			if (!rf)
				std::cout << "<<<<<<发送查询报价请求成功" << std::endl;
			else
				std::cout << "------>发送查询报价请求失败" << std::endl;
		}
	}

	std::cout << "=====报单请求成功，OnRtnOrder回调=====" << std::endl;
	std::cout << "经纪公司代码： " << pOrder->BrokerID << std::endl;
	std::cout << "投资者代码： " << pOrder->InvestorID << std::endl;
	std::cout << "合约代码： " << pOrder->InstrumentID << std::endl;
	std::cout << "报单引用： " << pOrder->OrderRef << std::endl;
	std::cout << "用户代码： " << pOrder->UserID << std::endl;
	std::cout << "报单价格条件： " << pOrder->OrderPriceType << std::endl;
	std::cout << "买卖方向： " << pOrder->Direction << std::endl;
	std::cout << "组合开平标志： " << pOrder->CombOffsetFlag << std::endl;
	std::cout << "组合投机套保标志： " << pOrder->CombHedgeFlag << std::endl;
	std::cout << "价格： " << pOrder->LimitPrice << std::endl;
	std::cout << "数量： " << pOrder->VolumeTotalOriginal << std::endl;
	std::cout << "有效期类型： " << pOrder->TimeCondition << std::endl;
	std::cout << "GTD日期： " << pOrder->GTDDate << std::endl;
	std::cout << "成交量类型： " << pOrder->VolumeCondition << std::endl;
	std::cout << "最小成交量： " << pOrder->MinVolume << std::endl;
	std::cout << "触发条件： " << pOrder->ContingentCondition << std::endl;
	std::cout << "止损价格： " << pOrder->StopPrice << std::endl;
	std::cout << "清平原因： " << pOrder->ForceCloseReason << std::endl;
	std::cout << "自动挂起标志： " << pOrder->IsAutoSuspend << std::endl;
	std::cout << "业务单元： " << pOrder->BusinessUnit << std::endl;
	std::cout << "请求编号： " << pOrder->RequestID << std::endl;
	std::cout << "用户强平标志： " << pOrder->UserForceClose << std::endl;
	std::cout << "互换单标志： " << pOrder->IsSwapOrder << std::endl;
	std::cout << "交易所代码： " << pOrder->ExchangeID << std::endl;
	std::cout << "投资单元代码： " << pOrder->InvestUnitID << std::endl;
	std::cout << "资金账户： " << pOrder->AccountID << std::endl;
	std::cout << "币种代码： " << pOrder->CurrencyID << std::endl;
	std::cout << "交易编码： " << pOrder->ClientID << std::endl;

}

// 交易通知
void WINAPI OnRtnTrade(
	CThostFtdcTradeField* pTrade) 
{
	std::cout << "=====报单请求成功。OnRtnTrade回调=====" << std::endl;
	std::cout << "经纪公司代码： " << pTrade->BrokerID << std::endl;
	std::cout << "投资者代码： " << pTrade->InvestorID << std::endl;
	std::cout << "合约代码： " << pTrade->InstrumentID << std::endl;
	std::cout << "报单引用： " << pTrade->OrderRef << std::endl;
	std::cout << "用户代码： " << pTrade->UserID << std::endl;	
	std::cout << "买卖方向： " << pTrade->Direction << std::endl;
	std::cout << "报单编号：" << pTrade->OrderSysID << std::endl;
}

// 预埋单请求响应
void WINAPI OnRspParkedOrderInsert(CThostFtdcParkedOrderField* pParkedOrder, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) 
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (bResult) 
	{

		g_parkedOrderInsertOK = true;
		g_cond_va.notify_one();

		std::cout << "=====预埋单请求成功=====" << std::endl;
		std::cout << "经纪公司代码： " << pParkedOrder->BrokerID << std::endl;
		std::cout << "投资者代码： " << pParkedOrder->InvestorID << std::endl;
		std::cout << "合约代码： " << pParkedOrder->InstrumentID << std::endl;
		std::cout << "报单引用： " << pParkedOrder->OrderRef << std::endl;
		std::cout << "用户代码： " << pParkedOrder->UserID << std::endl;
		std::cout << "报单价格条件： " << pParkedOrder->OrderPriceType << std::endl;
		std::cout << "买卖方向： " << pParkedOrder->Direction << std::endl;
		std::cout << "组合开平标志： " << pParkedOrder->CombOffsetFlag << std::endl;
		std::cout << "组合投机套保标志： " << pParkedOrder->CombHedgeFlag << std::endl;
		std::cout << "价格： " << pParkedOrder->LimitPrice << std::endl;
		std::cout << "数量： " << pParkedOrder->VolumeTotalOriginal << std::endl;
		std::cout << "有效期类型： " << pParkedOrder->TimeCondition << std::endl;
		std::cout << "GTD日期： " << pParkedOrder->GTDDate << std::endl;
		std::cout << "成交量类型： " << pParkedOrder->VolumeCondition << std::endl;
		std::cout << "最小成交量： " << pParkedOrder->MinVolume << std::endl;
		std::cout << "触发条件： " << pParkedOrder->ContingentCondition << std::endl;
		std::cout << "止损价格： " << pParkedOrder->StopPrice << std::endl;
		std::cout << "清平原因： " << pParkedOrder->ForceCloseReason << std::endl;
		std::cout << "自动挂起标志： " << pParkedOrder->IsAutoSuspend << std::endl;
		std::cout << "业务单元： " << pParkedOrder->BusinessUnit << std::endl;
		std::cout << "请求编号： " << pParkedOrder->RequestID << std::endl;
		std::cout << "用户强平标志： " << pParkedOrder->UserForceClose << std::endl;
		std::cout << "互换单标志： " << pParkedOrder->IsSwapOrder << std::endl;
		std::cout << "交易所代码： " << pParkedOrder->ExchangeID << std::endl;
		std::cout << "投资单元代码： " << pParkedOrder->InvestUnitID << std::endl;
		std::cout << "资金账户： " << pParkedOrder->AccountID << std::endl;
		std::cout << "币种代码： " << pParkedOrder->CurrencyID << std::endl;
		std::cout << "交易编码： " << pParkedOrder->ClientID << std::endl;

		// 删除埋单成功的单子
		if (g_CtpTdApiWrapperParams.isParkedOrderAction)
		{
			CThostFtdcParkedOrderActionField orderActionField = { '\0' };
			strcpy_s(orderActionField.BrokerID, pParkedOrder->BrokerID);
			strcpy_s(orderActionField.InvestorID, pParkedOrder->InvestorID);
			strcpy_s(orderActionField.ExchangeID, pParkedOrder->ExchangeID);
			strcpy_s(orderActionField.OrderSysID, pParkedOrder ->ParkedOrderID);
			strcpy_s(orderActionField.UserID, pParkedOrder ->UserID);
			strcpy_s(orderActionField.InstrumentID, pParkedOrder->InstrumentID);
			orderActionField.ActionFlag = THOST_FTDC_AF_Delete;

			int rf = g_pTdApi->ReqParkedOrderAction(&orderActionField, 0);
			if (!rf)
				std::cout << "发送删除预埋单请求成功" << std::endl;
			else
				std::cerr << "发送删除预埋单请求失败" << std::endl;
		}
	}
	else
		std::cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
};

void WINAPI OnRspParkedOrderAction(
	CThostFtdcParkedOrderActionField* pParkedOrderAction, 
	CThostFtdcRspInfoField* pRspInfo, 
	int nRequestID, 
	bool bIsLast) 
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult) 
	{
		g_parkedOrderActionOK = true;
		g_cond_va.notify_one();

		std::cout << "=====修改埋单回调=====" << std::endl;
		std::cout << "经纪公司代码：" << pParkedOrderAction->BrokerID <<std::endl;
		std::cout << "投资者代码：" << pParkedOrderAction->InvestorID << std::endl;
		std::cout << "报单操作引用：" << pParkedOrderAction->OrderActionRef << std::endl;
		std::cout << "报单引用：" << pParkedOrderAction->OrderRef << std::endl;
		std::cout << "请求编号：" << pParkedOrderAction->RequestID << std::endl;
		std::cout << "前置编号：" << pParkedOrderAction->FrontID << std::endl;
		std::cout << "会话ID：" << pParkedOrderAction->SessionID << std::endl;
		std::cout << "交易所编号：" << pParkedOrderAction->ExchangeID << std::endl;
		std::cout << "报单编号：" << pParkedOrderAction->OrderSysID << std::endl;
		std::cout << "操作标识：" << pParkedOrderAction->ActionFlag << std::endl;
		std::cout << "价格：" << pParkedOrderAction->LimitPrice << std::endl;
		std::cout << "数量变化：" << pParkedOrderAction->VolumeChange << std::endl;
		std::cout << "用户代码：" << pParkedOrderAction->UserID << std::endl;
		std::cout << "合约代码：" << pParkedOrderAction->InstrumentID << std::endl;
		std::cout << "预埋撤单单编号：" << pParkedOrderAction->ParkedOrderActionID << std::endl;
		std::cout << "用户类型：" << pParkedOrderAction->UserType << std::endl;
		std::cout << "预埋单状态：" << pParkedOrderAction->Status << std::endl;
		std::cout << "错误码：" << pParkedOrderAction->ErrorID << std::endl;
		std::cout << "错误消息：" << pParkedOrderAction->ErrorMsg << std::endl;
		std::cout << "投资单元代码：" << pParkedOrderAction->InvestUnitID << std::endl;
		std::cout << "IP地址：" << pParkedOrderAction->IPAddress << std::endl;
		std::cout << "mac地址：" << pParkedOrderAction->MacAddress << std::endl;
	}
	else
		std::cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// 查询报单响应
void WINAPI OnRspQryOrder(CThostFtdcOrderField* pOrder, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) 
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult) {
		g_qryOrderOK = true;
		g_cond_va.notify_one();

		std::cout << "====查询报单响应====" << std::endl;
		std::cout << "经纪公司代码： " << pOrder->BrokerID << std::endl;
		std::cout << "投资者代码： " << pOrder->InvestorID << std::endl;
		std::cout << "合约代码： " << pOrder->InstrumentID << std::endl;
		std::cout << "报单引用： " << pOrder->OrderRef << std::endl;
		std::cout << "用户代码： " << pOrder->UserID << std::endl;
		std::cout << "报单价格条件： " << pOrder->OrderPriceType << std::endl;
		std::cout << "买卖方向： " << pOrder->Direction << std::endl;
		std::cout << "组合开平标志： " << pOrder->CombOffsetFlag << std::endl;
		std::cout << "组合投机套保标志： " << pOrder->CombHedgeFlag << std::endl;
		std::cout << "价格： " << pOrder->LimitPrice << std::endl;
		std::cout << "数量： " << pOrder->VolumeTotalOriginal << std::endl;
		std::cout << "有效期类型： " << pOrder->TimeCondition << std::endl;
		std::cout << "GTD日期： " << pOrder->GTDDate << std::endl;
		std::cout << "成交量类型： " << pOrder->VolumeCondition << std::endl;
		std::cout << "最小成交量： " << pOrder->MinVolume << std::endl;
		std::cout << "触发条件： " << pOrder->ContingentCondition << std::endl;
		std::cout << "止损价格： " << pOrder->StopPrice << std::endl;
		std::cout << "清平原因： " << pOrder->ForceCloseReason << std::endl;
		std::cout << "自动挂起标志： " << pOrder->IsAutoSuspend << std::endl;
		std::cout << "业务单元： " << pOrder->BusinessUnit << std::endl;
		std::cout << "请求编号： " << pOrder->RequestID << std::endl;
		std::cout << "用户强平标志： " << pOrder->UserForceClose << std::endl;
		std::cout << "互换单标志： " << pOrder->IsSwapOrder << std::endl;
		std::cout << "交易所代码： " << pOrder->ExchangeID << std::endl;
	}
	else
		std::cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// 查询最大订单量响应
void WINAPI OnRspQueryMaxOrderVolume(
	CThostFtdcQueryMaxOrderVolumeField* pQueryMaxOrderVolume, 
	CThostFtdcRspInfoField* pRspInfo, 
	int nRequestID, 
	bool bIsLast) 
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult) {
		g_queryMaxOrderVolumeOK = true;
		g_cond_va.notify_one();

		std::cout << "====查询最大订单量响应====" << std::endl;
		std::cout << "经纪公司代码： " << pQueryMaxOrderVolume->BrokerID << std::endl;
		std::cout << "投资者代码： " << pQueryMaxOrderVolume->InvestorID << std::endl;
		std::cout << "合约代码： " << pQueryMaxOrderVolume->InstrumentID << std::endl;
		std::cout << "买卖方向： " << pQueryMaxOrderVolume->Direction << std::endl;
		std::cout << "开平标志： " << pQueryMaxOrderVolume->OffsetFlag << std::endl;
		std::cout << "投机套保标志： " << pQueryMaxOrderVolume->HedgeFlag << std::endl;
		std::cout << "最大允许报单数量： " << pQueryMaxOrderVolume->MaxVolume << std::endl;
		std::cout << "交易所代码： " << pQueryMaxOrderVolume->ExchangeID << std::endl;
		std::cout << "投资单元代码： " << pQueryMaxOrderVolume->InvestUnitID << std::endl;
	}
	else
		std::cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// 投资者结算结果确认回调
void WINAPI OnReqSettlementInfoConfirm(
	CThostFtdcSettlementInfoConfirmField* pSettlementInfoConfirm, 
	CThostFtdcRspInfoField* pRspInfo, 
	int nRequestID, 
	bool bIsLast) 
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult) 
	{
		g_settlementInfoConfirmOK = true;
		g_cond_va.notify_one();

		std::cout << "====投资者结算结果确认回调====" << std::endl;
		std::cout << "经纪公司代码：" << pSettlementInfoConfirm->BrokerID << std::endl;
		std::cout << "投资者代码： " << pSettlementInfoConfirm->InvestorID << std::endl;
		std::cout << "确认日期： " << pSettlementInfoConfirm->ConfirmDate << std::endl;
		std::cout << "确认时间： " << pSettlementInfoConfirm->ConfirmTime << std::endl;
		std::cout << "结算编号： " << pSettlementInfoConfirm->SettlementID << std::endl;
		std::cout << "投资者账号： " << pSettlementInfoConfirm->AccountID << std::endl;
		std::cout << "币种代码： " << pSettlementInfoConfirm->CurrencyID << std::endl;
	}
	else 
		std::cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// 询价失败响应
void WINAPI OnRspForQuoteInsert(
	CThostFtdcForQuoteField* pForQuote, 
	CThostFtdcRspInfoField* pRspInfo, 
	int nRequestID, 
	bool bIsLast)
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult) {
		std::cout << "====询价失败响应，OnRspForQuoteInsert====" << std::endl;
		std::cout << "经纪公司代码：" << pForQuote->BrokerID << std::endl;
		std::cout << "投资者代码： " << pForQuote->InvestorID << std::endl;
		std::cout << "合约代码： " << pForQuote->InstrumentID << std::endl;
		std::cout << "询价引用： " << pForQuote->ForQuoteRef << std::endl;
		std::cout << "用户代码： " << pForQuote->UserID << std::endl;
		std::cout << "交易所代买： " << pForQuote->ExchangeID << std::endl;
		std::cout << "投资单元代码： " << pForQuote->InvestUnitID << std::endl;
	}
	else
		std::cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// 询价错误响应
void WINAPI OnErrRtnForQuoteInsert(
	CThostFtdcInputForQuoteField* pInputForQuote, 
	CThostFtdcRspInfoField* pRspInfo) 
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult) {
		std::cout << "====询价失败响应，OnErrRtnForQuoteInsert====" << std::endl;
		std::cout << "经纪公司代码：" << pInputForQuote->BrokerID << std::endl;
		std::cout << "投资者代码： " << pInputForQuote->InvestorID << std::endl;
		std::cout << "合约代码： " << pInputForQuote->InstrumentID << std::endl;
		std::cout << "询价引用： " << pInputForQuote->ForQuoteRef << std::endl;
		std::cout << "用户代码： " << pInputForQuote->UserID << std::endl;
		std::cout << "交易所代买： " << pInputForQuote->ExchangeID << std::endl;
		std::cout << "投资单元代码： " << pInputForQuote->InvestUnitID << std::endl;
	}
	else
		std::cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// 此接口暂时不可用
void WINAPI OnRtnForQuoteRsp(CThostFtdcForQuoteRspField* pForQuoteRsp) 
{
};

// 报价响应
void WINAPI OnRspQryQuote(
	CThostFtdcQuoteField* pQuote, 
	CThostFtdcRspInfoField* pRspInfo, 
	int nRequestID, 
	bool bIsLast) 
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult) {

		g_qryQuoteOK = true;
		g_cond_va.notify_one();

		std::cout << "====请求报价响应====" << std::endl;
		std::cout << "经纪公司代码：" << pQuote->BrokerID << std::endl;
		std::cout << "投资者代码： " << pQuote->InvestorID << std::endl;
		std::cout << "合约代码： " << pQuote->InstrumentID << std::endl;
		std::cout << "报价引用： " << pQuote->QuoteRef << std::endl;
		std::cout << "用户代码： " << pQuote->UserID << std::endl;
		std::cout << "卖价格： " << pQuote->AskPrice << std::endl;
		std::cout << "买价格： " << pQuote->BidPrice << std::endl;
		std::cout << "卖数量： " << pQuote->AskVolume << std::endl;
		std::cout << "买数量： " << pQuote->BidVolume << std::endl;
		std::cout << "请求编号： " << pQuote->RequestID << std::endl;
		std::cout << "交易所代买： " << pQuote->ExchangeID << std::endl;
		std::cout << "投资单元代码： " << pQuote->InvestUnitID << std::endl;
	}
	else
		std::cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// 请求组合的响应
void WINAPI OnRspQryCombAction(
	CThostFtdcCombActionField* pCombAction, 
	CThostFtdcRspInfoField* pRspInfo, 
	int nRequestID, 
	bool bIsLast) 
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult) 
	{
		g_qryCombActionOK = true;
		g_cond_va.notify_one();

		std::cout << "====请求组合的响应====" << std::endl;
		std::cout << "经纪公司代码： " << pCombAction->BrokerID << std::endl;
		std::cout << "投资者代码： " << pCombAction->InvestorID << std::endl;
		std::cout << "合约代码： " << pCombAction->InstrumentID << std::endl;
		std::cout << "组合引用： " << pCombAction->CombActionRef << std::endl;
		std::cout << "用户代码： " << pCombAction->UserID << std::endl;		
		std::cout << "买卖方向： " << pCombAction->Direction << std::endl;
		std::cout << "数量： " << pCombAction->Volume << std::endl;
		std::cout << "组合指令方向： " << pCombAction->CombDirection << std::endl;
		std::cout << "投机套保标志： " << pCombAction->HedgeFlag << std::endl;
		std::cout << "本地申请组合编号： " << pCombAction->ActionLocalID << std::endl;
		std::cout << "交易所代码： " << pCombAction->ExchangeID << std::endl;
		std::cout << "会员代码： " << pCombAction->ParticipantID << std::endl;
		std::cout << "客户代码： " << pCombAction->ClientID << std::endl;
		std::cout << "合约在交易所代码： " << pCombAction->ExchangeInstID << std::endl;
		std::cout << "交易所交易员代码： " << pCombAction->TraderID << std::endl;
		std::cout << "安装编号： " << pCombAction->InstallID << std::endl;
		std::cout << "组合状态： " << pCombAction->ActionStatus << std::endl;
		std::cout << "报单提示序号： " << pCombAction->NotifySequence << std::endl;
		std::cout << "交易日： " << pCombAction->TradingDay << std::endl;
		std::cout << "结算编号： " << pCombAction->SettlementID << std::endl;
		std::cout << "序号： " << pCombAction->SequenceNo << std::endl;
		std::cout << "前置编号： " << pCombAction->FrontID << std::endl;
		std::cout << "会话ID： " << pCombAction->SessionID << std::endl;
		std::cout << "用户端产品信息： " << pCombAction->UserProductInfo << std::endl;
	}
	else
		std::cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// 查询组合合约安全系数响应
void WINAPI OnRspQryCombInstrumentGuard(
	CThostFtdcCombInstrumentGuardField* pCombInstrumentGuard, 
	CThostFtdcRspInfoField* pRspInfo, 
	int nRequestID, 
	bool bIsLast) 
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult) {
		g_qryCombInstrumentGuardOK = true;
		g_cond_va.notify_one();

		std::cout << "====请求组合的响应====" << std::endl;
		std::cout << "经纪公司代码： " << pCombInstrumentGuard->BrokerID << std::endl;		
		std::cout << "合约代码： " << pCombInstrumentGuard->InstrumentID << std::endl;
		std::cout << "安全系数： " << pCombInstrumentGuard->GuarantRatio << std::endl;
		std::cout << "交易所代码： " << pCombInstrumentGuard->ExchangeID << std::endl;
	}
	else
		std::cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// 查询资金转账记录
void WINAPI OnRspQryTransferSerial(
	CThostFtdcTransferSerialField* pTransferSerial, 
	CThostFtdcRspInfoField* pRspInfo, 
	int nRequestID, 
	bool bIsLast) 
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult) {
		g_qryTransferSerialOK = true;
		g_cond_va.notify_one();

		std::cout << "====查询转账记录响应====" << std::endl;
		std::cout << "平台流水号： " << pTransferSerial->PlateSerial << std::endl;
		std::cout << "交易发起方日期： " << pTransferSerial->TradeDate << std::endl;
		std::cout << "交易日期： " << pTransferSerial->TradingDay << std::endl;
		std::cout << "交易时间： " << pTransferSerial->TradeTime << std::endl;
		std::cout << "交易代码： " << pTransferSerial->TradeCode << std::endl;
		std::cout << "会话编号： " << pTransferSerial->SessionID << std::endl;
		std::cout << "银行编号： " << pTransferSerial->BankID << std::endl;
		std::cout << "银行分支机构编号： " << pTransferSerial->BankBranchID << std::endl;
		std::cout << "银行帐号类型： " << pTransferSerial->BankAccType << std::endl;
		std::cout << "银行帐号： " << pTransferSerial->BankAccount << std::endl;
		std::cout << "银行流水号： " << pTransferSerial->BankSerial << std::endl;
		std::cout << "期货公司编号： " << pTransferSerial->BrokerID << std::endl;
		std::cout << "期商分支代号： " << pTransferSerial->BrokerBranchID << std::endl;
		std::cout << "期货公司账号类型： " << pTransferSerial->FutureAccType << std::endl;
		std::cout << "投资者账号： " << pTransferSerial->AccountID << std::endl;
		std::cout << "投资者代码： " << pTransferSerial->InvestorID << std::endl;
		std::cout << "期货公司流水号： " << pTransferSerial->FutureSerial << std::endl;
		std::cout << "证件类型： " << pTransferSerial->IdCardType << std::endl;
		std::cout << "证件号码： " << pTransferSerial->IdentifiedCardNo << std::endl;
		std::cout << "币种代码： " << pTransferSerial->CurrencyID << std::endl;
		std::cout << "交易金额： " << pTransferSerial->TradeAmount << std::endl;
		std::cout << "应收客户费用： " << pTransferSerial->CustFee << std::endl;
		std::cout << "应收期货公司费用： " << pTransferSerial->BrokerFee << std::endl;
		std::cout << "有效标志： " << pTransferSerial->AvailabilityFlag << std::endl;
	}
	else
		std::cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// 查询银期签约关系响应
void WINAPI OnRspQryAccountregister(
	CThostFtdcAccountregisterField* pAccountregister, 
	CThostFtdcRspInfoField* pRspInfo, 
	int nRequestID, 
	bool bIsLast) 
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult) 
	{
		g_qryAccountregisterOK = true;
		g_cond_va.notify_one();

		std::cout << "====查询银期签约关系响应====" << std::endl;
		std::cout << "交易日期： " << pAccountregister->TradeDay << std::endl;
		std::cout << "银行编号： " << pAccountregister->BankID << std::endl;
		std::cout << "银行分支机构编码： " << pAccountregister->BankBranchID << std::endl;
		std::cout << "银行帐号： " << pAccountregister->BankAccount << std::endl;
		std::cout << "期货公司编码： " << pAccountregister->BrokerID << std::endl;
		std::cout << "期货公司分支机构编码： " << pAccountregister->BrokerBranchID << std::endl;
		std::cout << "投资者账号： " << pAccountregister->AccountID << std::endl;
		std::cout << "证件类型： " << pAccountregister->IdCardType << std::endl;
		std::cout << "证件号码： " << pAccountregister->IdentifiedCardNo << std::endl;
		std::cout << "客户姓名： " << pAccountregister->CustomerName << std::endl;
		std::cout << "币种代码： " << pAccountregister->CurrencyID << std::endl;
		std::cout << "开销户类型： " << pAccountregister->OpenOrDestroy << std::endl;
		std::cout << "签约日期： " << pAccountregister->RegDate << std::endl;
		std::cout << "解约日期： " << pAccountregister->OutDate << std::endl;
		std::cout << "交易ID： " << pAccountregister->TID << std::endl;
		std::cout << "客户类型： " << pAccountregister->CustType << std::endl;
		std::cout << "银行帐号类型： " << pAccountregister->BankAccType << std::endl;
	}
	else
		std::cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// 合约状态通知
void WINAPI OnRtnInstrumentStatus(
	CThostFtdcInstrumentStatusField* pInstrumentStatus) 
{
	g_instrumentStatusOK = true;
	g_cond_va.notify_one();

	std::cout << "====合约状态通知====" << std::endl;
	std::cout << "交易所代码： " << pInstrumentStatus->ExchangeID << std::endl;
	std::cout << "合约在交易所的代码： " << pInstrumentStatus->ExchangeInstID << std::endl;
	std::cout << "结算组代码： " << pInstrumentStatus->SettlementGroupID << std::endl;
	std::cout << "合约代码： " << pInstrumentStatus->InstrumentID << std::endl;
	std::cout << "合约交易状态： " << pInstrumentStatus->InstrumentStatus << std::endl;
	std::cout << "交易阶段编号： " << pInstrumentStatus->TradingSegmentSN << std::endl;
	std::cout << "进入本地时间： " << pInstrumentStatus->EnterTime << std::endl;
	std::cout << "进入本地时间原因： " << pInstrumentStatus->EnterReason << std::endl;

}

// 交易通知
void WINAPI OnRtnTradingNotice(
	CThostFtdcTradingNoticeInfoField* pTradingNoticeInfo) 
{
	g_TradingNoticeOK = true;
	g_cond_va.notify_one();

	std::cout << "====交易通知====" << std::endl;
	std::cout << "经济公司代码： " << pTradingNoticeInfo->BrokerID << std::endl;
	std::cout << "投资者代码： " << pTradingNoticeInfo->InvestorID << std::endl;
	std::cout << "发送时间： " << pTradingNoticeInfo->SendTime << std::endl;
	std::cout << "消息正文： " << pTradingNoticeInfo->FieldContent << std::endl;
	std::cout << "序列系列号： " << pTradingNoticeInfo->SequenceSeries << std::endl;
	std::cout << "序列号： " << pTradingNoticeInfo->SequenceNo << std::endl;
	std::cout << "投资单元代码： " << pTradingNoticeInfo->InvestUnitID << std::endl;
}

// 查询签约银行响应
void WINAPI OnRspQryContractBank(
	CThostFtdcContractBankField* pContractBank, 
	CThostFtdcRspInfoField* pRspInfo, 
	int nRequestID, 
	bool bIsLast) 
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult) {
		g_qryContractBankOK = true;
		g_cond_va.notify_one();

		std::cout << "====查询签约银行响应====" << std::endl;
		std::cout << "经济公司代码： " << pContractBank->BrokerID << std::endl;
		std::cout << "银行代码： " << pContractBank->BankID << std::endl;
		std::cout << "银行分中心代码： " << pContractBank->BankBrchID << std::endl;
		std::cout << "银行名称： " << pContractBank->BankName << std::endl;
	}
	else 
		std::cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// 查询预埋单响应
void WINAPI OnRspQryParkedOrder(
	CThostFtdcParkedOrderField* pParkedOrder, 
	CThostFtdcRspInfoField* pRspInfo, 
	int nRequestID, 
	bool bIsLast) 
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult) {
		g_qryParkedOrderOK = true;
		g_cond_va.notify_one();

		std::cout << "=====查询预埋单请求成功=====" << std::endl;
		std::cout << "经纪公司代码： " << pParkedOrder->BrokerID << std::endl;
		std::cout << "投资者代码： " << pParkedOrder->InvestorID << std::endl;
		std::cout << "合约代码： " << pParkedOrder->InstrumentID << std::endl;
		std::cout << "报单引用： " << pParkedOrder->OrderRef << std::endl;
		std::cout << "用户代码： " << pParkedOrder->UserID << std::endl;
		std::cout << "报单价格条件： " << pParkedOrder->OrderPriceType << std::endl;
		std::cout << "买卖方向： " << pParkedOrder->Direction << std::endl;
		std::cout << "组合开平标志： " << pParkedOrder->CombOffsetFlag << std::endl;
		std::cout << "组合投机套保标志： " << pParkedOrder->CombHedgeFlag << std::endl;
		std::cout << "价格： " << pParkedOrder->LimitPrice << std::endl;
		std::cout << "数量： " << pParkedOrder->VolumeTotalOriginal << std::endl;
		std::cout << "有效期类型： " << pParkedOrder->TimeCondition << std::endl;
		std::cout << "GTD日期： " << pParkedOrder->GTDDate << std::endl;
		std::cout << "成交量类型： " << pParkedOrder->VolumeCondition << std::endl;
		std::cout << "最小成交量： " << pParkedOrder->MinVolume << std::endl;
		std::cout << "触发条件： " << pParkedOrder->ContingentCondition << std::endl;
		std::cout << "止损价格： " << pParkedOrder->StopPrice << std::endl;
		std::cout << "清平原因： " << pParkedOrder->ForceCloseReason << std::endl;
		std::cout << "自动挂起标志： " << pParkedOrder->IsAutoSuspend << std::endl;
		std::cout << "业务单元： " << pParkedOrder->BusinessUnit << std::endl;
		std::cout << "请求编号： " << pParkedOrder->RequestID << std::endl;
		std::cout << "用户强平标志： " << pParkedOrder->UserForceClose << std::endl;
		std::cout << "互换单标志： " << pParkedOrder->IsSwapOrder << std::endl;
		std::cout << "交易所代码： " << pParkedOrder->ExchangeID << std::endl;
		std::cout << "投资单元代码： " << pParkedOrder->InvestUnitID << std::endl;
		std::cout << "资金账户： " << pParkedOrder->AccountID << std::endl;
		std::cout << "币种代码： " << pParkedOrder->CurrencyID << std::endl;
		std::cout << "交易编码： " << pParkedOrder->ClientID << std::endl;

	}
	else
		std::cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// 查询预埋撤单请求响应
void WINAPI OnRspQryParkedOrderAction(
	CThostFtdcParkedOrderActionField* pParkedOrderAction, 
	CThostFtdcRspInfoField* pRspInfo, 
	int nRequestID, 
	bool bIsLast)
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult) {

		g_qryParkedOrderActionOK = true;
		g_cond_va.notify_one();

		std::cout << "=====查询预埋单请求成功=====" << std::endl;
		std::cout << "经纪公司代码： " << pParkedOrderAction->BrokerID << std::endl;
		std::cout << "投资者代码： " << pParkedOrderAction->InvestorID << std::endl;
		std::cout << "合约代码： " << pParkedOrderAction->InstrumentID << std::endl;
		std::cout << "报单引用： " << pParkedOrderAction->OrderRef << std::endl;
		std::cout << "用户代码： " << pParkedOrderAction->UserID << std::endl;		
		std::cout << "价格： " << pParkedOrderAction->LimitPrice << std::endl;		
		std::cout << "请求编号： " << pParkedOrderAction->RequestID << std::endl;		
		std::cout << "交易所代码： " << pParkedOrderAction->ExchangeID << std::endl;
		std::cout << "投资单元代码： " << pParkedOrderAction->InvestUnitID << std::endl;		

	}
	else
		std::cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// 查询交易通知响应
void WINAPI OnRspQryTradingNotice(
	CThostFtdcTradingNoticeField* pTradingNotice, 
	CThostFtdcRspInfoField* pRspInfo, 
	int nRequestID, 
	bool bIsLast) 
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult) {
		g_qryTradingNoticeOK = true;
		g_cond_va.notify_one();

		std::cout << "=====查询预埋单请求成功=====" << std::endl;
		std::cout << "经济公司代码： " << pTradingNotice->BrokerID << std::endl;
		std::cout << "投资者代码： " << pTradingNotice->InvestorID << std::endl;
		std::cout << "发送时间： " << pTradingNotice->SendTime << std::endl;
		std::cout << "消息正文： " << pTradingNotice->FieldContent << std::endl;
		std::cout << "序列系列号： " << pTradingNotice->SequenceSeries << std::endl;
		std::cout << "序列号： " << pTradingNotice->SequenceNo << std::endl;
		std::cout << "投资单元代码： " << pTradingNotice->InvestUnitID << std::endl;
	}
	else 
		std::cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// 查询经济公司交易参数响应
void WINAPI OnRspQryBrokerTradingParams(
	CThostFtdcBrokerTradingParamsField* pBrokerTradingParams, 
	CThostFtdcRspInfoField* pRspInfo, 
	int nRequestID, 
	bool bIsLast) 
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult) {
		g_qryBrokerTradingParamsOK = true;
		g_cond_va.notify_one();

		std::cout << "=====查询经济公司交易参数响应=====" << std::endl;
		std::cout << "经济公司代码： " << pBrokerTradingParams->BrokerID << std::endl;
		std::cout << "投资者代码： " << pBrokerTradingParams->InvestorID << std::endl;
		std::cout << "保证金价格类型： " << pBrokerTradingParams->MarginPriceType << std::endl;
		std::cout << "盈亏算法： " << pBrokerTradingParams->Algorithm << std::endl;
		std::cout << "可用是否包含平仓盈利： " << pBrokerTradingParams->AvailIncludeCloseProfit << std::endl;
		std::cout << "币种代码： " << pBrokerTradingParams->CurrencyID << std::endl;
		std::cout << "期权权利金价格类型： " << pBrokerTradingParams->OptionRoyaltyPriceType << std::endl;
	}
	else
		std::cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// 查询经济公司交易算法响应
void WINAPI OnRspQryBrokerTradingAlgos(
	CThostFtdcBrokerTradingAlgosField* pBrokerTradingAlgos, 
	CThostFtdcRspInfoField* pRspInfo, 
	int nRequestID, 
	bool bIsLast) 
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult) {
		g_qryBrokerTradingAlgosOK = true;
		g_cond_va.notify_one();

		std::cout << "=====查询经济公司交易算法响应=====" << std::endl;
		std::cout << "经济公司代码： " << pBrokerTradingAlgos->BrokerID << std::endl;
		std::cout << "交易所代码： " << pBrokerTradingAlgos->ExchangeID << std::endl;
		std::cout << "合约代码： " << pBrokerTradingAlgos->InstrumentID << std::endl;
		std::cout << "持仓处理算法编号： " << pBrokerTradingAlgos->HandlePositionAlgoID << std::endl;
		std::cout << "寻找保证金率编号： " << pBrokerTradingAlgos->FindMarginRateAlgoID << std::endl;
		std::cout << "资金处理算法编号： " << pBrokerTradingAlgos->HandleTradingAccountAlgoID << std::endl;
	}
	else 
		std::cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// 期货查询银行余额通知
void WINAPI OnRtnQueryBankBalanceByFuture(
	CThostFtdcNotifyQueryAccountField* pNotifyQueryAccount) 
{
	g_queryBankBalanceByFutureOK = true;
	g_cond_va.notify_one();

	std::cout << "=====期货查询银行余额通知=====" << std::endl;
	std::cout << "业务功能码： " << pNotifyQueryAccount->TradeCode << std::endl;
	std::cout << "银行代码： " << pNotifyQueryAccount->BankID << std::endl;
	std::cout << "银行分支机构代码： " << pNotifyQueryAccount->BankBranchID << std::endl;
	std::cout << "期商代码： " << pNotifyQueryAccount->BrokerID << std::endl;
	std::cout << "期商分支机构代码： " << pNotifyQueryAccount->BrokerBranchID << std::endl;
	std::cout << "交易日期： " << pNotifyQueryAccount->TradeDate << std::endl;

}

// 期货查询银行余额错误回调
void WINAPI OnRspQueryBankAccountMoneyByFuture(
	CThostFtdcReqQueryAccountField* pReqQueryAccount, 
	CThostFtdcRspInfoField* pRspInfo, 
	int nRequestID, 
	bool bIsLast) 
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult) {
		std::cout << "=====期货查询银行余额失败回调=====" << std::endl;
		std::cout << "业务功能码： " << pReqQueryAccount->TradeCode << std::endl;
		std::cout << "银行代码： " << pReqQueryAccount->BankID << std::endl;
		std::cout << "银行分支机构代码： " << pReqQueryAccount->BankBranchID << std::endl;
		std::cout << "期商代码： " << pReqQueryAccount->BrokerID << std::endl;
		std::cout << "期商分支机构代码： " << pReqQueryAccount->BrokerBranchID << std::endl;
		std::cout << "交易日期： " << pReqQueryAccount->TradeDate << std::endl;
	}
	else 
		std::cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// 查询监控中心用户令牌响应
void WINAPI OnRspQueryCFMMCTradingAccountToken(
	CThostFtdcQueryCFMMCTradingAccountTokenField* pQueryCFMMCTradingAccountToken, 
	CThostFtdcRspInfoField* pRspInfo, 
	int nRequestID, 
	bool bIsLast) 
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult) {
		std::cout << "=====查询监控中心用户令牌响应=====" << std::endl;
		std::cout << "经济公司代码： " << pQueryCFMMCTradingAccountToken->BrokerID << std::endl;
		std::cout << "投资者代码： " << pQueryCFMMCTradingAccountToken->InvestorID << std::endl;
		std::cout << "投资单元代码： " << pQueryCFMMCTradingAccountToken->InvestUnitID << std::endl;
	}
	else
		std::cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// 监控中心用户令牌通知
void WINAPI OnRtnCFMMCTradingAccountToken(
	CThostFtdcCFMMCTradingAccountTokenField* pCFMMCTradingAccountToken) 
{
	g_queryCFMMCTradingAccountTokenOK = true;
	g_cond_va.notify_one();

	std::cout << "=====监控中心用户令牌通知=====" << std::endl;
	std::cout << "经济公司代码： " << pCFMMCTradingAccountToken->BrokerID << std::endl;
	std::cout << "经济公司统一编码： " << pCFMMCTradingAccountToken->ParticipantID << std::endl;
	std::cout << "投资者账户： " << pCFMMCTradingAccountToken->AccountID << std::endl;
	std::cout << "密钥编码： " << pCFMMCTradingAccountToken->KeyID << std::endl;
	std::cout << "动态令牌： " << pCFMMCTradingAccountToken->Token << std::endl;
}

// 期货请求银行转期货应答
void WINAPI OnRspFromBankToFutureByFuture(
	CThostFtdcReqTransferField* pReqTransfer, 
	CThostFtdcRspInfoField* pRspInfo, 
	int nRequestID, 
	bool bIsLast) 
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult) {
		g_reqFromBankToFutureByFutureOK = true;
		g_cond_va.notify_one();

		std::cout << "=====期货请求银行转期货应答=====" << std::endl;
		std::cout << "业务功能码： " << pReqTransfer->TradeCode << std::endl;
		std::cout << "银行代码： " << pReqTransfer->BankID << std::endl;
		std::cout << "银行分支结构代码： " << pReqTransfer->BankBranchID << std::endl;
		std::cout << "期商代码： " << pReqTransfer->BrokerID << std::endl;
		std::cout << "期商分支结构代码： " << pReqTransfer->BrokerBranchID << std::endl;
		std::cout << "交易日期： " << pReqTransfer->TradeDate << std::endl;
		std::cout << "交易时间： " << pReqTransfer->TradeTime << std::endl;
		std::cout << "银行流水号： " << pReqTransfer->BankSerial << std::endl;
		std::cout << "交易日期： " << pReqTransfer->TradingDay << std::endl;
		std::cout << "银行消息流水号： " << pReqTransfer->PlateSerial << std::endl;
		std::cout << "最后分片标志： " << pReqTransfer->LastFragment << std::endl;
		std::cout << "会话ID： " << pReqTransfer->SessionID << std::endl;
		std::cout << "客户名： " << pReqTransfer->CustomerName << std::endl;
		std::cout << "证件类型： " << pReqTransfer->IdCardType << std::endl;
	}
	else
		std::cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// 查询投资单元应答
void WINAPI OnRspQryInvestUnit(
	CThostFtdcInvestUnitField* pInvestUnit, 
	CThostFtdcRspInfoField* pRspInfo, 
	int nRequestID, 
	bool bIsLast) 
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult) {
		g_reqQryInvestUnitOK = true;
		g_cond_va.notify_one();

		std::cout << "=====查询投资单元应答=====" << std::endl;
		std::cout << "经济公司代码： " << pInvestUnit->BrokerID << std::endl;
		std::cout << "投资者代码： " << pInvestUnit->InvestorID << std::endl;
		std::cout << "投资单元代码： " << pInvestUnit->InvestUnitID << std::endl;
		std::cout << "投资单元名称： " << pInvestUnit->InvestorUnitName << std::endl;
		std::cout << "投资者分组代码： " << pInvestUnit->InvestorGroupID << std::endl;
		std::cout << "手续费率模板代码： " << pInvestUnit->CommModelID << std::endl;
		std::cout << "保证金率模板代码： " << pInvestUnit->MarginModelID << std::endl;
		std::cout << "资金账户： " << pInvestUnit->AccountID << std::endl;
		std::cout << "币种代码： " << pInvestUnit->CurrencyID << std::endl;		
	}
	else 
		std::cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// 请求查询二级市场响应
void WINAPI OnRspQrySecAgentTradeInfo(
	CThostFtdcSecAgentTradeInfoField* pSecAgentTradeInfo, 
	CThostFtdcRspInfoField* pRspInfo, 
	int nRequestID, 
	bool bIsLast) 
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult) 
	{
		g_reqQrySecAgentTradeInfoOK = true;
		g_cond_va.notify_one();

		std::cout << "=====请求查询二级市场应答=====" << std::endl;
		std::cout << "经济公司代码： " << pSecAgentTradeInfo->BrokerID << std::endl;
		std::cout << "境外机构资金帐号： " << pSecAgentTradeInfo->BrokerSecAgentID << std::endl;
		std::cout << "投资者代码： " << pSecAgentTradeInfo->InvestorID << std::endl;
		std::cout << "二级代理商姓名： " << pSecAgentTradeInfo->LongCustomerName << std::endl;
	}
	else
		std::cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// 请求查询二级代理商资金验证模式
void WINAPI OnRspQrySecAgentCheckMode(
	CThostFtdcSecAgentCheckModeField* pSecAgentCheckMode, 
	CThostFtdcRspInfoField* pRspInfo, 
	int nRequestID, 
	bool bIsLast)
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult)
	{
		g_reqQrySecAgentCheckModeOK = true;
		g_cond_va.notify_one();

		std::cout << "=====请求查询二级市场应答=====" << std::endl;
		std::cout << "经济公司代码： " << pSecAgentCheckMode->BrokerID << std::endl;
		std::cout << "境外机构资金帐号： " << pSecAgentCheckMode->BrokerSecAgentID << std::endl;
		std::cout << "投资者代码： " << pSecAgentCheckMode->InvestorID << std::endl;
		std::cout << "币种类型： " << pSecAgentCheckMode->CurrencyID << std::endl;
	}
	else
		std::cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// 查询资金账户
void WINAPI OnRspQrySecAgentTradingAccount(
	CThostFtdcTradingAccountField* pTradingAccount, 
	CThostFtdcRspInfoField* pRspInfo, 
	int nRequestID, 
	bool bIsLast) 
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult) 
	{
		g_reqQrySecAgentTradingAccountOK = true;
		g_cond_va.notify_one();

		std::cout << "=====请求查询投资者账户应答=====" << std::endl;
		std::cout << "经济公司代码： " << pTradingAccount->BrokerID << std::endl;
		std::cout << "投资者账户： " << pTradingAccount->AccountID << std::endl;
		std::cout << "上次质押金额： " << pTradingAccount->PreMortgage << std::endl;
		std::cout << "上次信用额度： " << pTradingAccount->PreCredit << std::endl;
		std::cout << "上次存款额度： " << pTradingAccount->PreDeposit << std::endl;
		std::cout << "上次结算备用金： " << pTradingAccount->PreBalance << std::endl;
		std::cout << "上次占用保障金： " << pTradingAccount->PreMargin << std::endl;
		std::cout << "利息基数： " << pTradingAccount->InterestBase << std::endl;
		std::cout << "利息收入： " << pTradingAccount->Interest << std::endl;
		std::cout << "入金金额： " << pTradingAccount->Deposit << std::endl;
		std::cout << "出金金额： " << pTradingAccount->Withdraw << std::endl;
		std::cout << "冻结的保障金： " << pTradingAccount->FrozenMargin << std::endl;
		std::cout << "冻结的资金： " << pTradingAccount->FrozenCash << std::endl;
		std::cout << "冻结的手续费： " << pTradingAccount->FrozenCommission << std::endl;
	}
	else 
		std::cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// 请求查询报单手续费
void WINAPI OnRspQryInstrumentOrderCommRate(
	CThostFtdcInstrumentOrderCommRateField* pInstrumentOrderCommRate, 
	CThostFtdcRspInfoField* pRspInfo, 
	int nRequestID, 
	bool bIsLast) 
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult) 
	{
		g_reqQryInstrumentOrderCommRateOK = true;
		g_cond_va.notify_one();

		std::cout << "=====请求查询报单手续费响应=====" << std::endl;
		std::cout << "合约代码： " << pInstrumentOrderCommRate->InstrumentID << std::endl;
		std::cout << "投资者范围： " << pInstrumentOrderCommRate->InvestorRange << std::endl;
		std::cout << "经济公司代码： " << pInstrumentOrderCommRate->BrokerID << std::endl;
		std::cout << "投资者代码： " << pInstrumentOrderCommRate->InvestorID << std::endl;
		std::cout << "投机套保标志： " << pInstrumentOrderCommRate->HedgeFlag << std::endl;
		std::cout << "报单手续费： " << pInstrumentOrderCommRate->OrderCommByVolume << std::endl;
		std::cout << "撤单手续费： " << pInstrumentOrderCommRate->OrderActionCommByVolume << std::endl;
		std::cout << "交易所代码： " << pInstrumentOrderCommRate->ExchangeID << std::endl;
		std::cout << "投资单元代码： " << pInstrumentOrderCommRate->InvestUnitID << std::endl;
	}
	else 
		std::cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// 请求查询做市商手续费响应
void WINAPI OnRspQryMMInstrumentCommissionRate(
	CThostFtdcMMInstrumentCommissionRateField* pMMInstrumentCommissionRate, 
	CThostFtdcRspInfoField* pRspInfo, 
	int nRequestID, 
	bool bIsLast) 
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult)
	{
		g_reqQryMMInstrumentCommissionRateOK = true;
		g_cond_va.notify_one();

		std::cout << "=====请求查询做市商合约手续费响应=====" << std::endl;
		std::cout << "合约代码： " << pMMInstrumentCommissionRate->InstrumentID << std::endl;
		std::cout << "投资者范围： " << pMMInstrumentCommissionRate->InvestorRange << std::endl;
		std::cout << "经济公司代码： " << pMMInstrumentCommissionRate->BrokerID << std::endl;
		std::cout << "投资者代码： " << pMMInstrumentCommissionRate->InvestorID << std::endl;
		std::cout << "开仓手续费率： " << pMMInstrumentCommissionRate->OpenRatioByMoney << std::endl;
		std::cout << "开仓手续费： " << pMMInstrumentCommissionRate->OpenRatioByVolume << std::endl;
		std::cout << "平仓手续费率： " << pMMInstrumentCommissionRate->CloseRatioByMoney << std::endl;
		std::cout << "平仓手续费： " << pMMInstrumentCommissionRate->CloseRatioByVolume << std::endl;
		std::cout << "平今手续费率： " << pMMInstrumentCommissionRate->CloseTodayRatioByMoney << std::endl;
		std::cout << "平今手续费： " << pMMInstrumentCommissionRate->CloseTodayRatioByVolume << std::endl;
	}
	else
		std::cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// 请求查询产品组响应
void WINAPI OnRspQryProductGroup (CThostFtdcProductGroupField* pProductGroup, 
	CThostFtdcRspInfoField* pRspInfo, 
	int nRequestID, 
	bool bIsLast) 
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult)
	{
		g_reqQryProductGroupOK = true;
		g_cond_va.notify_one();

		std::cout << "=====请求查询产品组响应=====" << std::endl;
		std::cout << "产品I代码： " << pProductGroup->ProductID << std::endl;
		std::cout << "交易所代码： " << pProductGroup->ExchangeID << std::endl;
		std::cout << "产品组代码： " << pProductGroup->ProductGroupID << std::endl;		
	}
	else
		std::cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// 请求查询产品报价汇率
void WINAPI OnRspQryProductExchRate(
	CThostFtdcProductExchRateField* pProductExchRate,
	CThostFtdcRspInfoField* pRspInfo,
	int nRequestID,
	bool bIsLast) 
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult)
	{
		g_reqQryProductExchRateOK = true;
		g_cond_va.notify_one();

		std::cout << "=====请求查询产品报价汇率响应=====" << std::endl;
		std::cout << "产品代码： " << pProductExchRate->ProductID << std::endl;
		std::cout << "交易所代码： " << pProductExchRate->ExchangeID << std::endl;
		std::cout << "汇率： " << pProductExchRate->ExchangeRate << std::endl;
	}
	else
		std::cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// 请求查询汇率
void WINAPI OnRspQryExchangeRate(
	CThostFtdcExchangeRateField* pExchangeRate, 
	CThostFtdcRspInfoField* pRspInfo, 
	int nRequestID, 
	bool bIsLast) 
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult)
	{
		g_reqQryExchangeRateOK = true;
		g_cond_va.notify_one();

		std::cout << "=====请求查询汇率响应=====" << std::endl;
		std::cout << "经济公司代码： " << pExchangeRate->BrokerID << std::endl;
		std::cout << "源币种： " << pExchangeRate->FromCurrencyID << std::endl;
		std::cout << "源币种数量： " << pExchangeRate->FromCurrencyUnit << std::endl;
		std::cout << "目标币种： " << pExchangeRate->ToCurrencyID << std::endl;
		std::cout << "汇率： " << pExchangeRate->ExchangeRate << std::endl;
	}
	else
		std::cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// 请求交易所调整的保证金率
void WINAPI OnRspQryExchangeMarginRateAdjust(
	CThostFtdcExchangeMarginRateAdjustField* pExchangeMarginRateAdjust, 
	CThostFtdcRspInfoField* pRspInfo, 
	int nRequestID, 
	bool bIsLast) 
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult)
	{
		g_reqQryExchangeMarginRateAdjustOK = true;
		g_cond_va.notify_one();

		std::cout << "=====请求交易所调整的保证金率响应=====" << std::endl;
		std::cout << "经济公司代码： " << pExchangeMarginRateAdjust->BrokerID << std::endl;
		std::cout << "合约代码： " << pExchangeMarginRateAdjust->InstrumentID << std::endl;
		std::cout << "投机套保标志： " << pExchangeMarginRateAdjust->HedgeFlag << std::endl;
		std::cout << "跟随交易所投资者多头保证金率： " << pExchangeMarginRateAdjust->LongMarginRatioByMoney << std::endl;
		std::cout << "跟随交易所投资者多头保证金费： " << pExchangeMarginRateAdjust->LongMarginRatioByVolume << std::endl;
	}
	else
		std::cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// 请求查询交易所汇率响应
void WINAPI OnRspQryExchangeMarginRate(
	CThostFtdcExchangeMarginRateField* pExchangeMarginRate, 
	CThostFtdcRspInfoField* pRspInfo, 
	int nRequestID, 
	bool bIsLast) 
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult)
	{
		g_reqQryExchangeMarginRateOK = true;
		g_cond_va.notify_one();

		std::cout << "=====请求查询交易所汇率响应=====" << std::endl;
		std::cout << "经济公司代码： " << pExchangeMarginRate->BrokerID << std::endl;
		std::cout << "合约代码： " << pExchangeMarginRate->InstrumentID << std::endl;
		std::cout << "投机套保标志： " << pExchangeMarginRate->HedgeFlag << std::endl;
		std::cout << "跟随交易所投资者多头保证金率： " << pExchangeMarginRate->LongMarginRatioByMoney << std::endl;
		std::cout << "跟随交易所投资者多头保证金费： " << pExchangeMarginRate->LongMarginRatioByVolume << std::endl;
	}
	else
		std::cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// 请求查询投资者品种/跨品种保证金
void WINAPI OnRspQryInvestorProductGroupMargin(
	CThostFtdcInvestorProductGroupMarginField* pInvestorProductGroupMargin, 
	CThostFtdcRspInfoField* pRspInfo, 
	int nRequestID, 
	bool bIsLast) 
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult)
	{
		g_reqQryInvestorProductGroupMarginOK = true;
		g_cond_va.notify_one();

		std::cout << "=====请求查询交易所汇率响应=====" << std::endl;
		std::cout << "品种跨品种标志： " << pInvestorProductGroupMargin->ProductGroupID << std::endl;
		std::cout << "经济公司代码： " << pInvestorProductGroupMargin->BrokerID << std::endl;
		std::cout << "投资者代码： " << pInvestorProductGroupMargin->InvestorID << std::endl;
		std::cout << "交易日： " << pInvestorProductGroupMargin->TradingDay << std::endl;
		std::cout << "结算编号： " << pInvestorProductGroupMargin->SettlementID << std::endl;
		std::cout << "冻结保证金： " << pInvestorProductGroupMargin->FrozenMargin << std::endl;
		std::cout << "多头冻结保证金： " << pInvestorProductGroupMargin->LongFrozenMargin << std::endl;
		std::cout << "空头冻结保证金： " << pInvestorProductGroupMargin->ShortFrozenMargin << std::endl;
		std::cout << "占用保证金： " << pInvestorProductGroupMargin->UseMargin << std::endl;
		std::cout << "多头保证金： " << pInvestorProductGroupMargin->LongUseMargin << std::endl;
		std::cout << "空头保证金： " << pInvestorProductGroupMargin->ShortUseMargin << std::endl;
		std::cout << "交易所保证金： " << pInvestorProductGroupMargin->ExchMargin << std::endl;
		std::cout << "交易所多头保证金： " << pInvestorProductGroupMargin->LongExchMargin << std::endl;
		std::cout << "交易所空头保证金： " << pInvestorProductGroupMargin->ShortExchMargin << std::endl;
		std::cout << "平仓盈亏： " << pInvestorProductGroupMargin->CloseProfit << std::endl;
		std::cout << "冻结的手续费： " << pInvestorProductGroupMargin->FrozenCommission << std::endl;
		std::cout << "手续费： " << pInvestorProductGroupMargin->Commission << std::endl;
		std::cout << "冻结资金： " << pInvestorProductGroupMargin->FrozenCash << std::endl;
		std::cout << "资金差额： " << pInvestorProductGroupMargin->CashIn << std::endl;
		std::cout << "持仓盈利： " << pInvestorProductGroupMargin->PositionProfit << std::endl;
		std::cout << "折扣总金额： " << pInvestorProductGroupMargin->OffsetAmount << std::endl;
		std::cout << "多头折扣总金额： " << pInvestorProductGroupMargin->LongOffsetAmount << std::endl;
	}
	else
		std::cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// 查询仓单信息响应
void WINAPI OnRspQryEWarrantOffset(
	CThostFtdcEWarrantOffsetField* pEWarrantOffset, 
	CThostFtdcRspInfoField* pRspInfo, 
	int nRequestID, 
	bool bIsLast) 
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult)
	{
		g_reqQryEWarrantOffsetOK = true;
		g_cond_va.notify_one();

		std::cout << "=====查询仓单信息响应=====" << std::endl;
		std::cout << "交易日期： " << pEWarrantOffset->TradingDay << std::endl;
		std::cout << "经济公司代码： " << pEWarrantOffset->BrokerID << std::endl;
		std::cout << "投资者代码： " << pEWarrantOffset->InvestorID << std::endl;
		std::cout << "交易所代码： " << pEWarrantOffset->ExchangeID << std::endl;
		std::cout << "合约代码： " << pEWarrantOffset->InstrumentID << std::endl;
		std::cout << "买卖方向： " << pEWarrantOffset->Direction << std::endl;
		std::cout << "投资套保标志： " << pEWarrantOffset->HedgeFlag << std::endl;
		std::cout << "数量： " << pEWarrantOffset->Volume << std::endl;				
	}
	else
		std::cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// 请求查询保证金监管系统经纪公司资金账户密钥响应
void WINAPI OnRspQryCFMMCTradingAccountKey(
	CThostFtdcCFMMCTradingAccountKeyField* pCFMMCTradingAccountKey, 
	CThostFtdcRspInfoField* pRspInfo, 
	int nRequestID, 
	bool bIsLast) 
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult)
	{
		g_reqQryCFMMCTradingAccountKeyOK = true;
		g_cond_va.notify_one();

		std::cout << "=====查询仓单信息响应=====" << std::endl;		
		std::cout << "经济公司代码： " << pCFMMCTradingAccountKey->BrokerID << std::endl;
		std::cout << "经济公司统一编码： " << pCFMMCTradingAccountKey->ParticipantID << std::endl;
		std::cout << "投资者账户： " << pCFMMCTradingAccountKey->AccountID << std::endl;
		std::cout << "密钥编号： " << pCFMMCTradingAccountKey->KeyID << std::endl;
		std::cout << "动态密钥： " << pCFMMCTradingAccountKey->CurrentKey << std::endl;		
	}
	else
		std::cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// 请求投资者组合持仓信息响应
void WINAPI OnRspQryInvestorPositionCombineDetail(
	CThostFtdcInvestorPositionCombineDetailField* pInvestorPositionCombineDetail, 
	CThostFtdcRspInfoField* pRspInfo, 
	int nRequestID, 
	bool bIsLast) 
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult)
	{
		g_reqQryInvestorPositionCombineDetailOK = true;
		g_cond_va.notify_one();

		std::cout << "=====请求投资者组合持仓信息响应=====" << std::endl;
		std::cout << "交易日： " << pInvestorPositionCombineDetail->TradingDay << std::endl;
		std::cout << "开仓日期： " << pInvestorPositionCombineDetail->OpenDate << std::endl;
		std::cout << "交易所代码： " << pInvestorPositionCombineDetail->ExchangeID << std::endl;
		std::cout << "结算编号： " << pInvestorPositionCombineDetail->SettlementID << std::endl;
		std::cout << "经济公司代码： " << pInvestorPositionCombineDetail->BrokerID << std::endl;
		std::cout << "投资者代码： " << pInvestorPositionCombineDetail->InvestorID << std::endl;
		std::cout << "组合编号： " << pInvestorPositionCombineDetail->ComTradeID << std::endl;
		std::cout << "撮合编号： " << pInvestorPositionCombineDetail->TradeID << std::endl;
		std::cout << "合约代码： " << pInvestorPositionCombineDetail->InstrumentID << std::endl;
		std::cout << "投机套保标志： " << pInvestorPositionCombineDetail->HedgeFlag << std::endl;
		std::cout << "买卖方向： " << pInvestorPositionCombineDetail->Direction << std::endl;
		std::cout << "持仓量： " << pInvestorPositionCombineDetail->TotalAmt << std::endl;
		std::cout << "投资者保证金： " << pInvestorPositionCombineDetail->Margin << std::endl;
		std::cout << "交易所保证金： " << pInvestorPositionCombineDetail->ExchMargin << std::endl;
		std::cout << "保证金率： " << pInvestorPositionCombineDetail->MarginRateByMoney << std::endl;
		std::cout << "保证金率（按手数）： " << pInvestorPositionCombineDetail->MarginRateByVolume << std::endl;
		std::cout << "单腿编号： " << pInvestorPositionCombineDetail->LegID << std::endl;
		std::cout << "单腿合约乘数： " << pInvestorPositionCombineDetail->LegMultiple << std::endl;
	}
	else
		std::cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// 请求查询投资者持仓信息响应
void WINAPI OnRspQryInvestorPositionDetail(
	CThostFtdcInvestorPositionDetailField* pInvestorPositionDetail, 
	CThostFtdcRspInfoField* pRspInfo, 
	int nRequestID, 
	bool bIsLast) 
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult)
	{
		g_reqQryInvestorPositionDetailOK = true;
		g_cond_va.notify_one();

		std::cout << "=====请求查询投资者持仓信息响应=====" << std::endl;
		std::cout << "交易日： " << pInvestorPositionDetail->TradingDay << std::endl;
		std::cout << "开仓日期： " << pInvestorPositionDetail->OpenDate << std::endl;
		std::cout << "交易所代码： " << pInvestorPositionDetail->ExchangeID << std::endl;
		std::cout << "结算编号： " << pInvestorPositionDetail->SettlementID << std::endl;
		std::cout << "经济公司代码： " << pInvestorPositionDetail->BrokerID << std::endl;
		std::cout << "投资者代码： " << pInvestorPositionDetail->InvestorID << std::endl;		
		std::cout << "撮合编号： " << pInvestorPositionDetail->TradeID << std::endl;
		std::cout << "合约代码： " << pInvestorPositionDetail->InstrumentID << std::endl;
		std::cout << "投机套保标志： " << pInvestorPositionDetail->HedgeFlag << std::endl;
		std::cout << "买卖方向： " << pInvestorPositionDetail->Direction << std::endl;		
		std::cout << "投资者保证金： " << pInvestorPositionDetail->Margin << std::endl;
		std::cout << "交易所保证金： " << pInvestorPositionDetail->ExchMargin << std::endl;
		std::cout << "保证金率： " << pInvestorPositionDetail->MarginRateByMoney << std::endl;
		std::cout << "保证金率（按手数）： " << pInvestorPositionDetail->MarginRateByVolume << std::endl;		
	}
	else
		std::cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// 请求银行转账记录响应
void WINAPI OnRspQryTransferBank(
	CThostFtdcTransferBankField* pTransferBank, 
	CThostFtdcRspInfoField* pRspInfo, 
	int nRequestID, 
	bool bIsLast) 
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult) 
	{
		g_reqQryTransferBankOK = true;
		g_cond_va.notify_one();

		std::cout << "=====请求查询投资者持仓信息响应=====" << std::endl;
		std::cout << "银行代码： " << pTransferBank->BankID << std::endl;
		std::cout << "银行分中心代码： " << pTransferBank->BankBrchID << std::endl;
		std::cout << "银行名称： " << pTransferBank->BankName << std::endl;
		std::cout << "是否活跃： " << pTransferBank->IsActive << std::endl;
	}
	else 
		std::cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// 请求查询投资者结算信息响应
void WINAPI OnRspQrySettlementInfo(
	CThostFtdcSettlementInfoField* pSettlementInfo, 
	CThostFtdcRspInfoField* pRspInfo, 
	int nRequestID, 
	bool bIsLast) 
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult)
	{
		g_reqQrySettlementInfoOK = true;
		g_cond_va.notify_one();

		std::cout << "=====请求查询投资者结算信息响应=====" << std::endl;
		std::cout << "交易日： " << pSettlementInfo->TradingDay << std::endl;
		std::cout << "结算编号： " << pSettlementInfo->SettlementID << std::endl;
		std::cout << "经济公司代码： " << pSettlementInfo->BrokerID << std::endl;
		std::cout << "投资者代码： " << pSettlementInfo->InvestorID << std::endl;
		std::cout << "序号： " << pSettlementInfo->SequenceNo << std::endl;
		std::cout << "消息正文： " << pSettlementInfo->Content << std::endl;
		std::cout << "投资者账号： " << pSettlementInfo->AccountID << std::endl;
	}
	else
		std::cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// 请求查询行情响应
void WINAPI OnRspQryDepthMarketData(
	CThostFtdcDepthMarketDataField* pDepthMarketData, 
	CThostFtdcRspInfoField* pRspInfo, 
	int nRequestID, 
	bool bIsLast) 
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult)
	{
		g_reqQryDepthMarketDataOK = true;
		g_cond_va.notify_one();

		std::cout << "=====请求查询行情响应=====" << std::endl;
		std::cout << "交易日： " << pDepthMarketData->TradingDay << std::endl;
		std::cout << "合约代码： " << pDepthMarketData->InstrumentID << std::endl;
		std::cout << "交易所代码： " << pDepthMarketData->ExchangeID << std::endl;
		std::cout << "合约在交易所代码： " << pDepthMarketData->ExchangeInstID << std::endl;
		std::cout << "最新价： " << pDepthMarketData->LastPrice << std::endl;
		std::cout << "上次结算价： " << pDepthMarketData->PreSettlementPrice << std::endl;
		std::cout << "昨日收盘价： " << pDepthMarketData->PreClosePrice << std::endl;
		std::cout << "昨日持仓量： " << pDepthMarketData->PreOpenInterest << std::endl;
		std::cout << "今日开盘价： " << pDepthMarketData->OpenPrice << std::endl;
		std::cout << "最高价： " << pDepthMarketData->HighestPrice << std::endl;
		std::cout << "最低价： " << pDepthMarketData->LowestPrice << std::endl;
		std::cout << "数量： " << pDepthMarketData->Volume << std::endl;
		std::cout << "成交金额： " << pDepthMarketData->Turnover << std::endl;
		std::cout << "持仓量： " << pDepthMarketData->OpenInterest << std::endl;
		std::cout << "今收盘价： " << pDepthMarketData->ClosePrice << std::endl;
	}
	else
		std::cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// 请求查询合约
void WINAPI OnRspQryInstrument(
	CThostFtdcInstrumentField* pInstrument, 
	CThostFtdcRspInfoField* pRspInfo, 
	int nRequestID, 
	bool bIsLast) 
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult)
	{
		g_reqQryInstrumentOK = true;
		g_cond_va.notify_one();

		std::cout << "=====请求查询合约响应=====" << std::endl;		
		std::cout << "合约代码： " << pInstrument->InstrumentID << std::endl;
		std::cout << "交易所代码： " << pInstrument->ExchangeID << std::endl;
		std::cout << "合约名称： " << pInstrument->InstrumentName << std::endl;
		std::cout << "合约在交易所代码： " << pInstrument->ExchangeInstID << std::endl;
		std::cout << "产品代码： " << pInstrument->ProductID << std::endl;
		std::cout << "产品类型： " << pInstrument->ProductClass << std::endl;
		std::cout << "交割年份： " << pInstrument->DeliveryYear << std::endl;
		std::cout << "交割月份： " << pInstrument->DeliveryMonth << std::endl;
		std::cout << "市价单最大下单量： " << pInstrument->MaxMarketOrderVolume << std::endl;
		std::cout << "市价单最小下单量： " << pInstrument->MinMarketOrderVolume << std::endl;
		std::cout << "限价单最大下单量： " << pInstrument->MaxLimitOrderVolume << std::endl;
		std::cout << "限价单最小下单量： " << pInstrument->MinLimitOrderVolume << std::endl;
		std::cout << "合约数量乘数： " << pInstrument->VolumeMultiple << std::endl;
		std::cout << "最小变动单位： " << pInstrument->PriceTick << std::endl;
		std::cout << "创建日： " << pInstrument->CreateDate << std::endl;
		std::cout << "上市日： " << pInstrument->OpenDate << std::endl;
		std::cout << "到期日： " << pInstrument->ExpireDate << std::endl;
		std::cout << "开始交割日： " << pInstrument->StartDelivDate << std::endl;
		std::cout << "结束交割日： " << pInstrument->EndDelivDate << std::endl;
		std::cout << "合约生命周期状态： " << pInstrument->InstLifePhase << std::endl;
		std::cout << "当前是否交易： " << pInstrument->IsTrading << std::endl;
		std::cout << "持仓类型： " << pInstrument->PositionType << std::endl;
		std::cout << "持仓日期类型： " << pInstrument->PositionDateType << std::endl;
		std::cout << "多头保证金率： " << pInstrument->LongMarginRatio << std::endl;
		std::cout << "空头保证金率： " << pInstrument->ShortMarginRatio << std::endl;
		std::cout << "是否使用大额保证金算法： " << pInstrument->MaxMarginSideAlgorithm << std::endl;
	}
	else
		std::cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// 请求查询交易所响应
void WINAPI OnRspQryExchange(
	CThostFtdcExchangeField* pExchange, 
	CThostFtdcRspInfoField* pRspInfo, 
	int nRequestID, 
	bool bIsLast) 
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult)
	{
		g_reqQryExchangeOK = true;
		g_cond_va.notify_one();

		std::cout << "=====请求查询交易所信息响应=====" << std::endl;
		std::cout << "交易所编号： " << pExchange->ExchangeID<< std::endl;
		std::cout << "交易所名称： " << pExchange->ExchangeName << std::endl;
		std::cout << "交易所属性： " << pExchange->ExchangeProperty << std::endl;		
	}
	else
		std::cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// 请求查询合约手续费
void WINAPI OnRspQryInstrumentCommissionRate(
	CThostFtdcInstrumentCommissionRateField* pInstrumentCommissionRate, 
	CThostFtdcRspInfoField* pRspInfo, 
	int nRequestID, 
	bool bIsLast) 
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult)
	{
		g_reqQryInstrumentCommissionRateOK = true;
		g_cond_va.notify_one();

		std::cout << "=====请求查询合约手续费信息响应=====" << std::endl;
		std::cout << "合约代码： " << pInstrumentCommissionRate->InstrumentID << std::endl;
		std::cout << "投资者范围： " << pInstrumentCommissionRate->InvestorRange << std::endl;
		std::cout << "经济公司代码： " << pInstrumentCommissionRate->BrokerID << std::endl;
		std::cout << "投资者代码： " << pInstrumentCommissionRate->InvestorID << std::endl;
		std::cout << "开仓手续费率： " << pInstrumentCommissionRate->OpenRatioByMoney << std::endl;
		std::cout << "开仓手续费： " << pInstrumentCommissionRate->OpenRatioByVolume << std::endl;
		std::cout << "平仓手续费率： " << pInstrumentCommissionRate->CloseRatioByMoney << std::endl;
		std::cout << "平仓手续费： " << pInstrumentCommissionRate->CloseRatioByVolume << std::endl;
		std::cout << "平今手续费率： " << pInstrumentCommissionRate->CloseTodayRatioByMoney << std::endl;
		std::cout << "平今手续费： " << pInstrumentCommissionRate->CloseTodayRatioByVolume << std::endl;
		std::cout << "交易所代码： " << pInstrumentCommissionRate->ExchangeID << std::endl;
		std::cout << "业务类型： " << pInstrumentCommissionRate->BizType << std::endl;
	}
	else
		std::cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// 请求查询合约保证金率
void WINAPI OnRspQryInstrumentMarginRate(
	CThostFtdcInstrumentMarginRateField* pInstrumentMarginRate, 
	CThostFtdcRspInfoField* pRspInfo, 
	int nRequestID, 
	bool bIsLast) 
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult)
	{
		g_reqQryInstrumentMarginRateOK = true;
		g_cond_va.notify_one();

		std::cout << "=====请求查询合约手续费信息响应=====" << std::endl;
		std::cout << "合约代码： " << pInstrumentMarginRate->InstrumentID << std::endl;
		std::cout << "投资者范围： " << pInstrumentMarginRate->InvestorRange << std::endl;
		std::cout << "经济公司代码： " << pInstrumentMarginRate->BrokerID << std::endl;
		std::cout << "投资者代码： " << pInstrumentMarginRate->InvestorID << std::endl;
		std::cout << "投机套保标志： " << pInstrumentMarginRate->HedgeFlag << std::endl;
		std::cout << "多头保证金率： " << pInstrumentMarginRate->LongMarginRatioByMoney << std::endl;
		std::cout << "多头保证金费： " << pInstrumentMarginRate->LongMarginRatioByVolume << std::endl;
		std::cout << "空头保证金率： " << pInstrumentMarginRate->ShortMarginRatioByMoney << std::endl;
		std::cout << "空头保证金： " << pInstrumentMarginRate->ShortMarginRatioByVolume << std::endl;
		std::cout << "是否相对交易所收取： " << pInstrumentMarginRate->IsRelative << std::endl;
		std::cout << "交易所代码： " << pInstrumentMarginRate->ExchangeID << std::endl;
		std::cout << "投资单元代码： " << pInstrumentMarginRate->InvestUnitID << std::endl;
	}
	else
		std::cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// 请求查询交易者编号
void WINAPI OnRspQryTradingCode(
	CThostFtdcTradingCodeField* pTradingCode, 
	CThostFtdcRspInfoField* pRspInfo, 
	int nRequestID, 
	bool bIsLast) 
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult) 
	{
		g_reqQryTradingCodeOK = true;
		g_cond_va.notify_one();

		std::cout << "=====请求查询交易者编号信息响应=====" << std::endl;
		std::cout << "投资者编号： " << pTradingCode->InvestorID << std::endl;
		std::cout << "经济公司代码： " << pTradingCode->BrokerID << std::endl;
		std::cout << "交易所代码： " << pTradingCode->ExchangeID << std::endl;
		std::cout << "客户端代码： " << pTradingCode->ClientID << std::endl;
		std::cout << "是否激活： " << pTradingCode->IsActive << std::endl;
		std::cout << "交易编码类型： " << pTradingCode->ClientIDType << std::endl;
		std::cout << "营业部编号： " << pTradingCode->BranchID << std::endl;
		std::cout << "业务类型： " << pTradingCode->BizType << std::endl;
	}
	else
		std::cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// 请求查询投资者响应
void WINAPI OnRspQryInvestor(
	CThostFtdcInvestorField* pInvestor, 
	CThostFtdcRspInfoField* pRspInfo, 
	int nRequestID, 
	bool bIsLast) 
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult)
	{
		g_reqQryInvestorOK = true;
		g_cond_va.notify_one();

		std::cout << "=====请求查询投资者响应=====" << std::endl;
		std::cout << "投资者编号： " << pInvestor->InvestorID << std::endl;
		std::cout << "经济公司代码： " << pInvestor->BrokerID << std::endl;
		std::cout << "投资者分组代码： " << pInvestor->InvestorGroupID << std::endl;
		std::cout << "投资者名称： " << pInvestor->InvestorName << std::endl;
		std::cout << "证件类型： " << pInvestor->IdentifiedCardType << std::endl;
		std::cout << "证件号码： " << pInvestor->IdentifiedCardNo << std::endl;
		std::cout << "是否激活： " << pInvestor->IsActive << std::endl;
		std::cout << "联系电话： " << pInvestor->Telephone << std::endl;
	}
	else
		std::cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// 查询资金账户响应
void WINAPI OnRspQryTradingAccount(
	CThostFtdcTradingAccountField* pTradingAccount, 
	CThostFtdcRspInfoField* pRspInfo, 
	int nRequestID, 
	bool bIsLast) 
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult)
	{
		g_reqQryTradingAccountOK = true;
		g_cond_va.notify_one();

		std::cout << "=====查询资金账户响应=====" << std::endl;		
		std::cout << "经济公司代码： " << pTradingAccount->BrokerID << std::endl;
		std::cout << "投资者账户： " << pTradingAccount->AccountID << std::endl;
		std::cout << "上次质押金额： " << pTradingAccount->PreMortgage << std::endl;
		std::cout << "上次信用额度： " << pTradingAccount->PreCredit << std::endl;
		std::cout << "上次存款额度： " << pTradingAccount->PreDeposit << std::endl;
		std::cout << "上次结算保证金： " << pTradingAccount->PreBalance << std::endl;
		std::cout << "上次占用的保证金： " << pTradingAccount->PreMargin << std::endl;
		std::cout << "利息基数： " << pTradingAccount->InterestBase << std::endl;
		std::cout << "利息收入： " << pTradingAccount->Interest << std::endl;
		std::cout << "入金金额： " << pTradingAccount->Deposit << std::endl;
		std::cout << "出金金额： " << pTradingAccount->Withdraw << std::endl;
		std::cout << "冻结保证金： " << pTradingAccount->FrozenMargin << std::endl;
		std::cout << "冻结资金： " << pTradingAccount->FrozenCash << std::endl;
		std::cout << "冻结的手续费： " << pTradingAccount->FrozenCommission << std::endl;
		std::cout << "当前的保证金： " << pTradingAccount->CurrMargin << std::endl;
	}
	else
		std::cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;

}

// 请求查询投资者持仓
void WINAPI OnRspQryInvestorPosition(
	CThostFtdcInvestorPositionField* pInvestorPosition, 
	CThostFtdcRspInfoField* pRspInfo, 
	int nRequestID, 
	bool bIsLast) 
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult)
	{
		g_reqQryInvestorPositionOK = true;
		g_cond_va.notify_one();

		std::cout << "=====请求查询投资者持仓响应=====" << std::endl;
		std::cout << "合约代码： " << pInvestorPosition->InstrumentID << std::endl;
		std::cout << "经济公司代码： " << pInvestorPosition->BrokerID << std::endl;
		std::cout << "投资者代码： " << pInvestorPosition->InvestorID << std::endl;
		std::cout << "持仓多空方向： " << pInvestorPosition->PosiDirection << std::endl;
		std::cout << "投机套保标志： " << pInvestorPosition->HedgeFlag << std::endl;
		std::cout << "持仓日期： " << pInvestorPosition->PositionDate << std::endl;
		std::cout << "上日持仓： " << pInvestorPosition->YdPosition << std::endl;
		std::cout << "多日持仓： " << pInvestorPosition->Position << std::endl;
		std::cout << "多头冻结： " << pInvestorPosition->LongFrozen << std::endl;
		
	}
	else
		std::cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// 请求查询交易响应
void WINAPI OnRspQryTrade(
	CThostFtdcTradeField* pTrade, 
	CThostFtdcRspInfoField* pRspInfo, 
	int nRequestID, 
	bool bIsLast) 
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult)
	{
		g_reqQryTradeOK = true;
		g_cond_va.notify_one();

		std::cout << "=====请求查询交易响应=====" << std::endl;
		std::cout << "经济公司代码： " << pTrade->BrokerID << std::endl;
		std::cout << "投资者代码： " << pTrade->InvestorID << std::endl;
		std::cout << "合约代码： " << pTrade->InstrumentID << std::endl;
		std::cout << "报单引用 ： " << pTrade->OrderRef << std::endl;
		std::cout << "用户代码： " << pTrade->UserID << std::endl;
		std::cout << "交易所代码： " << pTrade->ExchangeID << std::endl;
		std::cout << "成交编号： " << pTrade->TradeID << std::endl;
		std::cout << "买卖方向： " << pTrade->Direction << std::endl;
		std::cout << "报单编号： " << pTrade->OrderSysID << std::endl;
		std::cout << "会员代码： " << pTrade->ParticipantID << std::endl;
		std::cout << "客户代码： " << pTrade->ClientID << std::endl;
		std::cout << "交易角色： " << pTrade->TradingRole << std::endl;
	}
	else
		std::cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// 错误通知
void WINAPI OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (bResult)
		std::cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

#pragma endregion 

void Init() 
{
	cout << "连接交易服务器..." << endl;
	g_pTdApi = CreateFtdcTraderApi();   // 创建行情实例
	g_pTdSpi = CreateTraderSpi();
	g_pTdApi->RegisterSpi(g_pTdSpi);

	g_pTdApi->SubscribePrivateTopic(THOST_TERT_RESUME);		// 订阅私有流
	g_pTdApi->SubscribePublicTopic(THOST_TERT_RESUME);		// 订阅公有流

	g_pTdApi->RegisterFront(gTradeFrontAddr);				// 设置行情前置地址

	RegOnFrontConnected(g_pTdSpi, OnFrontConnected);
	RegOnFrontDisconnected(g_pTdSpi, OnFrontDisconnected);

	RegOnHeartBeatWarning(g_pTdSpi, OnHeartBeatWarning);

}

void Release() {
	g_pTdApi->Release();
	g_pTdApi = NULL;
}

TEST(CtpTdApiWrapper, 01Init)
{
	Init();
	g_CtpTdApiWrapperParams = { '\0' };
	g_pTdApi->Init();
	
	std::unique_lock<mutex> lck(g_mtx);
	g_cond_va.wait_for(lck, std::chrono::seconds(5), []() -> bool{ return g_initOK; });

	EXPECT_TRUE(g_pTdSpi != NULL);
	EXPECT_TRUE(g_pTdApi != NULL);
	EXPECT_TRUE(g_initOK);

	Release();
}

TEST(CtpTdApiWrapper, 02Auth)
{
	Init();
	g_CtpTdApiWrapperParams = { '\0' };
	g_CtpTdApiWrapperParams.isAuth = true;

	RegRspAuthenticate(g_pTdSpi, OnRspAuthenticate);	

	g_pTdApi->Init();

	std::unique_lock<mutex> lck(g_mtx);
	g_cond_va.wait_for(lck, std::chrono::seconds(5), []() -> bool { return g_initOK && g_authOK; });

	EXPECT_TRUE(g_pTdSpi != NULL);
	EXPECT_TRUE(g_pTdApi != NULL);
	EXPECT_TRUE(g_initOK);
	EXPECT_TRUE(g_authOK);

	Release();
}

TEST(CtpTdApiWrapper, 03Login)
{
	Init();
	g_CtpTdApiWrapperParams = { '\0' };
	g_CtpTdApiWrapperParams.isLogin = true;

	RegRspUserLogin(g_pTdSpi, OnRspUserLogin);

	g_pTdApi->Init();

	std::unique_lock<mutex> lck(g_mtx);
	g_cond_va.wait_for(lck, std::chrono::seconds(5), []() -> bool { return g_initOK && g_loginOK; });

	EXPECT_TRUE(g_pTdSpi != NULL);
	EXPECT_TRUE(g_pTdApi != NULL);
	EXPECT_TRUE(g_initOK);
	EXPECT_TRUE(g_loginOK);

	Release();
}

TEST(CtpTdApiWrapper, 04Logout)
{
	Init();
	g_CtpTdApiWrapperParams = { '\0' };
	g_CtpTdApiWrapperParams.isLogin = true;
	g_CtpTdApiWrapperParams.isLogout = true;

	RegRspUserLogin(g_pTdSpi, OnRspUserLogin);
	RegRspUserLogout(g_pTdSpi, OnRspUserLogout);

	g_pTdApi->Init();

	std::unique_lock<mutex> lck(g_mtx);
	g_cond_va.wait_for(lck, std::chrono::seconds(5), []() -> bool { return g_initOK && g_loginOK && g_logoutOK; });

	EXPECT_TRUE(g_pTdSpi != NULL);
	EXPECT_TRUE(g_pTdApi != NULL);
	EXPECT_TRUE(g_initOK);
	EXPECT_TRUE(g_loginOK);
	EXPECT_TRUE(g_logoutOK);

	Release();
}

TEST(CtpTdApiWrapper, 05UpdateLoginPwd)
{
	Init();
	g_CtpTdApiWrapperParams = { '\0' };
	g_CtpTdApiWrapperParams.isLogin = true;
	g_CtpTdApiWrapperParams.isUpdateLoginPwd = true;

	RegRspUserLogin(g_pTdSpi, OnRspUserLogin);
	RegRspUserPasswordUpdate(g_pTdSpi, OnRspUserPasswordUpdate);

	g_pTdApi->Init();

	std::unique_lock<mutex> lck(g_mtx);
	g_cond_va.wait_for(lck, std::chrono::seconds(5), []() -> bool { return g_initOK && g_loginOK && g_updateLoginPwdOK; });

	EXPECT_TRUE(g_pTdSpi != NULL);
	EXPECT_TRUE(g_pTdApi != NULL);
	EXPECT_TRUE(g_initOK);
	EXPECT_TRUE(g_loginOK);
	EXPECT_TRUE(g_updateLoginPwdOK);

	Release();
}


TEST(CtpTdApiWrapper, 06UpdateTrdAccountPwd)
{
	Init();
	g_CtpTdApiWrapperParams = { '\0' };
	g_CtpTdApiWrapperParams.isLogin = true;
	g_CtpTdApiWrapperParams.isUpdateTrdAccountPwd = true;

	RegRspUserLogin(g_pTdSpi, OnRspUserLogin);
	RegRspTradingAccountPasswordUpdate(g_pTdSpi, OnRspTradingAccountPasswordUpdate);

	g_pTdApi->Init();

	std::unique_lock<mutex> lck(g_mtx);
	g_cond_va.wait_for(lck, std::chrono::seconds(5), []() -> bool { return g_initOK && g_loginOK && g_updateTrdAccountPwdOK; });

	EXPECT_TRUE(g_pTdSpi != NULL);
	EXPECT_TRUE(g_pTdApi != NULL);
	EXPECT_TRUE(g_initOK);
	EXPECT_TRUE(g_loginOK);
	EXPECT_TRUE(g_updateTrdAccountPwdOK);

	Release();
}

// 报单
TEST(CtpTdApiWrapper, 07OrderInsert)
{
	Init();
	g_CtpTdApiWrapperParams = { '\0' };
	g_CtpTdApiWrapperParams.isLogin = true;
	g_CtpTdApiWrapperParams.isOrderInsert = true;

	RegRspUserLogin(g_pTdSpi, OnRspUserLogin);
	RegRspOrderInsert(g_pTdSpi, OnRspInsertOrder);
	RegErrRtnOrderInsert(g_pTdSpi, OnErrRtnOrderInsert);
	RegRtnOrder(g_pTdSpi, OnRtnOrder);
	RegRtnTrade(g_pTdSpi, OnRtnTrade);


	g_pTdApi->Init();

	std::unique_lock<mutex> lck(g_mtx);
	g_cond_va.wait_for(lck, std::chrono::seconds(5), []() -> bool { return g_initOK && g_loginOK && g_orderInsertOK; });

	EXPECT_TRUE(g_pTdSpi != NULL);
	EXPECT_TRUE(g_pTdApi != NULL);
	EXPECT_TRUE(g_initOK);
	EXPECT_TRUE(g_loginOK);
	EXPECT_TRUE(g_orderInsertOK);

	Release();
}

// 预埋单
TEST(CtpTdApiWrapper, 08ParkedOrderInsert)
{
	Init();
	g_CtpTdApiWrapperParams = { '\0' };
	g_CtpTdApiWrapperParams.isLogin = true;
	g_CtpTdApiWrapperParams.isParkedOrderInsert = true;

	RegRspUserLogin(g_pTdSpi, OnRspUserLogin);
	RegRspParkedOrderInsert(g_pTdSpi, OnRspParkedOrderInsert);

	g_pTdApi->Init();

	std::unique_lock<mutex> lck(g_mtx);
	g_cond_va.wait_for(lck, std::chrono::seconds(5), []() -> bool { return g_initOK && g_loginOK && g_parkedOrderInsertOK; });

	EXPECT_TRUE(g_pTdSpi != NULL);
	EXPECT_TRUE(g_pTdApi != NULL);
	EXPECT_TRUE(g_initOK);
	EXPECT_TRUE(g_loginOK);
	EXPECT_TRUE(g_parkedOrderInsertOK);

	Release();
}

// 预埋撤单
TEST(CtpTdApiWrapper, 09ParkedOrderAction)
{
	Init();
	g_CtpTdApiWrapperParams = { '\0' };
	g_CtpTdApiWrapperParams.isLogin = true;
	g_CtpTdApiWrapperParams.isParkedOrderInsert = true;
	g_CtpTdApiWrapperParams.isParkedOrderAction = true;

	RegRspUserLogin(g_pTdSpi, OnRspUserLogin);
	RegRspParkedOrderInsert(g_pTdSpi, OnRspParkedOrderInsert);
	RegRspParkedOrderAction(g_pTdSpi, OnRspParkedOrderAction);

	g_pTdApi->Init();

	std::unique_lock<mutex> lck(g_mtx);
	g_cond_va.wait_for(lck, std::chrono::seconds(5), []() -> bool { return g_initOK && g_loginOK && g_parkedOrderInsertOK && g_parkedOrderActionOK; });

	EXPECT_TRUE(g_pTdSpi != NULL);
	EXPECT_TRUE(g_pTdApi != NULL);
	EXPECT_TRUE(g_initOK);
	EXPECT_TRUE(g_loginOK);
	EXPECT_TRUE(g_parkedOrderInsertOK);

	Release();
}

// 预埋单撤单
TEST(CtpTdApiWrapper, 10RemoveParkedOrder)
{
	Init();
	g_CtpTdApiWrapperParams = { '\0' };
	g_CtpTdApiWrapperParams.isLogin = true;
	g_CtpTdApiWrapperParams.isParkedOrderInsert = true;
	g_CtpTdApiWrapperParams.isParkedOrderAction = true;

	RegRspUserLogin(g_pTdSpi, OnRspUserLogin);
	RegRspParkedOrderInsert(g_pTdSpi, OnRspParkedOrderInsert);	

	g_pTdApi->Init();

	std::unique_lock<mutex> lck(g_mtx);
	g_cond_va.wait_for(lck, std::chrono::seconds(5), []() -> bool { return g_initOK && g_loginOK && g_parkedOrderInsertOK && g_removeParkedOrderOK; });

	EXPECT_TRUE(g_pTdSpi != NULL);
	EXPECT_TRUE(g_pTdApi != NULL);
	EXPECT_TRUE(g_initOK);
	EXPECT_TRUE(g_loginOK);
	EXPECT_TRUE(g_parkedOrderInsertOK);

	Release();
}

// 撤单操作
TEST(CtpTdApiWrapper, 12OrderAction)
{
	Init();
	g_CtpTdApiWrapperParams = { '\0' };
	g_CtpTdApiWrapperParams.isLogin = true;
	g_CtpTdApiWrapperParams.isOrderInsert = true;
	g_CtpTdApiWrapperParams.isOrderAction = true;

	RegRspUserLogin(g_pTdSpi, OnRspUserLogin);
	RegRspOrderInsert(g_pTdSpi, OnRspInsertOrder);
	RegErrRtnOrderInsert(g_pTdSpi, OnErrRtnOrderInsert);
	RegRtnOrder(g_pTdSpi, OnRtnOrder);
	RegRtnTrade(g_pTdSpi, OnRtnTrade);

	g_pTdApi->Init();

	std::unique_lock<mutex> lck(g_mtx);
	g_cond_va.wait_for(lck, std::chrono::seconds(5), []() -> bool { return g_initOK && g_loginOK && g_orderInsertOK && g_orderActionOK; });

	EXPECT_TRUE(g_pTdSpi != NULL);
	EXPECT_TRUE(g_pTdApi != NULL);
	EXPECT_TRUE(g_initOK);
	EXPECT_TRUE(g_loginOK);
	EXPECT_TRUE(g_orderInsertOK);
	EXPECT_TRUE(g_orderActionOK);

	Release();
}

// 请求查询报单
TEST(CtpTdApiWrapper, 13ReqQryOrder)
{
	Init();
	g_CtpTdApiWrapperParams = { '\0' };
	g_CtpTdApiWrapperParams.isLogin = true;
	g_CtpTdApiWrapperParams.isQryOrder = true;

	RegRspUserLogin(g_pTdSpi, OnRspUserLogin);
	RegRspQryOrder(g_pTdSpi, OnRspQryOrder);	

	g_pTdApi->Init();

	std::unique_lock<mutex> lck(g_mtx);
	g_cond_va.wait_for(lck, std::chrono::seconds(5), []() -> bool { return g_initOK && g_loginOK && g_qryOrderOK; });

	EXPECT_TRUE(g_pTdSpi != NULL);
	EXPECT_TRUE(g_pTdApi != NULL);
	EXPECT_TRUE(g_initOK);
	EXPECT_TRUE(g_loginOK);
	EXPECT_TRUE(g_qryOrderOK);

	Release();
}

// 查询最大报单量
TEST(CtpTdApiWrapper, 14ReqQueryMaxOrderVolume)
{
	Init();
	g_CtpTdApiWrapperParams = { '\0' };
	g_CtpTdApiWrapperParams.isLogin = true;
	g_CtpTdApiWrapperParams.isQueryMaxOrderVolume = true;

	RegRspUserLogin(g_pTdSpi, OnRspUserLogin);
	RegRspQueryMaxOrderVolume(g_pTdSpi, OnRspQueryMaxOrderVolume);

	g_pTdApi->Init();

	std::unique_lock<mutex> lck(g_mtx);
	g_cond_va.wait_for(lck, std::chrono::seconds(5), []() -> bool { return g_initOK && g_loginOK && g_queryMaxOrderVolumeOK; });

	EXPECT_TRUE(g_pTdSpi != NULL);
	EXPECT_TRUE(g_pTdApi != NULL);
	EXPECT_TRUE(g_initOK);
	EXPECT_TRUE(g_loginOK);
	EXPECT_TRUE(g_queryMaxOrderVolumeOK);

	Release();
}

// 投资者结算结果确认
TEST(CtpTdApiWrapper, 15ReqSettlementInfoConfirm)
{
	Init();
	g_CtpTdApiWrapperParams = { '\0' };
	g_CtpTdApiWrapperParams.isLogin = true;
	g_CtpTdApiWrapperParams.isSettlementInfoConfirm = true;

	RegRspUserLogin(g_pTdSpi, OnRspUserLogin);
	RegRspSettlementInfoConfirm(g_pTdSpi, OnReqSettlementInfoConfirm);

	g_pTdApi->Init();

	std::unique_lock<mutex> lck(g_mtx);
	g_cond_va.wait_for(lck, std::chrono::seconds(5), []() -> bool { return g_initOK && g_loginOK && g_settlementInfoConfirmOK; });

	EXPECT_TRUE(g_pTdSpi != NULL);
	EXPECT_TRUE(g_pTdApi != NULL);
	EXPECT_TRUE(g_initOK);
	EXPECT_TRUE(g_loginOK);
	EXPECT_TRUE(g_settlementInfoConfirmOK);

	Release();
}

// 询价 （OnRtnForQuoteRsp：该接口暂时不可用）
TEST(CtpTdApiWrapper, 16ForQuoteInsert)
{
	Init();
	g_CtpTdApiWrapperParams = { '\0' };
	g_CtpTdApiWrapperParams.isLogin = true;
	g_CtpTdApiWrapperParams.isForQuoteInsert = true;

	RegRspUserLogin(g_pTdSpi, OnRspUserLogin);
	RegRspQryForQuote(g_pTdSpi, OnRspForQuoteInsert);

	g_pTdApi->Init();

	std::unique_lock<mutex> lck(g_mtx);
	g_cond_va.wait_for(lck, std::chrono::seconds(5), []() -> bool { return g_initOK && g_loginOK && g_forQuoteInsertOK; });

	EXPECT_TRUE(g_pTdSpi != NULL);
	EXPECT_TRUE(g_pTdApi != NULL);
	EXPECT_TRUE(g_initOK);
	EXPECT_TRUE(g_loginOK);
	EXPECT_TRUE(g_forQuoteInsertOK);

	Release();
}

// 查询报价
TEST(CtpTdApiWrapper, 17QryQuote)
{
	Init();
	g_CtpTdApiWrapperParams = { '\0' };
	g_CtpTdApiWrapperParams.isLogin = true;
	g_CtpTdApiWrapperParams.isOrderInsert = true;
	g_CtpTdApiWrapperParams.isQryQuote = true;

	RegRspUserLogin(g_pTdSpi, OnRspUserLogin);
	RegRspOrderInsert(g_pTdSpi, OnRspInsertOrder);
	RegErrRtnOrderInsert(g_pTdSpi, OnErrRtnOrderInsert);
	RegRtnOrder(g_pTdSpi, OnRtnOrder);
	RegRtnTrade(g_pTdSpi, OnRtnTrade);
	RegRspQryQuote(g_pTdSpi, OnRspQryQuote);

	g_pTdApi->Init();

	std::unique_lock<mutex> lck(g_mtx);
	g_cond_va.wait_for(lck, std::chrono::seconds(5), []() -> bool { return g_initOK && g_loginOK && g_orderInsertOK && g_qryQuoteOK; });

	EXPECT_TRUE(g_pTdSpi != NULL);
	EXPECT_TRUE(g_pTdApi != NULL);
	EXPECT_TRUE(g_initOK);
	EXPECT_TRUE(g_loginOK);
	EXPECT_TRUE(g_qryQuoteOK);

	Release();
}

// 申请组合查询
TEST(CtpTdApiWrapper, 18QryCombAction)
{
	Init();
	g_CtpTdApiWrapperParams = { '\0' };
	g_CtpTdApiWrapperParams.isLogin = true;
	g_CtpTdApiWrapperParams.isQryCombAction = true;	

	RegRspUserLogin(g_pTdSpi, OnRspUserLogin);
	RegRspQryCombAction(g_pTdSpi, OnRspQryCombAction);
	
	g_pTdApi->Init();

	std::unique_lock<mutex> lck(g_mtx);
	g_cond_va.wait_for(lck, std::chrono::seconds(5), []() -> bool { return g_initOK && g_loginOK && g_qryCombActionOK; });

	EXPECT_TRUE(g_pTdSpi != NULL);
	EXPECT_TRUE(g_pTdApi != NULL);
	EXPECT_TRUE(g_initOK);
	EXPECT_TRUE(g_loginOK);
	EXPECT_TRUE(g_qryCombActionOK);

	Release();
}

// 查询组合合约安全系数（暂时不会回调）
TEST(CtpTdApiWrapper, 19QryCombInstrumentGuard)
{
	Init();
	g_CtpTdApiWrapperParams = { '\0' };
	g_CtpTdApiWrapperParams.isLogin = true;
	g_CtpTdApiWrapperParams.isQryCombInstrumentGuard = true;

	RegRspUserLogin(g_pTdSpi, OnRspUserLogin);
	RegRspQryCombInstrumentGuard(g_pTdSpi, OnRspQryCombInstrumentGuard);

	g_pTdApi->Init();

	std::unique_lock<mutex> lck(g_mtx);
	g_cond_va.wait_for(lck, std::chrono::seconds(5), []() -> bool { return g_initOK && g_loginOK && g_qryCombInstrumentGuardOK; });

	EXPECT_TRUE(g_pTdSpi != NULL);
	EXPECT_TRUE(g_pTdApi != NULL);
	EXPECT_TRUE(g_initOK);
	EXPECT_TRUE(g_loginOK);
	EXPECT_TRUE(g_qryCombInstrumentGuardOK);

	Release();
}

// 请求查询转账流水
TEST(CtpTdApiWrapper, 20QryTransferSerial)
{
	Init();
	g_CtpTdApiWrapperParams = { '\0' };
	g_CtpTdApiWrapperParams.isLogin = true;
	g_CtpTdApiWrapperParams.isQryTransferSerial = true;

	RegRspUserLogin(g_pTdSpi, OnRspUserLogin);
	RegRspQryTransferSerial(g_pTdSpi, OnRspQryTransferSerial);

	g_pTdApi->Init();

	std::unique_lock<mutex> lck(g_mtx);
	g_cond_va.wait_for(lck, std::chrono::seconds(5), []() -> bool { return g_initOK && g_loginOK && g_qryTransferSerialOK; });

	EXPECT_TRUE(g_pTdSpi != NULL);
	EXPECT_TRUE(g_pTdApi != NULL);
	EXPECT_TRUE(g_initOK);
	EXPECT_TRUE(g_loginOK);
	EXPECT_TRUE(g_qryTransferSerialOK);

	Release();
}

// 查询银期签约关系
TEST(CtpTdApiWrapper, 21QryAccountregister)
{
	Init();
	g_CtpTdApiWrapperParams = { '\0' };
	g_CtpTdApiWrapperParams.isLogin = true;
	g_CtpTdApiWrapperParams.isQryAccountregister = true;

	RegRspUserLogin(g_pTdSpi, OnRspUserLogin);
	RegRspQryAccountregister(g_pTdSpi, OnRspQryAccountregister);

	g_pTdApi->Init();

	std::unique_lock<mutex> lck(g_mtx);
	g_cond_va.wait_for(lck, std::chrono::seconds(5), []() -> bool { return g_initOK && g_loginOK && g_qryAccountregisterOK; });

	EXPECT_TRUE(g_pTdSpi != NULL);
	EXPECT_TRUE(g_pTdApi != NULL);
	EXPECT_TRUE(g_initOK);
	EXPECT_TRUE(g_loginOK);
	EXPECT_TRUE(g_qryAccountregisterOK);

	Release();
}

// 合约交易状态通知
TEST(CtpTdApiWrapper, 22RtnInstrumentStatus)
{
	Init();
	g_CtpTdApiWrapperParams = { '\0' };
	g_CtpTdApiWrapperParams.isLogin = true;
	g_CtpTdApiWrapperParams.isOrderInsert = true;
	
	RegRspUserLogin(g_pTdSpi, OnRspUserLogin);
	RegRspOrderInsert(g_pTdSpi, OnRspInsertOrder);
	RegErrRtnOrderInsert(g_pTdSpi, OnErrRtnOrderInsert);
	RegRtnOrder(g_pTdSpi, OnRtnOrder);
	RegRtnTrade(g_pTdSpi, OnRtnTrade);
	RegRtnInstrumentStatus(g_pTdSpi, OnRtnInstrumentStatus);

	g_pTdApi->Init();

	std::unique_lock<mutex> lck(g_mtx);
	g_cond_va.wait_for(lck, std::chrono::seconds(5), []() -> bool { return g_initOK && g_loginOK && g_orderInsertOK && g_instrumentStatusOK; });

	EXPECT_TRUE(g_pTdSpi != NULL);
	EXPECT_TRUE(g_pTdApi != NULL);
	EXPECT_TRUE(g_initOK);
	EXPECT_TRUE(g_loginOK);
	EXPECT_TRUE(g_orderInsertOK);
	EXPECT_TRUE(g_instrumentStatusOK);

	Release();
}

// 交易通知 （会报结算结构未确认错误）
TEST(CtpTdApiWrapper, 22RtnTradingNotice)
{
	Init();
	g_CtpTdApiWrapperParams = { '\0' };
	g_CtpTdApiWrapperParams.isLogin = true;
	g_CtpTdApiWrapperParams.isOrderInsert = true;

	RegRspUserLogin(g_pTdSpi, OnRspUserLogin);
	RegRspOrderInsert(g_pTdSpi, OnRspInsertOrder);
	RegErrRtnOrderInsert(g_pTdSpi, OnErrRtnOrderInsert);
	RegRtnOrder(g_pTdSpi, OnRtnOrder);
	RegRtnTrade(g_pTdSpi, OnRtnTrade);
	RegRtnTradingNotice(g_pTdSpi, OnRtnTradingNotice);

	g_pTdApi->Init();

	std::unique_lock<mutex> lck(g_mtx);
	g_cond_va.wait_for(lck, std::chrono::seconds(5), []() -> bool { return g_initOK && g_loginOK && g_orderInsertOK && g_TradingNoticeOK; });

	EXPECT_TRUE(g_pTdSpi != NULL);
	EXPECT_TRUE(g_pTdApi != NULL);
	EXPECT_TRUE(g_initOK);
	EXPECT_TRUE(g_loginOK);
	EXPECT_TRUE(g_orderInsertOK);
	EXPECT_TRUE(g_TradingNoticeOK);

	Release();
}

// 查询签约银行响应
TEST(CtpTdApiWrapper, 23QryContractBank)
{
	Init();
	g_CtpTdApiWrapperParams = { '\0' };
	g_CtpTdApiWrapperParams.isLogin = true;
	g_CtpTdApiWrapperParams.isQryContractBank = true;

	RegRspUserLogin(g_pTdSpi, OnRspUserLogin);	
	RegRspQryContractBank(g_pTdSpi, OnRspQryContractBank);

	g_pTdApi->Init();

	std::unique_lock<mutex> lck(g_mtx);
	g_cond_va.wait_for(lck, std::chrono::seconds(5), []() -> bool { return g_initOK && g_loginOK && g_qryContractBankOK; });

	EXPECT_TRUE(g_pTdSpi != NULL);
	EXPECT_TRUE(g_pTdApi != NULL);
	EXPECT_TRUE(g_initOK);
	EXPECT_TRUE(g_loginOK);	
	EXPECT_TRUE(g_qryContractBankOK);

	Release();
}

// 查询预埋单响应
TEST(CtpTdApiWrapper, 24QryParkedOrder)
{
	Init();
	g_CtpTdApiWrapperParams = { '\0' };
	g_CtpTdApiWrapperParams.isLogin = true;
	g_CtpTdApiWrapperParams.isQryParkedOrder = true;

	RegRspUserLogin(g_pTdSpi, OnRspUserLogin);
	RegRspQryParkedOrder(g_pTdSpi, OnRspQryParkedOrder);

	g_pTdApi->Init();

	std::unique_lock<mutex> lck(g_mtx);
	g_cond_va.wait_for(lck, std::chrono::seconds(5), []() -> bool { return g_initOK && g_loginOK && g_qryParkedOrderOK; });

	EXPECT_TRUE(g_pTdSpi != NULL);
	EXPECT_TRUE(g_pTdApi != NULL);
	EXPECT_TRUE(g_initOK);
	EXPECT_TRUE(g_loginOK);
	EXPECT_TRUE(g_qryParkedOrderOK);

	Release();
}

// 请求查询预埋单撤单响应
TEST(CtpTdApiWrapper, 25QryParkedOrderAction)
{
	Init();
	g_CtpTdApiWrapperParams = { '\0' };
	g_CtpTdApiWrapperParams.isLogin = true;
	g_CtpTdApiWrapperParams.isQryParkedOrderAction = true;

	RegRspUserLogin(g_pTdSpi, OnRspUserLogin);
	RegRspQryParkedOrderAction(g_pTdSpi, OnRspQryParkedOrderAction);

	g_pTdApi->Init();

	std::unique_lock<mutex> lck(g_mtx);
	g_cond_va.wait_for(lck, std::chrono::seconds(5), []() -> bool { return g_initOK && g_loginOK && g_qryParkedOrderActionOK; });

	EXPECT_TRUE(g_pTdSpi != NULL);
	EXPECT_TRUE(g_pTdApi != NULL);
	EXPECT_TRUE(g_initOK);
	EXPECT_TRUE(g_loginOK);
	EXPECT_TRUE(g_qryParkedOrderActionOK);

	Release();
}

// 查询交易通知
TEST(CtpTdApiWrapper, 26QryTradingNotice)
{
	Init();
	g_CtpTdApiWrapperParams = { '\0' };
	g_CtpTdApiWrapperParams.isLogin = true;
	g_CtpTdApiWrapperParams.isQryTradingNotice = true;

	RegRspUserLogin(g_pTdSpi, OnRspUserLogin);
	RegRspQryTradingNotice(g_pTdSpi, OnRspQryTradingNotice);

	g_pTdApi->Init();

	std::unique_lock<mutex> lck(g_mtx);
	g_cond_va.wait_for(lck, std::chrono::seconds(5), []() -> bool { return g_initOK && g_loginOK && g_qryTradingNoticeOK; });

	EXPECT_TRUE(g_pTdSpi != NULL);
	EXPECT_TRUE(g_pTdApi != NULL);
	EXPECT_TRUE(g_initOK);
	EXPECT_TRUE(g_loginOK);
	EXPECT_TRUE(g_qryTradingNoticeOK);

	Release();
}

// 查询经济公司交易参数
TEST(CtpTdApiWrapper, 27QryBrokerTradingParams)
{
	Init();
	g_CtpTdApiWrapperParams = { '\0' };
	g_CtpTdApiWrapperParams.isLogin = true;
	g_CtpTdApiWrapperParams.isQryBrokerTradingParams = true;

	RegRspUserLogin(g_pTdSpi, OnRspUserLogin);
	RegRspQryBrokerTradingParams(g_pTdSpi, OnRspQryBrokerTradingParams);

	g_pTdApi->Init();

	std::unique_lock<mutex> lck(g_mtx);
	g_cond_va.wait_for(lck, std::chrono::seconds(5), []() -> bool { return g_initOK && g_loginOK && g_qryBrokerTradingParamsOK; });

	EXPECT_TRUE(g_pTdSpi != NULL);
	EXPECT_TRUE(g_pTdApi != NULL);
	EXPECT_TRUE(g_initOK);
	EXPECT_TRUE(g_loginOK);
	EXPECT_TRUE(g_qryBrokerTradingParamsOK);

	Release();
}

// 查询经济公司的交易算法
 TEST(CtpTdApiWrapper, 28QryBrokerTradingAlgos)
{
	Init();
	g_CtpTdApiWrapperParams = { '\0' };
	g_CtpTdApiWrapperParams.isLogin = true;
	g_CtpTdApiWrapperParams.isQryBrokerTradingAlgos = true;

	RegRspUserLogin(g_pTdSpi, OnRspUserLogin);
	RegRspQryBrokerTradingAlgos(g_pTdSpi, OnRspQryBrokerTradingAlgos);

	g_pTdApi->Init();

	std::unique_lock<mutex> lck(g_mtx);
	g_cond_va.wait_for(lck, std::chrono::seconds(5), []() -> bool { return g_initOK && g_loginOK && g_qryBrokerTradingAlgosOK; });

	EXPECT_TRUE(g_pTdSpi != NULL);
	EXPECT_TRUE(g_pTdApi != NULL);
	EXPECT_TRUE(g_initOK);
	EXPECT_TRUE(g_loginOK);
	EXPECT_TRUE(g_qryBrokerTradingAlgosOK);

	Release();
}

// 期货发起查询银行余额（资金账户不存在，请求会失败）
 TEST(CtpTdApiWrapper, 29QueryBankBalanceByFuture)
 {
	 Init();
	 g_CtpTdApiWrapperParams = { '\0' };
	 g_CtpTdApiWrapperParams.isLogin = true;
	 g_CtpTdApiWrapperParams.isQueryBankBalanceByFuture = true;

	 RegRspUserLogin(g_pTdSpi, OnRspUserLogin);
	 RegRtnQueryBankBalanceByFuture(g_pTdSpi, OnRtnQueryBankBalanceByFuture);
	 RegRspQueryBankAccountMoneyByFuture(g_pTdSpi, OnRspQueryBankAccountMoneyByFuture);
	 g_pTdApi->Init();

	 std::unique_lock<mutex> lck(g_mtx);
	 g_cond_va.wait_for(lck, std::chrono::seconds(5), []() -> bool { return g_initOK && g_loginOK && g_queryBankBalanceByFutureOK; });

	 EXPECT_TRUE(g_pTdSpi != NULL);
	 EXPECT_TRUE(g_pTdApi != NULL);
	 EXPECT_TRUE(g_initOK);
	 EXPECT_TRUE(g_loginOK);
	 EXPECT_TRUE(g_queryBankBalanceByFutureOK);

	 Release();
 }

 // 请求查询监控中心用户令牌 (该交易席位未连接到交易所)
 TEST(CtpTdApiWrapper, 30QueryCFMMCTradingAccountToken)
 {
	 Init();
	 g_CtpTdApiWrapperParams = { '\0' };
	 g_CtpTdApiWrapperParams.isLogin = true;
	 g_CtpTdApiWrapperParams.isQueryCFMMCTradingAccountToken = true;

	 RegRspUserLogin(g_pTdSpi, OnRspUserLogin);
	 RegRspQueryCFMMCTradingAccountToken(g_pTdSpi, OnRspQueryCFMMCTradingAccountToken);
	 RegRtnCFMMCTradingAccountToken(g_pTdSpi, OnRtnCFMMCTradingAccountToken);
	 g_pTdApi->Init();

	 std::unique_lock<mutex> lck(g_mtx);
	 g_cond_va.wait_for(lck, std::chrono::seconds(5), []() -> bool { return g_initOK && g_loginOK && g_queryCFMMCTradingAccountTokenOK; });

	 EXPECT_TRUE(g_pTdSpi != NULL);
	 EXPECT_TRUE(g_pTdApi != NULL);
	 EXPECT_TRUE(g_initOK);
	 EXPECT_TRUE(g_loginOK);
	 EXPECT_TRUE(g_queryCFMMCTradingAccountTokenOK);

	 Release();
 }

 // 期货发起银行资金转期货（资金账户不存在）
 TEST(CtpTdApiWrapper, 31ReqFromBankToFutureByFuture)
 {
	 Init();
	 g_CtpTdApiWrapperParams = { '\0' };
	 g_CtpTdApiWrapperParams.isLogin = true;
	 g_CtpTdApiWrapperParams.isReqFromBankToFutureByFuture = true;

	 RegRspUserLogin(g_pTdSpi, OnRspUserLogin);
	 RegRspFromBankToFutureByFuture(g_pTdSpi, OnRspFromBankToFutureByFuture);
	 g_pTdApi->Init();

	 std::unique_lock<mutex> lck(g_mtx);
	 g_cond_va.wait_for(lck, std::chrono::seconds(5), []() -> bool { return g_initOK && g_loginOK && g_reqFromBankToFutureByFutureOK; });

	 EXPECT_TRUE(g_pTdSpi != NULL);
	 EXPECT_TRUE(g_pTdApi != NULL);
	 EXPECT_TRUE(g_initOK);
	 EXPECT_TRUE(g_loginOK);
	 EXPECT_TRUE(g_reqFromBankToFutureByFutureOK);

	 Release();
 }

 // 期货发起期货资金转银行（资金账户不存在）
 TEST(CtpTdApiWrapper, 32ReqFromFutureToBankByFuture)
 {
	 Init();
	 g_CtpTdApiWrapperParams = { '\0' };
	 g_CtpTdApiWrapperParams.isLogin = true;
	 g_CtpTdApiWrapperParams.isReqFromFutureToBankByFuture = true;

	 RegRspUserLogin(g_pTdSpi, OnRspUserLogin);
	 RegRspFromFutureToBankByFuture(g_pTdSpi, OnRspFromBankToFutureByFuture);
	 g_pTdApi->Init();

	 std::unique_lock<mutex> lck(g_mtx);
	 g_cond_va.wait_for(lck, std::chrono::seconds(5), []() -> bool { return g_initOK && g_loginOK && g_reqFromFutureToBankByFutureOK; });

	 EXPECT_TRUE(g_pTdSpi != NULL);
	 EXPECT_TRUE(g_pTdApi != NULL);
	 EXPECT_TRUE(g_initOK);
	 EXPECT_TRUE(g_loginOK);
	 EXPECT_TRUE(g_reqFromFutureToBankByFutureOK);

	 Release();
 } 

 // 请求查询投资单元（一直没有回调）
 TEST(CtpTdApiWrapper, 33ReqQryInvestUnit)
 {
	 Init();
	 g_CtpTdApiWrapperParams = { '\0' };
	 g_CtpTdApiWrapperParams.isLogin = true;
	 g_CtpTdApiWrapperParams.isReqQryInvestUnit = true;

	 RegRspUserLogin(g_pTdSpi, OnRspUserLogin);
	 RegRspQryInvestUnit(g_pTdSpi, OnRspQryInvestUnit);
	 g_pTdApi->Init();

	 std::unique_lock<mutex> lck(g_mtx);
	 g_cond_va.wait_for(lck, std::chrono::seconds(5), []() -> bool { return g_initOK && g_loginOK && g_reqQryInvestUnitOK; });

	 EXPECT_TRUE(g_pTdSpi != NULL);
	 EXPECT_TRUE(g_pTdApi != NULL);
	 EXPECT_TRUE(g_initOK);
	 EXPECT_TRUE(g_loginOK);
	 EXPECT_TRUE(g_reqQryInvestUnitOK);

	 Release();
 }

 // 请求查询二级代理商信息
 TEST(CtpTdApiWrapper, 34ReqQrySecAgentTradeInfo)
 {
	 Init();
	 g_CtpTdApiWrapperParams = { '\0' };
	 g_CtpTdApiWrapperParams.isLogin = true;
	 g_CtpTdApiWrapperParams.isReqQrySecAgentTradeInfo = true;

	 RegRspUserLogin(g_pTdSpi, OnRspUserLogin);
	 RegRspQrySecAgentTradeInfo(g_pTdSpi, OnRspQrySecAgentTradeInfo);

	 g_pTdApi->Init();

	 std::unique_lock<mutex> lck(g_mtx);
	 g_cond_va.wait_for(lck, std::chrono::seconds(5), []() -> bool { return g_initOK && g_loginOK && g_reqQrySecAgentTradeInfoOK; });

	 EXPECT_TRUE(g_pTdSpi != NULL);
	 EXPECT_TRUE(g_pTdApi != NULL);
	 EXPECT_TRUE(g_initOK);
	 EXPECT_TRUE(g_loginOK);
	 EXPECT_TRUE(g_reqQrySecAgentTradeInfoOK);

	 Release();
 }

 // 请求查询二级代理商资金验证模式
 TEST(CtpTdApiWrapper, 35ReqQrySecAgentCheckMode)
 {
	 Init();
	 g_CtpTdApiWrapperParams = { '\0' };
	 g_CtpTdApiWrapperParams.isLogin = true;
	 g_CtpTdApiWrapperParams.isReqQrySecAgentCheckMode = true;

	 RegRspUserLogin(g_pTdSpi, OnRspUserLogin);
	 RegRspQrySecAgentCheckMode(g_pTdSpi, OnRspQrySecAgentCheckMode);

	 g_pTdApi->Init();

	 std::unique_lock<mutex> lck(g_mtx);
	 g_cond_va.wait_for(lck, std::chrono::seconds(5), []() -> bool { return g_initOK && g_loginOK && g_reqQrySecAgentCheckModeOK; });

	 EXPECT_TRUE(g_pTdSpi != NULL);
	 EXPECT_TRUE(g_pTdApi != NULL);
	 EXPECT_TRUE(g_initOK);
	 EXPECT_TRUE(g_loginOK);
	 EXPECT_TRUE(g_reqQrySecAgentCheckModeOK);

	 Release();
 }

 // 请求查询资金账户
 TEST(CtpTdApiWrapper, 36ReqQrySecAgentTradingAccount)
 {
	 Init();
	 g_CtpTdApiWrapperParams = { '\0' };
	 g_CtpTdApiWrapperParams.isLogin = true;
	 g_CtpTdApiWrapperParams.isReqQrySecAgentTradingAccount = true;

	 RegRspUserLogin(g_pTdSpi, OnRspUserLogin);
	 RegRspQrySecAgentTradingAccount(g_pTdSpi, OnRspQrySecAgentTradingAccount);

	 g_pTdApi->Init();

	 std::unique_lock<mutex> lck(g_mtx);
	 g_cond_va.wait_for(lck, std::chrono::seconds(5), []() -> bool { return g_initOK && g_loginOK && g_reqQrySecAgentTradingAccountOK; });

	 EXPECT_TRUE(g_pTdSpi != NULL);
	 EXPECT_TRUE(g_pTdApi != NULL);
	 EXPECT_TRUE(g_initOK);
	 EXPECT_TRUE(g_loginOK);
	 EXPECT_TRUE(g_reqQrySecAgentTradingAccountOK);

	 Release();
 }

 // 请求查询报单手续费
 TEST(CtpTdApiWrapper, 37ReqQryInstrumentOrderCommRate)
 {
	 Init();
	 g_CtpTdApiWrapperParams = { '\0' };
	 g_CtpTdApiWrapperParams.isLogin = true;
	 g_CtpTdApiWrapperParams.isReqQryInstrumentOrderCommRate = true;

	 RegRspUserLogin(g_pTdSpi, OnRspUserLogin);
	 RegRspQryInstrumentOrderCommRate(g_pTdSpi, OnRspQryInstrumentOrderCommRate);

	 g_pTdApi->Init();

	 std::unique_lock<mutex> lck(g_mtx);
	 g_cond_va.wait_for(lck, std::chrono::seconds(5), []() -> bool { return g_initOK && g_loginOK && g_reqQryInstrumentOrderCommRateOK; });

	 EXPECT_TRUE(g_pTdSpi != NULL);
	 EXPECT_TRUE(g_pTdApi != NULL);
	 EXPECT_TRUE(g_initOK);
	 EXPECT_TRUE(g_loginOK);
	 EXPECT_TRUE(g_reqQryInstrumentOrderCommRateOK);

	 Release();
 }

 // 请求查询做市商合约手续费率
 TEST(CtpTdApiWrapper, 38ReqQryMMInstrumentCommissionRate)
 {
	 Init();
	 g_CtpTdApiWrapperParams = { '\0' };
	 g_CtpTdApiWrapperParams.isLogin = true;
	 g_CtpTdApiWrapperParams.isReqQryMMInstrumentCommissionRate = true;

	 RegRspUserLogin(g_pTdSpi, OnRspUserLogin);
	 RegRspQryMMInstrumentCommissionRate(g_pTdSpi, OnRspQryMMInstrumentCommissionRate);

	 g_pTdApi->Init();

	 std::unique_lock<mutex> lck(g_mtx);
	 g_cond_va.wait_for(lck, std::chrono::seconds(5), []() -> bool { return g_initOK && g_loginOK && g_reqQryMMInstrumentCommissionRateOK; });

	 EXPECT_TRUE(g_pTdSpi != NULL);
	 EXPECT_TRUE(g_pTdApi != NULL);
	 EXPECT_TRUE(g_initOK);
	 EXPECT_TRUE(g_loginOK);
	 EXPECT_TRUE(g_reqQryMMInstrumentCommissionRateOK);

	 Release();
 }

 // 请求查询产品组
 TEST(CtpTdApiWrapper, 38ReqQryProductGroup)
 {
	 Init();
	 g_CtpTdApiWrapperParams = { '\0' };
	 g_CtpTdApiWrapperParams.isLogin = true;
	 g_CtpTdApiWrapperParams.isReqQryProductGroup = true;

	 RegRspUserLogin(g_pTdSpi, OnRspUserLogin);
	 RegRspQryProductGroup(g_pTdSpi, OnRspQryProductGroup);

	 g_pTdApi->Init();

	 std::unique_lock<mutex> lck(g_mtx);
	 g_cond_va.wait_for(lck, std::chrono::seconds(5), []() -> bool { return g_initOK && g_loginOK && g_reqQryProductGroupOK; });

	 EXPECT_TRUE(g_pTdSpi != NULL);
	 EXPECT_TRUE(g_pTdApi != NULL);
	 EXPECT_TRUE(g_initOK);
	 EXPECT_TRUE(g_loginOK);
	 EXPECT_TRUE(g_reqQryProductGroupOK);

	 Release();
 }

 // 请求查询产品报价汇率
 TEST(CtpTdApiWrapper, 39ReqQryProductExchRate)
 {
	 Init();
	 g_CtpTdApiWrapperParams = { '\0' };
	 g_CtpTdApiWrapperParams.isLogin = true;
	 g_CtpTdApiWrapperParams.isReqQryProductExchRate = true;

	 RegRspUserLogin(g_pTdSpi, OnRspUserLogin);
	 RegRspQryProductExchRate(g_pTdSpi, OnRspQryProductExchRate);

	 g_pTdApi->Init();

	 std::unique_lock<mutex> lck(g_mtx);
	 g_cond_va.wait_for(lck, std::chrono::seconds(5), []() -> bool { return g_initOK && g_loginOK && g_reqQryProductExchRateOK; });

	 EXPECT_TRUE(g_pTdSpi != NULL);
	 EXPECT_TRUE(g_pTdApi != NULL);
	 EXPECT_TRUE(g_initOK);
	 EXPECT_TRUE(g_loginOK);
	 EXPECT_TRUE(g_reqQryProductExchRateOK);

	 Release();
 }

 // 请求查询汇率
 TEST(CtpTdApiWrapper, 40ReqQryExchangeRate)
 {
	 Init();
	 g_CtpTdApiWrapperParams = { '\0' };
	 g_CtpTdApiWrapperParams.isLogin = true;
	 g_CtpTdApiWrapperParams.isReqQryExchangeRate = true;

	 RegRspUserLogin(g_pTdSpi, OnRspUserLogin);
	 RegRspQryExchangeRate(g_pTdSpi, OnRspQryExchangeRate);

	 g_pTdApi->Init();

	 std::unique_lock<mutex> lck(g_mtx);
	 g_cond_va.wait_for(lck, std::chrono::seconds(5), []() -> bool { return g_initOK && g_loginOK && g_reqQryExchangeRateOK; });

	 EXPECT_TRUE(g_pTdSpi != NULL);
	 EXPECT_TRUE(g_pTdApi != NULL);
	 EXPECT_TRUE(g_initOK);
	 EXPECT_TRUE(g_loginOK);
	 EXPECT_TRUE(g_reqQryExchangeRateOK);

	 Release();
 }

 // 请求查询交易所调整的保证金率
 TEST(CtpTdApiWrapper, 41ReqQryExchangeMarginRateAdjust)
 {
	 Init();
	 g_CtpTdApiWrapperParams = { '\0' };
	 g_CtpTdApiWrapperParams.isLogin = true;
	 g_CtpTdApiWrapperParams.isReqQryExchangeMarginRateAdjust = true;

	 RegRspUserLogin(g_pTdSpi, OnRspUserLogin);
	 RegRspQryExchangeMarginRateAdjust(g_pTdSpi, OnRspQryExchangeMarginRateAdjust);

	 g_pTdApi->Init();

	 std::unique_lock<mutex> lck(g_mtx);
	 g_cond_va.wait_for(lck, std::chrono::seconds(5), []() -> bool { return g_initOK && g_loginOK && g_reqQryExchangeMarginRateAdjustOK; });

	 EXPECT_TRUE(g_pTdSpi != NULL);
	 EXPECT_TRUE(g_pTdApi != NULL);
	 EXPECT_TRUE(g_initOK);
	 EXPECT_TRUE(g_loginOK);
	 EXPECT_TRUE(g_reqQryExchangeMarginRateAdjustOK);

	 Release();
 }
 
 // 请求查询交易所保证金率
 TEST(CtpTdApiWrapper, 42ReqQryExchangeMarginRate)
 {
	 Init();
	 g_CtpTdApiWrapperParams = { '\0' };
	 g_CtpTdApiWrapperParams.isLogin = true;
	 g_CtpTdApiWrapperParams.isReqQryExchangeMarginRate = true;

	 RegRspUserLogin(g_pTdSpi, OnRspUserLogin);
	 RegRspQryExchangeMarginRate(g_pTdSpi, OnRspQryExchangeMarginRate);

	 g_pTdApi->Init();

	 std::unique_lock<mutex> lck(g_mtx);
	 g_cond_va.wait_for(lck, std::chrono::seconds(5), []() -> bool { return g_initOK && g_loginOK && g_reqQryExchangeMarginRateOK; });

	 EXPECT_TRUE(g_pTdSpi != NULL);
	 EXPECT_TRUE(g_pTdApi != NULL);
	 EXPECT_TRUE(g_initOK);
	 EXPECT_TRUE(g_loginOK);
	 EXPECT_TRUE(g_reqQryExchangeMarginRateOK);

	 Release();
 }

 // 请求查询投资者品种/跨品种保证金
 TEST(CtpTdApiWrapper, 43ReqQryInvestorProductGroupMargin)
 {
	 Init();
	 g_CtpTdApiWrapperParams = { '\0' };
	 g_CtpTdApiWrapperParams.isLogin = true;
	 g_CtpTdApiWrapperParams.isReqQryInvestorProductGroupMargin = true;

	 RegRspUserLogin(g_pTdSpi, OnRspUserLogin);
	 RegRspQryInvestorProductGroupMargin(g_pTdSpi, OnRspQryInvestorProductGroupMargin);

	 g_pTdApi->Init();

	 std::unique_lock<mutex> lck(g_mtx);
	 g_cond_va.wait_for(lck, std::chrono::seconds(5), []() -> bool { return g_initOK && g_loginOK && g_reqQryInvestorProductGroupMarginOK; });

	 EXPECT_TRUE(g_pTdSpi != NULL);
	 EXPECT_TRUE(g_pTdApi != NULL);
	 EXPECT_TRUE(g_initOK);
	 EXPECT_TRUE(g_loginOK);
	 EXPECT_TRUE(g_reqQryInvestorProductGroupMarginOK);

	 Release();
 }
 
 // 请求查询仓单信息
 TEST(CtpTdApiWrapper, 44ReqQryEWarrantOffset)
 {
	 Init();
	 g_CtpTdApiWrapperParams = { '\0' };
	 g_CtpTdApiWrapperParams.isLogin = true;
	 g_CtpTdApiWrapperParams.isReqQryEWarrantOffset = true;

	 RegRspUserLogin(g_pTdSpi, OnRspUserLogin);
	 RegRspQryEWarrantOffset(g_pTdSpi, OnRspQryEWarrantOffset);

	 g_pTdApi->Init();

	 std::unique_lock<mutex> lck(g_mtx);
	 g_cond_va.wait_for(lck, std::chrono::seconds(5), []() -> bool { return g_initOK && g_loginOK && g_reqQryEWarrantOffsetOK; });

	 EXPECT_TRUE(g_pTdSpi != NULL);
	 EXPECT_TRUE(g_pTdApi != NULL);
	 EXPECT_TRUE(g_initOK);
	 EXPECT_TRUE(g_loginOK);
	 EXPECT_TRUE(g_reqQryEWarrantOffsetOK);

	 Release();
 }
 
 // 请求查询保证金监管系统经纪公司资金账户密钥
 TEST(CtpTdApiWrapper, 45ReqQryCFMMCTradingAccountKey)
 {
	 Init();
	 g_CtpTdApiWrapperParams = { '\0' };
	 g_CtpTdApiWrapperParams.isLogin = true;
	 g_CtpTdApiWrapperParams.isReqQryCFMMCTradingAccountKey = true;

	 RegRspUserLogin(g_pTdSpi, OnRspUserLogin);
	 RegRspQryCFMMCTradingAccountKey(g_pTdSpi, OnRspQryCFMMCTradingAccountKey);

	 g_pTdApi->Init();

	 std::unique_lock<mutex> lck(g_mtx);
	 g_cond_va.wait_for(lck, std::chrono::seconds(5), []() -> bool { return g_initOK && g_loginOK && g_reqQryCFMMCTradingAccountKeyOK; });

	 EXPECT_TRUE(g_pTdSpi != NULL);
	 EXPECT_TRUE(g_pTdApi != NULL);
	 EXPECT_TRUE(g_initOK);
	 EXPECT_TRUE(g_loginOK);
	 EXPECT_TRUE(g_reqQryCFMMCTradingAccountKeyOK);

	 Release();
 }

 // 请求查询投资者组合合约持仓明细
 TEST(CtpTdApiWrapper, 45ReqQryInvestorPositionCombineDetail)
 {
	 Init();
	 g_CtpTdApiWrapperParams = { '\0' };
	 g_CtpTdApiWrapperParams.isLogin = true;
	 g_CtpTdApiWrapperParams.isReqQryInvestorPositionCombineDetail = true;

	 RegRspUserLogin(g_pTdSpi, OnRspUserLogin);
	 RegRspQryInvestorPositionCombineDetail(g_pTdSpi, OnRspQryInvestorPositionCombineDetail);

	 g_pTdApi->Init();

	 std::unique_lock<mutex> lck(g_mtx);
	 g_cond_va.wait_for(lck, std::chrono::seconds(5), []() -> bool { return g_initOK && g_loginOK && g_reqQryInvestorPositionCombineDetailOK; });

	 EXPECT_TRUE(g_pTdSpi != NULL);
	 EXPECT_TRUE(g_pTdApi != NULL);
	 EXPECT_TRUE(g_initOK);
	 EXPECT_TRUE(g_loginOK);
	 EXPECT_TRUE(g_reqQryInvestorPositionCombineDetailOK);

	 Release();
 }
 
 // 请求查询投资者持仓明细
 TEST(CtpTdApiWrapper, 46ReqQryInvestorPositionDetail)
 {
	 Init();
	 g_CtpTdApiWrapperParams = { '\0' };
	 g_CtpTdApiWrapperParams.isLogin = true;
	 g_CtpTdApiWrapperParams.isReqQryInvestorPositionDetail = true;

	 RegRspUserLogin(g_pTdSpi, OnRspUserLogin);
	 RegRspQryInvestorPositionDetail(g_pTdSpi, OnRspQryInvestorPositionDetail);

	 g_pTdApi->Init();

	 std::unique_lock<mutex> lck(g_mtx);
	 g_cond_va.wait_for(lck, std::chrono::seconds(5), []() -> bool { return g_initOK && g_loginOK && g_reqQryInvestorPositionDetailOK; });

	 EXPECT_TRUE(g_pTdSpi != NULL);
	 EXPECT_TRUE(g_pTdApi != NULL);
	 EXPECT_TRUE(g_initOK);
	 EXPECT_TRUE(g_loginOK);
	 EXPECT_TRUE(g_reqQryInvestorPositionDetailOK);

	 Release();
 }
 
 // 请求查询转账银行
 TEST(CtpTdApiWrapper, 47ReqQryTransferBank)
 {
	 Init();
	 g_CtpTdApiWrapperParams = { '\0' };
	 g_CtpTdApiWrapperParams.isLogin = true;
	 g_CtpTdApiWrapperParams.isReqQryTransferBank = true;

	 RegRspUserLogin(g_pTdSpi, OnRspUserLogin);
	 RegRspQryTransferBank(g_pTdSpi, OnRspQryTransferBank);

	 g_pTdApi->Init();

	 std::unique_lock<mutex> lck(g_mtx);
	 g_cond_va.wait_for(lck, std::chrono::seconds(5), []() -> bool { return g_initOK && g_loginOK && g_reqQryTransferBankOK; });

	 EXPECT_TRUE(g_pTdSpi != NULL);
	 EXPECT_TRUE(g_pTdApi != NULL);
	 EXPECT_TRUE(g_initOK);
	 EXPECT_TRUE(g_loginOK);
	 EXPECT_TRUE(g_reqQryTransferBankOK);

	 Release();
 }

 // 请求查询投资者结算信息
 TEST(CtpTdApiWrapper, 48ReqQrySettlementInfo)
 {
	 Init();
	 g_CtpTdApiWrapperParams = { '\0' };
	 g_CtpTdApiWrapperParams.isLogin = true;
	 g_CtpTdApiWrapperParams.isReqQrySettlementInfo = true;

	 RegRspUserLogin(g_pTdSpi, OnRspUserLogin);
	 RegRspQrySettlementInfo(g_pTdSpi, OnRspQrySettlementInfo);

	 g_pTdApi->Init();

	 std::unique_lock<mutex> lck(g_mtx);
	 g_cond_va.wait_for(lck, std::chrono::seconds(5), []() -> bool { return g_initOK && g_loginOK && g_reqQrySettlementInfoOK; });

	 EXPECT_TRUE(g_pTdSpi != NULL);
	 EXPECT_TRUE(g_pTdApi != NULL);
	 EXPECT_TRUE(g_initOK);
	 EXPECT_TRUE(g_loginOK);
	 EXPECT_TRUE(g_reqQrySettlementInfoOK);

	 Release();
 }

 // 请求查询行情
 TEST(CtpTdApiWrapper, 49ReqQryDepthMarketData)
 {
	 Init();
	 g_CtpTdApiWrapperParams = { '\0' };
	 g_CtpTdApiWrapperParams.isLogin = true;
	 g_CtpTdApiWrapperParams.isReqQryDepthMarketData = true;

	 RegRspUserLogin(g_pTdSpi, OnRspUserLogin);
	 RegRspQryDepthMarketData(g_pTdSpi, OnRspQryDepthMarketData);

	 g_pTdApi->Init();

	 std::unique_lock<mutex> lck(g_mtx);
	 g_cond_va.wait_for(lck, std::chrono::seconds(5), []() -> bool { return g_initOK && g_loginOK && g_reqQryDepthMarketDataOK; });

	 EXPECT_TRUE(g_pTdSpi != NULL);
	 EXPECT_TRUE(g_pTdApi != NULL);
	 EXPECT_TRUE(g_initOK);
	 EXPECT_TRUE(g_loginOK);
	 EXPECT_TRUE(g_reqQryDepthMarketDataOK);

	 Release();
 }

 // 请求查询合约
 TEST(CtpTdApiWrapper, 50ReqQryInstrument)
 {
	 Init();
	 g_CtpTdApiWrapperParams = { '\0' };
	 g_CtpTdApiWrapperParams.isLogin = true;
	 g_CtpTdApiWrapperParams.isReqQryInstrument = true;

	 RegRspUserLogin(g_pTdSpi, OnRspUserLogin);
	 RegRspQryInstrument(g_pTdSpi, OnRspQryInstrument);

	 g_pTdApi->Init();

	 std::unique_lock<mutex> lck(g_mtx);
	 g_cond_va.wait_for(lck, std::chrono::seconds(5), []() -> bool { return g_initOK && g_loginOK && g_reqQryInstrumentOK; });

	 EXPECT_TRUE(g_pTdSpi != NULL);
	 EXPECT_TRUE(g_pTdApi != NULL);
	 EXPECT_TRUE(g_initOK);
	 EXPECT_TRUE(g_loginOK);
	 EXPECT_TRUE(g_reqQryInstrumentOK);

	 Release();
 }
 
 // 请求查询交易所
 TEST(CtpTdApiWrapper, 51ReqQryExchange)
 {
	 Init();
	 g_CtpTdApiWrapperParams = { '\0' };
	 g_CtpTdApiWrapperParams.isLogin = true;
	 g_CtpTdApiWrapperParams.isReqQryExchange = true;

	 RegRspUserLogin(g_pTdSpi, OnRspUserLogin);
	 RegRspQryExchange(g_pTdSpi, OnRspQryExchange);

	 g_pTdApi->Init();

	 std::unique_lock<mutex> lck(g_mtx);
	 g_cond_va.wait_for(lck, std::chrono::seconds(5), []() -> bool { return g_initOK && g_loginOK && g_reqQryExchangeOK; });

	 EXPECT_TRUE(g_pTdSpi != NULL);
	 EXPECT_TRUE(g_pTdApi != NULL);
	 EXPECT_TRUE(g_initOK);
	 EXPECT_TRUE(g_loginOK);
	 EXPECT_TRUE(g_reqQryExchangeOK);

	 Release();
 }

 // 请求查询合约手续费率
 TEST(CtpTdApiWrapper, 52ReqQryInstrumentCommissionRate)
 {
	 Init();
	 g_CtpTdApiWrapperParams = { '\0' };
	 g_CtpTdApiWrapperParams.isLogin = true;
	 g_CtpTdApiWrapperParams.isReqQryInstrumentCommissionRate = true;

	 RegRspUserLogin(g_pTdSpi, OnRspUserLogin);
	 RegRspQryInstrumentCommissionRate(g_pTdSpi, OnRspQryInstrumentCommissionRate);

	 g_pTdApi->Init();

	 std::unique_lock<mutex> lck(g_mtx);
	 g_cond_va.wait_for(lck, std::chrono::seconds(5), []() -> bool { return g_initOK && g_loginOK && g_reqQryInstrumentCommissionRateOK; });

	 EXPECT_TRUE(g_pTdSpi != NULL);
	 EXPECT_TRUE(g_pTdApi != NULL);
	 EXPECT_TRUE(g_initOK);
	 EXPECT_TRUE(g_loginOK);
	 EXPECT_TRUE(g_reqQryInstrumentCommissionRateOK);

	 Release();
 }

 // 请求查询合约的保证金率
 TEST(CtpTdApiWrapper, 53ReqQryInstrumentMarginRate)
 {
	 Init();
	 g_CtpTdApiWrapperParams = { '\0' };
	 g_CtpTdApiWrapperParams.isLogin = true;
	 g_CtpTdApiWrapperParams.isReqQryInstrumentMarginRate = true;

	 RegRspUserLogin(g_pTdSpi, OnRspUserLogin);
	 RegRspQryInstrumentMarginRate(g_pTdSpi, OnRspQryInstrumentMarginRate);

	 g_pTdApi->Init();

	 std::unique_lock<mutex> lck(g_mtx);
	 g_cond_va.wait_for(lck, std::chrono::seconds(5), []() -> bool { return g_initOK && g_loginOK && g_reqQryInstrumentMarginRateOK; });

	 EXPECT_TRUE(g_pTdSpi != NULL);
	 EXPECT_TRUE(g_pTdApi != NULL);
	 EXPECT_TRUE(g_initOK);
	 EXPECT_TRUE(g_loginOK);
	 EXPECT_TRUE(g_reqQryInstrumentMarginRateOK);

	 Release();
 }

 // 请求查询交易编码
 TEST(CtpTdApiWrapper, 54ReqQryTradingCode)
 {
	 Init();
	 g_CtpTdApiWrapperParams = { '\0' };
	 g_CtpTdApiWrapperParams.isLogin = true;
	 g_CtpTdApiWrapperParams.isReqQryTradingCode = true;

	 RegRspUserLogin(g_pTdSpi, OnRspUserLogin);
	 RegRspQryTradingCode(g_pTdSpi, OnRspQryTradingCode);

	 g_pTdApi->Init();

	 std::unique_lock<mutex> lck(g_mtx);
	 g_cond_va.wait_for(lck, std::chrono::seconds(5), []() -> bool { return g_initOK && g_loginOK && g_reqQryTradingCodeOK; });

	 EXPECT_TRUE(g_pTdSpi != NULL);
	 EXPECT_TRUE(g_pTdApi != NULL);
	 EXPECT_TRUE(g_initOK);
	 EXPECT_TRUE(g_loginOK);
	 EXPECT_TRUE(g_reqQryTradingCodeOK);

	 Release();
 }

 // 请求查询投资者
 TEST(CtpTdApiWrapper, 55ReqQryInvestor)
 {
	 Init();
	 g_CtpTdApiWrapperParams = { '\0' };
	 g_CtpTdApiWrapperParams.isLogin = true;
	 g_CtpTdApiWrapperParams.isReqQryInvestor = true;

	 RegRspUserLogin(g_pTdSpi, OnRspUserLogin);
	 RegRspQryInvestor(g_pTdSpi, OnRspQryInvestor);

	 g_pTdApi->Init();

	 std::unique_lock<mutex> lck(g_mtx);
	 g_cond_va.wait_for(lck, std::chrono::seconds(5), []() -> bool { return g_initOK && g_loginOK && g_reqQryInvestorOK; });

	 EXPECT_TRUE(g_pTdSpi != NULL);
	 EXPECT_TRUE(g_pTdApi != NULL);
	 EXPECT_TRUE(g_initOK);
	 EXPECT_TRUE(g_loginOK);
	 EXPECT_TRUE(g_reqQryInvestorOK);

	 Release();
 } 

 // 请求查询资金账户
 TEST(CtpTdApiWrapper, 56ReqQryTradingAccount)
 {
	 Init();
	 g_CtpTdApiWrapperParams = { '\0' };
	 g_CtpTdApiWrapperParams.isLogin = true;
	 g_CtpTdApiWrapperParams.isReqQryTradingAccount = true;

	 RegRspUserLogin(g_pTdSpi, OnRspUserLogin);
	 RegRspQryTradingAccount(g_pTdSpi, OnRspQryTradingAccount);

	 g_pTdApi->Init();

	 std::unique_lock<mutex> lck(g_mtx);
	 g_cond_va.wait_for(lck, std::chrono::seconds(5), []() -> bool { return g_initOK && g_loginOK && g_reqQryTradingAccountOK; });

	 EXPECT_TRUE(g_pTdSpi != NULL);
	 EXPECT_TRUE(g_pTdApi != NULL);
	 EXPECT_TRUE(g_initOK);
	 EXPECT_TRUE(g_loginOK);
	 EXPECT_TRUE(g_reqQryTradingAccountOK);

	 Release();
 }

 // 请求查询投资者持仓
 TEST(CtpTdApiWrapper, 57ReqQryInvestorPosition)
 {
	 Init();
	 g_CtpTdApiWrapperParams = { '\0' };
	 g_CtpTdApiWrapperParams.isLogin = true;
	 g_CtpTdApiWrapperParams.isReqQryInvestorPosition = true;

	 RegRspUserLogin(g_pTdSpi, OnRspUserLogin);
	 RegRspQryInvestorPosition(g_pTdSpi, OnRspQryInvestorPosition);

	 g_pTdApi->Init();

	 std::unique_lock<mutex> lck(g_mtx);
	 g_cond_va.wait_for(lck, std::chrono::seconds(5), []() -> bool { return g_initOK && g_loginOK && g_reqQryInvestorPositionOK; });

	 EXPECT_TRUE(g_pTdSpi != NULL);
	 EXPECT_TRUE(g_pTdApi != NULL);
	 EXPECT_TRUE(g_initOK);
	 EXPECT_TRUE(g_loginOK);
	 EXPECT_TRUE(g_reqQryInvestorPositionOK);

	 Release();
 }
 
 // 请求查询交易
 TEST(CtpTdApiWrapper, 58ReqQryTrade)
 {
	 Init();
	 g_CtpTdApiWrapperParams = { '\0' };
	 g_CtpTdApiWrapperParams.isLogin = true;
	 g_CtpTdApiWrapperParams.isReqQryTrade = true;

	 RegRspUserLogin(g_pTdSpi, OnRspUserLogin);
	 RegRspQryTrade(g_pTdSpi, OnRspQryTrade);

	 g_pTdApi->Init();

	 std::unique_lock<mutex> lck(g_mtx);
	 g_cond_va.wait_for(lck, std::chrono::seconds(5), []() -> bool { return g_initOK && g_loginOK && g_reqQryTradeOK; });

	 EXPECT_TRUE(g_pTdSpi != NULL);
	 EXPECT_TRUE(g_pTdApi != NULL);
	 EXPECT_TRUE(g_initOK);
	 EXPECT_TRUE(g_loginOK);
	 EXPECT_TRUE(g_reqQryTradeOK);

	 Release();
 }

 // 订阅私有流
 // SubscribePrivateTopic

 // 订阅公有流
 // SubscribePublicTopic

