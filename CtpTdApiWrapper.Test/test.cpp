#include "pch.h"
#include <ostream>
#include <fstream>
#include <mutex>
#include "..\CtpTdApiWrapper\TraderApi.h"
#include "..\CtpTdApiWrapper\TraderSpi.h"
using namespace std;

// ��������
TThostFtdcBrokerIDType gBrokerID = "9999";                         // ģ�⾭���̴���
TThostFtdcInvestorIDType gInvesterID = "180935";                         // Ͷ�����˻���
TThostFtdcPasswordType gInvesterPassword = "hello@123";                     // Ͷ��������

// �������
CThostFtdcTraderApi *g_pTdApi = nullptr;                           // ����ָ��
TraderSpi *g_pTdSpi = nullptr;                           // spi
//char gTradeFrontAddr[] = "tcp://180.168.146.187:10201";            // ģ�⽻��ǰ�õ�ַ ��һ��
char gTradeFrontAddr[] = "tcp://180.168.146.187:10130";            // ģ�⽻��ǰ�õ�ַ 24h
//char *g_pInstrumentID[] = {"rb2205"}; // �����Լ�����б��С��ϡ���֣��������ѡһ��
int instrumentNum = 1;                                     // �����Լ��������

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

	bool isForQuoteInsert;								// ��ѯ��
	bool isQryQuote;									// ��ѯ����
	bool isQryCombAction;								// ��ѯ���
	bool isQryCombInstrumentGuard;						// ��ѯ��Ϻ�Լ�İ�ȫϵ��
	bool isQryTransferSerial;							// ��ѯת����ˮ
	bool isQryAccountregister;							// ��ѯ����ǩԼ��ϵ

	bool isQryContractBank;								// ��ѯǩԼ����
	bool isQryParkedOrder;								// ��ѯԤ�񶩵�
	bool isQryParkedOrderAction;						// ��ѯԤ�񳷵�
	bool isQryTradingNotice;							// ��ѯ����֪ͨ
	bool isQryBrokerTradingParams;						// ��ѯ���ù�˾���ײ���

	bool isQryBrokerTradingAlgos;						// ��ѯ���ù�˾�Ľ����㷨
	bool isQueryBankBalanceByFuture;					// ��ѯ�ڻ��������
	bool isQueryCFMMCTradingAccountToken;				// ��ѯ��������û�����
	bool isReqFromBankToFutureByFuture;					// �ڻ���������ת�ڻ�����
	bool isReqFromFutureToBankByFuture;					// �ڻ������ڻ�ת��������

	bool isReqQryInvestUnit;							// �����ѯͶ�ʵ�Ԫ
	bool isReqQrySecAgentTradeInfo;						// �����ѯ������������Ϣ
	bool isReqQrySecAgentCheckMode;						// �����ѯ�����������ʽ���֤ģʽ
	bool isReqQrySecAgentTradingAccount;				// �����ѯ�ʽ��˻�
	bool isReqQryInstrumentOrderCommRate;				// ���󱨵�������
	bool isReqQryMMInstrumentCommissionRate;			// �����ѯ������������

	bool isReqQryProductGroup;							// �����ѯ��Ʒ��
	bool isReqQryProductExchRate;						// �����ѯ��Ʒ���ۻ���
	bool isReqQryExchangeRate;							// �����ѯ����
	bool isReqQryExchangeMarginRateAdjust;				// �������������ı�֤��
	bool isReqQryExchangeMarginRate;					// �����ѯ��������֤����
	bool isReqQryInvestorProductGroupMargin;			// �����ѯͶ����Ʒ��/��Ʒ�ֱ�֤��

	bool isReqQryEWarrantOffset;						// �����ѯ�ֲ���Ϣ
	bool isReqQryCFMMCTradingAccountKey;				// �����ѯ��֤����ϵͳ���͹�˾�ʽ��˻���Կ
	bool isReqQryInvestorPositionCombineDetail;			// �����ѯͶ������Ϻ�Լ�ֲ���ϸ
	bool isReqQryInvestorPositionDetail;				// �����ѯͶ���ߺ�Լ�ֲ���ϸ
	bool isReqQryTransferBank;							// �����ѯת������

	bool isReqQrySettlementInfo;						// �����ѯͶ���߽�����Ϣ
	bool isReqQryDepthMarketData;						// �����ѯ��������
	bool isReqQryInstrument;							// �����ѯ��Լ
	bool isReqQryExchange;								// �����ѯ������
	bool isReqQryInstrumentCommissionRate;				// �����ѯ��Լ������
	bool isReqQryInstrumentMarginRate;					// �����ѯ��Լ�ı�֤����

	bool isReqQryTradingCode;							// �����ѯ�����߱��
	bool isReqQryInvestor;								// �����ѯͶ����
	bool isReqQryTradingAccount;						// �����ѯ�ʽ��˻�
	bool isReqQryInvestorPosition;						// �����ѯͶ���ֲ߳�
	bool isReqQryTrade;									// �����ѯ����

};

CtpTdApiWrapperParams g_CtpTdApiWrapperParams = { '\0' };

// �߳�ͬ������
mutex g_mtx;
condition_variable g_cond_va;

// ���ڼ��ı���
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

	std::cout << "=====�����������ӳɹ�=====" << std::endl;

	// �����Ҫ��֤
	if (g_CtpTdApiWrapperParams.isAuth) 
	{
		CThostFtdcReqAuthenticateField authField = { '\0' };
		strcpy_s(authField.AppID, "");
		strcpy_s(authField.AuthCode, "123456");
		strcpy_s(authField.BrokerID, gBrokerID);
		strcpy_s(authField.UserID, gInvesterID);
		int rf = g_pTdApi->ReqAuthenticate(&authField, 0);

		if (!rf)
			cout << ">>>>>>������֤����ɹ�" << endl;
		else
			cerr << "---->>>������֤����ʧ��" << endl;
	}

	// �����Ҫ��¼
	if (g_CtpTdApiWrapperParams.isLogin) 
	{
		CThostFtdcReqUserLoginField loginReq;
		memset(&loginReq, 0, sizeof(loginReq));
		strcpy_s(loginReq.BrokerID, gBrokerID);
		strcpy_s(loginReq.UserID, gInvesterID);
		strcpy_s(loginReq.Password, gInvesterPassword);
		static int requestID = 0; // ������
		int rt = g_pTdApi->ReqUserLogin(&loginReq, requestID);
		if (!rt)
			std::cout << ">>>>>> ���͵�¼����ɹ�" << std::endl;
		else
			std::cerr << "--->>>���͵�¼����ʧ��" << std::endl;
	}	
}

// �Ͽ�����֪ͨ
void WINAPI OnFrontDisconnected(int nReason)
{
	std::cerr << "=====�������ӶϿ�=====" << std::endl;
	std::cerr << "�����룺 " << nReason << std::endl;
}

// ������ʱ����
void WINAPI OnHeartBeatWarning(int nTimeLapse)
{
	std::cerr << "=====����������ʱ=====" << std::endl;
	std::cerr << "���ϴ�����ʱ�䣺 " << nTimeLapse << std::endl;
}

