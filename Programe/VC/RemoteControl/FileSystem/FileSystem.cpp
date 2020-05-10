/*******************************************************************************************************
版权所有 (C) 2005 康林工作室；保留所有权利。
文件名：FileSystem.cpp
描  述：用于文件系统的操作
版  本：1.0
作  者：康  林
E_Mail：kl222@126.com
日  期：2005年8月17日
时  间：18:07:10
编译器：Microsoft Development Environment 7.10 —— C/C++ 7.10
*******************************************************************************************************/
#include "StdAfx.h"
#include ".\filesystem.h"

using namespace std;

CFileSystem::CFileSystem(void)
{
}

CFileSystem::~CFileSystem(void)
{
}

/*******************************************************************************************************
函数名：GetAllDriver
描  述：得到驱动器
参  数：void：无
返回值：类型为 DWORD 。
		如果函数成功调用,则返回当前有效逻辑驱器的掩码.比特0位表示驱动器A:，
		比特1位表示驱动器B:，比特2位表示驱动器C:，……

		……   4    3   2  1
		________________________
		| …… | 1 | 1 | 1 | 1 |
		------------------------
		  ……   ^   ^   ^   ^
		  ……   |   |   |   |
 		  ……   D:  C:  B:  A;	

版  本：1.0
作  者：康  林
时  间：2005年8月17日 18:11:05
*******************************************************************************************************/
DWORD CFileSystem::GetAllDrivers(void)
{
	return ::GetLogicalDrives();
}

/*******************************************************************************************************
函数名：GetAllDrivers
描  述：得到驱动器
参  数：
		nBufferLength:指定lpBuffer的最大尺寸.这个尺寸不包含终结符(NULL)"\0"
		lpBuffer:接收当前系统的有效驱动器字符串, 以两个终结符结束.驱动器符以一个终结符结束.
             例如:c:\<null>d:\<null><null>
返回值:如果调用失败,则返回0.
       如果成功,则返回字符串的大小,不包括最后的终结符.
       如果lpBuffer比所需的实际空间小,则返回比nBufferLength大的值,此值是所需要的实际尺寸.
版  本：1.0
作  者：康  林
时  间：2005年8月17日 18:13:09
*******************************************************************************************************/
DWORD CFileSystem::GetAllDrivers(DWORD nBufferLength, LPTSTR lpBuffer)
{
	return ::GetLogicalDriveStrings(nBufferLength, lpBuffer);
}

/*******************************************************************************************************
函数名：GetAllDrivers
描  述：得到驱动器
参  数：
        vector< string >&Drivers：包含驱动器的字符串数组
返回值：类型为 DWORD 。如果调用失败,则返回0.
       如果成功,则返回字符串的大小,不包括最后的终结符.
       如果lpBuffer比所需的实际空间小,则返回比nBufferLength大的值,此值是所需要的实际尺寸.
版  本：1.0
作  者：康  林
时  间：2005年8月22日 10:55:03
*******************************************************************************************************/
DWORD CFileSystem::GetAllDrivers(vector < string > &Drivers)
{
	const MAX_LEN = 1024;
	TCHAR szDrivers[MAX_LEN];
	TCHAR * p, *lp;
	int iLen;
	iLen = GetLogicalDriveStrings(MAX_LEN, szDrivers);
	if(iLen)
	{
		p = szDrivers;
		lp = p;
		while(p < szDrivers + iLen)
		{
			if(NULL == *p)
			{
				string s;
				s = lp;
				Drivers.push_back(s);
				lp = p + 1;
			} // 结束 if(NULL == *p)
			p++;
		} // 结束 while(p < szDrivers + iLen)
	} // 结束 if(iLen)
	return iLen;
}

/*******************************************************************************************************
函数名：GetCurDir
描  述：得到当前路径
参  数：void：无
返回值：类型为 string 。如果失败则返回空字符串""
版  本：1.0
作  者：康  林
时  间：2005年8月18日 7:57:23
*******************************************************************************************************/
string CFileSystem::GetCurDir(void)
{
	TCHAR pBuf[MAX_PATH];
	if(NULL != _tgetcwd(pBuf, MAX_PATH))
	{
		return pBuf; 
	}
	else
	{
		return _T("");
	} // 结束 if(NULL != _tgetcwd(pBuf, MAX_PATH))
}

