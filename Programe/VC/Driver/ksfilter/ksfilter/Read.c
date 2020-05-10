#include "sfilter.h"

NTSTATUS SfRead(IN PDEVICE_OBJECT DeviceObject,
				IN PIRP Irp)
{
	NTSTATUS status = STATUS_SUCCESS;
	PIO_STACK_LOCATION pIrpSp = IoGetCurrentIrpStackLocation(Irp);
	PSFILTER_DEVICE_EXTENSION pExt;

	PAGED_CODE();

	ASSERT(!IS_MY_CONTROL_DEVICE_OBJECT(DeviceObject));
	ASSERT(IS_MY_DEVICE_OBJECT(DeviceObject));

#ifdef DBG
	if(FlagOn(SFDEBUG_READWRITE, SfDebug))
	{
		KdPrint(("KSFilter:->SfRead\n"));
	} // ½áÊø if(FlagOn(SFDEBUG_READWRITE, SfDebug))
#endif

	status = SfPassThrough(DeviceObject, Irp);

#ifdef DBG
	if(FlagOn(SFDEBUG_READWRITE, SfDebug))
	{
		KdPrint(("KSFilter:<-SfRead\n"));
	} // ½áÊø if(FlagOn(SFDEBUG_READWRITE, SfDebug))
#endif
	return status;
}