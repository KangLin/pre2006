// test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\..\WMI.h"

using namespace std;

int devfun(IWbemClassObject * pclsObj)
{
	_tsetlocale(LC_ALL, _T(""));
	ASSERT(pclsObj != NULL);

	VARIANT vtProp;
	VariantInit(&vtProp);
	::setlocale(LC_ALL, NULL);
	// Get the value of the Name property
	HRESULT hr = pclsObj->Get(L"Description", 0, &vtProp, 0, 0);
	wcout << " Description: " << vtProp.bstrVal << endl;
	TRACE(_T("Description:%s\n"), vtProp.bstrVal);
	// Get the value of the FreePhysicalMemory property
	hr = pclsObj->Get(L"AdapterType",
		0, &vtProp, 0, 0);
	wcout << " AdapterType: "
		<< vtProp.bstrVal << endl;
	TRACE(_T("AdapterType:%s\n"), vtProp.bstrVal);
	VariantClear(&vtProp);

	return 0;
}

int fun(IWbemClassObject * pclsObj)
{
	_tsetlocale(LC_ALL, _T(""));
	ASSERT(pclsObj != NULL);

	VARIANT vtProp;
	VariantInit(&vtProp);

	// Get the value of the Name property
	HRESULT hr = pclsObj->Get(L"Name", 0, &vtProp, 0, 0);
	wcout << " OS Name : " << vtProp.bstrVal << endl;

	// Get the value of the FreePhysicalMemory property
	hr = pclsObj->Get(L"FreePhysicalMemory",
		0, &vtProp, 0, 0);
	wcout << " Free physical memory (in kilobytes): "
		<< vtProp.uintVal << endl;
	VariantClear(&vtProp);

	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	_tsetlocale(LC_ALL, _T(""));
	int nRetCode = 0;

	CWMI wmi;
	//if(wmi.ConnectServer(_T(""), _T("Christy"), _T("123456"), _T("\\\\192.168.1.161\\ROOT\\CIMV2")))
	if(wmi.ConnectServer(_T(""), NULL, NULL, _T("\\\\.\\ROOT\\CIMV2")))
	{
		wcout << "ConnectServer error" << endl;
		return 1;
	} // ½áÊø if(wmi.ConnectServer(_T(""), NULL, NULL, _T("\\ROOT\\CIMV2")))
	wmi.ExecQuery(_T("Select * from Win32_OperatingSystem"), fun);
	wmi.ExecQuery(_T("Select * from Win32_NetworkAdapter"), devfun);
	
	return nRetCode;
}

