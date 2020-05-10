#pragma once


// CProcessHide

class CProcessHide : public CWnd
{
	DECLARE_DYNAMIC(CProcessHide)

public:
	CProcessHide();
	virtual ~CProcessHide();

	int OnInitialUpdate(CNetManageViewDoc * pDocument);
	virtual int ProcessCommand(CCommand & cmd);

protected:
	DECLARE_MESSAGE_MAP()

	CNetManageViewDoc * m_pDocument;
public:
	afx_msg void OnPaint();
};


