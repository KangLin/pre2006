/*!
\warning 版权所有 (C) 2007 康林工作室；保留所有权利。
\file    Thread.h
\brief   线程的封装类
\version 1.0
\author  康  林 (kl222@126.com)
\date    2007年9月4日  15:46:37
\par     编译器:
         Microsoft Visual Studio 8.0 —— C/C++ 8.0
*/

#ifndef __THREAD_H_KL_2008_09_04__
#define __THREAD_H_KL_2008_09_04__

#pragma once

class CThread
{
public:
	CThread(void * pPara = NULL);
	virtual ~CThread(void);

	//得到线程的ID
	DWORD GetID();
	//启动线程
	virtual int Start();
	//关闭线程
	virtual int Stop();

	//以下函数仅供线程函数work使用,用户不能调用此公有函数
	void * GetPara();

	//线程的工作函数，其派生类中实现。
	virtual int Run(void * pPara) = 0;

private:
	void * m_pPara;    //传递给线程的参数
	HANDLE m_hThread;  //线程句柄
	DWORD m_dwID;      //线程ID

	//线程函数
	static int Work(void * pThis);
};

#endif //__THREAD_H_KL_2008_09_04__
