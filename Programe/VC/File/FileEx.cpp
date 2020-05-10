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

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFileEx::CFileEx()
{
    GetModuleFileName();
}


CFileEx::CFileEx(LPCTSTR pszFileName)
{
	SetFile(pszFileName);
}

CFileEx::~CFileEx()
{

}

/*******************************************************************************************************
函数名：SetFile
描  述：设置文件
参  数：
        LPCTSTR pszFileName：文件名
返回值：类型为 INT 。成功返回文件名的长度,失败返回0.
版  本：1.0.0.1
作  者：康  林
时  间：2006年9月7日 16:36:47
*******************************************************************************************************/
INT CFileEx::SetFile(LPCTSTR pszFileName)
{
	ASSERT(pszFileName);

	m_szFileName = pszFileName;
	m_szFileName.Replace(_T('/'), _T('\\'));

	return m_szFileName.GetLength();
}

/*******************************************************************************************************
函数名：GetModuleFileName
功  能：得到当前执行文件的文件名.
参  数：
         LPSTR szFileName：文件名
         INT iFileLen：文件名的长度
返回值：成功返回文件名的长度,失败返回0.
作  者：康  林
版  本：1.0.0.1
日  期：2004-11-11
时  间：18:05:37
*******************************************************************************************************/
INT CFileEx::GetModuleFileName(LPTSTR szFileName, INT iFileLen)
{
	ASSERT(szFileName != NULL && iFileLen != 0);

	int iLen = ::GetModuleFileName(::AfxGetInstanceHandle(), szFileName, iFileLen);
	if(!iLen)
	{
		TRACE(_T("得到当前执行文件名错误.\n"));
        return 0;
	}
	
	m_szFileName = szFileName;
	
	return iLen;
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

    int iLen = ::GetModuleFileName(::AfxGetInstanceHandle(), szFileName, MAX_PATH);
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
INT CFileEx::GetFilePath(LPTSTR szFilePath, INT iLength)
{
	ASSERT(szFilePath != NULL && 0 != iLength && !m_szFileName.IsEmpty());
	int i = m_szFileName.ReverseFind(_T('\\'));
	_tcscpy(szFilePath, m_szFileName.Left(i));
    return i;

    TCHAR drive [_MAX_DRIVE];
    TCHAR dir[_MAX_DIR];
    TCHAR fname [_MAX_FNAME];
    TCHAR ext[_MAX_EXT];
    _tsplitpath(m_szFileName, drive, dir, fname, ext);
    _tcscpy(szFilePath, drive);
    _tcscat(szFilePath, dir);
    return _tcslen(szFilePath);
}

/*******************************************************************************************************
函数名：GetFilePath
功  能：得到文件的路径
参  数：
         CString& szFilePath：得到文件的路径
返回值：得到文件的路径的长度
版  本：1.0.0.1
作  者：康  林
时  间：2005-5-14 10:50:50
*******************************************************************************************************/
INT CFileEx::GetFilePath(CString& szFilePath)
{
    TCHAR szPath[MAX_PATH];
    INT iR;
    iR = GetFilePath(szPath, MAX_PATH);
    if(iR > 0)
    {
        szFilePath = szPath;
    }
    return iR;
}

CString CFileEx::GetFilePath()
{
    CString szPath;
    GetFilePath(szPath);
    return szPath;
}

/*******************************************************************************************************
函数名：GetFileTitle
功  能：得到文件标题（不包括扩展名）
参  数：
         LPTSTR szFileTitle：得到文件标题（不包括扩展名）
         INT iFileLen：缓冲区的长度
返回值：得到文件标题（不包括扩展名）的长度
版  本：1.0.0.1
作  者：康  林
时  间：2005-5-14 10:50:30
*******************************************************************************************************/
INT CFileEx::GetFileTitle(LPTSTR szFileTitle, INT iFileLen)
{
	ASSERT(szFileTitle != NULL && iFileLen != 0 && !m_szFileName.IsEmpty());
	/*int i = m_szFileName.ReverseFind(_T('\\'));
	_tcscpy(szFileTitle, m_szFileName.Right(m_szFileName.GetLength() - i - 1));
	return i;*/
    TCHAR drive [_MAX_DRIVE];
    TCHAR dir[_MAX_DIR];
    TCHAR fname [_MAX_FNAME];
    TCHAR ext[_MAX_EXT];
    _tsplitpath(m_szFileName, drive, dir, fname, ext);
    _tcscpy(szFileTitle, fname);
    return _tcslen(szFileTitle);
}

/*******************************************************************************************************
函数名：GetFileTitle
功  能：得到文件标题（不包括扩展名）
参  数：
         CString& szFileTitle：得到文件标题（不包括扩展名）
返回值：得到文件标题（不包括扩展名）的长度
版  本：1.0.0.1
作  者：康  林
时  间：2005-5-14 10:50:04
*******************************************************************************************************/
INT CFileEx::GetFileTitle(CString& szFileTitle)
{
    TCHAR szTitle[MAX_PATH];
    INT iR;
    iR = GetFileTitle(szTitle, MAX_PATH);
    if(iR > 0)
    {
        szFileTitle = szTitle;
    }
    return iR;
}

CString CFileEx::GetFileTitle()
{
    CString szTitle;
    GetFileTitle(szTitle);
    return szTitle;
}

/*******************************************************************************************************
函数名：GetFileExt
功  能：返回扩展名（包括.)
参  数：
         LPTSTR szFileExt：返回扩展名（包括.)
         INT iFileLen：缓冲区的长度，默认为MAX_PATH
返回值：扩展名的长度
版  本：1.0.0.1
作  者：康  林
时  间：2005-5-14 10:48:10
*******************************************************************************************************/
INT CFileEx::GetFileExt(LPTSTR szFileExt, INT iFileLen)
{
    ASSERT(szFileExt != NULL && iFileLen != 0 && !m_szFileName.IsEmpty());
	/*int i = m_szFileName.ReverseFind(_T('\\'));
	_tcscpy(szFileTitle, m_szFileName.Right(m_szFileName.GetLength() - i - 1));
	return i;*/
    TCHAR drive [_MAX_DRIVE];
    TCHAR dir[_MAX_DIR];
    TCHAR fname [_MAX_FNAME];
    TCHAR ext[_MAX_EXT];
    _tsplitpath(m_szFileName, drive, dir, fname, ext);
    _tcscpy(szFileExt, ext);
    return _tcslen(szFileExt);
}

/*******************************************************************************************************
函数名：GetFileExt
功  能：返回扩展名（包括.)
参  数：
         CString& szFileExt：返回扩展名（包括.)
返回值：扩展名的长度
版  本：1.0.0.1
作  者：康  林
时  间：2005-5-14 10:47:31
*******************************************************************************************************/
INT CFileEx::GetFileExt(CString& szFileExt)
{
    TCHAR szExt[MAX_PATH];
    INT iR;
    iR = GetFileExt(szExt, MAX_PATH);
    if(iR > 0)
    {
        szFileExt = szExt;
    }
    return iR;
}

CString CFileEx::GetFileExt()
{
    CString szExt;
    GetFileExt(szExt);
    return szExt;
}

/*******************************************************************************************************
函数名：GetFileName
功  能：得到文件名（包括扩展名）
参  数：
         LPTSTR szFileName：得到文件名（包括扩展名）
         INT iFileLen：缓冲区的长度
返回值：得到文件名（包括扩展名）的长度
版  本：1.0.0.1
作  者：康  林
时  间：2005-5-14 10:49:04
*******************************************************************************************************/
INT CFileEx::GetFileName(LPTSTR szFileName, INT iFileLen)
{
    ASSERT(szFileName != NULL && iFileLen != 0 && !m_szFileName.IsEmpty());
	int i = m_szFileName.ReverseFind(_T('\\'));
	_tcscpy(szFileName, m_szFileName.Right(m_szFileName.GetLength() - i - 1));
	return i;
}

/*******************************************************************************************************
函数名：GetFileName
功  能：得到文件名（包括扩展名）
参  数：
         CString& szFileName：得到文件名（包括扩展名）
返回值：得到文件名（包括扩展名）的长度
版  本：1.0.0.1
作  者：康  林
时  间：2005-5-14 10:49:41
*******************************************************************************************************/
INT CFileEx::GetFileName(CString& szFileName)
{
    TCHAR szName[MAX_PATH];
    INT iR;
    iR = GetFileName(szName, MAX_PATH);
    if(iR > 0)
    {
        szFileName = szName;
    }
    return iR;
}

CString CFileEx::GetFileName()
{
    CString szFileName;
    GetFileName(szFileName);
    return szFileName;
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
