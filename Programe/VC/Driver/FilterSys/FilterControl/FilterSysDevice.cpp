#include "StdAfx.h"
#include "FilterSysDevice.h"
#include <Windows.h>
#include <tchar.h>

CFilterSysDevice::CFilterSysDevice(void)
{
	SetServiceName(_T("KFilter"));
	SetDeviceName(_T("KFilter"));
}

CFilterSysDevice::~CFilterSysDevice(void)
{
}
