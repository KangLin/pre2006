/*!
\warning 版权所有 (C) 2007 康林工作室；保留所有权利。
\file    ProcessInformation.cpp
\brief   得到进程信息类实现文件
\version 1.0
\author  康  林 (kl222@126.com)
\date    2007年8月15日  16:48:45
\par     编译器:
         Microsoft Visual Studio 8.0 —— C/C++ 8.0
*/


#include "stdafx.h"
#include "ProcessInformation.h"
#include "..\..\..\System\Process\ToolHelp.h"

CProcessInformation::CProcessInformation()
{

}

CProcessInformation::~CProcessInformation()
{

}

/*******************************************************************************************************
函数名：GetProcessName
描  述：得到指定进程的模块名
参  数：
        DWORD dwPID：进程ID
返回值：类型为 _tstring 。进程名
版  本：1.0.0.1
作  者：康  林
时  间：2007年8月15日 23:03:50
*******************************************************************************************************/
_tstring CProcessInformation::GetProcessName(DWORD dwPID)
{
	PROCESSENTRY32 pe;
	pe.dwSize = sizeof(pe);
	CToolHelp toolHelp(TH32CS_SNAPALL, dwPID);
	if(toolHelp.ProcessFind(dwPID, &pe))
	{
		_tstring szTemp = pe.szExeFile;
		return szTemp;
	}// 结束 if(toolHelp.ProcessFind(dwPID, &pe))
	return _tstring();
}

/*******************************************************************************************************
函数名：GetProcessPath
描  述：得到指定进程的全路径
参  数：
        DWORD dwPID：进程的ID
返回值：类型为 _tstring 。进程全路径
版  本：1.0.0.1
作  者：康  林
时  间：2007年8月15日 23:03:31
*******************************************************************************************************/
_tstring CProcessInformation::GetProcessPath(DWORD dwPID)
{
	PROCESSENTRY32 pe;
	pe.dwSize = sizeof(pe);
	CToolHelp toolHelp(TH32CS_SNAPALL, dwPID);
	if(toolHelp.ProcessFind(dwPID, &pe))
	{
		MODULEENTRY32 me;
		me.dwSize = sizeof(MODULEENTRY32);
		if(toolHelp.ModuleFind(pe.szExeFile, &me))
		{
			_tstring szTemp = me.szExePath;
			return szTemp;
		} // 结束 if(toolHelp.ModuleFind(pe.szExeFile, &me))
	} // 结束 if(toolHelp.ProcessFind(dwPID, &pe))
	return _tstring();
}

/*******************************************************************************************************
函数名：GetProcessModuleInfo
描  述：得到指定进程（包括模块）所有信息
参  数：
        DWORD dwPID                                   ：要查询进程的ID
		CProcessInfomation::PPROCESS_MODULE_INFO pInfo：
返回值：类型为 int 。成功返回S_OK，否则返回S_FAILE。
版  本：1.0.0.1
作  者：康  林
时  间：2007年8月15日 23:02:47
*******************************************************************************************************/
int CProcessInformation::GetProcessModuleInfo(DWORD dwPID, CProcessInformation::PPROCESS_MODULE_INFO pInfo)
{
	int nRet = S_OK;
	try
	{
		PROCESSENTRY32 pe;
		pe.dwSize = sizeof(pe);

		CToolHelp::EnableDebugPrivilege();

		CToolHelp toolHelp(TH32CS_SNAPALL, dwPID);
		if(toolHelp.ProcessFind(dwPID, &pe))
		{
			BOOL fOk = FALSE;
			MODULEENTRY32 me;
			me.dwSize = sizeof(MODULEENTRY32);
			for(fOk = toolHelp.ModuleFirst(&me); fOk; fOk = toolHelp.ModuleNext(&me))
			{
				MODULEINFO Module;
				Module.szModuleName = me.szModule;
				Module.dwGlbUsege = me.GlblcntUsage;
				Module.dwProcUsage = me.ProccntUsage;
				Module.dwBaseAddr = me.modBaseAddr;
				Module.dwSize = me.modBaseSize;
				Module.szExePath = me.szExePath;
				pInfo->Module.push_back(Module);
			} // 结束 for(fOk = toolHelp.ModuleFirst(&me); fOk; fOk = toolHelp.ModuleNext(&me))

			pInfo->szProcessName = pe.szExeFile;
			pInfo->dwProcessID = pe.th32ProcessID;
			pInfo->dwParentID = pe.th32ParentProcessID;
			pInfo->dwPriority = pe.pcPriClassBase;
			pInfo->dwUsage = pe.cntUsage;
			pInfo->dwThreadCount = pe.cntThreads;
			pInfo->dwModuleCount = pInfo->Module.size();
		}
		else
		{
			nRet = S_FALSE; 
		}// 结束 if(toolHelp.ProcessFind(dwPID, &pe))
	}
	catch (...)
	{
		nRet = S_FALSE;
	}

	CToolHelp::EnableDebugPrivilege(FALSE);

	return nRet;
}

