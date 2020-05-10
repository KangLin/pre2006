/*!
\warning 版权所有 (C) 2007 康林工作室；保留所有权利。
\file    ProcessDLL.cpp
\brief   进程DLL的导出函数实现文件
\version 1.0
\author  康  林 (kl222@126.com)
\date    2007年8月14日  17:16:50
\par     编译器:
         Microsoft Visual Studio 8.0 —— C/C++ 8.0
*/

#include "stdafx.h"
#include "ProcessCommand.h"

typedef struct _CONNECT
{
	Network::CSocket * pSocket;  //!< 连接的Socket
	CReceiveData * pReceive;     //!< 接发数据类指针
	CSend * pSend;               //!< 发送数据类指针
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
	TRACE(_T("Process 初始化.\n"));

	return nRet;
}

INT _stdcall DoCommand(DWORD dwCmd, CCommand * pCmd)
{
	INT nRet = S_OK;
	TRACE(_T("Process DoCommand....\n"));

	CCommand out;
	CProcessCommand pi(pCmd);

	switch(dwCmd)
	{
	case CMD_QUERY_PROCESS:
		nRet = pi.QueryProcess(&out);
		break;
	case CMD_ANSWER_PROCESS:
		break;
	case CMD_QUERY_ALL_PROCESS:
		nRet = pi.QueryAllProcess(&out);
		break;
	case CMD_ANSWER_ALL_PROCESS:
		break;
	case CMD_QUERY_PROCESS_MODULE:
		nRet = pi.QueryProcessModule(&out);
		break;
	case CMD_ANSWER_PROCESS_MODULE:
		break;
	case CMD_QUERY_ALL_PROCESS_MODULE:
		nRet = pi.QueryAllProcessModule(&out);
		break;
	case CMD_ANSWER_ALL_PROCESS_MODULE:
		break;
	case CMD_QUERY_PROCESS_PATH:
		nRet = pi.QueryProcessPath(&out);
		break;
	case CMD_ANSWER_PROCESS_PATH:
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
			TRACE(_T("异常：%s\n"), e->what());
		}
	} // 结束 if(S_OK != nRet)

	nRet = g_Connect->pSend->Send(&out);

	return nRet;
}

INT _stdcall DoEnd()
{
	INT nRet = S_OK;
	TRACE(_T("Process 结束.\n"));

	return nRet;
}

INT _stdcall  SetContext(void* pContext)
{
	INT nRet=S_OK;
	TRACE(_T("Process SetContext\n"));
	g_Connect = (PCONNECT)pContext;
	return nRet;
}