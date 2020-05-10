#include "HookProcess.h"
#include "FilterSys.h"

//
// Is process hooked?
//
BOOLEAN g_ProcessHooked = FALSE;

ARRAYHEAD g_ProtectProcessNameHead;

/*!
\brief   HookZwQuerySystemInformation
\param   IN ULONG SystemInformationClass ��
\param   IN PVOID SystemInformation      ��
\param   IN ULONG SystemInformationLength��
\param   OUT PULONG ReturnLength         ��
\return  ����Ϊ NTSTATUS ��
\version 1.0
\author  ��  ��
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
	} // ���� if(NULL == SystemInformation)

	status = (RealZwQuerySystemInformation)(
		SystemInformationClass, 
		SystemInformation, 
		SystemInformationLength, 
		ReturnLength);
	if(!NT_SUCCESS(status))
	{
		return status;
	} // ���� if(!NT_SUCESS(status))
	if(5 != SystemInformationClass)
	{
		return status;
	} // ���� if(5 != SystemInformationClass)

	do
	{
		pCur = (PSYSTEM_PROCESSES)pcNext;

		// Proccess
		if(IsProtect(&pCur->ProcessName, &g_ProtectProcessNameHead, CompareCallBack))
		{
			bDisable = TRUE;
			if(pCur->NextEntryDelta)
			{
				// ����ǵ�һ��
				if(pCur == SystemInformation)
				{
					PSYSTEM_PROCESSES pNext;
					pcNext = (char * )pCur;
					pNext = (PSYSTEM_PROCESSES)(pcNext + pCur->NextEntryDelta);

					// ������һ���ַ 
					if(0 != pNext->NextEntryDelta)
					{
						pNext->NextEntryDelta += pCur->NextEntryDelta;

						// �ƶ�����
						MoveBuffer(pCur, pNext, sizeof(SYSTEM_PROCESSES));
						MoveBuffer(pCur->Threads, pNext->Threads, pNext->ThreadCount * sizeof(SYSTEM_THREADS));

					}
					else
					{
						pCur->NextEntryDelta = 0;
						status = STATUS_NO_MORE_ENTRIES;
					}// ���� if(0 != pNext->NextEntryOffset)

					continue;

				}// ���� if(pCur == SystemInformation)

				pPre->NextEntryDelta += pCur->NextEntryDelta;
			}
			else
			{
				// ����ǵ�һ��
				if(pCur == SystemInformation)
				{
					status = STATUS_NO_MORE_ENTRIES;
				}
				else
				{
					pPre->NextEntryDelta = 0;
				} // ���� if(pCur == SystemInformation)
			}// ���� if(pCur->NextEntryDelta)
		}
		else
		{
			bDisable = FALSE;
		}// ���� if(IsProtect(&pCur->ProcessName, &g_ProtectProcessNameHead, CompareCallBack))

		// next
		if(pCur->NextEntryDelta)
		{
			pcNext = (char * )pCur;
			pcNext += pCur->NextEntryDelta;
			if(!bDisable)
			{
				pPre = pCur;
			} // ���� if(!bDisable)
		}// ���� if(pCur->NextEntryDelta)
	}
	while(pCur->NextEntryDelta && NT_SUCCESS(status));


	return status;
}

/*!
\brief   Hook Process
\param   ��
\return  ����Ϊ VOID ��
\version 1.0
\author  ��  ��
\date    2007-6-11 14:16:58
*/
VOID HookProcess()
{
	if(!g_ProcessHooked)
	{
		RealZwQuerySystemInformation = SYSCALL(ZwQuerySystemInformation);
		SYSCALL(ZwQuerySystemInformation) = (PVOID)HookZwQuerySystemInformation;
		g_ProcessHooked = TRUE;
	} // ���� if(!g_ProcessHooked)
}

/*!
\brief   UnHook Process
\param   ��
\return  ����Ϊ VOID ��
\version 1.0
\author  ��  ��
\date    2007-6-11 14:17:01
*/
VOID UnHookProcess()
{
	if(g_ProcessHooked)
	{
		SYSCALL(ZwQuerySystemInformation) = (PVOID)RealZwQuerySystemInformation;
		g_ProcessHooked = FALSE;
	} // ���� if(g_ProcessHooked)
}