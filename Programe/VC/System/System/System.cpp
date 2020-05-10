#include "stdafx.h"
#include "System.h"

CSystem::CSystem()
{

}

CSystem::~CSystem()
{

}

_tstring CSystem::GetSystemDirectory()
{
	TCHAR dir[MAX_PATH];
	_tstring szRet;
	UINT nLen = ::GetSystemDirectory(dir, MAX_PATH);
	if(nLen < MAX_PATH)
	{
		szRet = dir; 
	}
	else
	{
		TCHAR * p = new TCHAR[nLen];
		nLen = ::GetSystemDirectory(p, nLen);
		szRet = p;
		delete []p;
	}// ½áÊø if(nLen < MAX_PATH)
	return szRet;
}

_tstring CSystem::GetSystemRootDirectory()
{
	INT nPos = 0;
	_tstring szRet;
	_tstring szDir = GetSystemDirectory();
	nPos = szDir.find(_T(':'));
	TCHAR buf[3];
	memset(buf, 0, 3 * sizeof(TCHAR));
	_tcsncpy(buf, szDir.c_str(), nPos + 1);
	szRet = buf;
	return szRet;
}

INT CSystem::EnumRootDirectory(OPERATORFILE operat)
{
	DWORD dwDrives = GetLogicalDrives();
	int i = 0;
	TCHAR ch;
	_tstring szDriver;
	for(i = 0; i < 32; i++)
	{
		if((dwDrives >> i) && 0x00000001)
		{
			ch = _T('A') + i;
			szDriver = ch;
			szDriver += _T(":");
			operat(szDriver.c_str());
		} // ½áÊø if((dwDrives >> i) && 0x00000001)
	}// ½áÊø for(i = 0; i < 32; i++)
	return 0;
}