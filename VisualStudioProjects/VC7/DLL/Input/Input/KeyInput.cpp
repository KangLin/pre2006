#include "stdafx.h"
#include "KeyInput.h"

using namespace EnvDTE;
using namespace EnvDTE80;

CComPtr < EnvDTE::_DTE > g_pDTE;

void __stdcall Show()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	MessageBox(NULL, GetVcIncludeFolders(g_pDTE, CComBSTR(_T("Win32"))), NULL, MB_OK);
}

BOOL __stdcall SetDTE(EnvDTE::_DTE * pDTE)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if(pDTE)
	{
		g_pDTE = pDTE;
		return TRUE;
	} // ½áÊø if(pDTE)
	return FALSE;
}

CComBSTR GetVcIncludeFolders(EnvDTE::_DTE * pDTE, BSTR bstrPlatform /*= _T("Win32")*/)
{
	CComBSTR bstrIncludeFolders;
	HRESULT hr;

	if(pDTE != NULL)
	{
		CComPtr < EnvDTE::Projects > pProjects;
		CComPtr < EnvDTE::Properties > pProperties;
		CComPtr < EnvDTE::Property > pProperty;
		CComPtr < VCProjectEngineLibrary::VCProjectEngine > pProjectEngine;

		IfFailGoCheck(pDTE->GetObject(_T("VCProjects"), (IDispatch ** )&pProjects), pProjects);
		IfFailGoCheck(pProjects->get_Properties(&pProperties), pProperties);

		CComVariant v;
		v = _T("VCProjectEngine");
		IfFailGoCheck(pProperties->Item(v, &pProperty), pProperty);
		IfFailGoCheck(pProperty->get_Object((IDispatch ** )&pProjectEngine), pProjectEngine);

		CComPtr < VCProjectEngineLibrary::IVCCollection > pVCPlatforms;
		CComPtr < VCProjectEngineLibrary::VCPlatform > pVCPlatform;

		IfFailGoCheck(pProjectEngine->get_Platforms((IDispatch ** )&pVCPlatforms), pVCPlatforms);
		v = bstrPlatform;
		IfFailGoCheck(pVCPlatforms->Item(v, (IDispatch ** )&pVCPlatform), pVCPlatform);
		CComBSTR bstDir;
		IfFailGoCheck(pVCPlatform->get_IncludeDirectories(&bstDir), bstDir);
		pVCPlatform->Evaluate(bstDir, &bstrIncludeFolders);

	} // ½áÊø if(pDTE != NULL)

	return bstrIncludeFolders;

Error:
	return CComBSTR();
}
