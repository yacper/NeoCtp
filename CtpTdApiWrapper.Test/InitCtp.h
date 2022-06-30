#pragma once
#include "ICtpTdApi.h"

class InitCtp : public ICtpTdApi
{
public:
	
	virtual void Run() 
	{
		InitTdApi();
	}

	virtual void OnFrontConnected() 
	{
		std::cout << "连接网络成功" << std::endl;		
		NotifySuccess();
	}

	virtual void OnFrontDisconnected(int nReason) 
	{
		std::cout << "网络连接断开" << std::endl;
		std::cerr << "nReason： " << nReason << std::endl;
	};

};

TEST(CtpApiTest, 01InitCtp)
{
	InitCtp initCtp;
	initCtp.Run();
	bool isOK = initCtp.CheckIsOK();
	EXPECT_TRUE(isOK);
}
