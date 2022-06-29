#include "pch.h"
#include <ostream>
#include <fstream>
#include <mutex>
#include <string>
#include "MdSpi.h"
#include "MdApi.h"
#include "SubMarketData.h"
using namespace std;

// ��������
TThostFtdcBrokerIDType gBrokerID = "9999";                         // ģ�⾭���̴���
TThostFtdcInvestorIDType gInvesterID = "097266";                         // Ͷ�����˻���
TThostFtdcPasswordType gInvesterPassword = "hello@123";                     // Ͷ��������

// �������
CThostFtdcMdApi *g_pMdUserApi = nullptr;                           // ����ָ��
MdSpi *g_pMdSpi = nullptr;                           // spi
char gMdFrontAddr[] = "tcp://180.168.146.187:10211";               // ģ������ǰ�õ�ַ ��һ��
//char gMdFrontAddr[] = "tcp://180.168.146.187:10131";               // ģ������ǰ�õ�ַ 24h
char *g_pInstrumentID[] = {"cu2203,C73000"};								// �����Լ�����б��С��ϡ���֣��������ѡһ��
int instrumentNum = 1;                                             // �����Լ��������
string instrumentPath = "instrument.txt";


struct CtpMdApiTestParam
{
	// ��¼
	bool isLogin;
	bool isLogout;

	// ����
	bool isSubMarketData;
	bool isUnSubMarketData;
	bool isMarketDataNotice;

	// ѯ��
	bool isSubQuoteData;
	bool isUnSubQuoteData;
	bool isQuoteDataNotice;

	// ��ѯ�鲥
	bool isLookMulticast;
};

CtpMdApiTestParam g_ctpMdApiTestParam = { "\0" };

// ��¼
bool g_loginOK = false;
bool g_logoutOK = false;

// �г�����
bool g_subMarketDataOK = false;
bool g_unSubMarketDataOK = false;
bool g_marketDataNoticeOK = false;

// ѯ��
bool g_subQuoteDataOK = false;
bool g_unSubQuoteDataOK = false;
bool g_quoteDataNoticeOK = false;

// ��ѯ�鲥
bool g_lookMulticastOK = false;

// �߳�ͬ������
mutex mut;
condition_variable cond_va;

std::ofstream outLogFile;

enum LogLevel
{
	Debug = 0,
	Warn,
	Error,
};

char* logLevelName[] = { "Debug","Warn","Error" };

void InitLog() 
{
	//std::remove("log.txt");
	outLogFile.open("log.txt", std::ios::out);
}

void LogInfo(char* log, LogLevel level = LogLevel::Debug, bool show = true)
{
	char timeBuf[100] = { '\0' };
	time_t t = time(NULL);
	tm local = { '\0' };
	localtime_s(&local, &t);
	strftime(timeBuf, sizeof(timeBuf), "%Y/%m/%d %H:%M:%S", &local);

	// log ������ 2048 ����������
	char logBuf[2048] = { '\0' };	
	sprintf(logBuf, "%s [%s]: %s", timeBuf, logLevelName[level], log);
	outLogFile << logBuf << std::endl;

	if (show)
		if (level != LogLevel::Error)
			std::cout << logBuf << std::endl;
		else
			std::cerr << logBuf << std::endl;
}

#pragma region callbacks
void WINAPI  OnFrontConnected()
{
	if (g_ctpMdApiTestParam.isLogin) {
		LogInfo("=====�����������ӳɹ�=====");
		// ��ʼ��¼
		CThostFtdcReqUserLoginField loginReq;
		memset(&loginReq, 0, sizeof(loginReq));
		strcpy(loginReq.BrokerID, gBrokerID);
		strcpy(loginReq.UserID, gInvesterID);
		strcpy(loginReq.Password, gInvesterPassword);
		static int requestID = 0; // ������
		int rt = g_pMdUserApi->ReqUserLogin(&loginReq, requestID);

		if (!rt)
			LogInfo(">>>>>>���͵�¼����ɹ�");
		else
			LogInfo("--->>>���͵�¼����ʧ��", LogLevel::Error);
	}	

	char logBuf[128] = { '\0' };
	sprintf(logBuf, "API Version: %s", g_pMdUserApi->GetApiVersion());
	LogInfo(logBuf);
}


