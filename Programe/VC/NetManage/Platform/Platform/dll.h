#ifndef __DLL_H_KL__
#define __DLL_H_KL__

#pragma once

#ifdef _WIN32
#include <windows.h>
#endif // ���� #ifdef _WIN32

#ifdef __LINUX__
#include <dlfcn.h>
#include "tchar.h"
#endif // ���� #ifdef __LINUX__


#ifdef _WIN32
typedef HMODULE dll_t;
#endif // ���� #ifdef _WIN32

#ifdef __LINUX__
typedef void * dll_t;
#endif // ���� #ifdef __LINUX__

/*******************************************************************************************************
��������load_library
��  ��������ָ���Ķ�̬���ӿ�
��  ����
        LPCTSTR lpFileName����̬���ļ���
����ֵ������Ϊ dll_t ���ɹ����ض�̬������ʧ�ܷ���NULL��
��  ����1.0
��  �ߣ���  ��
ʱ  �䣺2006��10��23�� 11:46:17
*******************************************************************************************************/
dll_t load_library(LPCTSTR lpFileName);

/*******************************************************************************************************
��������free_library
��  �����رն�̬���ӿ�
��  ����
        dll_t hDll����̬����
����ֵ������Ϊ int ���ɹ�����0�����򷵻ط��㡣
��  ����1.0
��  �ߣ���  ��
ʱ  �䣺2006��10��23�� 11:49:50
*******************************************************************************************************/
int free_library(dll_t hDll);

//�õ�ָ���ĺ���ָ��
void* get_function(dll_t hDll, LPCSTR lpFunName);

#endif //__DLL_H_KL__
