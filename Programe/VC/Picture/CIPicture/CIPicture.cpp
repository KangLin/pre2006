/*******************************************************************************************************
�ļ�����CIPicture.cpp
��  �ܣ����ͼ�ε�ͨ������
��  ����
    һ������
        ����Դ����
        BOOL Load(UINT nIDRes);
		���ļ�����
		BOOL Load(LPCTSTR pszPathName);
		���ļ���������
		BOOL Load(CFile& file);
		��������
		BOOL Load(CArchive& ar);
		�����ӿڼ���
		BOOL Load(IStream* pstm);
        ������λͼ
		BOOL CreateEmpty();
        ����Դ����
    	BOOL CreateFromBitmap(UINT idResource);
	    BOOL CreateFromBitmap(CBitmap* pBitmap, CPalette* pPal = NULL,
	                    	BOOL bTransferOwnership = TRUE);
	    BOOL CreateFromBitmap(HBITMAP hbm, HPALETTE hpal = NULL,
		                    BOOL bTransferOwnership = FALSE);

	    BOOL CreateFromMetafile(HMETAFILE hmf, int xExt, int yExt,
		                    BOOL bTransferOwnership = FALSE);
        ����������
	    BOOL CreateFromIcon(UINT idResource);
	    BOOL CreateFromIcon(HICON hIcon, BOOL bTransferOwnership = FALSE);
	��������
        �õ�ͼ������
		GetType();
		�õ�λͼ��
		GetBitmap();
		�õ�ͼ�δ�С
		GetImageSize();
		���浽�ļ�
		SaveFile(LPCSTR lpszFileName);
��������Visual C++ 6.0
��  �ߣ���  ��
        ��Ȩ����  ��������Ȩ��
��  ����1.0.0.1
��  �ڣ�2004-12-20
ʱ  �䣺20:09:07

FileName��CIPicture.cpp
Function��
Compiler��Visual C++ 6.0
Author��  KangLin
          Copyright 2004 KangLin
Date��    2004-12-20
Time��    20:09:07
*******************************************************************************************************/

#include "StdAfx.h"
#include "CIPicture.h"
//#include <AFXOLE.H>
#include "C:\PROGRAM FILES\MICROSOFT VISUAL STUDIO\VC98\MFC\SRC\OLEIMPL2.H"  //���VC6.0���ǰ�Ĭ�ϰ�װ,�ı���ļ�·��

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
//��������� ===װ��ͼ��=== ���ܵĺ�����
//

/*******************************************************************************************************
��������Load
��  �ܣ�����Դ�м��� "IMAGE" ����ͼ��
��  ����
         UINT nIDRes����Դ��ʶ��
����ֵ���ɹ����� TRUE,���򷵻� FALSE.
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-12-20
ʱ  �䣺19:07:12
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
��������Load
��  �ܣ����ļ��м���ͼ��
��  ����
         LPCTSTR pszPathName��ͼ���ļ���
����ֵ���ɹ����� TRUE,���򷵻� FALSE.
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-12-20
ʱ  �䣺19:04:06
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
��������Load
��  �ܣ����ļ���(CFile)�������ͼ��
��  ����
         CFile& file���ļ�����
����ֵ���ɹ����� TRUE,���򷵻� FALSE.
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-12-20
ʱ  �䣺19:05:00
*******************************************************************************************************/
BOOL CIPicture::Load(CFile& file)
{
	CArchive ar(&file, CArchive::load | CArchive::bNoFlushOnDelete);
	return Load(ar);
}

//////////////////
// Load from archive--create stream and load from stream.

/*******************************************************************************************************
��������Load
��  �ܣ����ĵ����м���ͼ�Ρ������������м���ͼ�Ρ�
��  ����
         CArchive& ar���ĵ���
����ֵ���ɹ����� TRUE,���򷵻� FALSE.
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-12-20
ʱ  �䣺19:05:47
*******************************************************************************************************/
BOOL CIPicture::Load(CArchive& ar)
{
	CArchiveStream arcstream(&ar);
	return Load((IStream*)&arcstream);
}

/*******************************************************************************************************
��������Load
��  �ܣ��ӽӿ� IStream ����ͼ��
˵  ����OleLoadPicture�� �����м���
		OleCreatePictureIndirect�����ݽṹ PICTDESC ����һ���µĶ���
		IPicture::SaveAsFile����ͼ�����ݴ洢�����У���ʽ�����ļ���ʽ��ͬ
��  ����
         IStream* pstm���ӿ� IStream
����ֵ���ɹ����� TRUE,���򷵻� FALSE.
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-12-20
ʱ  �䣺19:06:17
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
//��������� ===װ��ͼ��=== ���ܵĺ�����
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
��������GetBitmap
��  �ܣ��õ�λͼ
��  ����
         CBitmap *pBitmap��λͼָ��
����ֵ���ɹ����� TRUE,���򷵻� FALSE
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-12-20
ʱ  �䣺18:50:01
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

