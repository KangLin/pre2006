/*!
\warning ��Ȩ���� (C) 2007 ���ֹ����ң���������Ȩ����
\file    NetManageServer.cpp
\brief   ����
\version 1.0
\author  ��  �� (kl222@126.com)
\date    2007��7��13��  15:48:35
\par     ������:
         Microsoft Visual Studio 8.0 ���� C/C++ 8.0
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
\brief   �������������
\param   CCommand & cmd   ������
\param   PCONNECT pConnect��������ָ��
\return  ����Ϊ int ���ɹ�����S_OK�����򷵻�FALSE��
\version 1.0
\author  ��  ��
\date    2007-8-21 17:49:37
*/
int CNetManageServer::ProcessCommand(CCommand & cmd, PCONNECT pConnect)
{
	int nRet = S_OK;

	//��ǲ����
	DWORD dwCmd = cmd.GetCommand();
	list<CDll::PDLL_STRUCT>::iterator itDll;
	ASSERT(m_pDll);
	for(itDll = m_pDll->m_lstDll.begin(); itDll != m_pDll->m_lstDll.end(); itDll++)
	{
		CDll::PDLL_STRUCT pDs = *itDll;
		if(pDs->pDoCommand)
		{
			//���������ģ���PCONNECT���ø�DLL��
			//���DLL��Ҫ�������ݵĻ��������ʵ�������������������������档
			if(pDs->pSetContext)
			{
				pDs->pSetContext(pConnect);
			}
			//ִ������
			pDs->pDoCommand(dwCmd, &cmd);
		} // ���� if(pDs->pDoCommand)
	}// ���� for(itDll = m_pDll->m_lstDll.begin(); itDll != m_pDll->m_lstDll.end(); itDll++)

	return nRet;
}