/*******************************************************************************************************
�ļ�����FileEx.cpp
��  �ܣ���չ�ļ���
��������Visual C++ 6.0
��  �ߣ���  ��
        ��Ȩ����  ��������Ȩ��
��  ����1.0.0.1
��  �ڣ�2004-11-11
ʱ  �䣺19:01:52
*******************************************************************************************************/

#include "stdafx.h"
#include "FileEx.h"
#include "Shlwapi.h"

#pragma comment(lib, "shlwapi")

#ifndef ASSERT
#define ASSERT _ASSERT
#endif

#ifndef TRACE
#define TRACE _tprintf
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFileEx::CFileEx()
{
	GetModuleFileName();
	m_hFile = INVALID_HANDLE_VALUE;
}

CFileEx::CFileEx(LPCTSTR pszFile)
{
	_ASSERT(pszFile);
	m_szFileName = pszFile;
	Close();
}

CFileEx::~CFileEx()
{

}

/*******************************************************************************************************
��������GetModuleFileName
��  �����õ���ǰִ���ļ����ļ���.
��  ������
����ֵ���ɹ������ļ����ĳ���,ʧ�ܷ���0.
��  ����1.0
��  �ߣ���  ��
ʱ  �䣺2005-6-13 13:39:15
*******************************************************************************************************/
INT CFileEx::GetModuleFileName()
{
    TCHAR szFileName[MAX_PATH];

	int iLen = ::GetModuleFileName(NULL, szFileName, MAX_PATH);
	if(!iLen)
	{
		TRACE(_T("�õ���ǰִ���ļ�������.\n"));
        return 0;
	}
	
	m_szFileName = szFileName;
	
	return iLen;
}

/*******************************************************************************************************
��������GetFilePath
��  �ܣ��õ��ļ���·��
��  ����
         LPSTR szFilePath���ļ���·��
         INT iLength���ļ���·������������
����ֵ���ɹ������ļ���·���ĳ���,���򷵻�0
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-11-11
ʱ  �䣺18:28:47
*******************************************************************************************************/
INT CFileEx::GetFilePath(const TCHAR * lpFullFileName, TCHAR * lpPath)
{
	int nRet = 0;
	if(lpFullFileName == NULL || lpPath == NULL)
	{
		_ASSERT(0);
		return 1;
	}// ���� if(lpFullFileName == NULL || lpPath == NULL)
	TCHAR * p = new TCHAR[_tcslen(lpFullFileName) + sizeof(TCHAR)];
	if(p == NULL)
	{
		return 2;
	} // ���� if(p == NULL)
	_tcscpy(p, lpFullFileName);
	TCHAR * pp = _tcsrev(p);
	pp = _tcsstr(pp, _T("\\"));
	if(pp == NULL)
	{
		delete []p;
		return 3;
	}// ���� if(pp == NULL)
	_tcscpy(lpPath, pp + 1);
	_tcsrev(lpPath);
	delete []p;
	return nRet;
}

_tstring CFileEx::GetFilePath()
{
	TCHAR szFileName[MAX_PATH];
	_tstring szName = _T("");
	if(!GetFilePath(m_szFileName.c_str(), szFileName))
	{
		szName = szFileName;
	}// ���� if(!GetFilePath(m_szFileName.c_str(), szFileName))
	return szName;
}

/*******************************************************************************************************
��������GetFileName
��  ����
��  ����
const TCHAR * lpFullFileName���ļ���
TCHAR * lpFile              ��·��
����ֵ������Ϊ int ��
��  ����1.0
��  �ߣ���  ��
ʱ  �䣺2007��4��23�� 14:50:09
*******************************************************************************************************/
int CFileEx::GetFileName(const TCHAR * lpFullFileName, TCHAR * lpFile)
{
	int nRet = 0;
	if(lpFile == NULL || lpFullFileName == NULL)
	{
		_ASSERT(0);
		return 1;
	}// ���� if(lpFile == NULL || lpFullFileName == NULL)
	TCHAR * p = new TCHAR[_tcslen(lpFullFileName) + sizeof(TCHAR)];
	if(p == NULL)
	{
		return 2;
	} // ���� if(p == NULL)
	_tcscpy(p, lpFullFileName);
	TCHAR * pp = _tcsrev(p);
	pp = _tcsstr(pp, _T("\\"));
	if(pp == NULL)
	{
		delete []p;
		return 3;
	}// ���� if(pp == NULL)
	nRet = pp - p;
	_tcsncpy(lpFile, p, nRet);
	*(lpFile + nRet) = 0;
	_tcsrev(lpFile);
	nRet = 0;
	delete []p;
	return nRet;
}

_tstring CFileEx::GetFileName()
{
	TCHAR szFileName[MAX_PATH];
	_tstring szName = _T("");
	if(!GetFileName(m_szFileName.c_str(), szFileName))
	{
		szName = szFileName;
	}// ���� if(!GetFileName(m_szFileName.c_str(), szFileName))
	return szName;
}

