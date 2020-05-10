/*******************************************************************************************************
文件名：CIPicture.cpp
功  能：完成图形的通常操作
用  法：
    一、加载
        从资源加载
        BOOL Load(UINT nIDRes);
		从文件加载
		BOOL Load(LPCTSTR pszPathName);
		从文件类对象加载
		BOOL Load(CFile& file);
		从流加载
		BOOL Load(CArchive& ar);
		从流接口加载
		BOOL Load(IStream* pstm);
        建立空位图
		BOOL CreateEmpty();
        从资源加载
    	BOOL CreateFromBitmap(UINT idResource);
	    BOOL CreateFromBitmap(CBitmap* pBitmap, CPalette* pPal = NULL,
	                    	BOOL bTransferOwnership = TRUE);
	    BOOL CreateFromBitmap(HBITMAP hbm, HPALETTE hpal = NULL,
		                    BOOL bTransferOwnership = FALSE);

	    BOOL CreateFromMetafile(HMETAFILE hmf, int xExt, int yExt,
		                    BOOL bTransferOwnership = FALSE);
        建立光标对象
	    BOOL CreateFromIcon(UINT idResource);
	    BOOL CreateFromIcon(HICON hIcon, BOOL bTransferOwnership = FALSE);
	二、操作
        得到图形类型
		GetType();
		得到位图类
		GetBitmap();
		得到图形大小
		GetImageSize();
		保存到文件
		SaveFile(LPCSTR lpszFileName);
编译器：Visual C++ 6.0
作  者：康  林
        版权所有  保留所有权利
版  本：1.0.0.1
日  期：2004-12-20
时  间：20:09:07

FileName：CIPicture.cpp
Function：
Compiler：Visual C++ 6.0
Author：  KangLin
          Copyright 2004 KangLin
Date：    2004-12-20
Time：    20:09:07
*******************************************************************************************************/

#include "StdAfx.h"
#include "CIPicture.h"
//#include <AFXOLE.H>
#include "C:\PROGRAM FILES\MICROSOFT VISUAL STUDIO\VC98\MFC\SRC\OLEIMPL2.H"  //如果VC6.0不是按默认安装,改变此文件路径

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////////////////////////////////
// CIPicture implementation
//

CIPicture::CIPicture()
{
}

CIPicture::~CIPicture()
{
}

//////////////////
// Load from resource. Looks for "IMAGE" type.
//

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//以下是完成 ===装载图形=== 功能的函数块
//

/*******************************************************************************************************
函数名：Load
功  能：从资源中加载 "IMAGE" 类型图形
参  数：
         UINT nIDRes：资源标识号
返回值：成功返回 TRUE,否则返回 FALSE.
作  者：康  林
版  本：1.0.0.1
日  期：2004-12-20
时  间：19:07:12
*******************************************************************************************************/
BOOL CIPicture::Load(UINT nIDRes)
{
	// find resource in resource file
	HINSTANCE hInst = AfxGetResourceHandle();
	HRSRC hRsrc = ::FindResource(hInst,
		MAKEINTRESOURCE(nIDRes),
		"IMAGE"); // type
	if (!hRsrc)
		return FALSE;

	// load resource into memory
	DWORD len = SizeofResource(hInst, hRsrc);
	BYTE* lpRsrc = (BYTE*)LoadResource(hInst, hRsrc);
	if (!lpRsrc)
		return FALSE;

	// create memory file and load it
	CMemFile file(lpRsrc, len);
	BOOL bRet = Load(file);
	FreeResource(hRsrc);

	return bRet;
}

/*******************************************************************************************************
函数名：Load
功  能：从文件中加载图形
参  数：
         LPCTSTR pszPathName：图形文件名
返回值：成功返回 TRUE,否则返回 FALSE.
作  者：康  林
版  本：1.0.0.1
日  期：2004-12-20
时  间：19:04:06
*******************************************************************************************************/
BOOL CIPicture::Load(LPCTSTR pszPathName)
{
	CFile file;
	if (!file.Open(pszPathName, CFile::modeRead|CFile::shareDenyWrite))
		return FALSE;
	BOOL bRet = Load(file);
	file.Close();
	return bRet;
}

