#include "StdAfx.h"
#include "Config.h"
#include ".\type.h"

CConfig::CConfig(void)
{
}

CConfig::~CConfig(void)
{
}

int CConfig::SetFileName(LPCTSTR lpszFileName)
{
	ASSERT(lpszFileName);
	if(lpszFileName)
	{
		m_szFileName = lpszFileName;
		return S_OK;
	} // ½áÊø if(lpszFileName)
	return S_FALSE;
}

int CConfig::SetConfig(LPCTSTR pszItem, LPCTSTR pszKey, LPCTSTR pszValue)
{
	int nRet = S_FALSE;
	ASSERT(pszItem && pszKey && pszValue);
	ASSERT(!m_szFileName.empty());
	if(::WritePrivateProfileString(pszItem, pszKey, pszValue, m_szFileName.c_str()))
	{
		nRet = S_OK;
	} // ½áÊø if(::WritePrivateProfileString(pszItem, pszKey, pszValue, m_szFileName.c_str()))
	return nRet;
}

int CConfig::GetConfig(LPCTSTR pszItem, LPCTSTR pszKey, _tstring & szRetValue, LPCTSTR lpDefault)
{
	int nRet = S_OK;
	DWORD dwLen = MAX_BUFFER;

	ASSERT(pszItem && pszKey);
	ASSERT(!m_szFileName.empty());

	TCHAR * pszValue = NULL;
	pszValue = new TCHAR[dwLen];
	if(NULL == pszValue)
	{
		TRACE(_T("%S(%d):allocate memery error.\n"), __FILE__, __LINE__);
		return S_FALSE;
	}// ½áÊø if(NULL == pszValue)

	dwLen = ::GetPrivateProfileString(pszItem, pszKey, lpDefault, pszValue, dwLen, m_szFileName.c_str());
	szRetValue = pszValue;

	delete []pszValue;

	return nRet;
}