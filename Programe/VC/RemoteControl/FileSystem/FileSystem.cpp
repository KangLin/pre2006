/*******************************************************************************************************
��Ȩ���� (C) 2005 ���ֹ����ң���������Ȩ����
�ļ�����FileSystem.cpp
��  ���������ļ�ϵͳ�Ĳ���
��  ����1.0
��  �ߣ���  ��
E_Mail��kl222@126.com
��  �ڣ�2005��8��17��
ʱ  �䣺18:07:10
��������Microsoft Development Environment 7.10 ���� C/C++ 7.10
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
��������GetAllDriver
��  �����õ�������
��  ����void����
����ֵ������Ϊ DWORD ��
		��������ɹ�����,�򷵻ص�ǰ��Ч�߼�����������.����0λ��ʾ������A:��
		����1λ��ʾ������B:������2λ��ʾ������C:������

		����   4    3   2  1
		________________________
		| ���� | 1 | 1 | 1 | 1 |
		------------------------
		  ����   ^   ^   ^   ^
		  ����   |   |   |   |
 		  ����   D:  C:  B:  A;	

��  ����1.0
��  �ߣ���  ��
ʱ  �䣺2005��8��17�� 18:11:05
*******************************************************************************************************/
DWORD CFileSystem::GetAllDrivers(void)
{
	return ::GetLogicalDrives();
}

/*******************************************************************************************************
��������GetAllDrivers
��  �����õ�������
��  ����
		nBufferLength:ָ��lpBuffer�����ߴ�.����ߴ粻�����ս��(NULL)"\0"
		lpBuffer:���յ�ǰϵͳ����Ч�������ַ���, �������ս������.����������һ���ս������.
             ����:c:\<null>d:\<null><null>
����ֵ:�������ʧ��,�򷵻�0.
       ����ɹ�,�򷵻��ַ����Ĵ�С,�����������ս��.
       ���lpBuffer�������ʵ�ʿռ�С,�򷵻ر�nBufferLength���ֵ,��ֵ������Ҫ��ʵ�ʳߴ�.
��  ����1.0
��  �ߣ���  ��
ʱ  �䣺2005��8��17�� 18:13:09
*******************************************************************************************************/
DWORD CFileSystem::GetAllDrivers(DWORD nBufferLength, LPTSTR lpBuffer)
{
	return ::GetLogicalDriveStrings(nBufferLength, lpBuffer);
}

/*******************************************************************************************************
��������GetAllDrivers
��  �����õ�������
��  ����
        vector< string >&Drivers���������������ַ�������
����ֵ������Ϊ DWORD ���������ʧ��,�򷵻�0.
       ����ɹ�,�򷵻��ַ����Ĵ�С,�����������ս��.
       ���lpBuffer�������ʵ�ʿռ�С,�򷵻ر�nBufferLength���ֵ,��ֵ������Ҫ��ʵ�ʳߴ�.
��  ����1.0
��  �ߣ���  ��
ʱ  �䣺2005��8��22�� 10:55:03
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
			} // ���� if(NULL == *p)
			p++;
		} // ���� while(p < szDrivers + iLen)
	} // ���� if(iLen)
	return iLen;
}

/*******************************************************************************************************
��������GetCurDir
��  �����õ���ǰ·��
��  ����void����
����ֵ������Ϊ string �����ʧ���򷵻ؿ��ַ���""
��  ����1.0
��  �ߣ���  ��
ʱ  �䣺2005��8��18�� 7:57:23
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
	} // ���� if(NULL != _tgetcwd(pBuf, MAX_PATH))
}

/*******************************************************************************************************
��������MakeDir
��  ����������Ŀ¼
��  ����
        LPCTSTR lpszPath��Ҫ������·��
����ֵ������Ϊ int ���ɹ�����0,ʧ�ܷ���-1
��  ����1.0
��  �ߣ���  ��
ʱ  �䣺2005��8��18�� 8:58:14
*******************************************************************************************************/
int CFileSystem::MakeDir(LPCTSTR lpszPath)
{	
	return _tmkdir(lpszPath);
}

/*******************************************************************************************************
��������ChangeDir
��  �����ı�Ŀ¼
��  ����
        LPCTSTR lpszPath��Ŀ¼
����ֵ������Ϊ int ��
��  ����1.0
��  �ߣ���  ��
ʱ  �䣺2005��8��23�� 11:35:19
*******************************************************************************************************/
int CFileSystem::ChangeDir(LPCTSTR lpszPath)
{
	return _tchdir(lpszPath);
}

