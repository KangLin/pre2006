/*!
\warning ��Ȩ���� (C) 2007 ���ֹ����ң���������Ȩ����
\file    JectDll.h
\brief   Զ��ע��DLL��
\version 1.0
\author  ��  �� (kl222@126.com)
\date    2007��6��2��  22:01:01
\par     ������:
         Microsoft Visual Studio 8.0 ���� C/C++ 8.0
*/

#ifndef __JECTDLL_H_KL_2007_06_02__
#define __JECTDLL_H_KL_2007_06_02__

#pragma once

#ifdef UNICODE
#define InjectLib InjectLibW
#define EjectLib  EjectLibW
#else
#define InjectLib InjectLibA
#define EjectLib  EjectLibA
#endif   // !UNICODE

BOOL WINAPI InjectLibA(DWORD dwProcessId, PCSTR pszLibFile);
BOOL WINAPI InjectLibW(DWORD dwProcessId, PCWSTR pszLibFile);
BOOL WINAPI EjectLibA(DWORD dwProcessId, PCSTR pszLibFile);
BOOL WINAPI EjectLibW(DWORD dwProcessId, PCWSTR pszLibFile);

#endif