// ��֤Ӧ��
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

		std::cout << "=====�˻���֤�ɹ�=====" << std::endl;
		std::cout << "���͹�˾���룺 " << pRspAuthenticateField->BrokerID<< std::endl;
		std::cout << "�û����룺 " << pRspAuthenticateField->UserID << std::endl;
		std::cout << "�û��˲�Ʒ��Ϣ�� " << pRspAuthenticateField->UserProductInfo << std::endl;
		std::cout << "App���룺 " << pRspAuthenticateField->AppID << std::endl;
		std::cout << "App���ͣ� " << pRspAuthenticateField->AppType << std::endl;
	}
	else 
		std::cerr << "���ش���--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// ��¼Ӧ��
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

		std::cout << "=====�˻���¼�ɹ�=====" << std::endl;
		std::cout << "�����գ� " << pRspUserLogin->TradingDay << std::endl;
		std::cout << "��¼ʱ�䣺 " << pRspUserLogin->LoginTime << std::endl;
		std::cout << "�����̣� " << pRspUserLogin->BrokerID << std::endl;
		std::cout << "�ʻ����� " << pRspUserLogin->UserID << std::endl;

		if (g_CtpTdApiWrapperParams.isLogout) 
		{
			CThostFtdcUserLogoutField logoutField = { '\0' };
			strcpy_s(logoutField.BrokerID, gBrokerID);
			strcpy_s(logoutField.UserID, gInvesterID);
			int rt = g_pTdApi->ReqUserLogout(&logoutField, 0);

			if (!rt)
				std::cout << ">>>>>>���͵ǳ�����ɹ�" << std::endl;			
			else 
				std::cerr << ">>>>>>���͵ǳ�����ʧ��" << std::endl;			
		}

		// ���µ�¼����
		if (g_CtpTdApiWrapperParams.isUpdateLoginPwd) {
			CThostFtdcUserPasswordUpdateField userPwdUpdateFiled = { '\0' };
			strcpy_s(userPwdUpdateFiled.BrokerID, gBrokerID);
			strcpy_s(userPwdUpdateFiled.UserID, gInvesterID);
			strcpy_s(userPwdUpdateFiled.OldPassword, gInvesterPassword);
			strcpy_s(userPwdUpdateFiled.NewPassword, gInvesterPassword);		// ע�ͣ���Ҫ���Ըù��ܣ����������µ����루���ܺ�������һ����

			int rt = g_pTdApi->ReqUserPasswordUpdate(&userPwdUpdateFiled, 0);
			if (!rt)
				std::cout << ">>>>>>���͸�����������ɹ�" << std::endl;
			else
				std::cerr << "--->>>���͸�����������ʧ��" << std::endl;
		}

		// ���½����˻�����
		if (g_CtpTdApiWrapperParams.isUpdateTrdAccountPwd) {

			CThostFtdcTradingAccountPasswordUpdateField tradingAccountPwdFiled = { '\0' };
			strcpy_s(tradingAccountPwdFiled.BrokerID, gBrokerID);
			strcpy_s(tradingAccountPwdFiled.AccountID, gInvesterID);
			strcpy_s(tradingAccountPwdFiled.OldPassword, "Welcome123");					// ����� simNow �����˻�������
			strcpy_s(tradingAccountPwdFiled.NewPassword, "hello@123");
			strcpy_s(tradingAccountPwdFiled.CurrencyID, "CNY");

			int rf = g_pTdApi->ReqTradingAccountPasswordUpdate(&tradingAccountPwdFiled, 0);
			if (!rf)
				std::cout << ">>>>>>>>���͸��Ľ����˻���������ɹ�" << std::endl;
			else
				std::cerr << "----->>>>�����޸Ľ����˻���������ʧ��" << std::endl;
		}

		// ��������
		if (g_CtpTdApiWrapperParams.isOrderInsert) 
		{
			CThostFtdcInputOrderField orderField = { '\0' };
			strcpy_s(orderField.BrokerID, gBrokerID);
			strcpy_s(orderField.InvestorID, gInvesterID);
			strcpy_s(orderField.ExchangeID, "SHFE");
			strcpy_s(orderField.InstrumentID, "ag2206");
			strcpy_s(orderField.UserID, gInvesterID);
			orderField.OrderPriceType = THOST_FTDC_OPT_LimitPrice;//�޼�
			orderField.Direction = THOST_FTDC_D_Buy;//��
			orderField.CombOffsetFlag[0] = THOST_FTDC_OF_Open;//��
			orderField.CombHedgeFlag[0] = THOST_FTDC_HF_Speculation;//Ͷ��
			orderField.LimitPrice = 4902;
			orderField.VolumeTotalOriginal = 1;
			orderField.TimeCondition = THOST_FTDC_TC_GFD;///������Ч
			orderField.VolumeCondition = THOST_FTDC_VC_AV;///��������
			orderField.MinVolume = 1;
			orderField.ContingentCondition = THOST_FTDC_CC_Immediately;
			orderField.StopPrice = 0;
			orderField.ForceCloseReason = THOST_FTDC_FCC_NotForceClose;
			orderField.IsAutoSuspend = 0;

			int rf = g_pTdApi->ReqOrderInsert(&orderField, 0);
			if (!rf)
				std::cout << "<<<<<<���ͱ�������ɹ�" << std::endl;
			else
				std::cerr << "----->���ͱ�������ʧ��" << std::endl;
		}

		// Ԥ��
		if (g_CtpTdApiWrapperParams.isParkedOrderInsert) 
		{
			CThostFtdcParkedOrderField orderField = { '\0' };
			strcpy_s(orderField.BrokerID, gBrokerID);
			strcpy_s(orderField.InvestorID, gInvesterID);
			strcpy_s(orderField.ExchangeID, "SHFE");
			strcpy_s(orderField.InstrumentID, "ag2206");
			strcpy_s(orderField.UserID, gInvesterID);
			orderField.OrderPriceType = THOST_FTDC_OPT_LimitPrice;//�޼�
			orderField.Direction = THOST_FTDC_D_Buy;//��
			orderField.CombOffsetFlag[0] = THOST_FTDC_OF_Open;//��
			orderField.CombHedgeFlag[0] = THOST_FTDC_HF_Speculation;//Ͷ��
			orderField.LimitPrice = 4950;
			orderField.VolumeTotalOriginal = 1;
			orderField.TimeCondition = THOST_FTDC_TC_GFD;///������Ч
			orderField.VolumeCondition = THOST_FTDC_VC_AV;///��������
			orderField.MinVolume = 1;
			orderField.ContingentCondition = THOST_FTDC_CC_Immediately;
			orderField.StopPrice = 0;
			orderField.ForceCloseReason = THOST_FTDC_FCC_NotForceClose;
			orderField.IsAutoSuspend = 0;

			int rf = g_pTdApi->ReqParkedOrderInsert(&orderField, 0);
			if (!rf)
				std::cout << "<<<<<<����Ԥ������ɹ�" << std::endl;
			else
				std::cerr << "----->����Ԥ�������ʧ��" << std::endl;
		}

		// ��ѯ����
		if (g_CtpTdApiWrapperParams.isQryOrder) 
		{
			CThostFtdcQryOrderField qryOrderField = { '\0' };
			strcpy_s(qryOrderField.BrokerID, gBrokerID);
			strcpy_s(qryOrderField.InvestorID, gInvesterID);
			strcpy_s(qryOrderField.InstrumentID, "ag2206");
			strcpy_s(qryOrderField.ExchangeID, "SHFE");

			int rf = g_pTdApi->ReqQryOrder(&qryOrderField, 0);
			if (!rf)
				std::cout << "<<<<<<��ѯ���������ͳɹ�" << std::endl;
			else
				std::cerr << "----->��ѯ����������ʧ��" << std::endl;
		}

		// ��ѯ��󱨵���
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
				std::cout << "<<<<<<���Ͳ�ѯ��󱨵�������ɹ�" << std::endl;
			else
				std::cerr << "------>���Ͳ�ѯ��󱨵�������ʧ��" << std::endl;
		}

		// ����Ͷ���߽�����ȷ��
		if (g_CtpTdApiWrapperParams.isSettlementInfoConfirm) 
		{
			CThostFtdcSettlementInfoConfirmField settlementInfoConfirmField = { '\0' };
			strcpy_s(settlementInfoConfirmField.BrokerID, gBrokerID);
			strcpy_s(settlementInfoConfirmField.InvestorID, gInvesterID);

			int rf = g_pTdApi->ReqSettlementInfoConfirm(&settlementInfoConfirmField, 0);
			if (!rf)
				std::cout << "Ͷ���߽�����ȷ�������ͳɹ�" << std::endl;
			else
				std::cerr << "Ͷ���߽�����ȷ��������ʧ��" << std::endl;
		}

		// ѯ������
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
				std::cout << "ѯ�������ͳɹ�" << std::endl;
			else
				std::cerr << "ѯ��������ʧ��" << std::endl;
		}

		// ��ѯ���
		if (g_CtpTdApiWrapperParams.isQryCombAction) 
		{
			CThostFtdcQryCombActionField qryCombActionField = { '\0' };
			strcpy(qryCombActionField.BrokerID, gBrokerID);
			strcpy(qryCombActionField.InvestorID, gInvesterID);
			strcpy(qryCombActionField.InstrumentID, "ag2206");//����д�򷵻�ȫ��
			strcpy(qryCombActionField.ExchangeID, "SHFE");

			int rf = g_pTdApi->ReqQryCombAction(&qryCombActionField, 0);
			if (!rf)
				std::cout << "��ѯ��������ͳɹ�" << std::endl;
			else
				std::cerr << "��ѯ���������ʧ��" << std::endl;
		}

		// ��ѯ��Ϻ�Լ�İ�ȫϵ��
		if (g_CtpTdApiWrapperParams.isQryCombInstrumentGuard) 
		{
			CThostFtdcQryCombInstrumentGuardField combInstrumentGuardField = { '\0' };
			strcpy_s(combInstrumentGuardField.BrokerID, gBrokerID);
			strcpy_s(combInstrumentGuardField.ExchangeID, "SHFE");
			strcpy_s(combInstrumentGuardField.InstrumentID, "ag2206");

			int rf = g_pTdApi->ReqQryCombInstrumentGuard(&combInstrumentGuardField, 0);
			if (!rf)
				std::cout << "��ѯ��Ϻ�Լ�İ�ȫϵ�������ͳɹ�" << std::endl;
			else
				std::cerr << "��ѯ��Ϻ�Լ�İ�ȫϵ��������ʧ��" << std::endl;
		}

		// ��ѯ�ʽ�ת����ˮ
		if (g_CtpTdApiWrapperParams.isQryTransferSerial) 
		{
			CThostFtdcQryTransferSerialField serialField = { '\0' };
			strcpy_s(serialField.BrokerID, gBrokerID);
			strcpy_s(serialField.AccountID, gInvesterID);

			int rf = g_pTdApi->ReqQryTransferSerial(&serialField, 0);
			if (!rf)
				std::cout << "��ѯ�ʽ�ת����ˮ�����ͳɹ�" << std::endl;
			else
				std::cerr << "��ѯ�ʽ�ת����ˮ������ʧ��" << std::endl;
		}

		// ��ѯ����ǩԼ��ϵ
		if (g_CtpTdApiWrapperParams.isQryAccountregister) 
		{
			CThostFtdcQryAccountregisterField accountregisterField = { '\0' };
			strcpy_s(accountregisterField.BrokerID, gBrokerID);
			strcpy_s(accountregisterField.AccountID, gInvesterID);

			int rf = g_pTdApi->ReqQryAccountregister(&accountregisterField, 0);
			if (!rf)
				std::cout << "��ѯ����ǩԼ��ϵ�����ͳɹ�" << std::endl;
			else
				std::cerr << "��ѯ����ǩԼ��ϵ������ʧ��" << std::endl;
		}

		// ��ѯǩԼ����
		if (g_CtpTdApiWrapperParams.isQryContractBank) 
		{
			CThostFtdcQryContractBankField contractBankField = { '\0' };
			strcpy_s(contractBankField.BrokerID, gBrokerID);
			
			int rf = g_pTdApi->ReqQryContractBank(&contractBankField, 0);
			if (!rf)
				std::cout << "��ѯǩԼ���������ͳɹ�" << std::endl;
			else
				std::cerr << "��ѯǩԼ����������ʧ��" << std::endl;
		}

		// ��ѯԤ��
		if (g_CtpTdApiWrapperParams.isQryParkedOrder) 
		{
			CThostFtdcQryParkedOrderField parkedOrderField = { '\0' };
			strcpy_s(parkedOrderField.BrokerID, gBrokerID);
			strcpy_s(parkedOrderField.InvestorID, gInvesterID);
			strcpy_s(parkedOrderField.ExchangeID, "SHFE");
			strcpy_s(parkedOrderField.InstrumentID, "ag2206");

			int rf = g_pTdApi->ReqQryParkedOrder(&parkedOrderField, 0);
			if (!rf)
				std::cout << "��ѯԤ�������ͳɹ�" << std::endl;
			else
				std::cerr << "��ѯԤ��������ʧ��" << std::endl;
		}

		// ��ѯԤ�񳷵�
		if (g_CtpTdApiWrapperParams.isQryParkedOrderAction) 
		{
			CThostFtdcQryParkedOrderActionField actionField = { '\0' };
			strcpy_s(actionField.BrokerID, gBrokerID);
			strcpy_s(actionField.InvestorID, gInvesterID);
			strcpy_s(actionField.ExchangeID, "SHFE");
			strcpy_s(actionField.InstrumentID, "ag2206");

			int rf = g_pTdApi->ReqQryParkedOrderAction(&actionField, 0);
			if (!rf)
				std::cout << "Ԥ�񳷵������ͳɹ�" << std::endl;
			else
				std::cerr << "Ԥ�񳷵�������ʧ��" << std::endl;
		}

		// ��ѯ����֪ͨ
		if (g_CtpTdApiWrapperParams.isQryTradingNotice) 
		{
			CThostFtdcQryTradingNoticeField noticeField = { '\0' };
			strcpy_s(noticeField.BrokerID, gBrokerID);
			strcpy_s(noticeField.InvestorID, gInvesterID);

			int rf = g_pTdApi->ReqQryTradingNotice(&noticeField, 0);
			if (!rf)
				std::cout << "����֪ͨ�����ͳɹ�" << std::endl;
			else
				std::cerr << "����֪ͨ������ʧ��" << std::endl;
		}

		// ��ѯ���ù�˾���ײ���
		if (g_CtpTdApiWrapperParams.isQryBrokerTradingParams) 
		{
			CThostFtdcQryBrokerTradingParamsField paramsField = { '\0' };
			strcpy_s(paramsField.BrokerID, gBrokerID);
			strcpy_s(paramsField.InvestorID, gInvesterID);

			int rf = g_pTdApi->ReqQryBrokerTradingParams(&paramsField, 0);
			if (!rf)
				std::cout << "��ѯ���ù�˾���ײ��������ͳɹ�" << std::endl;
			else
				std::cerr << "��ѯ���ù�˾���ײ���������ʧ��" << std::endl;
		}

		// ��ѯ���ù�˾�Ľ����㷨
		if (g_CtpTdApiWrapperParams.isQryBrokerTradingAlgos) 
		{
			CThostFtdcQryBrokerTradingAlgosField algosField = { '\0' };
			strcpy_s(algosField.BrokerID, gBrokerID);
			strcpy_s(algosField.ExchangeID, "SHFE");
			strcpy_s(algosField.InstrumentID, "ag2206");

			int rf = g_pTdApi->ReqQryBrokerTradingAlgos(&algosField, 0);
			if (!rf)
				std::cout << "��ѯ���ù�˾�Ľ����㷨�����ͳɹ�" << std::endl;
			else
				std::cerr << "��ѯ���ù�˾�Ľ����㷨������ʧ��" << std::endl;
		}

		// ��ѯ�ڻ������˻����
		if (g_CtpTdApiWrapperParams.isQueryBankBalanceByFuture) 
		{
			CThostFtdcReqQueryAccountField accountField = { '\0' };
			strcpy_s(accountField.BrokerID, gBrokerID);
			strcpy_s(accountField.AccountID, gInvesterID);
			strcpy_s(accountField.Password, gInvesterPassword);

			int rf = g_pTdApi->ReqQueryBankAccountMoneyByFuture(&accountField, 0);
			if (!rf)
				std::cout << "��ѯ�ڻ������˻���������ͳɹ�" << std::endl;
			else
				std::cerr << "��ѯ�ڻ������˻����������ʧ��" << std::endl;
		}

		// ��ѯ������Ľ�������
		if (g_CtpTdApiWrapperParams.isQueryCFMMCTradingAccountToken) 
		{
			CThostFtdcQueryCFMMCTradingAccountTokenField tokenField = { '\0' };
			strcpy_s(tokenField.BrokerID, gBrokerID);
			strcpy_s(tokenField.InvestorID, gInvesterID);

			int rf = g_pTdApi->ReqQueryCFMMCTradingAccountToken(&tokenField, 0);
			if (!rf)
				std::cout << "��ѯ�ڻ������˻���������ͳɹ�" << std::endl;
			else
				std::cerr << "��ѯ�ڻ������˻����������ʧ��" << std::endl;
		}

		// �ڻ���������ת�ڻ�����
		if (g_CtpTdApiWrapperParams.isReqFromBankToFutureByFuture) 
		{
			CThostFtdcReqTransferField transferField = { '\0' };
			strcpy_s(transferField.BrokerID, gBrokerID);
			strcpy_s(transferField.AccountID, gInvesterID);
			strcpy_s(transferField.Password, gInvesterPassword);

			int rf = g_pTdApi->ReqFromBankToFutureByFuture(&transferField, 0);
			if (!rf)
				std::cout << "�ڻ���������ת�ڻ������ͳɹ�" << std::endl;
			else
				std::cerr << "�ڻ���������ת�ڻ�������ʧ��" << std::endl;
		}

		// �ڻ������ڻ�ת��������
		if (g_CtpTdApiWrapperParams.isReqFromFutureToBankByFuture)
		{
			CThostFtdcReqTransferField transferField = { '\0' };
			strcpy_s(transferField.BrokerID, gBrokerID);
			strcpy_s(transferField.AccountID, gInvesterID);
			strcpy_s(transferField.Password, gInvesterPassword);

			int rf = g_pTdApi->ReqFromFutureToBankByFuture(&transferField, 0);
			if (!rf)
				std::cout << "�ڻ������ڻ�ת���������ͳɹ�" << std::endl;
			else
				std::cerr << "�ڻ������ڻ�ת����������ʧ��" << std::endl;
		}

		// ��ѯͶ�ʵ�Ԫ
		if (g_CtpTdApiWrapperParams.isReqQryInvestUnit) {
			CThostFtdcQryInvestUnitField unitField = { '\0' };
			strcpy_s(unitField.BrokerID, gBrokerID);
			strcpy_s(unitField.InvestorID, gInvesterID);

			int rf = g_pTdApi->ReqQryInvestUnit(&unitField, 0);
			if (!rf)
				std::cout << "��ѯͶ�ʵ�Ԫ�����ͳɹ�" << std::endl;
			else
				std::cerr << "��ѯͶ�ʵ�Ԫ������ʧ��" << std::endl;
		}

		// �����ѯ������������Ϣ
		if (g_CtpTdApiWrapperParams.isReqQrySecAgentTradeInfo) 
		{
			CThostFtdcQrySecAgentTradeInfoField agentTradeInfoField = { '\0' };
			strcpy_s(agentTradeInfoField.BrokerID, gBrokerID);
			strcpy_s(agentTradeInfoField.BrokerSecAgentID, "00000000");

			int rf = g_pTdApi->ReqQrySecAgentTradeInfo(&agentTradeInfoField, 0);
			if (!rf)
				std::cout << "�����ѯ������������Ϣ���ͳɹ�" << std::endl;
			else
				std::cerr << "�����ѯ������������Ϣ����ʧ��" << std::endl;
		}

		// �����ѯ�����������ʽ���֤ģʽ
		if (g_CtpTdApiWrapperParams.isReqQrySecAgentCheckMode) 
		{
			CThostFtdcQrySecAgentCheckModeField agentCheckModeField = { '\0' };
			strcpy_s(agentCheckModeField.BrokerID, gBrokerID);
			strcpy_s(agentCheckModeField.InvestorID, gInvesterID);

			int rf = g_pTdApi->ReqQrySecAgentCheckMode(&agentCheckModeField, 0);
			if (!rf)
				std::cout << "�����ѯ�����������ʽ���֤ģʽ��Ϣ���ͳɹ�" << std::endl;
			else
				std::cerr << "�����ѯ�����������ʽ���֤ģʽ��Ϣ����ʧ��" << std::endl;
		}

		// �����ѯ�ʽ��˻�
		if (g_CtpTdApiWrapperParams.isReqQrySecAgentTradingAccount) {
			CThostFtdcQryTradingAccountField accountField = { '\0' };
			strcpy_s(accountField.BrokerID, gBrokerID);
			strcpy_s(accountField.InvestorID, gInvesterID);

			int rf = g_pTdApi->ReqQrySecAgentTradingAccount(&accountField, 0);
			if (!rf)
				std::cout << "�����ѯ�ʽ��˻���Ϣ���ͳɹ�" << std::endl;
			else
				std::cerr << "�����ѯ�ʽ��˻���Ϣ����ʧ��" << std::endl;
		}

		// �����ѯ����������
		if (g_CtpTdApiWrapperParams.isReqQryInstrumentOrderCommRate) 
		{
			CThostFtdcQryInstrumentOrderCommRateField rateField = { '\0' };
			strcpy_s(rateField.BrokerID, gBrokerID);
			strcpy_s(rateField.InvestorID, gInvesterID);			
			strcpy_s(rateField.InstrumentID, "ag2206");

			int rf = g_pTdApi->ReqQryInstrumentOrderCommRate(&rateField, 0);
			if (!rf)
				std::cout << "�����ѯ������������Ϣ���ͳɹ�" << std::endl;
			else
				std::cerr << "�����ѯ������������Ϣ����ʧ��" << std::endl;
		}

		// �����ѯ�����̺�Լ��������
		if (g_CtpTdApiWrapperParams.isReqQryMMInstrumentCommissionRate) 
		{
			CThostFtdcQryMMInstrumentCommissionRateField rateField = { '\0' };
			strcpy_s(rateField.BrokerID, gBrokerID);
			strcpy_s(rateField.InvestorID, gInvesterID);
			strcpy_s(rateField.InstrumentID, "ag2206");

			int rf = g_pTdApi->ReqQryMMInstrumentCommissionRate(&rateField, 0);
			if (!rf)
				std::cout << "�����ѯ�����̺�Լ����������Ϣ���ͳɹ�" << std::endl;
			else
				std::cerr << "�����ѯ�����̺�Լ����������Ϣ����ʧ��" << std::endl;
		}

		// �����ѯ��Ʒ��
		if (g_CtpTdApiWrapperParams.isReqQryProductGroup) 
		{
			CThostFtdcQryProductGroupField productGroupField = { '\0' };
			strcpy_s(productGroupField.ProductID, "ag2206");
			strcpy_s(productGroupField.ExchangeID, "SHFE");

			int rf = g_pTdApi->ReqQryProductGroup(&productGroupField, 0);
			if (!rf)
				std::cout << "�����ѯ��Ʒ����Ϣ���ͳɹ�" << std::endl;
			else
				std::cerr << "�����ѯ��Ʒ����Ϣ����ʧ��" << std::endl;
		}

		// �����Ʒ���ۻ���
		if (g_CtpTdApiWrapperParams.isReqQryProductExchRate) 
		{
			CThostFtdcQryProductExchRateField rateField = { '\0' };
			strcpy_s(rateField.ExchangeID, "SHFE");
			strcpy_s(rateField.ProductID, "ag2206");

			int rf = g_pTdApi->ReqQryProductExchRate(&rateField, 0);
			if (!rf)
				std::cout << "�����Ʒ���ۻ�����Ϣ���ͳɹ�" << std::endl;
			else
				std::cerr << "�����Ʒ���ۻ�����Ϣ����ʧ��" << std::endl;
		}

		// �����ѯ����
		if (g_CtpTdApiWrapperParams.isReqQryExchangeRate) 
		{
			CThostFtdcQryExchangeRateField rateField = { '\0' };
			strcpy_s(rateField.BrokerID, gBrokerID);
			strcpy_s(rateField.FromCurrencyID, "CNY");
			strcpy_s(rateField.ToCurrencyID, "USD");

			int rf = g_pTdApi->ReqQryExchangeRate(&rateField, 0);
			if (!rf)
				std::cout << "�����Ʒ���ۻ�����Ϣ���ͳɹ�" << std::endl;
			else
				std::cerr << "�����Ʒ���ۻ�����Ϣ����ʧ��" << std::endl;
		}

		// �����ѯ�����������ı��Ͻ�
		if (g_CtpTdApiWrapperParams.isReqQryExchangeMarginRateAdjust) 
		{
			CThostFtdcQryExchangeMarginRateAdjustField adjustField = { '\0' };
			strcpy_s(adjustField.BrokerID, gBrokerID);			
			strcpy_s(adjustField.InstrumentID, "ag2206");
			adjustField.HedgeFlag = THOST_FTDC_HF_Speculation;

			int rf = g_pTdApi->ReqQryExchangeMarginRateAdjust(&adjustField, 0);
			if (!rf)
				std::cout << "�����Ʒ���ۻ�����Ϣ���ͳɹ�" << std::endl;
			else
				std::cerr << "�����Ʒ���ۻ�����Ϣ����ʧ��" << std::endl;
		}

		// �����ѯ��������֤����
		if (g_CtpTdApiWrapperParams.isReqQryExchangeMarginRate) 
		{
			CThostFtdcQryExchangeMarginRateField rateField = { '\0' };
			strcpy_s(rateField.BrokerID, gBrokerID);
			strcpy_s(rateField.InstrumentID, "ag2206");
			strcpy_s(rateField.ExchangeID, "SHFE");			
			rateField.HedgeFlag = THOST_FTDC_HF_Speculation;

			int rf = g_pTdApi->ReqQryExchangeMarginRate(&rateField, 0);
			if (!rf)
				std::cout << "�����ѯ��������֤������Ϣ���ͳɹ�" << std::endl;
			else
				std::cerr << "�����ѯ��������֤������Ϣ����ʧ��" << std::endl;
		}

		// ����Ͷ����Ʒ��/��Ʒ�ֱ�֤��
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
				std::cout << "����Ͷ����Ʒ��/��Ʒ�ֱ�֤����Ϣ���ͳɹ�" << std::endl;
			else
				std::cerr << "����Ͷ����Ʒ��/��Ʒ�ֱ�֤����Ϣ����ʧ��" << std::endl;
		}
		// �����ѯ�ֲ���Ϣ
		if (g_CtpTdApiWrapperParams.isReqQryEWarrantOffset) 
		{
			CThostFtdcQryEWarrantOffsetField offsetField = { '\0' };
			strcpy_s(offsetField.BrokerID, gBrokerID);
			strcpy_s(offsetField.ExchangeID, "SHFE");
			strcpy_s(offsetField.InstrumentID, "ag2206");
			strcpy_s(offsetField.InvestorID, gInvesterID);

			int rf = g_pTdApi->ReqQryEWarrantOffset(&offsetField, 0);
			if (!rf)
				std::cout << "�����ѯ�ֲ���Ϣ���ͳɹ�" << std::endl;
			else
				std::cerr << "�����ѯ�ֲ���Ϣ����ʧ��" << std::endl;
		}

		// �����ѯ��֤����ϵͳ���͹�˾�ʽ��˻���Կ
		if (g_CtpTdApiWrapperParams.isReqQryCFMMCTradingAccountKey) 
		{
			CThostFtdcQryCFMMCTradingAccountKeyField keyField = { '\0' };
			strcpy_s(keyField.BrokerID, gBrokerID);			
			strcpy_s(keyField.InvestorID, gInvesterID);

			int rf = g_pTdApi->ReqQryCFMMCTradingAccountKey(&keyField, 0);
			if (!rf)
				std::cout << "�����ѯ�ֲ���Ϣ���ͳɹ�" << std::endl;
			else
				std::cerr << "�����ѯ�ֲ���Ϣ����ʧ��" << std::endl;
		}

		// �����ѯͶ������ϳֲ���ϸ
		if (g_CtpTdApiWrapperParams.isReqQryInvestorPositionCombineDetail) 
		{
			CThostFtdcQryInvestorPositionCombineDetailField detailField = { '\0' };
			strcpy_s(detailField.BrokerID, gBrokerID);
			strcpy_s(detailField.InvestorID, gInvesterID);
			strcpy_s(detailField.CombInstrumentID, "ag2206");
			strcpy_s(detailField.ExchangeID, "SHFE");

			int rf = g_pTdApi->ReqQryInvestorPositionCombineDetail(&detailField, 0);
			if (!rf)
				std::cout << "�����ѯͶ������ϳֲ���ϸ��Ϣ���ͳɹ�" << std::endl;
			else
				std::cerr << "�����ѯͶ������ϳֲ���ϸ��Ϣ����ʧ��" << std::endl;
		}

		// �����ѯͶ���ֲ߳���ϸ
		if (g_CtpTdApiWrapperParams.isReqQryInvestorPositionDetail) 
		{
			CThostFtdcQryInvestorPositionDetailField detailField = { '\0' };
			strcpy_s(detailField.BrokerID, gBrokerID);
			strcpy_s(detailField.InvestorID, gInvesterID);
			strcpy_s(detailField.InstrumentID, "ag2206");
			strcpy_s(detailField.ExchangeID, "SHFE");

			int rf = g_pTdApi->ReqQryInvestorPositionDetail(&detailField, 0);
			if (!rf)
				std::cout << "�����ѯͶ������ϳֲ���ϸ��Ϣ���ͳɹ�" << std::endl;
			else
				std::cerr << "�����ѯͶ������ϳֲ���ϸ��Ϣ����ʧ��" << std::endl;
		}

		// �����ѯת������
		if (g_CtpTdApiWrapperParams.isReqQryTransferBank) 
		{
			CThostFtdcQryTransferBankField bankField = { '\0' };
			strcpy_s(bankField.BankID, "999");
			//strcpy_s(bankField.BankBrchID, "");

			int rf = g_pTdApi->ReqQryTransferBank(&bankField, 0);
			if (!rf)
				std::cout << "�����ѯת��������Ϣ���ͳɹ�" << std::endl;
			else
				std::cerr << "�����ѯת��������Ϣ����ʧ��" << std::endl;
		}

		// �����ѯͶ���߽�����Ϣ
		if (g_CtpTdApiWrapperParams.isReqQrySettlementInfo) 
		{
			CThostFtdcQrySettlementInfoField settlementInfoField = { '\0' };
			strcpy_s(settlementInfoField.BrokerID, gBrokerID);
			strcpy_s(settlementInfoField.InvestorID, gInvesterID);
			strcpy_s(settlementInfoField.TradingDay, "20220216");

			int rf = g_pTdApi->ReqQrySettlementInfo(&settlementInfoField, 0);
			if (!rf)
				std::cout << "�����ѯͶ���߽�����Ϣ���ͳɹ�" << std::endl;
			else
				std::cerr << "�����ѯͶ���߽�����Ϣ����ʧ��" << std::endl;
		}

		// �����ѯ����
		if (g_CtpTdApiWrapperParams.isReqQryDepthMarketData) 
		{
			CThostFtdcQryDepthMarketDataField marketDataField = { '\0' };
			strcpy_s(marketDataField.InstrumentID, "ag2206");
			strcpy_s(marketDataField.ExchangeID, "SHFE");

			int rf = g_pTdApi->ReqQryDepthMarketData(&marketDataField, 0);
			if (!rf)
				std::cout << "�����ѯ������Ϣ���ͳɹ�" << std::endl;
			else
				std::cerr << "�����ѯ������Ϣ����ʧ��" << std::endl;
		}

		// �����ѯ��Լ
		if (g_CtpTdApiWrapperParams.isReqQryInstrument) 
		{
			CThostFtdcQryInstrumentField instrumentField = { '\0' };
			strcpy_s(instrumentField.InstrumentID, "ag2206");
			strcpy_s(instrumentField.ExchangeID, "SHFE");

			int rf = g_pTdApi->ReqQryInstrument(&instrumentField, 0);
			if (!rf)
				std::cout << "�����ѯ��Լ��Ϣ���ͳɹ�" << std::endl;
			else
				std::cerr << "�����ѯ��Լ��Ϣ����ʧ��" << std::endl;
		}

		// �����ѯ������
		if (g_CtpTdApiWrapperParams.isReqQryExchange) 
		{
			CThostFtdcQryExchangeField exchangeField = { '\0' };			
			strcpy_s(exchangeField.ExchangeID, "SHFE");

			int rf = g_pTdApi->ReqQryExchange(&exchangeField, 0);
			if (!rf)
				std::cout << "�����ѯ��������Ϣ���ͳɹ�" << std::endl;
			else
				std::cerr << "�����ѯ��������Ϣ����ʧ��" << std::endl;
		}

		// �����Լ��������
		if (g_CtpTdApiWrapperParams.isReqQryInstrumentCommissionRate) 
		{
			CThostFtdcQryInstrumentCommissionRateField commissionRateField = { '\0' };
			strcpy_s(commissionRateField.BrokerID, gBrokerID);
			strcpy_s(commissionRateField.InvestorID, gInvesterID);
			strcpy_s(commissionRateField.InstrumentID, "ag2206");
			strcpy_s(commissionRateField.ExchangeID, "SHFE");

			int rf = g_pTdApi->ReqQryInstrumentCommissionRate(&commissionRateField, 0);
			if (!rf)
				std::cout << "�����ѯ��Լ��������Ϣ���ͳɹ�" << std::endl;
			else
				std::cerr << "�����ѯ��Լ��������Ϣ����ʧ��" << std::endl;
		}

		// �����ѯ��Լ�ı�֤����
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
				std::cout << "�����ѯ��Լ�ı�֤������Ϣ���ͳɹ�" << std::endl;
			else
				std::cerr << "�����ѯ��Լ�ı�֤������Ϣ����ʧ��" << std::endl;
		}

		// �����ѯ�����߱��
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
				std::cout << "�����ѯ�����߱����Ϣ���ͳɹ�" << std::endl;
			else
				std::cerr << "�����ѯ�����߱����Ϣ����ʧ��" << std::endl;
		}

		// �����ѯͶ����
		if (g_CtpTdApiWrapperParams.isReqQryInvestor) 
		{
			CThostFtdcQryInvestorField investorField = { '\0' };
			strcpy_s(investorField.BrokerID, gBrokerID);
			strcpy_s(investorField.InvestorID, gInvesterID);			

			int rf = g_pTdApi->ReqQryInvestor(&investorField, 0);
			if (!rf)
				std::cout << "�����ѯ�����߱����Ϣ���ͳɹ�" << std::endl;
			else
				std::cerr << "�����ѯ�����߱����Ϣ����ʧ��" << std::endl;
		}

		// �����ѯ�ʽ��˻�
		if (g_CtpTdApiWrapperParams.isReqQryTradingAccount) 
		{
			CThostFtdcQryTradingAccountField accountField = { '\0' };
			strcpy_s(accountField.BrokerID, gBrokerID);
			strcpy_s(accountField.InvestorID, gInvesterID);
			strcpy_s(accountField.CurrencyID, "CNY");

			int rf = g_pTdApi->ReqQryTradingAccount(&accountField, 0);
			if (!rf)
				std::cout << "�����ѯ�ʽ��˻���Ϣ���ͳɹ�" << std::endl;
			else
				std::cerr << "�����ѯ�ʽ��˻���Ϣ����ʧ��" << std::endl;
		}

		// �����ѯͶ���ֲ߳�
		if (g_CtpTdApiWrapperParams.isReqQryInvestorPosition) 
		{
			CThostFtdcQryInvestorPositionField positionField = { '\0' };
			strcpy_s(positionField.BrokerID, gBrokerID);
			strcpy_s(positionField.InvestorID, gInvesterID);			
			strcpy_s(positionField.InstrumentID, "ag2206");
			strcpy_s(positionField.ExchangeID, "SHFE");

			int rf = g_pTdApi->ReqQryInvestorPosition(&positionField, 0);
			if (!rf)
				std::cout << "�����ѯͶ���ֲ߳���Ϣ���ͳɹ�" << std::endl;
			else
				std::cerr << "�����ѯͶ���ֲ߳���Ϣ����ʧ��" << std::endl;
		}

		// �����ѯ����
		if (g_CtpTdApiWrapperParams.isReqQryTrade) 
		{
			CThostFtdcQryTradeField tradingField = { '\0' };
			strcpy_s(tradingField.BrokerID, gBrokerID);
			strcpy_s(tradingField.InvestorID, gInvesterID);
			strcpy_s(tradingField.InstrumentID, "ag2206");
			strcpy_s(tradingField.ExchangeID, "SHFE");

			int rf = g_pTdApi->ReqQryTrade(&tradingField, 0);
			if (!rf)
				std::cout << "�����ѯ������Ϣ���ͳɹ�" << std::endl;
			else
				std::cerr << "�����ѯ������Ϣ����ʧ��" << std::endl;
		}

		//// ��ʼ��������
		//int rt = g_pTdApi->SubscribeMarketData(g_pInstrumentID, instrumentNum);
		//if (!rt)
		//	std::cout << ">>>>>>���Ͷ�����������ɹ�" << std::endl;
		//else
		//	std::cerr << "--->>>���Ͷ�����������ʧ��" << std::endl;
	}
	else
		std::cerr << "���ش���--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// �ǳ�Ӧ��
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

		std::cout << "=====�˻��ǳ��ɹ�=====" << std::endl;
		std::cout << "�����̣� " << pUserLogout->BrokerID << std::endl;
		std::cout << "�ʻ����� " << pUserLogout->UserID << std::endl;
	}
	else
		std::cerr << "���ش���--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// ��������Ӧ��
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

		std::cout << "=====�û���������ɹ�=====" << std::endl;
		std::cout << "���͹�˾���룺 " << pUserPasswordUpdate->BrokerID << std::endl;
		std::cout << "�û����룺 " << pUserPasswordUpdate->UserID << std::endl;
		std::cout << "ԭʼ���룺 " << pUserPasswordUpdate->OldPassword << std::endl;
		std::cout << "���º�����룺 " << pUserPasswordUpdate->NewPassword << std::endl;
	}
	else
		std::cerr << "���ش���--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// �����˻���������Ӧ��
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

		std::cout << "=====�û���������ɹ�=====" << std::endl;
		std::cout << "���͹�˾���룺 " << pTradingAccountPasswordUpdate->BrokerID << std::endl;
		std::cout << "Ͷ�����ʺţ� " << pTradingAccountPasswordUpdate->AccountID << std::endl;
		std::cout << "ԭʼ���룺 " << pTradingAccountPasswordUpdate->OldPassword << std::endl;
		std::cout << "���º�����룺 " << pTradingAccountPasswordUpdate->NewPassword << std::endl;
		std::cout << "���ִ��룺 " << pTradingAccountPasswordUpdate->CurrencyID << std::endl;

	}
	else
		std::cerr << "���ش���--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// ��������ʧ�ܸú������ص�
