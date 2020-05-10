// CADPropPage.cpp : Implementation of the CCADPropPage property page class.

#include "stdafx.h"
#include "CAD.h"
#include "CADPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CCADPropPage, COlePropertyPage)



// Message map

BEGIN_MESSAGE_MAP(CCADPropPage, COlePropertyPage)
END_MESSAGE_MAP()



// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CCADPropPage, "CAD.CADPropPage.1",
	0x806607a7, 0x4bd, 0x4123, 0x87, 0x7d, 0x21, 0xb7, 0x76, 0x7a, 0x9a, 0x33)



// CCADPropPage::CCADPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CCADPropPage

BOOL CCADPropPage::CCADPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_CAD_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}



// CCADPropPage::CCADPropPage - Constructor

CCADPropPage::CCADPropPage() :
	COlePropertyPage(IDD, IDS_CAD_PPG_CAPTION)
{
}



// CCADPropPage::DoDataExchange - Moves data between page and properties

void CCADPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}



// CCADPropPage message handlers
