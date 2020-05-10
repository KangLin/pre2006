/*!
\warning ��Ȩ���� (C) 2007 ���ֹ����ң���������Ȩ����
\file    DirectoryControl.c
\brief   Implement directory control route.
\version 1.0
\author  ��  �� (kl222@126.com)
\date    2007��5��17��  13:32:42
\par     ������:
         Microsoft Visual Studio 8.0 ���� C/C++ 8.0
*/
#include "sfilter.h"
#include "Support.h"

//
// System service parameters for:  NtQueryDirectoryFile
//
typedef struct 
{
	ULONG Length;
	PUNICODE_STRING FileName;
	FILE_INFORMATION_CLASS FileInformationClass;
	ULONG POINTER_ALIGNMENT FileIndex;
} QUERYDIRECTORY, *PQUERYDIRECTORY;

NTSTATUS ShowFileBothDirectoryInformation(PFILE_BOTH_DIR_INFORMATION pFileBothDir)
{
	NTSTATUS status = STATUS_SUCCESS;
	char * pc = (char * )pFileBothDir;
	PFILE_BOTH_DIR_INFORMATION p = pFileBothDir;
	UNICODE_STRING fileName;
	
	ASSERT(pFileBothDir);
	if(NULL == pFileBothDir)
	{
		return STATUS_INVALID_PARAMETER;
	} // ���� if(NULL == pFileBothDir)

	do
	{
		p = (PFILE_BOTH_DIR_INFORMATION)pc;

		fileName.Length = (USHORT)p->FileNameLength;
		fileName.Buffer = p->FileName;
#ifdef DBG
		if(FlagOn(SFDEBUG_DIRECTORYCONTROL, SfDebug))
		{
			KdPrint(("KSFilter:SfDirectoryControl: FileName:%wZ\n", &fileName));
			fileName.Buffer = p->ShortName;
			fileName.Length = (USHORT)p->ShortNameLength;
			/*KdPrint(("KSFilter:SfDirectoryControl: FileNameLength:%d;shortfilenamelenght:%d;Ea:%d,PFILE_BOTH_DIR_INFORMATION:%d\n", p->FileNameLength, p->ShortNameLength,
				p->EaSize,sizeof(PFILE_BOTH_DIR_INFORMATION)));*/
			//KdPrint(("KSFilter:SfDirectoryControl: ShortFileName:%wZ\n", &fileName));
		}
#endif
		if(p->NextEntryOffset)
		{
			pc += p->NextEntryOffset;
		}// ���� if(p->NextEntryOffset)
	}
	while(p->NextEntryOffset);

	return status;

}