void WINAPI OnRspInsertOrder(
	CThostFtdcInputOrderField* pInputOrder, 
	CThostFtdcRspInfoField* pRspInfo, 
	int nRequestID, 
	bool bIsLast) 
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult) 
	{
		std::cout << "=====��������ʧ��=====" << std::endl;
		std::cout << "���͹�˾���룺 " << pInputOrder->BrokerID << std::endl;
		std::cout << "Ͷ���ߴ��룺 " << pInputOrder->InvestorID << std::endl;
		std::cout << "��Լ���룺 " << pInputOrder->InstrumentID << std::endl;
		std::cout << "�������ã� " << pInputOrder->OrderRef << std::endl;
		std::cout << "�û����룺 " << pInputOrder->UserID << std::endl;
		std::cout << "�����۸������� " << pInputOrder->OrderPriceType << std::endl;
		std::cout << "�������� " << pInputOrder->Direction << std::endl;
		std::cout << "��Ͽ�ƽ��־�� " << pInputOrder->CombOffsetFlag << std::endl;
		std::cout << "���Ͷ���ױ���־�� " << pInputOrder->CombHedgeFlag << std::endl;
		std::cout << "�۸� " << pInputOrder->LimitPrice << std::endl;
		std::cout << "������ " << pInputOrder->VolumeTotalOriginal << std::endl;
		std::cout << "��Ч�����ͣ� " << pInputOrder->TimeCondition << std::endl;
		std::cout << "GTD���ڣ� " << pInputOrder->GTDDate << std::endl;
		std::cout << "�ɽ������ͣ� " << pInputOrder->VolumeCondition << std::endl;
		std::cout << "��С�ɽ����� " << pInputOrder->MinVolume << std::endl;
		std::cout << "���������� " << pInputOrder->ContingentCondition << std::endl;
		std::cout << "ֹ��۸� " << pInputOrder->StopPrice << std::endl;
		std::cout << "��ƽԭ�� " << pInputOrder->ForceCloseReason << std::endl;
		std::cout << "�Զ������־�� " << pInputOrder->IsAutoSuspend << std::endl;
		std::cout << "ҵ��Ԫ�� " << pInputOrder->BusinessUnit << std::endl;
		std::cout << "�����ţ� " << pInputOrder->RequestID << std::endl;
		std::cout << "�û�ǿƽ��־�� " << pInputOrder->UserForceClose << std::endl;
		std::cout << "��������־�� " << pInputOrder->IsSwapOrder << std::endl;
		std::cout << "���������룺 " << pInputOrder->ExchangeID << std::endl;
		std::cout << "Ͷ�ʵ�Ԫ���룺 " << pInputOrder->InvestUnitID << std::endl;
		std::cout << "�ʽ��˻��� " << pInputOrder->AccountID << std::endl;
		std::cout << "���ִ��룺 " << pInputOrder->CurrencyID << std::endl;
		std::cout << "���ױ��룺 " << pInputOrder->ClientID << std::endl;
		std::cout << "IP��ַ�� " << pInputOrder->IPAddress << std::endl;
		std::cout << "Mac��ַ�� " << pInputOrder->MacAddress << std::endl;		
	}
	else
		std::cerr << "���ش���--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// ������ ctp �ܾ���ص�
