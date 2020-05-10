/*!
\warning 版权所有 (C) 2007 康林工作室；保留所有权利。
\file    SetInformation.c
\brief   设置文件信息派遣函数
\version 1.0
\author  康  林 (kl222@126.com)
\date    2007年5月9日  13:28:40
\par     编译器:
         Microsoft Visual Studio 8.0 —— C/C++ 8.0
*/

#include "sfilter.h"
#include "Support.h"

NTSTATUS
SfSetInformation(
    IN PDEVICE_OBJECT DeviceObject,
    IN PIRP Irp
	)
{
	NTSTATUS status = STATUS_SUCCESS;
	PIO_STACK_LOCATION pIrpSp = IoGetCurrentIrpStackLocation(Irp);
	PFILE_DISPOSITION_INFORMATION pDispInfo = NULL;
	PFILE_RENAME_INFORMATION pRenameInfo = NULL;
	FILE_BASIC_INFORMATION fileBasicInfo;
	PUNICODE_STRING pFileName = NULL;
	PSFILTER_DEVICE_EXTENSION pExt = NULL;

	PAGED_CODE();

	ASSERT(!IS_MY_CONTROL_DEVICE_OBJECT(DeviceObject));
	ASSERT(IS_MY_DEVICE_OBJECT(DeviceObject));


#ifdef DBG
	if(FlagOn(SFDEBUG_SET_INFORMATION, SfDebug))
	{
		KdPrint(("SfSetInformation: pIrpSp->FileObject->FileName:%wZ\n", &pIrpSp->FileObject->FileName));
		pExt = (PSFILTER_DEVICE_EXTENSION)DeviceObject->DeviceExtension;
		KdPrint(("Device Name:%wZ\n", &pExt->DeviceName));
		KdPrint(("Device Dos Name:%wZ\n", &pExt->DeviceLinkSymbolName));
	} // 结束 if(FlagOn(SFDEBUG_SET_INFORMATION, SfDebug))
#endif

	pExt = (PSFILTER_DEVICE_EXTENSION)DeviceObject->DeviceExtension;

	switch(pIrpSp->Parameters.SetFile.FileInformationClass)
	{
	case FileDispositionInformation:
		// Delete File
		pDispInfo = (PFILE_DISPOSITION_INFORMATION)Irp->AssociatedIrp.SystemBuffer;
		if(pDispInfo->DeleteFile)
		{
			status = GetFullPath(DeviceObject, Irp, &pFileName);
			if(NT_SUCCESS(status))
			{
				if(SfIsDisableDeleteFile(pFileName, CompareCallBack))
				{
					status = STATUS_NO_SUCH_FILE; //STATUS_ACCESS_DENIED;
				} // 结束 if(SfIsDisableDeleteFile(pFileName, CompareCallBack))
			}// 结束 if(NT_SUCCESS(status))
		}// 结束 if(pDispInfo->DeleteFile)

		break;
	case FileRenameInformation:
		// Rename File(Delete File)
		pRenameInfo = (PFILE_RENAME_INFORMATION)Irp->AssociatedIrp.SystemBuffer;

#ifdef DBG
		if(FlagOn(SFDEBUG_SET_INFORMATION, SfDebug))
		{
			KdPrint(("SfSetInformation: FileRenameInformation->FileName:%ws\n", pRenameInfo->FileName));
			KdPrint(("SfSetInformation: pRenameInfo->RootDirectory:%d\n", pRenameInfo->RootDirectory));
			KdPrint(("SfSetInformation: pRenameInfo->FileNameLength:%d\n", pRenameInfo->FileNameLength));
		} // 结束 (FlagOn(SFDEBUG_SET_INFORMATION, SfDebug))
#endif

		status = GetFullPath(DeviceObject, Irp, &pFileName);
		if(NT_SUCCESS(status))
		{
			status = SfQueryFileBasicInformation(pExt->AttachedToDeviceObject, pIrpSp->FileObject, &fileBasicInfo);
			if(NT_SUCCESS(status))
			{
				if(fileBasicInfo.FileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				{
					// Is Directory
					if(SfIsDisableDeleteFile(pFileName, CompareDirCallBack))
					{
						status = STATUS_ACCESS_DENIED;
					}// 结束 if(SfIsDisableDeleteFile(pFileName, CompareDirCallBack))
				}
				else
				{
					// Is File
					if(SfIsDisableDeleteFile(pFileName, CompareCallBack))
					{
						status = STATUS_ACCESS_DENIED;
					}// 结束 if(SfIsDisableDeleteFile(pFileName, CompareCallBack))
				} // 结束 if(fileBasicInfo.FileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			} // 结束 if(NT_SUCCESS(status))
		}// 结束 if(NT_SUCCESS(status))

		break;
	default:
		break;
	}// 结束 switch(pIrpSp->Parameters.SetFile.FileInformationClass)

	// Free buffer
	if(pFileName)
	{
		FreeUnicodeBuffer(pFileName);
	} // 结束 if(pFileName)
	
	if(NT_SUCCESS(status))
	{
		// Pass through irp
		status = SfPassThrough(DeviceObject, Irp);
	}
	else
	{
		Irp->IoStatus.Status = status;
		Irp->IoStatus.Information = 0;
		IoCompleteRequest(Irp, IO_NO_INCREMENT);
	} // 结束 if(NT_SUCCESS(status))

	return status;
}