INT CFileEx::GetFileExt(LPCTSTR lpFullFileName, TCHAR * lpFileExt)
{
	INT nRet = 0;
	if(NULL == lpFullFileName || NULL == lpFileExt)
	{
		_ASSERT(0);
		return 1;
	} // ���� if(NULL == lpFullFileName || NULL == lpFileExt)
	TCHAR * p = new TCHAR[_tcslen(lpFullFileName) + sizeof(TCHAR)];
	if(p == NULL)
	{
		return 2;
	} // ���� if(p == NULL)

	nRet = GetFileName(lpFullFileName, p);
	if(0 == nRet)
	{
		TCHAR * pp = _tcsrev(p);
		pp = _tcsstr(pp, _T("."));
		if(pp == NULL)
		{
			delete []p;
			return 3;
		}// ���� if(pp == NULL)
		nRet = pp - p;
		_tcsncpy(lpFileExt, p, nRet);
		*(lpFileExt + nRet) = 0;
		_tcsrev(lpFileExt);
		nRet = 0;
	}// ���� if(0 == nRet)

	delete []p;

	return nRet;
}

_tstring CFileEx::GetFileExt()
{
	TCHAR szFileName[MAX_PATH];
	_tstring szName = _T("");
	if(!GetFileExt(m_szFileName.c_str(), szFileName))
	{
		szName = szFileName;
	}// ���� if(!GetFileExt(m_szFileName.c_str(), szFileName))
	return szName;
}

INT CFileEx::GetFileTitle(LPCTSTR lpFullFileName, TCHAR * lpTitle)
{
	INT nRet = 0;
	if(NULL == lpFullFileName || NULL == lpTitle)
	{
		_ASSERT(0);
		return 1;
	} // ���� if(NULL == lpFullFileName || NULL == lpTitle)
	TCHAR * p = new TCHAR[_tcslen(lpFullFileName) + sizeof(TCHAR)];
	if(p == NULL)
	{
		return 2;
	} // ���� if(p == NULL)

	nRet = GetFileName(lpFullFileName, p);
	if(0 == nRet)
	{
		TCHAR * pp = _tcsstr(p, _T("."));
		if(pp == NULL)
		{
			_tcscpy(lpTitle, p); 
		}
		else
		{
			nRet = pp - p;
			_tcsncpy(lpTitle, p, nRet);
			*(lpTitle + nRet) = 0;
			nRet = 0;
		} // ���� if(pp == NULL)
	}// ���� if(0 == nRet)
	delete []p;
	return nRet;
}

_tstring CFileEx::GetFileTitle()
{
	TCHAR szFileName[MAX_PATH];
	_tstring szName = _T("");
	if(!GetFileTitle(m_szFileName.c_str(), szFileName))
	{
		szName = szFileName;
	}// ���� if(!GetFileTitle(m_szFileName.c_str(), szFileName))
	return szName;
}

/*******************************************************************************************************
��������GetRelativePath
��  �ܣ��õ����·��
��  ����
         LPTSTR lpszRelativePath�����·��
         LPCTSTR lpcszFrom����ʼ·����Ŀ��·��
         LPCTSTR lpcszTo������·����Ҫת����·��
         DWORD dwAttrFrom����ʼ·�����ԡ�FILE_ATTRIBUTE_DIRECTORY��lpcszFromΪ·��������Ϊ�ļ���
         DWORD dwAttrTo������·�����ԡ�FILE_ATTRIBUTE_DIRECTORY��lpcszToΪ·��������Ϊ�ļ���
����ֵ���ɹ�����TRUE�����򷵻�FALSE��
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005-5-14 9:58:28
*******************************************************************************************************/
BOOL CFileEx::GetRelativePath(LPTSTR lpszRelativePath, LPCTSTR lpcszFrom, LPCTSTR lpcszTo, DWORD dwAttrFrom, DWORD dwAttrTo)
{
    return PathRelativePathTo(lpszRelativePath, lpcszFrom, dwAttrFrom, lpcszTo, dwAttrTo);
}