void WINAPI OnErrRtnOrderInsert(
	CThostFtdcInputOrderField* pInputOrder, 
	CThostFtdcRspInfoField* pRspInfo) 
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult)
	{
		std::cout << "=====��������ʧ��=====" << std::endl;
		std::cout << "���͹�˾���룺 " << pInputOrder->BrokerID << std::endl;
		std::cout << "Ͷ���ߴ��룺 " << pInputOrder->InvestorID << std::endl;
		std::cout << "��Լ���룺 " << pInputOrder->InstrumentID << std::endl;
		std::cout << "�������ã� " << pInputOrder->OrderRef << std::endl;
		std::cout << "�û����룺 " << pInputOrder->UserID << std::endl;
		std::cout << "�����۸������� " << pInputOrder->OrderPriceType << std::endl;
		std::cout << "�������� " << pInputOrder->Direction << std::endl;
		std::cout << "��Ͽ�ƽ��־�� " << pInputOrder->CombOffsetFlag << std::endl;
		std::cout << "���Ͷ���ױ���־�� " << pInputOrder->CombHedgeFlag << std::endl;
		std::cout << "�۸� " << pInputOrder->LimitPrice << std::endl;
		std::cout << "������ " << pInputOrder->VolumeTotalOriginal << std::endl;
		std::cout << "��Ч�����ͣ� " << pInputOrder->TimeCondition << std::endl;
		std::cout << "GTD���ڣ� " << pInputOrder->GTDDate << std::endl;
		std::cout << "�ɽ������ͣ� " << pInputOrder->VolumeCondition << std::endl;
		std::cout << "��С�ɽ����� " << pInputOrder->MinVolume << std::endl;
		std::cout << "���������� " << pInputOrder->ContingentCondition << std::endl;
		std::cout << "ֹ��۸� " << pInputOrder->StopPrice << std::endl;
		std::cout << "��ƽԭ�� " << pInputOrder->ForceCloseReason << std::endl;
		std::cout << "�Զ������־�� " << pInputOrder->IsAutoSuspend << std::endl;
		std::cout << "ҵ��Ԫ�� " << pInputOrder->BusinessUnit << std::endl;
		std::cout << "�����ţ� " << pInputOrder->RequestID << std::endl;
		std::cout << "�û�ǿƽ��־�� " << pInputOrder->UserForceClose << std::endl;
		std::cout << "��������־�� " << pInputOrder->IsSwapOrder << std::endl;
		std::cout << "���������룺 " << pInputOrder->ExchangeID << std::endl;
		std::cout << "Ͷ�ʵ�Ԫ���룺 " << pInputOrder->InvestUnitID << std::endl;
		std::cout << "�ʽ��˻��� " << pInputOrder->AccountID << std::endl;
		std::cout << "���ִ��룺 " << pInputOrder->CurrencyID << std::endl;
		std::cout << "���ױ��룺 " << pInputOrder->ClientID << std::endl;
		std::cout << "IP��ַ�� " << pInputOrder->IPAddress << std::endl;
		std::cout << "Mac��ַ�� " << pInputOrder->MacAddress << std::endl;
	}
	else
		std::cerr << "���ش���--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
};

// ����֪ͨ��֪ͨ���ƣ� ctp ��̨��֤ͨ���ͻ�֪ͨһ��(��ζ�����û���ϱ��ɹ���)
void WINAPI OnRtnOrder(
	CThostFtdcOrderField* pOrder)
{
	//  �����Ѿ��ύ��������
	if (pOrder->OrderSysID != NULL && pOrder->OrderSysID[0] != '\0') {
		g_orderInsertOK = true;
		g_cond_va.notify_one();

		// ��ǰ�����Ѿ�������������ʼ����
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
				std::cout << "<<<<<<���ͳ�������ɹ�" << std::endl;
			else 
				std::cout << "------>���ͳ�������ʧ��" << std::endl;

			g_CtpTdApiWrapperParams.isOrderAction = false;
		}
		else {
			g_orderActionOK = true;
			g_cond_va.notify_one();
		}

		// ��ѯ����
		if (g_CtpTdApiWrapperParams.isQryQuote) {
			CThostFtdcQryQuoteField qryQuoteField = { '\0' };
			strcpy_s(qryQuoteField.BrokerID, gBrokerID);
			strcpy_s(qryQuoteField.InvestorID, gInvesterID);
			strcpy_s(qryQuoteField.InstrumentID, pOrder->InstrumentID);
			strcpy_s(qryQuoteField.ExchangeID, pOrder->ExchangeID);
			strcpy_s(qryQuoteField.QuoteSysID, pOrder->OrderSysID);

			int rf = g_pTdApi->ReqQryQuote(&qryQuoteField, 0);
			if (!rf)
				std::cout << "<<<<<<���Ͳ�ѯ��������ɹ�" << std::endl;
			else
				std::cout << "------>���Ͳ�ѯ��������ʧ��" << std::endl;
		}
	}

	std::cout << "=====��������ɹ���OnRtnOrder�ص�=====" << std::endl;
	std::cout << "���͹�˾���룺 " << pOrder->BrokerID << std::endl;
	std::cout << "Ͷ���ߴ��룺 " << pOrder->InvestorID << std::endl;
	std::cout << "��Լ���룺 " << pOrder->InstrumentID << std::endl;
	std::cout << "�������ã� " << pOrder->OrderRef << std::endl;
	std::cout << "�û����룺 " << pOrder->UserID << std::endl;
	std::cout << "�����۸������� " << pOrder->OrderPriceType << std::endl;
	std::cout << "�������� " << pOrder->Direction << std::endl;
	std::cout << "��Ͽ�ƽ��־�� " << pOrder->CombOffsetFlag << std::endl;
	std::cout << "���Ͷ���ױ���־�� " << pOrder->CombHedgeFlag << std::endl;
	std::cout << "�۸� " << pOrder->LimitPrice << std::endl;
	std::cout << "������ " << pOrder->VolumeTotalOriginal << std::endl;
	std::cout << "��Ч�����ͣ� " << pOrder->TimeCondition << std::endl;
	std::cout << "GTD���ڣ� " << pOrder->GTDDate << std::endl;
	std::cout << "�ɽ������ͣ� " << pOrder->VolumeCondition << std::endl;
	std::cout << "��С�ɽ����� " << pOrder->MinVolume << std::endl;
	std::cout << "���������� " << pOrder->ContingentCondition << std::endl;
	std::cout << "ֹ��۸� " << pOrder->StopPrice << std::endl;
	std::cout << "��ƽԭ�� " << pOrder->ForceCloseReason << std::endl;
	std::cout << "�Զ������־�� " << pOrder->IsAutoSuspend << std::endl;
	std::cout << "ҵ��Ԫ�� " << pOrder->BusinessUnit << std::endl;
	std::cout << "�����ţ� " << pOrder->RequestID << std::endl;
	std::cout << "�û�ǿƽ��־�� " << pOrder->UserForceClose << std::endl;
	std::cout << "��������־�� " << pOrder->IsSwapOrder << std::endl;
	std::cout << "���������룺 " << pOrder->ExchangeID << std::endl;
	std::cout << "Ͷ�ʵ�Ԫ���룺 " << pOrder->InvestUnitID << std::endl;
	std::cout << "�ʽ��˻��� " << pOrder->AccountID << std::endl;
	std::cout << "���ִ��룺 " << pOrder->CurrencyID << std::endl;
	std::cout << "���ױ��룺 " << pOrder->ClientID << std::endl;

}

// ����֪ͨ
void WINAPI OnRtnTrade(
	CThostFtdcTradeField* pTrade) 
{
	std::cout << "=====��������ɹ���OnRtnTrade�ص�=====" << std::endl;
	std::cout << "���͹�˾���룺 " << pTrade->BrokerID << std::endl;
	std::cout << "Ͷ���ߴ��룺 " << pTrade->InvestorID << std::endl;
	std::cout << "��Լ���룺 " << pTrade->InstrumentID << std::endl;
	std::cout << "�������ã� " << pTrade->OrderRef << std::endl;
	std::cout << "�û����룺 " << pTrade->UserID << std::endl;	
	std::cout << "�������� " << pTrade->Direction << std::endl;
	std::cout << "������ţ�" << pTrade->OrderSysID << std::endl;
}

// Ԥ��������Ӧ
void WINAPI OnRspParkedOrderInsert(CThostFtdcParkedOrderField* pParkedOrder, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) 
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (bResult) 
	{

		g_parkedOrderInsertOK = true;
		g_cond_va.notify_one();

		std::cout << "=====Ԥ������ɹ�=====" << std::endl;
		std::cout << "���͹�˾���룺 " << pParkedOrder->BrokerID << std::endl;
		std::cout << "Ͷ���ߴ��룺 " << pParkedOrder->InvestorID << std::endl;
		std::cout << "��Լ���룺 " << pParkedOrder->InstrumentID << std::endl;
		std::cout << "�������ã� " << pParkedOrder->OrderRef << std::endl;
		std::cout << "�û����룺 " << pParkedOrder->UserID << std::endl;
		std::cout << "�����۸������� " << pParkedOrder->OrderPriceType << std::endl;
		std::cout << "�������� " << pParkedOrder->Direction << std::endl;
		std::cout << "��Ͽ�ƽ��־�� " << pParkedOrder->CombOffsetFlag << std::endl;
		std::cout << "���Ͷ���ױ���־�� " << pParkedOrder->CombHedgeFlag << std::endl;
		std::cout << "�۸� " << pParkedOrder->LimitPrice << std::endl;
		std::cout << "������ " << pParkedOrder->VolumeTotalOriginal << std::endl;
		std::cout << "��Ч�����ͣ� " << pParkedOrder->TimeCondition << std::endl;
		std::cout << "GTD���ڣ� " << pParkedOrder->GTDDate << std::endl;
		std::cout << "�ɽ������ͣ� " << pParkedOrder->VolumeCondition << std::endl;
		std::cout << "��С�ɽ����� " << pParkedOrder->MinVolume << std::endl;
		std::cout << "���������� " << pParkedOrder->ContingentCondition << std::endl;
		std::cout << "ֹ��۸� " << pParkedOrder->StopPrice << std::endl;
		std::cout << "��ƽԭ�� " << pParkedOrder->ForceCloseReason << std::endl;
		std::cout << "�Զ������־�� " << pParkedOrder->IsAutoSuspend << std::endl;
		std::cout << "ҵ��Ԫ�� " << pParkedOrder->BusinessUnit << std::endl;
		std::cout << "�����ţ� " << pParkedOrder->RequestID << std::endl;
		std::cout << "�û�ǿƽ��־�� " << pParkedOrder->UserForceClose << std::endl;
		std::cout << "��������־�� " << pParkedOrder->IsSwapOrder << std::endl;
		std::cout << "���������룺 " << pParkedOrder->ExchangeID << std::endl;
		std::cout << "Ͷ�ʵ�Ԫ���룺 " << pParkedOrder->InvestUnitID << std::endl;
		std::cout << "�ʽ��˻��� " << pParkedOrder->AccountID << std::endl;
		std::cout << "���ִ��룺 " << pParkedOrder->CurrencyID << std::endl;
		std::cout << "���ױ��룺 " << pParkedOrder->ClientID << std::endl;

		// ɾ���񵥳ɹ��ĵ���
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
				std::cout << "����ɾ��Ԥ������ɹ�" << std::endl;
			else
				std::cerr << "����ɾ��Ԥ������ʧ��" << std::endl;
		}
	}
	else
		std::cerr << "���ش���--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
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

		std::cout << "=====�޸��񵥻ص�=====" << std::endl;
		std::cout << "���͹�˾���룺" << pParkedOrderAction->BrokerID <<std::endl;
		std::cout << "Ͷ���ߴ��룺" << pParkedOrderAction->InvestorID << std::endl;
		std::cout << "�����������ã�" << pParkedOrderAction->OrderActionRef << std::endl;
		std::cout << "�������ã�" << pParkedOrderAction->OrderRef << std::endl;
		std::cout << "�����ţ�" << pParkedOrderAction->RequestID << std::endl;
		std::cout << "ǰ�ñ�ţ�" << pParkedOrderAction->FrontID << std::endl;
		std::cout << "�ỰID��" << pParkedOrderAction->SessionID << std::endl;
		std::cout << "��������ţ�" << pParkedOrderAction->ExchangeID << std::endl;
		std::cout << "������ţ�" << pParkedOrderAction->OrderSysID << std::endl;
		std::cout << "������ʶ��" << pParkedOrderAction->ActionFlag << std::endl;
		std::cout << "�۸�" << pParkedOrderAction->LimitPrice << std::endl;
		std::cout << "�����仯��" << pParkedOrderAction->VolumeChange << std::endl;
		std::cout << "�û����룺" << pParkedOrderAction->UserID << std::endl;
		std::cout << "��Լ���룺" << pParkedOrderAction->InstrumentID << std::endl;
		std::cout << "Ԥ�񳷵�����ţ�" << pParkedOrderAction->ParkedOrderActionID << std::endl;
		std::cout << "�û����ͣ�" << pParkedOrderAction->UserType << std::endl;
		std::cout << "Ԥ��״̬��" << pParkedOrderAction->Status << std::endl;
		std::cout << "�����룺" << pParkedOrderAction->ErrorID << std::endl;
		std::cout << "������Ϣ��" << pParkedOrderAction->ErrorMsg << std::endl;
		std::cout << "Ͷ�ʵ�Ԫ���룺" << pParkedOrderAction->InvestUnitID << std::endl;
		std::cout << "IP��ַ��" << pParkedOrderAction->IPAddress << std::endl;
		std::cout << "mac��ַ��" << pParkedOrderAction->MacAddress << std::endl;
	}
	else
		std::cerr << "���ش���--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// ��ѯ������Ӧ
