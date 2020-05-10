#include "HookProcess.h"
#include "FilterSys.h"

//
// Is process hooked?
//
BOOLEAN g_ProcessHooked = FALSE;

ARRAYHEAD g_ProtectProcessNameHead;

/*!
\brief   HookZwQuerySystemInformation
\param   IN ULONG SystemInformationClass ：
\param   IN PVOID SystemInformation      ：
\param   IN ULONG SystemInformationLength：
\param   OUT PULONG ReturnLength         ：
\return  类型为 NTSTATUS 。
\version 1.0
\author  康  林
\date    2007-6-11 14:17:28
*/
NTSTATUS HookZwQuerySystemInformation( 
		IN ULONG SystemInformationClass, 
		IN PVOID SystemInformation, 
		IN ULONG SystemInformationLength, 
		OUT PULONG ReturnLength)
{
	NTSTATUS status = STATUS_SUCCESS;
	char * pcNext = (char * )SystemInformation;
	PSYSTEM_PROCESSES pCur = SystemInformation;
	PSYSTEM_PROCESSES pPre = SystemInformation;
	int nLen = 0;
	BOOLEAN bDisable = FALSE;

	ASSERT(SystemInformation);
	if(NULL == SystemInformation)
	{
		return STATUS_INVALID_PARAMETER;
	} // 结束 if(NULL == SystemInformation)

	status = (RealZwQuerySystemInformation)(
		SystemInformationClass, 
		SystemInformation, 
		SystemInformationLength, 
		ReturnLength);
	if(!NT_SUCCESS(status))
	{
		return status;
	} // 结束 if(!NT_SUCESS(status))
	if(5 != SystemInformationClass)
	{
		return status;
	} // 结束 if(5 != SystemInformationClass)

	do
	{
		pCur = (PSYSTEM_PROCESSES)pcNext;

		// Proccess
		if(IsProtect(&pCur->ProcessName, &g_ProtectProcessNameHead, CompareCallBack))
		{
			bDisable = TRUE;
			if(pCur->NextEntryDelta)
			{
				// 如果是第一个
				if(pCur == SystemInformation)
				{
					PSYSTEM_PROCESSES pNext;
					pcNext = (char * )pCur;
					pNext = (PSYSTEM_PROCESSES)(pcNext + pCur->NextEntryDelta);

					// 设置下一项地址 
					if(0 != pNext->NextEntryDelta)
					{
						pNext->NextEntryDelta += pCur->NextEntryDelta;

						// 移动数据
						MoveBuffer(pCur, pNext, sizeof(SYSTEM_PROCESSES));
						MoveBuffer(pCur->Threads, pNext->Threads, pNext->ThreadCount * sizeof(SYSTEM_THREADS));

					}
					else
					{
						pCur->NextEntryDelta = 0;
						status = STATUS_NO_MORE_ENTRIES;
					}// 结束 if(0 != pNext->NextEntryOffset)

					continue;

				}// 结束 if(pCur == SystemInformation)

				pPre->NextEntryDelta += pCur->NextEntryDelta;
			}
			else
			{
				// 如果是第一个
				if(pCur == SystemInformation)
				{
					status = STATUS_NO_MORE_ENTRIES;
				}
				else
				{
					pPre->NextEntryDelta = 0;
				} // 结束 if(pCur == SystemInformation)
			}// 结束 if(pCur->NextEntryDelta)
		}
		else
		{
			bDisable = FALSE;
		}// 结束 if(IsProtect(&pCur->ProcessName, &g_ProtectProcessNameHead, CompareCallBack))

		// next
		if(pCur->NextEntryDelta)
		{
			pcNext = (char * )pCur;
			pcNext += pCur->NextEntryDelta;
			if(!bDisable)
			{
				pPre = pCur;
			} // 结束 if(!bDisable)
		}// 结束 if(pCur->NextEntryDelta)
	}
	while(pCur->NextEntryDelta && NT_SUCCESS(status));


	return status;
}

/*!
\brief   Hook Process
\param   无
\return  类型为 VOID 。
\version 1.0
\author  康  林
\date    2007-6-11 14:16:58
*/
VOID HookProcess()
{
	if(!g_ProcessHooked)
	{
		RealZwQuerySystemInformation = SYSCALL(ZwQuerySystemInformation);
		SYSCALL(ZwQuerySystemInformation) = (PVOID)HookZwQuerySystemInformation;
		g_ProcessHooked = TRUE;
	} // 结束 if(!g_ProcessHooked)
}

/*!
\brief   UnHook Process
\param   无
\return  类型为 VOID 。
\version 1.0
\author  康  林
\date    2007-6-11 14:17:01
*/
VOID UnHookProcess()
{
	if(g_ProcessHooked)
	{
		SYSCALL(ZwQuerySystemInformation) = (PVOID)RealZwQuerySystemInformation;
		g_ProcessHooked = FALSE;
	} // 结束 if(g_ProcessHooked)
}