// �Ͽ�����֪ͨ
void WINAPI OnFrontDisconnected(int nReason)
{
	char errorLog[128] = { '\0' };
	sprintf(errorLog, "=====�������ӶϿ�===== \n �����룺%d", nReason);
	LogInfo(errorLog, LogLevel::Error);
}

// ������ʱ����
void WINAPI OnHeartBeatWarning(int nTimeLapse)
{
	char errorLog[128] = { '\0' };
	sprintf(errorLog, "=====����������ʱ=====\n ���ϴ�����ʱ�䣺%d", nTimeLapse);
	LogInfo(errorLog, LogLevel::Error);
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
		cond_va.notify_one();

		char buf[1024] = { '\0' };
		sprintf(buf, "=====�˻���¼�ɹ�===== \n �����գ� %s \n ��¼ʱ�䣺 %s \n �����̣� %s \n �ʻ����� %s", 
				pRspUserLogin->TradingDay, pRspUserLogin->LoginTime, pRspUserLogin->BrokerID,pRspUserLogin->UserID);

		LogInfo(buf);
		
		// ������������
		if (g_ctpMdApiTestParam.isSubMarketData) {
			int rt = g_pMdUserApi->SubscribeMarketData(g_pInstrumentID, instrumentNum);
			if (!rt)
				LogInfo(">>>>>>���Ͷ�����������ɹ�");
			else
				LogInfo("--->>>���Ͷ�����������ʧ��", LogLevel::Error);
		}

		// ����ѯ��
		if (g_ctpMdApiTestParam.isSubQuoteData) {
			int rt = g_pMdUserApi->SubscribeForQuoteRsp(g_pInstrumentID, instrumentNum);

			if (!rt)
				LogInfo(">>>>>>���Ͷ���ѯ������ɹ�");
			else
				LogInfo("--->>>���Ͷ���ѯ������ʧ��", LogLevel::Error);
		}

		// �ǳ�����
		if (g_ctpMdApiTestParam.isLogout) {
			CThostFtdcUserLogoutField logout = { "\0" };
			std::strcpy(logout.BrokerID, gBrokerID);
			std::strcpy(logout.UserID, gInvesterID);
			static int requestID = 0; // ������
			int rt = g_pMdUserApi->ReqUserLogout(&logout, requestID);

			if (!rt)
				LogInfo(">>>>>>���͵ǳ�����ɹ�");
			else
				LogInfo("--->>>���͵ǳ�����ʧ��", LogLevel::Error);
		}

		if (g_ctpMdApiTestParam.isLookMulticast) {
			CThostFtdcQryMulticastInstrumentField multicastInstrumentField = { '\0'};
			multicastInstrumentField.TopicID = 1001;		//��Ӧ���������鲥����topic			
			strcpy(multicastInstrumentField.InstrumentID, g_pInstrumentID[0]);
			int rt = g_pMdUserApi->ReqQryMulticastInstrument(&multicastInstrumentField, 1);

			if (!rt)
				LogInfo(">>>>>>���Ͳ�ѯ�鲥����ɹ�");
			else
				LogInfo("--->>>���Ͳ�ѯ�鲥����ʧ��", LogLevel::Error);
		}
	}
	else {
		char buf[1024] = { '\0' };
		sprintf(buf, "��¼ʧ�ܡ����ش���--->>> ErrorID=%d, ErrorMsg=%s", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
		LogInfo(buf, LogLevel::Error);
	}
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
		char buf[512] = { '\0' };
		sprintf(buf, "=====�˻��ǳ��ɹ�=====\n �����̣� %s \n �ʻ����� %s", pUserLogout->BrokerID, pUserLogout->UserID);
		LogInfo(buf);

		g_logoutOK = true;		
		cond_va.notify_one();
	}
	else {
		char buf[1024] = { '\0' };
		sprintf(buf, "�ǳ�ʧ�ܡ����ش���--->>> ErrorID=%d, ErrorMsg=%s", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
		LogInfo(buf, LogLevel::Error);
	}
}

