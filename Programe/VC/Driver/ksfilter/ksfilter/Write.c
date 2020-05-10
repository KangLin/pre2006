#include "sfilter.h"
#include "Support.h"

NTSTATUS SfWrite(IN PDEVICE_OBJECT DeviceObject,
				IN PIRP Irp)
{
	NTSTATUS status = STATUS_SUCCESS;
	PIO_STACK_LOCATION pIrpSp = IoGetCurrentIrpStackLocation(Irp);
	PSFILTER_DEVICE_EXTENSION pExt;
	BOOLEAN bIsDisable = FALSE;
	PUNICODE_STRING pFileName = NULL;

	PAGED_CODE();

	ASSERT(!IS_MY_CONTROL_DEVICE_OBJECT(DeviceObject));
	ASSERT(IS_MY_DEVICE_OBJECT(DeviceObject));

#ifdef DBG
	if(FlagOn(SFDEBUG_READWRITE, SfDebug))
	{
		KdPrint(("KSFilter:->SfWrite\n"));
		KdPrint(("SfWrite: pIrpSp->FileObject->FileName:%wZ\n", &pIrpSp->FileObject->FileName));
		pExt = (PSFILTER_DEVICE_EXTENSION)DeviceObject->DeviceExtension;
		KdPrint(("Device Name:%wZ\n", &pExt->DeviceName));
		KdPrint(("Device Dos Name:%wZ\n", &pExt->DeviceLinkSymbolName));
	} // 结束 if(FlagOn(SFDEBUG_READWRITE, SfDebug))
#endif

	status = GetFullPath(DeviceObject, Irp, &pFileName);
	if(NT_SUCCESS(status))
	{
		if(SfIsDisableDeleteFile(pFileName, CompareCallBack))
		{
			bIsDisable = TRUE;
		} // 结束 if(SfIsDisableDeleteFile(pFileName, CompareCallBack))
	}
	else
	{
		return status; 
	}// 结束 (SfIsDisableDeleteFile(pFileName, CompareCallBack))

	// Free buffer
	if(pFileName)
	{
		FreeUnicodeBuffer(pFileName);
	} // 结束 if(pFileName)
	
	if(bIsDisable)
	{
		status = STATUS_ACCESS_DENIED;
		Irp->IoStatus.Status = status;
		Irp->IoStatus.Information = 0;
		IoCompleteRequest(Irp, IO_NO_INCREMENT);
		return status;
	}
	else
	{
		status = SfPassThrough(DeviceObject, Irp);
	}	

#ifdef DBG
	if(FlagOn(SFDEBUG_READWRITE, SfDebug))
	{
		KdPrint(("KSFilter:<-SfWrite\n"));
	} // 结束 if(FlagOn(SFDEBUG_READWRITE, SfDebug))
#endif
	return status;
}