/*******************************************************************************************************
�ļ�����staticex.cpp
��  �ܣ���ʾ����λͼ
        ToolTip����
��������Visual C++ 6.0
��  �ߣ���  ��
        ��Ȩ����  ��������Ȩ��
��  ����1.0.0.1
��  �ڣ�2004-12-18
ʱ  �䣺19:41:30

FileName��staticex.cpp
Function��
Compiler��Visual C++ 6.0
Author��  KangLin
          Copyright 2004 KangLin
Date��    2004-12-18
Time��    19:41:30
*******************************************************************************************************/
// staticex.cpp : implementation file
//

#include "stdafx.h"
#include "..\..\�й�����\�й�����.h"
#include "staticex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStaticEx
IMPLEMENT_DYNCREATE(CStaticEx, CWnd)

CStaticEx::CStaticEx()
{
	SetTransparence(RGB(255, 255, 255), FALSE);
}

CStaticEx::~CStaticEx()
{
}


BEGIN_MESSAGE_MAP(CStaticEx, CWnd)
	//{{AFX_MSG_MAP(CStaticEx)
	ON_WM_PAINT()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CStaticEx::SetBitmap(HBITMAP hBitmap)
{

	/*******************************************************************************************************
	BITMAP bp;
	::GetObject(hBitmap, sizeof(BITMAP), &bp);
	if(m_bmpBK.GetSafeHandle())
	{
		m_bmpBK.Detach();
	}
	m_bmpBK.Attach(hBitmap);
	*******************************************************************************************************/
	m_BKPicture.CreateFromBitmap(hBitmap);

	this->InvalidateRect(NULL);
	return TRUE;
}

/*******************************************************************************************************
��������SetBitmap
��  �ܣ�����Դ����λͼ
��  ����
         UINT nID����Դ��ʶ��
����ֵ���ɹ����� TRUE�����򷵻� FALSE��
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-12-20
ʱ  �䣺20:03:56
*******************************************************************************************************/
BOOL CStaticEx::SetBitmap(UINT nID)
{
	BOOL bval = m_BKPicture.CreateFromBitmap(nID);
	InvalidateRect(NULL);
	return bval;
}

/*******************************************************************************************************
��������SetBitmap
��  �ܣ���λͼ��������λͼ
��  ����
         CBitmap* Bitmap��λͼ�����
����ֵ���ɹ����� TRUE�����򷵻� FALSE��
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-12-20
ʱ  �䣺20:04:38
*******************************************************************************************************/
BOOL CStaticEx::SetBitmap(CBitmap* Bitmap)
{
    if(m_BKPicture.CreateFromBitmap(Bitmap))
	{
		this->InvalidateRect(NULL);
		return TRUE;
	}
	return FALSE;
}

/*******************************************************************************************************
��������SetTransparence
��  �ܣ����ÿؼ������Ƿ�͸��
��  ����
         COLORREF nColor��͸��ɫ
         BOOL bTransparence�������Ƿ�͸��
����ֵ���ɹ����� TRUE�����򷵻� FALSE
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-12-21
ʱ  �䣺10:06:01
*******************************************************************************************************/
BOOL CStaticEx::SetTransparence(COLORREF nColor, BOOL bTransparence)
{
	m_TransparenceColor = nColor;
	m_bTransparence = bTransparence;
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CStaticEx message handlers

int CStaticEx::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
    InitToolTip();	
	return 0;
}