void WINAPI OnRspQryOrder(CThostFtdcOrderField* pOrder, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) 
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult) {
		g_qryOrderOK = true;
		g_cond_va.notify_one();

		std::cout << "====��ѯ������Ӧ====" << std::endl;
		std::cout << "���͹�˾���룺 " << pOrder->BrokerID << std::endl;
		std::cout << "Ͷ���ߴ��룺 " << pOrder->InvestorID << std::endl;
		std::cout << "��Լ���룺 " << pOrder->InstrumentID << std::endl;
		std::cout << "�������ã� " << pOrder->OrderRef << std::endl;
		std::cout << "�û����룺 " << pOrder->UserID << std::endl;
		std::cout << "�����۸������� " << pOrder->OrderPriceType << std::endl;
		std::cout << "�������� " << pOrder->Direction << std::endl;
		std::cout << "��Ͽ�ƽ��־�� " << pOrder->CombOffsetFlag << std::endl;
		std::cout << "���Ͷ���ױ���־�� " << pOrder->CombHedgeFlag << std::endl;
		std::cout << "�۸� " << pOrder->LimitPrice << std::endl;
		std::cout << "������ " << pOrder->VolumeTotalOriginal << std::endl;
		std::cout << "��Ч�����ͣ� " << pOrder->TimeCondition << std::endl;
		std::cout << "GTD���ڣ� " << pOrder->GTDDate << std::endl;
		std::cout << "�ɽ������ͣ� " << pOrder->VolumeCondition << std::endl;
		std::cout << "��С�ɽ����� " << pOrder->MinVolume << std::endl;
		std::cout << "���������� " << pOrder->ContingentCondition << std::endl;
		std::cout << "ֹ��۸� " << pOrder->StopPrice << std::endl;
		std::cout << "��ƽԭ�� " << pOrder->ForceCloseReason << std::endl;
		std::cout << "�Զ������־�� " << pOrder->IsAutoSuspend << std::endl;
		std::cout << "ҵ��Ԫ�� " << pOrder->BusinessUnit << std::endl;
		std::cout << "�����ţ� " << pOrder->RequestID << std::endl;
		std::cout << "�û�ǿƽ��־�� " << pOrder->UserForceClose << std::endl;
		std::cout << "��������־�� " << pOrder->IsSwapOrder << std::endl;
		std::cout << "���������룺 " << pOrder->ExchangeID << std::endl;
	}
	else
		std::cerr << "���ش���--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// ��ѯ��󶩵�����Ӧ
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

		std::cout << "====��ѯ��󶩵�����Ӧ====" << std::endl;
		std::cout << "���͹�˾���룺 " << pQueryMaxOrderVolume->BrokerID << std::endl;
		std::cout << "Ͷ���ߴ��룺 " << pQueryMaxOrderVolume->InvestorID << std::endl;
		std::cout << "��Լ���룺 " << pQueryMaxOrderVolume->InstrumentID << std::endl;
		std::cout << "�������� " << pQueryMaxOrderVolume->Direction << std::endl;
		std::cout << "��ƽ��־�� " << pQueryMaxOrderVolume->OffsetFlag << std::endl;
		std::cout << "Ͷ���ױ���־�� " << pQueryMaxOrderVolume->HedgeFlag << std::endl;
		std::cout << "��������������� " << pQueryMaxOrderVolume->MaxVolume << std::endl;
		std::cout << "���������룺 " << pQueryMaxOrderVolume->ExchangeID << std::endl;
		std::cout << "Ͷ�ʵ�Ԫ���룺 " << pQueryMaxOrderVolume->InvestUnitID << std::endl;
	}
	else
		std::cerr << "���ش���--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// Ͷ���߽�����ȷ�ϻص�
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

		std::cout << "====Ͷ���߽�����ȷ�ϻص�====" << std::endl;
		std::cout << "���͹�˾���룺" << pSettlementInfoConfirm->BrokerID << std::endl;
		std::cout << "Ͷ���ߴ��룺 " << pSettlementInfoConfirm->InvestorID << std::endl;
		std::cout << "ȷ�����ڣ� " << pSettlementInfoConfirm->ConfirmDate << std::endl;
		std::cout << "ȷ��ʱ�䣺 " << pSettlementInfoConfirm->ConfirmTime << std::endl;
		std::cout << "�����ţ� " << pSettlementInfoConfirm->SettlementID << std::endl;
		std::cout << "Ͷ�����˺ţ� " << pSettlementInfoConfirm->AccountID << std::endl;
		std::cout << "���ִ��룺 " << pSettlementInfoConfirm->CurrencyID << std::endl;
	}
	else 
		std::cerr << "���ش���--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// ѯ��ʧ����Ӧ
void WINAPI OnRspForQuoteInsert(
	CThostFtdcForQuoteField* pForQuote, 
	CThostFtdcRspInfoField* pRspInfo, 
	int nRequestID, 
	bool bIsLast)
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult) {
		std::cout << "====ѯ��ʧ����Ӧ��OnRspForQuoteInsert====" << std::endl;
		std::cout << "���͹�˾���룺" << pForQuote->BrokerID << std::endl;
		std::cout << "Ͷ���ߴ��룺 " << pForQuote->InvestorID << std::endl;
		std::cout << "��Լ���룺 " << pForQuote->InstrumentID << std::endl;
		std::cout << "ѯ�����ã� " << pForQuote->ForQuoteRef << std::endl;
		std::cout << "�û����룺 " << pForQuote->UserID << std::endl;
		std::cout << "���������� " << pForQuote->ExchangeID << std::endl;
		std::cout << "Ͷ�ʵ�Ԫ���룺 " << pForQuote->InvestUnitID << std::endl;
	}
	else
		std::cerr << "���ش���--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// ѯ�۴�����Ӧ
void WINAPI OnErrRtnForQuoteInsert(
	CThostFtdcInputForQuoteField* pInputForQuote, 
	CThostFtdcRspInfoField* pRspInfo) 
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult) {
		std::cout << "====ѯ��ʧ����Ӧ��OnErrRtnForQuoteInsert====" << std::endl;
		std::cout << "���͹�˾���룺" << pInputForQuote->BrokerID << std::endl;
		std::cout << "Ͷ���ߴ��룺 " << pInputForQuote->InvestorID << std::endl;
		std::cout << "��Լ���룺 " << pInputForQuote->InstrumentID << std::endl;
		std::cout << "ѯ�����ã� " << pInputForQuote->ForQuoteRef << std::endl;
		std::cout << "�û����룺 " << pInputForQuote->UserID << std::endl;
		std::cout << "���������� " << pInputForQuote->ExchangeID << std::endl;
		std::cout << "Ͷ�ʵ�Ԫ���룺 " << pInputForQuote->InvestUnitID << std::endl;
	}
	else
		std::cerr << "���ش���--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// �˽ӿ���ʱ������
void WINAPI OnRtnForQuoteRsp(CThostFtdcForQuoteRspField* pForQuoteRsp) 
{
};

// ������Ӧ
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

		std::cout << "====���󱨼���Ӧ====" << std::endl;
		std::cout << "���͹�˾���룺" << pQuote->BrokerID << std::endl;
		std::cout << "Ͷ���ߴ��룺 " << pQuote->InvestorID << std::endl;
		std::cout << "��Լ���룺 " << pQuote->InstrumentID << std::endl;
		std::cout << "�������ã� " << pQuote->QuoteRef << std::endl;
		std::cout << "�û����룺 " << pQuote->UserID << std::endl;
		std::cout << "���۸� " << pQuote->AskPrice << std::endl;
		std::cout << "��۸� " << pQuote->BidPrice << std::endl;
		std::cout << "�������� " << pQuote->AskVolume << std::endl;
		std::cout << "�������� " << pQuote->BidVolume << std::endl;
		std::cout << "�����ţ� " << pQuote->RequestID << std::endl;
		std::cout << "���������� " << pQuote->ExchangeID << std::endl;
		std::cout << "Ͷ�ʵ�Ԫ���룺 " << pQuote->InvestUnitID << std::endl;
	}
	else
		std::cerr << "���ش���--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// ������ϵ���Ӧ
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

		std::cout << "====������ϵ���Ӧ====" << std::endl;
		std::cout << "���͹�˾���룺 " << pCombAction->BrokerID << std::endl;
		std::cout << "Ͷ���ߴ��룺 " << pCombAction->InvestorID << std::endl;
		std::cout << "��Լ���룺 " << pCombAction->InstrumentID << std::endl;
		std::cout << "������ã� " << pCombAction->CombActionRef << std::endl;
		std::cout << "�û����룺 " << pCombAction->UserID << std::endl;		
		std::cout << "�������� " << pCombAction->Direction << std::endl;
		std::cout << "������ " << pCombAction->Volume << std::endl;
		std::cout << "���ָ��� " << pCombAction->CombDirection << std::endl;
		std::cout << "Ͷ���ױ���־�� " << pCombAction->HedgeFlag << std::endl;
		std::cout << "����������ϱ�ţ� " << pCombAction->ActionLocalID << std::endl;
		std::cout << "���������룺 " << pCombAction->ExchangeID << std::endl;
		std::cout << "��Ա���룺 " << pCombAction->ParticipantID << std::endl;
		std::cout << "�ͻ����룺 " << pCombAction->ClientID << std::endl;
		std::cout << "��Լ�ڽ��������룺 " << pCombAction->ExchangeInstID << std::endl;
		std::cout << "����������Ա���룺 " << pCombAction->TraderID << std::endl;
		std::cout << "��װ��ţ� " << pCombAction->InstallID << std::endl;
		std::cout << "���״̬�� " << pCombAction->ActionStatus << std::endl;
		std::cout << "������ʾ��ţ� " << pCombAction->NotifySequence << std::endl;
		std::cout << "�����գ� " << pCombAction->TradingDay << std::endl;
		std::cout << "�����ţ� " << pCombAction->SettlementID << std::endl;
		std::cout << "��ţ� " << pCombAction->SequenceNo << std::endl;
		std::cout << "ǰ�ñ�ţ� " << pCombAction->FrontID << std::endl;
		std::cout << "�ỰID�� " << pCombAction->SessionID << std::endl;
		std::cout << "�û��˲�Ʒ��Ϣ�� " << pCombAction->UserProductInfo << std::endl;
	}
	else
		std::cerr << "���ش���--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// ��ѯ��Ϻ�Լ��ȫϵ����Ӧ
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

		std::cout << "====������ϵ���Ӧ====" << std::endl;
		std::cout << "���͹�˾���룺 " << pCombInstrumentGuard->BrokerID << std::endl;		
		std::cout << "��Լ���룺 " << pCombInstrumentGuard->InstrumentID << std::endl;
		std::cout << "��ȫϵ���� " << pCombInstrumentGuard->GuarantRatio << std::endl;
		std::cout << "���������룺 " << pCombInstrumentGuard->ExchangeID << std::endl;
	}
	else
		std::cerr << "���ش���--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// ��ѯ�ʽ�ת�˼�¼
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

		std::cout << "====��ѯת�˼�¼��Ӧ====" << std::endl;
		std::cout << "ƽ̨��ˮ�ţ� " << pTransferSerial->PlateSerial << std::endl;
		std::cout << "���׷������ڣ� " << pTransferSerial->TradeDate << std::endl;
		std::cout << "�������ڣ� " << pTransferSerial->TradingDay << std::endl;
		std::cout << "����ʱ�䣺 " << pTransferSerial->TradeTime << std::endl;
		std::cout << "���״��룺 " << pTransferSerial->TradeCode << std::endl;
		std::cout << "�Ự��ţ� " << pTransferSerial->SessionID << std::endl;
		std::cout << "���б�ţ� " << pTransferSerial->BankID << std::endl;
		std::cout << "���з�֧������ţ� " << pTransferSerial->BankBranchID << std::endl;
		std::cout << "�����ʺ����ͣ� " << pTransferSerial->BankAccType << std::endl;
		std::cout << "�����ʺţ� " << pTransferSerial->BankAccount << std::endl;
		std::cout << "������ˮ�ţ� " << pTransferSerial->BankSerial << std::endl;
		std::cout << "�ڻ���˾��ţ� " << pTransferSerial->BrokerID << std::endl;
		std::cout << "���̷�֧���ţ� " << pTransferSerial->BrokerBranchID << std::endl;
		std::cout << "�ڻ���˾�˺����ͣ� " << pTransferSerial->FutureAccType << std::endl;
		std::cout << "Ͷ�����˺ţ� " << pTransferSerial->AccountID << std::endl;
		std::cout << "Ͷ���ߴ��룺 " << pTransferSerial->InvestorID << std::endl;
		std::cout << "�ڻ���˾��ˮ�ţ� " << pTransferSerial->FutureSerial << std::endl;
		std::cout << "֤�����ͣ� " << pTransferSerial->IdCardType << std::endl;
		std::cout << "֤�����룺 " << pTransferSerial->IdentifiedCardNo << std::endl;
		std::cout << "���ִ��룺 " << pTransferSerial->CurrencyID << std::endl;
		std::cout << "���׽� " << pTransferSerial->TradeAmount << std::endl;
		std::cout << "Ӧ�տͻ����ã� " << pTransferSerial->CustFee << std::endl;
		std::cout << "Ӧ���ڻ���˾���ã� " << pTransferSerial->BrokerFee << std::endl;
		std::cout << "��Ч��־�� " << pTransferSerial->AvailabilityFlag << std::endl;
	}
	else
		std::cerr << "���ش���--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// ��ѯ����ǩԼ��ϵ��Ӧ
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

		std::cout << "====��ѯ����ǩԼ��ϵ��Ӧ====" << std::endl;
		std::cout << "�������ڣ� " << pAccountregister->TradeDay << std::endl;
		std::cout << "���б�ţ� " << pAccountregister->BankID << std::endl;
		std::cout << "���з�֧�������룺 " << pAccountregister->BankBranchID << std::endl;
		std::cout << "�����ʺţ� " << pAccountregister->BankAccount << std::endl;
		std::cout << "�ڻ���˾���룺 " << pAccountregister->BrokerID << std::endl;
		std::cout << "�ڻ���˾��֧�������룺 " << pAccountregister->BrokerBranchID << std::endl;
		std::cout << "Ͷ�����˺ţ� " << pAccountregister->AccountID << std::endl;
		std::cout << "֤�����ͣ� " << pAccountregister->IdCardType << std::endl;
		std::cout << "֤�����룺 " << pAccountregister->IdentifiedCardNo << std::endl;
		std::cout << "�ͻ������� " << pAccountregister->CustomerName << std::endl;
		std::cout << "���ִ��룺 " << pAccountregister->CurrencyID << std::endl;
		std::cout << "���������ͣ� " << pAccountregister->OpenOrDestroy << std::endl;
		std::cout << "ǩԼ���ڣ� " << pAccountregister->RegDate << std::endl;
		std::cout << "��Լ���ڣ� " << pAccountregister->OutDate << std::endl;
		std::cout << "����ID�� " << pAccountregister->TID << std::endl;
		std::cout << "�ͻ����ͣ� " << pAccountregister->CustType << std::endl;
		std::cout << "�����ʺ����ͣ� " << pAccountregister->BankAccType << std::endl;
	}
	else
		std::cerr << "���ش���--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// ��Լ״̬֪ͨ
void WINAPI OnRtnInstrumentStatus(
	CThostFtdcInstrumentStatusField* pInstrumentStatus) 
{
	g_instrumentStatusOK = true;
	g_cond_va.notify_one();

	std::cout << "====��Լ״̬֪ͨ====" << std::endl;
	std::cout << "���������룺 " << pInstrumentStatus->ExchangeID << std::endl;
	std::cout << "��Լ�ڽ������Ĵ��룺 " << pInstrumentStatus->ExchangeInstID << std::endl;
	std::cout << "��������룺 " << pInstrumentStatus->SettlementGroupID << std::endl;
	std::cout << "��Լ���룺 " << pInstrumentStatus->InstrumentID << std::endl;
	std::cout << "��Լ����״̬�� " << pInstrumentStatus->InstrumentStatus << std::endl;
	std::cout << "���׽׶α�ţ� " << pInstrumentStatus->TradingSegmentSN << std::endl;
	std::cout << "���뱾��ʱ�䣺 " << pInstrumentStatus->EnterTime << std::endl;
	std::cout << "���뱾��ʱ��ԭ�� " << pInstrumentStatus->EnterReason << std::endl;

}

// ����֪ͨ
void WINAPI OnRtnTradingNotice(
	CThostFtdcTradingNoticeInfoField* pTradingNoticeInfo) 
{
	g_TradingNoticeOK = true;
	g_cond_va.notify_one();

	std::cout << "====����֪ͨ====" << std::endl;
	std::cout << "���ù�˾���룺 " << pTradingNoticeInfo->BrokerID << std::endl;
	std::cout << "Ͷ���ߴ��룺 " << pTradingNoticeInfo->InvestorID << std::endl;
	std::cout << "����ʱ�䣺 " << pTradingNoticeInfo->SendTime << std::endl;
	std::cout << "��Ϣ���ģ� " << pTradingNoticeInfo->FieldContent << std::endl;
	std::cout << "����ϵ�кţ� " << pTradingNoticeInfo->SequenceSeries << std::endl;
	std::cout << "���кţ� " << pTradingNoticeInfo->SequenceNo << std::endl;
	std::cout << "Ͷ�ʵ�Ԫ���룺 " << pTradingNoticeInfo->InvestUnitID << std::endl;
}

