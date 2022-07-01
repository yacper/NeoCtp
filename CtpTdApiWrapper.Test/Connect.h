#pragma once
#include "TdApiTestBase.h"

void OnFrontConnected()
{
	std::cout << "OnFrontConnected ��������ɹ�" << std::endl;
	TestBase->NotifySuccess();
}

void OnFrontDisconnected(int nReason)
{
	std::cout << "OnFrontDisconnected �������ӶϿ�" << std::endl;
	std::cerr << "nReason�� " << nReason << std::endl;
};


class Connect : public TdApiTestBase
{
public:
	virtual void Run()
	{
		InitTdApi();
		RegOnFrontConnected(m_pTdSpi, OnFrontConnected);
		RegOnFrontDisconnected(m_pTdSpi, OnFrontDisconnected);
	}
};

TEST(CtpApiTest, 01Connect)
{
	Connect initCtp;
	TestBase = &initCtp;
	initCtp.Run();
	bool isOK = initCtp.CheckIsOK();
	EXPECT_TRUE(isOK);
}
