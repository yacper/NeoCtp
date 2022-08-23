// pch.h: 这是预编译标头文件。
// 下方列出的文件仅编译一次，提高了将来生成的生成性能。
// 这还将影响 IntelliSense 性能，包括代码完成和许多代码浏览功能。
// 但是，如果此处列出的文件中的任何一个在生成之间有更新，它们全部都将被重新编译。
// 请勿在此处添加要频繁更新的文件，这将使得性能优势无效。

#ifndef PCH_H
#define PCH_H

#define WIN32_LEAN_AND_MEAN             // 从 Windows 头文件中排除极少使用的内容
// Windows 头文件
#include <windows.h>

#include"ThostFtdcUserApiStruct.h"
#include "ThostFtdcMdApi.h"   // 最新6.3.19版本 

#ifdef CTPMDAPIWRAPPER_EXPORTS
#define MDAPI_API __declspec(dllexport)
#else
#define MDAPI_API __declspec(dllimport)
#endif

#pragma comment (lib, "thostmduserapi_se.lib")

#pragma warning(disable : 4996)

#endif //PCH_H