// ����֪ͨ
void WINAPI  OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (bResult) {
		char buf[512] = { '\0' };
		sprintf(buf, "���ش���--->>> ErrorID=%d, ErrorMsg=%s", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
		LogInfo(buf, LogLevel::Error);
	}
}

// ��������Ӧ��
void WINAPI OnRspSubMarketData(
	CThostFtdcSpecificInstrumentField *pSpecificInstrument, 
	CThostFtdcRspInfoField *pRspInfo, 
	int nRequestID, 
	bool bIsLast)
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult)
	{
		g_subMarketDataOK = true;		
		cond_va.notify_one();

		char logBuf[128] = { '\0' };
		sprintf(logBuf, "=====��������ɹ�===== \n ��Լ���룺 %s", pSpecificInstrument->InstrumentID);
		LogInfo(logBuf);
		// �����Ҫ�����ļ��������ݿ⣬�����ﴴ����ͷ,��ͬ�ĺ�Լ�����洢
		char filePath[100] = {'\0'};
		sprintf(filePath, "%s_market_data.csv", pSpecificInstrument->InstrumentID);
		std::ofstream outFile;
		outFile.open(filePath, std::ios::out); // �¿��ļ�
		outFile << "��Լ����" << ","
			<< "����ʱ��" << ","
			<< "���¼�" << ","
			<< "�ɽ���" << ","
			<< "���һ" << ","
			<< "����һ" << ","
			<< "����һ" << ","
			<< "����һ" << ","
			<< "�ֲ���" << ","
			<< "������"
			<< std::endl;
		outFile.close();
	}
	else {
		char buf[1024] = { '\0' };
		sprintf(buf, "===��������ʧ��===\n���ش���--->>> ErrorID=%d, ErrorMsg=%s", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
		LogInfo(buf, LogLevel::Error);
	}
}

// ȡ����������Ӧ��
void WINAPI OnRspUnSubMarketData(
	CThostFtdcSpecificInstrumentField *pSpecificInstrument, 
	CThostFtdcRspInfoField *pRspInfo,
	int nRequestID, 
	bool bIsLast)
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult)
	{
		g_unSubMarketDataOK = true;		
		cond_va.notify_one();

		char logBuf[128] = { '\0' };
		sprintf(logBuf, "=====ȡ����������ɹ�===== \n ��Լ���룺 %s", pSpecificInstrument->InstrumentID);
		LogInfo(logBuf);
	}
	else {
		char buf[1024] = { '\0' };
		sprintf(buf, "===ȡ����������ʧ��===\n���ش���--->>> ErrorID=%d, ErrorMsg=%s", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
		LogInfo(buf, LogLevel::Error);
	}
}

// ����ѯ��Ӧ��
void WINAPI OnRspSubForQuoteRsp(
	CThostFtdcSpecificInstrumentField *pSpecificInstrument,
	CThostFtdcRspInfoField *pRspInfo,
	int nRequestID,
	bool bIsLast)
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult)
	{
		g_subQuoteDataOK = true;		
		cond_va.notify_one();

		char logBuf[128] = { '\0' };
		sprintf(logBuf, "=====����ѯ�۳ɹ�===== \n ��Լ���룺 %s", pSpecificInstrument->InstrumentID);
		LogInfo(logBuf);

		// ȡ������ѯ��
		if (g_ctpMdApiTestParam.isUnSubQuoteData) {
			char* pInstrumentID[1] = { pSpecificInstrument->InstrumentID };
			int rt = g_pMdUserApi->UnSubscribeForQuoteRsp(pInstrumentID, 1);
			if (!rt)
				LogInfo(">>>>>>����ȡ������ѯ������ɹ�");
			else
				LogInfo("--->>>����ȡ������ѯ������ʧ��", LogLevel::Error);
		}
	}
	else {
		char buf[1024] = { '\0' };
		sprintf(buf, "===����ѯ��ʧ��===\n���ش���--->>> ErrorID=%d, ErrorMsg=%s", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
		LogInfo(buf, LogLevel::Error);
	}
}

