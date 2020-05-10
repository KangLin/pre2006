/*!
\warning 版权所有 (C) 2008 康林工作室；保留所有权利。
\file    Thread.cpp
\brief   线程类
         用法:1、先实例化一个 CThread 对象
		      2、再调用 Start() 函数启动线程
\version 1.0
\author  康  林 (kl222@126.com)
\date    2008年4月5日  14:17:52
\par     编译器:
         Microsoft Visual Studio 8.0 —— C/C++ 8.0
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
	//	CTException e(_T("CTread 构造函数中建立线程失败"), GetLastError());
	//	throw e;
	//} // 结束 if(S_FALSE == dwRet)
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
	}// 结束 if(NULL == m_hThread)
	TRACE(_T("create thread id:0x%x\n"), m_dwID);
	return S_OK;
}

int CThread::Stop()
{
	TRACE(_T("CThread::Stop thread[0x%x]\n"), GetID());
	if(m_hThread)
	{
		//修改:这里的退出方式不是最完美的,存在资源泄漏.
		DWORD dwCode = 0;
		if(GetExitCodeThread(m_hThread, &dwCode))
		{
			while(STILL_ACTIVE == dwCode)
			{
				::TerminateThread(m_hThread, 100);
				GetExitCodeThread(m_hThread, &dwCode);
			} // 结束 while(STILL_ACTIVE == dwCode)
		} // 结束 if(GetExitCodeThread(m_hThread, &dwCode))
		CloseHandle(m_hThread);
		m_hThread = NULL;
	}// 结束 if(m_hThread)

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
	////因为在构造函数中启动线程,所以可能存在构造函数没有执行完,
	////线程就开始执行,出现R6025错误.所以在此休眠一段时间.
	//Sleep(10);
	
	CThread * p = (CThread * )pThis;

	p->Run(p->GetPara());

	return 0;
}
