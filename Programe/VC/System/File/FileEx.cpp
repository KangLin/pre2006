/*******************************************************************************************************
文件名：FileEx.cpp
功  能：扩展文件类
编译器：Visual C++ 6.0
作  者：康  林
        版权所有  保留所有权利
版  本：1.0.0.1
日  期：2004-11-11
时  间：19:01:52
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
函数名：GetModuleFileName
描  述：得到当前执行文件的文件名.
参  数：无
返回值：成功返回文件名的长度,失败返回0.
版  本：1.0
作  者：康  林
时  间：2005-6-13 13:39:15
*******************************************************************************************************/
INT CFileEx::GetModuleFileName()
{
    TCHAR szFileName[MAX_PATH];

	int iLen = ::GetModuleFileName(NULL, szFileName, MAX_PATH);
	if(!iLen)
	{
		TRACE(_T("得到当前执行文件名错误.\n"));
        return 0;
	}
	
	m_szFileName = szFileName;
	
	return iLen;
}

/*******************************************************************************************************
函数名：GetFilePath
功  能：得到文件的路径
参  数：
         LPSTR szFilePath：文件的路径
         INT iLength：文件的路径缓存区长度
返回值：成功返回文件的路径的长度,否则返回0
作  者：康  林
版  本：1.0.0.1
日  期：2004-11-11
时  间：18:28:47
*******************************************************************************************************/
INT CFileEx::GetFilePath(const TCHAR * lpFullFileName, TCHAR * lpPath)
{
	int nRet = 0;
	if(lpFullFileName == NULL || lpPath == NULL)
	{
		_ASSERT(0);
		return 1;
	}// 结束 if(lpFullFileName == NULL || lpPath == NULL)
	TCHAR * p = new TCHAR[_tcslen(lpFullFileName) + sizeof(TCHAR)];
	if(p == NULL)
	{
		return 2;
	} // 结束 if(p == NULL)
	_tcscpy(p, lpFullFileName);
	TCHAR * pp = _tcsrev(p);
	pp = _tcsstr(pp, _T("\\"));
	if(pp == NULL)
	{
		delete []p;
		return 3;
	}// 结束 if(pp == NULL)
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
	}// 结束 if(!GetFilePath(m_szFileName.c_str(), szFileName))
	return szName;
}

/*******************************************************************************************************
函数名：GetFileName
描  述：
参  数：
const TCHAR * lpFullFileName：文件名
TCHAR * lpFile              ：路径
返回值：类型为 int 。
版  本：1.0
作  者：康  林
时  间：2007年4月23日 14:50:09
*******************************************************************************************************/
int CFileEx::GetFileName(const TCHAR * lpFullFileName, TCHAR * lpFile)
{
	int nRet = 0;
	if(lpFile == NULL || lpFullFileName == NULL)
	{
		_ASSERT(0);
		return 1;
	}// 结束 if(lpFile == NULL || lpFullFileName == NULL)
	TCHAR * p = new TCHAR[_tcslen(lpFullFileName) + sizeof(TCHAR)];
	if(p == NULL)
	{
		return 2;
	} // 结束 if(p == NULL)
	_tcscpy(p, lpFullFileName);
	TCHAR * pp = _tcsrev(p);
	pp = _tcsstr(pp, _T("\\"));
	if(pp == NULL)
	{
		delete []p;
		return 3;
	}// 结束 if(pp == NULL)
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
	}// 结束 if(!GetFileName(m_szFileName.c_str(), szFileName))
	return szName;
}

INT CFileEx::GetFileExt(LPCTSTR lpFullFileName, TCHAR * lpFileExt)
{
	INT nRet = 0;
	if(NULL == lpFullFileName || NULL == lpFileExt)
	{
		_ASSERT(0);
		return 1;
	} // 结束 if(NULL == lpFullFileName || NULL == lpFileExt)
	TCHAR * p = new TCHAR[_tcslen(lpFullFileName) + sizeof(TCHAR)];
	if(p == NULL)
	{
		return 2;
	} // 结束 if(p == NULL)

	nRet = GetFileName(lpFullFileName, p);
	if(0 == nRet)
	{
		TCHAR * pp = _tcsrev(p);
		pp = _tcsstr(pp, _T("."));
		if(pp == NULL)
		{
			delete []p;
			return 3;
		}// 结束 if(pp == NULL)
		nRet = pp - p;
		_tcsncpy(lpFileExt, p, nRet);
		*(lpFileExt + nRet) = 0;
		_tcsrev(lpFileExt);
		nRet = 0;
	}// 结束 if(0 == nRet)

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
	}// 结束 if(!GetFileExt(m_szFileName.c_str(), szFileName))
	return szName;
}