/*!
\brief   �ݹ�ö��ָ��Ŀ¼�µ��ļ�
\param   LPCTSTR pszPath     ��Ҫ��ѯ��Ŀ¼
\param   OPERATORFILE operate�����ļ��Ĳ����ص�����
\param   BOOL * bExit        ���Ƿ��˳�������
\return  ����Ϊ INT ������Ŀ¼�µ��ļ���
\version 1.0
\author  ��  ��
\date    2007-6-4 23:11:03
*/
INT CFileEx::EnumDirectory(LPCTSTR pszPath, OPERATORFILE operate, BOOL * bExit)
{
	INT nRet = 0;
	WIN32_FIND_DATA ffd;
	HANDLE hFile = NULL;
	_tstring szFile = pszPath;
	if(szFile.at(szFile.size() - 1) != _T('\\'))
	{
		szFile += _T("\\");
	}// ���� if(szFile.at(szFile.size() - 1) != _T('\\'))
	try
	{
		_tstring szTmp = szFile + _T("*");
		hFile = ::FindFirstFile(szTmp.c_str(), &ffd);
		if(hFile != INVALID_HANDLE_VALUE)
		{
			do
			{
				if(FILE_ATTRIBUTE_DIRECTORY == ffd.dwFileAttributes && _T('.') != ffd.cFileName[0])
				{
					szTmp = szFile + ffd.cFileName;
					nRet = EnumDirectory(szTmp.c_str(), operate, bExit);
					if(operate(szTmp.c_str()))
					{
						*bExit = TRUE;
						break;
					}// ���� if(operate(szTmp.c_str()))
				}
				else
				{
					if(FILE_ATTRIBUTE_DIRECTORY != ffd.dwFileAttributes)
					{
						szTmp = szFile + ffd.cFileName;
						nRet++;
						if(operate(szTmp.c_str()))
						{
							*bExit = TRUE;
							break;
						}// ���� if(operate(szTmp.c_str()))
					} // ���� if(FILE_ATTRIBUTE_DIRECTORY != ffd.dwFileAttributes)
				}// ���� if(FILE_ATTRIBUTE_DIRECTORY == ffd.dwFileAttributes && _T('.') != ffd.cFileName[0])
			} while(::FindNextFile(hFile, &ffd) && (*bExit != TRUE)); // ���� while(::FindNextFile(hFile, &ffd) && (*bExit != TRUE))
			::FindClose(hFile);
		}// ���� if(hFile != INVALID_HANDLE_VALUE)

	}
	catch(...)
	{
		if(NULL == hFile)
		{
			::FindClose(hFile);
		}// ���� if(NULL == hFile)
		return nRet;
	}
	return nRet;
}

BOOL CFileEx::Open(LPCTSTR lpFileName,
				   DWORD dwDesiredAccess,
				   DWORD dwShareMode,
				   LPSECURITY_ATTRIBUTES lpSecurityAttributes,
				   DWORD dwCreationDisposition,
				   DWORD dwFlagsAndAttributes,
				   HANDLE hTemplateFile
				   )
{
	if(NULL == lpFileName)
	{
		return FALSE;
	}// ���� if(NULL == lpFileName)

	m_hFile = ::CreateFile(lpFileName,
		dwDesiredAccess,        // open for writing
		dwShareMode,            // do not share
		lpSecurityAttributes,   // default security
		dwCreationDisposition,  // overwrite existing
		dwFlagsAndAttributes,   // asynchronous I/O
		hTemplateFile
		);
	if(INVALID_HANDLE_VALUE == m_hFile)
	{
		return FALSE;
	}// ���� if(INVALID_HANDLE_VALUE == m_hFile)

	return TRUE;
}

BOOL CFileEx::Close()
{
	BOOL bRet = FALSE;
	if(INVALID_HANDLE_VALUE != m_hFile)
	{

		bRet = CloseHandle(m_hFile);
		m_hFile = INVALID_HANDLE_VALUE;
	}// ���� if(INVALID_HANDLE_VALUE != m_hFile)
	return bRet;
}

BOOL CFileEx::WriteString(LPCTSTR lpBuffer)
{
	DWORD dwLen = 0;
	if(NULL == lpBuffer)
	{
		return FALSE;
	} // ���� if(NULL == lpBuffer)
	dwLen = _tcslen(lpBuffer) * sizeof(TCHAR);
	return Write((LPVOID)lpBuffer, dwLen);
}

BOOL CFileEx::Write(LPVOID lpBuffer, DWORD dwLength)
{
	ASSERT(m_hFile != INVALID_HANDLE_VALUE);
	return WriteFile(m_hFile,lpBuffer,dwLength,&dwLength,NULL);
}

BOOL CFileEx::ReadString(CString & szString)
{
	BOOL bRet = FALSE;
	CString szTmp;
	TCHAR ch;
	DWORD nLen = sizeof(TCHAR);
	while(bRet = Read(&ch, &nLen))
	{
		if(_T('\n') == ch)
		{
			szString = szTmp;
			return TRUE;
		}
		szTmp = szTmp + ch;
		if(0 == nLen)
		{
			bRet = FALSE;
			break;
		} // ���� if(0 == nLen)
		nLen = sizeof(TCHAR);
	} // ���� while(bRet = Read(&ch, &nLen))
	return bRet;
}

/*!
\brief   Read File
\param   LPVOID lpBuffer  ��
\param   DWORD * pdwLength�������Ҫ����ֵ�Ƿ�Ϊ0,���Ϊ0��˵���ѵ��ļ���β.
\return  ����Ϊ BOOL ��
\version 1.0
\author  ��  ��
\date    2007-6-7 16:24:54
*/
BOOL CFileEx::Read(LPVOID lpBuffer, DWORD * pdwLength)
{
	ASSERT(m_hFile != INVALID_HANDLE_VALUE);
	return ReadFile(m_hFile, lpBuffer, *pdwLength, pdwLength, NULL);
}
