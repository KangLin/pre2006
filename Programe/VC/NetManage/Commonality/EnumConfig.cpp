#include "StdAfx.h"
#include "EnumConfig.h"

CEnumConfig::CEnumConfig(void)
{
}

CEnumConfig::~CEnumConfig(void)
{
}

INT CEnumConfig::Enum(LPCTSTR pszItem, ENUMOPERATE eo)
{
	INT nRet = S_OK;
	_tstring szKey, szRet;
	INT nCount = 0, i = 0;
	szKey = COUNT;
	nRet = GetConfig(pszItem, szKey.c_str(), szRet, _T("0"));
	if(S_FALSE == nRet)
	{
		return nRet;
	} // 结束 if(S_FALSE == nRet)

	nCount = _ttoi(szRet.c_str());
	for(i = 1; i <= nCount; i++)
	{
		szKey = pszItem;
		TCHAR tmp[20];
		_swprintf(tmp, _T("%d"), i);
		szKey += tmp;
		nRet = GetConfig(pszItem, szKey.c_str(), szRet, _T(""));
		if(S_OK == nRet)
		{
			eo(szRet.c_str()); 
		}
		else
		{
			TRACE(_T("%S(%d) Get Config error.\n"), __FILE__, __LINE__);
		} // 结束 if(S_OK == nRet)
	} // 结束 for(i = 1; i <= nCount; i++)
	return nRet;
}

INT CEnumConfig::AddKey(LPCTSTR pszItem, LPCTSTR pszValue)
{
	INT nRet = S_OK;
	INT nCount = 0;
	TCHAR tmp[20];
	_tstring szRet, szKey;
	GetConfig(pszItem, COUNT, szRet, _T("0"));
	nCount = _ttoi(szRet.c_str());
	szKey = pszItem;
	_swprintf(tmp, _T("%d"), nCount + 1);
	szKey += tmp;
	nRet = SetConfig(pszItem, szKey.c_str(), pszValue);
	if(S_OK == nRet)
	{
		SetConfig(pszItem, COUNT, tmp);
	} // 结束 if(S_OK == nRet)

	return nRet;
}

INT CEnumConfig::DeleteKey(LPCTSTR pszItem, LPCTSTR pszValue)
{
	INT nRet = S_OK;
	INT nCount = 0, i = 0;
	_tstring szKey, szRet;
	GetConfig(pszItem, COUNT, szRet, _T("0"));
	nCount = _ttoi(szRet.c_str());
	for(i = 1; i <= nCount; i++)
	{
		szKey = pszItem;
		TCHAR tmp[10];
		_swprintf(tmp, _T("%d"), nCount + 1);
		szKey += tmp;
		nRet = GetConfig(pszItem, szKey.c_str(), szRet, _T(""));
		if(S_OK == nRet)
		{
			//TODO:

		} // 结束 if(S_OK == nRet)
	} // 结束 for(i = 1; i <= nCount; i++)
	return nRet;
}