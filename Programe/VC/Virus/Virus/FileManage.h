/*!
\warning ��Ȩ���� (C) 2007 ���ֹ����ң���������Ȩ����
\file    FileManage.h
\brief   �ļ�������,���ڹ����ļ��ĸ������صȹ���
\version 1.0
\author  ��  �� (kl222@126.com)
\date    2007��6��26��  22:29:44
\par     ������:
         Microsoft Visual Studio 8.0 ���� C/C++ 8.0
*/
#pragma once

class CFileManage
{
public:
	CFileManage(void);
	~CFileManage(void);

	//�ļ�����
	BOOL CopyFile(LPCTSTR lpExistingFileName, LPCTSTR lpNewFileName);
	BOOL CopyFilesToDirectory(LPCTSTR lpszDir);
	BOOL CopyFilesToSysDirectory();
	BOOL CopyFilesToRoot(LPCTSTR lpszDir);

	//�ļ�����
	INT SetFilterFiles(LPCTSTR lpszDir);
};
