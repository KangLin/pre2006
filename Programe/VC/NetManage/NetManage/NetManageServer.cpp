/*!
\warning 版权所有 (C) 2007 康林工作室；保留所有权利。
\file    NetManageServer.cpp
\brief   服务
\version 1.0
\author  康  林 (kl222@126.com)
\date    2007年7月13日  15:48:35
\par     编译器:
         Microsoft Visual Studio 8.0 —— C/C++ 8.0
*/

#include "StdAfx.h"
#include "NetManageServer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CNetManageServer::CNetManageServer(void)
{
	m_pDll = NULL;
}

CNetManageServer::~CNetManageServer(void)
{
	
}

int CNetManageServer::SetDLL(CDll * pDll)
{
	m_pDll = pDll;
	return S_OK;
}


/*!
\brief   处理解包后的命令
\param   CCommand & cmd   ：命令
\param   PCONNECT pConnect：上下文指针
\return  类型为 int 。成功返回S_OK，否则返回FALSE。
\version 1.0
\author  康  林
\date    2007-8-21 17:49:37
*/
int CNetManageServer::ProcessCommand(CCommand & cmd, PCONNECT pConnect)
{
	int nRet = S_OK;

	//派遣命令
	DWORD dwCmd = cmd.GetCommand();
	list<CDll::PDLL_STRUCT>::iterator itDll;
	ASSERT(m_pDll);
	for(itDll = m_pDll->m_lstDll.begin(); itDll != m_pDll->m_lstDll.end(); itDll++)
	{
		CDll::PDLL_STRUCT pDs = *itDll;
		if(pDs->pDoCommand)
		{
			//设置上下文，把PCONNECT设置给DLL。
			//如果DLL需要发送数据的话，则可以实现这个函数，并把这个参数保存。
			if(pDs->pSetContext)
			{
				pDs->pSetContext(pConnect);
			}
			//执行命令
			pDs->pDoCommand(dwCmd, &cmd);
		} // 结束 if(pDs->pDoCommand)
	}// 结束 for(itDll = m_pDll->m_lstDll.begin(); itDll != m_pDll->m_lstDll.end(); itDll++)

	return nRet;
}