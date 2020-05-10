/*!
\warning ��Ȩ���� (C) 2007 ���ֹ����ң���������Ȩ����
\file    IOThread.h
\brief   ���ڹ��� IO �߳�
\version 1.0
\author  ��  �� (kl222@126.com)
\date    2007��7��4��  17:07:26
\par     ������:
         Microsoft Visual Studio 8.0 ���� C/C++ 8.0
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

	// �׽��ֶ���
	typedef struct _SOCKET_OBJ
	{
		SOCKET s;                                // �׽��־��
		HANDLE event;                            // ����׽�����������¼�������
		sockaddr_in addrRemote;                  // �ͻ��˵�ַ��Ϣ
	} SOCKET_OBJ, *PSOCKET_OBJ;

	// �̶߳���
	typedef struct _THREAD_OBJ
	{
		HANDLE events[WSA_MAXIMUM_WAIT_EVENTS];  // ��¼��ǰ�߳�Ҫ�ȴ����¼�����ľ��
		int nSocketCount;                        // ��¼��ǰ�̴߳�����׽��ֵ����� <=  WSA_MAXIMUM_WAIT_EVENTS

		list < PSOCKET_OBJ > pSock;              // ��ǰ�̴߳�����׽��ֶ����б�pSockHeaderָ���ͷ
		
		CRITICAL_SECTION cs;                     // �ؼ�����α�����Ϊ����ͬ���Ա��ṹ�ķ���

	} THREAD_OBJ, *PTHREAD_OBJ;

private:
	// �߳��б�
	map < PSOCKET_OBJ, PTHREAD_OBJ > m_pThread;  // ָ���̶߳����б��ͷ
	CRITICAL_SECTION m_cs;                       // ͬ���Դ�ȫ�ֱ����ķ���


	// ״̬��Ϣ
	LONG m_nTatolConnections;                    // �ܹ���������
	LONG m_nCurrentConnections;                  // ��ǰ��������

	static DWORD ServiceThread(LPVOID lpParam);
};

#endif //__IOTHREAD_H_KL_2007_07_04__