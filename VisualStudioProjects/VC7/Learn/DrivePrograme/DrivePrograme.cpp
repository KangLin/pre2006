// DrivePrograme.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "DrivePrograme.h"

#include <devguid.h>

#define DWORD_PTR DWORD
#define ULONG_PTR DWORD


extern "C" { 
#include <hidsdi.h>
}
// 需加入hid.lib

#include <setupapi.h>
// 需加入setupapi.lib
#pragma comment(lib,"C:\\NTDDK\\lib\\i386\\free\\setupapi")

#include <regstr.h>
#include <winbase.h>

#include <cfgmgr32.h>
// 需要加入cfgmgr32.lib
#pragma comment(lib,"C:\\NTDDK\\lib\\i386\\free\\cfgmgr32")

#include <initguid.h>


DEFINE_GUID(GUID_DEVINTERFACE_USB_DEVICE,
  0xA5DCBF10L, 0x6530, 0x11D2, 0x90, 0x1F, 0x00, 0xC0, 0x4F, 0xB9, 0x51, 0xED);
#define GUID_CLASS_USB_DEVICE           GUID_DEVINTERFACE_USB_DEVICE

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// The one and only application object

CWinApp theApp;

using namespace std;

BOOL DisableNetInterface(LPCTSTR lpszHardwareId, DWORD dwProperty, BOOL bStatus);

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// initialize MFC and print and error on failure
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: change error code to suit your needs
		cerr << _T("Fatal Error: MFC initialization failed") << endl;
		return 1;
	}
	
	DisableNetInterface(_T("PCI\\VEN_10EC&DEV_8139&SUBSYS_813910EC&REV_10"), SPDRP_HARDWAREID, false);

	return nRetCode;
}

/*******************************************************************************************************
函数名：DisableNetInterface
描  述：
参  数：
        LPCTSTR lpszHardwareId：设备ID
		DWORD dwProperty      ：说明lpszHardwareId是何值。
		BOOL bStatus          ：TRUE，禁用设备。FALSE，启用设备。
返回值：类型为 BOOL 。
版  本：1.0
作  者：康  林
时  间：2005年11月23日 19:15:31
*******************************************************************************************************/
BOOL DisableNetInterface(LPCTSTR lpszHardwareId, DWORD dwProperty, BOOL bStatus)
{
	//设备的ID。位于:HKEY_LOCAL_MACHINE\system\currentcontrolset
    //IN LPTSTR HardwareId=_T("PCI\\VEN_10EC&DEV_8139&SUBSYS_813910EC&REV_10");
	//IN LPTSTR HardwareId="USB\\Vid_0457&Pid_0163";
	//IN LPTSTR HardwareId="{4d36e972-e325-11ce-bfc1-08002be10318}" ;
	//IN LPTSTR HardwareId="{4D36E972-E325-11CE-BFC1-08002BE10318}" ;
    //硬件ComponentId，注册表地址：system\currentcontrolset\class\{4D36E972-E325-11CE-BFC1-08002BE10318}\0000

    DWORD NewState ;
    
    DWORD i,err ;
    BOOL Found=FALSE ;
    
    HDEVINFO hDevInfo ;
    SP_DEVINFO_DATA spDevInfoData ;
    
    if(bStatus)
	{
		//禁用
		NewState = DICS_DISABLE;
    }
    else 
    {
		//启用
		NewState = DICS_ENABLE;
	}

    //访问系统的硬件库
	hDevInfo = SetupDiGetClassDevs(NULL, "PCI", NULL, DIGCF_ALLCLASSES | DIGCF_PRESENT);
	if(hDevInfo == INVALID_HANDLE_VALUE)
    {
        TRACE(_T("访问系统硬件出错！\n"));
        return FALSE ;
    }
    
    //枚举硬件，获得需要的接口
	spDevInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
	BOOL flagEnum;
	for(i = 0; flagEnum = SetupDiEnumDeviceInfo(hDevInfo, i, &spDevInfoData); i++)
    {
        DWORD DataT ;
        
        CHAR buffer[2400]={0};
		DWORD buffersize=0 ;
        
        //获得硬件的属性值
		buffersize = sizeof(buffer);
		while(!SetupDiGetDeviceRegistryProperty(
			hDevInfo,
			&spDevInfoData,
			dwProperty, //SPDRP_HARDWAREID, //SPDRP_CLASSGUID,
			&DataT,
			(PBYTE)buffer,
			buffersize,
			&buffersize))
        {
			
			if(GetLastError() == ERROR_INVALID_DATA)
            {
                //不存在HardwareID. Continue.
                break ;
			}
			else if(GetLastError() == ERROR_INSUFFICIENT_BUFFER)
            {
                //buffer size不对.
                if(buffer)
					LocalFree(buffer);
//                buffer=(char*)LocalAlloc(LPTR,buffersize);
            }
            else 
            {
                //未知错误
                goto cleanup_DeviceInfo ;
            }
        }
        
        if(GetLastError()==ERROR_INVALID_DATA)
			continue ;
        
		if(NULL == buffer)
		{
		//	LocalFree(buffer);
			continue ;
		}
		
		if(!strcmpi(lpszHardwareId, buffer))
        {

			SP_PROPCHANGE_PARAMS spPropChangeParams ;
            
			spPropChangeParams.ClassInstallHeader.cbSize = sizeof(SP_CLASSINSTALL_HEADER);
			spPropChangeParams.ClassInstallHeader.InstallFunction = DIF_PROPERTYCHANGE;
			spPropChangeParams.Scope = DICS_FLAG_GLOBAL;
			spPropChangeParams.StateChange = NewState;
            //禁用：DICS_DISABLE，DICS_ENABLE启用

			if(!SetupDiSetClassInstallParams(hDevInfo, &spDevInfoData, (SP_CLASSINSTALL_HEADER * )&spPropChangeParams, sizeof(spPropChangeParams)))
            {
				DWORD errorcode = GetLastError();
            }
            
			if(!SetupDiCallClassInstaller(DIF_PROPERTYCHANGE, hDevInfo, &spDevInfoData))
            {
				DWORD errorcode = GetLastError();
            }
            
			switch(NewState)
			{
			case DICS_DISABLE :
				TRACE("成功禁用网络！\n");
				break ;
			case DICS_ENABLE :
				TRACE("成功启用网络！\n");
				break ;
			} // 结束 switch(NewState)
            
		} // 结束 if(!strcmpi(lpszHardwareId, buffer))
        
    } // 结束 for(i = 0; flagEnum = SetupDiEnumDeviceInfo(hDevInfo, i, &spDevInfoData); i++)
    
    //退出时，清理工作环境
cleanup_DeviceInfo :
	err = GetLastError();
    SetupDiDestroyDeviceInfoList(hDevInfo);
    SetLastError(err);
    
    return TRUE ;
}
