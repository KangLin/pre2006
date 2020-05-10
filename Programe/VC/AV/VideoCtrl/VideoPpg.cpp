// VideoPpg.cpp : Implementation of the CVideoPropPage property page class.

#include "stdafx.h"
#include "VideoCtrl.h"
#include "VideoPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CVideoPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CVideoPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CVideoPropPage)
	ON_BN_CLICKED(IDC_BUTTONABOUT, OnButtonabout)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CVideoPropPage, "VIDEOCTRL.VideoPropPage.1",
	0x763e02a9, 0x52b4, 0x4974, 0xa6, 0xea, 0x6, 0x55, 0x97, 0xca, 0xe1, 0xe1)


/////////////////////////////////////////////////////////////////////////////
// CVideoPropPage::CVideoPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CVideoPropPage

BOOL CVideoPropPage::CVideoPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_VIDEO_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CVideoPropPage::CVideoPropPage - Constructor

CVideoPropPage::CVideoPropPage() :
	COlePropertyPage(IDD, IDS_VIDEO_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CVideoPropPage)
	// NOTE: ClassWizard will add member initialization here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CVideoPropPage::DoDataExchange - Moves data between page and properties

void CVideoPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CVideoPropPage)
	// NOTE: ClassWizard will add DDP, DDX, and DDV calls here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CVideoPropPage message handlers

void CVideoPropPage::OnButtonabout() 
{
	CDialog dlgAbout(IDD_ABOUTBOX_VIDEO);
	dlgAbout.DoModal();	
}
