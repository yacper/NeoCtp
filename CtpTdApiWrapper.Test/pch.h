//
// pch.h
//

#pragma once

#define WIN32_LEAN_AND_MEAN             // �� Windows ͷ�ļ����ų�����ʹ�õ�����
// Windows ͷ�ļ�
#include <windows.h>

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <mutex>
#include <functional>

#include "gtest/gtest.h"


#include "ThostFtdcTraderApi.h"   // ����6.3.19�汾 
#include "ThostFtdcUserApiDataType.h"   // ����6.3.19�汾 
#include "ThostFtdcUserApiStruct.h"   // ����6.3.19�汾 

#include "..\CtpTdApiWrapper\TraderApi.h"
#include "..\CtpTdApiWrapper\TraderSpi.h"

#pragma comment (lib, "CtpTdApiWrapper.lib")

#pragma warning(disable : 4996)



