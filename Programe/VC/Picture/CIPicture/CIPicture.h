/*******************************************************************************************************
文件名：CIPicture.h
功  能：完成图形的通常操作
编译器：Visual C++ 6.0
作  者：康  林
        版权所有  保留所有权利
版  本：1.0.0.1
日  期：2004-12-20
时  间：20:09:17

FileName：CIPicture.h
Function：
Compiler：Visual C++ 6.0
Author：  KangLin
          Copyright 2004 KangLin
Date：    2004-12-20
Time：    20:09:17
*******************************************************************************************************/
#ifndef _CIPICTURE_H_KANGLIN_CHINA_2004_12_20_
#define _CIPICTURE_H_KANGLIN_CHINA_2004_12_20_

#pragma once
#include <atlbase.h>
#include <afxctl.h>
#include <afxpriv2.h>

class CIPicture : public CPictureHolder
{
public:
	CIPicture();
	~CIPicture();

	// Load frm various sosurces
	BOOL Load(UINT nIDRes);
	BOOL Load(LPCTSTR pszPathName);
	BOOL Load(CFile& file);
	BOOL Load(CArchive& ar);
	BOOL Load(IStream* pstm);

	BOOL SaveFile(LPCSTR lpszFileName);

	BOOL GetBitmap(CBitmap* pBitmap);
    CSize GetImageSize(CDC* pDC = NULL) const;

	// render to device context
	/*******************************************************************************************************
	BOOL Render(CDC* pDC, CRect rc=CRect(0,0,0,0),
		LPCRECT prcMFBounds=NULL) const;

	operator IPicture*() {
		return m_spIPicture;
	}

	void GetHIMETRICSize(OLE_XSIZE_HIMETRIC& cx, OLE_YSIZE_HIMETRIC& cy) const {
		cx = cy = 0;
		const_cast<CIPicture*>(this)->m_hr = m_spIPicture->get_Width(&cx);
		ASSERT(SUCCEEDED(m_hr));
		const_cast<CIPicture*>(this)->m_hr = m_spIPicture->get_Height(&cy);
		ASSERT(SUCCEEDED(m_hr));
	}

	void Free() {
		if (m_spIPicture) {
			m_spIPicture.Release();
		}
	}

protected:
	//CComQIPtr<IPicture>m_spIPicture;		 // ATL smart pointer to IPicture
	HRESULT m_hr;								 // last error code
	*******************************************************************************************************/
};

#endif//#ifndef _CIPICTURE_H_KANGLIN_CHINA_2004_12_20_