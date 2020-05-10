/*******************************************************************************************************
��Ȩ���� (C) 2005 ���ֹ����ң���������Ȩ����
�ļ�����FileSystem.h
��  ���������ļ�ϵͳ�Ĳ���
��  ����1.0
��  �ߣ���  ��
E_Mail��kl222@126.com
��  �ڣ�2005��8��17��
ʱ  �䣺18:06:45
��������Microsoft Development Environment 7.10 ���� C/C++ 7.10
*******************************************************************************************************/
#pragma once
#include <tchar.h> 
#include <iostream> 
#include <fstream>
#include <string> 
#include <atlbase.h>
#include <vector>
#include <io.h>

using namespace std;

class CFileSystem
{
public:
	CFileSystem(void);
	~CFileSystem(void);

#ifdef WIN32
	// �õ�������
	DWORD GetAllDrivers(void);
	// �õ�������
	DWORD GetAllDrivers(DWORD nBufferLength, LPTSTR lpBuffer);
	DWORD GetAllDrivers(vector < string > &Drivers);
#endif

	// �õ���ǰ·��
	string GetCurDir(void);
	// ����Ŀ¼
	int MakeDir(LPCTSTR lpszPath);
	// �ı�Ŀ¼
	int ChangeDir(LPCTSTR lpszPath);
	// ɾ��Ŀ¼
	int DeleteDir(LPCTSTR lpszPath);
	// ɾ��Ŀ¼��
	int DeleteDirTree(LPCTSTR lpszPath);
	
	// ɾ��Ŀ¼�ص�����
	static int DeleteTree(LPCTSTR lpszDirName, void* para);
	// ɾ���ļ��ص�����
	static int DeleteFile(LPCTSTR lpszFileName, void * para);

	// �����ļ���
	int BroweDir(LPCTSTR lpszPath, int(*pf)(LPCTSTR lpszFileName, void * para) = NULL, int(*pd)(LPCTSTR lpszDirName, void * para) = NULL, void * para = NULL);
	// �õ�Ŀ¼���ļ�
	int Dir(LPCTSTR lpszFileName, int(*pf)(LPCTSTR lpszFileName, void * para) = NULL, int(*pd)(LPCTSTR lpszDirName, void * para) = NULL, void * para = NULL);
	// ִ��ָ�����ļ�
	int Exect(LPCTSTR lpszFileName);
	// �õ��ļ���
	string GetFileName(LPCTSTR lpszPath);
	// �õ���չ��
	string GetExt(LPCTSTR lpszFile);
	// �õ��ļ�����
	string GetFileTitle(LPCTSTR lpszFile);
	// �õ�·��
	string GetPath(LPCTSTR lpszFile);
#ifdef WIN32
	// �õ�������
	string GetDriver(LPCTSTR lpszFile);
#endif
	
	// ɾ���ļ�
	int DeleteFile(LPCTSTR lpszFileName);
};
