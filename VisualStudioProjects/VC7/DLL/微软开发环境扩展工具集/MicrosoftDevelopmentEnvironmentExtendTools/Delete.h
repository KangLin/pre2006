#pragma once

class CDelete
{
public:
	CDelete(void);
	~CDelete(void);
	BOOL DeleteCommand(void);

private:
	CComPtr < EnvDTE::_DTE > m_pDTE;
    CComPtr < EnvDTE::TextSelection > m_pSel;
	CComPtr < EnvDTE::Document > m_pDoc;
	
public:
	BOOL Inital(EnvDTE::_DTE * pDTE);
	BOOL GetDocument(void);
	BOOL GetSelection(void);
};
