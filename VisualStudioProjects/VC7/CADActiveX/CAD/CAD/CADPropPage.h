#pragma once

// CADPropPage.h : Declaration of the CCADPropPage property page class.


// CCADPropPage : See CADPropPage.cpp for implementation.

class CCADPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CCADPropPage)
	DECLARE_OLECREATE_EX(CCADPropPage)

// Constructor
public:
	CCADPropPage();

// Dialog Data
	enum { IDD = IDD_PROPPAGE_CAD };

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	DECLARE_MESSAGE_MAP()
};

