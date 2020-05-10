/*******************************************************************************************************
版权所有 (C) 2006 ；保留所有权利。
文件名：Doc.h
描  述：文档，用于保存输入的数据
版  本：2.0.0.1
作  者：康  林
E_Mail：kl222@126.com
日  期：2006年11月23日
时  间：15:20:31
编译器：Microsoft Visual Studio 8.0 —— C/C++ 8.0
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
	CArray < TCHAR *, TCHAR * > m_arrContent;  //内容
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


