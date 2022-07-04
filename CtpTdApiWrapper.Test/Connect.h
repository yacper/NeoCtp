#pragma once
#include "TdApiTestBase.h"

void OnFrontConnected()
{
	std::cout << "OnFrontConnected 连接网络成功" << std::endl;
	TestBase->NotifySuccess();
}

void OnFrontDisconnected(int nReason)
{
	std::cout << "OnFrontDisconnected 网络连接断开" << std::endl;
	std::cerr << "nReason： " << nReason << std::endl;
};


class Connect : public TdApiTestBase
{
public:
	virtual void Run()
	{
		InitTdApi();
		RegOnRspFrontConnected(m_pTdSpi, OnFrontConnected);
		RegOnRspFrontDisconnected(m_pTdSpi, OnFrontDisconnected);
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
