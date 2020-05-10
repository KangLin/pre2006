/*!
\warning 版权所有 (C) 2007 康林工作室；保留所有权利。
\file    IOThread.h
\brief   用于管理 IO 线程
\version 1.0
\author  康  林 (kl222@126.com)
\date    2007年7月4日  17:07:26
\par     编译器:
         Microsoft Visual Studio 8.0 —— C/C++ 8.0
*/

#ifndef __IOTHREAD_H_KL_2007_07_04__
#define __IOTHREAD_H_KL_2007_07_04__

#pragma once

class CIOThread
{
public:
	CIOThread(void);
	~CIOThread(void);

	BOOL AddSocket(CSocket * s);
	BOOL RemoveSocket(CSocket * s);

	// 套节字对象
	typedef struct _SOCKET_OBJ
	{
		SOCKET s;                                // 套节字句柄
		HANDLE event;                            // 与此套节字相关联的事件对象句柄
		sockaddr_in addrRemote;                  // 客户端地址信息
	} SOCKET_OBJ, *PSOCKET_OBJ;

	// 线程对象
	typedef struct _THREAD_OBJ
	{
		HANDLE events[WSA_MAXIMUM_WAIT_EVENTS];  // 记录当前线程要等待的事件对象的句柄
		int nSocketCount;                        // 记录当前线程处理的套节字的数量 <=  WSA_MAXIMUM_WAIT_EVENTS

		list < PSOCKET_OBJ > pSock;              // 当前线程处理的套节字对象列表，pSockHeader指向表头
		
		CRITICAL_SECTION cs;                     // 关键代码段变量，为的是同步对本结构的访问

	} THREAD_OBJ, *PTHREAD_OBJ;

private:
	// 线程列表
	map < PSOCKET_OBJ, PTHREAD_OBJ > m_pThread;  // 指向线程对象列表表头
	CRITICAL_SECTION m_cs;                       // 同步对此全局变量的访问


	// 状态信息
	LONG m_nTatolConnections;                    // 总共连接数量
	LONG m_nCurrentConnections;                  // 当前连接数量

	static DWORD ServiceThread(LPVOID lpParam);
};

#endif //__IOTHREAD_H_KL_2007_07_04__