// ��ѯǩԼ������Ӧ
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

		std::cout << "====��ѯǩԼ������Ӧ====" << std::endl;
		std::cout << "���ù�˾���룺 " << pContractBank->BrokerID << std::endl;
		std::cout << "���д��룺 " << pContractBank->BankID << std::endl;
		std::cout << "���з����Ĵ��룺 " << pContractBank->BankBrchID << std::endl;
		std::cout << "�������ƣ� " << pContractBank->BankName << std::endl;
	}
	else 
		std::cerr << "���ش���--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// ��ѯԤ����Ӧ
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

		std::cout << "=====��ѯԤ������ɹ�=====" << std::endl;
		std::cout << "���͹�˾���룺 " << pParkedOrder->BrokerID << std::endl;
		std::cout << "Ͷ���ߴ��룺 " << pParkedOrder->InvestorID << std::endl;
		std::cout << "��Լ���룺 " << pParkedOrder->InstrumentID << std::endl;
		std::cout << "�������ã� " << pParkedOrder->OrderRef << std::endl;
		std::cout << "�û����룺 " << pParkedOrder->UserID << std::endl;
		std::cout << "�����۸������� " << pParkedOrder->OrderPriceType << std::endl;
		std::cout << "�������� " << pParkedOrder->Direction << std::endl;
		std::cout << "��Ͽ�ƽ��־�� " << pParkedOrder->CombOffsetFlag << std::endl;
		std::cout << "���Ͷ���ױ���־�� " << pParkedOrder->CombHedgeFlag << std::endl;
		std::cout << "�۸� " << pParkedOrder->LimitPrice << std::endl;
		std::cout << "������ " << pParkedOrder->VolumeTotalOriginal << std::endl;
		std::cout << "��Ч�����ͣ� " << pParkedOrder->TimeCondition << std::endl;
		std::cout << "GTD���ڣ� " << pParkedOrder->GTDDate << std::endl;
		std::cout << "�ɽ������ͣ� " << pParkedOrder->VolumeCondition << std::endl;
		std::cout << "��С�ɽ����� " << pParkedOrder->MinVolume << std::endl;
		std::cout << "���������� " << pParkedOrder->ContingentCondition << std::endl;
		std::cout << "ֹ��۸� " << pParkedOrder->StopPrice << std::endl;
		std::cout << "��ƽԭ�� " << pParkedOrder->ForceCloseReason << std::endl;
		std::cout << "�Զ������־�� " << pParkedOrder->IsAutoSuspend << std::endl;
		std::cout << "ҵ��Ԫ�� " << pParkedOrder->BusinessUnit << std::endl;
		std::cout << "�����ţ� " << pParkedOrder->RequestID << std::endl;
		std::cout << "�û�ǿƽ��־�� " << pParkedOrder->UserForceClose << std::endl;
		std::cout << "��������־�� " << pParkedOrder->IsSwapOrder << std::endl;
		std::cout << "���������룺 " << pParkedOrder->ExchangeID << std::endl;
		std::cout << "Ͷ�ʵ�Ԫ���룺 " << pParkedOrder->InvestUnitID << std::endl;
		std::cout << "�ʽ��˻��� " << pParkedOrder->AccountID << std::endl;
		std::cout << "���ִ��룺 " << pParkedOrder->CurrencyID << std::endl;
		std::cout << "���ױ��룺 " << pParkedOrder->ClientID << std::endl;

	}
	else
		std::cerr << "���ش���--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// ��ѯԤ�񳷵�������Ӧ
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

		std::cout << "=====��ѯԤ������ɹ�=====" << std::endl;
		std::cout << "���͹�˾���룺 " << pParkedOrderAction->BrokerID << std::endl;
		std::cout << "Ͷ���ߴ��룺 " << pParkedOrderAction->InvestorID << std::endl;
		std::cout << "��Լ���룺 " << pParkedOrderAction->InstrumentID << std::endl;
		std::cout << "�������ã� " << pParkedOrderAction->OrderRef << std::endl;
		std::cout << "�û����룺 " << pParkedOrderAction->UserID << std::endl;		
		std::cout << "�۸� " << pParkedOrderAction->LimitPrice << std::endl;		
		std::cout << "�����ţ� " << pParkedOrderAction->RequestID << std::endl;		
		std::cout << "���������룺 " << pParkedOrderAction->ExchangeID << std::endl;
		std::cout << "Ͷ�ʵ�Ԫ���룺 " << pParkedOrderAction->InvestUnitID << std::endl;		

	}
	else
		std::cerr << "���ش���--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// ��ѯ����֪ͨ��Ӧ
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

		std::cout << "=====��ѯԤ������ɹ�=====" << std::endl;
		std::cout << "���ù�˾���룺 " << pTradingNotice->BrokerID << std::endl;
		std::cout << "Ͷ���ߴ��룺 " << pTradingNotice->InvestorID << std::endl;
		std::cout << "����ʱ�䣺 " << pTradingNotice->SendTime << std::endl;
		std::cout << "��Ϣ���ģ� " << pTradingNotice->FieldContent << std::endl;
		std::cout << "����ϵ�кţ� " << pTradingNotice->SequenceSeries << std::endl;
		std::cout << "���кţ� " << pTradingNotice->SequenceNo << std::endl;
		std::cout << "Ͷ�ʵ�Ԫ���룺 " << pTradingNotice->InvestUnitID << std::endl;
	}
	else 
		std::cerr << "���ش���--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// ��ѯ���ù�˾���ײ�����Ӧ
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

		std::cout << "=====��ѯ���ù�˾���ײ�����Ӧ=====" << std::endl;
		std::cout << "���ù�˾���룺 " << pBrokerTradingParams->BrokerID << std::endl;
		std::cout << "Ͷ���ߴ��룺 " << pBrokerTradingParams->InvestorID << std::endl;
		std::cout << "��֤��۸����ͣ� " << pBrokerTradingParams->MarginPriceType << std::endl;
		std::cout << "ӯ���㷨�� " << pBrokerTradingParams->Algorithm << std::endl;
		std::cout << "�����Ƿ����ƽ��ӯ���� " << pBrokerTradingParams->AvailIncludeCloseProfit << std::endl;
		std::cout << "���ִ��룺 " << pBrokerTradingParams->CurrencyID << std::endl;
		std::cout << "��ȨȨ����۸����ͣ� " << pBrokerTradingParams->OptionRoyaltyPriceType << std::endl;
	}
	else
		std::cerr << "���ش���--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// ��ѯ���ù�˾�����㷨��Ӧ
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

		std::cout << "=====��ѯ���ù�˾�����㷨��Ӧ=====" << std::endl;
		std::cout << "���ù�˾���룺 " << pBrokerTradingAlgos->BrokerID << std::endl;
		std::cout << "���������룺 " << pBrokerTradingAlgos->ExchangeID << std::endl;
		std::cout << "��Լ���룺 " << pBrokerTradingAlgos->InstrumentID << std::endl;
		std::cout << "�ֲִ����㷨��ţ� " << pBrokerTradingAlgos->HandlePositionAlgoID << std::endl;
		std::cout << "Ѱ�ұ�֤���ʱ�ţ� " << pBrokerTradingAlgos->FindMarginRateAlgoID << std::endl;
		std::cout << "�ʽ����㷨��ţ� " << pBrokerTradingAlgos->HandleTradingAccountAlgoID << std::endl;
	}
	else 
		std::cerr << "���ش���--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// �ڻ���ѯ�������֪ͨ
void WINAPI OnRtnQueryBankBalanceByFuture(
	CThostFtdcNotifyQueryAccountField* pNotifyQueryAccount) 
{
	g_queryBankBalanceByFutureOK = true;
	g_cond_va.notify_one();

	std::cout << "=====�ڻ���ѯ�������֪ͨ=====" << std::endl;
	std::cout << "ҵ�����룺 " << pNotifyQueryAccount->TradeCode << std::endl;
	std::cout << "���д��룺 " << pNotifyQueryAccount->BankID << std::endl;
	std::cout << "���з�֧�������룺 " << pNotifyQueryAccount->BankBranchID << std::endl;
	std::cout << "���̴��룺 " << pNotifyQueryAccount->BrokerID << std::endl;
	std::cout << "���̷�֧�������룺 " << pNotifyQueryAccount->BrokerBranchID << std::endl;
	std::cout << "�������ڣ� " << pNotifyQueryAccount->TradeDate << std::endl;

}

// �ڻ���ѯ����������ص�
void WINAPI OnRspQueryBankAccountMoneyByFuture(
	CThostFtdcReqQueryAccountField* pReqQueryAccount, 
	CThostFtdcRspInfoField* pRspInfo, 
	int nRequestID, 
	bool bIsLast) 
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult) {
		std::cout << "=====�ڻ���ѯ�������ʧ�ܻص�=====" << std::endl;
		std::cout << "ҵ�����룺 " << pReqQueryAccount->TradeCode << std::endl;
		std::cout << "���д��룺 " << pReqQueryAccount->BankID << std::endl;
		std::cout << "���з�֧�������룺 " << pReqQueryAccount->BankBranchID << std::endl;
		std::cout << "���̴��룺 " << pReqQueryAccount->BrokerID << std::endl;
		std::cout << "���̷�֧�������룺 " << pReqQueryAccount->BrokerBranchID << std::endl;
		std::cout << "�������ڣ� " << pReqQueryAccount->TradeDate << std::endl;
	}
	else 
		std::cerr << "���ش���--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// ��ѯ��������û�������Ӧ
void WINAPI OnRspQueryCFMMCTradingAccountToken(
	CThostFtdcQueryCFMMCTradingAccountTokenField* pQueryCFMMCTradingAccountToken, 
	CThostFtdcRspInfoField* pRspInfo, 
	int nRequestID, 
	bool bIsLast) 
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult) {
		std::cout << "=====��ѯ��������û�������Ӧ=====" << std::endl;
		std::cout << "���ù�˾���룺 " << pQueryCFMMCTradingAccountToken->BrokerID << std::endl;
		std::cout << "Ͷ���ߴ��룺 " << pQueryCFMMCTradingAccountToken->InvestorID << std::endl;
		std::cout << "Ͷ�ʵ�Ԫ���룺 " << pQueryCFMMCTradingAccountToken->InvestUnitID << std::endl;
	}
	else
		std::cerr << "���ش���--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// ��������û�����֪ͨ
void WINAPI OnRtnCFMMCTradingAccountToken(
	CThostFtdcCFMMCTradingAccountTokenField* pCFMMCTradingAccountToken) 
{
	g_queryCFMMCTradingAccountTokenOK = true;
	g_cond_va.notify_one();

	std::cout << "=====��������û�����֪ͨ=====" << std::endl;
	std::cout << "���ù�˾���룺 " << pCFMMCTradingAccountToken->BrokerID << std::endl;
	std::cout << "���ù�˾ͳһ���룺 " << pCFMMCTradingAccountToken->ParticipantID << std::endl;
	std::cout << "Ͷ�����˻��� " << pCFMMCTradingAccountToken->AccountID << std::endl;
	std::cout << "��Կ���룺 " << pCFMMCTradingAccountToken->KeyID << std::endl;
	std::cout << "��̬���ƣ� " << pCFMMCTradingAccountToken->Token << std::endl;
}

