/*!
\warning ��Ȩ���� (C) 2007 ���ֹ����ң���������Ȩ����
\file    RegisterMonitorControl.cpp
\brief   ע�������������ʵ���ļ�
\version 1.0
\author  ��  �� (kl222@126.com)
\date    2007��6��7��  13:58:42
\par     ������:
         Microsoft Visual Studio 8.0 ���� C/C++ 8.0
*/

#include "StdAfx.h"
#include <windows.h>   
#include <tchar.h>
#include <winioctl.h>
#include "RegisterFilterControl.h"
#include "..\FilterSys\IoctlCmd.h"
#include <AtlBase.h>
#include <AtlConv.h>
#include <atlstr.h>
#include "..\..\..\System\File\FileEx.h"

#ifndef ASSERT
#define ASSERT _ASSERT
#endif

CRegisterFilterControl::CRegisterFilterControl(void)
{
}

CRegisterFilterControl::~CRegisterFilterControl(void)
{
}

/*!
\brief   �ҹ�ע����������
\return  ����Ϊ BOOL ��
\version 1.0
\author  ��  ��
\date    2007-6-7 14:00:09
*/
BOOL CRegisterFilterControl::Hook()
{
	DWORD nRetBytes = 0;
	BOOL bRet = TRUE;
	bRet = DeviceIoControl(REGFILTER_HOOK, NULL, NULL, NULL, NULL, &nRetBytes);
	return bRet;
}

/*!
\brief   UnHookReg
\return  ����Ϊ BOOL ��
\version 1.0
\author  ��  ��
\date    2007-6-7 14:00:47
*/
BOOL CRegisterFilterControl::UnHook()
{
	DWORD nRetBytes = 0;
	BOOL bRet = TRUE;
	bRet = DeviceIoControl(REGFILTER_UNHOOK, NULL, NULL, NULL, NULL, &nRetBytes);
	return bRet;
}

/*!
\brief   ���뱣������
\param   LPCTSTR pszContent��Ҫ��������
\return  ����Ϊ BOOL ���ɹ�����TRUE�����򷵻�FALSE��
\version 1.0
\author  ��  ��
\date    2007-6-7 14:00:56
*/
BOOL CRegisterFilterControl::SetProtectContent(LPCTSTR pszContent)
{
	USES_CONVERSION;
	ASSERT(pszContent);
	if(NULL == pszContent)
	{
		return FALSE;
	} // ���� if(NULL == szFile)
	BOOL bRet = TRUE;
	int nLen = (_tcslen(pszContent) + 1) * sizeof(TCHAR);
	LPTSTR p = new TCHAR[nLen];
	if(NULL == p)
	{
		return FALSE;
	} // ���� if(NULL == p)
	memcpy(p, (PVOID)pszContent, nLen);
	LPWSTR pszFile = T2W(p);
	pszFile = _tcsupr(pszFile);
	bRet = DeviceIoControl(REGFILTER_SET_PROTECT, pszFile, (wcslen(pszFile) + 1) * sizeof(WCHAR), NULL, 0);
	delete []p;
	return bRet;
}

/*!
\brief   �Ƴ���������
\param   LPCTSTR pszContent��Ҫ��������
\return  ����Ϊ BOOL ���ɹ�����TRUE�����򷵻�FALSE��
\version 1.0
\author  ��  ��
\date    2007-6-7 14:01:32
*/
BOOL CRegisterFilterControl::RemoveProtectContent(LPCTSTR pszContent)
{
	USES_CONVERSION;
	ASSERT(pszContent);
	if(NULL == pszContent)
	{
		return FALSE;
	} // ���� if(NULL == szFile)
	BOOL bRet = TRUE;
	int nLen = (_tcslen(pszContent) + 1)*sizeof(TCHAR);
	LPTSTR p = new TCHAR[nLen];
	if(NULL == p)
	{
		return FALSE;
	} // ���� if(NULL == p)
	memcpy(p, (PVOID)pszContent, nLen);
	LPWSTR pszFile = T2W(p);
	pszFile = _tcsupr(pszFile);
	bRet = DeviceIoControl(REGFILTER_REMOVE_PROTECT, pszFile, (wcslen(pszFile) + 1) * sizeof(WCHAR), NULL, 0);
	delete []p;
	return bRet;
}

/*!
\brief   Load Config from the file
\param   LPCTSTR lpszFile��the config file name
\return  ����Ϊ BOOL ��If success, return TRUE, otherwise,return FALSE.
\version 1.0
\author  ��  ��
\date    2007-5-22 14:31:49
*/
BOOL CRegisterFilterControl::LoadConfig(LPCTSTR lpszFile)
{
	BOOL bRet = TRUE;
	CString szTmp, szFile;
	CFileEx f;

	ASSERT(lpszFile);
	szFile = lpszFile;

	bRet = f.Open(szFile);
	if(bRet)
	{
		while(f.ReadString(szTmp))
		{
			bRet = SetProtectContent(szTmp.Left(szTmp.GetLength() - 1));
		}// ���� while(f.ReadString(szTmp.Left(szTmp.GetLength() - 1)))
		f.Close();
	}// ���� if(bRet)

	return bRet;
}

/*!
\brief   Save Config to the file.
\param   LPCTSTR lpszFile��the config file name
\return  ����Ϊ BOOL ��If success, return TRUE, otherwise,return FALSE.
\version 1.0
\author  ��  ��
\date    2007-5-22 14:31:42
*/
BOOL CRegisterFilterControl::SaveConfig(LPCTSTR lpszFile)
{
	BOOL bRet = TRUE;
	char * pBuf = NULL;
	char * pNew = NULL;
	int nPos = 0;
	DWORD nLen = MAX_PATH;
	DWORD dwErr = 0;
	char Buffer[MAX_PATH];
	CString szFile;
	CFileEx f;
	
	ASSERT(lpszFile);
	szFile = lpszFile;

	bRet = f.Open(szFile, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS);
	if(bRet)
	{
		while(bRet)
		{
			pBuf = Buffer;
			nLen = MAX_PATH;
			bRet = DeviceIoControl(REGFILTER_GET_POSITION_CONTENT, &nPos, sizeof(nPos), pBuf, nLen, &nLen, NULL);
			if(!bRet)
			{
				dwErr = GetLastError();
				if(dwErr == ERROR_MORE_DATA || nLen >= MAX_PATH - sizeof(WCHAR))
				{
					pNew = new char[nLen + sizeof(WCHAR)];
					if(NULL == pNew)
					{
						f.Close();
						return FALSE;
					}// ���� if(NULL == pBuf)
					pBuf = pNew;
					bRet = DeviceIoControl(REGFILTER_GET_POSITION_CONTENT, &nPos, sizeof(nPos), pBuf, nLen, &nLen, NULL);
				}// ���� (m_szConfigFileName)
			} // ���� if(!bRet)
			if(bRet)
			{
				memset(pBuf + nLen, 0, sizeof(WCHAR));
				f.WriteString((PWCHAR)pBuf);
				f.WriteString(_T("\r\n"));
			}// ���� if(bRet)
			if(NULL != pNew)
			{
				delete []pNew;
				pNew = NULL;
			}// ���� if(NULL != pNew)

			nPos++;
		}// ���� while(bRet)

		f.Close();
	}

	return TRUE;
}