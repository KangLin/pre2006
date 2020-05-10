#include "StdAfx.h"
#include "EncrypterManager.h"
#include "DES.h"

CEncrypterManager::CEncrypterManager(void)
{
	m_pDefault = new CDESEncrypter();
}

CEncrypterManager::~CEncrypterManager(void)
{
	std::map<tstring, CEncrypter *>::iterator it;
	for(it = m_Encrypter.begin(); it != m_Encrypter.end(); it++)
	{
		delete it->second;
	} // 结束 for(it = m_Encrypter.begin(); it != m_Encrypter.end(); it++)
}

int CEncrypterManager::RegisterEncrypter(const tstring & szName, CEncrypter * pEncrypter)
{
	int nRet = S_OK;
	std::pair<std::map<tstring, CEncrypter*>::iterator, bool> ret;
	ret = m_Encrypter.insert(make_pair(szName, pEncrypter));
	if(ret.second)
	{
		nRet = S_OK; 
	}
	else
	{
		nRet = S_FALSE;
	} // 结束 if(ret.second)
	return nRet;
}

CEncrypter * CEncrypterManager::GetEncrypter(const tstring &szName)
{
	CEncrypter * pEncrypter = NULL;
	std::map<tstring, CEncrypter*>::iterator it;
	it = m_Encrypter.find(szName);
	if(it == m_Encrypter.end())
	{
		return m_pDefault;
	} // 结束 if(it == m_Encrypter.end())
	pEncrypter = (*it).second;
	return pEncrypter;
}

int CEncrypterManager::RemoveEncrypter(const tstring & szName)
{
	if(0 < m_Encrypter.erase(szName))
	{
		return S_OK;
	}
	else
	{
		return S_FALSE;
	} // 结束 if(0 < m_Encrypter.erase(szName))
}