// DisplayVideoPpg.cpp : Implementation of the CDisplayVideoPropPage property page class.

#include "stdafx.h"
#include "DisplayVideo.h"
#include "DisplayVideoPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CDisplayVideoPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CDisplayVideoPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CDisplayVideoPropPage)
	ON_BN_CLICKED(IDC_BUTTONABOUT, OnButtonabout)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CDisplayVideoPropPage, "DISPLAYVIDEO.DisplayVideoPropPage.1",
	0x4c73572, 0xb1a, 0x4eed, 0x96, 0x36, 0x2b, 0x16, 0x1c, 0x2, 0x5b, 0x1a)


/////////////////////////////////////////////////////////////////////////////
// CDisplayVideoPropPage::CDisplayVideoPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CDisplayVideoPropPage

BOOL CDisplayVideoPropPage::CDisplayVideoPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_DISPLAYVIDEO_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CDisplayVideoPropPage::CDisplayVideoPropPage - Constructor

CDisplayVideoPropPage::CDisplayVideoPropPage() :
	COlePropertyPage(IDD, IDS_DISPLAYVIDEO_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CDisplayVideoPropPage)
	// NOTE: ClassWizard will add member initialization here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CDisplayVideoPropPage::DoDataExchange - Moves data between page and properties

void CDisplayVideoPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CDisplayVideoPropPage)
	// NOTE: ClassWizard will add DDP, DDX, and DDV calls here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CDisplayVideoPropPage message handlers

void CDisplayVideoPropPage::OnButtonabout() 
{
	CDialog dlgAbout(IDD_ABOUTBOX_DISPLAYVIDEO);
	dlgAbout.DoModal();
}
