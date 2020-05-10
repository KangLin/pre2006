/*******************************************************************************************************
��Ȩ���� (C) 2006 ����������Ȩ����
�ļ�����Doc.h
��  �����ĵ������ڱ������������
��  ����2.0.0.1
��  �ߣ���  ��
E_Mail��kl222@126.com
��  �ڣ�2006��11��23��
ʱ  �䣺15:20:31
��������Microsoft Visual Studio 8.0 ���� C/C++ 8.0
*******************************************************************************************************/
#pragma once

// CDoc command target
#include "afxcoll.h"

class CDoc : public CObject
{
public:
	CDoc();
	virtual ~CDoc();

private:
	CArray < TCHAR *, TCHAR * > m_arrContent;  //����
	CStringArray m_keyCache;
	int m_nKeyIndex;

public:
	LPTSTR GetRow(int nRow);
	TCHAR GetChar(int nRow, int nCol);
	int GetRowCount();

	int Add(LPCTSTR lpszInput);
	int FreeBuffer();

	int ClearKey();
	int AddKey(LPCTSTR lpszKey);
	LPCTSTR GetPrevKey();
	LPCTSTR GetNextKey();
	LPCTSTR GetKey(int nIndex);
};


