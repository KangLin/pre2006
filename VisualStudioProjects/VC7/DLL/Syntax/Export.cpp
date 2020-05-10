/*******************************************************************************************************
��Ȩ���� (C) 2005 ���ֹ����ң���������Ȩ����
�ļ�����Export.cpp
��  ����DLL�ĵ�������
�����б�
		 ShowHelp            ����ʾָ���İ����ļ�
		 ShowVersion         ����ʾ�汾��Ϣ
		 GetDLLPath          ���õ��� DLL ��·��
         MatchSplitSymbol    ;ƥ��ָ���ķ��Ŷ�
         PathRelativePath    ;ת·��Ϊ���·��
��  ����2005.6.0.1
��  �ߣ���  ��
E_Mail��kl222@126.com
��  �ڣ�2005��7��28��
ʱ  �䣺11:16:57
��������Microsoft Development Environment 7.10 ���� C/C++ 7.10
*******************************************************************************************************/
#include "stdafx.h"
#include "export.h"
#include "..\..\..\..\Programe\VC\File\FileEx.h"
#include <direct.h>

/*******************************************************************************************************
��������ShowHelp
��  ������ʾָ���İ����ļ�
��  ����
        LPCTSTR szhelpFile�������ļ���
����ֵ���ɹ����� TRUE�����򷵻� FALSE��
��  ����2005.6.0.1
��  �ߣ���  ��
ʱ  �䣺2005��7��6�� 13:36:47
*******************************************************************************************************/
extern "C" BOOL WINAPI ShowHelp()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CFileEx fe;
	CString szFile;
	fe.GetFilePath(szFile);
	szFile += _T("\\΢����������չ���߼��û��ֲ�.chm");
	::HtmlHelp(NULL, szFile, HH_DISPLAY_TOPIC, NULL);
    return TRUE;
}

/*******************************************************************************************************
��������ShowVersion
��  ������ʾ�汾��Ϣ
��  ������
����ֵ��
��  ����2005.6.0.1
��  �ߣ���  ��
ʱ  �䣺2005��7��6�� 17:58:33
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
��������GetDLLPath
��  �����õ��� DLL ��·��
��  ����
        LPTSTR pszPath��DLL ��·��
����ֵ��·���ĳ���
��  ����2005.6.0.1
��  �ߣ���  ��
ʱ  �䣺2005��7��6�� 13:35:58
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
��������PathRelativePath
��  �����õ����·��
��  ����
        LPTSTR pszPath  ��
		LPCTSTR pszFrom ��
		DWORD dwAttrFrom��
		LPCTSTR pszTo   ��
		DWORD dwAttrTo  ��
����ֵ��
��  ����2005.6.0.1
��  �ߣ���  ��
ʱ  �䣺2005��7��6�� 13:35:36
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
��������FullPath
��  �����õ�����·��
��  ����
        LPTSTR lpszPathOut ������·��
		LPCTSTR lpszFileIn �����·��
		LPCTSTR lpszCurPath����ǰ�ĵ���·��
����ֵ��LONG��·�����ȡ�
��  ����2005.6.0.1
��  �ߣ���  ��
ʱ  �䣺2005��1��19�� 18:47:21
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