// ȡ������ѯ��Ӧ��
void WINAPI OnRspUnSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult)
	{
		g_unSubQuoteDataOK = true;		
		cond_va.notify_one();

		char logBuf[128] = { '\0' };
		sprintf(logBuf, "=====ȡ������ѯ�۳ɹ�===== \n ��Լ���룺 %s", pSpecificInstrument->InstrumentID);
		LogInfo(logBuf);
	}
	else {
		char buf[1024] = { '\0' };
		sprintf(buf, "===ȡ������ѯ��ʧ��===\n���ش���--->>> ErrorID=%d, ErrorMsg=%s", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
		LogInfo(buf, LogLevel::Error);
	}
}

// ��������֪ͨ
void WINAPI OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData)
{
	g_marketDataNoticeOK = true;	
	cond_va.notify_one();	

	// ��ӡ���飬�ֶν϶࣬��ȡ����
	char logBuf[1024] = { '\0' };
	sprintf(logBuf, "=====����������===== \n �����գ� %s\n ���������룺 %s\n ��Լ���룺 %s\n ��Լ�ڽ������Ĵ��룺 %s\n ���¼ۣ� %f\n ������ %d",
		pDepthMarketData->TradingDay, pDepthMarketData->ExchangeID,pDepthMarketData->InstrumentID, pDepthMarketData->ExchangeInstID , (float)pDepthMarketData->LastPrice, pDepthMarketData->Volume);
	LogInfo(logBuf);	
	// ���ֻ��ȡĳһ����Լ���飬������tick�ش����ļ������ݿ�
	char filePath[100] = {'\0'};
	sprintf(filePath, "%s_market_data.csv", pDepthMarketData->InstrumentID);
	std::ofstream outFile;
	outFile.open(filePath, std::ios::app); // �ļ�׷��д�� 
	outFile << pDepthMarketData->InstrumentID << "," 
		<< pDepthMarketData->UpdateTime << "." << pDepthMarketData->UpdateMillisec << "," 
		<< pDepthMarketData->LastPrice << "," 
		<< pDepthMarketData->Volume << "," 
		<< pDepthMarketData->BidPrice1 << "," 
		<< pDepthMarketData->BidVolume1 << "," 
		<< pDepthMarketData->AskPrice1 << "," 
		<< pDepthMarketData->AskVolume1 << "," 
		<< pDepthMarketData->OpenInterest << "," 
		<< pDepthMarketData->Turnover << std::endl;
	outFile.close();

	// ��ֹ������,ǿ��ȡ������
	if (g_ctpMdApiTestParam.isUnSubMarketData) {
		// ȡ����������
		char* pInstrumentID[1] = { pDepthMarketData->InstrumentID };
		int rt = g_pMdUserApi->UnSubscribeMarketData(pInstrumentID, 1);
		if (!rt)
			LogInfo(">>>>>>����ȡ��������������ɹ�");
		else
			LogInfo("--->>>����ȡ��������������ʧ��", LogLevel::Error);
	}
}

