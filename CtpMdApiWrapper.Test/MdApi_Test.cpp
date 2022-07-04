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
//char gMdFrontAddr[] = "tcp://180.168.146.187:10211";               // ģ������ǰ�õ�ַ ��һ��
char gMdFrontAddr[] = "tcp://180.168.146.187:10131";               // ģ������ǰ�õ�ַ 24h

char* g_InstrumentID[] = { "rb2210","hc2210" };						// �����Լ�����б��С��ϡ���֣��������ѡһ��
int g_InstrumentNum = 2;												// �����Լ��������


//string instrumentPath = "instrument.txt";

CThostFtdcMdApi* g_pMdUserApi = nullptr;                           // ����ָ��
MdSpi* g_pMdSpi = nullptr;                           // spi

bool g_FrontConnected = false;	// ����������

// ��¼
bool g_Logined = false;		// �ѵ�¼
bool g_logoutOK = false;

// �г�����
int g_subMarketDataTimes = 0;
int g_unSubMarketDataTimes = 0;
bool g_marketDataNoticeOK = false;

// ѯ��
int g_subQuoteDataTimes = 0;
int g_unSubQuoteDataTimes = 0;
bool g_quoteDataNoticeOK = false;

// ��ѯ�鲥
bool g_lookMulticastOK = false;

// �߳�ͬ������
mutex g_Mutex;
condition_variable g_Condition;


#pragma region Log
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
#pragma endregion

#pragma region callbacks
// ����֪ͨ
void WINAPI
OnRspError(CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (bResult)
	{
		char buf[512] = { '\0' };
		sprintf(buf, "���ش���--->>> RequestID=%d ErrorID=%d, ErrorMsg=%s", nRequestID, pRspInfo->ErrorID, pRspInfo->ErrorMsg);
		LogInfo(buf, LogLevel::Error);

		{// ֪ͨ����
			g_Condition.notify_one();
		}
	}
}

// ������ʱ����
void WINAPI OnHeartBeatWarning(int nTimeLapse)
{
	char errorLog[128] = { '\0' };
	sprintf(errorLog, "=====����������ʱ=====\n ���ϴ�����ʱ�䣺%d", nTimeLapse);
	LogInfo(errorLog, LogLevel::Error);
}




class TestEnv :public testing::Environment
{
public:
	void SetUp()
	{
		InitLog();

		// ��ʼ�������߳�
		cout << "��ʼ������..." << endl;
		g_pMdUserApi = CreateFtdcMdApi();			// ��������ʵ��
		g_pMdSpi = CreateMdSpi();					// ��������ص�	

		RegisterSpi(g_pMdUserApi, g_pMdSpi);		// ע��ص�
		RegisterFront(g_pMdUserApi, gMdFrontAddr);  // ��������ǰ�õ�ַ

		/// callbacks
		RegOnRspError(g_pMdSpi, OnRspError);
		RegOnHeartBeatWarning(g_pMdSpi, OnHeartBeatWarning);

		//Join(g_pMdUserApi);		// �ȴ��߳��˳�
	}

	void TearDown()
	{
		Release(g_pMdUserApi);
		g_pMdUserApi = NULL;
		g_pMdSpi = NULL;
	}
};

#pragma endregion

void WINAPI  OnFrontConnected()
{
	g_FrontConnected = true;

	char logBuf[128] = { '\0' };
	sprintf(logBuf, "OnFrontConnected API Version: %s", g_pMdUserApi->GetApiVersion());
	LogInfo(logBuf);

	g_Condition.notify_one();
}


// �Ͽ�����֪ͨ
void WINAPI OnFrontDisconnected(int nReason)
{
	g_FrontConnected = false;

	char errorLog[128] = { '\0' };
	sprintf(errorLog, "=====�������ӶϿ�===== \n �����룺%d", nReason);
	LogInfo(errorLog, LogLevel::Error);
}


