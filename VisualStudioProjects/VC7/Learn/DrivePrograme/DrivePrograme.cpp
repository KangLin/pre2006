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
// �����hid.lib

#include <setupapi.h>
// �����setupapi.lib
#pragma comment(lib,"C:\\NTDDK\\lib\\i386\\free\\setupapi")

#include <regstr.h>
#include <winbase.h>

#include <cfgmgr32.h>
// ��Ҫ����cfgmgr32.lib
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
��������DisableNetInterface
��  ����
��  ����
        LPCTSTR lpszHardwareId���豸ID
		DWORD dwProperty      ��˵��lpszHardwareId�Ǻ�ֵ��
		BOOL bStatus          ��TRUE�������豸��FALSE�������豸��
����ֵ������Ϊ BOOL ��
��  ����1.0
��  �ߣ���  ��
ʱ  �䣺2005��11��23�� 19:15:31
*******************************************************************************************************/
BOOL DisableNetInterface(LPCTSTR lpszHardwareId, DWORD dwProperty, BOOL bStatus)
{
	//�豸��ID��λ��:HKEY_LOCAL_MACHINE\system\currentcontrolset
    //IN LPTSTR HardwareId=_T("PCI\\VEN_10EC&DEV_8139&SUBSYS_813910EC&REV_10");
	//IN LPTSTR HardwareId="USB\\Vid_0457&Pid_0163";
	//IN LPTSTR HardwareId="{4d36e972-e325-11ce-bfc1-08002be10318}" ;
	//IN LPTSTR HardwareId="{4D36E972-E325-11CE-BFC1-08002BE10318}" ;
    //Ӳ��ComponentId��ע����ַ��system\currentcontrolset\class\{4D36E972-E325-11CE-BFC1-08002BE10318}\0000

    DWORD NewState ;
    
    DWORD i,err ;
    BOOL Found=FALSE ;
    
    HDEVINFO hDevInfo ;
    SP_DEVINFO_DATA spDevInfoData ;
    
    if(bStatus)
	{
		//����
		NewState = DICS_DISABLE;
    }
    else 
    {
		//����
		NewState = DICS_ENABLE;
	}

    //����ϵͳ��Ӳ����
	hDevInfo = SetupDiGetClassDevs(NULL, "PCI", NULL, DIGCF_ALLCLASSES | DIGCF_PRESENT);
	if(hDevInfo == INVALID_HANDLE_VALUE)
    {
        TRACE(_T("����ϵͳӲ������\n"));
        return FALSE ;
    }
    
    //ö��Ӳ���������Ҫ�Ľӿ�
	spDevInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
	BOOL flagEnum;
	for(i = 0; flagEnum = SetupDiEnumDeviceInfo(hDevInfo, i, &spDevInfoData); i++)
    {
        DWORD DataT ;
        
        CHAR buffer[2400]={0};
		DWORD buffersize=0 ;
        
        //���Ӳ��������ֵ
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
                //������HardwareID. Continue.
                break ;
			}
			else if(GetLastError() == ERROR_INSUFFICIENT_BUFFER)
            {
                //buffer size����.
                if(buffer)
					LocalFree(buffer);
//                buffer=(char*)LocalAlloc(LPTR,buffersize);
            }
            else 
            {
                //δ֪����
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
            //���ã�DICS_DISABLE��DICS_ENABLE����

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
				TRACE("�ɹ��������磡\n");
				break ;
			case DICS_ENABLE :
				TRACE("�ɹ��������磡\n");
				break ;
			} // ���� switch(NewState)
            
		} // ���� if(!strcmpi(lpszHardwareId, buffer))
        
    } // ���� for(i = 0; flagEnum = SetupDiEnumDeviceInfo(hDevInfo, i, &spDevInfoData); i++)
    
    //�˳�ʱ������������
cleanup_DeviceInfo :
	err = GetLastError();
    SetupDiDestroyDeviceInfoList(hDevInfo);
    SetLastError(err);
    
    return TRUE ;
}