/*******************************************************************************************************
函数名：MakeDir
描  述：建立新目录
参  数：
        LPCTSTR lpszPath：要建立的路径
返回值：类型为 int 。成功返回0,失败返回-1
版  本：1.0
作  者：康  林
时  间：2005年8月18日 8:58:14
*******************************************************************************************************/
int CFileSystem::MakeDir(LPCTSTR lpszPath)
{	
	return _tmkdir(lpszPath);
}

/*******************************************************************************************************
函数名：ChangeDir
描  述：改变目录
参  数：
        LPCTSTR lpszPath：目录
返回值：类型为 int 。
版  本：1.0
作  者：康  林
时  间：2005年8月23日 11:35:19
*******************************************************************************************************/
int CFileSystem::ChangeDir(LPCTSTR lpszPath)
{
	return _tchdir(lpszPath);
}

/*******************************************************************************************************
函数名：DeleteDir
描  述：删除目录
参  数：
        LPCTSTR lpszPath：目录
返回值：类型为 int 。
版  本：1.0
作  者：康  林
时  间：2005年8月23日 11:35:02
*******************************************************************************************************/
int CFileSystem::DeleteDir(LPCTSTR lpszPath)
{
	return _trmdir(lpszPath);
}

/*******************************************************************************************************
函数名：DeleteDirTree
描  述：删除目录树，不管目录是否是空都删除。也可用来删除文件
参  数：
        LPCTSTR lpszPath：目录
返回值：类型为 int 。
版  本：1.0
作  者：康  林
时  间：2005年8月27日 17:21:26
*******************************************************************************************************/
int CFileSystem::DeleteDirTree(LPCTSTR lpszPath)
{
	Dir(lpszPath, DeleteFile, DeleteTree, this);
	DeleteDir(lpszPath);
	return 1;
}

/*******************************************************************************************************
函数名：DeleteTree
描  述：删除目录的回调函数
参  数：
        LPCTSTR lpszDirName：目录名
		void * para        ：传递过来的参数
返回值：类型为 int 。成功返回非0，失败返回0
版  本：1.0
作  者：康  林
时  间：2005年8月27日 17:19:27
*******************************************************************************************************/
int CFileSystem::DeleteTree(LPCTSTR lpszDirName, void * para)
{
	return !((CFileSystem * )para)->DeleteDir(lpszDirName);
}

/*******************************************************************************************************
函数名：DeleteFile
描  述：删除文件的回调函数
参  数：
        LPCTSTR lpszFileName：文件名
		void * para         ：传递过来的参数
返回值：类型为 int 。成功返回非0，失败返回0
版  本：1.0
作  者：康  林
时  间：2005年8月27日 17:20:26
*******************************************************************************************************/
int CFileSystem::DeleteFile(LPCTSTR lpszFileName, void * para)
{
	return !((CFileSystem*)para)->DeleteFile(lpszFileName);
}