//  
void WINAPI OnRtnForQuoteRsp(CThostFtdcForQuoteRspField* pForQuoteRsp)
{
	// ����ѯ�۽��
	char logBuf[1024] = { '\0' };
	sprintf(logBuf, "=====���ѯ�۽��=====\n �����գ� %s\n ���������룺 %s\n ��Լ���룺 %s\n ѯ�۱�ţ� %s",
		pForQuoteRsp->TradingDay, pForQuoteRsp->ExchangeID, pForQuoteRsp->InstrumentID, pForQuoteRsp->ForQuoteSysID);
	
	LogInfo(logBuf);

	g_quoteDataNoticeOK = true;		
	cond_va.notify_one();
}

void WINAPI OnRspQryMulticastInstrument(CThostFtdcMulticastInstrumentField* pMulticastInstrument, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) {
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);

	if (!bResult) {
		char logBuf[1024] = { '\0' };		
		sprintf(logBuf, "����ţ� %d\n ��Լ���룺%s\n ��Լ��ţ�%d\n ��׼�ۣ�%f\n ��Լ����������%d\n ��С�䶯��λ: %f",
			pMulticastInstrument->TopicID, pMulticastInstrument->InstrumentID, pMulticastInstrument->InstrumentNo, pMulticastInstrument->CodePrice, pMulticastInstrument->VolumeMultiple, pMulticastInstrument->PriceTick);

		LogInfo(logBuf);

		g_lookMulticastOK = true;		
		cond_va.notify_one();
	}
	else {
		char buf[1024] = { '\0' };
		sprintf(buf, "===�鿴��Լ�鲥ʧ��===\n���ش���--->>> ErrorID=%d, ErrorMsg=%s", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
		LogInfo(buf, LogLevel::Error);
	}
}

void Init() {
	InitLog();

	/*mut = mutex();
	cond_va = condition_variable();*/

	// ��ʼ�������߳�
	cout << "��ʼ������..." << endl;
	g_pMdUserApi = CreateFtdcMdApi();			// ��������ʵ��
	g_pMdSpi = CreateMdSpi();					// ��������ص�	

	g_pMdUserApi->RegisterSpi(g_pMdSpi);		// ע��ص�
	g_pMdUserApi->RegisterFront(gMdFrontAddr);  // ��������ǰ�õ�ַ

	/// callbacks
	RegOnFrontConnected(g_pMdSpi, OnFrontConnected);
	RegOnFrontDisconnected(g_pMdSpi, OnFrontDisconnected);

	RegOnRspError(g_pMdSpi, OnRspError);
	RegOnHeartBeatWarning(g_pMdSpi, OnHeartBeatWarning);


	RegOnRspUserLogin(g_pMdSpi, OnRspUserLogin);
	RegOnRspUserLogout(g_pMdSpi, OnRspUserLogout);

	RegOnRspSubMarketData(g_pMdSpi, OnRspSubMarketData);
	RegOnRspUnSubMarketData(g_pMdSpi, OnRspUnSubMarketData);

	RegOnRspSubForQuoteRsp(g_pMdSpi, OnRspSubForQuoteRsp);
	RegOnRspUnSubForQuoteRsp(g_pMdSpi, OnRspUnSubForQuoteRsp);

	RegOnRspQryMulticastInstrument(g_pMdSpi, OnRspQryMulticastInstrument);

	RegOnRtnDepthMarketData(g_pMdSpi, OnRtnDepthMarketData);

	RegOnRtnForQuoteRsp(g_pMdSpi, OnRtnForQuoteRsp);
	
	g_pMdUserApi->Init();                                // ��������
}

void Release() 
{
	/*g_pMdUserApi->Release();
	g_pMdUserApi = NULL;*/
}

#pragma endregion

