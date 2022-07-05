#pragma once
#include "ThostFtdcTraderApi.h"   // 最新6.3.19版本 
#include "ThostFtdcUserApiDataType.h"   // 最新6.3.19版本 
#include "ThostFtdcUserApiStruct.h"   // 最新6.3.19版本 

// 公共参数
TThostFtdcBrokerIDType gBrokerID = "9999";                         // 模拟经纪商代码
TThostFtdcInvestorIDType gInvesterID = "097266";                         // 投资者账户名
TThostFtdcPasswordType gInvesterPassword = "hello@1234";                     // 投资者密码

// 行情参数
char gTradeFrontAddr[] = "tcp://180.168.146.187:10201";            // 模拟交易前置地址 第一组
//char gTradeFrontAddr[] = "tcp://180.168.146.187:10130";            // 模拟交易前置地址 24h

char *g_pInstrumentID[] = {"rb2210", "hc2205", "i2205", "j2205"}; // 行情合约代码列表，中、上、大、郑交易所各选一种
int instrumentNum = 4;                                             // 行情合约订阅数量

