#include "StdAfx.h"
#include "PasswordManager.h"
#include <fstream>

CPasswordManager::CPasswordManager(void)
{
	m_szFile = _T("password.pwd");
	m_pEncrypterManager = NULL;
	m_Head.MajorVerson = 1;
	m_Head.MinorVerson = 0;
#ifdef UNICODE
	m_Head.nUnicode = 1;
#else
	m_Head.nUnicode = 0;
#endif // ���� #ifdef UNICODE
	m_Head.Extend = 0;

	PASSWORD_DATA data;
	data.szPassword = _T("ok");
	data.szTitle = _T("oktitle");
	data.time = time(NULL);
	m_Passwords[data.szTitle] = data;
	data.szTitle = _T("kk");
	data.szPassword = _T("pass");
	data.szDescription = _T("bb");
	data.szKey = _T("key");
	data.time = 189;
	m_Passwords[data.szTitle] = data;
}

CPasswordManager::~CPasswordManager(void)
{
}

int CPasswordManager::SetEncrypterManager(CEncrypterManager * pMng)
{
	if(pMng)
	{
		m_pEncrypterManager = pMng;
		return S_OK;
	}// ���� if(pMng)
	return S_FALSE;
}

int CPasswordManager::ClearData()
{
	try
	{
		m_Passwords.clear();
	}
	catch(...)
	{
		return S_FALSE;
	};

	return S_OK;
}

int CPasswordManager::GetFirstPassword(POSITION & pos)
{
	pos = m_Passwords.begin();
	return S_OK;
}

int CPasswordManager::GetNextPassword(PASSWORD_DATA & data, POSITION & pos)
{
	if(pos != m_Passwords.end())
	{
		data = pos->second;
		pos++;
		return S_OK;
	}// ���� if(pos != m_Passwords.end())
	return S_FALSE;
}

int CPasswordManager::InsertPassword(const tstring & szTitle, const PASSWORD_DATA & data)
{
	std::pair < std::map < tstring, PASSWORD_DATA > ::iterator, bool > ret;
	ret = m_Passwords.insert(make_pair(szTitle, data));
	return ret.second;
}

int CPasswordManager::GetPassword(const tstring & szTitle, PASSWORD_DATA & data)
{
	std::map < tstring, PASSWORD_DATA > ::iterator it;
	it = m_Passwords.find(szTitle);
	if(m_Passwords.end() == it)
	{
		return S_FALSE;
	}// ���� if(m_Passwords.end == it)
	data = it->second;
	return S_OK;
}

int CPasswordManager::DeletePassword(const tstring & szTitle)
{
	try
	{
		m_Passwords.erase(szTitle);
	}
	catch (...)
	{
		return S_FALSE;
	}

	return S_OK;
}

int CPasswordManager::LoadFile(LPCTSTR lpszFile)
{
	CEncrypter * pEncrypter = m_pEncrypterManager->GetEncrypter(_T("default"));
	if(NULL == pEncrypter)
	{
		return S_FALSE;
	}// ���� if(NULL == pEncrypter)

	std::ifstream in(lpszFile);
	if(!in)
	{
		TRACE(_T("���ļ�����,�����:"));
		return S_FALSE;
	} // ���� if(!in)

	//���ļ�ͷ
	FILE_HEAD head;
	in.read((char * )&head, sizeof(FILE_HEAD));

	//���ԭ�ڴ��е�����
	ClearData();

	//��������
	while(!in.eof())
	{
		PASSWORD_DATA data;
		char * pBuf = NULL;
		ReadFile(&pBuf, &in);
		data.szTitle = (LPCTSTR)pBuf;
		ReadFile(&pBuf, &in);
		data.szPassword = (LPCTSTR)pBuf;
		ReadFile(&pBuf, &in);
		data.szDescription = (LPCTSTR)pBuf;
		ReadFile(&pBuf, &in);
		data.szKey = (LPCTSTR)pBuf;
		ReadFile(&pBuf, &in);
		data.time = (time_t)*pBuf;
		m_Passwords[data.szTitle] = data;
	} // ���� while(!in.eof())

	in.close();
	in.clear();

	return S_OK;
}

int CPasswordManager::OutFile(LPCTSTR lpszFile)
{
	int nRet = 0;
	std::ofstream out(lpszFile);
	if(!out)
	{
		TRACE(_T("���ļ�[%s]����\n"), lpszFile);
		return S_FALSE;
	}// ���� if(!out)

	//д�ļ�ͷ
	out.write((char * )&m_Head, sizeof(FILE_HEAD));

	//д���ļ�
	std::map < tstring, PASSWORD_DATA > ::iterator it;
	for(it = m_Passwords.begin(); it != m_Passwords.end(); it++)
	{
		nRet = WriterFile((char * )it->second.szTitle.c_str(), sizeof(TCHAR)*(1 + it->second.szTitle.size()), &out);
		if(S_FALSE == nRet)
		{
			break;
		} // ���� if(S_FALSE == nRet)
		nRet = WriterFile((char * )it->second.szPassword.c_str(), sizeof(TCHAR)* (1 + it->second.szPassword.size()), &out);
		if(S_FALSE == nRet)
		{
			break;
		}// ���� if(S_FALSE == nRet)
		nRet = WriterFile((char * )it->second.szDescription.c_str(), sizeof(TCHAR)* (1 + it->second.szDescription.size()), &out);
		if(S_FALSE == nRet)
		{
			break;
		}// ���� if(S_FALSE == nRet)
		nRet = WriterFile((char * )it->second.szKey.c_str(), sizeof(TCHAR)*(1 + it->second.szKey.size()), &out);
		if(S_FALSE == nRet)
		{
			break;
		}// ���� if(S_FALSE == nRet)
		nRet = WriterFile((char * )&(it->second.time), sizeof(time_t), &out);
		if(S_FALSE == nRet)
		{
			break;
		} // ���� if(S_FALSE == nRet)
	} // ���� for(it = m_lstPassword.begin(); it != m_lstPassword.end(); it++)
	out.close();
	out.clear();
	return S_OK;
}

int CPasswordManager::WriterFile(char * pBuf, const int nLen, std::ofstream * pOut)
{
	int length = nLen;

	pOut->write((char * )&length, sizeof(int));
	pOut->write(pBuf, length);
	return S_OK;
}

int CPasswordManager::ReadFile(char ** pBuf, std::ifstream * pIn)
{
	int nRet = S_OK;
	const int length = 256;
	static char * pb = NULL;
	static char buf[length];
	int nLen = 0;

	pIn->read((char * )&nLen, sizeof(nLen));
	if(nLen > length)
	{
		if(NULL != pb && buf != pb)
		{
			delete []pb;
		}
		else
		{
			pb = new char[nLen];
			if(NULL == pb)
			{
				TRACE(_T("�����ڴ�ʧ��"));
				return S_FALSE;
			} // ���� if(NULL == pb)
		}// ���� if(NULL != pb && buf != pb)
	}
	else
	{
		pb = buf;
	}// ���� if(nLen > length)
	pIn->read(pb, nLen);
	*pBuf = pb;
	return nRet;
}
