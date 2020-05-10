/*!
\warning ��Ȩ���� (C) 2008 ���ֹ����ң���������Ȩ����
\file    Thread.cpp
\brief   �߳���
         �÷�:1����ʵ����һ�� CThread ����
		      2���ٵ��� Start() ���������߳�
\version 1.0
\author  ��  �� (kl222@126.com)
\date    2008��4��5��  14:17:52
\par     ������:
         Microsoft Visual Studio 8.0 ���� C/C++ 8.0
*/
#include "StdAfx.h"
#include "Thread.h"

CThread::CThread(void* pPara)
{
	m_pPara = pPara;
	m_hThread = NULL;
	m_dwID = 0;

	//int dwRet = Start();
	//if(S_FALSE == dwRet)
	//{
	//	CTException e(_T("CTread ���캯���н����߳�ʧ��"), GetLastError());
	//	throw e;
	//} // ���� if(S_FALSE == dwRet)
}

CThread::~CThread(void)
{
	TRACE(_T("CThread::~CThread thread[0x%x]\n"), m_dwID);
	//Stop();
}

int CThread::Start()
{
	m_hThread = ::CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Work, this, NULL, &m_dwID);
	if(NULL == m_hThread)
	{
		return S_FALSE;
	}// ���� if(NULL == m_hThread)
	TRACE(_T("create thread id:0x%x\n"), m_dwID);
	return S_OK;
}

int CThread::Stop()
{
	TRACE(_T("CThread::Stop thread[0x%x]\n"), GetID());
	if(m_hThread)
	{
		//�޸�:������˳���ʽ������������,������Դй©.
		DWORD dwCode = 0;
		if(GetExitCodeThread(m_hThread, &dwCode))
		{
			while(STILL_ACTIVE == dwCode)
			{
				::TerminateThread(m_hThread, 100);
				GetExitCodeThread(m_hThread, &dwCode);
			} // ���� while(STILL_ACTIVE == dwCode)
		} // ���� if(GetExitCodeThread(m_hThread, &dwCode))
		CloseHandle(m_hThread);
		m_hThread = NULL;
	}// ���� if(m_hThread)

	return S_OK;
}

DWORD CThread::GetID()
{
	return m_dwID;
}

void * CThread::GetPara()
{
	return m_pPara;
}

int CThread::Work(void * pThis)
{
	////��Ϊ�ڹ��캯���������߳�,���Կ��ܴ��ڹ��캯��û��ִ����,
	////�߳̾Ϳ�ʼִ��,����R6025����.�����ڴ�����һ��ʱ��.
	//Sleep(10);
	
	CThread * p = (CThread * )pThis;

	p->Run(p->GetPara());

	return 0;
}
