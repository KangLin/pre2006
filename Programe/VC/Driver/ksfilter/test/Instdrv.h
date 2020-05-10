#pragma once
#include <Winsvc.h>

/****************************************************************************
*
*    FUNCTION: InstallDriver( IN SC_HANDLE, IN LPCTSTR, IN LPCTSTR)
*
*    PURPOSE: Creates a driver service.
*
****************************************************************************/
BOOL InstallDriver(IN SC_HANDLE SchSCManager, IN LPCTSTR DriverName, IN LPCTSTR ServiceExe);

/****************************************************************************
*
*    FUNCTION: StartDriver( IN SC_HANDLE, IN LPCTSTR)
*
*    PURPOSE: Starts the driver service.
*
****************************************************************************/
BOOL StartDriver(IN SC_HANDLE SchSCManager, IN LPCTSTR DriverName);

/****************************************************************************
*
*    FUNCTION: OpenDevice( IN LPCTSTR, HANDLE *)
*
*    PURPOSE: Opens the device and returns a handle if desired.
*
****************************************************************************/
BOOL OpenDevice(IN LPCTSTR DriverName, HANDLE * lphDevice);

/****************************************************************************
*
*    FUNCTION: StopDriver( IN SC_HANDLE, IN LPCTSTR)
*
*    PURPOSE: Has the configuration manager stop the driver (unload it)
*
****************************************************************************/
BOOL StopDriver(IN SC_HANDLE SchSCManager, IN LPCTSTR DriverName);


/****************************************************************************
*
*    FUNCTION: RemoveDriver( IN SC_HANDLE, IN LPCTSTR)
*
*    PURPOSE: Deletes the driver service.
*
****************************************************************************/
BOOL RemoveDriver(IN SC_HANDLE SchSCManager, IN LPCTSTR DriverName);


/****************************************************************************
*
*    FUNCTION: UnloadDeviceDriver( const TCHAR *)
*
*    PURPOSE: Stops the driver and has the configuration manager unload it.
*
****************************************************************************/
BOOL UnloadDeviceDriver(const TCHAR * Name, const TCHAR * Machine = NULL);


BOOL LoadDeviceDriver(const TCHAR * Name, const TCHAR * Path, const TCHAR * Machine = NULL);

/****************************************************************************
*
*    FUNCTION: LoadDeviceDriver( const TCHAR, const TCHAR, HANDLE *)
*
*    PURPOSE: Registers a driver with the system configuration manager 
*	 and then loads it.
*
****************************************************************************/
BOOL LoadDeviceDriverAndOpen( const TCHAR * Name, const TCHAR * Path, 
							 HANDLE * lphDevice, PDWORD Error);
