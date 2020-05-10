// DSAddIn.h : header file
//

#if !defined(AFX_DSADDIN_H__1FFDDA25_9466_45DA_AA59_1956A40F2E2D__INCLUDED_)
#define AFX_DSADDIN_H__1FFDDA25_9466_45DA_AA59_1956A40F2E2D__INCLUDED_

#include "commands.h"
#include "..\..\..\..\VisualStudioProjects\VC7\DLL\AutoDisplayConstOrMacro\AutoDisplayConstOrMacro.h"

// {51748BAB-A8B0-4417-BA3E-54C6E0F7F042}
DEFINE_GUID(CLSID_DSAddIn,
0x51748bab, 0xa8b0, 0x4417, 0xba, 0x3e, 0x54, 0xc6, 0xe0, 0xf7, 0xf0, 0x42);

/////////////////////////////////////////////////////////////////////////////
// CDSAddIn

class CDSAddIn : 
	public IDSAddIn,
	public CComObjectRoot,
	public CComCoClass<CDSAddIn, &CLSID_DSAddIn>
{
public:
	DECLARE_REGISTRY(CDSAddIn, "MicrosoftDevelopmentEnvironmentExtendTools.DSAddIn.1",
		"MICROSOFTDEVELOPMENTENVIRONMENTEXTENDTOOLS Developer Studio Add-in", IDS_MICROSOFTDEVELOPMENTENVIRONMENTEXTENDTOOLS_LONGNAME,
		THREADFLAGS_BOTH)

	CDSAddIn()
	{
		m_pApplication = NULL;
	}
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
	IApplication* m_pApplication;
	DWORD m_dwCookie;
private:
	BOOL AddCommand(LPCTSTR lpszCmdName,  UINT ID_STRING,  LPCTSTR lpszMethod, UINT nImage = NULL, LPCTSTR lpszKey = NULL);

	BOOL m_bFirstTime;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DSADDIN_H__1FFDDA25_9466_45DA_AA59_1956A40F2E2D__INCLUDED)
