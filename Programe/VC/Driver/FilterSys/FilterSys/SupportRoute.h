/*!
\warning 版权所有 (C) 2007 康林工作室；保留所有权利。
\file    SupportRoute.h
\brief   支持函数的头文件
\version 1.0
\author  康  林 (kl222@126.com)
\date    2007年6月7日  13:53:46
\par     编译器:
         Microsoft Visual Studio 8.0 —— C/C++ 8.0
*/

#ifndef __SUPPORT_H_KL_2007_06_05__
#define __SUPPORT_H_KL_2007_06_05__

#pragma once

typedef PVOID POBJECT;

void GetFullName(HANDLE hKey, PUNICODE_STRING lpszSubKeyVal,
				 PCHAR fullname);

//ULONG GetProcessNameOffset();

//PCHAR GetProcess(PCHAR Name);

VOID ConvertToUpper(PCHAR Dest, PCHAR Source, ULONG Len);

POBJECT GetPointer(HANDLE handle);

VOID ReleasePointer(POBJECT object);

VOID AppendKeyInformation(IN KEY_INFORMATION_CLASS KeyInformationClass,
						  IN PVOID KeyInformation, PCHAR Buffer);

VOID AppendRegValueType(ULONG Type, PCHAR Buffer);

VOID AppendRegValueData(IN ULONG Type, IN PVOID Data, IN ULONG Length,
						IN OUT PCHAR Buffer);

VOID AppendValueInformation(IN KEY_VALUE_INFORMATION_CLASS KeyValueInformationClass,
							IN PVOID KeyValueInformation, PCHAR Buffer, PCHAR ValueName);

PCHAR ErrorString(NTSTATUS retval);

PCHAR strncatZ(PCHAR dest, PCHAR source, int length);



#endif // __SUPPORT_H_KL_2007_06_05__