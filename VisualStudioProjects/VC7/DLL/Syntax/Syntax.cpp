/*******************************************************************************************************
�ļ�����Syntax.cpp
��  �ܣ�C ���Դ����ʽ��
��  ����1.0.0.1
��  �ߣ���  ��
        ��Ȩ����  ��������Ȩ��
E_Mail��kl222@126.com
��  �ڣ�2005-5-5
ʱ  �䣺7:56:20
��������Microsoft Development Environment 7.10 ���� C/C++ 7.10

FileName��Syntax.cpp
Function��Format C/C++ Code.
Version ��1.0.0.1
Author  ��KangLin
          Copyright 2005 KangLin
E_Mail  ��kl222@126.com
Date    ��2005-5-5
Time    ��7:56:21
Compiler��Microsoft Development Environment 7.10 ���� C/C++ 7.10
*******************************************************************************************************/
// Syntax.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "Syntax.h"

//�޸�:�޸�ͷ�ļ�λ��
#include "C:\Program Files\HTML Help Workshop\include\htmlhelp.h"

#pragma  comment(lib, "Htmlhelp")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//	ע�⣡
//
//		����� DLL ��̬���ӵ� MFC
//		DLL���Ӵ� DLL ������
//		���� MFC ���κκ����ں�������ǰ��
//		��������� AFX_MANAGE_STATE �ꡣ
//
//		����:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// �˴�Ϊ��ͨ������
//		}
//
//		�˺������κ� MFC ����
//		������ÿ��������ʮ����Ҫ������ζ��
//		��������Ϊ�����еĵ�һ�����
//		���֣������������ж������������
//		������Ϊ���ǵĹ��캯���������� MFC
//		DLL ���á�
//
//		�й�������ϸ��Ϣ��
//		����� MFC ����˵�� 33 �� 58��
//

// CSyntaxApp

BEGIN_MESSAGE_MAP(CSyntaxApp, CWinApp)
END_MESSAGE_MAP()


// CSyntaxApp ����

CSyntaxApp::CSyntaxApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CSyntaxApp ����

CSyntaxApp theApp;

const GUID CDECL BASED_CODE _tlid =
		{ 0xC1C2101F, 0x69DF, 0x4374, { 0x8C, 0xAD, 0x22, 0x96, 0x1D, 0xB7, 0x89, 0x91 } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;


// CSyntaxApp ��ʼ��

BOOL CSyntaxApp::InitInstance()
{
	CWinApp::InitInstance();

	// ������ OLE ������(����)ע��Ϊ���С��⽫ʹ
	//  OLE ����Դ�����Ӧ�ó��򴴽�����
	COleObjectFactory::RegisterAll();

	return TRUE;
}

// DllGetClassObject - �����๤��

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return AfxDllGetClassObject(rclsid, riid, ppv);
}


// DllCanUnloadNow - ���� COM ж�� DLL

STDAPI DllCanUnloadNow(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return AfxDllCanUnloadNow();
}


// DllRegisterServer - ������ӵ�ϵͳע���

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return SELFREG_E_TYPELIB;

	if (!COleObjectFactory::UpdateRegistryAll())
		return SELFREG_E_CLASS;

	return S_OK;
}


// DllUnregisterServer - �����ϵͳע������Ƴ�

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