// �ڻ���������ת�ڻ�Ӧ��
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

		std::cout << "=====�ڻ���������ת�ڻ�Ӧ��=====" << std::endl;
		std::cout << "ҵ�����룺 " << pReqTransfer->TradeCode << std::endl;
		std::cout << "���д��룺 " << pReqTransfer->BankID << std::endl;
		std::cout << "���з�֧�ṹ���룺 " << pReqTransfer->BankBranchID << std::endl;
		std::cout << "���̴��룺 " << pReqTransfer->BrokerID << std::endl;
		std::cout << "���̷�֧�ṹ���룺 " << pReqTransfer->BrokerBranchID << std::endl;
		std::cout << "�������ڣ� " << pReqTransfer->TradeDate << std::endl;
		std::cout << "����ʱ�䣺 " << pReqTransfer->TradeTime << std::endl;
		std::cout << "������ˮ�ţ� " << pReqTransfer->BankSerial << std::endl;
		std::cout << "�������ڣ� " << pReqTransfer->TradingDay << std::endl;
		std::cout << "������Ϣ��ˮ�ţ� " << pReqTransfer->PlateSerial << std::endl;
		std::cout << "����Ƭ��־�� " << pReqTransfer->LastFragment << std::endl;
		std::cout << "�ỰID�� " << pReqTransfer->SessionID << std::endl;
		std::cout << "�ͻ����� " << pReqTransfer->CustomerName << std::endl;
		std::cout << "֤�����ͣ� " << pReqTransfer->IdCardType << std::endl;
	}
	else
		std::cerr << "���ش���--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// ��ѯͶ�ʵ�ԪӦ��
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

		std::cout << "=====��ѯͶ�ʵ�ԪӦ��=====" << std::endl;
		std::cout << "���ù�˾���룺 " << pInvestUnit->BrokerID << std::endl;
		std::cout << "Ͷ���ߴ��룺 " << pInvestUnit->InvestorID << std::endl;
		std::cout << "Ͷ�ʵ�Ԫ���룺 " << pInvestUnit->InvestUnitID << std::endl;
		std::cout << "Ͷ�ʵ�Ԫ���ƣ� " << pInvestUnit->InvestorUnitName << std::endl;
		std::cout << "Ͷ���߷�����룺 " << pInvestUnit->InvestorGroupID << std::endl;
		std::cout << "��������ģ����룺 " << pInvestUnit->CommModelID << std::endl;
		std::cout << "��֤����ģ����룺 " << pInvestUnit->MarginModelID << std::endl;
		std::cout << "�ʽ��˻��� " << pInvestUnit->AccountID << std::endl;
		std::cout << "���ִ��룺 " << pInvestUnit->CurrencyID << std::endl;		
	}
	else 
		std::cerr << "���ش���--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// �����ѯ�����г���Ӧ
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

		std::cout << "=====�����ѯ�����г�Ӧ��=====" << std::endl;
		std::cout << "���ù�˾���룺 " << pSecAgentTradeInfo->BrokerID << std::endl;
		std::cout << "��������ʽ��ʺţ� " << pSecAgentTradeInfo->BrokerSecAgentID << std::endl;
		std::cout << "Ͷ���ߴ��룺 " << pSecAgentTradeInfo->InvestorID << std::endl;
		std::cout << "���������������� " << pSecAgentTradeInfo->LongCustomerName << std::endl;
	}
	else
		std::cerr << "���ش���--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// �����ѯ�����������ʽ���֤ģʽ
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

		std::cout << "=====�����ѯ�����г�Ӧ��=====" << std::endl;
		std::cout << "���ù�˾���룺 " << pSecAgentCheckMode->BrokerID << std::endl;
		std::cout << "��������ʽ��ʺţ� " << pSecAgentCheckMode->BrokerSecAgentID << std::endl;
		std::cout << "Ͷ���ߴ��룺 " << pSecAgentCheckMode->InvestorID << std::endl;
		std::cout << "�������ͣ� " << pSecAgentCheckMode->CurrencyID << std::endl;
	}
	else
		std::cerr << "���ش���--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// ��ѯ�ʽ��˻�
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

		std::cout << "=====�����ѯͶ�����˻�Ӧ��=====" << std::endl;
		std::cout << "���ù�˾���룺 " << pTradingAccount->BrokerID << std::endl;
		std::cout << "Ͷ�����˻��� " << pTradingAccount->AccountID << std::endl;
		std::cout << "�ϴ���Ѻ�� " << pTradingAccount->PreMortgage << std::endl;
		std::cout << "�ϴ����ö�ȣ� " << pTradingAccount->PreCredit << std::endl;
		std::cout << "�ϴδ���ȣ� " << pTradingAccount->PreDeposit << std::endl;
		std::cout << "�ϴν��㱸�ý� " << pTradingAccount->PreBalance << std::endl;
		std::cout << "�ϴ�ռ�ñ��Ͻ� " << pTradingAccount->PreMargin << std::endl;
		std::cout << "��Ϣ������ " << pTradingAccount->InterestBase << std::endl;
		std::cout << "��Ϣ���룺 " << pTradingAccount->Interest << std::endl;
		std::cout << "���� " << pTradingAccount->Deposit << std::endl;
		std::cout << "����� " << pTradingAccount->Withdraw << std::endl;
		std::cout << "����ı��Ͻ� " << pTradingAccount->FrozenMargin << std::endl;
		std::cout << "������ʽ� " << pTradingAccount->FrozenCash << std::endl;
		std::cout << "����������ѣ� " << pTradingAccount->FrozenCommission << std::endl;
	}
	else 
		std::cerr << "���ش���--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// �����ѯ����������
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

		std::cout << "=====�����ѯ������������Ӧ=====" << std::endl;
		std::cout << "��Լ���룺 " << pInstrumentOrderCommRate->InstrumentID << std::endl;
		std::cout << "Ͷ���߷�Χ�� " << pInstrumentOrderCommRate->InvestorRange << std::endl;
		std::cout << "���ù�˾���룺 " << pInstrumentOrderCommRate->BrokerID << std::endl;
		std::cout << "Ͷ���ߴ��룺 " << pInstrumentOrderCommRate->InvestorID << std::endl;
		std::cout << "Ͷ���ױ���־�� " << pInstrumentOrderCommRate->HedgeFlag << std::endl;
		std::cout << "���������ѣ� " << pInstrumentOrderCommRate->OrderCommByVolume << std::endl;
		std::cout << "���������ѣ� " << pInstrumentOrderCommRate->OrderActionCommByVolume << std::endl;
		std::cout << "���������룺 " << pInstrumentOrderCommRate->ExchangeID << std::endl;
		std::cout << "Ͷ�ʵ�Ԫ���룺 " << pInstrumentOrderCommRate->InvestUnitID << std::endl;
	}
	else 
		std::cerr << "���ش���--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// �����ѯ��������������Ӧ
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

		std::cout << "=====�����ѯ�����̺�Լ��������Ӧ=====" << std::endl;
		std::cout << "��Լ���룺 " << pMMInstrumentCommissionRate->InstrumentID << std::endl;
		std::cout << "Ͷ���߷�Χ�� " << pMMInstrumentCommissionRate->InvestorRange << std::endl;
		std::cout << "���ù�˾���룺 " << pMMInstrumentCommissionRate->BrokerID << std::endl;
		std::cout << "Ͷ���ߴ��룺 " << pMMInstrumentCommissionRate->InvestorID << std::endl;
		std::cout << "�����������ʣ� " << pMMInstrumentCommissionRate->OpenRatioByMoney << std::endl;
		std::cout << "���������ѣ� " << pMMInstrumentCommissionRate->OpenRatioByVolume << std::endl;
		std::cout << "ƽ���������ʣ� " << pMMInstrumentCommissionRate->CloseRatioByMoney << std::endl;
		std::cout << "ƽ�������ѣ� " << pMMInstrumentCommissionRate->CloseRatioByVolume << std::endl;
		std::cout << "ƽ���������ʣ� " << pMMInstrumentCommissionRate->CloseTodayRatioByMoney << std::endl;
		std::cout << "ƽ�������ѣ� " << pMMInstrumentCommissionRate->CloseTodayRatioByVolume << std::endl;
	}
	else
		std::cerr << "���ش���--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// �����ѯ��Ʒ����Ӧ
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

		std::cout << "=====�����ѯ��Ʒ����Ӧ=====" << std::endl;
		std::cout << "��ƷI���룺 " << pProductGroup->ProductID << std::endl;
		std::cout << "���������룺 " << pProductGroup->ExchangeID << std::endl;
		std::cout << "��Ʒ����룺 " << pProductGroup->ProductGroupID << std::endl;		
	}
	else
		std::cerr << "���ش���--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// �����ѯ��Ʒ���ۻ���
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

		std::cout << "=====�����ѯ��Ʒ���ۻ�����Ӧ=====" << std::endl;
		std::cout << "��Ʒ���룺 " << pProductExchRate->ProductID << std::endl;
		std::cout << "���������룺 " << pProductExchRate->ExchangeID << std::endl;
		std::cout << "���ʣ� " << pProductExchRate->ExchangeRate << std::endl;
	}
	else
		std::cerr << "���ش���--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// �����ѯ����
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

		std::cout << "=====�����ѯ������Ӧ=====" << std::endl;
		std::cout << "���ù�˾���룺 " << pExchangeRate->BrokerID << std::endl;
		std::cout << "Դ���֣� " << pExchangeRate->FromCurrencyID << std::endl;
		std::cout << "Դ���������� " << pExchangeRate->FromCurrencyUnit << std::endl;
		std::cout << "Ŀ����֣� " << pExchangeRate->ToCurrencyID << std::endl;
		std::cout << "���ʣ� " << pExchangeRate->ExchangeRate << std::endl;
	}
	else
		std::cerr << "���ش���--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// �������������ı�֤����
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

		std::cout << "=====�������������ı�֤������Ӧ=====" << std::endl;
		std::cout << "���ù�˾���룺 " << pExchangeMarginRateAdjust->BrokerID << std::endl;
		std::cout << "��Լ���룺 " << pExchangeMarginRateAdjust->InstrumentID << std::endl;
		std::cout << "Ͷ���ױ���־�� " << pExchangeMarginRateAdjust->HedgeFlag << std::endl;
		std::cout << "���潻����Ͷ���߶�ͷ��֤���ʣ� " << pExchangeMarginRateAdjust->LongMarginRatioByMoney << std::endl;
		std::cout << "���潻����Ͷ���߶�ͷ��֤��ѣ� " << pExchangeMarginRateAdjust->LongMarginRatioByVolume << std::endl;
	}
	else
		std::cerr << "���ش���--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// �����ѯ������������Ӧ
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

		std::cout << "=====�����ѯ������������Ӧ=====" << std::endl;
		std::cout << "���ù�˾���룺 " << pExchangeMarginRate->BrokerID << std::endl;
		std::cout << "��Լ���룺 " << pExchangeMarginRate->InstrumentID << std::endl;
		std::cout << "Ͷ���ױ���־�� " << pExchangeMarginRate->HedgeFlag << std::endl;
		std::cout << "���潻����Ͷ���߶�ͷ��֤���ʣ� " << pExchangeMarginRate->LongMarginRatioByMoney << std::endl;
		std::cout << "���潻����Ͷ���߶�ͷ��֤��ѣ� " << pExchangeMarginRate->LongMarginRatioByVolume << std::endl;
	}
	else
		std::cerr << "���ش���--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// �����ѯͶ����Ʒ��/��Ʒ�ֱ�֤��
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

		std::cout << "=====�����ѯ������������Ӧ=====" << std::endl;
		std::cout << "Ʒ�ֿ�Ʒ�ֱ�־�� " << pInvestorProductGroupMargin->ProductGroupID << std::endl;
		std::cout << "���ù�˾���룺 " << pInvestorProductGroupMargin->BrokerID << std::endl;
		std::cout << "Ͷ���ߴ��룺 " << pInvestorProductGroupMargin->InvestorID << std::endl;
		std::cout << "�����գ� " << pInvestorProductGroupMargin->TradingDay << std::endl;
		std::cout << "�����ţ� " << pInvestorProductGroupMargin->SettlementID << std::endl;
		std::cout << "���ᱣ֤�� " << pInvestorProductGroupMargin->FrozenMargin << std::endl;
		std::cout << "��ͷ���ᱣ֤�� " << pInvestorProductGroupMargin->LongFrozenMargin << std::endl;
		std::cout << "��ͷ���ᱣ֤�� " << pInvestorProductGroupMargin->ShortFrozenMargin << std::endl;
		std::cout << "ռ�ñ�֤�� " << pInvestorProductGroupMargin->UseMargin << std::endl;
		std::cout << "��ͷ��֤�� " << pInvestorProductGroupMargin->LongUseMargin << std::endl;
		std::cout << "��ͷ��֤�� " << pInvestorProductGroupMargin->ShortUseMargin << std::endl;
		std::cout << "��������֤�� " << pInvestorProductGroupMargin->ExchMargin << std::endl;
		std::cout << "��������ͷ��֤�� " << pInvestorProductGroupMargin->LongExchMargin << std::endl;
		std::cout << "��������ͷ��֤�� " << pInvestorProductGroupMargin->ShortExchMargin << std::endl;
		std::cout << "ƽ��ӯ���� " << pInvestorProductGroupMargin->CloseProfit << std::endl;
		std::cout << "����������ѣ� " << pInvestorProductGroupMargin->FrozenCommission << std::endl;
		std::cout << "�����ѣ� " << pInvestorProductGroupMargin->Commission << std::endl;
		std::cout << "�����ʽ� " << pInvestorProductGroupMargin->FrozenCash << std::endl;
		std::cout << "�ʽ�� " << pInvestorProductGroupMargin->CashIn << std::endl;
		std::cout << "�ֲ�ӯ���� " << pInvestorProductGroupMargin->PositionProfit << std::endl;
		std::cout << "�ۿ��ܽ� " << pInvestorProductGroupMargin->OffsetAmount << std::endl;
		std::cout << "��ͷ�ۿ��ܽ� " << pInvestorProductGroupMargin->LongOffsetAmount << std::endl;
	}
	else
		std::cerr << "���ش���--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// ��ѯ�ֵ���Ϣ��Ӧ
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

		std::cout << "=====��ѯ�ֵ���Ϣ��Ӧ=====" << std::endl;
		std::cout << "�������ڣ� " << pEWarrantOffset->TradingDay << std::endl;
		std::cout << "���ù�˾���룺 " << pEWarrantOffset->BrokerID << std::endl;
		std::cout << "Ͷ���ߴ��룺 " << pEWarrantOffset->InvestorID << std::endl;
		std::cout << "���������룺 " << pEWarrantOffset->ExchangeID << std::endl;
		std::cout << "��Լ���룺 " << pEWarrantOffset->InstrumentID << std::endl;
		std::cout << "�������� " << pEWarrantOffset->Direction << std::endl;
		std::cout << "Ͷ���ױ���־�� " << pEWarrantOffset->HedgeFlag << std::endl;
		std::cout << "������ " << pEWarrantOffset->Volume << std::endl;				
	}
	else
		std::cerr << "���ش���--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// �����ѯ��֤����ϵͳ���͹�˾�ʽ��˻���Կ��Ӧ
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

		std::cout << "=====��ѯ�ֵ���Ϣ��Ӧ=====" << std::endl;		
		std::cout << "���ù�˾���룺 " << pCFMMCTradingAccountKey->BrokerID << std::endl;
		std::cout << "���ù�˾ͳһ���룺 " << pCFMMCTradingAccountKey->ParticipantID << std::endl;
		std::cout << "Ͷ�����˻��� " << pCFMMCTradingAccountKey->AccountID << std::endl;
		std::cout << "��Կ��ţ� " << pCFMMCTradingAccountKey->KeyID << std::endl;
		std::cout << "��̬��Կ�� " << pCFMMCTradingAccountKey->CurrentKey << std::endl;		
	}
	else
		std::cerr << "���ش���--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// ����Ͷ������ϳֲ���Ϣ��Ӧ
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

		std::cout << "=====����Ͷ������ϳֲ���Ϣ��Ӧ=====" << std::endl;
		std::cout << "�����գ� " << pInvestorPositionCombineDetail->TradingDay << std::endl;
		std::cout << "�������ڣ� " << pInvestorPositionCombineDetail->OpenDate << std::endl;
		std::cout << "���������룺 " << pInvestorPositionCombineDetail->ExchangeID << std::endl;
		std::cout << "�����ţ� " << pInvestorPositionCombineDetail->SettlementID << std::endl;
		std::cout << "���ù�˾���룺 " << pInvestorPositionCombineDetail->BrokerID << std::endl;
		std::cout << "Ͷ���ߴ��룺 " << pInvestorPositionCombineDetail->InvestorID << std::endl;
		std::cout << "��ϱ�ţ� " << pInvestorPositionCombineDetail->ComTradeID << std::endl;
		std::cout << "��ϱ�ţ� " << pInvestorPositionCombineDetail->TradeID << std::endl;
		std::cout << "��Լ���룺 " << pInvestorPositionCombineDetail->InstrumentID << std::endl;
		std::cout << "Ͷ���ױ���־�� " << pInvestorPositionCombineDetail->HedgeFlag << std::endl;
		std::cout << "�������� " << pInvestorPositionCombineDetail->Direction << std::endl;
		std::cout << "�ֲ����� " << pInvestorPositionCombineDetail->TotalAmt << std::endl;
		std::cout << "Ͷ���߱�֤�� " << pInvestorPositionCombineDetail->Margin << std::endl;
		std::cout << "��������֤�� " << pInvestorPositionCombineDetail->ExchMargin << std::endl;
		std::cout << "��֤���ʣ� " << pInvestorPositionCombineDetail->MarginRateByMoney << std::endl;
		std::cout << "��֤���ʣ����������� " << pInvestorPositionCombineDetail->MarginRateByVolume << std::endl;
		std::cout << "���ȱ�ţ� " << pInvestorPositionCombineDetail->LegID << std::endl;
		std::cout << "���Ⱥ�Լ������ " << pInvestorPositionCombineDetail->LegMultiple << std::endl;
	}
	else
		std::cerr << "���ش���--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// �����ѯͶ���ֲ߳���Ϣ��Ӧ
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

		std::cout << "=====�����ѯͶ���ֲ߳���Ϣ��Ӧ=====" << std::endl;
		std::cout << "�����գ� " << pInvestorPositionDetail->TradingDay << std::endl;
		std::cout << "�������ڣ� " << pInvestorPositionDetail->OpenDate << std::endl;
		std::cout << "���������룺 " << pInvestorPositionDetail->ExchangeID << std::endl;
		std::cout << "�����ţ� " << pInvestorPositionDetail->SettlementID << std::endl;
		std::cout << "���ù�˾���룺 " << pInvestorPositionDetail->BrokerID << std::endl;
		std::cout << "Ͷ���ߴ��룺 " << pInvestorPositionDetail->InvestorID << std::endl;		
		std::cout << "��ϱ�ţ� " << pInvestorPositionDetail->TradeID << std::endl;
		std::cout << "��Լ���룺 " << pInvestorPositionDetail->InstrumentID << std::endl;
		std::cout << "Ͷ���ױ���־�� " << pInvestorPositionDetail->HedgeFlag << std::endl;
		std::cout << "�������� " << pInvestorPositionDetail->Direction << std::endl;		
		std::cout << "Ͷ���߱�֤�� " << pInvestorPositionDetail->Margin << std::endl;
		std::cout << "��������֤�� " << pInvestorPositionDetail->ExchMargin << std::endl;
		std::cout << "��֤���ʣ� " << pInvestorPositionDetail->MarginRateByMoney << std::endl;
		std::cout << "��֤���ʣ����������� " << pInvestorPositionDetail->MarginRateByVolume << std::endl;		
	}
	else
		std::cerr << "���ش���--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// ��������ת�˼�¼��Ӧ
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

		std::cout << "=====�����ѯͶ���ֲ߳���Ϣ��Ӧ=====" << std::endl;
		std::cout << "���д��룺 " << pTransferBank->BankID << std::endl;
		std::cout << "���з����Ĵ��룺 " << pTransferBank->BankBrchID << std::endl;
		std::cout << "�������ƣ� " << pTransferBank->BankName << std::endl;
		std::cout << "�Ƿ��Ծ�� " << pTransferBank->IsActive << std::endl;
	}
	else 
		std::cerr << "���ش���--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// �����ѯͶ���߽�����Ϣ��Ӧ
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

		std::cout << "=====�����ѯͶ���߽�����Ϣ��Ӧ=====" << std::endl;
		std::cout << "�����գ� " << pSettlementInfo->TradingDay << std::endl;
		std::cout << "�����ţ� " << pSettlementInfo->SettlementID << std::endl;
		std::cout << "���ù�˾���룺 " << pSettlementInfo->BrokerID << std::endl;
		std::cout << "Ͷ���ߴ��룺 " << pSettlementInfo->InvestorID << std::endl;
		std::cout << "��ţ� " << pSettlementInfo->SequenceNo << std::endl;
		std::cout << "��Ϣ���ģ� " << pSettlementInfo->Content << std::endl;
		std::cout << "Ͷ�����˺ţ� " << pSettlementInfo->AccountID << std::endl;
	}
	else
		std::cerr << "���ش���--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// �����ѯ������Ӧ
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

		std::cout << "=====�����ѯ������Ӧ=====" << std::endl;
		std::cout << "�����գ� " << pDepthMarketData->TradingDay << std::endl;
		std::cout << "��Լ���룺 " << pDepthMarketData->InstrumentID << std::endl;
		std::cout << "���������룺 " << pDepthMarketData->ExchangeID << std::endl;
		std::cout << "��Լ�ڽ��������룺 " << pDepthMarketData->ExchangeInstID << std::endl;
		std::cout << "���¼ۣ� " << pDepthMarketData->LastPrice << std::endl;
		std::cout << "�ϴν���ۣ� " << pDepthMarketData->PreSettlementPrice << std::endl;
		std::cout << "�������̼ۣ� " << pDepthMarketData->PreClosePrice << std::endl;
		std::cout << "���ճֲ����� " << pDepthMarketData->PreOpenInterest << std::endl;
		std::cout << "���տ��̼ۣ� " << pDepthMarketData->OpenPrice << std::endl;
		std::cout << "��߼ۣ� " << pDepthMarketData->HighestPrice << std::endl;
		std::cout << "��ͼۣ� " << pDepthMarketData->LowestPrice << std::endl;
		std::cout << "������ " << pDepthMarketData->Volume << std::endl;
		std::cout << "�ɽ��� " << pDepthMarketData->Turnover << std::endl;
		std::cout << "�ֲ����� " << pDepthMarketData->OpenInterest << std::endl;
		std::cout << "�����̼ۣ� " << pDepthMarketData->ClosePrice << std::endl;
	}
	else
		std::cerr << "���ش���--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// �����ѯ��Լ
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

		std::cout << "=====�����ѯ��Լ��Ӧ=====" << std::endl;		
		std::cout << "��Լ���룺 " << pInstrument->InstrumentID << std::endl;
		std::cout << "���������룺 " << pInstrument->ExchangeID << std::endl;
		std::cout << "��Լ���ƣ� " << pInstrument->InstrumentName << std::endl;
		std::cout << "��Լ�ڽ��������룺 " << pInstrument->ExchangeInstID << std::endl;
		std::cout << "��Ʒ���룺 " << pInstrument->ProductID << std::endl;
		std::cout << "��Ʒ���ͣ� " << pInstrument->ProductClass << std::endl;
		std::cout << "������ݣ� " << pInstrument->DeliveryYear << std::endl;
		std::cout << "�����·ݣ� " << pInstrument->DeliveryMonth << std::endl;
		std::cout << "�м۵�����µ����� " << pInstrument->MaxMarketOrderVolume << std::endl;
		std::cout << "�м۵���С�µ����� " << pInstrument->MinMarketOrderVolume << std::endl;
		std::cout << "�޼۵�����µ����� " << pInstrument->MaxLimitOrderVolume << std::endl;
		std::cout << "�޼۵���С�µ����� " << pInstrument->MinLimitOrderVolume << std::endl;
		std::cout << "��Լ���������� " << pInstrument->VolumeMultiple << std::endl;
		std::cout << "��С�䶯��λ�� " << pInstrument->PriceTick << std::endl;
		std::cout << "�����գ� " << pInstrument->CreateDate << std::endl;
		std::cout << "�����գ� " << pInstrument->OpenDate << std::endl;
		std::cout << "�����գ� " << pInstrument->ExpireDate << std::endl;
		std::cout << "��ʼ�����գ� " << pInstrument->StartDelivDate << std::endl;
		std::cout << "���������գ� " << pInstrument->EndDelivDate << std::endl;
		std::cout << "��Լ��������״̬�� " << pInstrument->InstLifePhase << std::endl;
		std::cout << "��ǰ�Ƿ��ף� " << pInstrument->IsTrading << std::endl;
		std::cout << "�ֲ����ͣ� " << pInstrument->PositionType << std::endl;
		std::cout << "�ֲ��������ͣ� " << pInstrument->PositionDateType << std::endl;
		std::cout << "��ͷ��֤���ʣ� " << pInstrument->LongMarginRatio << std::endl;
		std::cout << "��ͷ��֤���ʣ� " << pInstrument->ShortMarginRatio << std::endl;
		std::cout << "�Ƿ�ʹ�ô�֤���㷨�� " << pInstrument->MaxMarginSideAlgorithm << std::endl;
	}
	else
		std::cerr << "���ش���--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// �����ѯ��������Ӧ
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

		std::cout << "=====�����ѯ��������Ϣ��Ӧ=====" << std::endl;
		std::cout << "��������ţ� " << pExchange->ExchangeID<< std::endl;
		std::cout << "���������ƣ� " << pExchange->ExchangeName << std::endl;
		std::cout << "���������ԣ� " << pExchange->ExchangeProperty << std::endl;		
	}
	else
		std::cerr << "���ش���--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// �����ѯ��Լ������
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

		std::cout << "=====�����ѯ��Լ��������Ϣ��Ӧ=====" << std::endl;
		std::cout << "��Լ���룺 " << pInstrumentCommissionRate->InstrumentID << std::endl;
		std::cout << "Ͷ���߷�Χ�� " << pInstrumentCommissionRate->InvestorRange << std::endl;
		std::cout << "���ù�˾���룺 " << pInstrumentCommissionRate->BrokerID << std::endl;
		std::cout << "Ͷ���ߴ��룺 " << pInstrumentCommissionRate->InvestorID << std::endl;
		std::cout << "�����������ʣ� " << pInstrumentCommissionRate->OpenRatioByMoney << std::endl;
		std::cout << "���������ѣ� " << pInstrumentCommissionRate->OpenRatioByVolume << std::endl;
		std::cout << "ƽ���������ʣ� " << pInstrumentCommissionRate->CloseRatioByMoney << std::endl;
		std::cout << "ƽ�������ѣ� " << pInstrumentCommissionRate->CloseRatioByVolume << std::endl;
		std::cout << "ƽ���������ʣ� " << pInstrumentCommissionRate->CloseTodayRatioByMoney << std::endl;
		std::cout << "ƽ�������ѣ� " << pInstrumentCommissionRate->CloseTodayRatioByVolume << std::endl;
		std::cout << "���������룺 " << pInstrumentCommissionRate->ExchangeID << std::endl;
		std::cout << "ҵ�����ͣ� " << pInstrumentCommissionRate->BizType << std::endl;
	}
	else
		std::cerr << "���ش���--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// �����ѯ��Լ��֤����
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

		std::cout << "=====�����ѯ��Լ��������Ϣ��Ӧ=====" << std::endl;
		std::cout << "��Լ���룺 " << pInstrumentMarginRate->InstrumentID << std::endl;
		std::cout << "Ͷ���߷�Χ�� " << pInstrumentMarginRate->InvestorRange << std::endl;
		std::cout << "���ù�˾���룺 " << pInstrumentMarginRate->BrokerID << std::endl;
		std::cout << "Ͷ���ߴ��룺 " << pInstrumentMarginRate->InvestorID << std::endl;
		std::cout << "Ͷ���ױ���־�� " << pInstrumentMarginRate->HedgeFlag << std::endl;
		std::cout << "��ͷ��֤���ʣ� " << pInstrumentMarginRate->LongMarginRatioByMoney << std::endl;
		std::cout << "��ͷ��֤��ѣ� " << pInstrumentMarginRate->LongMarginRatioByVolume << std::endl;
		std::cout << "��ͷ��֤���ʣ� " << pInstrumentMarginRate->ShortMarginRatioByMoney << std::endl;
		std::cout << "��ͷ��֤�� " << pInstrumentMarginRate->ShortMarginRatioByVolume << std::endl;
		std::cout << "�Ƿ���Խ�������ȡ�� " << pInstrumentMarginRate->IsRelative << std::endl;
		std::cout << "���������룺 " << pInstrumentMarginRate->ExchangeID << std::endl;
		std::cout << "Ͷ�ʵ�Ԫ���룺 " << pInstrumentMarginRate->InvestUnitID << std::endl;
	}
	else
		std::cerr << "���ش���--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// �����ѯ�����߱��
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

		std::cout << "=====�����ѯ�����߱����Ϣ��Ӧ=====" << std::endl;
		std::cout << "Ͷ���߱�ţ� " << pTradingCode->InvestorID << std::endl;
		std::cout << "���ù�˾���룺 " << pTradingCode->BrokerID << std::endl;
		std::cout << "���������룺 " << pTradingCode->ExchangeID << std::endl;
		std::cout << "�ͻ��˴��룺 " << pTradingCode->ClientID << std::endl;
		std::cout << "�Ƿ񼤻 " << pTradingCode->IsActive << std::endl;
		std::cout << "���ױ������ͣ� " << pTradingCode->ClientIDType << std::endl;
		std::cout << "Ӫҵ����ţ� " << pTradingCode->BranchID << std::endl;
		std::cout << "ҵ�����ͣ� " << pTradingCode->BizType << std::endl;
	}
	else
		std::cerr << "���ش���--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// �����ѯͶ������Ӧ
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

		std::cout << "=====�����ѯͶ������Ӧ=====" << std::endl;
		std::cout << "Ͷ���߱�ţ� " << pInvestor->InvestorID << std::endl;
		std::cout << "���ù�˾���룺 " << pInvestor->BrokerID << std::endl;
		std::cout << "Ͷ���߷�����룺 " << pInvestor->InvestorGroupID << std::endl;
		std::cout << "Ͷ�������ƣ� " << pInvestor->InvestorName << std::endl;
		std::cout << "֤�����ͣ� " << pInvestor->IdentifiedCardType << std::endl;
		std::cout << "֤�����룺 " << pInvestor->IdentifiedCardNo << std::endl;
		std::cout << "�Ƿ񼤻 " << pInvestor->IsActive << std::endl;
		std::cout << "��ϵ�绰�� " << pInvestor->Telephone << std::endl;
	}
	else
		std::cerr << "���ش���--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// ��ѯ�ʽ��˻���Ӧ
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

		std::cout << "=====��ѯ�ʽ��˻���Ӧ=====" << std::endl;		
		std::cout << "���ù�˾���룺 " << pTradingAccount->BrokerID << std::endl;
		std::cout << "Ͷ�����˻��� " << pTradingAccount->AccountID << std::endl;
		std::cout << "�ϴ���Ѻ�� " << pTradingAccount->PreMortgage << std::endl;
		std::cout << "�ϴ����ö�ȣ� " << pTradingAccount->PreCredit << std::endl;
		std::cout << "�ϴδ���ȣ� " << pTradingAccount->PreDeposit << std::endl;
		std::cout << "�ϴν��㱣֤�� " << pTradingAccount->PreBalance << std::endl;
		std::cout << "�ϴ�ռ�õı�֤�� " << pTradingAccount->PreMargin << std::endl;
		std::cout << "��Ϣ������ " << pTradingAccount->InterestBase << std::endl;
		std::cout << "��Ϣ���룺 " << pTradingAccount->Interest << std::endl;
		std::cout << "���� " << pTradingAccount->Deposit << std::endl;
		std::cout << "����� " << pTradingAccount->Withdraw << std::endl;
		std::cout << "���ᱣ֤�� " << pTradingAccount->FrozenMargin << std::endl;
		std::cout << "�����ʽ� " << pTradingAccount->FrozenCash << std::endl;
		std::cout << "����������ѣ� " << pTradingAccount->FrozenCommission << std::endl;
		std::cout << "��ǰ�ı�֤�� " << pTradingAccount->CurrMargin << std::endl;
	}
	else
		std::cerr << "���ش���--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;

}

