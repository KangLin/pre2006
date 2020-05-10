/*!
\warning 版权所有 (C) 2007 康林工作室；保留所有权利。
\file    Dispatch.c
\brief   派遣函数
\version 1.0
\author  康  林 (kl222@126.com)
\date    2007年6月7日  13:47:46
\par     编译器:
         Microsoft Visual Studio 8.0 —— C/C++ 8.0
*/

#include "FilterSys.h"

extern ARRAYHEAD g_ProtectRegisterNameHead;
extern ARRAYHEAD g_ProtectProcessNameHead;

//----------------------------------------------------------------------
//
// RegFilterDispatch
//
// In this routine we handle requests to our own device. The only 
// requests we care about handling explicitely are IOCTL commands that
// we will get from the GUI. We also expect to get Create and Close 
// commands when the GUI opens and closes communications with us.
//
//----------------------------------------------------------------------
NTSTATUS RegFilterDispatch( IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp )
{
    PIO_STACK_LOCATION      irpStack;
    PVOID                   inputBuffer;
    PVOID                   outputBuffer;
    ULONG                   inputBufferLength;
    ULONG                   outputBufferLength;
	NTSTATUS                status = STATUS_SUCCESS;

    //
    // Go ahead and set the request up as successful
    //
    Irp->IoStatus.Status      = status;
    Irp->IoStatus.Information = 0;

    //
    // Get a pointer to the current location in the Irp. This is where
    //     the function codes and parameters are located.
    //
    irpStack = IoGetCurrentIrpStackLocation (Irp);

    switch (irpStack->MajorFunction) {
    case IRP_MJ_CREATE:
		DbgPrint(("RegFilter: IRP_MJ_CREATE\n"));
        break;
    case IRP_MJ_SHUTDOWN:
		break;
    case IRP_MJ_CLOSE:
        DbgPrint(("RegFilter: IRP_MJ_CLOSE\n"));
		break;
	default:
		status = STATUS_NOT_IMPLEMENTED;
		break;
	}

    IoCompleteRequest( Irp, IO_NO_INCREMENT );
    return status;   
}

//----------------------------------------------------------------------
//
// RegmonDeviceControl
//
//----------------------------------------------------------------------
NTSTATUS RegFilterDeviceControl(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp)
{
	PIO_STACK_LOCATION      irpStack;
    PVOID                   inputBuffer = NULL;
    PVOID                   outputBuffer = NULL;
    ULONG                   inputBufferLength = 0;
    ULONG                   outputBufferLength = 0;
    ULONG                   ioControlCode;
	NTSTATUS                status;
	INT                     *pInPos = NULL;

	status = STATUS_SUCCESS;

	//
    // Go ahead and set the request up as successful
    //
    Irp->IoStatus.Status      = STATUS_SUCCESS;
    Irp->IoStatus.Information = 0;

    //
    // Get a pointer to the current location in the Irp. This is where
    //     the function codes and parameters are located.
    //
    irpStack = IoGetCurrentIrpStackLocation (Irp);

    //
    // Get the pointer to the input/output buffer and its length
    //
    inputBuffer             = Irp->AssociatedIrp.SystemBuffer;
    inputBufferLength       = irpStack->Parameters.DeviceIoControl.InputBufferLength;
    outputBuffer            = Irp->AssociatedIrp.SystemBuffer;
    outputBufferLength      = irpStack->Parameters.DeviceIoControl.OutputBufferLength;
	ioControlCode           = irpStack->Parameters.DeviceIoControl.IoControlCode;

	switch(ioControlCode)
	{
	case REGFILTER_HOOK:
		DbgPrint(("RegFilter: REGFILTER_HOOK\n"));
		HookRegistry();
		break;
	case REGFILTER_UNHOOK:
		DbgPrint(("RegFilter: REGFILTER_UNHOOK\n"));
		UnhookRegistry();
		break;
	case REGFILTER_SET_PROTECT:
		if(0 == inputBufferLength)
		{
			status = STATUS_INVALID_PARAMETER;
			break;
		}

		if(InsertElement(&g_ProtectRegisterNameHead, inputBuffer, inputBufferLength))
		{
			status = STATUS_UNSUCCESSFUL; 
		}

		break;
	case REGFILTER_REMOVE_PROTECT:
		if(0 == inputBufferLength)
		{
			status = STATUS_INVALID_PARAMETER;
			break;
		}

		if(RemoveElement(&g_ProtectRegisterNameHead, inputBuffer, inputBufferLength))
		{
			status = STATUS_UNSUCCESSFUL;
		}

		break;
	case REGFILTER_GET_POSITION_CONTENT:
		if(0 == inputBufferLength)
		{
			status = STATUS_INVALID_PARAMETER;
			break;
		}// 结束 if(0 == inputBufferLength)

		pInPos = Irp->AssociatedIrp.SystemBuffer;

		status = GetElement(&g_ProtectRegisterNameHead, *pInPos, outputBuffer, &outputBufferLength);
		Irp->IoStatus.Information = outputBufferLength;

		break;
	case PROCESSFILTER_HOOK:
		HookProcess();
		break;
	case PROCESSFILTER_UNHOOK:
		UnHookProcess();
		break;
	case PROCESSFILTER_SET_PROTECT:
		if(0 == inputBufferLength)
		{
			status = STATUS_INVALID_PARAMETER;
			break;
		}

		if(InsertElement(&g_ProtectProcessNameHead, inputBuffer, inputBufferLength))
		{
			status = STATUS_UNSUCCESSFUL; 
		}
		break;
	case PROCESSFILTER_REMOVE_PROTECT:
		if(0 == inputBufferLength)
		{
			status = STATUS_INVALID_PARAMETER;
			break;
		}

		if(RemoveElement(&g_ProtectProcessNameHead, inputBuffer, inputBufferLength))
		{
			status = STATUS_UNSUCCESSFUL;
		}

		break;
	case PROCESSFILTER_GET_POSITION_CONTENT:
		if(0 == inputBufferLength)
		{
			status = STATUS_INVALID_PARAMETER;
			break;
		}// 结束 if(0 == inputBufferLength)

		pInPos = Irp->AssociatedIrp.SystemBuffer;

		status = GetElement(&g_ProtectProcessNameHead, *pInPos, outputBuffer, &outputBufferLength);
		Irp->IoStatus.Information = outputBufferLength;

		break;
	default:
		status = STATUS_INVALID_DEVICE_REQUEST;
		break;
	}// 结束 switch(ioControlCode)

	IoCompleteRequest(Irp, IO_NO_INCREMENT);

	return status;
}
