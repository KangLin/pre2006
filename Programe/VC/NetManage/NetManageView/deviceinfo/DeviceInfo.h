#pragma once

#include "..\NetManageBaseView.h"

// CDeviceInfo view

class CDeviceInfo : public CNetManageBaseView
{
	DECLARE_DYNCREATE(CDeviceInfo)

protected:
	CDeviceInfo();           // protected constructor used by dynamic creation
	virtual ~CDeviceInfo();

public:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

	virtual int ProcessCommand(CCommand & cmd);

protected:
	DECLARE_MESSAGE_MAP()
};


