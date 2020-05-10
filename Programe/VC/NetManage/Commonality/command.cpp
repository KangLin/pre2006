/*!
\warning ��Ȩ���� (C) 2007 ���ֹ����ң���������Ȩ����
\file    command.cpp
\brief   ������ʵ���ļ�
\version 1.0
\author  ��  �� (kl222@126.com)
\date    2007��8��14��  15:14:08
\par     ������:
         Microsoft Visual Studio 8.0 ���� C/C++ 8.0
*/

#include "stdafx.h"
#include "command.h"
#include <stdio.h>
#include <stdexcept>

using namespace std;

CCommand::CCommand()
{
	m_nMaxLength = 0;
	m_nLength = 0;
	m_pBuffer = NULL;

	m_nNextPara = sizeof(DWORD);
}

CCommand::~CCommand()
{
	Clear();
}

/*!
\brief   �õ�����
\param   ��
\return  ����Ϊ DWORD ������
\version 1.0
\author  ��  ��
\date    2007-8-14 15:15:47
*/
DWORD CCommand::GetCommand()
{
	DWORD * pCmd = NULL;
	DWORD dwCmd = 0;
	ASSERT(m_pBuffer);
	if(m_pBuffer)
	{
		pCmd = (DWORD * )m_pBuffer;
		dwCmd = *pCmd;
		return dwCmd;
	} // ���� if(m_pBuffer)	
	CTException e(_T("�쳣���õ������������û��ʼ����"));
	throw e;
}

int CCommand::GetPara(void ** pPara, DWORD* pdwLength)
{
	if(m_nNextPara >= m_nLength)
	{
		CTException e(_T("������Χ!"), S_OUT_OF_RANGE);
		return S_OUT_OF_RANGE;
		return S_FALSE;
	}// ���� if(m_nNextPara >= m_nLength)
	*pPara = m_pBuffer + m_nNextPara + sizeof(DWORD);
	DWORD * pLen = (DWORD * )(m_pBuffer + m_nNextPara);
	*pdwLength = *pLen;
	m_nNextPara = m_nNextPara + sizeof(DWORD) + *pdwLength;
}

int CCommand::GetPara(_tstring * pPara)
{
	void * p = NULL;
	DWORD dwLen = 0;
	try
	{
		GetPara(&p, &dwLen);
		char * pp = new char[dwLen + sizeof(TCHAR)];
		memset(pp, 0, dwLen + sizeof(TCHAR));
		memcpy(pp, p, dwLen);
		*pPara = (LPCTSTR)pp;
		delete []pp;
		return S_OK;
	}
	catch(CTException e)
	{
		throw e;
		return S_FALSE;
	}
	return S_FALSE;
}

int CCommand::GetPara(DWORD * dwPara)
{
	if(m_nNextPara >= m_nLength)
	{
		CTException e(_T("������Χ!"), S_OUT_OF_RANGE);
		return S_OUT_OF_RANGE;
	}// ���� if(m_nNextPara >= m_nLength)
	DWORD * pLen = (DWORD * )(m_pBuffer + m_nNextPara);
	if(*pLen != sizeof(DWORD))
	{
		CTException e(_T("���Ͳ���!"), S_TYPE_ERROR);
		return S_FALSE;
	}// ���� if(*pLen != sizeof(DWORD))
	pLen ++;
	*dwPara = *pLen;
	m_nNextPara = m_nNextPara + sizeof(DWORD) + sizeof(DWORD);
	return S_OK;
}

int CCommand::GetPara(LONG * lgPara)
{
	if(m_nNextPara >= m_nLength)
	{
		CTException e(_T("������Χ!"), S_OUT_OF_RANGE);
		return S_OUT_OF_RANGE;
	}// ���� if(m_nNextPara >= m_nLength)
	DWORD * pLen = (DWORD * )(m_pBuffer + m_nNextPara);
	if(*pLen != sizeof(LONG))
	{
		CTException e(_T("���Ͳ���!"), S_TYPE_ERROR);
		return S_FALSE;
	}// ���� if(*pLen != sizeof(LONG))
	*lgPara = *(LONG * )(pLen + 1);
	m_nNextPara = m_nNextPara + sizeof(DWORD) + *pLen;
	return S_OK;
}

