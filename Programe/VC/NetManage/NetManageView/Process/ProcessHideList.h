#pragma once


// CProcessHideList

class CProcessHideList : public CWnd
{
	DECLARE_DYNAMIC(CProcessHideList)

public:
	CProcessHideList();
	virtual ~CProcessHideList();

protected:
	DECLARE_MESSAGE_MAP()
	

public:
	afx_msg void OnPaint();

	int OnInitialUpdate(CNetManageViewDoc * pDocument);
	virtual int ProcessCommand(CCommand & cmd);

private:
	CNetManageViewDoc * m_pDocument; //µ±Ç°ÎÄµµ
};


