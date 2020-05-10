#ifndef __SUPPORT_H_KL_2007_05_11__
#define __SUPPORT_H_KL_2007_05_11__

#include "Array.h"

INT CompareCallBack(PDATASTRUCT pDestination, PDATASTRUCT pSource);
INT CompareDirCallBack(PDATASTRUCT pDestination, PDATASTRUCT pSource);
INT ClearCallBack(PDATASTRUCT pClear);

NTSTATUS GetFullPath( IN PDEVICE_OBJECT DeviceObject,
					 IN PIRP Irp,
					 /*out*/PUNICODE_STRING* pFullPath
					 );
BOOLEAN SfIsDisableDeleteFile(PUNICODE_STRING pSourceFile, CHECKIFEQUAL compareCallBack);

INT InsertElement(PARRAYHEAD pRoot, PCHAR pString, INT nLen);
INT RemoveElement(PARRAYHEAD pRoot, PCHAR pString, INT nLen);
NTSTATUS GetElement(PARRAYHEAD pRoot, INT nPos, PCHAR pString, INT * pLen);

#endif //__SUPPORT_H_KL_2007_05_11__