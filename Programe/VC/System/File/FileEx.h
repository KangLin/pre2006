/*******************************************************************************************************
文件名：FileEx.h
用  法：1、先用一个文件名构造一个实例：
           CFileEx fe(_T("C:\\windows\\system\\text.txt"));
           或：
           CFileEx fe; //则自动得到当前执行文件的文件名。
		2、得到当前执行文件的文件名，(可以不执行1)
		   注意：调用这个函数后，文件名就成为当前执行的文件的名，
		         以后所调用的函数都是对于这个执行文件名而操作的。
		   fe.GetModuleFileName(...);
		3、得到文件标题：fe.GetFileTitle(...);
		4、得到文件路径：fe.GetFilePath(...);
        5、得到文件名：  fe.GetFileName(...);
        6、得到文件扩展名：fe.GetFileExt(...);
        7、得到相对路径：fe.GetRelativePath(...);
		
编译器：Visual C++ 6.0
作  者：康  林
        版权所有  保留所有权利
版  本：1.0.0.1
日  期：2004-11-11
时  间：19:01:37
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
#endif // 结束 #ifdef
#endif

/*!
\brief   用于枚举目录时的回调处理函数
\param   LPCTSTR szFile：
\return  类型为 BOOL 。
\version 1.0
\author  康  林
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
	//文件名，注意：当调用GetModuleFileName后，
	//就存储了这个执行文件的名。
	_tstring m_szFileName;
	HANDLE m_hFile;
};

#endif // !defined(AFX_FILEEX_H__624F4E7E_7EC6_4BE0_8569_FD9705EEF834__INCLUDED_)