// ��ʼ��
//TEST(CtpMdApiWrapperTest, 01Init) {
//
//	g_ctpMdApiTestParam = { '\0' };	
//	Init();
//
//	EXPECT_TRUE(g_pMdUserApi != NULL);
//	EXPECT_TRUE(g_pMdSpi != NULL);
//
//	Sleep(1000);
//	Release();
//}
//
//// ��¼
//TEST(CtpMdApiWrapperTest, 02Login) {
//	g_ctpMdApiTestParam = { '\0' };
//	g_ctpMdApiTestParam.isLogin = true;
//	Init();		
//	
//	std::unique_lock<mutex> lck(mut);
//	cond_va.wait_for(lck, std::chrono::seconds(5), []()-> bool { return g_loginOK; });
//
//	EXPECT_TRUE(g_pMdUserApi != NULL);
//	EXPECT_TRUE(g_pMdSpi != NULL);
//	EXPECT_TRUE(g_loginOK);
//
//	Release();
//}
//
//// �ǳ�
//TEST(CtpMdApiWrapperTest, 03Logout) {
//	g_ctpMdApiTestParam = { '\0' };
//	g_ctpMdApiTestParam.isLogin = true;
//	g_ctpMdApiTestParam.isLogout = true;
//	Init();
//	
//	std::unique_lock<mutex> lck(mut);
//	cond_va.wait_for(lck, std::chrono::seconds(5), []()-> bool { return g_logoutOK; });
//
//	EXPECT_TRUE(g_pMdUserApi != NULL);
//	EXPECT_TRUE(g_pMdSpi != NULL);
//	EXPECT_TRUE(g_loginOK);
//	EXPECT_TRUE(g_logoutOK);
//
//	Release();
//}
//
//// ��������
//TEST(CtpMdApiWrapperTest, 04SubMarketData) {
//	g_ctpMdApiTestParam = { '\0' };
//	g_ctpMdApiTestParam.isLogin = true;
//	g_ctpMdApiTestParam.isSubMarketData = true;
//	g_ctpMdApiTestParam.isUnSubMarketData = true;
//	Init();
//	
//	std::unique_lock<mutex> lck(mut);
//	cond_va.wait_for(lck, std::chrono::seconds(5), []()-> bool { return g_subMarketDataOK && g_marketDataNoticeOK && g_unSubMarketDataOK; });
//
//
//	EXPECT_TRUE(g_pMdUserApi != NULL);
//	EXPECT_TRUE(g_pMdSpi != NULL);
//	EXPECT_TRUE(g_loginOK);
//	EXPECT_TRUE(g_subMarketDataOK);
//	EXPECT_TRUE(g_unSubMarketDataOK);
//
//	Release();
//}
//
//// ȡ����������
//TEST(CtpMdApiWrapperTest, 05UnSubMarketData) {
//	g_ctpMdApiTestParam = { '\0' };
//	g_ctpMdApiTestParam.isLogin = true;
//	g_ctpMdApiTestParam.isSubMarketData = true;
//	g_ctpMdApiTestParam.isUnSubMarketData = true;
//	Init();
//	
//	std::unique_lock<mutex> lck(mut);
//	cond_va.wait_for(lck, std::chrono::seconds(5), []()-> bool { return g_subMarketDataOK && g_marketDataNoticeOK && g_unSubMarketDataOK; });
//
//	EXPECT_TRUE(g_pMdUserApi != NULL);
//	EXPECT_TRUE(g_pMdSpi != NULL);
//	EXPECT_TRUE(g_loginOK);
//	EXPECT_TRUE(g_subMarketDataOK);
//	EXPECT_TRUE(g_unSubMarketDataOK);
//
//	Release();
//}
//
//// ����֪ͨ
//TEST(CtpMdApiWrapperTest, 06DepthMarketDataNotify) {
//	g_ctpMdApiTestParam = { '\0' };
//	g_ctpMdApiTestParam.isLogin = true;
//	g_ctpMdApiTestParam.isSubMarketData = true;
//	g_ctpMdApiTestParam.isMarketDataNotice = true;
//	Init();
//	//LogInfo("����֪ͨ: ��ʼ����");
//	std::unique_lock<mutex> lck(mut);
//	cond_va.wait_for(lck, std::chrono::seconds(5), []()-> bool { return g_marketDataNoticeOK && g_subMarketDataOK && g_unSubMarketDataOK; });
//	LogInfo("����֪ͨ: �Ѿ����");
//	EXPECT_TRUE(g_pMdUserApi != NULL);
//	EXPECT_TRUE(g_pMdSpi != NULL);
//	EXPECT_TRUE(g_loginOK);
//	EXPECT_TRUE(g_subMarketDataOK);
//	EXPECT_TRUE(g_marketDataNoticeOK);
//
//	Release();
//}
//
//// ����ѯ��
//TEST(CtpMdApiWrapperTest, 07SubForQuote) {
//	g_ctpMdApiTestParam = { '\0' };
//	g_ctpMdApiTestParam.isLogin = true;
//	g_ctpMdApiTestParam.isSubQuoteData = true;	
//	Init();
//	
//	std::unique_lock<mutex> lck(mut);
//	cond_va.wait_for(lck, std::chrono::seconds(5), []()-> bool { return g_subQuoteDataOK; });
//
//	EXPECT_TRUE(g_pMdUserApi != NULL);
//	EXPECT_TRUE(g_pMdSpi != NULL);
//	EXPECT_TRUE(g_loginOK);
//	EXPECT_TRUE(g_subQuoteDataOK);	 
//
//	Release();
//}
//
//// ȡ������ѯ��
//TEST(CtpMdApiWrapperTest, 08UnSubForQuote) {
//	g_ctpMdApiTestParam = { '\0' };
//	g_ctpMdApiTestParam.isLogin = true;
//	g_ctpMdApiTestParam.isSubQuoteData = true;
//	g_ctpMdApiTestParam.isUnSubQuoteData = true;
//	Init();
//	
//	std::unique_lock<mutex> lck(mut);
//	cond_va.wait_for(lck, std::chrono::seconds(5), []()-> bool { return g_unSubQuoteDataOK; });
//
//	EXPECT_TRUE(g_pMdUserApi != NULL);
//	EXPECT_TRUE(g_pMdSpi != NULL);
//	EXPECT_TRUE(g_loginOK);
//	EXPECT_TRUE(g_subQuoteDataOK);
//	EXPECT_TRUE(g_unSubQuoteDataOK);
//
//	Release();
//}
//
//// ѯ��֪ͨ
//TEST(CtpMdApiWrapperTest, 09ForQuoteNotify) {
//	g_ctpMdApiTestParam = { '\0' };
//	g_ctpMdApiTestParam.isLogin = true;
//	g_ctpMdApiTestParam.isSubQuoteData = true;
//	g_ctpMdApiTestParam.isQuoteDataNotice = true;
//	Init();
//	
//	std::unique_lock<mutex> lck(mut);
//	cond_va.wait_for(lck, std::chrono::seconds(5), []()-> bool { return g_quoteDataNoticeOK; });
//
//	EXPECT_TRUE(g_pMdUserApi != NULL);
//	EXPECT_TRUE(g_pMdSpi != NULL);
//	EXPECT_TRUE(g_loginOK);
//	EXPECT_TRUE(g_subQuoteDataOK);
//	EXPECT_TRUE(g_quoteDataNoticeOK);
//
//	Release();
//}
//
//// ��ѯ�鲥
//TEST(CtpMdApiWrapperTest, 10LookMulticast) {	
//	g_ctpMdApiTestParam = { '\0' };
//	g_ctpMdApiTestParam.isLogin = true;
//	g_ctpMdApiTestParam.isLookMulticast = true;	
//	Init();
//	
//	std::unique_lock<mutex> lck(mut);
//	cond_va.wait_for(lck, std::chrono::seconds(5), []()-> bool { return g_lookMulticastOK; });
//
//	EXPECT_TRUE(g_pMdUserApi != NULL);
//	EXPECT_TRUE(g_pMdSpi != NULL);
//	EXPECT_TRUE(g_loginOK);
//	EXPECT_TRUE(g_lookMulticastOK);
//
//	Release();
//}
//
//