/*******************************************************************************************************
函数名：GetAllProcessModuleInfo
描  述：得到所有进程（包括模块）的信息
参  数：
        std::vector<PROCESS_MODULE_INFO>*pInfo：
返回值：类型为 int 。成功返回S_OK，否则返回S_FAILE。
版  本：1.0.0.1
作  者：康  林
时  间：2007年8月15日 23:00:17
*******************************************************************************************************/
int CProcessInformation::GetAllProcessModuleInfo(std::vector<PROCESS_MODULE_INFO> *pInfo)
{
	int nRet = S_OK;

	CToolHelp toolHelp(TH32CS_SNAPPROCESS);
	PROCESSENTRY32 pe;
	pe.dwSize = sizeof(pe);
	BOOL fOk = FALSE;
	for(fOk = toolHelp.ProcessFirst(&pe); fOk; fOk = toolHelp.ProcessNext(&pe))
	{
		PROCESS_MODULE_INFO Info;
		if(GetProcessModuleInfo(pe.th32ProcessID, &Info) == S_OK)
		{
			pInfo->push_back(Info);
		} // 结束 if(GetProcessInfo(pe.th32ProcessID, &Info) == S_OK)
	} // 结束 for(fOk = toolHelp.ProcessFirst(&pe); fOk; fOk = toolHelp.ProcessNext(&pe))
	return nRet;
}

/*******************************************************************************************************
函数名：GetProcessInfo
描  述：得到指定进程信息
参  数：
        DWORD dwPID                            ：指定的进程的ID
		CProcessInfomation::PPROCESS_INFO pInfo：
返回值：类型为 int 。成功返回S_OK，否则返回S_FAILE。
版  本：1.0.0.1
作  者：康  林
时  间：2007年8月15日 23:31:23
*******************************************************************************************************/
int CProcessInformation::GetProcessInfo(DWORD dwPID, CProcessInformation::PPROCESS_INFO pInfo)
{
	int nRet = S_OK;
	try
	{
		PROCESSENTRY32 pe;
		pe.dwSize = sizeof(pe);

		CToolHelp::EnableDebugPrivilege();

		CToolHelp toolHelp(TH32CS_SNAPALL, dwPID);
		if(toolHelp.ProcessFind(dwPID, &pe))
		{
			pInfo->szProcessName = pe.szExeFile;

			MODULEENTRY32 me;
			me.dwSize = sizeof(MODULEENTRY32);
			if(toolHelp.ModuleFind(pe.szExeFile, &me))
			{
				pInfo->szProcessPath = me.szExePath;
			} // 结束 (toolHelp.ModuleFind(pe.szExeFile, &me))
			pInfo->dwProcessID = pe.th32ProcessID;
			pInfo->dwParentID = pe.th32ParentProcessID;
			pInfo->dwPriority = pe.pcPriClassBase;
			pInfo->dwUsage = pe.cntUsage;
			pInfo->dwThreadCount = pe.cntThreads;
		}
		else
		{
			nRet = S_FALSE;
		}// 结束 if(toolHelp.ProcessFind(dwPID, &pe))
	}
	catch (...)
	{
		nRet = S_FALSE;
	}

	CToolHelp::EnableDebugPrivilege(FALSE);
	return nRet;
}

/*******************************************************************************************************
函数名：GetAllProcessInfo
描  述：得到所有进程信息
参  数：
        vector< PROCESS_INFO >*pInfo：
返回值：类型为 int 。成功返回S_OK，否则返回S_FAILE。
版  本：1.0.0.1
作  者：康  林
时  间：2007年8月15日 23:32:02
*******************************************************************************************************/
int CProcessInformation::GetAllProcessInfo(vector < PROCESS_INFO > *pInfo)
{
	int nRet = S_OK;

	CToolHelp toolHelp(TH32CS_SNAPPROCESS);
	PROCESSENTRY32 pe;
	pe.dwSize = sizeof(pe);
	BOOL fOk = FALSE;
	for(fOk = toolHelp.ProcessFirst(&pe); fOk; fOk = toolHelp.ProcessNext(&pe))
	{
		PROCESS_INFO Info;
		if(GetProcessInfo(pe.th32ProcessID, &Info) == S_OK)
		{
			pInfo->push_back(Info);
		} // 结束 if(GetProcessInfo(pe.th32ProcessID, &Info) == S_OK)
	}// 结束 for(fOk = toolHelp.ProcessFirst(&pe); fOk; fOk = toolHelp.ProcessNext(&pe))

	return nRet;
}