// ��ʼ��
TEST(CtpMdApiWrapperTest, 01_Connect)
{
	ASSERT_TRUE(g_pMdUserApi != NULL);
	ASSERT_TRUE(g_pMdSpi != NULL);

	RegOnRspFrontConnected(g_pMdSpi, OnFrontConnected);
	RegOnRspFrontDisconnected(g_pMdSpi, OnFrontDisconnected);

	Init(g_pMdUserApi);                                // ��������

	// wait 5 secs for connecting
	std::unique_lock<mutex> lck(g_Mutex);
	g_Condition.wait_for(lck, std::chrono::seconds(5), []()-> bool { return g_FrontConnected; });

	ASSERT_TRUE(g_FrontConnected);

	ASSERT_STREQ(GetApiVersion(), "v6.3.19_P1_20200106 15:21:32");
}

// ��¼Ӧ��
void WINAPI OnRspUserLogin(
	CThostFtdcRspUserLoginField* pRspUserLogin,
	CThostFtdcRspInfoField* pRspInfo,
	int nRequestID,
	bool bIsLast)
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult)
	{
		g_Logined = true;

		char buf[1024] = { '\0' };
		sprintf(buf, "=====�˻���¼�ɹ�===== \n �����գ� %s \n ��¼ʱ�䣺 %s \n �����̣� %s \n �ʻ����� %s",
				pRspUserLogin->TradingDay, pRspUserLogin->LoginTime, pRspUserLogin->BrokerID, pRspUserLogin->UserID);

		LogInfo(buf);

		//return;



		//if (g_ctpMdApiTestParam.isLookMulticast)
		//{
			//}
	}
	else
	{
		char buf[1024] = { '\0' };
		sprintf(buf, "��¼ʧ�ܡ����ش���--->>> ErrorID=%d, ErrorMsg=%s", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
		LogInfo(buf, LogLevel::Error);
	}

	g_Condition.notify_one();
}


// ��¼
TEST(CtpMdApiWrapperTest, 02_Login)
{

	RegOnRspUserLogin(g_pMdSpi, OnRspUserLogin);

	// ��ʼ��¼
	CThostFtdcReqUserLoginField loginReq;
	memset(&loginReq, 0, sizeof(loginReq));
	strcpy(loginReq.BrokerID, gBrokerID);
	strcpy(loginReq.UserID, gInvesterID);
	strcpy(loginReq.Password, gInvesterPassword);
	int requestID = 0; // ������

	int rt = ReqUserLogin(g_pMdUserApi, &loginReq, requestID);

	if (!rt)
		LogInfo(">>>>>>���͵�¼����ɹ�");
	else
		LogInfo("--->>>���͵�¼����ʧ��", LogLevel::Error);


	std::unique_lock<mutex> lck(g_Mutex);
	g_Condition.wait_for(lck, std::chrono::seconds(10), []()-> bool { return g_Logined; });

	ASSERT_TRUE(g_Logined);

	RegOnRspUserLogin(g_pMdSpi, nullptr);
}


