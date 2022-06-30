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
		cout << "���ӽ��׷�����..." << endl;
		if (m_pTdApi == NULL) {
			m_pTdApi = CreateFtdcTraderApi();									// ��������ʵ��		
			m_pTdApi->RegisterSpi(this);

			m_pTdApi->SubscribePrivateTopic(THOST_TERT_RESUME);		// ����˽����
			m_pTdApi->SubscribePublicTopic(THOST_TERT_RESUME);		// ���Ĺ�����
			m_pTdApi->RegisterFront(m_tradeFrontAddr);					// ��������ǰ�õ�ַ

			m_pTdApi->Init();											// ��ʼ�� ctp					
		}		
	}

	// �ص��ɹ������
	void NotifySuccess() 
	{
		m_isCheckOK = true;
		m_cndt_v.notify_one();
	}

	// �ص�ʧ��֪ͨ
	void NotifyFailed() 
	{
		m_isCheckOK = false;
		m_cndt_v.notify_one();
	}

	// ���ڼ�⵱ǰ�Ƿ�ɹ�
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
	// ��������
	TThostFtdcBrokerIDType m_brokerID = "9999";								 // ģ�⾭���̴���
	TThostFtdcInvestorIDType m_investerID = "180935";                         // Ͷ�����˻���
	TThostFtdcPasswordType m_investerPassword = "hello@123";                  // Ͷ��������

	// �������
	CThostFtdcTraderApi* m_pTdApi = nullptr;											// ����ָ��
	TraderSpi* m_pTdSpi = nullptr;											 // spi
	char m_tradeFrontAddr[28] = "tcp://180.168.146.187:10201";				 // ģ�⽻��ǰ�õ�ַ ��һ��
	//char m_tradeFrontAddr[28] = "tcp://180.168.146.187:10130";				 // ģ�⽻��ǰ�õ�ַ 24h

private:
	bool m_isCheckOK = false;
	std::mutex m_mtx;
	std::condition_variable m_cndt_v;

	int m_time = 7;															 // ��ʱʱ��	
};

