/*******************************************************************************************************
��Ȩ���� (C) 2006 ����������Ȩ����
�ļ�����Doc.cpp
��  �����ĵ������ڱ������������
��  ����2.0.0.1
��  �ߣ���  ��
E_Mail��kl222@126.com
��  �ڣ�2006��11��23��
ʱ  �䣺15:21:00
��������Microsoft Visual Studio 8.0 ���� C/C++ 8.0
*******************************************************************************************************/

#include "stdafx.h"
#include "Doc.h"

// CDoc

CDoc::CDoc()
{
}

CDoc::~CDoc()
{
	FreeBuffer();
}


// CDoc member functions
/*******************************************************************************************************
��������FreeBuffer
��  �����ͷ�����
��  ������
����ֵ������Ϊ int ���ɹ�����0
��  ����2.0.0.1
��  �ߣ���  ��
ʱ  �䣺2006��11��22�� 15:24:06
*******************************************************************************************************/
int CDoc::FreeBuffer()
{
	int i;
	int nEnd = m_arrContent.GetCount();
	for(i = 0; i < nEnd; i++)
	{
		delete []m_arrContent[i];
	}// ���� for(i = 0; i < nEnd; i++)
	m_arrContent.RemoveAll();
	return 0;
}

/*******************************************************************************************************
��������AddList
��  �������ַ������뵽�������
��  ����
LPCTSTR lpszInput��Ҫ������ַ���
����ֵ������Ϊ int ���ɹ�����0�����򷵻ط��㡣
��  ����2.0.0.1
��  �ߣ���  ��
ʱ  �䣺2006��11��23�� 14:40:58
*******************************************************************************************************/
int CDoc::Add(LPCTSTR lpszInput)
{
	LPTSTR lpstrTmp = NULL;
	lpstrTmp = new TCHAR[_tcslen(lpszInput) + sizeof(TCHAR)]; //���������ڴ���FreeBuffer���ͷ�
	if(lpstrTmp)
	{
		_tcscpy(lpstrTmp, lpszInput);
		m_arrContent.Add(lpstrTmp);
		return 0;
	} // ���� if(lpstrTmp)
	return 1;
}

/*******************************************************************************************************
��������GetRow
��  �����õ�ָ���е��ַ���
��  ����
        int nRow��ָ������(��1��ʼ)
����ֵ������Ϊ LPTSTR ������ָ�����ַ�����ָ�롣���ʧ�ܷ���NULL��
��  ����2.0.0.1
��  �ߣ���  ��
ʱ  �䣺2006��11��23�� 15:34:28
*******************************************************************************************************/
LPTSTR CDoc::GetRow(int nRow)
{
	if(nRow < 1 || nRow - 1 > m_arrContent.GetUpperBound())
	{
		return NULL;
	}// ���� if(nRow < 1 || nRow - 1 > m_arrContent.GetUpperBound())

	return m_arrContent[nRow - 1];
}

/*******************************************************************************************************
��������GetChar
��  �����õ�ָ�����ַ�
��  ����
        int nRow����(��1��ʼ)
		int nCol����(��1��ʼ)
����ֵ������Ϊ TCHAR ���ɹ�����ָ��λ�õ��ַ���ʧ�ܷ���0��
��  ����2.0.0.1
��  �ߣ���  ��
ʱ  �䣺2006��11��23�� 15:39:06
*******************************************************************************************************/
TCHAR CDoc::GetChar(int nRow, int nCol)
{
	int nLen = 0;
	LPCTSTR lpStr = GetRow(nRow);
	if(NULL == lpStr)
	{
		return NULL;
	} // ���� if(NULL == lpStr)
	nLen = _tcslen(lpStr);
	if(nCol - 1 > nLen)
	{
		return NULL;
	}// ���� if(nCol - 1 > nLen)
	return *(lpStr + nCol - 1);

}

/*******************************************************************************************************
��������GetRowCount
��  �����õ����ݵ�����
��  ������
����ֵ������Ϊ int ����������
��  ����2.0.0.1
��  �ߣ���  ��
ʱ  �䣺2006��11��23�� 17:11:32
*******************************************************************************************************/
int CDoc::GetRowCount()
{
	return m_arrContent.GetCount();
}


int CDoc::ClearKey()
{
	m_nKeyIndex = 0;
	m_keyCache.RemoveAll();
	return 0;
}

int CDoc::AddKey(LPCTSTR lpszKey)
{
	m_nKeyIndex = m_keyCache.Add(lpszKey);
	return ++m_nKeyIndex;
}

LPCTSTR CDoc::GetPrevKey()
{
	if(m_keyCache.IsEmpty())
	{
		return NULL;
	} // ���� if(m_keyCache.IsEmpty())
	m_nKeyIndex--;
	if(m_nKeyIndex < 0)
	{
		m_nKeyIndex = 0;
	} // ���� if(m_nKeyIndex < 0)
	return m_keyCache.GetAt(m_nKeyIndex);
}

LPCTSTR CDoc::GetNextKey()
{
	if(m_keyCache.IsEmpty())
	{
		return NULL;
	} // ���� if(m_keyCache.IsEmpty())
	m_nKeyIndex++;
	if(m_nKeyIndex >= m_keyCache.GetCount())
	{
		m_nKeyIndex = m_keyCache.GetCount() - 1;
	} // ���� if(m_nKeyIndex >= m_keyCache.GetCount())
	return m_keyCache.GetAt(m_nKeyIndex);
}

LPCTSTR CDoc::GetKey(int nIndex)
{
	if(m_keyCache.IsEmpty())
	{
		return NULL;
	} // ���� if(m_keyCache.IsEmpty())
	if(nIndex < 0 || nIndex > m_keyCache.GetCount())
	{
		return NULL;
	} // ���� if(nIndex < 0 || nIndex > m_keyCache.GetCount())
	return m_keyCache.GetAt(nIndex);
}

