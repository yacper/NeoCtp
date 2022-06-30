#pragma once
#include "TdApiTestBase.h"

void OnFrontConnected()
{
	std::cout << "��������ɹ�" << std::endl;
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
		std::cout << "�������ӶϿ�" << std::endl;
		std::cerr << "nReason�� " << nReason << std::endl;
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