/*******************************************************************************************************
函数名：BroweDir
描  述：遍历文件夹
参  数：
        LPCTSTR lpszPath                            ：要遍历的文件夹
		int (*pf)(LPCTSTR lpszFileName, void * para)：处理文件的回调函数
		int (*pd)(LPCTSTR lpszDirName, void * para) ：处理文件夹的回调函数
		void* para                                  ：要传递的参数指针
返回值：类型为 int 。返回0则终止查找。否则返回非0
版  本：1.0
作  者：康  林
时  间：2005年8月18日 9:25:02
*******************************************************************************************************/
int CFileSystem::BroweDir(LPCTSTR lpszPath, int(*pf)(LPCTSTR lpszFileName, void * para), int(*pd)(LPCTSTR lpszDirName, void * para), void * para)
{
	string szPath, szDir;
	szPath = lpszPath;
	szDir = lpszPath;
	if(szPath[szPath.size() - 1] != _T('\\'))
	{
		szPath += _T("\\");
		szDir += _T("\\");
	} // 结束 if(szPath[szPath.size() - 1] != _T('\\'))
	szPath += _T("*.*");

	long hFile;
	_finddata_t fileinfo;
	hFile = _findfirst(szPath.c_str(), &fileinfo);
	if(hFile != -1)
	{
		do
		{
			if(fileinfo.attrib & _A_SUBDIR)
			{
				if(_tcscmp(fileinfo.name, _T(".")) != 0 && _tcscmp(fileinfo.name, _T("..")) != 0)
				{
					//遍历目录
					szPath = szDir + fileinfo.name;
					if(0 == BroweDir(szPath.c_str(), pf, pd))
					{
						_findclose(hFile);
						return 0;
					} // 结束 if(0 == BroweDir(szPath.c_str(), pf, pd))
					if(pd)
					{
						if(pd(szPath.c_str(), para) == 0)
						{
							_findclose(hFile);
							return 0;
						} // 结束 if(pd(szPath.c_str(), para) == 0)
					} // 结束 if(pd)
				} // 结束 if(_tcscmp(fileinfo.name, _T(".")) != 0 && _tcscmp(fileinfo.name, _T("..")) != 0)
			}
			else
			{
				//是文件
				if(pf)
				{
					szPath = szDir + fileinfo.name;
					if(pf(szPath.c_str(), para) == 0)
					{
						_findclose(hFile);
						return 0;
					} // 结束 if(pf(szPath.c_str(), para) == 0)
				} // 结束 if(pf)
			} // 结束 if(fileinfo.attrib & _A_SUBDIR)
		}while(_findnext(hFile, &fileinfo) == 0);

		_findclose(hFile);
	} // 结束 if(hFile != -1)
	return 1;
}

/*******************************************************************************************************
函数名：Dir
描  述：得到目录或文件
参  数：
        LPCTSTR lpszFileName                       ：文件或目录名
		int(*pf)(LPCTSTR lpszFileName, void * para)：处理文件回调函数
		int(*pd)(LPCTSTR lpszDirName, void * para) ：处理文件夹回调函数
		void * para                                ：传递的参数
返回值：类型为 int 。返回0则终止查找。否则返回非0
版  本：1.0
作  者：康  林
时  间：2005年8月22日 10:56:35
*******************************************************************************************************/
int CFileSystem::Dir(LPCTSTR lpszFileName, int(*pf)(LPCTSTR lpszFileName, void * para), int(*pd)(LPCTSTR lpszDirName, void * para), void * para)
{
	string szPath;
	szPath = lpszFileName;
	long hFile;
	_finddata_t fileinfo;
	hFile = _findfirst(szPath.c_str(), &fileinfo);
	if(hFile != -1)
	{
		do
		{
			if(fileinfo.attrib & _A_SUBDIR)
			{
				if(_tcscmp(fileinfo.name, _T(".")) != 0 && _tcscmp(fileinfo.name, _T("..")) != 0)
				{
					//遍历目录
					szPath = fileinfo.name;
					if(0 == BroweDir(szPath.c_str(), pf, pd))
					{
						_findclose(hFile);
						return 0;
					} // 结束 if(0 == BroweDir(szPath.c_str(), pf, pd))
					if(pd)
					{
						if(pd(szPath.c_str(), para) == 0)
						{
							_findclose(hFile);
							return 0;
						} // 结束 if(pd(szPath.c_str(), para) == 0)
					} // 结束 if(pd)
				} // 结束 if(_tcscmp(fileinfo.name, _T(".")) != 0 && _tcscmp(fileinfo.name, _T("..")) != 0)
			}
			else
			{
				//是文件
				if(pf)
				{
					szPath = fileinfo.name;
					if(pf(szPath.c_str(), para) == 0)
					{
						_findclose(hFile);
						return 0;
					} // 结束 if(pf(szPath.c_str(), para) == 0)
				} // 结束 if(pf)
			} // 结束 if(fileinfo.attrib & _A_SUBDIR)
		}while(_findnext(hFile, &fileinfo) == 0);

		_findclose(hFile);
	} // 结束 if(hFile != -1)
	return 1;
}

/*******************************************************************************************************
函数名：Exect
描  述：执行指定的文件
参  数：
        LPCTSTR lpszFileName：要执行的文件
返回值：类型为 int 。
版  本：1.0
作  者：康  林
时  间：2005年8月23日 11:32:06
*******************************************************************************************************/
int CFileSystem::Exect(LPCTSTR lpszFileName)
{
	return system(lpszFileName);
}