/*******************************************************************************************************
��������DeleteDir
��  ����ɾ��Ŀ¼
��  ����
        LPCTSTR lpszPath��Ŀ¼
����ֵ������Ϊ int ��
��  ����1.0
��  �ߣ���  ��
ʱ  �䣺2005��8��23�� 11:35:02
*******************************************************************************************************/
int CFileSystem::DeleteDir(LPCTSTR lpszPath)
{
	return _trmdir(lpszPath);
}

/*******************************************************************************************************
��������DeleteDirTree
��  ����ɾ��Ŀ¼��������Ŀ¼�Ƿ��ǿն�ɾ����Ҳ������ɾ���ļ�
��  ����
        LPCTSTR lpszPath��Ŀ¼
����ֵ������Ϊ int ��
��  ����1.0
��  �ߣ���  ��
ʱ  �䣺2005��8��27�� 17:21:26
*******************************************************************************************************/
int CFileSystem::DeleteDirTree(LPCTSTR lpszPath)
{
	Dir(lpszPath, DeleteFile, DeleteTree, this);
	DeleteDir(lpszPath);
	return 1;
}

/*******************************************************************************************************
��������DeleteTree
��  ����ɾ��Ŀ¼�Ļص�����
��  ����
        LPCTSTR lpszDirName��Ŀ¼��
		void * para        �����ݹ����Ĳ���
����ֵ������Ϊ int ���ɹ����ط�0��ʧ�ܷ���0
��  ����1.0
��  �ߣ���  ��
ʱ  �䣺2005��8��27�� 17:19:27
*******************************************************************************************************/
int CFileSystem::DeleteTree(LPCTSTR lpszDirName, void * para)
{
	return !((CFileSystem * )para)->DeleteDir(lpszDirName);
}

/*******************************************************************************************************
��������DeleteFile
��  ����ɾ���ļ��Ļص�����
��  ����
        LPCTSTR lpszFileName���ļ���
		void * para         �����ݹ����Ĳ���
����ֵ������Ϊ int ���ɹ����ط�0��ʧ�ܷ���0
��  ����1.0
��  �ߣ���  ��
ʱ  �䣺2005��8��27�� 17:20:26
*******************************************************************************************************/
int CFileSystem::DeleteFile(LPCTSTR lpszFileName, void * para)
{
	return !((CFileSystem*)para)->DeleteFile(lpszFileName);
}

