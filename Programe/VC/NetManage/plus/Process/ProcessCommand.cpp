#include "StdAfx.h"
#include "ProcessCommand.h"
#include "ProcessInformation.h"

CProcessCommand::CProcessCommand(void)
{
	m_pCmd = NULL;
}

CProcessCommand::CProcessCommand(CCommand * pCmd)
{
	m_pCmd = pCmd;
}

CProcessCommand::~CProcessCommand(void)
{
}

int CProcessCommand::QueryAllProcess(CCommand* pCmd)
{
	int nRet = S_OK;

	ASSERT(m_pCmd && pCmd);

	pCmd->SetCommand(CMD_ANSWER_ALL_PROCESS);
	pCmd->AddPara((DWORD)S_OK);

	vector<CProcessInformation::PROCESS_INFO> info;
	CProcessInformation pi;
	if(pi.GetAllProcessInfo(&info) == S_OK)
	{
		pCmd->AddPara((DWORD)info.size());

		vector<CProcessInformation::PROCESS_INFO>::iterator it;
		for(it = info.begin(); it != info.end(); it++)
		{
			CProcessInformation::PROCESS_INFO *pInfo;
			pInfo = &(*it);
			try
			{
				pCmd->AddPara(pInfo->szProcessName.c_str());
				pCmd->AddPara(pInfo->szProcessPath.c_str());
				pCmd->AddPara(pInfo->dwProcessID);
				pCmd->AddPara(pInfo->dwParentID);
				pCmd->AddPara(pInfo->dwPriority);
				pCmd->AddPara(pInfo->dwUsage);
				pCmd->AddPara(pInfo->dwThreadCount);
			}
			catch(CTException e)
			{
				TRACE(_T("异常：%s\n"), e.what());
				nRet = S_FALSE;
				break;
			}
		} // 结束 for(it = info.begin(); it != info.end(); it++)
	} // 结束 if(pi.GetAllProcessInfo(&info) == S_OK)
	return nRet;
}

int CProcessCommand::AnswerAllProcess(vector<CProcessInformation::PROCESS_INFO> *pInfo)
{
	int nRet = S_OK;
	ASSERT(m_pCmd && pInfo);
	DWORD dwErr = S_FALSE;
	DWORD dwCount = 0;
	try
	{
		m_pCmd->GetPara(&dwErr);
		if(S_OK != dwErr)
		{
			return dwErr;
		}// 结束 if(S_OK != dwErr)
		m_pCmd->GetPara(&dwCount);
		while(dwCount--)
		{
			CProcessInformation::PROCESS_INFO info;
			m_pCmd->GetPara(&info.szProcessName);
			m_pCmd->GetPara(&info.szProcessPath);
			m_pCmd->GetPara(&info.dwProcessID);
			m_pCmd->GetPara(&info.dwParentID);
			m_pCmd->GetPara(&info.dwPriority);
			m_pCmd->GetPara(&info.dwUsage);
			m_pCmd->GetPara(&info.dwThreadCount);
			pInfo->push_back(info);
		} // 结束 while(dwCount--)
	}
	catch (CTException* e)
	{
		TRACE(_T("异常:%s\n"), e->what());
		nRet = S_FALSE;
	}

	return nRet;
}

int CProcessCommand::QueryAllProcessModule(CCommand* pCmd)
{
	int nRet = S_OK;

	ASSERT(m_pCmd && pCmd);

	pCmd->SetCommand(CMD_ANSWER_ALL_PROCESS_MODULE);
	pCmd->AddPara((DWORD)S_OK);

	CProcessInformation pi;
	vector < CProcessInformation::PROCESS_MODULE_INFO > Info;
	pi.GetAllProcessModuleInfo(&Info);
	try
	{
		pCmd->AddPara((DWORD)Info.size());
		vector<CProcessInformation::PROCESS_MODULE_INFO>::iterator it;
		for(it = Info.begin(); it != Info.end(); it++)
		{
			CProcessInformation::PROCESS_MODULE_INFO * pInfo;
			pInfo = &(*it);
			pCmd->AddPara(pInfo->szProcessName.c_str());
			pCmd->AddPara(pInfo->dwProcessID);
			pCmd->AddPara(pInfo->dwParentID);
			pCmd->AddPara(pInfo->dwPriority);
			pCmd->AddPara(pInfo->dwUsage);
			pCmd->AddPara(pInfo->dwThreadCount);
			pCmd->AddPara((DWORD)pInfo->Module.size());
			vector<CProcessInformation::MODULEINFO>::iterator itModule;
			for(itModule = pInfo->Module.begin(); itModule != pInfo->Module.end(); itModule++)
			{
				CProcessInformation::PMODULEINFO pModule;
				pModule = &(*itModule);
				pCmd->AddPara(pModule->szModuleName.c_str());
				pCmd->AddPara(pModule->dwGlbUsege);
				pCmd->AddPara(pModule->dwProcUsage);
				pCmd->AddPara((DWORD)pModule->dwBaseAddr);
				pCmd->AddPara(pModule->dwSize);
				pCmd->AddPara(pModule->szExePath.c_str());
			} // 结束 for(itModule = pInfo->Module.begin(); itModule != pInfo->Module.end(); itModule++)
		} // 结束 for(it = Info.begin(); it != Info.end(); it++)
	}
	catch(CTException e)
	{
		TRACE(_T("异常：%s\n"), e.what());
		nRet = S_FALSE;
	}

	return nRet;
}