// ��������Ӧ��
void WINAPI OnRspSubMarketData(
	CThostFtdcSpecificInstrumentField* pSpecificInstrument,
	CThostFtdcRspInfoField* pRspInfo,
	int nRequestID,
	bool bIsLast)
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult)
	{

		char logBuf[128] = { '\0' };
		sprintf(logBuf, "=====��������ɹ�  ��Լ���룺 %s", pSpecificInstrument->InstrumentID);
		LogInfo(logBuf);

		g_subMarketDataTimes += 1;

		// �����Ҫ�����ļ��������ݿ⣬�����ﴴ����ͷ,��ͬ�ĺ�Լ�����洢
		char filePath[100] = { '\0' };
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
	else
	{
		char buf[1024] = { '\0' };
		sprintf(buf, "===��������ʧ��===\n���ش���--->>> ErrorID=%d, ErrorMsg=%s", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
		LogInfo(buf, LogLevel::Error);
	}

	g_Condition.notify_one();
}

// ��������֪ͨ
void WINAPI OnRtnDepthMarketData(CThostFtdcDepthMarketDataField* pDepthMarketData)
{
	// ��ӡ���飬�ֶν϶࣬��ȡ����
	char logBuf[1024] = { '\0' };
	sprintf(logBuf, "=====����������===== \n �����գ� %s  %s.%d\n ���������룺 %s\n ��Լ���룺 %s\n ��Լ�ڽ������Ĵ��룺 %s\n ���¼ۣ� %f\n ������ %d",
			pDepthMarketData->TradingDay, pDepthMarketData->UpdateTime, pDepthMarketData->UpdateMillisec, pDepthMarketData->ExchangeID, pDepthMarketData->InstrumentID, pDepthMarketData->ExchangeInstID, (float)pDepthMarketData->LastPrice, pDepthMarketData->Volume);
	LogInfo(logBuf);

	// ���ֻ��ȡĳһ����Լ���飬������tick�ش����ļ������ݿ�
	char filePath[100] = { '\0' };
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


	g_marketDataNoticeOK = true;
	g_Condition.notify_one();
}


// ��������
TEST(CtpMdApiWrapperTest, 03_SubMarketData)
{
	RegOnRspSubMarketData(g_pMdSpi, OnRspSubMarketData);
	RegOnRtnDepthMarketData(g_pMdSpi, OnRtnDepthMarketData);

	// ������������
	int rt = SubscribeMarketData(g_pMdUserApi, g_InstrumentID, g_InstrumentNum);
	if (!rt)
		LogInfo(">>>>>>���Ͷ�����������ɹ�");
	else
		LogInfo("--->>>���Ͷ�����������ʧ��", LogLevel::Error);


	std::unique_lock<mutex> lck(g_Mutex);
	g_Condition.wait_for(lck, std::chrono::seconds(10), []()-> bool { return g_subMarketDataTimes && g_marketDataNoticeOK; });


	EXPECT_EQ(g_subMarketDataTimes, 2);
	EXPECT_TRUE(g_marketDataNoticeOK);

	// wait for more datas
	Sleep(3000);

	//RegOnRspSubMarketData(g_pMdSpi, nullptr);
	//RegOnRtnDepthMarketData(g_pMdSpi, nullptr);
}

// ȡ����������Ӧ��
void WINAPI OnRspUnSubMarketData(
	CThostFtdcSpecificInstrumentField* pSpecificInstrument,
	CThostFtdcRspInfoField* pRspInfo,
	int nRequestID,
	bool bIsLast)
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult)
	{
		g_unSubMarketDataTimes += 1;

		char logBuf[128] = { '\0' };
		sprintf(logBuf, "=====ȡ����������ɹ�===== \n ��Լ���룺 %s", pSpecificInstrument->InstrumentID);
		LogInfo(logBuf);
	}
	else
	{
		char buf[1024] = { '\0' };
		sprintf(buf, "===ȡ����������ʧ��===\n���ش���--->>> ErrorID=%d, ErrorMsg=%s", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
		LogInfo(buf, LogLevel::Error);
	}
	g_Condition.notify_one();
}


// ȡ���������
TEST(CtpMdApiWrapperTest, 04_UnSubMarketData)
{
	RegOnRspUnSubMarketData(g_pMdSpi, OnRspUnSubMarketData);

	// ȡ����������
	int rt = g_pMdUserApi->UnSubscribeMarketData(g_InstrumentID, g_InstrumentNum);
	if (!rt)
		LogInfo(">>>>>>����ȡ��������������ɹ�");
	else
		LogInfo("--->>>����ȡ��������������ʧ��", LogLevel::Error);


	std::unique_lock<mutex> lck(g_Mutex);
	// unsub ����Ҫ������2��
	g_Condition.wait_for(lck, std::chrono::seconds(5), []()-> bool { return g_unSubMarketDataTimes == g_InstrumentNum; });

	EXPECT_EQ(g_unSubMarketDataTimes, g_InstrumentNum);
}

