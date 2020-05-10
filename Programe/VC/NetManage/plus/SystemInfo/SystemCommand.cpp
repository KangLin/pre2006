#include "StdAfx.h"
#include "SystemCommand.h"
#include "..\..\..\System\System\WMIWin32OperationSystem.h"
#include "..\..\..\System\System\WMIComputerSystem.h"
#include "..\..\..\System\Service\WMIServiceInfo.h"

CSystemCommand::CSystemCommand(CCommand * pCmd)
{
	ASSERT(pCmd);
	m_pCmd = pCmd;
}

CSystemCommand::~CSystemCommand(void)
{
}

int CSystemCommand::QueryWMIWin32OperationSystemInformaion(CCommand * pCmd)
{
	int nRet = S_OK;

	pCmd->SetCommand((DWORD)CMD_ANSWER_WMI_WIN32_OPERATING_SYSTEM_INFORMATION);
	pCmd->AddPara((DWORD)S_OK);

	CWMIWin32OperationSystem wmi;
	CWMIWin32OperationSystem::WIN32_OPERATION_SYSTEM_INFORMATION Win32OperationSystem;
	if(wmi.GetWin32OperationSystem(&Win32OperationSystem) == S_OK)
	{
		try
		{
			pCmd->AddPara(Win32OperationSystem.szName.c_str());
			pCmd->AddPara(Win32OperationSystem.szVersion.c_str());
			pCmd->AddPara(Win32OperationSystem.szManufacture.c_str());
			pCmd->AddPara(Win32OperationSystem.szComputerName.c_str());
			pCmd->AddPara(Win32OperationSystem.szSerialNumber.c_str());
			pCmd->AddPara(Win32OperationSystem.szOrganization.c_str());
			pCmd->AddPara(Win32OperationSystem.szRegisteredUser.c_str());
			pCmd->AddPara(Win32OperationSystem.szStatus.c_str());
			pCmd->AddPara(Win32OperationSystem.szSystemDevice.c_str());
			pCmd->AddPara(Win32OperationSystem.szSystemDirectory.c_str());
			pCmd->AddPara(Win32OperationSystem.szSystemDrive.c_str());
			pCmd->AddPara(Win32OperationSystem.szWindowsDirectory.c_str());
		}
		catch (CTException* e)
		{
			nRet = S_FALSE;
			TRACE(_T("异常:%s"), e->what());
		}
	}
	else
	{
		nRet = S_FALSE; 
	}// 结束 if(wmi.GetWin32OperationSystem(&Win32OperationSystem) == S_OK)


	return nRet;
}

int CSystemCommand::QueryWMIComputerSystemInformation(CCommand * pCmd)
{
	int nRet = S_OK;

	pCmd->SetCommand((DWORD)CMD_ANSWER_WMI_COMPUTER_SYSTEM_INFORMATION);
	pCmd->AddPara((DWORD)S_OK);

	CWMIComputerSystem wmi;
	CWMIComputerSystem::COMPUTER_SYSTEM_INFORMATION info;
	if(wmi.GetComputerSystemInformation(&info) == S_OK)
	{
		try
		{
			pCmd->AddPara(info.szCaption.c_str());
			pCmd->AddPara(info.szManufacturer.c_str());
			pCmd->AddPara(info.szModel.c_str());
			pCmd->AddPara(info.szSystemType.c_str());
			pCmd->AddPara(info.szDomain.c_str());
			pCmd->AddPara(info.szUserName.c_str());
			pCmd->AddPara(info.szBootupState.c_str());
			pCmd->AddPara(info.szInitialLoadInfo.c_str());
			pCmd->AddPara(info.szLastLoadInfo.c_str());
			pCmd->AddPara(info.szName.c_str());
			pCmd->AddPara(info.szNameFormat.c_str());
			pCmd->AddPara(info.szPrimaryOwnerContact.c_str());
			pCmd->AddPara(info.szPrimaryOwnerName.c_str());
			pCmd->AddPara(info.szWorkgroup.c_str());
		}
		catch (CTException* e)
		{
			nRet = S_FALSE;
			TRACE(_T("异常:%s"), e->what());
		}
	}
	else
	{
		nRet = S_FALSE; 
	}// 结束 if(wmi.GetComputerSystemInformation(&info) == S_OK)

	return nRet;
}

int CSystemCommand::QueryWMIServiceInformation(CCommand * pCmd)
{
	int nRet = S_OK;

	pCmd->SetCommand((DWORD)CMD_ANSWER_WMI_SERVICE_INFORMATION);
	pCmd->AddPara((DWORD)S_OK);

	CWMIServiceInfo wmi;
	vector<CWMIServiceInfo::WMI_SERVICE_INFO> info;
	if(S_OK == wmi.GetServiceInformation(&info))
	{
		try
		{
			DWORD dwCount = info.size();
			pCmd->AddPara(dwCount);
			int i = 0;
			for(i = 0; i < dwCount; i++)
			{
				CWMIServiceInfo::PWMI_SERVICE_INFO pinfo;
				pinfo = &info[i];
				pCmd->AddPara(pinfo->szDisplayName.c_str());
				pCmd->AddPara(pinfo->szDescription.c_str());
				pCmd->AddPara(pinfo->szCaption.c_str());
				pCmd->AddPara(pinfo->szName.c_str());
				pCmd->AddPara(pinfo->szPathName.c_str());
				pCmd->AddPara(pinfo->szServiceType.c_str());
				pCmd->AddPara(pinfo->ProcessId);
				pCmd->AddPara(pinfo->szStartMode.c_str());
				pCmd->AddPara(pinfo->szStartName.c_str());
				pCmd->AddPara(pinfo->szState.c_str());
				pCmd->AddPara(pinfo->szSystemName.c_str());
				pCmd->AddPara(pinfo->szErrorControl.c_str());
				pCmd->AddPara(pinfo->bAcceptPause);
				pCmd->AddPara(pinfo->bAcceptStop);
			} // 结束 for(i = 0; i < dwCount; i++)
		}
		catch (CTException* e)
		{
			nRet = S_FALSE;
			TRACE(_T("异常:%s"), e->what());
		}
	} // 结束 if(S_OK == wmi.GetServiceInformation(&info))
	return nRet;
}