void CStaticEx::OnDraw(CDC* pDC)
{
	if(m_bTransparence && m_BKPicture.GetType() == PICTYPE_BITMAP)
	{
        CBitmap bmpBK;
		if(!m_BKPicture.GetBitmap(&bmpBK))
		{
			TRACE(_T("%s(%d) : ��CIPicture�õ�CBitmapʧ�ܡ�\n"), __FILE__, __LINE__);
			return;
		}
		BITMAP bp;
		if(!bmpBK.GetBitmap(&bp))
		{
			TRACE(_T("%s(%d) : ��CBitmap�õ�BITMAPʧ�ܡ�\n"), __FILE__, __LINE__);
			return;
		}
		CDC d;
		d.CreateCompatibleDC(pDC);
		d.SelectObject(&bmpBK);
		CRect rect;
		GetClientRect(&rect);
		//dc.StretchBlt(0, 0, rect.Width(), rect.Height(), 
		//          &d, 0, 0, bp.bmWidth, bp.bmHeight, SRCCOPY);
		TransparentBlt2(pDC->GetSafeHdc(), 0, 0, rect.Width(), rect.Height(), 
			d.GetSafeHdc(), 0, 0, bp.bmWidth, bp.bmHeight, m_TransparenceColor);
		bmpBK.Detach(); //�������ӣ�������CIPicture�е�λͼ��������
        
       /*******************************************************************************************************
	   #ifdef _DEBUG
	   static int i;
	   TRACE(_T("%s(%d) : ͸��%d\n"), __FILE__, __LINE__, i++);
	   #endif
       //*******************************************************************************************************/
	}
	else
	{
		CRect rect;
		GetClientRect(&rect);
		m_BKPicture.Render(pDC, rect, NULL);
	}
}

void CStaticEx::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	OnDraw(&dc);

	// Do not call CWnd::OnPaint() for painting messages
}


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//��������� ===ToolTip=== ���ܵĺ�����
//

/*******************************************************************************************************
��������InitToolTip
��  �ܣ���ʼ�� ToolTip
��  ������
����ֵ����
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-12-17
ʱ  �䣺19:54:35
*******************************************************************************************************/
void CStaticEx::InitToolTip()
{
	if (m_ToolTip.m_hWnd == NULL)
	{
		// Create ToolTip control
		m_ToolTip.Create(this);
		// Create inactive
		m_ToolTip.Activate(FALSE);
		// Enable multiline
		m_ToolTip.SendMessage(TTM_SETMAXTIPWIDTH, 0, 100);
	} // if
}

/*******************************************************************************************************
��������SetToolTipText
��  �ܣ�����ToolTip�ı�
��  ����
         LPCSTR lpszText��Ҫ��ʾ���ı�
         BOOL bActivate���Ƿ񼤻�
����ֵ��
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-12-17
ʱ  �䣺20:23:36
*******************************************************************************************************/
BOOL CStaticEx::SetToolTipText(LPCSTR lpszText, BOOL bActivate)
{
	// We cannot accept NULL pointer
	if (lpszText == NULL) return FALSE;

	// Initialize ToolTip
	InitToolTip();

	// If there is no tooltip defined then add it
	if (m_ToolTip.GetToolCount() == 0)
	{
		CRect rect; 
		GetClientRect(rect);
		m_ToolTip.AddTool(this, lpszText, rect, 1);
	} // if

	// Set text for tooltip
	m_ToolTip.UpdateTipText(lpszText, this, 1);
	m_ToolTip.Activate(bActivate);
	return TRUE;
}

/*******************************************************************************************************
��������SetToolTipText
��  �ܣ�����ToolTip�ı�
��  ����
         int nText��Ҫ��ʾ���ı�����Դ��
         BOOL bActivate���Ƿ񼤻�
����ֵ��
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-12-17
ʱ  �䣺20:24:10
*******************************************************************************************************/
BOOL CStaticEx::SetToolTipText(int nText, BOOL bActivate)
{
	CString sText;

	// Load string resource
	sText.LoadString(nText);
	// If string resource is not empty
	if (sText.IsEmpty() == FALSE) 
	{
		SetToolTipText((LPCTSTR)sText, bActivate);
	}
	return TRUE;
}

BOOL CStaticEx::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	m_ToolTip.RelayEvent(pMsg);
	return CWnd::PreTranslateMessage(pMsg);
}

//
//��������� ===ToolTip=== ���ܵĺ�����
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
