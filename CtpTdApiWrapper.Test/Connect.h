#pragma once
#include "TdApiTestBase.h"

void OnFrontConnected()
{
	std::cout << "连接网络成功" << std::endl;
	TestBase->NotifySuccess();
}


class Connect : public TdApiTestBase
{
public:
	virtual void Run()
	{
		InitTdApi();
		RegOnFrontConnected(m_pTdSpi, OnFrontConnected);
	}


	virtual void OnFrontDisconnected(int nReason)
	{
		std::cout << "网络连接断开" << std::endl;
		std::cerr << "nReason： " << nReason << std::endl;
	};

};

TEST(CtpApiTest, 01Connect)
{
	Connect initCtp;
	TestBase = &initCtp;
	initCtp.Run();
	bool isOK = initCtp.CheckIsOK();
	EXPECT_TRUE(isOK);
}
