/*******************************************************************************************************
版权所有 (C) 2005 康林工作室；保留所有权利。
文件名：Export.cpp
描  述：DLL的导出函数
函数列表：
		 ShowHelp            ：显示指定的帮助文件
		 ShowVersion         ：显示版本信息
		 GetDLLPath          ：得到此 DLL 的路径
         MatchSplitSymbol    ;匹配指定的符号对
         PathRelativePath    ;转路径为相对路径
版  本：2005.6.0.1
作  者：康  林
E_Mail：kl222@126.com
日  期：2005年7月28日
时  间：11:16:57
编译器：Microsoft Development Environment 7.10 —— C/C++ 7.10
*******************************************************************************************************/
#include "stdafx.h"
#include "export.h"
#include "..\..\..\..\Programe\VC\File\FileEx.h"
#include <direct.h>

/*******************************************************************************************************
函数名：ShowHelp
描  述：显示指定的帮助文件
参  数：
        LPCTSTR szhelpFile：帮助文件名
返回值：成功返回 TRUE，否则返回 FALSE。
版  本：2005.6.0.1
作  者：康  林
时  间：2005年7月6日 13:36:47
*******************************************************************************************************/
extern "C" BOOL WINAPI ShowHelp()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CFileEx fe;
	CString szFile;
	fe.GetFilePath(szFile);
	szFile += _T("\\微软开发环境扩展工具集用户手册.chm");
	::HtmlHelp(NULL, szFile, HH_DISPLAY_TOPIC, NULL);
    return TRUE;
}

/*******************************************************************************************************
函数名：ShowVersion
描  述：显示版本信息
参  数：无
返回值：
版  本：2005.6.0.1
作  者：康  林
时  间：2005年7月6日 17:58:33
*******************************************************************************************************/
extern "C" BOOL WINAPI ShowVersion()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CFileEx fe;
	CString szFile;
	fe.GetFilePath(szFile);
	szFile += _T("\\version.exe");
	WinExec(szFile, SW_SHOWNORMAL);
	return TRUE;
}

/*******************************************************************************************************
函数名：GetDLLPath
描  述：得到此 DLL 的路径
参  数：
        LPTSTR pszPath：DLL 的路径
返回值：路径的长度
版  本：2005.6.0.1
作  者：康  林
时  间：2005年7月6日 13:35:58
*******************************************************************************************************/
extern "C" LONG GetDLLPath(BSTR* lpszPath)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    CFileEx fe;
    CString szPath = fe.GetFilePath();
	::SysFreeString(*lpszPath);
	*lpszPath = szPath.AllocSysString();
	return ::SysStringByteLen(*lpszPath);
}

/*******************************************************************************************************
函数名：PathRelativePath
描  述：得到相对路径
参  数：
        LPTSTR pszPath  ：
		LPCTSTR pszFrom ：
		DWORD dwAttrFrom：
		LPCTSTR pszTo   ：
		DWORD dwAttrTo  ：
返回值：
版  本：2005.6.0.1
作  者：康  林
时  间：2005年7月6日 13:35:36
*******************************************************************************************************/
extern "C" LONG PathRelativePath(BSTR* pszPath,
                                 BSTR pszFrom,
                                 DWORD dwAttrFrom,
                                 BSTR pszTo,
                                 DWORD dwAttrTo
                                 )
{
	LPTSTR lpOut = new TCHAR[MAX_PATH];
	if(!lpOut)
	{
		return 0;
	}
    USES_CONVERSION;
	::PathRelativePathTo(lpOut, W2T(pszFrom), dwAttrFrom, W2T(pszTo), dwAttrTo);
    ::SysFreeString(*pszPath);	
	*pszPath = T2BSTR(lpOut);
	delete []lpOut;
	return ::SysStringByteLen(*pszPath);
}

/*******************************************************************************************************
函数名：FullPath
描  述：得到绝对路径
参  数：
        LPTSTR lpszPathOut ：绝对路径
		LPCTSTR lpszFileIn ：相对路径
		LPCTSTR lpszCurPath：当前文档的路径
返回值：LONG：路径长度。
版  本：2005.6.0.1
作  者：康  林
时  间：2005年1月19日 18:47:21
*******************************************************************************************************/
extern "C" LONG FullPath(LPTSTR lpszPathOut, LPCTSTR lpszFileIn, LPCTSTR lpszCurPath)
{
	TCHAR szCur[MAX_PATH];
	_tgetcwd(szCur, MAX_PATH);
	TCHAR szCurPath[MAX_PATH];
	CFileEx fe(lpszCurPath);
	fe.GetFilePath(szCurPath, MAX_PATH);
	_tchdir(szCurPath);
	if(::_tfullpath(lpszPathOut, lpszFileIn, MAX_PATH))
	{
		_tchdir(szCur);
		return _tcslen(lpszPathOut);
	}
	else
	{
		_tcscpy(lpszPathOut, lpszFileIn);
		_tchdir(szCur);
		return _tcslen(lpszPathOut);
	}
	_tchdir(szCur);
	return 0;
}