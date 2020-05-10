/*!
\warning 版权所有 (C) 2007 康林工作室；保留所有权利。
\file    FileManage.h
\brief   文件管理类,用于管理文件的复制隐藏等工作
\version 1.0
\author  康  林 (kl222@126.com)
\date    2007年6月26日  22:29:44
\par     编译器:
         Microsoft Visual Studio 8.0 —— C/C++ 8.0
*/
#pragma once

class CFileManage
{
public:
	CFileManage(void);
	~CFileManage(void);

	//文件操作
	BOOL CopyFile(LPCTSTR lpExistingFileName, LPCTSTR lpNewFileName);
	BOOL CopyFilesToDirectory(LPCTSTR lpszDir);
	BOOL CopyFilesToSysDirectory();
	BOOL CopyFilesToRoot(LPCTSTR lpszDir);

	//文件过滤
	INT SetFilterFiles(LPCTSTR lpszDir);
};
