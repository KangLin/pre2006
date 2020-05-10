// CADCtrl.cpp : Implementation of the CCADCtrl ActiveX Control class.

#include "stdafx.h"
#include "CAD.h"
#include "CADCtrl.h"
#include "CADPropPage.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CCADCtrl, COleControl)



// Message map

BEGIN_MESSAGE_MAP(CCADCtrl, COleControl)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()



// Dispatch map

BEGIN_DISPATCH_MAP(CCADCtrl, COleControl)
	DISP_FUNCTION_ID(CCADCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()



// Event map

BEGIN_EVENT_MAP(CCADCtrl, COleControl)
END_EVENT_MAP()



// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CCADCtrl, 1)
	PROPPAGEID(CCADPropPage::guid)
END_PROPPAGEIDS(CCADCtrl)



// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CCADCtrl, "CAD.CADCtrl.1",
	0x7958c036, 0xffcf, 0x4d83, 0x99, 0x55, 0x28, 0x3e, 0xea, 0xb9, 0xad, 0xe3)



// Type library ID and version

IMPLEMENT_OLETYPELIB(CCADCtrl, _tlid, _wVerMajor, _wVerMinor)



// Interface IDs

const IID BASED_CODE IID_DCAD =
		{ 0x8BE7099A, 0xB453, 0x41F2, { 0xB5, 0x25, 0x4F, 0x8D, 0x7, 0x3A, 0x1, 0x77 } };
const IID BASED_CODE IID_DCADEvents =
		{ 0x240C81B7, 0xFFBC, 0x4FC6, { 0xA6, 0x2E, 0xAF, 0x83, 0xA1, 0x7A, 0x4A, 0x5C } };



// Control type information

static const DWORD BASED_CODE _dwCADOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CCADCtrl, IDS_CAD, _dwCADOleMisc)



// CCADCtrl::CCADCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CCADCtrl

BOOL CCADCtrl::CCADCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: Verify that your control follows apartment-model threading rules.
	// Refer to MFC TechNote 64 for more information.
	// If your control does not conform to the apartment-model rules, then
	// you must modify the code below, changing the 6th parameter from
	// afxRegApartmentThreading to 0.

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_CAD,
			IDB_CAD,
			afxRegApartmentThreading,
			_dwCADOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}



// CCADCtrl::CCADCtrl - Constructor

CCADCtrl::CCADCtrl()
{
	InitializeIIDs(&IID_DCAD, &IID_DCADEvents);
	// TODO: Initialize your control's instance data here.
}



// CCADCtrl::~CCADCtrl - Destructor

CCADCtrl::~CCADCtrl()
{
	// TODO: Cleanup your control's instance data here.
}



// CCADCtrl::OnDraw - Drawing function

void CCADCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	if (!pdc)
		return;

	// TODO: Replace the following code with your own drawing code.
	pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	pdc->Ellipse(rcBounds);
}



// CCADCtrl::DoPropExchange - Persistence support

void CCADCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.
}



// CCADCtrl::OnResetState - Reset control to default state

void CCADCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}



// CCADCtrl::AboutBox - Display an "About" box to the user

void CCADCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_CAD);
	dlgAbout.DoModal();
}



// CCADCtrl message handlers
