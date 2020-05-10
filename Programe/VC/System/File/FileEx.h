/*******************************************************************************************************
�ļ�����FileEx.h
��  ����1������һ���ļ�������һ��ʵ����
           CFileEx fe(_T("C:\\windows\\system\\text.txt"));
           ��
           CFileEx fe; //���Զ��õ���ǰִ���ļ����ļ�����
		2���õ���ǰִ���ļ����ļ�����(���Բ�ִ��1)
		   ע�⣺��������������ļ����ͳ�Ϊ��ǰִ�е��ļ�������
		         �Ժ������õĺ������Ƕ������ִ���ļ����������ġ�
		   fe.GetModuleFileName(...);
		3���õ��ļ����⣺fe.GetFileTitle(...);
		4���õ��ļ�·����fe.GetFilePath(...);
        5���õ��ļ�����  fe.GetFileName(...);
        6���õ��ļ���չ����fe.GetFileExt(...);
        7���õ����·����fe.GetRelativePath(...);
		
��������Visual C++ 6.0
��  �ߣ���  ��
        ��Ȩ����  ��������Ȩ��
��  ����1.0.0.1
��  �ڣ�2004-11-11
ʱ  �䣺19:01:37
*******************************************************************************************************/

#if !defined(AFX_FILEEX_H__624F4E7E_7EC6_4BE0_8569_FD9705EEF834__INCLUDED_)
#define AFX_FILEEX_H__624F4E7E_7EC6_4BE0_8569_FD9705EEF834__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <atlstr.h>
#include <string>
using namespace std;

#ifndef _tstring
#ifdef _UNICODE
#define _tstring wstring
#else
#define _tstring string
#endif // ���� #ifdef
#endif

/*!
\brief   ����ö��Ŀ¼ʱ�Ļص�������
\param   LPCTSTR szFile��
\return  ����Ϊ BOOL ��
\version 1.0
\author  ��  ��
\date    2007-6-6 21:04:16
*/
typedef BOOL (*OPERATORFILE)(LPCTSTR szFile);

class CFileEx
{
public:
	CFileEx();
	CFileEx(LPCTSTR pszFile);
	virtual ~CFileEx();

	INT GetFilePath(const TCHAR * lpFullFileName, TCHAR * lpPath);
	INT GetFileName(const TCHAR * lpFullFileName, TCHAR * lpFile);
	INT GetFileTitle(LPCTSTR lpFullFileName, TCHAR * lpTitle);
	INT GetFileExt(LPCTSTR lpFullFileName, TCHAR * lpFileExt);

	_tstring GetFilePath();
	_tstring GetFileName();
	_tstring GetFileTitle();
	_tstring GetFileExt();

	_tstring GetFullPath() {return m_szFileName;}
    INT GetModuleFileName();
    static BOOL GetRelativePath(LPTSTR lpszRelativePath, LPCTSTR lpcszFrom, LPCTSTR lpcszTo, DWORD dwAttrFrom = FILE_ATTRIBUTE_DIRECTORY, DWORD dwAttrTo = FILE_ATTRIBUTE_NORMAL);

	INT EnumDirectory(LPCTSTR pszPath, OPERATORFILE operate, BOOL * bExit);


	BOOL Open(LPCTSTR lpFileName,
		DWORD dwDesiredAccess = GENERIC_READ | GENERIC_WRITE,
		DWORD dwShareMode = NULL,
		LPSECURITY_ATTRIBUTES lpSecurityAttributes = NULL,
		DWORD dwCreationDisposition = OPEN_ALWAYS,
		DWORD dwFlagsAndAttributes = FILE_ATTRIBUTE_NORMAL,
		HANDLE hTemplateFile = NULL
		);
	BOOL Close();

	BOOL WriteString(LPCTSTR lpBuffer);
	BOOL Write(LPVOID lpBuffer, DWORD dwLength);
	BOOL ReadString(CString& szString);
	BOOL Read(LPVOID lpBuffer, DWORD * pdwLength);

private:
	//�ļ�����ע�⣺������GetModuleFileName��
	//�ʹ洢�����ִ���ļ�������
	_tstring m_szFileName;
	HANDLE m_hFile;
};

#endif // !defined(AFX_FILEEX_H__624F4E7E_7EC6_4BE0_8569_FD9705EEF834__INCLUDED_)