/*!
\brief   Process FileBothDirectoryInformation request, hide file.
\param   IN PFILE_BOTH_DIR_INFORMATION pFileBothDir��
\param   IN PUNICODE_STRING pPath                  ��
\return  ����Ϊ NTSTATUS ��
\version 1.0
\author  ��  ��
\date    2007-5-20 12:29:26
*/
NTSTATUS ProcessFileBothDirectoryInformation(
	IN PFILE_BOTH_DIR_INFORMATION pFileBothDir,
	IN PUNICODE_STRING pPath
	)
{
	NTSTATUS status = STATUS_SUCCESS;
	char * pcNext = (char * )pFileBothDir;
	PFILE_BOTH_DIR_INFORMATION p = pFileBothDir;
	PFILE_BOTH_DIR_INFORMATION pPre = pFileBothDir;
	UNICODE_STRING fileName, pathName;
	PWCHAR pBuf = NULL;
	PCHAR pCom = NULL;
	int nLen = 0;
	BOOLEAN bDisable = FALSE;
	
	ASSERT(pFileBothDir && pPath);
	if(NULL == pFileBothDir || NULL == pPath)
	{
		return STATUS_INVALID_PARAMETER;
	} // ���� if(NULL == pFileBothDir || NULL == pPath)

	do
	{
		p = (PFILE_BOTH_DIR_INFORMATION)pcNext;

		// get full path
		nLen = pPath->Length + p->FileNameLength + sizeof(L'\\') + sizeof(WCHAR);
		pBuf = AllocateBuffer(nLen);
		if(NULL == pBuf)
		{
			return STATUS_INSUFFICIENT_RESOURCES;
		}// ���� if(NULL == pBuf)

		// �õ���һ���ļ���
		RtlInitEmptyUnicodeString(&pathName, pBuf, nLen);
		RtlAppendUnicodeStringToString(&pathName, pPath);
		fileName.Length = (USHORT)p->FileNameLength;
		fileName.Buffer = p->FileName;
		pCom = ((PCHAR)pPath->Buffer) + pPath->Length - sizeof(L'\\');
		if(RtlCompareMemory(pCom, L"\\", sizeof(L'\\')) != sizeof(L'\\'))
		{
			RtlAppendUnicodeToString(&pathName, L"\\");
		} // ���� if(RtlCompareMemory(pCom, L"\\", sizeof(L'\\')) != sizeof(L'\\'))
		
		RtlAppendUnicodeStringToString(&pathName, &fileName);

#ifdef DBG
		if(FlagOn(SFDEBUG_DIRECTORYCONTROL, SfDebug))
		{
			KdPrint(("KSFilter:SfDirectoryControl: FileName:%wZ\n", &fileName));
		}
#endif
		// Proccess
		if(SfIsDisableDeleteFile(&pathName, CompareCallBack))
		{
			bDisable = TRUE;
			if(p->NextEntryOffset)
			{
				// ����ǵ�һ��
				if(p == pFileBothDir)
				{
					PFILE_BOTH_DIR_INFORMATION pNext;
					pcNext = (char * )p;
					pNext = (PFILE_BOTH_DIR_INFORMATION)(pcNext + p->NextEntryOffset);

					// ������һ���ַ 
					if(0 != pNext->NextEntryOffset)
					{
						pNext->NextEntryOffset += p->NextEntryOffset;

						// �ƶ�����
						MoveBuffer(p, pNext, sizeof(FILE_BOTH_DIR_INFORMATION));
						MoveBuffer(p->FileName, pNext->FileName, pNext->FileNameLength);

					}
					else
					{
						p->NextEntryOffset = 0;
						status = STATUS_NO_MORE_FILES;
					}// ���� if(0 != pNext->NextEntryOffset)

					// free buffer
					FreeBuffer(pBuf);

					continue;
				}// ���� if(p == pFileBothDir)

				pPre->NextEntryOffset += p->NextEntryOffset;
			}
			else
			{
				// ����ǵ�һ��
				if(p == pFileBothDir)
				{
					status = STATUS_NO_MORE_FILES; 
				}
				else
				{
					pPre->NextEntryOffset = 0;
				} // ���� if(p == pFileBothDir)
			}// ���� if(p->NextEntryOffset)
		}
		else
		{
			bDisable = FALSE;
		}// ���� if(SfIsDisableDeleteFile(&pathName, CompareCallBack))

		// free buffer
		FreeBuffer(pBuf);

		// next
		if(p->NextEntryOffset)
		{
			pcNext = (char * )p;
			pcNext += p->NextEntryOffset;
			if(!bDisable)
			{
				pPre = p;
			} // ���� if(!bDisable)
		}// ���� if(p->NextEntryOffset)
	} while(p->NextEntryOffset && NT_SUCCESS(status));

	return status;

}