/*******************************************************************************************************
函数名：Load
功  能：从文件类(CFile)对象加载图形
参  数：
         CFile& file：文件对象
返回值：成功返回 TRUE,否则返回 FALSE.
作  者：康  林
版  本：1.0.0.1
日  期：2004-12-20
时  间：19:05:00
*******************************************************************************************************/
BOOL CIPicture::Load(CFile& file)
{
	CArchive ar(&file, CArchive::load | CArchive::bNoFlushOnDelete);
	return Load(ar);
}

//////////////////
// Load from archive--create stream and load from stream.

/*******************************************************************************************************
函数名：Load
功  能：从文档流中加载图形。建立并从流中加载图形。
参  数：
         CArchive& ar：文档流
返回值：成功返回 TRUE,否则返回 FALSE.
作  者：康  林
版  本：1.0.0.1
日  期：2004-12-20
时  间：19:05:47
*******************************************************************************************************/
BOOL CIPicture::Load(CArchive& ar)
{
	CArchiveStream arcstream(&ar);
	return Load((IStream*)&arcstream);
}

/*******************************************************************************************************
函数名：Load
功  能：从接口 IStream 加载图形
说  明：OleLoadPicture： 从流中加载
		OleCreatePictureIndirect：根据结构 PICTDESC 建立一个新的对象。
		IPicture::SaveAsFile：将图像数据存储到流中，格式与存成文件格式相同
参  数：
         IStream* pstm：接口 IStream
返回值：成功返回 TRUE,否则返回 FALSE.
作  者：康  林
版  本：1.0.0.1
日  期：2004-12-20
时  间：19:06:17
*******************************************************************************************************/
BOOL CIPicture::Load(IStream* pstm)
{
	//RELEASE(m_pPict);
	if(m_pPict != NULL)
		m_pPict->Release();
	m_pPict = NULL;
	HRESULT hr = OleLoadPicture(pstm, 0, FALSE,
		IID_IPicture, (void**)&m_pPict);
	ASSERT(SUCCEEDED(hr) && m_pPict);	
	return TRUE;
}

//
//以上是完成 ===装载图形=== 功能的函数块
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


/*******************************************************************************************************
//////////////////
// Render to device context. Covert to HIMETRIC for IPicture.
//
BOOL CIPicture::Render(CDC* pDC, CRect rc, LPCRECT prcMFBounds) const
{
	ASSERT(pDC);

	if (rc.IsRectNull()) {
		CSize sz = GetImageSize(pDC);
		rc.right = sz.cx;
		rc.bottom = sz.cy;
	}
	long hmWidth,hmHeight; // HIMETRIC units
	GetHIMETRICSize(hmWidth, hmHeight);
	m_spIPicture->Render(*pDC, rc.left, rc.top, rc.Width(), rc.Height(),
		0, hmHeight, hmWidth, -hmHeight, prcMFBounds);

	return TRUE;
}
*******************************************************************************************************/

//////////////////
// Get image size in pixels. Converts from HIMETRIC to device coords.
//
CSize CIPicture::GetImageSize(CDC* pDC) const
{
	if (!m_pPict)
		return CSize(0,0);
	
	LONG hmWidth, hmHeight; // HIMETRIC units
	m_pPict->get_Width(&hmWidth);
	m_pPict->get_Height(&hmHeight);
	CSize sz(hmWidth,hmHeight);
	if (pDC==NULL) {
		CWindowDC dc(NULL);
		dc.HIMETRICtoDP(&sz); // convert to pixels
	} else {
		pDC->HIMETRICtoDP(&sz);
	}
	return sz;
}


/*******************************************************************************************************
函数名：GetBitmap
功  能：得到位图
参  数：
         CBitmap *pBitmap：位图指针
返回值：成功返回 TRUE,否则返回 FALSE
作  者：康  林
版  本：1.0.0.1
日  期：2004-12-20
时  间：18:50:01
*******************************************************************************************************/
BOOL CIPicture::GetBitmap(CBitmap *pBitmap)
{
	ASSERT(pBitmap != NULL);
	
	// if picture is a bitmap
	if (PICTYPE_BITMAP == GetType())
	{
		HBITMAP hBitmap = NULL;
		
		// get handle of the bitmap
		m_pPict->get_Handle((OLE_HANDLE FAR *) &hBitmap);
		if(hBitmap != NULL) 
		{
			if(pBitmap->GetSafeHandle() != NULL)
			{
				pBitmap->Detach();
			}
			pBitmap->Attach(hBitmap);
			return true;
		} 
	}
	return false;	
}

BOOL CIPicture::SaveFile(LPCSTR lpszFileName)
{

	return TRUE;
}

