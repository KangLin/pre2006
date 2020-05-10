/*!
\warning ��Ȩ���� (C) 2007 ���ֹ����ң���������Ȩ����
\file    EnumConfig.h
\brief   ����ö������
\version 1.0
\author  ��  �� (kl222@126.com)
\date    2007��7��2��  17:06:25
\par     ������:
         Microsoft Visual Studio 8.0 ���� C/C++ 8.0
*/

/*
ö������������Լ����
һ��ö����Ŀ��
1������Ŀ�µ�һ���ؼ��ֱ�Ϊ Count ������ָ����������йؼ��ֵĸ�����
2���ؼ��ֵ�����Լ����
   ��Ŀ��+������ֵ
���磺
[DLL]
Count = 3                      ����̬���ӿ�ĸ���
DLL1  = "process.dll"          ���ؼ����ɡ���Ŀ�� + ����ֵ����ɣ�ֵΪ��̬���ӿ��ȫ·��
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
