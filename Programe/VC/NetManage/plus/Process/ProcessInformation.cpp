/*!
\warning ��Ȩ���� (C) 2007 ���ֹ����ң���������Ȩ����
\file    ProcessInformation.cpp
\brief   �õ�������Ϣ��ʵ���ļ�
\version 1.0
\author  ��  �� (kl222@126.com)
\date    2007��8��15��  16:48:45
\par     ������:
         Microsoft Visual Studio 8.0 ���� C/C++ 8.0
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
��������GetProcessName
��  �����õ�ָ�����̵�ģ����
��  ����
        DWORD dwPID������ID
����ֵ������Ϊ _tstring ��������
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2007��8��15�� 23:03:50
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
	}// ���� if(toolHelp.ProcessFind(dwPID, &pe))
	return _tstring();
}

/*******************************************************************************************************
��������GetProcessPath
��  �����õ�ָ�����̵�ȫ·��
��  ����
        DWORD dwPID�����̵�ID
����ֵ������Ϊ _tstring ������ȫ·��
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2007��8��15�� 23:03:31
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
		} // ���� if(toolHelp.ModuleFind(pe.szExeFile, &me))
	} // ���� if(toolHelp.ProcessFind(dwPID, &pe))
	return _tstring();
}

/*******************************************************************************************************
��������GetProcessModuleInfo
��  �����õ�ָ�����̣�����ģ�飩������Ϣ
��  ����
        DWORD dwPID                                   ��Ҫ��ѯ���̵�ID
		CProcessInfomation::PPROCESS_MODULE_INFO pInfo��
����ֵ������Ϊ int ���ɹ�����S_OK�����򷵻�S_FAILE��
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2007��8��15�� 23:02:47
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
			} // ���� for(fOk = toolHelp.ModuleFirst(&me); fOk; fOk = toolHelp.ModuleNext(&me))

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
		}// ���� if(toolHelp.ProcessFind(dwPID, &pe))
	}
	catch (...)
	{
		nRet = S_FALSE;
	}

	CToolHelp::EnableDebugPrivilege(FALSE);

	return nRet;
}

/*******************************************************************************************************
��������GetAllProcessModuleInfo
��  �����õ����н��̣�����ģ�飩����Ϣ
��  ����
        std::vector<PROCESS_MODULE_INFO>*pInfo��
����ֵ������Ϊ int ���ɹ�����S_OK�����򷵻�S_FAILE��
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2007��8��15�� 23:00:17
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
		} // ���� if(GetProcessInfo(pe.th32ProcessID, &Info) == S_OK)
	} // ���� for(fOk = toolHelp.ProcessFirst(&pe); fOk; fOk = toolHelp.ProcessNext(&pe))
	return nRet;
}

/*******************************************************************************************************
��������GetProcessInfo
��  �����õ�ָ��������Ϣ
��  ����
        DWORD dwPID                            ��ָ���Ľ��̵�ID
		CProcessInfomation::PPROCESS_INFO pInfo��
����ֵ������Ϊ int ���ɹ�����S_OK�����򷵻�S_FAILE��
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2007��8��15�� 23:31:23
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
			} // ���� (toolHelp.ModuleFind(pe.szExeFile, &me))
			pInfo->dwProcessID = pe.th32ProcessID;
			pInfo->dwParentID = pe.th32ParentProcessID;
			pInfo->dwPriority = pe.pcPriClassBase;
			pInfo->dwUsage = pe.cntUsage;
			pInfo->dwThreadCount = pe.cntThreads;
		}
		else
		{
			nRet = S_FALSE;
		}// ���� if(toolHelp.ProcessFind(dwPID, &pe))
	}
	catch (...)
	{
		nRet = S_FALSE;
	}

	CToolHelp::EnableDebugPrivilege(FALSE);
	return nRet;
}

/*******************************************************************************************************
��������GetAllProcessInfo
��  �����õ����н�����Ϣ
��  ����
        vector< PROCESS_INFO >*pInfo��
����ֵ������Ϊ int ���ɹ�����S_OK�����򷵻�S_FAILE��
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2007��8��15�� 23:32:02
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
		} // ���� if(GetProcessInfo(pe.th32ProcessID, &Info) == S_OK)
	}// ���� for(fOk = toolHelp.ProcessFirst(&pe); fOk; fOk = toolHelp.ProcessNext(&pe))

	return nRet;
}