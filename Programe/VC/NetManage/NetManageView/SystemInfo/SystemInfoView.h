#pragma once

#include "..\NetManageBaseView.h"

// CSystemInfo view

class CSystemInfoView : public CNetManageBaseView
{
	DECLARE_DYNCREATE(CSystemInfoView)

protected:
	CSystemInfoView();           // protected constructor used by dynamic creation
	virtual ~CSystemInfoView();

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


