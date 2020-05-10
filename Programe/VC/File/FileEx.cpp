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
��������SetFile
��  ���������ļ�
��  ����
        LPCTSTR pszFileName���ļ���
����ֵ������Ϊ INT ���ɹ������ļ����ĳ���,ʧ�ܷ���0.
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2006��9��7�� 16:36:47
*******************************************************************************************************/
INT CFileEx::SetFile(LPCTSTR pszFileName)
{
	ASSERT(pszFileName);

	m_szFileName = pszFileName;
	m_szFileName.Replace(_T('/'), _T('\\'));

	return m_szFileName.GetLength();
}

/*******************************************************************************************************
��������GetModuleFileName
��  �ܣ��õ���ǰִ���ļ����ļ���.
��  ����
         LPSTR szFileName���ļ���
         INT iFileLen���ļ����ĳ���
����ֵ���ɹ������ļ����ĳ���,ʧ�ܷ���0.
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-11-11
ʱ  �䣺18:05:37
*******************************************************************************************************/
INT CFileEx::GetModuleFileName(LPTSTR szFileName, INT iFileLen)
{
	ASSERT(szFileName != NULL && iFileLen != 0);

	int iLen = ::GetModuleFileName(::AfxGetInstanceHandle(), szFileName, iFileLen);
	if(!iLen)
	{
		TRACE(_T("�õ���ǰִ���ļ�������.\n"));
        return 0;
	}
	
	m_szFileName = szFileName;
	
	return iLen;
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

    int iLen = ::GetModuleFileName(::AfxGetInstanceHandle(), szFileName, MAX_PATH);
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
��������GetFilePath
��  �ܣ��õ��ļ���·��
��  ����
         CString& szFilePath���õ��ļ���·��
����ֵ���õ��ļ���·���ĳ���
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005-5-14 10:50:50
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
��������GetFileTitle
��  �ܣ��õ��ļ����⣨��������չ����
��  ����
         LPTSTR szFileTitle���õ��ļ����⣨��������չ����
         INT iFileLen���������ĳ���
����ֵ���õ��ļ����⣨��������չ�����ĳ���
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005-5-14 10:50:30
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
��������GetFileTitle
��  �ܣ��õ��ļ����⣨��������չ����
��  ����
         CString& szFileTitle���õ��ļ����⣨��������չ����
����ֵ���õ��ļ����⣨��������չ�����ĳ���
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005-5-14 10:50:04
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
��������GetFileExt
��  �ܣ�������չ��������.)
��  ����
         LPTSTR szFileExt��������չ��������.)
         INT iFileLen���������ĳ��ȣ�Ĭ��ΪMAX_PATH
����ֵ����չ���ĳ���
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005-5-14 10:48:10
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
��������GetFileExt
��  �ܣ�������չ��������.)
��  ����
         CString& szFileExt��������չ��������.)
����ֵ����չ���ĳ���
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005-5-14 10:47:31
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
��������GetFileName
��  �ܣ��õ��ļ�����������չ����
��  ����
         LPTSTR szFileName���õ��ļ�����������չ����
         INT iFileLen���������ĳ���
����ֵ���õ��ļ�����������չ�����ĳ���
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005-5-14 10:49:04
*******************************************************************************************************/
INT CFileEx::GetFileName(LPTSTR szFileName, INT iFileLen)
{
    ASSERT(szFileName != NULL && iFileLen != 0 && !m_szFileName.IsEmpty());
	int i = m_szFileName.ReverseFind(_T('\\'));
	_tcscpy(szFileName, m_szFileName.Right(m_szFileName.GetLength() - i - 1));
	return i;
}

/*******************************************************************************************************
��������GetFileName
��  �ܣ��õ��ļ�����������չ����
��  ����
         CString& szFileName���õ��ļ�����������չ����
����ֵ���õ��ļ�����������չ�����ĳ���
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005-5-14 10:49:41
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
