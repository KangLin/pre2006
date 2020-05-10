/*!
\warning ��Ȩ���� (C) 2007 ���ֹ����ң���������Ȩ����
\file    KSFilterControl.cpp
\brief   ���ڿ��� KSFilter �豸�Ŀ�
\version 1.0
\author  ��  �� (kl222@126.com)
\date    2007��5��13��  17:57:04
\par     ������:  
		 Microsoft Visual Studio 8.0 ���� C/C++ 8.0
\note
         \li 1���������Ĭ�Ϲ��캯�� CKSFilterControl() ,��һ��Ҫִ��������ã�
				 ���ŵ��� SetConfigName() ����Ҫ�������ļ��������ļ�����\n
			     ���� LoadConfig() �������ļ��м���Ҫ�������ļ�����\n
		 \li 2��CKSFilterControl(pszFile)\n
		 \li 3���˳�ʱ������SaveConfig()�������еı������ļ������浽�����ļ���ȥ����һ�����������������
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
\brief   ����Ҫ�������ļ���
\param   LPCTSTR szFile���ļ�����
\return  ����Ϊ BOOL ���ɹ����� TRUE��ʧ�ܷ��� FALSE��
\version 1.0
\author  ��  ��
\date    2007-5-13 18:46:37
*/
BOOL CKSFilterControl::SetProtectFile(LPCTSTR szFile)
{
	USES_CONVERSION;
	ASSERT(szFile);
	if(NULL == szFile)
	{
		return FALSE;
	} // ���� if(NULL == szFile)
	BOOL bRet = TRUE;
	int nLen = (_tcslen(szFile) + 1) * sizeof(TCHAR);
	LPTSTR p = new TCHAR[nLen];
	if(NULL == p)
	{
		return FALSE;
	} // ���� if(NULL == p)
	memcpy(p, (PVOID)szFile, nLen);
	LPWSTR pszFile = T2W(p);
	pszFile = _tcsupr(pszFile);
	bRet = DeviceIoControl(FSCTL_SET_PROTECT_FILE, pszFile, (wcslen(pszFile) + 1) * sizeof(WCHAR), NULL, 0);
	delete []p;
	return bRet;
}

/*!
\brief   ɾ��Ҫ�������ļ�
\param   LPCTSTR szFile��Ҫɾ�����ļ�
\return  ����Ϊ BOOL ���ɹ�����0,���򷵻ط���
\version 1.0
\author  ��  ��
\date    2007-5-15 14:19:42
*/
BOOL CKSFilterControl::RemoveProtectFile(LPCTSTR szFile)
{
	USES_CONVERSION;
	ASSERT(szFile);
	if(NULL == szFile)
	{
		return FALSE;
	} // ���� if(NULL == szFile)
	BOOL bRet = TRUE;
	int nLen = (_tcslen(szFile) + 1)*sizeof(TCHAR);
	LPTSTR p = new TCHAR[nLen];
	if(NULL == p)
	{
		return FALSE;
	} // ���� if(NULL == p)
	memcpy(p, (PVOID)szFile, nLen);
	LPWSTR pszFile = T2W(p);
	pszFile = _tcsupr(pszFile);
	bRet = DeviceIoControl(FSCTL_REMOVE_PROTECT_FILE, pszFile, (wcslen(pszFile) + 1) * sizeof(WCHAR), NULL, 0);
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
		}// ���� while(f.ReadString(szTmp.Left(szTmp.GetLength() - 1)))
		f.Close();
	}// ���� if(bRet)
	if(bRemove)
	{
		SetProtectFile(szFile);
	} // ���� if(bRemove)
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
					}// ���� if(NULL == pBuf)
					pBuf = pNew;
					bRet = DeviceIoControl(FSCTL_GET_POSITION_FILE, &nPos, sizeof(nPos), pBuf, nLen, &nLen, NULL);
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

		if(bRemove)
		{
			f.WriteString(szFile);
			f.WriteString(_T("\r\n"));
		}// ���� (szFile)

		f.Close();
	}

	if(bRemove)
	{
		SetProtectFile(szFile);
	}// ���� if(bRemove)

	return TRUE;
}