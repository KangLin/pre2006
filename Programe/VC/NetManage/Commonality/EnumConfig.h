/*!
\warning 版权所有 (C) 2007 康林工作室；保留所有权利。
\file    EnumConfig.h
\brief   用于枚举配置
\version 1.0
\author  康  林 (kl222@126.com)
\date    2007年7月2日  17:06:25
\par     编译器:
         Microsoft Visual Studio 8.0 —— C/C++ 8.0
*/

/*
枚举配置有下面约定：
一个枚举项目，
1、则项目下第一个关键字必为 Count ，用于指明这个配置中关键字的个数。
2、关键字的命名约定：
   项目名+其索引值
例如：
[DLL]
Count = 3                      ；动态链接库的个数
DLL1  = "process.dll"          ；关键字由“项目名 + 索引值”组成，值为动态链接库的全路径
DLL2  = "RemoteControl.dll"
DLL3  = "DeviceControl.dll"
.......

*/

#pragma once
#include "enum.h"
#include ".\Config.h"

#define COUNT _T("Count")

class CEnumConfig :	public CEnum, public CConfig
{
public:
	CEnumConfig(void);
	~CEnumConfig(void);

	//typedef INT(*ENUMOPERATE)(LPCTSTR pszValue);
	virtual INT Enum(LPCTSTR pszItem, ENUMOPERATE eo);

	INT AddKey(LPCTSTR pszItem, LPCTSTR pszValue);
	INT DeleteKey(LPCTSTR pszItem, LPCTSTR pszValue);

};
