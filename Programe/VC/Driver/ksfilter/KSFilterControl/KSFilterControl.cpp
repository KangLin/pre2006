/*!
\warning 版权所有 (C) 2007 康林工作室；保留所有权利。
\file    KSFilterControl.cpp
\brief   用于控制 KSFilter 设备的库
\version 1.0
\author  康  林 (kl222@126.com)
\date    2007年5月13日  17:57:04
\par     编译器:  
		 Microsoft Visual Studio 8.0 —— C/C++ 8.0
\note
         \li 1、如果调用默认构造函数 CKSFilterControl() ,则一定要执行下面调用：
				 接着调用 SetConfigName() 设置要保护的文件的配置文件名。\n
			     调用 LoadConfig() 从配置文件中加载要保护的文件名。\n
		 \li 2、CKSFilterControl(pszFile)\n
		 \li 3、退出时，调用SaveConfig()把驱动中的保护的文件名保存到配置文件中去。这一步在类的析构函数中
*/

#include "stdafx.h"
#include <Windows.h>
#include <winioctl.h>
#include "..\ksfilter\ksfilter.h"
#include "KSFilterControl.h"
#include <AtlBase.h>
#include <AtlConv.h>
#include "..\..\..\System\File\FileEx.h"

#ifndef ASSERT
#define ASSERT _ASSERT
#endif

CKSFilterControl::CKSFilterControl()
{
	SetServiceName(_T("KSFilter"));
	SetDeviceName(_T("KSFilter"));
}

CKSFilterControl::~CKSFilterControl()
{
}

/*!
\brief   设置要保护的文件。
\param   LPCTSTR szFile：文件名。
\return  类型为 BOOL 。成功返回 TRUE，失败返回 FALSE。
\version 1.0
\author  康  林
\date    2007-5-13 18:46:37
*/
BOOL CKSFilterControl::SetProtectFile(LPCTSTR szFile)
{
	USES_CONVERSION;
	ASSERT(szFile);
	if(NULL == szFile)
	{
		return FALSE;
	} // 结束 if(NULL == szFile)
	BOOL bRet = TRUE;
	int nLen = (_tcslen(szFile) + 1) * sizeof(TCHAR);
	LPTSTR p = new TCHAR[nLen];
	if(NULL == p)
	{
		return FALSE;
	} // 结束 if(NULL == p)
	memcpy(p, (PVOID)szFile, nLen);
	LPWSTR pszFile = T2W(p);
	pszFile = _tcsupr(pszFile);
	bRet = DeviceIoControl(FSCTL_SET_PROTECT_FILE, pszFile, (wcslen(pszFile) + 1) * sizeof(WCHAR), NULL, 0);
	delete []p;
	return bRet;
}

/*!
\brief   删除要保护的文件
\param   LPCTSTR szFile：要删除的文件
\return  类型为 BOOL 。成功返回0,否则返回非零
\version 1.0
\author  康  林
\date    2007-5-15 14:19:42
*/
BOOL CKSFilterControl::RemoveProtectFile(LPCTSTR szFile)
{
	USES_CONVERSION;
	ASSERT(szFile);
	if(NULL == szFile)
	{
		return FALSE;
	} // 结束 if(NULL == szFile)
	BOOL bRet = TRUE;
	int nLen = (_tcslen(szFile) + 1)*sizeof(TCHAR);
	LPTSTR p = new TCHAR[nLen];
	if(NULL == p)
	{
		return FALSE;
	} // 结束 if(NULL == p)
	memcpy(p, (PVOID)szFile, nLen);
	LPWSTR pszFile = T2W(p);
	pszFile = _tcsupr(pszFile);
	bRet = DeviceIoControl(FSCTL_REMOVE_PROTECT_FILE, pszFile, (wcslen(pszFile) + 1) * sizeof(WCHAR), NULL, 0);
	delete []p;
	return bRet;
}

/*!
\brief   Load Config from the file
\param   LPCTSTR lpszFile：the config file name
\return  类型为 BOOL 。If success, return TRUE, otherwise,return FALSE.
\version 1.0
\author  康  林
\date    2007-5-22 14:31:49
*/
BOOL CKSFilterControl::LoadConfig(LPCTSTR lpszFile)
{
	BOOL bRet = TRUE;
	BOOL bRemove = FALSE;
	CString szTmp, szFile;
	CFileEx f;

	ASSERT(lpszFile);
	szFile = lpszFile;
	bRemove = RemoveProtectFile(szFile);
	bRet = f.Open(szFile);
	if(bRet)
	{
		while(f.ReadString(szTmp))
		{
			bRet = SetProtectFile(szTmp.Left(szTmp.GetLength() - 1));
		}// 结束 while(f.ReadString(szTmp.Left(szTmp.GetLength() - 1)))
		f.Close();
	}// 结束 if(bRet)
	if(bRemove)
	{
		SetProtectFile(szFile);
	} // 结束 if(bRemove)
	return bRet;
}

/*!
\brief   Save Config to the file.
\param   LPCTSTR lpszFile：the config file name
\return  类型为 BOOL 。If success, return TRUE, otherwise,return FALSE.
\version 1.0
\author  康  林
\date    2007-5-22 14:31:42
*/
BOOL CKSFilterControl::SaveConfig(LPCTSTR lpszFile)
{
	BOOL bRet = TRUE;
	BOOL bRemove = FALSE;
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

	bRemove = RemoveProtectFile(szFile);

	bRet = f.Open(szFile, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS);
	if(bRet)
	{
		while(bRet)
		{
			pBuf = Buffer;
			nLen = MAX_PATH;
			bRet = DeviceIoControl(FSCTL_GET_POSITION_FILE, &nPos, sizeof(nPos), pBuf, nLen, &nLen, NULL);
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
					}// 结束 if(NULL == pBuf)
					pBuf = pNew;
					bRet = DeviceIoControl(FSCTL_GET_POSITION_FILE, &nPos, sizeof(nPos), pBuf, nLen, &nLen, NULL);
				}// 结束 (m_szConfigFileName)
			} // 结束 if(!bRet)
			if(bRet)
			{
				memset(pBuf + nLen, 0, sizeof(WCHAR));
				f.WriteString((PWCHAR)pBuf);
				f.WriteString(_T("\r\n"));
			}// 结束 if(bRet)
			if(NULL != pNew)
			{
				delete []pNew;
				pNew = NULL;
			}// 结束 if(NULL != pNew)

			nPos++;
		}// 结束 while(bRet)

		if(bRemove)
		{
			f.WriteString(szFile);
			f.WriteString(_T("\r\n"));
		}// 结束 (szFile)

		f.Close();
	}

	if(bRemove)
	{
		SetProtectFile(szFile);
	}// 结束 if(bRemove)

	return TRUE;
}