int CProcessCommand::AnswerAllProcessModule(vector<CProcessInformation::PROCESS_MODULE_INFO> *pInfo)
{
	int nRet = S_OK;
	DWORD dwErr = S_OK;
	try
	{
		m_pCmd->GetPara(&dwErr);
		if(S_OK != dwErr)
		{
			return dwErr;
		}// 结束 if(S_OK != dwErr)
		DWORD dwCount = 0;
		m_pCmd->GetPara(&dwCount);
		while(dwCount--)
		{
			CProcessInformation::PROCESS_MODULE_INFO info;
			m_pCmd->GetPara(&info.szProcessName);
			m_pCmd->GetPara(&info.dwProcessID);
			m_pCmd->GetPara(&info.dwParentID);
			m_pCmd->GetPara(&info.dwPriority);
			m_pCmd->GetPara(&info.dwUsage);
			m_pCmd->GetPara(&info.dwThreadCount);
			DWORD dwModuleCount = 0;
			m_pCmd->GetPara(&dwModuleCount);
			info.dwModuleCount = dwModuleCount;
			while(dwModuleCount--)
			{
				CProcessInformation::MODULEINFO moduleInfo;
				m_pCmd->GetPara(&moduleInfo.szModuleName);
				m_pCmd->GetPara(&moduleInfo.dwGlbUsege);
				m_pCmd->GetPara(&moduleInfo.dwProcUsage);
				m_pCmd->GetPara((DWORD * )&moduleInfo.dwBaseAddr);
				m_pCmd->GetPara(&moduleInfo.dwSize);
				m_pCmd->GetPara(&moduleInfo.szExePath);
				info.Module.push_back(moduleInfo);
			} // 结束 while(dwModuleCount--)
			pInfo->push_back(info);
		} // 结束 while(dwCount--)
	}
	catch(CTException e)
	{
		TRACE(_T("异常：%s\n"), e.what());
		nRet = S_FALSE;
	}
	
	return nRet;
}

int CProcessCommand::QueryProcess(CCommand* pCmd)
{
	int nRet = S_FALSE;

	ASSERT(m_pCmd && pCmd);

	pCmd->SetCommand(CMD_ANSWER_PROCESS);
	pCmd->AddPara((DWORD)S_OK);

	CProcessInformation pi;
	CProcessInformation::PROCESS_INFO info;
	DWORD dwID = 0;
	
	if(S_OK == m_pCmd->GetPara(&dwID))
	{
		if(S_OK == pi.GetProcessInfo(dwID, &info))
		{
			try
			{		
				pCmd->AddPara(info.szProcessName.c_str());
				pCmd->AddPara(info.szProcessPath.c_str());
				pCmd->AddPara(info.dwProcessID);
				pCmd->AddPara(info.dwParentID);
				pCmd->AddPara(info.dwPriority);
				pCmd->AddPara(info.dwUsage);
				pCmd->AddPara(info.dwThreadCount);
			}
			catch(CTException e)
			{
				TRACE(_T("异常：%s\n"), e.what());
				nRet = S_FALSE;
			}					
		}// 结束 if(S_OK == pi.GetProcessInfo(dwID, &info))
	} // 结束 if(S_OK == m_pCmd->GetPara(&dwID))

	return nRet;
}

int CProcessCommand::QueryProcessModule(CCommand* pCmd)
{
	int nRet = S_OK;

	return nRet;
}

int CProcessCommand::QueryProcessName(CCommand* pCmd)
{
	int nRet = S_OK;

	return nRet;
}

int CProcessCommand::QueryProcessPath(CCommand* pCmd)
{
	int nRet = S_OK;

	return nRet;
}