// ����ѯ��Ӧ��
void WINAPI OnRspSubForQuoteRsp(
	CThostFtdcSpecificInstrumentField* pSpecificInstrument,
	CThostFtdcRspInfoField* pRspInfo,
	int nRequestID,
	bool bIsLast)
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult)
	{
		g_subQuoteDataTimes += 1;

		char logBuf[128] = { '\0' };
		sprintf(logBuf, "=====����ѯ�۳ɹ�===== ��Լ���룺 %s", pSpecificInstrument->InstrumentID);
		LogInfo(logBuf);
	}
	else
	{
		char buf[1024] = { '\0' };
		sprintf(buf, "===����ѯ��ʧ��===\n���ش���--->>> ErrorID=%d, ErrorMsg=%s", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
		LogInfo(buf, LogLevel::Error);
	}
	g_Condition.notify_one();
}

void WINAPI OnRtnForQuoteRsp(CThostFtdcForQuoteRspField* pForQuoteRsp)
{
	// ����ѯ�۽��
	char logBuf[1024] = { '\0' };
	sprintf(logBuf, "=====���ѯ�۽��=====\n �����գ� %s\n ���������룺 %s\n ��Լ���룺 %s\n ѯ�۱�ţ� %s",
			pForQuoteRsp->TradingDay, pForQuoteRsp->ExchangeID, pForQuoteRsp->InstrumentID, pForQuoteRsp->ForQuoteSysID);

	LogInfo(logBuf);

	g_quoteDataNoticeOK = true;
	g_Condition.notify_one();
}

// ����ѯ��
TEST(CtpMdApiWrapperTest, 05_SubForQuote)
{
	RegOnRspSubForQuoteRsp(g_pMdSpi, OnRspSubForQuoteRsp);
	RegOnRtnForQuoteRsp(g_pMdSpi, OnRtnForQuoteRsp);

	// ����ѯ��
	int rt = SubscribeForQuoteRsp(g_pMdUserApi, g_InstrumentID, g_InstrumentNum);

	if (!rt)
		LogInfo(">>>>>>���Ͷ���ѯ������ɹ�");
	else
		LogInfo("--->>>���Ͷ���ѯ������ʧ��", LogLevel::Error);


	std::unique_lock<mutex> lck(g_Mutex);
	g_Condition.wait_for(lck, std::chrono::seconds(5), []()-> bool { return g_subQuoteDataTimes == g_InstrumentNum && g_quoteDataNoticeOK; });

	EXPECT_EQ(g_subQuoteDataTimes, g_InstrumentNum);
	EXPECT_FALSE(g_quoteDataNoticeOK);  // ����false��quote ����rtn��û������
}


