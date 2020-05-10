/*******************************************************************************************************
文件名：Syntax.cpp
功  能：C 语言代码格式化
版  本：1.0.0.1
作  者：康  林
        版权所有  保留所有权利
E_Mail：kl222@126.com
日  期：2005-5-5
时  间：7:56:20
编译器：Microsoft Development Environment 7.10 —— C/C++ 7.10

FileName：Syntax.cpp
Function：Format C/C++ Code.
Version ：1.0.0.1
Author  ：KangLin
          Copyright 2005 KangLin
E_Mail  ：kl222@126.com
Date    ：2005-5-5
Time    ：7:56:21
Compiler：Microsoft Development Environment 7.10 —— C/C++ 7.10
*******************************************************************************************************/
// Syntax.cpp : 定义 DLL 的初始化例程。
//

#include "stdafx.h"
#include "Syntax.h"

//修改:修改头文件位置
#include "C:\Program Files\HTML Help Workshop\include\htmlhelp.h"

#pragma  comment(lib, "Htmlhelp")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//	注意！
//
//		如果此 DLL 动态链接到 MFC
//		DLL，从此 DLL 导出并
//		调入 MFC 的任何函数在函数的最前面
//		都必须添加 AFX_MANAGE_STATE 宏。
//
//		例如:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// 此处为普通函数体
//		}
//
//		此宏先于任何 MFC 调用
//		出现在每个函数中十分重要。这意味着
//		它必须作为函数中的第一个语句
//		出现，甚至先于所有对象变量声明，
//		这是因为它们的构造函数可能生成 MFC
//		DLL 调用。
//
//		有关其他详细信息，
//		请参阅 MFC 技术说明 33 和 58。
//

// CSyntaxApp

BEGIN_MESSAGE_MAP(CSyntaxApp, CWinApp)
END_MESSAGE_MAP()


// CSyntaxApp 构造

CSyntaxApp::CSyntaxApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CSyntaxApp 对象

CSyntaxApp theApp;

const GUID CDECL BASED_CODE _tlid =
		{ 0xC1C2101F, 0x69DF, 0x4374, { 0x8C, 0xAD, 0x22, 0x96, 0x1D, 0xB7, 0x89, 0x91 } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;


// CSyntaxApp 初始化

BOOL CSyntaxApp::InitInstance()
{
	CWinApp::InitInstance();

	// 将所有 OLE 服务器(工厂)注册为运行。这将使
	//  OLE 库得以从其他应用程序创建对象。
	COleObjectFactory::RegisterAll();

	return TRUE;
}

// DllGetClassObject - 返回类工厂

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return AfxDllGetClassObject(rclsid, riid, ppv);
}


// DllCanUnloadNow - 允许 COM 卸载 DLL

STDAPI DllCanUnloadNow(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return AfxDllCanUnloadNow();
}


// DllRegisterServer - 将项添加到系统注册表

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return SELFREG_E_TYPELIB;

	if (!COleObjectFactory::UpdateRegistryAll())
		return SELFREG_E_CLASS;

	return S_OK;
}


// DllUnregisterServer - 将项从系统注册表中移除

STDAPI DllUnregisterServer(void)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return SELFREG_E_TYPELIB;

	if (!COleObjectFactory::UpdateRegistryAll(FALSE))
		return SELFREG_E_CLASS;

	return S_OK;
}

extern "C" void WINAPI Show(LPCTSTR szInput)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    /*MessageBox(NULL, szInput,NULL, MB_OK);
    int i = _tcslen(szInput);
    CString ss;
    ss.Format("%d", i);
    TCHAR s[10];
    itoa(i,&s,10);
    MessageBox(NULL, ss, NULL, MB_OK);*/

}

