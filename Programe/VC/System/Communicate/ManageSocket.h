/*!
\warning ��Ȩ���� (C) 2007 ���ֹ����ң���������Ȩ����
\file    ManageSocket.h
\brief   Socket �����࣬���ڹ��� Socket
\version 1.0
\author  ��  �� (kl222@126.com)
\date    2007��7��5��  11:01:49
\par     ������:
         Microsoft Visual Studio 8.0 ���� C/C++ 8.0
*/

#pragma once

#include ".\socket.h"
#include <vector>
#include <list>
using namespace std;

class CManageSocket
{
public:
	CManageSocket(void);
	virtual ~CManageSocket(void);

	int AddLister(Network::CSocketListener * sock, Network::CSocketServer * server);
	int RemoveLister(Network::CSocketListener * sock);
	int AddConncet(Network::CSocket * sock, Network::CSocketServer * server);
	int RemoveConnect(Network::CSocket * sock);

	int OnRun();

private:
	//Socket ��Ϣ�ṹ
	typedef struct _SOCKETINFO
	{
		union
		{
			Network::CSocket          * Connect;   //���� Socket
			Network::CSocketListener  * Listener;  //���� Socket
		} Sock;
		bool IsLister;                             //��������������������ĸ���Ա��
												   //TRUE���Ǽ��� Socket������Ϊ���� Socket

		HANDLE hEvent;                             //�¼�����
		Network::CSocketServer        * Service;   //��Socket��صķ���
	}SOCKETINFO, *PSOCKETINFO;

	//�߳���Ϣ�ṹ
	typedef struct _THREADINFO
	{
		//hEvents[0] Ϊ�߳��˳��ź��¼���WSAEventSelect �źŴ� hEvents[1] ��ʼ
		HANDLE hEvents[WSA_MAXIMUM_WAIT_EVENTS];  //��¼��ǰ�߳�Ҫ�ȴ����¼�����ľ��
		//int nSocketCount;                         // ��¼��ǰ�̴߳�����׽��ֵ����� <=  WSA_MAXIMUM_WAIT_EVENTS
		vector < PSOCKETINFO > socket;            //���̴߳���� Socket
		CRITICAL_SECTION cs;                      //�ؼ�����α�����Ϊ����ͬ���Ա��ṹ�ķ���
		BOOL* pbExit;
	}THREADINFO, *PTHREADINFO;

	//�̳߳ؽṹ
	typedef struct _THREADPOLLINFO
	{
		BOOL bIsLister;
		list < PTHREADINFO > m_Thread;            //�����̳߳�
		CRITICAL_SECTION cs;                      //�ؼ�����α�����Ϊ����ͬ���Ա��ṹ�ķ���
	}THREADPOLLINFO, *PTHREADPOLLINFO;

	//���ݸ������߳�(ProcessThread)�Ĳ����ṹ
	typedef struct _PARAMETER
	{
		CManageSocket * pManageSocket;
		PTHREADINFO pThread;
		HANDLE* phEvent;
		PTHREADPOLLINFO pPool;
	}PARAMETER, *PPARAMETER;

	//���� Socket
	int AddSocketObj(PTHREADINFO pThread, PSOCKETINFO pSocket);
	int RemoveSocketObj(PTHREADINFO pThread, PSOCKETINFO pSocket);
	int FreeSocketObj(PSOCKETINFO pSocket);
	int RebuildArray(PTHREADINFO pThread);

	//�����߳�
	int FreeThreadObj(PTHREADINFO pThread);
	PTHREADINFO AddThread(PTHREADPOLLINFO pPool);
	int RemoveThread(PTHREADPOLLINFO pPool, PTHREADINFO pThread);

	//�����̳߳�
	int AddSocketObj(PTHREADPOLLINFO pPool, PSOCKETINFO pSocket);
	int FreePool(PTHREADPOLLINFO pPool);

	int HandleIO(PTHREADINFO pThread, PSOCKETINFO pSocket);
	static DWORD ProcessThread(LPVOID lpPara);

private:
	THREADPOLLINFO m_ListerThreadPool;            //�����̳߳�
	THREADPOLLINFO m_IOThreadPool;                //IO�����̳߳�

	HANDLE m_hOnRunExit;                          //OnRun �����˳��¼�
	int m_dwOnRunDelay;

	///////////////////////////////////////////////////////////////////////////////////////////////
	//                                    ������
	///////////////////////////////////////////////////////////////////////////////////////////////
	LONG m_TotalListerThreadNumber;               //�����߳��ܸ���
	LONG m_CurrentListerThreadNumber;             //��ǰ�����̸߳���
	LONG m_TotalIOThreadNumber;                   //IO�����߳��ܸ���
	LONG m_CurrentIOThreadNumber;                 //��ǰIO�����̸߳���

	LONG m_TotalConnectNumber;                    //�ܹ����ӵĴ���
	LONG m_CurrentConnectNumber;                  //��ǰ���ӵĸ���
	LONG m_CurrentListerNumber;                   //��ǰ������
	LONG m_TotalListerNumber;


	///////////////////////////////////////////////////////////////////////////////////////////////
	//                                 Lister �����߳�
	///////////////////////////////////////////////////////////////////////////////////////////////
	typedef struct _LISTERINFO
	{
		PTHREADINFO pThread;
		PSOCKETINFO pSocket;
		Network::CSocket * Connect;
	}LISTERINFO, *PLISTERINFO;
	list < PLISTERINFO > m_lstLister;
	CRITICAL_SECTION m_csLister;                  //�ؼ�����α�����Ϊ����ͬ��m_lstLister�ķ���
	HANDLE m_hLister;                             //֪ͨ ProcessListerThread ���¼�����
	BOOL * m_pbExitListerThread;                  //ָʾ��������

	int AddLister(PLISTERINFO lpListerInfo);      //��m_lstLister�м���һ����
	PLISTERINFO GetLister();                      //�õ�m_lstLister�����е���ǰһ�������������ɾ����

	//���������ӵ� lister Socket
	static DWORD ProcessListerThread(LPVOID lpPara);

};
