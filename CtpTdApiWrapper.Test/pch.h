//
// pch.h
//

#pragma once

#define WIN32_LEAN_AND_MEAN             // 从 Windows 头文件中排除极少使用的内容
// Windows 头文件
#include <windows.h>

#include <iostream>
#include "gtest/gtest.h"


#include "ThostFtdcTraderApi.h"   // 最新6.3.19版本 
#include "ThostFtdcUserApiDataType.h"   // 最新6.3.19版本 
#include "ThostFtdcUserApiStruct.h"   // 最新6.3.19版本 


#pragma comment (lib, "CtpTdApiWrapper.lib")

#pragma warning(disable : 4996)



