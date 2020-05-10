// AddInsInput.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "AddInsInput.h"
#include <locale.h>
#include <string>
#include "IncludeFile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: If this DLL is dynamically linked against the MFC DLLs,
//		any functions exported from this DLL which call into
//		MFC must have the AFX_MANAGE_STATE macro added at the
//		very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  ȫ�ֳ���
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CComPtr < EnvDTE::_DTE > g_pDTE;
CSystemIncludeTiShi g_SystemIncludeTiShi;
CLocalIncludeTiShi g_LocalIncludeTiShi;

// CAddInsInputApp

BEGIN_MESSAGE_MAP(CAddInsInputApp, CWinApp)
END_MESSAGE_MAP()


// CAddInsInputApp construction

CAddInsInputApp::CAddInsInputApp()
{
	/*ע��:Ӧ�ó�������ʱ����UNICODEģʽ�£����ػ���������Ĭ��Ϊ_tsetlocale(LC_ALL, _T("C"))��
	��C����ת����Cת�����������ַ���������1-256֮�䣩��
	���CFile��typeText������� mbtowc ʱ����C����ת��������Ҫ�������������typeBinary���򲻴��ڴ����⡣
	TRACEҲ�������������
	Ҫʹ������ϵͳ���õ��������ã�
	//��������Ϊϵͳ���õ�����
	_tsetlocale(LC_ALL, _T(""));
	TRACE(_T("%s\n"), _tsetlocale(LC_ALL, NULL));
	*/
	_tsetlocale(LC_ALL, _T(""));
}


// The one and only CAddInsInputApp object
CAddInsInputApp theApp;

const GUID CDECL BASED_CODE _tlid =
		{ 0xD77655AE, 0x9898, 0x4B1B, { 0xBB, 0xEB, 0x5A, 0x75, 0x50, 0xE6, 0x3E, 0x43 } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;


// CAddInsInputApp initialization

BOOL CAddInsInputApp::InitInstance()
{	
	CWinApp::InitInstance();
	//TRACE(_T("%s(%d):CAddInsInputApp::Instance\n"), __FILE__, __LINE__);
	TRACE(_T("CAddInsInputApp::Instance\n"));

	// Initialize OLE libraries
	/*if (!AfxOleInit())
	{
		return FALSE;
	}*/
	
	// Register all OLE server (factories) as running.  This enables the
	//  OLE libraries to create objects from other applications.
	COleObjectFactory::RegisterAll();

	return TRUE;
}


int CAddInsInputApp::ExitInstance()
{
	// TODO: Add your specialized code here and/or call the base class
	//TRACE(_T("%s(%d):CAddInsInputApp::ExitInstance\n"), __FILE__, __LINE__);
	TRACE(_T("CAddInsInputApp::ExitInstance\n"));

	//::CoUninitialize();
	return CWinApp::ExitInstance();
}

// DllGetClassObject - Returns class factory

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return AfxDllGetClassObject(rclsid, riid, ppv);
}


// DllCanUnloadNow - Allows COM to unload DLL

STDAPI DllCanUnloadNow(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return AfxDllCanUnloadNow();
}


// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return SELFREG_E_TYPELIB;

	if (!COleObjectFactory::UpdateRegistryAll())
		return SELFREG_E_CLASS;

	return S_OK;
}


// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return SELFREG_E_TYPELIB;

	if (!COleObjectFactory::UpdateRegistryAll(FALSE))
		return SELFREG_E_CLASS;

	return S_OK;
}

// ������
void __stdcall Show()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
		
	g_SystemIncludeTiShi.Show(::GetDesktopWindow());
}

/*******************************************************************************************************
��������Init
��  ��������DTE���ɴ������á�����������
��  ����
        EnvDTE::_DTE * pDTE��
����ֵ������Ϊ BOOL ���ɹ�����TRUE��ʧ�ܷ���FALSE��
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2006��9��6�� 12:35:32
*******************************************************************************************************/
BOOL __stdcall Init(EnvDTE::_DTE * pDTE)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if(NULL == pDTE)
	{
		return FALSE;
	}// ���� if(NULL == pDTE)
	if(g_pDTE)
	{
		return FALSE;
	} // ���� if(g_pDTE)

	SetDTE(pDTE);

	if(g_SystemIncludeTiShi.GetSafeHwnd() == NULL)
	{
		g_SystemIncludeTiShi.CreateEx();
	}

	if(g_LocalIncludeTiShi.GetSafeHwnd() == NULL)
	{
		g_LocalIncludeTiShi.CreateEx();
	}

	g_SystemIncludeTiShi.Load();

	return TRUE;
}

BOOL __stdcall SetDTE(EnvDTE::_DTE * pDTE)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if(NULL == pDTE)
	{
		return FALSE;
	}// ���� if(NULL == pDTE)
	if(g_pDTE)
	{
		return FALSE;
	} // ���� if(g_pDTE)
	g_pDTE = pDTE;
	g_SystemIncludeTiShi.SetDTE(g_pDTE);
	g_LocalIncludeTiShi.SetDTE(g_pDTE);
	return TRUE;
}

void __stdcall Free()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	g_LocalIncludeTiShi.m_pDTE.Release(); // = NULL;
	g_SystemIncludeTiShi.m_pDTE.Release(); // = NULL;
	g_pDTE.Release(); // = NULL;
}