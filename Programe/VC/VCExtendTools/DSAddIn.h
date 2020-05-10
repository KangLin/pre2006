// DSAddIn.h : header file
//

#if !defined(AFX_DSADDIN_H__A75CFD1D_6902_46FC_9E5C_46899F76CC3B__INCLUDED_)
#define AFX_DSADDIN_H__A75CFD1D_6902_46FC_9E5C_46899F76CC3B__INCLUDED_

#include "commands.h"

// {AFC936C0-520D-4D62-A1A6-21C8E01BCA79}
DEFINE_GUID(CLSID_DSAddIn,
0xafc936c0, 0x520d, 0x4d62, 0xa1, 0xa6, 0x21, 0xc8, 0xe0, 0x1b, 0xca, 0x79);

/////////////////////////////////////////////////////////////////////////////
// CDSAddIn

class CDSAddIn : 
	public IDSAddIn,
	public CComObjectRoot,
	public CComCoClass<CDSAddIn, &CLSID_DSAddIn>
{
public:
	DECLARE_REGISTRY(CDSAddIn, "VCExtendTools.DSAddIn.1",
		"VCEXTENDTOOLS Developer Studio Add-in", IDS_VCEXTENDTOOLS_LONGNAME,
		THREADFLAGS_BOTH)

	CDSAddIn() {}
	BEGIN_COM_MAP(CDSAddIn)
		COM_INTERFACE_ENTRY(IDSAddIn)
	END_COM_MAP()
	DECLARE_NOT_AGGREGATABLE(CDSAddIn)

// IDSAddIns
public:
	STDMETHOD(OnConnection)(THIS_ IApplication* pApp, VARIANT_BOOL bFirstTime,
		long dwCookie, VARIANT_BOOL* OnConnection);
	STDMETHOD(OnDisconnection)(THIS_ VARIANT_BOOL bLastTime);

protected:
	CCommandsObj* m_pCommands;
	DWORD m_dwCookie;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DSADDIN_H__A75CFD1D_6902_46FC_9E5C_46899F76CC3B__INCLUDED)
