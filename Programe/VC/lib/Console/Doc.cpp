/*******************************************************************************************************
版权所有 (C) 2006 ；保留所有权利。
文件名：Doc.cpp
描  述：文档，用于保存输入的数据
版  本：2.0.0.1
作  者：康  林
E_Mail：kl222@126.com
日  期：2006年11月23日
时  间：15:21:00
编译器：Microsoft Visual Studio 8.0 —— C/C++ 8.0
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
函数名：FreeBuffer
描  述：释放内容
参  数：无
返回值：类型为 int 。成功返回0
版  本：2.0.0.1
作  者：康  林
时  间：2006年11月22日 15:24:06
*******************************************************************************************************/
int CDoc::FreeBuffer()
{
	int i;
	int nEnd = m_arrContent.GetCount();
	for(i = 0; i < nEnd; i++)
	{
		delete []m_arrContent[i];
	}// 结束 for(i = 0; i < nEnd; i++)
	m_arrContent.RemoveAll();
	return 0;
}

/*******************************************************************************************************
函数名：AddList
描  述：把字符串加入到内容最后
参  数：
LPCTSTR lpszInput：要加入的字符串
返回值：类型为 int 。成功返回0，否则返回非零。
版  本：2.0.0.1
作  者：康  林
时  间：2006年11月23日 14:40:58
*******************************************************************************************************/
int CDoc::Add(LPCTSTR lpszInput)
{
	LPTSTR lpstrTmp = NULL;
	lpstrTmp = new TCHAR[_tcslen(lpszInput) + sizeof(TCHAR)]; //这里分配的内存在FreeBuffer中释放
	if(lpstrTmp)
	{
		_tcscpy(lpstrTmp, lpszInput);
		m_arrContent.Add(lpstrTmp);
		return 0;
	} // 结束 if(lpstrTmp)
	return 1;
}

/*******************************************************************************************************
函数名：GetRow
描  述：得到指定行的字符串
参  数：
        int nRow：指定的行(从1开始)
返回值：类型为 LPTSTR 。返回指定行字符串的指针。如果失败返回NULL。
版  本：2.0.0.1
作  者：康  林
时  间：2006年11月23日 15:34:28
*******************************************************************************************************/
LPTSTR CDoc::GetRow(int nRow)
{
	if(nRow < 1 || nRow - 1 > m_arrContent.GetUpperBound())
	{
		return NULL;
	}// 结束 if(nRow < 1 || nRow - 1 > m_arrContent.GetUpperBound())

	return m_arrContent[nRow - 1];
}

/*******************************************************************************************************
函数名：GetChar
描  述：得到指定的字符
参  数：
        int nRow：行(从1开始)
		int nCol：列(从1开始)
返回值：类型为 TCHAR 。成功返回指定位置的字符，失败返回0。
版  本：2.0.0.1
作  者：康  林
时  间：2006年11月23日 15:39:06
*******************************************************************************************************/
TCHAR CDoc::GetChar(int nRow, int nCol)
{
	int nLen = 0;
	LPCTSTR lpStr = GetRow(nRow);
	if(NULL == lpStr)
	{
		return NULL;
	} // 结束 if(NULL == lpStr)
	nLen = _tcslen(lpStr);
	if(nCol - 1 > nLen)
	{
		return NULL;
	}// 结束 if(nCol - 1 > nLen)
	return *(lpStr + nCol - 1);

}

/*******************************************************************************************************
函数名：GetRowCount
描  述：得到内容的行数
参  数：无
返回值：类型为 int 。返回行数
版  本：2.0.0.1
作  者：康  林
时  间：2006年11月23日 17:11:32
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
	} // 结束 if(m_keyCache.IsEmpty())
	m_nKeyIndex--;
	if(m_nKeyIndex < 0)
	{
		m_nKeyIndex = 0;
	} // 结束 if(m_nKeyIndex < 0)
	return m_keyCache.GetAt(m_nKeyIndex);
}

LPCTSTR CDoc::GetNextKey()
{
	if(m_keyCache.IsEmpty())
	{
		return NULL;
	} // 结束 if(m_keyCache.IsEmpty())
	m_nKeyIndex++;
	if(m_nKeyIndex >= m_keyCache.GetCount())
	{
		m_nKeyIndex = m_keyCache.GetCount() - 1;
	} // 结束 if(m_nKeyIndex >= m_keyCache.GetCount())
	return m_keyCache.GetAt(m_nKeyIndex);
}

LPCTSTR CDoc::GetKey(int nIndex)
{
	if(m_keyCache.IsEmpty())
	{
		return NULL;
	} // 结束 if(m_keyCache.IsEmpty())
	if(nIndex < 0 || nIndex > m_keyCache.GetCount())
	{
		return NULL;
	} // 结束 if(nIndex < 0 || nIndex > m_keyCache.GetCount())
	return m_keyCache.GetAt(nIndex);
}

