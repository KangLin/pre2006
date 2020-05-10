// SystemInfo.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include ".\SystemCommand.h"

typedef struct _CONNECT
{
	Network::CSocket * pSocket;  //!< ���ӵ�Socket
	CReceiveData * pReceive;     //!< �ӷ�������ָ��
	CSend * pSend;               //!< ����������ָ��
} CONNECT, *PCONNECT;

PCONNECT g_Connect = NULL;

#ifdef _MANAGED
#pragma managed(push, off)
#endif

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
    return TRUE;
}

#ifdef _MANAGED
#pragma managed(pop)
#endif

INT _stdcall DoInitalize()
{
	INT nRet = S_OK;
	TRACE(_T("SystemInfo ��ʼ��.\n"));

	return nRet;
}

INT _stdcall DoCommand(DWORD dwCmd, CCommand * pCmd)
{
	INT nRet = S_OK;
	TRACE(_T("SystemInfo DoCommand....\n"));

	CCommand out;
	CSystemCommand sc(pCmd);
	switch(dwCmd)
	{
	case CMD_QUERY_WMI_WIN32_OPERATING_SYSTEM_INFORMATION:
		nRet = sc.QueryWMIWin32OperationSystemInformaion(&out);
		break;
	case CMD_QUERY_WMI_COMPUTER_SYSTEM_INFORMATION:
		nRet = sc.QueryWMIComputerSystemInformation(&out);
		break;
	case CMD_QUERY_WMI_SERVICE_INFORMATION:
		nRet = sc.QueryWMIServiceInformation(&out);
		break;
	default:
		break;
	}

	if(S_OK != nRet)
	{
		try
		{
			out.SetCommand(out.GetCommand());
			out.AddPara((DWORD)S_FALSE);
		}
		catch (CTException* e)
		{
			TRACE(_T("�쳣��%s\n"), e->what());
		}
	} // ���� if(S_OK != nRet)

	nRet = g_Connect->pSend->Send(&out);

	return nRet;
}

INT _stdcall DoEnd()
{
	INT nRet = S_OK;
	TRACE(_T("SystemInfo ����.\n"));

	return nRet;
}

INT _stdcall  SetContext(void* pContext)
{
	INT nRet=S_OK;
	TRACE(_T("SystemInfo SetContext\n"));
	g_Connect = (PCONNECT)pContext;
	return nRet;
}