/*******************************************************************************************************
��������BroweDir
��  ���������ļ���
��  ����
        LPCTSTR lpszPath                            ��Ҫ�������ļ���
		int (*pf)(LPCTSTR lpszFileName, void * para)�������ļ��Ļص�����
		int (*pd)(LPCTSTR lpszDirName, void * para) �������ļ��еĻص�����
		void* para                                  ��Ҫ���ݵĲ���ָ��
����ֵ������Ϊ int ������0����ֹ���ҡ����򷵻ط�0
��  ����1.0
��  �ߣ���  ��
ʱ  �䣺2005��8��18�� 9:25:02
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
	} // ���� if(szPath[szPath.size() - 1] != _T('\\'))
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
					//����Ŀ¼
					szPath = szDir + fileinfo.name;
					if(0 == BroweDir(szPath.c_str(), pf, pd))
					{
						_findclose(hFile);
						return 0;
					} // ���� if(0 == BroweDir(szPath.c_str(), pf, pd))
					if(pd)
					{
						if(pd(szPath.c_str(), para) == 0)
						{
							_findclose(hFile);
							return 0;
						} // ���� if(pd(szPath.c_str(), para) == 0)
					} // ���� if(pd)
				} // ���� if(_tcscmp(fileinfo.name, _T(".")) != 0 && _tcscmp(fileinfo.name, _T("..")) != 0)
			}
			else
			{
				//���ļ�
				if(pf)
				{
					szPath = szDir + fileinfo.name;
					if(pf(szPath.c_str(), para) == 0)
					{
						_findclose(hFile);
						return 0;
					} // ���� if(pf(szPath.c_str(), para) == 0)
				} // ���� if(pf)
			} // ���� if(fileinfo.attrib & _A_SUBDIR)
		}while(_findnext(hFile, &fileinfo) == 0);

		_findclose(hFile);
	} // ���� if(hFile != -1)
	return 1;
}

/*******************************************************************************************************
��������Dir
��  �����õ�Ŀ¼���ļ�
��  ����
        LPCTSTR lpszFileName                       ���ļ���Ŀ¼��
		int(*pf)(LPCTSTR lpszFileName, void * para)�������ļ��ص�����
		int(*pd)(LPCTSTR lpszDirName, void * para) �������ļ��лص�����
		void * para                                �����ݵĲ���
����ֵ������Ϊ int ������0����ֹ���ҡ����򷵻ط�0
��  ����1.0
��  �ߣ���  ��
ʱ  �䣺2005��8��22�� 10:56:35
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
					//����Ŀ¼
					szPath = fileinfo.name;
					if(0 == BroweDir(szPath.c_str(), pf, pd))
					{
						_findclose(hFile);
						return 0;
					} // ���� if(0 == BroweDir(szPath.c_str(), pf, pd))
					if(pd)
					{
						if(pd(szPath.c_str(), para) == 0)
						{
							_findclose(hFile);
							return 0;
						} // ���� if(pd(szPath.c_str(), para) == 0)
					} // ���� if(pd)
				} // ���� if(_tcscmp(fileinfo.name, _T(".")) != 0 && _tcscmp(fileinfo.name, _T("..")) != 0)
			}
			else
			{
				//���ļ�
				if(pf)
				{
					szPath = fileinfo.name;
					if(pf(szPath.c_str(), para) == 0)
					{
						_findclose(hFile);
						return 0;
					} // ���� if(pf(szPath.c_str(), para) == 0)
				} // ���� if(pf)
			} // ���� if(fileinfo.attrib & _A_SUBDIR)
		}while(_findnext(hFile, &fileinfo) == 0);

		_findclose(hFile);
	} // ���� if(hFile != -1)
	return 1;
}

/*******************************************************************************************************
��������Exect
��  ����ִ��ָ�����ļ�
��  ����
        LPCTSTR lpszFileName��Ҫִ�е��ļ�
����ֵ������Ϊ int ��
��  ����1.0
��  �ߣ���  ��
ʱ  �䣺2005��8��23�� 11:32:06
*******************************************************************************************************/
int CFileSystem::Exect(LPCTSTR lpszFileName)
{
	return system(lpszFileName);
}

/*******************************************************************************************************
��������GetFileName
��  �����õ��ļ���
��  ����
        LPCTSTR lpszPath���ļ���
����ֵ������Ϊ string ���ļ���������·����
��  ����1.0
��  �ߣ���  ��
ʱ  �䣺2005��8��23�� 11:32:29
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
		} // ���� if(_T('\\') == *p)
		p++;
	} // ���� while(*p != NULL)
	_tcsrev(lpbuf);
	p = lpbuf;
	LPTSTR pout = lpout;
	while(*p != NULL)
	{
		if(_T('/') == *p)
		{
			*pout = NULL;
			break;
		} // ���� if(_T('/') == *p)
		*pout = *p;
		p++;
		pout++;
	} // ���� while(*p != NULL)
	_tcsrev(lpout);
	string szPath = lpout;
	delete []lpbuf;
	delete []lpout;
	return szPath;
}

/*******************************************************************************************************
��������GetExt
��  �����õ���չ��
��  ����
        LPCTSTR lpszFile���ļ���
����ֵ������Ϊ string ����չ��
��  ����1.0
��  �ߣ���  ��
ʱ  �䣺2005��8��23�� 11:33:09
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
��������GetFileTitle
��  �����õ��ļ�����
��  ����
        LPCTSTR lpszFile���ļ���
����ֵ������Ϊ string ���ļ�����
��  ����1.0
��  �ߣ���  ��
ʱ  �䣺2005��8��23�� 11:33:30
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
��������GetPath
��  �����õ�·��
��  ����
        LPCTSTR lpszFile���ļ���
����ֵ������Ϊ string ��·��
��  ����1.0
��  �ߣ���  ��
ʱ  �䣺2005��8��23�� 11:33:59
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
��������GetDriver
��  �����õ�������
��  ����
        LPCTSTR lpszFile���ļ���
����ֵ������Ϊ string ����������
��  ����1.0
��  �ߣ���  ��
ʱ  �䣺2005��8��23�� 11:34:16
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

// ɾ���ļ�
int CFileSystem::DeleteFile(LPCTSTR lpszFileName)
{
	return _tremove(lpszFileName);
}