/*!
\brief   Ŀ¼������ǲ����(IRP_MJ_DIRECTORY_CONTROL)
\param   IN PDEVICE_OBJECT DeviceObject��
\param   IN PIRP Irp                   ��
\return  ����Ϊ NTSTATUS ��
\version 1.0
\author  ��  ��
\date    2007-5-19 15:05:06
*/
NTSTATUS SfDirectoryControl(IN PDEVICE_OBJECT DeviceObject,
				IN PIRP Irp)
{
	NTSTATUS status = STATUS_SUCCESS;
	PIO_STACK_LOCATION pIrpSp = IoGetCurrentIrpStackLocation(Irp);
	PSFILTER_DEVICE_EXTENSION pExt = NULL;
	PFILE_BOTH_DIR_INFORMATION pFileBothDir = NULL;
	PQUERYDIRECTORY pQueryDir = NULL;
	PUNICODE_STRING pFileName = NULL;

	PAGED_CODE();

	ASSERT(!IS_MY_CONTROL_DEVICE_OBJECT(DeviceObject));
	ASSERT(IS_MY_DEVICE_OBJECT(DeviceObject));

	switch(pIrpSp->MinorFunction)
	{
	case IRP_MN_NOTIFY_CHANGE_DIRECTORY:
#ifdef DBG
		if(FlagOn(SFDEBUG_DIRECTORYCONTROL, SfDebug))
		{
			KdPrint(("KSFilter:->SfDirectoryControl:MinorFunction = IRP_MN_NOTIFY_CHANGE_DIRECTORY\n"));
		} // ���� while(p->NextEntryOffset)
#endif

		break;
	case IRP_MN_QUERY_DIRECTORY :
		status = GetFullPath(DeviceObject, Irp, &pFileName);
		if(!NT_SUCCESS(status))
		{
			break;
		}// ���� if(NT_SUCCESS(status))

		pQueryDir = (PQUERYDIRECTORY)&pIrpSp->Parameters.QueryDirectory;

#ifdef DBG
		if(FlagOn(SFDEBUG_DIRECTORYCONTROL, SfDebug))
		{
			KdPrint(("KSFilter:SfDirectoryControl:MinorFunction = IRP_MN_QUERY_DIRECTORY\n"));
			KdPrint(("KSFilter:SfDirectoryControl: pIrpSp->FileObject->FileName:%wZ\n", &pIrpSp->FileObject->FileName));
			KdPrint(("KSFilter:SfDirectoryControl: pIrpSp->FileObject->FileName:%wZ\n", pQueryDir->FileName));
			KdPrint(("KSFilter:SfDirectoryControl:pIrpSp->Parameters.QueryDirectory.FileInformationClass = %d\n", pIrpSp->Parameters.QueryDirectory.FileInformationClass));
		} // ���� (FlagOn(SFDEBUG_DIRECTORYCONTROL, SfDebug))
#endif
	
		{
			pExt = (PSFILTER_DEVICE_EXTENSION)DeviceObject->DeviceExtension;
			status = SetCompletionRoutine(pExt->AttachedToDeviceObject, Irp);

#ifdef DBG
			if(FlagOn(SFDEBUG_DIRECTORYCONTROL, SfDebug))
			{
				KdPrint(("KSFitler:SfDirectoryControl:status:%d\n", status));
				KdPrint(("KSFitler:Irp->IoStatus.Information:%d\n", Irp->IoStatus.Information));
			} // ���� (FlagOn(SFDEBUG_DIRECTORYCONTROL, SfDebug))
#endif

			//
			//  Process Retrieve
			//
			if(NT_SUCCESS(status) && NT_SUCCESS(Irp->IoStatus.Status))
			{
				switch(pQueryDir->FileInformationClass)
				{
				case FileBothDirectoryInformation:
					pFileBothDir = Irp->UserBuffer;
					if(NULL != pFileBothDir || pFileBothDir->NextEntryOffset < pQueryDir->Length)
					{
						while((status = ProcessFileBothDirectoryInformation(pFileBothDir, pFileName)) == STATUS_NO_MORE_FILES)
						{
							status = SetCompletionRoutine(pExt->AttachedToDeviceObject, Irp);
							
							if(!NT_SUCCESS(status) || (0 == Irp->IoStatus.Information))
							{
								break;
							}
						} // ���� while((status = ProcessFileBothDirectoryInformation(pFileBothDir, pFileName)) == STATUS_NO_MORE_FILES)
					}// ���� if(NULL != pFileBothDir || pFileBothDir->NextEntryOffset < pQueryDir->Length)

				default:
					break;
				}// ���� switch(pIrpSp->Parameters.QueryDirectory.FileInformationClass)
			} // ���� if(NT_SUCCESS(status) && NT_SUCCESS(Irp->IoStatus.Status))

			// Free buffer
			if(pFileName)
			{
				FreeUnicodeBuffer(pFileName);
			}// ���� if(pFileName)

			//
			// continue processing the IRP
			//
#ifdef DBG
			if(FlagOn(SFDEBUG_DIRECTORYCONTROL, SfDebug))
			{
				KdPrint(("KSFitler:SfDirectoryControl:CompleteRequest\n"));
				KdPrint(("KSFitler:SfDirectoryControl:status:%d\n", status));
				KdPrint(("KSFitler:Irp->IoStatus.Information:%d\n", Irp->IoStatus.Information));
			} // ���� (FlagOn(SFDEBUG_DIRECTORYCONTROL, SfDebug))
#endif
			IoCompleteRequest( Irp, IO_NO_INCREMENT );

			return status;
		}
		break;
	default:
		break;
	}// ���� switch(pIrpSp->MinorFunction)

	if(NT_SUCCESS(status))
	{
		status = SfPassThrough(DeviceObject, Irp);
	}
	else
	{
		Irp->IoStatus.Status = status;
		Irp->IoStatus.Information = 0;
		IoCompleteRequest(Irp, IO_NO_INCREMENT);
		return status;
	} // ���� if(NT_SUCCESS(status))

	return status;
}