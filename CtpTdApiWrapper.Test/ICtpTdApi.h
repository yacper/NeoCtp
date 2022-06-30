#pragma once
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <mutex>
#include "pch.h"
#include "..\CtpTdApiWrapper\TraderApi.h"
#include "..\CtpTdApiWrapper\TraderSpi.h"
#include <functional>
using namespace std;


class ICtpTdApi:CThostFtdcTraderSpi
{
public:
	
	void InitTdApi()
	{
		cout << "连接交易服务器..." << endl;
		if (m_pTdApi == NULL) {
			m_pTdApi = CreateFtdcTraderApi();									// 创建行情实例		
			m_pTdApi->RegisterSpi(this);

			m_pTdApi->SubscribePrivateTopic(THOST_TERT_RESUME);		// 订阅私有流
			m_pTdApi->SubscribePublicTopic(THOST_TERT_RESUME);		// 订阅公有流
			m_pTdApi->RegisterFront(m_tradeFrontAddr);					// 设置行情前置地址

			m_pTdApi->Init();											// 初始化 ctp					
		}		
	}

	// 回调成功后调用
	void NotifySuccess() 
	{
		m_isCheckOK = true;
		m_cndt_v.notify_one();
	}

	// 回调失败通知
	void NotifyFailed() 
	{
		m_isCheckOK = false;
		m_cndt_v.notify_one();
	}

	// 用于检测当前是否成功
	virtual bool CheckIsOK() 
	{
		if (m_isCheckOK) {
			m_isCheckOK = false;
			return true;
		}

		std::unique_lock<mutex> lck(m_mtx);
		m_cndt_v.wait_for(lck, chrono::seconds(m_time));
		
		bool isOK = m_isCheckOK;
		m_isCheckOK = false;
		return isOK;
	}

	~ICtpTdApi()
	{
		Release();
	}

private:

	void Release() {
		// m_pTdApi->Join();
		m_pTdApi->Release();
		m_pTdApi = NULL;
	}

public:
	// 公共参数
	TThostFtdcBrokerIDType m_brokerID = "9999";								 // 模拟经纪商代码
	TThostFtdcInvestorIDType m_investerID = "180935";                         // 投资者账户名
	TThostFtdcPasswordType m_investerPassword = "hello@123";                  // 投资者密码

	// 行情参数
	CThostFtdcTraderApi* m_pTdApi = nullptr;											// 行情指针
	TraderSpi* m_pTdSpi = nullptr;											 // spi
	char m_tradeFrontAddr[28] = "tcp://180.168.146.187:10201";				 // 模拟交易前置地址 第一组
	//char m_tradeFrontAddr[28] = "tcp://180.168.146.187:10130";				 // 模拟交易前置地址 24h

private:
	bool m_isCheckOK = false;
	std::mutex m_mtx;
	std::condition_variable m_cndt_v;

	int m_time = 7;															 // 超时时间	
};

