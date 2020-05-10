#ifndef __KSFILTER_HEADER_KL__
#define __KSFILTER_HEADER_KL__

#pragma once

#include "ntifs.h"
#include "ntdddisk.h"
#include "ksfilter.h"
#include "Array.h"

/////////////////////////////////////////////////////////////////////////////
//
//                   Macro and Structure Definitions
//
/////////////////////////////////////////////////////////////////////////////

//
//  VERSION NOTE:
//
//  The following useful macros are defined in NTIFS.H in Windows XP and later.
//  We will define them locally if we are building for the Windows 2000 
//  environment.
//

#if WINVER == 0x0500

//
//  These macros are used to test, set and clear flags respectively
//

#ifndef FlagOn
#define FlagOn(_F,_SF)        ((_F) & (_SF))
#endif

#ifndef BooleanFlagOn
#define BooleanFlagOn(F,SF)   ((BOOLEAN)(((F) & (SF)) != 0))
#endif

#ifndef SetFlag
#define SetFlag(_F,_SF)       ((_F) |= (_SF))
#endif

#ifndef ClearFlag
#define ClearFlag(_F,_SF)     ((_F) &= ~(_SF))
#endif


#define RtlInitEmptyUnicodeString(_ucStr,_buf,_bufSize) \
    ((_ucStr)->Buffer = (_buf), \
     (_ucStr)->Length = 0, \
     (_ucStr)->MaximumLength = (USHORT)(_bufSize))


#ifndef min
#define min(a,b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef max
#define max(a,b) (((a) > (b)) ? (a) : (b))
#endif

//
//  We want ASSERT defined as an expression, which was fixed after Windows 2000
//

