#include "stdafx.h"
#include "Exception"

CTException::CTException()
{
	m_nErr = 0;
	m_pErr = NULL;
}

CTException::CTException(LPCTSTR lpErr, int nErr)
{
	int nLen = 0;
	nLen = _tcslen(lpErr) + sizeof(TCHAR);
	m_pErr = new TCHAR[nLen];
	if(m_pErr)
	{
		_tcscpy(m_pErr, lpErr);
	} // 结束 if(m_pErr)
	m_nErr = nErr;
}

CTException::CTException(LPCTSTR lpErr)
{
	int nLen = 0;
	nLen = _tcslen(lpErr) + sizeof(TCHAR);
	m_pErr = new TCHAR[nLen];
	if(m_pErr)
	{
		_tcscpy(m_pErr, lpErr);
	}// 结束 if(m_pErr)
	m_nErr = 0;
}

CTException::CTException(CTException & e)
{
	if(e.m_pErr)
	{
		int nLen = 0;
		nLen = _tcslen(e.m_pErr) + sizeof(TCHAR);
		m_pErr = new TCHAR[nLen];
		if(m_pErr)
		{
			_tcscpy(m_pErr, e.m_pErr);
		}// 结束 if(m_pErr)
	}// 结束 if(e.m_pErr)

	m_nErr = e.m_nErr;
}

CTException::~CTException()
{
	if(m_pErr)
	{
		delete []m_pErr;
	} // 结束 if(m_pErr)
}

LPCTSTR CTException::what()
{
	if(m_pErr)
	{
		return m_pErr;
	}// 结束 if(m_pErr)
	return _T("未知异常");
}