INT CFileEx::GetFileTitle(LPCTSTR lpFullFileName, TCHAR * lpTitle)
{
	INT nRet = 0;
	if(NULL == lpFullFileName || NULL == lpTitle)
	{
		_ASSERT(0);
		return 1;
	} // 结束 if(NULL == lpFullFileName || NULL == lpTitle)
	TCHAR * p = new TCHAR[_tcslen(lpFullFileName) + sizeof(TCHAR)];
	if(p == NULL)
	{
		return 2;
	} // 结束 if(p == NULL)

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
		} // 结束 if(pp == NULL)
	}// 结束 if(0 == nRet)
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
	}// 结束 if(!GetFileTitle(m_szFileName.c_str(), szFileName))
	return szName;
}

/*******************************************************************************************************
函数名：GetRelativePath
功  能：得到相对路径
参  数：
         LPTSTR lpszRelativePath：相对路径
         LPCTSTR lpcszFrom：开始路径，目标路径
         LPCTSTR lpcszTo：结束路径，要转换的路径
         DWORD dwAttrFrom：开始路径属性。FILE_ATTRIBUTE_DIRECTORY：lpcszFrom为路径，否则为文件。
         DWORD dwAttrTo：结束路径属性。FILE_ATTRIBUTE_DIRECTORY：lpcszTo为路径，否则为文件。
返回值：成功返回TRUE，否则返回FALSE。
版  本：1.0.0.1
作  者：康  林
时  间：2005-5-14 9:58:28
*******************************************************************************************************/
BOOL CFileEx::GetRelativePath(LPTSTR lpszRelativePath, LPCTSTR lpcszFrom, LPCTSTR lpcszTo, DWORD dwAttrFrom, DWORD dwAttrTo)
{
    return PathRelativePathTo(lpszRelativePath, lpcszFrom, dwAttrFrom, lpcszTo, dwAttrTo);
}

/*!
\brief   递归枚举指定目录下的文件
\param   LPCTSTR pszPath     ：要查询的目录
\param   OPERATORFILE operate：对文件的操作回调函数
\param   BOOL * bExit        ：是否退出本操作
\return  类型为 INT 。返回目录下的文件数
\version 1.0
\author  康  林
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
	}// 结束 if(szFile.at(szFile.size() - 1) != _T('\\'))
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
					}// 结束 if(operate(szTmp.c_str()))
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
						}// 结束 if(operate(szTmp.c_str()))
					} // 结束 if(FILE_ATTRIBUTE_DIRECTORY != ffd.dwFileAttributes)
				}// 结束 if(FILE_ATTRIBUTE_DIRECTORY == ffd.dwFileAttributes && _T('.') != ffd.cFileName[0])
			} while(::FindNextFile(hFile, &ffd) && (*bExit != TRUE)); // 结束 while(::FindNextFile(hFile, &ffd) && (*bExit != TRUE))
			::FindClose(hFile);
		}// 结束 if(hFile != INVALID_HANDLE_VALUE)

	}
	catch(...)
	{
		if(NULL == hFile)
		{
			::FindClose(hFile);
		}// 结束 if(NULL == hFile)
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
	}// 结束 if(NULL == lpFileName)

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
	}// 结束 if(INVALID_HANDLE_VALUE == m_hFile)

	return TRUE;
}

BOOL CFileEx::Close()
{
	BOOL bRet = FALSE;
	if(INVALID_HANDLE_VALUE != m_hFile)
	{

		bRet = CloseHandle(m_hFile);
		m_hFile = INVALID_HANDLE_VALUE;
	}// 结束 if(INVALID_HANDLE_VALUE != m_hFile)
	return bRet;
}

BOOL CFileEx::WriteString(LPCTSTR lpBuffer)
{
	DWORD dwLen = 0;
	if(NULL == lpBuffer)
	{
		return FALSE;
	} // 结束 if(NULL == lpBuffer)
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
		} // 结束 if(0 == nLen)
		nLen = sizeof(TCHAR);
	} // 结束 while(bRet = Read(&ch, &nLen))
	return bRet;
}

/*!
\brief   Read File
\param   LPVOID lpBuffer  ：
\param   DWORD * pdwLength：读完后要检查此值是否为0,如果为0则说明已到文件结尾.
\return  类型为 BOOL 。
\version 1.0
\author  康  林
\date    2007-6-7 16:24:54
*/
BOOL CFileEx::Read(LPVOID lpBuffer, DWORD * pdwLength)
{
	ASSERT(m_hFile != INVALID_HANDLE_VALUE);
	return ReadFile(m_hFile, lpBuffer, *pdwLength, pdwLength, NULL);
}