/*!
\brief   �õ�ָ��λ�õĲ���
\param   int nPos          ��������λ��
\param   const void ** pBuf��������ָ��
\param   DWORD* dwLength   �������ĳ���
\return  ����Ϊ int ���ɹ�����S_OK�����򷵻ش��롣
\version 1.0
\author  ��  ��
\date    2007-8-17 14:24:57
*/
int CCommand::GetPara(int nPos, const void ** pBuf, DWORD* dwLength)
{
	int nTotalLen = sizeof(DWORD);
	DWORD nLen = 0;                                    //��������
	char * pPara = NULL;

	while(nPos--)
	{
		DWORD * pLen = (DWORD * )(m_pBuffer + nTotalLen);
		nLen = *pLen;                                  //�������ĳ���
		pPara =(char*) pLen + 1;                       //������ָ��

		nTotalLen = nTotalLen + sizeof(DWORD) + nLen;  //��һ����λ��
		if(nTotalLen > m_nLength)
		{
			CTException e(_T("������Χ!"), S_OUT_OF_RANGE);
			return S_OUT_OF_RANGE;
		} // ���� if(nTotalLen > m_nLength)
	} // ���� while(nPos--)

	*dwLength = nLen;
	*pBuf = pPara;

	return S_OK;
}

/*!
\brief   ��������
\param   DWORD dwCmd������
\return  ����Ϊ int ���ɹ����� S_OK��ʧ�ܷ��� S_FALSE ��
\version 1.0
\author  ��  ��
\date    2007-8-14 15:16:04
*/
int CCommand::SetCommand(DWORD dwCmd)
{
	int nRet = S_OK;
	Clear();
	m_nMaxLength = 1024;
	m_nLength = sizeof(DWORD);
	m_pBuffer = new char[m_nMaxLength];
	if(NULL == m_pBuffer)
	{
		nRet = S_FALSE;
		CTException e(_T("�ڴ�������!"));
		throw e;
		return nRet;
	}
	else
	{
		memcpy(m_pBuffer, &dwCmd, m_nLength);
	}// ���� if(NULL == m_pBuffer)
	return nRet;
}

/*!
\brief   ��������
\param   DWORD dwCmd       ������
\param   const void * pPara���������ָ��
\param   DWORD dwLength    �������������
\return  ����Ϊ int ���ɹ����� S_OK��ʧ�ܷ��� S_FALSE ��
\version 1.0
\author  ��  ��
\date    2007-8-14 15:16:16
*/
int CCommand::SetCommand(DWORD dwCmd, const void * pPara, DWORD dwLength)
{
	int nRet = S_OK;
	Clear();
	m_nMaxLength = sizeof(DWORD) + dwLength;
	m_nLength = m_nMaxLength;
	m_pBuffer = new char[m_nMaxLength];
	if(NULL == m_pBuffer)
	{
		nRet = S_FALSE;
		CTException e(_T("�ڴ�������!"));
		throw e;
		return nRet;
	}
	else
	{
		memcpy(m_pBuffer, &dwCmd, m_nLength);
		memcpy(m_pBuffer + sizeof(DWORD), pPara, dwLength);
	}// ���� if(NULL == m_pBuffer)
	return nRet;
}

/*!
\brief   SetCommand
\param   const void * pBuf������ָ��
\param   DWORD dwLength   ������ȣ�����������Ĳ�����
\return  ����Ϊ int ���ɹ����� S_OK��ʧ�ܷ��� S_FALSE ��
\version 1.0
\author  ��  ��
\date    2007-8-14 15:16:44
*/
int CCommand::SetCommand(const void * pBuf, DWORD dwLength)
{
	int nRet = S_OK;
	Clear();
	m_nMaxLength = dwLength;
	m_nLength = dwLength;
	m_pBuffer = new char[m_nMaxLength];
	if(NULL == m_pBuffer)
	{
		nRet = S_FALSE;
		CTException e(_T("�ڴ�������!"));
		throw e;
		return nRet;
	}
	else
	{
		memcpy(m_pBuffer, pBuf, m_nMaxLength);
	} // ���� if(NULL == m_pBuffer)
	return nRet;
}