/*******************************************************************************************************
函数名：GetFileName
描  述：得到文件名
参  数：
        LPCTSTR lpszPath：文件名
返回值：类型为 string 。文件名，不含路径。
版  本：1.0
作  者：康  林
时  间：2005年8月23日 11:32:29
*******************************************************************************************************/
string CFileSystem::GetFileName(LPCTSTR lpszPath)
{
	LPTSTR lpbuf = new TCHAR[_tcslen(lpszPath) + sizeof(TCHAR)];
	LPTSTR lpout = new TCHAR[_tcslen(lpszPath) + sizeof(TCHAR)];
	_tcscpy(lpbuf, lpszPath);
	LPTSTR p = lpbuf;
	while(*p != NULL)
	{
		if(_T('\\') == *p)
		{
			*p = _T('/');
		} // 结束 if(_T('\\') == *p)
		p++;
	} // 结束 while(*p != NULL)
	_tcsrev(lpbuf);
	p = lpbuf;
	LPTSTR pout = lpout;
	while(*p != NULL)
	{
		if(_T('/') == *p)
		{
			*pout = NULL;
			break;
		} // 结束 if(_T('/') == *p)
		*pout = *p;
		p++;
		pout++;
	} // 结束 while(*p != NULL)
	_tcsrev(lpout);
	string szPath = lpout;
	delete []lpbuf;
	delete []lpout;
	return szPath;
}

/*******************************************************************************************************
函数名：GetExt
描  述：得到扩展名
参  数：
        LPCTSTR lpszFile：文件名
返回值：类型为 string 。扩展名
版  本：1.0
作  者：康  林
时  间：2005年8月23日 11:33:09
*******************************************************************************************************/
string CFileSystem::GetExt(LPCTSTR lpszFile)
{
	TCHAR drive [_MAX_DRIVE];
    TCHAR dir[_MAX_DIR];
    TCHAR fname [_MAX_FNAME];
    TCHAR ext[_MAX_EXT];
	_tsplitpath(lpszFile, drive, dir, fname, ext);
	string szExt = ext;
	return szExt;
}

/*******************************************************************************************************
函数名：GetFileTitle
描  述：得到文件标题
参  数：
        LPCTSTR lpszFile：文件名
返回值：类型为 string 。文件标题
版  本：1.0
作  者：康  林
时  间：2005年8月23日 11:33:30
*******************************************************************************************************/
string CFileSystem::GetFileTitle(LPCTSTR lpszFile)
{
	TCHAR drive [_MAX_DRIVE];
	TCHAR dir[_MAX_DIR];
	TCHAR fname [_MAX_FNAME];
	TCHAR ext[_MAX_EXT];
	_tsplitpath(lpszFile, drive, dir, fname, ext);
	string szTile = fname;
	return szTile;
}

/*******************************************************************************************************
函数名：GetPath
描  述：得到路径
参  数：
        LPCTSTR lpszFile：文件名
返回值：类型为 string 。路径
版  本：1.0
作  者：康  林
时  间：2005年8月23日 11:33:59
*******************************************************************************************************/
string CFileSystem::GetPath(LPCTSTR lpszFile)
{
	TCHAR drive [_MAX_DRIVE];
	TCHAR dir[_MAX_DIR];
	TCHAR fname [_MAX_FNAME];
	TCHAR ext[_MAX_EXT];
	_tsplitpath(lpszFile, drive, dir, fname, ext);
	string szPath = dir;
	return szPath;
}

#ifdef WIN32

/*******************************************************************************************************
函数名：GetDriver
描  述：得到驱动器
参  数：
        LPCTSTR lpszFile：文件名
返回值：类型为 string 。驱动器。
版  本：1.0
作  者：康  林
时  间：2005年8月23日 11:34:16
*******************************************************************************************************/
string CFileSystem::GetDriver(LPCTSTR lpszFile)
{
	TCHAR drive [_MAX_DRIVE];
	TCHAR dir[_MAX_DIR];
	TCHAR fname [_MAX_FNAME];
	TCHAR ext[_MAX_EXT];
	_tsplitpath(lpszFile, drive, dir, fname, ext);
	string szDrive = drive;
	return szDrive;
}

#endif

// 删除文件
int CFileSystem::DeleteFile(LPCTSTR lpszFileName)
{
	return _tremove(lpszFileName);
}
