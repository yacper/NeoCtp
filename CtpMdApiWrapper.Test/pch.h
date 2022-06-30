//
// pch.h
// Header for standard system include files.
//

#pragma once
#define WIN32_LEAN_AND_MEAN             // 从 Windows 头文件中排除极少使用的内容
// Windows 头文件
#include <windows.h>

#include <iostream>
#include "gtest/gtest.h"
#include "ThostFtdcMdApi.h"   // 最新6.3.19版本 

#pragma comment (lib, "CtpMdApiWrapper.lib")

#pragma warning(disable : 4996)

