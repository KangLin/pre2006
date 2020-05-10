#pragma once

#include ".\NetManageBaseView.h"

// CMemoryView view

class CMemoryView : public CNetManageBaseView
{
	DECLARE_DYNCREATE(CMemoryView)

protected:
	CMemoryView();           // protected constructor used by dynamic creation
	virtual ~CMemoryView();

public:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()

	virtual int ProcessCommand(CCommand & cmd);
};


