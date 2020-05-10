#pragma once

#include "..\..\..\..\VisualStudioProjects\VC7\socmca\socmca\WMI\WMI.h"

#ifdef SYSTEMINFO_EXPORTS
#define DllExport __declspec(dllexport)
#else
#define DllExport __declspec(dllimport)
#endif


class DllExport CWMISystemBiosInfo : public CWMI
{
public:
	CWMISystemBiosInfo(void);
	virtual ~CWMISystemBiosInfo(void);

	virtual int OnEnum(IWbemClassObject * pclsObj);

	typedef struct _SYSTEM_BIOS_INFO
	{
		//UINT16 BiosCharacteristics[];
		//_tstring BIOSVersion[];
		//_tstring szBuildNumber;
		_tstring szCaption;
		_tstring szCodeSet;
		_tstring szCurrentLanguage;
		_tstring szDescription;
		_tstring szIdentificationCode;
		UINT16 InstallableLanguages;
		//datetime InstallDate;
		_tstring szLanguageEdition;
		//_tstring ListOfLanguages[];
		_tstring szManufacturer;
		_tstring szName;
		_tstring szOtherTargetOS;
		boolean PrimaryBIOS;
		//datetime ReleaseDate;
		_tstring szSerialNumber;
		_tstring szSMBIOSBIOSVersion;
		UINT16 SMBIOSMajorVersion;
		UINT16 SMBIOSMinorVersion;
		boolean SMBIOSPresent;
		_tstring szSoftwareElementID;
		UINT16 SoftwareElementState;
		_tstring szStatus;
		UINT16 TargetOperatingSystem;
		_tstring szVersion;
	}SYSTEM_BIOS_INFO,*PSYSTEM_BIOS_INFO;

	int GetSystemBiosInfo(PSYSTEM_BIOS_INFO pInfo, LPCTSTR szIP = _T("."), LPCTSTR szUserName = NULL, LPCTSTR szPassword = NULL);

private:
	PSYSTEM_BIOS_INFO m_pInfo;

};
