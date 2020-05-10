// deviceinfo\DeviceInfo.cpp : implementation file
//

#include "stdafx.h"
#include "..\NetManageView.h"
#include "DeviceInfo.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CDeviceInfo

IMPLEMENT_DYNCREATE(CDeviceInfo, CNetManageBaseView)

CDeviceInfo::CDeviceInfo()
{

}

CDeviceInfo::~CDeviceInfo()
{
}

BEGIN_MESSAGE_MAP(CDeviceInfo, CNetManageBaseView)
END_MESSAGE_MAP()


// CDeviceInfo drawing

void CDeviceInfo::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}


// CDeviceInfo diagnostics

#ifdef _DEBUG
void CDeviceInfo::AssertValid() const
{
	CNetManageBaseView::AssertValid();
}

#ifndef _WIN32_WCE
void CDeviceInfo::Dump(CDumpContext& dc) const
{
	CNetManageBaseView::Dump(dc);
}
#endif
#endif //_DEBUG


// CDeviceInfo message handlers
int CDeviceInfo::ProcessCommand(CCommand & cmd)
{
	int nRet = S_OK;

	return nRet;
}