// ToolBarEx.cpp : implementation file
//
//Author:xiaojin
//Nanjing BC Foods Co. Limited
//E-mail:xiaoj@njb.swirebev.com
//Tel:025-8642091
//Date:04-30-2003

#include "stdafx.h"
#include "ToolBarEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CToolBarEx

CToolBarEx::CToolBarEx()
{
	sizeImage.cx =20;
	sizeImage.cy =20;
	img.Create(sizeImage.cx-1, sizeImage.cy-1, ILC_COLOR8|ILC_MASK, 1,1);
}

CToolBarEx::~CToolBarEx()
{
}


BEGIN_MESSAGE_MAP(CToolBarEx, CToolBar)
//{{AFX_MSG_MAP(CToolBarEx)
// NOTE - the ClassWizard will add and remove mapping macros here.
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CToolBarEx message handlers

void CToolBarEx::SetImage()
{
	this->GetToolBarCtrl().SetImageList (&img);
}

void CToolBarEx::SetButtonNumber(int n)
{
    SetButtons(NULL,n);
}

void CToolBarEx::SetButton(int nButton, int nID, int nImage,LPTSTR lpText)
{
    SetButtonInfo(nButton, nID, TBSTYLE_BUTTON, nImage);
	SetButtonText(nButton, lpText);	
}

void CToolBarEx::SetButton(int nButton, int nID, int nImage)
{
    SetButtonInfo(nButton, nID, TBSTYLE_BUTTON, nImage);
}

void CToolBarEx::SetSize(int nWidth,int nHeight)
{
    CSize cs;
	cs.cx =nWidth;
	cs.cy =nHeight;
	SetSizes(cs, sizeImage);
}

int CToolBarEx::AddIcon(HICON hIcon)
{
    return img.Add (hIcon);
}

int CToolBarEx::AddIcon(UINT uIconID)
{
	return AddIcon(AfxGetApp()->LoadIcon(uIconID));
}

void CToolBarEx::AddSeparator(int nButton)
{
	SetButtonInfo(nButton, 0, TBBS_SEPARATOR, 0);
}

void CToolBarEx::SetDefaultSize()
{
	CRect rectToolBar;
	//得到按钮的大小
	GetItemRect(0, &rectToolBar);
	//设置按钮的大小
	SetSizes(rectToolBar.Size (), sizeImage);
}

int CToolBarEx::AddBitmap(CBitmap *pbmImage, CBitmap *pbmMask)
{
    return img.Add( pbmImage, pbmMask);
}

int CToolBarEx::AddBitmap(CBitmap *pbmImage, COLORREF crMask)
{
    return img.Add( pbmImage, crMask);
}

void CToolBarEx::SetImageSize(int nImageWidth,int nImageHeight)
{
   sizeImage.cx = nImageWidth;
   sizeImage.cy =nImageHeight;
}

/*******************************************************************************************************
函数名：CreateEx
功  能：
参  数：
         CWnd *pParentWnd：
         CRect rcBorders：
		 DWORD dwCtrlStyle：
         DWORD dwStyle：         
         UINT nID：
返回值：
作  者：康  林
版  本：1.0.0.1
日  期：2004-12-10
时  间：11:22:01
*******************************************************************************************************/
BOOL CToolBarEx::CreateEx(CWnd* pParentWnd, 
						  CRect rcBorders,
						  DWORD dwCtrlStyle, 
						  DWORD dwStyle, 						   
						  UINT nID
						  )
{
	return CToolBar::CreateEx(pParentWnd, dwCtrlStyle, dwStyle, rcBorders, nID);
}

