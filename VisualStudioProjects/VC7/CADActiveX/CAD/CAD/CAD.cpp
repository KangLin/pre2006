// CAD.cpp : Implementation of CCADApp and DLL registration.

#include "stdafx.h"
#include "CAD.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CCADApp theApp;

const GUID CDECL BASED_CODE _tlid =
		{ 0xDFF5400B, 0xBAE8, 0x4569, { 0xA9, 0xA5, 0xD8, 0xDD, 0xB8, 0xDD, 0x1D, 0xA4 } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;



// CCADApp::InitInstance - DLL initialization

BOOL CCADApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: Add your own module initialization code here.
	}

	return bInit;
}



// CCADApp::ExitInstance - DLL termination

int CCADApp::ExitInstance()
{
	// TODO: Add your own module termination code here.

	return COleControlModule::ExitInstance();
}



// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}



// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}
