/*!
\warning ��Ȩ���� (C) 2007 ���ֹ����ң���������Ȩ����
\file    TestDll.cpp
\brief   ���ڲ��Կ����ͨ�Ż�����
\version 1.0
\author  ��  �� (kl222@126.com)
\date    2007��8��29��  14:39:02
\par     ������:
         Microsoft Visual Studio 8.0 ���� C/C++ 8.0
*/

// TestDll.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "test.h"

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
	TRACE(_T("TestDll ��ʼ��.\n"));

	return nRet;
}

INT _stdcall DoCommand(DWORD dwCmd, CCommand * pCmd)
{
	INT nRet = S_OK;
	TRACE(_T("TestDll DoCommand....\n"));

	CCommand out;

	switch(dwCmd)
	{
	case CMD_TEST_ECHO: //���Ի���
		nRet = OnTestEcho(pCmd, &out);
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
	TRACE(_T("TestDll ����.\n"));

	return nRet;
}

INT _stdcall  SetContext(void* pContext)
{
	INT nRet=S_OK;
	TRACE(_T("TestDll SetContext\n"));
	g_Connect = (PCONNECT)pContext;
	return nRet;
}