// �����ѯͶ���ֲ߳�
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

		std::cout << "=====�����ѯͶ���ֲ߳���Ӧ=====" << std::endl;
		std::cout << "��Լ���룺 " << pInvestorPosition->InstrumentID << std::endl;
		std::cout << "���ù�˾���룺 " << pInvestorPosition->BrokerID << std::endl;
		std::cout << "Ͷ���ߴ��룺 " << pInvestorPosition->InvestorID << std::endl;
		std::cout << "�ֲֶ�շ��� " << pInvestorPosition->PosiDirection << std::endl;
		std::cout << "Ͷ���ױ���־�� " << pInvestorPosition->HedgeFlag << std::endl;
		std::cout << "�ֲ����ڣ� " << pInvestorPosition->PositionDate << std::endl;
		std::cout << "���ճֲ֣� " << pInvestorPosition->YdPosition << std::endl;
		std::cout << "���ճֲ֣� " << pInvestorPosition->Position << std::endl;
		std::cout << "��ͷ���᣺ " << pInvestorPosition->LongFrozen << std::endl;
		
	}
	else
		std::cerr << "���ش���--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// �����ѯ������Ӧ
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

		std::cout << "=====�����ѯ������Ӧ=====" << std::endl;
		std::cout << "���ù�˾���룺 " << pTrade->BrokerID << std::endl;
		std::cout << "Ͷ���ߴ��룺 " << pTrade->InvestorID << std::endl;
		std::cout << "��Լ���룺 " << pTrade->InstrumentID << std::endl;
		std::cout << "�������� �� " << pTrade->OrderRef << std::endl;
		std::cout << "�û����룺 " << pTrade->UserID << std::endl;
		std::cout << "���������룺 " << pTrade->ExchangeID << std::endl;
		std::cout << "�ɽ���ţ� " << pTrade->TradeID << std::endl;
		std::cout << "�������� " << pTrade->Direction << std::endl;
		std::cout << "������ţ� " << pTrade->OrderSysID << std::endl;
		std::cout << "��Ա���룺 " << pTrade->ParticipantID << std::endl;
		std::cout << "�ͻ����룺 " << pTrade->ClientID << std::endl;
		std::cout << "���׽�ɫ�� " << pTrade->TradingRole << std::endl;
	}
	else
		std::cerr << "���ش���--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// ����֪ͨ
void WINAPI OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (bResult)
		std::cerr << "���ش���--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

#pragma endregion 

void Init() 
{
	cout << "���ӽ��׷�����..." << endl;
	g_pTdApi = CreateFtdcTraderApi();   // ��������ʵ��
	g_pTdSpi = CreateTraderSpi();
	g_pTdApi->RegisterSpi(g_pTdSpi);

	g_pTdApi->SubscribePrivateTopic(THOST_TERT_RESUME);		// ����˽����
	g_pTdApi->SubscribePublicTopic(THOST_TERT_RESUME);		// ���Ĺ�����

	g_pTdApi->RegisterFront(gTradeFrontAddr);				// ��������ǰ�õ�ַ

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

// ����
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

// Ԥ��
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

// Ԥ�񳷵�
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

// Ԥ�񵥳���
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

// ��������
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

// �����ѯ����
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

// ��ѯ��󱨵���
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

// Ͷ���߽�����ȷ��
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

// ѯ�� ��OnRtnForQuoteRsp���ýӿ���ʱ�����ã�
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

// ��ѯ����
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

// ������ϲ�ѯ
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

// ��ѯ��Ϻ�Լ��ȫϵ������ʱ����ص���
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

// �����ѯת����ˮ
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

// ��ѯ����ǩԼ��ϵ
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

// ��Լ����״̬֪ͨ
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

// ����֪ͨ ���ᱨ����ṹδȷ�ϴ���
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

// ��ѯǩԼ������Ӧ
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

// ��ѯԤ����Ӧ
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

// �����ѯԤ�񵥳�����Ӧ
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

// ��ѯ����֪ͨ
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

// ��ѯ���ù�˾���ײ���
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

// ��ѯ���ù�˾�Ľ����㷨
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

// �ڻ������ѯ�������ʽ��˻������ڣ������ʧ�ܣ�
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

 // �����ѯ��������û����� (�ý���ϯλδ���ӵ�������)
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

 // �ڻ����������ʽ�ת�ڻ����ʽ��˻������ڣ�
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

 // �ڻ������ڻ��ʽ�ת���У��ʽ��˻������ڣ�
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

 // �����ѯͶ�ʵ�Ԫ��һֱû�лص���
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

 // �����ѯ������������Ϣ
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

 // �����ѯ�����������ʽ���֤ģʽ
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

 // �����ѯ�ʽ��˻�
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

 // �����ѯ����������
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

 // �����ѯ�����̺�Լ��������
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

 // �����ѯ��Ʒ��
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

 // �����ѯ��Ʒ���ۻ���
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

 // �����ѯ����
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

 // �����ѯ�����������ı�֤����
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
 
 // �����ѯ��������֤����
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

 // �����ѯͶ����Ʒ��/��Ʒ�ֱ�֤��
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
 
 // �����ѯ�ֵ���Ϣ
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
 
 // �����ѯ��֤����ϵͳ���͹�˾�ʽ��˻���Կ
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

 // �����ѯͶ������Ϻ�Լ�ֲ���ϸ
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
 
 // �����ѯͶ���ֲ߳���ϸ
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
 
 // �����ѯת������
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

 // �����ѯͶ���߽�����Ϣ
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

 // �����ѯ����
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

 // �����ѯ��Լ
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
 
 // �����ѯ������
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

 // �����ѯ��Լ��������
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

 // �����ѯ��Լ�ı�֤����
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

 // �����ѯ���ױ���
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

 // �����ѯͶ����
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

 // �����ѯ�ʽ��˻�
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

 // �����ѯͶ���ֲ߳�
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
 
 // �����ѯ����
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

 // ����˽����
 // SubscribePrivateTopic

 // ���Ĺ�����
 // SubscribePublicTopic

