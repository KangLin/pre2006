#pragma once
#include "systeminfo.h"
#include "..\..\..\..\VisualStudioProjects\VC7\socmca\socmca\WMI\WMI.h"

class CWMISystemInfo : public CSystemInfo
{
public:
	CWMISystemInfo(void);
	virtual ~CWMISystemInfo(void);


	typedef struct _WIN32_OPERATION_SYSTEM
	{
		_tstring szName;
		_tstring szVersion;
		_tstring szManufacture;
		_tstring szComputerName;
		_tstring szSerialNumber;
		_tstring szOrganization;
		_tstring szRegisteredUser;
		_tstring szStatus;
		_tstring szSystemDevice;
		_tstring szSystemDirectory;
		_tstring szSystemDrive;
		_tstring szWindowsDirectory;
	} WIN32_OPERATION_SYSTEM, *PWIN32_OPERATION_SYSTEM;

	virtual int GetWin32OperationSystem(PWIN32_OPERATION_SYSTEM pWin32OperationSystem);

	int Win32OperationSystem(IWbemClassObject * pclsObj);

private:
	CWMI m_Wmi;
};
