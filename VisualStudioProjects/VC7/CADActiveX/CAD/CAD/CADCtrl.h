#pragma once

// CADCtrl.h : Declaration of the CCADCtrl ActiveX Control class.


// CCADCtrl : See CADCtrl.cpp for implementation.

class CCADCtrl : public COleControl
{
	DECLARE_DYNCREATE(CCADCtrl)

// Constructor
public:
	CCADCtrl();

// Overrides
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();

// Implementation
protected:
	~CCADCtrl();

	DECLARE_OLECREATE_EX(CCADCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CCADCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CCADCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CCADCtrl)		// Type name and misc status

// Message maps
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	};
};