#ifdef ASSERT
#undef ASSERT
#if DBG
#define ASSERT( exp ) \
    ((!(exp)) ? \
        (RtlAssert( #exp, __FILE__, __LINE__, NULL ),FALSE) : \
        TRUE)
#else
#define ASSERT( exp ) ((void) 0)
#endif
#endif        

#define ExFreePoolWithTag( a, b ) ExFreePool( (a) )

#endif /* WINVER == 0x0500 */

#ifndef Add2Ptr
#define Add2Ptr(P,I) ((PVOID)((PUCHAR)(P) + (I)))
#endif

//
//  Buffer size for local names on the stack
//

#define MAX_DEVNAME_LENGTH 64

//
//  Device extension definition for our driver.  Note that the same extension
//  is used for the following types of device objects:
//      - File system device object we attach to
//      - Mounted volume device objects we attach to
//

typedef struct _SFILTER_DEVICE_EXTENSION {

    //
    //  Pointer to the file system device object we are attached to
    //

    PDEVICE_OBJECT AttachedToDeviceObject;

    //
    //  Pointer to the real (disk) device object that is associated with
    //  the file system device object we are attached to
    //

    PDEVICE_OBJECT StorageStackDeviceObject;

    //
    //  Name for this device.  If attached to a Volume Device Object it is the
    //  name of the physical disk drive.  If attached to a Control Device
    //  Object it is the name of the Control Device Object.
    //

    UNICODE_STRING DeviceName;

    //
    //  Buffer used to hold the above unicode strings
    //

	WCHAR DeviceNameBuffer[MAX_DEVNAME_LENGTH];

	// Dos Name for this device. If attached to a Volume Device Object it is the
	// link symbol name of the physical disk drive.example:(c:¡¢d: ect).
	// If attached to a Control Device Object that is NULL
	UNICODE_STRING DeviceLinkSymbolName;

	WCHAR DeviceLinkSymbolNameBuffer[MAX_DEVNAME_LENGTH];

} SFILTER_DEVICE_EXTENSION, *PSFILTER_DEVICE_EXTENSION;

//
//  This structure contains the information we need to pass to the completion
//  processing for FSCTRLs.
//

typedef struct _FSCTRL_COMPLETION_CONTEXT {

    //
    //  The workitem that will be initialized with our context and 
    //  worker routine if this completion processing needs to be completed
    //  in a worker thread.
    //
    
    WORK_QUEUE_ITEM WorkItem;

    //
    //  The device object to which this device is currently directed.
    //
    
    PDEVICE_OBJECT DeviceObject;

    //
    //  The IRP for this FSCTRL operation.
    //
    
    PIRP Irp;

    //
    //  For mount operations, the new device object that we have allocated
    //  and partially initialized that we will attach to the mounted volume
    //  if the mount is successful.
    //
    
    PDEVICE_OBJECT NewDeviceObject;
    
} FSCTRL_COMPLETION_CONTEXT, *PFSCTRL_COMPLETION_CONTEXT;
        

//
//  Macro to test if this is my device object
//

#define IS_MY_DEVICE_OBJECT(_devObj) \
    (((_devObj) != NULL) && \
     ((_devObj)->DriverObject == gSFilterDriverObject) && \
      ((_devObj)->DeviceExtension != NULL))

//
//  Macro to test if this is my control device object
//

#define IS_MY_CONTROL_DEVICE_OBJECT(_devObj) \
    (((_devObj) == gSFilterControlDeviceObject) ? \
            (ASSERT(((_devObj)->DriverObject == gSFilterDriverObject) && \
                    ((_devObj)->DeviceExtension == NULL)), TRUE) : \
            FALSE)

//
//  Macro to test for device types we want to attach to
//

#define IS_DESIRED_DEVICE_TYPE(_type) \
    (((_type) == FILE_DEVICE_DISK_FILE_SYSTEM) || \
     ((_type) == FILE_DEVICE_CD_ROM_FILE_SYSTEM) || \
     ((_type) == FILE_DEVICE_NETWORK_FILE_SYSTEM))

//
//  Macro to test if FAST_IO_DISPATCH handling routine is valid
//

#define VALID_FAST_IO_DISPATCH_HANDLER(_FastIoDispatchPtr, _FieldName) \
    (((_FastIoDispatchPtr) != NULL) && \
     (((_FastIoDispatchPtr)->SizeOfFastIoDispatch) >= \
            (FIELD_OFFSET(FAST_IO_DISPATCH, _FieldName) + sizeof(void *))) && \
     ((_FastIoDispatchPtr)->_FieldName != NULL))


#if WINVER >= 0x0501
//
//  MULTIVERSION NOTE:
//
//  If built in the Windows XP environment or later, we will dynamically import
//  the function pointers for routines that were not supported on Windows 2000
//  so that we can build a driver that will run, with modified logic, on 
//  Windows 2000 or later.
//
//  Below are the prototypes for the function pointers that we need to 
//  dynamically import because not all OS versions support these routines.
//

typedef
NTSTATUS
(*PSF_REGISTER_FILE_SYSTEM_FILTER_CALLBACKS) (
    IN PDRIVER_OBJECT DriverObject,
    IN PFS_FILTER_CALLBACKS Callbacks
    );

typedef
NTSTATUS
(*PSF_ENUMERATE_DEVICE_OBJECT_LIST) (
    IN  PDRIVER_OBJECT DriverObject,
    IN  PDEVICE_OBJECT *DeviceObjectList,
    IN  ULONG DeviceObjectListSize,
    OUT PULONG ActualNumberDeviceObjects
    );

typedef
NTSTATUS
(*PSF_ATTACH_DEVICE_TO_DEVICE_STACK_SAFE) (
    IN PDEVICE_OBJECT SourceDevice,
    IN PDEVICE_OBJECT TargetDevice,
    OUT PDEVICE_OBJECT *AttachedToDeviceObject
    );

typedef    
PDEVICE_OBJECT
(*PSF_GET_LOWER_DEVICE_OBJECT) (
    IN  PDEVICE_OBJECT  DeviceObject
    );

typedef
PDEVICE_OBJECT
(*PSF_GET_DEVICE_ATTACHMENT_BASE_REF) (
    IN PDEVICE_OBJECT DeviceObject
    );

typedef
NTSTATUS
(*PSF_GET_DISK_DEVICE_OBJECT) (
    IN  PDEVICE_OBJECT  FileSystemDeviceObject,
    OUT PDEVICE_OBJECT  *DiskDeviceObject
    );

typedef
PDEVICE_OBJECT
(*PSF_GET_ATTACHED_DEVICE_REFERENCE) (
    IN PDEVICE_OBJECT DeviceObject
    );

typedef
NTSTATUS
(*PSF_GET_VERSION) (
    IN OUT PRTL_OSVERSIONINFOW VersionInformation
    );

typedef
NTSTATUS
(*PSF_VOLUME_DEVICE_TO_DOSNAME)(
	IN  PVOID  VolumeDeviceObject,
    OUT PUNICODE_STRING  DosName
    );

typedef struct _SF_DYNAMIC_FUNCTION_POINTERS {

    //
    //  The following routines should all be available on Windows XP (5.1) and
    //  later.
    //

    PSF_REGISTER_FILE_SYSTEM_FILTER_CALLBACKS RegisterFileSystemFilterCallbacks;
    PSF_ATTACH_DEVICE_TO_DEVICE_STACK_SAFE AttachDeviceToDeviceStackSafe;
    PSF_ENUMERATE_DEVICE_OBJECT_LIST EnumerateDeviceObjectList;
    PSF_GET_LOWER_DEVICE_OBJECT GetLowerDeviceObject;
    PSF_GET_DEVICE_ATTACHMENT_BASE_REF GetDeviceAttachmentBaseRef;
    PSF_GET_DISK_DEVICE_OBJECT GetDiskDeviceObject;
    PSF_GET_ATTACHED_DEVICE_REFERENCE GetAttachedDeviceReference;
	PSF_GET_VERSION GetVersion;
	PSF_VOLUME_DEVICE_TO_DOSNAME VolumeDeviceToDosName;

} SF_DYNAMIC_FUNCTION_POINTERS, *PSF_DYNAMIC_FUNCTION_POINTERS;

extern SF_DYNAMIC_FUNCTION_POINTERS gSfDynamicFunctions;

//
//  MULTIVERSION NOTE: For this version of the driver, we need to know the
//  current OS version while we are running to make decisions regarding what
//  logic to use when the logic cannot be the same for all platforms.  We
//  will look up the OS version in DriverEntry and store the values
//  in these global variables.
//

extern ULONG gSfOsMajorVersion;
extern ULONG gSfOsMinorVersion;

extern BOOLEAN gWriteProtectData;

//
//  Here is what the major and minor versions should be for the various OS versions:
//
//  OS Name                                 MajorVersion    MinorVersion
//  ---------------------------------------------------------------------
//  Windows 2000                             5                 0
//  Windows XP                               5                 1
//  Windows Server 2003                      5                 2
//

#define IS_WINDOWS2000() \
    ((gSfOsMajorVersion == 5) && (gSfOsMinorVersion == 0))

#define IS_WINDOWSXP() \
    ((gSfOsMajorVersion == 5) && (gSfOsMinorVersion == 1))

#define IS_WINDOWSXP_OR_LATER() \
    (((gSfOsMajorVersion == 5) && (gSfOsMinorVersion >= 1)) || \
     (gSfOsMajorVersion > 5))

#define IS_WINDOWSSRV2003_OR_LATER() \
    (((gSfOsMajorVersion == 5) && (gSfOsMinorVersion >= 2)) || \
     (gSfOsMajorVersion > 5))

#endif


//
//  TAG identifying memory SFilter allocates
//

#define SFLT_POOL_TAG   'tlFS'

//
//  This structure and these routines are used to retrieve the name of a file
//  object.  To prevent allocating memory every time we get a name this
//  structure contains a small buffer (which should handle 90+% of all names).
//  If we do overflow this buffer we will allocate a buffer big enough
//  for the name.
//

typedef struct _GET_NAME_CONTROL {

    PCHAR allocatedBuffer;
    CHAR smallBuffer[256];
    
} GET_NAME_CONTROL, *PGET_NAME_CONTROL;


PUNICODE_STRING
SfGetFileName(
    IN PFILE_OBJECT FileObject,
    IN NTSTATUS CreateStatus,
    IN OUT PGET_NAME_CONTROL NameControl
    );


VOID
SfGetFileNameCleanup(
    IN OUT PGET_NAME_CONTROL NameControl
    );


//
//  Macros for SFilter DbgPrint levels.
//

#define SF_LOG_PRINT( _dbgLevel, _string )                  \
    (FlagOn(SfDebug,(_dbgLevel)) ?                          \
        DbgPrint _string  :                                 \
        ((void)0))

//
//  Delay values for KeDelayExecutionThread()
//  (Values are negative to represent relative time)
//

#define DELAY_ONE_MICROSECOND   (-10)
#define DELAY_ONE_MILLISECOND   (DELAY_ONE_MICROSECOND*1000)
#define DELAY_ONE_SECOND        (DELAY_ONE_MILLISECOND*1000)

/////////////////////////////////////////////////////////////////////////////
//
//                      Debug Definitions
//
/////////////////////////////////////////////////////////////////////////////

//
//  DEBUG display flags
//

#define SFDEBUG_DISPLAY_ATTACHMENT_NAMES    0x00000001  //display names of device objects we attach to
#define SFDEBUG_DISPLAY_CREATE_NAMES        0x00000002  //get and display names during create
#define SFDEBUG_GET_CREATE_NAMES            0x00000004  //get name (don't display) during create
#define SFDEBUG_DO_CREATE_COMPLETION        0x00000008  //do create completion routine, don't get names
#define SFDEBUG_ATTACH_TO_FSRECOGNIZER      0x00000010  //do attach to FSRecognizer device objects
#define SFDEBUG_ATTACH_TO_SHADOW_COPIES     0x00000020  //do attach to ShadowCopy Volume device objects -- they are only around on Windows XP and later
#define SFDEBUG_SET_INFORMATION             0x00000080  //display set information route
#define SFDEBUG_CREATE                      0x00000100  //display create RouterAdvertisementsSent
#define SFDEBUG_READWRITE                   0x00000200  //display read and write route
#define SFDEBUG_DIRECTORYCONTROL            0x00000400  //display directory control route

extern ULONG SfDebug;


//
//  Given a device type, return a valid name
//

#define GET_DEVICE_TYPE_NAME( _type ) \
            ((((_type) > 0) && ((_type) < (sizeof(DeviceTypeNames) / sizeof(PCHAR)))) ? \
                DeviceTypeNames[ (_type) ] : \
                "[Unknown]")

//
//  Known device type names
//

static const PCHAR DeviceTypeNames[] = {
    "",
    "BEEP",
    "CD_ROM",
    "CD_ROM_FILE_SYSTEM",
    "CONTROLLER",
    "DATALINK",
    "DFS",
    "DISK",
    "DISK_FILE_SYSTEM",
    "FILE_SYSTEM",
    "INPORT_PORT",
    "KEYBOARD",
    "MAILSLOT",
    "MIDI_IN",
    "MIDI_OUT",
    "MOUSE",
    "MULTI_UNC_PROVIDER",
    "NAMED_PIPE",
    "NETWORK",
    "NETWORK_BROWSER",
    "NETWORK_FILE_SYSTEM",
    "NULL",
    "PARALLEL_PORT",
    "PHYSICAL_NETCARD",
    "PRINTER",
    "SCANNER",
    "SERIAL_MOUSE_PORT",
    "SERIAL_PORT",
    "SCREEN",
    "SOUND",
    "STREAMS",
    "TAPE",
    "TAPE_FILE_SYSTEM",
    "TRANSPORT",
    "UNKNOWN",
    "VIDEO",
    "VIRTUAL_DISK",
    "WAVE_IN",
    "WAVE_OUT",
    "8042_PORT",
    "NETWORK_REDIRECTOR",
    "BATTERY",
    "BUS_EXTENDER",
    "MODEM",
    "VDM",
    "MASS_STORAGE",
    "SMB",
    "KS",
    "CHANGER",
    "SMARTCARD",
    "ACPI",
    "DVD",
    "FULLSCREEN_VIDEO",
    "DFS_FILE_SYSTEM",
    "DFS_VOLUME",
    "SERENUM",
    "TERMSRV",
    "KSEC"
};

typedef struct _FILTERFILE
{
	UNICODE_STRING FileName;
	LIST_ENTRY Next;
}FILTERFILE, *PFILTERFILE;

/////////////////////////////////////////////////////////////////////////////
//
//                         Global variables
//
/////////////////////////////////////////////////////////////////////////////

extern PDRIVER_OBJECT gSFilterDriverObject;
extern PDEVICE_OBJECT gSFilterControlDeviceObject;
extern FAST_MUTEX gSfilterAttachLock;

/////////////////////////////////////////////////////////////////////////////
//
//                          Function Prototypes
//
/////////////////////////////////////////////////////////////////////////////

//
//  Define driver entry routine.
//

NTSTATUS
DriverEntry(
    IN PDRIVER_OBJECT DriverObject,
    IN PUNICODE_STRING RegistryPath
    );

#if DBG && WINVER >= 0x0501
VOID
DriverUnload(
    IN PDRIVER_OBJECT DriverObject
    );
#endif

//
//  Define the local routines used by this driver module.  This includes a
//  a sample of how to filter a create file operation, and then invoke an I/O
//  completion routine when the file has successfully been created/opened.
//

#if WINVER >= 0x0501
VOID
SfLoadDynamicFunctions (
    );

VOID
SfGetCurrentVersion (
    );
#endif

NTSTATUS
SfPassThrough(
    IN PDEVICE_OBJECT DeviceObject,
    IN PIRP Irp
    );

NTSTATUS
SfCreate(
    IN PDEVICE_OBJECT DeviceObject,
    IN PIRP Irp
    );

NTSTATUS
SetCompletionRoutine(
					 IN PDEVICE_OBJECT AttachedDeviceObject,
					 IN PIRP Irp
					 );

NTSTATUS
SfCompletionRoutine(
    IN PDEVICE_OBJECT DeviceObject,
    IN PIRP Irp,
    IN PVOID Context
    );

NTSTATUS
SfCleanupClose(
    IN PDEVICE_OBJECT DeviceObject,
    IN PIRP Irp
    );

NTSTATUS
SfRead(
	   IN PDEVICE_OBJECT DeviceObject,
	   IN PIRP Irp
	   );

NTSTATUS
SfWrite(
		IN PDEVICE_OBJECT DeviceObject,
		IN PIRP Irp);

NTSTATUS
SfDirectoryControl(
				   IN PDEVICE_OBJECT DeviceObject,
				   IN PIRP Irp);

NTSTATUS
SfFsControl(
    IN PDEVICE_OBJECT DeviceObject,
    IN PIRP Irp
    );

NTSTATUS
SfDeviceControl(
    IN PDEVICE_OBJECT DeviceObject,
    IN PIRP Irp
	);

NTSTATUS
SfSetInformation(
    IN PDEVICE_OBJECT DeviceObject,
    IN PIRP Irp
	);

NTSTATUS
SfFsControlMountVolume (
    IN PDEVICE_OBJECT DeviceObject,
    IN PIRP Irp
    );

VOID
SfFsControlMountVolumeCompleteWorker (
    IN PFSCTRL_COMPLETION_CONTEXT Context
    );

NTSTATUS
SfFsControlMountVolumeComplete (
    IN PDEVICE_OBJECT DeviceObject,
    IN PIRP Irp,
    IN PDEVICE_OBJECT NewDeviceObject
    );

NTSTATUS
SfFsControlLoadFileSystem (
    IN PDEVICE_OBJECT DeviceObject,
    IN PIRP Irp
    );

VOID
SfFsControlLoadFileSystemCompleteWorker (
    IN PFSCTRL_COMPLETION_CONTEXT Context
    );

NTSTATUS
SfFsControlLoadFileSystemComplete (
    IN PDEVICE_OBJECT DeviceObject,
    IN PIRP Irp
    );

NTSTATUS
SfFsControlCompletion(
    IN PDEVICE_OBJECT DeviceObject,
    IN PIRP Irp,
    IN PVOID Context
    );

BOOLEAN
SfFastIoCheckIfPossible(
    IN PFILE_OBJECT FileObject,
    IN PLARGE_INTEGER FileOffset,
    IN ULONG Length,
    IN BOOLEAN Wait,
    IN ULONG LockKey,
    IN BOOLEAN CheckForReadOperation,
    OUT PIO_STATUS_BLOCK IoStatus,
    IN PDEVICE_OBJECT DeviceObject
    );

BOOLEAN
SfFastIoRead(
    IN PFILE_OBJECT FileObject,
    IN PLARGE_INTEGER FileOffset,
    IN ULONG Length,
    IN BOOLEAN Wait,
    IN ULONG LockKey,
    OUT PVOID Buffer,
    OUT PIO_STATUS_BLOCK IoStatus,
    IN PDEVICE_OBJECT DeviceObject
    );

BOOLEAN
SfFastIoWrite(
    IN PFILE_OBJECT FileObject,
    IN PLARGE_INTEGER FileOffset,
    IN ULONG Length,
    IN BOOLEAN Wait,
    IN ULONG LockKey,
    IN PVOID Buffer,
    OUT PIO_STATUS_BLOCK IoStatus,
    IN PDEVICE_OBJECT DeviceObject
    );

BOOLEAN
SfFastIoQueryBasicInfo(
    IN PFILE_OBJECT FileObject,
    IN BOOLEAN Wait,
    OUT PFILE_BASIC_INFORMATION Buffer,
    OUT PIO_STATUS_BLOCK IoStatus,
    IN PDEVICE_OBJECT DeviceObject
    );

BOOLEAN
SfFastIoQueryStandardInfo(
    IN PFILE_OBJECT FileObject,
    IN BOOLEAN Wait,
    OUT PFILE_STANDARD_INFORMATION Buffer,
    OUT PIO_STATUS_BLOCK IoStatus,
    IN PDEVICE_OBJECT DeviceObject
    );

BOOLEAN
SfFastIoLock(
    IN PFILE_OBJECT FileObject,
    IN PLARGE_INTEGER FileOffset,
    IN PLARGE_INTEGER Length,
    PEPROCESS ProcessId,
    ULONG Key,
    BOOLEAN FailImmediately,
    BOOLEAN ExclusiveLock,
    OUT PIO_STATUS_BLOCK IoStatus,
    IN PDEVICE_OBJECT DeviceObject
    );

BOOLEAN
SfFastIoUnlockSingle(
    IN PFILE_OBJECT FileObject,
    IN PLARGE_INTEGER FileOffset,
    IN PLARGE_INTEGER Length,
    PEPROCESS ProcessId,
    ULONG Key,
    OUT PIO_STATUS_BLOCK IoStatus,
    IN PDEVICE_OBJECT DeviceObject
    );

BOOLEAN
SfFastIoUnlockAll(
    IN PFILE_OBJECT FileObject,
    PEPROCESS ProcessId,
    OUT PIO_STATUS_BLOCK IoStatus,
    IN PDEVICE_OBJECT DeviceObject
    );

BOOLEAN
SfFastIoUnlockAllByKey(
    IN PFILE_OBJECT FileObject,
    PVOID ProcessId,
    ULONG Key,
    OUT PIO_STATUS_BLOCK IoStatus,
    IN PDEVICE_OBJECT DeviceObject
    );

BOOLEAN
SfFastIoDeviceControl(
    IN PFILE_OBJECT FileObject,
    IN BOOLEAN Wait,
    IN PVOID InputBuffer OPTIONAL,
    IN ULONG InputBufferLength,
    OUT PVOID OutputBuffer OPTIONAL,
    IN ULONG OutputBufferLength,
    IN ULONG IoControlCode,
    OUT PIO_STATUS_BLOCK IoStatus,
    IN PDEVICE_OBJECT DeviceObject
    );

VOID
SfFastIoDetachDevice(
    IN PDEVICE_OBJECT SourceDevice,
    IN PDEVICE_OBJECT TargetDevice
    );

BOOLEAN
SfFastIoQueryNetworkOpenInfo(
    IN PFILE_OBJECT FileObject,
    IN BOOLEAN Wait,
    OUT PFILE_NETWORK_OPEN_INFORMATION Buffer,
    OUT PIO_STATUS_BLOCK IoStatus,
    IN PDEVICE_OBJECT DeviceObject
    );

BOOLEAN
SfFastIoMdlRead(
    IN PFILE_OBJECT FileObject,
    IN PLARGE_INTEGER FileOffset,
    IN ULONG Length,
    IN ULONG LockKey,
    OUT PMDL *MdlChain,
    OUT PIO_STATUS_BLOCK IoStatus,
    IN PDEVICE_OBJECT DeviceObject
    );


BOOLEAN
SfFastIoMdlReadComplete(
    IN PFILE_OBJECT FileObject,
    IN PMDL MdlChain,
    IN PDEVICE_OBJECT DeviceObject
    );

BOOLEAN
SfFastIoPrepareMdlWrite(
    IN PFILE_OBJECT FileObject,
    IN PLARGE_INTEGER FileOffset,
    IN ULONG Length,
    IN ULONG LockKey,
    OUT PMDL *MdlChain,
    OUT PIO_STATUS_BLOCK IoStatus,
    IN PDEVICE_OBJECT DeviceObject
    );

BOOLEAN
SfFastIoMdlWriteComplete(
    IN PFILE_OBJECT FileObject,
    IN PLARGE_INTEGER FileOffset,
    IN PMDL MdlChain,
    IN PDEVICE_OBJECT DeviceObject
    );

BOOLEAN
SfFastIoReadCompressed(
    IN PFILE_OBJECT FileObject,
    IN PLARGE_INTEGER FileOffset,
    IN ULONG Length,
    IN ULONG LockKey,
    OUT PVOID Buffer,
    OUT PMDL *MdlChain,
    OUT PIO_STATUS_BLOCK IoStatus,
    OUT struct _COMPRESSED_DATA_INFO *CompressedDataInfo,
    IN ULONG CompressedDataInfoLength,
    IN PDEVICE_OBJECT DeviceObject
    );

BOOLEAN
SfFastIoWriteCompressed(
    IN PFILE_OBJECT FileObject,
    IN PLARGE_INTEGER FileOffset,
    IN ULONG Length,
    IN ULONG LockKey,
    IN PVOID Buffer,
    OUT PMDL *MdlChain,
    OUT PIO_STATUS_BLOCK IoStatus,
    IN struct _COMPRESSED_DATA_INFO *CompressedDataInfo,
    IN ULONG CompressedDataInfoLength,
    IN PDEVICE_OBJECT DeviceObject
    );

BOOLEAN
SfFastIoMdlReadCompleteCompressed(
    IN PFILE_OBJECT FileObject,
    IN PMDL MdlChain,
    IN PDEVICE_OBJECT DeviceObject
    );

BOOLEAN
SfFastIoMdlWriteCompleteCompressed(
    IN PFILE_OBJECT FileObject,
    IN PLARGE_INTEGER FileOffset,
    IN PMDL MdlChain,
    IN PDEVICE_OBJECT DeviceObject
    );

BOOLEAN
SfFastIoQueryOpen(
    IN PIRP Irp,
    OUT PFILE_NETWORK_OPEN_INFORMATION NetworkInformation,
    IN PDEVICE_OBJECT DeviceObject
    );

#if WINVER >= 0x0501 /* See comment in DriverEntry */
NTSTATUS
SfPreFsFilterPassThrough (
    IN PFS_FILTER_CALLBACK_DATA Data,
    OUT PVOID *CompletionContext
    );

VOID
SfPostFsFilterPassThrough (
    IN PFS_FILTER_CALLBACK_DATA Data,
    IN NTSTATUS OperationStatus,
    IN PVOID CompletionContext
    );
#endif

VOID
SfFsNotification(
    IN PDEVICE_OBJECT DeviceObject,
    IN BOOLEAN FsActive
    );

NTSTATUS
SfAttachDeviceToDeviceStack (
    IN PDEVICE_OBJECT SourceDevice,
    IN PDEVICE_OBJECT TargetDevice,
    IN OUT PDEVICE_OBJECT *AttachedToDeviceObject
    );

NTSTATUS
SfAttachToFileSystemDevice(
    IN PDEVICE_OBJECT DeviceObject,
    IN PUNICODE_STRING DeviceName
    );

VOID
SfDetachFromFileSystemDevice (
    IN PDEVICE_OBJECT DeviceObject
    );

NTSTATUS
SfAttachToMountedDevice (
    IN PDEVICE_OBJECT DeviceObject,
    IN PDEVICE_OBJECT SFilterDeviceObject
    );

VOID
SfCleanupMountedDevice(
    IN PDEVICE_OBJECT DeviceObject
    );

#if WINVER >= 0x0501
NTSTATUS
SfEnumerateFileSystemVolumes(
    IN PDEVICE_OBJECT FSDeviceObject,
    IN PUNICODE_STRING FSName
    );
#endif

NTSTATUS
VolumeDeviceToDosName(
	IN PVOID VolumeDeviceObject,
	OUT PUNICODE_STRING DosName
	);

VOID
SfGetObjectName(
    IN PVOID Object,
    IN OUT PUNICODE_STRING Name
    );

VOID
SfGetBaseDeviceObjectName(
    IN PDEVICE_OBJECT DeviceObject,
    IN OUT PUNICODE_STRING DeviceName
    );

BOOLEAN
SfIsAttachedToDevice(
    PDEVICE_OBJECT DeviceObject,
    PDEVICE_OBJECT *AttachedDeviceObject OPTIONAL
    );

BOOLEAN
SfIsAttachedToDeviceW2K(
    PDEVICE_OBJECT DeviceObject,
    PDEVICE_OBJECT *AttachedDeviceObject OPTIONAL
    );

BOOLEAN
SfIsAttachedToDeviceWXPAndLater(
    PDEVICE_OBJECT DeviceObject,
    PDEVICE_OBJECT *AttachedDeviceObject OPTIONAL
    );

VOID
SfReadDriverParameters(
    IN PUNICODE_STRING RegistryPath
    );

NTSTATUS
SfIsShadowCopyVolume (
    IN PDEVICE_OBJECT StorageStackDeviceObject,
    OUT PBOOLEAN IsShadowCopy
    );

NTSTATUS
SfQueryFileInformation(
					 PDEVICE_OBJECT DeviceObject, 
					 PFILE_OBJECT FileObject,
					 FILE_INFORMATION_CLASS FileInformationClass,
					 PVOID FileInfo,
					 ULONG FileInfoLength
					 );

NTSTATUS
SfQueryFileInformationCompleted(
							  PDEVICE_OBJECT DeviceObject,
							  PIRP Irp,
							  PVOID Context
							  );

NTSTATUS
SfQueryFileBasicInformation(
						  PDEVICE_OBJECT DeviceObject, 
						  PFILE_OBJECT FileObject,
						  PFILE_BASIC_INFORMATION FileBasicInfo
						  );

NTSTATUS
SfQueryFileName(PDEVICE_OBJECT DeviceObject, 
				PFILE_OBJECT FileObject,
				PFILE_NAME_INFORMATION FileName,
				ULONG dwLen
				);

#endif //__KSFILTER_HEADER_KL__