/*!
\brief   ���Ӳ���
\param   const void * pBuf������ָ��
\param   DWORD dwLength   ����������
\return  ����Ϊ int ���ɹ����� S_OK��ʧ�ܷ��� S_FALSE ��
\version 1.0
\author  ��  ��
\date    2007-8-14 15:17:15
*/
int CCommand::AddPara(const void * pBuf, DWORD dwLength)
{
	int nRet = S_OK;
	char * pBuffer = NULL;
	if(m_nLength + dwLength + sizeof(DWORD) > m_nMaxLength)
	{
		//�ڴ治�������·����ڴ�
		m_nMaxLength = m_nMaxLength + dwLength + sizeof(DWORD) + dwLength + sizeof(DWORD);
		pBuffer = new char[m_nMaxLength];
		if(NULL == pBuffer)
		{
			CTException e(_T("�ڴ�������!"));
			throw e;
			return S_FALSE;
		}// ���� if(NULL == pBuffer)
		memcpy(pBuffer, m_pBuffer, m_nLength);
		delete []m_pBuffer;
		m_pBuffer = pBuffer;
	}// ���� if(m_nLength + dwLength + sizeof(DWORD) > m_nMaxLength)

	//��������
	memcpy(m_pBuffer + m_nLength, &dwLength, sizeof(DWORD));
	m_nLength += sizeof(DWORD);
	//����
	memcpy(m_pBuffer + m_nLength, pBuf, dwLength);
	m_nLength += dwLength;

	return nRet;
}

/*!
\brief   AddPara
\param   DWORD dwPara������
\return  ����Ϊ int ���ɹ����� S_OK��ʧ�ܷ��� S_FALSE ��
\version 1.0
\author  ��  ��
\date    2007-8-14 15:18:32
*/
int CCommand::AddPara(DWORD dwPara)
{
	return AddPara(&dwPara, sizeof(DWORD));
}

int CCommand::AddPara(LONG lgPara)
{
	return AddPara(&lgPara, sizeof(LONG));
}

int CCommand::AddPara(LPCTSTR lpszPara)
{
	ASSERT(lpszPara);
	DWORD dwLength = (_tcslen(lpszPara) + 1) * sizeof(TCHAR);
	return AddPara(lpszPara, dwLength);
}

int CCommand::AddPara(UINT32 dwPara)
{
	return AddPara(&dwPara,sizeof(UINT32));
}

int CCommand::AddPara(BOOL bPara)
{
	return AddPara(&bPara, sizeof(BOOL));
}

/*!
\brief   �޸�ָ��λ�õĲ��������ָ��λ�ò����ڷ���FALSE
\param   int nPos         ��Ҫ�޸ĵ�λ��(��1��ʼ)
\param   const void * pBuf������ָ��
\param   DWORD dwLength   ����������
\return  ����Ϊ int ���ɹ�����S_OK��ʧ�ܷ���S_FALSE��
\version 1.0
\author  ��  ��
\date    2007-8-17 12:37:06
*/
int CCommand::ModifyPara(int nPos, const void * pBuf, DWORD dwLength)
{
	int nTotalLen = sizeof(DWORD);
	DWORD nLen = 0;                                    //��������
	char * pPara = NULL;

	while(nPos--)
	{
		DWORD * pLen = (DWORD * )(m_pBuffer + nTotalLen);
		nLen = *pLen;                                  //�������ĳ���
		pPara =(char*) pLen + 1;                       //������ָ��
		
		nTotalLen = nTotalLen + sizeof(DWORD) + nLen;  //��һ����λ��
		if(nTotalLen > m_nLength)
		{
			return S_OUT_OF_RANGE;
		} // ���� if(nTotalLen > m_nLength)
	} // ���� while(nPos--)

	if(nLen == dwLength)
	{
		memcpy(pPara, pBuf, nLen);
		return S_OK;
	}// ���� if(nLen == dwLength)

	return S_TYPE_ERROR;
}

/*!
\brief   �õ��������ָ��
\param   ��
\return  ����Ϊ void * ���������ָ��
\version 1.0
\author  ��  ��
\date    2007-8-14 15:18:43
*/
void * CCommand::GetBuffer()
{
	return m_pBuffer;
}

/*!
\brief   �õ������
\param   ��
\return  ����Ϊ int �����泤��
\version 1.0
\author  ��  ��
\date    2007-8-14 15:19:05
*/
int CCommand::GetLength()
{
	return m_nLength;
}

/*!
\brief   �������
\param   ��
\return  ����Ϊ int ���ɹ����� S_OK��ʧ�ܷ��� S_FALSE ��
\version 1.0
\author  ��  ��
\date    2007-8-14 15:19:18
*/
int CCommand::Clear()
{
	if(m_pBuffer)
	{
		delete []m_pBuffer;
	}// ���� if(m_pBuffer)
	m_nMaxLength = 0;
	m_nLength = 0;
	return S_OK;
}