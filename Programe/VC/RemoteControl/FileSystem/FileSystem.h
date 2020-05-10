/*******************************************************************************************************
版权所有 (C) 2005 康林工作室；保留所有权利。
文件名：FileSystem.h
描  述：用于文件系统的操作
版  本：1.0
作  者：康  林
E_Mail：kl222@126.com
日  期：2005年8月17日
时  间：18:06:45
编译器：Microsoft Development Environment 7.10 —— C/C++ 7.10
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
	// 得到驱动器
	DWORD GetAllDrivers(void);
	// 得到驱动器
	DWORD GetAllDrivers(DWORD nBufferLength, LPTSTR lpBuffer);
	DWORD GetAllDrivers(vector < string > &Drivers);
#endif

	// 得到当前路径
	string GetCurDir(void);
	// 建立目录
	int MakeDir(LPCTSTR lpszPath);
	// 改变目录
	int ChangeDir(LPCTSTR lpszPath);
	// 删除目录
	int DeleteDir(LPCTSTR lpszPath);
	// 删除目录树
	int DeleteDirTree(LPCTSTR lpszPath);
	
	// 删除目录回调函数
	static int DeleteTree(LPCTSTR lpszDirName, void* para);
	// 删除文件回调函数
	static int DeleteFile(LPCTSTR lpszFileName, void * para);

	// 遍历文件夹
	int BroweDir(LPCTSTR lpszPath, int(*pf)(LPCTSTR lpszFileName, void * para) = NULL, int(*pd)(LPCTSTR lpszDirName, void * para) = NULL, void * para = NULL);
	// 得到目录或文件
	int Dir(LPCTSTR lpszFileName, int(*pf)(LPCTSTR lpszFileName, void * para) = NULL, int(*pd)(LPCTSTR lpszDirName, void * para) = NULL, void * para = NULL);
	// 执行指定的文件
	int Exect(LPCTSTR lpszFileName);
	// 得到文件名
	string GetFileName(LPCTSTR lpszPath);
	// 得到扩展名
	string GetExt(LPCTSTR lpszFile);
	// 得到文件标题
	string GetFileTitle(LPCTSTR lpszFile);
	// 得到路径
	string GetPath(LPCTSTR lpszFile);
#ifdef WIN32
	// 得到驱动器
	string GetDriver(LPCTSTR lpszFile);
#endif
	
	// 删除文件
	int DeleteFile(LPCTSTR lpszFileName);
};