// ȡ������ѯ��Ӧ��
void WINAPI OnRspUnSubForQuoteRsp(CThostFtdcSpecificInstrumentField* pSpecificInstrument, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
	if (!bResult)
	{
		g_unSubQuoteDataTimes += 1;

		char logBuf[128] = { '\0' };
		sprintf(logBuf, "=====ȡ������ѯ�۳ɹ�===== ��Լ���룺 %s", pSpecificInstrument->InstrumentID);
		LogInfo(logBuf);
	}
	else
	{
		char buf[1024] = { '\0' };
		sprintf(buf, "===ȡ������ѯ��ʧ��===\n���ش���--->>> ErrorID=%d, ErrorMsg=%s", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
		LogInfo(buf, LogLevel::Error);
	}
	g_Condition.notify_one();
}


// ȡ������ѯ��
TEST(CtpMdApiWrapperTest, 06_UnSubForQuote)
{
	RegOnRspUnSubForQuoteRsp(g_pMdSpi, OnRspUnSubForQuoteRsp);
	//ȡ������ѯ��
	int rt = g_pMdUserApi->UnSubscribeForQuoteRsp(g_InstrumentID, g_InstrumentNum);
	if (!rt)
		LogInfo(">>>>>>����ȡ������ѯ������ɹ�");
	else
		LogInfo("--->>>����ȡ������ѯ������ʧ��", LogLevel::Error);


	std::unique_lock<mutex> lck(g_Mutex);
	g_Condition.wait_for(lck, std::chrono::seconds(5), []()-> bool { return g_unSubQuoteDataTimes == g_InstrumentNum; });

	EXPECT_EQ(g_unSubQuoteDataTimes, g_InstrumentNum);
}

void WINAPI OnRspQryMulticastInstrument(CThostFtdcMulticastInstrumentField* pMulticastInstrument, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);

	if (!bResult)
	{
		char logBuf[1024] = { '\0' };
		sprintf(logBuf, "����ţ� %d\n ��Լ���룺%s\n ��Լ��ţ�%d\n ��׼�ۣ�%f\n ��Լ����������%d\n ��С�䶯��λ: %f",
				pMulticastInstrument->TopicID, pMulticastInstrument->InstrumentID, pMulticastInstrument->InstrumentNo, pMulticastInstrument->CodePrice, pMulticastInstrument->VolumeMultiple, pMulticastInstrument->PriceTick);

		LogInfo(logBuf);

		g_lookMulticastOK = true;
	}
	else
	{
		char buf[1024] = { '\0' };
		sprintf(buf, "===�鿴��Լ�鲥ʧ��===\n���ش���--->>> ErrorID=%d, ErrorMsg=%s", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
		LogInfo(buf, LogLevel::Error);
	}
	g_Condition.notify_one();
}

// ��ѯ�鲥
TEST(CtpMdApiWrapperTest, 07_LookMulticast)
{
	RegOnRspQryMulticastInstrument(g_pMdSpi, OnRspQryMulticastInstrument);

	CThostFtdcQryMulticastInstrumentField multicastInstrumentField = { '\0' };
	multicastInstrumentField.TopicID = 1001;		//��Ӧ���������鲥����topic			
	strcpy(multicastInstrumentField.InstrumentID, g_InstrumentID[0]);
	int rt = g_pMdUserApi->ReqQryMulticastInstrument(&multicastInstrumentField, 1);
	if (!rt)
		LogInfo(">>>>>>���Ͳ�ѯ�鲥����ɹ�");
	else
		LogInfo("--->>>���Ͳ�ѯ�鲥����ʧ��", LogLevel::Error);


	std::unique_lock<mutex> lck(g_Mutex);
	g_Condition.wait_for(lck, std::chrono::seconds(5), []()-> bool { return g_lookMulticastOK; });

	EXPECT_FALSE(g_lookMulticastOK);  // ������ ErrorID=77, ErrorMsg=CTP:�޴˹���
}



// �ǳ�Ӧ��
void WINAPI OnRspUserLogout(
	CThostFtdcUserLogoutField* pUserLogout,
	CThostFtdcRspInfoField* pRspInfo,
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
	}
	else
	{
		char buf[1024] = { '\0' };
		sprintf(buf, "�ǳ�ʧ�ܡ����ش���--->>> ErrorID=%d, ErrorMsg=%s", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
		LogInfo(buf, LogLevel::Error);
	}

	g_Condition.notify_one();
}


// �ǳ�
TEST(CtpMdApiWrapperTest, 08_Logout)
{
	RegOnRspUserLogout(g_pMdSpi, OnRspUserLogout);

	// �ǳ�����
	CThostFtdcUserLogoutField logout = { "\0" };
	std::strcpy(logout.BrokerID, gBrokerID);
	std::strcpy(logout.UserID, gInvesterID);
	int rt = ReqUserLogout(g_pMdUserApi, &logout, 33);
	if (!rt)
		LogInfo(">>>>>>���͵ǳ�����ɹ�");
	else
		LogInfo("--->>>���͵ǳ�����ʧ��", LogLevel::Error);


	std::unique_lock<mutex> lck(g_Mutex);
	g_Condition.wait_for(lck, std::chrono::seconds(5), []()-> bool { return g_logoutOK; });

	// logout �����ڲ������޷�ʹ��
	EXPECT_FALSE(g_logoutOK);  //���ش���--->>> RequestID=0 ErrorID=77, ErrorMsg=CTP:�޴˹��� 
}




int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);

	testing::Environment* env = new TestEnv();
	testing::AddGlobalTestEnvironment(env);


	RUN_ALL_TESTS();
	getchar();
	return 0;
}
